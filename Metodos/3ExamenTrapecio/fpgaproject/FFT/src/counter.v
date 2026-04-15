module counter (cnto,clko,clki);
input clki;
output clko;
output unsigned [31:0] cnto;
parameter CNT=10;
parameter overFlow=CNT/2-1;
reg unsigned [31:0] cnt_r=0;
reg clko=0;
always@(posedge clki) begin
    if(cnt_r==overFlow)begin
        cnt_r<=0;
        clko<=~clko;
    end
    else begin
        cnt_r <= cnt_r+1;
    end
end
assign cnto=cnt_r;
endmodule
