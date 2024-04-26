----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/04/2024 09:40:18 AM
-- Design Name: 
-- Module Name: CLK_80Hz - Behavioral
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

entity CLK_80Hz is
    Port ( IR100A : in STD_LOGIC;
           OR1A : out STD_LOGIC);
end CLK_80Hz;

architecture Behavioral of CLK_80Hz is
signal aux1 : integer range 0 to 100000000 := 0;
signal x1 : STD_LOGIC;
begin
process (IR100A)
    begin
        if rising_edge (IR100A) then
            aux1 <= aux1 + 1;
            if (aux1 = 10000) then
                x1 <= NOT x1;
                aux1 <= 0;
            end if;
        end if;
end process;
OR1A <= x1;
end Behavioral;