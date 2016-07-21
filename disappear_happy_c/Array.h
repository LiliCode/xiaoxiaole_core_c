//
//  Array.h
//  disappear_happy_c
//
//  Created by Lili on 16/7/21.
//  Copyright © 2016年 圈圈科技. All rights reserved.
//

#ifndef Array_h
#define Array_h

#include <stdio.h>
#include "Rect.h"

typedef unsigned long ArrayCount;

//元素结构
struct element
{
    Point element;
    struct element *next;
};

typedef struct element Element;

//数组结构
struct array
{
    ArrayCount count;   //数组容量
    Element *pArray;    //数组首地址
};

typedef struct array Array;

/**
 *  创建数组类型
 *
 *  @return 返回数组
 */
Array *createArray();

/**
 *  删除数组
 *
 *  @param array 需要删除的数组
 */
void deleteArray(Array *array);





#endif /* Array_h */





