// DQ.v
// How to use registers to latch data

module MemMod(CLK, D, Q);
   input CLK, D;
   output Q;

   reg Q;

   always @(posedge CLK) begin
      Q <= D;
   end
endmodule

module TestMod;
   reg clk, data_in;
   wire data_out;

   MemMod my_memory1(clk, data_in, data_out);

   always begin // this is clock wave
      clk = 0;  // 0 for half cycle (#1)
      #1;
      clk = 1;  // 1 for half cycle (#1)
      #1;
   end
   
   initial begin
      $display("Time CLK    D  Q");
      data_in = 0;
      #1;
      $display("%4d   %b    %b  %b", $time, clk, data_in, data_out);
      #1;
      $display("%4d   %b    %b  %b", $time, clk, data_in, data_out);

      data_in = 1;
      #1;
      $display("%4d   %b    %b  %b", $time, clk, data_in, data_out);
      #1;
      $display("%4d   %b    %b  %b", $time, clk, data_in, data_out);

      $finish;
   end
endmodule
