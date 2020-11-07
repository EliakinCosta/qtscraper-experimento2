import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.13

import "FontAwesome"

ItemDelegate {
    property alias iconName : toolButton.text
    property string displayText
    property color foregroundColor: "#03728c"

    width: parent.width
    text: "         " + displayText

    ToolButton {
        id: toolButton
        font { family: FontAwesome.solid }
        Material.foreground: foregroundColor
        onClicked: parent.clicked()
    }
}
