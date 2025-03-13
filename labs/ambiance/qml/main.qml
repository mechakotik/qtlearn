import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Dialogs
import Ambiance.Ambiance

ApplicationWindow {
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
        MenuItem { text: "Дождь"; onTriggered: ambiance.addSound("Дождь", "/res/sounds/rain.ogg") }
        MenuItem { text: "Шторм"; onTriggered: ambiance.addSound("Шторм", "/res/sounds/storm.ogg") }
        MenuItem { text: "Ветер"; onTriggered: ambiance.addSound("Ветер", "/res/sounds/wind.ogg") }
        MenuItem { text: "Волны"; onTriggered: ambiance.addSound("Волны", "/res/sounds/waves.ogg") }
        MenuItem { text: "Поток"; onTriggered: ambiance.addSound("Поток", "/res/sounds/stream.ogg") }
        MenuItem { text: "Птицы"; onTriggered: ambiance.addSound("Птицы", "/res/sounds/birds.ogg") }
        MenuItem { text: "Летняя ночь"; onTriggered: ambiance.addSound("Летняя ночь", "/res/sounds/summer-night.ogg") }
    }

    Menu {
        id: envMenu
        /*MenuItem { text: "Поезд"; onTriggered: ambiance.addSound("Поезд", "/res/sounds/rain.ogg") }
        MenuItem { text: "Лодка"; onTriggered: ambiance.addSound("Лодка", "/res/sounds/rain.ogg") }
        MenuItem { text: "Город"; onTriggered: ambiance.addSound("Город", "/res/sounds/rain.ogg") }
        MenuItem { text: "Кофейня"; onTriggered: ambiance.addSound("Дождь", "/res/sounds/rain.ogg") }
        MenuItem { text: "Костёр"; onTriggered: ambiance.addSound("Дождь", "/res/sounds/rain.ogg") }*/
    }

    Menu {
        id: noiseMenu
        MenuItem { text: "Розовый шум" }
        MenuItem { text: "Белый шум" }
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
                    }
                    Slider {
                        Layout.fillWidth: true
                        value: modelData.volume
                    }
                    ToolButton {
                        icon.source: "/res/icons/delete.svg"
                    }
                }
            }
            focus: true
            clip: true
        }
    }
}
