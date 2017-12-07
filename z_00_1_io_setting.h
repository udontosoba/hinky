/* z_00_1_io_setting.h */
#ifndef Z_00_1_IO_SETTING_H
#define Z_00_1_IO_SETTING_H

// input
// タッチセンサのポート情報
extern const int touch_sensor;
// 左カラーセンサのポート情報
extern const int left_color_sensor;
// 右カラーセンサのポート情報
extern const int right_color_sensor;
// 測距センサのポート情報
extern const int distance_measuring_sensor;

// output
// 左モータのポート情報
extern const int left_motor;
// 右モータのポート情報
extern const int right_motor;
// ビー玉用サーボモータのポート情報
extern const int motor_for_marble;

// タッチセンサのポート情報を返す．
extern const int get_touch_sensor_port(void);
// 左カラーセンサのポート情報を返す．
extern const int get_left_color_sensor_port(void);
// 右カラーセンサのポート情報を返す．
extern const int get_right_color_sensor_port(void);
// 測距センサのポート情報を返す．
extern const int get_distance_measuring_sensor_port(void);
// 左モータのポート情報を返す．
extern const int get_left_motor_port(void);
// 右モータのポート情報を返す．
extern const int get_right_motor_port(void);
// ビー玉用サーボモータのポート情報を返す．
extern const int get_motor_for_marble_port(void);

#endif
