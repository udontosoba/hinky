/**
 * TOPPERS/EV3　ロボコン提出コード
 * 動作説明　　指定コースを走行する．システムの概要は次に示>す通り
 *・ロボットの状態は「初期状態(s_1)」「停止状態(s_2)」「走行状態(s_3)」「設定状態(s_4)」の4状態．
 *・各状態の遷移関係は次の通り．
 *  プログラム開始 -> s_1
 *  s_1 -> s_2(キャリブレーション終了時)
 *  s_2 -> s_3(走行状態への遷移行動検知時)，s_2 -> s_4(設定状態への遷移行動検知時)
 *  s_3 -> s_2(走行終了(ボールを手放す行動をしたとき)または，停止状態への行動検知時)
 *  s_4 -> s_2(停止状態への行動検知時)
 *  ・s_1
 *  各センサのpre(1周期前の値)とcur(現在の値)を格納し終えるまで待機する．
 *  黒と白のキャリブレーションを行い，閾値の設定をする．
 *  ディスプレイ表示は「put on a black line and press hoge」「put on a red line and press hoge」など
 *  ・s_2
 *  ディスプレイの表示は「put start button」と「time = 00:00.0」(最大4分)
 *  ・s_3
 *  走行終了(ボールを手放す行動をしたとき)または停止状態への行動検知時(ボタン押下を想定)までモーターを回転させてコースを走行する．
 *  コース認識をして走行戦略を変える．各コースの走行にかかったタイムは保持しておく．コースの手前からリトライするときにそのタイムから再計測し表示する．
 *  ・s_4
 *  PID値，ロボットが走行しているコースの設定ができる．また，現在の電圧やキャリブの値を確認できる．
 *
 *  時間周期割り込みは，サンプリング時間(10ms = 0.01s)ごとに行われ，外部変数に格納される．開発者は外部変数が定義されているcファイルにアクセスする．(アクセスのための関数は用意する．)
 *  取得したタイムを用いて(if文を用いて)ディスプレイの更新や，モーター電圧の変更や，センサ値の取得を行う．
 *
 *  なお，黒は赤の上である．
 *
 * 00_ : 設定関係ファイル
 * 10_ : 皆に使ってもらう共通の独自関数ファイル
 * 20_ : 皆に書いてもらうファイル
 *
 * 参考
 * https://github.com/dashimaki360/onenightrobocon/blob/master/cookie_monster/app.cfg
 * http://dev.toppers.jp/trac_user/ev3pf/wiki/FAQ#Q周期的な>処理を追加するためにはどうすれば良いでしょうか
 */


#include "ev3api.h"
#include "app.h"

// input-output(io)の設定パラメータの定義が書かれてある．
#include "z_00_1_io_setting.h"
#include "z_00_2_state.h"
#include "z_20_1_init_state.h"
#include "z_20_2_stop_state.h"
#include "z_20_3_run_state.h"
#include "z_20_4_set_state.h"

//メインタスク
void main_task(intptr_t unused) {
  // ioポートの設定値をロボットに反映する．
  set_io();

  State state = init_state;
  while(1){
    switch (state) {
      case init_state:
        state = func_z_20_1_init_state_main();
        break;
      case stop_state:
        state = func_z_20_2_stop_state_main();
        break;
      case run_state:
        state = func_z_20_3_run_state_main();
        break;
      case set_state:
        state = func_z_20_4_set_state_main();
        break;
      default:
        state = func_z_20_1_init_state_main();
		    break;
    }
  }

  /*
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
*/
  return;
}

void set_io(void) {
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

  return;
}
