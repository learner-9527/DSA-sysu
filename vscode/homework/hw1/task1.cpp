#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// 宏定义，顺序表元素个数上限.
#define max_size 100

/**
 * @brief:
 * 1. 个人信息结构体，将作为顺序表数据元素.
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
 * 1. 通讯录顺序表.
 * 2. 通讯录是线性表，采用顺序存储实现.
 * @param data 个人信息结构体数组.
 * @param length 数组实际长度，即通讯录记录人数.
 */
typedef struct{
    info data[max_size];
    int length;
} address_list;

void init_list(address_list* &L);
void create_list(address_list* &L, info arr[], int n);
void destroy_list(address_list* &L);
int search_element(address_list* L, int number, info &e);
bool insert(address_list* &L, int i, info e);
bool delete_element(address_list* &L, int i, info &e);
void disply(address_list* L);
bool is_empty(address_list* L);
int get_length(address_list* L);

/**
 * 初始化顺序表.
 * @param L 顺序表指针.
 * @algorithm:
 * 1. 为L动态分配存储空间.
 * 2. 将length置为0，表示空表.
 */
void init_list(address_list* &L)
{
    L = (address_list*)malloc(sizeof(address_list));
    L->length = 0;
}

/**
 * @brief 用数组创建顺序表.
 * @complexity: T(n) = O(n).
 * @param L 顺序表指针.
 * @param arr 个人信息结构体数组.
 * @param n 数组长度.
 * @algorithm:
 * 1. 为L动态分配存储空间.
 * 2. 用循环将数组元素赋给顺序表.
 * 3. length置为n.
 */
void create_list(address_list* &L, info arr[], int n)
{
    L = (address_list*)malloc(sizeof(address_list));
    for (int i = 0; i < n; i++)
    {
        L->data[i] = arr[i];
    }
    L->length = n;
}

/**
 * @brief 销毁（并非置空）顺序表.
 * @param L 顺序表指针.
 * @algorithm:
 * 1. 释放L所指动态存储空间.
 */
void destroy_list(address_list* &L)
{
    free(L);
}

/**
 * @brief 查找指定学号的元素的逻辑序号和信息.
 * @complexity: T(n) = o(n).
 * @param L 顺序表指针.
 * @param number 指定学号.
 * @param e 接收该元素.
 * @algorithm:
 * 1. 遍历判断.
 * @return 该元素逻辑序号，找不到则返回0.
 */
int search_element(address_list* L, int number, info &e)
{
    int i;
    for (i = 0; i < L->length; i++)
    {
        if (L->data[i].student_number == number)
        {
            break;
        }
    }
    if (i == L->length)
    {
        return 0;
    }
    else
    {
        e = L->data[i];
        return i + 1;
    }
}

/**
 * @brief 在指定逻辑序号前插入元素.
 * @complexity: T(n) = o(n).
 * @param L 顺序表指针.
 * @param i 在逻辑序号i前插入元素，i取值1到length+1.
 * @param e 插入的元素.
 * @algorithm:
 * 1. 从后到前依次撤退一步，在插入位置腾出空位.
 * 2. 在空位插入.
 * 3. length自加1.
 * @return 表满或i不合法则插入失败返回false，否则插入成功返回true.
 */
bool insert(address_list* &L, int i, info e)
{
    int k;
    if (L->length == max_size || i < 1 || i > L->length + 1)
    {
        return false;
    }
    for (k = L->length; k >= i; k--)
    {
        L->data[k] = L->data[k-1];
    }
    L->data[k] = e;
    L->length++;
}

/**
 * @brief 删除指定逻辑序号的元素.
 * @complexity: T(n) = o(n).
 * @param L 顺序表指针.
 * @param i 删除逻辑序号i的元素，i取值1到length.
 * @param e 接收删除的元素.
 * @algorithm:
 * 1. 被删除元素后面的元素依次往前覆盖.
 * 2. length自减1.
 * @return i不合法则删除失败返回false，否则删除成功返回true.
 */
bool delete_element(address_list* &L, int i, info &e)
{
    int k;
    if (i < 1 || i > L->length)
    {
        return false;
    }
    for (k = i; k < L->length; k++)
    {
        L->data[k-1] = L->data[k];
    }
    L->length--;
}

/**
 * @brief 输出顺序表.
 * @complexity: T(n) = O(n).
 * @param L 顺序表指针.
 */
void disply(address_list* L)
{
    info e;
    int i;
    printf("\n");
    if (L->length == 0)
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
        for (i = 0; i < L->length; i++)
        {
            e = L->data[i];
            e.output();
        }
        printf("\n");
    }
}

/**
 * @brief 判断当前是否为空表.
 * @param L 顺序表指针.
 * @return 空表返回true，非空返回false.
 */
bool is_empty(address_list* L)
{
    return (L->length == 0);
}

/**
 * @brief 获得顺序表当前长度.
 * @param L 顺序表指针.
 * @return 返回长度length，取值范围0到max_size.
 */
int get_length(address_list* L)
{
    return L->length;
}

int main()
{
    address_list* L;
    info arr[max_size];
    info e;
    int number;
    int i;
    arr[0].input();
    create_list(L, arr, 1);
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