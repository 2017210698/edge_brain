/****************************************************************************
 * Copyright (C) 2017-2018 PI2STAR                                          *
 ****************************************************************************/

/**
 * @file eb_ACF_f32.c
 * @author liwg
 * @date 23 Dec 2018
 * @brief Float32 Autocorrelation extraction method
 *
 * Float32 Autocorrelation extraction method using arm_correlate_f32 and arm_max_f32.
 */

#include "arm_math.h"

/**
 * @brief Float32 Autocorrelation extraction functions.
 * @param[in]   *pSrc points to the input buffer.
 * @param[out]  *pitch points to the output base frequency.
 * @param[in]   *pCorrBuffer points to the correlation matrix buffer with the size of correlation matrix: 2*srcLen-1.
 * @param[in]   lmin the minimum base frequency.
 * @param[in]   lmax the maxmum base frequency. 
 * @param[in]   samplingRate sampling rate
 * @param[in]   srcLen the size of one input signal.
 * @return none.
 * @note  Using autocorrelation extraction method to obtain base frequency. 
          Float32 Autocorrelation extraction using arm_correlate_f32 and arm_max_f32.
*/

void eb_ACF_f32(
  float32_t * pSrc,
  uint8_t * pitch,
	float32_t * pCorrBuffer,
	uint32_t lmin,
  uint32_t lmax,
  uint32_t samplingRate,
  uint32_t srcLen)
{
	float32_t Max;
	uint32_t maxIndex;
	uint16_t bandWidth; // base frequency bandwidth
	lmax=(uint16_t)((float32_t)lmax/samplingRate*srcLen);
	lmin=(uint16_t)((float32_t)lmin/samplingRate*srcLen);
	bandWidth=lmax-lmin+1;
	
	/* compute the correlate matrix */
  arm_correlate_f32(pSrc,srcLen,pSrc,srcLen,pCorrBuffer);
	
	arm_max_f32(&pCorrBuffer[lmin-1],bandWidth,&Max,&maxIndex);
	
	/* compute the pitch in samplingRate */
	lmax=lmin+maxIndex-1;
	pitch[0]=(uint16_t)((float32_t)lmax/srcLen*samplingRate);
}
