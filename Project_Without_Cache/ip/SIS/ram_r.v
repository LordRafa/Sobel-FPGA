`timescale 1 ps / 1 ps
module ram_r(
    input clk,
    input rst,

    output wire[ADD_WIDTH-1:0] ram_r_address,
    input ram_r_waitrequest,
	input ram_r_readdatavalid,
    output wire[BYTE_ENABLE_WIDTH-1:0] ram_r_byteenable,
    output wire ram_r_read,
    input wire[DATA_WIDTH-1:0] ram_r_readdata,
    output wire[BURST_WIDTH_R-1:0] ram_r_burstcount,
	
	output wire [DATA_WIDTH-1:0] data_fifo_in,
	input read_fifo_in,
	input start_fifo_in,
	input [ADD_WIDTH-1:0] address_fifo_in,
	input [DATA_WIDTH-1:0] n_burst_fifo_in,
	output wire bussy_fifo_in,
	output wire empty_fifo_in,
	output wire [FIFO_DEPTH_LOG2:0] usedw_fifo_in
);
	parameter DATA_WIDTH = 32;
	parameter ADD_WIDTH = 32;
	parameter BYTE_ENABLE_WIDTH = 4; // derived parameter
	parameter MAX_BURST_COUNT_R = 32; // must be a multiple of 2 between 2 and 1024, when bursting is disabled this value must be set to 1
	parameter BURST_WIDTH_R = 6;
	parameter FIFO_DEPTH_LOG2 = 8;
	parameter FIFO_DEPTH = 256;
	
	wire read_complete;
	reg [DATA_WIDTH-1:0] reads_pending;
	wire read_burst_end;
	reg next_r;
	wire too_many_reads_pending;
	
	reg [ADD_WIDTH-1:0] read_address;
	
	reg [DATA_WIDTH-1:0] in_n;	
	reg [DATA_WIDTH-1:0] in_n_2;

	wire fifo_full;
	wire fifo_empty;
	wire [FIFO_DEPTH_LOG2:0] fifo_used;
	
	scfifo master_to_st_fifo(
		.aclr(start_fifo_in),
		.clock(clk),
	
		.data(ram_r_readdata),
		.wrreq(read_complete),

		.q(data_fifo_in),
		.rdreq(read_fifo_in),
		
		.full(fifo_full),
		.empty(fifo_empty),
		.usedw(fifo_used[FIFO_DEPTH_LOG2-1:0])
	);
	defparam master_to_st_fifo.lpm_width = DATA_WIDTH;
	defparam master_to_st_fifo.lpm_numwords = FIFO_DEPTH;
	defparam master_to_st_fifo.lpm_widthu = FIFO_DEPTH_LOG2;
	defparam master_to_st_fifo.lpm_showahead = "ON";
	defparam master_to_st_fifo.use_eab = "ON";
	defparam master_to_st_fifo.add_ram_output_register = "OFF";  // FIFO latency of 2
	defparam master_to_st_fifo.underflow_checking = "OFF";
	defparam master_to_st_fifo.overflow_checking = "OFF";
	
	always @(posedge clk or posedge rst) begin
		if (rst == 1) begin
			in_n <= 0;
		end else begin
			if (start_fifo_in == 1) begin
				in_n <= n_burst_fifo_in * MAX_BURST_COUNT_R;
			end else begin
				if (read_complete == 1) begin
					in_n <= in_n - 1;
				end
			end
		end
	end
	
	always @(posedge clk or posedge rst) begin
		if (rst == 1) begin
			in_n_2 <= 0;
		end else begin
			if (start_fifo_in == 1) begin
				in_n_2 <= n_burst_fifo_in * MAX_BURST_COUNT_R;
			end else begin
				if (read_burst_end == 1) begin
					in_n_2 <= in_n_2 - MAX_BURST_COUNT_R;
				end
			end
		end
	end
	
	always @(posedge clk) begin
		if (start_fifo_in == 1) begin
			read_address <= address_fifo_in;
		end else begin
			if (read_burst_end == 1) begin
				read_address <= read_address + MAX_BURST_COUNT_R * BYTE_ENABLE_WIDTH;
			end
		end
	end
	
	// tracking FIFO
	always @ (posedge clk) begin
		if (start_fifo_in == 1)	begin
			reads_pending <= 0;
		end	else begin
			if(read_burst_end == 1) begin
				if(ram_r_readdatavalid == 0) begin
					reads_pending <= reads_pending + MAX_BURST_COUNT_R;
				end else begin
					reads_pending <= reads_pending + MAX_BURST_COUNT_R - 1;  // a burst read was posted, but a word returned
				end
			end else begin
				if(ram_r_readdatavalid == 0) begin
					reads_pending <= reads_pending;  // burst read was not posted and no read returned
				end	else begin
					reads_pending <= reads_pending - 1;  // burst read was not posted but a word returned
				end
			end
		end
	end
	
	always @ (posedge clk) begin
		if (start_fifo_in == 1) begin
			next_r <= 0;
		end else begin
			if(read_burst_end == 1) begin
				next_r <= 0;
			end else begin
				if (ram_r_read == 1) begin
					next_r <= 1;
				end 
			end
		end
	end
	
	assign read_complete = (ram_r_readdatavalid == 1);
	assign read_burst_end = (ram_r_waitrequest == 0) & (next_r == 1);// & (header_c > 4);
	assign too_many_reads_pending = (reads_pending + fifo_used) >= (FIFO_DEPTH - MAX_BURST_COUNT_R - 4);  // make sure there are fewer reads posted than room in the FIFO

	assign ram_r_address = read_address;
	assign ram_r_read = (too_many_reads_pending == 0) & (in_n_2 != 0);// & (header_c > 4);
	assign ram_r_byteenable = {BYTE_ENABLE_WIDTH{1'b1}};
	assign ram_r_burstcount = MAX_BURST_COUNT_R;
	
	assign bussy_fifo_in = in_n != 0;
	assign empty_fifo_in = fifo_empty;
	
	assign usedw_fifo_in = fifo_used;
	
endmodule
