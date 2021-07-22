#include "ConsoleWindow.h"

#include <QApplication>
#include <ConsoleDemo.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConsoleDemo w;
    w.show();
    return a.exec();
}
