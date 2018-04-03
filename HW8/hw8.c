#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STACK_SIZE 20
typedef int element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

char tmp[MAX_STACK_SIZE] = "";

// 스택 초기화 함수
void init(StackType *s) {
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType *s) {
	return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType *s) {
	return (s->top == (MAX_STACK_SIZE-1));
}

// 삽입함수
void push(StackType *s, element item) {
	if ( is_full(s) ) {
		fprintf(stderr," \n");
		return;
	}
	else s->stack[++(s->top)] = item;
}

// 삭제함수
element pop(StackType *s) {
	if ( is_empty(s) ) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	} else return s->stack[(s->top)--];
}

// 피크함수
element peek(StackType *s) {
	if ( is_empty(s) ) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	} else return s->stack[s->top];
}

// 연산자의 우선순위를 반환한다.
int prec(char op) {
	switch(op){
		case '(': case ')': return 0;
		case '+': case '-': return 1;
		case '*': case '/': return 2;
		}
	return -1;
}

//infix to postfix
void infix_to_postfix(char infix[],char postfix[])
{
    StackType s;
    char x,token;
    int i,j;    //i-index of infix, j-index of postfix
    init(&s);
    j=0;
	
    for(i=0;infix[i]!='\0';i++)
    {
        token=infix[i];
        if(isalnum(token))
            postfix[j++]=token;
        else
            if(token=='(')
               push(&s,'(');
        else
            if(token==')')
                while((x=pop(&s))!='(')
                      postfix[j++]=x;
                else
                {
                    while(!is_empty(&s) && (prec(token) <= prec(peek(&s))))
                    {
                        x=pop(&s);
                        postfix[j++]=x;
                    }
                    push(&s,token);
                }
    }
 
    while(!is_empty(&s))
    {
        x=pop(&s);
        postfix[j++]=x;
    }
 
    postfix[j]='\0';
	printf("\npostfix_to_infix expression: %s", postfix);
}

char* postfix_to_infix(char expression[])
{
	printf("\ninfix_to_postfix expression: ");
	StackType s;
	StackType index;
	int size = strlen(expression);
	int i=0;
	char cmd;
	char op1, op2;
	init(&s);
	init(&index);
	while(i < size){
		cmd  = expression[i++];
		if(isdigit(cmd)){
			push(&s, cmd);
		}
		else{
			while(1){
				op2 = pop(&s);
				op1 = peek(&s);
				push(&index, op2);
				if(isdigit(op2) && isdigit(op1)){
					push(&index, cmd);
					while(!is_empty(&s)){
						push(&index, pop(&s));
					}
					break;
				}
				else{
					push(&index, pop(&s));
				}
			}
		}
		if(i < size && is_empty(&s)){
			while(!is_empty(&index)) push(&s, pop(&index));
		}
		while(!is_empty(&index)){
			char cmd;
			cmd = pop(&index);
			if(isdigit(cmd)){
				printf("((");
				printf("%c", cmd);
			}
			else if(prec(cmd) == 1){
				printf("%c", cmd);
				printf("%c", pop(&index));
				printf(")");
			}
			else{
				printf("%c", cmd);
				printf("%c", pop(&index));
				printf(")\n");
			}
		}
	}
	return expression;
}

int postfixEval(char exp[])
{   
	StackType s;
	init(&s);
  	int i = 0;
	if(!&s){
		return -1;
	}
	for(i = 0; exp[i]; ++i){
		if(isdigit(exp[i])){
			push(&s, exp[i] - '0');
		}
		else{
			int value1 = pop(&s);
			int value2 = pop(&s);
			switch(exp[i]){
				case '+':
					push(&s, value2 + value1);
					break;
				case '-':
					push(&s, value2 - value1);
					break;
				case '*':
					push(&s, value2*value1);
					break;
				case '/':
					push(&s, value2/value1);
					break;
				default:
					break;
			}	
		}
	}
	return pop(&s);
}

int main() { 

	FILE *f;
	char postfix[30];
	char* tmp = (char*)malloc(sizeof(char)*20);
	
	f=fopen("input1.txt","r");
	fscanf(f,"%s", tmp);
	infix_to_postfix(tmp,postfix);
	printf("\neval: %d \n", postfixEval(postfix)); 

	f=fopen("input2.txt","r");
	fscanf(f,"%s", tmp);
	postfix_to_infix(tmp);                   
	printf("eval: %d \n", postfixEval(tmp)); 
	
	return 0;
}
