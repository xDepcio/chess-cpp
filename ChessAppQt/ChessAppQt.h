#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChessAppQt.h"
#include "QtGame.h"

class ChessAppQt : public QMainWindow
{
    Q_OBJECT

public:
    ChessAppQt(QWidget *parent = nullptr);
    ~ChessAppQt();

    void startGame();
    void updateBoard();

private:
    Ui::ChessAppQtClass ui;
    QtGame* playedGame;
};
