#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

struct avl_node {
	struct avl_node *left_child, *right_child; /* Subtrees. */
	int data; /* Pointer to data. */
};

void display(struct avl_node *node)
{
	if (node != NULL) {
		printf("(");
		display(node->left_child);
		printf("%d", node->data);
		display(node->right_child);
		printf(")");
	}
}

// Ʈ���� ���̸� ��ȯ
int get_height(struct avl_node *node)
{
	int height = 0;
	height = Max(get_height(node->left_child), get_height(node->right_child));
	return height+1;
}

// ����� �����μ��� ��ȯ
int get_height_diff(struct avl_node *node)
{
	int height_diff = 0;
	if( node == NULL ) return 0;
	height_diff = get_height(node->left_child) - get_height(node->right_child);
	return height_diff;
}

struct avl_node* rotate_left(struct avl_node *parent) { 
	struct avl_node *child = parent->right_child;
	
	parent->right_child = child->left_child;
	child->left_child = parent;
	
	return child; 
}

struct avl_node* rebalance(struct avl_node **node)
{
	int height_diff = get_height_diff(*node); //�����μ��� �������� �Լ�
	printf("�����μ�: %d node: %d\n", height_diff, (*node)->data);
	if ( height_diff < -1 ){ 
		if( get_height_diff((*node)->right_child) < 0 )
		*node = rotate_left(*node);	
	}
	return *node;
}

struct avl_node* avl_add(struct avl_node **root, int new_key)
{
	if( *root == NULL ){
		*root = (struct avl_node *)malloc(sizeof(struct avl_node));
		if( *root == NULL ){
			exit(1);
		}
		(*root)->data = new_key;
		(*root)->left_child = (*root)->right_child = NULL;
	}
	
	else if( new_key > (*root)->data ){
		(*root)->right_child = avl_add(&((*root)->right_child), new_key);
		*root = rebalance(root); //STEP1������ �����μ��� ����Ѵ�
	}
	else{
		printf("�ߺ��� Ű\n");
		exit(1);
	}
	return *root;
}

struct avl_node *root; //�۷ι��� ������

void main()
	{
	//7,8,9,10,11
	avl_add(&root, 7);
	avl_add(&root, 8);
	avl_add(&root, 9);
	avl_add(&root, 10);
	avl_add(&root, 11);
	display(root);
}

