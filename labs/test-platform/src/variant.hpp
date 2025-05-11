#ifndef VARIANT_HPP
#define VARIANT_HPP

#include <QObject>

class Variant : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString text MEMBER text NOTIFY textChanged);
    Q_PROPERTY(int score MEMBER score NOTIFY scoreChanged);

public:
    Variant(QObject* parent = nullptr) : QObject(parent) {}

signals:
    void textChanged();
    void scoreChanged();

private:
    QString text;
    int score = 0;
};

#endif // VARIANT_HPP
