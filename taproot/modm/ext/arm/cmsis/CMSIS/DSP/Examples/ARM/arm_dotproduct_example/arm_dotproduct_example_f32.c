/* ----------------------------------------------------------------------
* Copyright (C) 2010-2012 ARM Limited. All rights reserved.
*
* $Date:         17. January 2013
* $Revision:     V1.4.0
*
* Project:       CMSIS DSP Library
* Title:         arm_dotproduct_example_f32.c
*
* Description:   Example code computing dot product of two vectors.
*
* Target Processor: Cortex-M4/Cortex-M3
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*   - Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   - Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the
*     distribution.
*   - Neither the name of ARM LIMITED nor the names of its contributors
*     may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
 * -------------------------------------------------------------------- */

/**
 * @ingroup groupExamples
 */

/**
 * @defgroup DotproductExample Dot Product Example
 *
 * \par Description:
 * \par
 * Demonstrates the use of the Multiply and Add functions to perform the dot product.
 * The dot product of two vectors is obtained by multiplying corresponding elements
 * and summing the products.

 * \par Algorithm:
 * \par
 * The two input vectors \c A and \c B with length \c n, are multiplied element-by-element
 * and then added to obtain dot product.
 * \par
 * This is denoted by the following equation:
 *         <pre>  dotProduct = A[0] * B[0] + A[1] * B[1] + ... + A[n-1] * B[n-1]</pre>
 *
 * \par Block Diagram:
 * \par
 * \image html dotProduct.gif
 *
 * \par Variables Description:
 * \par
 * \li \c srcA_buf_f32 points to first input vector
 * \li \c srcB_buf_f32 points to second input vector
 * \li \c testOutput   stores dot product of the two input vectors.
 *
 * \par CMSIS DSP Software Library Functions Used:
 * \par
 * - arm_mult_f32()
 * - arm_add_f32()
 *
 * <b> Refer  </b>
 * \link arm_dotproduct_example_f32.c \endlink
 *
 */


/** \example arm_dotproduct_example_f32.c
  */

#include <math.h>
#include "arm_math.h"

#if defined(SEMIHOSTING)
#include <stdio.h>
#endif

/* ----------------------------------------------------------------------
* Defines each of the tests performed
* ------------------------------------------------------------------- */
#define MAX_BLOCKSIZE     32
#define DELTA           (0.000001f)

/* ----------------------------------------------------------------------
* Test input data for Floating point Dot Product example for 32-blockSize
* Generated by the MATLAB randn() function
* ------------------------------------------------------------------- */
/* ----------------------------------------------------------------------
** Test input data of srcA for blockSize 32
** ------------------------------------------------------------------- */
float32_t srcA_buf_f32[MAX_BLOCKSIZE] =
{
  -0.4325648115282207,  -1.6655843782380970,  0.1253323064748307,
   0.2876764203585489,  -1.1464713506814637,  1.1909154656429988,
   1.1891642016521031,  -0.0376332765933176,  0.3272923614086541,
   0.1746391428209245,  -0.1867085776814394,  0.7257905482933027,
  -0.5883165430141887,   2.1831858181971011, -0.1363958830865957,
   0.1139313135208096,   1.0667682113591888,  0.0592814605236053,
  -0.0956484054836690,  -0.8323494636500225,  0.2944108163926404,
  -1.3361818579378040,   0.7143245518189522,  1.6235620644462707,
  -0.6917757017022868,   0.8579966728282626,  1.2540014216025324,
  -1.5937295764474768,  -1.4409644319010200,  0.5711476236581780,
  -0.3998855777153632,   0.6899973754643451
};

/* ----------------------------------------------------------------------
** Test input data of srcB for blockSize 32
** ------------------------------------------------------------------- */
float32_t srcB_buf_f32[MAX_BLOCKSIZE] =
{
   1.7491401329284098,  0.1325982188803279,   0.3252281811989881,
  -0.7938091410349637,  0.3149236145048914,  -0.5272704888029532,
   0.9322666565031119,  1.1646643544607362,  -2.0456694357357357,
  -0.6443728590041911,  1.7410657940825480,   0.4867684246821860,
   1.0488288293660140,  1.4885752747099299,   1.2705014969484090,
  -1.8561241921210170,  2.1343209047321410,   1.4358467535865909,
  -0.9173023332875400, -1.1060770780029008,   0.8105708062681296,
   0.6985430696369063, -0.4015827425012831,   1.2687512030669628,
  -0.7836083053674872,  0.2132664971465569,   0.7878984786088954,
   0.8966819356782295, -0.1869172943544062,   1.0131816724341454,
   0.2484350696132857,  0.0596083377937976
};

/* Reference dot product output */
float32_t  refDotProdOut = 5.9273644806352142;

/* ----------------------------------------------------------------------
* Declare Global variables
* ------------------------------------------------------------------- */
float32_t multOutput[MAX_BLOCKSIZE];  /* Intermediate output */
float32_t testOutput;  /* Final ouput */

arm_status status;   /* Status of the example */

int32_t main(void)
{
  uint32_t i;       /* Loop counter */
  float32_t diff;     /* Difference between reference and test outputs */

  /* Multiplication of two input buffers */
  arm_mult_f32(srcA_buf_f32, srcB_buf_f32, multOutput, MAX_BLOCKSIZE);

  /* Accumulate the multiplication output values to
     get the dot product of the two inputs */
  for(i=0; i< MAX_BLOCKSIZE; i++)
  {
    arm_add_f32(&testOutput, &multOutput[i], &testOutput, 1);
  }

  /* absolute value of difference between ref and test */
  diff = fabsf(refDotProdOut - testOutput);

  /* Comparison of dot product value with reference */
  status = (diff > DELTA) ? ARM_MATH_TEST_FAILURE : ARM_MATH_SUCCESS;

  if (status != ARM_MATH_SUCCESS)
  {
#if defined (SEMIHOSTING)
    printf("FAILURE\n");
#else
    while (1);                             /* main function does not return */
#endif
  }
  else
  {
#if defined (SEMIHOSTING)
    printf("SUCCESS\n");
#else
    while (1);                             /* main function does not return */
#endif
  }
}

 /** \endlink */
