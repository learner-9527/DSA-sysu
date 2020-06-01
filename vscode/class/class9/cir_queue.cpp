#include <iostream>
#include <windows.h>
using namespace std;

#define max_size 100

typedef int element_type;

// 环形队列.
struct cir_queue
{
    element_type data[max_size];
    int front;
    int rear;
};

void init_queue(cir_queue* &q)
{
    // 初始front和rear指向0.
    q = new cir_queue;
    q->front = 0;
    q->rear = 0;
}

void destroy(cir_queue* &q)
{
    delete q;
}

bool empty(cir_queue* q)
{
    // 空队当且仅当front和rear重合.
    return (q->front == q->rear);
}

bool enqueue(cir_queue* &q, element_type e)
{
    // 如果队满.
    if ((q->rear + 1) % max_size == q->front)
    {
        return false;
    }
    // rear指向当前队尾元素，仅当front等于rear时rear所指为空.
    q->rear = (q->rear + 1) % max_size;
    q->data[q->rear] = e;
    return true;
}

bool dequeue(cir_queue* &q, element_type &e)
{
    // 如果队空.
    if (q->front == q->rear)
    {
        return false;
    }
    // front所指位置永远为空，可理解为队头元素的前一个.
    q->front = (q->front + 1) % max_size;
    e = q->data[q->front];
}

void display(cir_queue* q)
{
    // count是队中元素个数.
    int count = (q->rear + max_size - q->front) % max_size;
    // i用于遍历输出，从front开始.
    int i = q->front;
    cout << "queue: ";
    while (count > 0)
    {
        // i循环进一，重复count次.
        i = (i + 1) % max_size;
        cout << q->data[i] << " ";
        count--;
    }
    cout << endl;
}

int main()
{
    element_type e;
    cir_queue* q;
    int i;
    init_queue(q);
    for (i = 0; i < 7; i++)
    {
        cin >> e;
        enqueue(q, e);
        display(q);
        if (i % 3 == 0)
        {
            dequeue(q, e);
            display(q);
        }
    }
    display(q);
    system("pause");
    return 0;
}