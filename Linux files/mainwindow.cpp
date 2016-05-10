#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <QMessageBox>
#include <sstream>
#include <sys/stat.h>
#include <sys/mman.h>
#include <elf.h>
#include <stdio.h>
#include <cstdio>
#include <fcntl.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this, SLOT(disasm()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this, SLOT(clear()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clear()
{
    this->ui->textEdit->clear();
    this->ui->textEdit_2->clear();
    this->ui->textEdit_3->clear();
}

int MainWindow::show_file(string &fname,vector<unsigned char> &code)
{
    int num;
    int offset;
    struct stat st;

    if (stat(fname.c_str(), &st) != 0)
    {
        this->ui->textEdit->append("ERROR");
        return 0;
    }
    int fd = open(fname.c_str(), O_RDONLY);
      char *p = (char*)mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

      Elf32_Ehdr *ehdr = (Elf32_Ehdr*)p;
      Elf32_Shdr *shdr = (Elf32_Shdr *)(p + ehdr->e_shoff);
      int shnum = ehdr->e_shnum;

      Elf32_Shdr *sh_strtab = &shdr[ehdr->e_shstrndx];
      const char *const sh_strtab_p = p + sh_strtab->sh_offset;

      for (int i = 0; i < shnum; ++i)
      {
        this->ui->textEdit->append("NAME:");
        this->ui->textEdit->append(sh_strtab_p + shdr[i].sh_name);
        this->ui->textEdit->append("\n");
        this->ui->textEdit->append("OFFSET:");
        this->ui->textEdit->append(QString::number(shdr[i].sh_offset));
        this->ui->textEdit->append("\n");
        this->ui->textEdit->append("size:");
        this->ui->textEdit->append(QString::number(shdr[i].sh_size));
        this->ui->textEdit->append("\n");
        if(!(QString((char*)(sh_strtab_p + shdr[i].sh_name)).compare(".text")))
        {
            num=shdr[i].sh_size;
            offset=shdr[i].sh_offset;

        }
      }

    unsigned char ab;
    FILE* fp=fopen(fname.c_str(),"r");
    fseek(fp,offset,SEEK_SET);
    for(int i=0;i<num;i++)
    {
        fread(&ab,1,sizeof(ab),fp);
        code.push_back(ab);
    }
    fclose(fp);
    return 1;

}

void MainWindow::show_res1(int j,res_data &k,length_dis &z)
{
    this->ui->textEdit_3->insertPlainText(QString::number(j));
    this->ui->textEdit_3->insertPlainText(") ");
    this->ui->textEdit_3->insertPlainText(QString::fromStdString(k.gethex(z)));
    this->ui->textEdit_3->insertPlainText("\n");
    this->ui->textEdit_2->insertPlainText(QString::number(j));
    this->ui->textEdit_2->insertPlainText(") ");
    this->ui->textEdit_2->insertPlainText(QString::fromStdString(" "));
    this->ui->textEdit_2->insertPlainText(QString::fromStdString(k.get_mnem()));
    this->ui->textEdit_2->insertPlainText(QString::fromStdString(" "));
    this->ui->textEdit_2->insertPlainText(QString::fromStdString(k.get_op1()));
    this->ui->textEdit_2->insertPlainText(QString::fromStdString(" "));
    this->ui->textEdit_2->insertPlainText(QString::fromStdString(k.get_op2()));
    this->ui->textEdit_2->insertPlainText("\n");
}

void MainWindow::show_res2(int j,res_data &k,length_dis &z)
{
    this->ui->textEdit_3->insertPlainText(QString::number(j));
    this->ui->textEdit_3->insertPlainText(") ");
    this->ui->textEdit_3->insertPlainText(QString::fromStdString(k.gethex(z)));
    this->ui->textEdit_3->insertPlainText("\n");
    this->ui->textEdit_2->insertPlainText(QString::number(j));
    this->ui->textEdit_2->insertPlainText(") ");
    this->ui->textEdit_2->insertPlainText("Failed to DIZASM");
    this->ui->textEdit_2->insertPlainText("\n");
}

int MainWindow::disasm()
{
        this->ui->textEdit->clear();
        this->ui->textEdit_2->clear();
        this->ui->textEdit_3->clear();
        int j=1;
        int i = 0;
        int num;
        int offset;
        vector<unsigned char> code;
        string fname =this->ui->lineEdit->text().toStdString();
        if(show_file(fname,code)==0)
        {
            return 0;
        }
        length_dis z;
        res_data k;
        Find_helper f;

        int size;
        while (!code.empty())
        {

            size=z.length(code.data(),1);
            if(z.getosize()==1 && z.get_err()!= 1)
            {
               f.get_n_tr(k,z);
               f.get_cl(k,z);
            }
            else
            {
                k.findop_2(z);
            }
            if(z.getfm()==1)
            {
                k.mod_parse(z);
            }
            k.imm(z);
            if (z.get_err()!= 1)
            {
                show_res1(j,k,z);
                code.erase(code.begin(), code.begin() + size);
            }
            else
            {
                show_res2(j,k,z);
                code.erase(code.begin(), code.begin() + 1);
            }
            k.clear();
            z.clear();
            j++;

        }
        return 0;
}
