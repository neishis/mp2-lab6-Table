#pragma once
#include "ArrayTable.h"

//Неупорядоченная таблица

template<typename TKey, typename TVal>
class ScanTable : public ArrayTable <TKey, TVal>
{
public:

	ScanTable(int _size) : ArrayTable(_size) {} //конструктор инициализации

	bool Find(TKey key) //Поиск по ключу
	{
		for (int i = 0; i < DataCount; i++) {
			Eff++;
			if (key == pRec[i].key) {
				Curr = i;
				return true;
			}
		}
		Curr = DataCount;
		return false;
	}

	void Insert(Record <TKey, TVal> rec) //Добавление элемента 
	{
		if (Find(rec.key)) {
			throw - 1;
		}
		Eff++;
		pRec[Curr] = rec;
		DataCount++;
	}

	void Delete(TKey key) // Удаление по ключу
	{
		if (Find(key) == 0) {
			throw - 1;
		}
		else {
			pRec[Curr] = pRec[DataCount - 1];
			DataCount--;
		}
	}
};


