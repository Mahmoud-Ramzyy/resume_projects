
% Normal FDD --> line33
%Extended FDD --> line 196
% Normal TDD --> line 310
%Extended TDD -->  line 446 

%% Load and Process I/Q Waveform 

    rmc = lteRMCDL('R.4');
    rmc.SSC = 0;           %Special subframe configuration, specified as nonnegative scalar
                           %integer between 0 and 9. Optional. Required only for 'TDD' duplex mode.
                           
    rmc.TDDConfig = 1;    %Uplink or downlink configuration for TDD, specified as a nonnegative   
                          %scalar integer between 0 and 6. %Optional. Required only for 'TDD' duplex mode.
                       
    rmc.NCellID = 283;
    rmc.CyclicPrefix = 'Normal';  % CP length
    rmc.DuplexMode = 'TDD';
    rmc.TotSubframes = 41;
    rmc.PHICHDuration = 'Extended'; % PHICH duration
    
    [eNodeBOutput,~,info] = lteRMCDLTool(rmc,[1;0;0;1]);
    sr = info.SamplingRate;     % Sampling rate of generated samples            


%% comparing with Normal FDD  

% Set eNodeB basic parameters
enb = struct;                   % eNodeB config structure
enb.DuplexMode = 'FDD';         % assume FDD duxplexing mode
enb.CyclicPrefix = 'Normal';    % assume normal cyclic prefix
enb.NDLRB = 6;                  % Number of resource blocks
ofdmInfo = lteOFDMInfo(enb);    % Needed to get the sampling rate

if (isempty(eNodeBOutput))
    fprintf('\nReceived signal must not be empty.\n');
    return;
end

%%  

% Downsample received signal     ASK DR
nSamples = ceil(ofdmInfo.SamplingRate/round(sr)*size(eNodeBOutput,1));
nRxAnts = size(eNodeBOutput, 2);
downsampled = zeros(nSamples, nRxAnts);
for i=1:nRxAnts
    downsampled(:,i) = resample(eNodeBOutput(:,i), ofdmInfo.SamplingRate, round(sr));
end

%% Frequency offset estimation and correction

delta_f = lteFrequencyOffset(setfield(enb,'DuplexMode','FDD'), downsampled); %#ok<SFLD>

downsampled = lteFrequencyCorrect(enb, downsampled, delta_f);
    
%% Cell Search and Synchronization

% Cell search to find cell identity and timing offset
%fprintf('\nPerforming cell search...\n');
[cellID, offset] = lteCellSearch(enb, downsampled);    %[cellid,offset] = lteCellSearch(enb,waveform)

% Compute the correlation for each of the three possible primary cell
% identities; the peak of the correlation for the cell identity established
% above is compared with the peak of the correlation for the other two
% primary cell identities in order to establish the quality of the
% correlation.
corr = cell(1,3);
for i = 0:2
    enb.NCellID = mod(cellID + i,504);
    [~,corr{i+1}] = lteDLFrameOffset(enb, downsampled);
    corr{i+1} = sum(corr{i+1},2);
end
threshold = 1.3 * max([corr{2}; corr{3}]); % multiplier of 1.3 empirically obtained

enb.NCellID = cellID;

% plot PSS/SSS correlation and threshold
synchCorrPlot.YLimits = [0 max([corr{1}; threshold])*1.1];
%step(synchCorrPlot, [corr{1} threshold*ones(size(corr{1}))]);

% perform timing synchronisation

downsampled = downsampled(1+offset:end,:); 
enb.NSubframe = 0; % ASK DR

% show cell-wide settings
%fprintf('Cell-wide settings after cell search:\n');
%disp(enb);

%% OFDM Demodulation and Channel Estimation  
% The OFDM downsampled I/Q waveform is demodulated to produce a resource
% grid |rgrid|. This is used to perform channel estimation. |hest| is the
% channel estimate, |nest| is an estimate of the noise (for MMSE
% equalization) and |cec| is the channel estimator configuration.
%
% For channel estimation the example assumes 4 cell specific reference
% signals. This means that channel estimates to each receiver antenna from
% all possible cell-specific reference signal ports are available. The true
% number of cell-specific reference signal ports is not yet known. The
% channel estimation is only performed on the first subframe, i.e. using
% the first |L| OFDM symbols in |rxgrid|.
%
% A conservative 9-by-9 pilot averaging window is used, in time and
% frequency, to reduce the impact of noise on pilot estimates during
% channel estimation.

% Channel estimator configuration
% %OLAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
cec.PilotAverage = 'UserDefined';     % Type of pilot averaging
cec.FreqWindow = 9;                   % Frequency window size    
cec.TimeWindow = 9;                   % Time window size    
cec.InterpType = 'cubic';             % 2D interpolation type
cec.InterpWindow = 'Centered';        % Interpolation window type
cec.InterpWinSize = 1;                % Interpolation window size  

% Assume 4 cell-specific reference signals for initial decoding attempt;
% ensures channel estimates are available for all cell-specific reference
% signals
enb.CellRefP = 4;   
                    
%fprintf('Performing OFDM demodulation...\n\n');

griddims = lteResourceGridSize(enb); % Resource grid dimensions
L = griddims(2);                     % Number of OFDM symbols in a subframe 
% OFDM demodulate signal 
rxgrid = lteOFDMDemodulate(enb, downsampled);    
if (isempty(rxgrid))
    fprintf('After timing synchronization, signal is shorter than one subframe so no further demodulation will be performed.\n');
    return;
end
% % Perform channel estimation
% if (strcmpi(enb.DuplexMode,'TDD'))
%     enb.TDDConfig = 0;
%     enb.SSC = 0;
% end
[hest, nest] = lteDLChannelEstimate(enb, cec, rxgrid(:,1:L,:));

%% PBCH Demodulation, BCH Decoding, MIB parsing
% The MIB is now decoded along with the number of cell-specific reference
% signal ports transmitted as a mask on the BCH CRC. The function
% <matlab:doc('ltePBCHDecode') ltePBCHDecode> establishes frame timing
% modulo 4 and returns this in the |nfmod4| parameter. It also returns the
% MIB bits in vector |mib| and the true number of cell-specific reference
% signal ports which is assigned into |enb.CellRefP| at the output of this
% function call. If the number of cell-specific reference signal ports is
% decoded as |enb.CellRefP=0|, this indicates a failure to decode the BCH.
% The function <matlab:doc('lteMIB') lteMIB> is used to parse the bit
% vector |mib| and add the relevant fields to the configuration structure
% |enb|. After MIB decoding, the detected bandwidth is present in
% |enb.NDLRB|. 

% Decode the MIB
% Extract resource elements (REs) corresponding to the PBCH from the first
% subframe across all receive antennas and channel estimates

pbchIndices = ltePBCHIndices(enb);
[pbchRx, pbchHest] = lteExtractResources( ...
    pbchIndices, rxgrid(:,1:L,:), hest(:,1:L,:,:));

% Decode PBCH
[bchBits, pbchSymbols, nfmod4, mib, enb.CellRefP] = ltePBCHDecode( ...
    enb, pbchRx, pbchHest, nest); 

% Parse MIB bits
enb = lteMIB(mib, enb); 

% Incorporate the nfmod4 value output from the function ltePBCHDecode, as
% the NFrame value established from the MIB is the System Frame Number
% (SFN) modulo 4 (it is stored in the MIB as floor(SFN/4))
enb.NFrame = enb.NFrame+nfmod4;

% Display cell wide settings after MIB decoding

if (enb.CellRefP~=0)

fprintf('\nPerforming frequency offset estimation...\n');
fprintf('Frequency offset: %0.3fHz\n',delta_f);

if (max(corr{1})<threshold)    
    warning('Synchronization signal correlation was weak; detected cell identity may be incorrect.');
end

fprintf('Timing offset to frame start: %d samples\n',offset);

fprintf('Performing MIB decoding...\n');
fprintf('Cell-wide settings after MIB decoding:\n');
disp(enb);

else
% comparing with Extended FDD  
    
% Set eNodeB basic parameters
enb = struct;                   % eNodeB config structure
enb.DuplexMode = 'FDD';         % assume FDD duxplexing mode
enb.CyclicPrefix = 'Extended';    % assume normal cyclic prefix
enb.NDLRB = 6;                  % Number of resource blocks
ofdmInfo = lteOFDMInfo(enb);    % Needed to get the sampling rate

%%  

% Downsample received signal
nSamples = ceil(ofdmInfo.SamplingRate/round(sr)*size(eNodeBOutput,1));
nRxAnts = size(eNodeBOutput, 2);
downsampled = zeros(nSamples, nRxAnts);
for i=1:nRxAnts
    downsampled(:,i) = resample(eNodeBOutput(:,i), ofdmInfo.SamplingRate, round(sr));
end

%% Frequency offset estimation and correction

delta_f = lteFrequencyOffset(setfield(enb,'DuplexMode','FDD'), downsampled); %#ok<SFLD>

downsampled = lteFrequencyCorrect(enb, downsampled, delta_f);
    
%% Cell Search and Synchronization

% Cell search to find cell identity and timing offset
%fprintf('\nPerforming cell search...\n');
[cellID, offset] = lteCellSearch(enb, downsampled);

% Compute the correlation for each of the three possible primary cell identities

corr = cell(1,3);
for i = 0:2
    enb.NCellID = mod(cellID + i,504);
    [~,corr{i+1}] = lteDLFrameOffset(enb, downsampled);
    corr{i+1} = sum(corr{i+1},2);
end
threshold = 1.3 * max([corr{2}; corr{3}]); % multiplier of 1.3 empirically obtained

enb.NCellID = cellID;

% plot PSS/SSS correlation and threshold
synchCorrPlot.YLimits = [0 max([corr{1}; threshold])*1.1];
%step(synchCorrPlot, [corr{1} threshold*ones(size(corr{1}))]);

% perform timing synchronisation

downsampled = downsampled(1+offset:end,:); 
enb.NSubframe = 0;


%% OFDM Demodulation and Channel Estimation  

% Channel estimator configuration
cec.PilotAverage = 'UserDefined';     % Type of pilot averaging
cec.FreqWindow = 9;                   % Frequency window size    
cec.TimeWindow = 9;                   % Time window size    
cec.InterpType = 'cubic';             % 2D interpolation type
cec.InterpWindow = 'Centered';        % Interpolation window type
cec.InterpWinSize = 1;                % Interpolation window size  

% Assume 4 cell-specific reference signals for initial decoding attempt
% ensures channel estimates are available for all cell-specific reference signal

enb.CellRefP = 4;   
                    
%fprintf('Performing OFDM demodulation...\n\n');

griddims = lteResourceGridSize(enb); % Resource grid dimensions
L = griddims(2);                     % Number of OFDM symbols in a subframe 
% OFDM demodulate signal 
rxgrid = lteOFDMDemodulate(enb, downsampled);    
if (isempty(rxgrid))
    fprintf('After timing synchronization, signal is shorter than one subframe so no further demodulation will be performed.\n');
    return;
end
% Perform channel estimation
% if (strcmpi(enb.DuplexMode,'TDD'))
%     enb.TDDConfig = 0;
%     enb.SSC = 0;
% end
[hest, nest] = lteDLChannelEstimate(enb, cec, rxgrid(:,1:L,:));

%% PBCH Demodulation, BCH Decoding, MIB parsing

% Decode the MIB
% Extract resource elements (REs) corresponding to the PBCH from the first
% subframe across all receive antennas and channel estimates

pbchIndices = ltePBCHIndices(enb);
[pbchRx, pbchHest] = lteExtractResources( ...
    pbchIndices, rxgrid(:,1:L,:), hest(:,1:L,:,:));

% Decode PBCH
[bchBits, pbchSymbols, nfmod4, mib, enb.CellRefP] = ltePBCHDecode( ...
    enb, pbchRx, pbchHest, nest); 

% Parse MIB bits
enb = lteMIB(mib, enb); 

enb.NFrame = enb.NFrame+nfmod4;

% Display cell wide settings after MIB decoding

if (enb.CellRefP~=0)

fprintf('\nPerforming frequency offset estimation...\n');
fprintf('Frequency offset: %0.3fHz\n',delta_f);

if (max(corr{1})<threshold)    
    warning('Synchronization signal correlation was weak; detected cell identity may be incorrect.');
end

fprintf('Timing offset to frame start: %d samples\n',offset);

fprintf('Performing MIB decoding...\n');
fprintf('Cell-wide settings after MIB decoding:\n');
disp(enb);
 
else
    %%  comparing with Normal TDD   %%%%
    
% Set eNodeB basic parameters
enb = struct;                   % eNodeB config structure
enb.DuplexMode = 'TDD';         % assume FDD duxplexing mode
enb.CyclicPrefix = 'Normal';    % assume normal cyclic prefix
enb.NDLRB = 6;                  % Number of resource blocks
ofdmInfo = lteOFDMInfo(enb);    % Needed to get the sampling rate

%%  

% Downsample received signal
nSamples = ceil(ofdmInfo.SamplingRate/round(sr)*size(eNodeBOutput,1));
nRxAnts = size(eNodeBOutput, 2);
downsampled = zeros(nSamples, nRxAnts);
for i=1:nRxAnts
    downsampled(:,i) = resample(eNodeBOutput(:,i), ofdmInfo.SamplingRate, round(sr));
end

%% Frequency offset estimation and correction
% Prior to OFDM demodulation, any significant frequency offset must be
% removed. The frequency offset in the I/Q waveform is estimated and
% corrected using <matlab:doc('lteFrequencyOffset') lteFrequencyOffset> and
% <matlab:doc('lteFrequencyCorrect') lteFrequencyCorrect>. The frequency
% offset is estimated by means of correlation of the cyclic prefix and
% therefore can estimate offsets up to +/- half the subcarrier spacing i.e.
% +/- 7.5kHz.


% % Note that the duplexing mode is set to FDD here because timing synch has
% % not yet been performed - for TDD we cannot use the duplexing arrangement 
% % to indicate which time periods to use for frequency offset estimation
% prior to doing timing synch.

delta_f = lteFrequencyOffset(setfield(enb,'DuplexMode','FDD'), downsampled); %#ok<SFLD>

downsampled = lteFrequencyCorrect(enb, downsampled, delta_f);
    
%% Cell Search and Synchronization

% Cell search to find cell identity and timing offset
%fprintf('\nPerforming cell search...\n');
[cellID, offset] = lteCellSearch(enb, downsampled);

% Compute the correlation for each of the three possible primary cell identities

corr = cell(1,3);
for i = 0:2
    enb.NCellID = mod(cellID + i,504);
    [~,corr{i+1}] = lteDLFrameOffset(enb, downsampled);
    corr{i+1} = sum(corr{i+1},2);
end
threshold = 1.3 * max([corr{2}; corr{3}]); % multiplier of 1.3 empirically obtained

enb.NCellID = cellID;

% plot PSS/SSS correlation and threshold
synchCorrPlot.YLimits = [0 max([corr{1}; threshold])*1.1];
%step(synchCorrPlot, [corr{1} threshold*ones(size(corr{1}))]);

% perform timing synchronisation

downsampled = downsampled(1+offset:end,:); 
enb.NSubframe = 0;


%% OFDM Demodulation and Channel Estimation  

% Channel estimator configuration
cec.PilotAverage = 'UserDefined';     % Type of pilot averaging
cec.FreqWindow = 9;                   % Frequency window size    
cec.TimeWindow = 9;                   % Time window size    
cec.InterpType = 'cubic';             % 2D interpolation type
cec.InterpWindow = 'Centered';        % Interpolation window type
cec.InterpWinSize = 1;                % Interpolation window size  

% Assume 4 cell-specific reference signals for initial decoding attempt
% ensures channel estimates are available for all cell-specific reference signal

enb.CellRefP = 4;   
                    
%fprintf('Performing OFDM demodulation...\n\n');

griddims = lteResourceGridSize(enb); % Resource grid dimensions
L = griddims(2);                     % Number of OFDM symbols in a subframe 
% OFDM demodulate signal 
rxgrid = lteOFDMDemodulate(enb, downsampled);    
if (isempty(rxgrid))
    fprintf('After timing synchronization, signal is shorter than one subframe so no further demodulation will be performed.\n');
    return;
end
% Perform channel estimation
if (strcmpi(enb.DuplexMode,'TDD'))
    enb.TDDConfig = rmc.TDDConfig ;
    enb.SSC = rmc.SSC ;
 
end
[hest, nest] = lteDLChannelEstimate(enb, cec, rxgrid(:,1:L,:));

%% PBCH Demodulation, BCH Decoding, MIB parsing

% Decode the MIB
% Extract resource elements (REs) corresponding to the PBCH from the first
% subframe across all receive antennas and channel estimates

pbchIndices = ltePBCHIndices(enb);
[pbchRx, pbchHest] = lteExtractResources( ...
    pbchIndices, rxgrid(:,1:L,:), hest(:,1:L,:,:));

% Decode PBCH
[bchBits, pbchSymbols, nfmod4, mib, enb.CellRefP] = ltePBCHDecode( ...
    enb, pbchRx, pbchHest, nest); 

% Parse MIB bits
enb = lteMIB(mib, enb); 

enb.NFrame = enb.NFrame+nfmod4;

% Display cell wide settings after MIB decoding

if (enb.CellRefP~=0)

fprintf('\nPerforming frequency offset estimation...\n');
fprintf('Frequency offset: %0.3fHz\n',delta_f);

if (max(corr{1})<threshold)    
    warning('Synchronization signal correlation was weak; detected cell identity may be incorrect.');
end

fprintf('Timing offset to frame start: %d samples\n',offset);

fprintf('Performing MIB decoding...\n');
fprintf('Cell-wide settings after MIB decoding:\n');
disp(enb);
    
else
        %%  comparing with Extended TDD   %%%%
    
% Set eNodeB basic parameters
enb = struct;                   % eNodeB config structure
enb.DuplexMode = 'TDD';         % assume FDD duxplexing mode
enb.CyclicPrefix = 'Extended';    % assume normal cyclic prefix
enb.NDLRB = 6;                  % Number of resource blocks
ofdmInfo = lteOFDMInfo(enb);    % Needed to get the sampling rate

%%  

% Downsample received signal
nSamples = ceil(ofdmInfo.SamplingRate/round(sr)*size(eNodeBOutput,1));
nRxAnts = size(eNodeBOutput, 2);
downsampled = zeros(nSamples, nRxAnts);
for i=1:nRxAnts
    downsampled(:,i) = resample(eNodeBOutput(:,i), ofdmInfo.SamplingRate, round(sr));
end

%% Frequency offset estimation and correction
% Prior to OFDM demodulation, any significant frequency offset must be
% removed. The frequency offset in the I/Q waveform is estimated and
% corrected using <matlab:doc('lteFrequencyOffset') lteFrequencyOffset> and
% <matlab:doc('lteFrequencyCorrect') lteFrequencyCorrect>. The frequency
% offset is estimated by means of correlation of the cyclic prefix and
% therefore can estimate offsets up to +/- half the subcarrier spacing i.e.
% +/- 7.5kHz.


% % Note that the duplexing mode is set to FDD here because timing synch has
% % not yet been performed - for TDD we cannot use the duplexing arrangement 
% % to indicate which time periods to use for frequency offset estimation
% prior to doing timing synch.

delta_f = lteFrequencyOffset(setfield(enb,'DuplexMode','FDD'), downsampled); %#ok<SFLD>

downsampled = lteFrequencyCorrect(enb, downsampled, delta_f);
    
%% Cell Search and Synchronization

% Cell search to find cell identity and timing offset
%fprintf('\nPerforming cell search...\n');
[cellID, offset] = lteCellSearch(enb, downsampled);

% Compute the correlation for each of the three possible primary cell identities

corr = cell(1,3);
for i = 0:2
    enb.NCellID = mod(cellID + i,504);
    [~,corr{i+1}] = lteDLFrameOffset(enb, downsampled);
    corr{i+1} = sum(corr{i+1},2);
end
threshold = 1.3 * max([corr{2}; corr{3}]); % multiplier of 1.3 empirically obtained

enb.NCellID = cellID;

% plot PSS/SSS correlation and threshold
synchCorrPlot.YLimits = [0 max([corr{1}; threshold])*1.1];
%step(synchCorrPlot, [corr{1} threshold*ones(size(corr{1}))]);

% perform timing synchronisation

downsampled = downsampled(1+offset:end,:); 
enb.NSubframe = 0;


%% OFDM Demodulation and Channel Estimation  

% Channel estimator configuration
cec.PilotAverage = 'UserDefined';     % Type of pilot averaging
cec.FreqWindow = 9;                   % Frequency window size    
cec.TimeWindow = 9;                   % Time window size    
cec.InterpType = 'cubic';             % 2D interpolation type
cec.InterpWindow = 'Centered';        % Interpolation window type
cec.InterpWinSize = 1;                % Interpolation window size  

% Assume 4 cell-specific reference signals for initial decoding attempt
% ensures channel estimates are available for all cell-specific reference signal

enb.CellRefP = 4;   
                    
%fprintf('Performing OFDM demodulation...\n\n');

griddims = lteResourceGridSize(enb); % Resource grid dimensions
L = griddims(2);                     % Number of OFDM symbols in a subframe 
% OFDM demodulate signal 
rxgrid = lteOFDMDemodulate(enb, downsampled);    
if (isempty(rxgrid))
    fprintf('After timing synchronization, signal is shorter than one subframe so no further demodulation will be performed.\n');
    return;
end
% Perform channel estimation
if (strcmpi(enb.DuplexMode,'TDD'))
    enb.TDDConfig = rmc.TDDConfig ;
    enb.SSC = rmc.SSC ;
 
end
[hest, nest] = lteDLChannelEstimate(enb, cec, rxgrid(:,1:L,:));

%% PBCH Demodulation, BCH Decoding, MIB parsing

% Decode the MIB
% Extract resource elements (REs) corresponding to the PBCH from the first
% subframe across all receive antennas and channel estimates

pbchIndices = ltePBCHIndices(enb);
[pbchRx, pbchHest] = lteExtractResources( ...
    pbchIndices, rxgrid(:,1:L,:), hest(:,1:L,:,:));

% Decode PBCH
[bchBits, pbchSymbols, nfmod4, mib, enb.CellRefP] = ltePBCHDecode( ...
    enb, pbchRx, pbchHest, nest); 

% Parse MIB bits
enb = lteMIB(mib, enb); 

enb.NFrame = enb.NFrame+nfmod4;

% Display cell wide settings after MIB decoding

if (enb.CellRefP~=0)

fprintf('\nPerforming frequency offset estimation...\n');
fprintf('Frequency offset: %0.3fHz\n',delta_f);

if (max(corr{1})<threshold)    
    warning('Synchronization signal correlation was weak; detected cell identity may be incorrect.');
end

fprintf('Timing offset to frame start: %d samples\n',offset);

fprintf('Performing MIB decoding...\n');
fprintf('Cell-wide settings after MIB decoding:\n');
disp(enb);
    
    
end
end
end
end


if (enb.CellRefP==0)
    fprintf('MIB decoding failed (enb.CellRefP=0).\n\n');
    return;
end
if (enb.NDLRB==0)
    fprintf('MIB decoding failed (enb.NDLRB=0).\n\n');
    return;
end

