import QtQuick 2.0

Rectangle {
    signal clicked
    states: [
        State {
            name: "X"
            PropertyChanges {
                target: img
                source: "qrc:/images/x.png"
            }
        },
        State {
            name: "O"
            PropertyChanges {
                target: img
                source: "qrc:/images/o.png"
            }
        },
        State {
            name: "empty"
            PropertyChanges {
                target: img
                source: ""
            }
        }
    ]
    Image {
        id: img
        anchors.fill: parent
    }

    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked()
    }
}
