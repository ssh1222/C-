//从上往下打印出二叉树的每个节点，同层节点从左至右打印。

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL)
	{
	}
}; */
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
class Solution {
public:
	vector<int> PrintFromTopToBottom(TreeNode* root)
	{
		vector<int> vec;
		if (root == NULL)
			return vec;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()){
			TreeNode *cur = q.front();
			cout << cur->val << endl;
			vec.push_back(cur->val);
			q.pop();
			if (cur->left)
				q.push(cur->left);
			if (cur->right)
				q.push(cur->right);
		}
		return vec;
	}
};