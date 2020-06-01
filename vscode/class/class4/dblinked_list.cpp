#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef int element_type;
typedef struct dblinked_node{
    element_type data;
    struct dblinked_node* prior;
    struct dblinked_node* next;
} dnode;

void create_list_first(dnode* &L, element_type arr[], int n);
void create_list_rear(dnode* &L, element_type arr[], int n);
void init_list(dnode* &L);
void destroy_list(dnode* &L);
bool empty_list(dnode* L);
int get_length(dnode* L);
void disply_list(dnode* L);
bool get_element(dnode* L, int i, element_type &e);
int locate_element(dnode* &L, element_type e);
bool insert_list(dnode* &L, int i, element_type e);
bool delete_element(dnode* &L, int i, element_type &e);
void split(dnode* &L1, dnode* &L2);
bool del_max_node(dnode* &L);

void create_list_first(dnode* &L, element_type arr[], int n)
{
    dnode* temp;
    L = (dnode*)malloc(sizeof(dnode));
    L->prior = NULL;
    L->next = NULL;
    for (int i = 0; i < n; i++)
    {
        temp = (dnode*)malloc(sizeof(dnode));
        temp->data = arr[i];
        // 双链表插入时需要判断下一个是否为空.
        // 为保留next，先处理右边两条后处理左边两条.
        // 为方便记忆，统一先prior后next.
        if (L->next != NULL)
        {
            L->next->prior = temp;
        }
        temp->next = L->next;
        temp->prior = L;
        L->next = temp;
    }
}

void create_list_rear(dnode* &L, element_type arr[], int n)
{
    dnode* rear;
    dnode* temp;
    L = (dnode*)malloc(sizeof(dnode));
    rear = L;
    for (int i = 0; i < n; i++)
    {
        temp = (dnode*)malloc(sizeof(dnode));
        temp->data = arr[i];
        temp->prior = rear;
        rear->next = temp;
        rear = temp;
    }
    rear->next = NULL;
}

void init_list(dnode* &L)
{
    L = (dnode*)malloc(sizeof(dnode));
    L->prior = NULL;
    L->next = NULL;
}

void destroy_list(dnode* &L)
{
    dnode* p;
    while (p->next != NULL)
    {
        p = p->next;
        free(p->prior);
    }
    free(p);
}

bool empty_list(dnode* L)
{
    return (L->next == NULL);
}

int get_length(dnode* L)
{
    dnode* p = L;
    int i = 0;
    while (p->next != NULL)
    {
        p = p->next;
        i++;
    }
    return i;
}

void disply_list(dnode* L)
{
    dnode* p = L;
    printf("dblinked list: ");
    while (p->next != NULL)
    {
        p = p->next;
        printf("%d ", p->data);
    }
    printf("\n");
}

bool get_element(dnode* L, int i, element_type &e)
{
    dnode* p = L;
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
    else
    {
        e = p->data;
        return true;
    }
}

int locate_element(dnode* &L, element_type e)
{
    dnode* p = L;
    int i = 0;
    while (p->next != NULL)
    {
        p = p->next;
        i++;
        if (p->data == e)
        {
            break;
        }
    }
    if (p->data == e)
    {
        return i;
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
bool insert_list(dnode* &L, int i, element_type e)
{
    dnode* pre = L;
    dnode* temp;
    if (i < 1)
    {
        return false;
    }
    int j = 0;
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
        temp = (dnode*)malloc(sizeof(dnode));
        temp->data = e;
        // 和普通链表一样，找的是前驱结点.
        // 区别在于插入时考虑prior的连接.
        if (pre->next != NULL)
        {
            pre->next->prior = temp;
        }
        temp->next = pre->next;
        temp->prior = pre;
        pre->next = temp;
        return true;
    }
}

bool delete_element(dnode* &L, int i, element_type &e)
{
    dnode* p = L;
    dnode* pre;
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
    else
    {
        // pre非必要，但可以使代码简洁.
        e = p->data;
        pre = p->prior;
        if (p->next != NULL)
        {
            p->next->prior = pre;
        }
        pre->next = p->next;
        free(p);
        return true;
    }
}

/**
 * 分开链表中逻辑序号为奇数和偶数的元素，分别放在 L1和 L2中.
 * @param L1 原链表，且将用于顺序存放奇数元素.
 * @param L2 用于逆序存放偶数元素.
 */
void split(dnode* &L1, dnode* &L2)
{
    dnode* p = L1;
    dnode* temp;
    int i = 0;
    L2 = (dnode*)malloc(sizeof(dnode));
    L2->next = NULL;
    L2->prior = NULL;
    while (p->next != NULL)
    {
        i++;
        if (i % 2 == 1)
        {
            p = p->next;
        }
        else
        {
            // temp是必要的.
            temp = p->next;
            if (temp->next != NULL)
            {
                temp->next->prior = p;
            }
            p->next = temp->next;
            if (L2->next != NULL)
            {
                L2->next->prior = temp;
            }
            temp->next = L2->next;
            temp->prior = L2;
            L2->next = temp;
        }
    }
}

bool del_max_node(dnode* &L)
{
    // p用于遍历.
    // max_p存放当前最大结点（擂台）.
    // max_p->data即为当前最大值，不需要设置max_val,利用指针更新最大值效率比用max_val高.
    // pre为了删除时代码简洁.
    dnode* p = L;
    dnode* max_p;
    dnode* pre;
    if (p->next == NULL)
    {
        return false;
    }
    p = p->next;
    max_p = p;
    while (p->next != NULL)
    {
        p = p->next;
        if (p->data > max_p->data)
        {
            max_p = p;
        }
    }
    // 双链表的删除不需要temp.
    // 删除只需要找到待删除结点，pre非必要，但可以使代码简洁.
    pre = max_p->prior;
    if (max_p->next != NULL)
    {
        max_p->next->prior = pre;
    }
    pre->next = max_p->next;
    free(max_p);
    return true;
}

int main()
{
    element_type e = 10086;
    int i;
    dnode* L, * L2;
    int n;
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
    // split 测试
    // split(L, L2);
    // disply_list(L);
    // disply_list(L2);

    // del_max_node 测试
    for (i = 0; i < 3; i++)
    {
        del_max_node(L);
        disply_list(L);
    }
    system("pause");
    return 0;
    return 0;
}