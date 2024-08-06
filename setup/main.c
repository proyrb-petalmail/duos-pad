/*Linux的头文件*/
#include <unistd.h>
#include <sys/time.h>

/*LVGL的头文件*/
#include "lvgl/lvgl.h"                  /*LVGL的核心*/
#include "lvgl/porting/lv_port_disp.h"  /*LVGL的显示移植*/
#include "lvgl/porting/lv_port_indev.h" /*LVGL的输入移植*/
#include "lvgl/porting/lv_port_fs.h"    /*LVGL的文件系统移植*/

/*自定义的头文件*/
#include "gui/gui.h" /*GUI*/
#include "main.h"    /*自定义的信息*/

/*本程序版本相关的宏定义*/
#define MAIN_VERSION_MAJOR 0 /*主版本号*/
#define MAIN_VERSION_MINOR 3 /*次版本号*/
#define MAIN_VERSION_PATCH 0 /*补版本号*/
#define MAIN_VERSION_INFO "" /*补充信息*/

/*系统环境相关的宏定义*/
#define SYS_RUN_DIR "/proc/self/exe" /*开启自启动时的程序运行时路径*/

/*文件相关的宏定义*/

/*全局变量*/
char slf_dir[DIR_MAX_LEN] = {0};
char fil_sys_dir[DIR_MAX_LEN] = {0};
char cmd_buf[CMD_MAX_LEN] = {0};

/*局部变量*/
static struct timeval sta_tim; /*计时起点*/
static uint64_t sta_msc;       /*计时起点毫秒数*/

uint32_t ctm_tik_get(void)
{
    static struct timeval now_tim;                                        /*当前时间*/
    gettimeofday(&now_tim, NULL);                                         /*获取当前时间*/
    return (now_tim.tv_sec * 1000000 + now_tim.tv_usec) / 1000 - sta_msc; /*返回LVGL心跳间隔的时长*/
}

/*清空字符串末尾的字符，直到遇到'/'符号截至，并将该符号换位结束符*/
static void cut_til(char *const str)
{
    char *tail = &(str[strlen(str) - 1]); /*从最后一个字符开始*/
    while ('/' != *tail)
        *(tail--) = '\0'; /*处理后的字符串末尾为'/'字符*/
    *tail = '\0';         /*去除末尾的'/'字符*/
}

/*获取程序自身所在的绝对目录*/
static void get_slf_dir(void)
{
    char self_link[DIR_MAX_LEN] = {0};                   /*本程序处于运行状态时，自身在系统中的链接*/
    snprintf(self_link, sizeof(self_link), SYS_RUN_DIR); /*获取本程序在系统中的链接*/
    readlink(self_link, slf_dir, sizeof(self_link));     /*从链接中获取本程序的存放路径*/
    cut_til(slf_dir);                                    /*切除路径末端的程序名得到目录*/
#if DEBUG
    LV_LOG_USER("slf_dir:%s", slf_dir); /*输出本程序的储存目录*/
#endif
}

/*设置LVGL文件系统的快捷路径*/
static void set_fil_sys_dir(void)
{
    sprintf(fil_sys_dir, "%s/%s", slf_dir, "%s"); /*在本程序所在目录后面追加"/%s"*/
#if DEBUG
    LV_LOG_USER("fil_sys_dir:%s", fil_sys_dir); /*输出文件系统的快捷目录*/
#endif
}

/*读取应用相关的信息*/
static void lod_app(void)
{
    //     /*根据应用列表配置应用*/
    //     sprintf(cmd_buf,
    //             "%s/%s",
    //             app_dir,
    //             APP_LST_FIL);          /*生成格式化命令*/
    //     tmp_fil = fopen(cmd_buf, "r"); /*以只读方式打开文件*/
    //     if (NULL == tmp_fil)
    //     {
    // #if DEBUG
    //         LV_LOG_USER("cannot open %s", cmd_buf); /*输出无法打开文件的信息*/
    // #endif
    //         exit(ERR_NOT_OPEN_FIL); /*返回错误代码并退出程序*/
    //     }
    //     for (uint8_t idx = 0; idx < app_cnt; idx++)
    //     {
    //         char red_buf[DIR_MAX_LEN] = {0};
    //         if (EOF == fscanf(tmp_fil, "%s", red_buf))
    //             break; /*逐行读取*/
    // #if DEBUG
    //         LV_LOG_USER("fscanf[%d]:%s", idx, red_buf);
    // #endif
    //         strncpy(&(app_lst[idx].dir[0]),
    //                 &(red_buf[strlen(slf_dir) + 1]),
    //                 strlen(red_buf));        /*切除前面slf_dir的内容得到应用的相对目录*/
    //         cut_til(&(app_lst[idx].dir[0])); /*切除末尾的'/'字符*/
    //         strncpy(&(app_lst[idx].nam[0]),
    //                 &(app_lst[idx].dir[strlen(APP_DIR_NAM) + 1]),
    //                 strlen(app_lst[idx].dir)); /*切除前面的内容得到应用的目录名称*/
    //         sprintf(&(app_lst[idx].icn[0]),
    //                 "L:%s/" AST_DIR_NAM "/%s",
    //                 &(app_lst[idx].dir[0]),
    //                 APP_ICN_FIL); /*生成应用图标在LVGL中的快捷路径*/
    // #if DEBUG
    //         LV_LOG_USER("dir:%s\nnam:%s\nicn:%s",
    //                     &(app_lst[idx].dir[0]),
    //                     &(app_lst[idx].nam[0]),
    //                     &(app_lst[idx].icn[0])); /*输出应用准备加载的图片*/
    // #endif
    //     }
    //     fclose(tmp_fil); /*关闭文件*/
}

static void int_ctm_tik(void)
{
    gettimeofday(&sta_tim, NULL);                                  /*获取当前时间*/
    sta_msc = (sta_tim.tv_sec * 1000000 + sta_tim.tv_usec) / 1000; /*获取毫秒数*/
}

int main(void)
{
    get_slf_dir();        /*获取本程序的储存目录*/
    set_fil_sys_dir();    /*设置LVGL驱动下的文件系统的快捷目录*/
    lod_app();            /*加载应用信息*/
    int_ctm_tik();        /*初始化LVGL心跳*/
    lv_init();            /*初始化LVGL库*/
    lv_port_disp_init();  /*初始化显示接口*/
    lv_port_indev_init(); /*初始化输入接口*/
    gui_int();            /*初始化GUI*/

    while (true)
        usleep(lv_timer_handler()); /*循环处理LVGL事务*/
}
