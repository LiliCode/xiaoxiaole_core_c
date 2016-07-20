//
//  DHMap.h
//  disappear_happy_c
//
//  Created by 圈圈科技 on 16/7/19.
//  Copyright © 2016年 圈圈科技. All rights reserved.
//

#ifndef DHMap_h
#define DHMap_h

#include <stdio.h>
#include <stdbool.h>
#include "Box.h"

#define MAP_SIZE (8)

//定义Map类型，Map是一个隐式指针类型，指向二维数组
typedef Box (*MapArray)[MAP_SIZE];


//地图结构
struct map
{
    Rect rect;  //大小和位置
    MapArray map_array; //列表
};

typedef struct map Map;


/**
 *  创建地图
 *
 *  @return 返回地图二维数组
 */
extern Map createMap();

/**
 *  点击地图上的点
 *
 *  @param map   地图
 *  @param point 点击位置
 */
extern void clickMapPoint(Map map, Point point);



/**
 *  打印地图
 */
extern void printMap(Map map);

#endif /* DHMap_h */




