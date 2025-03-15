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

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        nameFilters: ["Звуки (*.wav *.mp3 *.ogg *.flac)", "Все файлы (*)"]
        onAccepted: {
            ambiance.addCustom(selectedFile)
            visible = false
        }
        onRejected: {
            visible = false
        }
    }

    Menu {
        id: menu
        MenuItem {
            text: "Природа"
            hoverEnabled: true
            onTriggered: natureMenu.open()
        }
        MenuItem {
            text: "Окружение"
            hoverEnabled: true
            onTriggered: envMenu.open()
        }
        MenuItem {
            text: "Шум"
            hoverEnabled: true
            onTriggered: noiseMenu.open()
        }
        MenuSeparator {}
        MenuItem {
            text: "Импорт"
            hoverEnabled: true
            onTriggered: fileDialog.open()
        }
    }

    Menu {
        id: natureMenu
        MenuItem { text: "Дождь"; onTriggered: ambiance.add("Дождь", "qrc:/res/sounds/rain.ogg"); hoverEnabled: true }
        MenuItem { text: "Шторм"; onTriggered: ambiance.add("Шторм", "qrc:/res/sounds/storm.ogg"); hoverEnabled: true }
        MenuItem { text: "Ветер"; onTriggered: ambiance.add("Ветер", "qrc:/res/sounds/wind.ogg"); hoverEnabled: true }
        MenuItem { text: "Волны"; onTriggered: ambiance.add("Волны", "qrc:/res/sounds/waves.ogg"); hoverEnabled: true }
        MenuItem { text: "Поток"; onTriggered: ambiance.add("Поток", "qrc:/res/sounds/stream.ogg"); hoverEnabled: true }
        MenuItem { text: "Птицы"; onTriggered: ambiance.add("Птицы", "qrc:/res/sounds/birds.ogg"); hoverEnabled: true }
        MenuItem { text: "Летняя ночь"; onTriggered: ambiance.add("Летняя ночь", "qrc:/res/sounds/summer-night.ogg"); hoverEnabled: true }
    }

    Menu {
        id: envMenu
        MenuItem { text: "Поезд"; onTriggered: ambiance.add("Поезд", "qrc:/res/sounds/train.ogg"); hoverEnabled: true }
        MenuItem { text: "Лодка"; onTriggered: ambiance.add("Лодка", "qrc:/res/sounds/boat.ogg"); hoverEnabled: true }
        MenuItem { text: "Город"; onTriggered: ambiance.add("Город", "qrc:/res/sounds/city.ogg"); hoverEnabled: true }
        MenuItem { text: "Кофейня"; onTriggered: ambiance.add("Кофейня", "qrc:/res/sounds/coffee-shop.ogg"); hoverEnabled: true }
        MenuItem { text: "Костёр"; onTriggered: ambiance.add("Костёр", "qrc:/res/sounds/fireplace.ogg"); hoverEnabled: true }
    }

    Menu {
        id: noiseMenu
        MenuItem { text: "Розовый шум"; onTriggered: ambiance.add("Розовый шум", "qrc:/res/sounds/pink-noise.ogg"); hoverEnabled: true }
        MenuItem { text: "Белый шум"; onTriggered: ambiance.add("Белый шум", "qrc:/res/sounds/white-noise.ogg"); hoverEnabled: true }
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            DragHandler {
                acceptedDevices: PointerDevice.GenericPointer
                grabPermissions:  PointerHandler.CanTakeOverFromItems | PointerHandler.CanTakeOverFromHandlersOfDifferentType | PointerHandler.ApprovesTakeOverByAnything
                onActiveChanged: if (active) window.startSystemMove()
            }
            ToolButton {
                icon.source: "/res/icons/add_box.svg"
                onClicked: menu.open()
                visible: stack.depth === 1
                hoverEnabled: true
            }
            ToolButton {
                icon.source: "/res/icons/back.svg"
                onClicked: stack.pop()
                visible: stack.depth === 2
                hoverEnabled: true
            }
            Label {
                text: (stack.depth === 1 ? "Ambiance" : "Настройки")
                font.bold: true
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton {
                icon.source: "/res/icons/settings.svg"
                onClicked: stack.push(settingsView)
                visible: stack.depth === 1
                hoverEnabled: true
            }
            ToolButton {
                icon.source: "/res/icons/cancel.svg"
                onClicked: window.close()
                hoverEnabled: true
            }
        }
    }

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: mainView

        pushEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: 100
            }
        }
        pushExit: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 1
                to: 0
                duration: 100
            }
        }
        popEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: 100
            }
        }
        popExit: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 1
                to: 0
                duration: 100
            }
        }
    }

    Component {
        id: mainView

        ScrollView {
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
                            hoverEnabled: true
                        }
                        ToolButton {
                            icon.source: "/res/icons/delete.svg"
                            onClicked: ambiance.remove(index)
                            hoverEnabled: true
                        }
                    }
                }
                focus: true
                clip: true
            }
        }
    }

    Component {
        id: settingsView

        ColumnLayout {
            GridLayout {
                Layout.fillWidth: true
                Layout.margins: 20
                columns: 2
                rowSpacing: 15
                columnSpacing: 30

                Label { text: "Стиль" }
                ComboBox {
                    id: styleBox
                    model: ["Material", "Fluent", "Fusion", "По умолчанию", "Кастомный"]
                    currentIndex: ambiance.style
                    onActivated: ambiance.style = currentIndex
                    Layout.fillWidth: true
                    hoverEnabled: true
                }

                Label {
                    text: "Кастомный стиль"
                    enabled: styleBox.currentIndex === 4
                }
                TextField {
                    Layout.fillWidth: true
                    enabled: styleBox.currentIndex === 4
                    text: ambiance.customStyle
                    onEditingFinished: ambiance.customStyle = text
                    hoverEnabled: true
                }

                /*Label { text: "Цвет акцента" }
                ComboBox {
                    model: ["default"]
                    Layout.fillWidth: true
                }*/

                Label { text: "Тёмная тема" }
                CheckBox {
                    Layout.alignment: Qt.AlignRight
                    checked: ambiance.darkMode
                    onCheckedChanged: ambiance.darkMode = checked
                    hoverEnabled: true
                }

                Label { text: "Рамка окна" }
                CheckBox {
                    Layout.alignment: Qt.AlignRight
                    checked: ambiance.windowBorder
                    onCheckedChanged: ambiance.windowBorder = checked
                    hoverEnabled: true
                }
            }
            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
