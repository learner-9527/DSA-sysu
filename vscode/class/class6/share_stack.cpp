#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define max_size 100
typedef int element_type;
typedef struct{
    element_type data[max_size];
    int top1;
    int top2;
} share_stack;

void init_stack(share_stack* &s)
{
    s = (share_stack*)malloc(sizeof(share_stack));
    s->top1 = -1;
    s->top2 = max_size;
}

void destroy_stack(share_stack* &s)
{
    free(s);
}

/**
 * 压栈. T(n) = O(1).
 * @param s 共享栈指针.
 * @param i 栈序号，1表示左栈，2表示右栈.
 * @param e 压栈元素.
 * @return 压栈是否成功.
 */
bool push(share_stack* s, int i, element_type e)
{
    if (s->top1 == s->top2 - 1)
    {
        return false;
    }
    if (i == 1)
    {
        s->top1++;
        s->data[s->top1] = e;
    }
    else
    {
        s->top2--;
        s->data[s->top2] = e;
    }
    return true;
}

/**
 * 弹栈. T(n) = O(1).
 * @param s 栈指针.
 * @param i 栈序号，1表示左栈，2表示右栈.
 * @param e 接受弹出元素.
 * @return 弹栈是否成功.
 */
bool pop(share_stack* s, int i, element_type &e)
{
    if (i == 1)
    {
        if (s->top1 == -1)
        {
            return false;
        }
        e = s->data[s->top1];
        s->top1--;
    }
    else
    {
        if (s->top2 == max_size)
        {
            return false;
        }
        e = s->data[s->top2];
        s->top2++;
    }
    return true;
}

bool get_top(share_stack* s, int i, element_type &e)
{
    if (i == 1)
    {
        if (s->top1 == -1)
        {
            return false;
        }
        e = s->data[s->top1];
    }
    else
    {
        if (s->top2 == max_size)
        {
            return false;
        }
        e = s->data[s->top2];
    }
    return true;
}

bool empty_stack(share_stack* s)
{
    return (s->top1 == -1 && s->top2 == max_size);
}

int main()
{
    share_stack* s;
    element_type e;
    init_stack(s);
    push(s, 1, 1);
    push(s, 2, 2);
    pop(s, 1, e);
    printf("%d\n", e);
    pop(s, 2, e);
    printf("%d\n", e);
    system("pause");
    return 0;
}