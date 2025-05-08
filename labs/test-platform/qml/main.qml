import QtQuick
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQuick.Controls
import QtQuick.Controls.Material

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
}
