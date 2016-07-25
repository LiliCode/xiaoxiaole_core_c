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
    DHPoint element;
    struct element *next;   //下一个节点
};

typedef struct element Element;

//数组结构
struct array
{
    ArrayCount count;   //数组容量
    Element *pArray;    //数组首地址(头节点)
    Element *lastNode;  //数组尾节点
};

typedef struct array Array;

/**
 *  创建数组类型
 *
 *  @return 返回数组
 */
extern Array *createArray();

/**
 *  删除数组
 *
 *  @param array 需要删除的数组
 */
extern void deleteArray(Array *array);

/**
 *  打印数组元素
 *
 *  @param array 当前数组
 */
extern void printArray(Array *array);


/**
 *  向数组中添加元素
 *
 *  @param array   当前数组
 *  @param element 要添加的元素
 */
extern void addElement(Array *array, DHPoint element);

/**
 *  删除数组中的元素
 *
 *  @param array   当前数组
 *  @param element 要删除的元素
 */
extern void removeElement(Array *array, DHPoint element);

/**
 *  删除数组中的全部元素
 *
 *  @param array 当前数组
 */
extern void removeAllElement(Array *array);

/**
 *  获取数组index位置的元素
 *
 *  @param array 当前数组
 *  @param index 获取的位置
 *
 *  @return 返回index位置的元素
 */
extern DHPoint elementAtIndex(Array *array, unsigned long index);

/**
 *  删除数组index位置的元素
 *
 *  @param array 当前数组
 *  @param index 删除的位置
 */
extern void removeElementAtIndex(Array *array, unsigned long index);


#endif /* Array_h */











