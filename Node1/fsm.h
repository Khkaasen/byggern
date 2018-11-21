#ifndef fsm_h
#define fsm_h

#include <stdint.h>

typedef enum 
{
	MENU=0,
	IN_GAME = 1,
	GAME_OVER=2,
} STATES;


typedef struct change_of_state
{
	uint8_t enable;
	int8_t game_mode;

} change_of_state;


void update_IO_card();

void fsm();

void fsm_init();


#endif