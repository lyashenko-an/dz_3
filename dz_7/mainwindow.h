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
#include <QFont>
#include <QFontDialog>


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
    QAction *fontdialog;
    QAction *aligleft;
    QAction *aligcentr;
    QAction *aligright;


    QPrinter printer;
    QPushButton *lal;
    QPushButton *ceal;
    QPushButton *ral;


private slots:
    void open();
    void save();
    void help();
    void exit();
    void switchstil();
    void print();
    void fntdlg();

    void on_lal_clicked();
    void on_ceal_clicked();
    void on_ral_clicked();
};

#endif // MAINWINDOW_H
