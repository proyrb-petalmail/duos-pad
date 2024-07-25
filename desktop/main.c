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
#define MAIN_VERSION_MAJOR  1
#define MAIN_VERSION_MINOR  0
#define MAIN_VERSION_PATCH  0
#define MAIN_VERSION_INFO   ""

/*应用文件读取相关的宏定义*/
#define APP_LST_FIL "app_lst.txt"   /*应用列表的文件名称*/
#define APP_CNT_FIL "app_cnt.txt"   /*应用数量的文件名称*/
#define APP_CFG_FIL "app_cfg.txt"   /*应用配置的文件名称*/

/*全局变量*/
char    slf_dir[DIR_MAX_LEN];
char    fil_sys_dir[DIR_MAX_LEN];
char    cmd_buf[CMD_MAX_LEN];
uint8_t app_cnt;

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
#if DEBUG
    LV_LOG_USER("slf_dir:%s", slf_dir);                         /*输出本程序的储存目录*/
#endif  /*DEBUG*/
}

static void set_fil_sys_dir(void) {
    sprintf(fil_sys_dir, "%s%s", slf_dir, "%s");    /*生成格式化命令*/
#if DEBUG
    LV_LOG_USER("fil_sys_dir:%s", fil_sys_dir);     /*输出文件系统的快捷目录*/
#endif  /*DEBUG*/
}

static void lod_inf(void) {
    /*读取app目录的内容并写入到APP_LST_FIL文件中*/
    char app_dir[DIR_MAX_LEN];  /*应用目录*/
    strcpy(app_dir, slf_dir);   /*复制slf_dir至app_dir*/
    strcat(app_dir, "app");     /*在app_dir末尾追加"app/"得到应用目录*/
    sprintf(cmd_buf,
        "ls -d --color=none %s/*/ > %s/%s",
        app_dir,
        app_dir,
        APP_LST_FIL);           /*生成格式化命令*/
    system("mkdir app");        /*创建app目录*/
    system(cmd_buf);            /*执行命令：读取app目录的内容并写入到APP_LST_FIL文件中*/

    /*获取应用数量并写入到APP_CNT_FIL文件中*/
    sprintf(cmd_buf,
        "wc -l %s/%s | grep -o \"^\\S\\+\" > %s/%s",
        app_dir,
        APP_LST_FIL,
        app_dir,
        APP_CNT_FIL);   /*生成格式化命令*/
    system(cmd_buf);    /*执行命令：获取应用数量并写入到APP_CNT_FIL文件中*/

    /*读取应用数量*/
    sprintf(cmd_buf,
        "%s/%s",
        app_dir,
        APP_CNT_FIL);                           /*APP_CNT_FIL文件的路径*/
    FILE* tmp_fil = fopen(cmd_buf, "r");        /*以只读方式打开文件*/
    if(NULL == tmp_fil) {
#if DEBUG
        LV_LOG_USER("cannot open %s", cmd_buf); /*输出无法打开文件的信息*/
#endif  /*DEBUG*/
        exit(ERR_NOT_OPEN_FIL);                 /*返回错误代码并退出程序*/
    }
    fscanf(tmp_fil, "%d", &app_cnt);            /*获取应用数量*/
    fclose(tmp_fil);                            /*关闭文件*/
#if DEBUG
    LV_LOG_USER("app_cnt:%d", app_cnt);         /*输出读取到的应用数量*/
#endif  /*DEBUG*/

    /*根据应用数量分配内存*/
    app_lst = (App*)malloc(app_cnt * sizeof(App));                                      /*分配与应用数量相匹配的内存大小*/
    if(NULL == app_lst) {
#if DEBUG
        LV_LOG_USER("cannot malloc %d byte in \'App\' type", app_cnt * sizeof(App));    /*输出无法分配指定大小的内存给指定的类型*/
#endif  /*DEBUG*/
        exit(ERR_NOT_MLC);                                                              /*返回错误代码并退出程序*/
    }

    /*读取应用列表中应用所在目录*/
    sprintf(cmd_buf,
            "%s/%s",
            app_dir,
            APP_LST_FIL);                                                               /*生成格式化命令*/
    tmp_fil = fopen(cmd_buf, "r");                                                      /*以只读方式打开文件*/
    if(NULL == tmp_fil) {
#if DEBUG
        LV_LOG_USER("cannot open %s", cmd_buf);                                         /*输出无法打开文件的信息*/
#endif  /*DEBUG*/
        exit(ERR_NOT_OPEN_FIL);                                                         /*返回错误代码并退出程序*/
    }
    for(uint8_t idx = 0; idx < app_cnt; idx++) {
        char red_buf[DIR_MAX_LEN] = "";
        if(EOF == fscanf(tmp_fil, "%s", red_buf)) break;                                /*逐行读取*/
        strncpy(&(app_lst[idx].dir[0]), &(red_buf[strlen(slf_dir)]), strlen(red_buf));  /*切除前面slf_dir的内容得到应用在LVGL中的相对目录*/
        sprintf(&(app_lst[idx].img[0]),
            "L:%s/%s",
            &(app_lst[idx].dir[0]),
            APP_BTN_IMG);                                                               /*生成格式化命令*/
#if DEBUG
        LV_LOG_USER("%s\b img:%s", &(app_lst[idx].dir[0]), &(app_lst[idx].img[0]));     /*输出应用准备加载的图片*/
#endif  /*DEBUG*/
    }
    fclose(tmp_fil);                                                                    /*关闭文件*/

    /*读取应用的配置信息*/
    for(int idx = 0; idx < app_cnt; idx++) {
        sprintf(cmd_buf,
                "%s/%s/%s",
                slf_dir,
                &(app_lst[idx].dir[0]),
                APP_CFG_FIL);               /*格式化生成命令*/
        tmp_fil = fopen(cmd_buf, "r");      /*打开文件*/
        if(NULL == tmp_fil) {
#if DEBUG
            LV_LOG_USER("cannot open %s", cmd_buf);     /*输出无法打开文件的信息*/
#endif  /*DEBUG*/
            exit(ERR_NOT_OPEN_FIL);                     /*返回错误代码并退出程序*/
        }
        fscanf(tmp_fil, "%s", &(app_lst[idx].nam[0]));  /*读取应用的配置信息*/
        fclose(tmp_fil);                                /*关闭文件*/
    }
}

static void int_ctm_tik(void) {
    gettimeofday(&sta_tim, NULL);                                   /*获取当前时间*/
    sta_msc = (sta_tim.tv_sec * 1000000 + sta_tim.tv_usec) / 1000;  /*获取毫秒数*/
}

int main(void) {
    /**
     * 获取本程序的储存目录
     * 设置LVGL驱动下的文件系统的快捷目录
     * 加载信息
     * 初始化LVGL心跳
     * 初始化LVGL
     * 初始化显示接口
     * 初始化输入接口
     * 初始化GUI
     */
    get_slf_dir();
    set_fil_sys_dir();
    lod_inf();
    int_ctm_tik();
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    gui_int();
    
    while(true) usleep(lv_timer_handler()); /*循环处理LVGL事务*/
}
