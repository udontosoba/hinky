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
  double value; // 上記の情報を統合して得られる数
}value_t;

typedef struct {
  value_t p; //P
  value_t i; //I
  value_t d; //D
}ipd_para_t;

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
// PID値を取得する関数
extern const ipd_para_t * func_z_10_common_fetch_ipd_para(void);
// **************************************** コース

// **************************************** キャリブ

#endif
