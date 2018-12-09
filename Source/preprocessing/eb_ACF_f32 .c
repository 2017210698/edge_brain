/****************************************************************************
 * Copyright (C) 2017-2018 PI2STAR                                          *
 ****************************************************************************/

/**
 * @file eb_ACF_f32.c
 * @author lwg
 * @date 28 Nov 2018
 * @brief Float32 Autocorrelation extraction method
 *
 * Float32 Autocorrelation extraction method using arm_mean_f32.
 */

#include "arm_math.h"
#include "assert.h"
/**
 * @brief Float32 Autocorrelation extraction method.
 * @param[in]   *pSrc points to the input buffer
 * @param[out]  *pitch points to the output fundamental frequency
 * @param[in]   lmin lmax the range of fundamental frequency extraction
 * @param[in]   samplingRate 
 * @param[in]   frameLen the size of one frame data
*/
void eb_ACF_f32(
  float32_t * pSrc,
  float32_t * pitch,
	float32_t * invBuffer,
	float32_t * pDstBuffer,
  uint32_t lmin,
  uint32_t lmax,
  uint32_t samplingRate,
  uint32_t srcLen)
{
	uint32_t srcCount; // loop variable
	float32_t Max;
	uint32_t maxIndex;
	uint32_t pitchIndex; // pitch index in samplingRate
	
	/* compute the invBuffer sig[::-1] */
  for(srcCount=0;srcCount<srcLen;srcCount++)
	{
		invBuffer[srcLen-srcCount+1]=pSrc[srcCount];
	}
	
	/* compute the correlate matrix */
  arm_correlate_f32(pSrc,srcLen,invBuffer,srcLen,pDstBuffer);
		
	/* compute the max of correlate matrix */
	arm_max_f32(pDstBuffer,11,&Max,&maxIndex);
	
	/* compute the pitch index in samplingRate */
	pitchIndex=(maxIndex+1)/2;
	
	/* compute the pitch */
	pitch[0]=samplingRate*pitchIndex/srcLen;
	
	assert(pitch[0]>lmin && pitch[0]<lmax);
	
	
	/**
	if(pitch[0]<lmin || pitch[0] > lmax)
	{
		return (ARM_MATH_ARGUMENT_ERROR);
	}
	*/
}
