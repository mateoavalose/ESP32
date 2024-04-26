----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/27/2024 10:58:55 AM
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
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity TOP is
    Port ( CLK : in STD_LOGIC;
           Pul : in STD_LOGIC;
           PT : in STD_LOGIC;
           O7seg : out STD_LOGIC_VECTOR (6 downto 0);
           GND7seg : out STD_LOGIC_VECTOR (3 downto 0);
           Oled : out STD_LOGIC_VECTOR (15 downto 0));
end TOP;

architecture Behavioral of TOP is
component BCD_7SEG is
    Port ( Ibcd : in STD_LOGIC_VECTOR (3 downto 0);
           Oseg : out STD_LOGIC_VECTOR (6 downto 0));
end component;
component CLK_80Hz is
    Port ( IR100A : in STD_LOGIC;
           OR1A : out STD_LOGIC);
end component;
component CLK_3KHz is
    Port ( IR100B : in STD_LOGIC;
           OR1B : out STD_LOGIC);
end component;
component CLK_5KHz is
    Port ( IR100C : in STD_LOGIC;
           OR1C : out STD_LOGIC);
end component;
component CLK_7KHz is
    Port ( IR100D : in STD_LOGIC;
           OR1D : out STD_LOGIC);
end component;
component CLK_10Hz is
    Port ( IR100E : in STD_LOGIC;
           OR1E : out STD_LOGIC);
end component;
component COMP_4bits is
    Port ( A : in STD_LOGIC_VECTOR (3 downto 0);
           B : in STD_LOGIC_VECTOR (3 downto 0);
           O : out STD_LOGIC);
end component;
component Contador_4bits is
    Port ( I1 : in STD_LOGIC;
           Q1 : out STD_LOGIC_VECTOR (3 downto 0));
end component;
component Contador_2bits is
    Port ( I2 : in STD_LOGIC;
           Q2 : out STD_LOGIC_VECTOR (1 downto 0));
end component;
component DECO is
    Port ( Sdeco : in STD_LOGIC_VECTOR (1 downto 0);
           Odeco : out STD_LOGIC_VECTOR (3 downto 0));
end component;
component LEDSeq is
    Port ( E : in STD_LOGIC;
           CLK : in STD_LOGIC;
           Oled : out STD_LOGIC_VECTOR (15 downto 0));
end component;
component MUX4to1 is
    Port ( S : in STD_LOGIC_VECTOR (1 downto 0);
           O : out STD_LOGIC_VECTOR (3 downto 0);
           a : in STD_LOGIC_VECTOR (3 downto 0);
           b : in STD_LOGIC_VECTOR (3 downto 0);
           c : in STD_LOGIC_VECTOR (3 downto 0);
           d : in STD_LOGIC_VECTOR (3 downto 0));
end component;
signal OMux : STD_LOGIC_VECTOR (3 downto 0);

signal OclkA : STD_LOGIC;
signal OcontA : STD_LOGIC_VECTOR (1 downto 0);

signal contAux : STD_LOGIC;

signal OclkB : STD_LOGIC;
signal OcontB : STD_LOGIC_VECTOR (3 downto 0);

signal OclkC : STD_LOGIC;
signal OcontC : STD_LOGIC_VECTOR (3 downto 0);

signal OclkD : STD_LOGIC;
signal OcontD : STD_LOGIC_VECTOR (3 downto 0);

signal muxAux : STD_LOGIC_VECTOR (1 downto 0);

signal comp1Aux : STD_LOGIC;
signal comp2Aux : STD_LOGIC;
signal outComp : STD_LOGIC;

signal OclkE : STD_LOGIC;
signal ELED : STD_LOGIC;
signal OledAux : STD_LOGIC_VECTOR (15 downto 0);

signal Odeco : STD_LOGIC_VECTOR (3 downto 0);

begin
B0: BCD_7seg PORT MAP(OMux, O7seg);

B1: CLK_80Hz PORT MAP(CLK, OclkA);
B2: Contador_2bits PORT MAP(OclkA, OcontA);

contAux <= CLK OR NOT (Pul);

B3: CLK_3KHz PORT MAP(contAux, OclkB);
B4: Contador_4bits PORT MAP(OclkB, OcontB);

B5: CLK_5KHz PORT MAP(contAux, OclkC);
B6: Contador_4bits PORT MAP(OclkC, OcontC);

B7: CLK_7KHz PORT MAP(contAux, OclkD);
B8: Contador_4bits PORT MAP(OclkD, OcontD);

muxAux(0) <= OcontA(0) OR PT;
muxAux(1) <= OcontA(1) OR PT;
B9: MUX4to1 PORT MAP(muxAux, OMux, OcontB, OcontC, OcontD, OcontD);

B10: COMP_4bits PORT MAP(OcontB, OcontC, comp1Aux);
B11: COMP_4bits PORT MAP(OcontC, OcontD, comp2Aux);
outComp <= comp1Aux AND comp2Aux AND NOT (Pul);


B12: CLK_10Hz PORT MAP(CLK, OclkE);
ELED <= outComp OR PT;
B13: LEDseq PORT MAP(ELED, OclkE, OledAux);

process (outComp, PT)
    begin
        if (PT = '0' AND Pul = '0' AND outComp = '0') then
            Oled <= "1000000110000001";
        elsif (PT = '0' AND outComp = '0' AND Pul = '1') then
            Oled <= "0000000000000000";
        else
            Oled <= OledAux;
        end if;
    end process;

B14: DECO PORT MAP(OcontA, Odeco);
GND7seg <= Odeco;
end Behavioral;