#include "raycaster.hpp"
#include <QPainter>

rc::Raycaster::Raycaster(QQuickItem* parent) : QQuickPaintedItem(parent) {
    connect(this, &rc::Raycaster::modeChanged, this, &rc::Raycaster::redraw);
    connect(this, &rc::Raycaster::lightPositionChanged, this, &rc::Raycaster::redraw);
    clear();
}

void rc::Raycaster::paint(QPainter* painter) {
    drawPolygons(painter);
    if(mode == 2) {
        drawLight(painter);
    }
}

void rc::Raycaster::redraw() {
    update();
}

void rc::Raycaster::drawPolygons(QPainter* painter) {
    painter->setPen(QPen(QColor("#eeeeee"), 2));
    painter->setBrush(QColor("#eeeeee"));
    painter->setRenderHint(QPainter::Antialiasing, true);

    for(int p = 1; p < polygons.size(); p++) {
        for(int i = 0; i < polygons[p].size(); i++) {
            QPointF cur = polygons[p].at(i);
            QPointF next = polygons[p].at((i + 1) % polygons[p].size());
            if(mode != 2) {
                painter->drawEllipse(cur.x() - 4, cur.y() - 4, 8, 8);
            }
            if(i != polygons[p].size () - 1 || p != polygons.size() - 1) {
                painter->drawLine(cur.x(), cur.y(), next.x(), next.y());
            }
        }
    }
}

void rc::Raycaster::drawLight(QPainter* painter) {
    std::vector<QPointF> polygon = getLightPolygon(lightPosition);
    painter->setPen(QPen(QColor("#00000000")));
    painter->setBrush(QColor("#2eeeeeee"));
    painter->drawPolygon(polygon.data(), polygon.size());

    for(float angle = 0; angle < std::numbers::pi * 2; angle += std::numbers::pi / 3) {
        QPointF pos = lightPosition + QPointF(std::cos(angle), std::sin(angle)) * 16;
        std::vector<QPointF> polygon = getLightPolygon(pos);
        painter->drawPolygon(polygon.data(), polygon.size());
    }
}

float distance(const QPointF& a, const QPointF& b) {
    return std::sqrt((b.x() - a.x()) * (b.x() - a.x()) + (b.y() - a.y()) * (b.y() - a.y()));
}

std::vector<QPointF> rc::Raycaster::getLightPolygon(const QPointF& source) {
    std::vector<Ray> rays;
    for(const Polygon& polygon : polygons) {
        for(int i = 0; i < polygon.size(); i++) {
            Ray ray(source, polygon.at(i));
            rays.push_back(ray);
            rays.push_back(ray.rotate(0.01));
            rays.push_back(ray.rotate(-0.01));
        }
    }

    std::ranges::sort(rays, [](const Ray& a, const Ray& b) {
        return a.getAngle() < b.getAngle();
    });

    std::vector<QPointF> res;
    for(const Ray& ray : rays) {
        std::optional<QPointF> pos;
        for(const Polygon& polygon : polygons) {
            std::optional<QPointF> cur = polygon.intersect(ray);
            if(!cur.has_value()) {
                continue;
            }
            if(!pos.has_value() || distance(source, cur.value()) < distance(source, pos.value())) {
                pos = cur;
            }
        }
        if(pos.has_value()) {
            res.push_back(pos.value());
        }
    }

    return res;
}

void rc::Raycaster::newVertex(QPointF point) {
    if(polygons.back().size() == 0) {
        polygons.back().add(point);
    }
    polygons.back().add(point);
    update();
}

void rc::Raycaster::setLastVertex(QPointF point) {
    if(polygons.back().size() == 0) {
        return;
    }
    polygons.back().setLast(point);
    update();
}

void rc::Raycaster::finishPolygon() {
    polygons.back().pop();
    polygons.emplace_back();
    update();
}

void rc::Raycaster::clear() {
    polygons.clear();
    Polygon border;
    border.add({0, 0});
    border.add({2000, 0});
    border.add({2000, 2000});
    border.add({0, 2000});
    polygons.push_back(border);
    polygons.emplace_back();
    update();
}
