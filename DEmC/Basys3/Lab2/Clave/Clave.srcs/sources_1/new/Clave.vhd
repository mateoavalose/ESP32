----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/04/2024 07:44:06 PM
-- Design Name: 
-- Module Name: Clave - Behavioral
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
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Clave is
    Port ( RST : in STD_LOGIC;
           CLK : in STD_LOGIC;
           Pul1 : in STD_LOGIC;
           Pul2 : in STD_LOGIC;
           Pul3 : in STD_LOGIC;
           R : out STD_LOGIC;
           W : out STD_LOGIC);
end Clave;

architecture Behavioral of Clave is

Type state is (zero, one, two, three, four, five, six, seven, eight, nine);
signal actual : state := zero;

begin

Machine:
    process (CLK, RST)
        begin
         if(RST = '1' AND NOT(actual = eight)) then
            actual <= zero;
         elsif rising_edge (CLK) then
            case (actual) is
                when zero =>
                    if (Pul1 = '0' AND Pul2 = '0' AND Pul3 = '0') then
                        actual <= zero;
                    elsif (Pul1 = '1' AND Pul2 = '0' AND Pul3 = '0') then
                        actual <= one;
                    else
                        actual <= five;
                    end if;
                when one =>
                    if (Pul1 = '0' AND Pul2 = '0' AND Pul3 = '0') then
                        actual <= one;
                    elsif (Pul1 = '0' AND Pul2 = '0' AND Pul3 = '1') then
                        actual <= two;
                    else
                        actual <= six;
                    end if;
                when two =>
                    if (Pul1 = '0' AND Pul2 = '0' AND Pul3 = '0') then
                        actual <= two;
                    elsif (Pul1 = '1' AND Pul2 = '0' AND Pul3 = '0') then
                        actual <= three;
                    else
                        actual <= seven;
                    end if;
                when three =>
                    if (Pul1 = '0' AND Pul2 = '0' AND Pul3 = '0') then
                        actual <= three;
                    elsif (Pul1 = '0' AND Pul2 = '1' AND Pul3 = '0') then
                        actual <= four;
                    else
                        actual <= eight;
                    end if;
                when four =>
                    if (Pul1 = '0' AND Pul2 = '0' AND Pul3 = '0') then
                        actual <= four;
                    elsif ((Pul1 = '0' AND Pul2 = '1' AND Pul3 = '1') OR (Pul1 = '1' AND Pul2 = '0' AND Pul3 = '1') OR (Pul1 = '1' AND Pul2 = '1' AND Pul3 = '0')) then
                        actual <= nine;
                    end if;
                when five =>
                    if (Pul1 = '0' AND Pul2 = '0' AND Pul3 = '0') then
                        actual <= five;
                    else
                        actual <= six;
                    end if;
                when six =>
                    if (Pul1 = '0' AND Pul2 = '0' AND Pul3 = '0') then
                        actual <= six;
                    else
                        actual <= seven;
                    end if;
                when seven =>
                    if (Pul1 = '0' AND Pul2 = '0' AND Pul3 = '0') then
                        actual <= seven;
                    else
                        actual <= eight;
                    end if;
                when eight =>
                    if ((Pul1 = '0' AND Pul2 = '1' AND Pul3 = '1') OR (Pul1 = '1' AND Pul2 = '0' AND Pul3 = '1') OR (Pul1 = '1' AND Pul2 = '1' AND Pul3 = '0')) then
                        actual <= nine;
                    else
                        actual <= eight;
                    end if;
                when nine =>
                    if (Pul1 = '0' AND Pul2 = '0' AND Pul3 = '0') then
                        actual <= zero;
                    end if;
            end case;
        end if;
    end process Machine;

Outputs:
    process (actual)
        begin
            case (actual) is
                when four =>
                    R <= '1';
                    W <= '0';
                when eight =>
                    R <= '0';
                    W <= '1';
                when nine =>
                    R <= '1';
                    W <= '1';
                when others =>
                    R <= '0';
                    W <= '0';
            end case;
    end process Outputs;
end Behavioral;