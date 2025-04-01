#include "polygon.hpp"
#include <QPointF>
#include <QVector2D>

void rc::Polygon::add(QPointF vertex) { vertices.push_back(vertex); }
void rc::Polygon::setLast(QPointF vertex) { vertices.back() = vertex; }
void rc::Polygon::pop() { vertices.pop_back(); }
int rc::Polygon::size() const { return static_cast<int>(vertices.size()); }
QPointF rc::Polygon::at(int index) const { return vertices.at(index); }

std::optional<QPointF> rc::Polygon::intersect(const Ray& ray) const {
    float l = 0, r = 1e6, eps = 0.01;
    for(int it = 0; it < 100; it++) {
        float mid = (l + r) / 2;
        QPointF end = (QVector2D(ray.getOrigin()) + ray.getDirection() * mid).toPointF();
        if(intersects(ray.getOrigin(), end)) {
            r = mid - eps;
        } else {
            l = mid + eps;
        }
    }
    if(r > 8e5) {
        return std::nullopt;
    }
    return (QVector2D(ray.getOrigin()) + ray.getDirection() * l).toPointF();
}

bool rc::Polygon::intersects(const QPointF& a, const QPointF& b) const {
    for(int i = 0; i < vertices.size(); i++) {
        QPointF c = vertices.at(i);
        QPointF d = vertices.at((i + 1) % vertices.size());

        float s1 = (a.x() - c.x()) * (d.y() - c.y()) - (a.y() - c.y()) * (d.x() - c.x());
        float s2 = (b.x() - c.x()) * (d.y() - c.y()) - (b.y() - c.y()) * (d.x() - c.x());
        float s3 = (c.x() - a.x()) * (b.y() - a.y()) - (c.y() - a.y()) * (b.x() - a.x());
        float s4 = (d.x() - a.x()) * (b.y() - a.y()) - (d.y() - a.y()) * (b.x() - a.x());
        if(s1 * s2 <= 0 && s3 * s4 <= 0) {
            return true;
        }
    }

    return false;
}
