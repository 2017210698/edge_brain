/****************************************************************************
 * Copyright (C) 2017-2018 PI2STAR                                          *
 ****************************************************************************/

/**
 * @file edge_brain.h
 * @author Winfred SU
 * @date 28 Nov 2018
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

/**
 * Preprocessing functions
 */

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

#include"arm_math.h"

void eb_mean_filtering_f32(
  float32_t * pSrc,
  float32_t * pDst,
	float32_t * pBuffer,
  uint32_t blockSize,
  uint32_t winSize);


/**
* End of preprocessing functions
*/


/**
 * outlier detection functions
 */

/**
 * @brief Float32 outlier detection functions.
 * @param[in]   *pSrc points to the input buffer
 * @param[out]  *pDst points to the output buffer
 * @param[in]   srcLen the size of the input signal
 * @param[in]   dstLen the size of the output signal
 * @return none.
 * @note This is only an example to show the doc fomat and 
         project organization. A more efficient approach 
         should be implemented. 
*/

void eb_outlier_detection_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t srcLen,
	float32_t b
);


/**
* End of outlier detection functions
*/


/**
* Feature extraction functions
*/

/**
 * @brief Float32 harmonic frequency extraction
 * @param[in]   *pSrc points to the input buffer
 * @param[out]  *pDst points to the output buffer
 * @param[in]   f_0 the fundermental frequency
 * @param[in]   half_band the frequency bandwidth
 * @param[in]   dst_size the max order of the harmonic frequency, include 0.5X and 1X frequency
*/
// void eb_harmonic_freq_f32(
//   float32_t * pSrc,
//   float32_t * pDst,
//   float32_t f_0,
//   float32_t half_band,
//   uint8_t dst_size);
/**
 * @brief Float32 envolop spectrum
 * @param[in]   *pSrc points to the input buffer
 * @param[out]  *pDst points to the output buffer
 * @param[in]   src_size the size of the input signal
 * @param[in]   fft_size the size of FFT transform points
*/
// void eb_envolop_spectrum_f32(
//   float32_t * pSrc,
//   float32_t * pDst,
//   uint8_t src_size,
//   uint8_t fft_size);


/**
 * @brief Float32 Autocorrelation extraction method
 * @param[in]   *pSrc points to the input buffer
 * @param[out]  *pitch points to the output fundamental frequency
 * @param[in]   lmin lmax the range of fundamental frequency extraction
 * @param[in]   samplingRate 
 * @param[in]   frameLen the size of one frame data
*/
void eb_ACF_f32(
  float32_t * pSrc,
  uint8_t * pitch,
	float32_t * invBuffer,
	float32_t * pDstBuffer,
  uint8_t lmin,
  uint8_t lmax,
  uint32_t samplingRate,
  uint32_t srcLen);


/**
 * End of Feature extraction functions
 */
