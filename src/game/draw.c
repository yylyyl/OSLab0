#include "game.h"
#include "string.h"
#include "device/video.h"

/* 绘制屏幕上的内容。
 * 注意程序在绘图之前调用了prepare_buffer，结束前调用了display_buffer。
 * prepare_buffer会准备一个空白的绘图缓冲区，display_buffer则会将缓冲区绘制到屏幕上，
 * draw_pixel或draw_string绘制的内容将保存在缓冲区内(暂时不会显示在屏幕上)，调用
 * display_buffer后才会显示。
*/
#define left (SCR_WIDTH-game_x)/2
#define right left+game_x

void
redraw_screen() {
	snake_t it;
	const char *score;
	
	prepare_buffer(); /* 准备缓冲区 */

	/* 绘制每个字符 */
	for (it = snake_head(); it != NULL; it = it->_next) {
		//static char buf[2];
		//buf[0] = it->text + 'A'; buf[1] = 0;
		//draw_string(buf, it->x, it->y, 15);
		int i, j;
		for(i=0; i<snake_size; i++)
			for(j=0; j<snake_size; j++)
				if(it->x >= 0 && it->x < game_x/snake_size && it->y >= 0 && it->y < game_y/snake_size)
					draw_pixel(it->y * snake_size + j, left + it->x * snake_size + i, 15);
	}
	int i, j;
	//draw apple
	for(i=0; i<snake_size; i++)
		for(j=0; j<snake_size; j++)
			draw_pixel(get_apple_y() * snake_size + j, left + get_apple_x() * snake_size + i, 5);

	//draw square
	for(i=0; i<SCR_WIDTH; i++)
		for(j=0; j<SCR_HEIGHT; j++)
			if(i<left || i>right)
				draw_pixel(j, i, 7);

	if(is_over()) {
		char over[] = "GAME OVER";
		draw_string(over, (SCR_HEIGHT-8)/2, (SCR_WIDTH-strlen(over)*8)/2, 14);
	}
	/* 绘制命中数、miss数、最后一次按键扫描码和fps */
	draw_string(itoa(last_key_code()), SCR_HEIGHT - 8, 0, 48);
	score = itoa(get_score());
	draw_string(score, 0, SCR_WIDTH - strlen(score) * 8, 10);
	//miss = itoa(get_miss());
	//draw_string(miss, SCR_HEIGHT - 8, SCR_WIDTH - strlen(miss) * 8, 12);
	draw_string(itoa(get_fps()), 0, 0, 14);
	draw_string("FPS", 0, strlen(itoa(get_fps())) * 8, 14);

	display_buffer(); /* 绘制缓冲区 */
}

