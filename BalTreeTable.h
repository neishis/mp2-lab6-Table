#pragma once
#include "Table.h"
#include "TreeTable.h"

#define H_OK      0
#define H_INC	  1
#define H_DEC	 -1

template<typename TKey, typename TVal>
class BalTreeTable : public TreeTable <TKey, TVal> {
protected:

	int InsBalTree(TreeNode<TKey, TVal>*& pNode, Record rec)
	{
		int res = H_OK;
		Eff++;
		if (pNode == nullptr) {
			pNode = new TreeNode<TKey, TVal>(rec);
			rec = H_OK;
			DataCount++;
		}
		else {
			if (pRoot->rec.key > rec.key) {
				int tmp = InsBalTree(pNode->pLeft, rec);
				if (tmp == H_INC) {
					res = BalTreeLeft(pNode);
				}
			}
			else {
				int tmp = InsBalTree(pNode->pRight, rec);
				if (tmp == H_INC) {
					res = BalTreeRight(pNode);
				}
			}
		}
		return res;
	}


	int DelBalTree(TreeNode<TKey, TVal>*& pNode, TKey key)
	{
		int res = H_OK;
		Eff++;
		if (pNode == nullptr) return res;
		else {
			if (pNode->rec.key < key) {
				int tmp = DelBalTree(pNode->pRight, key);
				if (tmp != H_OK) res = BalTreeLeft(pNode, false);
			}
			else if (pNode->rec.key > key) {
				int tmp = DelBalTree(pNode->pLeft, key);
				if (tmp != H_OK) res = BalTreeRight(pNode, false);
			}
			else {
				DataCount--;
				if (pNode->pLeft == nullptr && pNode->pRight == nullptr) {
					delete pNode;
					pNode = nullptr;
					res = H_DEC;
				}
				else if (pNode->pLeft != nullptr) {
					pNode->rec = pNode->pRight->rec;
					delete pNode->pRight;
					pNode->pRight = nullptr;
					pNode->bal = 0;
					res = H_DEC;
				}
				else if (pNode->pRight != nullptr) {
					pNode->rec = pNode->pLeft->rec;
					delete pNode->pLeftt;
					pNode->pLeft = nullptr;
					pNode->bal = 0;
					res = H_DEC;
				}
				else {
					TreeNode<TKey, TVal> left = pNode->pLeft;
					TreeNode<TKey, TVal> right = pNode->pRight;
					TreeNode<TKey, TVal> pMin = FindMin(right);
					res = RemoveMin(right);
					pNode->rec = pMin->rec;
					delete pMin;
					pNode->pLeft = left;
					pNode->pRight = right;
					if (res != H_OK) {
						res = BalTreeLeft(pNode, false);
					}
				}
				return res;
			}
		}
	}


	TNode* FindMin(TreeNode<TKey, TVal>*& pNode)
	{
		while (pNode->pLeft != nullptr) {
			pNode = pNode->pLeft;
			Eff++;
		}
		return pNode;
	}


	int RemoveMin(TreeNode<TKey, TVal>*& pNode)
	{
		int res = H_OK;
		if (pNode->pLeft == nullptr) {
			pNode = pNode->pRight;
			res = H_DEC;
		}
		else {
			res = RemoveMin(pNode->pLeft);
			if (res != H_OK) {
				res = BalTreeRight(pNode, false);
			}
		}
		return res;
	}


	int BalTreeLeft(TreeNode<TKey, TVal>*& pNode)
	{
		int res = H_OK;
		if (pNode->bal == BalRight) {
			pNode->bal = BalOK;
			res = H_OK;
		}
		else if (pNode->bal == BalOK) {
			pNode->bal = BalLeft;
			res = H_INC;
		}
		else if (pNode->bal == BalLeft) {
			TreeNode* p1 = pNode->pLeft;
			if (p1->bal == BalLeft) {
				pNode->pLeft = p1->pRight;
				p1->pRight = pNode;
				pNode->bal = BalOK;
				pNode = p1;
				pNode->bal = BalOK;
			}
			else {
				TreeNode* p2 = p1->pRight;
				p1->pRight = p2->pLeft;
				pNode->pLeft = p2->pRight;
				p2->pLeft = p1;
				p2->pRight = pNode;
				pNode = p2;
				if (p2->bal == BalLeft) pNode->bal = BalRight;
				else pNode->bal = BalOK;
				if (p2->bal == BalRight) pNode->bal = BalLeft;
				else pNode->bal = BalOK;
			}
		}
	}


	int BalTreeRight(TreeNode<TKey, TVal>*& pNode)
	{
		int res = H_OK;
		if (pNode->bal == BalLeft) {
			pNode->bal = BalOK;
			res = H_OK;
		}
		else if (pNode->bal == BalOK) {
			pNode->bal = BalRight;
			res = H_INC;
		}
		else if (pNode->bal == BalRight) {
			TreeNode* p1 = pNode->pRight;
			if (p1->bal == BalRight) {
				pNode->pRight = p1->pLeft;
				p1->pLeft = pNode;
				pNode->bal = BalOK;
				pNode = p1;
				pNode->bal = BalOK;
			}
			else {
				TreeNode* p2 = p1->pRight;
				p1->pLeft = p2->pRight;
				pNode->pRight = p2->pLeft;
				p2->pRight = p1;
				p2->pLeft = pNode;
				pNode = p2;
				if (p2->bal == BalRight) pNode->bal = BalLeft;
				else pNode->bal = BalOK;
				if (p2->bal == BalLeft) pNode->bal = BalRight;
				else pNode->bal = BalOK;
			}
		}
	}

public:

	void Insert(Record rec) 
	{
		if (!Find(rec.key)) InsBalTree(pRoot, rec);
	}


	bool Delete(TKey key) 
	{
		if (Empty()) return false;
		DeleteRec(pRoot, key);
		return true;
	}
};
