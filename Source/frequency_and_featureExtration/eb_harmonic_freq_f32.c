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
 * @brief Float32 harmonic frequency extraction function.
 * @param[in]   *pSrc points to the input buffer.
 * @param[out]  *pDst points to the output buffer.
 * @param[in]   *pFftBuffer points to the FFT buffer used for intermediate buffer and FFT buffer.
 * @param[in]   *pMagBuffer points to the Mag buffer used for intermediate buffer and FFT buffer.
 * @param[in]   pitch the base frequency.
 * @param[in]   srcLen the size of input signal.
 * @param[in]   dst_size the max order of the harmonic frequency, include 0.5X and 1X frequency.
 * @param[in]   samplingRate sampling rate.
 * @return none.
 * @note 	Using FFT method to obtain harmonic frequency extraction.
 					Float32 harmonic frequency extraction using arm_mean_f32,arm_fill_f32,arm_sub_f32,
 					arm_rfft_fast_init_f32,arm_rfft_fast_f32,arm_cmplx_mag_f32.
*/

void eb_harmonic_freq_f32(
  float32_t * pSrc,
	float32_t * pDst,
	float32_t * pFftBuffer,
	float32_t * pMagBuffer,
	uint8_t pitch,
	uint16_t srcLen,
	uint8_t dstSize,
	uint32_t samplingRate)
{
  uint8_t dstCount; // loop number
  arm_rfft_fast_instance_f32 S;
	uint16_t fftSize=1024; // real sequence fft length
	uint8_t ifftFlag=0; // rfft if flag is 0, rifft if flag is 1
	float32_t pMeanResult; // store intermediate result
	uint8_t freqRange; // store frequency range of harmonic component
	uint8_t deltaRate;
	uint8_t halfBand;
	uint8_t beginFreq;
	uint8_t endFreq;
	
	// testSrc=eb_highPass_filter_f32();  // high pass filter
	/* get halfBand */
	float32_t median; // interval value
	arm_mean_f32(pSrc,srcLen,&median);
	arm_fill_f32(median,pFftBuffer,srcLen);
	arm_sub_f32(pSrc,pFftBuffer,pSrc,srcLen); // data = data-np.mean(data)
	deltaRate=samplingRate/fftSize; // frequence interval
	halfBand= (uint8_t)(0.5*pitch/deltaRate);	
	
	/* 0.5Multiple frequency extration parameters */
	beginFreq=(uint8_t)((0.5*pitch-halfBand)/deltaRate);
	endFreq=(uint8_t)((0.5*pitch+halfBand)/deltaRate);
	freqRange=endFreq-beginFreq+1;
	
	/* initiate the structure */
	arm_rfft_fast_init_f32(&S,fftSize);
	
	/* 1024 points arm_rfft_fast_f32 */
	arm_rfft_fast_f32(&S,pSrc,pFftBuffer,ifftFlag);
	
	/* compute the magnitute 512 points */
	arm_cmplx_mag_f32(pFftBuffer,pMagBuffer,fftSize);
  

	/* harmonic frequency extraction */
	/* 0.5Multiple frequency extration */
	arm_mean_f32(&pMagBuffer[beginFreq],freqRange,&pMeanResult);
	pDst[0]=pMeanResult*freqRange;
	
	/* other Multiple frequency extration */
	for(dstCount=1;dstCount<dstSize;dstCount++)
	{
		beginFreq=(dstCount*pitch-halfBand)/deltaRate;
		endFreq=(dstCount*pitch+halfBand)/deltaRate;
		freqRange=endFreq-beginFreq+1;
		arm_mean_f32(&pMagBuffer[beginFreq],freqRange,&pMeanResult);
		pDst[dstCount]=pMeanResult*freqRange;
		pDst++;
  }
}
