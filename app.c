/**
 * TOPPERS/EV3　サンプル　「黒い線に沿って進む」.
 * 動作説明　　白と黒の境界線に沿って進む。
 *           カラーセンサの出力の目標値を白と黒の中間値としている
 */

#include "ev3api.h"
#include "app.h"
#include <stdbool.h>

/**
 * ポートの接続対応
 * input
 * 1 : タッチセンサ(touch_sensor)
 * 2 : 左カラーセンサ(left_color_sensor)
 * 3 : 右カラーセンサ(right_color_sensor)
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

//メインタスク
void main_task(intptr_t unused) {
  // input
  // タッチセンサのポート情報
  ev3_sensor_config(touch_sensor, TOUCH_SENSOR);
  // 左カラーセンサのポート情報
  ev3_sensor_config(left_color_sensor, COLOR_SENSOR);
  // 右カラーセンサのポート情報
  ev3_sensor_config(right_color_sensor, COLOR_SENSOR);
  // 測距センサのポート情報
  ev3_sensor_config(distance_measuring_sensor, ULTRASONIC_SENSOR);

  // output
  // 左モータのポート情報
  ev3_motor_config(left_motor, LARGE_MOTOR);
  // 右モータのポート情報
  ev3_motor_config(right_motor, LARGE_MOTOR);
  // ビー玉用サーボモータのポート情報
  ev3_motor_config(motor_for_marble, MEDIUM_MOTOR);

  //変数宣言
  int mid_point = 50;  //明るさの目標値
  const int power = 100;      //モーターパワーj
  int steer = 0;             //ハンドル操作量

  // 目標値を決定する
  mid_point = ev3_color_sensor_get_reflect(left_color_sensor);

  //赤判定
  bool isOnRed_pre = false;
  bool isOnRed_cur = false;

  colorid_t colorid = ev3_color_sensor_get_color(right_color_sensor);
  isOnRed_cur = check_rising(colorid);
  isOnRed_pre = check_rising(colorid);

  while(1){
    //明るさ取得
    int reflect_val = ev3_color_sensor_get_reflect(left_color_sensor);
    //色取得
    colorid = ev3_color_sensor_get_color(right_color_sensor);

    if(isOnRed_cur == false){
      isOnRed_pre = isOnRed_cur;
      // 立ち上がり(チャタリング対策済み)を検知するとisOnReadにtrueを入れる．
      isOnRed_cur = check_rising(colorid);
    }else{
      isOnRed_pre = isOnRed_cur;
      // 立ち下がり(チャタリング対策済み)を検知するとisOnReadにfalseを入れる．
      isOnRed_cur = (!(check_falling(colorid)));
    }
    if(isOnRed_cur != isOnRed_pre){
      if(isOnRed_cur == True){
        // 赤のラインに通過始め
        
      }else{
        // 赤のラインに通過後

      }
    }
    //ハンドル操作量決定
    if(reflect_val > mid_point){  //目標値より白い
      steer = -50;    //左に曲がる
    }else{                        //目標値より黒い
      steer = 50;     //右に曲がる
    }

    //モータ操作量を更新
    ev3_motor_steer(left_motor, right_motor, power, steer);

    //明るさとハンドル操作量を表示
    char msg[256]= {0};
    sprintf(msg, "reflect_val:%03d steer:%03d", reflect_val, steer);
    ev3_lcd_draw_string(msg,0,20);

    tslp_tsk(1); //スリープ　10[ms]
  }

  return;
}

bool check_rising(colorid_t colorid){
  static int i = 0;
  if(colorid == COLOR_RED){
    i++;
  }else{
    i=0;
  }
  if(i >= 5){
    i = 0;
    return true;
  }else{
    return false;
  }
}
bool check_falling(colorid_t colorid){
  static int i = 0;
  if(colorid != COLOR_RED){
    i++;
  }else{
    i=0;
  }
  if(i >= 5){
    i = 0;
    return true;
  }else{
    return false;
  }
}
