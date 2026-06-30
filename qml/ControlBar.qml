import QtQuick
import QtQuick.Controls

// Start / Pause / Reset controls; emits signals upward rather than acting directly.
Row {
    id: root
    spacing: 12

    property bool running: false

    signal startRequested()

    signal pauseRequested()

    signal resetRequested()

    Button {
        text: root.running ? "Pause" : "Start"
        width: 100
        height: 30
        onClicked: root.running ? root.pauseRequested() : root.startRequested()

        background: Rectangle {
            color: parent.pressed ? Qt.lighter(GlobalStyle.accent, 1.3) : parent.hovered ? Qt.lighter(GlobalStyle.accent, 1.15) : GlobalStyle.accent
            radius: GlobalStyle.radius
        }

        contentItem: Text {
            text: parent.text
            color: GlobalStyle.textPrimary
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    Button {
        text: "Reset"
        width: 100
        height: 30
        onClicked: root.resetRequested()

        background: Rectangle {
            color: parent.pressed ? Qt.lighter(GlobalStyle.surface, 1.3) : parent.hovered ? Qt.lighter(GlobalStyle.surface, 1.15) : GlobalStyle.surface
            radius: GlobalStyle.radius
        }

        contentItem: Text {
            text: parent.text
            color: GlobalStyle.textPrimary
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}