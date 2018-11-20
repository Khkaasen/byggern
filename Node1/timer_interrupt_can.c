
timer;
timer_init()
{
	// Timer0 Overflow Interrupt Enable
	TIMSK |= (1<<TOIE0);

	//Timer to normal mode
	TCCR0 &= ~(1<<WGM00);
	TCCR0 &= ~(1<<WGM01);

	//Set prescaler to 1024
	TCCR0 |= (1<<CS00);
	TCCR0 &= ~(1<<CS01);
	TCCR0 |= (1<<CS02);

	timer =0;

}

reset_timer()
{
	timer =0;
	TCNT0 = 0;

}

ISR(Timer0_OFV_vec)
{
	timer++;
	if(timer == 480)
	{
		transmit_IO_card();
		timer=0;
		
	}
}