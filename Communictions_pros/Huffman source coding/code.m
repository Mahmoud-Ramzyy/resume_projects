clear;
close all;
clc;
%% Reading the gray scale image
gimg=imread('project_image.png');
figure,imshow(gimg)
title('original')
[m,n]=size(gimg);
 
%% get the prob of each symbol
prob=sym_prob(gimg,m,n);
%% create Huffman dictionary:
% step 1:sorts the elements of probs in descending order.
pro=sort(prob,'descend'); 
[r,sym_no]=find(pro==0,1); %to detect  how many symbols haven't 0 prob
sym_no=sym_no-1; 
Code_word=Huff_Dic(pro,sym_no);
%% encoding:
enimg=encoding(Code_word,gimg,sym_no);
%% decoding
deimg=decoding(enimg,Code_word,sym_no);
figure,imshow(gimg)
title('Decoded')
%% ratio
z=isequal(enimg,deimg); %not matched 100%
in = imfinfo('project_image.png');
imwrite(uint8(enimg),'comp.png');
cmprsd= imfinfo('project_image.png');
ratio=(in.Width*in.Height*in.BitDepth/8)/cmprsd.FileSize

