//James Rhodes
//Programming #2

module DecoderMod(s, o);
	input [1:0] s;
	output [0:3] o;
	
	not (o[0], s[1]);
	not (o[2], s[0]);
	assign o[1] = s[1];
	assign o[3] = s[0];
end module

module MuxMod(s, o);
	input [1:0] s;
	output [0:3] o;
	
	wire [0:3] s_decoded, 
	
	DecoderMod my_decoder(s, s_decoded);
	
	and (o[0], s_decoded[0], s_decoded[2]);
	and (o[1], s_decoded[0], s[3]);
	and (o[2], s[1], s_decoded[2]);
	and (o[3], s[1], s[3]);
endmodule

module TestMod
	reg [1:0] s;
	wire [0:3] o;
	
	MuxMod my_mux(s, o);
	
	initial begin
		$display("Time\ts1\ts0\to0\to1\to2\to3");
		$display("---------------------");
		$display("%0d\t%b\t%b\t%b\t%b\t%b\t%b", $time, s[1], s[0], o[0], o[1], o[2], o[3]);
	end
	
	initial begin
		s1 = 0; s0 = 0; #1;
		s1 = 0; s0 = 1; #1;
		s1 = 1; s0 = 0; #1;
		s1 = 1; s0 = 1; #1;
	end
endmodule