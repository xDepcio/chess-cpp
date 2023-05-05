#include "ChessAppQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChessAppQt w;
    w.show();
    return a.exec();
}
