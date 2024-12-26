#include<LPC21XX.H>
#include"header.h"
#define led (1<<18)
#define led1 (1<<5)
#define bulb (1<<19)
#define fan (1<<20)
#define bpin ((IOPIN0>>19)&1)
#define fpin ((IOPIN0>>20)&1)
int flag;
int f1;
int f2;
int f3;
extern unsigned char  temp;
main()
{
	char cmd=0;
	IODIR0|=led|bulb|fan|led1;
	uart0_init(9600);
	config_vic_for_uart0();
	config_uart0_intr();
	config_vic_for_eint0();
	config_eint0();
	config_vic_for_eint1();
	config_eint1();
	config_vic_for_eint2();
	config_eint2();
	uart0_tx_string("Bluetooth mode\r\n");
	uart0_tx_string("\r\nMenu\r\na.Fan on\r\nb.Fan off\r\nc.Bulb on\r\nd.Bulb off\r\ne.Both on\r\nf.Both off\r\ng.change mode\r\noption...");
	IOSET0=led;
	while(1)
	{
//		IOSET0=led1;
//		delay_ms(100);
//		IOCLR0=led1;
//		delay_ms(100);
		cmd=temp;
		if(flag==0)
			IOSET0=led;
		if(flag==0 &&	f1==1)
		{
			//IOSET0=led;
			switch(cmd)
			{
				case 'a': IOSET0=fan; break;
				case 'b': IOCLR0=fan; break;
				case 'c': IOSET0=bulb; break;
				case 'd': IOCLR0=bulb; break;
				case 'e': IOSET0=fan|bulb; break;
				case 'f': IOCLR0=fan|bulb; break;
				case 'g': flag=1;
			}
			uart0_tx_string("\r\nMenu\r\na.Fan on\r\nb.Fan off\r\nc.Bulb on\r\nd.Bulb off\r\ne.Both on\r\nf.Both off\r\ng.change mode\r\noption...");
			f1=0;
		}
		else if(flag==1)
		{
			IOCLR0=led;
			if(f3==1)
			{
				if(bpin==0)
					IOSET0=bulb;
				else
					IOCLR0=bulb;
				f3=0;
			}
			else if(f2==1)
			{
				if(fpin==0)
					IOSET0=fan;
				else
					IOCLR0=fan;
				f2=0;
			}
		}
	}
}
