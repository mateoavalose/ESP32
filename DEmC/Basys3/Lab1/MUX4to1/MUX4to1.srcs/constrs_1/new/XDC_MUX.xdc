## This file is a general .xdc for the Basys3 rev B board
## To use it in a project:
## - uncomment the lines corresponding to used pins
## - rename the used ports (in each line, after get_ports) according to the top level signal names in the project

# Switches
set_property PACKAGE_PIN V17 [get_ports {d[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {d[0]}]
set_property PACKAGE_PIN V16 [get_ports {d[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {d[1]}]
set_property PACKAGE_PIN W16 [get_ports {d[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {d[2]}]
set_property PACKAGE_PIN W17 [get_ports {d[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {d[3]}]
set_property PACKAGE_PIN W15 [get_ports {c[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {c[0]}]
set_property PACKAGE_PIN V15 [get_ports {c[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {c[1]}]
set_property PACKAGE_PIN W14 [get_ports {c[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {c[2]}]
set_property PACKAGE_PIN W13 [get_ports {c[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {c[3]}]
set_property PACKAGE_PIN V2 [get_ports {b[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {b[0]}]
set_property PACKAGE_PIN T3 [get_ports {b[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {b[1]}]
set_property PACKAGE_PIN T2 [get_ports {b[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {b[2]}]
set_property PACKAGE_PIN R3 [get_ports {b[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {b[3]}]
set_property PACKAGE_PIN W2 [get_ports {a[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {a[0]}]
set_property PACKAGE_PIN U1 [get_ports {a[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {a[1]}]
set_property PACKAGE_PIN T1 [get_ports {a[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {a[2]}]
set_property PACKAGE_PIN R2 [get_ports {a[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {a[3]}]
 

# LEDs
set_property PACKAGE_PIN U16 [get_ports {O[0]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O[0]}]
set_property PACKAGE_PIN E19 [get_ports {O[1]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O[1]}]
set_property PACKAGE_PIN U19 [get_ports {O[2]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O[2]}]
set_property PACKAGE_PIN V19 [get_ports {O[3]}]					
	set_property IOSTANDARD LVCMOS33 [get_ports {O[3]}]

##Buttons
set_property PACKAGE_PIN W19 [get_ports S[1]]						
	set_property IOSTANDARD LVCMOS33 [get_ports S[1]]
set_property PACKAGE_PIN T17 [get_ports S[0]]						
	set_property IOSTANDARD LVCMOS33 [get_ports S[0]]