#include "usbmultifunction.h"
#include "joystick.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "CAN_driver.h"
#define CHANNEL_X 4  //CHANNEL 1
#define CHANNEL_Y 5  //CHANNEL 2

#define X_OFFSET 127
#define Y_OFFSET 128
#define JOYSTICK_PERCENTAGE -0.788
#define JOYSTICK_ID 1

int get_dir(int8_t x, int8_t y){
        //nodir
    if (x==0 && y==0){return NEUTRAL;}
    //up/down (siden <= vil denne skje om det er x=-100 y=100)
    if(abs(x)<=abs(y)){
        if(y>0){return UP;}
        else {return DOWN;}
    }
    //left/right
    else if(abs(x)>abs(y)){
        if(x>0){return RIGHT;}
        else {return LEFT;}

    }
    else {return -1;}
}

joystick_status get_joystick_status() {

	joystick_status joystick;

    joystick.dir= NEUTRAL;

    //converting joystick x to percentage

    joystick.x = (X_OFFSET-read_channel(CHANNEL_X))*(JOYSTICK_PERCENTAGE);
    joystick.y = (Y_OFFSET-read_channel(CHANNEL_Y))*(JOYSTICK_PERCENTAGE);  

    //offset
    if(joystick.x>(-2) && joystick.x<2){
        joystick.x=0;
    }
    if(joystick.y>(-2) && joystick.y<2){
        joystick.y=0;
    }

    joystick.dir=get_dir(joystick.x,joystick.y);
    //printf("Joystick X:pos %4d  ", joystick.x);
    //printf("Joystick y:pos %4d \n  ", joystick.y);
    //printf("Joystick dir %4d \n", joystick.dir);
    return joystick;
    
    
	
}

bool pos_max(joystick_status joy)
{
    return (abs(joy.x)==100 || abs(joy.y)==100);
}



void transmit_joystick_status(joystick_status joystick)
{
    int8_t b[3] = {joystick.x,joystick.y,joystick.dir};
    can_message msg=
    {
        .length=3,
        .id=JOYSTICK_ID, //id = 1 is static joystick_pos
        .RTR=0
    };
    msg.data[0] = b[0];
    msg.data[1] = b[1];
    msg.data[2] = b[2];

    //printf("X  : %d \n", msg.data[0]);
    //printf("Y  : %d \n", msg.data[1]);
    //printf("DIR: %d \n", msg.data[2]);

    CAN_transmit(msg);

}