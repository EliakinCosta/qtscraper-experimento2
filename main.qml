import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13

import br.ifba.edu.emile 1.0

import "FontAwesome"

ApplicationWindow {
    id: window
    visible: true
    title: qsTr("Emile - Sistema de Gestão de Processos Acadêmicos")
    width: 298; height: 640

    header: ToolBar {
        Material.foreground: "white"
        visible: stackView.currentItem.header === null

        ToolButton {
            font { family: FontAwesome.solid }
            text: stackView.depth > 1 ? Icons.faChevronLeft : Icons.faBars
            onClicked: {
                if (stackView.depth > 1) stackView.pop()
                else drawer.open()
            }
        }
        Label {
            text: stackView.currentItem.title
            font.bold: true
            anchors.centerIn: parent
        }
        ToolButton {
            font { family: FontAwesome.solid }
            text: Icons.faInfo
            anchors.right: parent.right
            onClicked: infoDialog.open()
        }
    }

    Dialog {
        id: infoDialog

        x: (parent.width - width)/2
        y: (parent.height - height)/2
        width: window.width*0.9
        contentHeight: parent.height/2
        parent: ApplicationWindow.overlay

        modal: true
        title: "Emile v" + core.version
        standardButtons: Dialog.Ok

        Flickable {
            id: flickable
            clip: true
            anchors.fill: parent
            contentHeight: column.height

            Column {
                id: column
                spacing: 20
                width: parent.width

                Image {
                    id: logo
                    width: parent.width / 2
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/images/emile-logo.png"
                }

                Label {
                    width: parent.width
                    text: "Desenvolvido em <font color=\"green\">Qt</font> pelo "
                          + "Grupo de Pesquisa em Sistemas Distribuídos, Otimização, Redes e Tempo-Real (<a href=\"https://gsort.ifba.edu.br\" target=\"_blank\">GSORT</a>) "
                          + "e alunos de <a href=\"https://ads.ifba.edu.br\" _target=\"blank\">ADS</a> do Instituto Federal de Educação, Ciência e Tecnologia da Bahia (<a href=\"https://portal.ifba.edu.br\" target=\"_blank\">IFBA</a>), com o apoio da Diretoria de Gestão da Tecnologia da Informação (DGTI/IFBA)."
                          + "<br/><br/>Disponibilizado sob licença GPLv3.<br/><br/>Mantenedor: Sandro S. Andrade<br/>Colaboradores:<ul><li>Allan Edgard Silva Freitas</li><li>Ana Carolina Sokolonski</li><li>Flávia Maristela</li><li>Márcio Melo de Oliveira</li><li>Manoel Carvalho Neto</li><li>Matuzalém Guimarães</li><li>Monique Dantas</li><li>Pedro Santana</li><li>Renato Novais</li><li>Roger Souza</li><li>Vinicius Melo</li></ul>"
                    wrapMode: Label.Wrap
                    onLinkActivated: Qt.openUrlExternally(link)
                }
            }

            ScrollIndicator.vertical: ScrollIndicator {
                parent: infoDialog.contentItem
                anchors.top: flickable.top
                anchors.bottom: flickable.bottom
                anchors.right: parent.right
                anchors.rightMargin: -infoDialog.rightPadding + 1
            }
        }
    }

    Connections {
        target: core.networkController
        onNewVersionAvailable: newVersionDialog.visible = true
    }

    Dialog {
        id: newVersionDialog
        x: (parent.width - width)/2
        y: (parent.height - height)/2
        width: window.width*0.9
        parent: ApplicationWindow.overlay

        modal: true
        title: "Nova versão"
        anchors.centerIn: parent
        standardButtons: Dialog.Yes | Dialog.No

        contentItem: Label {
            text: "Uma nova versão do Emile está disponível. Deseja atualizar o aplicativo agora?"
            wrapMode: Text.WordWrap
        }
        onAccepted: Qt.openUrlExternally("https://play.google.com/store/apps/details?id=br.edu.ifba.gsort.emile")
    }

    Dialog {
        modal: true
        title: "Erro"
        x: (parent.width - width)/2
        y: (parent.height - height)/2
        width: window.width*0.9
        standardButtons: Dialog.Ok
        visible: core.networkController.errorString !== ""

        contentItem: Label {
            text: core.networkController.errorString
            wrapMode: Text.WordWrap
        }
    }

    Drawer {
        id: drawer
        width: parent.width * 3/4
        height: parent.height

        ColumnLayout {
            width: parent.width
            spacing: 0
            Image {
                source: "qrc:/images/emile-drawer.png"
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: 0.7133956386292835*parent.width
                fillMode: Image.PreserveAspectFit
                antialiasing: true
            }
            IconDelegate {
                Layout.fillWidth: true
                displayText: "Funcionalidades do SUAP"
                iconName: Icons.faBook
                onClicked: {
                    while (stackView.depth > 1) {
                        stackView.pop()
                    }
                    core.networkController.getBasicData()
                    drawer.close()
                }
            }
            IconDelegate {
                Layout.fillWidth: true
                displayText: "SEI - Consulta Pública"
                iconName: Icons.faBook
                onClicked: {
                    while (stackView.depth > 1) {
                        stackView.pop()
                    }
                    core.networkController.resetSEIPublicSearchAttempts()
                    core.networkController.prepareSEIPublicSearch()
                    drawer.close()
                }
            }
            IconDelegate {
                Layout.fillWidth: true
                displayText: "Notícias do IFBA"
                iconName: Icons.faRss
                onClicked: {
                    while (stackView.depth > 1) {
                        stackView.pop()
                    }
                    core.networkController.getIFBANews()
                    stackView.push("qrc:/IFBANews.qml")
                    drawer.close()
                }
            }
            IconDelegate {
                Layout.fillWidth: true
                displayText: "Editais 2019 da PRPGI"
                iconName: Icons.faHandshake
                onClicked: {
                    while (stackView.depth > 1) {
                        stackView.pop()
                    }
                    core.networkController.getPRPGINotices()
                    stackView.push("qrc:/PRPGINotices.qml")
                    drawer.close()
                }
            }
        }
    }

    Image {
        visible: core.networkController.status === NetworkController.Loading
        source: "qrc:///images/emile-logo.png"
        anchors.centerIn: parent
        width: Math.min(window.width, window.height)/3
        fillMode: Image.PreserveAspectFit
        antialiasing: true

        SequentialAnimation on scale {
            NumberAnimation { from: 1.0; to: 1.1; duration: 500 }
            NumberAnimation { from: 1.1; to: 1.0; duration: 500 }
            loops: Animation.Infinite
            running: core.networkController.status === NetworkController.Loading
        }
    }

    FontMetrics {
        id: fontMetrics
        font { family: "Awesome"; pointSize: 12 }
    }

    QtObject {
        id: internal

        property real maxIconWidth: fontMetrics.advanceWidth(Icons.faBusinessTime)
    }

    StackView {
        id: stackView
        anchors.fill: parent
        visible: core.networkController.status !== NetworkController.Loading
        initialItem: MainPage { }
    }

    onClosing: {
        if (Qt.platform.os == "android") {
            close.accepted = false
            if (stackView.depth > 1) stackView.pop()
        }
    }
}
