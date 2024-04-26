----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/04/2024 10:37:06 AM
-- Design Name: 
-- Module Name: CLK_10Hz - Behavioral
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

entity CLK_10Hz is
    Port ( IR100E : in STD_LOGIC;
           OR1E : out STD_LOGIC);
end CLK_10Hz;

architecture Behavioral of CLK_10Hz is
signal aux5 : integer range 0 to 100000000 := 0;
signal x5 : STD_LOGIC;
begin
process (IR100E)
    begin
        if rising_edge (IR100E) then
            aux5 <= aux5 + 1;
            if (aux5 = 9999999) then
                x5 <= NOT x5;
                aux5 <= 0;
            end if;
        end if;
    end process;
OR1E <= x5;
end Behavioral;