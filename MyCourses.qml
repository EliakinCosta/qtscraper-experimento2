import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13
import Qt.labs.settings 1.1

import br.ifba.edu.emile 1.0

import "FontAwesome"

Page {
    title: "Emile - Minhas Disciplinas"

    Settings {
        id: myCoursesSettings
        property alias currentTerm: termCombo.currentIndex
    }

    ColumnLayout {
        anchors { fill: parent; margins: 10 }

        ComboBox {
            id: termCombo
            Layout.fillWidth: true
            model: core.networkController.terms
            onModelChanged: currentIndex = core.networkController.terms.length - 1
            font.pixelSize: 14
            currentIndex: myCoursesSettings.currentTerm
            onCurrentIndexChanged: {
                if (currentIndex !== -1) {
                    core.networkController.getCourses(core.networkController.terms[currentIndex])
                }
            }
        }
        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: core.networkController.courses
            spacing: 10
            delegate: Frame {
                width: parent.width
                Material.elevation: 3
                ColumnLayout {
                    width: parent.width
                    IconLabel { icon: Icons.faBook; text: modelData.acronym + " (diário " + modelData.id + ")" }
                    IconLabel { icon: Icons.faChalkboardTeacher; text: modelData.name }
                    IconLabel { icon: Icons.faUserTie; text: modelData.professorName; visible: core.networkController.userType === NetworkController.UserType.Student }
                    IconLabel { icon: Icons.faGraduationCap; text: modelData.level }
                    IconLabel { icon: Icons.faHammer; text: modelData.workload }
                    Repeater {
                        model: modelData.timetable
                        IconLabel { icon: Icons.faClock; text: modelData.day + " (" + modelData.time + ")" }
                    }
                    MenuSeparator { Layout.fillWidth: true }
                    ItemDelegate {
                        Layout.fillWidth: true
                        Layout.topMargin: -parent.spacing
                        Layout.bottomMargin: -parent.spacing
                        font.capitalization: Font.AllUppercase
                        padding: 0; topPadding: 0; bottomPadding: 0
                        text: "Registro de aulas e faltas"
                        Label {
                            font { family: FontAwesome.solid }
                            anchors { right: parent.right; verticalCenter: parent.verticalCenter }
                            Material.foreground: "#03728c"
                            text: Icons.faChevronRight
                        }
                        onClicked: {
                            core.networkController.getCourseClasses(modelData.id)
                            stackView.push("qrc:/ClassRecord.qml", { course: modelData })
                        }
                    }
                }
            }
            Label {
                anchors.centerIn: parent
                width: parent.width-2*parent.spacing
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
                color: "#607D8B"
                visible: core.networkController.courses.length === 0
                text: "nenhuma disciplina cadastrada para este período"
            }
        }
    }
}
