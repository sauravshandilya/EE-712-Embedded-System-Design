import numpy as np	# for fft
import math 		# for finding square root


for_phase = 0.707 - 0.707*1j ; # the phase component

N = 9;
H = [None]*10;
res = [None]*10;
for i in range(0,10):
	H[i] = ((3.7847/math.sqrt(i+1))*for_phase); # magnitude and phase
#end
# finding inverse fft
h_array = np.asarray(H);
print h_array
coeff = np.fft.ifft(h_array);
coeff = abs(coeff); # absolute value
#print coeff
#print coeff[1]
for i in range(0,10):
	res[i] = 10000/coeff[i];
	print ("resistor" + str(i) + " =")
	print res[i]
#end

