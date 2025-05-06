close all; 
clc;

%% Generating Input Bits And Shaping it

N_symbol = 32; % Number of Symbols in MPSK 
N_bits = log2(N_symbol); % Number of Bits/Symbol
x_stream = randi([0 1],[2000 5]);% generating streams of 1's and 0's by rounding random numbers to nearest 1 or 0 ,
%Mtx size = 2000 x 5 
x_decimal = bi2de(x_stream,'left-msb'); % Converting Binary symbols to decimal values so we can map it later

%% Mapping the symbols and drawing constellation

y=MPSK_32_MOD(x_decimal); % mapping symbols to constellation

%% Drawing of constellation of Original signal after mapping without effect of channel noise
scatterplot(y,1,0);   %produces a scatter plot for the signal y every 1 value of the signal,starting from the 0 offset  
grid on 
axis([-2 2 -2 2]); 
title('Constellation of the original signal') 
legend('32PSK Constellation')

%% AWGN channel effect

% 1. For SNR= 30 dB
scatterplot(White_noise(y,30)); %produces a scatter plot for the signal y after making its SNR dwn to 30db
grid on
axis([-2 2 -2 2]); legend('32PSK noisy signal');
title('Constellation of the Noisy signal at 30 dB')

% 2.For SNR= 10 dB

scatterplot(White_noise(y,10));  %produces a scatter plot for the signal y after making it SNR dwn to 10db
legend('32PSK noisy signal');
axis([-2 2 -2 2]);  grid on
title('Constellation of the Noisy signal at 10 dB')

% 3.For SNR= 5 dB

scatterplot(White_noise(y,5));  %produces a scatter plot for the signal y after making its SNR dwn to 5db
legend('32PSK noisy signal');
axis([-2 2 -2 2]);  grid on
title('Constellation of the Noisy signal at 5 dB')

% 4.For SNR= 0 dB
scatterplot(White_noise(y,0));  %produces a scatter plot for the signal y after making its SNR dwn to 0db
legend('32PSK noisy signal');
axis([-2 2 -2 2]);  grid on
title('Constellation of the Noisy signal at 0 dB')

% 5.For SNR= -3 dB

c1=scatterplot(White_noise(y,-3));  %produces a scatter plot for the signal y making its SNR dwn to -3db
legend('32PSK noisy signal');
axis([-2 2 -2 2]);  grid on
title('Constellation of the Noisy signal at -3 dB')
%% Demapped signal
Y_Rx        = MPSK_32_DMOD(y);    %Demodulation of the original signal       
Y_Rx_SNRn10 = MPSK_32_DMOD(White_noise(y,-10));  %Demodulation of the sig after adding  noise from channel to it
Y_Rx_SNRn5  = MPSK_32_DMOD(White_noise(y,-5));   % with different values that makes its SNR dwn 
Y_Rx_SNR0   = MPSK_32_DMOD(White_noise(y,0));    % to different values too=-10,-5,0,5,...20 db
Y_Rx_SNR5   = MPSK_32_DMOD(White_noise(y,5));   
Y_Rx_SNR10  = MPSK_32_DMOD(White_noise(y,10));  
Y_Rx_SNR15  = MPSK_32_DMOD(White_noise(y,15));  
Y_Rx_SNR20  = MPSK_32_DMOD(White_noise(y,20));   

%% BER Calculations
SNR.dB = -10:5:20;  %preparing the SNR axis to be used in plots 

BER = [SER(x_decimal,Y_Rx_SNRn10) SER(x_decimal,Y_Rx_SNRn5) ...  %form a vector for the the symbol error rate 
    SER(x_decimal,Y_Rx_SNR0) SER(x_decimal,Y_Rx_SNR5) ...        %of the RX demodulation signals in different
    SER(x_decimal,Y_Rx_SNR10) SER(x_decimal,Y_Rx_SNR15) ...      %SNR levels then divide it by #bits/symbol
    SER(x_decimal,Y_Rx_SNR20)]/N_bits ;                        %to get the bit error rate for easch signal 
SNR.lin= 10.^(SNR.dB/10);     %convert the SNR  from db into decimal
BER_T = (2/log2(N_symbol))*qfunc(sqrt(2*SNR.lin*log2(N_symbol))*sin(pi/32));
%this is the theoretical relation for the Bit Error Rate of the MPSK-->M=32 
figure
semilogy(SNR.dB , BER,'red')
title('BER Vs SNR(dB)')
legend('BER')
xlabel('SNR(dB)')
ylabel('BER')
grid on
hold on;
semilogy(SNR.dB , BER_T,'blue' )
title('Theoretical BER & Stimulated BER  Vs SNR(dB) ')
legend('BER','Theoretical BER')
xlabel('SNR(dB)')
ylabel('BER')
grid on



