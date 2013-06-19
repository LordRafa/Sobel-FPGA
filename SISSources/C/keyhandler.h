/*
 * keyhandler.h
 *
 *  Created on: 12/04/2013
 *      Author: lordrafa
 */

#ifndef KEYHANDLER_H_
#define KEYHANDLER_H_

extern char fmask;

#include <stdio.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"

void init_button_pio();

#endif /* KEYHANDLER_H_ */
