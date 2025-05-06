%% This is a function that perform mapping of symbols on constellation for 32PSK Modulation techinque

function mappedSymbol=MPSK_32_MOD(symbol)

       mappedSymbol=cos((2*pi/32)*symbol)+1i*sin((2*pi/32)*symbol);
    %Symbole eqn for the MPSK
end

    
    
    
    
    
    
    
    
    
    