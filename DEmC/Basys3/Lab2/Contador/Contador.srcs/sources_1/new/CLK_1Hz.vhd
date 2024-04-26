----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/26/2024 08:16:28 AM
-- Design Name: 
-- Module Name: CLK_1Hz - Behavioral
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

entity CLK_1Hz is
    Port ( IR100 : in STD_LOGIC;
           OR1 : out STD_LOGIC);
end CLK_1Hz;

architecture Behavioral of CLK_1Hz is
signal aux : integer range 0 to 1000000000 := 0;
signal x : STD_LOGIC;
begin
process (IR100)
    begin
        if rising_edge (IR100) then
            aux <= aux + 1;
            
            if (aux = 49999999) then
                x <= NOT x;
                aux <= 0;
            end if;
        end if;
end process;
OR1 <= x;
end Behavioral;