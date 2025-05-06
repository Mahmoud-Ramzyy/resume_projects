clear;
close all;
clc; 
%% Cell-Wide Settings

enb.NDLRB = 15;                 % Number of resource blocks
enb.CellRefP = 1;               % One transmit antenna port
enb.NCellID = 10;               % Cell ID
enb.CyclicPrefix = 'Normal';    % Normal cyclic prefix
enb.DuplexMode = 'FDD';         % FDD

%% SNR Configuration

SNRdB = 22;             % Desired SNR in dB
SNR = 10^(SNRdB/20);    % Linear SNR  
rng('default');         % Configure random number generators

%% Channel Model Configuration
cfg.Seed = 1;                  % Random channel seed
cfg.NRxAnts = 1;               % 1 receive antenna
cfg.DelayProfile = 'EVA';      % EVA delay spread
cfg.DopplerFreq = 120;         % 120Hz Doppler frequency
cfg.MIMOCorrelation = 'Low';   % Low (no) MIMO correlation
cfg.InitTime = 0;              % Initialize at time zero
cfg.NTerms = 16;               % Oscillators used in fading model
cfg.ModelType = 'GMEDS';       % Rayleigh fading model type
cfg.InitPhase = 'Random';      % Random initial phases
cfg.NormalizePathGains = 'On'; % Normalize delay profile power 
cfg.NormalizeTxAnts = 'On';    % Normalize for transmit antennas

%% Channel Estimator Configuration


cec.PilotAverage = 'UserDefined'; % Pilot averaging method
cec.FreqWindow = 9;               % Frequency averaging window in REs
cec.TimeWindow = 9;               % Time averaging window in REs

%%
% Interpolation is performed by the channel estimator between pilot
% estimates to create a channel estimate for all REs. To improve the
% estimate multiple subframes can be used when interpolating. An
% interpolation window of 3 subframes with a centered interpolation window
% uses pilot estimates from 3 consecutive subframes to estimate the center
% subframe.

cec.InterpType = 'Cubic';         % Cubic interpolation
cec.InterpWinSize = 3;            % Interpolate up to 3 subframes 
                                  % simultaneously
cec.InterpWindow = 'Centred';     % Interpolation windowing method

%% Subframe Resource Grid Size


gridsize = lteDLResourceGridSize(enb);
K = gridsize(1);    % Number of subcarriers
L = gridsize(2);    % Number of OFDM symbols in one subframe
P = gridsize(3);    % Number of transmit antenna ports

%% Transmit Resource Grid
% An empty resource grid |txGrid| is created which will be populated with
% subframes.
txGrid = [];

%% Payload Data Generation


% Number of bits needed is size of resource grid (K*L*P) * number of bits
% per symbol (2 for QPSK)
numberOfBits = K*L*P*2; 

% Create random bit stream
inputBits = randi([0 1], numberOfBits, 1); 

% Modulate input bits
inputSym = lteSymbolModulate(inputBits,'QPSK');	

%% Frame Generation

% For all subframes within the frame
for sf = 0:10
    
    % Set subframe number
    enb.NSubframe = mod(sf,10);
    
    % Generate empty subframe
    subframe = lteDLResourceGrid(enb);
    
    % Map input symbols to grid
    subframe(:) = inputSym;

    % Generate synchronizing signals
    pssSym = ltePSS(enb);
    sssSym = lteSSS(enb);
    pssInd = ltePSSIndices(enb);
    sssInd = lteSSSIndices(enb);

    % Map synchronizing signals to the grid
    subframe(pssInd) = pssSym;
    subframe(sssInd) = sssSym;

    % Generate cell specific reference signal symbols and indices
    cellRsSym = lteCellRS(enb);
    cellRsInd = lteCellRSIndices(enb);

    % Map cell specific reference signal to grid
    subframe(cellRsInd) = cellRsSym;
    
    % Append subframe to grid to be transmitted
    txGrid = [txGrid subframe]; %#ok
      
end

%% OFDM Modulation

[txWaveform,info] = lteOFDMModulate(enb,txGrid); 
txGrid = txGrid(:,1:140);

%% Fading Channel


cfg.SamplingRate = info.SamplingRate;

% Pass data through the fading channel model
rxWaveform = lteFadingChannel(cfg,txWaveform);

%% Additive Noise
% The SNR is given by $\mathrm{SNR}=E_s/N_0$ where $E_s$ is the energy of
% the signal of interest and $N_0$ is the noise power. The noise added
% before OFDM demodulation will be amplified by the FFT. Therefore to
% normalize the SNR at the receiver (after OFDM demodulation) the noise
% must be scaled. The amplification is the square root of the size of the
% FFT. The size of the FFT can be determined from the sampling rate of
% the time domain waveform (|info.SamplingRate|) and the subcarrier spacing
% (15 kHz). The power of the noise to be added can be scaled so that $E_s$
% and $N_0$ are normalized after the OFDM demodulation to achieve the
% desired SNR (|SNRdB|).

% Calculate noise gain
N0 = 1/(sqrt(2.0*enb.CellRefP*double(info.Nfft))*SNR);

% Create additive white Gaussian noise
noise = N0*complex(randn(size(rxWaveform)),randn(size(rxWaveform)));   

% Add noise to the received time domain waveform
rxWaveform = rxWaveform + noise;

%% Synchronization
% The offset caused by the channel in the received time domain signal is
% obtained using <matlab:doc('lteDLFrameOffset') lteDLFrameOffset>. This
% function returns a value |offset| which indicates how many samples the
% waveform has been delayed. The offset is considered identical for
% waveforms received on all antennas. The received time domain waveform can
% then be manipulated to remove the delay using |offset|.

offset = lteDLFrameOffset(enb,rxWaveform);
rxWaveform = rxWaveform(1+offset:end,:);

%% OFDM Demodulation
% The time domain waveform undergoes OFDM demodulation to transform it to
% the frequency domain and recreate a resource grid. This is accomplished
% using <matlab:doc('lteOFDMDemodulate') lteOFDMDemodulate>. The resulting
% grid is a 3-dimensional matrix. The number of rows represents the number
% of subcarriers. The number of columns equals the number of OFDM symbols
% in a subframe. The number of subcarriers and symbols is the same for the
% returned grid from OFDM demodulation as the grid passed into
% <matlab:doc('lteOFDMModulate') lteOFDMModulate>. The number of planes
% (3rd dimension) in the grid corresponds to the number of receive
% antennas.

rxGrid = lteOFDMDemodulate(enb,rxWaveform);

%% Channel Estimation

enb.NSubframe = 0;
[estChannel, noiseEst] = lteDLChannelEstimate(enb,cec,rxGrid);

%% MMSE Equalization
% The effects of the channel on the received resource grid are equalized
% using <matlab:doc('lteEqualizeMMSE') lteEqualizeMMSE>. This function uses
% the estimate of the channel |estChannel| and noise |noiseEst| to equalize
% the received resource grid |rxGrid|. The function returns |eqGrid| which
% is the equalized grid. The dimensions of the equalized grid are the same
% as the original transmitted grid (|txGrid|) before OFDM modulation.

eqGrid = lteEqualizeMMSE(rxGrid, estChannel, noiseEst);

%% Analysis


% Calculate error between transmitted and equalized grid
eqError = txGrid - eqGrid;
rxError = txGrid - rxGrid;

% % Compute EVM across all input values
% % EVM of pre-equalized receive signal
% preEqualisedEVM = lteEVM(txGrid,rxGrid);
% fprintf('Percentage RMS EVM of Pre-Equalized signal: %0.3f%%\n', ...
%         preEqualisedEVM.RMS*100); 
% % EVM of post-equalized receive signal
% postEqualisedEVM = lteEVM(txGrid,eqGrid);
% fprintf('Percentage RMS EVM of Post-Equalized signal: %0.3f%%\n', ...
%         postEqualisedEVM.RMS*100); 
% 
% % Plot the received and equalized resource grids 
% hDownlinkEstimationEqualizationResults(rxGrid, eqGrid);
eee=eqGrid(1:12,1:14);
ee=reshape(eee,168,1);
rrr=rxGrid(1:12,1:14);
rr=reshape(rrr,168,1);
%% 
X = real(rr);
%X=fi(X);
X=fi(X,1,16,14);  % 1 for signed ,16 :word legnth,14:#fraction bits
xb=bin(X); 
xh=hex(X);   
%X=num2hex(X);
%M=dec2bin(typecast(X, 'uint32'), 32) - '0'; to rep in single prescion
%format
 dlmwrite('I.txt',xb,'delimiter','')
 %type('I.txt')
y=imag(rr);
y=fi(y,1,16,14);
yb=bin(y);
 dlmwrite('Q.txt',yb,'delimiter','')
 %type('Q.txt') 
 %%
 est=[-0.1082-0.4855i  -.3220-0.2797i  -0.5357-0.0739i  -0.7495+0.132i  -0.9632+0.338i....
     -0.6782+0.0635i  -0.3932-0.211i ....
    -0.1082-0.4855i  -.3220-0.2797i  -0.5357-0.0739i  -0.7495+0.132i  -0.9632+0.338i....
     -0.6782+0.0635i  -0.3932-0.211i ];
 est=repmat(est,12,1);
 mine=rrr/est;
