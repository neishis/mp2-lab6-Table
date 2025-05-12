#pragma once
#include "ArrayTable.h"

//Неупорядоченная таблица

template<typename TKey, typename TVal>
class ScanTable : public ArrayTable <TKey, TVal>
{
public:

	ScanTable(int _size) : ArrayTable(_size) {}

	bool Find(TKey key)
	{
		for (int i = 0; i < DataCount; i++) {
			Eff++;
			if (key == pRec[i].key) {
				Curr = i;
				Eff++;
				return true;
			}
		}
		Curr = DataCount;
		return false;
	}

	void Insert(Record <TKey, TVal> rec)
	{
		if (IsFull()) throw - 1;
		if (Find(rec.key)) {
			throw - 1;
		}
		Eff++;
		pRec[Curr] = rec;
		DataCount++;
	}

	void Delete(TKey key)
	{
		if (Find(key) == 0) {
			return;
		}
		else {
			pRec[Curr] = pRec[DataCount - 1];
			DataCount--;
			Eff++;
		}
	}

	Record<TKey, TVal> getCurr() {
		return pRec[Curr];
	}
};


