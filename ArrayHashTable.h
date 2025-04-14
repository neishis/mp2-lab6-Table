#pragma once
#include "Table.h"


template<typename TKey, typename TVal>
class ArrayHashTable : public HashTable <TKey, TVal>
{
protected:
	Record<Tkey, Tval>* pRec;
	Record<Tkey, Tval> Free, Del;
	int step, Curr;
public:

	ArrayHashTable(int _size, int _step = 13)
	{
		size = _size;
		sterp = _step;
		pRec = new Record[_size];
		Free = Record(-1);
		Del = Record(-2);
		for (int i = 0; i < size; i++) {
			pRec[i] = Free;
		}
	}

	~ArrayHashTable() 
	{
		delete[] pRecs;
	}

	bool IsFull() 
	{
		if (DataCount == size) return 1;
		else return 0;
	}

	bool Find(TKey key)
	{
		Curr = HashFunc(key);
		int tmp = -1;
		for (int i = 0; i < size; i++) {
			eff++;
			if (pRec[Curr] == Free) break;
			else if (pRec[Curr] == Del && tmp == -1) tmp = Curr;
			else if (pRec[Curr].key == key) return true;
			Curr = (Curr + step) % size;
		}
		if (tmp != -1) Curr = tmp;
		return false;
	}

	bool Insert(Record& rec) {
		if (Find(rec.key)) throw - 1;
		pRec[Curr] = rec;
		DataCount++;
		Eff++;
		return true;
	}

	void Delete(TKey key) {
		if (Find(key)) {
			pRec[Curr] = Del;
			DataCount--;
			Eff++;
		}
	}

	void Reset() {
		Curr = 0;
		while ((Curr < size) && (pRec[Curr] == Del || pRec[Curr] == Free) {
			Curr++;
		}
	}
	void GoNext() {
		Curr++;
		while ((Curr < size) && (pRec[Curr] == Del || pRec[Curr] == Free) {
			Curr++;
		}
	}

	bool IsEnd() {
		return Curr == size;
	}

	virtual int HashFunc(TKey key)
	{
		return key % size;
	}

};