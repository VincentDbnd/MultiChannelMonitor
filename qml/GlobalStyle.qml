pragma Singleton
import QtQuick
import QtGraphs

QtObject {
    readonly property color background: "#131313"
    readonly property color surface: "#232323"
    readonly property color accent: "#3498db"
    readonly property color textPrimary: "#ffffff"
    readonly property color textSecondary: "#aaaaaa"
    readonly property color firstChannel: "#d8963c"
    readonly property color secondChannel: "#68d83c"
    readonly property color thirdChannel: "#3ca1d8"
    readonly property color warning: "#ff7300"
    readonly property color danger: "#ff0000"


    readonly property var channelColors: [firstChannel, secondChannel, thirdChannel]

    readonly property int radius: 6
}