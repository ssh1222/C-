//����һ�ö����������������ȡ��Ӹ���㵽Ҷ������ξ����Ľ�㣨������Ҷ��㣩�γ�����һ��·�����·���ĳ���Ϊ������ȡ�

/*
struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};*/
class Solution {
public:
	int TreeDepth(TreeNode* pRoot)
	{
		if (pRoot == NULL){
			return 0;
		}
		int leftDepth = TreeDepth(pRoot->left) + 1;
		int rightDepth = TreeDepth(pRoot->right) + 1;

		return leftDepth > rightDepth ? leftDepth : rightDepth;
	}
};