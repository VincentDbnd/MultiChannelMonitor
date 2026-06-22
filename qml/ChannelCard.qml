import QtQuick
import MultiChannelMonitor

Rectangle {
    id: root

    // Public API of this component — like a typed React prop
    required property MeasurementChannel channel

    width: 180
    height: 100
    radius: 8
    color: "#27293d"

    Column {
        anchors.centerIn: parent
        spacing: 4

        Text {
            text: root.channel.label
            color: "white"
            font.pixelSize: 16
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: root.channel.currentValue.toFixed(2)
            color: "#7dd3fc"
            font.pixelSize: 24
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}