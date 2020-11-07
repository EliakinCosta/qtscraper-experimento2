import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13
import Qt.labs.settings 1.1

import "FontAwesome"

Page {
    title: "Emile - Meu Boletim"

    ColumnLayout {
        anchors { fill: parent; margins: 10 }

        ComboBox {
            id: gradesReportTermCombo
            Layout.fillWidth: true
            model: core.networkController.gradesReportTerms
            font.pixelSize: 14
            onCurrentIndexChanged: {
                if (currentIndex !== -1 && core.networkController.gradesReportTerms[currentIndex] !== undefined) {
                    core.networkController.getGradesReport(core.networkController.gradesReportTerms[currentIndex].replace('.', '_'))
                }
            }
        }
        ListView {            
            Layout.fillWidth: true; Layout.fillHeight: true
            clip: true
            model: core.networkController.gradesReport
            spacing: 10
            delegate: Frame {
                width: parent.width
                Material.elevation: 3
                ColumnLayout {
                    width: parent.width
                    IconLabel { icon: Icons.faChalkboardTeacher; text: modelData.courseName }
                    IconLabel { icon: Icons.faHammer; text: modelData.workload + " (" + modelData.totalClasses + " ministradas)" }
                    IconLabel { icon: Icons.faUserCheck; text: "Frequência total: " + modelData.attendance + " (" + modelData.totalUnattendances + " faltas)" }
                    IconLabel { icon: (modelData.situation === "Aprovado" || modelData.situation === "Cursando") ? Icons.faThumbsUp:Icons.faThumbsDown; text: modelData.situation; color: (modelData.situation === "Aprovado" || modelData.situation === "Cursando") ? "green":"red" }
                    IconLabel { icon: Icons.faThermometerHalf; visible: modelData.part1Grade !== undefined && modelData.part1Grade !== '-'; text: "Nota unidade 1: " + modelData.part1Grade + " (" + modelData.part1Unattendances + " faltas)" }
                    IconLabel { icon: Icons.faThermometerHalf; visible: modelData.part2Grade !== undefined && modelData.part2Grade !== '-'; text: "Nota unidade 2: " + modelData.part2Grade + " (" + modelData.part2Unattendances + " faltas)" }
                    IconLabel { icon: Icons.faThermometerHalf; visible: modelData.part3Grade !== undefined && modelData.part3Grade !== '-'; text: "Nota unidade 3: " + modelData.part3Grade + " (" + modelData.part3Unattendances + " faltas)" }
                    IconLabel { icon: Icons.faThermometerHalf; visible: modelData.part4Grade !== undefined && modelData.part4Grade !== '-'; text: "Nota unidade 4: " + modelData.part4Grade + " (" + modelData.part4Unattendances + " faltas)" }
                    IconLabel { icon: Icons.faStar; visible: modelData.partsGrade !== '-'; text: "Média das unidades: " + modelData.partsGrade }
                    IconLabel { icon: Icons.faThermometerHalf; visible: modelData.finalPartGrade !== "-"; text: "Nota avaliação final: " + modelData.finalPartGrade + "(" + modelData.finalPartUnattendances + " faltas)" }
                    IconLabel { icon: Icons.faMedal; visible: modelData.finalGrade !== '-'; text: "Média final: " + modelData.finalGrade }
                    MenuSeparator { Layout.fillWidth: true; visible: modelData.detailsLink !== undefined }
                    ItemDelegate {
                        Layout.fillWidth: true
                        Layout.topMargin: -parent.spacing; Layout.bottomMargin: -parent.spacing
                        visible: modelData.detailsLink !== undefined
                        font.capitalization: Font.AllUppercase
                        padding: 0; topPadding: 0; bottomPadding: 0
                        text: "Detalhar"
                        Label {
                            font { family: FontAwesome.solid }
                            anchors { right: parent.right; verticalCenter: parent.verticalCenter }
                            Material.foreground: "#03728c"
                            text: Icons.faChevronRight
                        }
                        onClicked: {
                            core.networkController.getGradesReportDetails(modelData.detailsLink)
                            stackView.push("qrc:/GradesReportDetails.qml", { course: modelData })
                        }
                    }
                }
            }
        }
    }
}
