import QtQuick
import QtQuick.Controls

Row {
    id: root
    spacing: 12

    property bool running: false

    signal startRequested()
    signal pauseRequested()
    signal resetRequested()

    Button {
        text: root.running ? "Pause" : "Start"
        onClicked: root.running ? root.pauseRequested() : root.startRequested()
    }

    Button {
        text: "Reset"
        onClicked: root.resetRequested()
    }
}