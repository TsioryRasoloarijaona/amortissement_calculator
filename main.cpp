#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QDir>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QStringList resources = QDir(":/icons").entryList();
    qDebug() << "Ressources disponibles dans /icons:" << resources;
    return a.exec();
}
