----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/04/2024 10:36:17 AM
-- Design Name: 
-- Module Name: LEDSeq - Behavioral
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

entity LEDSeq is
    Port ( E : in STD_LOGIC;
           CLK : in STD_LOGIC;
           Oled : out STD_LOGIC_VECTOR (15 downto 0));
end LEDSeq;

architecture Behavioral of LEDSeq is
signal auxL : STD_LOGIC_VECTOR (15 downto 0) := "0000000000000000";
begin
process (E, CLK)
    begin
        if (rising_edge (CLK) AND E = '1') then
            case (auxL) is
                when "0000000000000000" => auxL <= "1000000000000000";
                when "1000000000000000" => auxL <= "0100000000000000";
                when "0100000000000000" => auxL <= "0010000000000000";
                when "0010000000000000" => auxL <= "0001000000000000";
                when "0001000000000000" => auxL <= "0000100000000000";
                when "0000100000000000" => auxL <= "0000010000000000";
                when "0000010000000000" => auxL <= "0000001000000000";
                when "0000001000000000" => auxL <= "0000000100000000";
                when "0000000100000000" => auxL <= "0000000010000000";
                when "0000000010000000" => auxL <= "0000000001000000";
                when "0000000001000000" => auxL <= "0000000000100000";
                when "0000000000100000" => auxL <= "0000000000010000";
                when "0000000000010000" => auxL <= "0000000000001000";
                when "0000000000001000" => auxL <= "0000000000000100";
                when "0000000000000100" => auxL <= "0000000000000010";
                when "0000000000000010" => auxL <= "0000000000000001";
                when "0000000000000001" => auxL <= "0000000000000000";
                when others             => auxL <= "0000000000000000";
            end case;
        end if;
    end process;
Oled <= auxL;
end Behavioral;