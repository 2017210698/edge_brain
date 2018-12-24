/****************************************************************************
 * Copyright (C) 2017-2018 PI2STAR                                          *
 ****************************************************************************/

/**
 * @file edge_brain.h
 * @author liwg
 * @date 23 Dec 2018
 * @brief Public header file for edge brain library
 *
 * The library is divided into a number of functions each covering a specific category:
 * - Preprocessing functions
 * - Feature extraction functions
 * - Classification functions
 * 
 * The library has separate functions for operating on 8-bit integers, 16-bit integers,
 * 32-bit integer and 32-bit floating-point values.
 */

#include"arm_math.h"

/**
 * Preprocessing functions
 */

/**
 * @brief Float32 mean filtering function.
 * @param[in]   *pSrc points to the input buffer.
 * @param[out]  *pDst points to the output buffer.
 * @param[in]		*pBuffer points to window matrix buffer used for convolution.
 * @param[in]   srcLen the number of samples in input vector.
 * @param[in]   winSize filter window size.
 * @return none.
 * @note 	Using convolution method to obtain the mean filtering,
					after arm_conv,the length is srcLen+winLen-1, here we 
					only save srcLen numbers.
					Float32 mean filtering using arm_conv_f32 and arm_fill_f32.
*/

void eb_mean_filtering_f32(
  float32_t * pSrc,
  float32_t * pDst,
	float32_t * pBuffer,
  uint32_t srcLen,
  uint32_t winLen);
/**
 * End of mean filtering function.
 */

/**
 * @brief Float32 high-pass filtering function.
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
	float32_t numStages);

/**
 * End of outlier detection function.
 */

/**
 * @brief Float32 outlier detection function.
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
);


/**
* End of outlier detection function.
*/

/**
 * @brief Float32 Autocorrelation extraction function.
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
  uint8_t lmin,
  uint8_t lmax,
  uint32_t samplingRate,
  uint32_t srcLen);

/**
* End of Autocorrelation extraction function.
*/


/**
* End of preprocessing functions
*/

/*--------------------------------------------------------------------------*/

/**
* Feature extraction functions
*/

/**
 * @brief Float32 harmonic frequency extraction function.
 * @param[in]   *pSrc points to the input buffer.
 * @param[out]  *pDst points to the output buffer.
 * @param[in]   *pFftBuffer points to the FFT buffer used for intermediate buffer and FFT buffer.
 * @param[in]   *pMagBuffer points to the Mag buffer used for intermediate buffer and FFT buffer.
 * @param[in]   pitch the base frequency.
 * @param[in]   srcLen the size of input signal.
 * @param[in]   dst_size the max order of the harmonic frequency, include 0.5X and 1X frequency.
 * @param[in]   samplingRate sampling rate.
 * @return none.
 * @note 	Using FFT method to obtain harmonic frequency extraction.
 					Float32 harmonic frequency extraction using arm_mean_f32,arm_fill_f32,arm_sub_f32,
 					arm_rfft_fast_init_f32,arm_rfft_fast_f32,arm_cmplx_mag_f32.
*/

 void eb_harmonic_freq_f32(
  float32_t * pSrc,
  float32_t * pDst,
	float32_t * pFftBuffer,
	float32_t * pMagBuffer,
  uint8_t pitch,
	uint16_t srcLen,
  uint8_t dstSize,
	uint16_t samplingRate);
 
/**
* End of harmonic frequency extraction function.
*/
 
/**
 * @brief Float32 envolop spectrum function.
 * @param[in]   *pSrc points to the input buffer.
 * @param[out]  *pDst points to the output buffer.
 * @param[in]   *pBuffer points to the intermediate buffer used to insert zero to the input signal for arm_cfft_f32.
 * @param[in]   *pTransMatrix points to the intermediate buffer used for the transform matrix of hilbert transform.
 * @param[in]		fftSize the size of FFT transform points
 * @return none.
 * @note Using hilbert transform method to obtain envolop spectrum.
 					Float32 envolop spectrum using arm_cfft_f32,arm_offset_f32,arm_mult_f32 and arm_cmplx_mag_f32.
					Caution: the floating-point complex FFT uses a mixed cardinality algorithm implemented by multiple bases 8 
					and a single base 2 or base 4 algorithm. The algorithm supports lengths [16, 32, 64, ..., 4096] and uses 
					different twiddle factor tables for each length as needed.
					When arm_cfft_f32 is called, you need include the header file arm_const_structs.h.For example:
					arm_cfft_f32(arm_cfft_sR_f32_len64,pSrc,0,1), the above formula is to calculate a 64-point FFT

*/

 void eb_envolop_spectrum_f32(
	float32_t * pSrc,
	float32_t * pDst,
	float32_t * pBuffer,
	float32_t * pTransMatrix,
  uint16_t fftSize);
/**
* End of envolop spectrum function.
*/
 
/**
 * End of Feature extraction functions
*/
