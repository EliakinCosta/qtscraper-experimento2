import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13
import Qt.labs.settings 1.1

import "FontAwesome"

Page {
    title: "Emile - Notícias do IFBA"

    ColumnLayout {
        anchors { fill: parent; margins: 10 }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: core.networkController.IFBANews
            spacing: 10
            delegate: Frame {
                width: parent.width
                height: rowLayout.height + 2*rowLayout.anchors.margins
                Material.elevation: 3
                padding: 0
                topPadding: 0
                bottomPadding: 0
                ItemDelegate {
                    width: parent.width
                    height: rowLayout.height + 2*rowLayout.anchors.margins
                    padding: 0; topPadding: 0; bottomPadding: 0
                    RowLayout {
                        id: rowLayout
                        height: newsLabel.height+anchors.margins
                        anchors { right: parent.right; left: parent.left; top: parent.top; margins: 10 }
                        Label {
                            id: newsLabel
                            text: modelData.title
                            Layout.fillWidth: true
                            wrapMode: Text.WordWrap
                            Layout.alignment: Qt.AlignVCenter
                        }
                        Label {
                            font { family: FontAwesome.solid }
                            Material.foreground: "#03728c"
                            text: Icons.faChevronRight
                            Layout.alignment: Qt.AlignVCenter
                        }
                    }
                    onClicked: {
                        core.networkController.getIFBANews(modelData.url)
                        stackView.push("qrc:/News.qml", { newsTitle: modelData.title })
                    }
                }
            }
        }
    }

    Component.onCompleted: core.networkController.getIFBANews()
}
