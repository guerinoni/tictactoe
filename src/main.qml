import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import Game.enums 1.0

Window {
    visible: true
    color: "black"
    width: 640
    height: 480
    title: qsTr("Tic Tac Toe")

    Connections {
        target: game
        onAiElaborationFinished: {
            cells.itemAt(cell).state = "O"
        }
        onGameFinished: {
            switch(mode)
            {
            case GameFinishedEnum.Human:
                gameFinishedText.text = "You win, good job"
                break;
            case GameFinishedEnum.AI:
                gameFinishedText.text = "AI wins :P"
                break;
            default:
                gameFinishedText.text = "No more moves available"
            }
            gameFinishedPopup.open()
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
                    if(game.isMoveAllowed(index))
                    {
                        state = "X"
                        game.setHumanMove(index)
                    }
                }
            }

        }
    }

    Popup {
        id: gameFinishedPopup
        anchors.centerIn: parent
        width: parent.width / 3
        height: 40
        modal: true
        focus: true
        closePolicy: Popup.CloseOnPressOutsideParent
        contentItem: Text { id: gameFinishedText }
    }
}
