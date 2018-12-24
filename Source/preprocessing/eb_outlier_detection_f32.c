
/****************************************************************************
 * Copyright (C) 2017-2018 PI2STAR                                          *
 ****************************************************************************/

/**
 * @file eb_outlier_detection_f32.c
 * @author liwg
 * @date 23 Dec 2018
 * @brief Float32 outlier detection
 *
 * Float32 outlier detection using arm_max_f32.
 */

#include "arm_math.h"

/**
 * @brief Float32 outlier detection.
 * @param[in]   *pSrc points to the input buffer
 * @param[in]   srcLen the size of the input signal
 * @param[in]   b the constant parameter
 * @return none.
 * @note  Using median average method to outlier detection, remove the
          point away from the center. 
          Float32 outlier detection using arm_max_f32.
*/
void eb_outlier_detection_f32(
  float32_t * pSrc,
	uint32_t srcLen,
	float32_t b
)

{

	float32_t Max;
  uint32_t maxIndex;
  float32_t median;

  uint32_t srcCount; // loop variant
  float32_t lowerLimit;
  float32_t upperLimit;

  // Compute the maximum value of an array of pSrc.
  arm_max_f32(pSrc,srcLen,&Max,&maxIndex);

  // compute the median
  median=Max/4.0f;
  
  // outlier detection
  lowerLimit=(1-3*b)*median;
  upperLimit=(1+3*b)*median;
  for(srcCount=0;srcCount<srcLen;srcCount++)
	{	
    if(*pSrc<lowerLimit || *pSrc>upperLimit)
		{
      *pSrc++=median;
    }
		else{
			pSrc++;
		}
	}
}
