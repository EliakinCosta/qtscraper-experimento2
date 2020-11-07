import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13

import br.ifba.edu.emile 1.0

import "FontAwesome"

Page {
    title: "Emile - Funcionalidades do SUAP"

    ListView {
        anchors { fill: parent; margins: 10 }
        model: [
            { "icon": Icons.faDatabase, "description": "meus dados", "page": "qrc:/MyData.qml" },
            { "icon": Icons.faBook, "description": "minhas disciplinas", "page": "qrc:/MyCourses.qml" },
            { "icon": Icons.faMedal, "description": "meu boletim", "page": "qrc:/GradesReport.qml", "profile": NetworkController.UserType.Student },
            { "icon": Icons.faFilePdf, "description": "meus documentos", "page": "qrc:/Documents.qml", "profile": NetworkController.UserType.Student }
        ]
        spacing: 10
        delegate: Item {
            width: parent.width
            height: frame.height
            visible: modelData.profile === undefined || core.networkController.userType === modelData.profile
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
                        Material.foreground: "#03728c"
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
                    if (index === 2) core.networkController.getGradesReport()
                    stackView.push(modelData.page)
                }
            }
        }
    }
}
