/****************************************************************************************
* LatticeCrypto: an efficient post-quantum Ring-Learning With Errors cryptography library
*
*    Copyright (c) Microsoft Corporation. All rights reserved.
*
*
* Abstract: internal header file
*
*****************************************************************************************/  

#pragma once

// Basic constants
#define PARAMETER_N         1024
#define PARAMETER_Q         12289
#define SEED_BYTES          256/8
#define ERROR_SEED_BYTES    256/8
#define NONCE_SEED_BYTES    256/8
#define PARAMETER_Q4        3073 
#define PARAMETER_3Q4       9217 
#define PARAMETER_5Q4       15362 
#define PARAMETER_7Q4       21506 
#define PARAMETER_Q2        6145 
#define PARAMETER_3Q2       18434
    

// Macro definitions

#define NBITS_TO_NWORDS(nbits)      (((nbits)+(sizeof(digit_t)*8)-1)/(sizeof(digit_t)*8))    // Conversion macro from number of bits to number of computer words
#define NBYTES_TO_NWORDS(nbytes)    (((nbytes)+sizeof(digit_t)-1)/sizeof(digit_t))           // Conversion macro from number of bytes to number of computer words

// Macro to avoid compiler warnings when detecting unreferenced parameters
#define UNREFERENCED_PARAMETER(PAR) (PAR)

