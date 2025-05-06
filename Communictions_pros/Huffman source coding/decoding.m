function deimg=decoding(comimg,dic,symbol_no)
[m,n]=size(comimg);
for j=1:symbol_no
    %code=code_word(j,1);
    for i=1:m
        for k=1:n
            
            if dic(j,2)==comimg(i,k)
                comimg(i,k)=dic(j,1);
            end
        end
    end
end
deimg=comimg;

end