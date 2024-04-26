----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/04/2024 09:03:09 PM
-- Design Name: 
-- Module Name: TOP - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity TOP is
    Port ( CLKin : in STD_LOGIC;
           Reinicio : in STD_LOGIC;
           X : in STD_LOGIC;
           Y : in STD_LOGIC;
           Z : in STD_LOGIC;
           Rout : out STD_LOGIC;
           Wout : out STD_LOGIC);
end TOP;

architecture Behavioral of TOP is
component CLK_1Hz is
    Port ( IR100 : in STD_LOGIC;
           OR1 : out STD_LOGIC);
end component;
component Clave is
    Port ( RST : in STD_LOGIC;
           CLK : in STD_LOGIC;
           Pul1 : in STD_LOGIC;
           Pul2 : in STD_LOGIC;
           Pul3 : in STD_LOGIC;
           R : out STD_LOGIC;
           W : out STD_LOGIC);
end component;
signal AuxCLK : STD_LOGIC;

begin
B0: CLK_1Hz PORT MAP(CLKin,AuxCLK);
B1: Clave PORT MAP(Reinicio, AuxCLK, X, Y, Z, Rout, Wout);
end Behavioral;