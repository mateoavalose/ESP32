----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/19/2024 09:49:29 AM
-- Design Name: 
-- Module Name: DEMUX - Behavioral
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

entity DEMUX is
    Port ( I : in STD_LOGIC_VECTOR (3 downto 0);
           S : in STD_LOGIC_VECTOR (1 downto 0);
           O1 : out STD_LOGIC_VECTOR (3 downto 0);
           O2 : out STD_LOGIC_VECTOR (3 downto 0);
           O3 : out STD_LOGIC_VECTOR (3 downto 0);
           O4 : out STD_LOGIC_VECTOR (3 downto 0));
end DEMUX;

architecture Behavioral of DEMUX is
    signal a1 : STD_LOGIC_VECTOR (3 downto 0);
begin
    process (S)
        begin
            case (S) is
                when "00" => 
                    O1 <= I;
                    O2 <= "0000";
                    O3 <= "0000";
                    O4 <= "0000";
                when "01" => 
                    O1 <= "0000";
                    O2 <= I;
                    O3 <= "0000";
                    O4 <= "0000";
                when "10" => 
                    O1 <= "0000";
                    O2 <= "0000";
                    O3 <= I;
                    O4 <= "0000";
                when "11" => 
                    O1 <= "0000";
                    O2 <= "0000";
                    O3 <= "0000";
                    O4 <= I;
                when others => a1 <= "0000";
           end case;
      end process;

end Behavioral;