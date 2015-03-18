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
	parameter BYTE_ENABLE_WIDTH = 4; // derived parameter
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


//*********************************************************************Sobel Implementation*************************************************************************
	reg [3:0] stage;
	wire go_sobel;	
	assign go_sobel = (stage == 0) & (pixel_counter > 0) & (run == 1) & (usedw_fifo_out < FIFO_DEPTH);

	reg [9:0] sobel_col;
	reg [8:0] sobel_line;
	reg [31:0] add_main_pix;
	always @(posedge clk) begin
		if (start == 1) begin
			sobel_col <= 0;
			sobel_line <= 0;
			add_main_pix <= 0;
		end else begin
			if (stage == 4) begin
				if (sobel_col == 799) begin
					sobel_line <= sobel_line + 1;
					sobel_col <= 0;
				end else begin
					sobel_col <= sobel_col + 1;
				end
				add_main_pix <= add_main_pix + 4;
			end
		end
	end
	
	reg [3:0] pending_orders;
	always @(posedge clk) begin
		if (go_sobel == 1) begin
			if (sobel_col == 0) begin
				pending_orders <= 9;
			end else begin
				pending_orders <= 3;
			end
		end else begin
			if ((stage == 1) && (ram_r_waitrequest == 0)) begin
				pending_orders <= pending_orders - 1;
			end
		end
	end
	
	reg [31:0] add_pix_around;
	always @(posedge clk) begin
		if (go_sobel == 1) begin
			if (sobel_col == 0) begin
				add_pix_around <= base_add + add_main_pix - 3204;
			end else begin
				add_pix_around <= base_add + add_main_pix - 3196;
			end			
		end else begin
			if ((stage == 1) && (ram_r_waitrequest == 0)) begin
				if (pending_orders == 9) begin
					add_pix_around <= add_pix_around + 3200;
				end
				if (pending_orders == 8) begin
					add_pix_around <= add_pix_around + 3200;
				end
				if (pending_orders == 7) begin
					add_pix_around <= add_pix_around - 6396;
				end
				if (pending_orders == 6) begin
					add_pix_around <= add_pix_around + 3200;
				end
				if (pending_orders == 5) begin
					add_pix_around <= add_pix_around + 3200;
				end
				if (pending_orders == 4) begin
					add_pix_around <= add_pix_around - 6396;
				end
				if (pending_orders == 3) begin
					add_pix_around <= add_pix_around + 3200;
				end
				if (pending_orders == 2) begin
					add_pix_around <= add_pix_around + 3200;
				end
			end
		end
	end

	reg [3:0] pending_reads;
	always @(posedge clk) begin
		if (go_sobel == 1) begin
			if (sobel_col == 0) begin
				pending_reads <= 9;
			end else begin
				pending_reads <= 3;
			end
		end else begin
			if ((stage < 3) && (ram_r_readdatavalid == 1)) begin
				pending_reads <= pending_reads - 1;
			end
		end
	end
	
	reg [2:0] g_col;
	reg [2:0] g_line;	
	always @(posedge clk) begin
		if (start == 1) begin
			g_col <= 0;
			g_line <= 0;
		end else begin
			if (ram_r_readdatavalid == 1) begin
				if (g_line == 2) begin
					g_col <= g_col + 1;
					g_line <= 0;
				end else begin
					g_line <= g_line + 1;
				end
			end
			if (stage == 4) begin
				if (sobel_col == 799) begin
					g_col <= 0;
					g_line <= 0;
				end else begin
					g_col <= 2;
					g_line <= 0;
				end
			end
		end
	end


	wire jump_stage2;
	assign jump_stage2 = (pending_orders == 1) & (stage == 1) & (ram_r_waitrequest == 0);
	wire jump_stage3;
	assign jump_stage3 = (pending_reads == 0) & (stage == 2);
	always @(posedge clk or posedge rst) begin
		if (rst == 1) begin
			stage <= 0;
		end else begin
			if ((start == 1) | (stage == 9)) begin
				stage <= 0;
			end else begin
				if (go_sobel == 1) begin
					stage <= 1;
				end
				if (jump_stage2 == 1) begin
					stage <= 2;
				end
				if (jump_stage3 == 1) begin
					stage <= 3;
				end else begin
					if (stage > 2) begin
						stage <= stage + 1;
					end
				end
			end
		end
	end

	wire out_bound;
	assign out_bound = ((sobel_col + g_col - 2) == -1) | ((sobel_col + g_col - 2) == 800) | ((sobel_line + g_line - 2) == -1) | ((sobel_line + g_line - 2) == 480);
	
	assign ram_r_address = add_pix_around;
	assign ram_r_byteenable = {BYTE_ENABLE_WIDTH{1'b1}};
	assign ram_r_read = (stage == 1);
	assign ram_r_burstcount = 1;
	
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
			end
		end
		if (ram_r_readdatavalid == 1) begin
			if (out_bound == 0) begin
				g[g_col][g_line] <= ram_r_readdata[7:0];
			end else begin
				g[g_col][g_line] <= 0;
			end
		end
		if (stage == 3) begin
			gx <= g[0][0] + {g[0][1], 1'b0} + g[0][2];
			gx2 <= g[2][0] + {g[2][1], 1'b0} + g[2][2];
			gy <= g[0][0] + {g[1][0], 1'b0} + g[2][0];
			gy2 <= g[0][2] + {g[1][2], 1'b0} + g[2][2];
		end
		if (stage == 4) begin
			gx <= (gx > gx2)? gx - gx2 : gx2 - gx; // I need the absolute value
			gy <= (gy > gy2)? gy - gy2 : gy2 - gy; // 
		end
		if (stage == 5) begin
			gxgy <= gx + gy;
		end
		if (stage == 7) begin
			sobel_r <= gxgy > 255? 255 : gxgy; 
		end
		if (stage == 8) begin
			sobel_r <= 255 - sobel_r;
		end
	end
	
//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	assign data_fifo_out = {8'd0, {3{sobel_r}}};
	assign data_valid_fifo_out = (run == 1) & (stage == 9);
	
	assign endf = (run == 2);
	
endmodule
