#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLibrary>
#include"dl.h"
#include"res_ins.h"
#include"find_helper.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    int disasm();
    void clear();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int show_file(vector<unsigned char> &code);
    void show_res1(int j, res_data &k, length_dis &z);
    void show_res2(int j, res_data &k, length_dis &z);
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
