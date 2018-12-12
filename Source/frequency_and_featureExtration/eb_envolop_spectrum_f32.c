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
//	uint8_t ifftFlag=0; // rfft if flag is 0, rifft if flag is 1
//	arm_rfft_fast_instance_f32 S;
//		/* initiate the structure */
//	arm_rfft_fast_init_f32(&S,fftSize);
//	
//	/* 1024 points arm_rfft_fast_f32 */
//	arm_rfft_fast_f32(&S,pSrc,pFftBuffer,ifftFlag);

//	if(srcLen%2!=0)
//	{
//		srcLen--;
//	}

//	
//	arm_cmplx_mag_f32(pSrc,pSrc_fft,1024);
//	

	uint16_t i; 
	arm_rfft_fast_instance_f32 S; 
	/* 实数序列FFT长度 */ 
	uint8_t ifftFlag = 0; /* 初始化结构体S中的参数 */ 
	float32_t testInput_f32_10khz[1024];
	float32_t testOutput_f32_10khz[2048];
	float32_t testOutput[1024];
	arm_rfft_fast_init_f32(&S, fftSize);
	
	/* 按照实部，虚部，实部，虚部..... 的顺序存储数据 */ 
	for(i=0; i<1024; i++) 
	{ /* 50Hz正弦波，采样率1KHz */ 
	testInput_f32_10khz[i] = 1.2f*arm_sin_f32(2*3.1415926f*50*i/1000)+1; }
	/* 1024点实序列快速FFT */ 
	arm_rfft_fast_f32(&S, testInput_f32_10khz, testOutput_f32_10khz, ifftFlag);
	arm_cmplx_mag_f32(testOutput_f32_10khz, testOutput, fftSize);
	
	}

