/*
    荷兰国旗问题：设有一个条块序列，每个条块为红（0）、白（1）、兰（2）
    三种颜色中的一种。假设该序列采用链表存储，
    设计一个时间复杂度为O(n)的算法，
    使得这些条块按红、白、兰的顺序排好，即排成荷兰国旗图案。
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// 定义枚举类型color，分别以1，2，3表示三种颜色.
typedef enum{
    red = 1,
    white = 2,
    blue = 3
} color;

/**
 * 存储颜色条块的链表结点.
 * @param data 色条块，元素类型为color.
 * @param next 结点指针.
 */
typedef struct linked_node{
    color data;
    linked_node* next;
} color_node;

/**
 * 用色条块数组创建链表.
 * @complexity: T(n) = O(n).
 * @param L 链表头结点.
 * @param arr 色条块数组.
 * @param n 数组长度.
 * @algorithm:
 * 1. 头插法.
 */
void create_list_head(color_node* &L, color arr[], int n)
{
    color_node* temp;
    L = (color_node*)malloc(sizeof(color_node));
    L->next = NULL;
    for (int i = 0; i < n; i++)
    {
        temp = (color_node*)malloc(sizeof(color_node));
        temp->data = arr[i];
        temp->next = L->next;
        L->next = temp;
    }
}

/**
 * 将链表的色条快按红(1)，白(2)，蓝(3)排序，制成荷兰国旗.
 * @complexity:
 * 1. T(n) = O(n). 只遍历一次.
 * 2. S(n) = O(1). 在原表上重建，没有开辟新的表.
 * @param L 链表头结点指针.
 * @algorithm:
 * 构建三个纯色链表再合并.
 * 1. 遍历一次链表，新建成三条纯色链表.
 * 2. 将三条纯色链表连接起来.
 * @return 三种颜色不齐全则返回false，否则返回true.
 */
bool sort_flag(color_node* L)
{
    // white是白色链表头结点，blue是蓝色链表头结点.
    // white和blue用于构建纯色链表.
    // 红色条块保留在原先链表即可.
    color_node* white, * blue;
    // w_rear是白色链表尾结点，b_rear是蓝色链表尾结点.
    color_node* w_rear, * b_rear;
    // p用于遍历链表，temp用于配合p进行删除插入.
    color_node* p = L, * temp;
    white = (color_node*)malloc(sizeof(color_node));
    blue = (color_node*)malloc(sizeof(color_node));
    w_rear = white;
    b_rear = blue;
    w_rear->next = NULL;
    b_rear->next = NULL;
    while (p->next != NULL)
    {
        temp = p->next;
        // 如果是红色，前进一步.
        if (temp->data == 1)
        {
            p = temp;
        }
        // 如果是白色，先在原链表上删除该结点.
        // 再用尾插法将该结点插入到white链表.
        else if (temp->data == 2)
        {
            p->next = temp->next;
            w_rear->next = temp;
            w_rear = temp;
        }
        // 如果是蓝色，操作和白色类似.
        else
        {
            p->next = temp->next;
            b_rear->next = temp;
            b_rear = temp;
        }
    }
    // 连接三个纯色链表，利用尾指针rear可以免去遍历.
    p->next = white->next;
    w_rear->next = blue->next;
    b_rear->next = NULL;
    // 如果有某个指针没动过，则说明缺少某种颜色.
    if (p == L || white == w_rear || blue == b_rear)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void disply_list(color_node* L)
{
    color_node* p = L;
    printf("color list: ");
    while (p->next != NULL)
    {
        p = p->next;
        printf("%d ", p->data);
    }
    printf("\n");
}

void destroy_list(color_node* &L)
{
    color_node* p = L;
    color_node* pre = L;
    while (p->next != NULL)
    {
        p = p->next;
        free(pre);
        pre = p;
    }
    free(pre);
}

int main()
{
    // 创建数组.
    int n;
    printf("please enter the length of color list: ");
    scanf("%d", &n);
    color arr[n];
    color_node* flg;
    printf("please enter the color list: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    // 创建链表.
    printf("creating list...\n");
    create_list_head(flg, arr, n);
    disply_list(flg);
    // 排序.
    printf("making flag...\n");
    if (sort_flag(flg))
    {
        printf("success.\n");
    }
    else
    {
        printf("lack some certain colors.\n");
    }
    // 输出检验.
    disply_list(flg);
    destroy_list(flg);
    system("pause");
    return 0;
}