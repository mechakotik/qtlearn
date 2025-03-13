#include <QVariant>
#include <QUrl>
#include <ambiance.hpp>
#include "sound.hpp"

void amb::Ambiance::add(QString name, QUrl path) {
    Sound* sound = new Sound(this);
    sound->setProperty("name", name);
    sound->setProperty("path", path);
    sound->play();
    sounds.push_back(sound);
    emit soundsChanged();
}

void amb::Ambiance::remove(int index) {
    dynamic_cast<Sound*>(sounds.at(index))->stop();
    sounds.remove(index);
    emit soundsChanged();
}
