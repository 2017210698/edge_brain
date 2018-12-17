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
 * @brief Float32 envolop spectrum.
 * @param[in]   *pSrc points to the input buffer
 * @param[out]  *pDst points to the output buffer
 * @param[in]   src_size the size of the input signal
 * @param[in]   fft_size the size of FFT transform points
 * @return none.
 * @note This is only an example to show the doc fomat and 
				 project organization. A more efficient approach 
				 should be implemented. 
*/


void eb_envolop_spectrum_f32(
	float32_t * pSrc,
	float32_t * pDst,
	float32_t * pBuffer,
	uint16_t srcLen,
	uint16_t fftSize)
{
	uint16_t i; // loop variant
	float32_t pTransMatrix[2*256];
	float32_t pBufferRes[256];
	
	/* insert zero to prepare data format for arm_cfft_f32 */ 
	for(i=0;i<fftSize;i++)
	{
		pBuffer[2*i]=pSrc[i];
		pBuffer[2*i+1]=0;
		
		pBufferRes[i]=pSrc[i];
	}
	
	/* utilize the method in matlab to realize hilbert transform   */ 
	arm_cfft_f32(&arm_cfft_sR_f32_len16,pBuffer,0,1); // calculate the FFT of  the input sequence
	/* create a vector h whose elements h(i) have the format below */
	arm_offset_f32(pTransMatrix,-2,pTransMatrix,fftSize+1);
	pTransMatrix[0]=-1;
	pTransMatrix[fftSize+1]=-1;
	arm_mult_f32(pBuffer,pTransMatrix,pBuffer,2*fftSize);
	/**
	for(i=0;i<2*fftSize;i++)
	{
		if(i==0||i==1){
		pBuffer[i]=-pBuffer[i];
		}
		else if(i>1&&i<fftSize)
		{
			pBuffer[i]=-2*pBuffer[i];
		}
		else if(i==fftSize||i==fftSize+1){
			pBuffer[i]=-pBuffer[i];
		}
		else{
			pBuffer[i]=0;
		}
	}
	*/
	 // calculate the inverse FFT of the sequence obtained above
	arm_cfft_f32(&arm_cfft_sR_f32_len16,pBuffer,1,1);
	
	/* calculate sqrt(signal^2+hilbert^2) */
	for(i=0;i<fftSize;i++)
	{
		//pBuffer[2*i] = pSrc[i-fftSize];
		//pBuffer[2*i] = 1.2f*arm_sin_f32(2*3.1415926f*50*i/1000)+1;
		pBuffer[2*i]=pBufferRes[i];
	}
	arm_cmplx_mag_f32(pBuffer,pSrc,fftSize);
	
	/* insert zero to prepare data format for arm_cfft_f32 */ 
	for(i=0;i<fftSize;i++)
	{
		pBuffer[2*i] = pSrc[i];
		pBuffer[2*i+1]=0;
	}
	/* calculate the FFT of  the input sequence and the magnitude after FFT to obtain envolop */
	arm_cfft_f32(&arm_cfft_sR_f32_len16,pBuffer,0,1);
	arm_cmplx_mag_f32(pBuffer,pDst,fftSize);
}
