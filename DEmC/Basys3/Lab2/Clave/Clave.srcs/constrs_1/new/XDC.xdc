## This file is a general .xdc for the Basys3 rev B board
## To use it in a project:
## - uncomment the lines corresponding to used pins
## - rename the used ports (in each line, after get_ports) according to the top level signal names in the project

# Clock signal
set_property PACKAGE_PIN W5 [get_ports CLKin]							
	set_property IOSTANDARD LVCMOS33 [get_ports CLKin]
	create_clock -add -name sys_clk_pin -period 10.00 -waveform {0 5} [get_ports CLKin]


# LEDs
set_property PACKAGE_PIN U16 [get_ports {Rout}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Rout}]
set_property PACKAGE_PIN L1 [get_ports {Wout}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Wout}]
	

##Buttons
set_property PACKAGE_PIN U18 [get_ports Y]						
	set_property IOSTANDARD LVCMOS33 [get_ports Y]
#set_property PACKAGE_PIN T18 [get_ports btnU]						
	#set_property IOSTANDARD LVCMOS33 [get_ports btnU]
set_property PACKAGE_PIN W19 [get_ports X]						
	set_property IOSTANDARD LVCMOS33 [get_ports X]
set_property PACKAGE_PIN T17 [get_ports Z]						
	set_property IOSTANDARD LVCMOS33 [get_ports Z]
set_property PACKAGE_PIN U17 [get_ports Reinicio]						
	set_property IOSTANDARD LVCMOS33 [get_ports Reinicio]