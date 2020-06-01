#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef int element_type;
typedef struct cir_dblinked_node{
    element_type data;
    struct cir_dblinked_node* next;
    struct cir_dblinked_node* prior;
} cdnode;

void create_list_first(cdnode* &L, element_type arr[], int n)
{
    L = (cdnode*)malloc(sizeof(cdnode));
    L->next = L;
    L->prior = L;
    
}

int main()
{
    return 0;
}