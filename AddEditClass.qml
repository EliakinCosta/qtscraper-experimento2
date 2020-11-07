import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13
import Qt.labs.settings 1.1

import "FontAwesome"

Page {
    id: page

    property var classRecord
    property var course
    property int partIndex
    property var courseParts

    title: course.acronym + ((classRecord !== null) ? " - Edição":" - Inclusão") + " de Aula"

    header: ToolBar {
        Material.foreground: "white"

        RowLayout {
            width: parent.width
            ToolButton {
                font { family: FontAwesome.solid }
                visible: stackView.depth > 1
                text: stackView.depth > 2 ? Icons.faChevronLeft : Icons.faBars
                onClicked: {
                    if (stackView.depth > 2) stackView.pop()
                    else drawer.open()
                }
            }
            Label {
                text: stackView.currentItem.title
                font.bold: true
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }
            ToolButton {
                font { family: FontAwesome.solid }
                visible: stackView.depth > 1
                text: Icons.faSave
                onClicked: {
                    var month = monthTumbler.currentIndex+1
                    core.networkController.registerUpdateClass(course.id, courseParts[partCombo.currentIndex].id, hoursSpin.value, dayTumbler.model[dayTumbler.currentIndex]+"/"+"0".repeat(2-month.toString().length)+month+"/"+yearTumbler.model[yearTumbler.currentIndex], descriptionTextArea.text, courseParts[partIndex].id, (classRecord !== null) ? classRecord.id:"")
                    stackView.pop()
                }
            }
        }
    }

    Flickable {
        anchors { fill: parent; margins: 10 }
        contentWidth: parent.width - 2*anchors.margins
        contentHeight: layout.height
        ColumnLayout {
            id: layout
            width: parent.width - 2*parent.anchors.margins
            spacing: 30
            ColumnLayout {
                spacing: 5
                IconLabel { icon: Icons.faCubes; text: "Unidade"; inMenu: false }
                ComboBox {
                    id: partCombo
                    Layout.fillWidth: true
                    model: core.networkController.courseParts
                    textRole: "description"
                    font.pixelSize: 14
                }
            }
            ColumnLayout {
                spacing: 5
                IconLabel { icon: Icons.faBusinessTime; text: "Número de aulas"; inMenu: false }
                SpinBox {
                    id: hoursSpin
                    Layout.fillWidth: true;
                    from: 1; to: 8
                    font.pixelSize: 14
                }
            }
            ColumnLayout {
                spacing: 5
                IconLabel { icon: Icons.faCalendarAlt; text: "Data"; inMenu: false }
                RowLayout {
                    spacing: 10
                    Tumbler { id: dayTumbler }
                    Tumbler {
                        id: monthTumbler
                        Layout.fillWidth: true
                        model: [ "janeiro", "fevereiro", "março", "abril",
                                 "maio", "junho", "julho", "agosto",
                                 "setembro", "outubro", "novembro", "dezembro" ]
                        onCurrentIndexChanged: {
                            var dayIndex = dayTumbler.currentIndex
                            switch(currentIndex) {
                                case 0: case 2: case 4: case 6: case 7: case 9:
                                case 11: dayTumbler.model = [...Array(31).keys()].map(x => ++x)
                                    break;
                                case 3: case 5: case 8:
                                case 10: dayTumbler.model = [...Array(30).keys()].map(x => ++x)
                                    break;
                                case 1: dayTumbler.model = [...Array(((yearTumbler.currentItem.text % 4) == 0) ? 29:28).keys()].map(x => ++x)
                                    break;
                            }
                            if (dayIndex !== -1) {
                                dayTumbler.positionViewAtIndex(Math.min(dayIndex, dayTumbler.model.length-1), Tumbler.Center)
                                dayTumbler.currentIndex = Math.min(dayIndex, dayTumbler.model.length-1)
                            }
                        }
                    }
                    Tumbler {
                        id: yearTumbler
                        model: [...Array(15).keys()].map(x => (new Date().getFullYear())-x).reverse()
                        onCurrentIndexChanged: {
                            if (monthTumbler.currentIndex === 1) {
                                var dayIndex = dayTumbler.currentIndex
                                dayTumbler.model = [...Array(((currentItem.text % 4) == 0) ? 29:28).keys()].map(x => ++x)
                                if (dayIndex !== -1) {
                                    dayTumbler.positionViewAtIndex(Math.min(dayIndex, dayTumbler.model.length-1), Tumbler.Center)
                                    dayTumbler.currentIndex = Math.min(dayIndex, dayTumbler.model.length-1)
                                }
                            }
                        }
                    }
                }
            }
            ColumnLayout {
                visible: classRecord !== null
                spacing: 5
                IconLabel { icon: Icons.faUserTie; text: "Professor"; inMenu: false }
                Label { id: professorLabel; Layout.fillWidth: true }
            }
            ColumnLayout {
                spacing: 5
                IconLabel { icon: Icons.faClipboardCheck; text: "Conteúdo da aula"; inMenu: false }
                ScrollView {
                    Layout.fillWidth: true
                    Layout.minimumHeight: 100
                    TextArea { id: descriptionTextArea; font.pixelSize: 14; wrapMode: TextEdit.WordWrap }
                }
            }
        }
    }

    Component.onCompleted: {
        if (classRecord !== null) {
            partCombo.currentIndex = core.networkController.courseParts.findIndex(o => o.description === classRecord.part)
            hoursSpin.value = classRecord.hours
            var parts = classRecord.date.split('/')
            dayTumbler.currentIndex = parts[0]-1
            monthTumbler.currentIndex = parts[1]-1
            yearTumbler.currentIndex = yearTumbler.model.length-((new Date().getFullYear()) - parts[2])-1
            professorLabel.text = classRecord.professor
            descriptionTextArea.text = classRecord.description
        } else {
            partCombo.currentIndex = partIndex
            dayTumbler.currentIndex = (new Date().getDate())-1
            monthTumbler.currentIndex = (new Date().getMonth())
            yearTumbler.currentIndex = yearTumbler.model.length-1
        }
    }
}
