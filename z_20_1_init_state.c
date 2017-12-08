/* z_20_1_init_state.c */
#include "z_20_1_init_state.h"
#include "z_00_2_state.h"       //state情報が書かれてある
#include "z_00_1_io_setting.h"
#include "ev3api.h"             // EV3_PORT_hogeの定義が書かれてある．
#include "z_10_common.h"
#include <stdbool.h>

State func_z_20_1_init_state_main(void)
{
    /**
     * ポートの接続対応
     * input
     * 1 : タッチセンサ(touch_sensor)
     * 2 : 左カラーセfunc_z_20_1_init_state_mainンサ for 白黒判別 (left_color_sensor)
     * 3 : 右カラーセンサ for 赤判別(right_color_sensor)
     * 4 : 測距センサ(distance_measuring_sensor)
     * output
     * A :
     * B : 左車輪モータ(left_motor)
     * C : 右車輪モータ(right_motor)
     * D : ビー玉用サーボモータ(motor_for_marble)
     */
    
    // input
    const int touch_sensor = EV3_PORT_1;
    const int left_color_sensor = EV3_PORT_2;
    const int right_color_sensor = EV3_PORT_3;
    const int distance_measuring_sensor = EV3_PORT_4;
    
    // output
    const int left_motor = EV3_PORT_B;
    const int right_motor = EV3_PORT_C;
    const int motor_for_marble = EV3_PORT_D;
    
    //センサーポートを設定
    ev3_sensor_config(touch_sensor, TOUCH_SENSOR);
    ev3_sensor_config(left_color_sensor, COLOR_SENSOR);
    ev3_sensor_config(right_color_sensor, COLOR_SENSOR);
    ev3_sensor_config(distance_measuring_sensor, ULTRASONIC_SENSOR);
    
    //モーターポートを設定
    ev3_motor_config(left_motor, LARGE_MOTOR);
    ev3_motor_config(right_motor, LARGE_MOTOR);
    ev3_motor_config(motor_for_marble, LARGE_MOTOR);
    
    //
    char put_on_color[30];
    char ave_color[10];
    
    //ENTER_BUTTONの状態を保管する変数
    bool ENTER_BUTTON_State_Old = false ;
    bool ENTER_BUTTON_State_Now = ev3_button_is_pressed (ENTER_BUTTON) ;
    
    //ENTER牡丹を押すまで
    while (ENTER_BUTTON_State_Old = ENTER_BUTTON_State_Now)
        //黒の上に置けと表示
    {
        sprintf(put_on_color, "PUT ON BLACK, PUSH ENTER");
        ev3_lcd_draw_string (put_on_color, 0, 10);
        ENTER_BUTTON_State_Old = ENTER_BUTTON_State_Now;
        ENTER_BUTTON_State_Now = ev3_button_is_pressed (ENTER_BUTTON);
    }
    //LCDをクリア
    sprintf(put_on_color, "                        ");
    ev3_lcd_draw_string (put_on_color, 0, 10);
    
    //0.01秒ごとに黒の数値を取得し1秒間待つ(100個値を取る)
    int black_value[100] = {0} ;
    int timer_counter ;
    int sum_black = 0;
    int ave_black = 0;
    for (timer_counter = 0; timer_counter < 100;)
    {    black_value[timer_counter] = ev3_color_sensor_get_reflect(left_color_sensor);
        sum_black += black_value[timer_counter];
        func_z_10_common_increment_timer_counter();
    }
    ave_black = sum_black / 100;
    //平均値を黒色のキャリブ情報として格納する
    func_z_10_common_set_calib_black(0, 0, ave_black);
    
    //10個の値の平均を黒の代表値とし、1秒表示する。
    for (timer_counter = 0; timer_counter < 100;)
    {
        sprintf(ave_color, "%d",ave_black);
        ev3_lcd_draw_string (ave_color, 0, 10);
        func_z_10_common_increment_timer_counter();
    }
    
    //LCDをクリア
    sprintf(put_on_color, "                        ");
    ev3_lcd_draw_string (put_on_color, 0, 10);
    
    //ENTER_BUTTONの状態をクリア
    ENTER_BUTTON_State_Old = false ;
    ENTER_BUTTON_State_Now = ev3_button_is_pressed (ENTER_BUTTON) ;
    
    //ENTER牡丹を押すまで
    while (ENTER_BUTTON_State_Old = ENTER_BUTTON_State_Now)
        //白の上に置けと表示
    {
        sprintf(put_on_color, "PUT ON WHITE, PUSH ENTER");
        ev3_lcd_draw_string (put_on_color, 0, 10); //白の上に置けと表示
        ENTER_BUTTON_State_Old = ENTER_BUTTON_State_Now;
        ENTER_BUTTON_State_Now = ev3_button_is_pressed (ENTER_BUTTON);
    }
    //LCDをクリア
    sprintf(put_on_color, "                        ");
    ev3_lcd_draw_string (put_on_color, 0, 10);
    
    //0.01秒ごとに白の数値を取得しの1秒間待つ(100個値を取る)
    int white_value[100] = {0} ;
    int sum_white = 0;
    int ave_white = 0;
    for (timer_counter = 0; timer_counter < 100;)
    {    white_value[timer_counter] = ev3_color_sensor_get_reflect(left_color_sensor);
        sum_white += white_value[timer_counter];
        func_z_10_common_increment_timer_counter();
    }
    ave_white = sum_white / 100;
    
    //平均値を白色のキャリブ情報として格納する
    func_z_10_common_set_calib_white(0, 0, ave_white);
    
    //10個の値の平均を白の代表値とし、1秒表示する。
    for (timer_counter = 0; timer_counter < 100;)
    {
        sprintf(ave_color, "%d",ave_white);
        ev3_lcd_draw_string (ave_color, 0, 10);
        func_z_10_common_increment_timer_counter();
    }
    
    //LCDをクリア
    sprintf(put_on_color, "                        ");
    ev3_lcd_draw_string (put_on_color, 0, 10);
    
    return stop_state ;
}




