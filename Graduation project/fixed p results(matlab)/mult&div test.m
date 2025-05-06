clear;
close all;
clc;  
% temp = regexp( fileread('Q_grid.txt'), '\r?\n', 'split');
Itext = strsplit(fileread('II.txt'), {'\r', '\n'});  %read file and split into lines
Qtext = strsplit(fileread('QQ.txt'), {'\r', '\n'});  %read file and split into lines
mult = strsplit(fileread('mm.txt'), {'\r', '\n'});  %read file and split into lines
div = strsplit(fileread('dd.txt'), {'\r', '\n'});  %read file and split into lines
%isvalid = ~cellfun(@(t) any(t == 'x') | numel(t) < 16, div);  %line scontaining 'x' or shorter than 32 bits are not valid
%u=reshape([text{:}], 168, []);
I=reshape([Itext{:}], [16, 168]);
Q=reshape([Qtext{:}], [16, 168]);
m=reshape([mult{:}], [16, 168]);
d=reshape([div{:}], [16, 168]);
II=getfixed(I);
QQ=getfixed(Q);
%%
% mm=getfixed(m); %%1
% 
% actm=II(1:166,1).*QQ(1:166,1); %1
% y = linspace(1,30,30);
% actm1=actm(y,1);
% mm1=mm(y,1);
% %difm=abs(actm-mm);
% %y = linspace(1,30,30);
% figure
% plot(y,actm1,'b*',y,mm1,'r--o');
% %stem(y,actm1);
% title('The results of matlab and the fixed point multiplier block over 30 trials ')
% xlabel('trial')
% ylabel('Result')
% legend('matlab','Multiplier')
% 
% %%
 dd=getfixed(d);  %2
 actd=II(1:166,1)./QQ(1:166,1);  %2
% actd1=actd(y,1);
% dd1=dd(y,1);
% %diff=abs(actd-dd);
% figure
% plot(y,actd1,'b--',y,dd1,'r--o');
% title('The results of matlab and the fixed point divider block over 30 trials ')
% xlabel('trial')
% ylabel('Result')
% legend('matlab','Divider')
% msum=0;
% dsum=0;
% for i=1:166
%     msum=difm(i,1)+msum;
%     if abs(actd(i,1))<2
%     dsum=diff(i,1)+dsum;
%     end
% end
% mavg=msum/166;
% davg=dsum/166;




