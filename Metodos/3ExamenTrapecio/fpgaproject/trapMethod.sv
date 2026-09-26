module trap (
    input  logic sck,
    input  logic cs_n,
    input  logic mosi,
    output logic [127:0] frame,
    output logic frame_valid
);

    logic [6:0] bit_cnt;

    // if frame_valid = 1, data is ready to be taken
    always_ff @(posedge sck or posedge cs_n) begin
        if (cs_n) begin
            bit_cnt    <= '0;
            frame_valid<= 1'b0;
        end else begin
            frame <= {frame[126:0], mosi};
            if (bit_cnt == 7'd127) begin
                frame_valid <= 1'b1;
                bit_cnt     <= bit_cnt;
            end else 
            begin
                frame_valid <= 1'b0;
                bit_cnt     <= bit_cnt + 1'b1;
            end
        end
    end
endmodule