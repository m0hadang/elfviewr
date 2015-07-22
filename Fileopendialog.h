#ifndef FILEOPENDIALOG_H
#define FILEOPENDIALOG_H
#include <QString>
#include <QDialog>
#include <QDirModel>
namespace Ui {
class FileOpenDialog;
}

//File Explorer
class FileOpenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileOpenDialog(QWidget *parent = 0);
    ~FileOpenDialog();
    QString filePath;
    QString fileName;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::FileOpenDialog *ui;
    QDirModel* model;
};

#endif // FILEOPENDIALOG_H
