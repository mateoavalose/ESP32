----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/22/2024 08:44:06 AM
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
    Port ( R1 : in STD_LOGIC;
           P1 : in STD_LOGIC;
           S1 : in STD_LOGIC;
           R2 : in STD_LOGIC;
           P2 : in STD_LOGIC;
           S2 : in STD_LOGIC;
           V : in STD_LOGIC;
           Win1 : out STD_LOGIC;
           Win2 : out STD_LOGIC;
           Tie : out STD_LOGIC);
end COMP;

architecture Behavioral of COMP is

begin
Win1 <= ((R1 AND S2) OR (P1 AND R2) OR (S1 AND P2)) AND V;
Win2 <= ((R2 AND S1) OR (P2 AND R1) OR (S2 AND P1)) AND V;
Tie <= ((R1 AND R2) OR (P1 AND P2) OR (S1 AND S2)) AND V;
end Behavioral;
