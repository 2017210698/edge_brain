/****************************************************************************
 * Copyright (C) 2017-2018 PI2STAR                                          *
 ****************************************************************************/

/**
 * @file eb_harmonic_freq_f32.c
 * @author lwg
 * @date 28 Nov 2018
 * @brief Float32 envolop spectrum
 *
 * Float32 envolop spectrum using arm_cfft_f32 and arm_cfft_sR_f32.
 */

#include "arm_math.h"
#include "arm_const_structs.h"

/**
 * @brief Float32 envolop spectrum function.
 * @param[in]   *pSrc points to the input buffer.
 * @param[out]  *pDst points to the output buffer.
 * @param[in]   *pBuffer points to the intermediate buffer used to insert zero to the input signal for arm_cfft_f32.
 * @param[in]   *pTransMatrix points to the intermediate buffer used for the transform matrix of hilbert transform.
 * @param[in]		fftSize the size of FFT transform points
 * @return none.
 * @note Using hilbert transform method to obtain envolop spectrum.
 					Float32 envolop spectrum using arm_cfft_f32,arm_offset_f32,arm_mult_f32 and arm_cmplx_mag_f32.
 					Caution: the floating-point complex FFT uses a mixed cardinality algorithm implemented by multiple bases 8 
					and a single base 2 or base 4 algorithm. The algorithm supports lengths [16, 32, 64, ..., 4096] and uses 
					different twiddle factor tables for each length as needed.
					When arm_cfft_f32 is called, you need include the header file arm_const_structs.h.For example:
					arm_cfft_f32(arm_cfft_sR_f32_len64,pSrc,0,1), the above formula is to calculate a 64-point FFT
*/


void eb_envolop_spectrum_f32(
	float32_t * pSrc,
	float32_t * pDst,
	float32_t * pBuffer,
	float32_t * pTransMatrix,
	uint16_t fftSize)
{
	uint16_t i; // loop variant
	uint8_t ifftFlag=0; // rfft if flag is 0, rifft if flag is 1
  uint8_t bitReverseFlag=1; // flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit

	for(i=0;i<fftSize;i++) // insert zero to prepare data format for arm_cfft_f32 
	{
		pBuffer[2*i]=pSrc[i];
		pBuffer[2*i+1]=0;
		pDst[i]=pSrc[i]; // backup input signal  
	}
	
	/* utilize the method in matlab to realize hilbert transform   */ 
	arm_cfft_f32(&arm_cfft_sR_f32_len256,pBuffer,ifftFlag,bitReverseFlag); // calculate the FFT of  the input sequence
	/* create a vector h whose elements h(i) have the format below */
	arm_offset_f32(pTransMatrix,-2,pTransMatrix,fftSize+1);
	pTransMatrix[0]=-1;
	pTransMatrix[fftSize+1]=-1;
	arm_mult_f32(pBuffer,pTransMatrix,pBuffer,2*fftSize);
	

	 // calculate the inverse FFT of the sequence obtained above
	ifftFlag=1;
	arm_cfft_f32(&arm_cfft_sR_f32_len256,pBuffer,ifftFlag,bitReverseFlag);
	
	/* calculate sqrt(signal^2+hilbert^2) */
	for(i=0;i<fftSize;i++)
	{
		pBuffer[2*i]=pDst[i];
	}
	
	arm_cmplx_mag_f32(pBuffer,pSrc,fftSize);
	
	/* insert zero to prepare data format for arm_cfft_f32 */ 
	for(i=0;i<fftSize;i++)
	{
		pBuffer[2*i] = pSrc[i];
		pBuffer[2*i+1]=0;
	}
	/* calculate the FFT of  the input sequence and the magnitude after FFT to obtain envolop */
	ifftFlag=0;
	arm_cfft_f32(&arm_cfft_sR_f32_len256,pBuffer,ifftFlag,bitReverseFlag);
	arm_cmplx_mag_f32(pBuffer,pDst,fftSize);
}
