/* z_00_1_io_setting.c */
#include "z_00_1_io_setting.h"

// EV3_PORT_hogeの定義が書かれてある．
#include "ev3api.h"

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

const int get_touch_sensor_port(void)
{
  return touch_sensor;
}

const int get_left_color_sensor_port(void)
{
  return left_color_sensor;
}

const int get_right_color_sensor_port(void)
{
  return right_color_sensor;
}

const int get_distance_measuring_sensor_port(void)
{
  return distance_measuring_sensor;
}

const int get_left_motor_port(void)
{
  return left_motor;
}

const int get_right_motor_port(void)
{
  return right_motor;
}

const int get_motor_for_marble_port(void)
{
  return motor_for_marble;
}
