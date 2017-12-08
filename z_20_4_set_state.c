/* z_20_4_set_state.c */
#include "ev3api.h"
#include "z_10_common.h"
#include "z_20_4_set_state.h"
#include "z_00_2_state.h"
#include "ev3api.h"
#include "app.h"
#include <stdbool.h>

int battery = 0;
static char battery_char[] = {'0', ':', '0', '0', ':', '0', '0' };
pid_para_t * pid_lo;
cource_t cource;

State func_z_20_4_set_state_main(void){
    const cource_t * cource_lo;
    //電池残量
    battery = ev3_battery_voltage_mV ( );
    format_battery();
    ev3_lcd_draw_string (battery_char,0,10);
    //PID値
    //設定にはいります。現在のPIDを取得して表示
    pid_lo = func_z_10_common_fetch_pid_para();
    static int keta = 2;
    //こっから表示
    char msg[256]= {0};
    sprintf(msg, "P:%lf I:%lf D:%lf", pid_lo->p.integrated_value,pid_lo->i.integrated_value,pid_lo->d.integrated_value);
    ev3_lcd_draw_string(msg,0,20);
    //PIDの値を変更
    sprintf(msg, "cancel←、P↑、I→、D↓");
    ev3_lcd_draw_string(msg,1,20);
    //ボタン処理
    if (ev3_button_is_pressed(0)==true){
    }else if(ev3_button_is_pressed(2)==true){//ue
        func_z_10_common_increment_num_in_value(&(pid_lo->p), keta);
    }else if(ev3_button_is_pressed(1)==true){//yoko
        func_z_10_common_increment_num_in_value(&(pid_lo->i), keta);
    }else if(ev3_button_is_pressed(3)==true){//sita
        func_z_10_common_increment_num_in_value(&(pid_lo->i), keta);
    }

    //リスタート処理
    cource_lo = func_z_10_common_fetch_cource();//今のコースの位置の値を取る

    State next_state = init_state;
    return next_state;
}


void format_battery(void){
    itoa(battery, &battery_char[0], 1, ' '); //ひとけた
    battery_char[1] = ':';
    itoa(battery, &battery_char[2], 2, '0'); // 二桁
    battery_char[4] = ':';
    itoa(battery, &battery_char[5], 2, '0'); // 三けた
    return;
}
