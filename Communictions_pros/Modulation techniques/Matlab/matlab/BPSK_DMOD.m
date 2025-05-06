%% This is a function that performs demapping of symbols on constellation for BPSK Modulation techinque

function [D]= BPSK_DMOD(y)

D=mod(angle(y),2*pi);   %returns the remainder after division the phase of Rx signal by 2pi
D(and(D > 0.0*pi, D < 0.5*pi)) = 1;
D(and(D > 0.5*pi, D < 1.0*pi)) = 0;
end    
   