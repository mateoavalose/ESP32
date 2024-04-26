----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/27/2024 11:03:00 AM
-- Design Name: 
-- Module Name: DECO - Behavioral
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

entity DECO is
    Port ( Sdeco : in STD_LOGIC_VECTOR (1 downto 0);
           Odeco : out STD_LOGIC_VECTOR (3 downto 0));
end DECO;

architecture Behavioral of DECO is
signal a1 : STD_LOGIC_VECTOR(3 downto 0);
begin
process (Sdeco)
          begin
               case (Sdeco) is
                    when "00" => a1 <= "1110";
                    when "01" => a1 <= "1101";
                    when "10" => a1 <= "1011";
                    when "11" => a1 <= "1111";
               end case;
          end process;
Odeco <= a1;
end Behavioral;