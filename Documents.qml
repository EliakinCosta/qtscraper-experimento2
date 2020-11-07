import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13
import Qt.labs.settings 1.1

import "FontAwesome"

Page {
    title: "Emile - Notícias do IFBA"

    ListView {
        anchors { fill: parent; margins: 10 }
        model: [
            { "icon": Icons.faFilePdf, "description": "histórico escolar parcial", "url": "https://suap.ifba.edu.br/edu/emitir_historico_parcial_pdf/" },
            { "icon": Icons.faFilePdf, "description": "declaração de matrícula", "url": "https://suap.ifba.edu.br/edu/declaracaomatricula_pdf/" },
            { "icon": Icons.faFilePdf, "description": "comprovante de dados acadêmicos", "url": "https://suap.ifba.edu.br/edu/comprovante_dados_academicos_pdf/" },
            { "icon": Icons.faFilePdf, "description": "declaração de vínculo", "url": "https://suap.ifba.edu.br/edu/declaracaovinculo_pdf/" }
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
                onClicked: core.networkController.getStudentDocument(modelData.description, modelData.url)
            }
        }
    }
}
