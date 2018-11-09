// Memory.v
// to mimic how computer memory works

module TestMod;
   key-in input_data
   key-in addr
   write input_data into memory at given addr

   key-in addr
   read output_data out from memory from given addr
   show what's read (output_data)

   MemoryMod my_memory(addr, data, Read, Write);
endmodule

module MemoryMod(addr, input_data, Read, Write, output_data);
   input [3:0] addr;
   input [7:0] input_data;
   input Read, Write;
   output [7:0] output_data;

   reg [7:0] output_data;         // output buffer
   reg [7:0] memory_array [0:15]; // memory has only 16 bytes

   always @(posedge Write) begin  // CPU wants to write
      memory_array[addr] = input_data;
   end

   always @(posedge Read) begin  // CPU wants to write
      output_data = memory_array[addr];
   end
endmodule
