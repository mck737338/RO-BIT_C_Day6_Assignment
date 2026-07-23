#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
	int data;
	struct _Node* next;
}Node;

typedef struct _Stack {
	Node* top;
	int size;
}Stack;

void push(Stack* stk);
void pop(Stack* stk);
int top(Stack* stk);
int isEmpty(Stack* stk);
void printStack(Stack* stk);
int readStr();

void main() {
	Stack stk = { NULL, 0 };
	Stack* s = &stk;

	int fType;
		int value;

	while (1) {
		fType = readStr();		//실행할 함수 입력받기

		switch (fType) {		//각 함수의 값은 readStr() 참조
			case 0:
				push(s);
				break;
			case 1:
				pop(s);		//pop 실행
				break;
			case 2:
				printf("size: %d\n", s->size);		//size 실행,
				break;
			case 3:
				value = top(s);		//top 실행
				printf("data: %d\n", value);
				break;
			case 4:
				value = isEmpty(s);		//isEmpty 실행
				printf("isEmpty: %s\n", ((value == 1) ? "true": "false"));
				break;
			case 5:
				printStack(s);			//printStack 실행
				break;
			case 6:
				return;		//종료
			default:;		//잘못된 입력은 무시

		}
	}
}

void push(Stack* stk) {
	Node* nPtr = (Node*)malloc(sizeof(Node));		//추가할 노드의 메모리 할당
	printf("data: ");
	scanf("%d", &nPtr->data);	//노드의 데이터 저장
	nPtr->next = stk->top;	//새 노드의 끝에 스택의 top 노드 연결
	stk->top = nPtr;		//스택의 top을 새 노드로 변경
	stk->size++;			//스택 크기 변경
}

void pop(Stack* stk) {
	if (isEmpty(stk) == 1) {		//스택이 비어있으면 비어있음을 출력
		printf("Stack is Empty\n");
	}
	else {		//스택에 값이 존재할 때
		int temp = stk->top->data;		//top 노드의 값 저장
		Node* p = stk->top;				//top 노드의 주소 저장

		stk->top = stk->top->next;		//스택의 top 노드를 변경
		stk->size--;					//스택의 크기 변경

		printf("data: %d\n", temp);		//원래 top 노드의 값 출력

		free(p);		//원래 top 노드 주소의 메모리 할당 해제
	}
}

int top(Stack* stk) {
	int temp = stk->top->data;		//스택의 top 노드 값 읽기
	return temp;
}

int isEmpty(Stack* stk) {
	if (stk->size == 0) {		//스택의 크기가 0이면 빈 스택으로 판단
		return 1;
	}
	else {
		return 0;
	}
}

void printStack(Stack* stk) {
	if (isEmpty(stk) == 1) {		//스택이 비어있으면 비어있음을 출력
		printf("Stack is Empty\n");
	}
	else {
		Node* link = stk->top;		//스택의 top 노드부터 시작
		printf("stack:\n");
		while (link != NULL) {		//마지막 노드까지 반복
			printf("%d\n", link->data);		//현재 노드의 값 출력
			link = link->next;				//다음 노드로 이동, 마지막 노드에는 NULL값이 저장되어있음
		}
	}
}

int readStr() {
	char func_name[7][11] = {		//함수 이름
		"push", "pop", "size", "top", "isEmpty", "printStack", "exit"
	};

	char str[100];
	printf("\n");
	scanf("%s", str);		//문자열 입력 받기

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 20; j++) {
			if (str[j] != func_name[i][j]) {		//문자열과 함수 이름이 다르면 스킵
				break;
			}
			if (str[j] == NULL || func_name[i][j] == NULL) {		//문자열이 끝나면 함수 종류를 반환
				return i;
			}
		}
	}

	return -1;
}