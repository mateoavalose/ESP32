## This file is a general .xdc for the Basys3 rev B board
## To use it in a project:
## - uncomment the lines corresponding to used pins
## - rename the used ports (in each line, after get_ports) according to the top level signal names in the project
 
# Switches
set_property PACKAGE_PIN V17 [get_ports {P2[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {P2[2]}]
set_property PACKAGE_PIN V16 [get_ports {P2[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {P2[1]}]
set_property PACKAGE_PIN W16 [get_ports {P2[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {P2[0]}]

set_property PACKAGE_PIN U1 [get_ports {P1[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {P1[2]}]
set_property PACKAGE_PIN T1 [get_ports {P1[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {P1[1]}]
set_property PACKAGE_PIN R2 [get_ports {P1[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {P1[0]}]
 

# LEDs
set_property PACKAGE_PIN E19 [get_ports {LED_Out[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {LED_Out[1]}]

set_property PACKAGE_PIN V14 [get_ports {LED_Out[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {LED_Out[2]}]
set_property PACKAGE_PIN V13 [get_ports {LED_Out[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {LED_Out[2]}]

set_property PACKAGE_PIN P1 [get_ports {LED_Out[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {LED_Out[0]}]
	
	
#7 segment display
set_property PACKAGE_PIN W7 [get_ports {BCD_Out[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {BCD_Out[0]}]
set_property PACKAGE_PIN W6 [get_ports {BCD_Out[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {BCD_Out[1]}]
set_property PACKAGE_PIN U8 [get_ports {BCD_Out[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {BCD_Out[2]}]
set_property PACKAGE_PIN V8 [get_ports {BCD_Out[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {BCD_Out[3]}]
set_property PACKAGE_PIN U5 [get_ports {BCD_Out[4]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {BCD_Out[4]}]
set_property PACKAGE_PIN V5 [get_ports {BCD_Out[5]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {BCD_Out[5]}]
set_property PACKAGE_PIN U7 [get_ports {BCD_Out[6]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {BCD_Out[6]}]

##Buttons
set_property PACKAGE_PIN U18 [get_ports V]						
	set_property IOSTANDARD LVCMOS33 [get_ports V]