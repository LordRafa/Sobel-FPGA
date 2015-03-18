derive_pll_clocks -create_base_clocks
derive_clock_uncertainty

# JTAG Signal Constraints constrain the TCK port
#create_clock -name tck -period 100 [get_ports altera_reserved_tck]
# Cut all paths to and from tck
set_clock_groups -asynchronous -group [get_clocks altera_reserved_tck]
# Constrain the TDI port
set_input_delay -clock altera_reserved_tck -clock_fall 1 [get_ports altera_reserved_tdi]
# Constrain the TMS port
set_input_delay -clock altera_reserved_tck -clock_fall 1 [get_ports altera_reserved_tms]
# Constrain the TDO port
set_output_delay -clock altera_reserved_tck -clock_fall 1 [get_ports altera_reserved_tdo]
## Cutting the input reset path because Qsys synchronizes the reset input
set_false_path -from [get_ports top_reset_n]



set LCD_Base_Clock SistemaPrincipal_instance|clk_video|sd1|pll7|clk[1]
set LCD_Clock SistemaPrincipal_instance|clk_video|sd1|pll7|clk[0]

set DDR_Controller_Clock *|ddr_sdram|*|*|*|clk|pll|altpll_component|auto_generated|pll1|clk[1]
set DDR_Local_Clock      *|ddr_sdram|*|*|*|clk|pll|altpll_component|auto_generated|pll1|clk[2]


#### False Paths

set_false_path -from [get_clocks $LCD_Base_Clock] -to [get_clocks $DDR_Controller_Clock]
set_false_path -from [get_clocks $DDR_Controller_Clock] -to [get_clocks $LCD_Base_Clock]

set_false_path -from [get_clocks {top_clkin_50}] -to [get_clocks $DDR_Controller_Clock]
set_false_path -from [get_clocks $DDR_Controller_Clock] -to [get_clocks {top_clkin_50}]

set_false_path -from [get_clocks {top_clkin_50}] -to [get_clocks $DDR_Local_Clock]
set_false_path -from [get_clocks $DDR_Local_Clock] -to [get_clocks {top_clkin_50}]

#### Video input

create_clock -period 37.000 -name top_HC_TD_27MHZ [get_ports {top_HC_TD_27MHZ}]
set_false_path -from [get_clocks $DDR_Controller_Clock] -to top_HC_TD_27MHZ
set_false_path -from top_HC_TD_27MHZ -to [get_clocks $DDR_Controller_Clock]
set_input_delay -clock top_HC_TD_27MHZ -clock_fall  -min -3.4 [get_ports {top_HC_TD_D*}]
set_input_delay -clock top_HC_TD_27MHZ -clock_fall -max 4.6 [get_ports {top_HC_TD_D*}]

#### LCD output

create_generated_clock -name top_clk_to_offchip_video \
		-source [get_pins $LCD_Clock] \
		-divide_by 1 \
		[get_ports top_clk_to_offchip_video]

set_output_delay -clock [get_clocks top_clk_to_offchip_video] \
		-max 1.500 \
		[get_ports {top_HC_LCD_DATA* top_HC_DEN top_HC_HD top_HC_VD} ]

set_output_delay -clock [get_clocks top_clk_to_offchip_video] \
		-min 0.7 \
		[get_ports {top_HC_LCD_DATA* top_HC_DEN top_HC_HD top_HC_VD} ]
