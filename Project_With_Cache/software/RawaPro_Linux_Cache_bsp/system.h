/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu' in SOPC Builder design 'SistemaPrincipal'
 * SOPC Builder design path: ../../SistemaPrincipal.sopcinfo
 *
 * Generated: Wed Apr 24 16:47:43 WEST 2013
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_qsys"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0xc000820
#define ALT_CPU_CPU_FREQ 150000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1c
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 1024
#define ALT_CPU_EXCEPTION_ADDR 0x20
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 150000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0x1c
#define ALT_CPU_NAME "cpu"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_RESET_ADDR 0x0


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0xc000820
#define NIOS2_CPU_FREQ 150000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x1c
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 1024
#define NIOS2_EXCEPTION_ADDR 0x20
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 0x1c
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_RESET_ADDR 0x0


/*
 * Custom instruction macros
 *
 */

#define ALT_CI_NIOS_CUSTOM_INSTR_FLOATING_POINT_0(n,A,B) __builtin_custom_inii(ALT_CI_NIOS_CUSTOM_INSTR_FLOATING_POINT_0_N+(n&ALT_CI_NIOS_CUSTOM_INSTR_FLOATING_POINT_0_N_MASK),(A),(B))
#define ALT_CI_NIOS_CUSTOM_INSTR_FLOATING_POINT_0_N 0xfc
#define ALT_CI_NIOS_CUSTOM_INSTR_FLOATING_POINT_0_N_MASK ((1<<2)-1)
#define ALT_CI_SOBEL_INSTRUCTION_SET(n,A,B) __builtin_custom_inii(ALT_CI_SOBEL_INSTRUCTION_SET_N+(n&ALT_CI_SOBEL_INSTRUCTION_SET_N_MASK),(A),(B))
#define ALT_CI_SOBEL_INSTRUCTION_SET_N 0x4
#define ALT_CI_SOBEL_INSTRUCTION_SET_N_MASK ((1<<2)-1)


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_PERFORMANCE_COUNTER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_QSYS
#define __ALTERA_NIOS_CUSTOM_INSTR_FLOATING_POINT
#define __ALTMEMDDR
#define __ALTPLL
#define __ALT_VIP_VFR
#define __SOBEL_INSTRUCTION_SET


/*
 * SistemaVideo_FrameReader configuration
 *
 */

#define ALT_MODULE_CLASS_SistemaVideo_FrameReader alt_vip_vfr
#define SISTEMAVIDEO_FRAMEREADER_BASE 0xc001400
#define SISTEMAVIDEO_FRAMEREADER_IRQ 0
#define SISTEMAVIDEO_FRAMEREADER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SISTEMAVIDEO_FRAMEREADER_NAME "/dev/SistemaVideo_FrameReader"
#define SISTEMAVIDEO_FRAMEREADER_SPAN 128
#define SISTEMAVIDEO_FRAMEREADER_TYPE "alt_vip_vfr"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone III"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart"
#define ALT_STDERR_BASE 0x2000130
#define ALT_STDERR_DEV jtag_uart
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart"
#define ALT_STDIN_BASE 0x2000130
#define ALT_STDIN_DEV jtag_uart
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart"
#define ALT_STDOUT_BASE 0x2000130
#define ALT_STDOUT_DEV jtag_uart
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "SistemaPrincipal"


/*
 * av_i2c_clk_pio configuration
 *
 */

#define ALT_MODULE_CLASS_av_i2c_clk_pio altera_avalon_pio
#define AV_I2C_CLK_PIO_BASE 0x2000100
#define AV_I2C_CLK_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define AV_I2C_CLK_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define AV_I2C_CLK_PIO_CAPTURE 0
#define AV_I2C_CLK_PIO_DATA_WIDTH 1
#define AV_I2C_CLK_PIO_DO_TEST_BENCH_WIRING 0
#define AV_I2C_CLK_PIO_DRIVEN_SIM_VALUE 0x0
#define AV_I2C_CLK_PIO_EDGE_TYPE "NONE"
#define AV_I2C_CLK_PIO_FREQ 50000000u
#define AV_I2C_CLK_PIO_HAS_IN 0
#define AV_I2C_CLK_PIO_HAS_OUT 1
#define AV_I2C_CLK_PIO_HAS_TRI 0
#define AV_I2C_CLK_PIO_IRQ -1
#define AV_I2C_CLK_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define AV_I2C_CLK_PIO_IRQ_TYPE "NONE"
#define AV_I2C_CLK_PIO_NAME "/dev/av_i2c_clk_pio"
#define AV_I2C_CLK_PIO_RESET_VALUE 0x0
#define AV_I2C_CLK_PIO_SPAN 16
#define AV_I2C_CLK_PIO_TYPE "altera_avalon_pio"


/*
 * av_i2c_data_pio configuration
 *
 */

#define ALT_MODULE_CLASS_av_i2c_data_pio altera_avalon_pio
#define AV_I2C_DATA_PIO_BASE 0x2000090
#define AV_I2C_DATA_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define AV_I2C_DATA_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define AV_I2C_DATA_PIO_CAPTURE 0
#define AV_I2C_DATA_PIO_DATA_WIDTH 1
#define AV_I2C_DATA_PIO_DO_TEST_BENCH_WIRING 1
#define AV_I2C_DATA_PIO_DRIVEN_SIM_VALUE 0x0
#define AV_I2C_DATA_PIO_EDGE_TYPE "NONE"
#define AV_I2C_DATA_PIO_FREQ 50000000u
#define AV_I2C_DATA_PIO_HAS_IN 0
#define AV_I2C_DATA_PIO_HAS_OUT 0
#define AV_I2C_DATA_PIO_HAS_TRI 1
#define AV_I2C_DATA_PIO_IRQ -1
#define AV_I2C_DATA_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define AV_I2C_DATA_PIO_IRQ_TYPE "NONE"
#define AV_I2C_DATA_PIO_NAME "/dev/av_i2c_data_pio"
#define AV_I2C_DATA_PIO_RESET_VALUE 0x0
#define AV_I2C_DATA_PIO_SPAN 16
#define AV_I2C_DATA_PIO_TYPE "altera_avalon_pio"


/*
 * av_reset_pio configuration
 *
 */

#define ALT_MODULE_CLASS_av_reset_pio altera_avalon_pio
#define AV_RESET_PIO_BASE 0x2000110
#define AV_RESET_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define AV_RESET_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define AV_RESET_PIO_CAPTURE 0
#define AV_RESET_PIO_DATA_WIDTH 1
#define AV_RESET_PIO_DO_TEST_BENCH_WIRING 0
#define AV_RESET_PIO_DRIVEN_SIM_VALUE 0x0
#define AV_RESET_PIO_EDGE_TYPE "NONE"
#define AV_RESET_PIO_FREQ 50000000u
#define AV_RESET_PIO_HAS_IN 0
#define AV_RESET_PIO_HAS_OUT 1
#define AV_RESET_PIO_HAS_TRI 0
#define AV_RESET_PIO_IRQ -1
#define AV_RESET_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define AV_RESET_PIO_IRQ_TYPE "NONE"
#define AV_RESET_PIO_NAME "/dev/av_reset_pio"
#define AV_RESET_PIO_RESET_VALUE 0x0
#define AV_RESET_PIO_SPAN 16
#define AV_RESET_PIO_TYPE "altera_avalon_pio"


/*
 * clk_video configuration
 *
 */

#define ALT_MODULE_CLASS_clk_video altpll
#define CLK_VIDEO_BASE 0xc001350
#define CLK_VIDEO_IRQ -1
#define CLK_VIDEO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CLK_VIDEO_NAME "/dev/clk_video"
#define CLK_VIDEO_SPAN 16
#define CLK_VIDEO_TYPE "altpll"


/*
 * ddr_sdram configuration
 *
 */

#define ALT_MODULE_CLASS_ddr_sdram altmemddr
#define DDR_SDRAM_BASE 0x0
#define DDR_SDRAM_IRQ -1
#define DDR_SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DDR_SDRAM_NAME "/dev/ddr_sdram"
#define DDR_SDRAM_SPAN 33554432
#define DDR_SDRAM_TYPE "altmemddr"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart altera_avalon_jtag_uart
#define JTAG_UART_BASE 0x2000130
#define JTAG_UART_IRQ 10
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/jtag_uart"
#define JTAG_UART_READ_DEPTH 32
#define JTAG_UART_READ_THRESHOLD 4
#define JTAG_UART_SPAN 8
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 32
#define JTAG_UART_WRITE_THRESHOLD 4


/*
 * key_pio configuration
 *
 */

#define ALT_MODULE_CLASS_key_pio altera_avalon_pio
#define KEY_PIO_BASE 0x2000050
#define KEY_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define KEY_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define KEY_PIO_CAPTURE 1
#define KEY_PIO_DATA_WIDTH 8
#define KEY_PIO_DO_TEST_BENCH_WIRING 0
#define KEY_PIO_DRIVEN_SIM_VALUE 0x0
#define KEY_PIO_EDGE_TYPE "RISING"
#define KEY_PIO_FREQ 50000000u
#define KEY_PIO_HAS_IN 1
#define KEY_PIO_HAS_OUT 0
#define KEY_PIO_HAS_TRI 0
#define KEY_PIO_IRQ 2
#define KEY_PIO_IRQ_INTERRUPT_CONTROLLER_ID 0
#define KEY_PIO_IRQ_TYPE "EDGE"
#define KEY_PIO_NAME "/dev/key_pio"
#define KEY_PIO_RESET_VALUE 0x0
#define KEY_PIO_SPAN 16
#define KEY_PIO_TYPE "altera_avalon_pio"


/*
 * lcd_spi_en configuration
 *
 */

#define ALT_MODULE_CLASS_lcd_spi_en altera_avalon_pio
#define LCD_SPI_EN_BASE 0x2000070
#define LCD_SPI_EN_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_SPI_EN_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_SPI_EN_CAPTURE 0
#define LCD_SPI_EN_DATA_WIDTH 1
#define LCD_SPI_EN_DO_TEST_BENCH_WIRING 0
#define LCD_SPI_EN_DRIVEN_SIM_VALUE 0x0
#define LCD_SPI_EN_EDGE_TYPE "NONE"
#define LCD_SPI_EN_FREQ 50000000u
#define LCD_SPI_EN_HAS_IN 0
#define LCD_SPI_EN_HAS_OUT 1
#define LCD_SPI_EN_HAS_TRI 0
#define LCD_SPI_EN_IRQ -1
#define LCD_SPI_EN_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_SPI_EN_IRQ_TYPE "NONE"
#define LCD_SPI_EN_NAME "/dev/lcd_spi_en"
#define LCD_SPI_EN_RESET_VALUE 0x0
#define LCD_SPI_EN_SPAN 16
#define LCD_SPI_EN_TYPE "altera_avalon_pio"


/*
 * lcd_spi_scl configuration
 *
 */

#define ALT_MODULE_CLASS_lcd_spi_scl altera_avalon_pio
#define LCD_SPI_SCL_BASE 0x2000060
#define LCD_SPI_SCL_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_SPI_SCL_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_SPI_SCL_CAPTURE 0
#define LCD_SPI_SCL_DATA_WIDTH 1
#define LCD_SPI_SCL_DO_TEST_BENCH_WIRING 0
#define LCD_SPI_SCL_DRIVEN_SIM_VALUE 0x0
#define LCD_SPI_SCL_EDGE_TYPE "NONE"
#define LCD_SPI_SCL_FREQ 50000000u
#define LCD_SPI_SCL_HAS_IN 0
#define LCD_SPI_SCL_HAS_OUT 1
#define LCD_SPI_SCL_HAS_TRI 0
#define LCD_SPI_SCL_IRQ -1
#define LCD_SPI_SCL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_SPI_SCL_IRQ_TYPE "NONE"
#define LCD_SPI_SCL_NAME "/dev/lcd_spi_scl"
#define LCD_SPI_SCL_RESET_VALUE 0x0
#define LCD_SPI_SCL_SPAN 16
#define LCD_SPI_SCL_TYPE "altera_avalon_pio"


/*
 * lcd_spi_sdat configuration
 *
 */

#define ALT_MODULE_CLASS_lcd_spi_sdat altera_avalon_pio
#define LCD_SPI_SDAT_BASE 0x2000080
#define LCD_SPI_SDAT_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_SPI_SDAT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_SPI_SDAT_CAPTURE 0
#define LCD_SPI_SDAT_DATA_WIDTH 1
#define LCD_SPI_SDAT_DO_TEST_BENCH_WIRING 1
#define LCD_SPI_SDAT_DRIVEN_SIM_VALUE 0x0
#define LCD_SPI_SDAT_EDGE_TYPE "NONE"
#define LCD_SPI_SDAT_FREQ 50000000u
#define LCD_SPI_SDAT_HAS_IN 0
#define LCD_SPI_SDAT_HAS_OUT 0
#define LCD_SPI_SDAT_HAS_TRI 1
#define LCD_SPI_SDAT_IRQ -1
#define LCD_SPI_SDAT_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_SPI_SDAT_IRQ_TYPE "NONE"
#define LCD_SPI_SDAT_NAME "/dev/lcd_spi_sdat"
#define LCD_SPI_SDAT_RESET_VALUE 0x0
#define LCD_SPI_SDAT_SPAN 16
#define LCD_SPI_SDAT_TYPE "altera_avalon_pio"


/*
 * led_pio configuration
 *
 */

#define ALT_MODULE_CLASS_led_pio altera_avalon_pio
#define LED_PIO_BASE 0x2000040
#define LED_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define LED_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_PIO_CAPTURE 0
#define LED_PIO_DATA_WIDTH 8
#define LED_PIO_DO_TEST_BENCH_WIRING 0
#define LED_PIO_DRIVEN_SIM_VALUE 0x0
#define LED_PIO_EDGE_TYPE "NONE"
#define LED_PIO_FREQ 50000000u
#define LED_PIO_HAS_IN 0
#define LED_PIO_HAS_OUT 1
#define LED_PIO_HAS_TRI 0
#define LED_PIO_IRQ -1
#define LED_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_PIO_IRQ_TYPE "NONE"
#define LED_PIO_NAME "/dev/led_pio"
#define LED_PIO_RESET_VALUE 0x0
#define LED_PIO_SPAN 16
#define LED_PIO_TYPE "altera_avalon_pio"


/*
 * performance_counter configuration
 *
 */

#define ALT_MODULE_CLASS_performance_counter altera_avalon_performance_counter
#define PERFORMANCE_COUNTER_BASE 0x2000420
#define PERFORMANCE_COUNTER_HOW_MANY_SECTIONS 1
#define PERFORMANCE_COUNTER_IRQ -1
#define PERFORMANCE_COUNTER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PERFORMANCE_COUNTER_NAME "/dev/performance_counter"
#define PERFORMANCE_COUNTER_SPAN 32
#define PERFORMANCE_COUNTER_TYPE "altera_avalon_performance_counter"


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid_qsys
#define SYSID_BASE 0x2000120
#define SYSID_ID 0
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1366810869
#define SYSID_TYPE "altera_avalon_sysid_qsys"


/*
 * timer configuration
 *
 */

#define ALT_MODULE_CLASS_timer altera_avalon_timer
#define TIMER_ALWAYS_RUN 0
#define TIMER_BASE 0x2000400
#define TIMER_COUNTER_SIZE 32
#define TIMER_FIXED_PERIOD 0
#define TIMER_FREQ 150000000u
#define TIMER_IRQ 1
#define TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_LOAD_VALUE 1499ull
#define TIMER_MULT 1.0E-6
#define TIMER_NAME "/dev/timer"
#define TIMER_PERIOD 10
#define TIMER_PERIOD_UNITS "us"
#define TIMER_RESET_OUTPUT 0
#define TIMER_SNAPSHOT 1
#define TIMER_SPAN 32
#define TIMER_TICKS_PER_SEC 100000u
#define TIMER_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_TYPE "altera_avalon_timer"

#endif /* __SYSTEM_H_ */
