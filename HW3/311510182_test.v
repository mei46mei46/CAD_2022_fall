module test;

reg[7:0] in;
reg clk,reset;
wire[7:0] out;

initial begin
	clk=0;
	forever
    #5 clk = !clk;
end

initial begin
    $dumpfile("cpu.vcd");
    $dumpvars;	
end

cpu cc(.in(in), .clk(clk), .reset(reset), .out(out));

initial begin
	in    =8'b00000000;
	reset =1'b1;

#12 in    =8'b01101111;
	reset =1'b0;
     
//write your test pattern----------------

// inputA value = 255
 in = 8'b01100000;
 @(negedge clk);
 in = 8'b11111111;
 @(negedge clk);
// inputA value = 0
 in = 8'b01100000;
 @(negedge clk);
 in = 8'b00000000;
 @(negedge clk);
// inputB value = 0
 in = 8'b01110000;
 @(negedge clk);
 in = 8'b00000000;
 @(negedge clk);
 // inputB value = 255
 in = 8'b01110000;
 @(negedge clk);
 in = 8'b11111111;
 @(negedge clk);
// inputB value = 0
 in = 8'b01110000;
 @(negedge clk);
 in = 8'b00000000;
 @(negedge clk);
// input mem in 0000 value = 0
 in = 8'b10000000;
 @(negedge clk);
 in = 8'b00000000;
 @(negedge clk);
// output mem addr:0000
 in = 8'b11000000;
 @(negedge clk);
 in = 8'b00000000;
 @(negedge clk);
// loadC in 0000 value = 0 
 in = 8'b10100000;
 @(negedge clk);
 in = 8'b00000000;
 @(negedge clk);
// C=A-1
 in = 8'b00111111;
 @(negedge clk);
// A=C
 in = 8'b11010000;
 @(negedge clk);
// B=C
 in = 8'b11100000;
 @(negedge clk);
// C=A+1
 in = 8'b00100000;
 @(negedge clk);
// A=C
 in = 8'b11010000;
 @(negedge clk);
// B=C
 in = 8'b11100000;
 @(negedge clk);
// C=A+B
 in = 8'b00000000;  
 @(negedge clk);
// C=A+B+1
 in = 8'b01000000;
 @(negedge clk);
// C=-A
 in = 8'b01010000;  
 @(negedge clk);
// storeC
 in = 8'b10010000; 
 @(negedge clk);
// outputC 
 in = 8'b10110000;
 @(negedge clk);
// C=A-B
 in = 8'b00010000;
 @(negedge clk);
// storeC  
 in = 8'b10010000;
 @(negedge clk);
// outputC
 in = 8'b10110000;
 @(negedge clk);
// default
 in = 8'b11110000;
 @(negedge clk);
// reset toggle
reset =1'b1;
@(negedge clk);

//----------------------------------------
  $finish;

end
endmodule
