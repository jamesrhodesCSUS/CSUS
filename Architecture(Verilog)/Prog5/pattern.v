module TestMod;
   reg CLK;
   wire [0:12] Q;
   wire [6:0] ascii;

   always begin
      #1;
      CLK = 0;
      #1;
      CLK = 1;
   end

   RippleMod my_ripple(CLK, Q);
   CoderMod my_coder(Q, ascii);

   initial #25 $finish;

   initial begin
      $display("Time CLK  Q              Name");
      $monitor("%2d   %b    %b  %c", $time, CLK, Q, ascii);
   end
endmodule

module CoderMod(Q, ascii);
   input [0:12] Q;
   output [6:0] ascii;

   nor(ascii[6], Q[5], Q[12]);
   nor(ascii[5], Q[0], Q[6]);
   or (ascii[4], Q[4], Q[6], Q[11]);
   or (ascii[3], Q[0], Q[2], Q[7], Q[8]);
   or (ascii[2], Q[2], Q[3], Q[8], Q[9], Q[10]);
   or (ascii[1], Q[0], Q[4], Q[6], Q[8], Q[11]);
   or (ascii[0], Q[1], Q[2], Q[3], Q[4], Q[8], Q[10], Q[11]);
endmodule

module RippleMod(CLK, Q);
   input CLK;
   output [0:12] Q;

   reg [0:12] Q;

   always @(posedge CLK or negedge CLK) begin
      Q[ 0] <= Q[12];
      Q[ 1] <= Q[ 0];
      Q[ 2] <= Q[ 1];
      Q[ 3] <= Q[ 2];
      Q[ 4] <= Q[ 3];
      Q[ 5] <= Q[ 4];
      Q[ 6] <= Q[ 5];
      Q[ 7] <= Q[ 6];
      Q[ 8] <= Q[ 7];
      Q[ 9] <= Q[ 8];
      Q[10] <= Q[ 9];
      Q[11] <= Q[10];
      Q[12] <= Q[11];
   end

   initial Q = 4096;
endmodule