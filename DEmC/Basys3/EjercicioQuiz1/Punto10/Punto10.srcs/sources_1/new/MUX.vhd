----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/21/2024 09:34:21 PM
-- Design Name: 
-- Module Name: MUX - Behavioral
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

entity MUX is
    Port ( x : in STD_LOGIC_VECTOR (3 downto 0);
           y : in STD_LOGIC_VECTOR (3 downto 0);
           s : in STD_LOGIC;
           O : out STD_LOGIC_VECTOR (3 downto 0));
          
end MUX;

architecture Behavioral of MUX is
    signal a1 : STD_LOGIC_VECTOR (3 downto 0);
begin
    process (s)
        begin
            case (s) is
                when '0' => a1 <= x;
                when '1' => a1 <= y;
                when others => a1 <= "0000";
           end case;
      end process;
O <= a1;
end Behavioral;