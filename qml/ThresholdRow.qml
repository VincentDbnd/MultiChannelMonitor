import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    id: root

    required property string label
    required property color accentColor
    required property real from
    required property real to
    required property real value

    signal moved(real newValue)

    spacing: 8

    Rectangle { width: 8; height: 8; radius: 4; color: root.accentColor }

    Text {
        text: root.label
        color: GlobalStyle.textSecondary
        font.pixelSize: 11
        Layout.minimumWidth: 44
    }

    Slider {
        id: slider
        Layout.fillWidth: true
        implicitHeight: 24
        from: root.from
        to: root.to
        stepSize: 1
        onMoved: root.moved(value)

        background: Rectangle {
            x: slider.leftPadding
            y: slider.topPadding + slider.availableHeight / 2 - height / 2
            width: slider.availableWidth
            height: 4
            radius: 2
            color: GlobalStyle.background

            Rectangle {
                width: slider.visualPosition * parent.width
                height: parent.height
                radius: parent.radius
                color: root.accentColor
            }
        }

        handle: Rectangle {
            x: slider.leftPadding + slider.visualPosition * (slider.availableWidth - width)
            y: slider.topPadding + slider.availableHeight / 2 - height / 2
            width: 16; height: 16; radius: 8
            color: root.accentColor
        }

        Binding {
            target: slider
            property: "value"
            value: root.value
            when: !slider.pressed
        }
    }

    Text {
        text: root.value.toFixed(0)
        color: root.accentColor
        font.pixelSize: 11
        font.bold: true
        Layout.minimumWidth: 24
        horizontalAlignment: Text.AlignRight
    }
}
