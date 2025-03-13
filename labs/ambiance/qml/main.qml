import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Dialogs
import Ambiance.Ambiance

ApplicationWindow {
    id: window
    title: "Ambiance"
    width: 500
    height: 600
    visible: true

    Ambiance { id: ambiance }

    Menu {
        id: menu
        MenuItem {
            text: "Природа"
            onTriggered: natureMenu.open()
        }
        MenuItem {
            text: "Окружение"
            onTriggered: envMenu.open()
        }
        MenuItem {
            text: "Шум"
            onTriggered: noiseMenu.open()
        }
        MenuSeparator {}
        MenuItem {
            text: "Импорт"
        }
    }

    Menu {
        id: natureMenu
        MenuItem { text: "Дождь"; onTriggered: ambiance.add("Дождь", "qrc:/res/sounds/rain.ogg") }
        MenuItem { text: "Шторм"; onTriggered: ambiance.add("Шторм", "qrc:/res/sounds/storm.ogg") }
        MenuItem { text: "Ветер"; onTriggered: ambiance.add("Ветер", "qrc:/res/sounds/wind.ogg") }
        MenuItem { text: "Волны"; onTriggered: ambiance.add("Волны", "qrc:/res/sounds/waves.ogg") }
        MenuItem { text: "Поток"; onTriggered: ambiance.add("Поток", "qrc:/res/sounds/stream.ogg") }
        MenuItem { text: "Птицы"; onTriggered: ambiance.add("Птицы", "qrc:/res/sounds/birds.ogg") }
        MenuItem { text: "Летняя ночь"; onTriggered: ambiance.add("Летняя ночь", "qrc:/res/sounds/summer-night.ogg") }
    }

    Menu {
        id: envMenu
        MenuItem { text: "Поезд"; onTriggered: ambiance.add("Поезд", "qrc:/res/sounds/train.ogg") }
        MenuItem { text: "Лодка"; onTriggered: ambiance.add("Лодка", "qrc:/res/sounds/boat.ogg") }
        MenuItem { text: "Город"; onTriggered: ambiance.add("Город", "qrc:/res/sounds/city.ogg") }
        MenuItem { text: "Кофейня"; onTriggered: ambiance.add("Кофейня", "qrc:/res/sounds/coffee-shop.ogg") }
        MenuItem { text: "Костёр"; onTriggered: ambiance.add("Костёр", "qrc:/res/sounds/fireplace.ogg") }
    }

    Menu {
        id: noiseMenu
        MenuItem { text: "Розовый шум"; onTriggered: ambiance.add("Розовый шум", "qrc:/res/sounds/pink-noise.ogg") }
        MenuItem { text: "Белый шум"; onTriggered: ambiance.add("Белый шум", "qrc:/res/sounds/white-noise.ogg") }
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                icon.source: "/res/icons/add_box.svg"
                onClicked: menu.open()
            }
            Label {
                text: "Ambiance"
                font.bold: true
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton {
                icon.source: "/res/icons/settings.svg"
            }
            ToolButton {
                icon.source: "/res/icons/cancel.svg"
                onClicked: window.close()
            }
        }
    }

    ScrollView {
        anchors.fill: parent
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AsNeeded

        ListView {
            id: listView
            model: ambiance.sounds
            delegate: ItemDelegate {
                width: ListView.view.width
                contentItem: RowLayout {
                    Label {
                        text: modelData.name
                        rightPadding: 100 - contentWidth
                    }
                    Slider {
                        Layout.fillWidth: true
                        value: modelData.volume
                        onMoved: modelData.volume = value
                    }
                    ToolButton {
                        icon.source: "/res/icons/delete.svg"
                        onClicked: ambiance.remove(index)
                    }
                }
            }
            focus: true
            clip: true
        }
    }
}
