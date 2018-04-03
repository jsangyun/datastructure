//for visual studio 2013(fscanf_s problem)

#define _CRT_SECURE_NO_WARNING

#include <stdio.h>

#include <stdlib.h>

#include <memory.h>

#include <string.h>

 

typedef int element;

typedef struct _TreeNode

{

	element data;

	struct _TreeNode * left;

	struct _TreeNode * right;

} TreeNode;

 

TreeNode * createTreeNode(void)

{

	TreeNode * Node;

	Node = (TreeNode*)malloc(sizeof(TreeNode));

	

	return Node;

}

 

void setData(TreeNode * node, element data)

{

	node->left = NULL;

	node->right = NULL;

	node->data = data;

}

 

element getData(TreeNode * node)

{

	return node->data;

}

 

void makeLeftSubTree(TreeNode * main, TreeNode * sub)

{

	if (main->left != NULL) {

		exit(1);

	}

	else if (main->left == NULL) {

		main->left = sub;

	}

}

 

void makeRightSubTree(TreeNode * main, TreeNode * sub)

{

	if (main->right != NULL) {

		exit(1);

	}

	else if (main->right == NULL) {

		main->right = sub;

	}

}

 

TreeNode * getLeftSubTree(TreeNode * node)

{

	return node->left;

}

 

TreeNode * getRightSubTree(TreeNode * node)

{

	return node->right;

}

 

void printInorder(TreeNode *root){

	if(root != NULL){

		printInorder(getLeftSubTree(root));

		printf("%d ", root->data);

		printInorder(getRightSubTree(root));

	}

}

 

void printPreorder(TreeNode *root){

	if(root != NULL){

		printf("%d ", root->data );

		printPreorder(getLeftSubTree(root));

		printPreorder(getRightSubTree(root));

	}

}

 

void printPostorder(TreeNode *root){

	if(root != NULL){

		printPostorder(getLeftSubTree(root));

		printPostorder(getRightSubTree(root));

		printf("%d ", root->data);

	}

}

 

int main(void){

	FILE *input;

	input = fopen("input.txt", "r");

	

	char command; //받을 명령어

	

	TreeNode * root = createTreeNode();

	TreeNode * node1 = createTreeNode();

	TreeNode * node2 = createTreeNode();

	TreeNode * node3 = createTreeNode();

	TreeNode * node4 = createTreeNode();

	TreeNode * node5 = createTreeNode();

	TreeNode * node6 = createTreeNode();

	TreeNode * node7 = createTreeNode();

	TreeNode * node8 = createTreeNode();

	TreeNode * node9 = createTreeNode();

	

	setData(root, 54);

	setData(node1, 27);

	setData(node2, 13);

	setData(node3, 1);

	setData(node4, 44);

	setData(node5, 37);

	setData(node6, 89);

	setData(node7, 71);

	setData(node8, 64);

	setData(node9, 92);

	

	makeLeftSubTree(root, node1);

	makeLeftSubTree(node1, node2);

	makeLeftSubTree(node2, node3);

	makeLeftSubTree(node4, node5);

	makeLeftSubTree(node6, node7);

	makeLeftSubTree(node7, node8);

	makeRightSubTree(root, node6);

	makeRightSubTree(node6, node9);

	makeRightSubTree(node1, node4);

	

	while(1){

		command = fgetc(input);

		if(feof(input)) break;

		

		switch(command) {

			case 'i': printf("Inorder:   "); printInorder(root); printf("\n");

					break;

			case 'r': printf("Preorder:  "); printPreorder(root); printf("\n");

					break;

			case 'o': printf("Postorder: "); printPostorder(root); printf("\n");

				break;

			default:

				break;

		}

	}

 

	fclose(input);

    return 0;

}
