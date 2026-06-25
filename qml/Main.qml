import QtQuick
import QtQuick.Window
import QtQuick.Layouts

import MultiChannelMonitor

// Root window: wires AcquisitionEngine to ControlBar, ChannelCards and MultiChannelChart.
Window {
    width: 1600
    height: 900
    visible: true
    title: qsTr("Multi Channel Monitor")

    AcquisitionEngine {
        id: engine
    }

    Rectangle {
        anchors.fill: parent
        color: Style.background

        ControlBar {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            running: engine.running
            onStartRequested: engine.start()
            onPauseRequested: engine.pause()
            onResetRequested: {
                engine.reset()
                chart.clear()
            }
        }

        RowLayout {
            anchors.fill: parent

            spacing: 16

            Column {
                spacing: 16
                Layout.fillWidth: true
                Layout.fillHeight: true

                Row {
                    spacing: 24

                    Repeater {
                        model: engine.channels
                        delegate: ChannelCard {
                            required property MeasurementChannel modelData
                            channel: modelData
                        }
                    }
                }

                MultiChannelChart {
                    id: chart
                    width: parent.width
                    height: 320
                    visibleSamples: 40
                    channels: engine.channels
                }
            }

            Column {
                Layout.fillWidth: true
                Layout.fillHeight: true

                Rectangle {
                    width: 300
                    height: parent.height
                    radius: 4
                    color: Style.surface

                    ListView {
                        anchors.fill: parent
                        model: engine.notifications
                        spacing: 8

                        delegate: Notification {}
                    }
                }
            }
        }

    }
}