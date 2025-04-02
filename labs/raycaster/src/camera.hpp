#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <QPointF>
#include <QSizeF>

namespace rc {
    class Camera;
}

class rc::Camera {
public:
    [[nodiscard]] QPointF toGlobal(QPointF point, float height) const;
    [[nodiscard]] QPointF toLocal(QPointF point, float height) const;
    void shift(QPointF delta, float height);
    void rescale(float factor, QPointF mouse, QSizeF size);
    [[nodiscard]] QPointF getTopLeft() const;
    [[nodiscard]] float getScale() const;

private:
    QPointF topLeft{0, 0};
    float scale = 1;
};

#endif // CAMERA_HPP
