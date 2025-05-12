#pragma once
#include "HashTable.h"
#include<list>
#include<iterator>

template<typename TKey, typename TVal>
class ListHashTable : public HashTable <TKey, TVal>
{
protected:
	std::list<Record<TKey, TVal>>* pList;
	int CurrList;
	typename std::list<Record<TKey, TVal>>::iterator CurrI;
public:
	ListHashTable(int _size = 100) : HashTable <TKey, TVal>(_size) {
		pList = new std::list<Record<TKey, TVal>>[size];
		CurrList = -1;
	}
	~ListHashTable() override{
		delete[] pList;
	}

	bool IsFull() const override 
	{
		return false; // Список никогда не бывает полным
	}

	bool Find(TKey key) override 
	{
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

	void Insert(Record<TKey, TVal> rec) override {
		if (Find(rec.key)) return;
		pList[CurrList].push_front(rec);
		DataCount++;
		Eff++;
	}

	void Delete(TKey key) override {
		if (!Find(key)) return;
		pList[CurrList].erase(CurrI);
		DataCount--;
		Eff++;
	}
	void Reset() override {
		/*CurrList = 0;
		CurrI = pList[CurrList].begin;
		while (CurrI == pList[CurrList].end()) {
			CurrList++;
			if (CurrList >= size) break;
			else {
				CurrI = pList[CurrList].begin();
			}
		}*/
		for (CurrList = 0; CurrList < size; CurrList++) {
			if (!pList[CurrList].empty()) {
				CurrI = pList[CurrList].begin();
				return;
			}
		}
		CurrList = this->size;
	}
	void GoNext() override {
		CurrI++;
		while (CurrI == pList[CurrList].end()) {
			CurrList++;
			if (CurrList >= size) break;
			else {
				CurrI = pList[CurrList].begin();
			}
		}
	}
	bool IsEnd() override {
		return CurrList >= size;
	}

	Record<TKey, TVal> getCurr() override {
		if (CurrList < size && CurrI != pList[CurrList].end())
			return *CurrI;
	}

};
