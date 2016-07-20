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

/**
 *  全局地图数组
 */
static Box mapArray[MAP_SIZE][MAP_SIZE];


Map createMap()
{
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
            Box box = createBox(colors[color_index](), pointMake(row, col), true);
            *(*(map.map_array + row) + col) = box;
        }
    }
    
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
    if ((*(map.map_array + point.x) + point.y)->boxColor.type == clr)
    {
        return;
    }
    
    //如果点在地图中
    disapperBoxs(map, point);
}



void disapperBoxs(Map map, Point point)
{
    Box *clickBox = *(map.map_array + point.x) + point.y;
    
    if (clickBox->topBoxColor == clickBox->boxColor.type)
    {
        
    }
    else if (clickBox->bottomBoxColor == clickBox->boxColor.type)
    {
        
    }
    else if (clickBox->leftBoxColor == clickBox->boxColor.type)
    {
        
    }
    else if (clickBox->rightBoxColor == clickBox->boxColor.type)
    {
        
    }
}







