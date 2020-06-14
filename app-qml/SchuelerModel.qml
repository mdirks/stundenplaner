import QtQuick 2.0
import QtQuick.XmlListModel 2.0


XmlListModel {
    property int stundenId : 0
    //id: stundenModel
    source: "qrc:models/appmodel.xml"
    //source: "models/stunden.xml"

    query: "/import/stundenplaneintrag[@ID=" +stundenId + "]/property/klasse/property/schueler"

    XmlRole { name: "Vorname"; query: "@Vorname/string()" }
    XmlRole { name: "Nachname"; query: "@Nachname/string()" }

}


