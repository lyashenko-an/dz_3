#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    openAction = new QAction(tr("&Open"), this);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    exitAction = new QAction(tr("&Exit"), this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    helpAction = new QAction(tr("&Help"), this);


    fileMenu = this->menuBar()->addMenu(tr("&File"));
    fileMenu -> addAction(openAction);
    fileMenu -> addAction(saveAction);
    fileMenu -> addSeparator();
    fileMenu -> addAction(helpAction);
    fileMenu -> addSeparator();
    fileMenu -> addAction(exitAction);

    textEdit = new QTextEdit();

    setCentralWidget(textEdit);
    setWindowTitle(tr("dz_3 ver.2"));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::open()
{
 QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("Text file (*.txt)"));
    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error!!!"), tr("Not open file!"));
            return;
        }

        QTextStream in(&file);
        textEdit -> setText(in.readAll());
        file.close();
    }
}

void MainWindow::save()
{
 QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), "", tr("Text file (*.txt)"));
    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox msgBox; msgBox.setText("Not save file!"); msgBox.exec();
        }
  else
        {
            QTextStream stream(&file);
            stream << textEdit->toPlainText();
            stream.flush();
            file.close();
        }
    }
}
