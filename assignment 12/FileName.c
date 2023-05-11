#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_QUEUE_SIZE 100
typedef int element;
typedef struct { // 큐 타입
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} DequeType;
// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 초기화
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(DequeType* q)
{
	return (q->front == q->rear && q->data[q->front] == 0);
}
// 포화 상태 검출 함수
int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 원형큐 출력 함수
void deque_print(DequeType* q)
{
	printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}
// 삽입 함수
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// 삭제 함수
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
// 삭제 함수
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}
element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}
element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[q->rear];
}


int checking(char* exp) {
	DequeType queue;
	init_deque(&queue);
	int i = 0;
	while (exp[i] != '\0') {
		if (isalnum(exp[i])) {
			add_front(&queue, toupper(exp[i]));
		}
		i++;
	}
	for (i = 0; exp[i] != '\0'; i++) {
		char f, r;
		f = delete_front(&queue);
		r = delete_rear(&queue);
		if (f != r) {
			return 0;
		}
	}
	return 1;
}
int main(void)
{
	for (;;) {
		char palindrome[MAX_QUEUE_SIZE];
		printf("Enter a string (or input 'exit'): ");
		scanf_s(" %[^\n]", palindrome, MAX_QUEUE_SIZE);
		if (palindrome[0] == 'e' && palindrome[1] == 'x' && palindrome[2] == 'i' && palindrome[3] == 't' && palindrome[4] == '\0') {
			printf("program exit\n");
			printf("\n\n----------------------------------------------\n");
			system("pause");
			exit(1);
		}
		int result = checking(palindrome);
		if (result == 0) {
			printf("%s is not a palindrome.\n\n", palindrome);
		}
		else if(result == 1){
			printf("%s is a palindrome.\n\n", palindrome);
		}
	}
	return 0;
}