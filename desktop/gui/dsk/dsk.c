/*自定义的头文件*/
#include "../scr/scr.h" /*屏幕*/
#include "../gui.h"     /*GUI*/
#include "dsk.h"        /*自定义的信息*/

/*桌面相关的宏定义*/
#define BGC_IMG "bgc.png"
#define DSK_IMG "L:" AST_DIR_NAM "/" BGC_IMG /*桌面图片*/

/*全局变量*/
lv_obj_t *gui_scr_dsk = NULL;
App *app_lst = NULL;

/*局部变量*/
static lv_style_t dsk_def_sty; /*桌面在默认状态下的样式*/

/*局部函数*/
static void dsk_sty_int(void); /*初始化样式*/

/*设置桌面的样式*/
static void dsk_sty_int(void)
{
    /*设置默认状态的样式*/
    lv_style_init(&dsk_def_sty);                         /*初始化样式*/
    lv_style_set_width(&dsk_def_sty, MY_DISP_VER_RES);   /*设置宽度*/
    lv_style_set_height(&dsk_def_sty, MY_DISP_HOR_RES);  /*设置高度*/
    lv_style_set_bg_img_src(&dsk_def_sty, DSK_IMG);      /*设置背景图片*/
    lv_style_set_bg_img_opa(&dsk_def_sty, LV_OPA_COVER); /*设置背景图片透明度*/
}

/*初始化桌面*/
void dsk_int(void)
{
    dsk_sty_int();                                   /*初始化样式*/
    gui_scr_dsk = lv_obj_create(gui_scr);            /*在屏幕上创建矩形容器*/
    lv_obj_remove_style_all(gui_scr_dsk);            /*清除所有样式*/
    lv_obj_add_style(gui_scr_dsk, &dsk_def_sty, 0);  /*为默认状态添加样式*/
    lv_obj_clear_flag(gui_scr_dsk, LV_OBJ_FLAG_ALL); /*清除所有标志*/
}
