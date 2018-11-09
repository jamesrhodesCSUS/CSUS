// 123-recog.v
// sequence recognizer, recognize input of "123" by ouput match = 1

module TestMod;
   parameter STDIN = 32'h8000_0000; // keyboard-input file-handle address

   reg clk;
   reg [6:0] str [1:4];  // to what's to be entered
   wire match;           // to be set 1 when matched
   reg [6:0] ascii;      // each input letter is an ASCII bitmap

   RecognizerMod my_recognizer(clk, ascii, match);

   initial begin
      $display("Enter the the magic sequence: ");
      str[1] = $fgetc(STDIN);  // 1st letter
      str[2] = $fgetc(STDIN);  // 2nd letter
      str[3] = $fgetc(STDIN);  // 3rd letter
      str[4] = $fgetc(STDIN);  // ENTER key

      $display("Time clk    ascii       match");
      $monitor("%4d   %b    %c %b   %b", $time, clk, ascii, ascii, match);

      clk = 0;

      ascii = str[1];
      #1 clk = 1; #1 clk = 0;

      ascii = str[2];
      #1 clk = 1; #1 clk = 0;

      ascii = str[3];
      #1 clk = 1; #1 clk = 0;
   end
endmodule

module RecognizerMod(clk, ascii, match);
   input clk;
   input [6:0] ascii;
   output match;

   wire [0:2] Q [0:6];   // 3-input sequence, 7 bits each
   wire [6:0] submatch;  // all bits matched (7 3-bit sequences)

   wire invQ12, invQ01;

   //         654 3210   Q
   //     hex binary
   // '1' 31  011 0001 < q2
   // '2' 32  011 0010 < q1
   // '3' 33  011 0011 < q0

   RippleMod Ripple6(clk, ascii[6], Q[6]);
   // ...
   // ...
   // ...

   // ...
   // ...
   and(submatch[4], Q[4][2], Q[4][1], Q[4][0]);
   // ...
   // ...

   and(match, ..., submatch[4], ...);

//always @(clk) $display("is %b %b %b %b %b %b %b %b %b",
//   match, submatch, Q[6], Q[5], Q[4], Q[3], Q[2], Q[1], Q[0]);

endmodule

module RippleMod(clk, ascii_bit, q);
   input clk, ascii_bit;
   output [0:2] q;

   reg [0:2] q;          // flipflops

   always @(posedge clk) begin
      q[0] <= ascii_bit;
      q[1] <= q[0];
      q[2] <= q[1];
   end

   initial q = 3'b000;
endmodule

