----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/18/2024 06:50:59 PM
-- Design Name: 
-- Module Name: TOP_LAB1 - Behavioral
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

entity TOP_LAB1 is
    Port ( T_I : in STD_LOGIC_VECTOR (8 downto 0);
           T_Y : out STD_LOGIC_VECTOR (6 downto 0));
end TOP_LAB1;

architecture Behavioral of TOP_LAB1 is
    component COD_LAB1 is
        Port ( I : in STD_LOGIC_VECTOR (8 downto 0);
               P : out STD_LOGIC_VECTOR (3 downto 0));
    end component;
    component DECO_LAB1 is
        Port ( A : in STD_LOGIC_VECTOR (3 downto 0);
               Y : out STD_LOGIC_VECTOR (6 downto 0));
    end component;
    
    signal aux : STD_LOGIC_VECTOR (3 downto 0);
begin
    B0 : COD_lAB1 PORT MAP(T_I,aux);
    B1 : DECO_LAB1 PORT MAP(aux,T_Y);


end Behavioral;
