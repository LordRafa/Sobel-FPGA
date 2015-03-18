/*****************************************************************************
 *  File: i2c.c
 *
 * I2C write access routine using PIO ports
 * PIO port を利用した I2C write アクセスルーチン
 *
 *  by H.S.Hagiwara    Nov.29,2008
 *  
 ****************************************************************************/

#include "system.h"
#include "io.h"
#include "unistd.h"
#include <stdio.h>

//#include "altera_avalon_pio_regs.h"
#include "alt_types.h"

#include "altera_avalon_pio_regs.h"

#include "i2c.h"

typedef struct s_I2C_PIO {
  alt_u32 SDIN_ptr;
  alt_u32 SCLK_ptr;
} T_I2C_PIO;

static T_I2C_PIO I2C_PIO;

/* I2C の DATA/CLK 信号は、bi-directional であり、High-Z により、1 を表現
   するが、この評価キットでは CLK 信号はダイレクトに 1/0 をドライブする設計
   となっている                                                              */
#define I2C_SDIN_HIGHZ(i2c) IOWR_ALTERA_AVALON_PIO_DIRECTION(i2c->SDIN_ptr, ALTERA_AVALON_PIO_DIRECTION_INPUT)
#define I2C_SDIN_Z(i2c) I2C_SDIN_HIGHZ(i2c)
#define I2C_SDIN_1(i2c) I2C_SDIN_HIGHZ(i2c)
#define I2C_SDIN_0(i2c) IOWR_ALTERA_AVALON_PIO_DIRECTION(i2c->SDIN_ptr, ALTERA_AVALON_PIO_DIRECTION_OUTPUT)

#define I2C_SCLK_1(i2c) IOWR_ALTERA_AVALON_PIO_DATA(i2c->SCLK_ptr, 1)
#define I2C_SCLK_0(i2c) IOWR_ALTERA_AVALON_PIO_DATA(i2c->SCLK_ptr, 0)


static void i2c_setup_hw( T_I2C_PIO *i2c, alt_u32 sdin_base, alt_u32 sclk_base){
  i2c->SDIN_ptr = sdin_base;
  i2c->SCLK_ptr = sclk_base;


  IOWR_ALTERA_AVALON_PIO_DIRECTION(i2c->SDIN_ptr, ALTERA_AVALON_PIO_DIRECTION_INPUT);// High-Z
  IOWR_ALTERA_AVALON_PIO_DATA(i2c->SDIN_ptr, 0); // Set 0 for output 

  // reset WM8731 I2C I/F
  I2C_SCLK_1(i2c);
  usleep(1);
  I2C_SDIN_1(i2c);
  usleep(1);
  I2C_SDIN_0(i2c);
  usleep(1);
  I2C_SDIN_1(i2c);
  usleep(1000);

}

static void i2c_start( T_I2C_PIO *i2c){
  I2C_SCLK_1(i2c);
  usleep(1);
  I2C_SDIN_1(i2c);
  usleep(1);
  I2C_SDIN_0(i2c);
  usleep(1);
  I2C_SCLK_0(i2c);
  usleep(1);
}

static void i2c_bit_write( T_I2C_PIO *i2c, int dat){
//  I2C_SCLK_0(i2c);
//  usleep(1);

  if (dat) I2C_SDIN_1(i2c);
  else I2C_SDIN_0(i2c);

  usleep(1);
  I2C_SCLK_1(i2c);
  usleep(1);
  I2C_SCLK_0(i2c);
  usleep(1);
}


static void i2c_stop( T_I2C_PIO *i2c){
  I2C_SDIN_0(i2c);
  usleep(1);
  I2C_SCLK_1(i2c);
  usleep(1);
  I2C_SDIN_1(i2c);
  usleep(1);
}

static int i2c_ack_sense( T_I2C_PIO *i2c){
  int rv;

  I2C_SDIN_HIGHZ(i2c); // 
  usleep(1);
  I2C_SCLK_1(i2c);
  usleep(1);

  rv = IORD_ALTERA_AVALON_PIO_DATA(i2c->SDIN_ptr);
  
  I2C_SCLK_0(i2c);
  usleep(1);

  return rv;
}



/* I2C 書き込みアクセス */

void i2c_write_with_err_chk( unsigned char i2c_write_address,  unsigned char i2c_write_reg, unsigned char i2c_write_data, int err_chk_mask){
  int i;
  int rv;

  i2c_start(&I2C_PIO); 
  for(i=6;i>=0;i--){
    i2c_bit_write( &I2C_PIO, (i2c_write_address>>i)&1);
  }
    i2c_bit_write( &I2C_PIO, 0); // write command
    rv = i2c_ack_sense( &I2C_PIO); // sense ack
if( (err_chk_mask&1) && rv) printf("Error:Audio I2C ack access1\n"); // for debug

  for(i=7;i>=0;i--){
    i2c_bit_write( &I2C_PIO, (i2c_write_reg>>i)&1);
  }
    rv = i2c_ack_sense( &I2C_PIO); // sense ack
if((err_chk_mask&2) && rv) printf("Error:Audio I2C ack access2\n"); // for debug
    
  for(i=7;i>=0;i--){
    i2c_bit_write( &I2C_PIO, (i2c_write_data>>i)&1);
  }
    rv = i2c_ack_sense( &I2C_PIO); // sense ack
if((err_chk_mask&4) && rv) printf("Error:Audio I2C ack access3\n"); // for debug

  i2c_stop( &I2C_PIO);
}

/* i2c_write( unsigned char i2c_write_address,  unsigned char i2c_write_reg, unsigned char i2c_write_data) */
void i2c_write( unsigned char i2c_write_address,  unsigned char i2c_write_reg, unsigned char i2c_write_data){
  i2c_write_with_err_chk( i2c_write_address,  i2c_write_reg, i2c_write_data, 0xf);
} 


#if 1
/* I2C read access */
int i2c_read( unsigned char i2c_read_address,  unsigned char i2c_read_reg){
  int i;
  int rv;
  unsigned data;

  i2c_start(&I2C_PIO); 
  for(i=6;i>=0;i--){
    i2c_bit_write( &I2C_PIO, (i2c_read_address>>i)&1);
  }
  i2c_bit_write( &I2C_PIO, 0); // normal command

  rv = i2c_ack_sense( &I2C_PIO); // sense ack
  if(rv) {
    printf("Error:I2C RD ack access1\n"); // for debug
    rv = -1;
    goto ACK_ERROR;
  }

  for(i=7;i>=0;i--){
    i2c_bit_write( &I2C_PIO, (i2c_read_reg>>i)&1);
  }
  rv = i2c_ack_sense( &I2C_PIO); // sense ack
  if(rv) {
    printf("Error:I2C RD ack access2\n"); // for debug
    rv = -2;
    goto ACK_ERROR;
  }
   

  i2c_start(&I2C_PIO); 
  for(i=6;i>=0;i--){
    i2c_bit_write( &I2C_PIO, (i2c_read_address>>i)&1);
  }
  i2c_bit_write( &I2C_PIO, 1); // read command

  rv = i2c_ack_sense( &I2C_PIO); // sense ack
  if(rv) {
    printf("Error:I2C RD ack access3\n"); // for debug
    rv = -3;
    goto ACK_ERROR;
  }

  data = 0;
  for(i=7;i>=0;i--){
    data = data << 1;
    data |= i2c_ack_sense( &I2C_PIO) &1;
  }

    i2c_bit_write( &I2C_PIO, 1); // write master non-ack
//    i2c_bit_write( &I2C_PIO, 0); // write master non-ack

  i2c_stop( &I2C_PIO);

  return data;

ACK_ERROR:
  i2c_stop( &I2C_PIO);
  return rv;

}
#endif
#if 0
unsigned i2c_read( unsigned char i2c_read_address,  unsigned char i2c_read_reg){
  int i;
  int rv;
  unsigned data;

 
  i2c_start(&I2C_PIO); 
  for(i=6;i>=0;i--){
    i2c_bit_write( &I2C_PIO, (i2c_read_address>>i)&1);
  }
    i2c_bit_write( &I2C_PIO, 1); // read command

    rv = i2c_ack_sense( &I2C_PIO); // sense ack
if(rv) printf("Error:I2C RD ack access3\n"); // for debug

  data = 0;
  for(i=7;i>=0;i--){
    data = data << 1;
    data |= i2c_ack_sense( &I2C_PIO) &1;
  }

    i2c_bit_write( &I2C_PIO, 1); // write master non-ack

  i2c_stop( &I2C_PIO);

  return data;
}
#endif


/* Set up Hardware addresses for I2C PIO ports */
/* I2C 各ポートアドレスの設定 */
void init_i2c() {
  i2c_setup_hw( &I2C_PIO, AV_I2C_DATA_PIO_BASE, AV_I2C_CLK_PIO_BASE);
}
