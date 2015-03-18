/*****************************************************************************
 *  File: main.c for vip_demo
 *
 *  This file is the top level of the application selector.
 *
 ****************************************************************************/

#include <unistd.h>
#include "alt_tpo_lcd/alt_tpo_lcd.h"
#include "audio_tvdecoder/tvdecoder_ctrl.h"
#include "audio_tvdecoder/i2c.h"
#include "framereader/vip_wrapper_for_c_func.h"
#include "keyhandler/keyhandler.h"
#include "sfs/sfs.h"
#include "alt_video_display/alt_video_display.h"
#include "graphics_lib/simple_graphics.h"
#include <altera_avalon_performance_counter.h>

char fmask = 12; // MSB - * * * * 3 2 1 0 - LSB
// 4 - FPS
// 3 - COLOR/SOBEL
// 2 - VIDEO/IMAGEN
// 0 - SW/HW

int main() {

	unsigned int N[480][800];
	unsigned int M[480][800];
	unsigned int P[480][800];
	alt_video_display *display1;
	alt_video_display *display2;
	char strbuff[256];
	int sw;

	display1 = alt_video_display_only_frame_init(800, 480, 32, (int) M, 1);
	display2 = alt_video_display_only_frame_init(800, 480, 32, (int) N, 1);

	VIDEO_DECODER_RESET_ON; // reset TV Decoder chip

	printf("\n\n\n\n");
	printf("**********************************************************\n");
	printf("* INICIO RAWAPRO!                                        *\n");
	printf("**********************************************************\n\n");

	printf("Configuracion LCD: ");
	alt_tpo_lcd lcd_serial;
	lcd_serial.scen_pio = LCD_SPI_EN_BASE;
	lcd_serial.scl_pio = LCD_SPI_SCL_BASE;
	lcd_serial.sda_pio = LCD_SPI_SDAT_BASE;
	alt_tpo_lcd_init(&lcd_serial, 800, 480);
	printf("OK\n");

	printf("Configuracion Video Compuesto: ");
	// Release reset for TV decoder chip
	VIDEO_DECODER_RESET_OFF;
	// set hardware adderss of I2C port
	init_i2c();
	// initialize TV decoder chip
	tv_decoder_init();
	// monitor TV decoder status for debug
	printf("OK\n");

	printf("Configuracion Altera VIP FrameReader: ");
	Frame_Reader_init();
	Frame_Reader_set_frame_0_properties((int) &M[0][0], 800 * 480, 800 * 480,
			800, 480, 3); // 3=progressive video
	Frame_Reader_set_frame_1_properties((int) &N[0][0], 800 * 480, 800 * 480,
			800, 480, 3); // 3=progressive video
	printf("OK\n");

	printf("Configuracion Manejador de Botones: ");
	init_button_pio();
	printf("OK\n");

	printf("Configuracion LEDs: ");
	IOWR(LED_PIO_BASE, 0, ~fmask);
	printf("OK\n");

	printf("Iniciando bucle principal.\n");

	// Bucle principal del programa
	while (1) {

		PERF_RESET(PERFORMANCE_COUNTER_BASE);
		PERF_START_MEASURING(PERFORMANCE_COUNTER_BASE);
		if ((fmask & 2) == 2) {
			FrameWrite_HW((int)&P);
			AGrises(P);
			Sobel(P, M);
		} else {
			FrameWrite_HW((int)&M);
		}
		PERF_STOP_MEASURING(PERFORMANCE_COUNTER_BASE);

		if ((fmask & 1) == 1) {
			snprintf(strbuff, 256, "%llu ciclos por frame", perf_get_total_time((int*)PERFORMANCE_COUNTER_BASE));
			sw = vid_string_pixel_length_alpha(tahomabold_32, strbuff);
			vid_print_string_alpha(8, 8, ORANGE_24, BLACK_24, tahomabold_20,
					display1, strbuff);
		}

		Frame_Reader_switch_to_pb0();
		Frame_Reader_start();
		while ((fmask & 4) == 0) {
			usleep(200000);
		}

		PERF_RESET(PERFORMANCE_COUNTER_BASE);
		PERF_START_MEASURING(PERFORMANCE_COUNTER_BASE);
		if ((fmask & 2) == 2) {
			FrameWrite_HW((int)&P);
			AGrises(P);
			Sobel(P, N);
		} else {
			FrameWrite_HW((int)&N);
		}
		PERF_STOP_MEASURING(PERFORMANCE_COUNTER_BASE);

		if ((fmask & 1) == 1) {
			snprintf(strbuff, 256, "%llu ciclos por frame", perf_get_total_time((int*)PERFORMANCE_COUNTER_BASE));
			sw = vid_string_pixel_length_alpha(tahomabold_32, strbuff);
			vid_print_string_alpha(8, 8, ORANGE_24, BLACK_24, tahomabold_20,
					display2, strbuff);
		}

		Frame_Reader_switch_to_pb1();
		Frame_Reader_start();
		while ((fmask & 4) == 0) {
			usleep(200000);
		}
	}

	return (0);
}
