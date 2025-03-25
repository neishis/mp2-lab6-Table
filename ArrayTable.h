#pragma once
#include "Table.h"

//Массив

//оператор присваивания 
template<typename TKey, typename TVal>
class ArrayTable : public Table <TKey, TVal>
{
protected: 
	int size, Curr;
	Record <TKey, TVal>* pRec;

public:

	ArrayTable(int _size = 10)  : Table() // Конструктор инициализации
	{
		size = _size;
		pRec = new Record <TKey, TVal>[size];
		Curr = -1;
	}

	ArrayTable(const ArrayTable& at) // Конструктор копирования
	{
		size = at.size;
		Curr = at.Curr;
		pRec = new Record <TKey, TVal>[size];
		for (int i = 0; i < size; i++) {
			pRec[i] = at.pRec[i];
		}
	}

	~ArrayTable() { delete[] pRec;} // Деструктор

	/*Record getCurr() { return Curr->key; } // Возвращаем позицию*/

	virtual bool IsFull() const { return DataCount >= size; } // Массив заполнен

	void Reset() { Curr = 0; } // Переход в начало
	void GoNext() { Curr++; } // Ход вперед
	bool IsEnd() { return DataCount == Curr;} // Конец
};

