#include"./tim_list.h"
#include"./tim_vector.h"

typedef struct Stack {
    list contents;
    int size;
} Stack;//栈类，继承链表类
typedef Stack* stack;

stack stack_init(stack that, int n)//栈初始化复杂度o（n）
{
    that = (stack)malloc(sizeof(Stack));
    that->contents = list_init(that->contents, 0);
    that->size = n;
    
    return that;
}
bool stack_full(stack that)//判断是否栈满， 复杂度o（1）
{
    return that->contents->length >= that->size ? true : false;
}
bool stack_push(stack that, type element)//入栈, 复杂度o（n）
{
    if (stack_full(that)) return false;
    
    list_insert(that->contents, 0, element);
    return true;
}
type stack_pop(stack that)//出栈, 复杂度o（n)
{
    if (stack_full(that)) return (type)0;

    list_remove(that->contents, 0);
    return true;
}
void stack_free(stack that)//释放,复杂度o（n）
{
    list_free(that->contents);
    free(that);
}


 