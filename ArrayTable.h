#pragma once
#include "Table.h"

template<typename TKey, typename TVal>
class ArrayTable : public Table <TKey, TVal>
{
protected: 
	int size, Curr;
	Record <TKey, TVal>* pRec;

public:

	ArrayTable(int _size = 10)  : Table() 
	{
		size = _size;
		pRec = new Record <TKey, TVal>[size];
		Curr = -1;
		this->DataCount = 0;
	}

	ArrayTable(const ArrayTable& at) 
	{
		size = at.size;
		Curr = at.Curr;
		this->DataCount = at.DataCount;
		this->Eff = at.Eff;
		pRec = new Record <TKey, TVal>[size];
		for (int i = 0; i < size; i++) {
			pRec[i] = at.pRec[i];
		}
	}

	~ArrayTable() { delete[] pRec;} 

	bool IsFull() const { return this->DataCount >= size; }
	Record<TKey, TVal> getCurr() const { return pRec[Curr]; };

	void Reset() { Curr = 0; }
	void GoNext() { Curr++; }
	bool IsEnd() { return this->DataCount == Curr;}
};

