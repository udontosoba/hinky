/**
 * TOPPERS/EV3　サンプル　「黒い線に沿って進む」.
 * 動作説明　　白と黒の境界線に沿って進む。
 *           カラーセンサの出力の目標値を白と黒の中間値としている  
 */

#include "ev3api.h"
#include "app.h"

/**
 * ポートの接続対応
 * Touch sensor: Port 2
 * Color sensor: Port 3
 * USonic sensor: Port 4
 * Left  motor:  Port B
 * Right motor:  Port C
 */

const int touch_sensor = EV3_PORT_2;
const int color_sensor = EV3_PORT_3;
const int u_sonic_sensor = EV3_PORT_4;
const int left_motor = EV3_PORT_B;
const int right_motor = EV3_PORT_C;

//メインタスク
void main_task(intptr_t unused) {
  //モーターポートを設定 
  ev3_motor_config(left_motor, LARGE_MOTOR);
  ev3_motor_config(right_motor, LARGE_MOTOR);

  //センサーポートを設定
  ev3_sensor_config(touch_sensor, TOUCH_SENSOR);
  ev3_sensor_config(color_sensor, COLOR_SENSOR);
  ev3_sensor_config(u_sonic_sensor, ULTRASONIC_SENSOR);

  //変数宣言
  const int mid_point = 50;  //明るさの目標値
  const int power = 30;      //モーターパワーj
  int steer = 0;             //ハンドル操作量

  while(1){
    //明るさ取得
    int reflect_val = ev3_color_sensor_get_reflect(color_sensor);

    //ハンドル操作量決定
    if(reflect_val > mid_point){  //目標値より白い
      steer = 50;     //右に曲がる
    }else{                        //目標値より黒い
      steer = -50;    //左に曲がる
    }

    //モータ操作量を更新
    ev3_motor_steer(left_motor, right_motor, power, steer);

    //明るさとハンドル操作量を表示
    char msg[256]= {0};
    sprintf(msg, "reflect_val:%03d steer:%03d", reflect_val, steer);
    ev3_lcd_draw_string(msg,0,20);

    tslp_tsk(10); //スリープ　10[ms]
  }

  return;
}
