/*
    �����������⣺����һ���������У�ÿ������Ϊ�죨0�����ף�1��������2��
    ������ɫ�е�һ�֡���������в���˳���洢��
    ���һ��ʱ�临�Ӷ�ΪO(n)���㷨��
    ʹ����Щ���鰴�졢�ס�����˳���źã����ųɺ�������ͼ����
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// �궨�壬����˳������󳤶�.
#define max_size 100

// ����ö������color���ֱ���1��2��3��ʾ������ɫ.
typedef enum{
    red = 1,
    white = 2,
    blue = 3
} color;

/**
 * �洢��ɫ�����˳���.
 * @param data ɫ�������飬Ԫ������Ϊcolor.
 * @param length ����ʵ�ʳ���.
 */
typedef struct {
    color data[max_size];
    int length;
} color_list;

/**
 * ����ɫ����x��y.
 */
void swap(color &x, color &y)
{
    color temp = x;
    x = y;
    y = temp;
}

/**
 * �����鴴��color˳���.
 * @complexity: T(n) = O(n).
 * @param L ˳���ָ��.
 * @param arr ɫ��������.
 * @param n ���鳤��.
 * @algorithm:
 * 1. ΪL���붯̬�ռ�.
 * 2. ������arr��Ԫ�ظ���data.
 * 3. length��Ϊn.
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
 * ��˳����ɫ���찴��(1)����(2)����(3)�����Ƴɺ�������.
 * @complexity:
 * 1. T(n) = O(n). ֻ����һ��.
 * 2. S(n) = O(1). ��ԭ˳������ؽ���û�п����µı�.
 * @param L ˳���ָ��.
 * @algorithm:
 * ��·����.
 * 1. ���������α�red��white��blue.
 * 2. red��¼��ǰ���Һ�ɫ���飬blue��¼��ǰ������ɫ����.
 *    ��white��������.
 * 3. white������ɫ������������������һ��.
 * 4. white������ɫ������red++��Ȼ�󽻻�red��white��ָ����.
 *    ����red��ָλ���ѱ�white��������������white++.
 * 5. white������ɫ������blue--��Ȼ�󽻻�blue��white��ָ����.
 *    ����blue��ָλ��δ��white������������white����.
 * 6. white����blueʱ��white��������ߵ���ɫ���飬��������.
 * @return ������ɫ����ȫ�򷵻�false�����򷵻�true.
 */
bool sort_flag(color_list* L)
{
    // ���������α�.
    // white��0��ʼ�������ʳ�ʼ��Ϊ0.
    // ������ʼǰ��ɫ�������δ֪�������ұߵĺ�ɫ������-1.
    // ������ʼǰ��ɫ�������δ֪��������ߵ���ɫ������length.
    int red = -1, white = 0, blue = L->length;
    // white��ʼ����.
    while (white < blue)
    {
        // ����ǰ�ɫ(2)��white++������.
        if (L->data[white] == 2)
        {
            white++;
        }
        // ��������Ǻ�ɫ(1).
        // ���ұߵĺ�ɫ�����λ��+1.
        // ����white���ĺ�ɫ�����red����/��ɫ����.
        // ������white�ǰ�ɫ/��һ����ɫ���飬�������ֶ�Ҫwhite++������.
        else if (L->data[white] == 1)
        {
            red++;
            swap(L->data[white], L->data[red]);
            white++;
        }
        // ����Ļ���Ϊ��ɫ(3).
        // ����ߵ���ɫ�����λ��-1.
        // ����white������ɫ�����blue���ĺ�/��/��ɫ����.
        // ���ڽ�����white���������Ϊ��/��/����white���䣬�ټ��һ��.
        else
        {
            blue--;
            swap(L->data[white], L->data[blue]);
        }
    }
    // ����������������ұߵĺ�ɫ���黹��-1��˵��ȱ�ٺ�ɫ����.
    // �����������������ߵ���ɫ���黹��length��˵��ȱ����ɫ����.
    // ����������������ұߵĺ�ɫ�������������ߵ���ɫ���飬˵��ȱ�ٰ�ɫ����.
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
    // ��������.
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
    // ����˳���.
    printf("creating list...\n");
    create_list(flg, arr, n);
    display_list(flg);
    // ����.
    printf("making flag...\n");
    if (sort_flag(flg))
    {
        printf("success.\n");
    }
    else
    {
        printf("lack some certain colors.\n");
    }
    // �����֤.
    display_list(flg);
    destroy_list(flg);
    system("pause");
    return 0;
}