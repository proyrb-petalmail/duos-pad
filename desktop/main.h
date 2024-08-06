#ifndef MAIN_H
#define MAIN_H

/*C的头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*调试相关的宏定义*/
#define DEBUG 0 /*是否开启调试*/

/*LVGL屏幕设置相关的宏定义*/
#define MY_DISP_HOR_RES 800  /*显示屏定义的水平方向像素个数*/
#define MY_DISP_VER_RES 1280 /*显示屏定义的竖直方向像素个数*/

/*字符串处理相关的宏定义*/
#define DIR_MAX_LEN 64  /*目录长度*/
#define CMD_MAX_LEN 256 /*命令长度*/
#define APP_LAB_LEN 16  /*应用标签长度*/

/*程序错误代码相关的宏定义*/
#define ERR_NOT_OPEN_FIL 1 /*打开文件失败*/
#define ERR_NOT_MLC 2      /*分配内存失败*/

#define AST_DIR_NAM "assets" /*资源文件的目录名称*/

/*导出变量*/
extern char slf_dir[DIR_MAX_LEN];     /*本程序存放的目录*/
extern char fil_sys_dir[DIR_MAX_LEN]; /*LVGL驱动下的文件系统的快捷目录*/
extern char app_dir[DIR_MAX_LEN];     /*应用存放目录*/
extern char cmd_buf[CMD_MAX_LEN];     /*命令缓存*/
extern uint8_t app_cnt;               /*应用数量*/

/*导出函数*/
extern uint32_t ctm_tik_get(void); /*返回LVGL心跳间隔的时长*/

#endif /*MAIN_H*/
