2016 - EE712  Group M-01
================================================ 
 
Group Info 
---------- 
+   Saurav Shandilya
+   Piyush Manavar
+   Akshya Bajpai 
 
Project Description 
------------------- 

This projects aims at getting a programmable band limited noise by digital filtering white noise obtained by Pseudo Random Binary Sequence (PRBS) generator. PRBS is generated using 32 stage linear feedback shift registers (LFSR). The PRBS output spectrum approximates a white noise spectrum. The filter coefficients, of an 8-tap FIR filter to convert the white noise (PRBS output) to band limited noise, are obtained using MATLAB. Filtering is done by resistance-weighted op-amp based network for realizing a digital FIR filter from the shift register taps. Digital potentiometer (AD8403) has been used for getting variable resistors of summer circuit. The FFT spectrum of the PRBS and the output noise obtained are analyzed using a DSO and this matches the expected outcome. User interface is a python based GUI.
