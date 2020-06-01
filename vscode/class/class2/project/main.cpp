#include "sqlist.h"

#include <stdio.h>
#include <windows.h>

int main()
{
    sqlist* L;
    int a[5];
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &a[i]);
    }
    create_sqlist(L, a, 5);
    disply_sqlist(L);
    system("pause");
    return 0;
}