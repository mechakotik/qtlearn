import QtQuick
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQuick.Controls
import QtQuick.Controls.Material
import TestPlatform.TestPlatform

ApplicationWindow {
    id: window
    title: "Test Platform"
    width: 500
    height: 700
    visible: true

    Material.theme: Material.Dark
    Material.primary: "#3f3c40"
    Material.background: "#1c1b1f"
    Material.accent: Material.Grey

    TestPlatform {
        id: testpl
    }
    Component.onCompleted: {
        // requires error dialog to be initialized
        testpl.loadTestsList()
    }

    ErrorDialog {
        id: errorDialog
    }
    property var errorDialogExport: errorDialog

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            DragHandler {
                acceptedDevices: PointerDevice.GenericPointer
                grabPermissions: PointerHandler.CanTakeOverFromItems | PointerHandler.CanTakeOverFromHandlersOfDifferentType | PointerHandler.ApprovesTakeOverByAnything
                onActiveChanged: if (active) window.startSystemMove()
            }

            Item {
                Layout.fillWidth: true
                Label {
                    text: "Test Platform"
                    font.bold: true
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                ToolButton {
                    id: hideButton
                    icon.source: "/res/icons/hide.svg"
                    onClicked: window.showMinimized()
                    hoverEnabled: true
                    anchors.right: closeButton.left
                    anchors.verticalCenter: parent.verticalCenter
                }
                ToolButton {
                    id: closeButton
                    icon.source: "/res/icons/close.svg"
                    onClicked: window.close()
                    hoverEnabled: true
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: menuView

        pushEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: 100
            }
            PropertyAnimation {
                property: "x"
                from: 100
                to: 0
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
            PropertyAnimation {
                property: "x"
                from: 0
                to: -100
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
            PropertyAnimation {
                property: "x"
                from: -100
                to: 0
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
            PropertyAnimation {
                property: "x"
                from: 0
                to: 100
                duration: 100
            }
        }
    }

    Component {
        id: menuView

        ScrollView {
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AsNeeded

            ListView {
                id: listView
                model: testpl.tests
                delegate: ItemDelegate {
                    width: ListView.view.width
                    hoverEnabled: true
                    onClicked: stack.push(questionView, { test: listView.currentIndex, question: 0 })
                    contentItem: Label {
                        text: modelData.name
                        rightPadding: 100 - contentWidth
                        elide: Text.ElideRight
                    }
                }
                focus: true
                clip: true
            }
        }
    }

    Component {
        id: questionView

        Item {
            property var test
            property var question

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20

                Image {
                    source: testpl.tests[test].questions[question].image
                    Layout.maximumWidth: 400
                    Layout.maximumHeight: 300
                    Layout.alignment: Qt.AlignCenter
                    fillMode: Image.PreserveAspectFit
                    mipmap: true
                    onStatusChanged: {
                        if (status === Image.Error) errorDialog.show("Ошибка загрузки изображения " + source)
                    }
                }
                Label {
                    Layout.alignment: Qt.AlignCenter
                    text: testpl.tests[test].questions[question].text
                    enabled: text !== ""
                }
                Repeater {
                    model: testpl.tests[test].questions[question].variants
                    RadioButton {
                        Layout.fillWidth: true
                        text: modelData.text
                    }
                }
                Item {
                    Layout.fillHeight: true
                }
                Button {
                    Layout.alignment: Qt.AlignRight
                    text: "ПРОВЕРИТЬ"
                }
            }
        }
    }
}
