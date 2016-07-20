//
//  Color.c
//  disappear_happy_c
//
//  Created by 圈圈科技 on 16/7/19.
//  Copyright © 2016年 圈圈科技. All rights reserved.
//

#include "Color.h"

/*
 + (UIColor *)blackColor;      // 0.0 white
 + (UIColor *)darkGrayColor;   // 0.333 white
 + (UIColor *)lightGrayColor;  // 0.667 white
 + (UIColor *)whiteColor;      // 1.0 white
 + (UIColor *)grayColor;       // 0.5 white
 + (UIColor *)redColor;        // 1.0, 0.0, 0.0 RGB
 + (UIColor *)greenColor;      // 0.0, 1.0, 0.0 RGB
 + (UIColor *)blueColor;       // 0.0, 0.0, 1.0 RGB
 + (UIColor *)cyanColor;       // 0.0, 1.0, 1.0 RGB
 + (UIColor *)yellowColor;     // 1.0, 1.0, 0.0 RGB
 + (UIColor *)magentaColor;    // 1.0, 0.0, 1.0 RGB
 + (UIColor *)orangeColor;     // 1.0, 0.5, 0.0 RGB
 + (UIColor *)purpleColor;     // 0.5, 0.0, 0.5 RGB
 + (UIColor *)brownColor;      // 0.6, 0.4, 0.2 RGB
 + (UIColor *)clearColor;      // 0.0 white, 0.0 alpha
 */


Color colorWithRGBType(double R, double G, double B, double alpha, enum color_type type);

Color colorWithRGBType(double R, double G, double B, double alpha, enum color_type type)
{
    Color color = colorWithRGB(R, G, B, alpha);
    color.type = type;
    return color;
}

Color colorWithRGB(double R, double G, double B, double alpha)
{
    Color color;
    
    color.alpha = alpha;
    color.R = R;
    color.G = G;
    color.B = B;
    
    return color;
}

void printColor(const Color color)
{
    printf("R = %lg\nG = %lg\nB = %lg\nalpha = %lg\n", color.R, color.G, color.B, color.alpha);
}

//无色
Color clearColor()
{
    return colorWithRGBType(0, 0, 0, 0, clr);
}

//白色
Color whiteColor()
{
    return colorWithRGBType(1.0f, 1.0f, 1.0f, 1.0f, white);
}

//黑色
Color blackColor()
{
    return colorWithRGBType(0, 0, 0, 1.0f, black);
}

//红色
Color redColor()
{
    return colorWithRGBType(1.0f, 0, 0, 1.0f, red);
}

//绿色
Color greenColor()
{
    return colorWithRGBType(0, 1.0f, 0, 1.0f, green);
}

//蓝色
Color blueColor()
{
    return colorWithRGBType(0, 0, 1.0f, 1.0f, blue);
}

//蓝绿色
Color cyanColor()
{
    return colorWithRGBType(0, 1.0f, 1.0f, 1.0f, cyan);
}

//黄色
Color yellowColor()
{
    return colorWithRGBType(1.0f, 1.0f, 0, 1.0f, yellow);
}

//品红
Color magentaColor()
{
    return colorWithRGBType(1.0f, 0, 1.0f, 1.0f, magenta);
}

//橙色
Color orangeColor()
{
    return colorWithRGBType(1.0f, 0.5f, 0, 1.0f, orange);
}

//紫色
Color purpleColor()
{
    return colorWithRGBType(0.5f, 0, 0.5f, 1.0f, purple);
}

//棕色
Color brownColor()
{
    return colorWithRGBType(0.6f, 0.4f, 0.2f, 1.0f, brown);
}


