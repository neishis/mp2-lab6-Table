#pragma once
#include "Table.h"

//’эш таблица
//1 вариант: в таблице храним массивы списка
//2 вариант: если в таблтце зан€то нужное место, сместить с некоторым шагом и записать туда, повтор€ть пока не найдем свободное
// вводим пон€тие пустой и удаленной €чейки 
// поиск: идем либо до свободной €чейки либо до обнаружени€ ключа
// удаление: 

template<typename TKey, typename TVal>
class HashTable : public Table <TKey, TVal>
{
protected:
	int size;
	//HashTable(int _size) : ArrayTable(_size) {};

	virtual int HashFunc(TKey key) 
	{
		return key % size;
	}
	
};
