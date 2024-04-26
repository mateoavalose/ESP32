## This file is a general .xdc for the Basys3 rev B board
## To use it in a project:
## - uncomment the lines corresponding to used pins
## - rename the used ports (in each line, after get_ports) according to the top level signal names in the project

# Switches
set_property PACKAGE_PIN V17 [get_ports {B[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {B[0]}]
set_property PACKAGE_PIN V16 [get_ports {B[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {B[1]}]
set_property PACKAGE_PIN W16 [get_ports {B[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {B[2]}]
set_property PACKAGE_PIN W17 [get_ports {B[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {B[3]}]

# LEDs
set_property PACKAGE_PIN U16 [get_ports {O[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O[0]}]
set_property PACKAGE_PIN E19 [get_ports {O[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O[1]}]
set_property PACKAGE_PIN U19 [get_ports {O[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O[2]}]
set_property PACKAGE_PIN V19 [get_ports {O[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O[3]}]
set_property PACKAGE_PIN W18 [get_ports {O[4]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O[4]}]
set_property PACKAGE_PIN U15 [get_ports {O[5]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O[5]}]
set_property PACKAGE_PIN U14 [get_ports {O[6]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O[6]}]
set_property PACKAGE_PIN V14 [get_ports {O[7]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O[7]}]
set_property PACKAGE_PIN V13 [get_ports {O[8]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O[8]}]

#7 segment display 
set_property PACKAGE_PIN W7 [get_ports {D[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {D[0]}]
set_property PACKAGE_PIN W6 [get_ports {D[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {D[1]}]
set_property PACKAGE_PIN U8 [get_ports {D[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {D[2]}]
set_property PACKAGE_PIN V8 [get_ports {D[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {D[3]}]
set_property PACKAGE_PIN U5 [get_ports {D[4]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {D[4]}]
set_property PACKAGE_PIN V5 [get_ports {D[5]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {D[5]}]
set_property PACKAGE_PIN U7 [get_ports {D[6]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {D[6]}]