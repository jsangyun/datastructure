//for visual studio 2013(fscanf_s problem)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>
 
typedef struct TreeNode {
    int key;
    struct TreeNode *left, *right;
} TreeNode;
 
void display(TreeNode *p)
{
    if (p != NULL) {
        printf("(");
        display(p->left);
        printf("%d", p->key);
        display(p->right);
        printf(")");
    }
}
 
/*
We will implement binary search tree ADT with the three main functions
using iteration: insert, delete, and search. 
*/
TreeNode *search(TreeNode *node, int key)
{
    //Tree�� ��������� NULL�� ���� 
    if(node == NULL){
        return NULL;
    }
    //��ȯ 
    while(node != NULL){
        //���� ������ �ش� ��� ���� 
	    if(key == node->key){
	        return node;
	    }
	    //node���� �� ũ�� �������� ���� 
	    else if(key < node->key){
	        node = node->left;
	    }
	    //key���� �� ũ�� ���������� ���� 
	    else if(key > node->key){
	        node = node->right;
	    }
	}
}
 
//���� ���� ��带 ã���ִ� �Լ� 
TreeNode *minValueNode(TreeNode *node){
    TreeNode *temp;
    temp = node;
    //���� ���ʿ� �ִ� ��带 ã�� ���� 
    while(temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}
 
void insert_node(TreeNode **root, int key){
	TreeNode *ptr = *root; //������ 
	TreeNode *p = NULL; //�θ��� 
    //���縦 ���� ���ο� ��� ���� 
    TreeNode *temp;
    //Ž�� 
    while (ptr != NULL){
    	//Key���� ������ Ž���� ����� 
    	if(key == ptr->key){
    		return;
		}
		//���� ��尡 �θ� ��尡 �ȴ� 
		p = ptr;
		//node���� �� ũ�� ����
		if(key < ptr->key){
			ptr = ptr->left;
		}
		//key���� �� ũ�� ������
		else if(key > ptr->key){
			ptr = ptr->right;
		}
	}
	//Ʈ���� ������� �� ���� ���� 
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	if(temp == NULL){
		return;
	}
	temp->key = key;
	temp->left = temp->right = NULL; 
	if(p != NULL){
		if(key < p->key){
			p->left = temp;
		}
		else{
			p->right = temp;
		}
	}
	else{
		*root = temp;
	}
}
 
 
 
TreeNode *delete_node(TreeNode *node, int key)
{
    //If the node to be deleted has both children, it is replaced with the smallest node in the right subtree.
   TreeNode *ptr, *p;
   TreeNode *p_replace, *replace;
   TreeNode *child;
   
   p = NULL;
   ptr = node;
   while(ptr != NULL && ptr->key != key){
		p = ptr;
		ptr = (key < ptr->key) ? ptr->left : ptr->right;
   }
   //Ű�� Ʈ���� ���� ��� ���� ���� 
   if(ptr == NULL){
		printf("key is not in the tree");
		return;
   }
   
   //�ڽ� ��尡 ���� ��
   if((ptr->left == NULL) && (ptr->right == NULL)){
		if(p->left == ptr){
			p->left = NULL;
		}
		else{
			p->right = NULL;
		}
   }
   //�ڽĳ�尡 �ϳ��� ���� �� 
   if((ptr->left == NULL) || (ptr->right == NULL)){
		child = (ptr->left != NULL) ? ptr->left : ptr->right;
		if(p->left == ptr){
			p->left = child;
		}
		else{
			p->right = child;
		}
   }
   //�ڽ��� �ΰ��� ���
   else{
		replace = ptr->right;
		while(replace->left != NULL){
			p_replace = replace;
			replace = replace->left;
		}
		if(p_replace->left != NULL){
			p_replace->left = replace->right;
		}
		else{
			p_replace->right = replace->right;
		}
		ptr->key = replace->key;
		ptr = replace;
   }
   free(ptr); 
}
void main(int argc, char *argv[])
{
    char command;
    int key;
    FILE *input;
    TreeNode *root = NULL;
 
    if (argc == 1) input = fopen("input.txt", "r");
    else input = fopen(argv[1], "r");
    while (1) {
        command = fgetc(input);
        if (feof(input)) break;
        switch (command) {
        case 'i':
            fscanf(input, "%d", &key);
            insert_node(&root, key);
            break;
        case 'd':
            fscanf(input, "%d", &key);
            delete_node(root, key);
            break;
        case 's':
            fscanf(input, "%d", &key);
            if (search(root, key) != NULL)printf("key is in the tree: %d\n", key);
            else printf("key is not in the tree: %d\n", key);
            break;
        case 'p':
            display(root);
            printf("\n");
            break;
        default:
            break;
        }
    }
} 
