//
//  Rect.c
//  disappear_happy_c
//
//  Created by 圈圈科技 on 16/7/20.
//  Copyright © 2016年 圈圈科技. All rights reserved.
//

#include "Rect.h"


bool rectContainsPoint(DHRect rect, DHPoint point)
{
    if (point.x < rect.origin.x || point.y < rect.origin.y ||
        point.x > (rect.origin.x + rect.size.width) || point.y > (rect.origin.y + rect.size.height))
    {
        return false;
    }
    
    return true;
}


DHSize sizeMake(double width, double height)
{
    DHSize size;
    
    size.width = width;
    size.height = height;
    
    return size;
}

DHPoint pointMake(int x, int y)
{
    DHPoint point;
    
    point.x = x;
    point.y = y;
    
    return point;
}

bool equalToPoint(DHPoint p1, DHPoint p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}


DHRect rectMake(DHPoint point, DHSize size)
{
    DHRect rect;
    
    rect.origin = point;
    rect.size = size;
    
    return rect;
}


