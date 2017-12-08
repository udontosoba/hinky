/* z_10_common.h */
#ifndef Z_10_COMMON_H
#define Z_10_COMMON_H
#include <stdbool.h>

typedef struct {
  unsigned char minute; //分
  unsigned char sec; //秒
  unsigned char millisec_10; //10ミリ秒
}timer_t;

typedef struct {
  unsigned int integer_10; //10の位
  unsigned int integer_1; //1の位
  unsigned int decimal_first; //小数第一位
  unsigned int decimal_second; //小数第二位
  unsigned int decimal_third; //小数第三位
}value_t;

typedef struct {
  value_t p; //P
  value_t i; //I
  value_t d; //D
}ipd_para_t;

typedef struct {
  unsigned int min; //最小値
  unsigned int max; //最大値
  double ave; //平均値
}math_features_t;

typdef enum {c_1_hasitemae, c_2_hasiowari, c_3_tonnnerutemae, c_4_tonnneruowari, c_5_goaltemae}cource_t;

// タイマの数字を文字に変換する関数
extern void func_z_10_common_format_timer(timer_t timer);
// タイマの初期化を行う関数
extern void func_z_10_common_clear_timer(void);
// タイマの値を取得する関数
extern const timer_t * func_z_10_common_fetch_timer(void);
// タイマカウンタの値を取得する関数
extern const unsigned int timer_counter * func_z_10_common_fetch_timer_counter(void);
// 2つのタイマの値が同じか同じでないか判別する関数
extern bool func_z_10_common_are_same_timer(timer_t * timer_1, timer_t * timer_2);
// 2つのタイマカウンタの値が同じか同じでないか判別する関数
extern bool func_z_10_common_are_same_timer_counter(unsigned int * timer_counter_1, unsigned int * timer_counter_2);

#endif
