#include "ChessAppQt.h"

ChessAppQt::ChessAppQt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connectMenuBtns();
    {
        startGame();
        connectTrackerBtns();
    }
}

ChessAppQt::~ChessAppQt()
{}

void ChessAppQt::connectMenuBtns()
{
    connect(ui.menuPlayBtn, &QPushButton::clicked, this, [this]() {
        ui.stackedWidget->setCurrentIndex(0);
    });
}

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

    std::vector<std::vector<Square>>& squares = playedGame->getSquares();

    int qtSquareNum = 0;
    for (auto& row : squares)
    {
        for (auto& sqr : row)
        {
            std::string pathToPiece = getPathToPiece(sqr.getPiece());
            QString qImagePath = QString::fromStdString(pathToPiece);
            QPixmap pixmap(qImagePath);
            pixmap = pixmap.scaled(qtSquares[qtSquareNum]->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            qtSquares[qtSquareNum]->setPixmap(pixmap);
            qtSquares[qtSquareNum]->setAlignment(Qt::AlignCenter);
            qtSquareNum++;
        }
    }
}

void ChessAppQt::updateSquares(std::vector<std::pair<int, int>>& coordsToUpdate)
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
    std::vector<std::vector<Square>>& squares = playedGame->getSquares();

    for (auto& coord : coordsToUpdate)
    {
        Piece* piece = squares[coord.first][coord.second].getPiece();
        ClickableLabel* label = qtSquares[coord.first][coord.second];

        std::string pathToPiece = getPathToPiece(piece);
        QString qImagePath = QString::fromStdString(pathToPiece);
        QPixmap pixmap(qImagePath);
        pixmap = pixmap.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        label->setPixmap(pixmap);
        label->setAlignment(Qt::AlignCenter);

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
        colNum = 0;
        for (auto& sqr : row)
        {
            connect(sqr, &ClickableLabel::clicked, this, [this, sqr, rowNum, colNum]() {
                handleBoardFieldClick({ rowNum, colNum });
            });

            colNum++;
        }
        rowNum++;
    }

}

void ChessAppQt::displayMoves(std::vector<std::pair<int, int>> const& moves)
{
    std::vector<std::vector<QWidget*>> qtSquares = {
        { ui.row0col0, ui.row0col1, ui.row0col2, ui.row0col3, ui.row0col4, ui.row0col5, ui.row0col6, ui.row0col7 },
        { ui.row1col0, ui.row1col1, ui.row1col2, ui.row1col3, ui.row1col4, ui.row1col5, ui.row1col6, ui.row1col7 },
        { ui.row2col0, ui.row2col1, ui.row2col2, ui.row2col3, ui.row2col4, ui.row2col5, ui.row2col6, ui.row2col7 },
        { ui.row3col0, ui.row3col1, ui.row3col2, ui.row3col3, ui.row3col4, ui.row3col5, ui.row3col6, ui.row3col7 },
        { ui.row4col0, ui.row4col1, ui.row4col2, ui.row4col3, ui.row4col4, ui.row4col5, ui.row4col6, ui.row4col7 },
        { ui.row5col0, ui.row5col1, ui.row5col2, ui.row5col3, ui.row5col4, ui.row5col5, ui.row5col6, ui.row5col7 },
        { ui.row6col0, ui.row6col1, ui.row6col2, ui.row6col3, ui.row6col4, ui.row6col5, ui.row6col6, ui.row6col7 },
        { ui.row7col0, ui.row7col1, ui.row7col2, ui.row7col3, ui.row7col4, ui.row7col5, ui.row7col6, ui.row7col7 },
    };

    displayedSquares = moves;

    for (auto& move : moves)
    {
        qtSquares[move.first][move.second]->setStyleSheet("background-color: rgb(0, 0, 0);");
    }
}

void ChessAppQt::clearDisplayMoves(std::vector<std::pair<int, int>> const& moves)
{
    std::vector<std::vector<QWidget*>> qtSquares = {
        { ui.row0col0, ui.row0col1, ui.row0col2, ui.row0col3, ui.row0col4, ui.row0col5, ui.row0col6, ui.row0col7 },
        { ui.row1col0, ui.row1col1, ui.row1col2, ui.row1col3, ui.row1col4, ui.row1col5, ui.row1col6, ui.row1col7 },
        { ui.row2col0, ui.row2col1, ui.row2col2, ui.row2col3, ui.row2col4, ui.row2col5, ui.row2col6, ui.row2col7 },
        { ui.row3col0, ui.row3col1, ui.row3col2, ui.row3col3, ui.row3col4, ui.row3col5, ui.row3col6, ui.row3col7 },
        { ui.row4col0, ui.row4col1, ui.row4col2, ui.row4col3, ui.row4col4, ui.row4col5, ui.row4col6, ui.row4col7 },
        { ui.row5col0, ui.row5col1, ui.row5col2, ui.row5col3, ui.row5col4, ui.row5col5, ui.row5col6, ui.row5col7 },
        { ui.row6col0, ui.row6col1, ui.row6col2, ui.row6col3, ui.row6col4, ui.row6col5, ui.row6col6, ui.row6col7 },
        { ui.row7col0, ui.row7col1, ui.row7col2, ui.row7col3, ui.row7col4, ui.row7col5, ui.row7col6, ui.row7col7 },
    };

    for (auto& move : moves)
    {
        qtSquares[move.first][move.second]->setStyleSheet((move.first + move.second) % 2 == 0 ? "background-color: rgb(226, 232, 217);" : "background-color: rgb(32, 58, 3);");
    }

    displayedSquares = {};
}

void ChessAppQt::connectTrackerBtns()
{
    connect(ui.nextMoveBtn, &QPushButton::clicked, this, [this]() {
        playedGame->getBoard()->getMovesTracker()->next();
        auto move = playedGame->getBoard()->getMovesTracker()->getPointedMove();
        //std::vector<std::pair<int, int>> movesToUpdate = { move.from, move.to };
        updateSquares(move.affectedSquares);
        if (playedGame->getBoard()->getMovesTracker()->onLatestMove())
        {
            ui.nextMoveBtn->setDisabled(true);
            return;
        }
        ui.prevMoveBtn->setDisabled(false);
    });

    connect(ui.prevMoveBtn, &QPushButton::clicked, this, [this]() {
        auto move = playedGame->getBoard()->getMovesTracker()->getPointedMove();
        //std::vector<std::pair<int, int>> movesToUpdate = { move.from, move.to };
        playedGame->getBoard()->getMovesTracker()->previous();
        updateSquares(move.affectedSquares);
        if (playedGame->getBoard()->getMovesTracker()->getPointedMoveIndex() == -1)
        {
            ui.prevMoveBtn->setDisabled(true);
            return;
        }
        ui.nextMoveBtn->setDisabled(false);
    });
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
    Piece* clickedPiece = playedGame->getPieceAtCoords(fieldCoords);
    Piece* prevClicked = playedGame->getClickedPiece();
    auto prevCoords = playedGame->getClickedPieceCoords();
    auto turn = playedGame->getBoard()->getTurn();

    //bool prevCurrSame = clickedPiece->getColor() == prevClicked->getColor();
    //bool prevCurrNull = clickedPiece == nullptr && prevClicked == nullptr;
    //bool prevNullCurrOwn = prevClicked == nullptr && clickedPiece->getColor() == turn;
    //bool prevNullCurrEnemy = prevClicked == nullptr && clickedPiece->getColor() != turn;
    //bool prevCurrOwn = clickedPiece->getColor() == turn && prevClicked->getColor() == turn;

    clearDisplayMoves(displayedSquares);
    if (
        (prevClicked == nullptr && clickedPiece == nullptr) ||
        (prevClicked == nullptr && clickedPiece->getColor() != turn) ||
        (prevClicked != nullptr && prevClicked->getColor() != turn && clickedPiece == nullptr) ||
        (prevClicked != nullptr && prevClicked->getColor() != turn && clickedPiece->getColor() != turn)
        ) // prev and now clicked on empty
    {
        playedGame->setClickedPiece(clickedPiece);
        playedGame->setClickedPieceCoords(fieldCoords);
    }
    else if (
        (prevClicked != nullptr && prevClicked->getColor() == turn && clickedPiece == nullptr) ||
        (prevClicked != nullptr && prevClicked->getColor() == turn && clickedPiece->getColor() != turn))
    {
        // valid move and move
        if (playedGame->isMoveValid(prevCoords, fieldCoords))
        {
            //playedGame->move(prevCoords, fieldCoords);
            prevClicked->move(playedGame->getBoard(), fieldCoords);
            playedGame->getBoard()->setTurn(turn == Piece::Color::White ? Piece::Color::Black : Piece::Color::White);
            //std::vector<std::pair<int, int>> toUpdate = { prevCoords, fieldCoords };
            auto affectedSqrs = playedGame->getBoard()->getMovesTracker()->getPointedMove().affectedSquares;
            updateSquares(affectedSqrs);
        }
        playedGame->setClickedPiece(nullptr);
        playedGame->setClickedPieceCoords({});
    }
    else if (clickedPiece->getColor() == turn) // clicked on own
    {
        // display valid moves
        auto validMoves = playedGame->getPieceAtCoords(fieldCoords)->getValidMoves(playedGame->getBoard(), fieldCoords);
        displayMoves(validMoves);
        playedGame->setClickedPiece(clickedPiece);
        playedGame->setClickedPieceCoords(fieldCoords);
    }
    else
    {
        throw std::runtime_error(":(");
    }
}

