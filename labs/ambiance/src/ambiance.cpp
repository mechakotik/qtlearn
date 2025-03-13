#include <QVariant>
#include <QUrl>
#include <ambiance.hpp>
#include "sound.hpp"

void amb::Ambiance::addSound(QString name, QUrl path) {
    Sound* sound = new Sound();
    sound->setProperty("name", name);
    sound->setProperty("path", path);
    sound->play();
    sounds.push_back(sound);
    emit soundsChanged();
}
