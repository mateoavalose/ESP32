----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/04/2024 09:40:18 AM
-- Design Name: 
-- Module Name: CLK_7KHz - Behavioral
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

entity CLK_7KHz is
    Port ( IR100D : in STD_LOGIC;
           OR1D : out STD_LOGIC);
end CLK_7KHz;

architecture Behavioral of CLK_7KHz is
signal aux4 : integer range 0 to 100000000 := 0;
signal x4 : STD_LOGIC;
begin
process (IR100D)
    begin
        if rising_edge (IR100D) then
            aux4 <= aux4 + 1;
            if (aux4 = 14284) then
                x4 <= NOT x4;
                aux4 <= 0;
            end if;
        end if;
end process;
OR1D <= x4;
end Behavioral;