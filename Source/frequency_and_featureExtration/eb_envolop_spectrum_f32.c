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
	float32_t * pFftBuffer,
	uint16_t srcLen,
	uint16_t fftSize)
{

	uint8_t ifftFlag=0; // rfft if flag is 0, rifft if flag is 1
	//float32_t interValue;
	float32_t pIfftBuffer[2048];
	float32_t pInterBuffer[1024];
	arm_rfft_fast_instance_f32 S1,S2;
	/* initiate the structure */
	arm_rfft_fast_init_f32(&S1,fftSize);
	arm_rfft_fast_init_f32(&S2,2*fftSize);
	
	/* hilbert transform */
	arm_rfft_fast_f32(&S1,pSrc,pFftBuffer,ifftFlag);
	arm_scale_f32(pFftBuffer,2,pFftBuffer,2*fftSize);
	ifftFlag=1;
	arm_rfft_fast_f32(&S2,pFftBuffer,pIfftBuffer,ifftFlag);

	arm_cmplx_mag_f32(pIfftBuffer,pInterBuffer,fftSize);
	arm_rfft_fast_f32(&S1,pInterBuffer,pFftBuffer,ifftFlag);
	arm_cmplx_mag_f32(pFftBuffer,pDst,fftSize);
}
