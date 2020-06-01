#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/**
 * @brief:
 * 1. 个人信息结构体，将作为链表结点数据元素.
 * 2. 数据项有多个，因此用结构体存储.
 * 3. int存储号码时可能溢出，采用char数组存储.
 * @param student_number 学号.
 * @param name 姓名.
 * @param sex 性别.
 * @param phone_number 电话号码.
 * @param qq_number qq号码.
 * @method: input 输入信息.
 * @method: output 输出信息.
 */
typedef struct{
    int student_number;
    char name[10];
    char sex[5];
    char phone_number[15];
    char qq_number[15];
    void input();
    void output();
} info;

void info::input()
{
    printf("学号：");
    scanf("%d", &student_number);
    printf("姓名：");
    scanf("%s", &name);
    // getchar()接收回车符.
    getchar();
    printf("性别：");
    scanf("%s", &sex);
    getchar();
    printf("手机号码：");
    scanf("%s", &phone_number);
    getchar();
    printf("qq号码：");
    scanf("%s", &qq_number);
    getchar();
}

void info::output()
{
    printf("%d\t\t", student_number);
    printf("%s\t\t", name);
    printf("%s\t\t", sex);
    printf("%s\t\t", phone_number);
    printf("%s\n", qq_number);
}

/**
 * @brief:
 * 1. 通讯录链表.
 * 2. 通讯录是线性表，采用链式存储实现.
 * @param data 个人信息结构体.
 * @param next 链表指针.
 */
typedef struct node{
    info data;
    node* next;
} info_node;

void init_list(info_node* &L);
void create_list(info_node* &L, info arr[], int n);
void destroy_list(info_node* &L);
int search_element(info_node* L, int number, info &e);
bool insert(info_node* &L, int i, info e);
bool delete_element(info_node* &L, int i, info &e);
void disply(info_node* L);
bool is_empty(info_node* L);
int get_length(info_node* L);

/**
 * @brief 初始化链表.
 * @param L 头结点指针.
 * @algorithm:
 * 1. 为L动态分配存储空间.
 * 2. 将next置为NULL，表示空表.
 */
void init_list(info_node* &L)
{
    L = (info_node*)malloc(sizeof(info_node));
    L->next = NULL;
}

/**
 * @brief 用数组创建链表.
 * @complexity: T(n) = O(n).
 * @param L 链表头结点指针.
 * @param arr 个人信息结构体数组.
 * @param n 数组长度.
 * @algorithm:
 * 1. 为L动态分配存储空间.
 * 2. 采用尾插法.
 */
void create_list_rear(info_node* &L, info arr[], int n)
{
    info_node* temp;
    info_node* rear;
    L = (info_node*)malloc(sizeof(info_node));
    rear = L;
    for (int i = 0; i < n; i++)
    {
        temp = (info_node*)malloc(sizeof(info_node));
        temp->data = arr[i];
        rear->next = temp;
        rear = temp;
    }
    rear->next = NULL;
}

/**
 * @brief 销毁（并非置空）链表.
 * @complexity: T(n) = O(n).
 * @param L 链表头结点指针.
 * @algorithm:
 * 1. 释放每个结点所指动态存储空间.
 */
void destroy_list(info_node* &L)
{
    info_node* p = L;
    info_node* pre = L;
    while (p->next != NULL)
    {
        p = p->next;
        free(pre);
        pre = p;
    }
    free(pre);
}

/**
 * @brief 查找指定学号的元素的逻辑序号和信息.
 * @complexity: T(n) = o(n).
 * @param L 链表头结点指针.
 * @param number 指定学号.
 * @param e 接收该元素.
 * @algorithm:
 * 1. 遍历判断.
 * @return 该元素逻辑序号，找不到则返回0.
 */
int search_element(info_node* L, int number, info &e)
{
    info_node* p = L;
    int i = 0;
    while (p->next != NULL)
    {
        p = p->next;
        i++;
        if (p->data.student_number == number)
        {
            break;
        }
    }
    if (p->data.student_number == number)
    {
        e = p->data;
        return i;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 在指定逻辑序号前插入元素.
 * @complexity: T(n) = o(n).
 * @param L 链表指针.
 * @param i 在逻辑序号i前插入元素，i取值1到length+1.
 * @param e 插入的元素.
 * @algorithm:
 * 1. 找到前驱结点pre.
 * 2. pre配合temp完成插入.
 * @return i不合法则插入失败返回false，否则插入成功返回true.
 */
bool insert(info_node* &L, int i, info e)
{
    info_node* pre = L;
    info_node* temp;
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
        temp = (info_node*)malloc(sizeof(info_node));
        temp->data = e;
        temp->next = pre->next;
        pre->next = temp;
    }
}

/**
 * @brief 删除指定逻辑序号的元素.
 * @complexity: T(n) = o(n).
 * @param L 链表头结点指针.
 * @param i 删除逻辑序号i的元素，i取值1到length.
 * @param e 接收删除的元素.
 * @algorithm:
 * 1. 找到前驱指针pre.
 * 2. pre配合temp完成删除.
 * @return i不合法则删除失败返回false，否则删除成功返回true.
 */
bool delete_element(info_node* &L, int i, info &e)
{
    info_node* pre = L;
    info_node* temp;
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
        pre->next = temp->next;
        free(temp);
    }
}

/**
 * @brief 输出链表.
 * @complexity: T(n) = O(n).
 * @param L 链表表指针.
 */
void disply(info_node* L)
{
    info e;
    info_node* p = L;
    int i;
    printf("\n");
    if (p->next == NULL)
    {
        printf("通讯录暂无记录。\n");
    }
    else
    {
        for (i = 0; i < 80; i++)
        {
            printf("=");
        }
        printf("\n");
        printf("学号\t\t姓名\t\t性别\t\t手机号码\t\tQQ号\n");
        for (i = 0; i < 80; i++)
        {
            printf("=");
        }
        printf("\n");
        while (p->next != NULL)
        {
            p = p->next;
            e = p->data;
            e.output();
        }
        printf("\n");
    }
}

/**
 * @brief 判断当前是否为空表.
 * @param L 链表指针.
 * @return 空表返回true，非空返回false.
 */
bool is_empty(info_node* L)
{
    return (L->next == NULL);
}

/**
 * @brief 获得链表当前长度.
 * @complexity: T(n) = O(n).
 * @param L 链表指针.
 * @algorithm:
 * 1. 遍历统计.
 * @return 返回长度n.
 */
int get_length(info_node* L)
{
    info_node* p = L;
    int n = 0;
    while (p->next != NULL)
    {
        p = p->next;
        n++;
    }
    return n;
}

int main()
{
    info_node* L;
    info arr[10];
    info e;
    int number;
    int i;
    arr[0].input();
    create_list_rear(L, arr, 1);
    disply(L);
    delete_element(L, 1, arr[0]);
    for (int i = 0; i < 5; i++)
    {
        arr[i].input();
        insert(L, i + 1, arr[i]);
    }
    disply(L);
    printf("输入要查找的学号：");
    scanf("%d", &number);
    printf("该学生在第%d位，信息如下：\n", search_element(L, number, e));
    e.output();
    printf("输入要删除信息的学生的序号：");
    scanf("%d", &i);
    if (delete_element(L, i, e))
    {
        printf("第%d号学生信息已删除.\n", i);
    }
    disply(L);
    system("pause");
    return 0;
}