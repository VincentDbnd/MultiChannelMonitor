import QtQuick
import QtQuick.Window
import QtQuick.Controls
import MultiChannelMonitor

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Multi Channel Monitor")

    MeasurementChannel {
        id: channel
        label: "Canal 1"
    }

    Rectangle {
        anchors.fill: parent
        color: "#1e1e2e"

        Column {
            anchors.centerIn: parent
            spacing: 20

            Text {
                text: channel.label
                color: "white"
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                text: channel.currentValue.toFixed(2)
                color: "#7dd3fc"
                font.pixelSize: 48
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Button {
                text: "Nouvelle valeur"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: channel.randomize()
            }
        }
    }
}