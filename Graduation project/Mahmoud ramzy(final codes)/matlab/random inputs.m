clear;
close all;
clc;  
m=dec2hex(bin2dec('1111101110000000'));
b=hex2dec(m);
a=hex2dec('ffc7');  
j=0;
out=0;
% addation (5 fraction)
for i=1:16  %start from 1 not 0
    j=i-6;   %# fraction bits +1  6 /15/9
    b1 = bitget(a,i);  % a for hexa & b for binary
    if (i==16)
        if b1
          out= -1024+out;  %-2 not -1 as the signed bit now at 2nd int bit
        else
            out= out*1;
        end
    else
        out=out+(b1*(2^j));
    end
  end
