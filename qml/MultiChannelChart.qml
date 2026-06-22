import QtQuick
import QtGraphs
import MultiChannelMonitor

Item {
    id: root

    required property var channels
    property int visibleSamples: 40

    GraphsView {
        id: graphsView
        anchors.fill: parent
        antialiasing: true

        theme: GraphsTheme {
            colorScheme: GraphsTheme.ColorScheme.Dark
            backgroundColor: "#27293d"
        }

        // Explicit property bindings: axes bypass defaultProperty (seriesList)
        // and register with the view's axis renderer.
        axisX: ValueAxis {
            id: axisX
            min: 0
            max: root.visibleSamples
        }

        axisY: ValueAxis {
            id: axisY
            min: 0
            max: 100
        }
    }

    Instantiator {
        id: seriesInstantiator
        model: root.channels

        LineSeries {
            required property MeasurementChannel modelData
            required property int index

            name: modelData.label

            property int sampleIdx: 0

            Component.onCompleted: {
                const ch = modelData
                const isFirst = (index === 0)
                ch.currentValueChanged.connect(function() {
                    append(sampleIdx, ch.currentValue)
                    sampleIdx++
                    if (isFirst && sampleIdx > root.visibleSamples) {
                        axisX.min = sampleIdx - root.visibleSamples
                        axisX.max = sampleIdx
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
        axisX.min = 0
        axisX.max = root.visibleSamples
    }
}
