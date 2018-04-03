#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define KEY_SIZE   20   // 탐색키의 최대길이  
#define TABLE_SIZE   7   // 해싱 테이블의 크기 
#define equal(e1,e2) (!strcmp(e1.key,e2.key))

int binaryDeposit[8 * 2];
int transform(char *key);

typedef struct element
{
   char key[KEY_SIZE];
} element;

struct list
{
   element item;
   struct list *link;
};

struct list* hash_table[TABLE_SIZE];

int* decimal_to_binary(int* decimal){
   int binary[20] = {};
   int binaryDigit = 0;
   while (*decimal) {
      binary[binaryDigit++] = *decimal % 2;
      *decimal /= 2;
   }
   *decimal = binaryDigit;
   return binary;
}

int hash_function(char *key)
{
   int i;
   int cmd = transform(key);
   int *binary = decimal_to_binary(&cmd); 
   int binary_list[20];
   for (i = 0; i < cmd; i++) {
      binary_list[i] = binary[cmd - 1 - i];
   }
   int middlepoint = cmd / 2 - 1;
   return binary_list[middlepoint] + binary_list[middlepoint + 1] + binary_list[middlepoint + 2];
}

void hash_chain_find(element item, struct list *ht[])
{
   struct list* chase =ht[hash_function(item.key)];
   while (chase) {
      if (equal(item,chase->item)) {
         printf("키를 찾았음(item.key: %s)\n", item.key);
         return;
      }
      else chase = chase->link;
   }
   printf("키를 찾지못했음(item.key: %s)\n", item.key);
}

void hash_chain_print(struct list *ht[])
{
   struct list *node;
   int i;
   for (i = 0; i<TABLE_SIZE; i++) {
      printf("[%d] ->", i);
      for (node = ht[i]; node; node = node->link) {
         printf("%s->", node->item.key);
      }
      printf("\n");
   }
}

// 문자로 된 탐색키를 숫자로 변환
int transform(char *key)
{
   int number = 0;
   while (*key) number += *(key++);
   return number*number;
}

void hash_chain_add(element item, struct list *ht[])
{
   int hash_value = hash_function(item.key);
   struct list *ptr;
   struct list *node_before = NULL, *node = ht[hash_value];
   for (; node; node_before = node, node = node->link) {
      if (equal(node->item, item)) {
         printf("input err\n");
         return;
      }
   }

   ptr = (struct list *)malloc(sizeof(struct list));
   ptr->item = item;
   ptr->link = NULL;

   if (node_before) node_before->link = ptr;
   else ht[hash_value] = ptr;
}
////////실습시간에 다룬 코드(완성된 상태): END//////////

void main(int argc, const char** argv)
{

   FILE* f;
   element tmp;
   char input[KEY_SIZE] = " ";
   f = fopen(argv[1], "r");
   while (fscanf(f, "%s", &input) != EOF) {
      strcpy(tmp.key, input);
      hash_chain_add(tmp, hash_table);
   }
   hash_chain_print(hash_table);

   strcpy(tmp.key, "x");
   hash_chain_find(tmp, hash_table);
   strcpy(tmp.key, "c");
   hash_chain_find(tmp, hash_table);
}
