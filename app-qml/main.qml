import QtQuick 2.1
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import QtQuick.XmlListModel 2.0



ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Stundenplaner")

    header: ToolBar {
        //Material.foreground: "white"

        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                id : backButton
                enabled: stackView.depth > 1
                property string popText
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "images/back.png"                    
                }

                onClicked: {
                    stackView.pop()
                    titleLabel.text=popText
                    console.debug("Stack poped()")
                    //backButton.visible=false
                }
            }

            Label {
                id: titleLabel
                text: stackView.currentItem ? stackView.currentItem.text : "keine Auswahl"
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "images/menu.png"
                }
                onClicked: {
                    console.debug("Tool clicked")
                    optionsMenu.open()
                }

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    MenuItem {
                        text: "Settings"
                        onTriggered: settingsDialog.open()
                    }
                    MenuItem {
                        text: "About"
                        onTriggered: aboutDialog.open()
                    }
                    MenuItem {
                        text: "ModelFile"
                        onTriggered: fileDialog.open()
                    }
                }
            }


        }
    } //header


    WochenplanModel {
        id: wochenplanModel
        source: "file:/home/mopp/appmodel.xml"
        //source: "models/stunden.xml"
    }


    Drawer {
        id: drawer
        width: Math.min(window.width, window.height) / 3 * 2
        height: window.height
        //dragMargin: stackView.depth > 1 ? 0 : undefined

        ListView {
            id: listView

            focus: true
            currentIndex: -1
            anchors.fill: parent

            model: wochenplanModel

            delegate: ItemDelegate {
                width: parent.width
                text: Name + "\n" + Tag
                highlighted: ListView.isCurrentItem



                onClicked: {
                    listView.currentIndex = index
                    //stundenView.vstundenId = ID
                    //schuelerView.vstundenId = ID
                    backButton.visible=true
                    titleLabel.text = Name + "/" + Tag
                    //stackView.push("qrc:/StundenView.qml",{vstundenId: ID})
                    stackView.push("qrc:/SchuelerView.qml",{vstundenId:ID})
                    //stackView.push({ item : StundenView.createObject(), properties:{vstundenId:ID}})
                    drawer.close()
                }
            }



            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }//Drawer






    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: WochenplanView {
            id: stundenView
            parent: null
            //focus: visible
            //anchors.fill: parent
        }



            /*
            GridView {
            id: stackGridView

            focus: visible //true
            currentIndex: -1
            //anchors.fill: parent

            model: wochenplanModel

            delegate: ItemDelegate {
                width: parent.width
                text: Name + "\n" + Tag
                highlighted: ListView.isCurrentItem




                onClicked: {
                    stackGridView.currentIndex = index
                    stundenView.vstundenId = ID
                    backButton.visible=true
                    //stackView.push({ item : StundenView.createObject(), properties:{vstundenId:sid}})
                    stackView.push(stundenView)
                    }
            }



            ScrollIndicator.vertical: ScrollIndicator { }
        } //initialItem
        */



        /*
        SchuelerView {
            id: schuelerView
            parent: null
        }
        */





    }//StackView

    Rectangle {
        id:cameraView
        visible: false
        property string schueler: "Unbekannt"
        Text {
            id: text
            text: qsTr(cameraView.schueler)
            anchors.fill: parent
        }
    }



    CameraView {
        id: cameraViewTrue
        //anchors.fill: parent
        //anchors.centerIn: parent
    }



    Dialog {
        id: settingsDialog
        x: Math.round((window.width - width) / 2)
        y: Math.round(window.height / 6)
        width: Math.round(Math.min(window.width, window.height) / 3 * 2)
        modal: true
        focus: true
        title: "Settings"

        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            settings.style = styleBox.displayText
            settingsDialog.close()
        }
        onRejected: {
            styleBox.currentIndex = styleBox.styleIndex
            settingsDialog.close()
        }

        contentItem: ColumnLayout {
            id: settingsColumn
            spacing: 20

            RowLayout {
                spacing: 10

                Label {
                    text: "Style:"
                }

                ComboBox {
                    id: styleBox
                    property int styleIndex: -1
                    model: ["Default", "Material", "Universal"]
                    Component.onCompleted: {
                        //styleIndex = find(settings.style, Qt.MatchFixedString)
                        //if (styleIndex !== -1)
                        //    currentIndex = styleIndex
                    }
                    Layout.fillWidth: true
                }
            }

            Label {
                text: "Restart required"
                color: "#e41e25"
                opacity: styleBox.currentIndex !== styleBox.styleIndex ? 1.0 : 0.0
                horizontalAlignment: Label.AlignHCenter
                verticalAlignment: Label.AlignVCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    } //Dialog

    Dialog {
        id: aboutDialog
        modal: true
        focus: true
        title: "About"
        x: (window.width - width) / 2
        y: window.height / 6
        width: Math.min(window.width, window.height) / 3 * 2
        contentHeight: aboutColumn.height

        Column {
            id: aboutColumn
            spacing: 20

            Label {
                width: aboutDialog.availableWidth
                text: "The Qt Quick Controls 2 module delivers the next generation user interface controls based on Qt Quick."
                wrapMode: Label.Wrap
                font.pixelSize: 12
            }

            Label {
                width: aboutDialog.availableWidth
                text: "In comparison to the desktop-oriented Qt Quick Controls 1, Qt Quick Controls 2 "
                    + "are an order of magnitude simpler, lighter and faster, and are primarily targeted "
                    + "towards embedded and mobile platforms."
                wrapMode: Label.Wrap
                font.pixelSize: 12
            }
        }
    } //Dialog



    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
         }
        onRejected: {
            console.log("Canceled")
        }
        //Component.onCompleted: visible = true
    } //FileDialog

}
