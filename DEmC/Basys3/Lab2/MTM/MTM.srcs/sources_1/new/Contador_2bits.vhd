----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/04/2024 10:09:40 AM
-- Design Name: 
-- Module Name: Contador_2bits - Behavioral
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
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Contador_2bits is
    Port ( I2 : in STD_LOGIC;
           Q2 : out STD_LOGIC_VECTOR (1 downto 0));
end Contador_2bits;

architecture Behavioral of Contador_2bits is
signal cont_2: STD_LOGIC_VECTOR (1 downto 0) := "00";
begin
process (I2)
    begin
        if rising_edge (I2) then
            cont_2 <= cont_2 + 1;
        end if;
end process;
Q2 <= cont_2;
end Behavioral;