#include "camera.hpp"

QPointF rc::Camera::toGlobal(QPointF point, float height) const { return point * (scale / height) + topLeft; }
QPointF rc::Camera::toLocal(QPointF point, float height) const { return (point - topLeft) * (height / scale); }

void rc::Camera::shift(QPointF delta, float height) {
    topLeft -= delta * (1 / height) * scale;
}

void rc::Camera::rescale(float factor, QPointF mouse, QSizeF size) {
    double dx = mouse.x() / size.width();
    double dy = mouse.y() / size.height();
    scale *= (1 + factor);
    topLeft = topLeft - QPointF(dx, dy) * factor;
}

QPointF rc::Camera::getTopLeft() const { return topLeft; }
float rc::Camera::getScale() const { return scale; }
