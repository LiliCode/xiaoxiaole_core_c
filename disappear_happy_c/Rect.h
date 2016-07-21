//
//  Rect.h
//  disappear_happy_c
//
//  Created by 圈圈科技 on 16/7/20.
//  Copyright © 2016年 圈圈科技. All rights reserved.
//

#ifndef Rect_h
#define Rect_h

#include <stdio.h>
#include <stdbool.h>


//尺寸结构
struct size
{
    double width;
    double height;
};

typedef struct size Size;

/**
 *  创建Size并初始化
 *
 *  @param width  宽度
 *  @param height 高度
 *
 *  @return size
 */
Size sizeMake(double width, double height);

//坐标点结构
typedef struct
{
    int x;
    int y;
}Point;

/**
 *  创建Point并初始化
 *
 *  @param x x坐标
 *  @param y y坐标
 *
 *  @return 返回点
 */
Point pointMake(int x, int y);

/**
 *  比较两个点是否相等
 *
 *  @param p1 点1
 *  @param p2 点2
 *
 *  @return 返回是否相等的结果 true相等
 */
bool equalToPoint(Point p1, Point p2);

//区域结构体
typedef struct
{
    Point origin;   //位置
    Size size;      //大小
}Rect;

/**
 *  创建Rect结构并初始化
 *
 *  @param point 起点
 *  @param size  尺寸大小
 *
 *  @return 返回区域
 */
Rect rectMake(Point point, Size size);


/**
 *  点是否在区域内
 *
 *  @param rect  区域
 *  @param point 点
 *
 *  @return 返回bool
 */
bool rectContainsPoint(Rect rect, Point point);



#endif /* Rect_h */
