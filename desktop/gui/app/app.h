#ifndef APP_BTN_H
#define APP_BTN_H

/*LVGL的头文件*/
#include "../../lvgl/lvgl.h" /*LVGL的核心*/

/*应用文件相关的宏定义*/
#define APP_CFG_FIL "app.cfg" /*应用配置的文件名称*/
#define APP_ICN_FIL "icn.png" /*应用按钮的背景图片*/

/*导出函数*/
extern void app_int(App *lst, uint8_t cnt); /*初始化应用按钮*/

#endif /*APP_BTN_H*/
