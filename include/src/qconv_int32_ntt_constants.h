/****************************************************************************************
* LatticeCrypto: an efficient post-quantum Ring-Learning With Errors cryptography library
*
*    Copyright (c) Microsoft Corporation. All rights reserved.
*
*
* Abstract: fixed constants for the Number Theoretic Transform (NTT)
*
*****************************************************************************************/

#pragma once

#include "qconv_int32.h"

// N^-1 * prime_scale^-8
extern const qconv_int32_mod Ninv8_ntt1024_12289;

// N^-1 * prime_scale^-7 * omegainv_rev_ntt1024_12289[1]
extern const qconv_int32_mod omegainv7N_rev_ntt1024_12289;

// N^-1 * prime_scale^-11
extern const qconv_int32_mod Ninv11_ntt1024_12289;

// N^-1 * prime_scale^-10 * omegainv_rev_ntt1024_12289[1]
extern const qconv_int32_mod omegainv10N_rev_ntt1024_12289;


// Index-reversed matrices containing powers of psi (psi_rev_nttxxx_yyy) and inverse powers of omega (omegainv_rev_nttxxx_yyy),
// where xxx is parameter N and yyy is the prime q.

extern const qconv_inner_int32 psi_rev_ntt1024_12289[1024];

extern const qconv_inner_int32 omegainv_rev_ntt1024_12289[1024];

extern const qconv_inner_int32 psi_rev_ntt512_12289[512];

extern const qconv_inner_int32 omegainv_rev_ntt512_12289[512];