#include "find_helper.h"

Find_helper::Find_helper()
{
    unsigned char s = 0x00;

    for (int i = 0; i < 235; i++)
    {
        switch (s)
        {
        case 0x80:
            s=s+4;
            break;
        case 0xC0:
            s=s+2;
            break;
        case 0xD0:
            s=s+3;
            break;
        case 0xD8:
            s=s+8;
            break;
        case 0xF6:
            s=s+2;
            break;
        case 0xFF:
            s=s+2;
            break;
        }


        tr.insert(make_pair(s, res_data(findop_tr(s))));
        s++;
    }
}

res_data Find_helper::findop_tr(unsigned char s)
{
    res_data t;
    t.clear();
    switch (s)
            {
            case 0x80:
                s=s+4;
                break;
            case 0xC0:
                s=s+2;
                break;
            case 0xD0:
                s=s+3;
                break;
            case 0xD8:
                s=s+8;
                break;
            case 0xF6:
                s=s+2;
                break;
            case 0xFF:
                s=s+2;
                break;
            }
    switch (s)
                {
                    case	0x0:		t.set_mnem( "ADD");	t.set_d( (s& 0x02) >> 1);				break;
                    case	       0x1:		t.set_mnem( "ADD");	t.set_d( (s& 0x02) >> 1);				break;
                    case	       0x2:		t.set_mnem( "ADD");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x3:		t.set_mnem( "ADD");	t.set_d( (s& 0x02) >> 1);				break;
                    case	       0x4:		t.set_mnem( "ADD");		t.set_op1( "AL");	t.set_imm8( 1);			break;
                    case	       0x5:		t.set_mnem( "ADD");		t.set_op1( "EAX");	t.set_imm16( 1); t.set_imm32( 1);			break;
                    case	       0x6:		t.set_mnem( "PUSH");		t.set_op1( "ES");				break;
                    case	       0x7:		t.set_mnem( "POP");		t.set_op1( "ES");				break;
                    case	       0x8:		t.set_mnem( "OR");		t.set_d( (s& 0x02) >> 1);				break;
                    case	       0x9:		t.set_mnem( "OR");		t.set_d( (s& 0x02) >> 1);				break;
                    case	       0x0A:		t.set_mnem( "OR");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x0B:		t.set_mnem( "OR");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x0C:		t.set_mnem( "OR");		t.set_op1( "AL");	t.set_imm8( 1);			break;
                    case	       0x0D:		t.set_mnem( "OR");		t.set_op1( "EAX");	t.set_imm16( 1); t.set_imm32( 1);			break;
                    case	       0x0E:		t.set_mnem( "PUSH");		t.set_op1( "CS");				break;
                    case	       0x10:		t.set_mnem( "ADC"); t.set_d( (s& 0x02) >> 1);						break;
                    case	       0x11:		t.set_mnem( "ADC");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x12:		t.set_mnem( "ADC");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x13:		t.set_mnem( "ADC");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x14:		t.set_mnem( "ADC");		t.set_op1( "AL");	t.set_imm8( 1);			break;
                    case	       0x15:		t.set_mnem( "ADC");		t.set_op1( "EAX");	t.set_imm16( 1); t.set_imm32( 1);			break;
                    case	       0x16:		t.set_mnem( "PUSH");		t.set_op1( "SS");				break;
                    case	       0x17:		t.set_mnem( "POP");		t.set_op1( "SS");				break;
                    case	       0x18:		t.set_mnem( "SBB"); t.set_d( (s& 0x02) >> 1);						break;
                    case	       0x19:		t.set_mnem( "SBB"); t.set_d( (s& 0x02) >> 1);						break;
                    case	       0x1A:		t.set_mnem( "SBB");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x1B:		t.set_mnem( "SBB");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x1C:		t.set_mnem( "SBB");		t.set_op1( "AL");	t.set_imm8( 1);			break;
                    case	       0x1D:		t.set_mnem( "SBB");		t.set_op1( "EAX");	t.set_imm16( 1); t.set_imm32( 1);			break;
                    case	       0x1E:		t.set_mnem( "PUSH");		t.set_op1( "DS");				break;
                    case	       0x1F:		t.set_mnem( "POP");		t.set_op1( "DS");				break;
                    case	       0x20:		t.set_mnem( "AND"); t.set_d( (s& 0x02) >> 1);						break;
                    case	       0x21:		t.set_mnem( "AND"); t.set_d( (s& 0x02) >> 1);						break;
                    case	       0x22:		t.set_mnem( "AND");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x23:		t.set_mnem( "AND");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x24:		t.set_mnem( "AND");		t.set_op1( "AL");	t.set_imm8( 1);			break;
                    case	       0x25:		t.set_mnem( "AND");		t.set_op1( "EAX");	t.set_imm16( 1); t.set_imm32( 1);			break;
                    case	       0x27:		t.set_mnem( "DAA");						break;
                    case	       0x28:		t.set_mnem( "SUB"); t.set_d( (s& 0x02) >> 1);						break;
                    case	       0x29:		t.set_mnem( "SUB");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x2A:		t.set_mnem( "SUB");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x2B:		t.set_mnem( "SUB");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x2C:		t.set_mnem( "SUB");		t.set_op1( "AL");	t.set_imm8( 1);			break;
                    case	       0x2D:		t.set_mnem( "SUB");		t.set_op1( "EAX");	t.set_imm16( 1); t.set_imm32( 1);			break;
                    case	       0x2F:		t.set_mnem( "DAS");						break;
                    case	       0x30:		t.set_mnem( "XOR");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x31:		t.set_mnem( "XOR");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x32:		t.set_mnem( "XOR");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x33:		t.set_mnem( "XOR");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x34:		t.set_mnem( "XOR");		t.set_op1( "AL");	t.set_imm8( 1);			break;
                    case	       0x35:		t.set_mnem( "XOR");		t.set_op1( "EAX");	t.set_imm16( 1); t.set_imm32( 1);			break;
                    case	       0x37:		t.set_mnem( "AAA");						break;
                    case	       0x38:		t.set_mnem( "CMP");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x39:		t.set_mnem( "CMP");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x3A:		t.set_mnem( "CMP");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x3B:		t.set_mnem( "CMP");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x3C:		t.set_mnem( "CMP");		t.set_op1( "AL");	t.set_imm8( 1);			break;
                    case	       0x3D:		t.set_mnem( "CMP");		t.set_op1( "EAX");	t.set_imm16( 1); t.set_imm32( 1);			break;
                    case	       0x3F:		t.set_mnem( "AAS");		t.set_op1( "AL");	t.set_op2( "AH");			break;
                    case	  0x40:		t.set_mnem( "INC");		t.set_op1( "EAX");				break;
                    case	  0x41:		t.set_mnem( "INC");		t.set_op1( "ECX");				break;
                    case	  0x42:		t.set_mnem( "INC");		t.set_op1( "EDX");				break;
                    case	  0x43:		t.set_mnem( "INC");		t.set_op1( "EBX");				break;
                    case	  0x44:		t.set_mnem( "INC");		t.set_op1( "ESP");				break;
                    case	  0x45:		t.set_mnem( "INC");		t.set_op1( "EBP");				break;
                    case	  0x46:		t.set_mnem( "INC");		t.set_op1( "ESI");				break;
                    case	  0x47:		t.set_mnem( "INC");		t.set_op1( "EDI");				break;
                    case	  0x48:		t.set_mnem( "DEC");		t.set_op1( "EAX");				break;
                    case	  0x49:		t.set_mnem( "DEC");		t.set_op1( "ECX");				break;
                    case	  0x4A:		t.set_mnem( "DEC");		t.set_op1( "EDX");				break;
                    case	  0x4B:		t.set_mnem( "DEC");		t.set_op1( "EBX");				break;
                    case	  0x4C:		t.set_mnem( "DEC");		t.set_op1( "ESP");				break;
                    case	  0x4D:		t.set_mnem( "DEC");		t.set_op1( "EBP");				break;
                    case	  0x4E:		t.set_mnem( "DEC");		t.set_op1( "ESI");				break;
                    case	  0x4F:		t.set_mnem( "DEC");		t.set_op1( "EDI");				break;
                    case	  0x50:		t.set_mnem( "PUSH");		t.set_op1( "EAX");				break;
                    case	  0x51:		t.set_mnem( "PUSH");		t.set_op1( "ECX");				break;
                    case	  0x52:		t.set_mnem( "PUSH");		t.set_op1( "EDX");				break;
                    case	  0x53:		t.set_mnem( "PUSH");		t.set_op1( "EBX");				break;
                    case	  0x54:		t.set_mnem( "PUSH");		t.set_op1( "ESP");				break;
                    case	  0x55:		t.set_mnem( "PUSH");		t.set_op1( "EBP");				break;
                    case	  0x56:		t.set_mnem( "PUSH");		t.set_op1( "ESI");				break;
                    case	  0x57:		t.set_mnem( "PUSH");		t.set_op1( "EDI");				break;
                    case	  0x58:		t.set_mnem( "POP");		t.set_op1( "EAX");				break;
                    case	  0x59:		t.set_mnem( "POP");		t.set_op1( "ECX");				break;
                    case	  0x5A:		t.set_mnem( "POP");		t.set_op1( "EDX");				break;
                    case	  0x5B:		t.set_mnem( "POP");		t.set_op1( "EBX");				break;
                    case	  0x5C:		t.set_mnem( "POP");		t.set_op1( "ESP");				break;
                    case	  0x5D:		t.set_mnem( "POP");		t.set_op1( "EBP");				break;
                    case	  0x5E:		t.set_mnem( "POP");		t.set_op1( "ESI");				break;
                    case	  0x5F:		t.set_mnem( "POP");		t.set_op1( "EDI");				break;
                    case	       0x60:		t.set_mnem( "PUSHA");						break;
                    case	       0x61:		t.set_mnem( "POPA");						break;
                    case	       0x62:		t.set_mnem( "BOUND");						break;
                    case	       0x63:		t.set_mnem( "ARPL");						break;
                    case	       0x68:		t.set_mnem( "PUSH");		t.set_imm16( 1); t.set_imm32( 1);	t.set_ifl( 1);			break;
                    case	       0x69:		t.set_mnem( "IMUL");		t.set_ifl( 3);		t.set_imm16( 1); t.set_imm32( 1);		break;
                    case	       0x6A:		t.set_mnem( "PUSH");		t.set_imm8( 1);	t.set_ifl( 1);			break;
                    case	       0x6B:		t.set_mnem( "IMUL");		t.set_imm8( 1);	t.set_ifl( 3);			break;
                    case	       0x6C:		t.set_mnem( "INS");		t.set_op2( "DX");				break;
                    case	       0x6D:		t.set_mnem( "INS");		t.set_op2( "DX");				break;
                    case	       0x6E:		t.set_mnem( "OUTS");		t.set_op1( "DX");				break;
                    case	       0x6F:		t.set_mnem( "OUTS");		t.set_op1( "DX");				break;
                    case	       0x70:		t.set_mnem( "JO");						break;
                    case	       0x71:		t.set_mnem( "JNO");						break;
                    case	       0x72:		t.set_mnem( "JB");						break;
                    case	       0x73:		t.set_mnem( "JNB");						break;
                    case	       0x74:		t.set_mnem( "JZ");						break;
                    case	       0x75:		t.set_mnem( "JNZ");						break;
                    case	       0x76:		t.set_mnem( "JBE");						break;
                    case	       0x77:		t.set_mnem( "JNBE");						break;
                    case	       0x78:		t.set_mnem( "JS");						break;
                    case	       0x79:		t.set_mnem( "JNS");						break;
                    case	       0x7A:		t.set_mnem( "JP");						break;
                    case	       0x7B:		t.set_mnem( "JNP");						break;
                    case	       0x7C:		t.set_mnem( "JL");						break;
                    case	       0x7D:		t.set_mnem( "JNL");						break;
                    case	       0x7E:		t.set_mnem( "JLE");						break;
                    case	       0x7F:		t.set_mnem( "JNLE");						break;
                    case	       0x84:		t.set_mnem( "TEST");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x85:		t.set_mnem( "TEST");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x86:		t.set_mnem( "XCHG");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x87:		t.set_mnem( "XCHG");	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x88:		t.set_mnem( "MOV");	   t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x89:		t.set_mnem( "MOV");	   t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x8A:		t.set_mnem( "MOV");  	t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x8B:		t.set_mnem( "MOV");	    t.set_d( (s& 0x02) >> 1);					break;
                    case	       0x8C:		t.set_mnem( "MOV");						break;
                    case	       0x8D:		t.set_mnem( "LEA");						break;
                    case	       0x8E:		t.set_mnem( "MOV");						break;
                    case	       0x8F:		t.set_mnem( "POP");						break;
                    case	       0x90:		t.set_mnem( "NOP");						break;
                    case	       0x91:		t.set_mnem( "XCHG");		t.set_op1( "EAX");	t.set_op2( "ECX");			break;
                    case	       0x92:		t.set_mnem( "XCHG");		t.set_op1( "EAX");	t.set_op2( "EDX");			break;
                    case	       0x93:		t.set_mnem( "XCHG");		t.set_op1( "EAX");	t.set_op2( "EBX");			break;
                    case	       0x94:		t.set_mnem( "XCHG");		t.set_op1( "EAX");	t.set_op2( "ESP");			break;
                    case	       0x95:		t.set_mnem( "XCHG");		t.set_op1( "EAX");	t.set_op2( "EBP");			break;
                    case	       0x96:		t.set_mnem( "XCHG");		t.set_op1( "EAX");	t.set_op2( "ESI");			break;
                    case	       0x97:		t.set_mnem( "XCHG");		t.set_op1( "EAX");	t.set_op2( "EDI");			break;
                    case	       0x98:		t.set_mnem( "CBW");						break;
                    case	       0x99:		t.set_mnem( "CWD");						break;
                    case	       0x9A:		t.set_mnem( "CALLF");						break;
                    case	       0x9B:		t.set_mnem( "WAIT");						break;
                    case	       0x9C:		t.set_mnem( "PUSHF");						break;
                    case	       0x9D:		t.set_mnem( "POPF");						break;
                    case	       0x9E:		t.set_mnem( "SAHF");						break;
                    case	       0x9F:		t.set_mnem( "LAHF");						break;
                    case	       0xA0:		t.set_mnem( "MOV");		t.set_op1( "AL");			break;
                    case	       0xA1:		t.set_mnem( "MOV");		t.set_op1( "EAX");			break;
                    case	       0xA2:		t.set_mnem( "MOV");		t.set_op2( "AL");		break;
                    case	       0xA3:		t.set_mnem( "MOV");		t.set_op2( "EAX");			break;
                    case	       0xA4:		t.set_mnem( "MOVSB");						break;
                    case	       0xA5:		t.set_mnem( "MOVSW");						break;
                    case	       0xA6:		t.set_mnem( "CMPSB");						break;
                    case	       0xA7:		t.set_mnem( "CMPSW");						break;
                    case	       0xA8:		t.set_mnem( "TEST");		t.set_op1( "AL");	t.set_imm8( 1);			break;
                    case	       0xA9:		t.set_mnem( "TEST");		t.set_op1( "EAX");	t.set_imm16( 1); t.set_imm32( 1);			break;
                    case	       0xAA:		t.set_mnem( "STOSB");		break;
                    case	       0xAB:		t.set_mnem( "STOSW");						break;
                    case	       0xAC:		t.set_mnem( "LODSB");						break;
                    case	       0xAD:		t.set_mnem( "LODSW");						break;
                    case	       0xAE:		t.set_mnem( "SCASB");						break;
                    case	       0xAF:		t.set_mnem( "SCASW");						break;
                    case	       0xB0:		t.set_mnem( "MOV");		t.set_op1( "AL"); t.set_imm8( 1);	t.set_fl( 1);			break;
                    case	       0xB1:		t.set_mnem( "MOV");		t.set_op1( "CL"); t.set_imm8( 1);	t.set_fl( 1);			break;
                    case	       0xB2:		t.set_mnem( "MOV");		t.set_op1( "DL"); t.set_imm8( 1);	t.set_fl( 1);			break;
                    case	       0xB3:		t.set_mnem( "MOV");		t.set_op1( "BL"); t.set_imm8( 1);	t.set_fl( 1);			break;
                    case	       0xB4:		t.set_mnem( "MOV");		t.set_op1( "AH"); t.set_imm8( 1);	t.set_fl( 1);			break;
                    case	       0xB5:		t.set_mnem( "MOV");		t.set_op1( "CH"); t.set_imm8( 1);	t.set_fl( 1);			break;
                    case	       0xB6:		t.set_mnem( "MOV");		t.set_op1( "DH"); t.set_imm8( 1);	t.set_fl( 1);			break;
                    case	       0xB7:		t.set_mnem( "MOV");		t.set_op1( "BH"); t.set_imm8( 1);	t.set_fl( 1);			break;
                    case	       0xB8:		t.set_mnem( "MOV");     	t.set_op1( "EAX");	t.set_imm16( 1); t.set_imm32( 1);		t.set_fl( 1);		break;
                    case	       0xB9:		t.set_mnem( "MOV");		t.set_op1( "ECX"); t.set_imm16( 1); t.set_imm32( 1);		t.set_fl( 1);		break;
                    case	       0xBA:		t.set_mnem( "MOV");		t.set_op1( "EDX"); t.set_imm16( 1); t.set_imm32( 1);		t.set_fl( 1);		break;
                    case	       0xBB:		t.set_mnem( "MOV");		t.set_op1( "EBX"); t.set_imm16( 1); t.set_imm32( 1);		t.set_fl( 1);		break;
                    case	       0xBC:		t.set_mnem( "MOV");		t.set_op1( "ESP"); t.set_imm16( 1); t.set_imm32( 1);		t.set_fl( 1);		break;
                    case	       0xBD:		t.set_mnem( "MOV");		t.set_op1( "EBP"); t.set_imm16( 1); t.set_imm32( 1);		t.set_fl( 1);		break;
                    case	       0xBE:		t.set_mnem( "MOV");		t.set_op1( "ESI"); t.set_imm16( 1); t.set_imm32( 1);		t.set_fl( 1);		break;
                    case	       0xBF:		t.set_mnem( "MOV");		t.set_op1( "EDI");  t.set_imm16( 1); t.set_imm32( 1);	t.set_fl( 1);			break;

                    case	       0xC2:		t.set_mnem( "RETN");		t.set_imm16( 1); t.set_ifl( 1);				break;
                    case	       0xC3:		t.set_mnem( "RETN");						break;
                    case	       0xC4:		t.set_mnem( "LES");						break;
                    case	       0xC5:		t.set_mnem( "LDS");						break;
                    case	       0xC6:		t.set_mnem( "MOV");		t.set_imm8( 1);				break;
                    case	       0xC7:		t.set_mnem( "MOV");		t.set_imm16( 1); t.set_imm32( 1);				break;
                    case	       0xC8:		t.set_mnem( "ENTER");						break;
                    case	       0xC9:		t.set_mnem( "LEAVE");						break;
                    case	       0xCA:		t.set_mnem( "RETF");						break;
                    case	       0xCB:		t.set_mnem( "RETF");						break;
                    case	       0xCC:		t.set_mnem( "INT 3");						break;
                    case	       0xCD:		t.set_mnem( "INT");		t.set_imm8( 1); t.set_ifl( 1);				break;
                    case	       0xCE:		t.set_mnem( "INTO");						break;
                    case	       0xCF:		t.set_mnem( "IRET");						break;

                    case	       0xD4:		t.set_mnem( "AMX");						break;
                    case	       0xD5:		t.set_mnem( "ADX");						break;
                    case	       0xD6:		t.set_mnem( "SALC");						break;

                    case	       0xD7:		t.set_mnem( "XLAT");						break;


                    case	       0xE0:		t.set_mnem( "LOOPNE");						break;
                    case	       0xE1:		t.set_mnem( "LOOPE");						break;
                    case	       0xE2:		t.set_mnem( "LOOP");						break;
                    case	       0xE3:		t.set_mnem( "JECXZ");						break;
                    case	       0xE4:		t.set_mnem( "IN");						break;
                    case	       0xE5:		t.set_mnem( "IN");						break;
                    case	       0xE6:		t.set_mnem( "OUT");						break;
                    case	       0xE7:		t.set_mnem( "OUT");						break;
                    case	       0xE8:		t.set_mnem( "CALL");						break;
                    case	       0xE9:		t.set_mnem( "JMP");						break;
                    case	       0xEA:		t.set_mnem( "JMPF");						break;
                    case	       0xEB:		t.set_mnem( "JMP");						break;
                    case	       0xEC:		t.set_mnem( "IN");						break;
                    case	       0xED:		t.set_mnem( "IN");						break;
                    case	       0xEE:		t.set_mnem( "OUT");						break;
                    case	       0xEF:		t.set_mnem( "OUT");						break;
                    case	       0xF1:		t.set_mnem( "INT1");						break;
                    case	       0xF4:		t.set_mnem( "HLT");						break;
                    case	       0xF5:		t.set_mnem( "CMC");						break;

                    case	       0xF8:		t.set_mnem( "CLC");						break;
                    case	       0xF9:		t.set_mnem( "STC");						break;
                    case	       0xFA:		t.set_mnem( "CLI");						break;
                    case	       0xFB:		t.set_mnem( "STI");						break;
                    case	       0xFC:		t.set_mnem( "CLD");						break;
                    case	       0xFD:		t.set_mnem( "STD");						break;

                    }


        return t;

    }

void Find_helper::get_cl(res_data &s,length_dis &ld)
{
    s=tr.find(ld.getop()[0])->second;
}

int Find_helper::get_n_tr(res_data &s,length_dis &ld)
{
    if(ld.getosize()>1)
    {
        return 1;
    }
    switch ((ld.getop())[0])
    {
    case	       0x80:
                    switch (ld.getreg())
                    {
                    case	       0: s.set_imm8(1);          s.set_mnem("ADD");						break;
                    case	       1: s.set_imm8(1);		s.set_mnem("OR");						break;
                    case	       2: s.set_imm8(1);		s.set_mnem("ADC");						break;
                    case	       3: s.set_imm8(1);		s.set_mnem("SBB");						break;
                    case	       4: s.set_imm8(1);		s.set_mnem("AND");						break;
                    case	       5: s.set_imm8(1);		s.set_mnem("SUB");						break;
                    case	       6: s.set_imm8(1);		s.set_mnem("XOR");						break;
                    case	       7: s.set_imm8(1);		s.set_mnem("CMP");						break;
                    }
                    break;
                case           0x81:
                    switch (ld.getreg())
                    {
                    case	       0:s.set_imm16(1); s.set_imm32(1);          s.set_mnem("ADD");						break;
                    case	       1:s.set_imm16(1); s.set_imm32(1);		s.set_mnem("OR");						break;
                    case	       2:s.set_imm16(1); s.set_imm32(1);		s.set_mnem("ADC");						break;
                    case	       3:s.set_imm16(1); s.set_imm32(1);		s.set_mnem("SBB");						break;
                    case	       4:s.set_imm16(1); s.set_imm32(1);		s.set_mnem("AND");						break;
                    case	       5:s.set_imm16(1); s.set_imm32(1);		s.set_mnem("SUB");						break;
                    case	       6:s.set_imm16(1); s.set_imm32(1);		s.set_mnem("XOR");						break;
                    case	       7:s.set_imm16(1); s.set_imm32(1);		s.set_mnem("CMP");						break;
                    }
                    break;
                case           0x82:
                    switch (ld.getreg())
                    {
                    case	       0: s.set_imm8(1);         s.set_mnem("ADD");						break;
                    case	       1:s.set_imm8(1);		s.set_mnem("OR");						break;
                    case	       2:s.set_imm8(1);		s.set_mnem("ADC");						break;
                    case	       3:s.set_imm8(1);		s.set_mnem("SBB");						break;
                    case	       4:s.set_imm8(1);		s.set_mnem("AND");						break;
                    case	       5:s.set_imm8(1);		s.set_mnem("SUB");						break;
                    case	       6:s.set_imm8(1);		s.set_mnem("XOR");						break;
                    case	       7:s.set_imm8(1);		s.set_mnem("CMP");						break;
                    }
                    break;
                case           0x83:
                    switch (ld.getreg())
                    {
                    case	       0:s.set_imm8(1);          s.set_mnem("ADD");						break;
                    case	       1:s.set_imm8(1);		s.set_mnem("OR");						break;
                    case	       2:s.set_imm8(1);		s.set_mnem("ADC");						break;
                    case	       3:s.set_imm8(1);		s.set_mnem("SBB");						break;
                    case	       4:s.set_imm8(1);		s.set_mnem("AND");						break;
                    case	       5:s.set_imm8(1);		s.set_mnem("SUB");						break;
                    case	       6:s.set_imm8(1);		s.set_mnem("XOR");						break;
                    case	       7:s.set_imm8(1);		s.set_mnem("CMP");						break;
                    }
                    break;
                case           0xC0:
                    switch (ld.getreg())
                    {
                    case	       0:s.set_imm8(1);          s.set_mnem("ROL");						break;
                    case	       1:s.set_imm8(1);		s.set_mnem("ROR");						break;
                    case	       2:s.set_imm8(1);		s.set_mnem("RCL");						break;
                    case	       3:s.set_imm8(1);		s.set_mnem("RCR");						break;
                    case	       4:s.set_imm8(1);		s.set_mnem("SAL");						break;
                    case	       5:s.set_imm8(1);		s.set_mnem("SHR");						break;
                    case	       6:s.set_imm8(1);		s.set_mnem("SHL");						break;
                    case	       7:s.set_imm8(1);		s.set_mnem("SAR");						break;
                    }
                    break;
                case           0xC1:
                    switch (ld.getreg())
                    {
                    case	       0:s.set_imm8(1);          s.set_mnem("ROL");						break;
                    case	       1:s.set_imm8(1);		s.set_mnem("ROR");						break;
                    case	       2:s.set_imm8(1);		s.set_mnem("RCL");						break;
                    case	       3:s.set_imm8(1);		s.set_mnem("RCR");						break;
                    case	       4:s.set_imm8(1);		s.set_mnem("SAL");						break;
                    case	       5:s.set_imm8(1);		s.set_mnem("SHR");						break;
                    case	       6:s.set_imm8(1);		s.set_mnem("SHL");						break;
                    case	       7:s.set_imm8(1);		s.set_mnem("SAR");						break;
                    }
                    break;
                case           0xD0:
                    switch (ld.getreg())
                    {
                    case	       0:       s.set_mnem("ROL");    s.set_op2("1");						break;
                    case	       1:		s.set_mnem("ROR");    s.set_op2("1");						break;
                    case	       2:		s.set_mnem("RCL");	s.set_op2("1");					break;
                    case	       3:		s.set_mnem("RCR");    s.set_op2("1");						break;
                    case	       4:		s.set_mnem("SAL");	s.set_op2("1");					break;
                    case	       5:		s.set_mnem("SHR");	s.set_op2("1");					break;
                    case	       6:		s.set_mnem("SHL");	s.set_op2("1");					break;
                    case	       7:		s.set_mnem("SAR");	s.set_op2("1");					break;
                    }
                    break;
                case           0xD1:
                    switch (ld.getreg())
                    {
                    case	       0:          s.set_mnem("ROL"); s.set_op2("1");						break;
                    case	       1:		s.set_mnem("ROR");	s.set_op2("1");					break;
                    case	       2:		s.set_mnem("RCL");	s.set_op2("1");					break;
                    case	       3:		s.set_mnem("RCR");	s.set_op2("1");					break;
                    case	       4:		s.set_mnem("SAL");	s.set_op2("1");					break;
                    case	       5:		s.set_mnem("SHR");	s.set_op2("1");					break;
                    case	       6:		s.set_mnem("SHL");	s.set_op2("1");					break;
                    case	       7:		s.set_mnem("SAR");	s.set_op2("1");					break;
                    }
                    break;
                case           0xD2:
                    switch (ld.getreg())
                    {
                    case	       0:          s.set_mnem("ROL"); s.set_op2("CL");						break;
                    case	       1:		s.set_mnem("ROR");	s.set_op2("CL");					break;
                    case	       2:		s.set_mnem("RCL");	s.set_op2("CL");					break;
                    case	       3:		s.set_mnem("RCR");	s.set_op2("CL");					break;
                    case	       4:		s.set_mnem("SAL");	s.set_op2("CL");					break;
                    case	       5:		s.set_mnem("SHR");	s.set_op2("CL");					break;
                    case	       6:		s.set_mnem("SHL");	s.set_op2("CL");					break;
                    case	       7:		s.set_mnem("SAR");	s.set_op2("CL");					break;
                    }
                    break;
                case           0xD3:
                    switch (ld.getreg())
                    {
                    case	       0:          s.set_mnem("ROL");		s.set_op2("CL");				break;
                    case	       1:		s.set_mnem("ROR");		s.set_op2("CL");				break;
                    case	       2:		s.set_mnem("RCL");		s.set_op2("CL");				break;
                    case	       3:		s.set_mnem("RCR");		s.set_op2("CL");				break;
                    case	       4:		s.set_mnem("SAL");		s.set_op2("CL");				break;
                    case	       5:		s.set_mnem("SHR");			s.set_op2("CL");			break;
                    case	       6:		s.set_mnem("SHL");		s.set_op2("CL");				break;
                    case	       7:		s.set_mnem("SAR");		s.set_op2("CL");				break;
                    }
                    break;
                case           0xD8:
                    switch (ld.getreg())
                    {
                    case	       0:          s.set_mnem("FADD");						break;
                    case	       1:		s.set_mnem("FMUL");						break;
                    case	       2:		s.set_mnem("FCOM");						break;
                    case	       3:		s.set_mnem("FCOMP");						break;
                    case	       4:		s.set_mnem("FSUB");						break;
                    case	       5:		s.set_mnem("FSUBR");						break;
                    case	       6:		s.set_mnem("FDIV");						break;
                    case	       7:		s.set_mnem("FDIVR");						break;
                    }
                    break;
                case           0xD9:
                    switch (ld.getreg())
                    {
                    case	       0:          s.set_mnem("FLD");						break;
                    case	       1:		s.set_mnem("FXCH");						break;
                    case	       2:		s.set_mnem("FST");						break;
                    case	       3:		s.set_mnem("FSTP");						break;
                    case	       4:		s.set_mnem("FLDENV");						break;
                    case	       5:		s.set_mnem("FLDCW");						break;
                    case	       6:		s.set_mnem("FSTENV");						break;
                    case	       7:		s.set_mnem("FSTCW");						break;
                    }
                    break;
                case           0xDA:
                    switch (ld.getreg())
                    {
                    case	       0:          s.set_mnem("FIADD");						break;
                    case	       1:		s.set_mnem("FIMUL");						break;
                    case	       2:		s.set_mnem("FICOM");						break;
                    case	       3:		s.set_mnem("FICOMP");						break;
                    case	       4:		s.set_mnem("FISUB");						break;
                    case	       5:		s.set_mnem("FISUBR");						break;
                    case	       6:		s.set_mnem("FIDIV");						break;
                    case	       7:		s.set_mnem("FIDIVR");						break;
                    }
                    break;
                case           0xDB:
                    switch (ld.getreg())
                    {
                    case	       0:          s.set_mnem("FILD");						break;
                    case	       1:		s.set_mnem("FISTTP");						break;
                    case	       2:		s.set_mnem("FIST");						break;
                    case	       3:		s.set_mnem("FISTP");						break;
                    case	       4:		s.set_mnem("FNENI");						break;
                    case	       5:		s.set_mnem("FLD");						break;
                    case	       6:		s.set_mnem("FCOMI");						break;
                    case	       7:		s.set_mnem("FSTP");						break;
                    }
                    break;
                case	       0xDC:
                    switch (ld.getreg())
                    {
                    case	       0:          s.set_mnem("FADD");						break;
                    case	       1:		s.set_mnem("FMUL");						break;
                    case	       2:		s.set_mnem("FCOM");						break;
                    case	       3:		s.set_mnem("FCOMP");						break;
                    case	       4:		s.set_mnem("FSUB");						break;
                    case	       5:		s.set_mnem("FSUBR");						break;
                    case	       6:		s.set_mnem("FDIV");						break;
                    case	       7:		s.set_mnem("FDIVR");						break;
                    }
                    break;
                case	       0xDD:
                    switch (ld.getreg())
                    {
                    case	       0:          s.set_mnem("FLD");						break;
                    case	       1:		s.set_mnem("FISTTP");						break;
                    case	       2:		s.set_mnem("FST");						break;
                    case	       3:		s.set_mnem("FSTP");						break;
                    case	       4:		s.set_mnem("FRSTOR");						break;
                    case	       5:		s.set_mnem("FUCOMP");						break;
                    case	       6:		s.set_mnem("FNSAVE");						break;
                    case	       7:		s.set_mnem("FNSTSW");						break;
                    }
                    break;
                case	       0xDE:
                    switch (ld.getreg())
                    {
                    case	       0:          s.set_mnem("FIADD");						break;
                    case	       1:		s.set_mnem("FIMUL");						break;
                    case	       2:		s.set_mnem("FICOM");						break;
                    case	       3:		s.set_mnem("FICOMP");						break;
                    case	       4:		s.set_mnem("FISUB");						break;
                    case	       5:		s.set_mnem("FISUBR");						break;
                    case	       6:		s.set_mnem("FIDIV");						break;
                    case	       7:		s.set_mnem("FIDIVR");						break;
                    }
                    break;
                case	       0xDF:
                    switch (ld.getreg())
                    {
                    case	       0:          s.set_mnem("FILD");						break;
                    case	       1:		s.set_mnem("FISTTP");						break;
                    case	       2:		s.set_mnem("FIST");						break;
                    case	       3:		s.set_mnem("FISTP");						break;
                    case	       4:		s.set_mnem("FBLD");						break;
                    case	       5:		s.set_mnem("FILD");						break;
                    case	       6:		s.set_mnem("FBSTP");						break;
                    case	       7:		s.set_mnem("FISTP");						break;
                    }
                    break;
                 case           0xF6:
                    switch (ld.getreg())
                    {
                    case	       0:          s.set_mnem("TEST");		s.set_imm8(1);				break;
                    case	       1:		s.set_mnem("TEST");		s.set_imm8(1);				break;
                    case	       2:		s.set_mnem("NOT");						break;
                    case	       3:		s.set_mnem("NEG");						break;
                    case	       4:		s.set_mnem("MUL");						break;
                    case	       5:		s.set_mnem("IMUL");						break;
                    case	       6:		s.set_mnem("DIV");						break;
                    case	       7:		s.set_mnem("IDIV");					break;
                    }
                    break;
                case           0xF7:
                    switch (ld.getreg())
                    {
                    case	       0:          s.set_mnem("TEST");		s.set_imm16(1);				break;
                    case	       1:		s.set_mnem("TEST");		s.set_imm16(1);				break;
                    case	       2:		s.set_mnem("NOT");						break;
                    case	       3:		s.set_mnem("NEG");						break;
                    case	       4:		s.set_mnem("MUL");						break;
                    case	       5:		s.set_mnem("IMUL");						break;
                    case	       6:		s.set_mnem("DIV");						break;
                    case	       7:		s.set_mnem("IDIV");					break;
                    }
                    break;
                case           0xFF:
                    switch (ld.getreg())
                    {
                    case	       0:          s.set_mnem("INC");						break;
                    case	       1:		s.set_mnem("DEC");						break;
                    case	       2:		s.set_mnem("CALL");						break;
                    case	       3:		s.set_mnem("CALLF");						break;
                    case	       4:		s.set_mnem("JMP");						break;
                    case	       5:		s.set_mnem("JMPF");						break;
                    case	       6:		s.set_mnem("PUSH");						break;
                    }
                    break;
                case	       0xFE:
                    switch (ld.getreg())
                    {
                    case	       0:          s.set_mnem("INC");						break;
                    case	       1:		s.set_mnem("DEC");						break;
                    }
                    break;
        }

}
