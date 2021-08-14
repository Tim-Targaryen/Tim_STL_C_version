#ifndef TIM_VECTOR_H
#define TIM_VECTOR_H
//#define type int //可供替换

typedef struct Vector {
    type* head;
    int length;
} Vector;//向量类
typedef Vector* vector;

vector vector_init(vector that, int n)//按元素数量初始化,复杂度o（n）
{
    that = (vector)malloc(sizeof(Vector));
    that->head = (type*)malloc(sizeof(type) * n);
    that->length = n;
    for (int i = 0; i < n; i++) 
        that->head[i] = 0;
    
    return that;
}
type vector_find(vector that, int n)//按秩搜索，复杂度O(1)
{
    return that->head[n];
}
int vector_search(vector that, type target)//按值搜索，复杂度O（n）
{
    for (int i = 0; i < that->length; i++) 
        if (that->head[i] == target) return i;

    return -1;
}
bool vector_exist(vector that, type target)//判断是否存在，包装
{
    return vector_find(that, target) < 0 ? false : true;
}
bool vector_put(vector that, int n, type element)//覆盖，复杂度o（1）
{
    if (n > that->length || n < 0) return false;
    else {
        that->head[n] = element;
        return true;
    }
}
bool vector_insert(vector that, int n, type element)//插入，复杂度o（n）,递增式扩容有待优化
{
    if (n > that->length || n < 0) return false;
    type* new_head = (type*)malloc(sizeof(type) * (that->length + 1));

    for (int i = 0; i < that->length + 1; i++) {
        if (i < n) new_head[i] = that->head[i];
        else if (i == n) new_head[i] = element;
        else new_head[i + 1] = that->head[i];  
    }
    that->head = new_head;
    that->length++;

    return true;
}
bool vector_remove(vector that, int n)//删除，复杂度o（n）
{
    if (n > that->length || n < 0) return false;
    type* new_head = (type*)malloc(sizeof(type) * (that->length - 1));

    for (int i = 0; i < that->length - 1; i++) {
        if (i < n) new_head[i] = that->head[i];
        else new_head[i] = that->head[i + 1];
    }
    that->head = new_head;
    that->length--;

    return true;
}
void vector_free(vector that)//回收，复杂度o（n）
{
    free(that->head);
    free(that);
}
void traverse(vector that, void (*visit)(type* ))//遍历，接受复杂度为m的方法，复杂度o（m） 
{
    for (int i = 0; i < that->length; i++, that->head++) 
        visit(that->head);
}

#endif