## This file is a general .xdc for the Basys3 rev B board
## To use it in a project:
## - uncomment the lines corresponding to used pins
## - rename the used ports (in each line, after get_ports) according to the top level signal names in the project

# Clock signal
set_property PACKAGE_PIN W5 [get_ports I_T]							
	set_property IOSTANDARD LVCMOS33 [get_ports I_T]
	create_clock -add -name sys_clk_pin -period 10.00 -waveform {0 5} [get_ports I_T] 

# LEDs 
set_property PACKAGE_PIN U16 [get_ports {Q_T[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Q_T[0]}]
set_property PACKAGE_PIN E19 [get_ports {Q_T[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Q_T[1]}]
set_property PACKAGE_PIN U19 [get_ports {Q_T[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Q_T[2]}]
set_property PACKAGE_PIN V19 [get_ports {Q_T[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Q_T[3]}]