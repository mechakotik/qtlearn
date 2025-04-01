#include "ray.hpp"

rc::Ray::Ray(const QPointF& origin, const QVector2D& direction) : origin(origin), direction(direction) {}

rc::Ray::Ray(const QPointF& begin, const QPointF& end) : origin(begin) {
    direction = QVector2D(end - begin).normalized();
}

QPointF rc::Ray::getOrigin() const { return origin; }
QVector2D rc::Ray::getDirection() const { return direction; }
float rc::Ray::getAngle() const { return std::atan2(direction.y(), direction.x()); }

rc::Ray rc::Ray::rotate(float angle) const {
    float ang = getAngle() + angle;
    QVector2D newDirection(std::cos(ang), std::sin(ang));
    return Ray(origin, newDirection);
}
