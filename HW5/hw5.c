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
    //Tree가 비어있으면 NULL값 리턴 
    if(node == NULL){
        return NULL;
    }
    //순환 
    while(node != NULL){
        //값이 같으면 해당 노드 리턴 
	    if(key == node->key){
	        return node;
	    }
	    //node값이 더 크면 왼쪽으로 향함 
	    else if(key < node->key){
	        node = node->left;
	    }
	    //key값이 더 크면 오른쪽으로 향함 
	    else if(key > node->key){
	        node = node->right;
	    }
	}
}
 
//가장 작은 노드를 찾아주는 함수 
TreeNode *minValueNode(TreeNode *node){
    TreeNode *temp;
    temp = node;
    //가장 왼쪽에 있는 노드를 찾는 루프 
    while(temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}
 
void insert_node(TreeNode **root, int key){
	TreeNode *ptr = *root; //현재노드 
	TreeNode *p = NULL; //부모노드 
    //복사를 위한 새로운 노드 생성 
    TreeNode *temp;
    //탐색 
    while (ptr != NULL){
    	//Key값이 같으면 탐색을 멈춘다 
    	if(key == ptr->key){
    		return;
		}
		//현재 노드가 부모 노드가 된다 
		p = ptr;
		//node값이 더 크면 왼쪽
		if(key < ptr->key){
			ptr = ptr->left;
		}
		//key값이 더 크면 오른쪽
		else if(key > ptr->key){
			ptr = ptr->right;
		}
	}
	//트리가 비어있을 때 삽입 가능 
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
   //키가 트리에 없을 경우 에러 띄우기 
   if(ptr == NULL){
		printf("key is not in the tree");
		return;
   }
   
   //자식 노드가 없을 때
   if((ptr->left == NULL) && (ptr->right == NULL)){
		if(p->left == ptr){
			p->left = NULL;
		}
		else{
			p->right = NULL;
		}
   }
   //자식노드가 하나만 있을 때 
   if((ptr->left == NULL) || (ptr->right == NULL)){
		child = (ptr->left != NULL) ? ptr->left : ptr->right;
		if(p->left == ptr){
			p->left = child;
		}
		else{
			p->right = child;
		}
   }
   //자식이 두개일 경우
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
