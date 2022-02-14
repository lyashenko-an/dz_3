#ifndef MNW_H
#define MNW_H

#include <QWidget>
#include <QGridLayout>
#include <QTreeView>
#include <QComboBox>
#include <QPushButton>
#include <QStandardItemModel>
#include <QApplication>

Q_PROPERTY(QStandardItemModel *model READ getCurrentModel WRITE setNewModel)

class mnW : public QWidget
{
    Q_OBJECT
public:
    explicit mnW(QWidget *parent = nullptr);
    void clearTree();

    QStandardItemModel *getCurrentModel()const
    {
        return model;
    }
    void setNewModel(QStandardItemModel *newmodel);
    void rebuildModel(QString str);

private:
    QGridLayout *gridLay;
    QTreeView *tree;
    QPushButton *mainPath;
    QComboBox *diskSelBox;

private slots:
    void chgDisk(int index);
    void goMainPath();

private:
    QStandardItemModel *model;
    QString currentPath;

signals:

public slots:
};

#endif // MNW_H
