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
 * ˳���ṹ��.
 * @attribute data ����.
 * @attribute length ���鳤��.
 */
struct sqlist
{
    element_type data[max_size];
    int length;
};

/**
 * �����鴴��˳���. T(n) = O(n) S(n) = O(1)
 * @param L ˳���ָ�������.
 * @param arr ����.
 * @param n ���鳤��.
 * @algorithm:
        1. Ϊ L��̬�����ڴ�.
        2. �� arr��ֵ���� L.
        3. ���� L�ĳ��� length.
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
 * ��ʼ��˳���. T(n) = O(1) S(n) = O(1)
 * @param L ˳���ָ�������.
 * @algorithm:
        1. Ϊ L��̬�����ڴ�.
        2. ���� L�ĳ��� 0.
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
 * ��˳���ĵ� i��λ�ò���Ԫ��. T(n) = O(n) S(n) = O(1)
 * @param L ˳���ָ�������.
 * @param i ���߼����Ϊ i��Ԫ��֮ǰ���룬iȡ 1�� n+1.
 * @param e �������Ԫ��.
 * algorithm:
        1. ����ڳ���λ.
        2. ����Ԫ��.
        3. length�� 1.
 * @return �ж������ i�Ƿ�Ϸ�.
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
 * ɾ��˳����߼����Ϊ i��Ԫ��. T(n) = O(n) S(n) = O(1)
 * @param L ˳���ָ�������.
 * @param i ɾ��Ԫ�ص��߼���ţ�iȡ 1�� n.
 * @param e ���ձ�ɾ����Ԫ��.
 * algorithm:
        1. ��ǰ����.
        2. length�� 1���߼�ɾ����.
 * @return �ж������ i�Ƿ�Ϸ�.
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
 * ȥ��˳���������ֵΪ e��Ԫ��. T(n) = O(n) S(n) = O(1)
 * @param L ˳���ָ�������.
 * @param e Ҫ��ȥ��Ԫ��.
 * algorithm:
        1. ���÷�.
        2. ǰ�Ʒ�.
 */
void delete_element(sqlist* &L, element_type e)
{
// ���÷�
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
// ǰ�Ʒ�
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
 * ��˳����һ��Ԫ��Ϊ��׼������˳���ʹС�ڵ�������Ԫ������֮ǰ��
 * ��������Ԫ������֮��. T(n) = O(n) S(n) = O(1)
 * @param L ˳���ָ�������.
 * algorithm:
        ��������ĵݹ��㷨 partition.
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
 * ����˳���ʹ������ǰż���ں�. T(n) = O(n) S(n) = O(n)
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
    printf("������˳����ȣ� ");
    scanf("%d", &n);
    int a[n];
    printf("�����볤��Ϊ%d��˳��� ", n);
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