clear;
close all;
clc;
s=-1;
s1=1;
values=magic(12*14);
val=values(:,1);
val0=values(:,2);
for i=1:12*14
val(i) = s + rand*(s1-s);  %to generate random floating numbers
val0(i) = s + rand*(s1-s);
end
%val=single(val);
fixed_I=fi(val,1,16,10);  % 1 for signed ,16 :word legnth,14:#fraction bits
bin_I=bin(fixed_I);
hex_I=hex(fixed_I);
%val0=single(val0);
fixed_Q=fi(val0,1,16,10);  % 1 for signed ,16 :word legnth,14:#fraction bits
bin_Q=bin(fixed_Q);
hex_Q=hex(fixed_Q);
%N=dec2bin(typecast(val, 'uint32'), 32) - '0';
%M=dec2bin(typecast(val0, 'uint32'), 32) - '0';
dlmwrite('II.txt',bin_I,'delimiter','')
dlmwrite('QQ.txt',bin_Q,'delimiter','')
%type('II.txt')
type('QQ.txt')