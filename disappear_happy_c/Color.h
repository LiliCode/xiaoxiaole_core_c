//
//  Color.h
//  disappear_happy_c
//
//  Created by 圈圈科技 on 16/7/19.
//  Copyright © 2016年 圈圈科技. All rights reserved.
//

#ifndef Color_h
#define Color_h

#include <stdio.h>


//颜色辨别枚举
enum color_type
{
    //无色
    clr = 0,
    //白色
    white,
    //黑色
    black,
    //红色
    red,
    //绿色
    green,
    //蓝色
    blue,
    //蓝绿色
    cyan,
    //黄色
    yellow,
    //品红
    magenta,
    //橙色
    orange,
    //紫色
    purple,
    //棕色
    brown,
    //其他颜色
    ohter,
    
    color_type_Count
};

typedef enum color_type ColorType;

//颜色结构体
struct color
{
    double R;
    double G;
    double B;
    double alpha;
    
    ColorType type;
};

typedef struct color Color;

typedef Color (*color_function)();  //颜色值的函数指针



//无色
extern Color clearColor();
//白色
extern Color whiteColor();
//黑色
extern Color blackColor();
//红色
extern Color redColor();
//绿色
extern Color greenColor();
//蓝色
extern Color blueColor();
//蓝绿色
extern Color cyanColor();
//黄色
extern Color yellowColor();
//品红
extern Color magentaColor();
//橙色
extern Color orangeColor();
//紫色
extern Color purpleColor();
//棕色
extern Color brownColor();

/**
 *  根据RGB三基色设置颜色
 *
 *  @param R     红色通道值
 *  @param G     绿色通道值
 *  @param B     蓝色通道值
 *  @param alpha 透明通道值
 *
 *  @return 返回颜色结构
 */
extern Color colorWithRGB(double R, double G, double B, double alpha);

/**
 *  打印颜色
 *
 *  @param color 传入需要打印的颜色
 */
extern void printColor(const Color color);


#endif /* Color_h */




