function prob=sym_prob(img,rows,col)
Totalcount=rows*col;
for i=0:255
    counter=0;
    for j=1:rows
      for k=1:col
          if img(j,k)==i
              counter=counter+1;
          end
      end 
    end
    prob(i+1)=counter/Totalcount;
end
end
