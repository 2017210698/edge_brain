/****************************************************************************
 * Copyright (C) 2017-2018 PI2STAR                                          *
 ****************************************************************************/

/**
 * @file eb_harmonic_freq_f32.c
 * @author lwg
 * @date 28 Nov 2018
 * @brief Float32 harmonic frequency extration
 *
 * Float32 harmonic frequency extration using arm_cfft_f32 and arm_cfft_sR_f32.
 */

#include "arm_math.h"
#include "arm_const_structs.h"

/**
 * @brief Float32 harmonic frequency extration.
 * @param[in]   *pSrc points to the input buffer
 * @param[out]  *pDst points to the output buffer
 * @param[in]   f_0 the fundermental frequency
 * @param[in]   half_band the frequency bandwidth
 * @param[in]   dst_size the max order of the harmonic frequency, include 0.5X and 1X frequency
 * @return none.
 * @note This is only an example to show the doc fomat and 
         project organization. A more efficient approach 
         should be implemented. 
*/

void eb_harmonic_freq_f32(
  float32_t * pSrc,
	float32_t * pDst,
	float32_t * pFftBuffer,
	float32_t * pMagBuffer,
	uint8_t baseFreq,
	uint8_t halfBand,
	uint8_t dstSize,
	uint32_t samplingRate)
{
  uint8_t dstCount; // loop number
  arm_rfft_fast_instance_f32 S;
	uint16_t fftSize=1024; // real sequence fft length
	uint8_t ifftFlag=0; // rfft if flag is 0, rifft if flag is 1
	float32_t pMeanResult; // store intermediate result
	uint8_t blockSize; // store frequency range of harmonic component

	uint8_t deltaRate=samplingRate/fftSize;
	
	/* 0.5Multiple frequency extration parameters */
	uint8_t begFreq=(0.5*baseFreq-halfBand)/deltaRate;
	uint8_t endFreq=(0.5*baseFreq+halfBand)/deltaRate;
	blockSize=endFreq-begFreq+1;
	
	/* initiate the structure */
	arm_rfft_fast_init_f32(&S,fftSize);
	
	/* 1024 points arm_rfft_fast_f32 */
	arm_rfft_fast_f32(&S,pSrc,pFftBuffer,ifftFlag);
	
	/* compute the magnitute 512 points */
	arm_cmplx_mag_f32(pFftBuffer,pMagBuffer,fftSize);
  

	/* harmonic frequency extraction */
	/* 0.5Multiple frequency extration */
	arm_mean_f32(&pMagBuffer[begFreq],blockSize,&pMeanResult);
	pDst[0]=pMeanResult*blockSize;
	
	/* other Multiple frequency extration */
	for(dstCount=1;dstCount<dstSize;dstCount++)
	{
		begFreq=(dstCount*baseFreq-halfBand)/deltaRate;
		endFreq=(dstCount*baseFreq+halfBand)/deltaRate;
		blockSize=endFreq-begFreq+1;
		arm_mean_f32(&pMagBuffer[begFreq],blockSize,&pMeanResult);
		pDst[dstCount]=pMeanResult*blockSize;
		pDst++;
  }
}
