#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/**
 * @brief:
 * 1. ������Ϣ�ṹ�壬����Ϊ����������Ԫ��.
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
 * 1. ͨѶ¼����.
 * 2. ͨѶ¼�����Ա�������ʽ�洢ʵ��.
 * @param data ������Ϣ�ṹ��.
 * @param next ����ָ��.
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
 * @brief ��ʼ������.
 * @param L ͷ���ָ��.
 * @algorithm:
 * 1. ΪL��̬����洢�ռ�.
 * 2. ��next��ΪNULL����ʾ�ձ�.
 */
void init_list(info_node* &L)
{
    L = (info_node*)malloc(sizeof(info_node));
    L->next = NULL;
}

/**
 * @brief �����鴴������.
 * @complexity: T(n) = O(n).
 * @param L ����ͷ���ָ��.
 * @param arr ������Ϣ�ṹ������.
 * @param n ���鳤��.
 * @algorithm:
 * 1. ΪL��̬����洢�ռ�.
 * 2. ����β�巨.
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
 * @brief ���٣������ÿգ�����.
 * @complexity: T(n) = O(n).
 * @param L ����ͷ���ָ��.
 * @algorithm:
 * 1. �ͷ�ÿ�������ָ��̬�洢�ռ�.
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
 * @brief ����ָ��ѧ�ŵ�Ԫ�ص��߼���ź���Ϣ.
 * @complexity: T(n) = o(n).
 * @param L ����ͷ���ָ��.
 * @param number ָ��ѧ��.
 * @param e ���ո�Ԫ��.
 * @algorithm:
 * 1. �����ж�.
 * @return ��Ԫ���߼���ţ��Ҳ����򷵻�0.
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
 * @brief ��ָ���߼����ǰ����Ԫ��.
 * @complexity: T(n) = o(n).
 * @param L ����ָ��.
 * @param i ���߼����iǰ����Ԫ�أ�iȡֵ1��length+1.
 * @param e �����Ԫ��.
 * @algorithm:
 * 1. �ҵ�ǰ�����pre.
 * 2. pre���temp��ɲ���.
 * @return i���Ϸ������ʧ�ܷ���false���������ɹ�����true.
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
 * @brief ɾ��ָ���߼���ŵ�Ԫ��.
 * @complexity: T(n) = o(n).
 * @param L ����ͷ���ָ��.
 * @param i ɾ���߼����i��Ԫ�أ�iȡֵ1��length.
 * @param e ����ɾ����Ԫ��.
 * @algorithm:
 * 1. �ҵ�ǰ��ָ��pre.
 * 2. pre���temp���ɾ��.
 * @return i���Ϸ���ɾ��ʧ�ܷ���false������ɾ���ɹ�����true.
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
 * @brief �������.
 * @complexity: T(n) = O(n).
 * @param L �����ָ��.
 */
void disply(info_node* L)
{
    info e;
    info_node* p = L;
    int i;
    printf("\n");
    if (p->next == NULL)
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
 * @brief �жϵ�ǰ�Ƿ�Ϊ�ձ�.
 * @param L ����ָ��.
 * @return �ձ���true���ǿշ���false.
 */
bool is_empty(info_node* L)
{
    return (L->next == NULL);
}

/**
 * @brief �������ǰ����.
 * @complexity: T(n) = O(n).
 * @param L ����ָ��.
 * @algorithm:
 * 1. ����ͳ��.
 * @return ���س���n.
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