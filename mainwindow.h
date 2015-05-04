#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QString>
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
    int ReadFile(char* filename);
    QTreeWidgetItem* AddRootNameWidget(QTreeWidget* view, QString name);
    QTreeWidgetItem* AddRootValueWidget(QTreeWidget* view, QString left, QString center, QString right);
    QTreeWidgetItem* AddChild(int column, QTreeWidgetItem* parent, QString name);

    //Column setting
    void LoadFile();
    void NameWidgetColumnMode();
    void ValueWidgetColumnHexMode();
    void ValueWidgetColumnMemberMode();
    void dumpcode(unsigned char *buff, size_t len, size_t base);
    unsigned char  printchar(unsigned char c);

private slots:
    void on_treeWidgetName_itemSelectionChanged();

    void on_actionOpen_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    char* bufferPoint;
    size_t fileSize;
    ElfHeaderClass<Elf32_Ehdr> elfHeader;
    ElfPrgHeaderClass<Elf32_Phdr> elfPrgHeader;
    ElfSeHeaderClass<Elf32_Shdr> elfSeHeader;
    ElfHeaderClass<Elf64_Ehdr> elf64Header;
    ElfPrgHeaderClass<Elf64_Phdr> elf64PrgHeader;
    ElfSeHeaderClass<Elf64_Shdr> elf64SeHeader;

    ElfHeaderClass<Elf32_Ehdr>* temp1;
    ElfHeaderClass<Elf64_Ehdr>* temp2;

    QString filePath;
    QString fileName;
};

#endif // MAINWINDOW_H
