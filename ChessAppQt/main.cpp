#include "ChessAppQt.h"
#include <QtWidgets/QApplication>
//#include <qresource.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChessAppQt w;
    //QResource::registerResource(":/ChessAppQt.qrc");
    w.show();
    return a.exec();
}
