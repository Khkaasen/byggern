#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

#include "usbmultifunction.h"
#include "joystick.h"
#include "CAN_driver.h"

/* Joystick channels on usb multifunction card */
#define CHANNEL_X 4  //CHANNEL 1
#define CHANNEL_Y 5  //CHANNEL 2

/* Define all joystick constants */
#define X_OFFSET 127
#define Y_OFFSET 128
#define JOYSTICK_PERCENTAGE -0.788
#define JOYSTICK_ID 1
#define JOYSTICK_BUTTON_PIN PB2


int get_dir(int8_t x, int8_t y)
{
    /* nodir */
    if (x==0 && y==0){return NEUTRAL;}
    
    /* up/down */
    if(abs(x)<=abs(y))
    {
        if(y>0){return UP;}
        else {return DOWN;}
    }

    /* left/right */
    else if(abs(x)>abs(y))
    {
        if(x>0){return RIGHT;}
        else {return LEFT;}
    }
    else {return -1;}
}

joystick_struct get_joystick_status()                   //skal vi endre funknavn til joy_get_status?? må gjøres overalt 
{                     
	joystick_struct joystick;

    joystick.dir= NEUTRAL;                            //kan teste uten denne

    /* Converting joystick x to percentage */
    joystick.y = (Y_OFFSET-read_channel(CHANNEL_Y))*(JOYSTICK_PERCENTAGE); 
    joystick.x = (X_OFFSET-read_channel(CHANNEL_X))*(JOYSTICK_PERCENTAGE);
   
    /* Set joystick posistion offset */
    if(joystick.x>(-2) && joystick.x<2)
    {
        joystick.x=0;
    }

    if(joystick.y>(-2) && joystick.y<2)
    {
        joystick.y=0;
    }

    /* Set joystick direction */
    joystick.dir=get_dir(joystick.x,joystick.y);


    /* Set joystick button */
    joystick.button = (PINB & (1<<PB2));


    /* Forcing joystick value to 1 or 0 */
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

bool pos_max(joystick_struct joy)
{
    return (abs(joy.x)==100 || abs(joy.y)==100);
}

void transmit_joystick_status(joystick_struct joystick)
{
    /* Initialize can message with correct data bytes */
    int8_t byte[3] = 
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

    msg.data[0] = byte[0];
    msg.data[1] = byte[1];
    msg.data[2] = byte[2];

    /* Transmit can message to can */
    CAN_transmit(&msg);

}


