#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef int element_type;
typedef struct link_stack_node{
    element_type data;
    link_stack_node* next;
} ls_node;

void init_stack(ls_node* &s);
void destroy_stack(ls_node* &s);
bool empty_stack(ls_node* s);
void push(ls_node* &s, element_type e);
bool pop(ls_node* &s, element_type &e);
bool get_top(ls_node* s, element_type &e);

void init_stack(ls_node* &s)
{
    s = (ls_node*)malloc(sizeof(ls_node));
    s->next = NULL;
}

void destroy_stack(ls_node* &s)
{
    ls_node* p = s;
    ls_node* pre = s;
    while (p->next != NULL)
    {
        p = p->next;
        free(pre);
        pre = p;
    }
    free(pre);
}

bool empty_stack(ls_node* s)
{
    return (s->next == NULL);
}

void push(ls_node* &s, element_type e)
{
    ls_node* temp;
    temp = (ls_node*)malloc(sizeof(ls_node));
    temp->data = e;
    temp->next = s->next;
    s->next = temp;
}

bool pop(ls_node* &s, element_type &e)
{
    ls_node* temp;
    if (s->next == NULL)
    {
        return false;
    }
    temp = s->next;
    e = temp->data;
    s->next = temp->next;
    free(temp);
    return true;
}

bool get_top(ls_node* s, element_type &e)
{
    if (s->next == NULL)
    {
        return false;
    }
    e = s->next->data;
    return true;
}

int main()
{
    element_type e;
    ls_node* s;
    init_stack(s);
    if (empty_stack(s));
    printf("it's empty.\n");
    push(s, 5);
    pop(s, e);
    printf("%d\n", e);
    if(!pop(s, e))
    printf("pop fail.\n");
    system("pause");
    return 0;
}