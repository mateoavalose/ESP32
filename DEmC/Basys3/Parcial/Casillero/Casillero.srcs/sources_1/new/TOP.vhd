----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/21/2024 09:01:14 AM
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
           But1 : in STD_LOGIC;
           But2 : in STD_LOGIC;
           But3 : in STD_LOGIC;
           But4 : in STD_LOGIC;
           But5 : in STD_LOGIC;
           LEDAbierto : out STD_LOGIC;
           LEDErroneo : out STD_LOGIC;
           Disp7seg : out STD_LOGIC_VECTOR (6 downto 0)
           OUTState : out STD_LOGIC_VECTOR (3 downto 0));
end TOP;

architecture Behavioral of TOP is
component CLK_1Hz is
    Port ( IR100 : in STD_LOGIC;
           OR1 : out STD_LOGIC);
end component;
component Casillero is
    Port ( CLK : in STD_LOGIC;
           B12 : in STD_LOGIC;
           B34 : in STD_LOGIC;
           B56 : in STD_LOGIC;
           B78 : in STD_LOGIC;
           B90 : in STD_LOGIC;
           L1 : out STD_LOGIC;
           L2 : out STD_LOGIC;
           D7seg : out STD_LOGIC_VECTOR (6 downto 0));
end component;
signal AuxCLK : STD_LOGIC;
begin
B0: CLK_1Hz PORT MAP(CLKin, AuxCLK);
B1: Casillero PORT MAP(AuxCLK, But1, But2, But3, But4, But5, LEDAbierto, LEDErroneo, Disp7seg, OUTState);
end Behavioral;