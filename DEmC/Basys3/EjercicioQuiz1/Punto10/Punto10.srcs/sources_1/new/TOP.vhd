----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/21/2024 09:59:43 PM
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
    Port ( A : in STD_LOGIC_VECTOR (2 downto 0);
           B : in STD_LOGIC_VECTOR (2 downto 0);
           S : in STD_LOGIC;
           O : out STD_LOGIC_VECTOR (6 downto 0));
end TOP;

architecture Behavioral of TOP is
    component COMP is
        Port ( x : in STD_LOGIC_VECTOR (2 downto 0);
               y : in STD_LOGIC_VECTOR (2 downto 0);
               O : out STD_LOGIC);
    end component;
    component BCD_7SEG is
        Port ( BCD : in STD_LOGIC_VECTOR (3 downto 0);
               O : out STD_LOGIC_VECTOR (6 downto 0));
    end component;
    component SUM is
        Port ( x : in STD_LOGIC_VECTOR (2 downto 0);
               y : in STD_LOGIC_VECTOR (2 downto 0);
               Ci : in STD_LOGIC;
               S : out STD_LOGIC_VECTOR (3 downto 0));
               
    end component;
    component MUX is
        Port ( x : in STD_LOGIC_VECTOR (3 downto 0);
               y : in STD_LOGIC_VECTOR (3 downto 0);
               s : in STD_LOGIC;
               O : out STD_LOGIC_VECTOR (3 downto 0));
    end component;
    
    signal sumOut : STD_LOGIC_VECTOR (3 downto 0);
    signal compOut : STD_LOGIC;
    signal muxAux : STD_LOGIC_VECTOR (3 downto 0);
    signal bcd : STD_LOGIC_VECTOR (3 downto 0);
    signal sigA4 : STD_LOGIC_VECTOR (3 downto 0);
    SIGNAL sigB4 : STD_LOGIC_VECTOR (3 downto 0);
begin
sigA4 <= '0' & A;
sigB4 <= '0' & B;
    B0: SUM PORT MAP(A, B, '0', sumOut);
    B1: COMP PORT MAP(A, B, compOut);
    B2: MUX PORT MAP(sigA4, sigB4, compOut, muxAux);
    B3: MUX PORT MAP(sumOut, muxAux, S, bcd);
    B4: BCD_7SEG PORT MAP(bcd, O);

end Behavioral;