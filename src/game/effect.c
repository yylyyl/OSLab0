#include "game.h"
#include "common.h"
#include "string.h"
#include "adt/linklist.h"
#include "device/video.h"
#include "x86/x86.h"

LINKLIST_IMPL(snake, 10000)

static snake_t head = NULL;
static int score = 0;
static int apple_x=0, apple_y=0;
static bool die = FALSE;
static int direction = 0, next_direction = 0;
int get_apple_x(void) {
	return apple_x;
}

int get_apple_y(void) {
	return apple_y;
}

bool is_over(void) {
	return die;
}

int
get_score(void) {
	return score;
}

snake_t
snake_head(void) {
	return head;
}

//320x200, screen.
//#define game_x 280
//#define game_y 200
//#define snake_size 10
void add_apple(void) {
	int x, y;
	while(TRUE) {
		x = rand()%(game_x/snake_size-1);
		y = rand()%(game_y/snake_size-1);
		snake_t p = head;
		while(p!=NULL) {
			if(p->x==x && p->y==y)
				continue;
			p = p->_next;
		}
		break;
	}
	apple_x = x;
	apple_y = y;
		
}


void
update_snake(void) {
	if(die)
		return;
	snake_t s = head, tail = NULL;
	int last_x = -1, last_y = -1;
	int n = 0;

	direction = next_direction;
	while ( s != NULL ) {
		if(s!=head) {
			int x = s->x, y = s->y;	
			s->x = last_x;
			s->y = last_y;
			last_x = x;
			last_y = y;
		}else{
			last_x = s->x;
			last_y = s->y;
			if(direction==0)
				s->x -= 1;
			else if(direction==1)
				s->y += 1;
			else if(direction==2)
				s->x += 1;
			else	s->y -= 1;
			
		}

		tail = s;
		
		s = s->_next;
		n++;
	}
	if(head->x < 0 || head->y < 0 || head->x > game_x/snake_size-1 || head->y > game_y/snake_size-1)
		die = TRUE;

	snake_t p = head->_next;
	while(p!=NULL) {
		if(head->x == p->x && head->y == p->y) {
			die = TRUE;
			break;
		}
		p = p->_next;
	}

	if(apple_x == head->x && apple_y == head->y) {
		//add tail.
		add_apple();
		score++;
		snake_t now = snake_new();
		snake_insert(tail, NULL, now);
		now->x = last_x;
		now->y = last_y;
	}
}

void
start_snake(void) {
	add_apple();
	score = 0;
	head = snake_new();
	head->x = game_x/snake_size/2;
	head->y = game_y/snake_size/2;
	direction = 0;
	snake_t s = snake_new();
	s->x = head->x + 1;
	assert(s->x <= game_x/snake_size);
	s->y = head->y;
	snake_insert(head, NULL, s);
}

/* 更新按键 */
bool
update_keypress(void) {
	disable_interrupt();
	
	int i, d = -1, dd = direction;
	for (i = 0; i < 4; i++)
		if(query_key(i))
			d = i;
	if(d != -1) {
		release_key(d);
		if(die) {
			die = FALSE;
			
			snake_t p = head, q;
			while(p!=NULL) {
				q = p->_next;
				snake_free(p);
				p = q;
			}
			start_snake();
			return TRUE;
		}
		if(!(d-dd == 2 || dd-d == 2))
			next_direction = d;
		return TRUE;
	}


	enable_interrupt();

	return FALSE;
}

