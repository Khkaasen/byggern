#include "usbmultifunction.h"
#include "joystick.h"
#include <stdio.h>
#include <stdint.h>

#define CHANNEL_X 4  //CHANNEL 1
#define CHANNEL_Y 5  //CHANNEL 2
 


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

    joystick.x = (127-read_channel(CHANNEL_X))*(-0.788);
    joystick.y = (128-read_channel(CHANNEL_Y))*(-0.788);  

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

