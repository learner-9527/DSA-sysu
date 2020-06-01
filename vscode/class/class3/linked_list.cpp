#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef int element_type;
typedef struct linked_node{
    element_type data;
    struct linked_node* next;
} node;

void create_list_first(node* &L, element_type arr[], int n);
void create_list_rear(node* &L, element_type arr[], int n);
void init_list(node* &L);
void destroy_list(node* &L);
bool empty_list(node* L);
int get_length(node* L);
void disply_list(node* L);
bool get_element(node* L, int i, element_type &e);
int locate_element(node* &L, element_type e);
bool insert_list(node* &L, int i, element_type e);
bool delete_element(node* &L, int i, element_type &e);
void split(node* &L1, node* &L2);
bool del_max_node(node* &L);

void create_list_first(node* &L, element_type arr[], int n)
{
    node* temp;
    L = (node*)malloc(sizeof(node));
    L->next = NULL;
    for (int i = 0; i < n; i++)
    {
        temp = (node*)malloc(sizeof(node));
        temp->data = arr[i];
        temp->next = L->next;
        L->next = temp;
    }
}

void create_list_rear(node* &L, element_type arr[], int n)
{  
    node* rear, * temp;
    L = (node*)malloc(sizeof(node));
    // 不需要L->next = NULL，后续对rear赋值一次即可.
    rear = L;
    for (int i = 0; i < n; i++)
    {
        temp = (node*)malloc(sizeof(node));
        temp->data = arr[i];
        rear->next = temp;
        rear = temp;
    }
    rear->next = NULL;
}

void init_list(node* &L)
{
    L = (node*)malloc(sizeof(node));
    L->next = NULL;
}

/**
 * 销毁整个链表，包括头结点. T(n) = O(n)
 */
void destroy_list(node* &L)
{
    node* p, * pre;
    pre = L;
    p = L;
    while (p->next != NULL)
    {
        p = p->next;
        free(pre);
        pre = p;
    }
    free(pre);
}

bool empty_list(node* L)
{
    return (L->next == NULL);
}

int get_length(node* L)
{
    int n = 0;
    node* p = L;
    while (p->next != NULL)
    {
        p = p->next;
        n++;
    }
    return n;
}

void disply_list(node* L)
{
    node* p = L;
    printf("linked list: ");
    while (p->next != NULL)
    {
        p = p->next;
        printf("%d ", p->data);
    }
    printf("\n");
}

bool get_element(node* L, int i, element_type &e)
{
    node* p = L;
    int j = 0;
    if (i < 1)
    {
        return false;
    }
    while (j < i && p->next != NULL)
    {
        p = p->next;
        j++;
    }
    if (j < i)
    {
        return false;
    }
    e = p->data;
    return true;
}

int locate_element(node* L, element_type e)
{
    int idx;
    node* p = L;
    while (p->next != NULL)
    {
        p = p->next;
        idx++;
        if (p->data == e)
        {
            break;
        }
    }
    if (p->data == e)
    {
        return idx;
    }
    else
    {
        return 0;
    }
}

/**
 * 插入结点. T(n) = O(n)
 * @param L 原链表.
 * @param i 在逻辑序号为i的结点之前插入结点，i取值1到n+1，n+1表示在末尾插入.
 * @param e 待插入的数据元素.
 * @return 参数i取值不合法时返回false.
 */
bool insert_list(node* &L, int i, element_type e)
{
    // pre表示插入位置的前驱结点，temp用于插入操作.
    node* pre = L;
    node* temp;
    int j = 0;
    if (i < 1)
    {
        return false;
    }
    i--;
    while (j < i && pre->next != NULL)
    {
        pre = pre->next;
        j++;
    }
    if (j < i)
    {
        return false;
    }
    else
    {
        temp = (node*)malloc(sizeof(node));
        temp->data = e;
        temp->next = pre->next;
        pre->next = temp;
        return true;
    }
}

bool delete_element(node* &L, int i, element_type &e)
{
    // pre表示删除结点的前驱结点，temp用于删除操作.
    node* pre = L, * temp;
    int j = 0;
    if (i < 1)
    {
        return false;
    }
    i--;
    while (j < i && pre->next != NULL)
    {
        pre = pre->next;
        j++;
    }
    if (j < i || pre->next == NULL)
    {
        return false;
    }
    else
    {
        temp = pre->next;
        e = temp->data;
        pre->next = temp->next;
        free(temp);
        return true;
    }
}

/**
 * 分开链表中逻辑序号为奇数和偶数的元素，分别放在 L1和 L2中.
 * @param L1 原链表，且将用于顺序存放奇数元素.
 * @param L2 用于逆序存放偶数元素.
 */
void split(node* &L1, node* &L2)
{
    node* p = L1;
    node* temp;
    int i = 0;
    L2 = (node*)malloc(sizeof(node));
    L2->next = NULL;
    while (p->next != NULL)
    {
        i++;
        if (i % 2 == 1)
        {
            p = p->next;
        }
        else
        {
            temp = p->next;
            p->next = temp->next;
            temp->next = L2->next;
            L2->next = temp;
        }
    }
}

/**
 * 删除链表中数值最大的元素，不唯一则删除逻辑序号小的.
 * @param L 原链表.
 */
bool del_max_node(node* &L)
{
    // p用于遍历链表.
    // max_p存放当前最大结点（擂台），pre存放当前最大结点的前驱结点.
    // max_p->data即为当前最大值，不需要设置max_val,利用指针更新最大值效率比用max_val高.
    // pre用于配合max_p进行删除操作.
    node* p = L;
    node* max_p;
    node* pre = L;
    // 空表返回false.
    if (p->next == NULL)
    {
        return false;
    }
    // 不是空表先走一个.
    p = p->next;
    // 假定第一个是最大元素.
    max_p = p;
    // 下一个不是NULL则继续走.
    while (p->next != NULL)
    {
        // 如果下一个元素更大，更新max_val和pre.
        if (p->next->data > max_p->data)
        {
            max_p = p->next;
            pre = p;
        }
        // 否则继续走.
        p = p->next;
    }
    // temp和pre配合，删除结点.
    pre->next = max_p->next;
    free(max_p);
    return true;
}

int main()
{
    element_type e = 10086;
    int n;
    node* L;
    node* L2;
    printf("please enter the size of the array: ");
    scanf("%d", &n);
    element_type arr[n];
    printf("please enter the array: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    create_list_rear(L, arr, n);
    disply_list(L);

    // spilt 测试
    // split(L, L2);
    // disply_list(L);
    // disply_list(L2);

    // del_max_node 测试
    for (int i = 0; i < 3; i++)
    {
        del_max_node(L);
        disply_list(L);
    }

    // insert 和 delete 测试
    // for (i=0;i<=7;i++)
    // {
    //     if(insert_list(L,i,i))
    //     {
    //         disply_list(L);
    //         if (delete_element(L,i,e))
    //         printf("%d\n",e);
    //     }
    //     else
    //     {
    //         printf("wrong index\n");
    //     }
    // }
    system("pause");
    return 0;
}