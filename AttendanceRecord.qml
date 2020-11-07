import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13
import Qt.labs.settings 1.1

import "FontAwesome"

Page {
    property var course
    property var classRecord
    property int classIndex
    property var partRecord

    title: course.acronym + " - Registro de Faltas"
    property var studentsAttendances

    header: ToolBar {
        Material.foreground: "white"

        Label {
            text: stackView.currentItem.title
            font.bold: true
            anchors.centerIn: parent
        }
        ToolButton {
            font { family: FontAwesome.solid }
            anchors { left: parent.left; verticalCenter: parent.verticalCenter }
            visible: stackView.depth > 1
            text: stackView.depth > 2 ? Icons.faChevronLeft : Icons.faBars
            onClicked: {
                if (stackView.depth > 2) stackView.pop()
                else drawer.open()
            }
        }
        ToolButton {
            font { family: FontAwesome.solid }
            anchors { right: parent.right; verticalCenter: parent.verticalCenter }
            visible: stackView.depth > 1 && partRecord.closed !== "Sim"
            text: Icons.faSave
            onClicked: {
                stackView.pop()
                core.networkController.registerUpdateAttendance(classRecord.id, studentsAttendances, course.id, partRecord.id)
            }
        }
    }

    IconLabel {
        icon: Icons.faLock
        visible: partRecord.closed === "Sim"
        anchors { top: parent.top; right: parent.right; margins: 10; rightMargin: 5 }
    }

    ColumnLayout {
        anchors { fill: parent; margins: 10 }

        Label {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            text: "data da aula: " + classRecord.date
            color: "#3e3e3e"
        }

        SwipeView {
            id: swipeView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Repeater {
                model: core.networkController.courseStudents
                onModelChanged: {
                    studentsAttendances = {}
                    for (var i = 0; i < core.networkController.courseStudents.length; ++i)
                        studentsAttendances[core.networkController.courseStudents[i].id] = core.networkController.courseStudents[i].unattendances[classIndex]
                }

                Item {
                    ColumnLayout {
                        anchors.fill: parent
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 10
                            Label {
                                Layout.maximumWidth: parent.parent.width - 20
                                Layout.minimumWidth: parent.parent.width - 20
                                Layout.alignment: Qt.AlignHCenter
                                horizontalAlignment: Text.AlignHCenter
                                font { bold: true; pixelSize: 32 }
                                text: modelData.name
                                wrapMode: Text.WordWrap
                                Material.foreground: "#3e3e3e"
                            }
                            Label {
                                Layout.fillWidth: true
                                horizontalAlignment: Text.AlignHCenter
                                font { pixelSize: 16 }
                                text: modelData.enrollment
                                Material.foreground: "#3e3e3e"
                            }
                        }
                        ColumnLayout {
                            Layout.alignment: Qt.AlignHCenter
                            spacing: 2
                            Label {
                                id: unattendancesLabel
                                text: "Total de faltas: " + modelData.totalUnattendances + " em " + partRecord.totalClasses + " aulas (" + (100*modelData.totalUnattendances/partRecord.totalClasses).toFixed(2) + "%)"
                                Layout.alignment: Qt.AlignHCenter
                            }
                            ProgressBar {
                                id: progressBar
                                Layout.alignment: Qt.AlignHCenter
                                Layout.preferredWidth: unattendancesLabel.width
                                from: 0
                                to: partRecord.totalClasses
                                value: modelData.totalUnattendances
                                Behavior on value { NumberAnimation { duration: 1000; easing.type: Easing.InOutElastic } }
                                background: Rectangle {
                                    implicitWidth: 200
                                    implicitHeight: 30
                                    color: "#e6e6e6"
                                    radius: 3
                                }

                                contentItem: Item {
                                    implicitWidth: 200
                                    implicitHeight: 30

                                    Rectangle {
                                        width: progressBar.visualPosition * parent.width
                                        height: parent.height
                                        radius: 2
                                        color: modelData.totalUnattendances/partRecord.totalClasses < 0.2 ? Material.color(Material.Green):
                                                                                                            modelData.totalUnattendances/partRecord.totalClasses <= 0.25 ? "orange":Material.color(Material.Red)
                                    }
                                }
                            }
                        }
                        ColumnLayout {
                            Layout.alignment: Qt.AlignHCenter
                            spacing: -5
                            Label {
                                text: "Faltas a aplicar"
                                Layout.alignment: Qt.AlignHCenter
                            }
                            SpinBox {
                                id: unattendancesSpin
                                Layout.alignment: Qt.AlignHCenter
                                from: 1; to: classRecord.hours
                                value: core.networkController.courseStudents[index].unattendances[classIndex] === "0" ? classRecord.hours:core.networkController.courseStudents[index].unattendances[classIndex]
                                onValueChanged: if (timesButton.highlighted) studentsAttendances[core.networkController.courseStudents[index].id] = value
                                enabled: partRecord.closed !== "Sim"
                            }
                        }
                        Row {
                            Layout.alignment: Qt.AlignHCenter
                            spacing: 30
                            ColumnLayout {
                                RoundButton {
                                    id: checkButton
                                    padding: 25
                                    font { family: FontAwesome.solid; pointSize: 12 }
                                    text: Icons.faCheck
                                    Material.foreground: "white"
                                    highlighted: modelData.unattendances[classIndex] === "0"
                                    enabled: partRecord.closed !== "Sim"
                                    onClicked: {
                                        timesButton.highlighted = false
                                        highlighted = true
                                        studentsAttendances[core.networkController.courseStudents[index].id] = 0
                                        if (swipeView.currentIndex < core.networkController.courseStudents.length-1)
                                            swipeView.currentIndex++
                                    }
                                    background: Rectangle {
                                        implicitWidth: 40
                                        implicitHeight: 40
                                        radius: checkButton.radius
                                        opacity: enabled ? 1 : 0.3
                                        scale: checkButton.highlighted ? 1.3 : 1.0
                                        visible: !checkButton.flat || checkButton.down || checkButton.checked || checkButton.highlighted
                                        color: Material.color(Material.Green)
                                        border.color: "#444444"
                                        border.width: checkButton.highlighted ? 1 : 0
                                    }
                                }
                                Label { Layout.alignment: Qt.AlignHCenter; text: "presente"; Layout.topMargin: checkButton.scale === 1 ? (timesButton.height-checkButton.height):0 }
                            }
                            ColumnLayout {
                                RoundButton {
                                    id: timesButton
                                    padding: 25
                                    font { family: FontAwesome.solid; pointSize: 12 }
                                    text: Icons.faTimes
                                    Layout.preferredWidth: checkButton.width
                                    Material.foreground: "white"
                                    highlighted: modelData.unattendances[classIndex] !== "0"
                                    enabled: partRecord.closed !== "Sim"
                                    onClicked: {
                                        checkButton.highlighted = false
                                        highlighted = true
                                        studentsAttendances[core.networkController.courseStudents[index].id] = unattendancesSpin.value
                                        if (swipeView.currentIndex < core.networkController.courseStudents.length-1)
                                            swipeView.currentIndex++
                                    }
                                    background: Rectangle {
                                        implicitWidth: 40
                                        implicitHeight: 40
                                        radius: timesButton.radius
                                        opacity: enabled ? 1 : 0.3
                                        scale: timesButton.highlighted ? 1.3 : 1.0
                                        visible: !timesButton.flat || timesButton.down || timesButton.checked || timesButton.highlighted
                                        color: Material.color(Material.Red)
                                        border.color: "#444444"
                                        border.width: timesButton.highlighted ? 1 : 0
                                    }
                                }
                                Label { Layout.alignment: Qt.AlignHCenter; text: "ausente"; Layout.topMargin: timesButton.scale === 1 ? (checkButton.height-timesButton.height):0 }
                            }
                        }
                    }
                }
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            ItemDelegate {
                Label {
                    anchors.centerIn: parent
                    font { family: FontAwesome.solid }
                    Material.foreground: "#03728c"
                    text: Icons.faChevronLeft
                    enabled: swipeView.currentIndex > 0
                }
                onClicked: {
                    if (swipeView.currentIndex > 0)
                        swipeView.currentIndex--
                }
            }
            Label { text: swipeView.currentIndex+1 + " de " + core.networkController.courseStudents.length }
            ItemDelegate {
                Label {
                    anchors.centerIn: parent
                    font { family: FontAwesome.solid }
                    Material.foreground: "#03728c"
                    text: Icons.faChevronRight
                    enabled: swipeView.currentIndex < core.networkController.courseStudents.length-1
                }
                onClicked: {
                    if (swipeView.currentIndex < core.networkController.courseStudents.length-1)
                        swipeView.currentIndex++
                }
            }
        }
    }
}
