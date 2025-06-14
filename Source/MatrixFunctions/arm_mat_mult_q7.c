/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mat_mult_q7.c
 * Description:  Q15 matrix multiplication
 *
 * $Date:        23 April 2021
 *
 * $Revision:    V1.9.0
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

#include "dsp/matrix_functions.h"

/**
  @ingroup groupMatrix
 */

/**
  @addtogroup MatrixMult
  @{
 */

/**
  @brief         Q7 matrix multiplication.
  @param[in]     pSrcA      points to the first input matrix structure
  @param[in]     pSrcB      points to the second input matrix structure
  @param[out]    pDst       points to output matrix structure
  @param[in]     pState     points to the array for storing intermediate results
  @return        execution status
                   - \ref ARM_MATH_SUCCESS       : Operation successful
                   - \ref ARM_MATH_SIZE_MISMATCH : Matrix size check failed

  @par           Scaling and Overflow Behavior (except Neon version)
                   The function is implemented using an internal 32-bit accumulator. The inputs to the
                   multiplications are in 1.7 format and multiplications yield a 2.14 result.
                   The 2.14 intermediate results are accumulated in a 32-bit accumulator in 18.14 format.
                   The 18.14 result is then truncated to 18.7 format by discarding the low 7 bits
                   and then saturated to 1.7 format.
  @par           Neon version
                   The Neon version is currently using a 16-bit accumulator. As consequence, it should
                   not be used to multiply too big matrixes or you'll get saturation issues.
                   If you try to scale down the data to avoid the saturations, you may lose too
                   much accuracy. The Neon implementation is not (currently) made for big matrixes.

                            
  @par
                   Refer to \ref arm_mat_mult_fast_q15() for a faster but less precise version of this function.
 
  @par             pState
                   pState will contain the transpose of pSrcB
 */
#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)
__STATIC_FORCEINLINE arm_status arm_mat_mult_q7_2x2_mve(
    const arm_matrix_instance_q7 * pSrcA,
    const arm_matrix_instance_q7 * pSrcB,
    arm_matrix_instance_q7 * pDst)
{
    const uint32_t MATRIX_DIM = 2;
    q7_t const *pInB = (q7_t const *)pSrcB->pData;  /* input data matrix pointer B */
    q7_t       *pInA = pSrcA->pData;  /* input data matrix pointer A */
    q7_t       *pOut = pDst->pData;   /* output data matrix pointer */
    uint8x16_t vecColBOffs;
    q7_t       *pInA0 = pInA;
    q7_t       *pInA1 = pInA0 + MATRIX_DIM;
    q31_t       acc0, acc1;
    q7x16_t    vecB, vecA0, vecA1;
    mve_pred16_t p0 = vctp8q(MATRIX_DIM);

    vecColBOffs = vidupq_u8((uint32_t)0, 2); /* MATRIX_DIM */

    pInB = pSrcB->pData;

    vecB = vldrbq_gather_offset_z(pInB, vecColBOffs, p0);

    vecA0 = vldrbq_s8(pInA0);
    vecA1 = vldrbq_s8(pInA1);

    acc0 = vmladavq_s8(vecA0, vecB);
    acc1 = vmladavq_s8(vecA1, vecB);

    pOut[0 * MATRIX_DIM] = (q7_t) __SSAT(acc0 >> 7, 8);
    pOut[1 * MATRIX_DIM] = (q7_t) __SSAT(acc1 >> 7, 8);
    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrbq_gather_offset_z(pInB, vecColBOffs, p0);

    acc0 = vmladavq_s8(vecA0, vecB);
    acc1 = vmladavq_s8(vecA1, vecB);

    pOut[0 * MATRIX_DIM] = (q7_t) __SSAT(acc0 >> 7, 8);
    pOut[1 * MATRIX_DIM] = (q7_t) __SSAT(acc1 >> 7, 8);
    /*
     * Return to application
     */
    return (ARM_MATH_SUCCESS);
}


__STATIC_FORCEINLINE arm_status arm_mat_mult_q7_3x3_mve(
    const arm_matrix_instance_q7 * pSrcA,
    const arm_matrix_instance_q7 * pSrcB,
    arm_matrix_instance_q7 * pDst)
{
    const uint8_t  MATRIX_DIM = 3;
    q7_t const     *pInB = (q7_t const *)pSrcB->pData;  /* input data matrix pointer B */
    q7_t           *pInA = pSrcA->pData;  /* input data matrix pointer A */
    q7_t           *pOut = pDst->pData;   /* output data matrix pointer */
    uint8x16_t     vecColBOffs;
    q7_t           *pInA0 = pInA;
    q7_t           *pInA1 = pInA0 + MATRIX_DIM;
    q7_t           *pInA2 = pInA1 + MATRIX_DIM;
    q31_t           acc0, acc1, acc2;
    q7x16_t        vecB, vecA0, vecA1, vecA2;
    mve_pred16_t    p0 = vctp8q(MATRIX_DIM);

    vecColBOffs = vidupq_u8((uint32_t)0, 1);
    vecColBOffs = vecColBOffs * MATRIX_DIM;

    pInB = pSrcB->pData;

    vecB = vldrbq_gather_offset_z(pInB, vecColBOffs, p0);

    vecA0 = vldrbq_s8(pInA0);
    vecA1 = vldrbq_s8(pInA1);
    vecA2 = vldrbq_s8(pInA2);

    acc0 = vmladavq_s8(vecA0, vecB);
    acc1 = vmladavq_s8(vecA1, vecB);
    acc2 = vmladavq_s8(vecA2, vecB);

    pOut[0 * MATRIX_DIM] = (q7_t) __SSAT(acc0 >> 7, 8);
    pOut[1 * MATRIX_DIM] = (q7_t) __SSAT(acc1 >> 7, 8);
    pOut[2 * MATRIX_DIM] = (q7_t) __SSAT(acc2 >> 7, 8);
    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrbq_gather_offset_z(pInB, vecColBOffs, p0);

    acc0 = vmladavq_s8(vecA0, vecB);
    acc1 = vmladavq_s8(vecA1, vecB);
    acc2 = vmladavq_s8(vecA2, vecB);

    pOut[0 * MATRIX_DIM] = (q7_t) __SSAT(acc0 >> 7, 8);
    pOut[1 * MATRIX_DIM] = (q7_t) __SSAT(acc1 >> 7, 8);
    pOut[2 * MATRIX_DIM] = (q7_t) __SSAT(acc2 >> 7, 8);
    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrbq_gather_offset_z(pInB, vecColBOffs, p0);

    acc0 = vmladavq_s8(vecA0, vecB);
    acc1 = vmladavq_s8(vecA1, vecB);
    acc2 = vmladavq_s8(vecA2, vecB);

    pOut[0 * MATRIX_DIM] = (q7_t) __SSAT(acc0 >> 7, 8);
    pOut[1 * MATRIX_DIM] = (q7_t) __SSAT(acc1 >> 7, 8);
    pOut[2 * MATRIX_DIM] = (q7_t) __SSAT(acc2 >> 7, 8);
    /*
     * Return to application
     */
    return (ARM_MATH_SUCCESS);
}


__STATIC_FORCEINLINE arm_status arm_mat_mult_q7_4x4_mve(
    const arm_matrix_instance_q7 * pSrcA,
    const arm_matrix_instance_q7 * pSrcB,
    arm_matrix_instance_q7 * pDst)
{
    const uint32_t MATRIX_DIM = 4;
    q7_t const *pInB = (q7_t const *)pSrcB->pData;  /* input data matrix pointer B */
    q7_t       *pInA = pSrcA->pData;  /* input data matrix pointer A */
    q7_t       *pOut = pDst->pData;   /* output data matrix pointer */
    uint8x16_t vecColBOffs;
    q7_t       *pInA0 = pInA;
    q7_t       *pInA1 = pInA0 + MATRIX_DIM;
    q7_t       *pInA2 = pInA1 + MATRIX_DIM;
    q7_t       *pInA3 = pInA2 + MATRIX_DIM;
    q31_t       acc0, acc1, acc2, acc3;
    q7x16_t    vecB, vecA0, vecA1, vecA2, vecA3;
    mve_pred16_t p0 = vctp8q(MATRIX_DIM);

    vecColBOffs = vidupq_u8((uint32_t)0, 4);

    pInB = pSrcB->pData;

    vecB = vldrbq_gather_offset_z(pInB, vecColBOffs, p0);

    vecA0 = vldrbq_s8(pInA0);
    vecA1 = vldrbq_s8(pInA1);
    vecA2 = vldrbq_s8(pInA2);
    vecA3 = vldrbq_s8(pInA3);

    acc0 = vmladavq_s8(vecA0, vecB);
    acc1 = vmladavq_s8(vecA1, vecB);
    acc2 = vmladavq_s8(vecA2, vecB);
    acc3 = vmladavq_s8(vecA3, vecB);

    pOut[0 * MATRIX_DIM] = (q7_t) __SSAT(acc0 >> 7, 8);
    pOut[1 * MATRIX_DIM] = (q7_t) __SSAT(acc1 >> 7, 8);
    pOut[2 * MATRIX_DIM] = (q7_t) __SSAT(acc2 >> 7, 8);
    pOut[3 * MATRIX_DIM] = (q7_t) __SSAT(acc3 >> 7, 8);
    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrbq_gather_offset_z(pInB, vecColBOffs, p0);

    acc0 = vmladavq_s8(vecA0, vecB);
    acc1 = vmladavq_s8(vecA1, vecB);
    acc2 = vmladavq_s8(vecA2, vecB);
    acc3 = vmladavq_s8(vecA3, vecB);

    pOut[0 * MATRIX_DIM] = (q7_t) __SSAT(acc0 >> 7, 8);
    pOut[1 * MATRIX_DIM] = (q7_t) __SSAT(acc1 >> 7, 8);
    pOut[2 * MATRIX_DIM] = (q7_t) __SSAT(acc2 >> 7, 8);
    pOut[3 * MATRIX_DIM] = (q7_t) __SSAT(acc3 >> 7, 8);
    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrbq_gather_offset_z(pInB, vecColBOffs, p0);

    acc0 = vmladavq_s8(vecA0, vecB);
    acc1 = vmladavq_s8(vecA1, vecB);
    acc2 = vmladavq_s8(vecA2, vecB);
    acc3 = vmladavq_s8(vecA3, vecB);

    pOut[0 * MATRIX_DIM] = (q7_t) __SSAT(acc0 >> 7, 8);
    pOut[1 * MATRIX_DIM] = (q7_t) __SSAT(acc1 >> 7, 8);
    pOut[2 * MATRIX_DIM] = (q7_t) __SSAT(acc2 >> 7, 8);
    pOut[3 * MATRIX_DIM] = (q7_t) __SSAT(acc3 >> 7, 8);
    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrbq_gather_offset_z(pInB, vecColBOffs, p0);

    acc0 = vmladavq_s8(vecA0, vecB);
    acc1 = vmladavq_s8(vecA1, vecB);
    acc2 = vmladavq_s8(vecA2, vecB);
    acc3 = vmladavq_s8(vecA3, vecB);

    pOut[0 * MATRIX_DIM] = (q7_t) __SSAT(acc0 >> 7, 8);
    pOut[1 * MATRIX_DIM] = (q7_t) __SSAT(acc1 >> 7, 8);
    pOut[2 * MATRIX_DIM] = (q7_t) __SSAT(acc2 >> 7, 8);
    pOut[3 * MATRIX_DIM] = (q7_t) __SSAT(acc3 >> 7, 8);
    /*
     * Return to application
     */
    return (ARM_MATH_SUCCESS);
}

ARM_DSP_ATTRIBUTE arm_status arm_mat_mult_q7(
    const arm_matrix_instance_q7 * pSrcA,
    const arm_matrix_instance_q7 * pSrcB,
    arm_matrix_instance_q7 * pDst,
    q7_t * pState)
{
    q7_t    *pInA = pSrcA->pData;  /* input data matrix pointer A of Q7 type */
    q7_t    *pInB = pSrcB->pData;  /* input data matrix pointer B of Q7 type */
    q7_t    *pInA2;
    q7_t    *pInB2;
    q7_t    *px;               /* Temporary output data matrix pointer */
    q7_t    *px2;              /* Temporary output data matrix pointer */
    uint32_t  numRowsA = pSrcA->numRows;    /* number of rows of input matrix A    */
    uint32_t  numColsB = pSrcB->numCols;    /* number of columns of input matrix B */
    uint32_t  numColsA = pSrcA->numCols;    /* number of columns of input matrix A */
    uint32_t  numRowsB = pSrcB->numRows;    /* number of rows of input matrix A    */
    uint32_t  col, i = 0u, j, row = numRowsB;   /* loop counters */
    q7_t    *pSrcBT = pState;   /* input data matrix pointer for transpose */
    uint32_t  blkCnt;           /* loop counters */
    arm_status status;                            /* status of matrix multiplication */
    arm_matrix_instance_q7 BT;


   #ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrcA->numCols != pSrcB->numRows) ||
      (pSrcA->numRows != pDst->numRows)  ||
      (pSrcB->numCols != pDst->numCols)    )
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef ARM_MATH_MATRIX_CHECK */
  {
    /* small squared matrix specialized routines */
    if(numRowsA == numColsB && numColsB == numColsA) {
        if(numRowsA == 2)
            return arm_mat_mult_q7_2x2_mve(pSrcA, pSrcB, pDst);
        else if(numRowsA == 3)
            return arm_mat_mult_q7_3x3_mve(pSrcA, pSrcB, pDst);
        else if (numRowsA == 4)
            return arm_mat_mult_q7_4x4_mve(pSrcA, pSrcB, pDst);
    }
    /*
     * Matrix transpose
     */

    BT.numRows = numColsB;
    BT.numCols = numRowsB;
    BT.pData = pSrcBT;

    arm_mat_trans_q7(pSrcB, &BT);

    /*
     * Reset the variables for the usage in the following multiplication process
     */
    i = 0;
    row = numRowsA >> 1;
    px = pDst->pData;
    px2 = px + numColsB;

    /*
     * The following loop performs the dot-product of each row in pSrcA with each column in pSrcB
     */

    /*
     * row loop
     */
    while (row > 0u)
    {
        /*
         * For every row wise process, the column loop counter is to be initiated
         */
        col = numColsB >> 1;
        /*
         * For every row wise process, the pIn2 pointer is set
         * to the starting address of the transposed pSrcB data
         */
        pInB = pSrcBT;
        pInB2 = pInB + numRowsB;
        j = 0;

        /*
         * column loop
         */
        while (col > 0u)
        {
            q7_t const     *pSrcAVec, *pSrcBVec, *pSrcA2Vec, *pSrcB2Vec;
            q7x16_t        vecA, vecA2, vecB, vecB2;
            q31_t           acc0, acc1, acc2, acc3;

            /*
             * Initiate the pointer pIn1 to point to the starting address of the column being processed
             */
            pInA = pSrcA->pData + i;
            pInA2 = pInA + numColsA;
            pInB = pSrcBT + j;
            pInB2 = pInB + numRowsB;

            pSrcAVec = (q7_t const *) pInA;
            pSrcA2Vec = (q7_t const *)pInA2;
            pSrcBVec = (q7_t const *) pInB;
            pSrcB2Vec = (q7_t const *)pInB2;

            acc0 = 0L;
            acc1 = 0L;
            acc2 = 0L;
            acc3 = 0L;

            vecA = vld1q(pSrcAVec);  
            pSrcAVec += 16;

            blkCnt = numColsA >> 4;
            while (blkCnt > 0U)
            {
                vecB = vld1q(pSrcBVec);  
                pSrcBVec += 16;
                acc0 = vmladavaq_s8(acc0, vecA, vecB);
                vecA2 = vld1q(pSrcA2Vec);  
                pSrcA2Vec += 16;
                acc1 = vmladavaq_s8(acc1, vecA2, vecB);
                vecB2 = vld1q(pSrcB2Vec);  
                pSrcB2Vec += 16;
                acc2 = vmladavaq_s8(acc2, vecA, vecB2);
                vecA = vld1q(pSrcAVec);  
                pSrcAVec += 16;
                acc3 = vmladavaq_s8(acc3, vecA2, vecB2);

                blkCnt--;
            }
            /*
             * tail
             * (will be merged thru tail predication)
             */
            blkCnt = numColsA & 0xF;
            if (blkCnt > 0U)
            {
                mve_pred16_t p0 = vctp8q(blkCnt);
                vecB = vld1q(pSrcBVec);
                acc0 = vmladavaq_p_s8(acc0, vecA, vecB, p0);
                vecA2 = vld1q(pSrcA2Vec);
                acc1 = vmladavaq_p_s8(acc1, vecA2, vecB, p0);
                vecB2 = vld1q(pSrcB2Vec);
                acc2 = vmladavaq_p_s8(acc2, vecA, vecB2, p0);
                vecA = vld1q(pSrcAVec);
                acc3 = vmladavaq_p_s8(acc3, vecA2, vecB2, p0);
            }

            *px++ = (q7_t) __SSAT(acc0 >> 7, 8);
            *px++ = (q7_t) __SSAT(acc2 >> 7, 8);
            *px2++ = (q7_t) __SSAT(acc1 >> 7, 8);
            *px2++ = (q7_t) __SSAT(acc3 >> 7, 8);
            j += numRowsB * 2;
            /*
             * Decrement the column loop counter
             */
            col--;

        }

        i = i + numColsA * 2;
        px = px2 + (numColsB & 1u);
        px2 = px + numColsB;
        /*
         * Decrement the row loop counter
         */
        row--;
    }

    /*
     * Compute remaining row and/or column below
     */

    if (numColsB & 1u)
    {
        row = numRowsA & (~0x1);    //avoid redundant computation
        px = pDst->pData + numColsB - 1;
        i = 0;

        /*
         * row loop
         */
        while (row > 0)
        {
            q7_t const   *pSrcAVec, *pSrcBVec;
            q7x16_t       vecA, vecB;
            q63_t           acc0;

            /*
             * point to last column in matrix B
             */
            pInB = pSrcBT + numRowsB * (numColsB - 1);
            pInA = pSrcA->pData + i;

            pSrcAVec = (q7_t const *) pInA;
            pSrcBVec = (q7_t const *) pInB;

            acc0 = 0LL;
            blkCnt = (numColsA) >> 4;
            while (blkCnt > 0U)
            {
                vecA = vld1q(pSrcAVec);  
                pSrcAVec += 16;
                vecB = vld1q(pSrcBVec);  
                pSrcBVec += 16;
                acc0 = vmladavaq_s8(acc0, vecA, vecB);

                blkCnt--;
            }
            /*
             * tail
             * (will be merged thru tail predication)
             */
            blkCnt = numColsA & 0xF;
            if (blkCnt > 0U)
            {
                mve_pred16_t p0 = vctp8q(blkCnt);
                vecA = vld1q(pSrcAVec);
                vecB = vld1q(pSrcBVec);
                acc0 = vmladavaq_p_s8(acc0, vecA, vecB, p0);
            }

            *px = (q7_t) __SSAT(acc0 >> 7, 8);

            px += numColsB;

            i += numColsA;
            /*
             * Decrement the row loop counter
             */
            row--;
        }
    }

    if (numRowsA & 1u)
    {
        col = numColsB;
        i = 0u;
        /*
         * point to last row in output matrix
         */
        px = pDst->pData + (numColsB) * (numRowsA - 1);
        /*
         * col loop
         */
        while (col > 0)
        {
            q7_t const    *pSrcAVec, *pSrcBVec;
            q7x16_t       vecA, vecB;
            q63_t           acc0;

            /*
             * point to last row in matrix A
             */
            pInA = pSrcA->pData + (numRowsA - 1) * numColsA;
            pInB = pSrcBT + i;

            /*
             * Set the variable sum, that acts as accumulator, to zero
             */
            pSrcAVec = (q7_t const *) pInA;
            pSrcBVec = (q7_t const *) pInB;
            acc0 = 0LL;

            blkCnt = (numColsA) >> 4;
            while (blkCnt > 0U)
            {
                vecA = vld1q(pSrcAVec); 
                pSrcAVec += 16;
                vecB = vld1q(pSrcBVec); 
                pSrcBVec += 16;
                acc0 = vmladavaq_s8(acc0, vecA, vecB);

                blkCnt--;
            }
            /*
             * tail
             * (will be merged thru tail predication)
             */
            blkCnt = numColsA & 0xF;
            if (blkCnt > 0U)
            {
                mve_pred16_t p0 = vctp8q(blkCnt);
                vecA = vld1q(pSrcAVec);
                vecB = vld1q(pSrcBVec);
                acc0 = vmladavaq_p_s8(acc0, vecA, vecB, p0);
            }

            *px++ = (q7_t) __SSAT(acc0 >> 7, 8);

            i += numColsA;

            /*
             * Decrement the col loop counter
             */
            col--;
        }
    }
    /*
     * Return to application
     */
     status = ARM_MATH_SUCCESS;
    }
    return(status);
}
#else

#if defined(ARM_MATH_NEON) 

/**
 * @brief Q7 matrix multiplication
 * @param[in]       *pSrcA points to the first input matrix structure
 * @param[in]       *pSrcB points to the second input matrix structure
 * @param[out]      *pDst points to output matrix structure
 * @param[in]       *pState points to the array for storing intermediate results (Unused in some versions)
 * @return          The function returns either
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
 */

#define LANE 16
#define DTYPE q7_t
#define HEADERTYPE DTYPE
#define VEC int8x16_t
#define VECACC struct { \
    int32x4_t val[4];   \
}

#define CLEAR_ACC(tmp)\
  tmp.val[0] = vdupq_n_s32(0); \
  tmp.val[1] = vdupq_n_s32(0); \
  tmp.val[2] = vdupq_n_s32(0); \
  tmp.val[3] = vdupq_n_s32(0);


#define TMPMAC \
int16x8_t tmp;

#define TMPLD       \
  int8x16_t tmp1;   \
  int16x8x2_t tmp2; 

#define TMPST                \
  int16x4_t tlow;            \
  int16x4_t thigh;           \
  int8x8_t  htmplo,htmphigh;


#define SCALARACC int32_t 
#define SCALAR_LOAD_AND_WIDEN(DST,PTR) DST = (SCALARACC)(*(PTR))
#define SCALAR_STORE_AND_NARROW(PTR,VAL) *(PTR) = (q7_t) __SSAT((VAL) >> 7, 8)
#define SCALAR_MAC_N(ACC,VEC,SCALAR) ACC += (SCALARACC)(VEC) * (SCALARACC)(SCALAR)

#define VLOAD(DST,PTR) DST = vld1q_s8((PTR))
#define VSTORE(PTR,VAL) vst1q_s8((PTR),(VAL))

#define VLOAD_ACC(DST,PTR)         \
  DST.val[0] = vld1q_s32((PTR)+4*0); \
  DST.val[1] = vld1q_s32((PTR)+4*1); \
  DST.val[2] = vld1q_s32((PTR)+4*2); \
  DST.val[3] = vld1q_s32((PTR)+4*3);

#define VSTORE_ACC(PTR,VAL)        \
  vst1q_s32((PTR)+4*0,(VAL).val[0]); \
  vst1q_s32((PTR)+4*1,(VAL).val[1]); \
  vst1q_s32((PTR)+4*2,(VAL).val[2]); \
  vst1q_s32((PTR)+4*3,(VAL).val[3]);

#define VLOAD_AND_WIDEN(DST,PTR)                       \
    tmp1 = vld1q_s8((PTR));                            \
    tmp2.val[0] = vmovl_s8(vget_low_s8(tmp1));         \
    tmp2.val[1] = vmovl_s8(vget_high_s8(tmp1));        \
    DST.val[0] = vmovl_s16(vget_low_s16(tmp2.val[0]));  \
    DST.val[1] = vmovl_s16(vget_high_s16(tmp2.val[0])); \
    DST.val[2] = vmovl_s16(vget_low_s16(tmp2.val[1]));  \
    DST.val[3] = vmovl_s16(vget_high_s16(tmp2.val[1]));

#define VSTORE_AND_NARROW(PTR,VAL)                      \
    tlow = vqshrn_n_s32(VAL.val[0],7);                  \
    thigh = vqshrn_n_s32(VAL.val[1],7);                 \
    htmplo = vqmovn_s16(vcombine_s16(tlow,thigh)); \
    tlow = vqshrn_n_s32(VAL.val[2],7);                  \
    thigh = vqshrn_n_s32(VAL.val[3],7);                 \
    htmphigh = vqmovn_s16(vcombine_s16(tlow,thigh)); \
    vst1q_s8(PTR,vcombine_s8(htmplo,htmphigh));

    #define VMAC_N(ACC,VEC,SCALAR)                                    \
    tmp = vmull_s8(vget_low_s8(VEC),vdup_n_s8(SCALAR));               \
    ACC.val[0] = vaddq_s32(ACC.val[0],vmovl_s16(vget_low_s16(tmp)));  \
    ACC.val[1] = vaddq_s32(ACC.val[1],vmovl_s16(vget_high_s16(tmp))); \
    tmp = vmull_s8(vget_high_s8(VEC),vdup_n_s8(SCALAR));              \
    ACC.val[2] = vaddq_s32(ACC.val[2],vmovl_s16(vget_low_s16(tmp)));  \
    ACC.val[3] = vaddq_s32(ACC.val[3],vmovl_s16(vget_high_s16(tmp)));

#define MATTYPE arm_matrix_instance_q7
#define EXT(A) A##_q7
#define HAS_TEMP_BUFFER
#define USE_TMP_REGISTER

#define FUNCNAME arm_mat_mult_q7


#include "_arm_mat_mult_neon.c"


#else
ARM_DSP_ATTRIBUTE arm_status arm_mat_mult_q7(const arm_matrix_instance_q7 *pSrcA, 
    const arm_matrix_instance_q7 *pSrcB,
     arm_matrix_instance_q7 *pDst, 
     q7_t *pState)
{
    q31_t sum; /* accumulator */
    q7_t *pIn1 = pSrcA->pData;                    /* input data matrix pointer A */
    q7_t *pIn2 = pSrcB->pData;                    /* input data matrix pointer B */
    q7_t *pInA = pSrcA->pData;                    /* input data matrix pointer A of Q7 type */
    q7_t *pInB = pSrcB->pData;                    /* input data matrix pointer B of Q7 type */
    q7_t *pOut = pDst->pData;                     /* output data matrix pointer */
    q7_t *px;                                     /* Temporary output data matrix pointer */
    uint16_t numColsB = pSrcB->numCols;           /* number of columns of input matrix B */
    uint16_t numColsA = pSrcA->numCols;           /* number of columns of input matrix A */
    uint16_t numRowsA = pSrcA->numRows;           /* number of rows of input matrix A    */
    uint16_t col, i = 0U, row = numRowsA, colCnt; /* loop counters */
    arm_status status;                            /* status of matrix multiplication */

    (void)pState;

#ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrcA->numCols != pSrcB->numRows) ||
      (pSrcA->numRows != pDst->numRows)  ||
      (pSrcB->numCols != pDst->numCols)    )
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef ARM_MATH_MATRIX_CHECK */

    {
        /* The following loop performs the dot-product of each row in pSrcA with each column in pSrcB */
        /* row loop */
        do {
            /* Output pointer is set to starting address of the row being processed */
            px = pOut + i;

            /* For every row wise process, the column loop counter is to be initiated */
            col = numColsB;

            /* For every row wise process, the pIn2 pointer is set
             ** to the starting address of the pSrcB data */
            pIn2 = pSrcB->pData;

            /* column loop */
            do {
                /* Set the variable sum, that acts as accumulator, to zero */
                sum = 0;

                /* Initiate the pointer pIn1 to point to the starting address of pSrcA */
                pIn1 = pInA;

                /* Matrix A columns number of MAC operations are to be performed */
                colCnt = numColsA;

                /* matrix multiplication */
                while (colCnt > 0U) {
                    /* c(m,n) = a(1,1)*b(1,1) + a(1,2) * b(2,1) + .... + a(m,p)*b(p,n) */
                    /* Perform the multiply-accumulates */
                    sum += (q31_t)*pIn1++ * *pIn2;
                    pIn2 += numColsB;

                    /* Decrement the loop counter */
                    colCnt--;
                }

                /* Convert the result from 34.30 to 1.15 format and store the saturated value in destination buffer */
                /* Saturate and store the result in the destination buffer */
                *px++ = (q7_t)__SSAT((sum >> 7), 8);

                /* Decrement the column loop counter */
                col--;

                /* Update the pointer pIn2 to point to the  starting address of the next column */
                pIn2 = pInB + (numColsB - col);

            } while (col > 0U);

            /* Update the pointer pSrcA to point to the  starting address of the next row */
            i = i + numColsB;
            pInA = pInA + numColsA;

            /* Decrement the row loop counter */
            row--;

        } while (row > 0U);

        /* set status as ARM_MATH_SUCCESS */
        status = ARM_MATH_SUCCESS;
    }

    /* Return to application */
    return (status);
}
#endif /* #if defined(ARM_MATH_NEON) */
#endif /* defined(ARM_MATH_MVEI) */

/**
  @} end of MatrixMult group
 */
