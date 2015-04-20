#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
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
    void AddRootNameWidget(QTreeWidget* view, QString name);
    void AddRootValueWidget(QTreeWidget* view, QString offset, QString member, QString value);
    void AddChild(int column, QTreeWidgetItem* parent, QString name);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H


