#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define max_size 100

typedef char element_type;

typedef struct{
    element_type data[max_size];
    int top;
} sq_stack;

void init_stack(sq_stack* &s);
void destroy_stack(sq_stack* &s);
bool empty_stack(sq_stack* s);
bool push(sq_stack* &s, element_type e);
bool pop(sq_stack* &s, element_type &e);
bool get_top(sq_stack* s, element_type &e);
void disply_stack(sq_stack* s);
bool symmetirc(element_type arr[]);
void trans(int num, int k);
bool match(char str[], int n);

void init_stack(sq_stack* &s)
{
    s = (sq_stack*)malloc(sizeof(sq_stack));
    s->top = -1;
}

void destroy_stack(sq_stack* &s)
{
    free(s);
}

bool empty_stack(sq_stack* s)
{
    return (s->top == -1);
}

bool push(sq_stack* &s, element_type e)
{
    if (s->top == max_size - 1)
    {
        return false;
    }
    else
    {
        s->top++;
        s->data[s->top] = e;
        return true;
    }
}

bool pop(sq_stack* &s, element_type &e)
{
    if (s->top == -1)
    {
        return false;
    }
    else
    {
        e = s->data[s->top];
        s->top--;
        return true;
    }
}

bool get_top(sq_stack* s, element_type &e)
{
    if (s->top == -1)
    {
        return false;
    }
    else
    {
        e = s->data[s->top];
        return true;
    }
}

void disply_stack(sq_stack* s)
{
    printf("stack: ");
    for (int i = 0; i <= s->top; i++)
    {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

/**
 * 判断数组是否对称. T(n) = O(n).
 * @param arr 数组.
 */
bool symmetirc(element_type arr[])
{
    sq_stack* s;
    element_type e;
    int i;
    init_stack(s);
    for (i = 0; arr[i] != '\0'; i++)
    {
        push(s, arr[i]);
    }
    for (i = 0; arr[i] != '\0'; i++)
    {
        pop(s, e);
        if (e != arr[i])
        {
            destroy_stack(s);
            return false;
        }
    }
    destroy_stack(s);
    return true;
}

/**
 * 输出非负十进制数的k进制形式. T(n) = O(log n).
 * @param num 非负十进制数.
 * @param k 制定转换进制.
 */
void trans(int num, int k)
{
    sq_stack* s;
    int remainder;
    int e;
    init_stack(s);
    if (num == 0)
    {
        printf("0\n");
    }
    while (num != 0)
    {
        remainder = num % k;
        push(s, remainder);
        num /= k;
    }
    // 遍历出栈条件.
    while (!empty_stack(s))
    {
    //    pop(s, e);
        printf("%d", e);
    }
    printf("\n");
    destroy_stack(s);
}

/**
 * 判断字符串的左右括号是否匹配.
 * @param str 字符串.
 * @param n 字符串长度.
 * @algorithm:
 * 1. 遍历字符串，遇到'('则存入栈.
 * 2. 遇到')'则出栈.
 * 3. 不匹配当且仅当中途出栈失败或者最后栈不为空.
 * @return 匹配返回true，否则返回false.
 */
bool match(char str[], int n)
{
    sq_stack* s;
    init_stack(s);
    // element_type: char
    element_type e;
    for (int i = 0; i < n; i++)
    {
        if (str[i] == '(')
        {
            push(s, str[i]);
        }
        else if (str[i] == ')')
        {
            if (!pop(s, e))
            {
                return false;
            }
        }
    }
    if (empty_stack(s))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    // symmetric测试.
    // element_type arr[max_size] = {1, 2, 1};
    // sq_stack* s;
    // init_stack(s);
    // if (symmetirc(arr))
    // printf("it's symmetric.\n");
    // else
    // {
    //     printf("it's not symmetric.\n");
    // }

    // trans测试.
    // trans(10, 8);

    // match测试.
    // char str[5] = {'(', '1', '2', '5', ')'};
    // if (match(str, 5))  printf("yes\n");
    system("pause");
    return 0;
}