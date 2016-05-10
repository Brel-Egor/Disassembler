
#include <stdio.h>
#include "dl.h"
#include "table_for_ld.h"
//#include <string.h>
#define	F_INVALID		0x01
#define F_PREFIX		0x02
#define	F_REX			0x04
#define F_MODRM			0x08
#define F_SIB			0x10
#define F_DISP			0x20
#define F_IMM			0x40
#define F_RELATIVE		0x80
#define OP_NONE                         0x00
#define OP_INVALID                      0x80

#define OP_DATA_I8                      0x01
#define OP_DATA_I16                     0x02
#define OP_DATA_I16_I32         0x04
#define OP_DATA_I16_I32_I64     0x08
#define OP_EXTENDED                     0x10
#define OP_RELATIVE                     0x20
#define OP_MODRM                        0x40
#define OP_PREFIX                       0x80

length_dis::length_dis()
{
    for (int z = 0; z < 4; z++)
    {
        maspr[z] = 0;
    }
    for (int z = 0; z < 4; z++)
    {
        masop[z] = 0;
    }
    for (int z = 0; z < 4; z++)
    {
        masdis[z] = 0;
    }
    for (int z = 0; z < 8; z++)
    {
        masimm[z] = 0;
    }
    fl_mod = 0;
    fl_sib = 0;
    mod = NULL;
    reg = NULL;
    rm = NULL;
    int i = 0;
    int k = 0;
    flags = NULL;
    error = 0;
    rex = NULL;
    pref = NULL;
    modrm = NULL;
    sib = NULL;
    op_num = 0;
    pref_size = 0;
    opcd_offset = NULL;
    opcd_size = NULL;
    disp_offset = NULL;
    disp_size = NULL;
    imm_offset = NULL;
    imm_size = NULL;
    pr_26 = 0;
    pr_2E = 0;
    pr_36 = 0;
    pr_3E = 0;
    pr_64 = 0;
    pr_65 = 0;
    pr_66 = 0;
    pr_67 = 0;
    pr_F0 = 0;
    pr_F2 = 0;
    pr_F3 = 0;
}

length_dis::~length_dis()
{

}

void length_dis::clear()
{
    for (int z = 0; z < 4; z++)
    {
        maspr[z] = 0;
    }
    for (int z = 0; z < 4; z++)
    {
        masop[z] = 0;
    }
    for (int z = 0; z < 4; z++)
    {
        masdis[z] = 0;
    }
    for (int z = 0; z < 8; z++)
    {
        masimm[z] = 0;
    }
    fl_mod = 0;
    fl_sib = 0;
    mod = NULL;
    reg = NULL;
    rm = NULL;
    int i = 0;
    int k = 0;
    flags = NULL;
    error = 0;
    rex = NULL;
    pref = NULL;
    modrm = NULL;
    sib = NULL;
    op_num = 0;
    pref_size = 0;
    opcd_offset = NULL;
    opcd_size = NULL;
    disp_offset = NULL;
    disp_size = NULL;
    imm_offset = NULL;
    imm_size = NULL;
    pr_26 = 0;
    pr_2E = 0;
    pr_36 = 0;
    pr_3E = 0;
    pr_64 = 0;
    pr_65 = 0;
    pr_66 = 0;
    pr_67 = 0;
    pr_F0 = 0;
    pr_F2 = 0;
    pr_F3 = 0;
}

int length_dis::getprsize()
{
    return pref_size;
}

unsigned char length_dis::one_table(unsigned char op)
{
    return table_1[op];
}

unsigned char length_dis::two_table(unsigned char op)
{
    return table_2[op];
}

unsigned char length_dis::getmodrm()
{
    return modrm;
}

unsigned char length_dis::getsib()
{
    return sib;
}

void length_dis::set_err(int t)
{
   error =t;
}

void length_dis::set_op(unsigned char s)
{
    getop()[0]=s;
}

unsigned int length_dis::length(vector<unsigned char> &code, int is64)
{
    /* phase 1: parse prefixies */
    unsigned char op, f, rexw;
    int s=0,i=0;
    unsigned char *p = code.data();
    while (this->one_table(*p) & OP_PREFIX) {
        switch (*p)
        {
        case 0x66:
            pr_66 = 1;
            this->pr_66 = 1;
            this->pref = *p;
            this->maspr[this->pref_size] = *p;
            break;
        case 0x67:
            pr_67 = 1;
            this->pr_67 = 1;
            this->pref = *p;
            this->maspr[this->pref_size] = *p;
            break;
        case 0x26:
            pr_26 = 1;
            this->pr_26 = 1;
            this->pref = *p;
            this->maspr[this->pref_size] = *p;
            break;
        case 0x2E:
            pr_2E = 1;
            this->pr_2E = 1;
            this->pref = *p;
            this->maspr[this->pref_size] = *p;
            break;
        case 0x36:
            pr_36 = 1;
            this->pr_36 = 1;
            this->pref = *p;
            this->maspr[this->pref_size] = *p;
            break;
        case 0x3E:
            pr_3E = 1;
            this->pr_3E = 1;
            this->pref = *p;
            this->maspr[this->pref_size] = *p;
            break;
        case 0x64:
            pr_64 = 1;
            this->pr_64 = 1;
            this->pref = *p;
            this->maspr[this->pref_size] = *p;
            break;
        case 0x65:
            pr_65 = 1;
            this->pr_65 = 1;
            this->pref = *p;
            this->maspr[this->pref_size] = *p;
            break;
        case 0xF0:
            pr_F0 = 1;
            this->pr_F0 = 1;
            this->pref = *p;
            this->maspr[this->pref_size] = *p;
            break;
        case 0xF2:
            pr_F2 = 1;
            this->pr_F2 = 1;
            this->pref = *p;
            this->maspr[this->pref_size] = *p;
            break;
        case 0xF3:
            pr_F3 = 1;
            this->pr_F3 = 1;
            this->pref = *p;
            this->maspr[this->pref_size] = *p;
            break;
        }

        p++; s++;
        this->flags|= F_PREFIX;
        if (s == 15)
        {
            this->error = 1;
            this->flags |= F_INVALID;
            return s;
        }
        this->pref_size++;
    }
    /* parse REX prefix */
    if (is64 && *p >> 4 == 4) {
        this->rex = *p;
        rexw = (this->rex >> 3) & 1;
        this->flags |= F_REX;
        p++; s++;
    }

    /* can be only one REX prefix */
    if (is64 && *p >> 4 == 4) {
        this->flags |= F_INVALID;
        this->error = 1;
        s++;
        return s;
    }

    /* phase 2: parse opcode */
    this->opcd_offset = (unsigned char)(p - code.data());
    this->opcd_size = 1;
    op = *p++; s++;
    this->op_num++;
    this->masop[i] = op;
    i++;
    /* is 2 byte opcede? */
    if (op == 0x0F)
    {
        op = *p++; s++;
        this->masop[i] = op;
        this->opcd_size++;
        this->op_num++;
        i++;
        f = this->two_table(op);
        if (f & OP_INVALID)
        {
            this->error = 1;
            this->flags |= F_INVALID;
            return s;
        }
        /* for SSE instructions */
        if (f & OP_EXTENDED)
        {
            op = *p++; s++;
            this->opcd_size++;
            this->op_num++;
            this->masop[i] = op;
        }
    }
    else
    {
        f = this->one_table(op);
        /* pr_66 = pr_67 for opcodes A0-A3 */
        if (op >= 0xA0 && op <= 0xA3)
        {
            pr_66 = pr_67;
        }
    }

    /* phase 3: parse ModR/M, SIB and DISP */
    if (f & OP_MODRM)
    {
        this->fl_mod = 1;
        unsigned char mod = (*p >> 6);
        unsigned char ro = (*p & 0x38) >> 3;
        unsigned char rm = (*p & 7);
        this->mod = mod;
        this->reg = ro;
        this->rm = rm;
        this->modrm = *p++; s++;
        this->flags |= F_MODRM;

        /* in F6,F7 opcodes immediate data present if R/O == 0 */
        if (op == 0xF6 && (ro == 0 || ro == 1))
        {
            f |= OP_DATA_I8;
        }
        if (op == 0xF7 && (ro == 0 || ro == 1))
        {
            f |= OP_DATA_I16_I32_I64;
        }

        /* is SIB byte exist? */
        if (mod != 3 && rm == 4 && !(!0 && pr_67))
        {
            this->fl_sib = 1;
            this->sib = *p++;
            s++;
            this->ss = (this->sib >> 6);
            this->index = (this->sib & 0x38) >> 3;
            this->base = (this->sib & 7);
            this->flags |= F_SIB;

            /* if base == 5 and mod == 0 */
            if ((this->sib & 7) == 5 && mod == 0)
            {
                this->disp_size = 4;
            }
        }
        switch (mod) {
        case 0:
            if (0)
            {
                if (rm == 5)
                {
                    this->disp_size = 4;
                    if (0)
                    {
                        this->flags |= F_RELATIVE;
                    }
                }
            }
            else
            {
                if (pr_67)
                {
                    if (rm == 6)
                    {
                        this->disp_size = 2;
                    }
                }
                else
                {
                    if (rm == 5)
                    {
                        this->disp_size = 4;
                    }
                }
            }
            break;
        case 1:
            this->disp_size = 1;
            break;
        case 2:
            if (0)
            {
                this->disp_size = 4;
            }
            else
            {
                if (pr_67)
                {
                    this->disp_size = 2;
                }
                else
                {
                    this->disp_size = 4;
                }
            }
            break;
        }

        if (this->disp_size)
        {
            this->disp_offset = (unsigned char)(p - code.data());
            for (int z = 0; z < this->disp_size; z++)
            {
                this->masdis[z] = *p++;
            }
            s += this->disp_size;
            this->flags |= F_DISP;
        }
    }

    /* phase 4: parse immediate data */
    if (rexw && f & OP_DATA_I16_I32_I64)
    {
        this->imm_size = 8;
    }
    else
    {
        if (f & OP_DATA_I16_I32 || f & OP_DATA_I16_I32_I64)
        {
            this->imm_size = 4 - (pr_66 << 1);
        }
    }
    /* if exist, add OP_DATA_I16 and OP_DATA_I8 size */
    this->imm_size += f & 3;

    if (this->imm_size) {
        for (int z = 0; z < this->imm_size; z++)
        {
            this->masimm[z] = *p++;
        }
        s += this->imm_size;
        this->imm_offset = (unsigned char)(p - code.data());
        this->flags |= F_IMM;
        if (f & OP_RELATIVE)
        {
            this->flags |= F_RELATIVE;
        }
    }
    /* instruction is too long */
    if (s > 15)
    {
        this->error = 1;
        this->flags |= F_INVALID;
    }
    return s;
}

unsigned char* length_dis::getdis()
{
    return masdis;
}

unsigned char* length_dis::getpr()
{
    return maspr;
}

unsigned char* length_dis::getimm()
{
    return masimm;
}

unsigned char* length_dis::getop()
{
    return masop;
}

int length_dis::getdsize()
{
    return disp_size;
}


int length_dis::getisize()
{
    return imm_size;
}

int length_dis::get_err()
{
    return error;
}

int length_dis::getfm()
{
    return fl_mod;
}

int length_dis::getpr66()
{
    return pr_66;
}
int length_dis::getprF2()
{
    return pr_F2;
}
int length_dis::getprF3()
{
    return pr_F3;
}
int length_dis::getfs()
{
    return fl_sib;
}

int length_dis::getosize()
{
    return op_num;
}

unsigned char length_dis::getreg()
{
    return reg;
}

unsigned char length_dis::getmod()
{
    return mod;
}

unsigned char length_dis::getrm()
{
    return rm;
}

unsigned char length_dis::getss()
{
    return ss;
}

unsigned char length_dis::getindex()
{
    return index;
}

unsigned char length_dis::getbase()
{
    return base;
}
