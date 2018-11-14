#include "usbmultifunction.h"
#include "joystick.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "CAN_driver.h"
#include <avr/io.h>

/* joystick channels on usb multifunction card */
#define CHANNEL_X 4  //CHANNEL 1
#define CHANNEL_Y 5  //CHANNEL 2

/* define all joystick constants */
#define X_OFFSET 127
#define Y_OFFSET 128
#define JOYSTICK_PERCENTAGE -0.788
#define JOYSTICK_ID 1
#define JOYSTICK_BUTTON_PIN PB2


int get_dir(int8_t x, int8_t y){
    
    /* nodir */
    if (x==0 && y==0){return NEUTRAL;}
    
    /* up/down */
    if(abs(x)<=abs(y)){
        if(y>0){return UP;}
        else {return DOWN;}
    }

    /* left/right */
    else if(abs(x)>abs(y)){
        if(x>0){return RIGHT;}
        else {return LEFT;}

    }

    else {return -1;} //trenger vi denne?? 
}

joystick_status get_joystick_status() {   //skal vi endre funknavn til joy_get_status?? må gjøres overalt 

	joystick_status joystick;

    joystick.dir= NEUTRAL; // trenger vi denne linjen? vi gir ny verdi lenger nede her. 

    /*converting joystick x to percentage*/
    joystick.x = (X_OFFSET-read_channel(CHANNEL_X))*(JOYSTICK_PERCENTAGE);
    joystick.y = (Y_OFFSET-read_channel(CHANNEL_Y))*(JOYSTICK_PERCENTAGE);  

    /* set joystick posistion offset */
    if(joystick.x>(-2) && joystick.x<2){
        joystick.x=0;
    }
    if(joystick.y>(-2) && joystick.y<2){
        joystick.y=0;
    }

    /* set joystick direction */
    joystick.dir=get_dir(joystick.x,joystick.y);


    /* set joystick button */
    joystick.button = (PINB & (1<<PB2));


    /* forcing joystick value to 1 or 0 */
    if (joystick.button >0) 
    {
        joystick.button=1;
    }
    else 
    {
        joystick.button=0;
    }

    return joystick;
}



bool pos_max(joystick_status joy) //trenger vi denne? hvor brukes den?? kan brukes om vi skal kalibrere joystick
{
    return (abs(joy.x)==100 || abs(joy.y)==100);
}



void transmit_joystick_status(joystick_status joystick)
{
    /* initialize can message with correct data bytes */
    int8_t b[3] = 
    {
        joystick.x,
        joystick.y,
        joystick.dir
    };

    can_message msg=
    {
        .length=3,
        .id=JOYSTICK_ID,
        .RTR=0
    };

    msg.data[0] = b[0];
    msg.data[1] = b[1];
    msg.data[2] = b[2];

    /* transmit can message to can */
    CAN_transmit(msg);

}


