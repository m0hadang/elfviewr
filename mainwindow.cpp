#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ElfDataType.h"
#include <stdio.h>
#include <elf.h>
#include <QMessageBox>
#include <QList>
#include <QTreeWidgetItem>
#include "Fileopendialog.h"
#define HEA_TYPE 0
#define PRG_TYPE 1
#define SE_TYPE 2
#define HEA_LEVEL -1
#define MEM_LEVEL 0

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //32bit
    elf32Header = new ElfHeaderClass<Elf32_Ehdr>;
    elf32PrgHeader = new ElfPrgHeaderClass<Elf32_Phdr>;
    elf32SeHeader = new ElfSeHeaderClass<Elf32_Shdr>;
    //64bit
    elf64Header = new ElfHeaderClass<Elf64_Ehdr>;
    elf64PrgHeader = new ElfPrgHeaderClass<Elf64_Phdr>;
    elf64SeHeader = new ElfSeHeaderClass<Elf64_Shdr>;
}

MainWindow::~MainWindow()
{
    delete ui;
    free(bufferPoint);
}

void MainWindow::LoadFile()
{
    NameWidgetColumnMode();
    ValueWidgetColumnHexMode();

    try
    {
        char* str = (char*)malloc(filePath.size()+2);
        memset(str,0,filePath.size()+2);
        memcpy(str, filePath.toStdString().c_str(), filePath.size()+2);
        bitInfo = ReadFile(str);
        free(str);
    } catch(...){
        QMessageBox::information(this, "File open error", "File open error");
    }

    switch(bitInfo)
    {
      case ELFCLASS32:
        QMessageBox::information(this, "32bit ELF", "this is 32bit elf");
        ElfDataType::SetBitInfo(ELFCLASS32);
        break;

      case ELFCLASS64:
        ElfDataType::SetBitInfo(ELFCLASS64);
        QMessageBox::information(this, "64bit ELF", "this is 64bit elf");
        break;

      default:
        QMessageBox::information(this, "wrong ELF", "this is wrong elf");
        return;
    }

    //init headers

    SetEHeader();
    SetEHeaderMemberList();
    SetPrgHeader();
    SetPrgHeaderMemberList();
    SetSeHeader();
    SetSeHeaderMemberList();

    QTreeWidgetItem* topItem;
    topItem = AddRootNameWidget(ui->treeWidgetName, fileName);
    ui->treeWidgetName->expandAll();

    //add name tree widget item
    AddChild(0, topItem, "Header");

    //Add Program Header Member in Name Widget
    QTreeWidgetItem* middleItem = AddChild(0, topItem, "Program Header");
    foreach(QString item, GetPrgP_typeStringList())
    {
        AddChild(0, middleItem, item);
    }
    //Add Section Header Member in Name Widget
    middleItem = AddChild(0, topItem, "Section Header");
    foreach(QString item, GetSeP_typeStringList())
    {
        AddChild(0, middleItem, item);
    }

}
void MainWindow::SetEHeader()
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        elf32Header->SetHeader(bufferPoint);
        break;

      case ELFCLASS64:
        elf64Header->SetHeader(bufferPoint);
        break;
    }
}
void MainWindow::SetEHeaderMemberList()
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        elf32Header->SetHeaderMemberList();
        break;

      case ELFCLASS64:
        elf64Header->SetHeaderMemberList();
        break;
    }
}
void MainWindow::SetPrgHeader()
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        elf32PrgHeader->SetHeader(bufferPoint, elf32Header->prgHeaderOffset, elf32Header->prgHeaderEntSize, elf32Header->prgHeaderNumber);
        break;

      case ELFCLASS64:
        elf64PrgHeader->SetHeader(bufferPoint, elf64Header->prgHeaderOffset, elf64Header->prgHeaderEntSize, elf64Header->prgHeaderNumber);
        break;
    }
}
void MainWindow::SetPrgHeaderMemberList()
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        elf32PrgHeader->SetHeaderMemberList();
        break;

      case ELFCLASS64:
        elf64PrgHeader->SetHeaderMemberList();
        break;
    }

}
void MainWindow::SetSeHeader()
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        elf32SeHeader->SetHeader(bufferPoint, elf32Header->seHeaderOffset, elf32Header->seHeaderEntSize, elf32Header->seHeaderNumber);
        break;

      case ELFCLASS64:
        elf64SeHeader->SetHeader(bufferPoint, elf64Header->seHeaderOffset, elf64Header->seHeaderEntSize, elf64Header->seHeaderNumber);
        break;
    }
}
void MainWindow::SetSeHeaderMemberList()
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        elf32SeHeader->SetHeaderMemberList();
        break;

      case ELFCLASS64:
        elf64SeHeader->SetHeaderMemberList();
        break;
    }
}
QList<QString> MainWindow::GetPrgP_typeStringList()
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        return elf32PrgHeader->p_typeStringList;

      case ELFCLASS64:
        return elf64PrgHeader->p_typeStringList;
    }
}
QList<QString> MainWindow::GetSeP_typeStringList()
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        return elf32SeHeader->s_typeStringList;

      case ELFCLASS64:
        return elf64SeHeader->s_typeStringList;
    }
}
size_t MainWindow::GetHeaderOffset()
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        return elf32Header->GetOffset();

      case ELFCLASS64:
        return elf64Header->GetOffset();
    }
}
size_t MainWindow::GetPrgOffset()
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        return elf32PrgHeader->GetOffset();

      case ELFCLASS64:
        return elf64PrgHeader->GetOffset();
    }
}
size_t MainWindow::GetSeOffset()
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        return elf32SeHeader->GetOffset();

      case ELFCLASS64:
        return elf64SeHeader->GetOffset();
    }
}
QList<ElfDataType> MainWindow::GetPrgP_list(int row)
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        return elf32PrgHeader->p_list[row];

      case ELFCLASS64:
        return elf64PrgHeader->p_list[row];
    }
}
QList<ElfDataType> MainWindow::GetSeS_list(int row)
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        return elf32SeHeader->s_list[row];

      case ELFCLASS64:
        return elf64SeHeader->s_list[row];
    }
}
size_t MainWindow::GetPrgTotalSize()
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        return elf32PrgHeader->GetTotalSize();

      case ELFCLASS64:
        return elf64PrgHeader->GetTotalSize();
    }
}
size_t MainWindow::GetSeTotalSize()
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        return elf32SeHeader->GetTotalSize();

      case ELFCLASS64:
        return elf64SeHeader->GetTotalSize();
    }
}
QList<ElfDataType> MainWindow::GetHeaderMemberList()
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        return elf32Header->headerMemberList;

      case ELFCLASS64:
        return elf64Header->headerMemberList;
    }
}
unsigned char* MainWindow::GetPrgPointer()
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        return (unsigned char*)elf32PrgHeader->GetHeader();

      case ELFCLASS64:
        return (unsigned char*)elf64PrgHeader->GetHeader();
    }
}

unsigned char* MainWindow::GetSePointer()
{
    switch(bitInfo)
    {
      case ELFCLASS32:
        return (unsigned char*)elf32SeHeader->GetHeader();

      case ELFCLASS64:
        return (unsigned char*)elf64SeHeader->GetHeader();
    }
}
//, char* &bufferPoint
int MainWindow::ReadFile(char* filename)
{
  FILE* fp;
  fp = fopen(filename,"rb");
  if(fp==NULL)
  {
    QMessageBox::information(this,"File error","File Open Error");
    exit(1);
  }
//GET FILE SIZE
  //size_t fileSize;
  fseek(fp, 0, SEEK_END);
  fileSize = ftell(fp);
  rewind(fp);


  bufferPoint = (char*)malloc(sizeof(char)*fileSize);
//READ FILE
  size_t result;
  result = fread(bufferPoint,1,fileSize,fp);
  if(result != fileSize)
  {
    fputs("Reading error", stderr);
    exit(3);
  }
//DUMP FILE

  unsigned char e_ident[EI_NIDENT];
  memcpy((char*)&e_ident, bufferPoint, EI_NIDENT);

  int bitInfo = e_ident[EI_CLASS];



  //파일 헥스 덤프
  //dumpcode((unsigned char*)buffer,fileSize);

  fclose(fp);
  return bitInfo;
}
QTreeWidgetItem* MainWindow::AddRootNameWidget(QTreeWidget* view, QString name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(view);
    item->setText(0, name);
    view->addTopLevelItem(item);

    return item;
}

QTreeWidgetItem* MainWindow::AddRootValueWidget(QTreeWidget* view, QString left, QString center, QString right)
{

    QTreeWidgetItem *item = new QTreeWidgetItem(view);

    item->setText(0, left);
    item->setText(1, center);
    item->setText(2, right);
    view->addTopLevelItem(item);
    return item;
}

QTreeWidgetItem* MainWindow::AddChild(int column, QTreeWidgetItem* parent, QString name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(column,name);
    parent->addChild(item);
    return item;
}

void MainWindow::NameWidgetColumnMode()
{
    //setting name tree widget
    ui->treeWidgetName->setColumnCount(1);
    ui->treeWidgetName->setHeaderLabel("NAME");
}

void MainWindow::ValueWidgetColumnMemberMode()
{
    //setting value widget in Member Mode
    ui->treeWidgetValue->setColumnCount(3);
    ui->treeWidgetValue->setColumnWidth(0,200);
    ui->treeWidgetValue->setColumnWidth(1,200);
    ui->treeWidgetValue->setColumnWidth(2,200);
    ui->treeWidgetValue->setHeaderLabels(QStringList() << "Offset" << "Member" << "Value");
}
void MainWindow::ValueWidgetColumnHexMode()
{
    //setting value widget in Hex Mode
    ui->treeWidgetValue->setColumnCount(3);
    ui->treeWidgetValue->setColumnWidth(0,200);
    ui->treeWidgetValue->setColumnWidth(1,400);
    ui->treeWidgetValue->setColumnWidth(2,200);
    ui->treeWidgetValue->setHeaderLabels(QStringList() << "Offset" << "Hex" << "Asci");
}

void MainWindow::on_treeWidgetName_itemSelectionChanged()
{
    ui->treeWidgetValue->clear();
    const QModelIndex index = ui->treeWidgetName->currentIndex();
    bool notRootItem = index.parent().isValid();

    int row = index.row();
    if(notRootItem)
    {
        int itemLevel = index.parent().parent().row();
        switch(itemLevel)
        {
        case HEA_LEVEL:
            ValueWidgetColumnHexMode();
            switch(row)
            {
                case HEA_TYPE:
                    //add value tree widget item
                    foreach(ElfDataType item, GetHeaderMemberList())
                    {
                        AddRootValueWidget(ui->treeWidgetValue, item.memberOffset,  item.memberName, item.memberValue);
                    }
                    break;

                case PRG_TYPE:
                    dumpcode(GetPrgPointer(), GetPrgTotalSize(), GetPrgOffset());
                    break;

                case SE_TYPE:
                    dumpcode(GetSePointer(), GetSeTotalSize(), GetSeOffset());
                    break;
            }
            break;

        case MEM_LEVEL:
            ValueWidgetColumnMemberMode();
            int headerType = index.parent().row();
            switch(headerType)
            {
                case HEA_TYPE:
                //EMPTRY
                    break;

                case PRG_TYPE:
                    //add value tree widget item
                    foreach(ElfDataType item, GetPrgP_list(row))
                    {
                        AddRootValueWidget(ui->treeWidgetValue, item.memberOffset,  item.memberName, item.memberValue);
                    }
                    break;

                case SE_TYPE:
                    //add value tree widget item
                    foreach(ElfDataType item, GetSeS_list(row))
                    {
                        AddRootValueWidget(ui->treeWidgetValue, item.memberOffset,  item.memberName, item.memberValue);
                    }
                    break;
            }
            break;
        }
    }
    else//all hex print
    {
        dumpcode((unsigned char*)bufferPoint, fileSize, GetHeaderOffset());
    }
}




unsigned char MainWindow::printchar(unsigned char c)
{
    if(isprint(c))
      return c;
    else
      return '.';
}

void MainWindow::dumpcode(unsigned char *buff, size_t len, size_t base)
{


    QString offset;
    QString hex;
    QString asci;
    QString temp;
    size_t i;
    for(i=0;i<len;i++)
    {
      if(i%16==0)
      {
          if(bitInfo==ELFCLASS32)
            offset.sprintf("0x%08x  ",i + base); //Offset output
          else if(bitInfo==ELFCLASS64)
            offset.sprintf("0x%016x  ",i + base); //Offset output
      }

      temp.sprintf("%02x  ",buff[i]);
      hex.append(temp); //1 byte hex output
      if(i%16-15==0)
      {
        size_t j;
        for(j=i-15;j<=i;j++)
        {
          temp.sprintf("%c ",printchar(buff[j]));
          asci.append(temp); //Asci output
        }

        AddRootValueWidget(ui->treeWidgetValue, offset,  hex, asci);
        offset.clear();
        hex.clear();
        asci.clear();
      }
    }

    if(i%16!=0)
    {
      size_t j;

      for(j=i-i%16;j<len;j++)
        asci.append(printchar(buff[j])); // Asci output
      AddRootValueWidget(ui->treeWidgetValue, offset,  hex, asci);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    FileOpenDialog mDialog;
    mDialog.setModal(true);
    mDialog.exec();
    filePath = mDialog.filePath;
    fileName = mDialog.fileName;

    if(filePath == "")
    {
        QMessageBox::information(this, "NO FILE", "THE FILE IS NOT EXIST");
        return ;
    }
    LoadFile();

}

void MainWindow::on_actionExit_triggered()
{
    close();
}
