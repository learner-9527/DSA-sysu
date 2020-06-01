#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define max_size 50
typedef int element_type;

struct sqlist;

void create_sqlist(sqlist* &L, element_type arr[], int n);
void init_sqlist(sqlist* &L);
void destroy_sqlist(sqlist* &L);
bool insert_element(sqlist* &L, int i, element_type e);
bool delete_element(sqlist* &L, int i, element_type &e);
bool is_empty_sqlist(sqlist* L);
int get_length(sqlist* L);
bool get_element(sqlist* L, int i, element_type &e);
int locate_element(sqlist* L, element_type e);
void disply_sqlist(sqlist* L);
void union_sqlist(sqlist* L1, sqlist* L2, sqlist* &L);
void delete_element(sqlist* &L, element_type e);
void partition(sqlist* &L);
void odd_even(sqlist* &L);

/**
 * 顺序表结构体.
 * @attribute data 数组.
 * @attribute length 数组长度.
 */
struct sqlist
{
    element_type data[max_size];
    int length;
};

/**
 * 用数组创建顺序表. T(n) = O(n) S(n) = O(1)
 * @param L 顺序表指针的引用.
 * @param arr 数组.
 * @param n 数组长度.
 * @algorithm:
        1. 为 L动态分配内存.
        2. 将 arr的值赋给 L.
        3. 设置 L的长度 length.
 */
void create_sqlist(struct sqlist* &L, element_type arr[], int n)
{
    L = (sqlist*)malloc(sizeof(sqlist));
    for (int i = 0; i < n; i++)
    {
        L->data[i] = arr[i];
    }
    L->length = n;
}

/**
 * 初始化顺序表. T(n) = O(1) S(n) = O(1)
 * @param L 顺序表指针的引用.
 * @algorithm:
        1. 为 L动态分配内存.
        2. 设置 L的长度 0.
 */
void init_sqlist(sqlist* &L)
{
    L = (sqlist*)malloc(sizeof(sqlist));
    L->length = 0;
}

void destroy_sqlist(sqlist* &L)
{
    free(L);
}

/**
 * 在顺序表的第 i号位置插入元素. T(n) = O(n) S(n) = O(1)
 * @param L 顺序表指针的引用.
 * @param i 在逻辑序号为 i的元素之前插入，i取 1到 n+1.
 * @param e 待插入的元素.
 * algorithm:
        1. 向后腾出空位.
        2. 插入元素.
        3. length加 1.
 * @return 判断输入的 i是否合法.
 */
bool insert_element(sqlist* &L, int i, element_type e)
{
    if (i < 1 || i > L->length + 1 || L->length == max_size)
    {
        return false;
    }
    i--;
    for (int j = L->length; j > i; j--)
    {
        L->data[j] = L->data[j-1];
    }
    L->data[i] = e;
    L->length++;
    return true;    
}

/**
 * 删除顺序表逻辑序号为 i的元素. T(n) = O(n) S(n) = O(1)
 * @param L 顺序表指针的引用.
 * @param i 删除元素的逻辑序号，i取 1到 n.
 * @param e 接收被删除的元素.
 * algorithm:
        1. 向前覆盖.
        2. length减 1（逻辑删除）.
 * @return 判断输入的 i是否合法.
 */
bool delete_element(sqlist* &L, int i, element_type &e)
{
    if (i < 1 || i > L->length)
    {
        return false;
    }
    i--;
    e = L->data[i];
    for (int j = i; j < L->length - 1; j++)
    {
        L->data[j] = L->data[j+1];
    }
    L->length--;
    return true;
}

bool is_empty_sqlist(sqlist* L)
{
    return (L->length == 0);
}

int get_length(sqlist* L)
{
    return L->length;
}

bool get_element(sqlist* L, int i, element_type &e)
{
    if (i < 1 || i > L->length)
    {
        return false;
    }
    i--;
    e = L->data[i];
    return true;
}

int locate_element(sqlist* L, element_type e)
{
    int i = 0;
    for (; i < L->length; i++)
    {
        if (L->data[i] == e)
        {
            break;
        }
    }
    if (i == L->length)
    {
        return 0;
    }
    return i + 1;
}

void disply_sqlist(sqlist* L)
{
    for (int i = 0; i < L->length; i++)
    {
        printf("%d ", L->data[i]);
    }
    printf("\n");
}

void union_sqlist(sqlist* L1, sqlist* L2, sqlist* &L)
{
    int i,j;
    L = (sqlist*)malloc(sizeof(sqlist));
    for (i = 0; i < L1->length; i++)
    {
        L->data[i] = L1->data[i];
    }
    for (j = 0; j < L2->length; j++)
    {
        L->data[i+j] = L2->data[j];
    }
    L->length = i + j;
}

/**
 * 去除顺序表中所有值为 e的元素. T(n) = O(n) S(n) = O(1)
 * @param L 顺序表指针的引用.
 * @param e 要除去的元素.
 * algorithm:
        1. 重用法.
        2. 前移法.
 */
void delete_element(sqlist* &L, element_type e)
{
// 重用法
    int k = 0,i = 0;
    for (; i < L->length; i++)
    {
        if (L->data[i] != e)
        {
            L->data[k] = L->data[i];
            k++;
        }
    }
    L->length = k;
// 前移法
    // int k = 0, i =0;
    // for (; i < L->length; i++)
    // {
    //     if (L->data[i] != e)
    //     {
    //         L->data[i-k] = L->data[i];
    //     }
    //     else
    //     {
    //         k++;
    //     }
    // }
    // L->length = i - k;
}

/**
 * 以顺序表第一个元素为基准，重排顺序表，使小于等于它的元素在它之前，
 * 大于它的元素在它之后. T(n) = O(n) S(n) = O(1)
 * @param L 顺序表指针的引用.
 * algorithm:
        快速排序的递归算法 partition.
 */
void partition(sqlist* &L)
{
    element_type pivot = L->data[0];
    int i = 0, j = L->length -1;
    while (i != j)
    {
        while (L->data[j] > pivot && i != j)
        {
            j--;
        }
        L->data[i] = L->data[j];
        while (L->data[i] <= pivot && i != j)
        {
            i++;
        }
        L->data[j] = L->data[i];
    }
    L->data[i] = pivot;
}

/**
 * 重排顺序表，使奇数在前偶数在后. T(n) = O(n) S(n) = O(n)
 */
void odd_even(sqlist* &L)
{
    int i = 0, j = L->length - 1;
    element_type temp;
    while (i < j)
    {
        while (L->data[i] % 2 == 1 && i < j)
        {
            i++;
        }
        while (L->data[j] % 2 == 0 && i < j)
        {
            j--;
        }
        temp = L->data[i];
        L->data[i] = L->data[j];
        L->data[j] = temp;
    }
}

int main()
{
    sqlist* L;
    int e;
    int n;
    printf("请输入顺序表长度： ");
    scanf("%d", &n);
    int a[n];
    printf("请输入长度为%d的顺序表： ", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    create_sqlist(L, a, n);
    disply_sqlist(L);
    odd_even(L);
    disply_sqlist(L);
    system("pause");
    return 0;
}