import QtQuick
import MultiChannelMonitor

// Displays the label and live value for a single measurement channel.
Rectangle {
    id: root

    required property MeasurementChannel channel

    width: 180
    height: 100
    radius: GlobalStyle.radius
    color: GlobalStyle.surface

    Column {
        anchors.centerIn: parent
        spacing: 4

        Text {
            text: root.channel.label
            color: GlobalStyle.textSecondary
            font.pixelSize: 16
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: root.channel.currentValue.toFixed(2)
            color: GlobalStyle.channelColors[root.channel.index] ?? GlobalStyle.accent
            font.pixelSize: 24
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

    }
}