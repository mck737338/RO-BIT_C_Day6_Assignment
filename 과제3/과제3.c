#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
	int data;
	struct _Node* next;
}Node;

typedef struct _Queue {
	Node* front;
	int size;
}Queue;

void enqueue(Queue* q);
void dequeue(Queue* q);
void size(Queue* q);
int front(Queue* q);
int rear(Queue* q);
int isEmpty(Queue* q);
void printQueue(Queue* q);
int readStr();

void main() {
	Queue que = { NULL, 0 };
	Queue* q = &que;

	int fType;
	int value;

	while (1) {
		fType = readStr();		//실행할 함수 입력받기

		switch (fType) {		//각 함수의 값은 readStr() 참조
		case 0:
			enqueue(q);			//Enqueue 실행
			break;
		case 1:
			dequeue(q);			//Dequeue 실행
			break;
		case 2:
			size(q);			//size 실행
			break;
		case 3:
			value = front(q);		//front 실행
			printf("data: %d\n", value);
			break;
		case 4:
			value = rear(q);		//rear 실행
			printf("data: %d\n", value);
			break;
		case 5:
			value = isEmpty(q);		//isEmpty 실행
			printf("isEmpty: %s\n", ((value == 1) ? "true" : "false"));
			break;
		case 6:
			printQueue(q);				//printStack 실행
			break;
		case 7:
			return;		//종료
		default:;		//잘못된 입력은 무시

		}
	}


}

void enqueue(Queue* q) {
	Node* nPtr = (Node*)malloc(sizeof(Node));	//추가할 노드의 메모리 할당
	printf("data: ");
	scanf("%d", &nPtr->data);	//노드의 데이터 저장
	nPtr->next = NULL;
	
	if (q->size == 0) {		//만약 큐가 비었으면 front에 저장
		q->front = nPtr;
	}
	else {
		Node* link = q->front;		//front부터 마지막 노드까지 이동 하여 노드 붙이기
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

void dequeue(Queue* q) {
	if (isEmpty(q) == 1) {
		printf("Queue is Empty\n");		//큐가 비었으면	비어있다고 출력
	}
	else {
		int temp = q->front->data;		//front의 데이터 저장
		Node* p = q->front;				//front의 노드 주소 저장

		q->front = q->front->next;		//front 노드 변경
		q->size--;						//큐의 크기 변경

		printf("data: %d\n", temp);
		
		free(p);			//원래 front 노드의 메모리 할당 해제
	}
}

void size(Queue* q) {
	printf("size: %d\n", q->size);		//크기 출력
}

int front(Queue* q) {
	return q->front->data;		//front의 데이터 반환
}

int rear(Queue* q) {
	if (isEmpty(q) != 0) {		//큐가 비어있지 않으면 데이터 반환
		Node* link = q->front;		//큐의 front부터 마지막 노드까지 이동
		while (link->next != NULL) {
			link = link->next;
		}
		return link->data;		//마지막 노드의 데이터(rear) 반환
	}
}

int isEmpty(Queue* q) {
	if (q->size == 0) {		//큐의 크기가 0이면 1(true) 반환
		return 1;
	}
	else {
		return 0;			//아니라면 0(false) 반환
	}
}

void printQueue(Queue* q) {
	if (isEmpty(q) == 1) {		//큐가 비어있으면 비어있음을 출력
		printf("Queue is Empty\n");
	}
	else {
		Node* link = q->front;		//큐의 front 노드부터 시작
		printf("queue:\n");
		while (link != NULL) {		//마지막 노드까지 반복
			printf("%d\n", link->data);		//현재 노드의 값 출력
			link = link->next;				//다음 노드로 이동, 마지막 노드에는 NULL값이 저장되어있음
		}
	}
}

int readStr() {
	char func_name[8][11] = {		//함수 이름
		"Enqueue", "Dequeue", "size", "front", "rear", "isEmpty", "printQueue", "exit"
	};

	char str[100];
	printf("\n");
	scanf("%s", str);		//문자열 입력 받기

	for (int i = 0; i < 8; i++) {
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