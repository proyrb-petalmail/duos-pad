#ifndef SCR_H
#define SCR_H

/*LVGL的头文件*/
#include "../../lvgl/lvgl.h" /*LVGL的核心*/

/*导出变量*/
extern lv_obj_t *gui_scr; /*屏幕*/

/*导出函数*/
extern void scr_int(void); /*初始化屏幕*/

#endif /*SCR_H*/
