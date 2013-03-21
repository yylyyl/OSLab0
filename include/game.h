#ifndef __GAME_H__
#define __GAME_H__

#include "common.h"
#include "adt/linklist.h"

/* 中断时调用的函数 */
void timer_event(void);
void keyboard_event(int scan_code);

/* 按键相关 */
void press_key(int scan_code);
void release_key(int ch);
bool query_key(int ch);
int last_key_code(void);

/* 定义fly_t链表 */
LINKLIST_DEF(snake)
	int x, y;
	//int text;
	//int direction;
	//0: left, 1: down, 2: right, 3: up
LINKLIST_DEF_FI(snake)

/* 主循环 */
void main_loop(void);

/* 游戏逻辑相关 */
//void create_new_letter(void);
//void update_letter_pos(void);
int get_apple_x(void);
int get_apple_y(void);
void start_snake(void);
void update_snake(void);
bool update_keypress(void);
bool is_over(void);
int get_score(void);
//int get_hit(void);
//int get_miss(void);
int get_fps(void);
void set_fps(int fps);
snake_t snake_head(void);

void redraw_screen(void);

/* 随机数 */
int rand(void);
void srand(int seed);

#endif
