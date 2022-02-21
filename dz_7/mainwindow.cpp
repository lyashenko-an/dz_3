#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    //openAct(nullptr),
    //saveAct(nullptr),
    //helpAct(nullptr),
    //stile(nullptr),
    //exitAct(nullptr),
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

    fileMenu = this -> menuBar() ->addMenu(tr("&Menu"));
    openAction = new QAction(tr("&Open"), this);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    saveAction = new QAction(tr("&Save"), this);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    exitAction = new QAction(tr("&Exit"), this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    helpAction = new QAction(tr("&Help"), this);
    connect(helpAction, SIGNAL(triggered()), this, SLOT(help()));
    printAct = new QAction(tr("&Print"), this);
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));
    fontdialog = new QAction(tr("&Shrift"), this);
    connect(fontdialog, SIGNAL(triggered()), this, SLOT(fntdlg()));

    fileMenu -> addAction(openAction);
    fileMenu -> addAction(saveAction);
    fileMenu -> addSeparator();
    fileMenu -> addAction(fontdialog);
    fileMenu -> addSeparator();
    fileMenu -> addAction(helpAction);
    fileMenu -> addSeparator();
    fileMenu -> addAction(printAct);
    fileMenu -> addSeparator();
    fileMenu -> addAction(exitAction);

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

    fileMenu = this -> menuBar() ->addMenu(tr("&Text"));

    aligleft = new QAction(tr("&Align to left"), this);
    connect(aligleft, SIGNAL(triggered()), this, SLOT(on_lal_clicked()));

    aligcentr = new QAction(tr("&Align to centre"), this);
    connect(aligcentr, SIGNAL(triggered()), this, SLOT(on_ceal_clicked()));

    aligright = new QAction(tr("&Align to right"), this);
    connect(aligright, SIGNAL(triggered()), this, SLOT(on_ral_clicked()));

    fileMenu -> addAction(aligleft);
    fileMenu -> addAction(aligcentr);
    fileMenu -> addAction(aligright);

    fileMenu = this -> menuBar() ->addMenu(tr("&Help"));

    textEdit = new QTextEdit();
    setWindowTitle(tr("dz_6 ver.1"));

    QPixmap *pic = new QPixmap(":/la.png");
    QIcon *icon = new QIcon(*pic);
    ui -> lal -> setIcon(*icon);
    ui -> lal -> setIconSize(QSize(pic->width(), pic->height()));

    *pic = QPixmap(":/ca.png");
    *icon = QIcon(*pic);
    ui -> ceal -> setIcon(*icon);
    ui -> ceal -> setIconSize(QSize(pic->width(), pic->height()));

    *pic = QPixmap(":/ra.png");
    *icon = QIcon(*pic);
    ui -> ral -> setIcon(*icon);
    ui -> ral -> setIconSize(QSize(pic->width(), pic->height()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fntdlg()
{
    QFont font = textEdit -> textCursor().charFormat().font();
    QFontDialog fdlg(font, this);
    bool ok;
    font = fdlg.getFont(&ok);
    if (ok)
        {
        QTextCharFormat fmt;
        fmt.setFont(font);
        textEdit -> textCursor().setCharFormat(fmt);
        }
}


void MainWindow::print()
{
    QPrintDialog dialg(&printer, this);
    dialg.setWindowTitle("Print");
    if (dialg.exec() != QDialog::Accepted)
    return;
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

void MainWindow::on_lal_clicked()
{
    QTextCursor cursor = ui -> textEdit -> textCursor();
    QTextBlockFormat txtForm = cursor.blockFormat();
    txtForm.setAlignment(Qt::AlignLeft);
    cursor.mergeBlockFormat(txtForm);
    ui -> textEdit -> setTextCursor(cursor);
}

void MainWindow::on_ceal_clicked()
{
    QTextCursor cursor = ui -> textEdit -> textCursor();
    QTextBlockFormat txtForm = cursor.blockFormat();
    txtForm.setAlignment(Qt::AlignCenter);
    cursor.mergeBlockFormat(txtForm);
    ui -> textEdit -> setTextCursor(cursor);
}

void MainWindow::on_ral_clicked()
{
    QTextCursor cursor = ui -> textEdit -> textCursor();
    QTextBlockFormat txtForm = cursor.blockFormat();
    txtForm.setAlignment(Qt::AlignRight);
    cursor.mergeBlockFormat(txtForm);
    ui -> textEdit -> setTextCursor(cursor);
}
