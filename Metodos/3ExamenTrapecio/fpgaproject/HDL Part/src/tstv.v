module counter(clk,trigger,count_half,count_max);
input clk;
output reg trigger;
output reg count_half;
output reg count_max;

reg [7:0] count;
//reg trigger = 1'b0;

localparam TRIG = 0;
localparam HALF = 127;
localparam MAX = 255; 

// count process 
always @(posedge clk) begin
count = count +1; 
// trigger  
    if(count == TRIG) 
    begin
    trigger = 1'b1;
    end 
    else begin
    trigger = 1'b0;
    end 
// trigger  

    if(count == HALF) 
    begin
    count_half = 1'b1;
    end 
    else begin
    count_half = 1'b0;
    end 
// max  

    if(count == MAX) 
    begin
    count_max = 1'b1;
    end 
    else begin
    count_max = 1'b0;
    end 
end


endmodule