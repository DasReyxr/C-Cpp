create_clock -name clk_in -period 20 -waveform {0 10} [get_ports {clk}]
create_clock -name myclk -period 10 -waveform {0 5} [get_nets {sysClk}]
report_timing -setup -from_clock [get_clocks {clk_in}] -to_clock [get_clocks {clk_in}] -max_paths 25 -max_common_paths 1
report_timing -hold -from_clock [get_clocks {clk_in}] -to_clock [get_clocks {clk_in}] -max_paths 25 -max_common_paths 1
report_timing -recovery -from_clock [get_clocks {clk_in}] -to_clock [get_clocks {clk_in}] -max_paths 25 -max_common_paths 1
report_timing -removal -from_clock [get_clocks {clk_in}] -to_clock [get_clocks {clk_in}] -max_paths 25 -max_common_paths 1
