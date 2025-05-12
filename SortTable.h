#pragma once
#include "Table.h"


template<typename TKey, typename TVal>
class SortTable : public ScanTable <TKey, TVal>
{
public:

	SortTable(int _size) : ScanTable(_size) {};

	bool Find(TKey key) 
	{
		int start = 0, finish = DataCount - 1;
		while (start <= finish) {
			Eff++;
			int ind = (start + finish) / 2;
			if (pRec[ind].key > key) {
				finish = ind-1;
			}
			else if (pRec[ind].key < key) {
				start = ind + 1;
			}
			else {
				Curr = ind;
				return true;
			}
		}
		Curr = start;
		return false;
	}

	void Insert(Record<TKey, TVal> rec)
	{
		bool res = Find(rec.key);
		if (res == true) return;
		else {
			for(int i = DataCount; i > Curr; i--) {
				pRec[i] = pRec[i - 1];
				Eff++;
			}
			pRec[Curr] = rec;
			DataCount++;
			Eff++;
		}
	}

	void Delete(TKey key) 
	{
		bool res = Find(key);
		if (res == false) return;
		else {
			for (int i = Curr; i < DataCount-1; i++) {
				pRec[i] = pRec[i + 1];
				Eff++;
			}
			DataCount--;
			Eff++;
		}
	}

	Record<TKey, TVal> getCurr() {
		return pRec[Curr];
	}

	void SelectSort()
	{
		int i = 0, j = 0;
		while (i < DataCount) {
			j = i;
			int k = i;
			int mini = pRec[i].key;
			while (j < DataCount) {
				if (mini > pRec[i].key) {
					mini = pRec[i].key;
					k = j;
				}
				j++;
				Eff++;
			}
			Record rec = pRec[k];
			pRec[k] = pRec[i];
			pRec[i] = rec;
			i++;
		}
	}

	void QSort() 
	{
		QSortRec(0, DataCount - 1);
	}

	void QSortRec(int start, int finish) 
	{
		int Left = start;
		int Right = finish;
		Record k = pRec[(start + finish) / 2];
		while (Left < Right) {
			while (pRec[Left] < k) {
				Left++;
			}
			while (pRec[Right] > k) {
				Right--;
			}
			if (Left <= Right) {
				swap(pRec[Left], pRec[Right]);
				Left++; 
				Right--;
			}
		}
		if (start < Left) QSortRec(start, Left);
		if (Right < finish) QSortRec(Right, finish);

	}

	void Merge(int left, int middle, int right) {
		int i = left, j = middle, k = left;
		while (i <= middle && j <= right) {
			if (pRec[i].key <= pRec[j].key) tmpArr[k] = pRec[i];
			else {
				tmpArr[k] = pRec[j];
				j++;
			}
			k++;
		}
		if (i <= middle) {
			while (i <= middle) {
				tmpArr[k] = pRec[i];
				k++;
				i++;
			}
		}
		else {
			while (j <= right) {
				tmpArr[k] = pRec[j];
				k++;
				j++;
			}
		}
		for (int i = left; i <= right; i++) {
			pRec[i] = tmpArr[i];
		}
	}

	void MergeSort(int left, int right) {
		if (left == right) return;
		int middle = (left + right) / 2;
		MergeSort(left, middle);
		MergeSort(middle + 1, right);
		Merge(left, middle, right);
	}
};