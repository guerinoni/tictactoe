#pragma once

#include "Game.hpp"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void handleMove();
    void updateAfterAImove(quint8 cell);

private:
    Ui::MainWindow* ui;

    QAction* m_quit;

    Game m_game;
};
