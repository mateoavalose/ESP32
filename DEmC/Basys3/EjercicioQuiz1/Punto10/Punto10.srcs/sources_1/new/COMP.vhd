----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/21/2024 09:34:21 PM
-- Design Name: 
-- Module Name: COMP - Behavioral
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

entity COMP is
    Port ( x : in STD_LOGIC_VECTOR (2 downto 0);
           y : in STD_LOGIC_VECTOR (2 downto 0);
           O : out STD_LOGIC);
end COMP;

architecture Behavioral of COMP is
begin
O <= '1' when (x < y) else '0';              
end Behavioral;