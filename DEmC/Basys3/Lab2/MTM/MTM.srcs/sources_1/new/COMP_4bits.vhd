----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/04/2024 10:22:33 AM
-- Design Name: 
-- Module Name: COMP_4bits - Behavioral
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

entity COMP_4bits is
    Port ( A : in STD_LOGIC_VECTOR (3 downto 0);
           B : in STD_LOGIC_VECTOR (3 downto 0);
           O : out STD_LOGIC);
end COMP_4bits;

architecture Behavioral of COMP_4bits is
signal aux : STD_LOGIC;
begin
process (A, B)
    begin
        if (A > B) then
            aux <= '0';
        end if;
        if (A = B) then
            aux <= '1';
        end if;
        if (A < B) then
            aux <= '0';
        end if;
    end process;
O <= aux;
end Behavioral;