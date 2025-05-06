%% This is a function that perform demapping of symbols on constellation for 32PSK Modulation techinque

function [D]= MPSK_32_DMOD(y)

D=mod(angle(y),2*pi);   %returns the remainder after division the phase of Rx signal by 2pi
g = 2*pi/32;  %the distance or phase shift btn 2 successive symboles

for i=1:length(y)  %looping till reach the certain symbole that has a phase btn nxt and previous symboles
    for x = 0:31
        D(and(D >=  x*g - g/2, D < x*g + g/2)) = x;
    end
end    
end    
   