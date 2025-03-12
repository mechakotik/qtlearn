#ifndef AMBIANCE_HPP
#define AMBIANCE_HPP

#include <QObject>
#include <QUrl>

namespace amb {
    class Ambiance;
}

class amb::Ambiance : public QObject {
    Q_OBJECT
    Q_PROPERTY(QObjectList sounds MEMBER sounds NOTIFY soundsChanged)

public:
    Q_INVOKABLE void addSound(QString name, QUrl path);

signals:
    void soundsChanged();

private:
    QObjectList sounds;
};

#endif // AMBIANCE_HPP
