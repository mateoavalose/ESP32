----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/22/2024 08:44:06 AM
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
    Port ( Ideco : in STD_LOGIC_VECTOR (1 downto 0);
           Odeco : out STD_LOGIC_VECTOR (3 downto 0);
           V : in STD_LOGIC);
end DECO;

architecture Behavioral of DECO is
signal a2 : STD_LOGIC_VECTOR(3 downto 0);
begin
    process (Ideco)
        begin
            case (Ideco) is
                when "00" =>
                    a2 <= "0000";
                when "01" =>
                    a2 <= "0001";
                when "10" =>
                    a2 <= "0010";
                when others =>
                    a2 <= "1111";
           end case;
    end process;
Odeco <= a2 when V = '1' else "1111";
end Behavioral;
