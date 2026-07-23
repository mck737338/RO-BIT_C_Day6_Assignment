#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
	char data;
	struct _Node* next;
}Node;

typedef struct _String {
	Node* first;
	int size;
}Str;

void push(Str* stk);
char pop(Str* stk);
void enqueue(Str* q);
char dequeue(Str* q);
void inputStr(Str* stk, Str* q);
void isPalind(Str* stk, Str* q);

void main() {
	Str stack = { NULL, 0 };
	Str queue = { NULL, 0 };

	Str* stk = &stack;
	Str* q = &queue;

	inputStr(stk, q);
	isPalind(stk, q);

}

void push(Str* stk, char ip) {
	Node* nPtr = (Node*)malloc(sizeof(Node));		//추가할 노드의 메모리 할당
	nPtr->data = ip;
	nPtr->next = stk->first;	//새 노드의 끝에 스택의 first 노드 연결
	stk->first = nPtr;		//스택의 first을 새 노드로 변경
	stk->size++;			//스택 크기 변경
}

char pop(Str* stk) {
	char temp = stk->first->data;		//first 노드의 값 저장
	Node* p = stk->first;				//first 노드의 주소 저장

	stk->first = stk->first->next;		//스택의 first 노드를 변경
	stk->size--;					//스택의 크기 변경

	free(p);		//원래 first 노드 주소의 메모리 할당 해제
	return temp;
}

void enqueue(Str* q, char ip) {
	Node* nPtr = (Node*)malloc(sizeof(Node));	//추가할 노드의 메모리 할당
	nPtr->data = ip;
	nPtr->next = NULL;

	if (q->size == 0) {		//만약 큐가 비었으면 first에 저장
		q->first = nPtr;
	}
	else {
		Node* link = q->first;		//first부터 마지막 노드까지 이동 하여 노드 붙이기
		while (link->next != nPtr) {
			if (link->next == NULL) {
				link->next = nPtr;
			}
			else {
				link = link->next;
			}
		}
	}

	q->size++;

}

char dequeue(Str* q) {
	char temp = q->first->data;		//first의 데이터 저장
	Node* p = q->first;				//first의 노드 주소 저장

	q->first = q->first->next;		//first 노드 변경
	q->size--;						//큐의 크기 변경

	free(p);			//원래 first 노드의 메모리 할당 해제

	return temp;
}

void inputStr(Str* stk, Str* q) {
	char ip;

	while (1) {
		scanf("%c", &ip);
		if (ip == '\n') {
			return;
		}
		push(stk, ip);
		enqueue(q, ip);
	}
}

void isPalind(Str* stk, Str* q) {
	int d1, d2;
	for (int i = 0; i < stk->size; i++) {
		d1 = pop(stk);
		d2 = dequeue(q);
		if (d1 != d2) {
			printf("the String is not Palindraome");
			return;
		}
	}

	printf("the String is Palindraome");
}