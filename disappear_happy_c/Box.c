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
    box.foundFlag = false;
    
    return box;
}

/**
 *  复制箱子
 *
 *  @param srcBox 需要替换的箱子
 *  @param desBox 被复制的箱子
 *
 *  @return 返回新的副本
 */
Box *copyBox(Box *srcBox, const Box *desBox)
{
    srcBox->boxColor = desBox->boxColor;
    srcBox->point = desBox->point;
    srcBox->visible = desBox->visible;
    srcBox->foundFlag = desBox->foundFlag;
    
    srcBox->topBoxColor = desBox->topBoxColor;
    srcBox->bottomBoxColor = desBox->bottomBoxColor;
    srcBox->leftBoxColor = desBox->leftBoxColor;
    srcBox->rightBoxColor = desBox->rightBoxColor;
    
    return srcBox;
}


/**
 *  使箱子不可见
 *
 *  @param box 传入box指针
 */
void invisible(Box *box)
{
    box->visible = false;
    box->boxColor = clearColor();
}


bool isVisible(const Box *box)
{
    return box->visible && box->boxColor.type != clr;
}




