`timescale 1 ps / 1 ps
module Sobel (
	input clk,
	input rst,

	output [31:0] data_fifo_out,
	output data_valid_fifo_out,
	input wire [8:0] usedw_fifo_out,
	
	output wire[31:0] ram_r_address,
	input ram_r_waitrequest,
	input ram_r_readdatavalid,
	output wire[3:0] ram_r_byteenable,
	output wire ram_r_read,
	input wire[31:0] ram_r_readdata,
	output wire[5:0] ram_r_burstcount,
	
	input start,
	output endf,
	input [31:0] base_add
);

	parameter DATA_WIDTH=32;
	parameter ADD_WIDTH = 32;
	parameter BYTE_ENABLE_WIDTH = 4;
	parameter BURST_WIDTH_R = 6;
	parameter FIFO_DEPTH = 256;
	parameter FIFO_DEPTH_LOG2 = 8;

	reg [18:0] pixel_counter;
	reg [1:0] run;
	always @ (posedge clk or posedge rst) begin
		if (rst == 1) begin
			run <= 0;
		end else begin
			if (start == 1) begin
				run <= 1;
			end else begin
				if (pixel_counter == 0) begin
					run <= 2;
				end
				if (endf == 1) begin
					run <= 0;
				end
			end
		end
	end


	always @ (posedge clk) begin
		if (start == 1) begin
			pixel_counter <= 384000;
		end else begin
			if (data_valid_fifo_out) begin
				pixel_counter <= pixel_counter - 1;
			end
		end
	end
	
	wire [12:0] cache_valid_lines;
	wire cache_free_line;
	wire [7:0] cache_pixel;

	Sobel_cache Sobel_cache_instance (
		.clk(clk),
		.rst(rst),
		.start(start),
		.base_add(base_add),

		.rdaddress(add_pix_around),
		.valid_lines(cache_valid_lines),
		.free_line(cache_free_line),
		.q(cache_pixel),

		.ram_r_address(ram_r_address),
		.ram_r_waitrequest(ram_r_waitrequest),
		.ram_r_readdatavalid(ram_r_readdatavalid),
		.ram_r_byteenable(ram_r_byteenable),
		.ram_r_read(ram_r_read),
		.ram_r_readdata(ram_r_readdata),
		.ram_r_burstcount(ram_r_burstcount)
	);

//++++++++++++Sobel Implementation++++++++++++
	reg [3:0] stage;
	wire go_sobel;	
	assign go_sobel = (stage == 0) & (pixel_counter > 0) & (run == 1) & (usedw_fifo_out < FIFO_DEPTH) & (cache_valid_lines > 13'd2399);
	assign cache_free_line = (sobel_col == 799) & (stage == 2) & (sobel_line > 0) & (sobel_line < 478);

	reg [9:0] sobel_col;
	reg [8:0] sobel_line;
	reg [13:0] add_main_pix;
	always @(posedge clk) begin
		if (start == 1) begin
			sobel_col <= 0;
			sobel_line <= 0;
			add_main_pix <= 0;
		end else begin
			if (stage == 3) begin
				if (sobel_col == 799) begin
					sobel_line <= sobel_line + 1;
					sobel_col <= 0;
				end else begin
					sobel_col <= sobel_col + 1;
				end
				if (add_main_pix == 7999) begin
					add_main_pix <= 0;
				end else begin
					add_main_pix <= add_main_pix + 1;
				end
			end
		end
	end
	
	reg [13:0] add_pix_around;
	always @(posedge clk) begin
		if (go_sobel == 1) begin
			if (sobel_col == 0) begin
				if (add_main_pix < 800) begin
					add_pix_around <= 7200 + add_main_pix;
				end else begin
					add_pix_around <= add_main_pix - 800;
				end
			end else begin
				if (add_main_pix < 800) begin
					add_pix_around <= 7201 + add_main_pix;
				end else begin
					add_pix_around <= add_main_pix - 799;
				end
			end			
		end
		if (stage == 1) begin
			if (pending_reads != 4) begin
				if (add_pix_around > 7199) begin
					add_pix_around <= add_pix_around - 7200;
				end else begin
					add_pix_around <= add_pix_around + 800;
				end
			end
			if (pending_reads == 4) begin
				if (add_pix_around > 1598) begin
					add_pix_around <= add_pix_around - 1599;
				end else begin
					add_pix_around <= add_pix_around + 6401;
				end
			end
		end
	end

	reg [3:0] pending_reads;
	always @(posedge clk) begin
		if (go_sobel == 1) begin
			if (sobel_col == 0) begin
				pending_reads <= 6;
			end else begin
				pending_reads <= 3;
			end
		end else begin
			if (stage == 1) begin
				pending_reads <= pending_reads - 1;
			end
		end
	end
	
	reg [2:0] g_col;
	reg [2:0] g_line;	
	always @(posedge clk) begin
		if (start == 1) begin
			g_col <= 1;
			g_line <= 0;
		end else begin
			if (stage == 1) begin
				if (g_line == 2) begin
					g_col <= g_col + 1;
					g_line <= 0;
				end else begin
					g_line <= g_line + 1;
				end
			end
			if (stage == 3) begin
				if (sobel_col == 799) begin
					g_col <= 1;
					g_line <= 0;
				end else begin
					g_col <= 2;
					g_line <= 0;
				end
			end
		end
	end

	wire jump_stage2;
	assign jump_stage2 = (pending_reads == 0) & (stage == 1);
	always @(posedge clk or posedge rst) begin
		if (rst == 1) begin
			stage <= 0;
		end else begin
			if ((start == 1) | (stage == 7)) begin
				stage <= 0;
			end else begin
				if (go_sobel == 1) begin
					stage <= 1;
				end
				if (jump_stage2 == 1) begin
					stage <= 2;
				end else begin
					if (stage > 1) begin
						stage <= stage + 1;
					end
				end
			end
		end
	end

	wire out_bound;
	assign out_bound = ((sobel_col + g_col - 2) == -1) | ((sobel_col + g_col - 2) == 800) | ((sobel_line + g_line - 2) == -1) | ((sobel_line + g_line - 2) == 480);
	
	reg [10:0] gx;
	reg [9:0] gx2;	
	reg [10:0] gy;
	reg [9:0] gy2;
	reg [20:0] gxgy;
	reg [7:0] sobel_r;
	wire[10:0] sqrt_r;
	reg [7:0] g[0:2][0:2];
	always @(posedge clk) begin
		if (go_sobel == 1) begin
			if (sobel_col != 0) begin
				g[0][0] <= g[1][0];
				g[0][1] <= g[1][1];
				g[0][2] <= g[1][2];
				g[1][0] <= g[2][0];
				g[1][1] <= g[2][1];
				g[1][2] <= g[2][2];
			end else begin
				g[0][0] <= 0;
				g[0][1] <= 0;
				g[0][2] <= 0;
			end
		end
		if (stage == 1) begin
			if (out_bound == 0) begin
				g[g_col][g_line] <= cache_pixel;
			end else begin
				g[g_col][g_line] <= 0;
			end
		end
		if (stage == 2) begin
			gx <= g[0][0] + {g[0][1], 1'b0} + g[0][2];
			gx2 <= g[2][0] + {g[2][1], 1'b0} + g[2][2];
			gy <= g[0][0] + {g[1][0], 1'b0} + g[2][0];
			gy2 <= g[0][2] + {g[1][2], 1'b0} + g[2][2];
		end
		if (stage == 3) begin
			gx <= (gx > gx2)? gx - gx2 : gx2 - gx;
			gy <= (gy > gy2)? gy - gy2 : gy2 - gy;
		end
		if (stage == 4) begin
			gxgy <= gx + gy;
		end
		if (stage == 5) begin
			sobel_r <= gxgy > 255? 255 : gxgy; 
		end
		if (stage == 6) begin
			sobel_r <= 255 - sobel_r;
		end
	end
	
//------------------------------

	assign data_fifo_out = {8'd0, {3{sobel_r}}};
	assign data_valid_fifo_out = (run == 1) & (stage ==7);
	
	assign endf = (run == 2);
	
endmodule
