#include "polygon.hpp"
#include <QPointF>
#include <QVector2D>

void rc::Polygon::add(QPointF vertex) { vertices.push_back(vertex); }
void rc::Polygon::setLast(QPointF vertex) { vertices.back() = vertex; }
void rc::Polygon::pop() { vertices.pop_back(); }
int rc::Polygon::size() const { return static_cast<int>(vertices.size()); }
QPointF rc::Polygon::at(int index) const { return vertices.at(index); }

std::optional<QPointF> intersectSegments(const QPointF& a, const QPointF& b, const QPointF& c, const QPointF& d) {
    float x1 = a.x(), y1 = a.y();
    float x2 = b.x(), y2 = b.y();
    float x3 = c.x(), y3 = c.y();
    float x4 = d.x(), y4 = d.y();
    float pxA = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
    float pxB = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    float pyA = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);
    float pyB = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    QPointF res(pxA / pxB, pyA / pyB);
    float eps = std::max({std::abs(x1), std::abs(x2), std::abs(x3), std::abs(x4)}) * 1e-12;
    if(std::min(x1, x2) - eps <= res.x() && res.x() <= std::max(x1, x2) + eps && std::min(x3, x4) - eps <= res.x() && res.x() <= std::max(x3, x4) + eps &&
        std::min(y1, y2) - eps <= res.y() && res.y() <= std::max(y1, y2) + eps && std::min(y3, y4) - eps <= res.y() && res.y() <= std::max(y3, y4) + eps) {
        return res;
    }
    return std::nullopt;
}

namespace {
    float distance(const QPointF& a, const QPointF& b) {
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
