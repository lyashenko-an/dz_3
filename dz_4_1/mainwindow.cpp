#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    openAct(nullptr),
    saveAct(nullptr),
    helpAct(nullptr),
    stile(nullptr),
    exitAct(nullptr),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui -> comboBox ->addItems(QStringList() << "en_EN" << "ru_RU");

    myTranslator.load(QString("dz_4_") + QString("en_EN"));
    qApp ->installTranslator(&myTranslator);


    openAct = new QPushButton(this);
    openAct -> move(10, 440);

    saveAct = new QPushButton(this);
    saveAct -> move(110, 440);

    helpAct = new QPushButton(this);
    helpAct -> move(210, 440);

    stile = new QPushButton(this);
    stile -> move(310, 440);

    exitAct = new QPushButton(this);
    exitAct -> move(410, 440);

    keyctrlo = new QShortcut(this);
    keyctrlo->setKey(Qt::CTRL + Qt::Key_O);

    keyctrls = new QShortcut(this);
    keyctrls->setKey(Qt::CTRL + Qt::Key_S);

    keyctrlq = new QShortcut(this);
    keyctrlq->setKey(Qt::CTRL + Qt::Key_Q);

    openAct -> setText(tr("Open"));
    saveAct -> setText(tr("Save"));
    helpAct -> setText(tr("Help"));
    stile -> setText(tr("Stil"));
    exitAct -> setText(tr("Exit"));



    connect(openAct, SIGNAL(clicked()), this, SLOT(open()));
    connect(saveAct, SIGNAL(clicked()), this, SLOT(save()));
    connect(helpAct, SIGNAL(clicked()), this, SLOT(help()));
    connect(stile, SIGNAL(clicked()), this, SLOT(switchstil()));
    connect(exitAct, SIGNAL(clicked()), this, SLOT(exit()));
    connect(keyctrlo, SIGNAL(activated()), this, SLOT(open()));
    connect(keyctrls, SIGNAL(activated()), this, SLOT(save()));
    connect(keyctrlq, SIGNAL(activated()), this, SLOT(exit()));
    connect(ui -> comboBox, static_cast<void (QComboBox:: *)(const QString &) > (&QComboBox::currentIndexChanged), [=](const QString &str){
        myTranslator.load("dz_4_" + str, ".");
        qApp -> installTranslator(&myTranslator);
    });

    textEdit = new QTextEdit();
    setWindowTitle(tr("dz_4 ver.1"));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *event)
{
if(event -> type() == QEvent::LanguageChange)
    {
    ui -> retranslateUi(this);
    }
}

void MainWindow::switchstil()
{
   qApp -> setStyleSheet("QPushButton {font: bold 14 px; background-color: white;} QMainWindow{background-color:blue}");
}

void MainWindow::open()
{
 QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("Text file (*.txt)"));
    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("File reading "), tr("Error!!!"));
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
            QMessageBox::critical(this, tr("File writing "), tr("Error!!!"));
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
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error reading the help file"), tr("!!!"));
            return;
        }
        QTextStream in(&file);
        ui -> textEdit -> setText(in.readAll());
        file.close();
}

void MainWindow::exit()
{
    close();
}
