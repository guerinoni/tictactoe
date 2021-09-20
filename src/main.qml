import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    color: "black"
    width: 640
    height: 480
    title: qsTr("Tic Tac Toe")

    property bool human_turn: true

    Connections {
        target: game
        onAiElaborationFinished: {
            human_turn = true
            cells.itemAt(cell).state = "O"
        }
    }

    Grid {
        id: board
        width: parent.width
        height: parent.height

        columns: 3
        spacing: 5

        Repeater {
            id: cells
            model: 9

            Cell {
                state: "empty"
                width: board.width / 3
                height: board.height / 3
                onClicked: {
                    if(human_turn && state == "empty")
                    {
                        state = "X"
                        human_turn = false
                        game.setHumanMove(index)
                    }
                }
            }

        }
    }
}
