/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mat_mult_q15.c
 * Description:  Q15 matrix multiplication
 *
 * $Date:        3 Nov 2021
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

#include "dsp/matrix_functions.h"

/**
  @ingroup groupMatrix
 */

/**
  @addtogroup MatrixMult
  @{
 */

/**
  @brief         Q15 matrix multiplication.
  @param[in]     pSrcA      points to the first input matrix structure
  @param[in]     pSrcB      points to the second input matrix structure
  @param[out]    pDst       points to output matrix structure
  @param[in]     pState     points to the array for storing intermediate results
  @return        execution status
                   - \ref ARM_MATH_SUCCESS       : Operation successful
                   - \ref ARM_MATH_SIZE_MISMATCH : Matrix size check failed

  @par           Scaling and Overflow Behavior (except on Neon)
                   The function is implemented using an internal 64-bit accumulator. The inputs to the
                   multiplications are in 1.15 format and multiplications yield a 2.30 result.
                   The 2.30 intermediate results are accumulated in a 64-bit accumulator in 34.30 format.
                   This approach provides 33 guard bits and there is no risk of overflow.
                   The 34.30 result is then truncated to 34.15 format by discarding the low 15 bits
                   and then saturated to 1.15 format.
  @par           Neon version
                   The Neon version is currently using a 32-bit accumulator. As consequence, it should
                   not be used to multiply too big matrixes or you'll get saturation issues.
                   If you try to scale down the data to avoid the saturations, you may lose too
                   much accuracy. The Neon implementation is not (currently) made for big matrixes.
                               
  @par
                   Refer to \ref arm_mat_mult_fast_q15() for a faster but less precise version of this function.
 
  @par             pState
                   pState will contain the transpose of pSrcB
 */
#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)

#define MVE_ASRL_SAT16(acc, shift)          ((sqrshrl_sat48(acc, -(32-shift)) >> 32) & 0xffffffff)

#define MATRIX_DIM2 2
#define MATRIX_DIM3 3
#define MATRIX_DIM4 4

__STATIC_INLINE arm_status arm_mat_mult_q15_2x2_mve(
    const arm_matrix_instance_q15 * pSrcA,
    const arm_matrix_instance_q15 * pSrcB,
    arm_matrix_instance_q15 * pDst)
{
    q15_t       *pInB = pSrcB->pData;  /* input data matrix pointer B */
    q15_t       *pInA = pSrcA->pData;  /* input data matrix pointer A */
    q15_t       *pOut = pDst->pData;   /* output data matrix pointer */
    uint16x8_t  vecColBOffs;
    q15_t       *pInA0 = pInA;
    q15_t       *pInA1 = pInA0 + MATRIX_DIM2;
    q63_t        acc0, acc1;
    q15x8_t     vecB, vecA0, vecA1;
    mve_pred16_t p0 = vctp16q(MATRIX_DIM2);

    vecColBOffs = vidupq_u16((uint32_t)0, 2); /* MATRIX_DIM2 */

    pInB = pSrcB->pData;

    vecB = vldrhq_gather_shifted_offset_z_s16((q15_t const *)pInB, vecColBOffs, p0);

    vecA0 = vldrhq_s16(pInA0);
    vecA1 = vldrhq_s16(pInA1);

    acc0 = vmlaldavq(vecA0, vecB);
    acc1 = vmlaldavq(vecA1, vecB);

    acc0 = asrl(acc0, 15);
    acc1 = asrl(acc1, 15);

    pOut[0 * MATRIX_DIM2] = (q15_t) __SSAT(acc0, 16);
    pOut[1 * MATRIX_DIM2] = (q15_t) __SSAT(acc1, 16);
    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrhq_gather_shifted_offset_z_s16(pInB, vecColBOffs, p0);

    acc0 = vmlaldavq(vecA0, vecB);
    acc1 = vmlaldavq(vecA1, vecB);

    acc0 = asrl(acc0, 15);
    acc1 = asrl(acc1, 15);

    pOut[0 * MATRIX_DIM2] = (q15_t) __SSAT(acc0, 16);
    pOut[1 * MATRIX_DIM2] = (q15_t) __SSAT(acc1, 16);

    /*
     * Return to application
     */
    return (ARM_MATH_SUCCESS);
}



__STATIC_INLINE arm_status arm_mat_mult_q15_3x3_mve(
    const arm_matrix_instance_q15 * pSrcA,
    const arm_matrix_instance_q15 * pSrcB,
    arm_matrix_instance_q15 * pDst)
{
    q15_t       *pInB = pSrcB->pData;  /* input data matrix pointer B */
    q15_t       *pInA = pSrcA->pData;  /* input data matrix pointer A */
    q15_t       *pOut = pDst->pData;   /* output data matrix pointer */
    uint16x8_t vecColBOffs;
    q15_t       *pInA0 = pInA;
    q15_t       *pInA1 = pInA0 + MATRIX_DIM3;
    q15_t       *pInA2 = pInA1 + MATRIX_DIM3;
    q63_t        acc0, acc1, acc2;
    q15x8_t    vecB, vecA0, vecA1, vecA2;
    mve_pred16_t p0 = vctp16q(MATRIX_DIM3);

    vecColBOffs = vidupq_u16((uint32_t)0, 1);
    vecColBOffs = vecColBOffs * MATRIX_DIM3;

    pInB = pSrcB->pData;

    vecB = vldrhq_gather_shifted_offset_z_s16((q15_t const *)pInB, vecColBOffs, p0);

    vecA0 = vldrhq_s16(pInA0);
    vecA1 = vldrhq_s16(pInA1);
    vecA2 = vldrhq_s16(pInA2);

    acc0 = vmlaldavq(vecA0, vecB);
    acc1 = vmlaldavq(vecA1, vecB);
    acc2 = vmlaldavq(vecA2, vecB);

    acc0 = asrl(acc0, 15);
    acc1 = asrl(acc1, 15);
    acc2 = asrl(acc2, 15);

    pOut[0 * MATRIX_DIM3] = (q15_t) __SSAT(acc0, 16);
    pOut[1 * MATRIX_DIM3] = (q15_t) __SSAT(acc1, 16);
    pOut[2 * MATRIX_DIM3] = (q15_t) __SSAT(acc2, 16);
    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrhq_gather_shifted_offset_z_s16(pInB, vecColBOffs, p0);

    acc0 = vmlaldavq(vecA0, vecB);
    acc1 = vmlaldavq(vecA1, vecB);
    acc2 = vmlaldavq(vecA2, vecB);

    acc0 = asrl(acc0, 15);
    acc1 = asrl(acc1, 15);
    acc2 = asrl(acc2, 15);

    pOut[0 * MATRIX_DIM3] = (q15_t) __SSAT(acc0, 16);
    pOut[1 * MATRIX_DIM3] = (q15_t) __SSAT(acc1, 16);
    pOut[2 * MATRIX_DIM3] = (q15_t) __SSAT(acc2, 16);
    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrhq_gather_shifted_offset_z_s16(pInB, vecColBOffs, p0);

    acc0 = vmlaldavq(vecA0, vecB);
    acc1 = vmlaldavq(vecA1, vecB);
    acc2 = vmlaldavq(vecA2, vecB);

    acc0 = asrl(acc0, 15);
    acc1 = asrl(acc1, 15);
    acc2 = asrl(acc2, 15);

    pOut[0 * MATRIX_DIM3] = (q15_t) __SSAT(acc0, 16);
    pOut[1 * MATRIX_DIM3] = (q15_t) __SSAT(acc1, 16);
    pOut[2 * MATRIX_DIM3] = (q15_t) __SSAT(acc2, 16);
    /*
     * Return to application
     */
    return (ARM_MATH_SUCCESS);
}


__STATIC_INLINE arm_status arm_mat_mult_q15_4x4_mve(
    const arm_matrix_instance_q15 * pSrcA,
    const arm_matrix_instance_q15 * pSrcB,
    arm_matrix_instance_q15 * pDst)
{
    q15_t       *pInB = pSrcB->pData;  /* input data matrix pointer B */
    q15_t       *pInA = pSrcA->pData;  /* input data matrix pointer A */
    q15_t       *pOut = pDst->pData;   /* output data matrix pointer */
    uint16x8_t vecColBOffs;
    q15_t       *pInA0 = pInA;
    q15_t       *pInA1 = pInA0 + MATRIX_DIM4;
    q15_t       *pInA2 = pInA1 + MATRIX_DIM4;
    q15_t       *pInA3 = pInA2 + MATRIX_DIM4;
    q63_t        acc0, acc1, acc2, acc3;
    q15x8_t     vecB, vecA0, vecA1, vecA2, vecA3;
    mve_pred16_t p0 = vctp16q(MATRIX_DIM4);

    vecColBOffs = vidupq_u16((uint32_t)0, 4);

    pInB = pSrcB->pData;

    vecB = vldrhq_gather_shifted_offset_z_s16((q15_t const *)pInB, vecColBOffs, p0);

    vecA0 = vldrhq_s16(pInA0);
    vecA1 = vldrhq_s16(pInA1);
    vecA2 = vldrhq_s16(pInA2);
    vecA3 = vldrhq_s16(pInA3);

    acc0 = vmlaldavq(vecA0, vecB);
    acc1 = vmlaldavq(vecA1, vecB);
    acc2 = vmlaldavq(vecA2, vecB);
    acc3 = vmlaldavq(vecA3, vecB);

    acc0 = asrl(acc0, 15);
    acc1 = asrl(acc1, 15);
    acc2 = asrl(acc2, 15);
    acc3 = asrl(acc3, 15);

    pOut[0 * MATRIX_DIM4] = (q15_t) __SSAT(acc0, 16);
    pOut[1 * MATRIX_DIM4] = (q15_t) __SSAT(acc1, 16);
    pOut[2 * MATRIX_DIM4] = (q15_t) __SSAT(acc2, 16);
    pOut[3 * MATRIX_DIM4] = (q15_t) __SSAT(acc3, 16);
    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrhq_gather_shifted_offset_z_s16(pInB, vecColBOffs, p0);

    acc0 = vmlaldavq(vecA0, vecB);
    acc1 = vmlaldavq(vecA1, vecB);
    acc2 = vmlaldavq(vecA2, vecB);
    acc3 = vmlaldavq(vecA3, vecB);

    acc0 = asrl(acc0, 15);
    acc1 = asrl(acc1, 15);
    acc2 = asrl(acc2, 15);
    acc3 = asrl(acc3, 15);

    pOut[0 * MATRIX_DIM4] = (q15_t) __SSAT(acc0, 16);
    pOut[1 * MATRIX_DIM4] = (q15_t) __SSAT(acc1, 16);
    pOut[2 * MATRIX_DIM4] = (q15_t) __SSAT(acc2, 16);
    pOut[3 * MATRIX_DIM4] = (q15_t) __SSAT(acc3, 16);

    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrhq_gather_shifted_offset_z_s16(pInB, vecColBOffs, p0);

    acc0 = vmlaldavq(vecA0, vecB);
    acc1 = vmlaldavq(vecA1, vecB);
    acc2 = vmlaldavq(vecA2, vecB);
    acc3 = vmlaldavq(vecA3, vecB);

    acc0 = asrl(acc0, 15);
    acc1 = asrl(acc1, 15);
    acc2 = asrl(acc2, 15);
    acc3 = asrl(acc3, 15);

    pOut[0 * MATRIX_DIM4] = (q15_t) __SSAT(acc0, 16);
    pOut[1 * MATRIX_DIM4] = (q15_t) __SSAT(acc1, 16);
    pOut[2 * MATRIX_DIM4] = (q15_t) __SSAT(acc2, 16);
    pOut[3 * MATRIX_DIM4] = (q15_t) __SSAT(acc3, 16);

    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrhq_gather_shifted_offset_z_s16(pInB, vecColBOffs, p0);

    acc0 = vmlaldavq(vecA0, vecB);
    acc1 = vmlaldavq(vecA1, vecB);
    acc2 = vmlaldavq(vecA2, vecB);
    acc3 = vmlaldavq(vecA3, vecB);

    acc0 = asrl(acc0, 15);
    acc1 = asrl(acc1, 15);
    acc2 = asrl(acc2, 15);
    acc3 = asrl(acc3, 15);

    pOut[0 * MATRIX_DIM4] = (q15_t) __SSAT(acc0, 16);
    pOut[1 * MATRIX_DIM4] = (q15_t) __SSAT(acc1, 16);
    pOut[2 * MATRIX_DIM4] = (q15_t) __SSAT(acc2, 16);
    pOut[3 * MATRIX_DIM4] = (q15_t) __SSAT(acc3, 16);
    /*
     * Return to application
     */
    return (ARM_MATH_SUCCESS);
}


ARM_DSP_ATTRIBUTE arm_status arm_mat_mult_q15(
    const arm_matrix_instance_q15 * pSrcA,
    const arm_matrix_instance_q15 * pSrcB,
    arm_matrix_instance_q15 * pDst,
    q15_t * pState)
{
    q15_t          *pInA = pSrcA->pData;        /* input data matrix pointer A */
    q15_t          *pInB = pSrcB->pData;        /* input data matrix pointer B */
    q15_t          *pInA2;
    q15_t          *pInB2;
    q15_t          *px;         /* Temporary output data matrix pointer */
    q15_t          *px2;        /* Temporary output data matrix pointer */
    uint32_t        numRowsA = pSrcA->numRows;  /* number of rows of input matrix A    */
    uint32_t        numColsB = pSrcB->numCols;  /* number of columns of input matrix B */
    uint32_t        numColsA = pSrcA->numCols;  /* number of columns of input matrix A */
    uint32_t        numRowsB = pSrcB->numRows;  /* number of rows of input matrix A    */
    uint32_t        col, i = 0u, j, row = numRowsB;     /* loop counters */
    q15_t          *pSrcBT = pState;    /* input data matrix pointer for transpose */
    uint32_t        blkCnt;     /* loop counters */
    arm_status      status;                             /* Status of matrix multiplication */
    arm_matrix_instance_q15 BT;

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
#endif
    {
        /* small squared matrix specialized routines */
        if (numRowsA == numColsB && numColsB == numColsA) {

            if (numRowsA == 1) {
                q63_t           sum;
                sum = pInA[0] * pInB[0];
                pDst->pData[0] = (q15_t) __SSAT((sum >> 15), 16);
                return (ARM_MATH_SUCCESS);
            } else if (numRowsA == 2)
                return arm_mat_mult_q15_2x2_mve(pSrcA, pSrcB, pDst);
            else if (numRowsA == 3)
                return arm_mat_mult_q15_3x3_mve(pSrcA, pSrcB, pDst);
            else if (numRowsA == 4)
                return arm_mat_mult_q15_4x4_mve(pSrcA, pSrcB, pDst);
        }

        /*
         * Matrix transpose
         */

        BT.numRows = numColsB;
        BT.numCols = numRowsB;
        BT.pData = pSrcBT;

        arm_mat_trans_q15(pSrcB, &BT);


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
        while (row > 0u) {
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
            while (col > 0u) {
                q15_t const    *pSrcAVec, *pSrcBVec, *pSrcA2Vec, *pSrcB2Vec;
                q15x8_t         vecA, vecA2, vecB, vecB2;
                q63_t           acc0, acc1, acc2, acc3;

                /*
                 * Initiate the pointer pIn1 to point to the starting address of the column being processed
                 */
                pInA = pSrcA->pData + i;
                pInA2 = pInA + numColsA;
                pInB = pSrcBT + j;
                pInB2 = pInB + numRowsB;


                pSrcAVec = (q15_t const *) pInA;
                pSrcA2Vec = (q15_t const *) pInA2;
                pSrcBVec = (q15_t const *) pInB;
                pSrcB2Vec = (q15_t const *) pInB2;

                acc0 = 0LL;
                acc1 = 0LL;
                acc2 = 0LL;
                acc3 = 0LL;

                vecA = vld1q(pSrcAVec);
                pSrcAVec += 8;

                blkCnt = numColsA / 8;
                while (blkCnt > 0U) {
                    vecB = vld1q(pSrcBVec);
                    pSrcBVec += 8;
                    acc0 = vmlaldavaq(acc0, vecA, vecB);
                    vecA2 = vld1q(pSrcA2Vec);
                    pSrcA2Vec += 8;
                    acc1 = vmlaldavaq(acc1, vecA2, vecB);
                    vecB2 = vld1q(pSrcB2Vec);
                    pSrcB2Vec += 8;
                    acc2 = vmlaldavaq(acc2, vecA, vecB2);
                    vecA = vld1q(pSrcAVec);
                    pSrcAVec += 8;
                    acc3 = vmlaldavaq(acc3, vecA2, vecB2);

                    blkCnt--;
                }
                /*
                 * tail
                 */
                blkCnt = numColsA & 7;
                if (blkCnt > 0U) {
                    mve_pred16_t    p0 = vctp16q(blkCnt);
                    vecB = vld1q(pSrcBVec);
                    acc0 = vmlaldavaq_p(acc0, vecA, vecB, p0);
                    vecA2 = vld1q(pSrcA2Vec);
                    acc1 = vmlaldavaq_p(acc1, vecA2, vecB, p0);
                    vecB2 = vld1q(pSrcB2Vec);
                    acc2 = vmlaldavaq_p(acc2, vecA, vecB2, p0);
                    vecA = vld1q(pSrcAVec);
                    acc3 = vmlaldavaq_p(acc3, vecA2, vecB2, p0);
                }

                *px++ = (q15_t) MVE_ASRL_SAT16(acc0, 15);
                *px++ = (q15_t) MVE_ASRL_SAT16(acc2, 15);
                *px2++ = (q15_t) MVE_ASRL_SAT16(acc1, 15);
                *px2++ = (q15_t) MVE_ASRL_SAT16(acc3, 15);
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

        if (numColsB & 1u) {
            row = numRowsA & (~0x1);    //avoid redundant computation
            px = pDst->pData + numColsB - 1;
            i = 0;

            /*
             * row loop
             */
            while (row > 0) {
                q15_t const    *pSrcAVec, *pSrcBVec;
                q15x8_t         vecA, vecB;
                q63_t           acc0;

                /*
                 * point to last column in matrix B
                 */
                pInB = pSrcBT + numRowsB * (numColsB - 1);
                pInA = pSrcA->pData + i;

                pSrcAVec = (q15_t const *) pInA;
                pSrcBVec = (q15_t const *) pInB;

                acc0 = 0LL;
                blkCnt = (numColsA) / 8;
                while (blkCnt > 0U) {
                    vecA = vld1q(pSrcAVec);
                    pSrcAVec += 8;
                    vecB = vld1q(pSrcBVec);
                    pSrcBVec += 8;
                    acc0 = vmlaldavaq(acc0, vecA, vecB);

                    blkCnt--;
                }
                /*
                 * tail
                 */
                blkCnt = (numColsA & 7);
                if (blkCnt > 0U) {
                    mve_pred16_t    p0 = vctp16q(blkCnt);
                    vecA = vld1q(pSrcAVec);
                    vecB = vld1q(pSrcBVec);
                    acc0 = vmlaldavaq_p(acc0, vecA, vecB, p0);
                }

                *px = (q15_t) MVE_ASRL_SAT16(acc0, 15);

                px += numColsB;

                i += numColsA;
                /*
                 * Decrement the row loop counter
                 */
                row--;
            }
        }

        if (numRowsA & 1u) {
            col = numColsB;
            i = 0u;
            /*
             * point to last row in output matrix
             */
            px = pDst->pData + (numColsB) * (numRowsA - 1);
            /*
             * col loop
             */
            while (col > 0) {
                q15_t const    *pSrcAVec, *pSrcBVec;
                q15x8_t         vecA, vecB;
                q63_t           acc0;

                /*
                 * point to last row in matrix A
                 */
                pInA = pSrcA->pData + (numRowsA - 1) * numColsA;
                pInB = pSrcBT + i;

                /*
                 * Set the variable sum, that acts as accumulator, to zero
                 */
                pSrcAVec = (q15_t const *) pInA;
                pSrcBVec = (q15_t const *) pInB;
                acc0 = 0LL;

                blkCnt = ((numColsA) / 8);
                while (blkCnt > 0U) {
                    vecA = vld1q(pSrcAVec);
                    pSrcAVec += 8;
                    vecB = vld1q(pSrcBVec);
                    pSrcBVec += 8;
                    acc0 = vmlaldavaq(acc0, vecA, vecB);

                    blkCnt--;
                }
                /*
                 * tail
                 */
                blkCnt = (numColsA & 7);
                if (blkCnt > 0U) {
                    mve_pred16_t    p0 = vctp16q(blkCnt);
                    vecA = vld1q(pSrcAVec);
                    vecB = vld1q(pSrcBVec);
                    acc0 = vmlaldavaq_p(acc0, vecA, vecB, p0);
                }

                *px++ = (q15_t) MVE_ASRL_SAT16(acc0, 15);

                i += numColsA;

                /*
                 * Decrement the col loop counter
                 */
                col--;
            }
        }

        /* Set status as ARM_MATH_SUCCESS */
        status = ARM_MATH_SUCCESS;
    }
    /* Return to application */
    return (status);
}

#else

#if defined(ARM_MATH_NEON)

/**
  @brief         Q15 matrix multiplication.
  @param[in]     pSrcA      points to the first input matrix structure
  @param[in]     pSrcB      points to the second input matrix structure
  @param[out]    pDst       points to output matrix structure
  @param[in]     pState     points to the array for storing intermediate results
  @return        execution status
                   - \ref ARM_MATH_SUCCESS       : Operation successful
                   - \ref ARM_MATH_SIZE_MISMATCH : Matrix size check failed
**/


#define LANE 8

#define DTYPE q15_t
#define HEADERTYPE DTYPE
#define VEC int16x8_t
#define VECACC struct { \
    int64x2_t val[4];   \
}

#define CLEAR_ACC(tmp) \
    tmp.val[0] = vdupq_n_s64(0); \
    tmp.val[1] = vdupq_n_s64(0); \
    tmp.val[2] = vdupq_n_s64(0); \
    tmp.val[3] = vdupq_n_s64(0);

#define DEBUGVACC(X)

#define DEBUGV(X)

#define DEBUGS(X) 

#define DEBUGSACC(X)

#if defined(ARM_DSP_TESTING)
int cov_mat_mul_q15[20]={0};
#define LOGKERNEL(A,B) cov_mat_mul_q15[B]=1;
#else
#define LOGKERNEL(A,B) 
#endif

#define TMPMAC \
int32x4_t tmp;

#define TMPLD       \
  int16x8_t tmp1;   \
  int32x4x2_t tmp2;

#define TMPST                 \
  int32x2_t tlow;             \
  int32x2_t thigh;            \
  int16x4_t  htmplo,htmphigh;

#define SCALARACC int64_t 
#define SCALAR_LOAD_AND_WIDEN(DST,PTR) DST = (SCALARACC)(*(PTR))
#define SCALAR_STORE_AND_NARROW(PTR,VAL) *(PTR) = (q15_t) __SSAT((VAL) >> 15, 16)
#define SCALAR_MAC_N(ACC,VEC,SCALAR) ACC += (SCALARACC)(VEC) * (SCALARACC)(SCALAR)

#define VLOAD(DST,PTR) DST = vld1q_s16((PTR))
#define VSTORE(PTR,VAL) vst1q_s16((PTR),(VAL))

#define VLOAD_ACC(DST,PTR)         \
  DST.val[0] = vld1q_s64((PTR)+2*0); \
  DST.val[1] = vld1q_s64((PTR)+2*1); \
  DST.val[2] = vld1q_s64((PTR)+2*2); \
  DST.val[3] = vld1q_s64((PTR)+2*3);

#define VSTORE_ACC(PTR,VAL)        \
  vst1q_s64((PTR)+2*0,(VAL).val[0]); \
  vst1q_s64((PTR)+2*1,(VAL).val[1]); \
  vst1q_s64((PTR)+2*2,(VAL).val[2]); \
  vst1q_s64((PTR)+2*3,(VAL).val[3]);

#define VLOAD_AND_WIDEN(DST,PTR)                       \
    tmp1 = vld1q_s16((PTR));                            \
    tmp2.val[0] = vmovl_s16(vget_low_s16(tmp1));         \
    tmp2.val[1] = vmovl_s16(vget_high_s16(tmp1));        \
    DST.val[0] = vmovl_s32(vget_low_s32(tmp2.val[0]));  \
    DST.val[1] = vmovl_s32(vget_high_s32(tmp2.val[0])); \
    DST.val[2] = vmovl_s32(vget_low_s32(tmp2.val[1]));  \
    DST.val[3] = vmovl_s32(vget_high_s32(tmp2.val[1]));

#define VSTORE_AND_NARROW(PTR,VAL)                      \
    tlow = vqshrn_n_s64(VAL.val[0],15);                  \
    thigh = vqshrn_n_s64(VAL.val[1],15);                 \
    htmplo = vqmovn_s32(vcombine_s32(tlow,thigh)); \
    tlow = vqshrn_n_s64(VAL.val[2],15);                  \
    thigh = vqshrn_n_s64(VAL.val[3],15);                 \
    htmphigh = vqmovn_s32(vcombine_s32(tlow,thigh)); \
    vst1q_s16(PTR,vcombine_s16(htmplo,htmphigh));

  #define VMAC_N(ACC,VEC,SCALAR)                                    \
    tmp = vmull_s16(vget_low_s16(VEC),vdup_n_s16(SCALAR));               \
    ACC.val[0] = vqaddq_s64(ACC.val[0],vmovl_s32(vget_low_s32(tmp)));  \
    ACC.val[1] = vqaddq_s64(ACC.val[1],vmovl_s32(vget_high_s32(tmp))); \
    tmp = vmull_s16(vget_high_s16(VEC),vdup_n_s16(SCALAR));              \
    ACC.val[2] = vqaddq_s64(ACC.val[2],vmovl_s32(vget_low_s32(tmp)));  \
    ACC.val[3] = vqaddq_s64(ACC.val[3],vmovl_s32(vget_high_s32(tmp)));

#define MATTYPE arm_matrix_instance_q15
#define EXT(A) A##_q15
#define HAS_TEMP_BUFFER
#define USE_TMP_REGISTER

#define FUNCNAME arm_mat_mult_q15

#include "_arm_mat_mult_neon.c"

#else
ARM_DSP_ATTRIBUTE arm_status arm_mat_mult_q15(
  const arm_matrix_instance_q15 * pSrcA,
  const arm_matrix_instance_q15 * pSrcB,
        arm_matrix_instance_q15 * pDst,
        q15_t                   * pState)
{
        q63_t sum;                                     /* Accumulator */

#if defined (ARM_MATH_DSP)                             /* != CM0 */

        q15_t *pSrcBT = pState;                        /* Input data matrix pointer for transpose */
        q15_t *pInA = pSrcA->pData;                    /* Input data matrix pointer A of Q15 type */
        q15_t *pInB = pSrcB->pData;                    /* Input data matrix pointer B of Q15 type */
        q15_t *px;                                     /* Temporary output data matrix pointer */
        uint16_t numRowsA = pSrcA->numRows;            /* Number of rows of input matrix A */
        uint16_t numColsB = pSrcB->numCols;            /* Number of columns of input matrix B */
        uint16_t numColsA = pSrcA->numCols;            /* Number of columns of input matrix A */
        uint16_t numRowsB = pSrcB->numRows;            /* Number of rows of input matrix B */
        uint32_t col, i = 0U, row = numRowsB, colCnt;  /* Loop counters */
        arm_status status;                             /* Status of matrix multiplication */

        q31_t inA1, inB1, inA2, inB2;
        arm_matrix_instance_q15 BT;

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

    BT.numRows = numColsB;
    BT.numCols = numRowsB;
    BT.pData = pSrcBT;

    arm_mat_trans_q15(pSrcB,&BT);
    /* Reset variables for usage in following multiplication process */
    row = numRowsA;
    i = 0U;
    px = pDst->pData;

    /* The following loop performs the dot-product of each row in pSrcA with each column in pSrcB */
    /* row loop */
    do
    {
      /* For every row wise process, column loop counter is to be initiated */
      col = numColsB;

      /* For every row wise process, pIn2 pointer is set to starting address of transposed pSrcB data */
      pInB = pSrcBT;

      /* column loop */
      do
      {
        /* Set variable sum, that acts as accumulator, to zero */
        sum = 0;

        /* Initiate pointer pInA to point to starting address of column being processed */
        pInA = pSrcA->pData + i;

        /* Apply loop unrolling and compute 2 MACs simultaneously. */
        colCnt = numColsA >> 2U;

        /* matrix multiplication */
        while (colCnt > 0U)
        {
          /* c(m,n) = a(1,1) * b(1,1) + a(1,2) * b(2,1) + .... + a(m,p) * b(p,n) */

          /* read real and imag values from pSrcA and pSrcB buffer */
          inA1 = read_q15x2_ia (&pInA);
          inB1 = read_q15x2_ia (&pInB);

          inA2 = read_q15x2_ia (&pInA);
          inB2 = read_q15x2_ia (&pInB);

          /* Multiply and Accumulates */
          sum = __SMLALD(inA1, inB1, sum);
          sum = __SMLALD(inA2, inB2, sum);

          /* Decrement loop counter */
          colCnt--;
        }

        /* process remaining column samples */
        colCnt = numColsA % 0x4U;

        while (colCnt > 0U)
        {
          /* c(m,n) = a(1,1) * b(1,1) + a(1,2) * b(2,1) + .... + a(m,p) * b(p,n) */
          sum += *pInA++ * *pInB++;

          /* Decrement loop counter */
          colCnt--;
        }

        /* Saturate and store result in destination buffer */
        *px = (q15_t) (__SSAT((sum >> 15), 16));
        px++;

        /* Decrement column loop counter */
        col--;

      } while (col > 0U);

      i = i + numColsA;

      /* Decrement row loop counter */
      row--;

    } while (row > 0U);

#else /* #if defined (ARM_MATH_DSP) */

        q15_t *pIn1 = pSrcA->pData;                    /* Input data matrix pointer A */
        q15_t *pIn2 = pSrcB->pData;                    /* Input data matrix pointer B */
        q15_t *pInA = pSrcA->pData;                    /* Input data matrix pointer A of Q15 type */
        q15_t *pInB = pSrcB->pData;                    /* Input data matrix pointer B of Q15 type */
        q15_t *pOut = pDst->pData;                     /* Output data matrix pointer */
        q15_t *px;                                     /* Temporary output data matrix pointer */
        uint16_t numColsB = pSrcB->numCols;            /* Number of columns of input matrix B */
        uint16_t numColsA = pSrcA->numCols;            /* Number of columns of input matrix A */
        uint16_t numRowsA = pSrcA->numRows;            /* Number of rows of input matrix A    */
        uint32_t col, i = 0U, row = numRowsA, colCnt;  /* Loop counters */
        arm_status status;                             /* Status of matrix multiplication */
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
    do
    {
      /* Output pointer is set to starting address of the row being processed */
      px = pOut + i;

      /* For every row wise process, column loop counter is to be initiated */
      col = numColsB;

      /* For every row wise process, pIn2 pointer is set to starting address of pSrcB data */
      pIn2 = pSrcB->pData;

      /* column loop */
      do
      {
        /* Set the variable sum, that acts as accumulator, to zero */
        sum = 0;

        /* Initiate pointer pIn1 to point to starting address of pSrcA */
        pIn1 = pInA;

        /* Matrix A columns number of MAC operations are to be performed */
        colCnt = numColsA;

        /* matrix multiplication */
        while (colCnt > 0U)
        {
          /* c(m,n) = a(1,1) * b(1,1) + a(1,2) * b(2,1) + .... + a(m,p) * b(p,n) */

          /* Perform multiply-accumulates */
          sum += (q31_t) * pIn1++ * *pIn2;
          pIn2 += numColsB;

          /* Decrement loop counter */
          colCnt--;
        }

        /* Convert result from 34.30 to 1.15 format and store saturated value in destination buffer */

        /* Saturate and store result in destination buffer */
        *px++ = (q15_t) __SSAT((sum >> 15), 16);

        /* Decrement column loop counter */
        col--;

        /* Update pointer pIn2 to point to starting address of next column */
        pIn2 = pInB + (numColsB - col);

      } while (col > 0U);

      /* Update pointer pSrcA to point to starting address of next row */
      i = i + numColsB;
      pInA = pInA + numColsA;

      /* Decrement row loop counter */
      row--;

    } while (row > 0U);

#endif /* #if defined (ARM_MATH_DSP) */

    /* Set status as ARM_MATH_SUCCESS */
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
