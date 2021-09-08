#include "MainWindow.hpp"
#include "./ui_MainWindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pb0, &QPushButton::clicked, this, &MainWindow::handleMove);
    connect(ui->pb1, &QPushButton::clicked, this, &MainWindow::handleMove);
    connect(ui->pb2, &QPushButton::clicked, this, &MainWindow::handleMove);
    connect(ui->pb3, &QPushButton::clicked, this, &MainWindow::handleMove);
    connect(ui->pb4, &QPushButton::clicked, this, &MainWindow::handleMove);
    connect(ui->pb5, &QPushButton::clicked, this, &MainWindow::handleMove);
    connect(ui->pb6, &QPushButton::clicked, this, &MainWindow::handleMove);
    connect(ui->pb7, &QPushButton::clicked, this, &MainWindow::handleMove);
    connect(ui->pb8, &QPushButton::clicked, this, &MainWindow::handleMove);

    connect(&m_game, &Game::AIelaborationFinished, this, &MainWindow::updateAfterAImove);
    connect(&m_game, &Game::gameFinished, this, [&](Game::GameFinished mode) {
        auto modeMsg = "";
        switch (mode) {
        case Game::GameFinished::EndOfMoves:
            modeMsg = "No more moves available";
            break;
        case Game::GameFinished::Human:
            modeMsg = "You win, good job";
            break;
        case Game::GameFinished::AI:
            modeMsg = "AI wins :P";
            break;
        }

        QMessageBox::information(this, "Game Finished", modeMsg, QMessageBox::Ok);
    });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::handleMove()
{
    auto* obj = qobject_cast<QPushButton*>(sender());
    if (!obj) {
        qWarning() << "failed obj cast to QPushButton";
        return;
    }

    obj->setText(m_game.currentTurnSymbol());
    auto cell = obj->objectName().right(1).toUInt();
    m_game.setHumanMove(cell);
}

void MainWindow::updateAfterAImove(quint8 cell)
{
    if (cell == 0)
        ui->pb0->setText(m_game.currentTurnSymbol());
    if (cell == 1)
        ui->pb1->setText(m_game.currentTurnSymbol());
    if (cell == 2)
        ui->pb2->setText(m_game.currentTurnSymbol());
    if (cell == 3)
        ui->pb3->setText(m_game.currentTurnSymbol());
    if (cell == 4)
        ui->pb4->setText(m_game.currentTurnSymbol());
    if (cell == 5)
        ui->pb5->setText(m_game.currentTurnSymbol());
    if (cell == 6)
        ui->pb6->setText(m_game.currentTurnSymbol());
    if (cell == 7)
        ui->pb7->setText(m_game.currentTurnSymbol());
    if (cell == 8)
        ui->pb8->setText(m_game.currentTurnSymbol());
}
