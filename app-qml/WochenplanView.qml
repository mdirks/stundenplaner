import QtQuick 2.1
import QtQuick.Controls 2.1
//import QtQuick.Layouts 1.3

ListView {
    id: wochenplanView

    focus: true
    currentIndex: -1
    anchors.fill: parent

    model: wochenplanModel

    WochenplanModel {
        id: wochenplanModel
        source: "models/appmodel.xml"
        //source: "models/stunden.xml"
    }


    delegate: ItemDelegate {
        width: parent.width
        text: Name + "\n" + Tag
        highlighted: ListView.isCurrentItem



        onClicked: {
            currentIndex = index
            //stundenView.vstundenId = ID
            //schuelerView.vstundenId = ID
            backButton.visible=true
            titleLabel.text = Name + "/" + Tag
            stackView.push("qrc:/SchuelerView.qml",{vstundenId:ID})
            //stackView.push({ item : StundenView.createObject(), properties:{vstundenId:sid}})
            drawer.close()
        }
    }




}
