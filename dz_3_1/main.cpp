#include "mainwindow.h"
#include <QApplication>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setQuitOnLastWindowClosed(true);

    /*
    QTextEdit textEdit;
    textEdit.show();
    */

   MainWindow w;
   w.show();

    return a.exec();
}
