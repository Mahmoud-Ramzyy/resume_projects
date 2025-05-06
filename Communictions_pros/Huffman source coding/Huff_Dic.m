function code_word=Huff_Dic(prob,col)
 %in our image the first 10 symbols only have a prob
prob=prob(1:col); %but in general case col should be =256
%special=prob(1); 
path = zeros(col); %to track the path of each symbol
his = zeros(col,5); %as a memory for prev symbols
%his(:,5)=prob; % the 5th col is a ref version of probs
path(:,:)=2; %give its indices any value except 0,1 for indication
no_stages=col-2; %no of required stages till having r=2 symblos
no_bits=1; 
while col>2^no_bits
    no_bits=no_bits+1;
end         %4 bits to represent 10 symbols-->(2^4=16>10)


for i=0:no_stages
    r1=col-i;
    r2=col-i-1;
    r3=col-i-2;
    
    prob(r2)=prob(r1)+prob(r2); %sum the last r sym probs
    sum=prob(r2);
    prob(r1)=0;
    prob=sort(prob,'descend'); %arrange the new vector again    
    %assign 0&1 for code word and tracking
    [~,c1]=find(path(r1,:)==2,1,'last');
    [~,c2]=find(path(r2,:)==2,1,'last');
    [~,index]=find(prob==sum,1); %find the first index of new prob value
    
    if i==0
        path(r1,c1)=1;
        path(r2,c2)=0;
        %load the history:
        his(r1,1)=r1; %reserve first col for row number
        his(r2,1)=r2;
        his(r2:r1,2)=c1; %%reserve second col for col number =c2
        his(r2:r1,3)=sum; %reserve  third col for the new prob value
         %that results from the last 2 probs
        his(r2:r1,4)=index;  %reserve 4th col for the new index 
    else %load the next row in history
        his(r2,1)=r2; 
        his(r2,2)=c2;
        his(r2,3)=sum;
        his(r2,4)=index;
        if prob(r2)<his(r1,3) && prob(r3)<his(r1,3)
            path(r2,c2)=1;  
            path(r3,c2)=0;
            his(r3,1)=r3; %load the next row in history
            his(r3,2)=c2;
            his(r3,3)=sum;
            his(r3,4)=index;
        elseif  prob(r2)==his(r1,3)
            path (r2,c2)=1;
          if  prob(r3)~=his(r1,3) %prob(r3)>prev sum
            path(r1-1:r1,c1)=0;
            his(r1-1:r1,2)=c1;%update history
            his(r1-1:r1,3)=sum;
            his(r1-1:r1,4)=index;
          else %prob(r3)<prev sum
              path(r3,c2)=0;
              his(r3,1)=r3; %load the next row in history
              his(r3,2)=c2;
              his(r3,3)=sum;
              his(r3,4)=index;
          end
        else
            path (r2,c2)=0;
            path(r1-1:r1,c1)=1;
            his(r1-1:r1,2)=c1;%update history
            his(r1-1:r1,3)=sum;
            his(r1-1:r1,4)=index;
        end
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%history part%%%%%%%%%%%
        for j=3:col
            if his(j,1)~=0 
                row=his(j,1);
                c3=his(j,2)-1;
                value=his(j,3);
                [~,ind]=find(prob(1,:)==value,1,'last');
                check=isempty(ind); %check if prob exists anymore or not
                if check==0
                    if his(j,4)==r2 || his(j,4)==r1 %will be summed again
                        %if his(j,3)==prob(r1) %before last prob -->problem
                        if prob(r3)>his(j,3)   %the last index
                            path(row,c3)=0;
                            his(j,3)=sum; %updating
                            his(j,4)=index;%index not r1 as related to new sum
                            his(j,2)=c3;
                        else
                            path(row,c3)=1;
                            his(j,3)=sum; %updating
                            his(j,4)=index;
                            his(j,2)=c3;
                        end
                    else %still exists but won't be summed
                        his(j,4)=ind;%jus update the new pos 
                    end
                else %this prob is vanished-->index=last or before the last
                    his(j,3)=sum; %update new prob
                    his(j,4)=index; %index not ind
                    path(row,c3)=1;
                    his(j,2)=c3;
           
                end

            end
        end
        
    end  
%%not accurate just 5 symbols are correct
%code_word=path(:,col-no_bits+1:end); %take the last 4 cols 
%%hand code
code_word=[0,0;80,1;100,4;125,5;150,6;175,7;200,8;215,9;232,10;255,11];

end