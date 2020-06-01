#include "sqlist.h"

#include <stdio.h>
#include <windows.h>

struct sqlist{
/*
    顺序表结构体
    属性：
        data    element_type类型的数组，最大长度为 max_size
        length  数组实际长度
*/
    element_type data[max_size];
    int length;
};

void create_sqlist(struct sqlist* &L, element_type a[], int n)
{
/*
    用数组创建顺序表    T(n) = O(n) S(n) = O(1)
    参数：
        L   顺序表指针的引用
        a   数组
        n   数组长度
    算法：
        1. 为 L动态分配内存
        2. 将 a的值赋给 L
        3. 设置 L的长度 length
*/
    L = (sqlist*)malloc(sizeof(sqlist));
    for (int i = 0; i < n; i++)
    {
        L->data[i] = a[i];
    }
    L->length = n;
}

void init_sqlist(sqlist* &L)
{
/*
    初始化顺序表    T(n) = O(1) S(n) = O(1)
    参数：
        L   顺序表指针的引用
    算法：
        1. 为 L动态分配内存
        2. 设置 L的长度 0
*/
    L = (sqlist*)malloc(sizeof(sqlist));
    L->length = 0;
}

void destroy_sqlist(sqlist* &L)
{
/*
    销毁顺序表    T(n) = O(1) S(n) = O(1)
    参数：
        L   顺序表指针的引用
    算法：
        释放动态分配给指针的空间
*/
    free(L);
}

bool insert_element(sqlist* &L, int i, element_type e)
{
/*
    在顺序表的第 i号位置插入元素    T(n) = O(n) S(n) = O(1)
    参数：
        L   顺序表指针的引用
        i   在逻辑序号为 i的元素之前插入，i取 1到 n+1
        e   待插入的元素
    算法：
        1. 向后腾出空位
        2. 插入元素
        3. length加 1
    返回值：
        bool    判断输入的 i是否合法
*/
    if (i < 1 || i > L->length + 1 || L->length == max_size)
        return false;
    i--;
    for (int j = L->length; j > i; j--)
    {
        L->data[j] = L->data[j-1];
    }
    L->data[i] = e;
    L->length++;
    return true;    
}

bool delete_element(sqlist* &L, int i, element_type &e)
{
/*
    删除顺序表逻辑序号为 i的元素    T(n) = O(n) S(n) = O(1)
    参数：
        L   顺序表指针的引用
        i   删除元素的逻辑序号，i取 1到 n
        e   接受被删除的元素（弹出）
    算法：
        1. 向前覆盖
        2. length减 1（逻辑删除）
    返回值：
        bool    判断输入的 i是否合法
*/
    if (i < 1 || i > L->length)
        return false;
    i--;
    e = L->data[i];
    for (int j = i; j < L->length - 1; j++)
    {
        L->data[i] = L->data[i+1];
    }
    L->length--;
    return true;
}

bool is_empty_sqlist(sqlist* L)
{
/*
    判断顺序表是否为空    T(n) = O(1) S(n) = O(1)
    参数：
        L   顺序表指针的引用
    算法：
        判断 length是否为 0
*/
    return (L->length == 0);
}

int get_length(sqlist* L)
{
/*
    返回顺序表长度    T(n) = O(1) S(n) = O(1)
    参数：
        L   顺序表指针的引用
    算法：
        通过返回值返回 length
*/
    return L->length;
}

bool get_element(sqlist* L, int i, element_type &e)
{
/*
    查找顺序表中指定逻辑序号的元素    T(n) = O(1) S(n) = O(1)
    参数：
        L   顺序表指针的引用
        i   指定的逻辑序号, i取 1到 n
        e   接受元素
    算法：
        随机存取
    返回值：
        bool    判断输入的 i是否合法
*/
    if (i < 1 || i > L->length)
        return false;
    i--;
    e = L->data[i];
    return true;
}

int locate_element(sqlist* L, element_type e)
{
/*
    查找顺序表中指定元素的逻辑序号    T(n) = O(n) S(n) = O(1)
    参数：
        L   顺序表指针的引用
        e   要查找的指定元素
    算法：
        遍历判断
    返回值：
        int     返回指定元素的逻辑序号，找不到则返回 0
*/
    int i = 0;
    for (; i < L->length; i++)
    {
        if (L->data[i] == e)
            break;
    }
    if (i == L->length)
        return 0;
    return i + 1;
}

void disply_sqlist(sqlist* L)
{
/*
    输出顺序表    T(n) = O(n) S(n) = O(1)
    参数：
        L   顺序表指针的引用
*/
    for (int i = 0; i < L->length; i++)
    {
        printf("%d ", L->data[i]);
    }
    printf("\n");
}