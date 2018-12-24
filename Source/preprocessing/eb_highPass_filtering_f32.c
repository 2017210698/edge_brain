
/****************************************************************************
 * Copyright (C) 2017-2018 PI2STAR                                          *
 ****************************************************************************/

/**
 * @file eb_highPass_filtering_f32.c
 * @author liwg
 * @date 23 Dec 2018
 * @brief Float32 high-pass filtering
 *
 * 	Float32 high-pass filtering using arm_biquad_casd_inst_f32,
 		arm_biquad_cascade_df1_init_f32,arm_biquad_cascade_df1_f32,
		arm_scale_f32 and arm_sub_f32. 
 */

#include "arm_math.h"

/**
 * @brief Float32 high-pass filtering.
 * @param[in]   *pSrc points to the input buffer.
 * @param[out]  *pDst points to the output buffer.
 * @param[in]		*IIRStateF32 points to intermediate state buffer the size 
								is numTaps + blockSize - 1.
 * @param[in]   srcLen the number of samples in input vector.
 * @param[in]   *IIRCoeffs32LP points to ButterWorth Low-pass Filter 
								coefficients with 80Hz obtained from matlab fdatool buffer.
 * @return none.
 * @note 	Using convolution method to obtain the mean filtering,
					after arm_conv,the length is srcLen+winLen-1, here we 
					only save srcLen numbers.
					Float32 high-pass filtering using arm_biquad_casd_inst_f32,
					arm_biquad_cascade_df1_init_f32,arm_biquad_cascade_df1_f32,
					arm_scale_f32 and arm_sub_f32. 
*/

void eb_highPass_filtering_f32(
	float32_t * pSrc,
	float32_t * pDst,
	float32_t * IIRStateF32,
	float32_t srcLen,
	const float32_t * IIRCoeffs32LP,
	float32_t numStages)
{
	
	float32_t ScaleValue;
	arm_biquad_casd_df1_inst_f32 S;
	arm_biquad_cascade_df1_init_f32(&S,numStages,(float32_t*)IIRCoeffs32LP,(float32_t*)&IIRStateF32[0]); // initiate the structure S
	
	/* IIRfir filtering */
	arm_biquad_cascade_df1_f32(&S,pSrc,pDst,srcLen);
	
	ScaleValue = 0.052219514664161221f * 0.04279801741658381f;
	arm_scale_f32(pDst,ScaleValue,pDst,srcLen);
	arm_sub_f32(pSrc,pDst,pDst,srcLen); // pSrc substraction the signal after low-pass filtering
}
