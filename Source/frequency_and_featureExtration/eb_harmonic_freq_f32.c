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

#define fftSize 1024
#define ifftFlag 0
#define doBitReverse 1

void eb_harmonic_freq_f32(
  float32_t * pSrc,
	float32_t * pDst,
	float32_t f_0,
	float32_t half_band,
	uint8_t dst_size)
{
  uint8_t dstCount; // loop number
  
  float32_t pDst_mean[2*half_band];

  float32_t mag_spectrum[fftSize]; // magnitude spectrum 
        
   /* Process the data through the CFFT module */
  arm_cfft_f32(&arm_cfft_sR_f32_len1024,pSrc,ifftFlag,doBitReverse);

   /* Process the data through the Complex Magnitude Module for
   calculating the magnitude */
   arm_cmplx_mag_f32(pSrc,mag_spectrum,fftSize);
  
  // harmonic frequency extraction
  for(dstCount=1;dstCount<dst_size;dstCount++){
   // arm_mean_f32(dstCount*f_0-half_band,2*half_band,pDst_mean);
  }
  arm_scale_f32(pDst_mean,2*half_band,pDst,dst_size);
  
}
