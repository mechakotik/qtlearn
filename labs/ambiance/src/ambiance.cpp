#include <QVariant>
#include <QUrl>
#include <QQuickStyle>
#include <toml.hpp>
#include "ambiance.hpp"
#include "sound.hpp"

amb::Ambiance::Ambiance(QObject* parent) : QObject(parent) {
    try {
        loadConfig();
    } catch(std::exception& e) {
        qWarning() << "Ambiance: failed to load config\n" << e.what();
    }
}

amb::Ambiance::~Ambiance() {
    try {
        saveConfig();
    } catch(std::exception& e) {
        qWarning() << "Ambiance: failed to save config\n" << e.what();
    }
}

void amb::Ambiance::loadConfig() {
    toml::value configTable = toml::parse("config.toml");
    for(const toml::value& sound : configTable.at("sounds").as_array()) {
        add(sound.at("name").as_string().c_str(), QUrl(sound.at("path").as_string().c_str(), QUrl::StrictMode), sound.at("volume").as_floating());
    }
}

void amb::Ambiance::saveConfig() {
    toml::table configTable;
    configTable["sounds"] = toml::array();
    for(QObject* object : sounds) {
        Sound* sound = dynamic_cast<Sound*>(object);
        toml::table soundTable;
        soundTable["name"] = sound->property("name").toString().toStdString();
        soundTable["path"] = sound->property("path").toUrl().toString().toStdString();
        soundTable["volume"] = sound->property("volume").toDouble();
        configTable.at("sounds").as_array().emplace_back(soundTable);
    }

    std::ofstream fout("config.toml");
    fout << toml::format(toml::value(configTable), toml::spec::v(1, 1, 0));
    fout.close();
}

void amb::Ambiance::add(QString name, QUrl path, double volume) {
    Sound* sound = new Sound(this);
    sound->setProperty("name", name);
    sound->setProperty("path", path);
    sound->setProperty("volume", volume);
    sound->play();
    sounds.push_back(sound);
    emit soundsChanged();
}

void amb::Ambiance::addCustom(QUrl path) {
    QString name = path.toString();
    int suf = 0;
    while(suf < name.size() && name[name.size() - suf - 1] != '/') {
        suf++;
    }
    name = name.right(suf);
    add(name, path);
}

void amb::Ambiance::remove(int index) {
    dynamic_cast<Sound*>(sounds.at(index))->stop();
    sounds.remove(index);
    emit soundsChanged();
}
