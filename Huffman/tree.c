#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include <assert.h>

void setChildren(struct tree *root); //function that I created for tree.c

typedef struct tree
{
	int data;
	struct tree *parent;
	struct tree *left;
	struct tree *right;
}TREE;

//creates a tree with the given arguments ( O(1) ).
TREE *createTree(int data, TREE *left, TREE *right) {

	TREE *head = (TREE*)malloc(sizeof(TREE));

	assert( head != NULL ); //ensure that the tree created is not NULL
	
    //setting the head's data 
	head->data = data;
	head->left = left;
	head->right = right;
	head->parent = NULL;

    
	if(left!=NULL) //removes other parent pointers to the left node passed into createTree
	{
        setChildren(left);
		left->parent = head;
	}
	if(right!=NULL) //removes other parent pointers to the right node passed into createTree
	{
        setChildren(right); 
		right->parent = head;
	}

	return head;

}

//returns data of the node ( O(1) ).
int getData(TREE *root) {

	assert(root!=NULL); //ensure that it is not NULL
	return root->data;
}

//returns pointer to the parent node ( O(1) )
TREE *getParent(TREE *root) { 

	assert(root!=NULL); //ensure that root isn't NULL
	return root->parent;
}

//returns left tree ( O(1) )
TREE *getLeft(TREE *root) {

	assert(root!=NULL); //ensure that it isn't NULL
	return root->left;
}

// returns pointer to right child of given root ( O(1) )
TREE *getRight(TREE *root) {

	assert(root!=NULL); //ensure that it isn't NULL
	return root->right;
}

//takes out root's left node and then replaces it ( O(1) )
void setLeft(TREE *root, TREE *left) {

    //ensure that both left and root are not null
	assert(root != NULL);
	assert(left != NULL);

	if(root->left != NULL) {
		setChildren(root->left); //take out the left node
	}

	root->left = left; //replace it with what has been passed in ^
	root->left->parent=root; //set the new left's parent to the root

}

//takes out root's right node and then replaces it ( O(1) )
void setRight(TREE *root, TREE *right) {

    //ensure that both the root and right node are not NULL
	assert(root != NULL);
	assert(right != NULL);

	if(root->right != NULL) {
		setChildren(root->right); //take out the current right node
	}

	root->right = right; //replace it with that has been passed in
	root->right->parent=root; //set the new right's parent to the root
}

void destroyTree(TREE *root) //Traverses a tree in post-order and frees every node. O(n).
{
    //recursively checks whether left and right are NOT NULL and then destroys the tree and then root
	if (root->right != NULL ) {
        	destroyTree(root->right);
    	}  
    	if ( root->left != NULL ) {
        	destroyTree(root->left);
    	}

	free(root);
}

//if the parent has child (children) then it sets the right and left pointers to NULL ( O(1) ).
//I implemented the function because it helped me understand tree.c better and helped me with huffman
void setChildren(TREE *root) { 

	if (root->parent == NULL)
		return;
	if(root->parent->right==root) {
		root->parent->right = NULL; //set the parent's left child back to NULL
    	}
	if(root->parent->left==root) {
		root->parent->left = NULL; //set the parent's right child back to NULL
    }
}

