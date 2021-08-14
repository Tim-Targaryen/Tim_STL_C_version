#ifndef TIM_LIST_H
#define TIM_LIST_H
//#define type int //可供替换

typedef struct node {
    type element;
    int rank;
    node* next;
} node;//结点类
typedef struct List{
    node* head;
    int length;
} List;//链表类
typedef List* list;

list list_init(list that, int n)//生成链表，复杂度O(n)(malloc意义下)
{
    that = (list)malloc(sizeof(list));
    if ( n <= 0) {
        that->length = 0;
        that->head = NULL;
        return that;
    }//边界处理

    that->head = (node*)malloc(sizeof(node));
    that->head->element = 0;
    that->head->next = NULL;
    that->head->rank = 0;
    node* temp1 = that->head;
    node* temp2 = NULL;

    for (int i = 0; i < n - 1; i++) {
        temp2 = (node*)malloc(sizeof(node));
        temp2->element = (type)0;
        temp2->rank = i + 1;
        temp2->next = NULL;
        temp1->next = temp2;
        temp1 = temp2;
        temp2 = temp2->next;
    }
    that->length = n;
    
    return that;
}
node* list_find(list that, int n)//按序搜索,复杂度o(n),返回元素所在结点
{
    if (n > that->length || n < 0) return NULL;//越界
    node* temp = that->head;
    
    for (int i = 0; i < n; i++) {
        if (temp == NULL) return NULL;
        temp = temp->next;
    }
    
    return temp;
}
type list_get(list that, int n)//包装find，返回元素副本
{
    if (n >= that->length || n < 0) return (type)0;//越界
    return list_find(that, n)->element;
}
void list_traverse(list that, void (*visit)(node* ), int begin, int end)//遍历，接受对每个元素的visit操作
{
    if (begin == -1) {
        begin = 0;
        end = that->length;
    }
    
    node* temp = list_find(that, begin);
    for (int i = begin; i < end; i++, temp = temp->next) 
        visit(temp);
}
void list_index_up(node* temp) 
{
    temp->rank ++;
}
void list_index_down(node* temp)
{
    temp->rank --;
}
int list_search(list that, type target)//按值搜索,复杂度o(n)，返回序号
{
    node* temp = that->head;
    
    while(temp != NULL) {
        if (temp->element == target) return temp->rank;
        temp = temp->next;
    }

    return -1;
}
bool list_exist(list that, type target)//判断是否存在,复杂度o(n),包装
{
    if (list_search(that, target) != -1) return true;
    else return false;
}
bool list_put(list that, int n, type element)//覆盖,复杂度o(n)  
{
    if (n >= that->length || n < 0) return false;//越界
    node* temp = that->head;

    for (int i = 0; i < n; i++) {
        if (temp->next == NULL) return false;
        temp = temp->next;
    }
    temp->element = element;
    
    return true;
}
bool list_insert(list that, int n, type element)//插入,复杂度o(n)(mov指令下)
{
    if (n > that->length || n < 0) return false;//越界
    node* new_node = (node*)malloc(sizeof(node));
    new_node->element = element;
    new_node->rank = n;

    if (that->length == 0) {
        that->head = new_node;
        that->head->next = NULL;
        that->length++;
        return true;
    }
    if (n == 0) {
        new_node->next = that->head;
        that->head = new_node;
        list_traverse(that, list_index_up, 1, that->length + 1 );
        that->length++;
        return true;
    }//边界处理
    if (n == that->length - 1) {
        node* temp = list_find(that, that->length - 2);
        new_node->next = temp->next;
        temp->next->rank++;
        temp->next = new_node;
        that->length++;
        return true;
    }//边界处理
    
    node* temp = list_find(that, n - 1);
    new_node->next = temp->next;
    temp->next = new_node;
    list_traverse(that, list_index_up, new_node->next->rank, that->length + 1);
    that->length++;

    return true;
}
bool list_remove(list that, int n)//删除节点, 复杂度o（1)
{
    if (n > that->length || n < 0 || that->length == 0) return false;

    if (n == 0) {
        node* temp = that->head;
        list_traverse(that, list_index_down, -1, -1);
        that->head = that->head->next;
        free(temp);
        that->length--;
        return true;
    }//边界处理
    if (n == that->length) {
        node* temp = list_find(that, n);
        free(temp);
        that->length--;
        return true;
    }
    
    node* temp1 = list_find(that, n - 1);
    node* temp2 = temp1->next;
    temp1->next = temp1->next->next;
    free(temp2);
    list_traverse(that, list_index_down, temp1->rank + 1, that->length - 1);
    that->length--;
    
    return true;
}
void list_free(list that)//释放，复杂度 o(n)
{
    int len = that->length;
    
    for (int i = 0; i < len; i++) {
        node* temp = that->head;
        that->head = that->head->next;
        free(temp);
    }
    free(that);
}

#endif

