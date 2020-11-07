import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13
import Qt.labs.settings 1.1

import "FontAwesome"

Page {
    title: "Bem-vindo ao Emile"

    ListView {
        anchors { fill: parent; margins: 10 }
        model: [
            { "icon": Icons.faBook, "description": "funcionalidades do SUAP", "page": "qrc:/SUAP.qml" },
            { "icon": Icons.faLaptopCode, "description": "SEI - consulta pública", "page": "qrc:/SEIPublicSearch.qml" },
            { "icon": Icons.faRss, "description": "notícias do IFBA", "page": "qrc:/IFBANews.qml" },
            { "icon": Icons.faHandshake, "description": "editais 2019 da PRPGI", "page": "qrc:/PRPGINotices.qml" }
        ]
        spacing: 10
        delegate: Item {
            width: parent.width
            height: frame.height
            Frame {
                id: frame
                width: parent.width
                Material.elevation: 1
                ColumnLayout {
                    id: columnLayout
                    width: parent.width
                    spacing: 10
                    Label {
                        Layout.fillWidth: true
                        horizontalAlignment: Text.AlignHCenter
                        font { family: FontAwesome.solid; pointSize: 24 }
                        text: modelData.icon
                        color: "#03728c"
                    }
                    Label {
                        Layout.fillWidth: true
                        horizontalAlignment: Text.AlignHCenter
                        font.capitalization: Font.AllUppercase
                        text: modelData.description
                    }
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    switch(index) {
                        case 0:
                            core.networkController.getBasicData()
                            break
                        case 1:
                            core.networkController.resetSEIPublicSearchAttempts()
                            core.networkController.prepareSEIPublicSearch()
                            break
                        default:
                            stackView.push(modelData.page)
                            break
                    }
                }
            }
        }
    }

    Connections {
        target: core.networkController
        onUserAuthenticated: stackView.push("qrc:/SUAP.qml")
        onSeiPublicSearchPrepared: stackView.push("qrc:/SEIPublicSearch.qml")
    }
}
