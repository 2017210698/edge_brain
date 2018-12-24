/****************************************************************************
 * Copyright (C) 2017-2018 PI2STAR                                          *
 ****************************************************************************/

/**
 * @file eb_mean_filtering_f32.c
 * @author Winfred SU
 * @date 28 Nov 2018
 * @brief Float32 mean filtering
 *
 * Float32 mean filtering using arm_conv_f32 and arm_fill_f32.
 */

#include "arm_math.h"

/**
 * @brief Float32 mean filtering.
 * @param[in]   *pSrc points to the input buffer.
 * @param[out]  *pDst points to the output buffer.
 * @param[in]   *pBuffer points to window matrix buffer used for convolution.
 * @param[in]   srcLen the number of samples in input vector.
 * @param[in]   winSize filter window size.
 * @return none.
 * @note  Using convolution method to obtain the mean filtering, 
          after arm_conv,the length is srcLen+winLen-1, here we 
          only save srcLen numbers.
          Float32 mean filtering using arm_conv_f32 and arm_fill_f32.
*/

void eb_mean_filtering_f32(
  float32_t * pSrc,
  float32_t * pDst,
	float32_t * pBuffer,
  uint32_t srcLen,
  uint32_t winLen)
{	
	// using convolution method to obtain the mean filtering
	arm_fill_f32(1.0f/winLen,pBuffer,winLen);
	arm_conv_f32(pSrc,srcLen,pBuffer,winLen,pDst);
}
