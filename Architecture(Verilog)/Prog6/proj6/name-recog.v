//James Rhodes
//6th programming, CSC 137

module TestMod;
	parameter STDIN = 32'h8000_0000;

	reg CLK;
	reg [6:0] str [1:6];
	wire match;
	reg [6:0] ascii;

	RecognizerMod my_recognizer(CLK, ascii, match);

	initial begin
		$display("Enter the magic Sequence: ");
		str[1] = $fgetc(STDIN);
		str[2] = $fgetc(STDIN);
		str[3] = $fgetc(STDIN);
		str[4] = $fgetc(STDIN);
		str[5] = $fgetc(STDIN);
		str[6] = $fgetc(STDIN);

		$display("Time  CLK   ascii         match");
		$monitor("%2d    %b     %c %b     %b", $time, CLK, ascii, ascii, match);

		CLK = 0;

		ascii = str[1];
		#1 CLK = 1; #1 CLK = 0;

		ascii = str[2];
		#1 CLK = 1; #1 CLK = 0;

		ascii = str[3];
		#1 CLK = 1; #1 CLK = 0;
		
		ascii = str[4];
		#1 CLK = 1; #1 CLK = 0;

		ascii = str[5];
		#1 CLK = 1; #1 CLK = 0;
	end
endmodule

module RecognizerMod(CLK, ascii, match);
	input CLK;
	input [6:0] ascii;
	output match;

	wire [0:4] Q [0:6];
	wire [6:0] submatch;
	wire inv60, inv54, inv50, inv42, inv41, inv34, inv32, inv20, inv14;
	wire invQ50, invQ51, invQ44, invQ31, invQ34, invQ22, invQ23, invQ10, invQ14, invQ00;	

	RippleMod Rip6(CLK, ascii[6], Q[0]);
	RippleMod Rip5(CLK, ascii[5], Q[1]);
        RippleMod Rip4(CLK, ascii[4], Q[2]);
        RippleMod Rip3(CLK, ascii[3], Q[3]);
        RippleMod Rip2(CLK, ascii[2], Q[4]);
        RippleMod Rip1(CLK, ascii[1], Q[5]);
        RippleMod Rip0(CLK, ascii[0], Q[6]);

	not(inv60, Q[6][0]);
	and(submatch[6], Q[6][4], Q[6][3], Q[6][2], Q[6][1], inv60);
	not(inv54, Q[5][4]);
	not(inv50, Q[5][0]);
	nor(submatch[5], inv54, Q[5][3], Q[5][2], Q[5][1], inv50);
	not(inv42, Q[4][2]);
	not(inv41, Q[4][1]);
	nor(submatch[4], Q[4][4], Q[4][3], inv42, inv41, Q[4][0]);
	not(inv34, Q[3][4]);
	not(inv32, Q[3][2]);
	nor(submatch[3], inv34, Q[3][3], inv32, Q[3][1], Q[3][0]);
	not(inv20, Q[2][0]);
	nor(submatch[2], Q[2][4], Q[2][3], Q[2][2], Q[2][1], inv20);
	not(inv14, Q[1][4]);
	and(submatch[1], inv14, Q[1][3], Q[1][2], Q[1][1], Q[1][0]);
	and(submatch[0], Q[0][4], Q[0][3], Q[0][2], Q[0][1], Q[0][0]);
/*
	and(submatch[6], Q[6][4], Q[6][3], Q[6][2], Q[6][1], Q[6][0]);
	not(invQ50, Q[5][0]);
	not(invQ51, Q[5][1]);
        and(submatch[5], Q[5][4], Q[5][3], Q[5][2], invQ51, invQ50);
	not(invQ44, Q[4][4]);
        nor(submatch[4], invQ44, Q[4][3], Q[4][2], Q[4][1], Q[4][0]);
	not(invQ31, Q[3][1]);
	not(invQ34, Q[3][4]);
        and(submatch[3], invQ34, Q[3][3], Q[3][2], invQ31, Q[3][0]);
	not(invQ22, Q[2][2]);
	not(invQ23, Q[2][3]);
        nor(submatch[2], Q[2][4], invQ23, invQ22, Q[2][2], Q[2][0]);
	not(invQ10, Q[1][0]);
	not(invQ14, Q[1][4]);
        nor(submatch[1], invQ14, Q[1][3], Q[1][2], Q[1][1], invQ10);
	not(invQ00, Q[0][0]);
        and(submatch[0], Q[0][4], Q[0][3], Q[0][2], Q[0][1], invQ00);
*/
	and(match, submatch[6], submatch[5], submatch[4], submatch[3], submatch[2], submatch[1], submatch[0]);
endmodule

module RippleMod(CLK, ascii_bit, q);
	input CLK, ascii_bit;
	output [0:4] q;

	reg [0:4] q;

	always @(posedge CLK) begin
		q[0] <= ascii_bit;
		q[1] <= q[0];
		q[2] <=	q[1];
		q[3] <= q[2];
		q[4] <= q[3];
	end

	initial q = 5'b10000;
endmodule
