import QtQuick
import QtQuick.Window
import QtQuick.Layouts

import MultiChannelMonitor

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
        color: "#1e1e2e"

        GridLayout {

        }
        Column {
            anchors.fill: parent
            anchors.margins: 24
            spacing: 16

            ControlBar {
                running: engine.running
                onStartRequested: engine.start()
                onPauseRequested: engine.pause()
                onResetRequested: {
                    engine.reset()
                    chart.clear()
                }
            }

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
    }
}