//Sidney Robinson


#include <stdio.h>
#include <stdlib.h>
#include "BST.h"
#include <string.h>


//Helper function which allows us to malloc space for a new insert, especially in the case of empty pointer
BSTObj *new_node(char *new_data)
{
		BSTObj *newNode = malloc(sizeof(BSTObj));
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		char * stringHold = malloc(sizeof(new_data + 1));
		strcpy(stringHold,new_data);
		newNode->term = stringHold;
		return newNode;
}


//Inserts the given Node with the given term/new data value into it's proper place in the binary tree
int insert(char *new_data,  BSTObj **pBST)
{
	if(pBST == NULL)
	{
		return 0;
		//printf("test");
	}
	if(*pBST == NULL)
	{
		*pBST = new_node(new_data);
		 //printf(MSG_NONE);
		return 0;
	}
	if(new_data == NULL)
	{
			
		return 0;
	}
	//BSTObj  *test;
	//test = new_node(new_data);

	if((strcasecmp(new_data,(*pBST)->term)) <0 )
	{
		insert(new_data,&((*pBST)->leftChild));
	}
	else if((strcasecmp(new_data,(*pBST)->term)) > 0 )
	{
		insert(new_data, &((*pBST)->rightChild));
	}
	else if((strcasecmp(new_data,(*pBST)->term)) == 0 )
	{
		return -1;
	}
	
}

//Code to print the traversal inORder
void inorderTraverse(FILE *out, BSTObj *T)
{
	if(T == NULL)
	{
		return;
	}
	
	inorderTraverse(out,T->leftChild);
	
	printf("%s \n" , T->term);
	
	inorderTraverse(out,T->rightChild);
}

//Traverses the tree and prints out the terms in PreOrder order
void preorderTraverse(FILE *out, BSTObj *T)
{
		if(T == NULL)
	{
		return;
	}
	
	
	printf("%s \n", T->term);
	
	preorderTraverse(out,T->leftChild);
	
	preorderTraverse(out,T->rightChild);
}
//Traverses the tree and prints out the terms in postOrder order
void postorderTraverse(FILE *out, BSTObj *T)
{
		if(T == NULL)
	{
		return;
	}
	postorderTraverse(out, T->leftChild);
	
	postorderTraverse(out, T->rightChild);
	
	printf("%s \n", T->term);
}

//Prints out the leaves in order
void inorderLeaves(FILE *out, BSTObj *T)
{
		if(T == NULL)
	{
		return;
	}
	inorderLeaves(out,T->leftChild);
	{
		if(T->leftChild == NULL && T->rightChild == NULL)
		{
			fprintf(out, "%s ", T->term);
		}
	}
	
	
}
//Code used to find a specific node based on the term value of ti
BSTObj *find(char *term_to_find, BSTObj *T)
{
	if(T==NULL)
	{
		return NULL;
	}
	if(strcasecmp((T->term), term_to_find) == 0)
	{
		//printf(MSG_FOUND, term_to_find);
		return T;
	}
	else if(strcasecmp((T->term), term_to_find) > 0)
	{
	 return find(term_to_find,T->leftChild);
	}
	else if(strcasecmp((T->term), term_to_find) < 0)
	{
	return find(term_to_find,T->rightChild);
	}
	return NULL;
}
//Calculates the tree Height by traversing through it add incrementing height
int treeHeight(BSTObj *T, int height)
{
	if(T==NULL)
	{
		return 0;
	}
	int leftH = treeHeight(T->leftChild,height);
	int rightH = treeHeight(T->rightChild,height);
	if(leftH > rightH)
	{
		return leftH+1;
	}
	return rightH+1;
	
}
//copies the tree into a new independent binary tree
BSTObj * copyTree(BSTObj *T)
{
	if(T == NULL)
	{
		return NULL;
	}
	BSTObj * newHold;
	newHold = malloc(sizeof(BSTObj));
	newHold->term = T->term;
	newHold->leftChild = copyTree(T->leftChild);
	newHold->rightChild = copyTree(T->rightChild);
	return newHold;
}
//frees the entire tree
void makeEmpty(BSTObj **pT)
{
	if(*pT == NULL)
	{
		return;
	}
	else
	{
		makeEmpty(&((*pT)->rightChild));
		free((*pT)->term);
		makeEmpty(&((*pT)->leftChild));
		free(*pT);
		*pT = NULL;
	}
	makeEmpty(pT);
	*pT = NULL;
}
//helper function to find the node
int findNode(BSTObj * T)
{
	if (T == NULL)
		return 0;
	
	if(find(T->term, T) != NULL)
	{
		return 1;
	}else
		return 0;
}
//helper function to delete the node
int deleteNode(BSTObj ** T)
{
	if (*T == NULL)
		return 0;
	
	(*T)->term = NULL;
	free(*T);
	*T = NULL;
	return 1;
}
//helper function to take a node and find the far left value
//assume we call it on the right child of the function
BSTObj * findLeftMost(BSTObj * T)
{
	BSTObj * temp =  T;
	while((temp->leftChild) != NULL)
		temp = temp->leftChild;
	
	return temp;
}

//helper function to find the right most node in the tree
BSTObj * findRightMost(BSTObj * T)
{
	BSTObj * temp =  T;
	while((temp->rightChild) != NULL)
		temp = temp->rightChild;
	
	return temp;
}

//deletes an item from the list
int deleteItem(char *term_to_delete, BSTObj **pT)
{
	if (term_to_delete == NULL )
	{
		return 0;
	}

	if(find(term_to_delete, pT) != NULL)
	{
		
		
		if(((&*(find(term_to_delete, pT)->leftChild)) == NULL && ((&*(find(term_to_delete, pT)->rightChild))) == NULL))
		{
	
			deleteNode(&*(find(term_to_delete, pT)));
			return 1;
		}
		
		if ((&*(find(term_to_delete, pT)->rightChild)) == NULL && ((&*(find(term_to_delete, pT)->leftChild)) != NULL))
		{
			BSTObj* dummy = new_node((&*(find(term_to_delete, pT)->leftChild))->term);
			(&*(find(term_to_delete, pT)))->term = dummy->term;
			(&*(find(term_to_delete, pT)))->leftChild = ((&*(find(term_to_delete, pT)->leftChild))->leftChild);
			free(dummy);
			deleteNode((&*(find(term_to_delete, pT)))->leftChild);
			return 1;
		}
		if ((&*(find(term_to_delete, pT)->rightChild)) != NULL)
		{
			
			BSTObj* temp = findLeftMost(&*(find(term_to_delete, pT)->rightChild));
			temp->term = findLeftMost(&*(find(term_to_delete, pT)->rightChild))->term;
			BSTObj* dummy = new_node(temp->term);
		    (&*(find(term_to_delete, pT)))->term = dummy->term;
			deleteNode(&*temp);
			free(dummy);
			return 1;
		}
		
	} else
	return 0;
}








