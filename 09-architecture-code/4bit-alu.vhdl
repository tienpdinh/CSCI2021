library IEEE;
entity alu is
 Port(A_IN : in signed(3 downto 0);
      B_IN : in signed(3 downto 0);
      OPER : in STD_LOGIC_VECTOR(1 downto 0);
      OUTP : out signed(3 downto 0));
end alu;
 
architecture Behavioral of alu is
begin
  process(A_IN, B_IN, OPER) 
  begin
    case OPER is
      when "00" => 
        OUTP <= A_IN xor B_IN; --XOR gate 
      when "01" => 
        OUTP <= A_IN and B_IN; --AND gate 
      when "10" => 
        OUTP <= A_IN or  B_IN; --OR gate 
      when "11" => 
        OUTP <= A_IN +   B_IN; --addition 
    end case; 
    
  end process; 
end Behavioral;
