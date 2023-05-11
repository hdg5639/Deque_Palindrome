#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_QUEUE_SIZE 100
typedef int element;
typedef struct { // ť Ÿ��
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} DequeType;
// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// �ʱ�ȭ
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}
// ���� ���� ���� �Լ�
int is_empty(DequeType* q)
{
	return (q->front == q->rear && q->data[q->front] == 0);
}
// ��ȭ ���� ���� �Լ�
int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// ����ť ��� �Լ�
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
// ���� �Լ�
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// ���� �Լ�
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
// ���� �Լ�
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}
element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}
element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
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