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

private slots:
    void open();
    void save();
    void help();
    void exit();
    void switchstil();
    //void ctrls();
    //void ctrlo();
};

#endif // MAINWINDOW_H
