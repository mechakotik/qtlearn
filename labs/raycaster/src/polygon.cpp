#include "polygon.hpp"
#include <QPointF>
#include <QVector2D>

void rc::Polygon::add(QPointF vertex) {
    vertices.push_back(vertex);
    rebuildExtra();
}

void rc::Polygon::setLast(QPointF vertex) {
    vertices.back() = vertex;
    rebuildExtra();
}

void rc::Polygon::pop() {
    vertices.pop_back();
    rebuildExtra();
}

int rc::Polygon::size() const { return static_cast<int>(vertices.size()); }
QPointF rc::Polygon::at(int index) const { return vertices.at(index); }

int rc::Polygon::extraSize() const { return static_cast<int>(extra.size()); }
QPointF rc::Polygon::extraAt(int index) const { return extra.at(index); }

std::optional<QPointF> intersectSegments(const QPointF& a, const QPointF& b, const QPointF& c, const QPointF& d) {
    double x1 = a.x(), y1 = a.y();
    double x2 = b.x(), y2 = b.y();
    double x3 = c.x(), y3 = c.y();
    double x4 = d.x(), y4 = d.y();
    double pxA = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
    double pxB = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    double pyA = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);
    double pyB = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    QPointF res(pxA / pxB, pyA / pyB);
    double eps = 1e-5;
    if(std::min(x1, x2) - eps <= res.x() && res.x() <= std::max(x1, x2) + eps && std::min(x3, x4) - eps <= res.x() && res.x() <= std::max(x3, x4) + eps &&
        std::min(y1, y2) - eps <= res.y() && res.y() <= std::max(y1, y2) + eps && std::min(y3, y4) - eps <= res.y() && res.y() <= std::max(y3, y4) + eps) {
        return res;
    }
    return std::nullopt;
}

namespace {
    double distance(const QPointF& a, const QPointF& b) {
        return std::sqrt((b.x() - a.x()) * (b.x() - a.x()) + (b.y() - a.y()) * (b.y() - a.y()));
    }
}

std::optional<QPointF> rc::Polygon::intersect(const Ray& ray) const {
    QPointF rayBegin = ray.getOrigin();
    QPointF rayEnd = (QVector2D(ray.getOrigin()) + ray.getDirection() * 1e8).toPointF();
    std::optional<QPointF> res;

    for(int i = 0; i < vertices.size(); i++) {
        QPointF cur = vertices.at(i);
        QPointF next = vertices.at((i + 1) % vertices.size());
        std::optional<QPointF> pt = intersectSegments(cur, next, rayBegin, rayEnd);
        if(!pt.has_value()) {
            continue;
        }
        if(!res.has_value() || distance(rayBegin, pt.value()) < distance(rayBegin, res.value())) {
            res = pt;
        }
    }

    return res;
}

void rc::Polygon::rebuildExtra() {
    extra.clear();
    for(int i = 0; i < vertices.size(); i++) {
        for(int j = i + 1; j < vertices.size(); j++) {
            QPointF a = vertices[i];
            QPointF b = vertices[(i + 1) % vertices.size()];
            QPointF c = vertices[j];
            QPointF d = vertices[(j + 1) % vertices.size()];
            std::optional<QPointF> p = intersectSegments(a, b, c, d);
            if(p.has_value()) {
                extra.push_back(p.value());
            }
        }
    }
}
