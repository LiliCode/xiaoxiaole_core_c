//
//  Array.c
//  disappear_happy_c
//
//  Created by Lili on 16/7/21.
//  Copyright © 2016年 圈圈科技. All rights reserved.
//

#include "Array.h"
#include <stdlib.h>

/**
 *  创建数组类型
 *
 *  @return 返回数组
 */
Array *createArray()
{
    Array *array = (Array *)malloc(sizeof(Array));
    array->count = 0;
    array->pArray = NULL;
    
    return array;
}

/**
 *  删除数组
 *
 *  @param array 需要删除的数组
 */
void deleteArray(Array *array)
{
    //先删除数组中指向数组首地址的链表
    
    
    array->pArray = NULL;
    //容量置0
    array->count = 0;
    //删除数组
    free(array);
    array = NULL;
}







