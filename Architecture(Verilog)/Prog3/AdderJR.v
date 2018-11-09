//James Rhodes
//137

module TestMod;
        parameter STDIN = 32'h8000_0000;

        reg [7:0] str [1:3];
        reg [4:0] x, y;
        wire [4:0] s;
        wire c5;

        BigAdder my_Adder(x, y, s, c5);

        initial begin
                $display("Enter X: ");
                str[1] = $fgetc(STDIN);
                str[2] = $fgetc(STDIN);
                str[3] = $fgetc(STDIN);
                x = (str[1] - 48) * 10 + (str[2] - 48) * 1;

                $display("EnterY: ");
                str[1] = $fgetc(STDIN);
                str[2] = $fgetc(STDIN);
                str[3] = $fgetc(STDIN);
                y = (str[1] - 48) * 10 + (str[2] - 48) * 1;

                #1;
                $display("X: %d (%b)", x, x);
                $display("Y: %d (%b)", y, y);
                $display("Result: %d (%b)", s, s);
                $display("C5: %d", c5);
        end
endmodule

module BigAdder(x, y, s, c5);
        input [4:0] x, y;
        output [4:0] s;
        output c5;
        wire [4:0] x, y;
        wire c5;

        wire [4:0] c;

        assign c[0] = 0;

        FullAdderMod my_FA0(x[0], y[0], c[0], s[0], c[1]);
        FullAdderMod my_FA1(x[1], y[1], c[1], s[1], c[2]);
        FullAdderMod my_FA2(x[2], y[2], c[2], s[2], c[3]);
        FullAdderMod my_FA3(x[3], y[3], c[3], s[3], c[4]);
        FullAdderMod my_FA4(x[4], y[4], c[4], s[4], c5);
endmodule

module FullAdderMod(x, y, cin, cout, sum);
        input x, y, cin;
        output cout, sum;

        MajorityMod my_Maj(x, y, cin, cout);
        ParityMod my_Par(x, y, cin, sum);
endmodule

module MajorityMod(x, y, cin, cout);
        input x, y, cin;
        output cout;

        wire [0:2] and_out;

        and(and_out[0], x, y);
        and(and_out[1], x, cin);
        and(and_out[2], cin, y);

        or (cout, and_out[0], and_out[1], and_out[2]);
endmodule

module ParityMod(x, y, cin, sum);
        input x, y, cin;
        output sum;

        wire xor_out;

        xor(xor_out, x, y);
        xor(sum, xor_out, cin);
endmodule                          