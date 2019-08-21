//题目描述
//输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
//例如输入前序遍历序列{ 1, 2, 4, 7, 3, 5, 6, 8 }和中序遍历序列{ 4, 7, 2, 1, 5, 3, 8, 6 }，则重建二叉树并返回。
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