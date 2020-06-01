#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// �궨�壬˳���Ԫ�ظ�������.
#define max_size 100

/**
 * @brief:
 * 1. ������Ϣ�ṹ�壬����Ϊ˳�������Ԫ��.
 * 2. �������ж��������ýṹ��洢.
 * 3. int�洢����ʱ�������������char����洢.
 * @param student_number ѧ��.
 * @param name ����.
 * @param sex �Ա�.
 * @param phone_number �绰����.
 * @param qq_number qq����.
 * @method: input ������Ϣ.
 * @method: output �����Ϣ.
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
    printf("ѧ�ţ�");
    scanf("%d", &student_number);
    printf("������");
    scanf("%s", &name);
    // getchar()���ջس���.
    getchar();
    printf("�Ա�");
    scanf("%s", &sex);
    getchar();
    printf("�ֻ����룺");
    scanf("%s", &phone_number);
    getchar();
    printf("qq���룺");
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
 * 1. ͨѶ¼˳���.
 * 2. ͨѶ¼�����Ա�����˳��洢ʵ��.
 * @param data ������Ϣ�ṹ������.
 * @param length ����ʵ�ʳ��ȣ���ͨѶ¼��¼����.
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
 * ��ʼ��˳���.
 * @param L ˳���ָ��.
 * @algorithm:
 * 1. ΪL��̬����洢�ռ�.
 * 2. ��length��Ϊ0����ʾ�ձ�.
 */
void init_list(address_list* &L)
{
    L = (address_list*)malloc(sizeof(address_list));
    L->length = 0;
}

/**
 * @brief �����鴴��˳���.
 * @complexity: T(n) = O(n).
 * @param L ˳���ָ��.
 * @param arr ������Ϣ�ṹ������.
 * @param n ���鳤��.
 * @algorithm:
 * 1. ΪL��̬����洢�ռ�.
 * 2. ��ѭ��������Ԫ�ظ���˳���.
 * 3. length��Ϊn.
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
 * @brief ���٣������ÿգ�˳���.
 * @param L ˳���ָ��.
 * @algorithm:
 * 1. �ͷ�L��ָ��̬�洢�ռ�.
 */
void destroy_list(address_list* &L)
{
    free(L);
}

/**
 * @brief ����ָ��ѧ�ŵ�Ԫ�ص��߼���ź���Ϣ.
 * @complexity: T(n) = o(n).
 * @param L ˳���ָ��.
 * @param number ָ��ѧ��.
 * @param e ���ո�Ԫ��.
 * @algorithm:
 * 1. �����ж�.
 * @return ��Ԫ���߼���ţ��Ҳ����򷵻�0.
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
 * @brief ��ָ���߼����ǰ����Ԫ��.
 * @complexity: T(n) = o(n).
 * @param L ˳���ָ��.
 * @param i ���߼����iǰ����Ԫ�أ�iȡֵ1��length+1.
 * @param e �����Ԫ��.
 * @algorithm:
 * 1. �Ӻ�ǰ���γ���һ�����ڲ���λ���ڳ���λ.
 * 2. �ڿ�λ����.
 * 3. length�Լ�1.
 * @return ������i���Ϸ������ʧ�ܷ���false���������ɹ�����true.
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
 * @brief ɾ��ָ���߼���ŵ�Ԫ��.
 * @complexity: T(n) = o(n).
 * @param L ˳���ָ��.
 * @param i ɾ���߼����i��Ԫ�أ�iȡֵ1��length.
 * @param e ����ɾ����Ԫ��.
 * @algorithm:
 * 1. ��ɾ��Ԫ�غ����Ԫ��������ǰ����.
 * 2. length�Լ�1.
 * @return i���Ϸ���ɾ��ʧ�ܷ���false������ɾ���ɹ�����true.
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
 * @brief ���˳���.
 * @complexity: T(n) = O(n).
 * @param L ˳���ָ��.
 */
void disply(address_list* L)
{
    info e;
    int i;
    printf("\n");
    if (L->length == 0)
    {
        printf("ͨѶ¼���޼�¼��\n");
    }
    else
    {
        for (i = 0; i < 80; i++)
        {
            printf("=");
        }
        printf("\n");
        printf("ѧ��\t\t����\t\t�Ա�\t\t�ֻ�����\t\tQQ��\n");
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
 * @brief �жϵ�ǰ�Ƿ�Ϊ�ձ�.
 * @param L ˳���ָ��.
 * @return �ձ���true���ǿշ���false.
 */
bool is_empty(address_list* L)
{
    return (L->length == 0);
}

/**
 * @brief ���˳���ǰ����.
 * @param L ˳���ָ��.
 * @return ���س���length��ȡֵ��Χ0��max_size.
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
    printf("����Ҫ���ҵ�ѧ�ţ�");
    scanf("%d", &number);
    printf("��ѧ���ڵ�%dλ����Ϣ���£�\n", search_element(L, number, e));
    e.output();
    printf("����Ҫɾ����Ϣ��ѧ������ţ�");
    scanf("%d", &i);
    if (delete_element(L, i, e))
    {
        printf("��%d��ѧ����Ϣ��ɾ��.\n", i);
    }
    disply(L);
    system("pause");
    return 0;
}