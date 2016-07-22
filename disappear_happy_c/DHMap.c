//
//  DHMap.c
//  disappear_happy_c
//
//  Created by 圈圈科技 on 16/7/19.
//  Copyright © 2016年 圈圈科技. All rights reserved.
//

#include "DHMap.h"
#include <stdlib.h>
#include <time.h>


#define Debug (1)   //调试

/**
 *  全局地图数组
 */
static Box mapArray[MAP_SIZE][MAP_SIZE];

/**
 *  存放找到同种颜色箱子的位置
 */
Array *foundBoxList;


/**
 *  找到相同的方块
 *
 *  @param map        地图
 *  @param touchPoint 点击点
 *  @param fromPoint  从哪个点过来
 */
void foundBoxs(Map map, Point touchPoint, Point fromPoint);

/**
 *  使同种颜色的箱子消失
 *
 *  @param map          游戏地图
 *  @param boxLocations 同种颜色箱子位置的集合
 */
void destroyBoxs(Map map, Array *boxLocations);

/**
 *  移动箱子
 *
 *  @param map          地图
 *  @param boxLocations 位置
 */
void moveBoxs(Map map, Array *boxLocations);

/**
 *  求最值
 *
 *  @param locations 数组
 *  @param compare   回调比较
 *
 *  @return 返回最大或最小值
 */
int extremum(Array *locations, bool (*compare)(int value1, int value2));

/**
 *  遍历位置
 *
 *  @param map       游戏地图
 *  @param locations 同种颜色箱子的位置
 *  @param callback  回调函数
 */
void enumerateLocations(Map map, Array *locations, void (*callback)(Map map, Point location));

/**
 *  箱子消失的回调函数
 *
 *  @param map      游戏地图
 *  @param location 传出位置
 */
void destroyBoxCallback(Map map, Point location);



Map createMap()
{
    //初始化地图
    Map map;
    map.rect = rectMake(pointMake(0, 0), sizeMake(MAP_SIZE, MAP_SIZE));
    map.map_array = mapArray;

    //随机种子
    srand((unsigned)time(NULL));
    //颜色
    color_function colors[] = {redColor, yellowColor, blueColor};
    
    for(int row = 0; row < map.rect.size.height; row++)
    {
        for(int col = 0; col < map.rect.size.width; col++)
        {
            int color_index = rand() % (sizeof(colors) / sizeof(color_function));
            //创建box
            Box box = createBox(colors[color_index](), pointMake(col, row), true);
            *(*(map.map_array + row) + col) = box;
        }
    }
    
    //初始化存放同种颜色箱子位置的数组
    foundBoxList = createArray();
    
    return map;
}

void initMap(Map map)
{
    for(int row = 0; row < map.rect.size.height; row++)
    {
        for(int col = 0; col < map.rect.size.width; col++)
        {
            Box *box = *(map.map_array + row) + col;
            //设置周围颜色类型
            box->topBoxColor = row? (*(map.map_array + row-1) + col)->boxColor.type : clr;
            box->bottomBoxColor = row != map.rect.size.height-1? (*(map.map_array + row+1) + col)->boxColor.type : clr;
            box->leftBoxColor = col? (*(map.map_array + row) + col-1)->boxColor.type : clr;
            box->rightBoxColor = col != map.rect.size.width-1? (*(map.map_array + row) + col+1)->boxColor.type : clr;
        }
    }
}


void printMap(Map map)
{
    for(int i = 0; i < map.rect.size.height; i++)
    {
        for(int j = 0; j < map.rect.size.width; j++)
        {
            printf("%d ", (*(map.map_array + i) + j)->boxColor.type);
        }
        
        printf("\n");
    }
}


void clickMapPoint(Map map, Point point)
{
    //判断是否在点击范围内
    if (!rectContainsPoint(map.rect, point))
    {
        return;
    }
    
    //判断点击的box是否是无效的box
    Box *clickBox = *(map.map_array + point.y) + point.x;
    if (clickBox->boxColor.type == clr && !clickBox->visible)
    {
        return;
    }
    
    //如果点在地图中
    //找到同种颜色的箱子
    foundBoxs(map, point, point);
    //销毁箱子
    destroyBoxs(map, foundBoxList);
}



void foundBoxs(Map map, Point touchPoint, Point fromPoint)
{
    //获取触摸点的box
    Box *clickBox = *(map.map_array + touchPoint.y) + touchPoint.x;
    //已经找到过一次
    clickBox->foundFlag = true;
    //保存箱子位置
    addElement(foundBoxList, clickBox->point);
#if Debug
    printf("boxColor.type = %d location = {%d , %d}\n",clickBox->boxColor.type, clickBox->point.x, clickBox->point.y);
#endif
    //向上查找
    if (clickBox->topBoxColor == clickBox->boxColor.type && fromPoint.y != touchPoint.y-1)
    {
        //判断下一个box是否被查找过
        if (!(*(map.map_array + touchPoint.y-1) + touchPoint.x)->foundFlag)
        {
            //递归调用 不断查找
            foundBoxs(map, pointMake(touchPoint.x, touchPoint.y-1), touchPoint);
        }
    }
    //向下查找
    if (clickBox->bottomBoxColor == clickBox->boxColor.type && fromPoint.y != touchPoint.y+1)
    {
        if (!(*(map.map_array + touchPoint.y+1) + touchPoint.x)->foundFlag)
        {
            foundBoxs(map, pointMake(touchPoint.x, touchPoint.y+1), touchPoint);
        }
    }
    //向左查找
    if (clickBox->leftBoxColor == clickBox->boxColor.type && fromPoint.x != touchPoint.x-1)
    {
        if (!(*(map.map_array + touchPoint.y) + touchPoint.x-1)->foundFlag)
        {
            foundBoxs(map, pointMake(touchPoint.x-1, touchPoint.y), touchPoint);
        }
    }
    //向右查找
    if (clickBox->rightBoxColor == clickBox->boxColor.type && fromPoint.x != touchPoint.x+1)
    {
        if (!(*(map.map_array + touchPoint.y) + touchPoint.x+1)->foundFlag)
        {
            foundBoxs(map, pointMake(touchPoint.x+1, touchPoint.y), touchPoint);
        }
    }
}


void enumerateLocations(Map map, Array *locations, void (*callback)(Map map, Point location))
{
    if (!locations || !locations->pArray)
    {
        printf("数组为空!\n");
        return;
    }
    
    Element *tempNode = locations->pArray;
    while (tempNode)
    {
        //回调
        callback(map, tempNode->element);
        
        //计数
        tempNode = tempNode->next;
    }
}

void destroyBoxCallback(Map map, Point location)
{
    //销毁箱子
    Box *box = *(map.map_array + location.y) + location.x;
    //不可见
    invisible(box);
}

void destroyBoxs(Map map, Array *boxLocations)
{
    //必须要用两个或两个以上的箱子才能消失
    if (boxLocations->count >= 2)
    {
        //遍历位置
        enumerateLocations(map, boxLocations, destroyBoxCallback);
        //向下移动或向左移动
        moveBoxs(map, boxLocations);
        //删除数组全部元素
        removeAllElement(boxLocations);
    }
    else
    {
        //只有一个箱子的时候
        Point location = elementAtIndex(boxLocations, 0);
        Box *box = *(map.map_array + location.y) + location.x;
        box->foundFlag = false; //重置找到标示
#if Debug
        printf("function destroyBoxs -> 没有箱子可以消失!\n");
#endif
        //删除数组全部元素
        removeAllElement(boxLocations);
    }
}

bool compareMax(int value1, int value2)
{
    return value1 < value2;
}

bool compareMin(int value1, int value2)
{
    return value1 > value2;
}

int extremum(Array *locations, bool (*compare)(int value1, int value2))
{
    if (!locations && !locations->pArray)
    {
        printf("数组为空!\n");
        return 0;
    }
    
    Element *tempNode = locations->pArray;
    int max = tempNode->element.x;  //初始值
    while (tempNode)
    {
        if (compare(max, tempNode->element.x))
        {
            max = tempNode->element.x;
        }
        
        //计数
        tempNode = tempNode->next;
    }
    
    return max;
}


void moveBoxs(Map map, Array *boxLocations)
{
    //找最大最小列
    int maxX = extremum(boxLocations, compareMax);
    int minX = extremum(boxLocations, compareMin);
#if Debug
    printf("minRow = %d maxRow = %d\n",minX, maxX);
#endif
    
    for (int px = minX; px <= maxX; px++)
    {
        for (int py = map.rect.size.height-1; py >= 0; py--)
        {
            Box *box = *(map.map_array + py) + px;
            if (isVisible(box))
            {
                continue;   //如果箱子可见，就跳到上面的箱子
            }
            
            //源箱子不可见
            //找到显示的箱子交换
            for (int pyy = py-1; pyy >= 0; pyy--)
            {
                Box *desBox = *(map.map_array + pyy) + px;
                if (!isVisible(desBox))
                {
                    continue;   //如果箱子不可见，就跳到上面的箱子
                }
                
                //目标箱子可见
                //交换
                Box *tempBox = box;
                copyBox(box, desBox);
                copyBox(desBox, tempBox);
#if Debug
                printMap(map);
                printf("\n");
#endif
                break;
            }
        }
    }
}









