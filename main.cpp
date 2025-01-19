#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QDir>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QIcon icon(":/files/profits_32.png");
    a.setWindowIcon(icon);
    MainWindow w;
    w.setWindowFlags(w.windowFlags() & ~Qt::WindowMaximizeButtonHint);
    w.show();


    return a.exec();
}
