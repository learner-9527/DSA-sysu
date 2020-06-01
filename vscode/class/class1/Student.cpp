/*
1.输入学生的学号、姓名和三门课的成绩，存入结构体中
2.编写函数，求学生三门课的总成绩，存入结构体中
3.在main中输入学生信息，调用求和函数，输出学生的学号、姓名、总成绩
4.编写sort函数，参数为结构体数组指针和数组中有效元素个数，
  实现结构体数组按总成绩从高到低排序
*/
#include <stdio.h>
#include <windows.h>
struct Student
{
    int no;
    char name[10];
    int grade[3];
    int grade_total;
};
void sum_score(Student *students, int num)
{
    int result;
    for(int i=0; i<num; i++)
    {
        result = 0;
        for(int j=0; j<3; j++)
        {
            result += students[i].grade[j];
        }
        students[i].grade_total = result;
    }
}
void sort(Student *students, int num)
{
    Student temp;
    for(int j=0; j<num-1; j++)
    {
        for(int i=0; i<num-1-j; i++)
        {
            if(students[i].grade_total < students[i+1].grade_total)
            {
                temp = students[i];
                students[i] = students[i+1];
                students[i+1] = temp;
            }
        }
    }
}
int main()
{
    Student students[3];
    for(int i=0; i<3; i++)
    {
        printf("请输入第%d名学生的学号：\n", i+1);
        scanf("%d", &students[i].no);
        printf("请输入第%d名学生的姓名：\n", i+1);
        getchar();
        gets(students[i].name);
        printf("请输入第%d名学生的成绩：\n", i+1);
        for(int j=0; j<3; j++)
        {
            printf("请输入第%d门成绩：", j+1);
            scanf("%d", &students[i].grade[j]);
        }
    }
    sum_score(students, 3);
    printf("\n");
    for(int i=0; i<3; i++)
    {
        printf("第%d名学生的学号：%d\t", i+1, students[i].no);
        printf("姓名：%s\t", students[i].name);
        printf("总成绩：%d\n", students[i].grade_total);
    }
    sort(students, 3);
    printf("\n");
    for(int i=0; i<3; i++)
    {
        printf("第%d名学生的学号：%d\t", i+1, students[i].no);
        printf("姓名：%s\t", students[i].name);
        printf("总成绩：%d\n", students[i].grade_total);
    }
    system("pause");
    return 0;
}