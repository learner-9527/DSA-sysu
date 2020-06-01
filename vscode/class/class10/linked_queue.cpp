#include <iostream>
#include <windows.h>
using namespace std;

typedef int element_type;

// 队列数据结点.
struct node{
    element_type data;
    node* next;
};

// 队列头结点.
struct queue{
    // 分别用于指向队头结点和队尾结点.
    node* front;
    node* rear;
};

void init_queue(queue* &q)
{
    q = new queue;
    // 队头队尾为NULL表示空队.
    q->front = NULL;
    q->rear = NULL;
}

bool empty(queue* q)
{
    // 队空当且仅当front为NULL当且仅当rear为NULL.
    return (q->front == NULL);
}

// 链表无需考虑队满，入队必成功，返回void.
void enqueue(queue* &q, element_type e)
{
    node* temp;
    temp = new node;
    temp->data = e;
    temp->next = NULL;
    // 判断是否队空.
    if (q->front == NULL)
    {
        // 队空则需要使front指向temp.
        q->front = temp;
    }
    else
    {
        q->rear->next = temp;
    }
    q->rear = temp;
}

bool dequeue(queue* &q, element_type &e)
{
    node* temp = q->front;
    // 队空则出队失败.
    if (q->rear == NULL)
    {
        return false;
    }
    // front指向temp的后继结点.
    q->front = temp->next;
    e = temp->data;
    // 如果temp是队尾元素.
    if (q->rear == temp)
    {
        // rear指向NULL，表示队空.
        q->rear = NULL;
    }
    // 否则rear不用改变.
    delete temp;
    return true;
}

void destroy(queue* &q)
{
    node* p = q->front;
    node* pre = q->front;
    // 删除头结点.
    delete q;
    // 删除链表.
    while(p->next != NULL)
    {
        p = p->next;
        delete pre;
        pre = p;
    }
    delete pre;
}

void display(queue* q)
{
    node* p = q->front;
    cout << "queue: ";
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

int main()
{
    queue* q;
    element_type e;
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
    system("pause");
    return 0;
}