import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13
import Qt.labs.settings 1.1

import "FontAwesome"

Page {
    title: "Emile - Editais da PRPGI"

    ColumnLayout {
        anchors { fill: parent; margins: 10 }

        ListView {
            id: noticesView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: core.networkController.PRPGINotices
            spacing: 10
            property Label selectedItem: null
            delegate: Frame {
                width: parent.width
                height: rowLayout.height + 2*rowLayout.anchors.margins
                Material.elevation: 3
                padding: 0
                topPadding: 0
                bottomPadding: 0
                clip: true
                ItemDelegate {
                    width: parent.width
                    height: rowLayout.height + 2*rowLayout.anchors.margins
                    padding: 0; topPadding: 0; bottomPadding: 0
                    RowLayout {
                        id: rowLayout
                        height: noticeLayout.height+anchors.margins
                        Behavior on height { NumberAnimation { duration: 500; easing.type: Easing.OutBounce } }
                        anchors { right: parent.right; left: parent.left; top: parent.top; margins: 10 }
                        ColumnLayout {
                            id: noticeLayout
                            Layout.fillWidth: true
                            Label {
                                text: modelData.title
                                Layout.fillWidth: true
                                wrapMode: Text.WordWrap
                                font.bold: true
                                Layout.alignment: Qt.AlignVCenter
                                Label {
                                    id: chevron
                                    font { family: FontAwesome.solid }
                                    Material.foreground: "#03728c"
                                    text: Icons.faChevronDown
                                    anchors { right: parent.right; verticalCenter: parent.verticalCenter }
                                }
                            }
                            Label {
                                text: modelData.description
                                Layout.fillWidth: true
                                wrapMode: Text.WordWrap
                                Layout.alignment: Qt.AlignVCenter
                            }
                            Label {
                                Layout.fillWidth: true
                                Layout.margins: 10
                                text: modelData.contents
                                wrapMode: Text.WordWrap
                                onLinkActivated: Qt.openUrlExternally(link)
                                visible: chevron.text === Icons.faChevronUp
                            }
                        }
                    }
                    onClicked: {
                        if (noticesView.selectedItem !== null && noticesView.selectedItem !== chevron)
                            noticesView.selectedItem.text = Icons.faChevronDown
                        chevron.text = (chevron.text === Icons.faChevronDown) ? Icons.faChevronUp:Icons.faChevronDown
                        noticesView.selectedItem = chevron
                    }
                }
            }
        }
    }

    Component.onCompleted: core.networkController.getPRPGINotices()
}
