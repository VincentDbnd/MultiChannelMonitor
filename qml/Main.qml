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

    Text {
        text : "MultiChannelMonitor @VincentDbnd"
        anchors.bottom : parent.bottom
        anchors.left : parent.left
        anchors.margins : 5
        color: GlobalStyle.textSecondary
        font.pixelSize: 16
        z : 10
    }

    Rectangle {
        anchors.fill: parent
        color: GlobalStyle.background


        RowLayout {
            id: mainRow
            anchors.fill: parent
            anchors.margins: 15

            spacing: 15

            ColumnLayout {
                Layout.preferredWidth: mainRow.width * 4 / 5
                spacing: 15

                RowLayout {
                    spacing: 15

                    Repeater {
                        model: engine.channels
                        delegate: ChannelCard {
                            required property MeasurementChannel modelData
                            channel: modelData
                        }
                    }

                    ThresholdEditor {
                        Layout.fillWidth: true
                        warningThreshold: engine.warningThreshold
                        dangerThreshold: engine.dangerThreshold
                        onWarningThresholdChanged: engine.warningThreshold = warningThreshold
                        onDangerThresholdChanged: engine.dangerThreshold = dangerThreshold
                    }
                }

                MultiChannelChart {
                    id: chart
                    Layout.fillWidth: true; Layout.preferredHeight: mainRow.height * 2 / 3
                    visibleSamples: 40
                    channels: engine.channels
                }

                ControlBar {
                    running: engine.running
                    onStartRequested: engine.start()
                    onPauseRequested: engine.pause()
                    onResetRequested: {
                        engine.reset()
                        chart.clear()
                    }
                }

                Item {
                    Layout.fillHeight: true
                }

            }

            ColumnLayout {
                Layout.preferredWidth: mainRow.width * 1 / 5

                Rectangle {
                    color: GlobalStyle.surface
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    radius: GlobalStyle.radius

                    ListView {
                        anchors.fill: parent
                        anchors.margins: 10
                        clip: true
                        model: engine.notifications
                        spacing: 8

                        delegate: Notification {
                        }
                    }

                }
            }

        }
    }
}