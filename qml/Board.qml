import QtQuick 2.12
import QtQuick.Controls 2.12

import Game.enums 1.0

Item {
    property string popUpMessage

    function reset() {
        for (var i = 0; i < cells.count; i++) {
            cells.itemAt(i).state = "empty"
        }

        game.emptyBoard()
        gameFinishedPopup.close()
    }

    Connections {
        target: game
        function onAiElaborationFinished(cell) {
            cells.itemAt(cell).state = "O"
        }
        function onGameFinished(mode) {
            switch (mode) {
            case GameFinishedEnum.Human:
                popUpMessage = "You win, good job"
                break
            case GameFinishedEnum.AI:
                popUpMessage = "AI wins :P"
                break
            default:
                popUpMessage = "No more moves available"
            }
            gameFinishedPopup.open()
        }
    }

    Grid {
        id: board

        anchors.fill: parent
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
                    if (game.isMoveAllowed(index)) {
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
        closePolicy: Popup.CloseOnPressOutside
        contentItem: Text {
            id: gameFinishedText
            text: popUpMessage
        }
    }
}
