/*****************************************************************************
 * File: tvdecoder_ctrl.h
 *
 * TV decoder
 *
 *  Author : H.S.Hagiwara    Nov.29,2008
 *  
 ****************************************************************************/

#ifndef __TVDECODER_CTRL_H__
#define __TVDECODER_CTRL_H__

#include "i2c.h"
#include "altera_avalon_pio_regs.h"
#include "system.h"

#define VIDEO_DECODER_RESET_ON IOWR_ALTERA_AVALON_PIO_DATA(AV_RESET_PIO_BASE, 0);
#define VIDEO_DECODER_RESET_OFF IOWR_ALTERA_AVALON_PIO_DATA(AV_RESET_PIO_BASE, 1);

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void tv_decoder_write(int ad, int dt);
int tv_decoder_read(int ad);

void tv_decoder_init();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TVDECODER_CTRL_H__ */
