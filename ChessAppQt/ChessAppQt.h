#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChessAppQt.h"

class ChessAppQt : public QMainWindow
{
    Q_OBJECT

public:
    ChessAppQt(QWidget *parent = nullptr);
    ~ChessAppQt();

private:
    Ui::ChessAppQtClass ui;
};
