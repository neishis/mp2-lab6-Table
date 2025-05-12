#pragma once
#include "HashTable.h"


template<typename TKey, typename TVal>
class ArrayHashTable : public HashTable <TKey, TVal>
{
protected:
	Record<TKey, TVal>* pRec;
	Record<TKey, TVal> Free, Del;
	int step, Curr;
public:

	ArrayHashTable(int _size, int _step = 13) : HashTable(_size)
	{
		size = _size;
		step = _step;
		pRec = new Record<TKey, TVal>[_size];
		Free.key = -1;
		Del.key = -2;
		for (int i = 0; i < size; i++) {
			pRec[i] = Free;
		}
	}

	~ArrayHashTable() 
	{
		delete[] pRec;
	}

	bool IsFull() const override
	{
		if (DataCount == size) return 1;
		else return 0;
	}

	bool Find(TKey key) override
	{
		Curr = HashFunc(key);
		int tmp = -1;
		for (int i = 0; i < size; i++) {
			Eff++;
			if (pRec[Curr] == Free) break;
			else if (pRec[Curr] == Del && tmp == -1) tmp = Curr;
			else if (pRec[Curr].key == key) return true;
			Curr = (Curr + step) % size;
		}
		if (tmp != -1) Curr = tmp;
		return false;
	}

	void Insert(Record<TKey, TVal> rec)  override 
	{
		if (Find(rec.key)) return;
		pRec[Curr] = rec;
		DataCount++;
		Eff++;
	}

	void Delete(TKey key) override 
	{
		if (Find(key)) {
			pRec[Curr] = Del;
			DataCount--;
			Eff++;
		}
	}

	void Reset() override 
	{
		Curr = 0;
		while ((Curr < size) && (pRec[Curr] == Del || pRec[Curr] == Free)) {
			Curr++;
		}
	}
	void GoNext() override 
	{
		Curr++;
		while ((Curr < size) && (pRec[Curr] == Del || pRec[Curr] == Free)) {
			Curr++;
		}
	}

	bool IsEnd() override {
		return Curr == size;
	}

	Record<TKey, TVal> getCurr() override {
		return pRec[Curr];
	}

};