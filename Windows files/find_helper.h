#pragma once
#ifndef FIND_HELPER_H
#define FIND_HELPER_H
#include"res_ins.h"
#include"dl.h"
class Find_helper
{
private:
    map<unsigned char,res_data> tr;
public:
    Find_helper();
    ~Find_helper()
    {

    }
    res_data findop_tr(unsigned char s);
    void get_cl(res_data &t,length_dis &ld);
    int get_n_tr(res_data &t,length_dis &ld);
};

#endif // FIND_HELPER_H
