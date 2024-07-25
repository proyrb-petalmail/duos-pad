/*自定义的头文件*/
#include    "../gui.h"  /*GUI*/
#include    "app.h"     /*自定义的信息*/

/*全局变量*/

void app_int(void) {
    lv_obj_t* tmp = lv_obj_create(gui_scr);
    lv_obj_remove_style_all(tmp);               /*清除所有样式*/
    lv_obj_set_width(tmp, MY_DISP_HOR_RES);
    lv_obj_set_height(tmp, MY_DISP_VER_RES);
    lv_obj_set_style_bg_color(tmp, lv_color_hex(0x00FFFF), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(tmp, LV_OPA_COVER, LV_STATE_DEFAULT);
    lv_obj_clear_flag(tmp, LV_OBJ_FLAG_ALL);    /*清除所有标志*/
}
