/*
 * coeff.h
 *
 *  Created on: 01-May-2016
 *      Author: saurav
 */

#ifndef COEFF_H_
#define COEFF_H_

// low pass filter coeffs.
#define R0 34026
#define R1 10067
#define R2 6040
#define R3 4861
#define R4 4861
#define R5 6040
#define R6 10067
#define R7 34026


/*
#define R0 4836
#define R1 25254
#define R2 37939
#define R3 45983
#define R4 48755
#define R5 45983
#define R6 37939
#define R7 25254
*/

/*
#define R0 10743
#define R1 1434
#define R2 850
#define R3 750
#define R4 974
#define R5 2651
#define R6 7861
#define R7 65443
*/

/*
#define R0 1282
#define R1 1894
#define R2 2163
#define R3 1433
#define R4 5420
#define R5 1355
#define R6 5165
#define R7 7811
*/


uint32_t filter_coeff [8][8] = {
		{4836,25254,37939,45983,48755,45983,37939,25254},			//low pass
		{10743,1434,850,750,974,2651,7861,65443},					// BP 101-201
		{1282, 1894, 2163, 1433, 5420, 1355, 5165, 7811}			//BP 301-401

};

#endif /* COEFF_H_ */
