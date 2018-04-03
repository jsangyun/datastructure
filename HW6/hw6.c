#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

struct avl_node   {
    struct avl_node *left_child, *right_child;  /* Subtrees. */
    int data;                   /* Pointer to data. */
};

struct avl_node *root;

// ������ ȸ�� �Լ�
struct avl_node* rotate_right(struct avl_node *parent)
{
	struct avl_node *child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;
	return child;
}

// ���� ȸ�� �Լ�
struct avl_node* rotate_left(struct avl_node *parent)
{
	struct avl_node *child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;
	return child;
}

// ������-���� ȸ�� �Լ�
struct avl_node* rotate_right_left(struct avl_node *parent) 
{
   struct avl_node *child = parent->right_child;
   if (child->left_child->left_child != NULL)                       //���� ll rotate�� �Ѵ�.
   {
      struct avl_node *tmp = child->left_child->left_child;
      parent->right_child = child->left_child;
      parent->right_child->right_child = child;
      child->left_child = tmp;
   }
   else
   {                                                                  //rr rotate�� �Ѵ�.
      struct avl_node *tmp = child->left_child->right_child;
      parent->right_child = child->left_child;
      parent->right_child->right_child = child;
      child->left_child = tmp;
   }
   child = rotate_left(parent);
   return child;
}

// ����-������ ȸ�� �Լ�
struct avl_node* rotate_left_right(struct avl_node *parent)
{
   struct avl_node *child = parent->left_child;                        
   if (child->right_child->left_child != NULL)            //���� �κ� rr rotate�� �Ѵ�.
   {
      struct avl_node *tmp = child->right_child->left_child;
      parent->left_child = child->right_child;
      parent->left_child->left_child = child;
      child->right_child = tmp;
   } 
   else
   {                                                           //ll rotate�� �Ѵ�.
      struct avl_node *tmp = child->right_child->right_child;
      parent->left_child = child->right_child;
      parent->left_child->left_child = child;
      child->right_child = tmp;
   }
   child = rotate_right(parent);
   return child;
}


// Ʈ���� ���̸� ��ȯ
int get_height(struct avl_node *node)
{
	int height=0;
	if( node != NULL )
		height = 1 + max(get_height(node->left_child), get_height(node->right_child));
	return height;
}

// ����� �����μ��� ��ȯ
int get_height_diff(struct avl_node *node) 
{
	if( node == NULL ) return 0;
	return get_height(node->left_child) - get_height(node->right_child);
} 

// Ʈ���� ����Ʈ���� �����
struct avl_node* rebalance(struct avl_node **node)
{
	int height_diff = get_height_diff(*node);
	if( height_diff > 1 ){
		if( get_height_diff((*node)->left_child) > 0 )
			*node = rotate_right(*node);
		else
			*node = rotate_left_right(*node);
	}
	else if ( height_diff < -1 ){
		if( get_height_diff((*node)->right_child) < 0 )
			*node = rotate_left(*node);
		else
			*node = rotate_right_left(*node);
	}
	return *node;
}

// AVL Ʈ���� ���� ����
struct avl_node * avl_add(struct avl_node **root, int new_key)
{
	if( *root == NULL ){
		*root = (struct avl_node *)malloc(sizeof(struct avl_node));
		if(*root == NULL ){
			exit(1);
		}
		(*root)->data = new_key;
		(*root)->left_child = (*root)->right_child = NULL;
	}
	else if( new_key < (*root)->data ){
		(*root)->left_child = avl_add(&((*root)->left_child), new_key);
		*root = rebalance(root);
	}
	else if( new_key > (*root)->data ){
		(*root)->right_child = avl_add(&((*root)->right_child), new_key);
		*root = rebalance(root);
	}
	else{
		printf("�ߺ��� Ű\n");
		exit(1);
	}
	return *root;
}
//����Լ� �����Ǿ�����
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
// AVL Ʈ���� Ž���Լ�
struct avl_node *avl_search(struct avl_node *node, int key) 
{ 
	if( node == NULL ) return NULL; 
	printf("%d ", node->data);
	if( key == node->data ) return node; 
	else if( key < node->data ) 
	   	return avl_search(node->left_child, key); 
	else 
		return avl_search(node->right_child, key); 
} 

void main()
{
	char command;
	int key;
	FILE *input;
	root = NULL;
	input = fopen("input.txt", "r");

	while (1) {
		command = fgetc(input);
		if (feof(input)) break;
		switch (command) {
		case 'i':
			fscanf(input, "%d", &key);
			avl_add(&root, key);
			break;
		default:
			break;
		}
	}

	display(root);

}
