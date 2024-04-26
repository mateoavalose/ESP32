## This file is a general .xdc for the Basys3 rev B board
## To use it in a project:
## - uncomment the lines corresponding to used pins
## - rename the used ports (in each line, after get_ports) according to the top level signal names in the project

# Clock signal
set_property PACKAGE_PIN W5 [get_ports CLKin]							
	set_property IOSTANDARD LVCMOS33 [get_ports CLKin]
	create_clock -add -name sys_clk_pin -period 10.00 -waveform {0 5} [get_ports CLKin]

# LEDs
set_property PACKAGE_PIN U16 [get_ports {LEDAbierto}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {LEDAbierto}]
set_property PACKAGE_PIN L1 [get_ports {LEDErroneo}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {LEDErroneo}]
	
set_property PACKAGE_PIN V14 [get_ports {OUTState[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {OUTState[0]}]
set_property PACKAGE_PIN V13 [get_ports {OUTState[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {OUTState[1]}]
set_property PACKAGE_PIN V3 [get_ports {OUTState[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {OUTState[2]}]
set_property PACKAGE_PIN W3 [get_ports {OUTState[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {OUTState[3]}]
	
	
#7 segment display
set_property PACKAGE_PIN W7 [get_ports {Disp7seg[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Disp7seg[0]}]
set_property PACKAGE_PIN W6 [get_ports {Disp7seg[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Disp7seg[1]}]
set_property PACKAGE_PIN U8 [get_ports {Disp7seg[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Disp7seg[2]}]
set_property PACKAGE_PIN V8 [get_ports {Disp7seg[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Disp7seg[3]}]
set_property PACKAGE_PIN U5 [get_ports {Disp7seg[4]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Disp7seg[4]}]
set_property PACKAGE_PIN V5 [get_ports {Disp7seg[5]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Disp7seg[5]}]
set_property PACKAGE_PIN U7 [get_ports {Disp7seg[6]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Disp7seg[6]}]


##Buttons
set_property PACKAGE_PIN U18 [get_ports But3]						
	set_property IOSTANDARD LVCMOS33 [get_ports But3]
set_property PACKAGE_PIN T18 [get_ports But1]						
	set_property IOSTANDARD LVCMOS33 [get_ports But1]
set_property PACKAGE_PIN W19 [get_ports But2]						
	set_property IOSTANDARD LVCMOS33 [get_ports But2]
set_property PACKAGE_PIN T17 [get_ports But4]						
	set_property IOSTANDARD LVCMOS33 [get_ports But4]
set_property PACKAGE_PIN U17 [get_ports But5]						
	set_property IOSTANDARD LVCMOS33 [get_ports But5]