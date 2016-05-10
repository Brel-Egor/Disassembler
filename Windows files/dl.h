
#ifndef _LengthDASM_
#define _LengthDASM_
#include <string>
#include <vector>
using namespace std;

class length_dis
{
protected:
    string dis;
    unsigned char		flags;
    int error;
    unsigned char maspr[11];
    unsigned char masop[4];
    unsigned char masdis[8];
    unsigned char masimm[8];
    int pref_size;
    int op_num;
    int fl_mod;
    int fl_sib;
    unsigned char		rex;
    unsigned char		pref;
    unsigned char		modrm;
    unsigned char		sib;
    unsigned char		opcd_offset;
    unsigned char	opcd_size;
    unsigned char		disp_offset;
    int		disp_size;
    unsigned char		imm_offset;
    int		imm_size;
    unsigned char	 mod;
    unsigned char	 reg;
    unsigned char	 rm;
    unsigned char	 ss;
    unsigned char	 index;
    unsigned char	 base;
    int pr_26;
    int pr_2E;
    int pr_36;
    int pr_3E;
    int pr_64;
    int pr_65;
    int pr_66;
    int pr_67;
    int pr_F0;
    int pr_F2;
    int pr_F3;
public:
    length_dis();
    int get_err();
    void set_err(int t);
    unsigned char* getdis();
    unsigned char* getimm();
    unsigned char* getop();
    unsigned char* getpr();
    int getdsize();
    void set_op(unsigned char s);
    int getisize();
    int getosize();
    int getprsize();
    int getpr66();
    int getprF2();
    int getprF3();
    unsigned char getreg();
    unsigned char getmod();
    unsigned char getrm();
    unsigned char getss();
    unsigned char getindex();
    unsigned char getbase();
    int getfm();
    int getfs();
    unsigned char getmodrm();
    unsigned char getsib();
    void clear();
    unsigned int length(vector<unsigned char> &code, int is64);
    unsigned char one_table(unsigned char opcode);
    unsigned char two_table(unsigned char opcode);
    ~length_dis();
};

#endif /* _LDASM_ */
