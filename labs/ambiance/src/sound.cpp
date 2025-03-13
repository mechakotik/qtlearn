#include <sound.hpp>

amb::Sound::Sound(QObject* parent) : QObject(parent) {
    player = new QMediaPlayer(this);
    output = new QAudioOutput(this);
    player->setAudioOutput(output);
    connect(this, &amb::Sound::volumeChanged, this, &amb::Sound::updateVolume);
}

void amb::Sound::play() {
    player->setSource(path);
    player->setLoops(QMediaPlayer::Infinite);
    output->setVolume(static_cast<float>(volume));
    player->play();
}

void amb::Sound::stop() {
    player->stop();
}

void amb::Sound::updateVolume() {
    output->setVolume(static_cast<float>(volume));
}
