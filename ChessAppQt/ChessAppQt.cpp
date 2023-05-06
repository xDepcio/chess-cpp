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
    connectSquares();

    playedGame = new QtGame();
    playedGame->run();
    updateBoard();
}

void ChessAppQt::updateBoard()
{
    std::vector<QLabel*> qtSquares = {
        ui.row0col0label, ui.row0col1label, ui.row0col2label, ui.row0col3label, ui.row0col4label, ui.row0col5label, ui.row0col6label, ui.row0col7label,
        ui.row1col0label, ui.row1col1label, ui.row1col2label, ui.row1col3label, ui.row1col4label, ui.row1col5label, ui.row1col6label, ui.row1col7label,
        ui.row2col0label, ui.row2col1label, ui.row2col2label, ui.row2col3label, ui.row2col4label, ui.row2col5label, ui.row2col6label, ui.row2col7label,
        ui.row3col0label, ui.row3col1label, ui.row3col2label, ui.row3col3label, ui.row3col4label, ui.row3col5label, ui.row3col6label, ui.row3col7label,
        ui.row4col0label, ui.row4col1label, ui.row4col2label, ui.row4col3label, ui.row4col4label, ui.row4col5label, ui.row4col6label, ui.row4col7label,
        ui.row5col0label, ui.row5col1label, ui.row5col2label, ui.row5col3label, ui.row5col4label, ui.row5col5label, ui.row5col6label, ui.row5col7label,
        ui.row6col0label, ui.row6col1label, ui.row6col2label, ui.row6col3label, ui.row6col4label, ui.row6col5label, ui.row6col6label, ui.row6col7label,
        ui.row7col0label, ui.row7col1label, ui.row7col2label, ui.row7col3label, ui.row7col4label, ui.row7col5label, ui.row7col6label, ui.row7col7label,
    };

    std::vector<std::vector<Square>>& squares = playedGame->getBoard();

    int qtSquareNum = 0;
    for (auto& row : squares)
    {
        for (auto& sqr : row)
        {
            std::string pathToPiece = getPathToPiece(sqr.getPiece());
            QString qImagePath = QString::fromStdString(pathToPiece);
            QPixmap pixmap(qImagePath);
            pixmap = pixmap.scaled(qtSquares[qtSquareNum]->size()*2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            qtSquares[qtSquareNum]->setPixmap(pixmap);
            qtSquares[qtSquareNum]->setAlignment(Qt::AlignCenter);
            qtSquareNum++;
        }
    }
}

void ChessAppQt::connectSquares()
{
    std::vector<std::vector<ClickableLabel*>> qtSquares = {
        { ui.row0col0label, ui.row0col1label, ui.row0col2label, ui.row0col3label, ui.row0col4label, ui.row0col5label, ui.row0col6label, ui.row0col7label },
        { ui.row1col0label, ui.row1col1label, ui.row1col2label, ui.row1col3label, ui.row1col4label, ui.row1col5label, ui.row1col6label, ui.row1col7label },
        { ui.row2col0label, ui.row2col1label, ui.row2col2label, ui.row2col3label, ui.row2col4label, ui.row2col5label, ui.row2col6label, ui.row2col7label },
        { ui.row3col0label, ui.row3col1label, ui.row3col2label, ui.row3col3label, ui.row3col4label, ui.row3col5label, ui.row3col6label, ui.row3col7label },
        { ui.row4col0label, ui.row4col1label, ui.row4col2label, ui.row4col3label, ui.row4col4label, ui.row4col5label, ui.row4col6label, ui.row4col7label },
        { ui.row5col0label, ui.row5col1label, ui.row5col2label, ui.row5col3label, ui.row5col4label, ui.row5col5label, ui.row5col6label, ui.row5col7label },
        { ui.row6col0label, ui.row6col1label, ui.row6col2label, ui.row6col3label, ui.row6col4label, ui.row6col5label, ui.row6col6label, ui.row6col7label },
        { ui.row7col0label, ui.row7col1label, ui.row7col2label, ui.row7col3label, ui.row7col4label, ui.row7col5label, ui.row7col6label, ui.row7col7label },
    };

    int rowNum = 0;
    int colNum = 0;
    for (auto& row : qtSquares)
    {
        for (auto& sqr : row)
        {
            //connect(sqr, &ClickableLabel::clicked, this, &ChessAppQt::handleBoardFieldClick);
            sqr->setProperty("row", rowNum);
            sqr->setProperty("col", colNum);

            connect(sqr, &ClickableLabel::clicked, this, [this, sqr]() {
                int rowNumPassed = sqr->property("row").toInt();
                int colNumPassed = sqr->property("col").toInt();

                handleBoardFieldClick({ rowNumPassed, colNumPassed });
            });

            colNum++;
        }
        rowNum++;
    }

}

std::string ChessAppQt::getPathToPiece(Piece* piece) const
{
    if (piece == nullptr)
        return "";
    
    // TODO... Change to universal path
    std::string base = "C:/Users/Olek/Desktop/pieces/";
    

    if (dynamic_cast<Pawn*>(piece))
        base += "pawn";
    if (dynamic_cast<Knight*>(piece))
        base += "knight";
    if (dynamic_cast<Bishop*>(piece))
        base += "bishop";
    if (dynamic_cast<Queen*>(piece))
        base += "queen";
    if (dynamic_cast<King*>(piece))
        base += "king";
    if (dynamic_cast<Rook*>(piece))
        base += "rook";

    base += piece->getColor() == Piece::Color::White ? "-white.png" : "-black.png";

    return base;
}

void ChessAppQt::handleBoardFieldClick(std::pair<int, int> const& fieldCoords)
{
    throw std::runtime_error("xd");
}

