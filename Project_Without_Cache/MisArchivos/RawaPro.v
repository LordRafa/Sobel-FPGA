// NEEK_VIP_demo_LCD_SVGA demo top design
// Rev.1: jtag_uart is replaced with uart1
//
//Legal Notice: (C)2008 Altera Corporation. All rights reserved.  Your
//use of Altera Corporation's design tools, logic functions and other
//software and tools, and its AMPP partner logic functions, and any
//output files any of the foregoing (including device programming or
//simulation files), and any associated documentation or information are
//expressly subject to the terms and conditions of the Altera Program
//License Subscription Agreement or other applicable license agreement,
//including, without limitation, that your use is for the sole purpose
//of programming logic devices manufactured by Altera and sold by Altera
//or its authorized distributors.  Please refer to the applicable
//agreement for further details.

// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module RawaPro (
                                      // inputs:
                                       top_HC_ADC_DOUT,
                                       top_HC_ADC_PENIRQ_N,
                                       top_HC_RX_CLK,
                                       top_HC_RX_COL,
                                       top_HC_RX_CRS,
                                       top_HC_RX_D,
                                       top_HC_RX_DV,
                                       top_HC_RX_ERR,
                                       top_HC_SD_DAT,
                                       top_HC_TX_CLK,
                                       top_HC_UART_RXD,
                                       top_button,
                                       top_clkin_50,
                                       top_reset_n,

                                      // outputs:
                                       top_HC_ADC_CS_N,
                                       top_HC_ADC_DCLK,
                                       top_HC_ADC_DIN,
                                       top_HC_DEN,
                                       top_HC_ETH_RESET_N,
                                       top_HC_HD,
                                       top_HC_ID_I2CDAT,
                                       top_HC_ID_I2CSCL,
                                       top_HC_LCD_DATA,
                                       top_HC_MDC,
                                       top_HC_MDIO,
                                       top_HC_SCEN,
                                       top_HC_SDA,
                                       top_HC_SD_CLK,
                                       top_HC_SD_CMD,
                                       top_HC_SD_DAT3,
                                       top_HC_TX_D,
                                       top_HC_TX_EN,
                                       top_HC_UART_TXD,
                                       top_HC_VD,
                                       top_clk_to_offchip_video,
                                       top_flash_cs_n,
                                       top_flash_oe_n,
                                       top_flash_reset_n,
                                       top_flash_ssram_a,
                                       top_flash_ssram_d,
                                       top_flash_wr_n,
                                       top_led,
                                       top_mem_addr,
                                       top_mem_ba,
                                       top_mem_cas_n,
                                       top_mem_cke,
                                       top_mem_clk,
                                       top_mem_clk_n,
                                       top_mem_cs_n,
                                       top_mem_dm,
                                       top_mem_dq,
                                       top_mem_dqs,
                                       top_mem_ras_n,
                                       top_mem_we_n,
                                       top_ssram_adsc_n,
                                       top_ssram_bw_n,
                                       top_ssram_bwe_n,
                                       top_ssram_ce_n,
                                       top_ssram_clk,
                                       top_ssram_oe_n
,top_HC_TD_D
,top_HC_TD_HS
,top_HC_TD_VS
,top_HC_TD_27MHZ
,top_HC_TD_RESET
,top_HC_I2C_SCLK
,top_HC_I2C_SDAT



/*, top_HC_VGA_DATA
, top_HC_VGA_CLOCK
, top_HC_VGA_HS
, top_HC_VGA_VS
, top_HC_VGA_BLANK
, top_HC_VGA_SYNC*/

, top_HC_GREST
                                    )
;

  output           top_HC_ADC_CS_N;
  output           top_HC_ADC_DCLK;
  output           top_HC_ADC_DIN;
  output           top_HC_DEN;
  output           top_HC_ETH_RESET_N;
  output           top_HC_HD;
  inout            top_HC_ID_I2CDAT;
  output           top_HC_ID_I2CSCL;
  output  [  7: 0] top_HC_LCD_DATA;
  output           top_HC_MDC;
  inout            top_HC_MDIO;
  output           top_HC_SCEN;
  inout            top_HC_SDA;
  output           top_HC_SD_CLK;
  output           top_HC_SD_CMD;
  output           top_HC_SD_DAT3;
  output  [  3: 0] top_HC_TX_D;
  output           top_HC_TX_EN;
  output           top_HC_UART_TXD;
  output           top_HC_VD;
  output           top_clk_to_offchip_video;
  output           top_flash_cs_n;
  output           top_flash_oe_n;
  output           top_flash_reset_n;
  output  [ 23: 1] top_flash_ssram_a;
  inout   [ 31: 0] top_flash_ssram_d;
  output           top_flash_wr_n;
  output  [  3: 0] top_led;
  output  [ 12: 0] top_mem_addr;
  output  [  1: 0] top_mem_ba;
  output           top_mem_cas_n;
  output           top_mem_cke;
  inout            top_mem_clk;
  inout            top_mem_clk_n;
  output           top_mem_cs_n;
  output  [  1: 0] top_mem_dm;
  inout   [ 15: 0] top_mem_dq;
  inout   [  1: 0] top_mem_dqs;
  output           top_mem_ras_n;
  output           top_mem_we_n;
  output           top_ssram_adsc_n;
  output  [  3: 0] top_ssram_bw_n;
  output           top_ssram_bwe_n;
  output           top_ssram_ce_n;
  output           top_ssram_clk;
  output           top_ssram_oe_n;
  input            top_HC_ADC_DOUT;
  input            top_HC_ADC_PENIRQ_N;
  input            top_HC_RX_CLK;
  input            top_HC_RX_COL;
  input            top_HC_RX_CRS;
  input   [  3: 0] top_HC_RX_D;
  input            top_HC_RX_DV;
  input            top_HC_RX_ERR;
  input            top_HC_SD_DAT;
  input            top_HC_TX_CLK;
  input            top_HC_UART_RXD;
  input   [  3: 0] top_button;
  input            top_clkin_50;
  input            top_reset_n;



//TV Decoder
  input	[7:0]	top_HC_TD_D;
  input			top_HC_TD_HS;
  input			top_HC_TD_VS;
  input			top_HC_TD_27MHZ;
  output		top_HC_TD_RESET;

// Audio and TV decoder I2C
  output top_HC_I2C_SCLK;
  inout  top_HC_I2C_SDAT;


  /*output [9:0] top_HC_VGA_DATA;
  output top_HC_VGA_CLOCK;
  output top_HC_VGA_HS;
  output top_HC_VGA_VS;
  output top_HC_VGA_BLANK;
  output top_HC_VGA_SYNC;*/

  output top_HC_GREST;

  wire             top_CDn_to_the_el_camino_sd_card_controller;
  wire             top_HC_ADC_CS_N;
  wire             top_HC_ADC_DCLK;
  wire             top_HC_ADC_DIN;
  wire             top_HC_DEN;
  wire             top_HC_ETH_RESET_N;
  wire             top_HC_HD;
  wire             top_HC_ID_I2CDAT;
  wire             top_HC_ID_I2CSCL;
  wire    [  7: 0] top_HC_LCD_DATA;
  wire             top_HC_MDC;
  wire             top_HC_MDIO;
  wire             top_HC_SCEN;
  wire             top_HC_SDA;
  wire             top_HC_SD_CLK;
  wire             top_HC_SD_CMD;
  wire             top_HC_SD_DAT3;
  wire    [  3: 0] top_HC_TX_D;
  wire             top_HC_TX_EN;
  wire             top_HC_UART_TXD;
  wire             top_HC_VD;
  wire             top_SCLK_from_the_touch_panel_spi;
  wire             top_SS_n_from_the_touch_panel_spi;
  wire             top_WP_to_the_el_camino_sd_card_controller;
  wire             top_clk_to_offchip_video;
  wire             top_ddr_sdram_aux_full_rate_clk_out;
  wire             top_ddr_sdram_aux_half_rate_clk_out;
  wire             top_ddr_sdram_phy_clk_out;
  wire             top_flash_cs_n;
  wire             top_flash_oe_n;
  wire             top_flash_reset_n;
  wire    [ 23: 1] top_flash_ssram_a;
  wire    [ 31: 0] top_flash_ssram_d;
  wire             top_flash_wr_n;
  wire    [  3: 0] top_in_port_to_the_button_pio;
  wire    [  3: 0] top_led;
  wire             top_local_init_done_from_the_ddr_sdram;
  wire             top_local_refresh_ack_from_the_ddr_sdram;
  wire             top_local_wdata_req_from_the_ddr_sdram;
  wire    [ 12: 0] top_mem_addr;
  wire    [  1: 0] top_mem_ba;
  wire             top_mem_cas_n;
  wire             top_mem_cke;
  wire             top_mem_clk;
  wire             top_mem_clk_n;
  wire             top_mem_cs_n;
  wire    [  1: 0] top_mem_dm;
  wire    [ 15: 0] top_mem_dq;
  wire    [  1: 0] top_mem_dqs;
  wire             top_mem_ras_n;
  wire             top_mem_we_n;
  wire             top_out_port_from_the_lcd_i2c_en;
  wire             top_out_port_from_the_lcd_i2c_scl;
  wire             top_peripheral_clk;
  wire             top_remote_update_clk;
  wire             top_reset_phy_clk_n_from_the_ddr_sdram;
  wire             top_ssram_adsc_n;
  wire    [  3: 0] top_ssram_bw_n;
  wire             top_ssram_bwe_n;
  wire             top_ssram_ce_n;
  wire             top_ssram_clk;
  wire             top_ssram_oe_n;

  wire h_sync;
  wire v_sync;

  wire video_in_valid;
  wire video_in_locked;
  wire [7:0] video_in_data;

  /*wire vga_base_clock;
  wire vga_clock; // *3 of the base clock
  wire [23:0] VGA_DATA;
  wire VGA_BLANK;
  wire VGA_HS;
  wire VGA_VS;*/

  wire lcd_base_clock;
  wire lcd_clock; // *3 of the base clock
  wire [23:0] LCD_DATA;
  wire LCD_BLANK;
  wire LCD_HS;
  wire LCD_VS;

wire clk_100;
wire clk_33;
wire clk_120;
wire clk_40;

wire [3:0] led_pio_wire;
wire dmy;
//wire pll_locked_input_in_reset_reset_n;
//wire locked_from_the_altpll_0;

//assign pll_locked_input_in_reset_reset_n = locked_from_the_altpll_0;

  SistemaPrincipal SistemaPrincipal_instance (
		//***************************Reloj Principal***************************
		.sys_clk_clk                                (top_clkin_50),
		.reset_reset_n                              (top_reset_n),
		//---------------------------------------------------------------------

		//**************************Relojes de Salida**************************
		.clk_100_clk(clk_100),
      .clk_33_clk(clk_33),
		.altpll_0_areset_conduit_export(0),
		//--------------------------------------------------------------------- 

		//**************************Entrada de Video***************************
      .bidir_port_to_and_from_the_av_i2c_data_pio (top_HC_I2C_SDAT),
      .out_port_from_the_av_i2c_clk_pio           (top_HC_I2C_SCLK),
		.out_port_from_the_td_reset_pio             (top_HC_TD_RESET),
		
      .video_in_vid_clk                           (top_HC_TD_27MHZ),
      .video_in_vid_data                          (video_in_data),
      .video_in_vid_datavalid                     (video_in_valid),
      .video_in_vid_locked                        (video_in_locked),
		//---------------------------------------------------------------------
		
		//***************************Salida de Video***************************
      .out_port_from_the_lcd_i2c_en               (top_out_port_from_the_lcd_i2c_en),
      .out_port_from_the_lcd_i2c_scl              (top_out_port_from_the_lcd_i2c_scl),
		.bidir_port_to_and_from_the_lcd_i2c_sdat    (top_HC_SDA),
		
      .video_out_vid_clk                          (lcd_base_clock),
      .video_out_vid_data                         (LCD_DATA),
      .video_out_vid_datavalid                    (LCD_BLANK),
      .video_out_vid_h_sync                       (LCD_HS),
      .video_out_vid_v_sync                       (LCD_VS),
		//---------------------------------------------------------------------
		
		//*****************************Memoria RAM*****************************
      .ddr_sdram_memory_mem_addr                  (top_mem_addr),
      .ddr_sdram_memory_mem_ba                    (top_mem_ba),
      .ddr_sdram_memory_mem_cas_n                 (top_mem_cas_n),
      .ddr_sdram_memory_mem_cke                   (top_mem_cke),
      .ddr_sdram_memory_mem_clk_n                 (top_mem_clk_n),
      .ddr_sdram_memory_mem_clk                   (top_mem_clk),
      .ddr_sdram_memory_mem_cs_n                  (top_mem_cs_n),
      .ddr_sdram_memory_mem_dm                    (top_mem_dm),
      .ddr_sdram_memory_mem_dq                    (top_mem_dq),
      .ddr_sdram_memory_mem_dqs                   (top_mem_dqs),
      .ddr_sdram_memory_mem_ras_n                 (top_mem_ras_n),
      .ddr_sdram_memory_mem_we_n                  (top_mem_we_n),

      .ddr_sdram_external_connection_reset_phy_clk_n (top_reset_phy_clk_n_from_the_ddr_sdram),
		//---------------------------------------------------------------------
				
		//********************************Otros********************************
		.key_pio_export(top_in_port_to_the_button_pio),
		.led_pio_export(led_pio_wire)
		//---------------------------------------------------------------------
      
    );
	 
  assign video_in_data = top_HC_TD_D;

  assign video_in_valid = 1'b1;
  assign video_in_locked = 1'b1;

  /*vga_serial u_vga_serial( 
    .data(VGA_DATA), .blank(VGA_BLANK), .hs(VGA_HS), .vs(VGA_VS),
    .clk3(vga_clock), .data3(top_HC_VGA_DATA[9:2]), .blank3(top_HC_VGA_BLANK), .hs3(top_HC_VGA_HS), .vs3(top_HC_VGA_VS)
  );*/

  vga_serial u_lcd_serial( 
    .data(LCD_DATA), .blank(LCD_BLANK), .hs(LCD_HS), .vs(LCD_VS),
    .clk3(lcd_clock), .data3(top_HC_LCD_DATA), .blank3(top_HC_DEN), .hs3(h_sync), .vs3(v_sync)
  );



  /*assign vga_clock = clk_100;
  assign vga_base_clock = clk_33;*/

  assign lcd_clock = clk_100;
  assign lcd_base_clock = clk_33;




  assign top_clk_to_offchip_video = lcd_clock;
  /*assign top_HC_VGA_CLOCK = vga_clock;

  assign top_HC_VGA_SYNC = 1'b1;*/

  assign top_HC_HD = h_sync;
  assign top_HC_VD = v_sync;

  assign top_CDn_to_the_el_camino_sd_card_controller = 1'b0;
  assign top_WP_to_the_el_camino_sd_card_controller = 1'b0;

  assign top_HC_SCEN = top_out_port_from_the_lcd_i2c_en;
  assign top_HC_ADC_DCLK = ~top_out_port_from_the_lcd_i2c_en ? top_out_port_from_the_lcd_i2c_scl: 0;


//  assign top_HC_TD_RESET = 1'b1; 

  assign top_HC_GREST = 1'b1;
  assign top_led = led_pio_wire;

  assign top_HC_ETH_RESET_N = 1'b0;
  assign top_in_port_to_the_button_pio = top_button;

endmodule

