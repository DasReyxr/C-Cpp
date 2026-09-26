module downCnt(cnt,over,clk,rst);
parameter DW=8;
parameter INIT=256;
input clk,rst;
output over;
output [DW-1:0] cnt;

reg unsigned [DW-1:0] cnt_r = INIT-1;
wire isOver = cnt_r==0;
always @(posedge clk) begin
    if(isOver | rst)begin
        cnt_r <= INIT-1;
    end
    else begin
        cnt_r <= cnt_r-1'b1;
    end
end
assign over = isOver;
assign cnt = cnt_r;
endmodule
