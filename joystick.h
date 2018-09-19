

typedef enum 
{
	UP=0,
	RIGHT=1,
	DOWN=2,
	LEFT=3,
	NO_DIR=4
} joystick_dir;

typedef struct joystick_status
{
	unsigned char x;
	unsigned char y;
	joystick_dir dir;
} joystick_status;

joystick_status get_joystick_status(void);