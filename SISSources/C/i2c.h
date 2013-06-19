/*****************************************************************************
 *  File: i2c.h
 *
 * I2C write access routine using PIO ports
 * PIO port
 *
 *  Author : H.S.Hagiwara    Nov.29,2008
 *  
 ****************************************************************************/

#ifndef __I2C_H__
#define __I2C_H__

#include "system.h"
#include "io.h"
#include "unistd.h"
#include <stdio.h>

//#include "altera_avalon_pio_regs.h"
#include "alt_types.h"

#include "altera_avalon_pio_regs.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* I2C write access */

void i2c_write( unsigned char i2c_write_address,  unsigned char i2c_write_reg, unsigned char i2c_write_data);
void i2c_write_with_err_chk( unsigned char i2c_write_address,  unsigned char i2c_write_reg, unsigned char i2c_write_data, int err_chk_mask);

int i2c_read( unsigned char i2c_read_address,  unsigned char i2c_read_reg);

/* Set up Hardware addresses for I2C PIO ports */
void init_i2c();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __I2C_H__ */
