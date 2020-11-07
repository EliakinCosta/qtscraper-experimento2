import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13
import Qt.labs.settings 1.1

Page {
    title: "Emile - Notícias do IFBA"

    property string newsTitle

    Flickable {
        anchors.fill: parent
        contentWidth: parent.width
        contentHeight: newsLayout.height

        ColumnLayout {
            id: newsLayout
            width: parent.width

            Image {
                source: "qrc:/images/news" + Math.round(Math.random() * (10 - 1) + 1) + ".png"
                sourceSize.width: parent.width
                fillMode: Image.PreserveAspectFit

                Rectangle {
                    anchors.bottom: parent.bottom
                    width: parent.width; height: childrenRect.height + 20
                    color: "#C01b1b1b"
                    Label {
                        anchors { right: parent.right; left: parent.left; top: parent.top; margins: 10 }
                        color: "white"
                        text: newsTitle
                        font.pointSize: 14
                        wrapMode: Text.WordWrap
                    }
                }
            }

            Label {
                Layout.fillWidth: true; Layout.fillHeight: true
                Layout.margins: 10
                text: core.networkController.news
                wrapMode: Text.WordWrap
                onLinkActivated: Qt.openUrlExternally(link)
            }
        }
    }
}
