import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13
import Qt.labs.settings 1.1

import "FontAwesome"

Page {
    title: "Emile - SEI - Detalhes do Processo"

    property var processCache
    property int documentsCount
    property int movesCount

    Settings {
        id: mySeiProcessesSettings
    }

    Flickable {
        anchors { fill: parent; margins: 10 }
        contentWidth: parent.width - 2*anchors.margins
        contentHeight: columnLayout.height

        ColumnLayout {
            id: columnLayout
            width: parent.width - 2*parent.anchors.margins
            spacing: 10
            GroupBox {
                title: "Autuação"
                Layout.fillWidth: true
                Material.elevation: 1
                ColumnLayout {
                    width: parent.width
                    spacing: 10
                    IconLabel { icon: Icons.faCubes; text: core.networkController.seiProcessDetails.data['Processo'] }
                    IconLabel { icon: Icons.faMapSigns; text: core.networkController.seiProcessDetails.data['Tipo'] }
                    IconLabel { icon: Icons.faCalendar; text: core.networkController.seiProcessDetails.data['Data de Registro'] }
                    IconLabel { icon: Icons.faUser; text: "Interessados:\n" + core.networkController.seiProcessDetails.data['Interessados'] }
                }
            }
            GroupBox {
                title: "Protocolos (" + core.networkController.seiProcessDetails.documents.length + " registros" + ((core.networkController.seiProcessDetails.documents.length !== documentsCount) ? (" - " + (core.networkController.seiProcessDetails.documents.length-documentsCount) + ((core.networkController.seiProcessDetails.documents.length-documentsCount === 1) ? " novo":" novos")):"") + ")"
                Layout.fillWidth: true
                Material.elevation: 1
                ColumnLayout {
                    width: parent.width
                    spacing: 10
                    Repeater {
                        model: core.networkController.seiProcessDetails.documents
                        IconLabel { icon: Icons.faFileAlt; text: modelData.type + " (" + modelData.department + " - " + modelData.date + ")"; font.bold: (index >= documentsCount) ? true:false }
                    }
                }
            }
            GroupBox {
                title: "Andamentos (" + core.networkController.seiProcessDetails.moves.length + " registros" + ((core.networkController.seiProcessDetails.moves.length !== movesCount) ? (" - " + (core.networkController.seiProcessDetails.moves.length-movesCount) + ((core.networkController.seiProcessDetails.moves.length-movesCount === 1) ? " novo":" novos")):"") + ")"
                Layout.fillWidth: true
                Material.elevation: 1
                ColumnLayout {
                    width: parent.width
                    spacing: 10
                    Repeater {
                        model: core.networkController.seiProcessDetails.moves
                        IconLabel { icon: Icons.faShoePrints; text: modelData.datetime + " (" + modelData.department + ") - " + modelData.description; font.bold: (index < core.networkController.seiProcessDetails.moves.length-movesCount) ? true:false }
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        processCache = mySeiProcessesSettings.value("processCache")
        if (processCache === undefined) {
            processCache = ({})
        }
        console.log(Object.keys(processCache))
        if (processCache[core.networkController.seiProcessDetails.data['Processo']] === undefined) {
            documentsCount = core.networkController.seiProcessDetails.documents.length
            movesCount = core.networkController.seiProcessDetails.moves.length
        } else {
            documentsCount = processCache[core.networkController.seiProcessDetails.data['Processo']].documentsCount
            movesCount = processCache[core.networkController.seiProcessDetails.data['Processo']].movesCount
        }
        console.log(documentsCount)
        console.log(movesCount)
        processCache[core.networkController.seiProcessDetails.data['Processo']] = {}
        processCache[core.networkController.seiProcessDetails.data['Processo']].documentsCount = core.networkController.seiProcessDetails.documents.length
        processCache[core.networkController.seiProcessDetails.data['Processo']].movesCount = core.networkController.seiProcessDetails.moves.length
        mySeiProcessesSettings.setValue("processCache", processCache)
        mySeiProcessesSettings.sync()
    }
}
