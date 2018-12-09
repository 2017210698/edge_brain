#include"arm_math.h"
#include"arm_const_structs.h"

#define TEST_LENGTH_SAMPLE 2048


/* -------------------------------------------------------------------
* External Input and Output buffer Declarations for FFT Example
* ------------------------------------------------------------------- */
extern float32_t testInput_f32_10khz[TEST_LENGTH_SAMPLES];
static float32_t testOutput[TEST_LENGTH_SAMPLES/2];

uint32_t fftSize = 1024;
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;





