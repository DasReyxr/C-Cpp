`include "defile.v"
module testfft_top (
    input clk,
    input [6:3] key,
    output [16:1] led,
    output [52:11] out,
    input  [10:3] in
);

    wire [7:0] adIn = in[10:3];
    wire [31:0] oData;
    wire psod;
    wire pipd;
    wire peod;
    wire pbusy;
    wire psoud;
    wire popd;
    wire peoud;
    wire pFftClk;
    wire pFftClk_t;
    wire probe2;

    assign out[52:37] = oData[15:0];    
    assign out[26:11] = oData[31:16];   
    assign out[27]=psod;
    assign out[28]=pipd;
    assign out[29]=peod;
    assign out[30]=pbusy;
    assign out[31]=psoud;
    assign out[32]=popd;
    assign out[33]=peoud;
    assign out[34]=pFftClk;
    assign out[35]=pFftClk;
    assign out[36]=probe2;


    wire [15:0] sXnRe;
 
    wire pllClk = clk;

    Gowin_rPLL pll_fft(
        .clkout(fftClk), //output clkout
        .clkin(clk) //input clkin
    );


    wire [31:0] cntOut2;
    wire sysClk ;
    counter cntInst2(
        .cnto(cntOut2),
        .clko(sysClk),
        .clki(pllClk)
    );
    defparam cntInst2.CNT =2;

    deUstb deUstb_inst(
        .out(fftStart),
        .in(~key[4]),
        .clk(fftClk)
    );
    deUstb deUstb_rst(
        .out(fftRst),
        .in(~key[3]),
        .clk(fftClk)
    );

    localparam IPD_DW = `INPUT_DATA_WIDTH ;
    localparam OPD_DW = `OUTPUT_DATA_WIDTH ;

`ifdef SCALING_NONE
    localparam FRC_DW = `FRC_DW ;
    localparam SYS_DW = IPD_DW + FRC_DW ;
`endif
`ifndef SCALING_NONE
    localparam SYS_DW = IPD_DW ;
`endif
    localparam POINTS_LOG = `POINTS_LOG ;
    localparam POINTS= 2 ** POINTS_LOG ;
    localparam TDF_DW= `TWIDDLE_FACTOR_WIDTH;
    wire [POINTS_LOG -1:0] idx;
    wire signed [OPD_DW -1:0] xk_re;
    wire signed [OPD_DW -1:0] xk_im;
    wire sod, ipd, eod, busy, soud, opd, eoud;

`ifdef MODE_DYNAMIC_THROUGH_PORT
    input ifft;
`endif

`ifdef VARIABLE
    input pset;
    input [3:0] points;
`endif 

`ifdef SCALING_DYNAMIC_THROUGH_PORT
    input sfset;
    input [3:0] sfact;
`endif
`ifdef SCALING_DYNAMIC_THROUGH_PORT
    input unsigned [1:0] scal;
`endif

    testfft u_testfft (
        .clk(fftClk),   
        .rst(fftRst),
        .ipd(ipd),
        .dout(sXnRe)
    );

    MOD_FFT myfft(
    .idx(idx),
    .xk_re(xk_re),
    .xk_im(xk_im),
    .sod(sod),
    .ipd(ipd),
    .eod(eod),
    .busy(busy),
    .soud(soud),
    .opd(opd),
    .eoud(eoud),
    .xn_re(sXnRe),
    .xn_im(sXnRe),
    .start(fftStart),
    .clk(fftClk),   
    .rst(fftRst)
`ifdef MODE_DYNAMIC_THROUGH_PORT
    ,.ifft(ifft)
`endif

`ifdef VARIABLE
    ,.pset(pset)
    ,.points(points)
`endif 

`ifdef SCALING_DYNAMIC_THROUGH_PORT
    ,.sfset(sfset)
    ,.sfact(sfact)
`endif
`ifdef SCALING_DYNAMIC_THROUGH_PORT
    ,.scal(scal)
`endif
    );

    wire [2:0] outState;
    downCnt outCrt(
    .cnt(outState),
    .over(),
    .clk(sysClk),
    .rst(eod)
    );
    defparam outCrt.DW=3;
    defparam outCrt.INIT=5;
    wire isSt0 = outState == 0;
    wire isSt1 = outState == 1;
    wire isSt2 = outState == 2;
    wire isSt3 = outState == 3;
    wire isSt4 = outState == 4;
    wire [15:0] busyData4 ;

    assign led[16] = | (~key);
    assign led[1] = ipd;
    assign led[2] = busy;
    assign led[3] = opd;
    assign led[15:4] = adIn;
    assign psod=sod;
    assign pipd=ipd;
    assign peod=eod;
    assign pbusy=busy;
    assign psoud=soud;
    assign popd=opd;
    assign peoud=eoud;
    assign pFftClk=fftClk;
    assign pFftClk_t = sysClk; 
   
    assign oData[31:16] = xk_re;
    assign oData[15:0] = xk_im;
    assign probe2= isSt4;
  

    assign busyData4=outState;
endmodule
