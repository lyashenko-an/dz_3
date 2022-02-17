#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QShortcut>
#include <QTextEdit>
#include <QPushButton>
#include <QResource>
#include <QTranslator>
#include <QComboBox>
#include <QEvent>
#include <QTextCodec>
#include <QPrintDialog>
#include <QPrinter>
#include <QPainter>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void changeEvent(QEvent *event) override;

private:
    Ui::MainWindow *ui;
    QTextEdit *textEdit;
    QPushButton *openAct;
    QPushButton *saveAct;
    QPushButton *helpAct;
    QPushButton *stile;
    QPushButton *exitAct;
    QShortcut *keyctrls;
    QShortcut *keyctrlo;
    QShortcut *keyctrlq;

    QComboBox *comboBox;
    QTranslator myTranslator;
    QMenu *fileMenu;

    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *helpAction;
    QAction *printAct;

    QPrinter printer;



private slots:
    void open();
    void save();
    void help();
    void exit();
    void switchstil();
    void print();
    //void ctrls();
    //void ctrlo();
};

#endif // MAINWINDOW_H


/*
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
*/
