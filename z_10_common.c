/* z_10_common.c */
#include "z_10_common.h"
#include <stdbool.h>
#include <string.h>

#define NULL ((void *)0)
#define abs(x) (((x) < 0) ? -(x) : (x))

static char * reverse(char * s);

// **************************************** タイマ
static my_timer_t timer_value = {0, 0, 0};
static char timer_char[] = {'0', ':', '0', '0', ':', '0', '0' };
static my_timer_t my_timer_vec[5] = {
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};
static unsigned int timer_counter = 0;
// **************************************** PID
static pid_para_t pid_para = {
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0}
};
// **************************************** コース
static cource_t cource = c_1_hasitemae;
// **************************************** キャリブ
static math_features_t black_info = {0 ,0, 0}; //黒色のキャリブ情報
static math_features_t white_info = {0 ,0, 0}; //白色のキャリブ情報

////////////////////////////////////////////////////////
char * itoa(int n, char *s, int w, char pad){
  int i, sign;
  sign = n;
  i = 0;
  do{
    s[i++] = abs(n % 10) + '0';
  } while((n /= 10 != 0));

  if(sign < 0){
    s[i++] = '-';
  }
  while(i < w){
    s[i++] = pad;
  }
  s[i] = '\0';
  return reverse(s);
}
static char * reverse(char *s){
  int c, i, j;
  for(i = 0, j = strlen((const char *)s) - 1; i < j; i++, j--){
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
  return s;
}

void func_z_10_common_clear_timer(void){
  timer_value.minute = 0;
  timer_value.sec = 0;
  timer_value.millisec_10 = 0;
  timer_counter = 0;
  return;
}
const my_timer_t * func_z_10_common_fetch_timer(void){
  return &timer_value;
}
void func_z_10_common_format_timer(void){
  itoa(timer_value.minute, &timer_char[0], 1, ' '); //分
  timer_char[1] = ':';
  itoa(timer_value.minute, &timer_char[2], 2, '0'); // 秒
  timer_char[4] = ':';
  itoa(timer_value.minute, &timer_char[5], 2, '0'); // 10ミリ秒
  return;
}
const char * func_z_10_common_fetch_timer_char(void){
  func_z_10_common_format_timer();
  return &timer_char;
}
const unsigned int * func_z_10_common_fetch_timer_counter(void){
  return &timer_counter;
}
void func_z_10_common_increment_timer(void){
  if(timer_value.millisec_10 <= 98){
    timer_value.millisec_10++;
  }else{
    timer_value.millisec_10 = 0;
    if(timer_value.sec <= 58){
      timer_value.sec++;
    }else{
      timer_value.sec = 0;
      if(timer_value.minute <= 8){
        timer_value.minute++;
      }else{
        // 0:00:00に初期化（timer_countは個別に初期化すること）
        timer_value.minute = 0;
      }
    }
  }
  return;
}
void func_z_10_common_increment_timer_counter(void){
  timer_counter++;
  return;
}
bool func_z_10_common_are_same_timer(my_timer_t * timer_1, my_timer_t * timer_2){
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

////////////////////////////////////////////////////////
pid_para_t * func_z_10_common_fetch_pid_para(void){
  return &pid_para;
}
void func_z_10_common_update_integrated_value(value_t * value){
  value->integrated_value = 10 * (value->integer_10) + (value->integer_1) + 0.1 * (value->decimal_first) + 0.01 * (value->decimal_second) + 0.001 * (value->decimal_third);
  return;
}
void func_z_10_common_increment_num_in_value(value_t * value, int keta){
  unsigned int  * p_int;
  switch (keta) {
    case 2:
      p_int = &(value->integer_10);
      break;
    case 1:
      p_int = &(value->integer_1);
      break;
    case -1:
      p_int = &(value->decimal_first);
      break;
    case -2:
      p_int = &(value->decimal_second);
      break;
    case -3:
      p_int = &(value->decimal_third);
      break;
    default:
      p_int = NULL;
      break;
  }
  if(p_int == NULL){
    return;
  }
  if((*p_int) <= 8){
    (*p_int)++;
    func_z_10_common_update_integrated_value(value);
    return;
  }
  return;
}
void func_z_10_common_decrement_num_in_value(value_t * value, int keta){
  unsigned int  * p_int;
  switch (keta) {
    case 2:
      p_int = &(value->integer_10);
      break;
    case 1:
      p_int = &(value->integer_1);
      break;
    case -1:
      p_int = &(value->decimal_first);
      break;
    case -2:
      p_int = &(value->decimal_second);
      break;
    case -3:
      p_int = &(value->decimal_third);
      break;
    default:
      p_int = NULL;
      break;
  }
  if(p_int == NULL){
    return;
  }
  if((*p_int) >= 1){
    (*p_int)--;
    func_z_10_common_update_integrated_value(value);
    return;
  }
  return;
}
void func_z_10_common_set_value(value_t * value, unsigned int integer_10_hoge, unsigned int integer_1_hoge, unsigned int decimal_first_hoge, unsigned int decimal_second_hoge, unsigned int decimal_third_hoge){
  value->integer_10 = integer_10_hoge;
  value->integer_1 = integer_1_hoge;
  value->decimal_first = decimal_first_hoge;
  value->decimal_second = decimal_second_hoge;
  value->decimal_third = decimal_third_hoge;
  func_z_10_common_update_integrated_value(value);
}
////////////////////////////////////////////////////////
const cource_t * func_z_10_common_fetch_cource(void){
  return &cource;
}
void func_z_10_common_set_cource(cource_t cource_hoge){
  cource = cource_hoge;
  return;
}
////////////////////////////////////////////////////////
const math_features_t * func_z_10_common_fetch_calib_black(void){
  return &black_info;
}
void func_z_10_common_set_calib_black(unsigned int min_hoge, unsigned int max_hoge, double ave_hoge){
  black_info.min = min_hoge;
  black_info.max = max_hoge;
  black_info.ave = ave_hoge;
}
const math_features_t * func_z_10_common_fetch_calib_white(void){
  return &white_info;
}
void func_z_10_common_set_calib_white(unsigned int min_hoge, unsigned int max_hoge, double ave_hoge){
  white_info.min = min_hoge;
  white_info.max = max_hoge;
  white_info.ave = ave_hoge;
}
