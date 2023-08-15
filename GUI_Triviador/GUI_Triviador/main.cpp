#include "GUI_Triviador.h"
//#include "MatchHistory.h"
#include "game.h"
//#include "Register.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game w;
    //Register w;
    //GUI_Triviador w;
    //MatchHistory w;
    w.resize(650,400);
    w.show();
    return a.exec();
}
