#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mnw.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    fmqw = new mnW(this);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
