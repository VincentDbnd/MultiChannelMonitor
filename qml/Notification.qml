import QtQuick
import MultiChannelMonitor

Rectangle {
    id: root

    required property string label
    required property string core
    required property string channel
    required property int severity

    width: 260
    height: 70
    radius: 4
    border.width : 2
    border.color : "#fbbf24"
    color: root.severity === NotificationsModel.Danger ? "#4c1d1d" : "#2d2d1d"

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
            color: root.severity === NotificationsModel.Danger ? "#f87171" : "#fbbf24"
            font.pixelSize: 13
            font.bold: true
        }

        Text {
            text: root.core
            color: "#d1d5db"
            font.pixelSize: 11
        }
    }
}
