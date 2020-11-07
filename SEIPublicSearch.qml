import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13
import Qt.labs.settings 1.1

import "FontAwesome"

Page {
    title: "Emile - SEI - Consulta Pública"

    Settings {
        id: mySeiProcessesSettings
    }

    Dialog {
        id: removeProcessesDialog

        x: (parent.width - width)/2; y: (parent.height - height)/2
        width: window.width*0.9
        contentHeight: parent.height/2
        parent: ApplicationWindow.overlay

        modal: true
        title: "Remoção de consultas anteriores"
        standardButtons: Dialog.Ok | Dialog.Cancel

        Flickable {
            id: flickable
            clip: true
            anchors.fill: parent
            contentHeight: column.height

            ColumnLayout {
                id: column
                width: parent.width
                CheckBox { id: allCheckBox; text: "todos"; font.bold: true }
                Repeater {
                    id: repeater
                    model: Object.keys(mySeiProcessesSettings.value("processCache"))
                    CheckBox { text: modelData; checked: allCheckBox.checked }
                }
            }

            ScrollIndicator.vertical: ScrollIndicator {
                parent: removeProcessesDialog.contentItem
                anchors.top: flickable.top
                anchors.bottom: flickable.bottom
                anchors.right: parent.right
                anchors.rightMargin: -removeProcessesDialog.rightPadding + 1
            }
        }

        onAccepted: {
            var processCache = mySeiProcessesSettings.value("processCache")
            for (var i = 0; i < repeater.count; ++i)
                if (repeater.itemAt(i).checked)
                    delete processCache[repeater.itemAt(i).text];
            mySeiProcessesSettings.setValue("processCache", processCache)
            mySeiProcessesSettings.sync()
            repeater.model = Qt.binding(function() { return Object.keys(mySeiProcessesSettings.value("processCache")) })
            previousProcessesComboBox.model = Qt.binding(function() { return [""].concat(Object.keys(mySeiProcessesSettings.value("processCache"))) })
            previousProcessesComboBox.currentIndex = 0
            if (Object.keys(mySeiProcessesSettings.value("processCache")).length === 0) {
                previousProcessesLabel.visible = false
                previousProcessesLayout.visible = false
            }
        }
    }

    ColumnLayout {
        anchors { left: parent.left; right: parent.right; top: parent.top; margins: 10 }
        spacing: 30

        IconLabel { id: previousProcessesLabel; icon: Icons.faCubes; text: "Consultas anteriores"; inMenu: false; visible: mySeiProcessesSettings.value("processCache") !== undefined && Object.keys(mySeiProcessesSettings.value("processCache")).length > 0; Layout.bottomMargin: -25 }
        RowLayout {
            id: previousProcessesLayout
            Layout.fillWidth: true
            spacing: 0
            visible: mySeiProcessesSettings.value("processCache") !== undefined && Object.keys(mySeiProcessesSettings.value("processCache")).length > 0
            ComboBox {
                id: previousProcessesComboBox
                Layout.fillWidth: true
                model: [""].concat(Object.keys(mySeiProcessesSettings.value("processCache")))
                onCurrentTextChanged: processNumber.text = currentText
            }
            ToolButton {
                font { family: FontAwesome.solid; pointSize: 12 }
                text: Icons.faTrash
                Material.foreground: "#03728c"
                onClicked: removeProcessesDialog.open()
            }
        }
        IconLabel { icon: Icons.faCubes; text: "Nº do processo ou documento"; inMenu: false; Layout.bottomMargin: -25 }
        TextField { id: processNumber; Layout.fillWidth: true }
        IconLabel { icon: Icons.faUserShield; text: "Digite os seguintes caracteres"; inMenu: false }
        Image {
            Layout.alignment: Qt.AlignHCenter
            source: (core.networkController.seiPublicSearchCaptcha !== '') ? "https://sei.ifba.edu.br" + core.networkController.seiPublicSearchCaptcha:""
            Layout.bottomMargin: -25
        }
        TextField { id: captcha; Layout.fillWidth: true }
        Button {
            text: "Consultar"
            Layout.alignment: Qt.AlignHCenter
            Material.background: "#03728c"
            Material.foreground: "white"
            onClicked: {
                core.networkController.resetSEIPublicSearchAttempts()
                core.networkController.searchSEIProcess(processNumber.text, captcha.text)
            }
        }
    }

    Connections {
        target: core.networkController
        onErrorStringChanged: captcha.text = ''
        onSeiProcessDetailsAvailable: stackView.push("SEIProcessDetails.qml");
    }
}
