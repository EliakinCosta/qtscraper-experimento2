import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13
import Qt.labs.settings 1.1

import "FontAwesome"

Page {
    title: "Emile - Detalhe do Boletim"

    Flickable {
        anchors.fill: parent
        contentWidth: parent.width
        contentHeight: detailsLayout.height

        ColumnLayout {
            id: detailsLayout
            width: parent.width
            spacing: 10

            Repeater {
                model: core.networkController.gradesReportDetails
                ColumnLayout {
                    spacing: 10
                    Layout.fillWidth: true
                    Label {
                        Layout.fillWidth: true
                        Layout.leftMargin: 10; Layout.rightMargin: 10; Layout.topMargin: 10
                        horizontalAlignment: Qt.AlignHCenter
                        text: modelData.gradesTerm
                        visible: modelData.grades.length > 0
                    }
                    Repeater {
                        Layout.fillWidth: true
                        clip: true
                        model: modelData.grades
                        Frame {
                            Layout.fillWidth: true
                            Layout.leftMargin: 10; Layout.rightMargin: 10
                            Material.elevation: 3
                            ColumnLayout {
                                width: parent.width
                                IconLabel { icon: Icons.faBook; text: modelData.acronym + " (" + modelData.type + ")" + (modelData.description !== '-' ? (" - " + modelData.description):"") }
                                IconLabel { icon: Icons.faStar; text: "Nota: " + modelData.grade + (modelData.weight !== '-' ? (" (peso " + modelData.weight + ")"):"") }
                            }
                        }
                    }
                }
            }
        }
    }
}
