#pragma once
#include <map>
#include"dl.h"
#include<string>
using namespace std;
class res_data
{
protected:
    int r;
    int	d;
    int ifl;
    int fl;
    int imm8;
    int imm16;
    int imm32;
    string mnem;
    string op1;
    string op2;
public:
    res_data();
    void clear();
    void imm(length_dis &ld);
    string get_mnem();
    string get_op1();
    string get_op2();
    string sib_parse(length_dis &ld);
    string convert_d(length_dis &ld);
    string convert_i(length_dis &ld);
    string gethex(length_dis &ld);
    void findop_2(length_dis &ld);
    void mod_parse(length_dis &ld);          
    void set_r(int t);
    void set_d(int t);
    void set_ifl(int t);
    void set_fl(int t);
    void set_imm8(int t);
    void set_imm16(int t);
    void set_imm32(int t);
    void set_mnem(string t);
    void set_op1(string t);
    void set_op2(string t);
    ~res_data();
};
