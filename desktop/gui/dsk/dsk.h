#ifndef DSK_H
#define DSK_H

/*LVGL的头文件*/
#include "../../lvgl/lvgl.h" /*LVGL的核心*/

/*导出自定义类型*/
typedef struct struct_App
{
    char dir[DIR_MAX_LEN]; /*应用所在目录*/
    char nam[APP_LAB_LEN]; /*应用名称*/
    char icn[DIR_MAX_LEN]; /*应用按钮的背景图片*/
    lv_obj_t *obj;         /*应用对象*/
} App;

/*桌面布局相关的宏定义*/
#define DSK_ROW 3                                     /*桌面布局的行数*/
#define DSK_COL 4                                     /*桌面布局的列数*/
#define DSK_HOR_PAD (MY_DISP_VER_RES / (DSK_COL + 1)) /*桌面水平布局的间距*/
#define DSK_VER_PAD (MY_DISP_HOR_RES / (DSK_ROW + 1)) /*桌面竖直布局的间距*/

/*导出变量*/
extern lv_obj_t *gui_scr_dsk; /*桌面*/
extern App *app_lst;          /*应用列表*/

/*导出函数*/
extern void dsk_int(void); /*初始化桌面*/

#endif /*DSK_H*/
