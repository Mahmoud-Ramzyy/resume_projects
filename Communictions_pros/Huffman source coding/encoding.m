function en=encoding(code_word,img,symbol_no)
[m,n]=size(img);
for j=1:symbol_no
    %code=code_word(j,1);
    for i=1:m
        for k=1:n
            
            if code_word(j,1)==img(i,k)
                img(i,k)=code_word(j,2);
            end
        end
    end
end
en=img;
        
    
end