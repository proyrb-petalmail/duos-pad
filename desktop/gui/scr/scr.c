/*自定义的头文件*/
#include    "../gui.h"  /*GUI*/
#include    "scr.h"     /*自定义的信息*/

/*全局变量*/
lv_obj_t*   gui_scr     =   NULL;

void scr_int(void) {
    /*初始化屏幕*/
    gui_scr = lv_scr_act();                         /*获取当前活动的屏幕*/
    lv_obj_remove_style_all(gui_scr);               /*清除所有样式*/
    lv_obj_clear_flag(gui_scr, LV_OBJ_FLAG_ALL);    /*清除所有标志*/
}
