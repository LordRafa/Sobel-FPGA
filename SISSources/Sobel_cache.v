`timescale 1 ps / 1 ps

module Sobel_cache (
	input              clk,
	input              rst,
	input              start,
	input       [ADD_WIDTH-1:0] base_add,

	input       [13:0] rdaddress,
	output wire [12:0] valid_lines,
	input              free_line,
	output wire [ 7:0] q,

	output wire [ADD_WIDTH-1:0] ram_r_address,
	input              ram_r_waitrequest,
	input              ram_r_readdatavalid,
	output wire [BYTE_ENABLE_WIDTH-1:0] ram_r_byteenable,
	output wire        ram_r_read,
	input       [DATA_WIDTH-1:0] ram_r_readdata,
	output wire [BURST_WIDTH_R-1:0] ram_r_burstcount
);

	parameter DATA_WIDTH=32;
	parameter ADD_WIDTH = 32;
	parameter BYTE_ENABLE_WIDTH = 4;
	parameter BURST_WIDTH_R = 6;
	parameter MAX_BURST_COUNT_R = 32;

	reg [ADD_WIDTH-1:0] read_address;
	reg [ADD_WIDTH-1:0] write_address;	
	reg [12:0] used_cache_pixels;
	
	
	reg [31:0] in_n;
	always @(posedge clk or posedge rst) begin
		if (rst == 1) begin
			in_n <= 0;
		end else begin
			if (start == 1) begin
				in_n <= 384000;
			end else begin
				if (read_burst_end == 1) begin
					in_n <= in_n - MAX_BURST_COUNT_R;
				end
			end
		end
	end
	
	always @(posedge clk) begin
		if (start == 1) begin
			read_address <= base_add;
		end else begin
			if (read_burst_end == 1) begin
				read_address <= read_address + MAX_BURST_COUNT_R * BYTE_ENABLE_WIDTH;
			end
		end
	end

//	reg [ 3:0] valid;
	always @(posedge clk) begin
		if (start == 1) begin
			used_cache_pixels <= 0;
		end else begin
			if (read_complete == 1) begin
				if (free_line == 0) begin
					used_cache_pixels <= used_cache_pixels + 1;
				end else begin
					used_cache_pixels <= used_cache_pixels - 799;
				end
			end else begin
				if (free_line == 1) begin
					used_cache_pixels <= used_cache_pixels - 800;
				end
			end
		end
	end
	assign valid_lines = used_cache_pixels;

	reg [31:0] reads_pending;
	always @ (posedge clk) begin
		if (start == 1)	begin
			reads_pending <= 0;
		end	else begin
			if(read_burst_end == 1) begin
				if(read_complete == 0) begin
					reads_pending <= reads_pending + MAX_BURST_COUNT_R;
				end else begin
					reads_pending <= reads_pending + MAX_BURST_COUNT_R - 1;
				end
			end else begin
				if(read_complete == 0) begin
					reads_pending <= reads_pending;
				end	else begin
					reads_pending <= reads_pending - 1;
				end
			end
		end
	end
	
	reg [31:0] next_r;
	always @ (posedge clk) begin
		if (start == 1) begin
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
	
	always @(posedge clk) begin
		if (start == 1) begin
			write_address <= 0;
		end else begin
			if (read_complete == 1) begin
				if (write_address == 7999) begin
					write_address <= 0;
				end else begin
					write_address <= write_address + 1;
				end
			end
		end
	end
	
	altsyncram	altsyncram_component (
				.clock0 (clk),
				.data_a (ram_r_readdata[7:0]),
				.address_a (write_address),
				.wren_a (read_complete),
				.address_b (rdaddress),
				.q_b (q),
				.aclr0 (1'b0),
				.aclr1 (1'b0),
				.addressstall_a (1'b0),
				.addressstall_b (1'b0),
				.byteena_a (1'b1),
				.byteena_b (1'b1),
				.clock1 (1'b1),
				.clocken0 (1'b1),
				.clocken1 (1'b1),
				.clocken2 (1'b1),
				.clocken3 (1'b1),
				.data_b ({8{1'b1}}),
				.eccstatus (),
				.q_a (),
				.rden_a (1'b1),
				.rden_b (1'b1),
				.wren_b (1'b0));
	defparam
		altsyncram_component.address_aclr_b = "NONE",
		altsyncram_component.address_reg_b = "CLOCK0",
		altsyncram_component.clock_enable_input_a = "BYPASS",
		altsyncram_component.clock_enable_input_b = "BYPASS",
		altsyncram_component.clock_enable_output_b = "BYPASS",
		altsyncram_component.intended_device_family = "Cyclone III",
		altsyncram_component.lpm_type = "altsyncram",
		altsyncram_component.numwords_a = 8192,
		altsyncram_component.numwords_b = 8192,
		altsyncram_component.operation_mode = "DUAL_PORT",
		altsyncram_component.outdata_aclr_b = "NONE",
		altsyncram_component.outdata_reg_b = "CLOCK0",
		altsyncram_component.power_up_uninitialized = "FALSE",
		altsyncram_component.read_during_write_mode_mixed_ports = "DONT_CARE",
		altsyncram_component.widthad_a = 13,
		altsyncram_component.widthad_b = 13,
		altsyncram_component.width_a = 8,
		altsyncram_component.width_b = 8,
		altsyncram_component.width_byteena_a = 1;
		
	assign read_complete = (ram_r_readdatavalid == 1);
	assign read_burst_end = (ram_r_waitrequest == 0) & (next_r == 1);
	assign too_many_reads_pending = (reads_pending + used_cache_pixels) > (8000 - MAX_BURST_COUNT_R);

	assign ram_r_address = read_address;
	assign ram_r_read = (too_many_reads_pending == 0) & (in_n != 0);
	assign ram_r_byteenable = {BYTE_ENABLE_WIDTH{1'b1}};
	assign ram_r_burstcount = MAX_BURST_COUNT_R;
	
endmodule
