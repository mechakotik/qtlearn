#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include <QObject>

class Checkbox : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString text MEMBER text NOTIFY textChanged)
    Q_PROPERTY(bool need MEMBER need NOTIFY needChanged)
    Q_PROPERTY(int score MEMBER score NOTIFY scoreChanged)

public:
    Checkbox(QObject *parent = nullptr) : QObject(parent) {}

signals:
    void textChanged();
    void needChanged();
    void scoreChanged();

private:
    QString text;
    bool need = false;
    int score = 0;
};

#endif // CHECKBOX_HPP
