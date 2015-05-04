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

    int bit;
    try
    {
        char* str = (char*)malloc(filePath.size()+2);
        memset(str,0,filePath.size()+2);
        memcpy(str, filePath.toStdString().c_str(), filePath.size()+2);
        bit = ReadFile(str);
        free(str);
    } catch(...){
        QMessageBox::information(this, "File open error", "File open error");
    }

    switch(bit)
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

   temp1->SetHeader(bufferPoint);
   temp1->SetHeaderMemberList();


    //init headers
    elfHeader.SetHeader(bufferPoint);
    elfHeader.SetHeaderMemberList();
    elfPrgHeader.SetHeader(bufferPoint, elfHeader.prgHeaderOffset, elfHeader.prgHeaderEntSize, elfHeader.prgHeaderNumber);
    elfPrgHeader.SetHeaderMemberList();
    elfSeHeader.SetHeader(bufferPoint, elfHeader.seHeaderOffset, elfHeader.seHeaderEntSize, elfHeader.seHeaderNumber);
    elfSeHeader.SetHeaderMemberList();

    QTreeWidgetItem* topItem;
    topItem = AddRootNameWidget(ui->treeWidgetName, fileName);
    ui->treeWidgetName->expandAll();

    //add name tree widget item
    AddChild(0, topItem, "Header");

    //Add Program Header Member in Name Widget
    QTreeWidgetItem* middleItem = AddChild(0, topItem, "Program Header");
    foreach(QString item, elfPrgHeader.p_typeStringList)
    {
        AddChild(0, middleItem, item);
    }
    //Add Section Header Member in Name Widget
    middleItem = AddChild(0, topItem, "Section Header");
    foreach(QString item, elfSeHeader.s_typeStringList)
    {
        AddChild(0, middleItem, item);
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
                    foreach(ElfDataType item, elfHeader.headerMemberList)
                    {
                        AddRootValueWidget(ui->treeWidgetValue, item.memberOffset,  item.memberName, item.memberValue);
                    }
                    break;

                case PRG_TYPE:
                    dumpcode((unsigned char*)elfPrgHeader.GetHeader(), elfPrgHeader.GetTotalSize(), elfPrgHeader.GetOffset());
                    break;

                case SE_TYPE:
                    dumpcode((unsigned char*)elfSeHeader.GetHeader(), elfSeHeader.GetTotalSize(), elfSeHeader.GetOffset());
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
                    foreach(ElfDataType item, elfPrgHeader.p_list[row])
                    {
                        AddRootValueWidget(ui->treeWidgetValue, item.memberOffset,  item.memberName, item.memberValue);
                    }
                    break;

                case SE_TYPE:
                    //add value tree widget item
                    foreach(ElfDataType item, elfSeHeader.s_list[row])
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
        dumpcode((unsigned char*)bufferPoint, fileSize, elfHeader.GetOffset());
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
        offset.sprintf("0x%08x  ",i + base); //Offset output

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
