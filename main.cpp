#include "imgtoasciiwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImgToAsciiWidget w;
    w.show();

    return a.exec();
}
