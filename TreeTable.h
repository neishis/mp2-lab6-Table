#pragma once
#include "Table.h"

#define BalOK		 0
#define BalLeft		-1 
#define BalRight	 1

template<typename TKey, typename TVal>
struct TreeNode {
	Record <TKey, TVal> rec;
	TreeNode* pLeft, * pRight;
	int bal;
};

template<typename TKey, typename TVal>
class TreeTable : public Table <TKey, TVal> {
protected:
	TreeNode<typename TKey, typename TVal>* pRoot, * pCurr, * pPrev;
	stack<TreeNode* > st;
	int pos;
public:
	TreeTable() : Table() { pRoot = pCurr = pPrev = nullptr; }

	bool Find(TKey key) {
		pCurr = pRoot;
		pPrev = nullptr;
		while (pCurr != nullptr) {
			eff++;
			if (pCurr->rec.key == key) return true;
			else if (pCurr->rec.key < key) {
				pPrev = pCurr; 
				pCurr = pCurr->pLeft;
			}
			else {
				pPrev = pCurr;
				pCurr = pCurr->pRight;
			}
		}
		pCurr = pPrev;
		return false;
	}

	void Insert(Record <TKey, TVal> rec) {
		bool res = Find(rec.key);
		if (res) return;
		DataCount++;
		Eff++;
		TreeNode <TKey, TVal>* newN = new TreeNode<TKey, TVal>;
		newN->rec = rec;
		newN->pLeft = newN->pRight = nullptr;
		if (pRoot = nullptr) pRoot = newN;
		else if (pCurr->rec.key > rec.key) {
			pCurr->pLeft = newN;
		}
		else {
			pCurr->pRight = newN;
		}
		return true;
	}

	void Delete(TKey key) {
		bool res = Find(rec.key);
		if (!res) return;
		else {
			TreeNode<TKey, TVal>* pDel = nullptr;
			if (pCurr->pRight == nullptr)
			{
				if (pPrev == nullptr) pRoot = pRoot->pLeft;
				else {
					if (pCurr == pPrev->pRight)
						pPrev->pRight = pCurr->pLeft;
					else
						pPrev->pLeft = pCurr->pLeft;
				}
			}
			else if (pCurr->pLeft == nullptr)
			{
				if (pPrev == nullptr)  pRoot = pRoot->pRight;
				else {
					if (pCurr == pPrev->pRight)
						pPrev->pRight = pCurr->pRight;
					else
						pPrev->pLeft = pCurr->pRight;
				}
			}
			else
			{
				TreeNode<TKey, TVal>* tmp = pCurr->pLeft;
				pPrev = pCurr;
				while (tmp->pRight != nullptr) {
					Eff++;
					pPrev = tmp;
					tmp = tmp->pRight;
				}
				pCurr->rec = tmp->rec;
				if (pPrev != pCurr)
					pPrev->pRight = tmp->pLeft;
				else
					pPrev->pLeft = tmp->pLeft;
				pDel = tmp;
			}
			Eff++;
			delete pDel;
			DataCount--;
		}
		void Reset() {
			st.clear();
			while (pCurr->pLeft!= nullptr) {
				st.push(pCurr);
				pCurr = pCurr->pLeft;
			}
			st.push(pCurr);
			pos = 0;
		}

		void GoNext() {
			pCurr = pCurr->pRight;
			st.pop();
			if (pCurr = nullptr && !st.empty) pCurr = st.top();
			else {
				while (pCurr->pLeft != nullptr) {
					st.push(pCurr);
					pCurr = pCurr->pLeft;
				}
				st.push(pCurr);
				pos++;
			}
		}
		bool IsEnd() {
			return pos == DataCount;
		}

		void PrintRec(ostream& os, Node* p) {
			if (p == nullptr) return;
			for (int i = 0; i < level; i++) {
				os << " ";
			}
			os << p->key << endl;
			level++;
			PrintRec(os, p->pRight);
			PrintRec(os, p->pLeft);
			level--;
		}
		void Print(ostream& os) {
			int level = 0;
			PrintRec(os, pRoot);
		}
	}
};