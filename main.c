/*
    这是Tim自己开发的c容器库“tim_STL"，
    将想放入的元素define成type便可开箱即用，
    main.c 为主测试程序
*/
#include<stdio.h>   
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#define type int
/*#define Type int
#define type Type*  //想拿到元素引用的用法*/
#include"./tim_list.h"
#include"./tim_vector.h"
#include"./tim_stack.h"
#include"./tim_queue.h"

void list_test()
{
    list my_list = list_init(my_list, 5);
    
    list_put(my_list, 1, 999);
    printf("get:%d\n", list_get(my_list, 1));
    printf("se:%d\n", list_search(my_list, 999));
    list_insert(my_list, 4, 666);
    list_remove(my_list, 5);
    list_free(my_list);

    return;
}
void vector_test()
{
    vector my_vector = vector_init(my_vector, 5);

    for(int i = 0; i < 5; i++) 
        vector_put(my_vector, i, i * i);
    printf("find:%d\n", vector_find(my_vector,3));
    printf("se:%d\n", vector_search(my_vector, 16));
    vector_insert(my_vector, 3, 999);
    vector_remove(my_vector, 0);
    vector_free(my_vector);

    return;
}
void stack_test()
{
    stack my_stack = stack_init(my_stack, 5);

    for (int i = 0; i < 6; i++) 
        stack_push(my_stack, i + 1); 
    for (int i = 0; i < my_stack->size; i++) 
        printf("pop %d:%d\n", i, stack_pop(my_stack));
    stack_free(my_stack);

    return;
}
int main()
{
    int n;

    /*printf("Which data-structure you want to test:\n");
    scanf("%d", &n);

    switch (n) {
        case 1:
            vector_test();
            break;
        case 2:
            list_test();
            break;
        case 3:
            break;
        default:
            break;
    }*/
    //vector_test();
    //list_test();
    stack_test();
    printf("\nTest over!");

    return 0;
}