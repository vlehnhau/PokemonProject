#include "gui/Gui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gui w;
    w.show();
    return QApplication::exec();
}

