#include "tree.h"
#include <vector>


vector<TreeNode*> GenerateBTree(vector<int>& inOrderTraNums)
{
	vector<TreeNode*> vecTree, vecTreeL, vecTreeR;
	size_t i = 0;
	size_t j = 0;
	vector<int> left, right;

	if (inOrderTraNums.size() == 0)
	{
		vecTree.push_back(NULL);
		return vecTree;
	}

	for (i = 0; i < inOrderTraNums.size(); i++)
	{
		for (j = 0; j < i; j++)
		{
			left.push_back(inOrderTraNums[j]);
		}

		for (j = i + 1; j < inOrderTraNums.size(); j++)
		{
			right.push_back(inOrderTraNums[j]);
		}

		vecTreeL = GenerateBTree(left);
		vecTreeR = GenerateBTree(right);

		for (TreeNode* left_node : vecTreeL)
		{
			for (TreeNode* right_node : vecTreeR)
			{
				TreeNode* t = new TreeNode(i);
				t->left = left_node;
				t->right = right_node;
				vecTree.push_back(t);
			}
		}
	}

	return vecTree;
}
