----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/18/2024 07:31:38 PM
-- Design Name: 
-- Module Name: COD_LAB1 - Behavioral
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

entity COD_LAB1 is
    Port ( B : in STD_LOGIC_VECTOR (3 downto 0);
           D : out STD_LOGIC_VECTOR (6 downto 0);
           O : out STD_LOGIC_VECTOR (8 downto 0));
end COD_LAB1;

architecture Behavioral of COD_LAB1 is
signal a1 : STD_LOGIC_VECTOR (6 downto 0);
signal a2: STD_LOGIC_VECTOR (8 downto 0);
begin
    process (B)
          begin
               case (B) is
                    when "0000" => 
                        a1 <= "1000000";
                        a2 <= "000000000";
                    when "0001" =>
                        a1 <= "1111001";
                        a2 <= "000000001";
                    when "0010" => 
                        a1 <= "0100100";
                        a2 <= "000000011";
                    when "0011" => 
                        a1 <= "0110000";
                        a2 <= "000000111";
                    when "0100" => 
                        a1 <= "0011001";
                        a2 <= "000001111";
                    when "0101" => 
                        a1 <= "0010010";
                        a2 <= "000011111";
                    when "0110" => 
                        a1 <= "0000010";
                        a2 <= "000111111";
                    when "0111" => 
                        a1 <= "1111000";
                        a2 <= "001111111";
                    when "1000" => 
                        a1 <= "0000000";
                        a2 <= "011111111";
                    when "1001" => 
                        a1 <= "0011000";
                        a2 <= "111111111";
                    when others =>
                        a1 <= "1111111";
                        a2 <= "000000000";
               end case;
          end process;
D <= a1;
O <= a2;
end Behavioral;
