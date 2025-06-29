/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        MatrixFunctions.c
 * Description:  Combination of all matrix function source files.
 *
 * $Date:        18. March 2019
 * $Revision:    V1.0.0
 *
 * Target Processor: Cortex-M cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2019 ARM Limited or its affiliates. All rights reserved.
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

#include "arm_mat_add_f32.c"
#include "arm_mat_add_q15.c"
#include "arm_mat_add_q31.c"
#include "arm_mat_cmplx_mult_f32.c"
#include "arm_mat_cmplx_mult_q15.c"
#include "arm_mat_cmplx_mult_q31.c"
#include "arm_mat_init_f64.c"
#include "arm_mat_init_f32.c"
#include "arm_mat_init_q15.c"
#include "arm_mat_init_q7.c"
#include "arm_mat_init_q31.c"
#include "arm_mat_inverse_f32.c"
#include "arm_mat_inverse_f64.c"
#include "arm_mat_mult_f64.c"
#include "arm_mat_mult_f32.c"
#include "arm_mat_mult_fast_q15.c"
#include "arm_mat_mult_fast_q31.c"
#include "arm_mat_mult_q7.c"
#include "arm_mat_mult_q15.c"
#include "arm_mat_mult_q31.c"
#include "arm_mat_mult_opt_q31.c"
#include "arm_mat_scale_f32.c"
#include "arm_mat_scale_q15.c"
#include "arm_mat_scale_q31.c"
#include "arm_mat_sub_f64.c"
#include "arm_mat_sub_f32.c"
#include "arm_mat_sub_q15.c"
#include "arm_mat_sub_q31.c"
#include "arm_mat_trans_f32.c"
#include "arm_mat_trans_f64.c"
#include "arm_mat_trans_q7.c"
#include "arm_mat_trans_q15.c"
#include "arm_mat_trans_q31.c"
#include "arm_mat_vec_mult_f32.c"
#include "arm_mat_vec_mult_q31.c"
#include "arm_mat_vec_mult_q15.c"
#include "arm_mat_vec_mult_q7.c"
#include "arm_mat_cmplx_trans_f32.c"
#include "arm_mat_cmplx_trans_q31.c"
#include "arm_mat_cmplx_trans_q15.c"
#include "arm_mat_cholesky_f64.c"
#include "arm_mat_cholesky_f32.c"
#include "arm_mat_solve_upper_triangular_f32.c"
#include "arm_mat_solve_lower_triangular_f32.c"
#include "arm_mat_solve_upper_triangular_f64.c"
#include "arm_mat_solve_lower_triangular_f64.c"
#include "arm_mat_ldlt_f32.c"
#include "arm_mat_ldlt_f64.c"
#include "arm_mat_qr_f32.c"
#include "arm_mat_qr_f64.c"
#include "arm_householder_f64.c"
#include "arm_householder_f32.c"
#if defined(ARM_MATH_NEON)
#include "_arm_mat_mult_neon_buffers.c"
#endif
