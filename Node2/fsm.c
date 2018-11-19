#include "fsm.h"

int state;

int change_state;


can_message msg_rec = {
    .data={0,0},
    .length = 2,
    .id=1,
    .RTR= 0
};


void fsm_init(){
	change_state = 0;

	state = IDLE; 

}


void fsm(){

state= IDLE;

	while(1){

		case IDLE:

		while(1){

			if (msg_rec.id==2) // 2 er game_start_id fra node 1.  
				state= SET_UP;
				break; // vil brake while loop her.
		}

		case SET_UP:
		
		
		
	}
}

ISR(INT4_vect) {

  //_delay_ms(100);
  //printf("Hallaais\n\r" );
  //printf("%x\n\r", MCP_read(MCP_CANINTF));

  CAN_receive(&msg_rec);