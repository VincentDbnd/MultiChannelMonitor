import QtQuick
import QtQuick.Window
import QtQuick.Controls
import MultiChannelMonitor

Window {
    width: 760
    height: 480
    visible: true
    title: qsTr("Multi Channel Monitor")

    AcquisitionEngine {
        id: engine
    }

    Rectangle {
        anchors.fill: parent
        color: "#1e1e2e"

        Column {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 24

            Row {
                spacing: 12
                anchors.horizontalCenter: parent.horizontalCenter

                Button {
                    text: engine.running ? "Pause" : "Start"
                    onClicked: engine.running ? engine.pause() : engine.start()
                }

                Button {
                    text: "Reset"
                    onClicked: engine.reset()
                }
            }

            Row {
                spacing: 24
                anchors.horizontalCenter: parent.horizontalCenter

                // One delegate instantiated per channel exposed by the engine
                Repeater {
                    model: engine.channels

                    delegate: Rectangle {
                        width: 180
                        height: 140
                        radius: 8
                        color: "#27293d"

                        Column {
                            anchors.centerIn: parent
                            spacing: 8

                            Text {
                                text: modelData.label
                                color: "white"
                                font.pixelSize: 18
                                anchors.horizontalCenter: parent.horizontalCenter
                            }

                            Text {
                                text: modelData.currentValue.toFixed(2)
                                color: "#7dd3fc"
                                font.pixelSize: 32
                                font.bold: true
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }
                    }
                }
            }
        }
    }
}