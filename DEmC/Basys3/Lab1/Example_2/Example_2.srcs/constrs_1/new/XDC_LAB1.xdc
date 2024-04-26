## This file is a general .xdc for the Basys3 rev B board
## To use it in a project:
## - uncomment the lines corresponding to used pins
## - rename the used ports (in each line, after get_ports) according to the top level signal names in the project
 
# Switches
set_property PACKAGE_PIN V17 [get_ports {T_I[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {T_I[0]}]
set_property PACKAGE_PIN V16 [get_ports {T_I[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {T_I[1]}]
set_property PACKAGE_PIN W16 [get_ports {T_I[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {T_I[2]}]
set_property PACKAGE_PIN W17 [get_ports {T_I[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {T_I[3]}]
set_property PACKAGE_PIN W15 [get_ports {T_I[4]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {T_I[4]}]
set_property PACKAGE_PIN V15 [get_ports {T_I[5]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {T_I[5]}]
set_property PACKAGE_PIN W14 [get_ports {T_I[6]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {T_I[6]}]
set_property PACKAGE_PIN W13 [get_ports {T_I[7]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {T_I[7]}]
set_property PACKAGE_PIN V2 [get_ports {T_I[8]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {T_I[8]}]

#7 segment display
set_property PACKAGE_PIN W7 [get_ports {T_Y[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {T_Y[0]}]
set_property PACKAGE_PIN W6 [get_ports {T_Y[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {T_Y[1]}]
set_property PACKAGE_PIN U8 [get_ports {T_Y[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {T_Y[2]}]
set_property PACKAGE_PIN V8 [get_ports {T_Y[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {T_Y[3]}]
set_property PACKAGE_PIN U5 [get_ports {T_Y[4]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {T_Y[4]}]
set_property PACKAGE_PIN V5 [get_ports {T_Y[5]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {T_Y[5]}]
set_property PACKAGE_PIN U7 [get_ports {T_Y[6]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {T_Y[6]}]