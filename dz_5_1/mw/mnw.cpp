#include "mnw.h"
#include <QDir>

mnW::mnW(QWidget *parent) : QWidget(parent) , model(nullptr)
{
    gridLay = new QGridLayout(this);
    this->setLayout(gridLay);
    tree = new QTreeView(this);

    gridLay->addWidget(tree, 1, 0, 10, 10);
    setMinimumSize(500, 600);

    if(QSysInfo::productType() == "windows")
    {
        diskSelBox = new QComboBox(this);
        QFileInfoList list = QDir::drives();
        QFileInfoList::const_iterator listdisk = list.begin();
        int amount = list.count();
        for (int i= 0; i < amount; i++)
            {
            diskSelBox -> addItem(listdisk -> path());
            listdisk++;
            }
        if (amount > 0)
            {
            rebuildModel(list.at(0).path());
            }

        gridLay -> addWidget(diskSelBox, 0, 0, 1, 2);
        connect(diskSelBox, SIGNAL(activated(int)), this, SLOT(chgDisk(int)));
    }
    else
    {
        mainPath = new QPushButton(this);
        mainPath -> setText("/");
        gridLay -> addWidget(mainPath, 0, 0, 1, 2);
        connect(mainPath, SIGNAL(clicked()), this, SLOT(goMainPath()));
        rebuildModel("/");
    }
}

void mnW::chgDisk(int index)
{
    QFileInfoList list = QDir::drives();
    rebuildModel(list.at(index).path());
}

void mnW::goMainPath()
{
    rebuildModel("/");
}

void mnW::setNewModel(QStandardItemModel *newmodel)
{
    tree -> setModel(newmodel);
    model = newmodel;
}

void mnW::rebuildModel(QString str)
{
    currentPath = str;
    QStandardItemModel *model = new QStandardItemModel(this);
    QList<QStandardItem *> items;
    items.append(new QStandardItem(QIcon(QApplication::style() -> standardIcon(QStyle::SP_DriveHDIcon)), str));
    model -> appendRow(items);

    QDir dir(str);
    dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Dirs);
    QStringList list = dir.entryList();
    int amount = list.count();
    QList<QStandardItem *>folders;
    for (int i = 0; i < amount; i++)
    {
    QStandardItem *f = new QStandardItem(QIcon(QApplication::style() -> standardIcon(QStyle::SP_DirIcon)), list.at(i));
    folders.append(f);
    }

    items.at(0)->appendRows(folders);

    dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Files);amount = list.count();
    QList<QStandardItem *> files;

    for (int i = 0; i < amount; i++)
        {
        QStandardItem* f = new
        QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon)),
        list.at(i));
        files.append(f);
        }
    items.at(0)->appendRows(files);
    setNewModel(model);
}
