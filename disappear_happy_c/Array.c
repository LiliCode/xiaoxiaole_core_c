//
//  Array.c
//  disappear_happy_c
//
//  Created by Lili on 16/7/21.
//  Copyright © 2016年 圈圈科技. All rights reserved.
//

#include "Array.h"
#include <stdlib.h>

#define Debug (0)

/**
 *  分配元素节点
 *
 *  @return 返回元素节点
 */
Element *allocElementNode(Point element);

Element *allocElementNode(Point element)
{
    Element *elementNode = (Element *)malloc(sizeof(Element));
    if (!elementNode)
    {
        printf("节点分配失败!\n");
        return NULL;
    }
    
    elementNode->element = element;
    elementNode->next = NULL;
    
    return elementNode;
}

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
    array->lastNode = array->pArray;
    
    return array;
}

/**
 *  删除数组
 *
 *  @param array 需要删除的数组
 */
void deleteArray(Array *array)
{
    if (!array || !array->pArray)
    {
        printf("数组为空!\n");
        return;
    }
    
    //先删除数组中指向数组首地址的链表
    removeAllElement(array);
    
    array->pArray = NULL;
    array->lastNode = NULL;
    //容量置0
    array->count = 0;
    //删除数组
    free(array);
    array = NULL;
}

/**
 *  打印数组元素
 *
 *  @param array 当前数组
 */
void printArray(Array *array)
{
    if (!array || !array->pArray)
    {
        printf("数组为空!\n");
        return;
    }
    
    Element *tempNode = array->pArray;
    while (tempNode)
    {
        printf("point = {%d , %d}\n", tempNode->element.x, tempNode->element.y);
        tempNode = tempNode->next;
    }
}

/**
 *  向数组中添加元素
 *
 *  @param array   当前数组
 *  @param element 要添加的元素
 */
void addElement(Array *array, Point element)
{
    if (!array)
    {
        printf("数组为空!\n");
        return;
    }
    
    Element *node = allocElementNode(element);
    if (!node)
    {
        return;
    }
    
    //节点不为空 插入
    //头节点为空时，插入到头节点的next
    if (!array->pArray)
    {
        array->pArray = node;   //保存头节点
        array->lastNode = array->pArray;    //设置尾节点
    }
    else
    {
        //如果头节点不为空，新节点插入到尾节点next
        array->lastNode->next = node;
        //重置尾节点
        array->lastNode = node;
    }
    
    //计数器++
    array->count++;
}

/**
 *  删除数组中的元素
 *
 *  @param array   当前数组
 *  @param element 要删除的元素
 */
void removeElement(Array *array, Point element)
{
    if (!array || !array->pArray)
    {
        printf("数组为空!\n");
        return;
    }
    
    //查找元素
    Element *tempNode = array->pArray;  //当前游标
    Element *revNode = NULL;            //前一个节点
    while (tempNode)
    {
        if (equalToPoint(element, tempNode->element) && tempNode == array->pArray)
        {
            //如果是头节点
            array->pArray = tempNode->next; //头节点指向第二个节点
            free(tempNode); //释放节点
            array->count--; //计数器--
        }
        else if (equalToPoint(element, tempNode->element) && !tempNode->next)
        {
            //如果是尾节点
            revNode->next = NULL;
            //重置数组中的尾节点
            array->lastNode = revNode;
            free(tempNode); //释放尾节点
            array->count--; //计数器--
        }
        else
        {
            //中间的节点
            if (equalToPoint(element, tempNode->element))
            {
                //连接两边的节点
                revNode->next = tempNode->next;
                //释放节点
                free(tempNode);
                array->count--; //计数器--
            }
            else
            {
                revNode = tempNode;
            }
        }
        
        tempNode = tempNode->next;
    }
}

/**
 *  删除数组中的全部元素
 *
 *  @param array 当前数组
 */
void removeAllElement(Array *array)
{
    if (!array || !array->pArray)
    {
        printf("数组为空!\n");
        return;
    }
    
    Element *tempNode = array->pArray;
    while (tempNode)
    {
        array->pArray = tempNode->next; //头节点指向第二个节点
        free(tempNode);
        tempNode = array->pArray;
        array->count--;
#if Debug
        printf("\n");
        printArray(array);
#endif
    }
    
    //重置尾节点
    array->lastNode = NULL;
}

/**
 *  获取数组index位置的元素
 *
 *  @param array 当前数组
 *  @param index 获取的位置
 *
 *  @return 返回index位置的元素
 */
Point elementAtIndex(Array *array, unsigned long index)
{
    if (!array || !array->pArray)
    {
        printf("数组为空!\n");
        return pointMake(-1, -1);
    }
    
    Element *tempNode = array->pArray;
    unsigned long count = 0;
    Point point;
    while (tempNode)
    {
        //判断
        if (count == index)
        {
            point = tempNode->element;
            break;
        }
        
        //计数
        count++;
        tempNode = tempNode->next;
    }
    
    return point;
}

/**
 *  删除数组index位置的元素
 *
 *  @param array 当前数组
 *  @param index 删除的位置
 */
void removeElementAtIndex(Array *array, unsigned long index)
{
    if (!array || !array->pArray)
    {
        printf("数组为空!\n");
        return;
    }
    
    
    
}





