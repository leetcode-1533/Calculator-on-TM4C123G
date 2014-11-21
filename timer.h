#define NVIC_ST_CTRL_R		(*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R  (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R (*((volatile unsigned long *)0xE000E018))


#define SYSCTL_RCC_R            (*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RCC2_R           (*((volatile unsigned long *)0x400FE070))
#define SYSCTL_RIS_R            (*((volatile unsigned long *)0x400fe050))

void control(void);

void sys_init(void);

void delay(unsigned long test);

void more_delay(unsigned long test);

void ms_delay(unsigned long test);

void us_delay(unsigned long test);
