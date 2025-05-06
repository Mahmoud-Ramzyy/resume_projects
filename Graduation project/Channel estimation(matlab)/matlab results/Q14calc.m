clear;
close all;
clc;  
m=dec2hex(bin2dec('0000001100100000'));
b=hex2dec(m); %if binary 
 a=hex2dec('f27f');   %if hexa enter it
j=0;
out=0;
 %mult  (14 fraction)
for i=1:16  %start from 1 not 0
    j=i-11;   %# fraction bits +1 
    lastbit = bitget(b,i);  % a for hexa & b for binary
    if (i==16)
        if lastbit
           out= -32+out;
        else
            out= out*1;
        end
    else
        out=out+(lastbit*(2^j));
    end
    
end



