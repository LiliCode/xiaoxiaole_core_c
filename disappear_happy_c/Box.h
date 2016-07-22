//
//  Box.h
//  disappear_happy_c
//
//  Created by 圈圈科技 on 16/7/19.
//  Copyright © 2016年 圈圈科技. All rights reserved.
//

#ifndef Box_h
#define Box_h

#include <stdio.h>
#include <stdbool.h>
#include "Color.h"
#include "Rect.h"


//方格结构体
struct box
{
    //基本属性
    Color boxColor; //颜色
    Point point;    //点坐标
    bool visible;   //是否可见
    //附加属性，在查找的时候用
    //这个方块周围的方块颜色类型
    ColorType topBoxColor;
    ColorType bottomBoxColor;
    ColorType leftBoxColor;
    ColorType rightBoxColor;
    //flag表示用于是否已经查找过
    bool foundFlag;
};

typedef struct box Box;

/**
 *  创建Box
 *
 *  @param color   box颜色
 *  @param visible 是否可见
 *
 *  @return 返回box
 */
Box createBox(Color color, Point point, bool visible);

/**
 *  复制箱子
 *
 *  @param srcBox 需要替换的箱子
 *  @param desBox 被复制的箱子
 *
 *  @return 返回新的副本
 */
Box *copyBox(Box *srcBox, const Box *desBox);

/**
 *  使箱子不可见
 *
 *  @param box 传入box指针
 */
void invisible(Box *box);

/**
 *  是否可见
 *
 *  @param box 箱子
 *
 *  @return 返回true 可见， false不可见
 */
bool isVisible(const Box *box);


#endif /* Box_h */




