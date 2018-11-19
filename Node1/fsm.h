
typedef enum 
{
	MENU=0,
	IN_GAME = 1,
	GAME_OVER=2,
} STATES;


typedef struct change_state
{
	uint8_t enable;
	int8_t game_mode;

} change_state;


void update_IO_card();


void fsm();

void fsm_init();


