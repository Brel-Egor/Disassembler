#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <string>

#include <QMessageBox>
#include <sstream>
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
    this->ui->lineEdit->clear();
    this->ui->textEdit->clear();
    this->ui->textEdit_2->clear();
    this->ui->textEdit_3->clear();
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


void MainWindow::show_res2(int j, res_data &k, length_dis &z)
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


int MainWindow::show_file(vector<unsigned char> &code)
{
    int i;
    int num;
    IMAGE_NT_HEADERS peHead;
    IMAGE_DOS_HEADER dosMZ;
    IMAGE_SECTION_HEADER *secHead;
    unsigned long d;
    HANDLE host;
    const char* file = this->ui->lineEdit->text().toStdString().c_str();
    if ((host = CreateFileA(file, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
    {
        this->ui->textEdit->insertPlainText("File OPEN Error");
        return 0;
    }
    if (!ReadFile(host, (void*)&dosMZ, sizeof(dosMZ), &d, NULL))
    {
        this->ui->textEdit->insertPlainText("Read Fail");
        return 0;
    }
    if (!(dosMZ.e_magic == IMAGE_DOS_SIGNATURE))
    {
        this->ui->textEdit->insertPlainText("Not a Valid PE");
        return 0;
    }
    SetFilePointer(host, dosMZ.e_lfanew, NULL, FILE_BEGIN);
    if (!ReadFile(host, (void*)&peHead, sizeof(peHead), &d, NULL))
    {
        this->ui->textEdit->insertPlainText("Read Fail");
        return 0;
    }
    if (!(peHead.Signature == IMAGE_NT_SIGNATURE))
    {
        this->ui->textEdit->insertPlainText("Not a Valid PE");
        return 0;
    }
    this->ui->textEdit->insertPlainText("Number of Sections :");
    this->ui->textEdit->insertPlainText(QString::number(peHead.FileHeader.NumberOfSections));
    this->ui->textEdit->insertPlainText("\n");

    secHead = (IMAGE_SECTION_HEADER*)GlobalAlloc(GMEM_FIXED, sizeof(IMAGE_SECTION_HEADER)*peHead.FileHeader.NumberOfSections);
    ReadFile(host, (void*)secHead, sizeof(IMAGE_SECTION_HEADER)*peHead.FileHeader.NumberOfSections, &d, NULL);
    for (i = 0; i<peHead.FileHeader.NumberOfSections; i++)
    {
        this->ui->textEdit->insertPlainText("Section Name :");
        this->ui->textEdit->insertPlainText(QString::fromStdString(reinterpret_cast<char*>(secHead[i].Name)));
        this->ui->textEdit->insertPlainText("\n");

        this->ui->textEdit->insertPlainText("RVA          :");
        this->ui->textEdit->insertPlainText(QString::number((int)secHead[i].VirtualAddress,16));
        this->ui->textEdit->insertPlainText("\n");

        this->ui->textEdit->insertPlainText("Pointer to Raw Data :");
        this->ui->textEdit->insertPlainText(QString::number((int)secHead[i].PointerToRawData,16));
        this->ui->textEdit->insertPlainText("\n");

        this->ui->textEdit->insertPlainText("Size of Data :");
        this->ui->textEdit->insertPlainText(QString::number((int)secHead[i].SizeOfRawData,16));
        this->ui->textEdit->insertPlainText("\n");
        if(!QString::fromStdString(reinterpret_cast<char*>(secHead[i].Name)).compare(".text"))
        {
            this->ui->textEdit->insertPlainText(QString::number(i));
            SetFilePointer(host, (int)secHead[i].PointerToRawData, NULL, FILE_BEGIN);
            num=(int)secHead[i].SizeOfRawData;
        }
    }

        unsigned char s;
        code.push_back(0xC6);
        code.push_back(0x44);
         code.push_back(0x30);
          code.push_back(0xFF);
           code.push_back(0x00);
        for (i = 0; i<num; i++)
        {

            ReadFile(host, &s, 1, &d, NULL);

            code.push_back(s);

        }
}

int MainWindow::disasm()
{
        this->ui->textEdit->clear();
        this->ui->textEdit_2->clear();
        this->ui->textEdit_3->clear();
        int j=1;
        vector<unsigned char> code;
        if(show_file(code)==0)
        {
            return 0;
        }
        length_dis z;
        res_data k;
        Find_helper f;

        int size;
        while (!code.empty())
        {

            size=z.length(code,0);
            if(z.getosize()==1 && z.get_err()!= 1)
            {
               if(f.get_n_tr(k,z)==1)
               {
                  f.get_cl(k,z);
               }
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
