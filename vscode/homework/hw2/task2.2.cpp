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
 * 1. T(n) = O(n). 只遍历一次.
 * 2. S(n) = O(1). 在原顺序表上重建，没有开辟新的表.
 * @param L 顺序表指针.
 * @algorithm:
 * 三路排序.
 * 1. 设置三个游标red，white，blue.
 * 2. red记录当前最右红色条块，blue记录当前最左蓝色条块.
 *    用white遍历数组.
 * 3. white遇到白色则跳过，继续往右走一步.
 * 4. white遇到红色则先让red++，然后交换red和white所指条块.
 *    由于red所指位置已被white检查过，交换后让white++.
 * 5. white遇到蓝色则先让blue--，然后交换blue和white所指条块.
 *    由于blue所指位置未被white检查过，交换后white不变.
 * 6. white等于blue时，white到达最左边的蓝色条块，遍历结束.
 * @return 三种颜色不齐全则返回false，否则返回true.
 */
bool sort_flag(color_list* L)
{
    // 定义三个游标.
    // white从0开始遍历，故初始化为0.
    // 遍历开始前红色条块个数未知，故最右边的红色条块在-1.
    // 遍历开始前蓝色条块个数未知，故最左边的蓝色条块在length.
    int red = -1, white = 0, blue = L->length;
    // white开始遍历.
    while (white < blue)
    {
        // 如果是白色(2)，white++继续走.
        if (L->data[white] == 2)
        {
            white++;
        }
        // 否则如果是红色(1).
        // 最右边的红色条块的位置+1.
        // 交换white处的红色条块和red处红/白色条块.
        // 交换后white是白色/第一个红色条块，无论哪种都要white++继续走.
        else if (L->data[white] == 1)
        {
            red++;
            swap(L->data[white], L->data[red]);
            white++;
        }
        // 否则的话必为蓝色(3).
        // 最左边的蓝色条块的位置-1.
        // 交换white处的蓝色条块和blue处的红/白/蓝色条块.
        // 由于交换后white出条块可能为红/白/蓝，white不变，再检查一次.
        else
        {
            blue--;
            swap(L->data[white], L->data[blue]);
        }
    }
    // 如果遍历结束后最右边的红色条块还在-1，说明缺少红色条块.
    // 如果遍历结束后最左边的蓝色条块还在length，说明缺少蓝色条块.
    // 如果遍历结束后最右边的红色条块紧挨着最左边的蓝色条块，说明缺少白色条块.
    if (red == -1 || blue == L->length || red == blue - 1)
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