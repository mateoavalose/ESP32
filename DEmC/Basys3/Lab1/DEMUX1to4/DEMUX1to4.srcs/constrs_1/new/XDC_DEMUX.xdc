## This file is a general .xdc for the Basys3 rev B board
## To use it in a project:
## - uncomment the lines corresponding to used pins
## - rename the used ports (in each line, after get_ports) according to the top level signal names in the project

# Switches
set_property PACKAGE_PIN V17 [get_ports {S[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {S[0]}]
set_property PACKAGE_PIN V16 [get_ports {S[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {S[1]}]
	
set_property PACKAGE_PIN W2 [get_ports {I[0]}]		
	set_property IOSTANDARD LVCMOS33 [get_ports {I[0]}]
set_property PACKAGE_PIN U1 [get_ports {I[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {I[1]}]
set_property PACKAGE_PIN T1 [get_ports {I[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {I[2]}]
set_property PACKAGE_PIN R2 [get_ports {I[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {I[3]}]
 
# LEDs
set_property PACKAGE_PIN U16 [get_ports {O4[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O4[0]}]
set_property PACKAGE_PIN E19 [get_ports {O4[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O4[1]}]
set_property PACKAGE_PIN U19 [get_ports {O4[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O4[2]}]
set_property PACKAGE_PIN V19 [get_ports {O4[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O4[3]}]
	
set_property PACKAGE_PIN W18 [get_ports {O3[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O3[0]}]
set_property PACKAGE_PIN U15 [get_ports {O3[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O3[1]}]
set_property PACKAGE_PIN U14 [get_ports {O3[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O3[2]}]
set_property PACKAGE_PIN V14 [get_ports {O3[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O3[3]}]
	
set_property PACKAGE_PIN V13 [get_ports {O2[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O2[0]}]
set_property PACKAGE_PIN V3 [get_ports {O2[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O2[1]}]
set_property PACKAGE_PIN W3 [get_ports {O2[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O2[2]}]
set_property PACKAGE_PIN U3 [get_ports {O2[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O2[3]}]
	
set_property PACKAGE_PIN P3 [get_ports {O1[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O1[0]}]
set_property PACKAGE_PIN N3 [get_ports {O1[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O1[1]}]
set_property PACKAGE_PIN P1 [get_ports {O1[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O1[2]}]
set_property PACKAGE_PIN L1 [get_ports {O1[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O1[3]}]