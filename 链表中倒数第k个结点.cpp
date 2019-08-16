//题目描述
//输入一个链表，输出该链表中倒数第k个结点。
#include <iostream>

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) 
		:val(x)
		, next(NULL) 
	{}
};

class Solution {
public:
	ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
	{
		if (pListHead == nullptr || k == 0)
			return nullptr;
		int count = 0;
		ListNode *cur = pListHead;
		while (cur){
			cur = cur->next;
			++count;
		}
		if (count >= k){
			ListNode *tmp = pListHead;
			ListNode *ret = pListHead;
			while (k--)
				tmp = tmp->next;
			while (tmp != nullptr){
				tmp = tmp->next;
				ret = ret->next;
			}
			return ret;
		}
		return nullptr;
	}
};