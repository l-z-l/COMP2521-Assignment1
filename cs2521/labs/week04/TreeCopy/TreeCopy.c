
#include "tree.h"
#include <stdlib.h>

int TreeHeightCount(Tree t){
	if (t == NULL) {
		return 0;
	} else {
		if (TreeHeightCount(t->left) >= TreeHeightCount(t->right)) {
			return TreeHeightCount(t->left) + 1;
		} else {
			return TreeHeightCount(t->right) + 1;
		}
	}
}
Tree clone(Tree t, int depth) {
	if (t == NULL) 
		return t;
	
	//create new node and make it a copy of node pointed by t
	Tree temp = malloc(sizeof(*t));
	temp->value = t->value;		  //copying data
	temp->left = NULL;
	temp->right = NULL;
	depth--;
	if (depth < 0)
	{
		return temp;
	}
	temp->left = clone(t->left, depth);   //cloning left child
	temp->right = clone(t->right, depth); //cloning right child
	return temp;
}

Tree TreeCopy(Tree t, int depth) {
	if (depth < 0) 
		return NULL;
	else if (TreeHeightCount(t) <= depth) {
		return t;
	}
	else {
		return clone(t, depth);
	}
	return NULL;
}

