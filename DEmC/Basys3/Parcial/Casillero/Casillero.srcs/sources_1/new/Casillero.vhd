----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/21/2024 08:36:44 AM
-- Design Name: 
-- Module Name: Casillero - Behavioral
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

entity Casillero is
    Port ( CLK : in STD_LOGIC;
           B12 : in STD_LOGIC;
           B34 : in STD_LOGIC;
           B56 : in STD_LOGIC;
           B78 : in STD_LOGIC;
           B90 : in STD_LOGIC;
           L1 : out STD_LOGIC;
           L2 : out STD_LOGIC;
           D7seg : out STD_LOGIC_VECTOR (6 downto 0)
           stateLED : out STD_LOGIC_VECTOR (3 downto 0));
end Casillero;

architecture Behavioral of Casillero is
signal aux3 : integer range 0 to 10 := 0;
signal aux6 : integer range 0 to 15 := 0;
signal fin3 : STD_LOGIC := '0';
signal fin6 : STD_LOGIC := '0';
Type state is (zero, one, two, three, four, five, six);
signal actual : state := zero;

begin

Machine:
    process (CLK)
        begin
         if rising_edge (CLK) then
            case (actual) is
                when zero =>
                    if (B12 = '0' AND B34 = '0' AND B56 = '0' AND B78 = '0' AND B90 = '0') then
                        actual <= zero;
                    elsif (B12 = '1' AND B34 = '0' AND B56 = '0' AND B78 = '0' AND B90 = '0') then
                        actual <= one;
                    else
                        actual <= four;
                    end if;
                when one =>
                    if (B12 = '0' AND B34 = '0' AND B56 = '0' AND B78 = '0' AND B90 = '0') then
                        actual <= one;
                    elsif (B12 = '1' AND B34 = '0' AND B56 = '0' AND B78 = '0' AND B90 = '0') then
                        actual <= two;
                    else
                        actual <= five;
                    end if;
                when two =>
                    if (B12 = '0' AND B34 = '0' AND B56 = '0' AND B78 = '0' AND B90 = '0') then
                        actual <= two;
                    elsif (B12 = '0' AND B34 = '0' AND B56 = '1' AND B78 = '0' AND B90 = '0') then
                        actual <= three;
                    else
                        actual <= six;
                    end if;
                when three =>
                        actual <= three;
                        if (fin3 = '1') then
                            actual <= zero;
                        end if;
                when four =>
                    if (B12 = '0' AND B34 = '0' AND B56 = '0' AND B78 = '0' AND B90 = '0') then
                        actual <= four;
                    else
                        actual <= five;
                    end if;
                when five =>
                    if (B12 = '0' AND B34 = '0' AND B56 = '0' AND B78 = '0' AND B90 = '0') then
                        actual <= five;
                    else
                        actual <= six;
                    end if;
                when six =>
                        actual <= six;
                        if (fin6 = '1') then
                            actual <= zero;
                        end if;
                        
            end case;
        end if;
    end process Machine;
    
Outputs:
    process (actual, CLK)
        begin
            case (actual) is
                when three =>
                    stateLED <= "0011";
                    L1 <= '1';
                    L2 <= '0';
                    if rising_edge (CLK) then
                        case (aux3) is
                            when 0 => D7seg <= "1000000";
                            when 1 => D7seg <= "1111001";
                            when 2 => D7seg <= "0100100";
                            when 3 => D7seg <= "0110000";
                            when 4 => D7seg <= "0011001";
                            when 5 => D7seg <= "0010010";
                            when 6 => D7seg <= "0000010";
                            when 7 => D7seg <= "1111000";
                            when 8 => D7seg <= "0000000";
                            when 9 => D7seg <= "0011000";
                            when others => D7seg <= "1111111";
                            end case;     
                        if (aux3 = 9) then
                            aux3 <= 0;
                            fin3 <= '1';
                        else
                            aux3 <= aux3 + 1;
                        end if;
                    end if;
                when six =>
                    stateLED <= "0101";
                    L1 <= '0';
                    L2 <= '1';
                    D7seg <= "1111111";
                    if rising_edge (CLK) then
                        if (aux6 = 14) then
                            aux6 <= 0;
                            fin6 <= '1';
                        else
                            aux6 <= aux6 + 1;
                        end if;
                    end if;
                when others =>
                    stateLED <= "1111";
                    L1 <= '0';
                    L2 <= '0';
                    D7seg <= "1111111";
                    fin3 <= '0';
                    fin6 <= '0';
            end case;
    end process Outputs;
    
end Behavioral;
