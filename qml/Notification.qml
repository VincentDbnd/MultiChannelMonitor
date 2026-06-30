import QtQuick
import MultiChannelMonitor

Rectangle {
    id: root

    required property string label
    required property string core
    required property string channel
    required property int severity

    width: parent ? parent.width : 0
    height: 50
    radius: GlobalStyle.radius
    border.width: 2
    border.color: root.severity === NotificationsModel.Danger ? GlobalStyle.danger : GlobalStyle.warning
    color: root.severity === NotificationsModel.Danger ? Qt.rgba(GlobalStyle.danger.r, GlobalStyle.danger.g, GlobalStyle.danger.b, 0.15) : Qt.rgba(GlobalStyle.warning.r, GlobalStyle.warning.g, GlobalStyle.warning.b, 0.15)

    opacity: 0
    transform: Translate {
        id: slideT; y: -(root.height + 8)
    }

    Component.onCompleted: entryAnim.start()

    ParallelAnimation {
        id: entryAnim
        NumberAnimation {
            target: slideT; property: "y"
            from: -(root.height + 8);
            to: 0
            duration: 650; easing.type: Easing.OutCubic
        }
        NumberAnimation {
            target: root; property: "opacity"
            from: 0;
            to: 1
            duration: 500
        }
    }

    Column {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 12
        spacing: 4

        Text {
            text: root.channel + " – " + root.label
            color: root.severity === NotificationsModel.Danger ? GlobalStyle.danger : GlobalStyle.warning
            font.pixelSize: 13
            font.bold: true
        }

        Text {
            text: root.core
            color: GlobalStyle.textPrimary
            font.pixelSize: 11
        }
    }
}
