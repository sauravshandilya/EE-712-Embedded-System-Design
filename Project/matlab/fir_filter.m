for_phase = 0.707 - 0.707*1i; % the phase component
N = 9;
for i = 1:N
    H(i) = (3.7847/sqrt(i))*for_phase; % magnitude and phase
end
% finding inverse fft
coeff = ifft(H,N);
coeff = abs(coeff); % absolute value
for i = 1:N
    res(i) = 10000/coeff(i);
end