%% This function gets the symbol error rate 
function [H]=SER(x,y)
n=0;  %just a counter
for i=1:length(x)
    if x(i) == y(i)  %checks if the original sig matched the RX deomodulated sig
        n=n+1;
    end
end
H=(length(x)-n)/length(x);
end