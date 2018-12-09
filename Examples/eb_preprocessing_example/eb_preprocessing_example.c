/****************************************************************************
 * Copyright (C) 2017-2018 PI2STAR                                          *
 ****************************************************************************/

/**
 * @file eb_preprocessing_example.c
 * @author Winfred SU
 * @date 28 Nov 2018
 * @brief Examples of preprocessing functions
 *
 * Demonstrates the use of the preprocessing functions. 
 */

#include "arm_math.h"
#include "edge_brain.h"

int main(void)
{
  
	float32_t b=1.4286f;	
	// ------------------------------------------------------------------
  /* test input data */
  float32_t testSrc[5] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
  /* test output buffer */
  float32_t testDst[6] = {0};
	/* window matrix buffer */
	float32_t pBuffer[2]={0};
	/* source signal Size */
	uint32_t srcLen=5;
	/* window size */
	uint32_t winSize=2;
	
	/* outlier buffer */
	float32_t outlierDst[6]={0};
	/* the size of the signal after filtering */ 
	uint32_t filterSize=srcLen+winSize-1;
	
	/* ACF  invBuffer */ 
	float32_t invBuffer[6];
	float32_t pDstBuffer[11]; // the size of correlation matrix: 2*6-1
	uint8_t pitch[1];
	uint8_t lmin=10u;
	uint8_t lmax=200u;
	uint16_t samplingRate=20000;
			
	//--------------------------------------------------------------------
  /* mean filtering, input size = 5, window = 2 */
  eb_mean_filtering_f32(testSrc, testDst, pBuffer,srcLen, winSize);
	/* the length of the signal after mean filtering */
	
	/* outlier detection, input size =5 */
  eb_outlier_detection_f32(testDst,outlierDst,filterSize,b);
			
	/* ACF input signal size=filterSize[0] */
	eb_ACF_f32(outlierDst,pitch,invBuffer,pDstBuffer,lmin,lmax,samplingRate,srcLen);
		
  while(1);
}

