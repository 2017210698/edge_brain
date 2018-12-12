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
 * @param[in]   *pSrc points to the input buffer
 * @param[out]  *pDst points to the output buffer
 * @param[in]   blockSize number of samples in input vector
 * @param[in]   winSize filter window size
 * @return none.
 * @note This is only an example to show the doc fomat and 
         project organization. A more efficient approach 
         should be implemented. 
*/

void eb_mean_filtering_f32(
  float32_t * pSrc,
  float32_t * pDst,
	float32_t * pBuffer,
  uint32_t blockSize,
  uint32_t winSize)
{
	
	
	// using convolution method to obtain the mean filtering
	arm_fill_f32(1.0f/winSize,pBuffer,winSize);
	arm_conv_f32(pSrc,blockSize,pBuffer,winSize,pDst);
	
	/* using meaning method */
	
	//  uint32_t i;         /* loop counter */
	//  uint32_t dstSize;   /* output buffer size */
		
	//  /* Calculate output buffer size */
	//  dstSize = blockSize - winSize + 1;
	//  
	//  for(i=0; i<dstSize; i++){
	//    arm_mean_f32(pSrc++, winSize, pDst++);
	//  }	
}
