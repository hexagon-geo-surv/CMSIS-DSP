/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mfcc_f32.c
 * Description:  MFCC function for the f32 version
 *
 * $Date:        07 September 2021
 * $Revision:    V1.10.0
 *
 * Target Processor: Cortex-M and Cortex-A cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2021 ARM Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */



#include "dsp/transform_functions.h"
#include "dsp/statistics_functions.h"
#include "dsp/basic_math_functions.h"
#include "dsp/complex_math_functions.h"
#include "dsp/fast_math_functions.h"
#include "dsp/matrix_functions.h"

/**
  @ingroup MFCC
 */



/**
  @addtogroup MFCCF32
  @{
 */

/**
  @brief         MFCC F32
  @param[in]    S       points to the mfcc instance structure
  @param[in]     pSrc points to the input samples
  @param[out]     pDst  points to the output MFCC values
  @param[inout]     pTmp  points to a temporary buffer of complex

  @par           Description
                   The number of input samples if the FFT length used
                   when initializing the instance data structure.

                   The source buffer is modified by this function.

 @par   Neon implementation
                 The Neon implementation has a different API.
                 There is an additional temporary buffer pTmp2.
                 The source buffer is  modified.
 @code
        void arm_mfcc_f32(
             const arm_mfcc_instance_f32 * S,
                   float32_t *pSrc,
                   float32_t *pDst,
                   float32_t *pTmp,
                   float32_t *pTmp2
          );
  @endcode

  @par Size of buffers according to the target architecture and datatype:
       They are described on the page \ref transformbuffers "transform buffers".
 */
#if defined(ARM_MATH_NEON)
ARM_DSP_ATTRIBUTE void arm_mfcc_f32(
  const arm_mfcc_instance_f32 * S,
  float32_t *pSrc,
  float32_t *pDst,
  float32_t *pTmp,
  float32_t *pTmp2
  )
#else
ARM_DSP_ATTRIBUTE void arm_mfcc_f32(
  const arm_mfcc_instance_f32 * S,
  float32_t *pSrc,
  float32_t *pDst,
  float32_t *pTmp
  )
#endif
{
  float32_t maxValue;
  uint32_t  index; 
  uint32_t i;
  float32_t result;
  const float32_t *coefs=S->filterCoefs;
  arm_matrix_instance_f32 pDctMat;

  /* Normalize */
  arm_absmax_f32(pSrc,S->fftLen,&maxValue,&index);

  if (maxValue != 0.0f)
  {
     arm_scale_f32(pSrc,1.0f/maxValue,pSrc,S->fftLen);
  }

  /* Multiply by window */
  arm_mult_f32(pSrc,S->windowCoefs,pSrc,S->fftLen);

  /* Compute spectrum magnitude 
  */
#if defined(ARM_MATH_NEON) 
  arm_rfft_fast_f32(&(S->rfft),pSrc,pTmp,pTmp2,0);
  pTmp[1]=0.0f;
#else
#if defined(ARM_MFCC_USE_CFFT)
  /* some HW accelerator for CMSIS-DSP used in some boards
     are only providing acceleration for CFFT.
     With ARM_MFCC_USE_CFFT enabled, CFFT is used and the MFCC
     will be accelerated on those boards.
 
     The default is to use RFFT
  */
  /* Convert from real to complex */
  for(i=0; i < S->fftLen ; i++)
  {
    pTmp[2*i] = pSrc[i];
    pTmp[2*i+1] = 0.0f;
  }
  arm_cfft_f32(&(S->cfft),pTmp,0,1);
#else
  /* Default RFFT based implementation */
  arm_rfft_fast_f32(&(S->rfft),pSrc,pTmp,0);
  pTmp[1]=0.0f;
#endif /* ARM_MFCC_USE_CFFT */
#endif /* ARM_MATH_NEON */
  arm_cmplx_mag_f32(pTmp,pSrc,S->fftLen);
  if (maxValue != 0.0f)
  {
     arm_scale_f32(pSrc,maxValue,pSrc,S->fftLen);
  }

  /* Apply MEL filters */
  for(i=0; i<S->nbMelFilters; i++)
  {
      arm_dot_prod_f32(pSrc+S->filterPos[i],
        coefs,
        S->filterLengths[i],
        &result);

      coefs += S->filterLengths[i];

      pTmp[i] = result;

  }

  /* Compute the log */
  arm_offset_f32(pTmp,1.0e-6f,pTmp,S->nbMelFilters);
  arm_vlog_f32(pTmp,pTmp,S->nbMelFilters);

  /* Multiply with the DCT matrix */

  pDctMat.numRows=S->nbDctOutputs;
  pDctMat.numCols=S->nbMelFilters;
  pDctMat.pData=(float32_t*)S->dctCoefs;

  arm_mat_vec_mult_f32(&pDctMat, pTmp, pDst);
      

}

/**
  @} end of MFCCF32 group
 */
