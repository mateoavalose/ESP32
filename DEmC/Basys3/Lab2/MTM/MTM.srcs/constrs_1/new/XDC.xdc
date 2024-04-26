## This file is a general .xdc for the Basys3 rev B board
## To use it in a project:
## - uncomment the lines corresponding to used pins
## - rename the used ports (in each line, after get_ports) according to the top level signal names in the project

# Clock signal
set_property PACKAGE_PIN W5 [get_ports CLK]							
	set_property IOSTANDARD LVCMOS33 [get_ports CLK]
	create_clock -add -name sys_clk_pin -period 10.00 -waveform {0 5} [get_ports CLK]

# LEDs 
set_property PACKAGE_PIN U16 [get_ports {Oled[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Oled[0]}]
set_property PACKAGE_PIN E19 [get_ports {Oled[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Oled[1]}]
set_property PACKAGE_PIN U19 [get_ports {Oled[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Oled[2]}]
set_property PACKAGE_PIN V19 [get_ports {Oled[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Oled[3]}]
set_property PACKAGE_PIN W18 [get_ports {Oled[4]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Oled[4]}]
set_property PACKAGE_PIN U15 [get_ports {Oled[5]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Oled[5]}]
set_property PACKAGE_PIN U14 [get_ports {Oled[6]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Oled[6]}]
set_property PACKAGE_PIN V14 [get_ports {Oled[7]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Oled[7]}]
set_property PACKAGE_PIN V13 [get_ports {Oled[8]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Oled[8]}]
set_property PACKAGE_PIN V3 [get_ports {Oled[9]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Oled[9]}]
set_property PACKAGE_PIN W3 [get_ports {Oled[10]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Oled[10]}]
set_property PACKAGE_PIN U3 [get_ports {Oled[11]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Oled[11]}]
set_property PACKAGE_PIN P3 [get_ports {Oled[12]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Oled[12]}]
set_property PACKAGE_PIN N3 [get_ports {Oled[13]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Oled[13]}]
set_property PACKAGE_PIN P1 [get_ports {Oled[14]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Oled[14]}]
set_property PACKAGE_PIN L1 [get_ports {Oled[15]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {Oled[15]}]
	
	
#7 segment display 
set_property PACKAGE_PIN W7 [get_ports {O7seg[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O7seg[0]}]
set_property PACKAGE_PIN W6 [get_ports {O7seg[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O7seg[1]}]
set_property PACKAGE_PIN U8 [get_ports {O7seg[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O7seg[2]}]
set_property PACKAGE_PIN V8 [get_ports {O7seg[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O7seg[3]}]
set_property PACKAGE_PIN U5 [get_ports {O7seg[4]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O7seg[4]}]
set_property PACKAGE_PIN V5 [get_ports {O7seg[5]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O7seg[5]}]
set_property PACKAGE_PIN U7 [get_ports {O7seg[6]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O7seg[6]}]

set_property PACKAGE_PIN U2 [get_ports {GND7seg[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {GND7seg[0]}]
set_property PACKAGE_PIN U4 [get_ports {GND7seg[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {GND7seg[1]}]
set_property PACKAGE_PIN V4 [get_ports {GND7seg[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {GND7seg[2]}]
set_property PACKAGE_PIN W4 [get_ports {GND7seg[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {GND7seg[3]}]
	

##Buttons
set_property PACKAGE_PIN U18 [get_ports Pul]						
	set_property IOSTANDARD LVCMOS33 [get_ports Pul]
set_property PACKAGE_PIN U17 [get_ports PT]						
	set_property IOSTANDARD LVCMOS33 [get_ports PT]