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
#define PI 3.14

void eb_envolop_spectrum_f32(
	float32_t * pSrc,
	float32_t * pDst,
	uint8_t src_size,
	uint8_t fft_size)
{
	uint8_t i; // loop variant
	float32_t * pSrc_fft;
	float32_t * pSrc_abs;
	uint32_t t; // the time points of input signal
	float32_t Ht[src_size];

	for(i=0;i<src_size;i++) 
	{
		Ht[i]=i/(PI*fft_size);
	}
	arm_conv_f32()
	arm_rms_f32(pSrc,src_size,)
	arm_cfft_f32(&arm_cfft_f32_len1024,pSrc,0,1);
	arm_cmplx_mag_f32(pSrc,pSrc_fft,1024);
	

	}

