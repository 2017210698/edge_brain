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
  /* test input data */
  float32_t testSrc[5] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
  
  /* test output buffer */
  float32_t testDst[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
  
  /* mean filtering, input size = 5, window = 2 */
  eb_mean_filtering_f32(testSrc, testDst, 5, 2);
	
	
  
  while(1);
}
