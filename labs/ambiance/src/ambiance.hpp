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
    Ambiance(QObject* parent = nullptr);
    ~Ambiance();

    Q_INVOKABLE void add(QString name, QUrl path, double volume = 1);
    Q_INVOKABLE void addCustom(QUrl url);
    Q_INVOKABLE void remove(int index);

signals:
    void soundsChanged();

private:
    void loadConfig();
    void saveConfig();

    QObjectList sounds;
};

#endif // AMBIANCE_HPP
