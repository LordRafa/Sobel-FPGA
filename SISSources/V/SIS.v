/*
 * SIS.v
 *
 *  Created on: 09/10/2012
 *      Author: Lord_Rafa
 */

module SIS (
	input clk,
	input rst,

	output wire[ADD_WIDTH-1:0] ram_w_address,
	input ram_w_waitrequest,
	output wire[BYTE_ENABLE_WIDTH-1:0] ram_w_byteenable,
	output wire ram_w_write,
	output wire[DATA_WIDTH-1:0] ram_w_writedata,
	output wire[BURST_WIDTH_W-1:0] ram_w_burstcount,

	output wire[ADD_WIDTH-1:0] ram_r_address,
	input ram_r_waitrequest,
	input ram_r_readdatavalid,
	output wire[BYTE_ENABLE_WIDTH-1:0] ram_r_byteenable,
	output wire ram_r_read,
	input wire[DATA_WIDTH-1:0] ram_r_readdata,
	output wire[BURST_WIDTH_R-1:0] ram_r_burstcount,

	input [23:0] din_data,
	input din_valid,
	output wire din_ready,
	input wire din_sop,
	input wire din_eop,
	
	input cpu_clk,
	input cpu_rst,
	input cpu_clk_en,
	input cpu_start,
	output wire cpu_done,
	input[DATA_WIDTH-1:0] cpu_addr,
	input[DATA_WIDTH-1:0] cpu_addw,
	output wire[DATA_WIDTH-1:0] cpu_result,
	input [1:0] n
);

	parameter DATA_WIDTH = 32;
	parameter ADD_WIDTH = 32;
	parameter BURST_WIDTH_W = 5;
	parameter BURST_WIDTH_R = 6;
	parameter BYTE_ENABLE_WIDTH = 4; // derived parameter
	parameter FIFO_DEPTH_LOG2 = 8;

	wire [DATA_WIDTH-1:0] data_fifo_in;
	wire read_fifo_in;
	wire start_fifo_in;
	wire [ADD_WIDTH-1:0] address_fifo_in;
	wire [DATA_WIDTH-1:0] n_burst_fifo_in;
	wire bussy_fifo_in;
	wire empty_fifo_in;
	wire [FIFO_DEPTH_LOG2:0] usedw_fifo_in;
	
	wire [DATA_WIDTH-1:0] data_fifo_out;
	wire data_valid_fifo_out;
	wire start_fifo_out;
	wire [ADD_WIDTH-1:0] address_fifo_out;
	wire [DATA_WIDTH-1:0] n_burst_fifo_out;
	wire bussy_fifo_out;
	wire full_fifo_out;
	wire [FIFO_DEPTH_LOG2:0] usedw_fifo_out;
	
	wire [DATA_WIDTH-1:0] data_out_frame_writer;
	wire data_out_valid_frame_writer;

	wire [DATA_WIDTH-1:0] data_out_agrises;
	wire data_out_valid_agrises;
	
	wire [DATA_WIDTH-1:0] data_out_sobel;
	wire data_out_valid_sobel;
	
	wire read_agrises;
	wire read_sobel;
	
	wire reset_values;

	reg [1:0] init;
	reg run;

	reg valid;
	reg [DATA_WIDTH-1:0] bridge;
	
	wire framewriter_end;
	wire agrises_end;
	wire sobel_end;
	
	wire start_framewriter;
	wire start_agrises;
	wire start_sobel;
	
	wire[ADD_WIDTH-1:0] agrises_ram_r_address;
	wire[BYTE_ENABLE_WIDTH-1:0] agrises_ram_r_byteenable;
	wire agrises_ram_r_read;
	wire[BURST_WIDTH_R-1:0] agrises_ram_r_burstcount;
	
	wire[ADD_WIDTH-1:0] sobel_ram_r_address;
	wire[BYTE_ENABLE_WIDTH-1:0] sobel_ram_r_byteenable;
	wire sobel_ram_r_read;
	wire[BURST_WIDTH_R-1:0] sobel_ram_r_burstcount;

	ram_r ram_r_instance (
		.clk(clk),
		.rst(rst),

		.ram_r_address(agrises_ram_r_address),
		.ram_r_waitrequest(ram_r_waitrequest),
		.ram_r_readdatavalid(ram_r_readdatavalid),
		.ram_r_byteenable(agrises_ram_r_byteenable),
		.ram_r_read(agrises_ram_r_read),
		.ram_r_readdata(ram_r_readdata),
		.ram_r_burstcount(agrises_ram_r_burstcount),

		.data_fifo_in(data_fifo_in),
		.read_fifo_in(read_fifo_in),
		.start_fifo_in(start_fifo_in),
		.address_fifo_in(address_fifo_in),
		.n_burst_fifo_in(n_burst_fifo_in),
		.bussy_fifo_in(bussy_fifo_in),
		.empty_fifo_in(empty_fifo_in),
		.usedw_fifo_in(usedw_fifo_in)
	);
	
	ram_w ram_w_instance (
		.clk(clk),
		.rst(rst),

		.ram_w_address(ram_w_address),
		.ram_w_waitrequest(ram_w_waitrequest),
		.ram_w_byteenable(ram_w_byteenable),
		.ram_w_write(ram_w_write),
		.ram_w_writedata(ram_w_writedata),
		.ram_w_burstcount(ram_w_burstcount),

		.data_fifo_out(data_fifo_out),
		.data_valid_fifo_out(data_valid_fifo_out),
		.start_fifo_out(start_fifo_out),
		.address_fifo_out(address_fifo_out),
		.n_burst_fifo_out(n_burst_fifo_out),
		.bussy_fifo_out(bussy_fifo_out),
		.full_fifo_out(full_fifo_out),
		.usedw_fifo_out(usedw_fifo_out)
	);	

	FrameWriter FrameWriter_instance (
		.clk(clk),
		.rst(rst),

		.din_data(din_data),
		.din_valid(din_valid),
		.din_ready(din_ready),
		.din_sop(din_sop),
		.din_eop(din_eop),

		.data_fifo_out(data_out_frame_writer),
		.data_valid_fifo_out(data_out_valid_frame_writer),
		.usedw_fifo_out(usedw_fifo_out),

		.start(start_framewriter),
		.endf(framewriter_end)
	);
	
	AGrises AGrises_instance (
		.clk(clk),
		.rst(rst),

		.data_fifo_out(data_out_agrises),
		.data_valid_fifo_out(data_out_valid_agrises),
		.usedw_fifo_out(usedw_fifo_out),

		.data_fifo_in(data_fifo_in),
		.read_fifo_in(read_agrises),
		.usedw_fifo_in(usedw_fifo_in),

		.start(start_agrises),
		.endf(agrises_end)
	);
	
	Sobel Sobel_instance (
		.clk(clk),
		.rst(rst),

		.data_fifo_out(data_out_sobel),
		.data_valid_fifo_out(data_out_valid_sobel),
		.usedw_fifo_out(usedw_fifo_out),

		.ram_r_address(sobel_ram_r_address),
		.ram_r_waitrequest(ram_r_waitrequest),
		.ram_r_readdatavalid(ram_r_readdatavalid),
		.ram_r_byteenable(sobel_ram_r_byteenable),
		.ram_r_read(sobel_ram_r_read),
		.ram_r_readdata(ram_r_readdata),
		.ram_r_burstcount(sobel_ram_r_burstcount),

		.start(start_sobel),
		.endf(sobel_end),
		.base_add(cpu_addr)
	);
	
	// Inicializacion
	always @(negedge cpu_clk or posedge cpu_rst) begin
		if (cpu_rst == 1) begin
			init <= 2'd0;
		end else begin
			if ((cpu_clk_en == 1) && (cpu_start == 1)) begin
				init <= 2'd1;
			end else begin
				if ((bussy_fifo_out == 0) && (run == 1'd1)) begin
					init <= 2'd2;
				end else begin
					if ((init == 2'd2) && (run == 1'd0)) begin
						init <= 2'd3;
					end else begin
						if (cpu_done == 1) begin
							init <= 2'd0;
						end
					end
				end
			end
		end
	end
	
	always @(posedge clk) begin
		if (reset_values == 1) begin
			run <= 1;
		end else begin
			if (init == 2'd2) begin
				run <= 0;
			end
		end
	end
	
	assign data_fifo_out = (n == 0)? data_out_frame_writer : ((n == 1)? data_out_agrises : data_out_sobel);
	assign data_valid_fifo_out = (n == 0)? data_out_valid_frame_writer : ((n == 1)? data_out_valid_agrises : data_out_valid_sobel);
	assign start_fifo_out = reset_values;
	assign address_fifo_out = cpu_addw;
	assign n_burst_fifo_out = 12000;

	assign read_fifo_in = (n == 0)? 0 : ((n == 1)? read_agrises : read_sobel);	
	assign start_fifo_in = reset_values;
	assign address_fifo_in = cpu_addr;
	assign n_burst_fifo_in = (n != 1)? 0 : 12000;
	
	assign ram_r_address = (n == 1)? agrises_ram_r_address : sobel_ram_r_address;
	assign ram_r_byteenable = (n == 1)? agrises_ram_r_byteenable : sobel_ram_r_byteenable;
	assign ram_r_read = (n == 1)? agrises_ram_r_read : sobel_ram_r_read;
	assign ram_r_burstcount = (n == 1)? agrises_ram_r_burstcount : sobel_ram_r_burstcount;
	
	assign start_framewriter = (reset_values == 1) & (n == 0);
	assign start_agrises = (reset_values == 1) & (n == 1);
	assign start_sobel = (reset_values == 1) & (n == 2);

	assign reset_values = ((init == 1) & (run == 0));

	assign cpu_done = (init == 2'd3);
	assign cpu_result = 0;

endmodule
