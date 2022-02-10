#include "mainwindow.h"
#include <QApplication>
#include <QTextEdit>
#include <QPushButton>
#include <QResource>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QResource::registerResource("./help_dz.qrc");

    MainWindow w;
    w.show();

    return a.exec();
}
