----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/04/2024 09:40:18 AM
-- Design Name: 
-- Module Name: CLK_3KHz - Behavioral
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

entity CLK_3KHz is
    Port ( IR100B : in STD_LOGIC;
           OR1B : out STD_LOGIC);
end CLK_3KHz;

architecture Behavioral of CLK_3KHz is
signal aux2 : integer range 0 to 100000000 := 0;
signal x2 : STD_LOGIC;
begin
process (IR100B)
    begin
        if rising_edge (IR100B) then
            aux2 <= aux2 + 1;
            if (aux2 = 33333) then
                x2 <= NOT x2;
                aux2 <= 0;
            end if;
        end if;
end process;
OR1B <= x2;
end Behavioral;