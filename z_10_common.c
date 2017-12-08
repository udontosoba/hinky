/* z_10_common.c */
#include "z_10_common.h"
#include <stdlib.h>
#include <stdbool.h>

static timer_t timer_value = {0, 0, 0};
static char timer_char[] = {'0', ':', '0', '0', ':', '0', '0' }
static unsigned int timer_counter = 0;

static ipd_para_t ipd_para = {
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0}
};

static cource_t cource = c_1_hasitemae;

static math_features_t black_info = {0 ,0, 0};

static math_features_t white_info = {0 ,0, 0};

void func_z_10_common_format_timer(timer_t timer){
  itoa(timer_value.minute, &timer_char[0], 1, ' '); //分
  timer_char[1] = ':';
  itoa(timer_value.minute, &timer_char[2], 2, '0'); // 秒
  timer_char[4] = ':';
  itoa(timer_value.minute, &timer_char[5], 2, '0'); // 10ミリ秒
  return;
}

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

const unsigned int timer_counter * func_z_10_common_fetch_timer_counter(void){
  return &timer_counter;
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
