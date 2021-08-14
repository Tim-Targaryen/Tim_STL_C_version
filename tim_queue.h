#include"./tim_list.h"
#include"./tim_vector.h"

typedef struct Queue {
    list contents;
    int size;
} Queue;//队列类，继承链表类
typedef Queue* queue;

queue queue_init(queue that, int n)//初始化，复杂度o(n)
{
    that = (queue)malloc(sizeof(queue));
    that->contents = list_init(that->contents, 0);
    that->size = n;
    
    return that;
}
bool queue_full(queue that)//队列是否排满，复杂度o（n）
{
    return that->size <= that->contents->length ? true : false;
}
bool queue_in(queue that, type element)//入队，复杂度o（1）
{
    if (queue_full(that) == true) return false;

    list_insert(that->contents, that->contents->length - 1, element);
    return true;
}
type queue_out(queue that, type element)//出队,复杂度o（1）
{
    if (queue_full(that) == true) return (type)0;

    list_remove(that->contents, 0);
    return true;
}
void queue_free(queue that)//释放
{
    list_free(that->contents);
    free(that);
}