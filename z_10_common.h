/* z_10_common.h */
#ifndef Z_10_COMMON_H
#define Z_10_COMMON_H
#include <stdbool.h>

// タイマ，PID，コース，キャリブに関する記述

// タイム
typedef struct {
  unsigned char minute; //分
  unsigned char sec; //秒
  unsigned char millisec_10; //10ミリ秒
}timer_t;

// PID
typedef struct {
  unsigned int integer_10; //10の位
  unsigned int integer_1; //1の位
  unsigned int decimal_first; //小数第一位
  unsigned int decimal_second; //小数第二位
  unsigned int decimal_third; //小数第三位
  double integrated_value; // 上記の情報を統合して得られる数
}value_t;

typedef struct {
  value_t p; //P
  value_t i; //I
  value_t d; //D
}pid_para_t;

// コース
typdef enum {c_1_hasitemae, c_2_hasiowari, c_3_tonnnerutemae, c_4_tonnneruowari, c_5_goaltemae}cource_t;

// キャリブ
typedef struct {
  unsigned int min; //最小値
  unsigned int max; //最大値
  double ave; //平均値
}math_features_t;

// **************************************** タイマ
// タイマの初期化を行う関数
extern void func_z_10_common_clear_timer(void);
// タイマの値を取得する関数
extern const timer_t * func_z_10_common_fetch_timer(void);
// タイマの数字を文字に変換する関数
extern void func_z_10_common_format_timer(void);
// 現在のタイマの文字列を取得する関数（タイマの数字を文字に変換する関数をこの中で使う）
extern const char * func_z_10_common_fetch_timer_char(void);
// タイマカウンタの値を取得する関数
extern const unsigned int * func_z_10_common_fetch_timer_counter(void);
// タイマの値を10ミリ秒インクリメントする関数
extern void func_z_10_common_increment_timer(void);
// タイマカウンタの値を1(10ミリ秒分)インクリメントする関数
extern void func_z_10_common_increment_timer_counter(void);
// 2つのタイマの値が同じか同じでないか判別する関数
extern bool func_z_10_common_are_same_timer(timer_t * timer_1, timer_t * timer_2);
// 2つのタイマカウンタの値が同じか同じでないか判別する関数
extern bool func_z_10_common_are_same_timer_counter(unsigned int * timer_counter_1, unsigned int * timer_counter_2);
// **************************************** PID
// PID値を取得する関数(res->p.valueでアクセスできる，resはこの関数の返り値．PIDの関数の設計を間違えたので返り値をconstに出来なかった．)
extern pid_para_t * func_z_10_common_fetch_pid_para(void);
// value_tのintegrated_valueを更新する
extern void func_z_10_common_update_integrated_value(value_t * value);
// value_tの指定桁(2, 1, -1, -2, -3の5種類．それぞれ，十の位，一の位，小数第一位，小数第二位，小数第三位に対応)をインクリメントする関数．
extern void func_z_10_common_increment_num_in_value(value_t * value, int keta);
// value_tの指定桁(2, 1, -1, -2, -3の5種類．それぞれ，十の位，一の位，小数第一位，小数第二位，小数第三位に対応)をデクリメントする関数．
extern void func_z_10_common_decrement_num_in_value(value_t * value, int keta);
// value_tの値を設定する(設定する十の位，一の位，小数第一位，小数第二位，小数第三位の情報が必要)
extern void func_z_10_common_set_value(value_t * value, unsigned int integer_10_hoge, unsigned int integer_1_hoge, unsigned int decimal_first_hoge, unsigned int decimal_second_hoge, unsigned int decimal_third_hoge);
// **************************************** コース
// コースの値を取得する関数
extern const cource_t * func_z_10_common_fetch_cource(void);
// コースの値を変更する関数
extern void func_z_10_common_set_cource(cource_t cource_hoge);
// **************************************** キャリブ
// キャリブの値(黒)を取得する関数
extern const math_features_t * func_z_10_common_fetch_calib_black(void);
// キャリブの値(黒)を変更する関数
extern void func_z_10_common_set_calib_black(unsigned int min_hoge, unsigned int max_hoge, double ave_hoge);
// キャリブの値(白)を取得する関数
extern const math_features_t * func_z_10_common_fetch_calib_white(void);
// キャリブの値(白)を変更する関数
extern void func_z_10_common_set_calib_white(unsigned int min_hoge, unsigned int max_hoge, double ave_hoge);
#endif
