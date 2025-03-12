#include <iostream>
#include <sound.hpp>

void amb::Sound::play() {
    player = new QMediaPlayer;
    output = new QAudioOutput;
    player->setAudioOutput(output);

    player->setSource(QUrl::fromLocalFile("/data/qtlearn/labs/basics/ambiance/res/sounds/rain.ogg"));
    player->setLoops(QMediaPlayer::Infinite);
    output->setVolume(1);
    player->play();

    std::cerr << path.toString().toStdString() << ' ' << player->isPlaying() << std::endl;
}
