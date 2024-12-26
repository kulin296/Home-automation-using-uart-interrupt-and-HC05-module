#include<LPC21xx.H>
unsigned char temp;
extern int flag;
extern int f1;
extern int f2;
extern int f3;
void UART0_Handler(void)__irq
{
	int r=U0IIR;
	r&=0x0E;
	if(r==4)
	{
		temp=U0RBR;
		U0THR=temp;
		f1=1;
	}
	VICVectAddr=0;
}

void config_vic_for_uart0(void)
{
	VICIntSelect=0;
	VICVectCntl0=6|(1<<5);
	VICVectAddr0=(int)UART0_Handler;
	VICIntEnable=(1<<6);
}

void config_uart0_intr(void)
{
	U0IER=3;
}

void  EINT0_Handler(void)__irq
{
	flag^=1;
	EXTINT=1;
	VICVectAddr=0;
}

void config_vic_for_eint0(void)
{
	VICIntSelect=0;
	VICVectCntl1=14|(1<<5);
	VICVectAddr1=(int)EINT0_Handler;
	VICIntEnable=(1<<14);
}

void config_eint0(void)
{
	PINSEL1|=1;
	EXTMODE=1;
	EXTPOLAR=0;
}
void  EINT1_Handler(void)__irq
{
	f3=1;
	EXTINT|=(1<<1);
	VICVectAddr=0;
}

void config_vic_for_eint1(void)
{
	VICIntSelect=0;
	VICVectCntl2=15|(1<<5);
	VICVectAddr2=(int)EINT1_Handler;
	VICIntEnable=(1<<15);
}

void config_eint1(void)
{
	PINSEL0 |= (1<<29);
	EXTMODE|=1<<1;
	EXTPOLAR &= ~(1<<1);
}
void  EINT2_Handler(void)__irq
{
	f2=1;
	EXTINT|=(1<<2);
	VICVectAddr=0;
}

void config_vic_for_eint2(void)
{
	VICIntSelect=0;
	VICVectCntl3=16|(1<<5);
	VICVectAddr3=(int)EINT2_Handler;
	VICIntEnable=(1<<16);
}

void config_eint2(void)
{
	PINSEL0 |= (1<<31);
	EXTMODE|=1<<2;
	EXTPOLAR &= ~(1<<2);
}
