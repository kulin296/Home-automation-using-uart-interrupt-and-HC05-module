#include<LPC21XX.H>
#include"header.h"
#define sw1 ((IOPIN0>>15)&1)
#define sw2 ((IOPIN0>>16)&1)
#define sw3 ((IOPIN0>>17)&1)
#define led (1<<18)
#define bulb (1<<19)
#define fan (1<<20)
#define bpin ((IOPIN0>>19)&1)
#define fpin ((IOPIN0>>20)&1)
int flag=0;
main()
{
	char cmd;
	IODIR0|=led|bulb|fan;
	
	uart0_init(9600);
	while(1)
	{
		if(flag==0)
		{
			IOSET0=led;
			uart0_tx_string("\r\nMenu\r\na.Fan on\r\nb.Fan off\r\nc.Bulb on\r\nd.Bulb off\r\ne.Both on\r\nf.Both off\r\ng.change mode\r\noption...");
			cmd=uart0_rx();
			uart0_tx(cmd);
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
		}
		else if(flag==1)
		{
			IOCLR0=led;
			if(sw1==0)
			{
				while(sw1==0);
				if(bpin==0)
					IOSET0=bulb;
				else
					IOCLR0=bulb;
				
			}
			else if(sw2==0)
			{
				while(sw2==0);
				if(fpin==0)
					IOSET0=fan;
				else
					IOCLR0=fan;
			}
			else if(sw3==0)
			{
				while(sw3==0);
				flag=0;
			}

		}
	}
}
