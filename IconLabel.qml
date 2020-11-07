import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13

import "FontAwesome"

RowLayout {
    property alias icon: iconLabel.text
    property alias text: textLabel.text
    property alias font: textLabel.font
    property alias horizontalAlignment: iconLabel.horizontalAlignment
    property bool inMenu: true
    property color foregroundColor: "#03728c"
    property alias color: textLabel.color

    spacing: 10

    Label {
        id: iconLabel
        Layout.preferredWidth: inMenu ? internal.maxIconWidth:-1
        Layout.minimumWidth: inMenu ? -1:internal.maxIconWidth
        horizontalAlignment: inMenu ? Text.AlignHCenter:Text.AlignLeft
        font { family: FontAwesome.solid; pointSize: 12 }
        Material.foreground: foregroundColor
    }
    Label {
        id: textLabel
        Layout.fillWidth: true
        wrapMode: Text.WordWrap
    }
}
