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

#define NONE_COL   (-1)    //没找到空列

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
 *  @param fromPoint  从哪个点过来，当前点击点就传入当前点位置
 */
void foundBoxs(Map map, DHPoint touchPoint, DHPoint fromPoint);

/**
 *  使同种颜色的箱子消失
 *
 *  @param map          游戏地图
 *  @param boxLocations 同种颜色箱子位置的集合
 */
void destroyBoxs(Map map, Array *boxLocations);

/**
 *  箱子下落
 *
 *  @param map          地图
 *  @param boxLocations 位置
 */
void fallBoxs(Map map, Array *boxLocations);

/**
 *  消除空行
 *
 *  @param map 当前地图
 *  @param col 需要消除的行
 */
void disappearEmptyCols(Map map, const int col);

/**
 *  获取空列
 *
 *  @param map        当前地图
 *  @param lowerLimit 范围下限
 *  @param upperLimit 范围山上限
 *
 *  @return 返回空列编号
 */
int getEmptyCol(Map map, int lowerLimit, int upperLimit);

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
void enumerateLocations(Map map, Array *locations, void (*callback)(Map map, DHPoint location));

/**
 *  箱子消失的回调函数
 *
 *  @param map      游戏地图
 *  @param location 传出位置
 */
void destroyBoxCallback(Map map, DHPoint location);

/**
 初始化地图
 
 - returns: 返回空
 */
void initMap(Map map);

void initMap(Map map)
{
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
}


Map createMap(pAlert msgCallback)
{
    //初始化地图
    Map map;
    map.rect = rectMake(pointMake(0, 0), sizeMake(MAP_SIZE, MAP_SIZE));
    map.map_array = mapArray;
    map.alert = msgCallback;    //消息回调
    
    //初始化地图
    initMap(map);
    
    //初始化存放同种颜色箱子位置的数组
    foundBoxList = createArray();
    
    return map;
}

/**
 *  重置地图
 *
 *  @param map 地图
 */
extern void resetMap(Map map)
{
    //删除选中数组的全部元素
    removeAllElement(foundBoxList);
    //重新初始化地图
    initMap(map);
}

/**
 *  删除地图
 *
 *  @param map 地图
 */
extern void deleteMap(Map map)
{
    //删除存放同种颜色数组
    deleteArray(foundBoxList);
    //清除地图
    for(int row = 0; row < map.rect.size.height; row++)
    {
        for(int col = 0; col < map.rect.size.width; col++)
        {
            //创建box
            Box box = createBox(clearColor(), pointMake(col, row), false);
            *(*(map.map_array + row) + col) = box;
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


void clickMapPoint(Map map, DHPoint point)
{
    //判断是否在点击范围内
    if (!rectContainsPoint(map.rect, point))
    {
        if (map.alert) map.alert("点击在地图区域外!", ClickOutsideRect);
        return;
    }
    
    //判断点击的box是否是无效的box
    Box *clickBox = *(map.map_array + point.y) + point.x;
    if (!isVisible(clickBox))
    {
        if (map.alert) map.alert("点击了无效方块!", ClickInvalid);
        return;
    }
    
    //如果点在地图中
    //找到同种颜色的箱子
    foundBoxs(map, point, point);
    //销毁箱子
    destroyBoxs(map, foundBoxList);
}



void foundBoxs(Map map, DHPoint touchPoint, DHPoint fromPoint)
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
    
    //获取四个方向的相邻的方块类型 使用条件表达式判断是否在边界
    ColorType topBoxColorType = touchPoint.y-1 >= 0? (*(map.map_array + touchPoint.y-1) + touchPoint.x)->boxColor.type : clr;
    ColorType bottomBoxColorType = touchPoint.y+1 <= map.rect.size.height-1? (*(map.map_array + touchPoint.y+1) + touchPoint.x)->boxColor.type : clr;
    ColorType leftBoxColorType = touchPoint.x-1 >= 0? (*(map.map_array + touchPoint.y) + touchPoint.x-1)->boxColor.type : clr;
    ColorType rightBoxColorType = touchPoint.x+1 <= map.rect.size.width-1? (*(map.map_array + touchPoint.y) + touchPoint.x+1)->boxColor.type : clr;
    
    //向上查找
    if (topBoxColorType == clickBox->boxColor.type && fromPoint.y != touchPoint.y-1)
    {
        //判断下一个box是否被查找过
        if (!(*(map.map_array + touchPoint.y-1) + touchPoint.x)->foundFlag)
        {
            //递归调用 不断查找
            foundBoxs(map, pointMake(touchPoint.x, touchPoint.y-1), touchPoint);
        }
    }
    //向下查找
    if (bottomBoxColorType == clickBox->boxColor.type && fromPoint.y != touchPoint.y+1)
    {
        if (!(*(map.map_array + touchPoint.y+1) + touchPoint.x)->foundFlag)
        {
            foundBoxs(map, pointMake(touchPoint.x, touchPoint.y+1), touchPoint);
        }
    }
    //向左查找
    if (leftBoxColorType == clickBox->boxColor.type && fromPoint.x != touchPoint.x-1)
    {
        if (!(*(map.map_array + touchPoint.y) + touchPoint.x-1)->foundFlag)
        {
            foundBoxs(map, pointMake(touchPoint.x-1, touchPoint.y), touchPoint);
        }
    }
    //向右查找
    if (rightBoxColorType == clickBox->boxColor.type && fromPoint.x != touchPoint.x+1)
    {
        if (!(*(map.map_array + touchPoint.y) + touchPoint.x+1)->foundFlag)
        {
            foundBoxs(map, pointMake(touchPoint.x+1, touchPoint.y), touchPoint);
        }
    }
}


void enumerateLocations(Map map, Array *locations, void (*callback)(Map map, DHPoint location))
{
    if (!locations || !locations->pArray)
    {
#if Debug
        printf("数组为空!\n");
#endif
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

void destroyBoxCallback(Map map, DHPoint location)
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
        if (map.alert) map.alert("方块将要消失!", BoxWillDisapper);
        //遍历位置
        enumerateLocations(map, boxLocations, destroyBoxCallback);
        
#if Debug
        printMap(map);
        printf("\n");
#endif
        
        //向下移动或向左移动填补空缺位置
        fallBoxs(map, boxLocations);
        //删除数组保存的相同颜色方块的位置
        removeAllElement(boxLocations);
        
        if (map.alert) map.alert("方块已经消失!", BoxDidDisapper);
    }
    else
    {
        //只有一个箱子的时候
        DHPoint location = elementAtIndex(boxLocations, 0);
        Box *box = *(map.map_array + location.y) + location.x;
        box->foundFlag = false; //重置找到标示
        //消息回调
        if (map.alert) map.alert("没有可以消失的方块!", ClickInvalid);
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


void fallBoxs(Map map, Array *boxLocations)
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
                Box tempBox;
                copyBox(&tempBox, box);
                copyBox(box, desBox);
                copyBox(desBox, &tempBox);
                
                break;
            }
        }
    }
    
    //遇到空列整体左移
    //先找到空列
    while (1)
    {
        int emptyCol = getEmptyCol(map, minX, maxX--);
        if (emptyCol == NONE_COL || emptyCol == map.rect.size.width-1)
        {
            break;
        }
        //消去空行
        disappearEmptyCols(map, emptyCol);
    }
    
#if Debug
    printMap(map);
#endif
}


void disappearEmptyCols(Map map, const int col)
{
    for (int py = 0; py <= (int)map.rect.size.height-1; py++)
    {
        for (int px = col+1; px <= (int)map.rect.size.width-1; px++)
        {
            Box *srcBox = *(map.map_array + py) + px-1; //空行的方块
            Box *desBox = *(map.map_array + py) + px;   //被交换的方块
            //向左平移
            Box tempBox;
            copyBox(&tempBox, srcBox);
            copyBox(srcBox, desBox);
            copyBox(desBox, &tempBox);
        }
    }
}

int getEmptyCol(Map map, int lowerLimit, int upperLimit)
{
    int emptyCol = NONE_COL;
    for (int px = lowerLimit; px <= upperLimit; px++)
    {
        //获取最底部的方块
        Box *box = *(map.map_array + (int)map.rect.size.height-1) + px;
        //判断是否可见
        if (!isVisible(box))
        {
            emptyCol = px;
            break;  //不找了
        }
    }
    
    return emptyCol;
}







