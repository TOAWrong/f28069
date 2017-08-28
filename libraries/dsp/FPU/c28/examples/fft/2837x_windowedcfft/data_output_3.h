//#############################################################################
//! \file /2837x_WindowedCFFT/data_output_3.h
//!
//! \brief  Phase of the Output of the Complex Windowed FFT 128 pt Example
//!
//! Run the CFFTWindowedforC28xNew.m MATLAB script to get the input/output
//! vectors
//
//#############################################################################
// $TI Release: C28x Floating Point Unit Library V1.50.00.00 $
// $Release Date: May 22, 2017 $
// $Copyright: Copyright (C) 2017 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################
#if    0 //(TEST_INPUT_REAL == 1)
 3.1415927,  1.3844039, -1.9619918,  1.5455629,
-1.5724192,  1.5957108, -1.8563391, -2.4139096,
-1.8363832,  1.3315033, -1.7868787,  1.3830893,
 1.4207361,  1.4523907,  2.2200769,  1.5187269,
-2.0309563,  1.5786390, -1.9995103,  1.6343864,
-2.0420125,  1.6882643, -2.1190768,  1.7418284,
-2.2232788,  1.7960419, -2.3490214,  1.8514790,
-2.4875975,  1.9084675, -2.6273795,  1.9671795,
-2.7570684,  2.0276872, -2.8690879,  2.0899981,
-2.9605800,  2.1540771, -3.0322050,  2.2198605,
-3.0863893,  2.2872653, -3.1260531,  2.3561947,
 3.1292264,  2.4265422,  3.1107117,  2.4981931,
 3.0996481,  2.5710269,  3.0944741,  2.6449175,
 3.0939354,  2.7197344,  3.0970177,  2.7953425,
 3.1028880,  2.8716035,  3.1108491,  2.9483758,
 3.1203013,  3.0255152,  3.1307123,  3.1028756,
 3.1415927, -3.1028756, -3.1307123, -3.0255152,
-3.1203013, -2.9483758, -3.1108491, -2.8716035,
-3.1028880, -2.7953425, -3.0970177, -2.7197344,
-3.0939354, -2.6449175, -3.0944741, -2.5710269,
-3.0996481, -2.4981931, -3.1107117, -2.4265422,
-3.1292264, -2.3561947,  3.1260531, -2.2872653,
 3.0863893, -2.2198605,  3.0322050, -2.1540771,
 2.9605800, -2.0899981,  2.8690879, -2.0276872,
 2.7570684, -1.9671795,  2.6273795, -1.9084675,
 2.4875975, -1.8514790,  2.3490214, -1.7960419,
 2.2232788, -1.7418284,  2.1190768, -1.6882643,
 2.0420125, -1.6343864,  1.9995103, -1.5786390,
 2.0309563, -1.5187269, -2.2200769, -1.4523907,
-1.4207361, -1.3830893,  1.7868787, -1.3315033,
 1.8363832,  2.4139096,  1.8563391, -1.5957108,
 1.5724192, -1.5455629,  1.9619918, -1.3844039,
#else //(TEST_INPUT_COMPLEX == 1)
-3.0044641,  1.3836742, -1.9596122,  1.5455641,
-1.5725275,  1.5957178, -1.8650680, -2.4111711,
-1.8374235,  1.3315074, -1.7872961,  1.3832098,
 1.4903185,  1.4562960, -2.7889029,  1.5474775,
-2.5843974,  1.7471063, -2.6447840,  2.6635574,
-2.6804731, -2.7597865, -2.6777752,  0.4867483,
-2.6289893,  0.5457449, -2.1609758,  0.6018187,
-1.1887621,  0.0987288, -0.5687139, -0.3968770,
-0.4145604,  2.7548500, -0.3624990,  2.8016410,
 2.8932444,  2.8271162, -1.2110615,  2.8368100,
-0.7489007,  2.8403278, -0.7347996,  2.8443446,
-0.7674696,  2.8525817, -0.8211608,  2.8667794,
-0.8951457,  2.8875741, -0.9964725,  2.9151043,
-1.1370333,  2.9493966, -1.3296696,  2.9906237,
-1.5757316,  3.0393281, -1.8467641,  3.0967125,
-2.0925370, -3.1180336, -2.2807403, -3.0339183,
-2.4102189, -2.9247099, -2.4937678, -2.7693739,
-2.5447028, -2.5150560, -2.5731805, -2.0301211,
-2.5864037, -1.2571834, -2.5895109, -0.6710409,
-2.5863011, -0.3646830, -2.5796855, -0.1841889,
-2.5718832, -0.0593851, -2.5643219,  0.0367153,
-2.5569639,  0.1155772, -2.5457213,  0.1825213,
-2.5084499,  0.2402813, -2.1364009,  0.2909304,
 0.2542115,  0.3377919, -2.7791638,  0.3864589,
-2.7273486, -2.7245528, -2.5808614, -2.9996474,
-1.9861909,  2.7346292, -0.9875531,  2.6211449,
-0.5124732,  2.6558720, -0.4634366, -0.4929709,
-0.4441279, -0.9798810, -0.4211925, -1.4305048,
-0.3805689, -1.4908986, -0.6673781, -1.4485153,
-1.3583656, -1.3829688,  1.7864610, -1.3314992,
 1.8353399,  2.4166680,  1.8473191, -1.5957038,
 1.5723110, -1.5455618,  1.9646177, -1.3851276,

#endif //(TEST_INPUT_REAL == 1)
// End of file
