----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/26/2024 08:26:54 AM
-- Design Name: 
-- Module Name: TOP_Contador - Behavioral
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
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity TOP_Contador is
    Port ( I_T : in STD_LOGIC;
           Q_T : out STD_LOGIC_VECTOR (3 downto 0));
end TOP_Contador;

architecture Behavioral of TOP_Contador is
component CLK_1Hz is
    Port ( IR100 : in STD_LOGIC;
           OR1 : out STD_LOGIC);
end component;

component Contador is
    Port ( I : in STD_LOGIC;
           Q : out STD_LOGIC_VECTOR (3 downto 0));
end component;
signal aux1 : STD_LOGIC;
begin
B1 : CLK_1Hz PORT MAP(I_T, aux1);
B2 : Contador PORT MAP(aux1, Q_T);

end Behavioral;
