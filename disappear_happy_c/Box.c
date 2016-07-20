//
//  Box.c
//  disappear_happy_c
//
//  Created by 圈圈科技 on 16/7/19.
//  Copyright © 2016年 圈圈科技. All rights reserved.
//

#include "Box.h"


Box createBox(Color color, Point point, bool visible)
{
    Box box;
    
    box.boxColor = color;
    box.point = point;
    box.visible = true;
    
    return box;
}

/**
 *  使箱子不可见
 *
 *  @param box 传入box指针
 */
void invisible(Box *box)
{
    box->visible = false;
}

/**
 *  使箱子可见
 *
 *  @param box 传入box指针
 */
void visible(Box *box)
{
    box->visible = true;
}




