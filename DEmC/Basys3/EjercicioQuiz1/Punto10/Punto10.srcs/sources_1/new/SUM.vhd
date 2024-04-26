----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/21/2024 09:34:21 PM
-- Design Name: 
-- Module Name: SUM - Behavioral
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

entity SUM is
    Port ( x : in STD_LOGIC_VECTOR (2 downto 0);
           y : in STD_LOGIC_VECTOR (2 downto 0);
           Ci : in STD_LOGIC;
           S : out STD_LOGIC_VECTOR (3 downto 0));
end SUM;

architecture Behavioral of SUM is
signal Carry : STD_LOGIC_VECTOR (4 downto 0);
begin
    process (x, y, Ci, Carry)
        begin
        carry(0) <= Ci;
        for i in 0 to 2 loop
            S(i) <= x(i) XOR y(i) XOR carry(i);
            carry(i+1) <= (x(i) AND y(i)) or (carry(i) AND (x(i) XOR y(i)));
            end loop;
        S(3) <= carry(3);
    end process;
end Behavioral;