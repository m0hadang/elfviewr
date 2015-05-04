#include "Fileopendialog.h"
#include "ui_Fileopendialog.h"

#include <QMessageBox>
FileOpenDialog::FileOpenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileOpenDialog)
{
    ui->setupUi(this);
    model = new QDirModel(this);
    model->setReadOnly(true);
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

    ui->treeView->setModel(model);


}

FileOpenDialog::~FileOpenDialog()
{
    delete ui;
}

void FileOpenDialog::on_buttonBox_accepted()
{
    QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid())
    {
        filePath = "";
        fileName = "";
        return ;
    }

    if(model->fileInfo(index).isDir())
        QMessageBox::information(this, "Directory", "This is directory");

    else
    {
        filePath = model->filePath(index);
        fileName = model->fileName(index);
    }
}
