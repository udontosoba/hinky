/* z_10_common.c */
#include "z_10_common.h"
#include <stdlib.h>
#include <stdbool.h>

// **************************************** タイマ
static timer_t timer_value = {0, 0, 0};
static char timer_char[] = {'0', ':', '0', '0', ':', '0', '0' }
static unsigned int timer_counter = 0;
// **************************************** PID
static ipd_para_t ipd_para = {
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0}
};
// **************************************** コース
static cource_t cource = c_1_hasitemae;
// **************************************** キャリブ
static math_features_t black_info = {0 ,0, 0}; //黒色のキャリブ情報
static math_features_t white_info = {0 ,0, 0}; //白色のキャリブ情報

////////////////////////////////////////////////////////
void func_z_10_common_clear_timer(void){
  timer_value.minute = 0;
  timer_value.sec = 0;
  timer_value.millisec = 0;
  timer_counter = 0;
  return;
}
const timer_t * func_z_10_common_fetch_timer(void){
  return &timer_value;
}
const unsigned int * func_z_10_common_fetch_timer_counter(void){
  return &timer_counter;
}
void func_z_10_common_increment_timer(void){
  timer_counter++;
  return;
}
void func_z_10_common_increment_timer_counter(void){
  if(timer_value.millisec_10 <= 98){
    timer_value.millisec_10++;
  }else{
    if(timer_value.sec < 58){
      timer_value.millisec_10 = 0;
      timer_value.sec++;
    }else{
      if(timer_value.minute < 8){

      }
    }
  }

  return;
}
void func_z_10_common_format_timer(timer_t timer){
  itoa(timer_value.minute, &timer_char[0], 1, ' '); //分
  timer_char[1] = ':';
  itoa(timer_value.minute, &timer_char[2], 2, '0'); // 秒
  timer_char[4] = ':';
  itoa(timer_value.minute, &timer_char[5], 2, '0'); // 10ミリ秒
  return;
}
bool func_z_10_common_are_same_timer(timer_t * timer_1, timer_t * timer_2){
  if(timer_1->minute != timer_2->minute){
    return false;
  }
  if(timer_1->sec != timer_2->sec){
    return false;
  }
  if(timer_1->millisec_10 != timer_2->millisec_10){
    return false;
  }
  return true;
}

bool func_z_10_common_are_same_timer_counter(unsigned int * timer_counter_1, unsigned int * timer_counter_2){
  if((*timer_counter_1) != (*timer_counter_2)){
    return false;
  }
  return true;
}
