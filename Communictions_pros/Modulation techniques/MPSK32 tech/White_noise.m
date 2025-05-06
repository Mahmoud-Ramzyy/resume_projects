
%% This is a function that simulating the channel where awgn noise is added

function N = White_noise(Signal,SNR_dB)
rng('default'); % to geneate the same random values of noise in every time
L = length(Signal); %length of Signal
SNR = 10^(SNR_dB/10); %SNR to linear scale
Esym = sum(abs(Signal).^2)/(L); %Calculate actual symbol energy
N0 = Esym/SNR; %Find the noise spectral density
noiseSigma=sqrt(N0/2); %Standard deviation for AWGN Noise 
n = noiseSigma*(randn(L,1)+1i*randn(L,1));%computed noise
N = Signal + n; %received signal
end