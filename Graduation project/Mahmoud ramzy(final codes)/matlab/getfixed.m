function value=getfixed(u)
j=0;
out=0;
[m,n]=size(u);
for k=1:n-1
    p=u(:,k);
    p=reshape(p,1,16);
    p=dec2hex(bin2dec(p));
    p=hex2dec(p);
    % mult  (14 fraction)
    for i=1:16  %start from 1 not 0
        j=i-11;   %# fraction bits +1
        lastbit = bitget(p,i);  % a for hexa & b for binary
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
    value(k,1)=out;
        out=0;
        m=0;
end

end