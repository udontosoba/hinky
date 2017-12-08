/* z_20_4_set_state.c */
#include "ev3api.h"
#include "z_10_common.h"
#include "z_20_4_set_state.h"
#include "z_00_2_state.h"


int battery = 0;
static char battery_char[] = {'0', ':', '0', '0', ':', '0', '0' };

cource_t cource;



State func_z_20_4_set_state_main(void){
    const cource_t * cource_lo;
    //電池残量
    battery = ev3_battery_voltage_mV ( );
    format_battery();
    ev3_lcd_draw_string (battery_char,0,10);
    //PID値
    if (ev3_button_is_pressed(0)==false){//左ボタンでスキップ出来る
        //設定にはいります

    }

    //リスタート処理
    cource_lo = func_z_10_common_fetch_cource();
    //func_z_10_common_set_cource(&cource_lo cource_hoge);


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
