//
//  main.c
//  disappear_happy_c
//
//  Created by 圈圈科技 on 16/7/19.
//  Copyright © 2016年 圈圈科技. All rights reserved.
//

#include <stdio.h>
#include "DHMap.h"
#include "Array.h"


int main(int argc, const char * argv[])
{
    Map map = createMap();
    initMap(map);
    
    printMap(map);
    
    printf("\n");
    
    clickMapPoint(map, pointMake(2, 2));
    
    printMap(map);
    
//    Array *array = createArray();
//    
//    addElement(array, pointMake(0, 0));
//    addElement(array, pointMake(0, 1));
//    addElement(array, pointMake(0, 2));
//    addElement(array, pointMake(0, 3));
//    
//    printArray(array);
//    
//    removeElement(array, pointMake(0, 2));
//    
//    printf("\n");
//    printArray(array);
//    
//    removeAllElement(array);
//    printf("\n");
//    printArray(array);
//    
//    deleteArray(array);
    
    
    return 0;
}









