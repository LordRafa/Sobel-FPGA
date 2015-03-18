/*****************************************************************************
 * File: tvdecoder_ctrl.c
 *
 * TV decoder
 *
 *  Author : H.S.Hagiwara    Nov.29,2008
 *  
 ****************************************************************************/

#include "system.h"
#include "tvdecoder_ctrl.h"
#include "io.h"
#include <unistd.h>

#define TVDECODER_I2C_WRITE(a,d) i2c_write(0x40>>1,a,d)
#define TVDECODER_I2C_WRITE_ERRCHK(a,d,m) i2c_write_with_err_chk(0x40>>1,a,d,m)
#define TVDECODER_I2C_READ(a) i2c_read(0x40>>1,a)
#define itemsof(x) sizeof(x)/sizeof(x[0])

/*
 static unsigned short adv7180_setting[]={
 0x00, 0x00,
 0xc3, 0x01,
 0xc4, 0x80,
 0x04, 0x57,
 0x17, 0x41,
 0x58, 0x01,
 0x3d, 0xa2,
 //0x37, 0xa0,
 0x3e, 0x6a,
 0x3f, 0xa0,
 0x0e, 0x80,
 0x55, 0x81,
 //0x37, 0xA0,       // Polarity regiser
 0x37, 0xA1,       // Polarity regiser
 0x08, 0x80,    	// Contrast Register
 0x0a, 0x18,    	// Brightness Register
 0x2c, 0x8e,    	// AGC Mode control
 0x2d, 0xf8,       // Chroma Gain Control 1
 0x2e, 0xce,    	// Chroma Gain Control 2
 0x2f, 0xf4,    	// Luma Gain Control 1
 0x30, 0xb2,    	// Luma Gain Control 2
 0x0e, 0x00,
 };
 */

static unsigned short adv7180_setting[] = { 0x00, 0x00, // input control: Autodetect TV format, Coposite input
		0xc3, 0x01, // select AIN1
		0xc4, 0x80, // manual select

		0x3a, 0x17, // AIN2,3 power down

		0x04, 0x44, // ITU-R BT.656 compatible

		0x0d, 0x1c, // Set Free-run color
//0x0c, 0x37, // Force free-run mode

//0x04, 0x57,
//0x17, 0x41,

//0x58, 0x01,
//0x3d, 0xa2,
//0x37, 0xa0,
//0x3e, 0x6a,
//0x3f, 0xa0,
//0x0e, 0x80,
//0x55, 0x81,
//0x37, 0xA0,       // Polarity regiser
//0x37, 0xA1,       // Polarity regiser

//0x08, 0x80,    	// Contrast Register 
//0x0a, 0x18,    	// Brightness Register 
//0x2c, 0x8e,    	// AGC Mode control
//0x2d, 0xf8,       // Chroma Gain Control 1
//0x2e, 0xce,    	// Chroma Gain Control 2
//0x2f, 0xf4,    	// Luma Gain Control 1
//0x30, 0xb2,    	// Luma Gain Control 2	
//0x0e, 0x00,
		};

void tv_decoder_write(int ad, int dt) {
	TVDECODER_I2C_WRITE( ad, dt);
}

int tv_decoder_read(int ad) {
	return TVDECODER_I2C_READ( ad );
}

void tv_decoder_init() {
	int i;

	/* reset ADV7180 */
	TVDECODER_I2C_WRITE_ERRCHK( 0x0f, 0x80, 0x3);
	// skip third ACK check in I2C write protocol
	usleep(200 * 1000); // wait 200ms

	for (i = 0; i < itemsof(adv7180_setting); i += 2) {
		tv_decoder_write(adv7180_setting[i], adv7180_setting[i + 1]);
	}
}
