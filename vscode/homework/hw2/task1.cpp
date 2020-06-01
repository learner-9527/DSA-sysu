#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

#define max_class 20

/**
 * 存储学生信息的结点.
 * @param number 学号.
 * @param name 姓名.
 * @param next 指向下一个学生的指针.
 */
typedef struct studentnode{
    string number;
    string name;
    studentnode* next;
    void print();
} stud;

void stud::print()
{
    cout << number << '\t';
    cout << name << endl;
}

/**
 * 存储班级信息的顺序表.
 * @param Class 班级数组，存储该班级的学生链表头指针.
 * @param length 数组实际长度.
 */
typedef struct{
    stud* Class[max_class];    
    int length;
} class_list;

/**
 * 创建班级顺序表.
 * @param L 顺序表指针.
 * @param n 班级个数.
 */
void create_classes(class_list* &L, int n)
{
    L = new class_list;
    for (int i = 0; i < n; i++)
    {
        L->Class[i] = new stud;
        L->Class[i]->next = NULL;
    }
    L->length = n;
}

/**
 * 添加一个班级.
 */
bool add_class(class_list* &L, int i)
{
    if (L->length == max_class)
    {
        return false;
    }
    L->Class[--i] = new stud;
    L->Class[i]->next = NULL;
    L->length++;
}

/**
 * 尾插法为某个班级注册m个学生.
 * @complexity: T(n,m) = O(m). n个班级，每班m个学生.
 * @param L 班级顺序表指针.
 * @param i 班号，取值1到length.
 */
bool enroll(class_list* &L, int i)
{
    if (i < 1 || i > L->length)
    {
        return false;
    }
    stud* temp;
    stud* rear = L->Class[--i];
    int m;
    cout << "enroll class " << i + 1 << ":\n";
    cout << "the number of students: ";
    cin >> m;
    for (int j = 0; j < m; j++)
    {
        temp = new stud;
        cout << "student's number: ";
        cin >> temp->number;
        cout << "student's name: ";
        cin >> temp->name;
        rear->next = temp;
        rear = temp;
    }
    rear->next = NULL;
    return true;
}

/**
 * 在某个班级新添加一个学生.
 * @complexity: T(n,m) = O(1). n个班级，每班m个学生.
 * @param L 班级顺序表指针.
 * @param i 班号.
 */
bool insert(class_list* &L, int i)
{
    stud* temp;
    if (i < 1 || i > L->length)
    {
        return false;
    }
    temp = new stud;
    cout << "student's number: ";
    cin >> temp->number;
    cout << "student's name: ";
    cin >> temp->name;
    temp->next = L->Class[--i]->next;
    L->Class[i]->next = temp;
    return true;
}

/**
 * 删除指定班级和学号的学生.
 * @complexity: T(n,m) = O(m). n个班级，每班m个学生.
 * @param L 班级顺序表指针.
 * @param i 班号.
 * @param number 学号.
 */
stud* _delete(class_list* &L, int i, string number)
{
    stud* p = L->Class[--i];
    stud* pre = p;
    while (p->next != NULL)
    {
        p = p->next;
        if (p->number == number)
        {
            pre->next = p->next;
            return p;
        }
        pre = p;
    }
}

/**
 * 查找指定班级和学号的学生.
 * @complexity: T(n,m) = O(m). n个班级，每班m个学生.
 * @param L 班级顺序表指针.
 * @param i 班号.
 * @param number 学号.
 */
void search(class_list* L, int i, string number)
{
    stud* p = L->Class[--i];
    while (p->next != NULL)
    {
        p = p->next;
        if (p->number == number)
        {
            p->print();
            return;
        }
    }
    cout << "can't find this student." << endl;
}

/**
 * 输出所有班级所有学生信息.
 * @complexity: T(n,m) = O(nm). n个班级，每班m个学生.
 */
void display(class_list* L)
{
    stud* p;
    for (int i = 0; i < L->length; i++)
    {
        p = L->Class[i];
        cout << "class " << i + 1 << endl;
        while (p->next != NULL)
        {
            p = p->next;
            p->print();
        }
    }
}

int main()
{
    class_list* L;
    stud* s;
    string number;
    int n;
    cout << "the number of class: ";
    cin >> n;
    create_classes(L, n);
    // 再加一个班级，共n+1个.
    add_class(L, n + 1);
    for (int i = 1; i <= n + 1; i++)
    {
        enroll(L, i);
    }
    display(L);
    // 在1班插入学生.
    insert(L, 1);
    display(L);
    cout << "delete number: (for example, in class 1)";
    cin >> number;
    getchar();
    // 删除1班某个学生.
    s = _delete(L, 1, number);
    s->print();
    display(L);
    cout << "search number: (for example, in class 2)";
    cin >> number;
    // 查找2班某个学生.
    search(L, 2, number);
    system("pause");
    return 0;
}