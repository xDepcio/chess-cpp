#include "ChessAppQt.h"

ChessAppQt::ChessAppQt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    startGame();
}

ChessAppQt::~ChessAppQt()
{}

void ChessAppQt::startGame()
{
    playedGame = new QtGame();
    playedGame->run();
    updateBoard();
}

void ChessAppQt::updateBoard()
{
    QPixmap pixmap("D:/Biblioteki/Pobrane/pawn.png");
    pixmap = pixmap.scaled(ui.labelTest->size()*2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui.labelTest->setPixmap(pixmap);
    ui.labelTest->setAlignment(Qt::AlignCenter);
    //ui.labelTest->setFixedSize(pixmap.width(), pixmap.height());
    //ui.labelTest->setText("xddd");
}
