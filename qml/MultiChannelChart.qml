import QtQuick
import QtQuick.Controls
import QtGraphs
import MultiChannelMonitor

// Scrolling line graph that plots live samples for every channel.
Item {
    id: root

    required property var channels
    property int visibleSamples: 40
    property int totalSamples: 0
    property bool liveMode: true

    function updateAxisX(start) {
        axisX.min = start
        axisX.max = start + visibleSamples
    }

    Rectangle {
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: hScrollBar.top
        }
        radius: GlobalStyle.radius
        layer.enabled: true
        color: "transparent"

        GraphsView {
            id: graphsView
            anchors.fill: parent
            antialiasing: true

            theme: GraphsTheme {
                plotAreaBackgroundColor: Qt.darker(GlobalStyle.surface, 1.4)
                backgroundColor: GlobalStyle.surface
                grid.mainColor: GlobalStyle.surface
            }

            axisX: ValueAxis {
                id: axisX
                min: 0
                max: root.visibleSamples
                tickInterval: 100000
            }

            axisY: ValueAxis {
                id: axisY
                min: 0
                max: 100
                tickInterval: 20
                tickAnchor: 0
            }
        }
    }

    ScrollBar {
        id: hScrollBar
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        orientation: Qt.Horizontal
        size: root.totalSamples > root.visibleSamples ? root.visibleSamples / root.totalSamples : 1.0

        onPositionChanged: {
            if (!pressed) return
            root.liveMode = (position + size >= 1.0)
            const maxStart = root.totalSamples - root.visibleSamples
            root.updateAxisX(Math.round(position / (1.0 - size) * maxStart))
        }
    }

    Instantiator {
        id: seriesInstantiator
        model: root.channels

        LineSeries {
            required property MeasurementChannel modelData
            required property int index

            name: modelData.label
            color: GlobalStyle.channelColors[index] ?? GlobalStyle.accent

            property int sampleIdx: 0

            Component.onCompleted: {
                const ch = modelData
                const isFirst = (index === 0)
                ch.currentValueChanged.connect(function () {
                    append(sampleIdx, ch.currentValue)
                    sampleIdx++
                    if (isFirst) {
                        root.totalSamples = sampleIdx
                        if (root.liveMode && sampleIdx > root.visibleSamples) {
                            const liveStart = sampleIdx - root.visibleSamples
                            root.updateAxisX(liveStart)
                            hScrollBar.position = liveStart / sampleIdx
                        }
                    }
                })
            }
        }

        onObjectAdded: (idx, obj) => graphsView.addSeries(obj)
        onObjectRemoved: (idx, obj) => graphsView.removeSeries(obj)
    }

    function clear() {
        for (let i = 0; i < seriesInstantiator.count; i++) {
            const s = seriesInstantiator.objectAt(i)
            s.clear()
            s.sampleIdx = 0
        }
        totalSamples = 0
        liveMode = true
        updateAxisX(0)
        hScrollBar.position = 0
    }
}
