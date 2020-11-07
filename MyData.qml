import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13

import br.ifba.edu.emile 1.0

Page {
    title: "Emile - Meus Dados"

    Flickable {
        anchors { fill: parent; margins: 10 }
        contentWidth: parent.width - 2*anchors.margins
        contentHeight: columnLayout.height

        ColumnLayout {
            id: columnLayout
            width: parent.width - 2*parent.anchors.margins
            spacing: 10
            GroupBox {
                title: core.networkController.userType === NetworkController.UserType.Professor ? "Informações Gerais":"Dados Gerais"
                visible: core.networkController.myData.generalInformation !== undefined && core.networkController.myData.generalInformation.length > 0
                Layout.fillWidth: true
                Material.elevation: 1
                ColumnLayout {
                    width: parent.width
                    spacing: 15
                    Repeater {
                        model: core.networkController.myData.generalInformation
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 5
                            Label {
                                Layout.fillWidth: true
                                wrapMode: Text.WordWrap
                                text: modelData.header
                                font.bold: true
                                Material.foreground: "#03728c"
                            }
                            Label {
                                Layout.fillWidth: true
                                wrapMode: Text.WordWrap
                                text: modelData.value
                            }
                        }
                    }
                }
            }
            GroupBox {
                title: "Dados do Professor"
                visible: core.networkController.userType === NetworkController.UserType.Professor && core.networkController.myData.professorInformation.length > 0
                Layout.fillWidth: true
                Material.elevation: 1
                ColumnLayout {
                    width: parent.width
                    spacing: 15
                    Repeater {
                        model: core.networkController.myData.professorInformation
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 5
                            Label {
                                Layout.fillWidth: true
                                wrapMode: Text.WordWrap
                                text: modelData.header
                                font.bold: true
                                Material.foreground: "#03728c"
                            }
                            Label {
                                Layout.fillWidth: true
                                wrapMode: Text.WordWrap
                                text: modelData.value
                            }
                        }
                    }
                }
            }
            GroupBox {
                title: "Dados Acadêmicos"
                visible: core.networkController.userType === NetworkController.UserType.Student && core.networkController.myData.academicInformation !== undefined && core.networkController.myData.academicInformation.length > 0
                Layout.fillWidth: true
                Material.elevation: 1
                ColumnLayout {
                    width: parent.width
                    spacing: 15
                    Repeater {
                        model: core.networkController.myData.academicInformation
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 5
                            Label {
                                Layout.fillWidth: true
                                wrapMode: Text.WordWrap
                                text: modelData.header
                                font.bold: true
                                Material.foreground: "#03728c"
                            }
                            Label {
                                Layout.fillWidth: true
                                wrapMode: Text.WordWrap
                                text: modelData.value
                            }
                        }
                    }
                }
            }
            GroupBox {
                title: "Dados do Curso"
                visible: core.networkController.userType === NetworkController.UserType.Student && core.networkController.myData.courseInformation !== undefined && core.networkController.myData.courseInformation.length > 0
                Layout.fillWidth: true
                Material.elevation: 1
                ColumnLayout {
                    width: parent.width
                    spacing: 15
                    Repeater {
                        model: core.networkController.myData.courseInformation
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 5
                            Label {
                                Layout.fillWidth: true
                                wrapMode: Text.WordWrap
                                text: modelData.header
                                font.bold: true
                                Material.foreground: "#03728c"
                            }
                            Label {
                                Layout.fillWidth: true
                                wrapMode: Text.WordWrap
                                text: modelData.value
                            }
                        }
                    }
                }
            }
            GroupBox {
                title: "Dados sobre Cotas"
                visible: core.networkController.userType === NetworkController.UserType.Student && core.networkController.myData.quotaInformation !== undefined && core.networkController.myData.quotaInformation.length > 0
                Layout.fillWidth: true
                Material.elevation: 1
                ColumnLayout {
                    width: parent.width
                    spacing: 15
                    Repeater {
                        model: core.networkController.myData.quotaInformation
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 5
                            Label {
                                Layout.fillWidth: true
                                wrapMode: Text.WordWrap
                                text: modelData.header
                                font.bold: true
                                Material.foreground: "#03728c"
                            }
                            Label {
                                Layout.fillWidth: true
                                wrapMode: Text.WordWrap
                                text: modelData.value
                            }
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted: core.networkController.getMyData()
}
