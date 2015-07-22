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
    void SetEHeader();
    void SetEHeaderMemberList();
    void ClearEHeaderMemberList();
    void SetPrgHeader();
    void SetPrgHeaderMemberList();
    void ClearPrgHeaderMemberList();
    void SetSeHeader();
    void SetSeHeaderMemberList();
    void ClearSeHeaderMemberList();
    QList<QString> GetPrgP_typeStringList();
    QList<QString> GetSeP_typeStringList();
    size_t GetHeaderOffset();
    size_t GetPrgOffset();
    size_t GetSeOffset();
    QList<ElfDataType> GetPrgP_list(int row);
    QList<ElfDataType> GetSeS_list(int row);
    size_t GetPrgTotalSize();
    size_t GetSeTotalSize();
    QList<ElfDataType> GetHeaderMemberList();
    unsigned char* GetPrgPointer();
    unsigned char* GetSePointer();
private slots:
    void on_treeWidgetName_itemSelectionChanged();

    void on_actionOpen_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    //file memory pointer, file dump memory is loaded memory and this pointer will point dump memory
    char* bufferPoint;
    //Operating System bit information
    int bitInfo;
    //file size
    size_t fileSize;

    //only one version used
    //32bit ELF
    ElfHeaderClass<Elf32_Ehdr>* elf32Header;
    ElfPrgHeaderClass<Elf32_Phdr>* elf32PrgHeader;
    ElfSeHeaderClass<Elf32_Shdr>* elf32SeHeader;
    //64bit ELF
    ElfHeaderClass<Elf64_Ehdr>* elf64Header;
    ElfPrgHeaderClass<Elf64_Phdr>* elf64PrgHeader;
    ElfSeHeaderClass<Elf64_Shdr>* elf64SeHeader;

    //Open file path
    QString filePath;
    //Open file name
    QString fileName;
};

#endif // MAINWINDOW_H
