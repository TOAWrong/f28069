;******************************************************************************
;******************************************************************************
; 
; FILE: rfft_512_data.asm
; 
; DESCRIPTION: Input test data for the FFT
; 
;******************************************************************************
;  $TI Release: C28x VCU Library V2.10.00.00 $
;  $Release Date: May 22, 2017 $
;  $Copyright: Copyright (C) 2017 Texas Instruments Incorporated -
;              http://www.ti.com/ ALL RIGHTS RESERVED $
;******************************************************************************
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;******************************************************************************
		;.cdecls   C,LIST,"fft.h"
;############################################################################
;
;/*! \page RFFT_512_DATA (Input test data to the FFT)
;
; The input test data is a two tone function. We run the fft on this 
; data and compare to the expected output.
;*/
;############################################################################
       
        .sect .econst
        .global _RFFT16_512p_in_data,_RFFT16_512p_out_data
         
; FFT input data, two-tone test          
_RFFT16_512p_in_data: 
        .word   2232, 1930,  1165, 286,  -347, -560,  -445, -286
        .word   -373, -809,  -1440, -1930,  -1957, -1406,  -445, 560
        .word   1237, 1406,  1165, 809,  648, 809,  1165, 1406
        .word   1237, 560,  -445, -1406,  -1957, -1930,  -1440, -809
        .word   -373, -286,  -445, -560,  -347, 286,  1165, 1930
        .word   2232, 1930,  1165, 286,  -347, -560,  -445, -286
        .word   -373, -809,  -1440, -1930,  -1957, -1406,  -445, 560
        .word   1237, 1406,  1165, 809,  648, 809,  1165, 1406
        .word   1237, 560,  -445, -1406,  -1957, -1930,  -1440, -809
        .word   -373, -286,  -445, -560,  -347, 286,  1165, 1930
        .word   2232, 1930,  1165, 286,  -347, -560,  -445, -286
        .word   -373, -809,  -1440, -1930,  -1957, -1406,  -445, 560
        .word   1237, 1406,  1165, 809,  648, 809,  1165, 1406
        .word   1237, 560,  -445, -1406,  -1957, -1930,  -1440, -809
        .word   -373, -286,  -445, -560,  -347, 286,  1165, 1930
        .word   2232, 1930,  1165, 286,  -347, -560,  -445, -286
        .word   -373, -809,  -1440, -1930,  -1957, -1406,  -445, 560
        .word   1237, 1406,  1165, 809,  648, 809,  1165, 1406
        .word   1237, 560,  -445, -1406,  -1957, -1930,  -1440, -809
        .word   -373, -286,  -445, -560,  -347, 286,  1165, 1930
        .word   2232, 1930,  1165, 286,  -347, -560,  -445, -286
        .word   -373, -809,  -1440, -1930,  -1957, -1406,  -445, 560
        .word   1237, 1406,  1165, 809,  648, 809,  1165, 1406
        .word   1237, 560,  -445, -1406,  -1957, -1930,  -1440, -809
        .word   -373, -286,  -445, -560,  -347, 286,  1165, 1930
        .word   2232, 1930,  1165, 286,  -347, -560,  -445, -286
        .word   -373, -809,  -1440, -1930,  -1957, -1406,  -445, 560
        .word   1237, 1406,  1165, 809,  648, 809,  1165, 1406
        .word   1237, 560,  -445, -1406,  -1957, -1930,  -1440, -809
        .word   -373, -286,  -445, -560,  -347, 286,  1165, 1930
        .word   2232, 1930,  1165, 286,  -347, -560,  -445, -286
        .word   -373, -809,  -1440, -1930,  -1957, -1406,  -445, 560
        .word   1237, 1406,  1165, 809,  648, 809,  1165, 1406
        .word   1237, 560,  -445, -1406,  -1957, -1930,  -1440, -809
        .word   -373, -286,  -445, -560,  -347, 286,  1165, 1930
        .word   2232, 1930,  1165, 286,  -347, -560,  -445, -286
        .word   -373, -809,  -1440, -1930,  -1957, -1406,  -445, 560
        .word   1237, 1406,  1165, 809,  648, 809,  1165, 1406
        .word   1237, 560,  -445, -1406,  -1957, -1930,  -1440, -809
        .word   -373, -286,  -445, -560,  -347, 286,  1165, 1930
        .word   2232, 1930,  1165, 286,  -347, -560,  -445, -286
        .word   -373, -809,  -1440, -1930,  -1957, -1406,  -445, 560
        .word   1237, 1406,  1165, 809,  648, 809,  1165, 1406
        .word   1237, 560,  -445, -1406,  -1957, -1930,  -1440, -809
        .word   -373, -286,  -445, -560,  -347, 286,  1165, 1930
        .word   2232, 1930,  1165, 286,  -347, -560,  -445, -286
        .word   -373, -809,  -1440, -1930,  -1957, -1406,  -445, 560
        .word   1237, 1406,  1165, 809,  648, 809,  1165, 1406
        .word   1237, 560,  -445, -1406,  -1957, -1930,  -1440, -809
        .word   -373, -286,  -445, -560,  -347, 286,  1165, 1930
        .word   2232, 1930,  1165, 286,  -347, -560,  -445, -286
        .word   -373, -809,  -1440, -1930,  -1957, -1406,  -445, 560
        .word   1237, 1406,  1165, 809,  648, 809,  1165, 1406
        .word   1237, 560,  -445, -1406,  -1957, -1930,  -1440, -809
        .word   -373, -286,  -445, -560,  -347, 286,  1165, 1930
        .word   2232, 1930,  1165, 286,  -347, -560,  -445, -286
        .word   -373, -809,  -1440, -1930,  -1957, -1406,  -445, 560
        .word   1237, 1406,  1165, 809,  648, 809,  1165, 1406
        .word   1237, 560,  -445, -1406,  -1957, -1930,  -1440, -809
        .word   -373, -286,  -445, -560,  -347, 286,  1165, 1930
        .word   2232, 1930,  1165, 286,  -347, -560,  -445, -286
        .word   -373, -809,  -1440, -1930,  -1957, -1406,  -445, 560
        .word   1237, 1406,  1165, 809,  648, 809,  1165, 1406
        .word   1237, 560,  -445, -1406,  -1957, -1930,  -1440, -809
				
; FFT output data
_RFFT16_512p_out_data: 
        .word   0, -2,  1, -2,  1, -2,  2, -2
        .word   3, -2,  3, -3,  4, -3,  5, -3
        .word   6, -3,  6, -4,  7, -4,  9, -4
        .word   10, -4,  11, -5,  13, -5,  15, -5
        .word   17, -6,  19, -7,  23, -8,  27, -9
        .word   33, -11,  41, -14,  54, -17,  75, -25
        .word   126, -41,  342, -111,  -522, 169,  -152, 49
        .word   -90, 30,  -65, 21,  -51, 17,  -42, 14
        .word   -36, 12,  -31, 11,  -29, 9,  -25, 8
        .word   -22, 8,  -22, 7,  -20, 7,  -19, 7
        .word   -18, 6,  -16, 6,  -16, 5,  -15, 5
        .word   -14, 5,  -13, 5,  -13, 5,  -12, 5
        .word   -12, 5,  -11, 5,  -11, 4,  -11, 4
        .word   -11, 4,  -10, 5,  -10, 4,  -10, 4
        .word   -9, 4,  -9, 4,  -9, 4,  -9, 4
        .word   -8, 4,  -8, 4,  -8, 3,  -8, 3
        .word   -7, 399,  -7, 3,  -7, 4,  -7, 3
        .word   -7, 3,  -7, 4,  -7, 3,  -7, 3
        .word   -6, 3,  -7, 3,  -6, 3,  -6, 4
        .word   -6, 3,  -6, 3,  -6, 3,  -5, 3
        .word   -5, 3,  -5, 3,  -5, 3,  -5, 3
        .word   -4, 3,  -5, 3,  -5, 3,  -5, 3
        .word   -4, 3,  -4, 3,  -5, 3,  -4, 3
        .word   -4, 3,  -4, 3,  -4, 3,  -4, 3
        .word   -4, 3,  -4, 3,  -4, 3,  -4, 2
        .word   -4, 3,  -4, 3,  -4, 3,  -3, 3
        .word   -4, 3,  -4, 3,  -4, 3,  -4, 3
        .word   -4, 3,  -4, 3,  -4, 3,  -4, 3
        .word   -4, 3,  -3, 2,  -4, 3,  -3, 3
        .word   -3, 3,  -3, 2,  -3, 3,  -3, 3
        .word   -2, 3,  -2, 3,  -3, 3,  -3, 3
        .word   -3, 3,  -2, 3,  -2, 3,  -2, 3
        .word   -2, 3,  -2, 2,  -2, 3,  -2, 3
        .word   -3, 3,  -2, 3,  -3, 3,  -2, 3
        .word   -2, 3,  -2, 2,  -2, 3,  -2, 3
        .word   -2, 3,  -3, 3,  -3, 3,  -2, 3
        .word   -3, 3,  -3, 2,  -2, 3,  -3, 2
        .word   -3, 3,  -3, 3,  -2, 3,  -2, 3
        .word   -3, 3,  -2, 3,  -2, 3,  -2, 3
        .word   -2, 3,  -2, 3,  -2, 3,  -2, 3
        .word   -2, 3,  -2, 3,  -1, 3,  -2, 3
        .word   -1, 3,  -1, 3,  -2, 3,  -1, 3
        .word   -1, 3,  -2, 2,  -1, 3,  -2, 3
        .word   -1, 3,  -2, 3,  -1, 3,  -2, 3
        .word   -1, 3,  -2, 3,  -1, 3,  -1, 3
        .word   -1, 3,  -1, 2,  -1, 3,  -2, 3
        .word   -1, 3,  -2, 3,  -1, 3,  -1, 2
        .word   -1, 3,  -1, 3,  -1, 2,  -1, 3
        .word   -1, 3,  -2, 3,  -1, 3,  -1, 2
        .word   -1, 2,  -1, 2,  -1, 3,  -1, 3
        .word   -1, 3,  -1, 3,  -1, 3,  -1, 2
        .word   -1, 3,  -1, 3,  0, 3,  -1, 2
        .word   -1, 2,  -1, 3,  -1, 3,  -1, 3
        .word   -1, 3,  -1, 3,  -1, 3,  -1, 3
        .word   -1, 3,  -1, 2,  -1, 2,  -1, 3
        .word   0, 2,  -1, 3,  -1, 3,  -1, 2
        .word   -1, 3,  -1, 2,  -1, 2,  -1, 3
        .word   -1, 2,  -1, 3,  -1, 3,  0, 3
        .word   0, 3,  -1, 3,  0, 2,  0, 3
        .word   0, 3,  0, 3,  0, 3,  -1, 3
        .word   0, 3,  0, 3,  0, 2,  -1, 3
        .word   0, 2,  0, 3,  0, 3,  0, 4
        .word   0, 2,  0, 2,  0, 2,  0, 3
        .word   0, 2,  0, 2,  0, 2,  0, 3

        
