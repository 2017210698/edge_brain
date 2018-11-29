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
void eb_mean_filtering_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize,
  uint32_t winSize);

/**
 * End of preprocessing functions
 */
