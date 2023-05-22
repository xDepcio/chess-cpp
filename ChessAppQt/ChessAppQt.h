#pragma once
#include <QtWidgets/QMainWindow>
#include <iostream>
#include "ui_ChessAppQt.h"
//#include "QtGame.h"
//#include "ClickableLabel.h"

class QtGame;
class Piece;
class SkinsManager;

class ChessAppQt : public QMainWindow
{
    Q_OBJECT

public:
    ChessAppQt(QWidget *parent = nullptr);
    ~ChessAppQt();

    void connectMenuBtns();

    void updateBoard();
    void updateSquares(std::vector<std::pair<int, int>>& coordsToUpdate);
    void connectSquares();
    void displayMoves(std::vector<std::pair<int, int>> const& moves);
    void clearDisplayMoves(std::vector<std::pair<int, int>> const& moves);

    void connectTrackerBtns();

    void setupSkinsManagement();

    void setupPromotionBtns();

    void startNewChessGame();

    void startNewChessGameFromSave(std::string const& savePath);

    void handleChessGameStateChange();

    void handleBoardFieldClick(std::pair<int, int> const& fieldCoords);

    void handleRestartBtn();
    void connectRestartBtn();
    void connectBackBtn();
    void connectSaveBtn();
    void loadSavedGames();
    void connectSavesBackBtn();

private:
    std::vector<std::pair<int, int>> displayedSquares;
    Ui::ChessAppQtClass ui;
    QtGame* playedGame;
    std::unique_ptr<SkinsManager> skinsManager;
};
