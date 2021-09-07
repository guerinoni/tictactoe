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

    obj->setText(m_game.currentTurnSymbol());
    auto cell = obj->objectName().right(1).toUInt();
    m_game.setHumanMove(cell);
}
