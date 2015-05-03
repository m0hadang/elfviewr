#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include "ElfHeaderClass.h"
#include "ElfPrgHeaderClass.h"
#include "ElfSeHeaderClass.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int ReadFile(char* filename, char* &bufferPoint);
    QTreeWidgetItem* AddRootNameWidget(QTreeWidget* view, QString name);
    QTreeWidgetItem* AddRootValueWidget(QTreeWidget* view, QString left, QString center, QString right);
    QTreeWidgetItem* AddChild(int column, QTreeWidgetItem* parent, QString name);
    //Column setting
    void NameWidgetColumnMode();
    void ValueWidgetColumnHexMode();
    void ValueWidgetColumnMemberMode();

private slots:
    void on_treeWidgetName_itemSelectionChanged();

private:
    Ui::MainWindow *ui;
    char* bufferPoint;
    ElfHeaderClass<Elf32_Ehdr> elfHeader;
    ElfPrgHeaderClass<Elf32_Phdr> elfPrgHeader;
    ElfSeHeaderClass<Elf32_Shdr> elfSeHeader;
};

#endif // MAINWINDOW_H
