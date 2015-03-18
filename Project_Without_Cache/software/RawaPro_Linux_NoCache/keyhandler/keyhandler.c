/*
 * keyhandler.c
 *
 *  Created on: 12/04/2013
 *      Author: lordrafa
 */

#include "keyhandler.h"

void handle_button_interrupts(void* context) {
	int button;
	volatile int* fmask_ptr = (volatile int*) context;

	button = IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEY_PIO_BASE);
	*fmask_ptr ^= button;

	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY_PIO_BASE, 0);
	IOWR(LED_PIO_BASE, 0, ~fmask);

	switch (button) {
	case 1:
		printf("Pulsado Boton 1 - Valor fmask:%d.\n", fmask);
		break;
	case 2:
		printf("Pulsado Boton 2 - Valor fmask:%d.\n", fmask);
		break;
	case 4:
		printf("Pulsado Boton 3 - Valor fmask:%d.\n", fmask);
		break;
	case 8:
		printf("Pulsado Boton 4 - Valor fmask:%d.\n", fmask);
		break;
	}

}

void init_button_pio() {
	void* fmask_ptr = (void*) &fmask;
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEY_PIO_BASE, 0xf);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY_PIO_BASE, 0x0);
	alt_ic_isr_register(KEY_PIO_IRQ_INTERRUPT_CONTROLLER_ID, KEY_PIO_IRQ,
			handle_button_interrupts, fmask_ptr, 0x0);
}
