close all; 
clc;

%% Generating Input Bits And Shaping it

N_symbol = 2; % Number of Symbols in MPSK 
N_bits = log2(N_symbol); % Number of Bits/Symbol
x_stream = randi([0 1],[2000 1]);% generating streams of 1's and 0's by rounding random numbers to nearest 1 or 0 ,
%Mtx size = 2000 x 1
x_decimal = bi2de(x_stream,'left-msb'); % Converting Binary symbols to decimal values so we can map it later

%% Mapping the symbols and drawing constellation

y=BPSK_MOD(x_decimal); % mapping symbols to constellation

%% Drawing of constellation of Original signal after mapping without effect of channel noise

scatterplot(y,1,0);   %produces a scatter plot for the signal y every 1 value of the signal,starting from the 0 offset  
hold on
grid on 
figure (1)
axis([-2 2 -2 2]); 
title('Constellation of the original signal') 
legend('BPSK Constellation')

%% UPsampling &rectangular shaping
L=8; %# of samples
%Z = upsample(y,n);
M= rectpulse(y,L);
t= linspace(0,2000,length(M));
figure(2)
stem(t,real(M));
grid on
xlim([0 20]);
xlabel('Time (s)');
ylabel('Amplitude (V)');
title({'BPSK','Base Band Modulated Signal'});
%% matched filter:
b1 = M(end:-1:length(M)); %matched filter's coefficients is given by time reverse of M
b2= filter(b1,1,M);
p=(White_noise(b2,10));  %adding 10db white noise 
MF=conv(M,p,'same');
figure (3)
stem(t,real(MF));
grid on;
xlim([0 50]);
xlabel('Time (s)');
ylabel('Amplitude (V)');
title({'BPSK','Base Band Demodulated Signal'});
%% AWGN channel effect
b3= downsample(b2,L); %downsampling 
figure (3)
scatterplot(White_noise(b3,10)); %produces a scatter plot for the signal y after making its SNR dwn to 30db
grid on
axis([-2 2 -2 2]);
legend('BPSK noisy signal');
title('Constellation of the Noisy signal at 10 dB')

figure (4)
scatterplot(White_noise(b3,5)); %produces a scatter plot for the signal y after making its SNR dwn to 5db
grid on
axis([-4 4 -4 4]);
legend('BPSK noisy signal');
title('Constellation of the Noisy signal at 5 dB')

figure (5)
scatterplot(White_noise(b3,-10)); %produces a scatter plot for the signal y after making its SNR dwn to -10db
grid on
%axis([-5 5 -5 5]);
legend('BPSK noisy signal');
title('Constellation of the Noisy signal at -10 dB')

%% Detection & BER
Y_Rx= BPSK_DMOD(b3);    %Demodulation of the original signal       
Y_Rx_SNR10 = BPSK_DMOD(White_noise(b3,10));  %Demodulation of the sig after adding  noise from channel 
Y_Rx_SNR5  = BPSK_DMOD(White_noise(b3,5));   % to it with different values that makes its SNR dwn 
Y_Rx_SNRn10   = BPSK_DMOD(White_noise(b3,-10));    % to different values too
SNR.dB = -10:5:20;  %preparing the SNR axis to be used in plots
BER = [SER(x_decimal,Y_Rx_SNRn10) SER(x_decimal,Y_Rx_SNR5) ...  %form a vector for the the symbol error rate 
    SER(x_decimal,Y_Rx_SNR10)]/N_bits  ; %of the RX demodulation signals in snr levels
  
SNR.lin= 10.^(SNR.dB/10);     %convert the SNR  from db to decimal
BER_T = (1/2)*erfc(sqrt(SNR.lin));
figure (7)
semilogy(SNR.dB , BER,'red*')
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
