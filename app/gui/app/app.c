/*自定义的头文件*/
#include "../gui.h" /*GUI*/
#include "app.h"    /*自定义的信息*/

/*文件相关的宏定义*/
#define EXT_BTN_ICN "ext_btn_icn.png"                            /*退出按钮的图标文件*/
#define EXT_BTN_ICN_PAT "L:" AST_DIR_NAM "/" EXT_BTN_ICN         /*退出按钮的图标文件在LVLG文件系统中的快捷路径*/
#define CNT_BTN_ICN "cnt_btn_icn.png"                            /*刷新按钮的图标文件*/
#define CNT_BTN_ICN_PAT "L:" AST_DIR_NAM "/" CNT_BTN_ICN         /*刷新按钮的图标文件在LVLG文件系统中的快捷路径*/
#define DIS_CNT_BTN_ICN "dis_cnt_btn_icn.png"                    /*刷新按钮的图标文件*/
#define DIS_CNT_BTN_ICN_PAT "L:" AST_DIR_NAM "/" DIS_CNT_BTN_ICN /*刷新按钮的图标文件在LVLG文件系统中的快捷路径*/

/*顶部横栏相关的宏定义*/
#define TOP_BAR_SIZE 100   /*尺寸*/
#define TOP_BAR_LFT_MAG 15 /*内部布局距离左侧边界的间距*/

/*退出按钮相关的宏定义*/
#define EXT_BTN_DEF_SIZ 70                        /*退出按钮的默认大小*/
#define EXT_BTN_DEF_PRE_SIZ (EXT_BTN_DEF_SIZ + 8) /*退出按钮在按压状态下的尺寸*/

/*动画相关的宏定义*/
#define EXT_BTN_DEF_TIM 300                       /*退出按钮默认状态下动画时长*/
#define EXT_BTN_DEF_PRE_TIM 200                   /*退出按钮按压状态下动画时长*/
#define EXT_BTN_DEF_ANI lv_anim_path_overshoot    /*退出按钮默认状态下的动画*/
#define EXT_BTN_DEF_PRE_ANI lv_anim_path_ease_out /*退出按钮按压状态下的动画*/

/*全局变量*/
static int wln_sta = 1;              /*WLAN状态*/
static lv_obj_t *bgc = NULL;         /*背景*/
static lv_obj_t *top_bar = NULL;     /*顶部栏*/
static lv_obj_t *ext_btn = NULL;     /*退出按钮*/
static lv_obj_t *top_bar_lab = NULL; /*应用标签*/
static lv_obj_t *cnt_btn = NULL;     /*刷新按钮*/
static lv_obj_t *wln_bar = NULL;     /*wlan状态栏*/
static lv_obj_t *wln_bar_lab = NULL; /*wlan状态栏标签*/
static lv_obj_t *wln_bar_led = NULL; /*wlan状态栏指示灯*/
static lv_obj_t *wln_nam = NULL;     /*wifi名称文本框*/
static lv_obj_t *wln_pwd = NULL;     /*wifi密码文本框*/
static lv_obj_t *key_bod = NULL;     /*键盘*/

static lv_style_t bgc_def_sty;         /*应用背景容器在默认状态下的样式*/
static lv_style_t top_bar_def_sty;     /*应用顶部栏在默认状态下的样式*/
static lv_style_t wln_bar_def_sty;     /*WLAN栏在默认状态下的样式*/
static lv_style_t wln_txt_are_def_sty; /*Wifi名称文本栏在默认状态下的样式*/
static lv_style_t wln_txt_are_foc_sty; /*Wifi名称文本栏在获焦状态下的样式*/

const static lv_style_prop_t ext_btn_def_sty_pop[] = {
    LV_STYLE_WIDTH,
    LV_STYLE_HEIGHT,
    LV_STYLE_PROP_INV};                                   /*过渡动画需要的样式属性*/
static lv_style_transition_dsc_t ext_btn_def_sty_tst_dsc; /*过渡动画解释器*/
static lv_style_t ext_btn_def_sty;                        /*退出按钮在默认状态下的样式*/

const static lv_style_prop_t ext_btn_def_pre_sty_pop[] = {
    LV_STYLE_WIDTH,
    LV_STYLE_HEIGHT,
    LV_STYLE_PROP_INV};                                       /*过渡动画需要的样式属性*/
static lv_style_transition_dsc_t ext_btn_def_pre_sty_tst_dsc; /*过渡动画解释器*/
static lv_style_t ext_btn_def_pre_sty;                        /*退出按钮在按压状态下的样式*/

const static lv_style_prop_t cnt_btn_def_sty_pop[] = {
    LV_STYLE_WIDTH,
    LV_STYLE_HEIGHT,
    LV_STYLE_PROP_INV};                                   /*过渡动画需要的样式属性*/
static lv_style_transition_dsc_t cnt_btn_def_sty_tst_dsc; /*过渡动画解释器*/
static lv_style_t cnt_btn_def_sty;                        /*刷新按钮在默认状态下的样式*/

const static lv_style_prop_t cnt_btn_def_pre_sty_pop[] = {
    LV_STYLE_WIDTH,
    LV_STYLE_HEIGHT,
    LV_STYLE_PROP_INV};                                       /*过渡动画需要的样式属性*/
static lv_style_transition_dsc_t cnt_btn_def_pre_sty_tst_dsc; /*过渡动画解释器*/
static lv_style_t cnt_btn_def_pre_sty;                        /*刷新按钮在按压状态下的样式*/

/*初始化应用*/
static void style_init(void)
{
    /*设置背景样式*/
    lv_style_set_width(&bgc_def_sty, MY_DISP_HOR_RES);           /*设置宽度*/
    lv_style_set_height(&bgc_def_sty, MY_DISP_VER_RES);          /*设置高度*/
    lv_style_set_align(&bgc_def_sty, LV_ALIGN_CENTER);           /*设置布局基准为父对象中心*/
    lv_style_set_bg_color(&bgc_def_sty, lv_color_hex(0xEEEEEE)); /*设置背景颜色*/
    lv_style_set_bg_opa(&bgc_def_sty, LV_OPA_COVER);             /*设置透明度：覆盖*/

    /*设置顶部栏样式*/
    lv_style_set_width(&top_bar_def_sty, MY_DISP_HOR_RES);                        /*设置宽度*/
    lv_style_set_height(&top_bar_def_sty, TOP_BAR_SIZE);                          /*设置高度*/
    lv_style_set_align(&top_bar_def_sty, LV_ALIGN_CENTER);                        /*设置布局基准为父对象中心*/
    lv_style_set_x(&top_bar_def_sty, 0);                                          /*设置x坐标*/
    lv_style_set_y(&top_bar_def_sty, (TOP_BAR_SIZE / 2) - (MY_DISP_VER_RES / 2)); /*设置y坐标：顶部*/
    lv_style_set_bg_color(&top_bar_def_sty, lv_color_hex(0xFFFFFF));              /*设置背景颜色*/
    lv_style_set_bg_opa(&top_bar_def_sty, LV_OPA_COVER);                          /*设置透明度：覆盖*/
    lv_style_set_shadow_width(&top_bar_def_sty, 50);                              /*设置阴影范围*/
    lv_style_set_shadow_spread(&top_bar_def_sty, -14);                            /*设置阴影传播*/

    /*设置退出按钮在默认状态下的样式*/
    lv_style_transition_dsc_init(
        &ext_btn_def_sty_tst_dsc,
        ext_btn_def_sty_pop,
        EXT_BTN_DEF_ANI,
        EXT_BTN_DEF_TIM,
        0,
        NULL);                                                                                         /*设置过渡动画解释器*/
    lv_style_init(&ext_btn_def_sty);                                                                   /*初始化样式*/
    lv_style_set_width(&ext_btn_def_sty, EXT_BTN_DEF_SIZ);                                             /*设置宽度*/
    lv_style_set_height(&ext_btn_def_sty, EXT_BTN_DEF_SIZ);                                            /*设置高度*/
    lv_style_set_align(&ext_btn_def_sty, LV_ALIGN_CENTER);                                             /*设置布局基准为父对象中心*/
    lv_style_set_x(&ext_btn_def_sty, TOP_BAR_LFT_MAG + (EXT_BTN_DEF_SIZ / 2) - (MY_DISP_HOR_RES / 2)); /*设置x坐标：左侧*/
    lv_style_set_y(&ext_btn_def_sty, 0);                                                               /*设置y坐标：居中*/
    lv_style_set_bg_color(&ext_btn_def_sty, lv_color_hex(0xFF0000));                                   /*设置背景颜色*/
    lv_style_set_bg_opa(&ext_btn_def_sty, LV_OPA_COVER);                                               /*设置透明度：覆盖*/
    lv_style_set_bg_img_src(&ext_btn_def_sty, EXT_BTN_ICN_PAT);                                        /*设置背景图片*/
    lv_style_set_bg_img_opa(&ext_btn_def_sty, LV_OPA_COVER);                                           /*设置背景图片透明度*/
    lv_style_set_radius(&ext_btn_def_sty, EXT_BTN_DEF_SIZ / 4);                                        /*设置圆角*/
    lv_style_set_shadow_width(&ext_btn_def_sty, 50);                                                   /*设置阴影范围*/
    lv_style_set_shadow_ofs_y(&ext_btn_def_sty, 8);                                                    /*设置阴影偏移*/
    lv_style_set_shadow_spread(&ext_btn_def_sty, -12);                                                 /*设置阴影传播*/
    lv_style_set_transition(&ext_btn_def_sty, &ext_btn_def_sty_tst_dsc);                               /*设置过渡动画*/

    /*设置退出按钮在按压状态下的样式*/
    lv_style_transition_dsc_init(
        &ext_btn_def_pre_sty_tst_dsc,
        ext_btn_def_pre_sty_pop,
        EXT_BTN_DEF_PRE_ANI,
        EXT_BTN_DEF_PRE_TIM,
        0,
        NULL);                                                                   /*设置过渡动画解释器*/
    lv_style_init(&ext_btn_def_pre_sty);                                         /*初始化样式*/
    lv_style_set_width(&ext_btn_def_pre_sty, EXT_BTN_DEF_PRE_SIZ);               /*设置宽度*/
    lv_style_set_height(&ext_btn_def_pre_sty, EXT_BTN_DEF_PRE_SIZ);              /*设置高度*/
    lv_style_set_transition(&ext_btn_def_pre_sty, &ext_btn_def_pre_sty_tst_dsc); /*设置过渡动画*/

    /*设置按钮在默认状态下的样式*/
    lv_style_transition_dsc_init(
        &cnt_btn_def_sty_tst_dsc,
        cnt_btn_def_sty_pop,
        EXT_BTN_DEF_ANI,
        EXT_BTN_DEF_TIM,
        0,
        NULL);                                                                                         /*设置过渡动画解释器*/
    lv_style_init(&cnt_btn_def_sty);                                                                   /*初始化样式*/
    lv_style_set_width(&cnt_btn_def_sty, EXT_BTN_DEF_SIZ);                                             /*设置宽度*/
    lv_style_set_height(&cnt_btn_def_sty, EXT_BTN_DEF_SIZ);                                            /*设置高度*/
    lv_style_set_align(&cnt_btn_def_sty, LV_ALIGN_CENTER);                                             /*设置布局基准为父对象中心*/
    lv_style_set_x(&cnt_btn_def_sty, (MY_DISP_HOR_RES / 2) - (EXT_BTN_DEF_SIZ / 2) - TOP_BAR_LFT_MAG); /*设置x坐标：左侧*/
    lv_style_set_y(&cnt_btn_def_sty, 0);                                                               /*设置y坐标：居中*/
    lv_style_set_bg_color(&cnt_btn_def_sty, lv_color_hex(0x0000FF));                                   /*设置背景颜色*/
    lv_style_set_bg_opa(&cnt_btn_def_sty, LV_OPA_COVER);                                               /*设置透明度：覆盖*/
    lv_style_set_bg_img_src(&cnt_btn_def_sty, CNT_BTN_ICN_PAT);                                        /*设置背景图片*/
    lv_style_set_bg_img_opa(&cnt_btn_def_sty, LV_OPA_COVER);                                           /*设置背景图片透明度*/
    lv_style_set_radius(&cnt_btn_def_sty, EXT_BTN_DEF_SIZ / 4);                                        /*设置圆角*/
    lv_style_set_shadow_width(&cnt_btn_def_sty, 50);                                                   /*设置阴影范围*/
    lv_style_set_shadow_ofs_y(&cnt_btn_def_sty, 8);                                                    /*设置阴影偏移*/
    lv_style_set_shadow_spread(&cnt_btn_def_sty, -12);                                                 /*设置阴影传播*/
    lv_style_set_transition(&cnt_btn_def_sty, &cnt_btn_def_sty_tst_dsc);                               /*设置过渡动画*/

    /*设置按钮在按压状态下的样式*/
    lv_style_transition_dsc_init(
        &cnt_btn_def_pre_sty_tst_dsc,
        cnt_btn_def_pre_sty_pop,
        EXT_BTN_DEF_PRE_ANI,
        EXT_BTN_DEF_PRE_TIM,
        0,
        NULL);                                                                   /*设置过渡动画解释器*/
    lv_style_init(&cnt_btn_def_pre_sty);                                         /*初始化样式*/
    lv_style_set_width(&cnt_btn_def_pre_sty, EXT_BTN_DEF_PRE_SIZ);               /*设置宽度*/
    lv_style_set_height(&cnt_btn_def_pre_sty, EXT_BTN_DEF_PRE_SIZ);              /*设置高度*/
    lv_style_set_transition(&cnt_btn_def_pre_sty, &cnt_btn_def_pre_sty_tst_dsc); /*设置过渡动画*/

    /*设置wlan的状态栏样式*/
    lv_style_set_width(&wln_bar_def_sty, MY_DISP_HOR_RES * 0.8);                                        /*设置宽度*/
    lv_style_set_height(&wln_bar_def_sty, TOP_BAR_SIZE);                                                /*设置高度*/
    lv_style_set_align(&wln_bar_def_sty, LV_ALIGN_CENTER);                                              /*设置布局基准为父对象中心*/
    lv_style_set_x(&wln_bar_def_sty, 0);                                                                /*设置x坐标*/
    lv_style_set_y(&wln_bar_def_sty, TOP_BAR_SIZE * 1.25 + (TOP_BAR_SIZE / 2) - (MY_DISP_VER_RES / 2)); /*设置y坐标：顶部*/
    lv_style_set_bg_color(&wln_bar_def_sty, lv_color_hex(0xFFFFFF));                                    /*设置背景颜色*/
    lv_style_set_bg_opa(&wln_bar_def_sty, LV_OPA_COVER);                                                /*设置透明度：覆盖*/
    lv_style_set_radius(&wln_bar_def_sty, EXT_BTN_DEF_SIZ / 4);                                         /*设置圆角*/
    lv_style_set_shadow_width(&wln_bar_def_sty, 50);                                                    /*设置阴影范围*/
    lv_style_set_shadow_spread(&wln_bar_def_sty, -14);                                                  /*设置阴影传播*/

    /*设置wifi名称文本框在默认状态下的样式*/
    lv_style_init(&wln_txt_are_def_sty);                                 /*初始化样式*/
    lv_style_set_width(&wln_txt_are_def_sty, MY_DISP_HOR_RES * 0.8);     /*设置宽度*/
    lv_style_set_height(&wln_txt_are_def_sty, TOP_BAR_SIZE);             /*设置高度*/
    lv_style_set_align(&wln_txt_are_def_sty, LV_ALIGN_CENTER);           /*设置布局基准为父对象中心*/
    lv_style_set_x(&wln_txt_are_def_sty, 0);                             /*设置x坐标：左侧*/
    lv_style_set_bg_color(&wln_txt_are_def_sty, lv_color_hex(0xFFFFFF)); /*设置背景颜色*/
    lv_style_set_bg_opa(&wln_txt_are_def_sty, LV_OPA_COVER);             /*设置透明度：覆盖*/
    lv_style_set_radius(&wln_txt_are_def_sty, EXT_BTN_DEF_SIZ / 4);      /*设置圆角*/
    lv_style_set_shadow_width(&wln_txt_are_def_sty, 50);                 /*设置阴影范围*/
    lv_style_set_shadow_spread(&wln_txt_are_def_sty, -14);               /*设置阴影传播*/
    lv_style_set_text_font(&wln_txt_are_def_sty, &lv_font_montserrat_30);
    lv_style_set_pad_top(&wln_txt_are_def_sty, 20);
    lv_style_set_pad_bottom(&wln_txt_are_def_sty, 20);
    lv_style_set_pad_left(&wln_txt_are_def_sty, 30);
    lv_style_set_pad_right(&wln_txt_are_def_sty, 30);

    /*设置wifi名称文本框在获焦状态下的样式*/
    lv_style_init(&wln_txt_are_foc_sty);                                     /*初始化样式*/
    lv_style_set_border_color(&wln_txt_are_foc_sty, lv_color_hex(0xBBBBBB)); /*设置边框颜色*/
    lv_style_set_border_opa(&wln_txt_are_foc_sty, LV_OPA_COVER);             /*设置边框透明度*/
    lv_style_set_border_width(&wln_txt_are_foc_sty, 3);                      /*设置边框宽度*/
}

/*获取当前wlan状态*/
static int get_wln_sta(void)
{
    int ret_val = 1;                                                       /*返回值*/
    char chk_std[] = "wpa_state=COMPLETED";                                /*比对标准*/
    sprintf(cmd_buf, "wpa_cli -i wlan0 status | grep -r \"%s\"", chk_std); /*生成格式化命令*/
    FILE *tmp_fil = popen(cmd_buf, "r");                                   /*打开文件*/
    if (NULL != tmp_fil)
    {
        if (NULL != fgets(cmd_buf, CMD_MAX_LEN, tmp_fil))
        {
            if (0 == memcmp(cmd_buf, chk_std, strlen(chk_std)))
                ret_val = 0; /*如果与比对标准一致则说明连接成功*/
        }
        pclose(tmp_fil); /*关闭文件*/
    }
    return ret_val;
}

/*定时器的回调函数*/
static void timer_cb(lv_timer_t *timer)
{
    wln_sta = get_wln_sta(); /*检测WLAN的网络连接状态*/
    if (0 == wln_sta)
    {
        lv_led_on(wln_bar_led);                                                       /*打开指示灯*/
        lv_obj_set_style_bg_color(cnt_btn, lv_color_hex(0xFF0000), LV_STATE_DEFAULT); /*设置背景颜色*/
        lv_obj_set_style_bg_img_src(cnt_btn, DIS_CNT_BTN_ICN_PAT, LV_STATE_DEFAULT);  /*设置背景图标*/
    }
    else
    {
        lv_led_off(wln_bar_led);                                                      /*关闭指示灯*/
        lv_obj_set_style_bg_color(cnt_btn, lv_color_hex(0x0000FF), LV_STATE_DEFAULT); /*设置背景颜色*/
        lv_obj_set_style_bg_img_src(cnt_btn, CNT_BTN_ICN_PAT, LV_STATE_DEFAULT);      /*设置背景图标*/
    }
}

/*按钮按压事件的回调函数*/
static void btn_pre_evt_cb(lv_event_t *evt)
{
    lv_obj_t *evt_app_btn = lv_event_get_target(evt); /*获取事件产生的源头组件*/
    if (ext_btn == evt_app_btn)
    {
        lv_style_transition_dsc_init(
            &ext_btn_def_sty_tst_dsc,
            ext_btn_def_sty_pop,
            EXT_BTN_DEF_ANI,
            EXT_BTN_DEF_TIM,
            0,
            NULL); /*设置过渡动画解释器*/
    }
    else if (cnt_btn == evt_app_btn)
    {
        lv_style_transition_dsc_init(
            &cnt_btn_def_sty_tst_dsc,
            cnt_btn_def_sty_pop,
            EXT_BTN_DEF_ANI,
            EXT_BTN_DEF_TIM,
            0,
            NULL); /*设置过渡动画解释器*/
    }
}

/*按钮短击事件的回调函数*/
static void btn_sht_clk_evt_cb(lv_event_t *evt)
{
    lv_obj_t *evt_app_btn = lv_event_get_target(evt); /*获取事件产生的源头组件*/
    if (ext_btn == evt_app_btn)
    {
        exit(0); /*退出程序*/
    }
    else if (cnt_btn == evt_app_btn)
    {
        if (0 == wln_sta)
        {
            system("ifconfig wlan0 down");
            system("ps | grep \"wpa_supplicant\" | awk '{print $1}' | head - n1 | xargs kill"); /*结束WLAN相关的网络进程*/
        }
        else
        {
            system("ifconfig wlan0 up");
            sprintf(cmd_buf,
                    "echo \"ctrl_interface=/var/run/wpa_supplicant\n"
                    "ap_scan=1\nupdate_config=1\nnetwork={\n"
                    "    ssid=\\\"%s\\\"\n    psk=\\\"%s\\\"\n"
                    "    key_mgmt=WPA-PSK\n}\" > /etc/wpa_supplicant.conf",
                    lv_textarea_get_text(wln_nam), lv_textarea_get_text(wln_pwd)); /*生成更新wifi配置的命令*/
            system(cmd_buf);                                                       /*执行更新wifi配置文件的命令*/
            system("wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant.conf");      /*重新运行WLAN相关的网络进程*/
        }
    }
}

/*文本框获焦事件的回调函数*/
static void txt_are_foc_evt_cb(lv_event_t *evt)
{
    lv_obj_t *evt_txt_are = lv_event_get_target(evt); /*获取事件产生的源头组件*/
    if (wln_nam == evt_txt_are)
    {
        lv_keyboard_set_textarea(key_bod, wln_nam); /*绑定文本框*/
    }
    else if (wln_pwd == evt_txt_are)
    {
        lv_keyboard_set_textarea(key_bod, wln_pwd); /*绑定文本框*/
    }
}

/*初始化应用*/
void app_int(void)
{
    /*初始化样式*/
    style_init();

    /*背景*/
    bgc = lv_obj_create(gui_scr);                          /*创建背景容器组件*/
    lv_obj_remove_style_all(bgc);                          /*清除所有样式*/
    lv_obj_add_style(bgc, &bgc_def_sty, LV_STATE_DEFAULT); /*为默认状态添加样式*/
    lv_obj_clear_flag(bgc, LV_OBJ_FLAG_ALL);               /*清除所有标志*/

    /*顶部横栏*/
    top_bar = lv_obj_create(bgc);                                  /*创建顶部栏*/
    lv_obj_remove_style_all(top_bar);                              /*清除所有样式*/
    lv_obj_add_style(top_bar, &top_bar_def_sty, LV_STATE_DEFAULT); /*为默认状态添加样式*/
    lv_obj_clear_flag(top_bar, LV_OBJ_FLAG_ALL);                   /*清除所有标志*/

    /*顶部栏左侧退出按钮*/
    ext_btn = lv_btn_create(top_bar);                                               /*创建顶部栏左侧的退出按钮*/
    lv_obj_remove_style_all(ext_btn);                                               /*清除所有样式*/
    lv_obj_add_style(ext_btn, &ext_btn_def_sty, LV_STATE_DEFAULT);                  /*为默认状态添加样式*/
    lv_obj_add_style(ext_btn, &ext_btn_def_pre_sty, LV_STATE_PRESSED);              /*为默认按压状态添加样式*/
    lv_obj_clear_flag(ext_btn, LV_OBJ_FLAG_ALL);                                    /*清除所有标志*/
    lv_obj_add_flag(ext_btn, LV_OBJ_FLAG_CLICKABLE);                                /*添加可点击标志*/
    lv_obj_add_event_cb(ext_btn, btn_pre_evt_cb, LV_EVENT_PRESSED, NULL);           /*为按压事件添加回调函数*/
    lv_obj_add_event_cb(ext_btn, btn_sht_clk_evt_cb, LV_EVENT_SHORT_CLICKED, NULL); /*为短击事件添加回调函数*/

    /*顶部栏标签*/
    top_bar_lab = lv_label_create(top_bar);                                            /*创建顶部栏左侧的退出按钮*/
    lv_label_set_text(top_bar_lab, "setup");                                           /*设置文本*/
    lv_obj_set_style_text_font(top_bar_lab, &lv_font_montserrat_40, LV_STATE_DEFAULT); /*设置字体大小*/
    lv_obj_center(top_bar_lab);                                                        /*居中*/
    lv_obj_clear_flag(top_bar_lab, LV_OBJ_FLAG_ALL);                                   /*清除所有标志*/

    /*顶部栏右侧的刷新按钮*/
    cnt_btn = lv_btn_create(top_bar);                                               /*创建顶部栏右侧的刷新按钮*/
    lv_obj_remove_style_all(cnt_btn);                                               /*清除所有样式*/
    lv_obj_add_style(cnt_btn, &cnt_btn_def_sty, LV_STATE_DEFAULT);                  /*为默认状态添加样式*/
    lv_obj_add_style(cnt_btn, &cnt_btn_def_pre_sty, LV_STATE_PRESSED);              /*为默认按压状态添加样式*/
    lv_obj_clear_flag(cnt_btn, LV_OBJ_FLAG_ALL);                                    /*清除所有标志*/
    lv_obj_add_flag(cnt_btn, LV_OBJ_FLAG_CLICKABLE);                                /*添加可点击标志*/
    lv_obj_add_event_cb(cnt_btn, btn_pre_evt_cb, LV_EVENT_PRESSED, NULL);           /*为按压事件添加回调函数*/
    lv_obj_add_event_cb(cnt_btn, btn_sht_clk_evt_cb, LV_EVENT_SHORT_CLICKED, NULL); /*为短击事件添加回调函数*/

    /*wlan的状态栏*/
    wln_bar = lv_obj_create(bgc);                                  /*创建顶部栏*/
    lv_obj_remove_style_all(wln_bar);                              /*清除所有样式*/
    lv_obj_add_style(wln_bar, &wln_bar_def_sty, LV_STATE_DEFAULT); /*为默认状态添加样式*/
    lv_obj_clear_flag(wln_bar, LV_OBJ_FLAG_ALL);                   /*清除所有标志*/

    /*wlan栏左侧标签*/
    wln_bar_lab = lv_label_create(wln_bar);                                            /*创建wln栏左侧的标签*/
    lv_label_set_text(wln_bar_lab, "WLAN Connect State");                              /*设置文本*/
    lv_obj_set_style_text_font(wln_bar_lab, &lv_font_montserrat_30, LV_STATE_DEFAULT); /*设置字体大小*/
    lv_obj_set_align(wln_bar_lab, LV_ALIGN_LEFT_MID);                                  /*居中*/
    lv_obj_set_x(wln_bar_lab, 30);                                                     /*设置相对x坐标*/
    lv_obj_clear_flag(wln_bar_lab, LV_OBJ_FLAG_ALL);                                   /*清除所有标志*/

    /*wlan栏右侧指示灯*/
    wln_bar_led = lv_led_create(wln_bar);              /*创建wln状态栏右侧的指示灯*/
    lv_obj_set_size(wln_bar_led, 50, 50);              /*设置尺寸*/
    lv_obj_set_align(wln_bar_led, LV_ALIGN_RIGHT_MID); /*居中*/
    lv_obj_set_x(wln_bar_led, -30);                    /*左侧边距*/
    lv_obj_clear_flag(wln_bar_led, LV_OBJ_FLAG_ALL);   /*清除所有标志*/

    /*Wifi名称文本框*/
    wln_nam = lv_textarea_create(bgc);                                                                               /*创建文本框*/
    lv_obj_add_style(wln_nam, &wln_txt_are_def_sty, LV_STATE_DEFAULT);                                               /*为默认状态添加样式*/
    lv_obj_set_style_y(wln_nam, TOP_BAR_SIZE * 2.34 + (TOP_BAR_SIZE / 2) - (MY_DISP_VER_RES / 2), LV_STATE_DEFAULT); /*设置y坐标*/
    lv_obj_add_style(wln_nam, &wln_txt_are_foc_sty, LV_STATE_FOCUSED);                                               /*为获焦状态添加样式*/
    lv_obj_clear_flag(wln_nam, LV_OBJ_FLAG_ALL);                                                                     /*清除所有标志*/
    lv_obj_add_flag(wln_nam,
                    LV_OBJ_FLAG_CLICKABLE |
                        LV_OBJ_FLAG_CLICK_FOCUSABLE |
                        LV_OBJ_FLAG_SCROLLABLE); /*添加可点击，可通过点击获焦，允许滚动*/
    lv_textarea_set_placeholder_text(wln_nam, "Name");
    lv_textarea_set_one_line(wln_nam, true);                                  /*设置为单行模式*/
    lv_textarea_set_cursor_click_pos(wln_nam, true);                          /*设置触摸改变光标位置*/
    lv_obj_add_event_cb(wln_nam, txt_are_foc_evt_cb, LV_EVENT_FOCUSED, NULL); /*为获焦事件添加回调函数*/

    /*Wifi密码文本框*/
    wln_pwd = lv_textarea_create(bgc);                                                                               /*创建文本框*/
    lv_obj_add_style(wln_pwd, &wln_txt_are_def_sty, LV_STATE_DEFAULT);                                               /*为默认状态添加样式*/
    lv_obj_set_style_y(wln_pwd, TOP_BAR_SIZE * 3.33 + (TOP_BAR_SIZE / 2) - (MY_DISP_VER_RES / 2), LV_STATE_DEFAULT); /*设置y坐标*/
    lv_obj_add_style(wln_pwd, &wln_txt_are_foc_sty, LV_STATE_FOCUSED);                                               /*为获焦状态添加样式*/
    lv_obj_clear_flag(wln_pwd, LV_OBJ_FLAG_ALL);                                                                     /*清除所有标志*/
    lv_obj_add_flag(wln_pwd,
                    LV_OBJ_FLAG_CLICKABLE |
                        LV_OBJ_FLAG_CLICK_FOCUSABLE |
                        LV_OBJ_FLAG_SCROLLABLE); /*添加可点击，可通过点击获焦，允许滚动*/
    lv_textarea_set_placeholder_text(wln_pwd, "Password");
    lv_textarea_set_one_line(wln_pwd, true);                                  /*设置为单行模式*/
    lv_textarea_set_cursor_click_pos(wln_pwd, true);                          /*设置触摸改变光标位置*/
    lv_obj_add_event_cb(wln_pwd, txt_are_foc_evt_cb, LV_EVENT_FOCUSED, NULL); /*为获焦事件添加回调函数*/

    /*键盘*/
    key_bod = lv_keyboard_create(bgc);                                             /*创建键盘*/
    lv_obj_set_size(key_bod, MY_DISP_HOR_RES, MY_DISP_VER_RES / 3);                /*限制尺寸*/
    lv_obj_set_style_text_font(key_bod, &lv_font_montserrat_30, LV_STATE_DEFAULT); /*设置字体大小*/
    lv_keyboard_set_popovers(key_bod, true);                                       /*允许按下按键时弹出提示*/

    /*定时检测WLAN的连接状态*/
    lv_timer_t *timer = lv_timer_create(timer_cb, 200, NULL); /*创建定时器*/
    lv_timer_set_repeat_count(timer, -1);                     /*无限重复*/
    lv_timer_ready(timer);                                    /*在下次心跳时调用*/
}
