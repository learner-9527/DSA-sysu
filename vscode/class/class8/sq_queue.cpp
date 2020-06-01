#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

#define max_size 50

typedef int element_type;

/**
 * 顺序队列.
 * @param data 队列数组.
 * @param front 指向队头元素的前一个元素.
 * @param rear 指向队尾元素.
 */
typedef struct{
    element_type data[max_size];
    int front;
    int rear;
} sq_queue;

void init_queue(sq_queue* &q);
void destroy_queue(sq_queue* &q);
bool empty(sq_queue* q);
bool enqueue(sq_queue* &q, element_type e);
bool dequeue(sq_queue* &q, element_type &e);
void display(sq_queue* q);

void init_queue(sq_queue* &q)
{
    q = new sq_queue;
    // 初始时，队列为空，front和rear指向-1.
    q->front = -1;
    q->rear = -1;
}

void destroy_queue(sq_queue* &q)
{
    delete q;
}

bool empty(sq_queue* q)
{
    return (q->front == q->rear);
}

bool enqueue(sq_queue* &q, element_type e)
{
    if (q->rear == max_size - 1)
    {
        return false;
    }
    q->data[++q->rear] = e;
    return true;
}

bool dequeue(sq_queue* &q, element_type &e)
{
    if (q->front == q->rear)
    {
        return false;
    }
    e = q->data[++q->front];
    return true;
}

void display(sq_queue* q)
{
    cout << "queue: ";
    for (int i = q->front + 1; i <= q->rear; i++)
    {
        cout << q->data[i] << " ";
    }
    cout << endl;
}

int main()
{
    vector<element_type> arr(10);
    element_type e;
    sq_queue* Q;
    init_queue(Q);
    for (int i = 0; i < 10; i++)
    {
        cin >> arr[i];
        enqueue(Q, arr[i]);
        display(Q);
        if ((i + 1) % 3 == 0)
        {
            dequeue(Q, e);
            display(Q);
        }
    }
    display(Q);
    system("pause");
    return 0;
}