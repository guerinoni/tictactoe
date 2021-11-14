import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    color: "black"
    width: 640
    height: 480
    title: qsTr("Tic Tac Toe")

    menuBar: MenuBar {
        Menu {
            title: qsTr("Options")

            Action {
                text: qsTr("New Match")
                onTriggered: board.reset()
            }

            Action {
                text: qsTr("Settings")
                onTriggered: console.log("settings clicked")
            }

            MenuSeparator {}

            Action {
                text: qsTr("Quit")
                shortcut: Shortcut {
                    sequence: StandardKey.Quit
                }

                onTriggered: Qt.quit()
            }
        }
    }

    Board {
        id: board

        anchors.fill: parent
    }
}
