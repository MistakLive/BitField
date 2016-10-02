#include <iostream>
using namespace std;

#ifndef vector_h
#define vector_h


class TBitField
{
	int BitLen;									//max q of bit
	unsigned int *Mem;							//memory for bit string
	int MemLen;									//size of string
	int GetIndex (const int index) const;
	unsigned int GetMemMask (const int index) const;

public:
	TBitField (int len);
	TBitField (const TBitField &BF1);

	~TBitField();

	int GetBit(const int index) const;
	void SetBit(const int index);
	void DelBit(const int index);

	friend istream& operator >> (istream &is, TBitField &bf);
	friend ostream& operator << (istream &os, const TBitField &bf);

	int GetLen(void) const;

	TBitField & operator = (const TBitField &bf);
	TBitField operator | (const TBitField &bf);			//or
	TBitField operator & (const TBitField &bf);			//and
	TBitField operator ~(void);							//not
	
};

#endif