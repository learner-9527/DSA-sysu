#include <iostream>
#include <windows.h>
using namespace std;

typedef int element_type;

// �������ݽ��.
struct node{
    element_type data;
    node* next;
};

// ����ͷ���.
struct queue{
    // �ֱ�����ָ���ͷ���Ͷ�β���.
    node* front;
    node* rear;
};

void init_queue(queue* &q)
{
    q = new queue;
    // ��ͷ��βΪNULL��ʾ�ն�.
    q->front = NULL;
    q->rear = NULL;
}

bool empty(queue* q)
{
    // �ӿյ��ҽ���frontΪNULL���ҽ���rearΪNULL.
    return (q->front == NULL);
}

// �������迼�Ƕ�������ӱسɹ�������void.
void enqueue(queue* &q, element_type e)
{
    node* temp;
    temp = new node;
    temp->data = e;
    temp->next = NULL;
    // �ж��Ƿ�ӿ�.
    if (q->front == NULL)
    {
        // �ӿ�����Ҫʹfrontָ��temp.
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
    // �ӿ������ʧ��.
    if (q->rear == NULL)
    {
        return false;
    }
    // frontָ��temp�ĺ�̽��.
    q->front = temp->next;
    e = temp->data;
    // ���temp�Ƕ�βԪ��.
    if (q->rear == temp)
    {
        // rearָ��NULL����ʾ�ӿ�.
        q->rear = NULL;
    }
    // ����rear���øı�.
    delete temp;
    return true;
}

void destroy(queue* &q)
{
    node* p = q->front;
    node* pre = q->front;
    // ɾ��ͷ���.
    delete q;
    // ɾ������.
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