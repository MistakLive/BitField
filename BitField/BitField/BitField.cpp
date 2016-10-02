#include "BitField.h"

TBitField :: TBitField (int len)
{
	MemLen= (len+15) >> 5;
	Mem =  new unsigned int[MemLen];
	if (Mem != NULL )
		for (int i=0; i<MemLen; i++) Mem[i] = 0;

}

TBitField :: TBitField (const TBitField &BF1)
{
	BitLen = BF1.BitLen;
	MemLen = BF1.BitLen;
	Mem = new unsigned int[MemLen];
	if (Mem != NULL )
		for (int i=0; i<MemLen; i++) Mem[i] = 0;

}

TBitField :: ~TBitField ()
{
	delete Mem;
	Mem = NULL;
}


int TBitField :: GetIndex (const int index) const
{
	return index >> 5;
}
unsigned int TBitField :: GetMemMask (const int index) const
{
	return 1 << (index & 31);
}

int TBitField :: GetBit (const int index) const
{
	if ( (index > -1) && (index < BitLen) )
	{
		int k=GetIndex(index);
		return Mem[k] & GetMemMask(index);
	}
}

void TBitField :: SetBit (const int index) 
{
	if ( (index > -1) && (index < BitLen) )
	{
		int k=GetIndex(index);
		Mem[k]|=GetMemMask(index);
	}
}

void TBitField :: DelBit (const int index) 
{
	if ( (index > -1) && (index < BitLen) )
	{
		int k=GetIndex(index);
		Mem[k] &=~GetMemMask(index);
	}
}

istream &operator >> (istream &is, TBitField &bf)
{
	int i=0; char ch;
	do {(is >> ch);} while (ch !=' ');
	while (1) 
	{
		is >> ch;
		if ( ch == '0') bf.DelBit(i++);
		else if (ch == '1') bf.SetBit(i++); else break;
	}
	return is;
}

ostream &operator << (ostream &os, const TBitField &bf)
{
	int len=bf.GetLen();
	for (int i=0; i<len; i++)
		if (bf.GetBit(i)) os << '1'; 
		else os << '0';
	return os;
}
int TBitField :: GetLen(void) const
{
	return BitLen;
}

TBitField & TBitField :: operator = (const TBitField &bf)
{
	BitLen=bf.BitLen;
	if (MemLen != bf.MemLen) 
	{
		if (Mem!=NULL) delete Mem;
		Mem = new unsigned int [MemLen];
	}
	if (Mem != NULL)
		for (int i=0; i<MemLen; i++) Mem[i]=bf.Mem[i];
	return *this;
}

TBitField TBitField :: operator | (const TBitField &bf)
{
	int i, len=BitLen;
	if (bf.BitLen > len) len =bf.BitLen;
	TBitField tmp(len);
	for (i=0; i<MemLen; i++) tmp.Mem[i]   =  Mem[i];
	for (i=0; i<MemLen; i++) tmp.Mem[i] |=bf.Mem[i];
	return tmp;
}

TBitField TBitField :: operator & (const TBitField &bf)
{
	int i, len=BitLen;
	if (bf.BitLen > len) len =bf.BitLen;
	TBitField tmp(len);
	for (i=0; i<MemLen; i++) tmp.Mem[i]   =  Mem[i];
	for (i=0; i<MemLen; i++) tmp.Mem[i] &=bf.Mem[i];
	return tmp;
}

TBitField TBitField :: operator ~(void)
{
	int len=BitLen;
	TBitField tmp(len);
	for (int i=0; i<MemLen; i++) tmp.Mem  = ~Mem[i];
	return tmp;
}