import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13
import Qt.labs.settings 1.1

import br.ifba.edu.emile 1.0

import "FontAwesome"

Page {
    property var course

    title: course.acronym + " - Registro de Aulas"

    Dialog {
        id: confirmationDialog
        modal: true
        title: "Remoção de Aula"
        anchors.centerIn: parent
        standardButtons: Dialog.Ok | Dialog.Cancel

        Label { text: "Confirma a exclusão desta aula?" }

        onAccepted: core.networkController.removeClass(core.networkController.courseClasses[listView.currentIndex].id, listView.currentIndex, course.id, core.networkController.courseParts[partCombo.currentIndex].id)
        onRejected: {
            listView.selectedItem.visible = false
            listView.selectedItem = null
        }
    }

    QtObject {
        id: classRecordInternal

        property int totalClasses
        property int totalUnattendances
    }

    ColumnLayout {
        anchors { fill: parent; margins: 10 }

        Label {
            visible: core.networkController.userType === NetworkController.UserType.Student && classRecordInternal.totalClasses > 0
            text: "Total de faltas: " + classRecordInternal.totalUnattendances + " em " + classRecordInternal.totalClasses + " aulas (" + (100*classRecordInternal.totalUnattendances/classRecordInternal.totalClasses).toFixed(2) + "%)"
            Layout.fillWidth: true
        }

        ProgressBar {
            id: progressBar
            visible: core.networkController.userType === NetworkController.UserType.Student && classRecordInternal.totalClasses > 0
            Layout.fillWidth: true
            from: 0
            to: classRecordInternal.totalClasses
            value: classRecordInternal.totalUnattendances
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
                    color: classRecordInternal.totalUnattendances/classRecordInternal.totalClasses < 0.2 ? Material.color(Material.Green):
                           classRecordInternal.totalUnattendances/classRecordInternal.totalClasses <= 0.25 ? "orange":Material.color(Material.Red)
                }
            }
        }

        Label {
            visible: core.networkController.userType === NetworkController.UserType.Professor
            text: core.networkController.courseParts[partCombo.currentIndex] !== undefined ? "Total: " + core.networkController.courseParts[partCombo.currentIndex].totalClassesString + " (" + core.networkController.courseParts[partCombo.currentIndex].classesPercentage + "%)":""
            Layout.fillWidth: true
        }

        ProgressBar {
            id: progressBar2
            visible: core.networkController.userType === NetworkController.UserType.Professor
            Layout.fillWidth: true
            from: 0; to: 100
            value: core.networkController.courseParts[partCombo.currentIndex] !== undefined ? parseInt(core.networkController.courseParts[partCombo.currentIndex].classesPercentage):0
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
                    width: progressBar2.visualPosition * parent.width
                    height: parent.height
                    radius: 2
                    color: "#03728c"
                }
            }
        }

        ComboBox {
            id: partCombo
            visible: core.networkController.userType === NetworkController.UserType.Professor
            Layout.fillWidth: true
            model: core.networkController.courseParts
            textRole: "description"
            font.pixelSize: 14
            onCurrentIndexChanged: {
                if (currentIndex !== -1 && currentText !== "")
                    core.networkController.getCourseClasses(course.id, core.networkController.courseParts[currentIndex].id)
            }
        }

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: core.networkController.courseClasses

            onModelChanged: {
                classRecordInternal.totalClasses = 0
                classRecordInternal.totalUnattendances = 0
                for (var i = 0; i < core.networkController.courseClasses.length; ++i) {
                    classRecordInternal.totalClasses += parseInt(core.networkController.courseClasses[i].hours)
                    classRecordInternal.totalUnattendances += parseInt(core.networkController.courseClasses[i].unattendances)
                }
            }

            spacing: 10
            clip: true

            property var selectedItem: null

            delegate: Item {
                width: parent.width
                height: frame.height
                Frame {
                    id: frame
                    width: parent.width
                    Material.elevation: 3

                    ColumnLayout {
                        width: parent.width
                        Item {
                            Layout.fillWidth: true
                            implicitHeight: controlsLayout.height
                            ColumnLayout {
                                id: controlsLayout
                                width: parent.width
                                IconLabel { icon: Icons.faCubes; text: modelData.part }
                                IconLabel { icon: Icons.faBusinessTime; text: modelData.hours + " aulas" }
                                IconLabel { icon: Icons.faCalendarAlt; text: modelData.date }
                                IconLabel { icon: Icons.faUserTie; text: modelData.professor }
                                IconLabel { icon: Icons.faClipboardCheck; text: modelData.description }
                                IconLabel { icon: Icons.faTimes; text: modelData.unattendances; visible: core.networkController.userType === NetworkController.UserType.Student }
                            }
                            MouseArea {
                                anchors.fill: parent
                                onPressAndHold: {
                                    if (core.networkController.userType === NetworkController.UserType.Professor && modelData.id !== '') {
                                        listView.currentIndex = index
                                        if (listView.selectedItem !== null && listView.selectedItem !== layout)
                                            listView.selectedItem.visible = false
                                        layout.visible = !layout.visible
                                        listView.selectedItem = (layout.visible) ? layout:null
                                    }
                                }
                                onClicked: {
                                    if (core.networkController.userType === NetworkController.UserType.Professor && modelData.id !== '') {
                                        listView.currentIndex = index
                                        if (listView.selectedItem !== null) {
                                            listView.selectedItem.visible = false
                                            listView.selectedItem = null
                                        }
                                    }
                                }
                            }
                            ToolTip {
                                id: tooltip
                                anchors.centerIn: parent
                                delay: 1000
                                timeout: 4000
                                visible: index === 0 && frame.visible && core.networkController.userType === NetworkController.UserType.Professor && modelData.id !== ''
                                text: qsTr("pressione e segure para opções")
                            }
                        }
                        MenuSeparator { Layout.fillWidth: true; visible: core.networkController.userType === NetworkController.UserType.Professor }
                        ItemDelegate {
                            Layout.fillWidth: true
                            Layout.topMargin: -parent.spacing
                            Layout.bottomMargin: -parent.spacing
                            font.capitalization: Font.AllUppercase
                            padding: 0; topPadding: 0; bottomPadding: 0
                            text: "Registro de faltas"
                            visible: core.networkController.userType === NetworkController.UserType.Professor
                            Label {
                                font { family: FontAwesome.solid }
                                anchors { right: parent.right; verticalCenter: parent.verticalCenter }
                                Material.foreground: "#03728c"
                                text: Icons.faChevronRight
                            }
                            onClicked: {
                                if (core.networkController.userType === NetworkController.UserType.Professor) {
                                    listView.currentIndex = index
                                    if (listView.selectedItem !== null) {
                                        listView.selectedItem.visible = false
                                        listView.selectedItem = null
                                    }
                                }
                                stackView.push("qrc:/AttendanceRecord.qml", { course: course, classRecord: core.networkController.courseClasses[index], classIndex: index, partRecord: partCombo.model[partCombo.currentIndex] })
                            }
                        }
                    }
                }
                IconLabel {
                    icon: Icons.faLock
                    visible: core.networkController.userType === NetworkController.UserType.Professor && modelData.id === ''
                    anchors { top: frame.top; right: frame.right; margins: 12; rightMargin: 7 }
                }
                ColumnLayout {
                    id: layout
                    visible: false
                    onVisibleChanged: if (visible) { anim.running = true }
                    spacing: -5
                    z: 1
                    anchors { top: frame.top; right: frame.right; margins: 5; rightMargin: 0 }
                    RoundButton {
                        id: removeButton
                        font { family: FontAwesome.solid; pointSize: 10 }
                        text: Icons.faTrash
                        Material.foreground: "white"
                        Material.background: Material.Red
                        onClicked: confirmationDialog.visible = true
                    }
                    RoundButton {
                        font { family: FontAwesome.solid; pointSize: 10 }
                        text: Icons.faPen
                        Material.foreground: "white"
                        Material.background: "#03728c"
                        onClicked: stackView.push("qrc:/AddEditClass.qml", { classRecord: modelData, course: course, partIndex: partCombo.currentIndex, courseParts: core.networkController.courseParts })
                    }
                    PropertyAnimation { id: anim; target: layout; property: "anchors.topMargin"; from: frame.height; to: 0; duration: 1000; easing.type: Easing.OutBounce }
                }
            }
            Label {
                anchors.centerIn: parent
                width: parent.width-2*parent.spacing
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
                color: "#607D8B"
                visible: listView.model.length === 0
                text: "nenhuma aula cadastrada para esta unidade"
            }
        }
    }

    RoundButton {
        anchors { bottom: parent.bottom; right: parent.right; margins: 10 }
        padding: 25
        font { family: FontAwesome.solid; pointSize: 12 }
        visible: core.networkController.userType === NetworkController.UserType.Professor && core.networkController.courseParts[partCombo.currentIndex] !== undefined && core.networkController.courseParts[partCombo.currentIndex].closed !== "Sim"
        text: Icons.faPlus
        Material.foreground: "white"
        Material.background: "#03728c"
        onClicked: stackView.push("qrc:/AddEditClass.qml", { classRecord: null, course: course, partIndex: partCombo.currentIndex, courseParts: core.networkController.courseParts })
    }
}
