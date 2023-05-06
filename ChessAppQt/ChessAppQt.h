#pragma once

#include <QtWidgets/QMainWindow>
#include <iostream>
#include "ui_ChessAppQt.h"
#include "QtGame.h"
#include "ClickableLabel.h"

class ChessAppQt : public QMainWindow
{
    Q_OBJECT

public:
    ChessAppQt(QWidget *parent = nullptr);
    ~ChessAppQt();

    void startGame();
    void updateBoard();
    void updateSquares(std::vector<std::pair<int, int>>& coordsToUpdate);
    void connectSquares();

    std::string getPathToPiece(Piece* piece) const;

    void handleBoardFieldClick(std::pair<int, int> const& fieldCoords);

private:
    Ui::ChessAppQtClass ui;
    QtGame* playedGame;
};
