#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <QObject>
#include <QStringList>
#include "checkbox.hpp"
#include "variant.hpp"

class Question : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString text MEMBER text NOTIFY textChanged)
    Q_PROPERTY(QString image MEMBER image NOTIFY imageChanged)
    Q_PROPERTY(QObjectList variants MEMBER variants NOTIFY variantsChanged)
    Q_PROPERTY(QObjectList checkboxes MEMBER checkboxes NOTIFY checkboxesChanged)
    Q_PROPERTY(bool checked MEMBER checked NOTIFY checkedChanged)

public:
    Question(QObject* parent = nullptr) : QObject(parent) {}
    void addVariant(Variant* variant);
    void addCheckbox(Checkbox* checkbox);

signals:
    void textChanged();
    void imageChanged();
    void variantsChanged();
    void checkboxesChanged();
    void checkedChanged();

private:
    QString text;
    QString image;
    QObjectList variants;
    QObjectList checkboxes;
    bool checked = false;
};

#endif // QUESTION_HPP
