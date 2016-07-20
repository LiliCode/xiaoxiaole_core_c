//
//  Rect.c
//  disappear_happy_c
//
//  Created by 圈圈科技 on 16/7/20.
//  Copyright © 2016年 圈圈科技. All rights reserved.
//

#include "Rect.h"


bool rectContainsPoint(Rect rect, Point point)
{
    if (point.x < rect.origin.x || point.y < rect.origin.y ||
        point.x > (rect.origin.x + rect.size.width) || point.y > (rect.origin.y + rect.size.height))
    {
        return false;
    }
    
    return true;
}


Size sizeMake(double width, double height)
{
    Size size;
    
    size.width = width;
    size.height = height;
    
    return size;
}

Point pointMake(int x, int y)
{
    Point point;
    
    point.x = x;
    point.y = y;
    
    return point;
}

Rect rectMake(Point point, Size size)
{
    Rect rect;
    
    rect.origin = point;
    rect.size = size;
    
    return rect;
}


