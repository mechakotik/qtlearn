#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <QObject>
#include <QStringList>
#include "variant.hpp"

class Question : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString text MEMBER text NOTIFY textChanged)
    Q_PROPERTY(QString image MEMBER image NOTIFY imageChanged)
    Q_PROPERTY(QObjectList variants MEMBER variants NOTIFY variantsChanged)

public:
    Question(QObject* parent = nullptr) : QObject(parent) {}
    void addVariant(Variant* variant);

signals:
    void textChanged();
    void imageChanged();
    void variantsChanged();

private:
    QString text;
    QString image;
    QObjectList variants;
};

#endif // QUESTION_HPP
