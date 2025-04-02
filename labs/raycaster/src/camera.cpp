#include "camera.hpp"
#include <QDebug>

QPointF rc::Camera::toGlobal(QPointF point, float height) const { return point * (scale / height) + topLeft; }
QPointF rc::Camera::toLocal(QPointF point, float height) const { return (point - topLeft) * (height / scale); }

void rc::Camera::shift(QPointF delta, float height) {
    topLeft -= delta * (1 / height) * scale;
    normalizeTopLeft();
}

void rc::Camera::rescale(float factor, QPointF mouse, QSizeF size) {
    double dx = mouse.x() / size.width();
    double dy = mouse.y() / size.height();

    if(scale * (1 + factor) < 1.0F) {
        scale = 1.0F;
    } else if(scale * (1 + factor) > 1000.0F) {
        scale = 1000.0F;
    } else {
        scale *= (1 + factor);
        topLeft = topLeft - QPointF(dx, dy) * factor;
        normalizeTopLeft();
    }
}

void rc::Camera::normalizeTopLeft() {
    if(topLeft.x() < -1000) {
        topLeft.setX(-1000);
    }
    if(topLeft.x() > 1000 - scale) {
        topLeft.setX(1000 - scale);
    }
    if(topLeft.y() < -1000) {
        topLeft.setY(-1000);
    }
    if(topLeft.y() > 1000 - scale) {
        topLeft.setY(1000 - scale);
    }
}

QPointF rc::Camera::getTopLeft() const { return topLeft; }
float rc::Camera::getScale() const { return scale; }
