import QtQuick 2.0
import QtQuick.XmlListModel 2.0


XmlListModel {
    query: "/import/stundenplaneintrag"

    XmlRole { name: "Name"; query: "@Name/string()" }
    XmlRole { name: "Tag"; query: "@Tag/string()" }
    XmlRole { name: "Nr"; query: "@NrStunde/string()" }
    XmlRole { name: "ID"; query: "@ID/string()" }
}

