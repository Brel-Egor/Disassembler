#include"res_ins.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
string res_data::convert_d(length_dis &ld)
{
    int num = ld.getdsize();
    string mas;
    char *converted;
    converted = (char*)malloc((num * 2 + 1)*sizeof(int*));
    for (int i = 0; i < num; i++)
    {
        sprintf(&converted[i * 2], "%02X", (ld.getdis())[i]);
    }

    mas += converted;
    free(converted);
    return  mas;
}

res_data::res_data()
{

}

res_data::~res_data()
{

}


string res_data::convert_i(length_dis &ld)
{
    int num = ld.getisize();
    string mas;
    char *converted;
    converted = (char*)malloc((num * 2 + 1)*sizeof(int*));
    for (int i = 0; i < num; i++)
    {
        sprintf(&converted[i * 2], "%02X", (ld.getimm())[i]);
    }
    mas += converted;
    free(converted);
    return  mas;
}


string res_data::gethex(length_dis &ld)
{
    string s;
    int num = ld.getprsize();
    char *converted;
    if(num!=0)
    {
        converted = (char*)malloc((num * 2 + 1)*sizeof(int*));
        for (int i = 0; i < num; i++)
        {
            sprintf(&converted[i * 2], "%X", (ld.getpr())[i]);
        }
        s+="Prefics:";
        s += converted;
        s+=' ';
        free(converted);
    }

    num = ld.getosize();
    if(num!=0)
    {
        converted = (char*)malloc((num * 2 + 1)*sizeof(int*));
        for (int i = 0; i < num; i++)
        {
            sprintf(&converted[i * 2], "%X", (ld.getop())[i]);
        }
        s+="Opcode:";
        s += converted;
        s+=' ';
        free(converted);
    }
    if(ld.getfm()==1)
    {
        num = 1;
        converted = (char*)malloc((num * 2 + 1)*sizeof(int*));
        for (int i = 0; i < num; i++)
        {
            sprintf(&converted[i * 2], "%X", ld.getmodrm());
        }
        s+="ModR/M:";
        s += converted;
        s+=' ';
        free(converted);
    }
    if(ld.getfs()==1)
    {
        num = 1;
        converted = (char*)malloc((num * 2 + 1)*sizeof(int*));
        for (int i = 0; i < num; i++)
        {
            sprintf(&converted[i * 2], "%X", ld.getsib());
        }
        s+="SIB:";
        s += converted;
        s+=' ';
        free(converted);
    }
    if(ld.getdsize()!=0)
    {
        s+="DISP:";
        s+=convert_d(ld);
        s+=' ';
    }
    if(ld.getisize()!=0)
    {
        s+="IMM:";
        s+=convert_i(ld);
        s+=' ';
    }
    return s;
}

void res_data::clear()
{
    d = -1;
    r = -1;
    ifl = -1;
    fl = -1;
    imm8 = imm16 =imm32 = -1;
    mnem.clear();
    op1.clear();
    op2.clear();
}


void res_data::findop_2(length_dis &ld)
{
    if (ld.get_err() == 1)
    {
        return;
    }
    if (ld.getosize() == 2)
    {
        switch ((ld.getop())[1])
        {
        case           0x0:
            switch (ld.getreg())
            {
            case	       0:       mnem = "SLDT";						break;
            case	       1:		mnem = "STR";						break;
            case	       2:		mnem = "LLDT";						break;
            case	       3:		mnem = "LTR";						break;
            case	       4:		mnem = "VERR";						break;
            case	       5:		mnem = "VERW";						break;
            case	       6:		mnem = "JMPE";                       break;
            }
            break;
        case           0x1:
            switch (ld.getreg())
            {
            case	       0:
                switch ((ld.getop())[2])
                {
                case 0xC1: mnem = "VMCALL"; break;
                case 0xC2: mnem = "VMLAUNCH"; break;
                case 0xC3: mnem = "VMRESUME"; break;
                case 0xC4: mnem = "VMXOFF"; break;
                }
                mnem = "SGDT"; break;
            case	       1:
                switch ((ld.getop())[2])
                {
                case 0xC8: mnem = "MONITOR"; break;
                case 0xC9: mnem = "MWAIT"; break;
                }
                mnem = "SIDT"; break;
            case	       2:
                switch ((ld.getop())[2])
                {
                case 0xD0: mnem = "XGETBV"; break;
                case 0xD1: mnem = "XSETBV"; break;
                }
                mnem = "LGDT"; break;
            case	       3:		mnem = "LIDT";						break;
            case	       4:		mnem = "SMSW";						break;
            case	       6:		mnem = "LMSW";                       break;
            case           7:
                switch ((ld.getop())[2])
                {
                case 0xF9: mnem = "RDTSCP"; break;
                }
                mnem = "INVLPG"; break;
            }
            break;
        case	   0x2:	mnem = "LAR";	break;
        case	   0x3:	mnem = "LSL";	break;
        case	   0x5:	mnem = "LOADALL";	break;
        case	   0x6:	mnem = "CLTS";	break;
        case	   0x7:	mnem = "LOADALL";	break;
        case	   0x8:	mnem = "INVD";	break;
        case	   0x9:	mnem = "WBINVD";	break;
        case	   0x0B:	mnem = "UD2";	break;
        case	   0x0D:	mnem = "NOP";	break;
        case	   0x0E:	mnem = "FEMMS";	break;
        case	   0x11:
            if ((ld.getprF3()) == 1)
            {
                mnem = "MOVSS";	break;
            }
            if ((ld.getprF2()) == 1)
            {
                mnem = "MOVSD";	break;
            }
            if ((ld.getpr66()) == 1)
            {
                mnem = "MOVUPD";	break;
            }
            mnem = "MOVUPS";	break;
        case	   0x10:
            if ((ld.getprF3()) == 1)
            {
                mnem = "MOVSS";	break;
            }
            if ((ld.getprF2()) == 1)
            {
                mnem = "MOVSD";	break;
            }
            if ((ld.getpr66()) == 1)
            {
                mnem = "MOVUPD";	break;
            }
            mnem = "MOVUPS";	break;
        case	   0x12:
            if ((ld.getprF3()) == 1)
            {
                mnem = "MOVSLDUP";	break;
            }
            if ((ld.getprF2()) == 1)
            {
                mnem = "MOVDDUP";	break;
            }
            if ((ld.getpr66()) == 1)
            {
                mnem = "MOVLPD";	break;
            }
            mnem = "MOVLPS";	break;
        case	   0x13:
            if ((ld.getpr66()) == 1)
            {
                mnem = "MOVLPD";	break;
            }
            mnem = "MOVLPS";	break;
        case	   0x14:
            if ((ld.getpr66()) == 1)
            {
                mnem = "UNPCKLPD";	break;
            }
            mnem = "UNPCKLPS";	break;
        case	   0x15:
            if ((ld.getpr66()) == 1)
            {
                mnem = "UNPCKHPD";	break;
            }
            mnem = "UNPCKHPS";	break;
        case	   0x16:
            if ((ld.getprF3()) == 1)
            {
                mnem = "MOVSHDUP";	break;
            }
            if ((ld.getpr66()) == 1)
            {
                mnem = "MOVHPD";	break;
            }
            mnem = "MOVLHPS";	break;
        case	   0x17:
            if ((ld.getpr66()) == 1)
            {
                mnem = "MOVHPD";	break;
            }
            mnem = "MOVHPS";	break;
        case	   0x18:
            switch (ld.getreg())
            {
            case	       0:          mnem = "PREFETCHNTA";						break;
            case	       1: 	mnem = "PREFETCHT0";						break;
            case	       2: 		mnem = "PREFETCHT1";						break;
            case	       3: 	mnem = "PREFETCHT2";						break;
            case	       4: 		mnem = "HINT_NOP";						break;
            case	       5: 		mnem = "HINT_NOP";						break;
            case	       6: 		mnem = "HINT_NOP";						break;
            case	       7: 		mnem = "HINT_NOP";						break;
            }
            break;
        case	   0x19:	mnem = "HINT_NOP";	break;
        case	   0x1A:	mnem = "HINT_NOP";	break;
        case	   0x1B:	mnem = "HINT_NOP";	break;
        case	   0x1C:	mnem = "HINT_NOP";	break;
        case	   0x1D:	mnem = "HINT_NOP";	break;
        case	   0x1E:	mnem = "HINT_NOP";	break;
        case	   0x1F:
            switch (ld.getreg())
            {
            case	       0:          mnem = "NOP";						break;
            case	       1: 	mnem = "HINT_NOP";						break;
            case	       2: 		mnem = "HINT_NOP";						break;
            case	       3: 	mnem = "HINT_NOP";						break;
            case	       4: 		mnem = "HINT_NOP";						break;
            case	       5: 		mnem = "HINT_NOP";						break;
            case	       6: 		mnem = "HINT_NOP";						break;
            case	       7: 		mnem = "HINT_NOP";						break;
            }
            break;
        case	   0x28:
            if ((ld.getpr66()) == 1)
            {
                mnem = "MOVAPD";	break;
            }
            mnem = "MOVAPS";	break;
        case	   0x29:
            if ((ld.getpr66()) == 1)
            {
                mnem = "MOVAPD";	break;
            }
            mnem = "MOVAPS";	break;
        case	   0x2A:
            if ((ld.getprF3()) == 1)
            {
                mnem = "CVTSI2SS";	break;
            }
            if ((ld.getprF2()) == 1)
            {
                mnem = "CVTSI2SD";	break;
            }
            if ((ld.getpr66()) == 1)
            {
                mnem = "CVTPI2PD";	break;
            }
            mnem = "CVTPI2PS";	break;
        case	   0x2B:
            if ((ld.getpr66()) == 1)
            {
                mnem = "MOVNTPD";	break;
            }
            mnem = "MOVNTPS";	break;
        case	   0x2C:
            if ((ld.getprF3()) == 1)
            {
                mnem = "CVTTSS2SI";	break;
            }
            if ((ld.getprF2()) == 1)
            {
                mnem = "CVTTSD2SI";	break;
            }
            if ((ld.getpr66()) == 1)
            {
                mnem = "CVTTPD2PI";	break;
            }
            mnem = "CVTTPS2PI";	break;
        case	   0x2D:
            if ((ld.getprF3()) == 1)
            {
                mnem = "CVTSS2SI";	break;
            }
            if ((ld.getprF2()) == 1)
            {
                mnem = "CVTPD2PI";	break;
            }
            if ((ld.getpr66()) == 1)
            {
                mnem = "CVTSD2SI";	break;
            }
            mnem = "CVTPS2PI";	break;
        case	   0x2E:
            if ((ld.getpr66()) == 1)
            {
                mnem = "UCOMISD";	break;
            }
            mnem = "UCOMISS";	break;
        case	   0x2F:
            if ((ld.getpr66()) == 1)
            {
                mnem = "COMISD";	break;
            }
            mnem = "COMISS";	break;
        case	   0x30:	mnem = "WRMSR";	break;
        case	   0x31:	mnem = "RDTSC";	break;
        case	   0x32:	mnem = "RDMSR";	break;
        case	   0x33:	mnem = "RDPMC";	break;
        case	   0x34:	mnem = "SYSENTER";	break;
        case	   0x35:	mnem = "SYSEXIT";	break;
        case	   0x37:	mnem = "GETSEC";	break;
        case	   0x38:
            switch ((ld.getop())[2])
            {
            case 0x0: mnem = "PSHUFB"; break;
            case 0x1: mnem = "PHADDW"; break;
            case 0x2: mnem = "PHADDD"; break;
            case 0x3: mnem = "PHADDSW"; break;

            case 0x4: mnem = "PMADDUBSW"; break;
            case 0x5: mnem = "PHSUBW"; break;
            case 0x6: mnem = "PHSUBD"; break;
            case 0x7: mnem = "PHSUBSW"; break;
            case 0x8: mnem = "PSIGNB"; break;
            case 0x9: mnem = "PSIGNW"; break;
            case 0x0A: mnem = "PSIGND"; break;
            case 0x0B: mnem = "PMULHRSW"; break;
            case 0x10: mnem = "PBLENDVB"; break;
            case 0x14: mnem = "BLENDVPS"; break;
            case 0x15: mnem = "BLENDVPD"; break;
            case 0x17: mnem = "PTEST"; break;
            case 0x1C: mnem = "PABSB"; break;
            case 0x1D: mnem = "PABSW"; break;
            case 0x1E: mnem = "PABSD"; break;
            case 0x20: mnem = "PMOVSXBW"; break;
            case 0x21: mnem = "PMOVSXBD"; break;
            case 0x22: mnem = "PMOVSXBQ"; break;
            case 0x23: mnem = "PMOVSXWD"; break;
            case 0x24: mnem = "PMOVSXWQ"; break;
            case 0x25: mnem = "PMOVSXDQ"; break;
            case 0x28: mnem = "PMULDQ"; break;
            case 0x29: mnem = "PCMPEQQ"; break;
            case 0x2A: mnem = "MOVNTDQA"; break;
            case 0x2B: mnem = "PACKUSDW"; break;
            case 0x30: mnem = "PMOVZXBW"; break;
            case 0x31: mnem = "PMOVZXBD"; break;
            case 0x32: mnem = "PMOVZXBQ"; break;
            case 0x33: mnem = "PMOVZXWD"; break;
            case 0x34: mnem = "PMOVZXWQ"; break;
            case 0x35: mnem = "PMOVZXDQ"; break;
            case 0x37: mnem = "PCMPGTQ"; break;
            case 0x38: mnem = "PMINSB"; break;
            case 0x39: mnem = "PMINSD"; break;
            case 0x3A: mnem = "PMINUW"; break;
            case 0x3B: mnem = "PMINUD"; break;
            case 0x3C: mnem = "PMAXSB"; break;
            case 0x3D: mnem = "PMAXSD"; break;
            case 0x3E: mnem = "PMAXUW"; break;
            case 0x3F: mnem = "PMAXUD"; break;
            case 0x40: mnem = "PMULLD"; break;
            case 0x41: mnem = "PHMINPOSUW"; break;
            case 0x80: mnem = "INVEPT"; break;
            case 0x81: mnem = "INVVPID"; break;
            case 0xF0:
                if ((ld.getprF2()) == 1)
                {
                    mnem = "crc32"; break;
                }
                mnem = "MOVBE"; break;
            case 0xF1:
                if ((ld.getprF2()) == 1)
                {
                    mnem = "crc32"; break;
                }
                mnem = "MOVBE"; break;
            }mnem = "PSHUFB";	break;
        }
    }

}

string res_data::sib_parse(length_dis &ld)
{
    string s;
    switch (ld.getbase())
    {
    case 0:s = "EAX"; break;
    case 1:s = "ECX"; break;
    case 2:s = "EDX"; break;
    case 3:s = "EBX"; break;
    case 4:s = "ESP"; break;
    case 5:
        if (ld.getmod() == 0)
        {
            break;
        }
        if (ld.getmod() == 1)
        {
            s = "EBP";
            break;
        }
        if (ld.getmod() == 2)
        {
            s = "EBP";
            break;
        }
        break;
    case 6:s = "ESI"; break;
    case 7:s = "EDI"; break;
    }

    switch (ld.getss())
    {
    case 0:
        switch (ld.getindex())
        {
        case 0:s += "+EAX"; break;
        case 1:s += "+ECX"; break;
        case 2:s += "+EDX"; break;
        case 3:s += "+EBX"; break;
        case 4: break;
        case 5:s += "+EBP"; break;
        case 6:s += "+ESI"; break;
        case 7:s += "+EDI"; break;
        }break;
    case 1:
        switch (ld.getindex())
        {
        case 0:s += "+EAX*2"; break;
        case 1:s += "+ECX*2"; break;
        case 2:s += "+EDX*2"; break;
        case 3:s += "+EBX*2"; break;
        case 4: break;
        case 5:s += "+EBP*2"; break;
        case 6:s += "+ESI*2"; break;
        case 7:s += "+EDI*2"; break;
        }break;
    case 2:
        switch (ld.getindex())
        {
        case 0:s += "+EAX*4"; break;
        case 1:s += "+ECX*4"; break;
        case 2:s += "+EDX*4"; break;
        case 3:s += "+EBX*4"; break;
        case 4: break;
        case 5:s += "+EBP*4"; break;
        case 6:s += "+ESI*4"; break;
        case 7:s += "+EDI*4"; break;
        }break;
    case 3:
        switch (ld.getindex())
        {
        case 0:s += "+EAX*8"; break;
        case 1:s += "+ECX*8"; break;
        case 2:s += "+EDX*8"; break;
        case 3:s += "+EBX*8"; break;
        case 4: break;
        case 5:s += "+EBP*8"; break;
        case 6:s += "+ESI*8"; break;
        case 7:s += "+EDI*8"; break;
        }break;

    }
    return s;
}

void res_data::imm(length_dis &ld)
{
    if (fl == 1)
    {
        op2 = convert_i(ld);
        return;
    }
    if (imm8 == 1 || imm16 == 1)
    {
        string s;
        if (ifl == 1)
        {
            op1 = convert_i(ld);
            return;
        }
        op1 = op2;
        op2 = convert_i(ld);
        return;
    }
    if (ld.getisize() != 0)
    {
        op1 = convert_i(ld);
    }
}

void res_data::mod_parse(length_dis &ld)
{
    unsigned char z;
    if(ld.getosize()==1)
    {
        z=(ld.getop())[0];
    }
    else
    {
       z=(ld.getop())[1];
    }
    if (z & 0x01)
        {
            if (ld.getpr66()== 0)
            {
                switch (ld.getmod())
                {
                case 0:
                    switch (ld.getrm())
                    {
                    case 0:
                        op2 = "EAX";
                        break;
                    case 1:
                        op2 = "ECX";
                        break;
                    case 2:
                        op2 = "EDX";
                        break;
                    case 3:
                        op2 = "EBX";
                        break;
                    case 4:
                        op2 = sib_parse(ld);
                        break;
                    case 5:
                        op2 = convert_d(ld);
                        break;
                    case 6:
                        op2 = "ESI";
                        break;
                    case 7:
                        op2 = "EDI";
                        break;
                    }break;
                case 1:
                    switch (ld.getrm())
                    {
                    case 0:
                        op2 = "EAX+" + convert_d(ld);
                        break;
                    case 1:
                        op2 = "ECX+" + convert_d(ld);
                        break;
                    case 2:
                        op2 = "EDX+" + convert_d(ld);
                        break;
                    case 3:
                        op2 = "EBX+" + convert_d(ld);
                        break;
                    case 4:
                        op2 = sib_parse(ld) + convert_d(ld);
                        break;
                    case 5:
                        op2 = "EBP+" + convert_d(ld);
                        break;
                    case 6:
                        op2 = "ESI+" + convert_d(ld);
                        break;
                    case 7:
                        op2 = "EDI+" + convert_d(ld);
                        break;
                    }break;
                case 2:
                    switch (ld.getrm())
                    {
                    case 0:
                        op2 = "EAX+" + convert_d(ld);
                        break;
                    case 1:
                        op2 = "ECX+" + convert_d(ld);
                        break;
                    case 2:
                        op2 = "EDX+" + convert_d(ld);
                        break;
                    case 3:
                        op2 = "EBX+" + convert_d(ld);
                        break;
                    case 4:
                        op2 = sib_parse(ld) + "+" + convert_d(ld);
                        break;
                    case 5:
                        op2 = "EBP+" + convert_d(ld);
                        break;
                    case 6:
                        op2 = "ESI+" + convert_d(ld);
                        break;
                    case 7:
                        op2 = "EDI+" + convert_d(ld);
                        break;
                    }break;
                case 3:
                    switch (ld.getrm())
                    {
                    case 0:
                        op2 = "EAX";
                        break;
                    case 1:
                        op2 = "ECX";
                        break;
                    case 2:
                        op2 = "EDX";
                        break;
                    case 3:
                        op2 = "EBX";
                        break;
                    case 4:
                        op2 = "ESP";
                        break;
                    case 5:
                        op2 = "EBP";
                        break;
                    case 6:
                        op2 = "ESI";
                        break;
                    case 7:
                        op2 = "EDI";
                        break;
                    }
                }
                switch (ld.getreg())
                {
                case 0:op1 = "EAX"; break;
                case 1:op1 = "ECX"; break;
                case 2:op1 = "EDX"; break;
                case 3:op1 = "EBX"; break;
                case 4:op1 = "ESP"; break;
                case 5:op1 = "EBP"; break;
                case 6:op1 = "ESI"; break;
                case 7:op1 = "EDI"; break;
                }
                if (d == 0)
                {
                    string s = op1;
                    op1 = op2;
                    op2 = s;
                }
            }
            else
            {
                switch (ld.getmod())
                {
                case 0:
                    switch (ld.getrm())
                    {
                    case 0:
                        op2 = "AX";
                        break;
                    case 1:
                        op2 = "CX";
                        break;
                    case 2:
                        op2 = "DX";
                        break;
                    case 3:
                        op2 = "BX";
                        break;
                    case 4:
                        op2 = sib_parse(ld);
                        break;
                    case 5:
                        op2 = convert_d(ld);
                        break;
                    case 6:
                        op2 = "SI";
                        break;
                    case 7:
                        op2 = "DI";
                        break;
                    }break;
                case 1:
                    switch (ld.getrm())
                    {
                    case 0:
                        op2 = "AX+" + convert_d(ld);
                        break;
                    case 1:
                        op2 = "CX+" + convert_d(ld);
                        break;
                    case 2:
                        op2 = "DX+" + convert_d(ld);
                        break;
                    case 3:
                        op2 = "BX+" + convert_d(ld);
                        break;
                    case 4:
                        op2 = sib_parse(ld) + convert_d(ld);
                        break;
                    case 5:
                        op2 = "BP+" + convert_d(ld);
                        break;
                    case 6:
                        op2 = "EI+" + convert_d(ld);
                        break;
                    case 7:
                        op2 = "DI+" + convert_d(ld);
                        break;
                    }break;
                case 2:
                    switch (ld.getrm())
                    {
                    case 0:
                        op2 = "AX+" + convert_d(ld);
                        break;
                    case 1:
                        op2 = "CX+" + convert_d(ld);
                        break;
                    case 2:
                        op2 = "DX+" + convert_d(ld);
                        break;
                    case 3:
                        op2 = "BX+" + convert_d(ld);
                        break;
                    case 4:
                        op2 = sib_parse(ld) + "+" + convert_d(ld);
                        break;
                    case 5:
                        op2 = "BP+" + convert_d(ld);
                        break;
                    case 6:
                        op2 = "SI+" + convert_d(ld);
                        break;
                    case 7:
                        op2 = "DI+" + convert_d(ld);
                        break;
                    }break;
                case 3:
                    switch (ld.getrm())
                    {
                    case 0:
                        op2 = "AX";
                        break;
                    case 1:
                        op2 = "CX";
                        break;
                    case 2:
                        op2 = "DX";
                        break;
                    case 3:
                        op2 = "BX";
                        break;
                    case 4:
                        op2 = "SP";
                        break;
                    case 5:
                        op2 = "BP";
                        break;
                    case 6:
                        op2 = "SI";
                        break;
                    case 7:
                        op2 = "DI";
                        break;
                    }
                }
                switch (ld.getreg())
                {
                case 0:op1 = "AX"; break;
                case 1:op1 = "CX"; break;
                case 2:op1 = "DX"; break;
                case 3:op1 = "BX"; break;
                case 4:op1 = "SP"; break;
                case 5:op1 = "BP"; break;
                case 6:op1 = "SI"; break;
                case 7:op1 = "DI"; break;
                }
                if (d == 0)
                {
                    string s = op1;
                    op1 = op2;
                    op2 = s;
                }
            }
        }
        else {
            switch (ld.getmod())
            {
            case 0:
                switch (ld.getrm())
                {
                case 0:
                    op2 = "EAX";
                    break;
                case 1:
                    op2 = "ECX";
                    break;
                case 2:
                    op2 = "EDX";
                    break;
                case 3:
                    op2 = "EBX";
                    break;
                case 4:
                    op2 = sib_parse(ld);
                    break;
                case 5:
                    op2 = convert_d(ld);
                    break;
                case 6:
                    op2 = "ESI";
                    break;
                case 7:
                    op2 = "EDI";
                    break;
                }break;
            case 1:
                switch (ld.getrm())
                {
                case 0:
                    op2 = "EAX+" + convert_d(ld);
                    break;
                case 1:
                    op2 = "ECX+" + convert_d(ld);
                    break;
                case 2:
                    op2 = "EDX+" + convert_d(ld);
                    break;
                case 3:
                    op2 = "EBX+" + convert_d(ld);
                    break;
                case 4:
                    op2 = sib_parse(ld) + convert_d(ld);
                    break;
                case 5:
                    op2 = "EBP+" + convert_d(ld);
                    break;
                case 6:
                    op2 = "ESI+" + convert_d(ld);
                    break;
                case 7:
                    op2 = "EDI+" + convert_d(ld);
                    break;
                }break;
            case 2:
                switch (ld.getrm())
                {
                case 0:
                    op2 = "EAX+" + convert_d(ld);
                    break;
                case 1:
                    op2 = "ECX+" + convert_d(ld);
                    break;
                case 2:
                    op2 = "EDX+" + convert_d(ld);
                    break;
                case 3:
                    op2 = "EBX+" + convert_d(ld);
                    break;
                case 4:
                    op2 = sib_parse(ld) + "+" + convert_d(ld);
                    break;
                case 5:
                    op2 = "EBP+" + convert_d(ld);
                    break;
                case 6:
                    op2 = "ESI+" + convert_d(ld);
                    break;
                case 7:
                    op2 = "EDI+" + convert_d(ld);
                    break;
                }break;
            case 3:
                switch (ld.getrm())
                {
                case 0:
                    op2 = "EAX";
                    break;
                case 1:
                    op2 = "ECX";
                    break;
                case 2:
                    op2 = "EDX";
                    break;
                case 3:
                    op2 = "EBX";
                    break;
                case 4:
                    op2 = "ESP";
                    break;
                case 5:
                    op2 = "EBP";
                    break;
                case 6:
                    op2 = "ESI";
                    break;
                case 7:
                    op2 = "EDI";
                    break;
                }
            }
            switch (ld.getreg())
            {
            case 0:op1 = "AL"; break;
            case 1:op1 = "CL"; break;
            case 2:op1 = "DL"; break;
            case 3:op1 = "BL"; break;
            case 4:op1 = "AH"; break;
            case 5:op1 = "CH"; break;
            case 6:op1 = "DH"; break;
            case 7:op1 = "BH"; break;
            }
            if (d == 0)
            {
                string s = op1;
                op1 = op2;
                op2 = s;
            }
        }
}


string res_data::get_mnem()
{
    return mnem;
}

string res_data::get_op1()
{
    return op1;
}

string res_data::get_op2()
{
    return op2;
}

void res_data::set_r(int t)
{
    r=t;
}
void res_data::set_d(int t)
{
    d=t;
}
void res_data::set_ifl(int t)
{
    ifl=t;
}
void res_data::set_fl(int t)
{
    fl=t;
}
void res_data::set_imm8(int t)
{
    imm8=t;
}

void res_data::set_imm16(int t)
{
    imm16=t;
}
void res_data::set_imm32(int t)
{
    imm32=t;
}
void res_data::set_mnem(string t)
{
    mnem=t;
}

void res_data::set_op1(string t)
{
   op1=t;
}
void res_data::set_op2(string t)
{
    op2=t;
}
