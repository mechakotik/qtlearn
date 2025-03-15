#ifndef AMBIANCE_HPP
#define AMBIANCE_HPP

#include <QQuickItem>
#include <QUrl>

namespace amb {
    class Ambiance;
}

class amb::Ambiance : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(QObjectList sounds MEMBER sounds NOTIFY soundsChanged)
    Q_PROPERTY(int style MEMBER style NOTIFY styleChanged)
    Q_PROPERTY(QString customStyle MEMBER customStyle NOTIFY customStyleChanged)
    Q_PROPERTY(bool darkMode MEMBER darkMode NOTIFY darkModeChanged)
    Q_PROPERTY(bool windowBorder MEMBER windowBorder NOTIFY windowBorderChanged)

public:
    Ambiance(QQuickItem* parent = nullptr);
    ~Ambiance();

    Q_INVOKABLE void add(QString name, QUrl path, double volume = 1);
    Q_INVOKABLE void addCustom(QUrl url);
    Q_INVOKABLE void remove(int index);

signals:
    void soundsChanged();
    void styleChanged();
    void customStyleChanged();
    void darkModeChanged();
    void windowBorderChanged();

private slots:
    void updateWindowBorder();

private:
    void loadConfig();
    void saveConfig();

    QObjectList sounds;
    int style = 0;
    QString customStyle;
    bool darkMode = true;
    bool windowBorder = false;
};

#endif // AMBIANCE_HPP
