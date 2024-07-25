/*Linux的头文件*/
#include    <unistd.h>
#include    <sys/time.h>
#include    <pthread.h>

/*LVGL的头文件*/
#include    "lvgl/lvgl.h"                   /*LVGL的核心*/
#include    "lvgl/porting/lv_port_disp.h"   /*LVGL的显示移植*/
#include    "lvgl/porting/lv_port_indev.h"  /*LVGL的输入移植*/
#include    "lvgl/porting/lv_port_fs.h"     /*LVGL的文件系统移植*/

/*自定义的头文件*/
#include    "gui/gui.h" /*GUI*/
#include    "main.h"    /*自定义的信息*/

/*本程序版本相关的宏定义*/
#define MAIN_VERSION_MAJOR  0
#define MAIN_VERSION_MINOR  1
#define MAIN_VERSION_PATCH  0
#define MAIN_VERSION_INFO   ""

/*全局变量*/
char    slf_dir[DIR_MAX_LEN];
char    fil_sys_dir[DIR_MAX_LEN];
char    cmd_buf[CMD_MAX_LEN];

/*局部变量*/
static  struct timeval  sta_tim;    /*计时起点*/
static  uint64_t        sta_msc;    /*计时起点毫秒数*/

uint32_t ctm_tik_get(void) {
    static struct timeval now_tim;                                          /*当前时间*/
    gettimeofday(&now_tim, NULL);                                           /*获取当前时间*/
    return (now_tim.tv_sec * 1000000 + now_tim.tv_usec) / 1000 - sta_msc;   /*返回LVGL心跳间隔的时长*/
}

static void cut_til(char* const str) {
    char* tail = &(str[strlen(str) - 1]);   /*从最后一个字符开始*/
    while('/' != *tail) *(tail--) = '\0';   /*处理后的字符串末尾为'/'字符*/
}

static void get_slf_dir(void) {
    char self_link[DIR_MAX_LEN];                                /*本程序处于运行状态时，自身在系统中的链接*/
    snprintf(self_link, sizeof(self_link), "/proc/self/exe");   /*获取本程序在系统中的链接*/
    readlink(self_link, slf_dir, sizeof(self_link));            /*从链接中获取本程序的存放路径*/
    cut_til(slf_dir);                                           /*切除路径末端的程序名得到目录*/
    LV_LOG_USER("slf_dir:%s", slf_dir);                         /*在LVGL的日志输出本程序的储存目录*/
}

static void set_fil_sys_dir(void) {
    sprintf(fil_sys_dir, "%s%s", slf_dir, "%s");    /*生成格式化命令*/
    LV_LOG_USER("fil_sys_dir:%s", fil_sys_dir);     /*在LVGL的日志输出文件系统的快捷目录*/
}

static void int_ctm_tik(void) {
    gettimeofday(&sta_tim, NULL);                                   /*获取当前时间*/
    sta_msc = (sta_tim.tv_sec * 1000000 + sta_tim.tv_usec) / 1000;  /*获取毫秒数*/
}

int main(void) {
    /**
     * 获取本程序的储存目录
     * 设置LVGL驱动下的文件系统的快捷目录
     * 初始化LVGL心跳
     * 初始化LVGL
     * 初始化显示接口
     * 初始化输入接口
     * 初始化GUI
     */
    get_slf_dir();
    set_fil_sys_dir();
    int_ctm_tik();
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    gui_int();
    
    while(true) usleep(lv_timer_handler()); /*循环处理LVGL事务*/
}
