#include "ChessAppQt.h"
#include "QtGame.h"
#include "ChessBotQt.h"
#include <qresource.h>
#include "../ChessLib/Square.h"
#include "../ChessLib/Board.h"
#include "../ChessLib/MovesTracker.h"
#include "../ChessLib/Pawn.h"
#include "../ChessLib/Knight.h"
#include "../ChessLib/Bishop.h"
#include "../ChessLib/Rook.h"
#include "../ChessLib/King.h"
#include "../ChessLib/Queen.h"
#include "SkinsManager.h"
#include "../ChessLib/Constants.h"
#include <filesystem>
#include "../ChessLib/Constants.h"


ChessAppQt::ChessAppQt(QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    setupSkinsManagement();
    connectMenuBtns();
    connectSquares();
    connectTrackerBtns();

    setupDiffWidget();

    connectRestartBtn();
    setupPromotionBtns();
    connectBackBtn();
    connectSaveBtn();
    //loadSavedGames();
    connectSavesBackBtn();
}

ChessAppQt::~ChessAppQt()
{}

void ChessAppQt::connectMenuBtns()
{
    connect(ui.menuPlayBtn, &QPushButton::clicked, this, [this]() {
        startNewChessGame();
        ui.stackedWidget->setCurrentIndex(0);
        });

    connect(ui.menuPlayBotBtn, &QPushButton::clicked, this, [this]() {
        startNewChessGameWithBot();
        ui.stackedWidget->setCurrentIndex(0);
        });

    connect(ui.menuSkinsBtn, &QPushButton::clicked, this, [this]() {
        ui.stackedWidget->setCurrentIndex(1);
        });

    connect(ui.menuHistoryBtn, &QPushButton::clicked, this, [this]() {
        ui.stackedWidget->setCurrentIndex(3);
        loadSavedGames();
        });
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
            std::string pathToPiece = skinsManager.get()->getPathToPiece(sqr.getPiece());
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

        std::string pathToPiece = skinsManager.get()->getPathToPiece(piece);

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
        qtSquares[move.first][move.second]->setStyleSheet((move.first + move.second) % 2 == 0 ? "background-color: rgb(181, 237, 144);" : "background-color: rgb(154, 211, 97);");
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
        qtSquares[move.first][move.second]->setStyleSheet((move.first + move.second) % 2 == 0 ? "background-color: rgb(238, 238, 210);" : "background-color: rgb(118, 150, 86);");
    }

    displayedSquares = {};
}

void ChessAppQt::connectTrackerBtns()
{
    connect(ui.nextMoveBtn, &QPushButton::clicked, this, [this]() {
        playedGame->getBoard()->getMovesTracker()->next();
        auto move = playedGame->getBoard()->getMovesTracker()->getPointedMove();
        updateSquares(move->affectedSquares);
        if (playedGame->getBoard()->getMovesTracker()->onLatestMove())
        {
            ui.nextMoveBtn->setDisabled(true);
        }
        else
        {
            ui.nextMoveBtn->setDisabled(false);
        }
        ui.prevMoveBtn->setDisabled(false);
        });

    connect(ui.prevMoveBtn, &QPushButton::clicked, this, [this]() {
        
        auto move = playedGame->getBoard()->getMovesTracker()->getPointedMove();
        playedGame->getBoard()->getMovesTracker()->previous();
        updateSquares(move->affectedSquares);
        if (playedGame->getBoard()->getMovesTracker()->getPointedMoveIndex() <= -1)
        {
            ui.prevMoveBtn->setDisabled(true);
        }
        else
        {
            ui.prevMoveBtn->setDisabled(false);
        }
        ui.nextMoveBtn->setDisabled(false);
        });

    connect(ui.startFromNowBtn, &QPushButton::clicked, this, [this]() {
        ui.gameEndLabel->setText("");
        playedGame->getBoard()->getMovesTracker()->startFromCurrent();
        ui.nextMoveBtn->setDisabled(true);
    });
}

void ChessAppQt::setupDiffWidget()
{
    //ui.diffWidget->hide();

    connect(ui.diffSlider, &QSlider::sliderMoved, this, [this]() {

        std::stringstream ss;
        ss << "Poziom trudności: ";
        ss << ui.diffSlider->value();
        ui.label_3->setText(ss.str().c_str());
        playedGame->setGameDiff(ui.diffSlider->value());
        });

    connect(ui.diffSlider, &QSlider::valueChanged, this, [this]() {

        std::stringstream ss;
        ss << "Poziom trudności: ";
        ss << ui.diffSlider->value();
        ui.label_3->setText(ss.str().c_str());
        playedGame->setGameDiff(ui.diffSlider->value());
        });
    
}

void ChessAppQt::setupSkinsManagement()
{
    skinsManager = std::move(std::make_unique<SkinsManager>());
    skinsManager.get()->setSelectedPackage(SkinsManager::SkinsPackage::STANDARD);

    connect(ui.skinsBackBtn, &QPushButton::clicked, this, [this]() {
        ui.stackedWidget->setCurrentIndex(2);
        });

    connect(ui.radioBtnStandard, &QRadioButton::clicked, this, [this]() {
        skinsManager.get()->setSelectedPackage(SkinsManager::SkinsPackage::STANDARD);
        });

    connect(ui.radioBtnStarWars, &QRadioButton::clicked, this, [this]() {
        skinsManager.get()->setSelectedPackage(SkinsManager::SkinsPackage::STARWARS);
        });
}

void ChessAppQt::setupPromotionBtns()
{
    ui.promotionWidget->hide();

    connect(ui.promotionQueenBtn, &QPushButton::clicked, this, [this]() {
        playedGame->choosePromotion(Promotions::QUEEN);
        updateSquares(playedGame->getBoard()->getMovesTracker()->getPointedMove()->affectedSquares);
        ui.promotionWidget->hide();
        });
    connect(ui.promotionKnightBtn, &QPushButton::clicked, this, [this]() {
        playedGame->choosePromotion(Promotions::KNGIHT);
        updateSquares(playedGame->getBoard()->getMovesTracker()->getPointedMove()->affectedSquares);
        ui.promotionWidget->hide();
        });
    connect(ui.promotionRookBtn, &QPushButton::clicked, this, [this]() {
        playedGame->choosePromotion(Promotions::ROOK);
        updateSquares(playedGame->getBoard()->getMovesTracker()->getPointedMove()->affectedSquares);
        ui.promotionWidget->hide();
        });
    connect(ui.promotionBishopBtn, &QPushButton::clicked, this, [this]() {
        playedGame->choosePromotion(Promotions::BISHOP);
        updateSquares(playedGame->getBoard()->getMovesTracker()->getPointedMove()->affectedSquares);
        ui.promotionWidget->hide();
        });
}

void ChessAppQt::startNewChessGame()
{
    ui.nextMoveBtn->setDisabled(true);
    ui.prevMoveBtn->setDisabled(true);
    ui.promotionWidget->hide();
    ui.diffWidget->hide();
    ui.gameEndLabel->setText("");

    playedGame = new QtGame();
    playedGame->run();
    updateBoard();
}

void ChessAppQt::startNewChessGameWithBot()
{
    ui.nextMoveBtn->setDisabled(true);
    ui.prevMoveBtn->setDisabled(true);
    ui.promotionWidget->hide();
    ui.diffWidget->show();
    ui.gameEndLabel->setText("");

    playedGame = new QtGame();
    stockfish = new ChessBot();


    playedGame->setUpBotGame(Color::Black);

    playedGame->run();
    updateBoard();
}



void ChessAppQt::startNewChessGameFromSave(std::string const& savePath)
{
    ui.stackedWidget->setCurrentIndex(0);

    ui.nextMoveBtn->setDisabled(true);
    ui.prevMoveBtn->setDisabled(true);
    ui.promotionWidget->hide();
    ui.gameEndLabel->setText("");

    playedGame = new QtGame();
    playedGame->run();
    playedGame->loadGameFromFile(savePath);
    updateBoard();
    if (playedGame->getBoard()->getMovesTracker()->getMoveCount() > 0)
    {
        ui.prevMoveBtn->setDisabled(false);
    }
}

void ChessAppQt::handleChessGameStateChange()
{
    switch (playedGame->getBoardState())
    {
    case BoardState::CHECKMATED_BLACK:
        ui.gameEndLabel->setText("♔ Białe wygrywają!");
        break;
    case BoardState::CHECKMATED_WHITE:
        ui.gameEndLabel->setText("♚ Czarne wygrywają!");
        break;
    case BoardState::STALEMATE:
        ui.gameEndLabel->setText("♚ Remis! ♔");
        break;
    case BoardState::PLAYED:
        ui.prevMoveBtn->setDisabled(false);
        break;
    case BoardState::REQUEST_PROMOTION:
        ui.promotionWidget->show();
        break;
    default:
        break;
    }
}


void ChessAppQt::handleBoardFieldClick(std::pair<int, int> const& fieldCoords)
{
    Piece* clickedPiece = playedGame->getPieceAtCoords(fieldCoords);
    Piece* prevClicked = playedGame->getClickedPiece();
    auto prevCoords = playedGame->getClickedPieceCoords();
    auto turn = playedGame->getBoard()->getTurn();
    if (not playedGame->isBotGame())
    {

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
                //prevClicked->move(playedGame->getBoard(), fieldCoords);
                playedGame->move(prevClicked, fieldCoords);
                playedGame->getBoard()->setTurn(turn == Color::White ? Color::Black : Color::White);
                auto affectedSqrs = playedGame->getBoard()->getMovesTracker()->getPointedMove()->affectedSquares;
                updateSquares(affectedSqrs);
                handleChessGameStateChange();
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
    else
    {
        auto bot_color = playedGame->getBotColor();
        if (playedGame->getBoard()->getTurn() != bot_color)
        {
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
                    //prevClicked->move(playedGame->getBoard(), fieldCoords);
                    playedGame->move(prevClicked, fieldCoords);
                    playedGame->getBoard()->setTurn(turn == Color::White ? Color::Black : Color::White);
                    auto affectedSqrs = playedGame->getBoard()->getMovesTracker()->getPointedMove()->affectedSquares;
                    updateSquares(affectedSqrs);
                    handleChessGameStateChange();
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
        else
        {

            clearDisplayMoves(displayedSquares);

            std::string fenPos = playedGame->getBoard()->getFenBoard();

            stockfish->setDifficulty(playedGame->getGameDiff());

            std::string bestFishMove = stockfish->getBestMove(fenPos);

            auto coords = playedGame->parseCoords(bestFishMove);

            playedGame->move(playedGame->getPieceAtCoords(coords.first), coords.second);
            playedGame->getBoard()->setTurn(turn == Color::White ? Color::Black : Color::White);

            auto affectedSqrs = playedGame->getBoard()->getMovesTracker()->getPointedMove()->affectedSquares;
            updateSquares(affectedSqrs);
            handleChessGameStateChange();

        }
    }
}

void ChessAppQt::handleRestartBtn()
{
    bool bot = playedGame->isBotGame();
    delete playedGame;
    if (not bot)
        startNewChessGame();
    else
        startNewChessGameWithBot();
}

void ChessAppQt::connectRestartBtn()
{
    connect(ui.restartBtn, &QPushButton::clicked, this, &ChessAppQt::handleRestartBtn);
}

void ChessAppQt::connectBackBtn()
{
    connect(ui.backBtn, &QPushButton::clicked, this, [this]() {
        ui.stackedWidget->setCurrentIndex(2);
        });
}

void ChessAppQt::connectSaveBtn()
{
    connect(ui.saveBtn, &QPushButton::clicked, this, [this]() {
        playedGame->saveCurrentGameToFile(constants::SAVE_FILES_DIR);
        });
}

void ChessAppQt::loadSavedGames()
{
    foreach(QObject * child, ui.savesHolderWidget->children()) {
        // Check if the child widget is of type QWidget
        if (QWidget* childWidget = qobject_cast<QWidget*>(child)) {
            // Delete the child widget
            delete childWidget;
        }
    }

    for (const auto& entry : std::filesystem::directory_iterator(constants::SAVE_FILES_DIR)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            QWidget* saveHolder = new QWidget();
            ui.savesHolderLayout->addWidget(saveHolder);
            QHBoxLayout* layout = new QHBoxLayout(saveHolder);

            QLabel* label = new QLabel();
            label->setText(QString::fromStdString(entry.path().filename().string()));
            layout->addWidget(label);

            QPushButton* button = new QPushButton(QString("Wczytaj"));
            button->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
            layout->addWidget(button);

            connect(button, &QPushButton::clicked, this, [this, entry]() {
                startNewChessGameFromSave(entry.path().string());
                });
        }
    }
}

void ChessAppQt::connectSavesBackBtn()
{
    connect(ui.saveBackBtn, &QPushButton::clicked, this, [this]() {
        ui.stackedWidget->setCurrentIndex(2);
        });
}

