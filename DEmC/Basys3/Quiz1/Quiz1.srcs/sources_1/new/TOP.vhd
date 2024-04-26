----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/22/2024 08:57:27 AM
-- Design Name: 
-- Module Name: TOP - Behavioral
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

entity TOP is
    Port ( P1 : in STD_LOGIC_VECTOR (2 downto 0);
           P2 : in STD_LOGIC_VECTOR (2 downto 0);
           V : in STD_LOGIC;
           LED_Out : out STD_LOGIC_VECTOR (2 downto 0);
           BCD_Out : out STD_LOGIC_VECTOR (6 downto 0));
end TOP;
architecture Behavioral of TOP is
    component COMP is
        Port( R1 : in STD_LOGIC;
              P1 : in STD_LOGIC;
              S1 : in STD_LOGIC;
              R2 : in STD_LOGIC;
              P2 : in STD_LOGIC;
              S2 : in STD_LOGIC;
              V : in STD_LOGIC;
              Win1 : out STD_LOGIC;
              Win2 : out STD_LOGIC;
              Tie : out STD_LOGIC);
    end component;
    component DECO is
        Port( Ideco : in STD_LOGIC_VECTOR (1 downto 0);
              Odeco : out STD_LOGIC_VECTOR (3 downto 0);
              V : in STD_LOGIC);
    end component;
    component BCD_7SEG is
        Port( Ibcd : in STD_LOGIC_VECTOR (3 downto 0);
              Obcd : out STD_LOGIC_VECTOR (6 downto 0));
    end component;
signal bcdIN : STD_LOGIC_VECTOR (3 downto 0);
signal LEDaux : STD_LOGIC_VECTOR (2 downto 0);
signal DECOaux : STD_LOGIC_VECTOR (1 downto 0);
begin
    B0: COMP PORT MAP(P1(0), P1(1), P1(2), P2(0), P2(1), P2(2), V, LEDaux(0), LEDaux(1), LEDaux(2));
DECOaux <= LEDaux(1) & LEDaux(0);
    B1: DECO PORT MAP(DECOaux, bcdIN, V);
    B2: BCD_7SEG PORT MAP(bcdIN, BCD_Out);
LED_Out <= LEDaux;
end Behavioral;
