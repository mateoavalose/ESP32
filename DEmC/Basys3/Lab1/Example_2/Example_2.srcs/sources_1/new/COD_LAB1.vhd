----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/18/2024 06:47:15 PM
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
     Port ( I : in STD_LOGIC_VECTOR (8 downto 0);
	    P : out STD_LOGIC_VECTOR (3 downto 0));
end COD_LAB1;

architecture Behavioral of COD_LAB1 is
 signal a1 : STD_LOGIC_VECTOR (3 downto 0);
begin
     process (I)
          begin
               case (I) is
                    when "000000000" => a1 <= "0000";
                    when "000000001" => a1 <= "0001";
                    when "000000010" => a1 <= "0010";
                    when "000000100" => a1 <= "0011";
                    when "000001000" => a1 <= "0100";
                    when "000010000" => a1 <= "0101";
                    when "000100000" => a1 <= "0110";
                    when "001000000" => a1 <= "0111";
                    when "010000000" => a1 <= "1000";
                    when "100000000" => a1 <= "1001";
                    when others      => a1 <= "1111";
               end case;
          end process;
P <= a1;

end Behavioral;