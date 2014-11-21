#include "timer.h"

void sys_init(void){
	NVIC_ST_CTRL_R = 0x0;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x5;
}

void delay(unsigned long test){
	NVIC_ST_RELOAD_R = test - 1;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R&(0x1<<16))==0)
	{}
}

void more_delay(unsigned long test){
	unsigned long i;
	for(i = 0; i<test ; i++){
		delay(800000);
	}
}

void ms_delay(unsigned long test){
	unsigned long i;
	for(i = 0; i<test ; i++){
		delay(80000);
	}
}

void us_delay(unsigned long test){
	unsigned long i;
	for(i = 0; i<test ; i++){
		delay(80);
	}
}

void control(void){
	SYSCTL_RCC2_R |= 0x80000000; //use *** bit31 : Enable more function from rcc2 not to use rcc solely
	
	SYSCTL_RCC2_R |= 0x800;   //Using bit 11 bypass to disconnect
	
	SYSCTL_RCC_R &= ~0x7C0;  // choosing XTAL
	SYSCTL_RCC_R |= 0x540;  // choosing XTAL
	
	SYSCTL_RCC2_R &= ~0x70;//OSCSRC2 cleaning, using main oscillator
	
	SYSCTL_RCC2_R &= ~0x2000; // Activate oscillator
	
	//
	SYSCTL_RCC2_R |= 0x40000000; //***bit 30  // choosing div 400 1 as 400 2 as be 2 divided so 200Mhz
	
	SYSCTL_RCC2_R &= ~0x1FC00000;   // Choosing divider
	SYSCTL_RCC2_R |= (0x4)<<22;    // Choosing divider
	
	while((SYSCTL_RIS_R&0x40)==0){ //waiting
	}
	
	SYSCTL_RCC2_R &= ~0x800;  //Using bit 11 bypass to connect: //50MHZ
}
