//��Ŀ����
//����ĳ��������ǰ���������������Ľ�������ؽ����ö����������������ǰ���������������Ľ���ж������ظ������֡�
//��������ǰ���������{ 1, 2, 4, 7, 3, 5, 6, 8 }�������������{ 4, 7, 2, 1, 5, 3, 8, 6 }�����ؽ������������ء�
/**
* Definition for binary tree
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class Solution {
public:
	TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin)
	{
		return Tree(pre, 0, pre.size(), vin, 0, vin.size());
	}

	TreeNode* Tree(vector<int> &a, int abegin, int aend, vector<int> &b, int bbegin, int bend)
	{
		if (abegin >= aend || bbegin >= bend)
			return NULL;
		TreeNode* root = new TreeNode(a[abegin]);
		int pivot;
		for (pivot = bbegin; pivot < bend; ++pivot){
			if (b[pivot] == a[abegin])
				break;
		}
		root->left = Tree(a, abegin + 1, abegin + pivot - bbegin + 1, b, bbegin, pivot);
		root->right = Tree(a, abegin + pivot - bbegin + 1, aend, b, pivot + 1, bend);
		return root;
	}
};