`timescale 1 ps / 1 ps
module ram_w(
    input clk,
    input rst,

    output wire[ADD_WIDTH-1:0] ram_w_address,
    input ram_w_waitrequest,
    output wire[BYTE_ENABLE_WIDTH-1:0] ram_w_byteenable,
    output wire ram_w_write,
    output wire[DATA_WIDTH-1:0] ram_w_writedata,
    output wire[BURST_WIDTH_W-1:0] ram_w_burstcount,
	
	input [DATA_WIDTH-1:0] data_fifo_out,
	input data_valid_fifo_out,
	input start_fifo_out,
	input [ADD_WIDTH-1:0] address_fifo_out,
	input [DATA_WIDTH-1:0] n_burst_fifo_out,
	output wire bussy_fifo_out,
	output wire full_fifo_out,
	output wire [FIFO_DEPTH_LOG2:0] usedw_fifo_out
);
	parameter DATA_WIDTH = 32;
	parameter ADD_WIDTH = 32;
	parameter BYTE_ENABLE_WIDTH = 4; // derived parameter
	parameter MAX_BURST_COUNT_W = 32; // must be a multiple of 2 between 2 and 1024, when bursting is disabled this value must be set to 1
	parameter BURST_WIDTH_W = 5;
	parameter FIFO_DEPTH_LOG2 = 8;
	parameter FIFO_DEPTH = 256;
	
	reg write;
	wire set_write;
	wire reset_write;
	
	wire write_complete;
	
	reg [BURST_WIDTH_W:0] burst_write_n;
	wire write_burst_end;
	
	reg [DATA_WIDTH-1:0] out_n;

	reg [ADD_WIDTH-1:0] write_address;
	
	wire fifo_full;
	wire [FIFO_DEPTH_LOG2:0] fifo_used;
	
	scfifo master_to_st_fifo(
		.aclr(start_fifo_out),
		.clock(clk),
		
		.data(data_fifo_out),
		.wrreq(data_valid_fifo_out),

		.q(ram_w_writedata),
		.rdreq(write_complete),
		
		.full(fifo_full),
		.usedw(fifo_used[FIFO_DEPTH_LOG2-1:0])
	);
	defparam master_to_st_fifo.lpm_width = DATA_WIDTH;
	defparam master_to_st_fifo.lpm_numwords = FIFO_DEPTH;
	defparam master_to_st_fifo.lpm_widthu = FIFO_DEPTH_LOG2;
	defparam master_to_st_fifo.lpm_showahead = "ON";
	defparam master_to_st_fifo.use_eab = "ON";
	defparam master_to_st_fifo.add_ram_output_register = "ON";  // FIFO latency of 2
	defparam master_to_st_fifo.underflow_checking = "OFF";
	defparam master_to_st_fifo.overflow_checking = "OFF";

	always @(posedge clk or posedge rst) begin
		if (rst == 1) begin
			write <= 0;
		end else begin
			if (reset_write == 1) begin
				write <= 0;
			end else begin
				if (set_write == 1) begin
					write <= 1;
				end
			end
		end
	end
	
	always @(posedge clk or posedge rst) begin
		if (rst == 1) begin
			out_n <= 0;
		end else begin
			if (start_fifo_out == 1) begin
				out_n <= n_burst_fifo_out * MAX_BURST_COUNT_W;
			end else begin
				if (write_complete == 1) begin
					out_n <= out_n - 1;
				end
			end
		end
	end
	
	always @(posedge clk) begin
		if (start_fifo_out == 1) begin
			burst_write_n <= MAX_BURST_COUNT_W;
		end
		else begin
			if (write_burst_end == 1) begin
				burst_write_n <= MAX_BURST_COUNT_W;
			end else begin
				if (write_complete == 1) begin
					burst_write_n <= burst_write_n - 1;
				end
			end
		end
	end
	
	always @(posedge clk) begin
		if (start_fifo_out == 1) begin
			write_address <= address_fifo_out;
		end else begin
			if (write_burst_end == 1) begin
				write_address <= write_address + MAX_BURST_COUNT_W * BYTE_ENABLE_WIDTH;
			end
		end
	end
	
	assign write_complete = (write == 1) & (ram_w_waitrequest == 0);
	assign write_burst_end = (burst_write_n == 1) & (write_complete == 1);

	assign fifo_used[FIFO_DEPTH_LOG2] = fifo_full;

	assign set_write = (out_n != 0) & (fifo_used >= MAX_BURST_COUNT_W);
	assign reset_write = ((fifo_used <= MAX_BURST_COUNT_W) | (out_n == 1)) & (write_burst_end == 1);
	
	assign ram_w_address = write_address;
	assign ram_w_write = write;
	assign ram_w_byteenable = {BYTE_ENABLE_WIDTH{1'b1}};
	assign ram_w_burstcount = MAX_BURST_COUNT_W;
	
	assign bussy_fifo_out = out_n != 0;
	assign full_fifo_out = fifo_full;
	assign usedw_fifo_out = fifo_used;

endmodule
