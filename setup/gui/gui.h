#ifndef GUI_H
#define GUI_H

/*LVGL的头文件*/
#include "../lvgl/lvgl.h" /*LVGL的核心*/

/*自定义的头文件*/
#include "scr/scr.h" /*屏幕*/
#include "app/app.h" /*应用*/

/*LVGL对象标志相关的宏定义*/
#define LV_OBJ_FLAG_ALL 0b11111111111111111111 /*所有内置标志*/

/*导出函数*/
extern void gui_int(void); /*初始化GUI*/

#endif /*GUI_H*/
