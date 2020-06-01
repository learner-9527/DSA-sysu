/*
    荷兰国旗问题：设有一个条块序列，每个条块为红（0）、白（1）、兰（2）
    三种颜色中的一种。假设该序列采用顺序表存储，
    设计一个时间复杂度为O(n)的算法，
    使得这些条块按红、白、兰的顺序排好，即排成荷兰国旗图案。
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// 宏定义，条块顺序表的最大长度.
#define max_size 100

// 定义枚举类型color，分别以1，2，3表示三种颜色.
typedef enum{
    red = 1,
    white = 2,
    blue = 3
} color;

/**
 * 存储颜色条块的顺序表.
 * @param data 色条块数组，元素类型为color.
 * @param length 数组实际长度.
 */
typedef struct {
    color data[max_size];
    int length;
} color_list;

/**
 * 交换色条快x和y.
 */
void swap(color &x, color &y)
{
    color temp = x;
    x = y;
    y = temp;
}

/**
 * 用数组创建color顺序表.
 * @complexity: T(n) = O(n).
 * @param L 顺序表指针.
 * @param arr 色条快数组.
 * @param n 数组长度.
 * @algorithm:
 * 1. 为L申请动态空间.
 * 2. 遍历将arr的元素赋给data.
 * 3. length置为n.
 */
void create_list(color_list* &L, color arr[], int n)
{
    L = (color_list*)malloc(sizeof(color_list));
    for (int i = 0; i < n; i++)
    {
        L->data[i] = arr[i];
    }
    L->length = n;
}

/**
 * 将顺序表的色条快按红(1)，白(2)，蓝(3)排序，制成荷兰国旗.
 * @complexity:
 * 1. T(n) = O(n). 遍历两次.
 * 2. S(n) = O(1). 在原顺序表上重建，没有开辟新的表.
 * @param L 顺序表指针.
 * @algorithm:
 * 计数排序.
 * 1. 定义三个计数变量.
 * 2. 遍历一轮，统计三种颜色数量.
 * 3. 遍历二轮，重写顺序表.
 * @return 三种颜色不齐全则返回false，否则返回true.
 */
bool sort_flag(color_list* L)
{
    // 定义三个计数变量.
    int red = 0, white = 0, blue = 0;
    int i;
    // 遍历一轮，统计三种颜色数量.
    for (i = 0; i < L->length; i++)
    {
        switch (L->data[i])
        {
        case 1:
            red++;
            break;
        case 2:
            white++;
            break;
        case 3:
            blue++;
            break;
        default:
            break;
        }
    }
    // 遍历第二轮，重写顺序表.
    for (i = 0; i < L->length; i++)
    {
        if (i < red)
        {
            L->data[i] = color(1);
        }
        else if (i < red + white)
        {
            L->data[i] = color(2);
        }
        else
        {
            L->data[i] = color(3);
        }
    }
    // 用计数变量判断是否缺少某种颜色.
    if (red == 0 || blue == 0 || red == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void display_list(color_list* L)
{
    printf("color list: ");
    for (int i = 0; i < L->length; i++)
    {
        printf("%d ", L->data[i]);
    }
    printf("\n");
}

void destroy_list(color_list* &L)
{
    free(L);
}

int main()
{
    // 创建数组.
    int n;
    printf("please enter the length of the color list: ");
    scanf("%d", &n);
    color arr[n];
    int i;
    color_list* flg;
    printf("please enter the color list: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    // 创建顺序表.
    printf("creating list...\n");
    create_list(flg, arr, n);
    display_list(flg);
    // 排序.
    printf("making flag...\n");
    if (sort_flag(flg))
    {
        printf("success.\n");
    }
    else
    {
        printf("lack some certain colors.\n");
    }
    // 输出验证.
    display_list(flg);
    destroy_list(flg);
    system("pause");
    return 0;
}