#pragma once

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

private:
    Ui::MainWindow* ui;

    enum class Turn {
        Human,
        AI
    };

    Turn m_turn { Turn::Human }; // TODO: make this random

    void flipTurn();
    QString currentTurnSymbol() const noexcept;
};
