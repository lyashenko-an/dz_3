#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    openAct(nullptr),
    saveAct(nullptr),
    helpAct(nullptr),
    lyng(nullptr),
    exitAct(nullptr),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    switchLyngvo(QLocale::system().name());

    openAct = new QPushButton(this);
    openAct -> move(10, 440);

    saveAct = new QPushButton(this);
    saveAct -> move(110, 440);

    helpAct = new QPushButton(this);
    helpAct -> move(210, 440);

    lyng = new QPushButton(this);
    lyng -> move(310, 440);

    exitAct = new QPushButton(this);
    exitAct -> move(410, 440);

    openAct -> setText(tr("Open"));
    saveAct -> setText(tr("Save"));
    helpAct -> setText(tr("Help"));
    lyng -> setText(tr("Lyngvo"));
    exitAct -> setText(tr("Exit"));

    connect(openAct, SIGNAL(clicked()), this, SLOT(open()));
    connect(saveAct, SIGNAL(clicked()), this, SLOT(save()));
    connect(helpAct, SIGNAL(clicked()), this, SLOT(help()));
    connect(lyng, SIGNAL(clicked()), this, SLOT(lyngvo()));
    connect(exitAct, SIGNAL(clicked()), this, SLOT(exit()));


    textEdit = new QTextEdit();

    setWindowTitle(tr("dz_4 ver.1"));




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
        ui -> textEdit -> setText(in.readAll());
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
            stream << ui -> textEdit -> toPlainText();
            stream.flush();
            file.close();
        }
    }
}

void MainWindow::help()
{

    QFile file(":/help.txt");
    if(file.open(QIODevice::ReadOnly))
        {
        QTextStream help_fl(&file);
        ui -> textEdit -> setText(help_fl.readAll());
        file.close();
        }
}


void MainWindow::lyngvo()
{
QObject *obj = sender();
if (obj == lyng) switchLyngvo("ru");
}

void MainWindow::switchLyngvo(QString langvage)
{
    translater.load(langvage);
    qApp -> installTranslator(&translater);
    QString str = tr("Open");
    openAct -> setText(str + "ru");
    //saveAct -> setText(tr("Save"));
    //helpAct -> setText(tr("Help"));
    //lyng -> setText(tr("Lyngvo"));
    //exitAct -> setText(tr("Exit"));


}

void MainWindow::exit()
{
    close();
}