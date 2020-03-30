
#include <stdlib.h>

#include "tree.h"

#define abs(a) (a<0)?(-a):(a)


int TreeNodeCount(Tree t) {
	if (t == NULL) 
		return 0;
	else
		return 1 + TreeNodeCount(t->left) + TreeNodeCount(t->right);
}

bool TreeIsPerfectlyBalanced(Tree t) {
	
	if (t == NULL) {
		return true;
	}
	if (abs(TreeNodeCount(t->left) - TreeNodeCount(t->right)) <= 1)
		return true && TreeIsPerfectlyBalanced(t->left) && TreeIsPerfectlyBalanced(t->right);
	else 
		return false;
}

