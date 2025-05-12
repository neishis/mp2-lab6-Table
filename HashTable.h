#pragma once
#include "Table.h"

template<typename TKey, typename TVal>
class HashTable : public Table <TKey, TVal>
{
protected:
	int size;
	HashTable(int _size) : Table<TKey, TVal>() {
		size = _size;
	}

	virtual int HashFunc(TKey key) const
	{
		return key % size;
	}
	
};
