
#include <stdlib.h>

#include "BSTree.h"


int BSTreeNodeCount(BSTree t) {
	// int total_nodes = 0;
	// if (t == NULL) {
	// 	return 0;
	// }
	// if (t->left != NULL) {
	// 	total_nodes += BSTreeNodeCount(t->left);
	// }
	// if (t->right != NULL) {
	// 	total_nodes += BSTreeNodeCount(t->right);
	// }
	// if (t->left == NULL && t->right == NULL) {
	// 	return 1;
	// }
	// return total_nodes;
	if (t == NULL)
		return 0;
	else
		return 1 + BSTreeNodeCount (t->left) + BSTreeNodeCount (t->right);
}
int BSTreeGetKth(BSTree t, int k) {
	// int left = 0;
	// int right = 0;
	if (t == NULL) {
		return -1;
	}
	int LeftNodeCount = BSTreeNodeCount(t->left);
	if (LeftNodeCount == k) {
		return t->value;
	}
	if (LeftNodeCount > k) {
		return BSTreeGetKth(t->left, k);
	} else {
		// ask the tutor and discuss it with him
		return BSTreeGetKth(t->right, k - LeftNodeCount - 1);
	}

	// return -42;
}

