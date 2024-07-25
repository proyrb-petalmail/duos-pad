/*自定义的头文件*/
#include    "../dsk/dsk.h"  /*桌面*/
#include    "../gui.h"      /*GUI*/
#include    "app.h"         /*自定义的信息*/

/*LVGL对象状态相关的宏定义*/
#define LV_STATE_OPENED LV_STATE_USER_1 /*处于打开状态*/

/*应用按钮属性相关的宏定义*/
#define APP_BTN_DEF_SIZ     100                     /*应用按钮在默认状态下的尺寸*/
#define APP_BTN_DEF_PRE_SIZ (APP_BTN_DEF_SIZ + 8)   /*应用按钮在默认按压状态下的尺寸*/
#define APP_BTN_DEF_PRE_OFY 8                       /*应用按钮在默认按压状态下的Y坐标偏移量*/
#define APP_BTN_MIN_SIZ     96                      /*应用按钮最小的尺寸*/

/*过渡动画相关的宏定义*/
#define APP_DEF_TIM         300                     /*应用默认状态下动画时长*/
#define APP_DEF_PRE_TIM     200                     /*应用默认按压状态下动画时长*/
#define APP_OPN_TIM         400                     /*应用打开状态下动画时长*/
#define APP_CLS_TIM         800                     /*应用关闭状态下动画时长*/
#define APP_BTN_DEF_ANI     lv_anim_path_overshoot  /*应用按钮默认状态下的动画*/
#define APP_BTN_DEF_PRE_ANI lv_anim_path_ease_out   /*应用按钮默认按压状态下的动画*/
#define APP_BTN_DEF_OPN_ANI lv_anim_path_ease_out   /*应用按钮打开状态下的动画*/
#define APP_BTN_CLS_DEF_ANI lv_anim_path_overshoot  /*应用按钮关闭状态下的动画*/
#define APP_LAB_DEF_ANI     lv_anim_path_ease_out   /*应用标签默认状态下的动画*/
#define APP_LAB_DEF_PRE_ANI lv_anim_path_ease_out   /*应用标签默认按压状态下的动画*/
#define APP_LAB_DEF_OPN_ANI lv_anim_path_ease_out   /*应用标签打开状态下的动画*/
#define APP_LAB_CLS_DEF_ANI lv_anim_path_ease_out   /*应用标签关闭状态下的动画*/

/*局部变量*/
const static    lv_style_prop_t             app_btn_def_sty_pop[] = {
                                                LV_STYLE_WIDTH,
                                                LV_STYLE_MIN_WIDTH,
                                                LV_STYLE_HEIGHT,
                                                LV_STYLE_MIN_HEIGHT,
                                                LV_STYLE_X,
                                                LV_STYLE_Y,
                                                LV_STYLE_RADIUS,
                                                LV_STYLE_TRANSLATE_Y,
                                                LV_STYLE_PROP_INV};         /*过渡动画需要的样式属性*/
static          lv_style_transition_dsc_t   app_btn_def_sty_tst_dsc;        /*过渡动画解释器*/
static          lv_style_t                  app_btn_def_sty;                /*应用按钮在默认状态下的样式*/

const static    lv_style_prop_t             app_btn_def_pre_sty_pop[] = {
                                                LV_STYLE_WIDTH,
                                                LV_STYLE_HEIGHT,
                                                LV_STYLE_TRANSLATE_Y,
                                                LV_STYLE_PROP_INV};         /*过渡动画需要的样式属性*/
static          lv_style_transition_dsc_t   app_btn_def_pre_sty_tst_dsc;    /*过渡动画解释器*/
static          lv_style_t                  app_btn_def_pre_sty;            /*应用按钮在默认按压状态下的样式*/

const static    lv_style_prop_t             app_btn_opn_sty_pop[] = {
                                                LV_STYLE_WIDTH,
                                                LV_STYLE_HEIGHT,
                                                LV_STYLE_X,
                                                LV_STYLE_Y,
                                                LV_STYLE_RADIUS,
                                                LV_STYLE_PROP_INV};         /*过渡动画需要的样式属性*/
static          lv_style_transition_dsc_t   app_btn_opn_sty_tst_dsc;        /*过渡动画解释器*/
static          lv_style_t                  app_btn_opn_sty;                /*应用按钮在打开状态下的样式*/

const static    lv_style_prop_t             app_lab_def_sty_pop[] = {
                                                LV_STYLE_TEXT_OPA,
                                                LV_STYLE_TEXT_LETTER_SPACE,
                                                LV_STYLE_TRANSLATE_Y,
                                                LV_STYLE_PROP_INV};         /*过渡动画需要的样式属性*/
static          lv_style_transition_dsc_t   app_lab_def_sty_tst_dsc;        /*过渡动画解释器*/
static          lv_style_t                  app_lab_def_sty;                /*应用按钮在默认状态下的样式*/

const static    lv_style_prop_t             app_lab_def_pre_sty_pop[] = {
                                                LV_STYLE_TEXT_LETTER_SPACE,
                                                LV_STYLE_PROP_INV};         /*过渡动画需要的样式属性*/
static          lv_style_transition_dsc_t   app_lab_def_pre_sty_tst_dsc;    /*过渡动画解释器*/
static          lv_style_t                  app_lab_def_pre_sty;            /*应用按钮在默认按压状态下的样式*/

const static    lv_style_prop_t             app_lab_opn_sty_pop[] = {
                                                LV_STYLE_TEXT_OPA,
                                                LV_STYLE_TRANSLATE_Y,
                                                LV_STYLE_PROP_INV};         /*过渡动画需要的样式属性*/
static          lv_style_transition_dsc_t   app_lab_opn_sty_tst_dsc;        /*过渡动画解释器*/
static          lv_style_t                  app_lab_opn_sty;                /*应用按钮在打开状态下的样式*/

/*局部函数*/
static void app_btn_sty_int(void) {
    /*设置应用按钮在默认状态下的样式*/
    lv_style_transition_dsc_init(
        &app_btn_def_sty_tst_dsc,
        app_btn_def_sty_pop,
        APP_BTN_DEF_ANI,
        APP_DEF_TIM,
        0,
        NULL);                                                              /*设置过渡动画解释器*/
    lv_style_init(&app_btn_def_sty);                                        /*初始化样式*/
    lv_style_set_width(&app_btn_def_sty, APP_BTN_DEF_SIZ);                  /*设置宽度*/
    lv_style_set_min_width(&app_btn_def_sty, APP_BTN_MIN_SIZ);              /*设置最小宽度*/
    lv_style_set_height(&app_btn_def_sty, APP_BTN_DEF_SIZ);                 /*设置高度*/
    lv_style_set_min_height(&app_btn_def_sty, APP_BTN_MIN_SIZ);             /*设置最小高度*/
    lv_style_set_align(&app_btn_def_sty, LV_ALIGN_CENTER);                  /*设置布局基准为父对象中心*/
    lv_style_set_bg_color(&app_btn_def_sty, lv_color_hex(0xFFFFFF));        /*设置背景颜色*/
    lv_style_set_bg_opa(&app_btn_def_sty, LV_OPA_COVER);                    /*设置背景透明度*/
    lv_style_set_radius(&app_btn_def_sty, 30);                              /*设置圆角*/
    lv_style_set_shadow_width(&app_btn_def_sty, 100);                       /*设置阴影范围*/
    lv_style_set_shadow_ofs_y(&app_btn_def_sty, APP_BTN_DEF_PRE_OFY * 2);   /*设置阴影偏移*/
    lv_style_set_shadow_spread(&app_btn_def_sty, -20);                      /*设置阴影传播*/
    lv_style_set_transition(&app_btn_def_sty, &app_btn_def_sty_tst_dsc);    /*设置过渡动画*/
    
    /*设置应用按钮在默认按压状态下的样式*/
    lv_style_transition_dsc_init(
        &app_btn_def_pre_sty_tst_dsc,
        app_btn_def_pre_sty_pop,
        APP_BTN_DEF_PRE_ANI,
        APP_DEF_PRE_TIM,
        0,
        NULL);                                                                      /*设置过渡动画解释器*/
    lv_style_init(&app_btn_def_pre_sty);                                            /*初始化样式*/
    lv_style_set_width(&app_btn_def_pre_sty, APP_BTN_DEF_PRE_SIZ);                  /*设置宽度*/
    lv_style_set_height(&app_btn_def_pre_sty, APP_BTN_DEF_PRE_SIZ);                 /*设置高度*/
    lv_style_set_translate_y(&app_btn_def_pre_sty, -APP_BTN_DEF_PRE_OFY);           /*设置Y坐标偏移量*/
    lv_style_set_transition(&app_btn_def_pre_sty, &app_btn_def_pre_sty_tst_dsc);    /*设置过渡动画*/
    
    /*设置应用按钮在打开状态下的样式*/
    lv_style_transition_dsc_init(
        &app_btn_opn_sty_tst_dsc,
        app_btn_opn_sty_pop,
        APP_BTN_DEF_OPN_ANI,
        APP_OPN_TIM,
        0,
        NULL);                                                              /*设置过渡动画解释器*/
    lv_style_init(&app_btn_opn_sty);                                        /*初始化样式*/
    lv_style_set_width(&app_btn_opn_sty, MY_DISP_VER_RES);                  /*设置宽度*/
    lv_style_set_height(&app_btn_opn_sty, MY_DISP_HOR_RES);                 /*设置高度*/
    lv_style_set_x(&app_btn_opn_sty, 0);                                    /*设置X坐标*/
    lv_style_set_y(&app_btn_opn_sty, 0);                                    /*设置Y坐标*/
    lv_style_set_radius(&app_btn_opn_sty, 0);                               /*设置圆角*/
    lv_style_set_transition(&app_btn_opn_sty, &app_btn_opn_sty_tst_dsc);    /*设置过渡动画*/

    /*设置应用标签在默认状态下的样式*/
    lv_style_transition_dsc_init(
        &app_lab_def_sty_tst_dsc,
        app_lab_def_sty_pop,
        APP_LAB_DEF_ANI,
        APP_DEF_TIM,
        0,
        NULL);                                                              /*设置过渡动画解释器*/
    lv_style_init(&app_lab_def_sty);                                        /*初始化样式*/
    lv_style_set_align(&app_lab_def_sty, LV_ALIGN_BOTTOM_MID);              /*设置布局基准为父对象中心*/
    lv_style_set_text_color(&app_lab_def_sty, lv_color_hex(0xFFFFFF));      /*设置文本颜色*/
    lv_style_set_text_opa(&app_lab_def_sty, LV_OPA_COVER);                  /*设置文本透明度*/
    lv_style_set_text_font(&app_lab_def_sty, &lv_font_montserrat_24);       /*设置字体大小*/
    lv_style_set_text_letter_space(&app_lab_def_sty, 0);                    /*设置字体间距*/
    lv_style_set_y(&app_lab_def_sty, 30);                                   /*设置Y坐标*/
    lv_style_set_transition(&app_lab_def_sty, &app_lab_def_sty_tst_dsc);    /*设置过渡动画*/
    
    /*设置应用标签在默认按压状态下的样式*/
    lv_style_transition_dsc_init(
        &app_lab_def_pre_sty_tst_dsc,
        app_lab_def_pre_sty_pop,
        APP_LAB_DEF_PRE_ANI,
        APP_DEF_PRE_TIM,
        0,
        NULL);                                                                      /*设置过渡动画解释器*/
    lv_style_init(&app_lab_def_pre_sty);                                            /*初始化样式*/
    lv_style_set_text_letter_space(&app_lab_def_pre_sty, 3);                        /*设置字体间距*/
    lv_style_set_transition(&app_lab_def_pre_sty, &app_lab_def_pre_sty_tst_dsc);    /*设置过渡动画*/
    
    /*设置应用标签在打开状态下的样式*/
    lv_style_transition_dsc_init(
        &app_lab_opn_sty_tst_dsc,
        app_lab_opn_sty_pop,
        APP_LAB_DEF_OPN_ANI,
        APP_OPN_TIM,
        0,
        NULL);                                                              /*设置过渡动画解释器*/
    lv_style_init(&app_lab_opn_sty);                                        /*初始化样式*/
    lv_style_set_translate_y(&app_lab_opn_sty, -30);                        /*设置Y坐标偏移量*/
    lv_style_set_text_opa(&app_lab_opn_sty, 0);                             /*设置文本透明度*/
    lv_style_set_transition(&app_lab_opn_sty, &app_lab_opn_sty_tst_dsc);    /*设置过渡动画*/
}

static void app_btn_cal(lv_timer_t* timer) {
    lv_obj_t* btn = (lv_obj_t*)(timer->user_data);      /*获取应用按钮对象*/
    if(NULL != btn) {
        lv_state_t btn_state = lv_obj_get_state(btn);   /*获取应用按钮的状态*/
        if(MY_DISP_VER_RES == lv_obj_get_width(btn) && MY_DISP_HOR_RES == lv_obj_get_height(btn)) {
            LV_LOG_USER("ok");
        }
    }
}

static void app_btn_pre_evt_cb(lv_event_t* evt) {
    lv_obj_t* evt_app_btn = lv_event_get_target(evt);
    lv_obj_t* evt_app_lab = lv_obj_get_child(evt_app_btn, 0);
    lv_obj_add_state(evt_app_lab, LV_STATE_PRESSED);
    lv_style_transition_dsc_init(
        &app_btn_def_sty_tst_dsc,
        app_btn_def_sty_pop,
        APP_BTN_DEF_ANI,
        APP_DEF_TIM,
        0,
        NULL);                      /*设置过渡动画解释器*/
    lv_style_transition_dsc_init(
        &app_lab_def_sty_tst_dsc,
        app_lab_def_sty_pop,
        APP_LAB_DEF_ANI,
        APP_DEF_TIM,
        0,
        NULL);                      /*设置过渡动画解释器*/
}

static void app_btn_pre_los_evt_cb(lv_event_t* evt) {
    lv_obj_t* evt_app_btn = lv_event_get_target(evt);
    lv_obj_t* evt_app_lab = lv_obj_get_child(evt_app_btn, 0);
    lv_obj_clear_state(evt_app_lab, LV_STATE_PRESSED);      /*为应用标签清除按压状态*/
}

static void app_btn_sht_clk_evt_cb(lv_event_t* evt) {
    lv_obj_t* evt_app_btn = lv_event_get_target(evt);
    lv_obj_t* evt_app_lab = lv_obj_get_child(evt_app_btn, 0);
    static bool app_state = false;                                                  /*应用的打开状态*/
    app_state = (app_state) ? false : true;                                         /*响应电机事件来改变应用状态*/
    if(app_state) {
        lv_style_transition_dsc_init(
            &app_btn_opn_sty_tst_dsc,
            app_btn_opn_sty_pop,
            APP_BTN_DEF_OPN_ANI,                                                    /*应用按钮从默认状态到打开状态的动画函数*/
            APP_OPN_TIM,                                                            /*应用打开动画时长*/
            0,                                                                      /*没有延时直接加载*/
            NULL);                                                                  /*设置过渡动画解释器*/
        lv_style_transition_dsc_init(
            &app_lab_def_sty_tst_dsc,
            app_lab_def_sty_pop,
            APP_LAB_DEF_OPN_ANI,                                                    /*应用标签从默认状态到打开状态的动画函数*/
            APP_OPN_TIM,                                                            /*应用打开动画时长*/
            0,                                                                      /*没有延时直接加载*/
            NULL);                                                                  /*设置过渡动画解释器*/
        lv_obj_move_foreground(evt_app_btn);                                        /*将应用至于前景*/
        lv_obj_add_state(evt_app_btn, LV_STATE_OPENED);                             /*为应用按钮添加打开状态*/
        lv_obj_add_state(evt_app_lab, LV_STATE_OPENED);                             /*为应用标签添加打开状态*/
    }
    else {
        lv_style_transition_dsc_init(
            &app_btn_def_sty_tst_dsc,
            app_btn_def_sty_pop,
            APP_BTN_CLS_DEF_ANI,                                /*应用按钮从关闭状态到默认状态的动画函数*/
            APP_CLS_TIM,                                        /*应用关闭动画时长*/
            0,                                                  /*没有延时直接加载*/
            NULL);                                              /*设置过渡动画解释器*/
        lv_style_transition_dsc_init(
            &app_lab_def_sty_tst_dsc,
            app_lab_def_sty_pop,
            APP_LAB_CLS_DEF_ANI,                                /*应用按钮从关闭状态到默认状态的动画函数*/
            APP_CLS_TIM,                                        /*应用关闭动画时长*/
            0,                                                  /*没有延时直接加载*/
            NULL);                                              /*设置过渡动画解释器*/
        lv_obj_clear_state(evt_app_btn, LV_STATE_OPENED);       /*清除应用按钮的打开状态*/
        lv_obj_clear_state(evt_app_lab, LV_STATE_OPENED);       /*清除应用标签的打开状态*/
    }
}

static void app_btn_rel_evt_cb(lv_event_t* evt) {
    lv_obj_t* evt_app_btn = lv_event_get_target(evt);
    lv_obj_t* evt_app_lab = lv_obj_get_child(evt_app_btn, 0);
    lv_obj_clear_state(evt_app_lab, LV_STATE_PRESSED);          /*为应用标签清除按压状态*/
}

static void app_btn_siz_evt_cb(lv_event_t* evt) {
    lv_obj_t* evt_app_btn = lv_event_get_target(evt);
    lv_state_t btn_state = lv_obj_get_state(evt_app_btn);       /*获取应用按钮的状态*/
    if(MY_DISP_VER_RES == lv_obj_get_width(evt_app_btn)) {
        LV_LOG_USER("dir:%s", (char *)evt->user_data);
    }
}

static int32_t get_app_rlt_x(uint8_t idx) {
    float col_idx = idx % DSK_COL; /*列坐标*/
    if(0 == DSK_COL % 2) {
        float col_mid = ((float)DSK_COL + 1.0f) / 2.0f; /*列坐标中轴线*/
        return (col_idx + 1.0 - col_mid) * DSK_HOR_PAD;
    }
    else {
        float col_mid = (float)DSK_COL / 2.0;           /*列坐标中轴线*/
        return (col_idx + 0.5 - col_mid) * DSK_HOR_PAD;
    }
}

static int32_t get_app_rlt_y(uint8_t idx) {
    float row_idx = idx / DSK_COL; /*横坐标*/
    if(0 == DSK_ROW % 2) {
        float row_mid = ((float)DSK_ROW + 1.0f) / 2.0f; /*横坐标中轴线*/
        return (row_idx + 1.0 - row_mid + 1) * DSK_VER_PAD;
    }
    else {
        float row_mid = (float)DSK_ROW / 2.0;           /*横坐标中轴线*/
        return (row_idx + 0.5 - row_mid) * DSK_VER_PAD;
    }
}

void app_int(App* lst, uint8_t cnt) {
    /*为应用列表中的应用逐个创建应用对象并初始化*/
    app_btn_sty_int();                                                                          /*初始化样式*/
    lv_obj_t* tmp_obj = NULL;
    for(uint8_t idx = 0; idx < cnt; idx++) {
        tmp_obj = lv_obj_create(gui_scr_dsk);                                                   /*在桌面上创建应用按钮*/
        lv_obj_remove_style_all(tmp_obj);                                                       /*清除所有样式*/
        lv_obj_add_style(tmp_obj, &app_btn_def_sty, LV_STATE_DEFAULT);                          /*为默认状态添加样式*/
        lv_obj_set_style_x(tmp_obj, get_app_rlt_x(idx), LV_STATE_DEFAULT);                      /*设置X轴相对坐标*/
        lv_obj_set_style_y(tmp_obj, get_app_rlt_y(idx), LV_STATE_DEFAULT);                      /*设置Y轴相对坐标*/
        lv_obj_set_style_bg_img_src(tmp_obj, &lst[idx].img[0], LV_STATE_DEFAULT);               /*设置背景图片*/
        lv_obj_set_style_bg_img_opa(tmp_obj, LV_OPA_COVER, LV_STATE_DEFAULT);                   /*设置背景图片透明度*/
        lv_obj_add_style(tmp_obj, &app_btn_def_pre_sty, LV_STATE_PRESSED);                      /*为默认按压状态添加样式*/
        lv_obj_add_style(tmp_obj, &app_btn_opn_sty, LV_STATE_OPENED);                           /*为打开状态添加样式*/
        lv_obj_clear_flag(tmp_obj, LV_OBJ_FLAG_ALL);                                            /*清除所有标志*/
        lv_obj_add_flag(
            tmp_obj,
            LV_OBJ_FLAG_CLICKABLE |                                                             /*允许点击*/
            LV_OBJ_FLAG_OVERFLOW_VISIBLE);                                                      /*允许绘制子组件超出的部分*/
        lv_obj_add_event_cb(tmp_obj, app_btn_pre_evt_cb, LV_EVENT_PRESSED, NULL);               /*为按压事件添加回调函数*/
        lv_obj_add_event_cb(tmp_obj, app_btn_pre_los_evt_cb, LV_EVENT_PRESS_LOST, NULL);        /*为失压事件添加回调函数*/
        lv_obj_add_event_cb(tmp_obj, app_btn_sht_clk_evt_cb, LV_EVENT_SHORT_CLICKED, NULL);     /*为短击事件添加回调函数*/
        lv_obj_add_event_cb(tmp_obj, app_btn_rel_evt_cb, LV_EVENT_RELEASED, NULL);              /*为释放事件添加回调函数*/
        lv_obj_add_event_cb(tmp_obj, app_btn_siz_evt_cb, LV_EVENT_SIZE_CHANGED, lst[idx].dir);  /*为缩放事件添加回调函数*/
        lst[idx].obj = tmp_obj;                                                                 /*记录新建的应用对象*/
        tmp_obj = lv_label_create(tmp_obj);                                                     /*在应用按钮上创建标签*/
        lv_obj_remove_style_all(tmp_obj);                                                       /*清除所有样式*/
        lv_obj_add_style(tmp_obj, &app_lab_def_sty, LV_STATE_DEFAULT);                          /*为默认状态添加样式*/
        lv_obj_add_style(tmp_obj, &app_lab_def_pre_sty, LV_STATE_PRESSED);                      /*为默认按压状态添加样式*/
        lv_obj_add_style(tmp_obj, &app_lab_opn_sty, LV_STATE_OPENED);                           /*为打开状态添加样式*/
        lv_obj_clear_flag(tmp_obj, LV_OBJ_FLAG_ALL);                                            /*清除所有标志*/
        lv_label_set_text(tmp_obj, &(lst[idx].nam[0]));                                         /*设置应用标签*/
    }
}
