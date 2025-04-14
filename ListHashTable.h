#pragma once
#include "Table.h"


template<typename TKey, typename TVal>
class ListHashTable : public HashTable <TKey, TVal>
{
protected:
	list<Record>* pList;
	int CurrList;
	list<Record> ::iterator CurrI;
public:
	//в конструкторе должен быть объ€влен массив списков
	ListHashTable(int _size = 100) : HashTable(_size) {
		pList = new list<Record<TKey, TVal>>[size];
		CurrLust = -1;
	}
	~ListHashTable(){
		delete[] pList;
	}
	bool Find(TKey key) {
		CurrList = HashFunc(key);
		bool res = false;
		for (CurrI = pList[CurrList].begin(); CurrI != pList[CurrList].end(); CurrI++) {
			if (CurrI->key == key) {
				res = true;
				break;
			}
			Eff++;
		}
		return res;
	}

	void Insert(Record rec) {
		if (Find(rec.key)) return;
		pList[CurrList].pushFront(rec);
		DataCount++;
		Eff++;
	}

	void Delete(Tkey key) {
		if (!Find(key)) return;
		pList[CurrList].erase(CurrI);
		DataCount--;
		Eff++;
	}
	void Reset() {
		CurrList = 0;
		CurrI = pList[CurrList].begin();
		while (CurrI == pList[CurrList].end()) {
			CurrList++;
			if (CurrList >= size) break;
			else {
				CurrI = pList[CurrList].begin();
			}
		}
	}
	void GoNext() {
		CurrI++;
		while (CurrI == pList[CurrList].end()) {
			CurrList++;
			if (CurrList >= size) break;
			else {
				CurrI = pList[CurrList].begin();
			}
		}
	}
	bool IsEnd() {
		return CurrList >= size;
	}
};
