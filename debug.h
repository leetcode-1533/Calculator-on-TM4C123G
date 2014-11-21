/*
 * debug.h
 *
 *  Created on: Nov 11, 2014
 *      Author: tk
 */

#ifndef DEBUG_H_
#define DEBUG_H_


#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

void ConfigureUART(void);



#endif /* DEBUG_H_ */
