----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/04/2024 10:09:40 AM
-- Design Name: 
-- Module Name: Ccontador_4bits - Behavioral
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

entity Contador_4bits is
    Port ( I1 : in STD_LOGIC;
           Q1 : out STD_LOGIC_VECTOR (3 downto 0));
end Contador_4bits;

architecture Behavioral of Contador_4bits is
signal cont_1 : STD_LOGIC_VECTOR (3 downto 0) := "0000";
begin
process (I1)
    begin
        if rising_edge (I1) then
            cont_1 <= cont_1 + 1;
            if (cont_1 >= "1001") then
                cont_1 <= "0000"; 
            end if;
        end if;
end process;
Q1 <= cont_1;
end Behavioral;