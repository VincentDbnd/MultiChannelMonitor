import QtQuick
import QtQuick.Layouts

Rectangle {
    id: root

    property real warningThreshold: 95
    property real dangerThreshold: 98

    height: 100
    radius: GlobalStyle.radius
    color: GlobalStyle.surface

    ColumnLayout {
        anchors { top: parent.top; left: parent.left; right: parent.right; margins: 12 }
        spacing: 8

        Text {
            text: "Thresholds"
            color: GlobalStyle.textSecondary
            font.pixelSize: 11
        }

        ThresholdRow {
            Layout.fillWidth: true
            label: "Warning"
            accentColor: GlobalStyle.warning
            from: 0
            to: root.dangerThreshold - 1
            value: root.warningThreshold
            onMoved: (v) => root.warningThreshold = v
        }

        ThresholdRow {
            Layout.fillWidth: true
            label: "Danger"
            accentColor: GlobalStyle.danger
            from: root.warningThreshold + 1
            to: 100
            value: root.dangerThreshold
            onMoved: (v) => root.dangerThreshold = v
        }
    }
}
