----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/21/2024 09:34:21 PM
-- Design Name: 
-- Module Name: BCD_7SEG - Behavioral
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

entity BCD_7SEG is
    Port ( BCD : in STD_LOGIC_VECTOR (3 downto 0);
           O : out STD_LOGIC_VECTOR (6 downto 0));
end BCD_7SEG;

architecture Behavioral of BCD_7SEG is
signal a1 : STD_LOGIC_VECTOR (6 downto 0);
begin
    process (BCD)
          begin
               case (BCD) is
                    when "0000" => 
                        a1 <= "1000000";
                    when "0001" =>
                        a1 <= "1111001";
                    when "0010" => 
                        a1 <= "0100100";
                    when "0011" => 
                        a1 <= "0110000";
                    when "0100" => 
                        a1 <= "0011001";
                    when "0101" => 
                        a1 <= "0010010";
                    when "0110" => 
                        a1 <= "0000010";
                    when "0111" => 
                        a1 <= "1111000";
                    when "1000" => 
                        a1 <= "0000000";
                    when "1001" => 
                        a1 <= "0011000";
                    when others =>
                        a1 <= "1111111";
               end case;
          end process;
O <= a1;

end Behavioral;