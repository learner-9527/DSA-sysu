#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef int element_type;

typedef struct cirnode{
    element_type data;
    struct cirnode* next;
} cnode;

void create_list_first(cnode* &L, element_type arr[], int n)
{
    cnode* temp;
    L = (cnode*)malloc(sizeof(cnode));
    L->next = L;
    for (int i = 0; i < n; i++)
    {
        temp = (cnode*)malloc(sizeof(cnode));
        temp->data = arr[i];
    }

}

void create_list_rear(cnode* &L, element_type arr[], int n)
{

}

void init_list(cnode* &L)
{
    L = (cnode*)malloc(sizeof(cnode));
    // 与普通单链表区别仅在于NULL换成L
    L->next = L;
}

void destroy_list(cnode* L)
{
    cnode* p = L;
    cnode* pre = L;
    // 与普通单链表区别仅在于NULL换成L
    while (p->next != L)
    {
        p = p->next;
        free(pre);
        pre = p;
    }
    free(pre);
}

bool empty_list(cnode* L)
{
    // 与普通单链表区别仅在于NULL换成L
    return (L->next == L);
}

int get_length(cnode* L)
{
    cnode* p = L;
    int n = 0;
    // 与普通单链表区别仅在于NULL换成L
    while (p->next != L)
    {
        p = p->next;
        n++;
    }
    return n;
}

void display_list(cnode* L)
{
    cnode* p = L;
    printf("cirlinked list: ");
    // 与普通单链表区别仅在于NULL换成L
    while (p->next != L)
    {
        p = p->next;
        printf("%d ", p->data);
    }
    printf("\n");
}

bool get_element(cnode* L, int i, element_type &e)
{
    cnode* p = L;
    int j = 0;
    if (i < 1)
    {
        return false;
    }
    // 与普通单链表区别仅在于NULL换成L
    while (j < i && p->next != L)
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

int locate_element(cnode* L, element_type)
{

}

int main()
{
    return 0;
}