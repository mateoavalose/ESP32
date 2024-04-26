----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/04/2024 09:41:13 AM
-- Design Name: 
-- Module Name: CLK_5KHz - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity CLK_5KHz is
    Port ( IR100C : in STD_LOGIC;
           OR1C : out STD_LOGIC);
end CLK_5KHz;

architecture Behavioral of CLK_5KHz is
signal aux3 : integer range 0 to 100000000 := 0;
signal x3 : STD_LOGIC;
begin
process (IR100C)
    begin
        if rising_edge (IR100C) then
            aux3 <= aux3 + 1;
            if (aux3 = 19999) then
                x3 <= NOT x3;
                aux3 <= 0;
            end if;
        end if;
end process;
OR1C <= x3;
end Behavioral;