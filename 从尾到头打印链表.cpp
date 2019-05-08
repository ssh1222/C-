//����һ������������ֵ��β��ͷ��˳�򷵻�һ��ArrayList��

/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
	vector<int> printListFromTailToHead(ListNode* head)
	{
		ListNode *cur = head;
		int count = 0;
		while (cur){
			count++;
			cur = cur->next;
		}
		cur = head;
		vector<int> vec;
		vec.resize(count);
		while (cur){
			vec[--count] = cur->val;
			cur = cur->next;
		}
		return vec;
	}
};