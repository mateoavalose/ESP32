----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/27/2024 11:01:10 AM
-- Design Name: 
-- Module Name: MUX4to1 - Behavioral
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

entity MUX4to1 is
    Port ( S : in STD_LOGIC_VECTOR (1 downto 0);
           O : out STD_LOGIC_VECTOR (3 downto 0);
           a : in STD_LOGIC_VECTOR (3 downto 0);
           b : in STD_LOGIC_VECTOR (3 downto 0);
           c : in STD_LOGIC_VECTOR (3 downto 0);
           d : in STD_LOGIC_VECTOR (3 downto 0));
end MUX4to1;

architecture Behavioral of MUX4to1 is
signal a1 : STD_LOGIC_VECTOR(3 downto 0);
begin
 process (S)
        begin
            case (S) is
                when "00" => a1 <= a;
                when "01" => a1 <= b;
                when "10" => a1 <= c;
                when "11" => a1 <= d;
           end case;
      end process;
O <= a1;
end Behavioral;