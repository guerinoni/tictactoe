#include "MainWindow.hpp"
#include "./ui_MainWindow.h"

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
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::handleMove()
{
    auto* obj = qobject_cast<QPushButton*>(sender());
    if (!obj) {
        qWarning() << "failed obj cast to QPushButton";
        return;
    }

    obj->setText(currentTurnSymbol());
    flipTurn();
}

void MainWindow::flipTurn()
{
    if (m_turn == Turn::Human)
        m_turn = Turn::AI;
    else if (m_turn == Turn::AI)
        m_turn = Turn::Human;
    else
        assert(false);
}

QString MainWindow::currentTurnSymbol() const noexcept
{
    if (m_turn == Turn::Human)
        return "X";
    if (m_turn == Turn::AI)
        return "O";

    assert(false);
    return "";
}
