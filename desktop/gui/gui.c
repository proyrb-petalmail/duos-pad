/*自定义的头文件*/
#include "gui.h" /*自定义的信息*/

void gui_int(void)
{
    scr_int();                 /*初始化屏幕*/
    dsk_int();                 /*初始化桌面*/
    app_int(app_lst, app_cnt); /*初始化应用按钮*/
}
