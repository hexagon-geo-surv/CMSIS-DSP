/*
 *  Copyright 2015-16 ARM Limited
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of ARM Limited nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY ARM LIMITED AND CONTRIBUTORS "AS IS" AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL ARM LIMITED BE LIABLE FOR ANY
 *  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* license of Kiss FFT */
/*
Copyright (c) 2003-2010, Mark Borgerding

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    * Neither the author nor the names of any contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
 * NE10 Library : dsp/NE10_fft_generic_int32.neonintrisic.cpp
 *
 * This file must be compiled by C++ toolchain because some functions are
 * written as template functions to make it easier for compiler to
 * reduce branch jump.
 */

#include "CMSIS_NE10_fft_generic_int32.neonintrinsic.h"
#include "CMSIS_NE10_fft.h"

#define NE10_MIXED_RADIX_GENERIC_BUTTERFLY_INT32_NEON_DISPATCH(ISINVERSE)         \
static inline void ne10_mixed_radix_generic_butterfly_int32_neon_dispatch_##ISINVERSE (  \
        ne10_fft_cpx_int32_t *Fout,                                               \
        const ne10_fft_cpx_int32_t *Fin,                                          \
        const ne10_uint32_t *factors,                                              \
        const ne10_fft_cpx_int32_t *twiddles,                                     \
        ne10_fft_cpx_int32_t *buffer,                                             \
        ne10_int32_t is_scaled_flag)                                              \
{                                                                                 \
    ne10_int32_t stage_count = factors[0];                                        \
    ne10_int32_t fstride = factors[1];                                            \
    ne10_int32_t radix = factors[stage_count << 1]; /* radix of first stage */      \
                                                                                  \
    /* nfft below is not the actual length of FFT, it is 1/4 of the actual one*/    \
    /* instead. */                                                                \
    ne10_int32_t nfft = fstride * radix;                                          \
                                                                                  \
    void (*ne10_mixed_butterfly_f) (CPLX *, const CPLX *, const ne10_uint32_t *,   \
            const ne10_fft_cpx_int32_t *, CPLX *) = NULL;                         \
                                                                                  \
    void (*ne10_last_stage_f) (CPLX *, const CPLX *, const ne10_fft_cpx_int32_t *,\
            ne10_int32_t, ne10_int32_t, ne10_int32_t) = NULL;                     \
                                                                                  \
    if (is_scaled_flag == 1)                                                      \
    {                                                                             \
        ne10_mixed_butterfly_f =                                                  \
            ne10_mixed_radix_generic_butterfly_int32_neon_impl_##ISINVERSE##_1;   \
    }                                                                             \
    else                                                                          \
    {                                                                             \
        ne10_mixed_butterfly_f =                                                  \
            ne10_mixed_radix_generic_butterfly_int32_neon_impl_##ISINVERSE##_0;   \
    }                                                                             \
                                                                                  \
    if (is_scaled_flag == 1)                                                      \
    {                                                                             \
        ne10_last_stage_f =                                                       \
            ne10_c2c_1d_last_stage_neon_##ISINVERSE##_1;                          \
    }                                                                             \
    else                                                                          \
    {                                                                             \
        ne10_last_stage_f =                                                       \
            ne10_c2c_1d_last_stage_neon_##ISINVERSE##_0;                          \
    }                                                                             \
                                                                                  \
    ne10_mixed_butterfly_f ((CPLX *) buffer,                                      \
            (const CPLX *) Fin, /* From Fin to buffer */                            \
            factors,                                                              \
            twiddles,                                                             \
            (CPLX *) Fout); /* Fout is "buffer" for these stages.*/                 \
                                                                                  \
    ne10_last_stage_f ((CPLX *) Fout,                                             \
            (const CPLX *) buffer, /* From buffer to Fout  */                       \
            twiddles + nfft,                                                      \
            1, /* out_step == fstride == 1  */                                      \
            nfft, /* in_step == mstride == nfft */                                  \
            nfft * 4); /* Actual length of FFT    */                                \
}

NE10_MIXED_RADIX_GENERIC_BUTTERFLY_INT32_NEON_DISPATCH(0)
NE10_MIXED_RADIX_GENERIC_BUTTERFLY_INT32_NEON_DISPATCH(1)

void arm_ne10_mixed_radix_generic_butterfly_int32_neon (
        const arm_cfft_instance_q31 *S,
        const ne10_fft_cpx_int32_t *in,
        ne10_fft_cpx_int32_t *out,
        ne10_fft_cpx_int32_t *buffer,
        ne10_int32_t scaled_flag)
{
    (void)scaled_flag;
    // The scaling flag does not have the same meaning for the
    // generic and the normal implementation
    ne10_mixed_radix_generic_butterfly_int32_neon_dispatch_0 (
            out, in, 
            S->factors, 
            (const ne10_fft_cpx_int32_t*)S->pTwiddle, 
            buffer, 
            1);
}

void arm_ne10_mixed_radix_generic_butterfly_inverse_int32_neon (
        const arm_cfft_instance_q31 *S,
        const ne10_fft_cpx_int32_t *in,
        ne10_fft_cpx_int32_t *out,
        ne10_fft_cpx_int32_t *buffer,
        ne10_int32_t scaled_flag)
{
    (void)scaled_flag;
    // The scaling flag does not have the same meaning for the
    // generic and the normal implementation
    ne10_mixed_radix_generic_butterfly_int32_neon_dispatch_1 (
            out, in, 
            S->factors, 
            (const ne10_fft_cpx_int32_t*)S->pTwiddle, 
            buffer, 
            1);
}
