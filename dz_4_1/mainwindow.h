#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTextEdit *textEdit;
    QPushButton *openAct;
    QPushButton *saveAct;
    QPushButton *helpAct;
    QPushButton *lyng;
    QPushButton *exitAct;
    QTranslator translater;
    void switchLyngvo(QString langvage);


private slots:
    void open();
    void save();
    void help();
    void lyngvo();
    void exit();
};

#endif // MAINWINDOW_H
