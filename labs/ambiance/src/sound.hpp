#ifndef SOUND_HPP
#define SOUND_HPP

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

namespace amb {
    class Sound;
}

class amb::Sound : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString name MEMBER name NOTIFY nameChanged)
    Q_PROPERTY(QUrl path MEMBER path NOTIFY pathChanged)
    Q_PROPERTY(double volume MEMBER volume NOTIFY volumeChanged)

public:
    void play();

signals:
    void nameChanged();
    void pathChanged();
    void volumeChanged();

private:
    QMediaPlayer* player;
    QAudioOutput* output;
    QString name;
    QUrl path;
    double volume = 1;
};

#endif // SOUND_HPP
