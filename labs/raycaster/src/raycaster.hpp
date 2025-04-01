#ifndef RAYCASTER_HPP
#define RAYCASTER_HPP

#include <QQuickPaintedItem>
#include "polygon.hpp"

namespace rc {
    class Raycaster;
}

class rc::Raycaster : public QQuickPaintedItem {
    Q_OBJECT
    Q_PROPERTY(int mode MEMBER mode NOTIFY modeChanged);
    Q_PROPERTY(QPointF lightPosition MEMBER lightPosition NOTIFY lightPositionChanged);
    QML_ELEMENT

public:
    Raycaster(QQuickItem* parent = nullptr);
    void paint(QPainter* painter) override;

    // Polygon editing
    Q_INVOKABLE void newVertex(QPointF point);
    Q_INVOKABLE void setLastVertex(QPointF point);
    Q_INVOKABLE void finishPolygon();

    Q_INVOKABLE void clear();

signals:
    void modeChanged();
    void lightPositionChanged();

public slots:
    void redraw();

private:
    void drawPolygons(QPainter* painter);
    void drawLight(QPainter* painter);
    std::vector<QPointF> getLightPolygon(const QPointF& source);

    std::vector<Polygon> polygons;

    QPointF lightPosition;
    int mode = 0;
};

#endif // RAYCASTER_HPP
