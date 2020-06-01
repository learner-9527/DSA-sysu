#ifndef SQLIST
#define SQLIST

#define max_size 50
typedef int element_type;

struct sqlist;

void create_sqlist(sqlist* &L, element_type a[], int n);
void init_sqlist(sqlist* &L);
void destroy_sqlist(sqlist* &L);
bool insert_element(sqlist* &L, int i, element_type e);
bool delete_element(sqlist* &L, int i, element_type &e);
bool is_empty_sqlist(sqlist* L);
int get_length(sqlist* L);
bool get_element(sqlist* L, int i, element_type &e);
int locate_element(sqlist* L, element_type e);
void disply_sqlist(sqlist* L);

#endif  // SQLIST
/*
    C语言中没有 bool类型，没有引用 &，使用结构体必须加前缀 struct。。。
    十分不便，故文件类型统一使用 .cpp
*/