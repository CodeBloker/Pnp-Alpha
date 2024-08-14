﻿/////////////////////////////////////////////////////////////////
//
// Filename          :  MILIM.H
// Revision          :  10.40.0881
//
// Copyright © Matrox Electronic Systems Ltd., 1992-2021.
// All Rights Reserved
//
/////////////////////////////////////////////////////////////////

#ifndef __MILIM_H__
#define __MILIM_H__

/************************************************************************/
/* MimAlloc()                                                           */
/************************************************************************/
#define M_DEINTERLACE_CONTEXT                         1L

#define M_FLAT_FIELD_CONTEXT                          3L
#define M_DEAD_PIXEL_CONTEXT                          4L
#define M_REARRANGE_CONTEXT                           5L
#define M_STAT_MULTIPLE_CONTEXT                       6L
#define M_MATCH_CONTEXT                               7L
#define M_PROJECT_SHAPE_CONTEXT                       8L
#define M_WAVELET_TRANSFORM_CONTEXT                   9L
#define M_WAVELET_TRANSFORM_CUSTOM_CONTEXT            10L
#define M_FIND_ORIENTATION_CONTEXT                    11L
#define M_LOCATE_PEAK_1D_CONTEXT                      12L
#define M_HISTOGRAM_EQUALIZE_ADAPTIVE_CONTEXT         13L
#define M_BINARIZE_ADAPTIVE_CONTEXT                   14L
#define M_BINARIZE_ADAPTIVE_FROM_SEED_CONTEXT         15L
#define M_STATISTICS_CONTEXT                          16L
#define M_STATISTICS_CUMULATIVE_CONTEXT               17L
#define M_AUGMENTATION_CONTEXT                        18L
#define M_LINEAR_FILTER_IIR_CONTEXT                   19L


/************************************************************************/
/* MimGetResult()                                                       */
/************************************************************************/
#define M_VALUE                                       0L
#define M_POSITION_X                                  0x00003400L
#define M_POSITION_Y                                  0x00004400L
#define M_NB_EVENT                                    5L
#define M_NUMBER                                      1009L    // Already defined elsewhere
#define M_TOTAL_NUMBER                                1010L    // Already defined elsewhere
#define M_NUMBER_OF_LEVELS                            1797L
#define M_WAVELET_TYPE                                1802L    // Already defined elsewhere
#define M_TRANSFORMATION_MODE                         1824L    // Already defined elsewhere
#define M_WAVELET_SIZE                                1856L
#define M_WAVELET_DRAW_SIZE_X_WITH_PADDING            1857L
#define M_WAVELET_DRAW_SIZE_Y_WITH_PADDING            1858L
#define M_REAL_PART                                   0x1000L
#define M_IMAGINARY_PART                              0x2000L
#define M_TRANSFORMATION_DOMAIN                       1864L
#define M_ORIGINAL_IMAGE_SIZE_X                       1869L
#define M_ORIGINAL_IMAGE_SIZE_Y                       1870L
#define M_WAVELET_DRAW_SIZE_X                         1871L
#define M_WAVELET_DRAW_SIZE_Y                         1872L
#define M_ALLOCATED_TYPE                              2183L

/************************************************************************/
/* MimGetResult/MimHistogram()                                          */
/************************************************************************/
#define M_CUMULATIVE_VALUE                            1L
#define M_PERCENTAGE                                  2L    // to be used as a complement to M_VALUE and M_CUMULATIVE_VALUE
#define M_PERCENTILE_VALUE                            0x10L // can also be used as a complement to M_GREATER/... with MimBinarize
#define M_PERCENTILE_VALUE_RESULT_SIZE                101L  // 0 to 100%
#define M_HIST_REAL_SIZE                              102L  // Real size of histogram obtain from automatic bin size.
#define M_HIST_VALUE_OFFSET                           103L  // Source value of the first bin.
#define M_HIST_VALUE_RANGE                            104L  // Source value range.

/************************************************************************/
/* MimGetResult/MimAugment()                                          */
/************************************************************************/
#define M_AUG_ROTATION_ANGLE                              3265L
#define M_AUG_TRANSLATION_X                               3266L
#define M_AUG_TRANSLATION_Y                               3267L
#define M_AUG_SCALE_FACTOR                                3268L
#define M_AUG_ASPECT_RATIO                                3269L
#define M_AUG_ASPECT_RATIO_MODE                           3373L
#define M_AUG_FLIP_DIRECTION                              3374L
#define M_AUG_SHEAR_X                                     3270L
#define M_AUG_SHEAR_Y                                     3271L
#define M_AUG_DILATION_NB_ITERATIONS                      3272L
#define M_AUG_EROSION_NB_ITERATIONS                       3273L
#define M_AUG_DILATION_ASYM_NB_ITERATIONS                 3274L
#define M_AUG_DILATION_ASYM_SUBAREA                       3275L
#define M_AUG_EROSION_ASYM_NB_ITERATIONS                  3276L
#define M_AUG_EROSION_ASYM_SUBAREA                        3277L
#define M_AUG_LIGHTING_DIRECTIONAL_ANGLE                  3278L
#define M_AUG_SATURATION_GAIN                             3279L
#define M_AUG_HSV_VALUE_GAIN                              3280L
#define M_AUG_HUE_OFFSET                                  3281L
#define M_AUG_SMOOTH_DERICHE_VALUE                        3282L
#define M_AUG_BLUR_MOTION_SIZE                            3283L
#define M_AUG_BLUR_MOTION_ANGLE                           3284L
#define M_AUG_SHARPEN_DERICHE_VALUE                       3285L
#define M_AUG_SMOOTH_GAUSSIAN_STDDEV                      3286L
#define M_AUG_CROP_TOP_LEFT_X                             3287L
#define M_AUG_CROP_TOP_LEFT_Y                             3288L
#define M_AUG_CROP_BOTTOM_RIGHT_X                         3289L
#define M_AUG_CROP_BOTTOM_RIGHT_Y                         3290L
#define M_AUG_NOISE_SALT_PEPPER_DENSITY                   3375L
#define M_AUG_NOISE_MULTIPLICATIVE_STDDEV                 3376L
#define M_AUG_NOISE_GAUSSIAN_ADDITIVE_STDDEV              3377L
#define M_AUG_INTENSITY_MULTIPLY_VALUE                    3365L
#define M_AUG_INTENSITY_ADD_VALUE                         3366L
#define M_AUG_GAMMA_VALUE_BAND_0                          3367L
#define M_AUG_GAMMA_VALUE_BAND_1                          3369L
#define M_AUG_GAMMA_VALUE_BAND_2                          3371L

#define M_AUG_SEED_USED                                   3423L 


/* Result vectors */
#define M_AUG_OPERATIONS_ENABLED                          3291L
#define M_AUG_OPERATIONS_APPLIED                          3292L
#define M_AUG_OPERATION_RESULT_TYPES                      3293L
#define M_AUG_OPERATION_RESULT_VALUES                     3294L
#define M_AUG_OPERATION_ASSOCIATED_WITH_RESULT_TYPES      3295L
#define M_AUG_REVERSE_TRANSFORMATION_MATRIX               3399L 



/************************************************************************/
/* MimGetResultSingle()                                                 */
/************************************************************************/
#define M_WAVELET_COEFFICIENTS_IMAGE_ID               1850L
#define M_WAVELET_LEVEL_SIZE_X                        1798L
#define M_WAVELET_LEVEL_SIZE_Y                        1799L
#define M_WAVELET_LEVEL_PADDING_OFFSET_X              1866L
#define M_WAVELET_LEVEL_PADDING_OFFSET_Y              1867L
#define M_PREDEFINED                                  1967L
#define M_COMPLEX                                     1968L

#define M_HORIZONTAL_LEVEL_TAG                        0x01000000L
#define M_HORIZONTAL_LEVEL(a)                         (M_HORIZONTAL_LEVEL_TAG + (a))
#define M_VERTICAL_LEVEL_TAG                          0x02000000L
#define M_VERTICAL_LEVEL(a)                           (M_VERTICAL_LEVEL_TAG + (a))
#define M_DIAGONAL_LEVEL_TAG                          0x04000000L
#define M_DIAGONAL_LEVEL(a)                           (M_DIAGONAL_LEVEL_TAG + (a))
#define M_APPROXIMATION                               0x08000000L

/************************************************************************/
/* MimGetResult2d()/MimStatMultiple                                     */
/************************************************************************/
#define M_MAX                                         0x04000000L    //Already defined elsewhere
#define M_MAX_ABS                                     0x00800000L    //Already defined elsewhere
#define M_MEAN                                        0x08000000L    //Already defined elsewhere
#define M_MIN                                         0x02000000L    //Already defined elsewhere
#define M_MIN_ABS                                     0x00200000L    //Already defined elsewhere
#define M_STANDARD_DEVIATION                          0x10000000L    //Already defined elsewhere
#define M_SUM                                         0x00004000L    //Already defined elsewhere
#define M_SUM_ABS                                     0x00000008L    //Already defined elsewhere
#define M_SUM_OF_SQUARES                              0x00000400L    //Already defined elsewhere

/************************************************************************/
/* MimControl()/MimInquire()                                            */
/************************************************************************/
#define M_IN_IM_CONTROL_MIL_ID_RANGE(X)               ((X) == M_DARK_IMAGE || \
                                                       (X) == M_OFFSET_IMAGE || \
                                                       (X) == M_FLAT_IMAGE || \
                                                       (X) == M_DEAD_PIXELS || \
                                                       (X) == M_MODEL_IMAGE || \
                                                       (X) == M_MASK_IMAGE)


// To avoid eventual clashes with M_TYPE_XXX, we must use the mask before checking the value itself.
#define M_MASK_MIM_INQUIRE_TYPE                       0x0001FFFF
#define M_RESULT_SIZE                                 0L
#define M_RESULT_TYPE                                 1L
#define M_DEINTERLACE_TYPE                            2L
#define M_DISCARD_FIELD                               3L
#define M_FIRST_FIELD                                 4L
#define M_MOTION_DETECT_NUM_FRAMES                    5L
#define M_MOTION_DETECT_THRESHOLD                     6L
#define M_MOTION_DETECT_REFERENCE_FRAME               7L
#define M_MOTION_DETECT_OUTPUT                        8L
#define M_SOURCE_FIRST_IMAGE                          9L
#define M_SOURCE_START_IMAGE                          M_SOURCE_FIRST_IMAGE
#if OldDefinesSupport
#define M_EXTENDED_CONTEXT_TYPE                       10L
MIL_DEPRECATED(M_EXTENDED_CONTEXT_TYPE, 1010)
#endif
#define M_EXTENDED_CONTEXT_TYPE_DEPRECATED            10L
#define M_EXTENDED_RESULT_TYPE                        11L
#define M_INTERNAL_CONTEXT_TYPE                       2906L
#define M_ASSOCIATED_CONTEXT_TYPE                     2968L

// Inquire and control types for M_FLAT_FIELD_CONTEXT.
#define M_DARK_IMAGE                                  200L
#define M_OFFSET_IMAGE                                201L
#define M_FLAT_IMAGE                                  202L

#define M_DARK_CONST                                  203L
#define M_OFFSET_CONST                                204L
#define M_FLAT_CONST                                  205L
#define M_GAIN_CONST                                  206L

#define M_DARK_IMAGE_NB_BANDS                         207L
#define M_DARK_IMAGE_WIDTH                            208L
#define M_DARK_IMAGE_HEIGHT                           209L
#define M_DARK_IMAGE_TYPE                             210L

#define M_OFFSET_IMAGE_NB_BANDS                       212L
#define M_OFFSET_IMAGE_WIDTH                          213L
#define M_OFFSET_IMAGE_HEIGHT                         214L
#define M_OFFSET_IMAGE_TYPE                           215L

#define M_FLAT_IMAGE_NB_BANDS                         217L
#define M_FLAT_IMAGE_WIDTH                            218L
#define M_FLAT_IMAGE_HEIGHT                           219L
#define M_FLAT_IMAGE_TYPE                             220L

#define M_EFFECTIVE_GAIN_CONST                        221L

#define M_INVALID_CONST                               0x40000000L

// Inquire and control types for M_REARRANGE_CONTEXT.
#define M_X_SOURCE                                    300L
#define M_Y_SOURCE                                    301L
#define M_XY_SOURCE                                   302L
#define M_X_DESTINATION                               303L
#define M_Y_DESTINATION                               304L
#define M_XY_DESTINATION                              305L
#define M_X_SIZE                                      306L
#define M_Y_SIZE                                      307L
#define M_XY_SIZE                                     308L

#define M_X_SOURCE_ARRAY_SIZE                         309L
#define M_Y_SOURCE_ARRAY_SIZE                         310L
#define M_XY_SOURCE_ARRAY_SIZE                        311L
#define M_X_DESTINATION_ARRAY_SIZE                    312L
#define M_Y_DESTINATION_ARRAY_SIZE                    313L
#define M_XY_DESTINATION_ARRAY_SIZE                   314L
#define M_X_SIZE_ARRAY_SIZE                           315L
#define M_Y_SIZE_ARRAY_SIZE                           316L
#define M_XY_SIZE_ARRAY_SIZE                          317L

// Inquire and control types for M_DEAD_PIXEL_CONTEXT.
#define M_DEAD_PIXELS                                 80L
#define M_X_DEAD_PIXELS                               81L
#define M_Y_DEAD_PIXELS                               82L
#define M_XY_DEAD_PIXELS                              83L

#define M_X_DEAD_PIXELS_ARRAY_SIZE                    84L
#define M_Y_DEAD_PIXELS_ARRAY_SIZE                    85L
#define M_XY_DEAD_PIXELS_ARRAY_SIZE                   86L
#define M_DEAD_PIXELS_IMAGE_NB_BANDS                  87L      //Inquire only
#define M_DEAD_PIXELS_IMAGE_WIDTH                     88L      //Inquire only
#define M_DEAD_PIXELS_IMAGE_HEIGHT                    89L      //Inquire only
#define M_DEAD_PIXELS_IMAGE_TYPE                      91L      //Inquire only
#define M_DEAD_PIXELS_IMAGE_ATTRIBUTE                 92L      //Inquire only


// Inquire and control types for M_STAT_MULTIPLE_CONTEXT.
#define M_TYPE                                        1008L    //Already defined elsewhere
#define M_SIZE_X                                      1536L    //Already defined elsewhere
#define M_SIZE_Y                                      1537L    //Already defined elsewhere
#define M_2D                                          90L
//See MimStat for M_TYPE possible values.

// Inquire and control types for M_MATCH_CONTEXT.
#define M_MODEL_IMAGE                                 1019L
#define M_MASK_IMAGE                                  1020L       //Already defined in milreg.h
#define M_MAX_SCORE                                   100L
#define M_SCORE_TYPE                                  37L         //Already defined elsewhere
#define M_MODEL_STEP                                  33L         //Already defined elsewhere
#define M_MODE                                        103L        //Already defined elsewhere
#define M_CORRELATE_NORMALIZED                        1L          //Mode value.
#define M_CORRELATE                                   2L          //Mode value.
#define M_ABS_SUM_OF_DIFFERENCES                      3L          //Mode value.
#define M_MAX_DEPTH                                   MIL_MAKE_CONST(0xFFFFFFFF, 0x00000000FFFFFFFF)  //M_MAX_SCORE value.
#define M_NORM                                        4000L       //Already defined elsewhere, ScoreType value.
#define M_SQR_NORM                                    4001L       //Already defined elsewhere, ScoreType value.
#define M_NORM_CLIP                                   4002L       //ScoreType value.
#define M_NORM_CLIP_SQR                               4003L       //ScoreType value.

#define M_MODEL_IMAGE_NB_BANDS                        105L        //Inquire only
#define M_MODEL_IMAGE_WIDTH                           106L        //Inquire only
#define M_MODEL_IMAGE_HEIGHT                          107L        //Inquire only
#define M_MODEL_IMAGE_TYPE                            108L        //Inquire only
#define M_MODEL_IMAGE_ATTRIBUTE                       109L        //Inquire only

#define M_MASK_IMAGE_NB_BANDS                         110L        //Inquire only
#define M_MASK_IMAGE_WIDTH                            111L        //Inquire only
#define M_MASK_IMAGE_HEIGHT                           112L        //Inquire only
#define M_MASK_IMAGE_TYPE                             113L        //Inquire only
#define M_MASK_IMAGE_ATTRIBUTE                        114L        //Inquire only


// Inquire and control types for M_WAVELET_TRANSFORM_CONTEXT.
#define M_WAVELET_TYPE                                1802L
#define M_CUSTOM                                      2           //WaveletType value
#define M_DAUBECHIES_1                                3L          //WaveletType value
#define M_DAUBECHIES_2                                4L          //WaveletType value
#define M_DAUBECHIES_3                                5L          //WaveletType value
#define M_DAUBECHIES_4                                6L          //WaveletType value
#define M_DAUBECHIES_5                                7L          //WaveletType value
#define M_DAUBECHIES_6                                8L          //WaveletType value
#define M_DAUBECHIES_7                                9L          //WaveletType value
#define M_DAUBECHIES_8                                10L         //WaveletType value
#define M_DAUBECHIES_3_COMPLEX                        11L         //WaveletType value
#define M_DAUBECHIES_5_COMPLEX                        12L         //WaveletType value
#define M_DAUBECHIES_7_COMPLEX                        13L         //WaveletType value
#define M_SYMLET_1                                    14L         //WaveletType value
#define M_SYMLET_2                                    15L         //WaveletType value
#define M_SYMLET_3                                    16L         //WaveletType value
#define M_SYMLET_4                                    17L         //WaveletType value
#define M_SYMLET_5                                    18L         //WaveletType value
#define M_SYMLET_6                                    19L         //WaveletType value
#define M_SYMLET_7                                    20L         //WaveletType value
#define M_SYMLET_8                                    21L         //WaveletType value
#define M_HAAR                                        1L          //WaveletType value
#define M_TRANSFORMATION_MODE                         1824L
#define M_DYADIC                                      1825L       //DecompositionMode value
#define M_UNDECIMATED                                 1826L       //DecompositionMode value
#define M_FILTER_FORWARD_LOW_PASS_ID                  1820L       // MimWaveletSetFilter
#define M_FILTER_REVERSE_LOW_PASS_ID                  1821L       // MimWaveletSetFilter
#define M_FILTER_FORWARD_HIGH_PASS_ID                 1822L       // MimWaveletSetFilter
#define M_FILTER_REVERSE_HIGH_PASS_ID                 1823L       // MimWaveletSetFilter
#define M_WAVELET_VALIDITY                            1827L       // MimInquire
#define M_WAVELET_CONTEXT_TYPE                        1828L       // MimInquire
#define M_REAL_PART                                   0x1000L     // MimInquire
#define M_IMAGINARY_PART                              0x2000L     // MimInquire

// Inquire and control types for M_FIND_ORIENTATION_CONTEXT.
#define M_INTERPOLATION_MODE                          3018L       //Defined in mildisplay.h
#define M_FREQUENCY_CUTOFF_RATIO_LOW                  1830L        //Low frequency cut off
#define M_FREQUENCY_CUTOFF_RATIO_HIGH                 1831L        //High frequency cut off
#define M_CLIP_CENTER                                 106L        //Mode value
#define M_RESIZE_DOWN                                 107L        //Mode value
#define M_RESIZE_UP                                   108L        //Mode value
#define M_CENTERED_WINDOW                             (M_PSEUDO_ID | 0x40)
#define M_SCORE                                       0x00001400L  //Defined in milgab.h
#define M_BORDER_ATTENUATION                          109L

// Inquire and control types for M_HISTOGRAM_EQUALIZE_ADAPTIVE_CONTEXT.
#define M_NUMBER_OF_TILES_X                           250L        // Number of tiles in X
#define M_NUMBER_OF_TILES_Y                           251L        // Number of tiles in Y
#define M_CLIP_LIMIT                                  252L        // Mormalized clip limit.
#define M_HIST_SIZE                                   253L        // Number of histogram bins.
#define M_ACCORDING_TO_SOURCE                         -1L         // Number of bin determine from source range.
#define M_OPERATION                                   M_METHOD    // Already defined elsewhere. Histogram equalization distrition.
#define M_UNIFORM                                     1           // Already defined elsewhere
#define M_EXPONENTIAL                                 2           // Already defined elsewhere
#define M_RAYLEIGH                                    3           // Already defined elsewhere
#define M_HYPER_CUBE_ROOT                             4           // Already defined elsewhere
#define M_HYPER_LOG                                   5           // Already defined elsewhere
#define M_ALPHA_VALUE                                 5278L       // Already defined elsewhere


// Inquire and control types for M_LOCATE_PEAK_1D_CONTEXT.
#define M_SCAN_LANE_DIRECTION                         1
#define M_PEAK_VALUE_MODE                             2
#define M_PEAK_INTENSITY_MODE                         3
#define M_NUMBER_OF_PEAKS                             4
#define M_SORT_CRITERION                              5
#define M_PEAK_WIDTH_NOMINAL                          6
#define M_PEAK_WIDTH_DELTA                            7
#define M_FRAME_SIZE                                  8
#define M_FULL_SIZE                                   0L          // Already defined in mildisplay.h
#define M_SELECT_PEAK(a,b)  ((MIL_INT64)((MIL_UINT64)(a) << 32 | (MIL_UINT64)(b)))

//Common to many objects.
#define M_MODE                                        103L

// Already defined in another header file.
#define M_LINES                                       0x00000080L

#define M_RECTS                                       0x00000100L

#define M_AVERAGE                                     0x00000020L
#define M_DISCARD                                     0x00000021L
#define M_BOB                                         0x00000022L
#define M_ADAPTIVE_AVERAGE                            0x00000023L
#define M_ADAPTIVE_DISCARD                            0x00000024L
#define M_ADAPTIVE_BOB                                0x00000025L
#define M_ADAPTATIVE_AVERAGE                          M_ADAPTIVE_AVERAGE
#define M_ADAPTATIVE_DISCARD                          M_ADAPTIVE_DISCARD
#define M_ADAPTATIVE_BOB                              M_ADAPTIVE_BOB
#define M_ODD_FIELD                                   1L
#define M_EVEN_FIELD                                  2L
#define M_FIRST_FRAME                                 0x40000001L
#define M_CENTER_FRAME                                0x40000002L
#define M_LAST_FRAME                                  0x40000003L
#define M_RESULT_OUTPUT_UNITS 	                     1300L
#define M_NUMBER_OF_FRAMES                            1080L

// Control values for M_RESULT_OUTPUT_UNITS
#define M_PIXEL                              0x1000L
#define M_WORLD                              0x2000L
#define M_ACCORDING_TO_CALIBRATION             1301L

// Control for M_HIST_LIST
#define  M_HIST_BIN_SIZE_MODE                            400L        // ControlType to specify binning mode.
#define  M_REGULAR                                       0x00020000L // Define elsewhere. Default mode used before, with no binning and
// just ignore values that don't fit in the size of the result.
#define  M_FIT_SRC_RANGE                                 0x01        // Use the size as the number of bin and a simple algo for indexing.
#define  M_FIT_SRC_DATA                                  0x02        // Use the size as the number of bin and a simple algo for indexing.
#define  M_FREEDMAN                                      0x03        // MIL automaticly determine optimal bin size/number of bin using Freedman algorithm.
#define  M_HIST_SMOOTHING_ITERATIONS                     401L        // Number of smoothing pass to do as post processing.

// Inquire and control types for M_LINEAR_FILTER_IIR_CONTEXT.
#define M_FILTER_TYPE                           1046L                               // Already defined in miledge.h, milmeas.h
#define M_SHEN                                  0x802L                              // FilterType value.
#define M_DERICHE                               M_ID_OFFSET_OF_DEFAULT_KERNEL + 10L // FilterType value. Already defined in miledge.h
#define M_VLIET                                 0x803L                              // FilterType value.

#define M_SMOOTHNESS                            108L                                // Already defined in    milmod.h, milmeas.h
#define M_FILTER_SMOOTHNESS                     M_SMOOTHNESS                        // Already defined in    milmeas.h

#define M_FILTER_SMOOTHNESS_TYPE                2842L
#define M_NORMALIZED                            0x00000002L                         // Smoothness type value.
#define M_NATIVE                                0x00000003L                         // Smoothness type value.

#define M_FILTER_RESPONSE_TYPE                  2843L
#define M_SLOPE                                 2844L                               // Response type value.
#define M_STEP                                  2845L                               // Response type value.

#define M_FILTER_ASPECT_RATIO                   2846L

#define M_FILTER_DEFAULT_SHARPEN_PARAM          4056L


/************************************************************************/
/* MimFindExtreme()                                                     */
/************************************************************************/
#define M_MIN_VALUE                                   MAKE_INT64(0x0000010000000000)
#define M_MAX_VALUE                                   MAKE_INT64(0x0000020000000000)
#define M_MIN_ABS_VALUE                               4L
#define M_MAX_ABS_VALUE                               8L

/************************************************************************/
/* MimStat()                                                            */
/************************************************************************/
#define M_MIN_ABS                                     0x00200000L    //Already defined elsewhere
#define M_MAX_ABS                                     0x00800000L    //Already defined elsewhere
#define M_SUM_ABS                                     0x00000008L    //Already defined elsewhere
#define M_SUM_OF_SQUARES                              0x00000400L    //Already defined elsewhere
#define M_SUM                                         0x00004000L    //Already defined in milocr.h
#define M_MEAN                                        0x08000000L    //Already defined in milmeas.h
#define M_STANDARD_DEVIATION                          0x10000000L    //Already defined in milmeas.h
#define M_NUMBER                                      1009L          // Already defined elsewhere 0x000003F1
#define M_ANGULAR_DATA_MEAN                           0x00000004L
#define M_ANGULAR_DATA_COHERENCE                      0x00000800L
#define M_ORIENTATION_DATA_MEAN                       0x00001000L
#define M_ORIENTATION_DATA_COHERENCE                  0x00002000L

/************************************************************************/
/* MimStatCalculate()                                                            */
/************************************************************************/
#define M_STAT_TYPE                                   2149
#define M_GLCM_STAT_TYPE                              2150
#define M_GLCM_PAIR_OFFSET_X                          2151
#define M_GLCM_PAIR_OFFSET_Y                          2152
#define M_STEP_SIZE_X                                 2153
#define M_STEP_SIZE_Y                                 2160
#define M_GLCM_QUANTIFICATION                         2161
#define M_STAT_GLCM_DISSIMILARITY                     2162
#define M_STAT_GLCM_ENERGY                            2163
#define M_STAT_GLCM_ENTROPY                           2164
#define M_STAT_GLCM_HOMOGENEITY                       2165
#define M_CONDITION                                   2167
#define M_COND_LOW                                    2168
#define M_COND_HIGH                                   2172
#define M_STAT_GLCM_CORRELATION                       2173
#define M_STAT_GLCM_CONTRAST                          2174

/* These defines preserve the values of their non-prefixed counterpart where possible. */
#define M_STAT_MIN                                         2502
#define M_STAT_MAX                                         2503
#define M_STAT_MIN_ABS                                     2504
#define M_STAT_MAX_ABS                                     2505
#define M_STAT_SUM_ABS                                     2506
#define M_STAT_SUM_OF_SQUARES                              2507
#define M_STAT_SUM                                         2508
#define M_STAT_MEAN                                        2509
#define M_STAT_STANDARD_DEVIATION                          2510
#define M_STAT_NUMBER                                      1009L       // Same as M_NUMBER
#define M_STAT_ANGULAR_DATA_MEAN                           2511
#define M_STAT_ANGULAR_DATA_COHERENCE                      2512
#define M_STAT_ORIENTATION_DATA_MEAN                       2513
#define M_STAT_ORIENTATION_DATA_COHERENCE                  2514

/************************************************************************/
/* MimArith()                                                           */
/************************************************************************/
#define M_CONSTANT                                    0x8000L
#define M_FIXED_POINT                                 0x00004000L
#define M_FLOAT_PROC                                  0x40000000L
#define M_LOGICAL                                     0x08000000L
#define M_SOURCE_VALUE                                0x00010000L
#define M_ADD                                         0x0000L
#define M_ADD_CONST                                   (M_ADD | M_CONSTANT)
#define M_SUB                                         0x0001L
#define M_SUB_CONST                                   (M_SUB | M_CONSTANT)
#define M_NEG_SUB                                     0x000AL
#define M_CONST_SUB                                   (M_NEG_SUB | M_CONSTANT)
#define M_SUB_ABS                                     0x0011L
#define M_SUB_CONST_ABS                               (M_SUB_ABS | M_CONSTANT)
#define M_MIN                                         0x02000000L
#define M_MIN_CONST                                   (M_MIN | M_CONSTANT)
#define M_MAX                                         0x04000000L
#define M_MAX_CONST                                   (M_MAX | M_CONSTANT)
#define M_OR                                          0x0016L
#define M_OR_CONST                                    (M_OR  | M_CONSTANT)
#define M_AND                                         0x0017L
#define M_AND_CONST                                   (M_AND | M_CONSTANT)
#define M_XOR                                         0x0018L
#define M_XOR_CONST                                   (M_XOR | M_CONSTANT)
#define M_NOR                                         0x0019L
#define M_NOR_CONST                                   (M_NOR | M_CONSTANT)
#define M_NAND                                        0x001AL
#define M_NAND_CONST                                  (M_NAND | M_CONSTANT)
#define M_XNOR                                        0x001BL
#define M_XNOR_CONST                                  (M_XNOR | M_CONSTANT)
#define M_NOT                                         0x0014L
#define M_NEG                                         0x0023L
#define M_ABS                                         0x000CL
#define M_PASS                                        0x0002L
#define M_CONST_PASS                                  (M_PASS | M_CONSTANT)
#define M_MULT                                        0x0100L
#define M_MULT_CONST                                  (M_MULT | M_CONSTANT)
#define M_DIV                                         0x0101L
#define M_DIV_CONST                                   (M_DIV | M_CONSTANT)
#define M_INV_DIV                                     0x0102L
#define M_CONST_DIV                                   (M_INV_DIV | M_CONSTANT)
#define M_SQRT                                        0x0103L
#define M_SQUARE_ROOT                                 M_SQRT
#define M_SQUARE                                      0x00000020L // Already defined in milmod.h
#define M_CUBE                                        0x0104L
#define M_LN                                          0x0105L
#define M_LOG10                                       0x0106L
#define M_LOG2                                        0x0107L
#define M_EXP_CONST                                   0x0108L
#define M_CONST_EXP                                   0x0109L
#define M_EXP                                         0x010AL     // Also defined in mil.h for MgenLutFunction
#define M_LOG_CONST                                   0x010BL
#define M_CONST_LOG                                   0x010CL
#define M_LOG                                         0x010DL     // Also defined in mil.h for MgenLutFunction
#define M_ATAN2                                       0x010EL
#define M_INTEGRAL                                    0x010FL
#define M_AVG                                         0x0110L
#define M_ABS_SUB                                     0x0111L
#define M_MIN_ABS                                     0x00200000L // Already defined elsewhere
#define M_MAX_ABS                                     0x00800000L // Already defined elsewhere

// Note that those are valid only with M_LOGICAL, avoiding conflict with other flags.
#define M_EQUAL                                       3L
#define M_NOT_EQUAL                                   4L
#define M_GREATER                                     5L
#define M_LESS                                        6L
#define M_GREATER_OR_EQUAL                            7L
#define M_LESS_OR_EQUAL                               8L

#define M_EQUAL_CONST                                 (M_EQUAL | M_CONSTANT)
#define M_NOT_EQUAL_CONST                             (M_NOT_EQUAL | M_CONSTANT)
#define M_GREATER_CONST                               (M_GREATER | M_CONSTANT)
#define M_LESS_CONST                                  (M_LESS | M_CONSTANT)
#define M_GREATER_OR_EQUAL_CONST                      (M_GREATER_OR_EQUAL | M_CONSTANT)
#define M_LESS_OR_EQUAL_CONST                         (M_LESS_OR_EQUAL | M_CONSTANT)

/************************************************************************/
/* MimArithMultiple()                                                   */
/************************************************************************/
#define M_OFFSET_GAIN                                 0x0000L
#define M_WEIGHTED_AVERAGE                            0x0001L
#define M_MULTIPLY_ACCUMULATE_1                       0x0002L
#define M_MULTIPLY_ACCUMULATE_2                       0x0004L

/************************************************************************/
/* MimFlip()                                                            */
/************************************************************************/
#define M_FLIP_VERTICAL                               1L
#define M_FLIP_HORIZONTAL                             2L

/************************************************************************/
/* MimBinarize(), MimClip(), MimLocateEvent(), MimStat()                */
/* Some of these defines are also define in milutil.h                   */
/************************************************************************/
#define M_IN_RANGE                                    1L
#define M_OUT_RANGE                                   2L
#define M_EQUAL                                       3L
#define M_NOT_EQUAL                                   4L
#define M_GREATER                                     5L
#define M_LESS                                        6L
#define M_GREATER_OR_EQUAL                            7L
#define M_LESS_OR_EQUAL                               8L
#define M_MASK                                        0x00001000L
#define M_ALL                                         0x40000000L

/************************************************************************/
/* These flags are specific to MimLocateEvent()                         */
/************************************************************************/

//The encoding for extremum mode is done on 11 bits, with the 8 lower bits
//indicating we use > or >= (0 or 1) for a specific neighbor, the bit 8 is used
//to select minimum or maximum (0 or 1) and bit 9 for the special case strickly
//greater than any one and greater or equal to all others. Bit 10 is indicating
//that one mode is selected. Note that for the neighbor position, we use the
//same convention than MimConnectMap.
// n3 n2 n1
// n4 X  n0
// n5 n6 n7
#define M_LOCATE_EVENT_EXTREMUM_MODE_SHIFT      17L                                             // =utilities=
#define M_LOCAL_MAX_NOT_STRICT                  (0x05FFL << M_LOCATE_EVENT_EXTREMUM_MODE_SHIFT) //Greater or equal to all
#define M_LOCAL_MAX_STRICT_MEDIUM               (0x0587L << M_LOCATE_EVENT_EXTREMUM_MODE_SHIFT) //Greater right
#define M_LOCAL_MIN_NOT_STRICT                  (0x04FFL << M_LOCATE_EVENT_EXTREMUM_MODE_SHIFT) //Less or equal to all
#define M_LOCAL_MIN_STRICT_MEDIUM               (0x0487L << M_LOCATE_EVENT_EXTREMUM_MODE_SHIFT) //Less right

/************************************************************************/
/* MimBinarize()                                                        */
/************************************************************************/
// reserve bits 4-7 to the binarization method
#define M_BINARIZATION_METHOD_MASK                    0x0F0L
//#define M_PERCENTILE_VALUE                            0x10L // already defined at the beginning of the file
#define M_TRIANGLE_BISECTION_DARK                     0x20L
#define M_TRIANGLE_BISECTION_BRIGHT                   0x30L
#define M_BIMODAL                                     0x40L
#define M_FIXED                                       0x50L
#define M_DISCRETE_RANGE                              0x1000L
#define M_RETURN_VALUE_AS_FLOAT_IN_INT                0x2000L

/************************************************************************/
/* MimConvolve()                                                        */
/************************************************************************/
#define M_ID_OFFSET_OF_DEFAULT_KERNEL                 (0x00100000L|M_PSEUDO_ID)
#define M_ID_OFFSET_OF_EDGE_DETECTVAR                 (0x00100100L|M_PSEUDO_ID)

#define M_SMOOTH                                      (M_ID_OFFSET_OF_DEFAULT_KERNEL +  0L)
#define M_LAPLACIAN_EDGE                              (M_ID_OFFSET_OF_DEFAULT_KERNEL +  1L)
#define M_LAPLACIAN_EDGE2                             (M_ID_OFFSET_OF_DEFAULT_KERNEL +  2L)
#define M_SHARPEN                                     (M_ID_OFFSET_OF_DEFAULT_KERNEL +  3L)
#define M_SHARPEN2                                    (M_ID_OFFSET_OF_DEFAULT_KERNEL +  4L)
#define M_HORIZ_EDGE                                  (M_ID_OFFSET_OF_DEFAULT_KERNEL +  5L)
#define M_VERT_EDGE                                   (M_ID_OFFSET_OF_DEFAULT_KERNEL +  6L)
#define M_EDGE_DETECT                                 (M_ID_OFFSET_OF_DEFAULT_KERNEL +  7L)
#define M_EDGE_DETECT2                                (M_ID_OFFSET_OF_DEFAULT_KERNEL +  8L)
#define M_EDGE_DETECT_SQR                             (M_ID_OFFSET_OF_DEFAULT_KERNEL +  9L)
#define M_FIRST_DERIVATIVE_X                          (M_ID_OFFSET_OF_DEFAULT_KERNEL + 10L)
#define M_FIRST_DERIVATIVE_Y                          (M_ID_OFFSET_OF_DEFAULT_KERNEL + 11L)
#define M_SECOND_DERIVATIVE_X                         (M_ID_OFFSET_OF_DEFAULT_KERNEL + 12L)
#define M_SECOND_DERIVATIVE_Y                         (M_ID_OFFSET_OF_DEFAULT_KERNEL + 13L)
#define M_SECOND_DERIVATIVE_XY                        (M_ID_OFFSET_OF_DEFAULT_KERNEL + 14L)
#define M_HORIZONTAL_EDGE_SOBEL                       (M_ID_OFFSET_OF_DEFAULT_KERNEL + 15L)
#define M_VERTICAL_EDGE_SOBEL                         (M_ID_OFFSET_OF_DEFAULT_KERNEL + 16L)
#define M_HORIZONTAL_EDGE_PREWITT                     (M_ID_OFFSET_OF_DEFAULT_KERNEL + 17L)
#define M_VERTICAL_EDGE_PREWITT                       (M_ID_OFFSET_OF_DEFAULT_KERNEL + 18L)
#define M_SOBEL_X                                     (M_ID_OFFSET_OF_DEFAULT_KERNEL + 19L)
#define M_SOBEL_Y                                     (M_ID_OFFSET_OF_DEFAULT_KERNEL + 20L)
#define M_PREWITT_X                                   (M_ID_OFFSET_OF_DEFAULT_KERNEL + 21L)
#define M_PREWITT_Y                                   (M_ID_OFFSET_OF_DEFAULT_KERNEL + 22L)
#define M_LAPLACIAN_ISO_8                             (M_ID_OFFSET_OF_DEFAULT_KERNEL + 23L)
#define M_EDGE_DETECTVAR(Val)                         (M_ID_OFFSET_OF_EDGE_DETECTVAR + Val)

#define M_EDGE_DETECT_SOBEL_FAST                      M_EDGE_DETECT
#define M_EDGE_DETECT_PREWITT_FAST                    M_EDGE_DETECT2
#define M_LAPLACIAN_4                                 M_LAPLACIAN_EDGE
#define M_LAPLACIAN_8                                 M_LAPLACIAN_EDGE2
#define M_SHARPEN_4                                   M_SHARPEN2
#define M_SHARPEN_8                                   M_SHARPEN

#define M_OVERSCAN_ENABLE                             0x00008000L
#define M_OVERSCAN_DISABLE                            0x00080000L
#define M_OVERSCAN_FAST                               0x00040000L

#if OldDefinesSupport

#define M_SHEN_PREDEFINED_KERNEL                      (0x10000000L|M_ID_OFFSET_OF_DEFAULT_KERNEL)                                   
#define M_DERICHE_PREDEFINED_KERNEL                   (0x20000000L|M_ID_OFFSET_OF_DEFAULT_KERNEL)                                   
#define M_SHEN_PREDEFINED_KERNEL_INVALID_TYPE         (0x01000000L|M_SHEN_PREDEFINED_KERNEL)                                        
#define M_SHEN_PREDEFINED_KERNEL_INVALID_FACTOR       (0x02000000L|M_SHEN_PREDEFINED_KERNEL)                                        
#define M_DERICHE_PREDEFINED_KERNEL_INVALID_TYPE      (0x01000000L|M_DERICHE_PREDEFINED_KERNEL)                                     
#define M_DERICHE_PREDEFINED_KERNEL_INVALID_FACTOR    (0x02000000L|M_DERICHE_PREDEFINED_KERNEL)                                     
#define M_IS_SHEN_PREDEFINED_KERNEL(KernelId)         (((KernelId) & M_SHEN_PREDEFINED_KERNEL) == M_SHEN_PREDEFINED_KERNEL)         
#define M_IS_DERICHE_PREDEFINED_KERNEL(KernelId)      (((KernelId) & M_DERICHE_PREDEFINED_KERNEL) == M_DERICHE_PREDEFINED_KERNEL)

#define M_SHEN_FILTER(FilterOperation, FilterSmoothness)  (((((FilterOperation) & M_ID_OFFSET_OF_DEFAULT_KERNEL) != M_ID_OFFSET_OF_DEFAULT_KERNEL) && (FilterOperation!=M_DEFAULT))   ? M_SHEN_PREDEFINED_KERNEL_INVALID_TYPE :   \
   ((((FilterOperation) & (~(M_ID_OFFSET_OF_DEFAULT_KERNEL | 0xFF))) != 0) && (FilterOperation!=M_DEFAULT))                    ? M_SHEN_PREDEFINED_KERNEL_INVALID_TYPE :   \
   (((((FilterSmoothness) < 0) || ((FilterSmoothness) > 100))) && (FilterSmoothness!=M_DEFAULT))                               ? M_SHEN_PREDEFINED_KERNEL_INVALID_FACTOR : \
   M_SHEN_PREDEFINED_KERNEL | ((FilterOperation==M_DEFAULT) ? 0x80 : FilterOperation) | ((FilterSmoothness==M_DEFAULT)?(0xFF00):(((long) FilterSmoothness) << 8))          )
MIL_DEPRECATED(M_SHEN_FILTER, 1040)       // Use new M_LINEAR_FILTER_IIR_CONTEXT with MimConvolve or MimDerivative instead.

#define M_DERICHE_FILTER(FilterOperation, FilterSmoothness) (((((FilterOperation) & M_ID_OFFSET_OF_DEFAULT_KERNEL) != M_ID_OFFSET_OF_DEFAULT_KERNEL) && (FilterOperation!=M_DEFAULT)) ? M_DERICHE_PREDEFINED_KERNEL_INVALID_TYPE :   \
   ((((FilterOperation) & (~(M_ID_OFFSET_OF_DEFAULT_KERNEL | 0xFF))) != 0) && (FilterOperation!=M_DEFAULT))                  ? M_DERICHE_PREDEFINED_KERNEL_INVALID_TYPE :   \
   (((((FilterSmoothness) < 0) || ((FilterSmoothness) > 100))) && (FilterSmoothness!=M_DEFAULT))                             ? M_DERICHE_PREDEFINED_KERNEL_INVALID_FACTOR : \
   M_DERICHE_PREDEFINED_KERNEL | ((FilterOperation==M_DEFAULT) ? 0x80 : FilterOperation) | ((FilterSmoothness==M_DEFAULT)?(0xFF00):(((long) FilterSmoothness) << 8))        )
MIL_DEPRECATED(M_DERICHE_FILTER, 1040)    // Use new M_LINEAR_FILTER_IIR_CONTEXT with MimConvolve or MimDerivative instead.
#endif

/************************************************************************/
/* MimDifferential()                                                    */
/************************************************************************/
#define  M_GAUSSIAN_CURVATURE                         2691L             // Already defined.
#define  M_GRADIENT                                   3306L
#define  M_GRADIENT_SQR                               3307L
#define  M_HESSIAN                                    3308L
#define  M_JACOBIAN                                   3309L
#define  M_LAPLACIAN                                  3310L
#define  M_MEAN_CURVATURE                             2692L             // Already defined.
#define  M_SHARPEN                                    (M_ID_OFFSET_OF_DEFAULT_KERNEL +  3L)  // Already defined for MimConvolve.


/************************************************************************/
/* MimEdgeDetect()                                                      */
/************************************************************************/
#if M_MIL_LITE || MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION
#define M_SOBEL                                       M_EDGE_DETECT_SOBEL_FAST
#endif
#define M_NOT_WRITE_ANGLE                             1L
#define M_NOT_WRITE_INT                               2L
#define M_FAST_ANGLE                                  4L
#define M_FAST_GRADIENT                               8L
#define M_FAST_EDGE_DETECT                            (M_FAST_ANGLE + M_FAST_GRADIENT)
#define M_REGULAR_ANGLE                               16L
#define M_REGULAR_GRADIENT                            64L
#define M_REGULAR_EDGE_DETECT                         (M_REGULAR_ANGLE + M_REGULAR_GRADIENT)
#define M_USE_RESERVED_ANGLE_VALUE                    128L

/************************************************************************/
/* MimRank()                                                            */
/************************************************************************/
#define M_MEDIAN                                      0x10000L
#define M_3X3_RECT                                    (M_ID_OFFSET_OF_DEFAULT_KERNEL + 20L)
#define M_3X3_CROSS                                   (M_ID_OFFSET_OF_DEFAULT_KERNEL + 21L)
#define M_5X5_RECT                                    (M_ID_OFFSET_OF_DEFAULT_KERNEL + 30L)

/************************************************************************/
/* MimMorphic(), ...                                                    */
/************************************************************************/
#define M_ERODE                                       1L
#define M_DILATE                                      2L
#define M_THIN                                        3L
#define M_THICK                                       4L
#define M_HIT_OR_MISS                                 5L
#define M_MATCH                                       6L
#define M_AREA_OPEN                                   7L
#define M_AREA_CLOSE                                  8L
#define M_TOP_HAT                                     9L
#define M_BOTTOM_HAT                                 10L
#define M_LEVEL                                      11L

// These flags are already defined elsewhere. We use the same values here.
#define M_OPEN                                       0x00000010L
#define M_CLOSE                                      0x00000020L

/************************************************************************/
/* MimErode()                                                           */
/************************************************************************/
#define M_BINARY_ULTIMATE                             1L
#define M_BINARY_ULTIMATE_ACCUMULATE                  2460L

/************************************************************************/
/* MimThin()                                                            */
/************************************************************************/
#define M_TO_SKELETON                                -1L
#define M_BINARY2                                     1L
#define M_BINARY3                                     2L
#define M_OVERSCAN_REPLACE_MAX                        0x10
#define M_OVERSCAN_REPLACE_MIN                        0x20

/************************************************************************/
/* MimThick()                                                           */
/************************************************************************/
#define M_TO_IDEMPOTENCE                              M_TO_SKELETON

/************************************************************************/
/* MimDistance()                                                        */
/************************************************************************/
#define M_CHAMFER_3_4                                 0x01
#define M_CITY_BLOCK                                  0x02
#define M_CHESSBOARD                                  0x04
#define M_FORWARD                                     0x01
#define M_BACKWARD                                    0x02
#define M_OVERSCAN_TO_DO                              0x04
#define M_BOTH                                        0x07

/************************************************************************/
/* MimWatershed()                                                        */
/************************************************************************/
#define M_WATERSHED                                   0x0001
#define M_BASIN                                       0x0002
#define M_MINIMA_FILL                                 0x0004
#define M_MAXIMA_FILL                                 0x0008

#define M_4_CONNECTED                                 0x00000010L
#define M_8_CONNECTED                                 0x00000020L
#define M_REGULAR                                     0x00020000L
#define M_STRAIGHT_WATERSHED                          0x0080
#define M_SKIP_LAST_LEVEL                             0x0100
#define M_FILL_SOURCE                                 0x0200
#define M_LABELLED_MARKER                             0x0400
#define M_LABELED_MARKER                              M_LABELLED_MARKER

#define M_METHOD_1                                    0x1000
#define M_METHOD_2                                    0x2000

#define M_BASIN_4_CONNECTED                           0x4000
#define M_BASIN_8_CONNECTED                           0x8000

/************************************************************************/
/* MimProject()                                                         */
/************************************************************************/
#define M_0_DEGREE                                      0.0
#define M_90_DEGREE                                    90.0
#define M_180_DEGREE                                  180.0
#define M_270_DEGREE                                  270.0

/************************************************************************/
/* MimResize(), MimTranslate() and MimRotate()                          */
/************************************************************************/
#define M_OVERSCAN_DISABLE                            0x00080000L
#define M_OVERSCAN_ENABLE                             0x00008000L
#define M_OVERSCAN_FAST                               0x00040000L
#define M_INTERPOLATE                                 0x00000004L
#define M_BILINEAR                                    0x00000008L
#define M_BICUBIC                                     0x00000010L
#define M_AVERAGE                                     0x00000020L
#define M_NEAREST_NEIGHBOR                            0x00000040L
#define M_OVERSCAN_CLEAR                              0x00000080L
#define M_FIT_ALL_ANGLE                               0x00000100L
#define M_BINARY                                      0x00001000L
#define M_FAST                                        0x00002000L
#define M_REGULAR                                     0x00020000L

/************************************************************************/
/* MimResize                                                            */
/************************************************************************/
#define M_FILL_DESTINATION                            -1 // DO NOT MODIFY, WITHOUT CODE MODIFICATION

/************************************************************************/
/* MimHistogramEqualize()                                               */
/************************************************************************/
#define M_UNIFORM                                     1
#define M_EXPONENTIAL                                 2
#define M_RAYLEIGH                                    3
#define M_HYPER_CUBE_ROOT                             4
#define M_HYPER_LOG                                   5

/************************************************************************/
/* MimConvert()                                                         */
/************************************************************************/
#define M_REGULAR                                     0x00020000L
#define M_FAST                                        0x00002000L
#define M_MASK                                        0x00001000L

#define M_ID_OFFSET_OF_DEFAULT_CONVERT                (0x00200000L|M_PSEUDO_ID)

#define M_RGB_TO_HSL                                  (M_ID_OFFSET_OF_DEFAULT_CONVERT + 1L)     // Same as Mil.h
#define M_RGB_TO_HLS                                  M_RGB_TO_HSL                              // Obsolete
#define M_RGB_TO_L                                    (M_ID_OFFSET_OF_DEFAULT_CONVERT + 2L)     // Same as Mil.h
#define M_HSL_TO_RGB                                  (M_ID_OFFSET_OF_DEFAULT_CONVERT + 3L)     // Same as Mil.h
#define M_HLS_TO_RGB                                  M_HSL_TO_RGB                              // Obsolete
#define M_L_TO_RGB                                    (M_ID_OFFSET_OF_DEFAULT_CONVERT + 4L)     // Same as Mil.h
#define M_RGB_TO_Y                                    (M_ID_OFFSET_OF_DEFAULT_CONVERT + 5L)     // Same as Mil.h
#define M_RGB_TO_H                                    (M_ID_OFFSET_OF_DEFAULT_CONVERT + 6L)     // Same as Mil.h

#define M_RGB_TO_YUV16                                (M_ID_OFFSET_OF_DEFAULT_CONVERT + 101L)   // Same as Mil.h
#define M_YUV16_TO_RGB                                (M_ID_OFFSET_OF_DEFAULT_CONVERT + 301L)   // Same as Mil.h
#define M_RGB_NORMALIZE                               (M_ID_OFFSET_OF_DEFAULT_CONVERT + 10L)
#define M_RGB_TO_HSV                                  (M_ID_OFFSET_OF_DEFAULT_CONVERT + 11L)    // Same as Mildev.h
#define M_HSV_TO_RGB                                  (M_ID_OFFSET_OF_DEFAULT_CONVERT + 12L)    // Same as Mildev.h

#define M_SRGB_LINEAR_TO_LAB                          (M_ID_OFFSET_OF_DEFAULT_CONVERT + 500L)
#define M_SRGB_TO_LAB                                 (M_ID_OFFSET_OF_DEFAULT_CONVERT + 501L)
#define M_LAB_TO_SRGB_LINEAR                          (M_ID_OFFSET_OF_DEFAULT_CONVERT + 502L)
#define M_LAB_TO_SRGB                                 (M_ID_OFFSET_OF_DEFAULT_CONVERT + 503L)
#define M_SRGB_LINEAR_TO_LCH                          (M_ID_OFFSET_OF_DEFAULT_CONVERT + 504L)
#define M_SRGB_TO_LCH                                 (M_ID_OFFSET_OF_DEFAULT_CONVERT + 505L)
#define M_LCH_TO_SRGB_LINEAR                          (M_ID_OFFSET_OF_DEFAULT_CONVERT + 506L)
#define M_LCH_TO_SRGB                                 (M_ID_OFFSET_OF_DEFAULT_CONVERT + 507L)

#define M_MATRIX_ID(x)                                (x)                                       // Obsolete from MIL 9

// If the conversion type is set to M_DEFAULT, the conversion will be
//  choosen according to the type of buffers passed to the function.
#define M_DEFAULT                                    0x10000000L

// These can be added to the conversion type to speed-up the
//   process ( M_FAST ) or have a better precision ( M_REGULAR ).
//   Not all conversion are affected by this flag.
#define M_REGULAR                                     0x00020000L
#define M_FAST                                        0x00002000L

/************************************************************************/
/* MimWarp()                                                            */
/************************************************************************/
/* 8 bits reserved for number of fractional bits */
#define M_WARP_MATRIX                                 0x00100000L
#define M_WARP_POLYNOMIAL                             0x00200000L
#define M_WARP_LUT                                    0x00400000L
#define M_OVERSCAN_ENABLE                             0x00008000L
#define M_OVERSCAN_DISABLE                            0x00080000L
#define M_OVERSCAN_FAST                               0x00040000L
#define M_OVERSCAN_CLEAR                              0x00000080L
#define M_FIXED_POINT                                 0x00004000L

/************************************************************************/
/* MimTransform()                                                       */
/************************************************************************/
#define M_FFT                                         1L
#define M_DCT8X8                                      2L
#define M_DCT                                         3L
#define M_POLAR                                       5L

#define M_FORWARD                                     0x01
#define M_REVERSE                                     4L
#define M_NORMALIZED                                  0x00000002L
#define M_NORMALIZE                                   M_NORMALIZED
#define M_1D_ROWS                                     0x00000010L
#define M_1D_COLUMNS                                  0x00000020L
#define M_REAL                                        0x00000040L
#define M_CENTER                                      0x00000080L
#define M_MAGNITUDE                                   0x00000100L
#define M_PHASE                                       0x00000200L
#define M_LOG_SCALE                                   0x00000400L
#define M_FAST_PHASE                                  0x00000800L
#define M_SQUARE_MAGNITUDE                            0x00001000L
#define M_NORMALIZE_PHASE                             0x00002000L
#define M_NORMALIZE_PHASE_255                         0x00008000L
#define M_CLOCKWISE_PHASE                             0x00010000L
#define M_USE_CORDIC                                  0x00020000L
#define M_INTERNAL_FFT_NEW                            0x00000008L


/************************************************************************/
/* MimWaveletTransform()                                                */
/************************************************************************/
#define M_FORWARD                                     0x01            // Already defined elsewhere
#define M_REVERSE                                     4L              // Already defined elsewhere
#define M_COPY                                        0x00020000L     // Already defined elsewhere

/************************************************************************/
/* MimWaveletDenoise  ()                                                */
/************************************************************************/
#define M_DENOISE_PSEUDO_ID                              (0x00100100L|M_PSEUDO_ID)   // =utilities
#define M_BAYES_SHRINK                                   (M_DENOISE_PSEUDO_ID + 2L)
#define M_SURE_SHRINK                                    (M_DENOISE_PSEUDO_ID + 3L)
#define M_NEIGH_SHRINK                                   (M_DENOISE_PSEUDO_ID + 4L)

/************************************************************************/
/* MimPolarTransform()                                                  */
/************************************************************************/
#define M_RECTANGULAR_TO_POLAR                        0x00000001L
#define M_POLAR_TO_RECTANGULAR                        0x00000002L
#define M_FIXED_POINT                                 0x00004000L
#define M_RECTANGULAR_TO_POLAR_LUT                    0x00008000L
#define M_POLAR_TO_RECTANGULAR_LUT                    0x00010000L

/************************************************************************/
/* MimDraw()                                                       */
/************************************************************************/
#define M_DRAW_PEAKS                                  0x01000000L
#define M_DRAW_DARK_IMAGE                             0x02000000L
#define M_DRAW_OFFSET_IMAGE                           0x04000000L
#define M_DRAW_FLAT_IMAGE                             0x08000000L
#define M_DOTS                                        0x00000040L
#define M_LINES                                       0x00000080L
#define M_1D_ROWS                                     0x00000010L    // Already defined elsewhere
#define M_1D_COLUMNS                                  0x00000020L    // Already defined elsewhere
#define M_DRAW_STAT_RESULT                            0x00000100L
#define M_DRAW_WAVELET                                0x00010000L
#define M_DRAW_WAVELET_WITH_PADDING                   0x00000800L
#define M_DRAW_MODEL                                  0x00001000L
#define M_DRAW_MASK                                   0x200000L      // Already defined elsewhere
#define M_DRAW_PATH                                   0x00000200L
#define M_DRAW_DEAD_PIXELS                            0x00000400L
#define M_DRAW_IMAGE_ORIENTATION                      0x00002000L
#define M_DRAW_DEPTH_MAP_ROW                          0x00004000L
#define M_DRAW_INTENSITY_MAP_ROW                      0x00008000L
#define M_DRAW_GLCM_MATRIX                            0x00100000L
#define M_AUTO_SCALE                                           2L   // Already defined in mil.h
#define M_SATURATION                                      0x2000L   // Already defined in mil.h

#define M_DRAW_AUG_IMAGE                              0x00020000L // TOMODIFY: review this value

/************************************************************************/
/* MimStatMultiple()                                                    */
/************************************************************************/
#define M_CALCULATE                                   1L          // Already defined elsewhere
#define M_PREPROCESS                                  0x00000002L // Already defined elsewhere
#define M_REMOVE                                      0x00000004L
#define M_RESET_EXTREMES                              0x00000008L

/************************************************************************/
/* MimFlatField(), MimDeadPixelCorrection(), MimRearrange() and         */
/* MimStatMultiple()                                                    */
/************************************************************************/
#define M_PREPROCESS                                  0x00000002L

/************************************************************************/
/* MimProjectShape(), MgenLutWarp()                                     */
/************************************************************************/
#define M_OPTIMAL_SIZE_X                              0x1L
#define M_OPTIMAL_SIZE_Y                              0x2L
#define M_PATH_LIST                                   0x3L
#define M_X_PATH_LIST                                 0x4L
#define M_Y_PATH_LIST                                 0x5L
#define M_XY_PATH_LIST                                0x6L
#define M_PATH_WIDTH_LIST                             0x7L

/************************************************************************/
/* MimLocatepeak1d()                                                    */
/************************************************************************/
#define M_SCAN_LANE_INDEX                             0x000100000L
#define M_RANK_INDEX                                  0x000200000L

#define M_PEAK_POSITION                               0x000400000L
#define M_PEAK_POSITION_X                             0x000800000L
#define M_PEAK_POSITION_Y                             0x001000000L

#define M_NUMBER                                      1009L         // defined in milmeas.h
#define M_PEAK_INTENSITY_RANGE                        0x000008000L
#define M_PEAK_INTENSITY                              0x000010000L
#define M_FRAME_INDEX                                 0x002000000L

#define M_PEAK_WIDTH                                  11L
#define M_NUMBER_OF_SCAN_LANES                        0x000020000L
#define M_INCLUDE_MISSING_DATA                        0x000040000L
#define M_ONLY_MISSING_DATA                           0x000080000L

#define M_STATUS                                      0x00008002L // Already defined elsewhere

/************************************************************************/
/* MimBinarizeAdaptive()                                                */
/************************************************************************/
#define M_THRESHOLD_MODE                                33L    // Already defined in    miledge.h
#define M_NIBLACK                                     1880L
#define M_BERNSEN                                     1881L
#define M_LOCAL_MEAN                                  1882L
#define M_PSEUDOMEDIAN                                1883L
#define M_LOCAL_DIMENSION                             1884L
#define M_MINIMUM_CONTRAST                            600L     // Also defined in milstr.h
#define M_GLOBAL_MAX                                  1885L
#define M_GLOBAL_MIN                                  1886L
#define M_NIBLACK_BIAS                                1887L
#define M_GLOBAL_OFFSET                               1888L
//#define M_HYSTERESIS 31L
#define M_NIBLACK_BIAS_SECOND_PASS                            1889L
#define M_GLOBAL_OFFSET_SECOND_PASS                           1890L
#define M_AVERAGE_MODE                                1891L
//#define M_UNIFORM                                      1L
#define M_GAUSSIAN                                    0x805L //also defined in miledge.h
#define M_RECONSTRUCT                                 1892L
#define M_NB_ITERATIONS                               1893L
#define M_NB_SEED_ITERATIONS                          1894L
#define M_TOGGLE                                      1895L
#define M_THRESHOLD_TYPE                              3000L

/************************************************************************/
/* MimAugment()                                                     */
/************************************************************************/

#define M_SAVE_REPORT                             0x200L // already defined in milcode.h
                                             
#define M_PRIORITY                           0x00004000L
#define M_PROBABILITY                        0x00008000L

// STRUCTURE
#define M_AUG_DILATION_OP                          3098L
#define M_AUG_EROSION_OP                           3099L
#define M_AUG_DILATION_ASYM_OP                     3100L
#define M_AUG_EROSION_ASYM_OP                      3101L

// GEOMETRIQUE
#define M_AUG_FLIP_OP                              2870L
#define M_AUG_CROP_OP                              3102L

// AFFINE
#define M_AUG_ROTATION_OP                          3103L
#define M_AUG_SCALE_OP                             3104L
#define M_AUG_TRANSLATION_X_OP                     3105L
#define M_AUG_TRANSLATION_Y_OP                     3106L
#define M_AUG_ASPECT_RATIO_OP                      3107L
#define M_AUG_SHEAR_X_OP                           2892L
#define M_AUG_SHEAR_Y_OP                           2893L

// INTENSITY
#define M_AUG_INTENSITY_MULTIPLY_OP                2940L
#define M_AUG_INTENSITY_ADD_OP                     2887L
#define M_AUG_GAMMA_OP                             2962L
#define M_AUG_LIGHTING_DIRECTIONAL_OP              3108L
#define M_AUG_SATURATION_GAIN_OP                   2910L
#define M_AUG_HUE_OFFSET_OP                        2917L
#define M_AUG_HSV_VALUE_GAIN_OP                    2914L

// FILTER
#define M_AUG_SMOOTH_DERICHE_OP                    2920L
#define M_AUG_SMOOTH_GAUSSIAN_OP                   2932L
#define M_AUG_BLUR_MOTION_OP                       2923L
#define M_AUG_SHARPEN_DERICHE_OP                   2928L

// NOISE
#define M_AUG_NOISE_GAUSSIAN_ADDITIVE_OP           2955L
#define M_AUG_NOISE_MULTIPLICATIVE_OP              2950L
#define M_AUG_NOISE_SALT_PEPPER_OP                 2947L


// Augmentation Control parameters
#define M_AUG_DILATION_OP_NB_ITERATIONS_MAX           2873L
#define M_AUG_EROSION_OP_NB_ITERATIONS_MAX            2875L
#define M_AUG_DILATION_ASYM_OP_NB_ITERATIONS_MAX      2881L
#define M_AUG_EROSION_ASYM_OP_NB_ITERATIONS_MAX       2882L

#define M_AUG_FLIP_OP_DIRECTION                       3120L
#define M_AUG_CROP_OP_FACTOR_X                        2884L
#define M_AUG_CROP_OP_FACTOR_Y                        2885L
#define M_AUG_CROP_OP_RESIZE                          2886L

#define M_AUG_SCALE_OP_FACTOR_MAX                     2876L
#define M_AUG_SCALE_OP_FACTOR_MIN                     2877L
#define M_AUG_ROTATION_OP_ANGLE_MAX                   2805L
#define M_AUG_ROTATION_OP_ANGLE_REF                   3348L 
#define M_AUG_ROTATION_OP_ANGLE_DELTA                 3349L
#define M_AUG_ROTATION_OP_ANGLE_STEP                  3350L
#define M_AUG_ROTATION_OP_ANGLE_MIN                   3351L
#define M_AUG_TRANSLATION_X_OP_MAX                    2868L
#define M_AUG_TRANSLATION_Y_OP_MAX                    2869L
#define M_AUG_ASPECT_RATIO_OP_MIN                     2878L
#define M_AUG_ASPECT_RATIO_OP_MAX                     2879L
#define M_AUG_ASPECT_RATIO_OP_MODE                    2880L
#define M_AUG_SHEAR_X_OP_MIN                          2888L
#define M_AUG_SHEAR_X_OP_MAX                          2889L
#define M_AUG_SHEAR_Y_OP_MIN                          2890L
#define M_AUG_SHEAR_Y_OP_MAX                          2891L

#define M_AUG_LIGHTING_DIRECTIONAL_OP_ANGLE_MAX       2894L
#define M_AUG_LIGHTING_DIRECTIONAL_OP_INTENSITY_MIN   2895L
#define M_AUG_LIGHTING_DIRECTIONAL_OP_INTENSITY_MAX   2896L
#define M_AUG_SATURATION_GAIN_OP_MIN                  2911L
#define M_AUG_SATURATION_GAIN_OP_MAX                  2912L
#define M_AUG_HUE_OFFSET_OP_MIN                       2915L
#define M_AUG_HUE_OFFSET_OP_MAX                       2916L
#define M_AUG_HSV_VALUE_GAIN_OP_MIN                   2918L
#define M_AUG_HSV_VALUE_GAIN_OP_MAX                   2919L

#define M_GAIN_CONST                                  206L  // Already defined for M_FLAT_FIELD_CONTEXT
#define M_AUG_INTENSITY_MULTIPLY_OP_VALUE             M_GAIN_CONST
#define M_AUG_INTENSITY_MULTIPLY_OP_DELTA             2941L
#define M_AUG_INTENSITY_MULTIPLY_OP_MODE              2959L
#define M_OFFSET_CONST                                204L  // Already defined for M_FLAT_FIELD_CONTEXT
#define M_AUG_INTENSITY_ADD_OP_VALUE                  M_OFFSET_CONST
#define M_AUG_INTENSITY_ADD_OP_DELTA                  2958L
#define M_AUG_INTENSITY_ADD_OP_MODE                   2883L 
#define M_GAMMA                                       6672L // Already defined mil.h
#define M_AUG_GAMMA_OP_VALUE                          M_GAMMA
#define M_AUG_GAMMA_OP_DELTA                          2963L
#define M_AUG_GAMMA_OP_MODE                           2942L

#define M_AUG_SMOOTH_DERICHE_OP_FACTOR_MIN             2921L
#define M_AUG_SMOOTH_DERICHE_OP_FACTOR_MAX             2922L
#define M_AUG_SMOOTH_GAUSSIAN_OP_STDDEV_MIN            2933L
#define M_AUG_SMOOTH_GAUSSIAN_OP_STDDEV_MAX            2934L
#define M_AUG_BLUR_MOTION_OP_SIZE_MIN                  2924L
#define M_AUG_BLUR_MOTION_OP_SIZE_MAX                  2925L
#define M_AUG_BLUR_MOTION_OP_ANGLE_MIN                 2926L
#define M_AUG_BLUR_MOTION_OP_ANGLE_MAX                 2927L
#define M_AUG_SHARPEN_DERICHE_OP_FACTOR_MIN            2929L
#define M_AUG_SHARPEN_DERICHE_OP_FACTOR_MAX            2930L

#define M_AUG_NOISE_SALT_PEPPER_OP_DENSITY             2948L
#define M_AUG_NOISE_SALT_PEPPER_OP_DENSITY_DELTA       2949L
#define M_AUG_NOISE_MULTIPLICATIVE_OP_STDDEV           2951L
#define M_AUG_NOISE_MULTIPLICATIVE_OP_STDDEV_DELTA     2952L
#define M_AUG_NOISE_MULTIPLICATIVE_OP_INTENSITY_MIN    2953L
#define M_AUG_NOISE_MULTIPLICATIVE_OP_DISTRIBUTION     2954L
#define M_AUG_NOISE_GAUSSIAN_ADDITIVE_OP_STDDEV        2956L
#define M_AUG_NOISE_GAUSSIAN_ADDITIVE_OP_STDDEV_DELTA  2957L

#define M_AUG_RNG_INIT_VALUE                           2867L
#define M_AUG_SEED_MODE                                3421L
//#define M_AUG_CONTEXT_SEED                             3422L 
#define M_AUG_OPTIMAL_SIZE_X                           3419L 
#define M_AUG_OPTIMAL_SIZE_Y                           3420L 

/* Parameter value */
#define M_ALL_BANDS                                    M_ALL_BAND // Already defined mil.h
#define M_PER_BAND                                     2966L
#define M_UNIFORM                                      1      // Already defined MimHistogramEqualize()
#define M_GAUSSIAN                                     0x805L // Already defined in miledge.h
#define M_RGB                                          8L     // Already defined in mil.h
#define M_LEFT_HALF                                    M_LEFT
#define M_RIGHT_HALF                                   M_RIGHT
#define M_UPPER_HALF                                   M_TOP
#define M_LOWER_HALF                                   M_BOTTOM
#define M_NORMAL                                       8L // Already defined in mil.h
#define M_INVERT                                       2L // Arleady defined in milocr.h    

#define M_RNG_AUTO                                     3422L
#define M_RNG_INIT_VALUE                               3464L
#define M_USER_DEFINED_SEED                            3465L

#define M_AUTO_VALUE                                   MAKE_INT64(0x0000000100000000) 
/************************************************************************/
/* MimStatCalculate()                                                   */
/************************************************************************/

/************************************************************************/
/* MimFilterAdaptive()                                                   */
/************************************************************************/
#define M_BILATERAL                                   (M_PSEUDO_ID | 0x400)

#if OldDefinesSupport
   #define M_NOPEL                                    (M_PSEUDO_ID | 0x401)
   MIL_DEPRECATED(M_NOPEL, 1040) // Use M_NOISE_PEAK_REMOVAL instead.
#endif
#define M_NOISE_PEAK_REMOVAL                          (M_PSEUDO_ID | 0x402)
#define M_MEDIAN                                      0x10000L       // Already defined elsewhere.
#define M_MEAN                                        0x08000000L    // Already defined elsewhere.
#define M_EXTREME                                     3393L

/************************************************************************/
/* MimRemap()                                                           */
/************************************************************************/

// Control for M_HIST_LIST
#define  M_FIT_SRC_RANGE                                 0x01        // Already defined as control for M_HIST_LIST.
#define  M_FIT_SRC_DATA                                  0x02        // Already defined as control for M_HIST_LIST.
#define  M_CENTERED                                      0x00010000

#ifdef __cplusplus

inline MIL_INT64 ExtractTypeFromValue(MIL_INT64 Value,
                                      MIL_INT64 Type1,
                                      MIL_INT64 Type2 = 0,
                                      MIL_INT64 Type3 = 0,
                                      MIL_INT64 Type4 = 0,
                                      MIL_INT64 Type5 = 0,
                                      MIL_INT64 Type6 = 0,
                                      MIL_INT64 Type7 = 0,
                                      MIL_INT64 Type8 = 0)
   {
   MIL_INT64 Type = (Value & M_HLVLDATATYPE_MASK);
   if (Type) // type specified.
      {
      // If the extracted type doesn't match one of the allowed types, set it to 0.
      if (Type != Type1 &&
          Type != Type2 &&
          Type != Type3 &&
          Type != Type4 &&
          Type != Type5 &&
          Type != Type6 &&
          Type != Type7 &&
          Type != Type8)
         {
         Type = 0;
         }
      }

   return Type;
   }

#endif

/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
{
#endif


      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* POINT TO POINT : */

      /* -------------------------------------------------------------- */

#if M_MIL_USE_64BIT
   #define MimArith(Src1, Src2, Dest, Op) MimArithDouble(M_MILID_TO_DOUBLE(Src1), M_MILID_TO_DOUBLE(Src2), Dest, Op)
#else
   #define MimArithDouble MimArith
#endif
MIL_DLLFUNC void MFTYPE    MimArithDouble       (MIL_DOUBLE Src1ImageBufIdOrConst,
                                     MIL_DOUBLE Src2ImageBufIdOrConst,
                                     MIL_ID DstImageBufId,
                                     MIL_INT64 Operation);

#if M_MIL_USE_64BIT
   #define MimArithMultiple(Src1, Src2, Src3, Src4, Src5, Dest, Op, OpFlag) MimArithMultipleDouble(M_MILID_TO_DOUBLE(Src1), M_MILID_TO_DOUBLE(Src2), M_MILID_TO_DOUBLE(Src3), Src4, Src5, Dest, Op, OpFlag)
#else
   #define MimArithMultipleDouble MimArithMultiple
#endif
MIL_DLLFUNC void MFTYPE    MimArithMultipleDouble(MIL_DOUBLE Src1ImageBufId,
                                      MIL_DOUBLE Src2ImageBufIdOrConst,
                                      MIL_DOUBLE Src3ImageBufIdOrConst,
                                      MIL_DOUBLE Src4Const,
                                      MIL_DOUBLE Src5Const,
                                      MIL_ID DstImageBufId,
                                      MIL_INT64  Operation,
                                      MIL_INT64  OperationFlag);

MIL_DLLFUNC void MFTYPE    MimLutMap            (MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_ID LutBufId);

MIL_DLLFUNC void MFTYPE    MimShift             (MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_INT NbBitsToShift);

MIL_DLLFUNC MIL_INT MFTYPE    MimBinarizeDouble    (MIL_ID     SrcImageBufId,
                                        MIL_ID     DstImageBufId,
                                        MIL_INT64  ConditionAndThreshMode,
                                        MIL_DOUBLE LowParam,
                                        MIL_DOUBLE HighParam);

MIL_DLLFUNC void MFTYPE    MimClipDouble        (MIL_ID     SrcImageBufId,
                                     MIL_ID     DstImageBufId,
                                     MIL_INT64  Condition,
                                     MIL_DOUBLE CondLow,
                                     MIL_DOUBLE CondHigh,
                                     MIL_DOUBLE WriteLow,
                                     MIL_DOUBLE WriteHigh);

MIL_DLLFUNC void MFTYPE    MimFlatField         (MIL_ID FlatFieldContextImId,
                                     MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_INT64 ControlFlag);

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* NEIGHBOURHOOD : */

      /* -------------------------------------------------------------- */

MIL_DLLFUNC void MFTYPE    MimDeinterlace       (MIL_ID DeinterlaceContextImId,
                                     const MIL_ID *SrcImageArrayPtr,
                                     const MIL_ID *DstImageArrayPtr,
                                     MIL_INT SrcImageCount,
                                     MIL_INT DstImageCount,
                                     MIL_INT64 ControlFlag);


      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* GEOMETRICAL: */

   /* -------------------------------------------------------------- */

MIL_DLLFUNC void MFTYPE    MimResize             (MIL_ID     SrcImageBufId,
                                      MIL_ID     DstImageOrArrayBufId,
                                      MIL_DOUBLE ScaleFactorX,
                                      MIL_DOUBLE ScaleFactorY,
                                      MIL_INT64  InterpolationMode);

MIL_DLLFUNC void MFTYPE    MimRotate             (MIL_ID     SrcImageBufId,
                                      MIL_ID     DstImageOrArrayBufId,
                                      MIL_DOUBLE Angle,
                                      MIL_DOUBLE SrcCenX,
                                      MIL_DOUBLE SrcCenY,
                                      MIL_DOUBLE DstCenX,
                                      MIL_DOUBLE DstCenY,
                                      MIL_INT64  InterpolationMode);

MIL_DLLFUNC void MFTYPE    MimFlip               (MIL_ID SrcImageBufId,
                                      MIL_ID DstImageBufId,
                                      MIL_INT64 Operation,
                                      MIL_INT64 OpFlag);

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* STATISTICAL: */

      /* -------------------------------------------------------------- */

MIL_DLLFUNC void MFTYPE    MimHistogram         (MIL_ID SrcImageBufId,
                                     MIL_ID HistResultImId);

MIL_DLLFUNC void MFTYPE    MimHistogramEqualizeDouble(MIL_ID     SrcImageBufId,
                                          MIL_ID     DstImageBufId,
                                          MIL_INT64  Operation,
                                          MIL_DOUBLE Alpha,
                                          MIL_DOUBLE Min,
                                          MIL_DOUBLE Max);

MIL_DLLFUNC void MFTYPE    MimFindExtreme       (MIL_ID SrcImageBufId,
                                     MIL_ID ExtremeResultImId,
                                     MIL_INT64 ExtremeType);

MIL_DLLFUNC MIL_ID MFTYPE  MimAllocResult       (MIL_ID SysId,
                                     MIL_INT NbEntries,
                                     MIL_INT64 ResultType,
                                     MIL_ID* ResultImIdPtr);

MIL_DLLFUNC void MFTYPE    MimFree              (MIL_ID ContextOrResultImId);

MIL_DLLFUNC MIL_INT MFTYPE MimInquire           (MIL_ID ContextOrResultImId,
                                     MIL_INT64 InquireType,
                                     void* UserVarPtr);

MIL_DLLFUNC void MFTYPE    MimGetResult2d       (MIL_ID ResultImId,
                                     MIL_INT OffsetX,
                                     MIL_INT OffsetY,
                                     MIL_INT SizeX,
                                     MIL_INT SizeY,
                                     MIL_INT64  ResultType,
                                     MIL_INT64  ControlFlag,
                                     void* UserArrayPtr);

MIL_DLLFUNC void MFTYPE    MimGetResult1d       (MIL_ID ResultImId,
                                     MIL_INT OffEntry,
                                     MIL_INT NbEntries,
                                     MIL_INT64 ResultType,
                                     void* UserArrayPtr);

MIL_DLLFUNC void MFTYPE    MimGetResult         (MIL_ID ResultImId,
                                     MIL_INT64 ResultType,
                                     void* UserArrayPtr);

/*
                                     */
MIL_DLLFUNC void MFTYPE    MimGetResultSingleInt64   (MIL_ID ResultImId,
                                     MIL_INT64 Index1,
                                     MIL_INT64 Index2,
                                     MIL_INT64 ResultType,
                                     void* UserArrayPtr);

MIL_DLLFUNC MIL_ID MFTYPE  MimAlloc             (MIL_ID SysId,
                                     MIL_INT64 ContextType,
                                     MIL_INT64 ControlFlag,
                                     MIL_ID* ContextImIdPtr);

#if M_MIL_USE_64BIT
// Prototypes for 64 bits OSs

MIL_DLLFUNC void MFTYPE    MimControlInt64      (MIL_ID ContextOrResultImId,
                                     MIL_INT64 ControlType,
                                     MIL_INT64 ControlValue);

MIL_DLLFUNC void MFTYPE    MimControlDouble     (MIL_ID ContextOrResultImId,
                                     MIL_INT64 ControlType,
                                     MIL_DOUBLE ControlValue);
#else
// Prototypes for 32 bits OSs

#define MimControlDouble   MimControl
#define MimControlInt64    MimControl
MIL_DLLFUNC void MFTYPE    MimControl           (MIL_ID     ContextOrResultImId,
                                     MIL_INT64  ControlType,
                                     MIL_DOUBLE ControlValue);
#endif

MIL_DLLFUNC MIL_INT MFTYPE MimGet               (MIL_ID     ContextImId,
                                     MIL_INT64  GetType,
                                     MIL_INT    ArraySize,
                                     void *     Param1Ptr,
                                     void *     Param2Ptr,
                                     MIL_INT64  ControlFlag);

MIL_DLLFUNC void MFTYPE    MimPut               (MIL_ID      ContextImId,
                                     MIL_INT64   PutType,
                                     MIL_INT     ArraySize,
                                     const void *Param1Ptr,
                                     const void *Param2Ptr,
                                     MIL_INT64   ControlFlag);

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* CONVERSION: */

      /* -------------------------------------------------------------- */

MIL_DLLFUNC void MFTYPE    MimConvert           (MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_ID ArrayBufIdOrConversionType);

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* BUF: */

      /* -------------------------------------------------------------- */

MIL_DLLFUNC void MFTYPE    MimRearrange         (MIL_ID RearrangeContextImId,
                                     MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_INT64 ControlFlag);

#if M_MIL_USE_UNICODE

MIL_DLLFUNC MIL_ID MFTYPE MimRestoreA           (MIL_CONST_TEXTA_PTR FileName,
                                     MIL_ID      SysId,
                                     MIL_INT64   ControlFlag,
                                     MIL_ID*     ContextImIdPtr);
MIL_DLLFUNC void MFTYPE MimSaveA                (MIL_CONST_TEXTA_PTR FileName,
                                     MIL_ID      ContextImId,
                                     MIL_INT64   ControlFlag);
MIL_DLLFUNC void MFTYPE MimStreamA              (MIL_TEXTA_PTR      MemPtrOrFileName,
                                     MIL_ID     SysId,
                                     MIL_INT64  Operation,
                                     MIL_INT64  StreamType,
                                     MIL_DOUBLE Version,
                                     MIL_INT64  ControlFlag,
                                     MIL_ID*    ContextImIdPtr,
                                     MIL_INT*   SizeByteVarPtr);

MIL_DLLFUNC MIL_ID MFTYPE MimRestoreW  (MIL_CONST_TEXTW_PTR FileName,
                                     MIL_ID SysId,
                                     MIL_INT64  ControlFlag,
                                     MIL_ID *ContextImIdPtr);
MIL_DLLFUNC void MFTYPE MimSaveW                (MIL_CONST_TEXTW_PTR FileName,
                                     MIL_ID ContextImId,
                                     MIL_INT64  ControlFlag);
MIL_DLLFUNC void MFTYPE MimStreamW              (MIL_TEXTW_PTR MemPtrOrFileName,
                                     MIL_ID       SysId,
                                     MIL_INT64    Operation,
                                     MIL_INT64    StreamType,
                                     MIL_DOUBLE   Version,
                                     MIL_INT64    ControlFlag,
                                     MIL_ID*      ContextImIdPtr,
                                     MIL_INT*     SizeByteVarPtr);

#if M_MIL_UNICODE_API
#define MimRestore   MimRestoreW
#define MimSave      MimSaveW
#define MimStream    MimStreamW
#else
#define MimRestore   MimRestoreA
#define MimSave      MimSaveA
#define MimStream    MimStreamA
#endif

#else

MIL_DLLFUNC MIL_ID MFTYPE MimRestore            (MIL_CONST_TEXT_PTR FileName,
                                     MIL_ID SysId,
                                     MIL_INT64  ControlFlag,
                                     MIL_ID *ContextImIdPtr);

MIL_DLLFUNC void MFTYPE MimSave                 (MIL_CONST_TEXT_PTR FileName,
                                     MIL_ID ContextImId,
                                     MIL_INT64  ControlFlag);

MIL_DLLFUNC void MFTYPE MimStream               (MIL_TEXT_PTR  MemPtrOrFileName,
                                     MIL_ID        SysId,
                                     MIL_INT64     Operation,
                                     MIL_INT64     StreamType,
                                     MIL_DOUBLE    Version,
                                     MIL_INT64     ControlFlag,
                                     MIL_ID*       ContextImIdPtr,
                                     MIL_INT*      SizeByteVarPtr);
#endif   //#if M_MIL_USE_UNICODE

#if (!M_MIL_LITE)

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* NEIGHBOURHOOD : */

      /* -------------------------------------------------------------- */

MIL_DLLFUNC void MFTYPE    MimConvolve          (MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_ID FilterContextImOrKernelBufId);


MIL_DLLFUNC void MFTYPE    MimRank              (MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_ID StructElemBufId,
                                     MIL_INT Rank,
                                     MIL_INT64 ProcMode);

MIL_DLLFUNC void MFTYPE    MimEdgeDetectMIL_INT (MIL_ID SrcImageBufId,
                                     MIL_ID DstIntensityImageBufId,
                                     MIL_ID DstAngleImageBufId,
                                     MIL_ID KernelId,
                                     MIL_INT64 ControlFlag,
                                     MIL_INT Threshold);

MIL_DLLFUNC void MFTYPE    MimMatch             (MIL_ID MatchContextImId,
                                     MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_INT64 ControlFlag);

MIL_DLLFUNC void MFTYPE MimBinarizeAdaptive (  MIL_ID AdaptiveBinarizeContextImId,
                                               MIL_ID SrcImageBufId,
                                               MIL_ID SeedImage1BufId,
                                               MIL_ID SeedImage2BufId,
                                               MIL_ID BinarizedImageBufId,
                                               MIL_ID ThresholdImageBufId,
                                               MIL_INT64 ControlFlag);

MIL_DLLFUNC void MFTYPE MimAugment(MIL_ID    AugmentationContextImId,
                                   MIL_ID    SrcImageBufId,
                                   MIL_ID    DstImageBufOrAugmentationResultImId,
                                   MIL_INT64 SeedValue,
                                   MIL_INT64 ControlFlag);

MIL_DLLFUNC void MFTYPE MimFilterAdaptive(MIL_ID      AdaptiveFilterContextImId,
                                          MIL_ID      SrcImageBufId,
                                          MIL_ID      DstImageBufId,
                                          MIL_DOUBLE  Param1,
                                          MIL_DOUBLE  Param2,
                                          MIL_DOUBLE  Param3,
                                          MIL_INT64   ControlFlag
                                          );



MIL_DLLFUNC void MFTYPE MimDifferential(MIL_ID     Drv1ImageBufIdOrFilterContextImId, 
                                        MIL_ID     SrcOrDrv2ImageBufId, 
                                        MIL_ID     SrcOrDrv3ImageBufId, 
                                        MIL_ID     Drv4ImageBufId, 
                                        MIL_ID     Drv5ImageBufId, 
                                        MIL_ID     Dst1ImageBufId, 
                                        MIL_ID     Dst2ImageBufId,
                                        MIL_DOUBLE Param,
                                        MIL_INT64  Operation,
                                        MIL_INT64  ControlFlag);

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* MORPHOLOGICAL: */

      /* -------------------------------------------------------------- */

MIL_DLLFUNC void MFTYPE    MimLabel             (MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_INT64 ProcMode);

MIL_DLLFUNC void MFTYPE    MimConnectMap        (MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_ID LutBufId);

MIL_DLLFUNC void MFTYPE    MimDilate            (MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_INT NbIteration,
                                     MIL_INT64 ProcMode);

MIL_DLLFUNC void MFTYPE    MimErode             (MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_INT NbIteration,
                                     MIL_INT64 ProcMode);

MIL_DLLFUNC void MFTYPE    MimClose             (MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_INT NbIteration,
                                     MIL_INT64 ProcMode);

MIL_DLLFUNC void MFTYPE    MimOpen              (MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_INT NbIteration,
                                     MIL_INT64 ProcMode);

MIL_DLLFUNC void MFTYPE    MimMorphic           (MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_ID StructElemBufId,
                                     MIL_INT64 Operation,
                                     MIL_INT NbIterationOrArea,
                                     MIL_INT64 ProcMode);

MIL_DLLFUNC void MFTYPE    MimThin              (MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_INT NbIteration,
                                     MIL_INT64 ProcMode);

MIL_DLLFUNC void MFTYPE    MimThick             (MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_INT NbIteration,
                                     MIL_INT64 ProcMode);

MIL_DLLFUNC void MFTYPE    MimDistance          (MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_INT64 DistanceTransform);

MIL_DLLFUNC void MFTYPE    MimWatershed         (MIL_ID SrcImageBufId,
                                     MIL_ID MarkerImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_INT MinVariation,
                                     MIL_INT64 ControlFlag);

MIL_DLLFUNC void MFTYPE    MimZoneOfInfluence   (MIL_ID SrcImageBufId,
                                     MIL_ID DstImageBufId,
                                     MIL_INT64 OperationFlag);

MIL_DLLFUNC void MFTYPE    MimDeadPixelCorrection(MIL_ID DeadPixelContextImId,
                                      MIL_ID SrcImageBufId,
                                      MIL_ID DstImageBufId,
                                      MIL_INT64 ControlFlag);

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* GEOMETRICAL: */

      /* -------------------------------------------------------------- */

MIL_DLLFUNC void MFTYPE    MimTranslate          (MIL_ID     SrcImageBufId,
                                      MIL_ID     DstImageOrArrayBufId,
                                      MIL_DOUBLE DisplacementX,
                                      MIL_DOUBLE DisplacementY,
                                      MIL_INT64  InterpolationMode);

MIL_DLLFUNC void MFTYPE    MimWarp               (MIL_ID SrcImageBufId,
                                      MIL_ID DstImageBufId,
                                      MIL_ID WarpParam1BufId,
                                      MIL_ID WarpParam2BufId,
                                      MIL_INT64 OperationMode,
                                      MIL_INT64 InterpolationMode);

MIL_DLLFUNC void MFTYPE    MimWarpList(MIL_ID WarpParamBufId,
                                       MIL_INT64 TransformType,
                                       MIL_INT NumPoints,
                                       const MIL_DOUBLE* SrcCoordXArrayPtr,
                                       const MIL_DOUBLE* SrcCoordYArrayPtr,
                                       MIL_DOUBLE* DstCoordXArrayPtr,
                                       MIL_DOUBLE* DstCoordYArrayPtr,
                                       MIL_INT64 ControlFlag);

MIL_DLLFUNC void MFTYPE    MimPolarTransform (MIL_ID      SrcImageOrDstXLutBufId,
                                  MIL_ID      DstImageOrYLutBufId,
                                  MIL_DOUBLE  CenterPosX,
                                  MIL_DOUBLE  CenterPosY,
                                  MIL_DOUBLE  StartRadius,
                                  MIL_DOUBLE  EndRadius,
                                  MIL_DOUBLE  StartAngle,
                                  MIL_DOUBLE  EndAngle,
                                  MIL_INT64   OperationMode,
                                  MIL_INT64   InterpolationMode,
                                  MIL_DOUBLE *DstSizeXPtr,
                                  MIL_DOUBLE *DstSizeYPtr);

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* STATISTICAL: */

      /* -------------------------------------------------------------- */

MIL_DLLFUNC void MFTYPE    MimBoundingBox(MIL_ID SrcImageBufId,
                                          MIL_INT64 Condition,
                                          MIL_DOUBLE CondLow,
                                          MIL_DOUBLE CondHigh,
                                          MIL_INT64 BoxDefinitionType,
                                          MIL_INT* TopLeftX,
                                          MIL_INT* TopLeftY,
                                          MIL_INT* BottomRightX,
                                          MIL_INT* BottomRightY,
                                          MIL_INT64 ControlFlag);

MIL_DLLFUNC void MFTYPE    MimProject           (MIL_ID SrcImageBufId,
                                                 MIL_ID ProjResultImId,
                                                 MIL_DOUBLE ProjectionAngle);

#if M_MILIM_FUNCTION_DEPRECATION_WARNING
MIL_DEPRECATED(MimProject, 1060) // Use MimProjection instead.
#endif

MIL_DLLFUNC void MFTYPE MimProjection(MIL_ID       SrcImageBufId,
                                      MIL_ID       DstImageBufOrResultImId,
                                      MIL_DOUBLE   ProjectionAxisAngle,
                                      MIL_INT64    Operation,
                                      MIL_DOUBLE   OperationValue);

#if M_MIL_USE_64BIT
   #define MimStat(Src, Result, Type, Condition, CondLow, CondHigh) MimStatDouble(Src, Result, Type, Condition, M_MILID_TO_DOUBLE(CondLow), CondHigh)
#else
   #define MimStatDouble MimStat
#endif
MIL_DLLFUNC void MFTYPE    MimStatDouble        (MIL_ID SrcImageBufId,
                                     MIL_ID StatResultImId,
                                     MIL_INT64 StatType,
                                     MIL_INT64 Condition,
                                     MIL_DOUBLE CondLow,
                                     MIL_DOUBLE CondHigh);

#if M_MILIM_FUNCTION_DEPRECATION_WARNING
MIL_DEPRECATED(MimStat, 1060) // Use MimStatCalculate instead.
#endif

MIL_DLLFUNC void MFTYPE    MimStatMultiple      (MIL_ID StatMultipleContextImId,
                                     MIL_ID SrcImageBufId,
                                     MIL_ID StatMultipleResultImId,
                                     MIL_INT64 ControlFlag);
#if M_MILIM_FUNCTION_DEPRECATION_WARNING
MIL_DEPRECATED(MimStatMultiple, 1060) // Use MimStatCalculate instead.
#endif

MIL_DLLFUNC MIL_INT MFTYPE MimLocateEventDouble (MIL_ID     SrcImageBufId,
                                     MIL_ID     EventResultImId,
                                     MIL_INT64  Condition,
                                     MIL_DOUBLE CondLow,
                                     MIL_DOUBLE CondHigh);

MIL_DLLFUNC void MFTYPE    MimLocatePeak1dDouble(MIL_ID ContextId,
                                                 MIL_ID SrcImageBufId,
                                                 MIL_ID ResultId,
                                                 MIL_INT PeakWidthNominal,
                                                 MIL_INT PeakWidthDelta,
                                                 MIL_DOUBLE MinContrast,
                                                 MIL_INT64 ControlFlag,
                                                 MIL_DOUBLE ControlValue);

MIL_DLLFUNC MIL_INT MFTYPE MimCountDifference   (MIL_ID Src1ImageBufId,
                                     MIL_ID Src2ImageBufId,
                                     MIL_ID CountResultImId);

MIL_DLLFUNC void MFTYPE    MimHistogramEqualizeAdaptive(MIL_ID AdaptiveEqualizeContextImId,
                                               MIL_ID SrcImageBufId,
                                               MIL_ID DstImageBufId,
                                               MIL_INT64 ControlFlag);


MIL_DLLFUNC void MFTYPE MimFindOrientation(MIL_ID OrientationContextImId,
                                       MIL_ID SrcImageBufId,
                                       MIL_ID OrientationResultImId,
                                       MIL_INT64  ControlFlag);

MIL_DLLFUNC void MFTYPE    MimStatCalculate(MIL_ID StatContextImId,
                                            MIL_ID SrcImageBufId,
                                            MIL_ID StatResultImId,
                                            MIL_INT64 ControlFlag);

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* REMAPPING: */

      /* -------------------------------------------------------------- */

MIL_DLLFUNC void MFTYPE MimRemap(MIL_ID RemapContextImId,
                                 MIL_ID SrcImageBufId,
                                 MIL_ID DstImageBufId,
                                 MIL_INT64 ControlFlag);


      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* TRANSFORM: */

      /* -------------------------------------------------------------- */

MIL_DLLFUNC void MFTYPE MimTransform            (MIL_ID SrcImageRBufId,
                                     MIL_ID SrcImageIBufId,
                                     MIL_ID DstImageRBufId,
                                     MIL_ID DstImageIBufId,
                                     MIL_INT64 TransformType,
                                     MIL_INT64 ControlFlag);


/* -------------------------------------------------------------- */
/* -------------------------------------------------------------- */

/* WAVELET TRANSFORM: */

/* -------------------------------------------------------------- */

MIL_DLLFUNC void MFTYPE MimWaveletTransform     (MIL_ID WaveletContextImId,
                                     MIL_ID SrcImageBufOrWaveletResultImId,
                                     MIL_ID DstImageBufOrWaveletResultImId,
                                     MIL_INT64 TransformType,
                                     MIL_INT Level,
                                     MIL_INT64 ControlFlag);


      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* WAVELET DENOISE: */

      /* -------------------------------------------------------------- */

MIL_DLLFUNC void MFTYPE MimWaveletDenoise (MIL_ID WaveletContextImId,
                                     MIL_ID SrcImageBufOrWaveletResultImId,
                                     MIL_ID DstImageBufOrWaveletResultImId,
                                     MIL_INT Level,
                                     MIL_ID DenoisingType,
                                     MIL_INT64 ControlFlag);

      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* SET FILTER FOR WAVELET TRANSFORM: */

      /* -------------------------------------------------------------- */

MIL_DLLFUNC void MFTYPE MimWaveletSetFilter     (MIL_ID    WaveletContextImId,
                                     MIL_ID    LowForwardRealFilterId,
                                     MIL_ID    HighForwardRealFilterId,
                                     MIL_ID    LowReverseRealFilterId,
                                     MIL_ID    HighReverseRealFilterId,
                                     MIL_ID    LowForwardImaginaryFilterId,
                                     MIL_ID    HighForwardImaginaryFilterId,
                                     MIL_ID    LowReverseImaginaryFilterId,
                                     MIL_ID    HighReverseImaginaryFilterId,
                                     MIL_INT64 ControlFlag);


      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* DRAW: */

      /* -------------------------------------------------------------- */

MIL_DLLFUNC void MFTYPE MimDrawDouble           (MIL_ID     ContextGraId,
                                     MIL_ID     Src1MilId,
                                     MIL_ID     Src2MilId,
                                     MIL_ID     DstImageBufOrListGraId,
                                     MIL_INT64  Operation,
                                     MIL_DOUBLE Param1,
                                     MIL_DOUBLE Param2,
                                     MIL_INT64  ControlFlag);

#endif // (!MIL_LITE)


#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus

inline void MFTYPE MimStreamCpp(MilStreamParam MemPtrOrFileName,
                                MIL_ID         SysId,
                                MIL_INT64      Operation,
                                MIL_INT64      StreamType,
                                MIL_DOUBLE     Version,
                                MIL_INT64      ControlFlag,
                                MIL_ID*        ContextImIdPtr,
                                MIL_INT*       SizeByteVarPtr)
   {
   MimStream(MemPtrOrFileName.m_Param, SysId, Operation, StreamType, Version, ControlFlag, ContextImIdPtr, SizeByteVarPtr);
   }

#undef  MimStream
#define MimStream MimStreamCpp

#endif // __cplusplus

#ifdef __cplusplus

inline bool M_IN_IM_INQUIRE_DOUBLE_RANGE(MIL_ID ContextOrResultId, MIL_INT64 InquireType)
   {
   if(M_NB_ELEMENTS_BIT_SET(InquireType))
      {
      return false;
      }

   switch (InquireType & M_MASK_MIM_INQUIRE_TYPE)
      {
      case M_FILTER_SMOOTHNESS: // case M_MODEL_IMAGE_TYPE:
         {
         MIL_INT ContextType = MimInquire(ContextOrResultId, M_INTERNAL_CONTEXT_TYPE, M_NULL);

         if (ContextType == M_LINEAR_FILTER_IIR_CONTEXT)
            {
            return true;
            }

         return false; // if (ContextType == M_MATCH_CONTEXT)
         }

      case M_DARK_CONST:
      case M_OFFSET_CONST:
      case M_FLAT_CONST:
      case M_GAIN_CONST:
      case M_EFFECTIVE_GAIN_CONST:
      case M_MAX_SCORE:
      case M_CLIP_LIMIT:
      case M_ALPHA_VALUE:
      case M_FREQUENCY_CUTOFF_RATIO_HIGH:
      case M_FREQUENCY_CUTOFF_RATIO_LOW:
      case M_MINIMUM_CONTRAST:
      case M_GLOBAL_MAX:
      case M_GLOBAL_MIN:
      case M_NIBLACK_BIAS:
      case M_GLOBAL_OFFSET:
      case M_NIBLACK_BIAS_SECOND_PASS:
      case M_GLOBAL_OFFSET_SECOND_PASS:
      case M_COND_HIGH:
      case M_COND_LOW:
      case M_FILTER_ASPECT_RATIO:
      case M_FILTER_DEFAULT_SHARPEN_PARAM:
      case M_AUG_ROTATION_OP_ANGLE_MAX:
      case M_AUG_ROTATION_OP_ANGLE_REF:
      case M_AUG_ROTATION_OP_ANGLE_DELTA:
      case M_AUG_ROTATION_OP_ANGLE_STEP:
      case M_AUG_TRANSLATION_X_OP_MAX:
      case M_AUG_TRANSLATION_Y_OP_MAX:
      case M_AUG_SCALE_OP_FACTOR_MIN:
      case M_AUG_SCALE_OP_FACTOR_MAX:
      case M_AUG_ASPECT_RATIO_OP_MIN:
      case M_AUG_ASPECT_RATIO_OP_MAX:
      case M_AUG_CROP_OP_FACTOR_X:
      case M_AUG_CROP_OP_FACTOR_Y:
      case M_AUG_SHEAR_X_OP_MIN:
      case M_AUG_SHEAR_X_OP_MAX:
      case M_AUG_SHEAR_Y_OP_MIN:
      case M_AUG_SHEAR_Y_OP_MAX:
      case M_AUG_LIGHTING_DIRECTIONAL_OP_INTENSITY_MAX:
      case M_AUG_LIGHTING_DIRECTIONAL_OP_INTENSITY_MIN:
      case M_AUG_LIGHTING_DIRECTIONAL_OP_ANGLE_MAX:
      case M_AUG_SATURATION_GAIN_OP_MIN:
      case M_AUG_SATURATION_GAIN_OP_MAX:
      case M_AUG_HSV_VALUE_GAIN_OP_MIN:
      case M_AUG_HSV_VALUE_GAIN_OP_MAX:
      case M_AUG_HUE_OFFSET_OP_MIN:
      case M_AUG_HUE_OFFSET_OP_MAX:
      case M_AUG_SMOOTH_DERICHE_OP_FACTOR_MIN:
      case M_AUG_SMOOTH_DERICHE_OP_FACTOR_MAX:
      case M_AUG_BLUR_MOTION_OP_ANGLE_MIN:
      case M_AUG_BLUR_MOTION_OP_ANGLE_MAX:
      case M_AUG_SHARPEN_DERICHE_OP_FACTOR_MIN:
      case M_AUG_SHARPEN_DERICHE_OP_FACTOR_MAX:
      case M_AUG_SMOOTH_GAUSSIAN_OP_STDDEV_MAX:
      case M_AUG_SMOOTH_GAUSSIAN_OP_STDDEV_MIN:
      case M_AUG_NOISE_SALT_PEPPER_OP_DENSITY:
      case M_AUG_NOISE_SALT_PEPPER_OP_DENSITY_DELTA:
      case M_AUG_NOISE_MULTIPLICATIVE_OP_STDDEV:
      case M_AUG_NOISE_MULTIPLICATIVE_OP_STDDEV_DELTA:
      case M_AUG_NOISE_MULTIPLICATIVE_OP_INTENSITY_MIN:
      case M_AUG_NOISE_GAUSSIAN_ADDITIVE_OP_STDDEV:
      case M_AUG_NOISE_GAUSSIAN_ADDITIVE_OP_STDDEV_DELTA:
      case M_AUG_INTENSITY_MULTIPLY_OP_DELTA:
      case M_AUG_INTENSITY_ADD_OP_DELTA:
      case M_GAMMA:
      case M_AUG_GAMMA_OP_DELTA:
      case M_AUG_DILATION_OP + M_PROBABILITY:
      case M_AUG_EROSION_OP + M_PROBABILITY:
      case M_AUG_DILATION_ASYM_OP + M_PROBABILITY:
      case M_AUG_EROSION_ASYM_OP + M_PROBABILITY:
      case M_AUG_FLIP_OP + M_PROBABILITY:
      case M_AUG_CROP_OP + M_PROBABILITY:
      case M_AUG_ROTATION_OP + M_PROBABILITY:
      case M_AUG_SCALE_OP + M_PROBABILITY:
      case M_AUG_TRANSLATION_X_OP + M_PROBABILITY:
      case M_AUG_TRANSLATION_Y_OP + M_PROBABILITY:
      case M_AUG_ASPECT_RATIO_OP + M_PROBABILITY:
      case M_AUG_SHEAR_X_OP + M_PROBABILITY:
      case M_AUG_SHEAR_Y_OP + M_PROBABILITY:
      case M_AUG_INTENSITY_MULTIPLY_OP + M_PROBABILITY:
      case M_AUG_INTENSITY_ADD_OP + M_PROBABILITY:
      case M_AUG_GAMMA_OP + M_PROBABILITY:
      case M_AUG_LIGHTING_DIRECTIONAL_OP + M_PROBABILITY:
      case M_AUG_SATURATION_GAIN_OP + M_PROBABILITY:
      case M_AUG_HUE_OFFSET_OP + M_PROBABILITY:
      case M_AUG_HSV_VALUE_GAIN_OP + M_PROBABILITY:
      case M_AUG_SMOOTH_DERICHE_OP + M_PROBABILITY:
      case M_AUG_SMOOTH_GAUSSIAN_OP + M_PROBABILITY:
      case M_AUG_BLUR_MOTION_OP + M_PROBABILITY:
      case M_AUG_SHARPEN_DERICHE_OP + M_PROBABILITY:
      case M_AUG_NOISE_GAUSSIAN_ADDITIVE_OP + M_PROBABILITY:
      case M_AUG_NOISE_MULTIPLICATIVE_OP + M_PROBABILITY:
      case M_AUG_NOISE_SALT_PEPPER_OP + M_PROBABILITY:
         {
         return true;
         }

      default:
         {
         break;
         }
      }

   return false;
   }

inline bool M_IN_IM_INQUIRE_MIL_INT64_RANGE(MIL_ID ContextOrResultId, MIL_INT64 InquireType)
   {
   UNREFERENCED_PARAMETER(ContextOrResultId);

   if(M_NB_ELEMENTS_BIT_SET(InquireType))
      {
      return false;
      }

   switch (InquireType & M_MASK_MIM_INQUIRE_TYPE)
      {
      case M_EXTENDED_CONTEXT_TYPE_DEPRECATED:
      case M_EXTENDED_RESULT_TYPE:
      case M_DEAD_PIXELS_IMAGE_ATTRIBUTE:
      case M_MODEL_IMAGE_ATTRIBUTE:
      case M_MASK_IMAGE_ATTRIBUTE:
      case M_ALLOCATED_TYPE:
         {
         return true;
         }

      default:
         {
         break;
         }
      }

   return false;
   }

inline bool M_IM_INQUIRE_MUST_HAVE_USER_PTR(MIL_ID ContextOrResultId, MIL_INT64 InquireType)
   {
   #if M_MIL_USE_64BIT

   return M_IN_IM_INQUIRE_DOUBLE_RANGE(ContextOrResultId, InquireType);

   #else

   return (M_IN_IM_INQUIRE_DOUBLE_RANGE(ContextOrResultId, InquireType) || M_IN_IM_INQUIRE_MIL_INT64_RANGE(ContextOrResultId, InquireType));

   #endif
   }

#endif

#if M_MIL_USE_64BIT
#ifdef __cplusplus
//////////////////////////////////////////////////////////////
// MbufControl function definition when compiling c++ files
//////////////////////////////////////////////////////////////
#if !M_MIL_USE_LINUX
inline void MimControl(MIL_ID ContextOrResultImId,
                       MIL_INT64 ControlType,
                       int ControlValue)
   {
   MimControlInt64(ContextOrResultImId, ControlType, ControlValue);
   };
#endif

inline void MimControl(MIL_ID ContextOrResultImId,
                       MIL_INT64 ControlType,
                       MIL_INT32 ControlValue)
   {
   MimControlInt64(ContextOrResultImId, ControlType, ControlValue);
   }

inline void MimControl(MIL_ID ContextOrResultImId,
                       MIL_INT64 ControlType,
                       MIL_INT64 ControlValue)
   {
   MimControlInt64(ContextOrResultImId, ControlType, ControlValue);
   }

inline void MimControl(MIL_ID ContextOrResultImId,
                       MIL_INT64 ControlType,
                       MIL_DOUBLE ControlValue)
   {
   MimControlDouble(ContextOrResultImId, ControlType, ControlValue);
   }

#else
//////////////////////////////////////////////////////////////
// For C file, call the default function, i.e. Int64 one
//////////////////////////////////////////////////////////////
#define MimControl  MimControlInt64

#endif // __cplusplus
#endif // M_MIL_USE_64BIT

#if(defined(__cplusplus))

//////////////////////////////////////////////////////////////
// MbufBinarize function definition when compiling c++ files
//////////////////////////////////////////////////////////////
inline MIL_INT MFTYPE MimBinarize(MIL_ID     SrcImageBufId,
                                  MIL_ID     DstImageBufId,
                                  MIL_INT64  ConditionAndThreshMode,
                                  MIL_DOUBLE LowParam,
                                  MIL_DOUBLE HighParam)
   {
   return   MimBinarizeDouble(SrcImageBufId, DstImageBufId, ConditionAndThreshMode, LowParam, HighParam);
   }

inline void MFTYPE MimClip(MIL_ID     SrcImageBufId,
                           MIL_ID     DstImageBufId,
                           MIL_INT64  Condition,
                           MIL_DOUBLE CondLow,
                           MIL_DOUBLE CondHigh,
                           MIL_DOUBLE WriteLow,
                           MIL_DOUBLE WriteHigh)
   {
   MimClipDouble(SrcImageBufId, DstImageBufId, Condition, CondLow, CondHigh, WriteLow, WriteHigh);
   }

inline void MFTYPE MimHistogramEqualize(MIL_ID      SrcImageBufId,
                                        MIL_ID      DstImageBufId,
                                        MIL_INT64   EqualizationType,
                                        MIL_DOUBLE  Alpha,
                                        MIL_DOUBLE  Min,
                                        MIL_DOUBLE  Max)
   {
   MimHistogramEqualizeDouble(SrcImageBufId, DstImageBufId, EqualizationType, Alpha, Min, Max);
   }

#if (!M_MIL_LITE)

inline void MFTYPE MimDraw(MIL_ID     ContextGraId,
                           MIL_ID     Src1MilId,
                           MIL_ID     Src2MilId,
                           MIL_ID     DstImageBufOrListGraId,
                           MIL_INT64  Operation,
                           MIL_DOUBLE Param1,
                           MIL_DOUBLE Param2,
                           MIL_INT64  ControlFlag)
   {
   MimDrawDouble(ContextGraId, Src1MilId, Src2MilId, DstImageBufOrListGraId, Operation, Param1, Param2, ControlFlag);
   }

inline void MFTYPE MimEdgeDetect(MIL_ID SrcImageBufId,
                                 MIL_ID DstIntensityImageBufId,
                                 MIL_ID DstAngleImageBufId,
                                 MIL_ID KernelId,
                                 MIL_INT64 ControlFlag,
                                 MIL_INT Threshold)
   {
   MimEdgeDetectMIL_INT(SrcImageBufId, DstIntensityImageBufId, DstAngleImageBufId, KernelId, ControlFlag, Threshold);
   }

inline MIL_INT MFTYPE MimLocateEvent(MIL_ID     SrcImageBufId,
                                     MIL_ID     EventResultImId,
                                     MIL_INT64  Condition,
                                     MIL_DOUBLE CondLow,
                                     MIL_DOUBLE CondHigh)
   {
   return MimLocateEventDouble(SrcImageBufId, EventResultImId, Condition, CondLow, CondHigh);
   }

inline void MFTYPE MimLocatePeak1d(MIL_ID ContextId,
                                   MIL_ID SrcImageBufId,
                                   MIL_ID ResultId,
                                   MIL_INT PeakWidthNominal,
                                   MIL_INT PeakWidthDelta,
                                   MIL_DOUBLE MinContrast,
                                   MIL_INT64 ControlFlag,
                                   MIL_DOUBLE ControlValue)
   {
   MimLocatePeak1dDouble(ContextId, SrcImageBufId, ResultId, PeakWidthNominal, PeakWidthDelta, MinContrast, ControlFlag, ControlValue);
   }


#endif

#else //#if(!defined(__cplusplus))

#define  MimBinarize                   MimBinarizeDouble
#define  MimClip                       MimClipDouble
#define  MimHistogramEqualize          MimHistogramEqualizeDouble

#if (!M_MIL_LITE)

#define  MimDraw                       MimDrawDouble
#define  MimEdgeDetect                 MimEdgeDetectMIL_INT
#define  MimLocateEvent                MimLocateEventDouble
#define  MimLocatePeak1d               MimLocatePeak1dDouble
#endif

#endif   //#if(defined(__cplusplus))

#define  MimGetResultSingle            MimGetResultSingleInt64

#if M_MIL_USE_SAFE_TYPE

//////////////////////////////////////////////////////////////
// See milos.h for explanation about these functions.
//////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------
// MimGetResult

inline void MFTYPE MimGetResultUnsafe  (MIL_ID ResultImId, MIL_INT64  ResultType, void           *UserArrayPtr);
inline void MFTYPE MimGetResultSafeType(MIL_ID ResultImId, MIL_INT64  ResultType, int             UserArrayPtr);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MimGetResultSafeType(MIL_ID ResultImId, MIL_INT64  ResultType, std::nullptr_t              );
#endif
inline void MFTYPE MimGetResultSafeType(MIL_ID ResultImId, MIL_INT64  ResultType, MIL_INT32      *UserArrayPtr);
inline void MFTYPE MimGetResultSafeType(MIL_ID ResultImId, MIL_INT64  ResultType, MIL_INT64      *UserArrayPtr);
inline void MFTYPE MimGetResultSafeType(MIL_ID ResultImId, MIL_INT64  ResultType, float          *UserArrayPtr);
inline void MFTYPE MimGetResultSafeType(MIL_ID ResultImId, MIL_INT64  ResultType, MIL_DOUBLE     *UserArrayPtr);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline void MFTYPE MimGetResultSafeType(MIL_ID ResultImId, MIL_INT64  ResultType, MIL_UINT32     *UserArrayPtr);
inline void MFTYPE MimGetResultSafeType(MIL_ID ResultImId, MIL_INT64  ResultType, MIL_UINT64     *UserArrayPtr);
#endif

//-------------------------------------------------------------------------------------
// MimGetResult1d

inline void MFTYPE MimGetResult1dUnsafe  (MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, void           *UserArrayPtr);
inline void MFTYPE MimGetResult1dSafeType(MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, int             UserArrayPtr);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MimGetResult1dSafeType(MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, std::nullptr_t              );
#endif
inline void MFTYPE MimGetResult1dSafeType(MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, MIL_INT32      *UserArrayPtr);
inline void MFTYPE MimGetResult1dSafeType(MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, MIL_INT64      *UserArrayPtr);
inline void MFTYPE MimGetResult1dSafeType(MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, float          *UserArrayPtr);
inline void MFTYPE MimGetResult1dSafeType(MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, MIL_DOUBLE     *UserArrayPtr);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline void MFTYPE MimGetResult1dSafeType(MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, MIL_UINT32     *UserArrayPtr);
inline void MFTYPE MimGetResult1dSafeType(MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, MIL_UINT64     *UserArrayPtr);
#endif

//-------------------------------------------------------------------------------------
// MimGetResult2d

inline void MFTYPE MimGetResult2dUnsafe  (MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, void           *UserArrayPtr);
inline void MFTYPE MimGetResult2dSafeType(MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, int             UserArrayPtr);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MimGetResult2dSafeType(MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, std::nullptr_t              );
#endif
inline void MFTYPE MimGetResult2dSafeType(MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, MIL_INT32      *UserArrayPtr);
inline void MFTYPE MimGetResult2dSafeType(MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, MIL_INT64      *UserArrayPtr);
inline void MFTYPE MimGetResult2dSafeType(MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, float          *UserArrayPtr);
inline void MFTYPE MimGetResult2dSafeType(MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, MIL_DOUBLE     *UserArrayPtr);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline void MFTYPE MimGetResult2dSafeType(MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, MIL_UINT32     *UserArrayPtr);
inline void MFTYPE MimGetResult2dSafeType(MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, MIL_UINT64     *UserArrayPtr);
#endif

//-------------------------------------------------------------------------------------
// MimGetResultSingle

inline void MFTYPE MimGetResultSingleUnsafe  (MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, void           *UserArrayPtr);
inline void MFTYPE MimGetResultSingleSafeType(MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, int             UserArrayPtr);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MimGetResultSingleSafeType(MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, std::nullptr_t              );
#endif
inline void MFTYPE MimGetResultSingleSafeType(MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, MIL_INT32      *UserArrayPtr);
inline void MFTYPE MimGetResultSingleSafeType(MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, MIL_INT64      *UserArrayPtr);
inline void MFTYPE MimGetResultSingleSafeType(MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, float          *UserArrayPtr);
inline void MFTYPE MimGetResultSingleSafeType(MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, MIL_DOUBLE     *UserArrayPtr);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline void MFTYPE MimGetResultSingleSafeType(MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, MIL_UINT32     *UserArrayPtr);
inline void MFTYPE MimGetResultSingleSafeType(MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, MIL_UINT64     *UserArrayPtr);
#endif   //#if(defined(__cplusplus))
//-------------------------------------------------------------------------------------
// MimGet

inline MIL_INT MFTYPE MimGetUnsafe  (MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, void        *Param1Ptr, void        *Param2Ptr, MIL_INT64 ControlFlag);
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, int         *Param1Ptr, int         *Param2Ptr, MIL_INT64 ControlFlag);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, std::nullptr_t        , std::nullptr_t        , MIL_INT64 ControlFlag);
#endif
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, MIL_INT32   *Param1Ptr, MIL_INT32   *Param2Ptr, MIL_INT64 ControlFlag);
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, MIL_INT64   *Param1Ptr, MIL_INT64   *Param2Ptr, MIL_INT64 ControlFlag);
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, float       *Param1Ptr, float       *Param2Ptr, MIL_INT64 ControlFlag);
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, MIL_DOUBLE  *Param1Ptr, MIL_DOUBLE  *Param2Ptr, MIL_INT64 ControlFlag);
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, char        *Param1Ptr, char        *Param2Ptr, MIL_INT64 ControlFlag);
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, short       *Param1Ptr, short       *Param2Ptr, MIL_INT64 ControlFlag);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, MIL_UINT32  *Param1Ptr, MIL_UINT32  *Param2Ptr, MIL_INT64 ControlFlag);
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, MIL_UINT64  *Param1Ptr, MIL_UINT64  *Param2Ptr, MIL_INT64 ControlFlag);
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, MIL_UINT8   *Param1Ptr, MIL_UINT8   *Param2Ptr, MIL_INT64 ControlFlag);
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, MIL_UINT16  *Param1Ptr, MIL_UINT16  *Param2Ptr, MIL_INT64 ControlFlag);
#endif

// ----------------------------------------------------------
// MimInquire

inline MIL_INT MFTYPE MimInquireUnsafe  (MIL_ID ContextOrResultImId, MIL_INT64  ParamToInquire, void        * ValuePtr);
inline MIL_INT MFTYPE MimInquireSafeType(MIL_ID ContextOrResultImId, MIL_INT64  ParamToInquire, int           ValuePtr);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE MimInquireSafeType(MIL_ID ContextOrResultImId, MIL_INT64  ParamToInquire, std::nullptr_t        );
#endif
inline MIL_INT MFTYPE MimInquireSafeType(MIL_ID ContextOrResultImId, MIL_INT64  ParamToInquire, MIL_INT32   * ValuePtr);
inline MIL_INT MFTYPE MimInquireSafeType(MIL_ID ContextOrResultImId, MIL_INT64  ParamToInquire, MIL_INT64   * ValuePtr);
inline MIL_INT MFTYPE MimInquireSafeType(MIL_ID ContextOrResultImId, MIL_INT64  ParamToInquire, MIL_DOUBLE  * ValuePtr);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline MIL_INT MFTYPE MimInquireSafeType(MIL_ID ContextOrResultImId, MIL_INT64  ParamToInquire, MIL_UINT32  * ValuePtr);
inline MIL_INT MFTYPE MimInquireSafeType(MIL_ID ContextOrResultImId, MIL_INT64  ParamToInquire, MIL_UINT64  * ValuePtr);
#endif

// -------------------------------------------------------------------------
// MimGetResult

inline MIL_INT64 RequiredTypeFromBufType(MIL_ID ResultImId)
   {
   MIL_INT Type = MbufInquire(ResultImId, M_TYPE, M_NULL);

   if (Type == 32+M_FLOAT)
      {
      return M_TYPE_FLOAT;
      }
   else if (Type == 64+M_FLOAT)
      {
      return M_TYPE_DOUBLE;
      }

   return M_TYPE_MIL_INT;
   }

inline bool IsAugmentResult(MIL_INT64 ResultType, MIL_INT64* ResultDataType)
   {
   bool bAskAvailable = (ResultType & M_AVAILABLE) == M_AVAILABLE;
   MIL_INT64 ResultTypeStripped = ResultType & ~M_AVAILABLE;
   bool bIsAugmentResultType = false;
   switch(ResultTypeStripped)
      {
      case M_AUG_DILATION_NB_ITERATIONS:
      case M_AUG_EROSION_NB_ITERATIONS:
      case M_AUG_DILATION_ASYM_NB_ITERATIONS:
      case M_AUG_DILATION_ASYM_SUBAREA:
      case M_AUG_EROSION_ASYM_NB_ITERATIONS:
      case M_AUG_EROSION_ASYM_SUBAREA:
      case M_AUG_FLIP_DIRECTION:
      case M_AUG_CROP_TOP_LEFT_X:
      case M_AUG_CROP_TOP_LEFT_Y:
      case M_AUG_CROP_BOTTOM_RIGHT_X:
      case M_AUG_CROP_BOTTOM_RIGHT_Y:
      case M_AUG_ROTATION_ANGLE:
      case M_AUG_SCALE_FACTOR:
      case M_AUG_TRANSLATION_X:
      case M_AUG_TRANSLATION_Y:
      case M_AUG_ASPECT_RATIO:
      case M_AUG_ASPECT_RATIO_MODE:
      case M_AUG_SHEAR_X:
      case M_AUG_SHEAR_Y:
      case M_AUG_INTENSITY_MULTIPLY_VALUE:
      case M_AUG_INTENSITY_ADD_VALUE:
      case M_AUG_GAMMA_VALUE_BAND_0:
      case M_AUG_GAMMA_VALUE_BAND_1:
      case M_AUG_GAMMA_VALUE_BAND_2:
      case M_AUG_LIGHTING_DIRECTIONAL_ANGLE:
      case M_AUG_SATURATION_GAIN:
      case M_AUG_HUE_OFFSET:
      case M_AUG_HSV_VALUE_GAIN:
      case M_AUG_SMOOTH_DERICHE_VALUE:
      case M_AUG_SMOOTH_GAUSSIAN_STDDEV:
      case M_AUG_BLUR_MOTION_SIZE:
      case M_AUG_BLUR_MOTION_ANGLE:
      case M_AUG_SHARPEN_DERICHE_VALUE:
      case M_AUG_NOISE_GAUSSIAN_ADDITIVE_STDDEV:
      case M_AUG_NOISE_MULTIPLICATIVE_STDDEV:
      case M_AUG_NOISE_SALT_PEPPER_DENSITY:
      case M_AUG_OPTIMAL_SIZE_X:
      case M_AUG_OPTIMAL_SIZE_Y:
      case M_AUG_SEED_USED:
      case M_AUG_REVERSE_TRANSFORMATION_MATRIX:
      case M_AUG_OPERATIONS_ENABLED:
      case M_AUG_OPERATIONS_APPLIED:
      case M_AUG_OPERATION_RESULT_TYPES:
      case M_AUG_OPERATION_ASSOCIATED_WITH_RESULT_TYPES:
         *ResultDataType = M_TYPE_MIL_DOUBLE;
         bIsAugmentResultType = true;
         break;

      default:
         bIsAugmentResultType = false;
         break;
      }
   if(bIsAugmentResultType)
      {
      if(bAskAvailable)
         *ResultDataType = M_TYPE_MIL_INT;
      return true;
      }
   else
      return false;

   }

inline MIL_INT64  MimGetResultRequiredType(MIL_ID ResultImId, MIL_INT64  ResultType)
   {
   /* MimAugment Result specific (include M_AVAILABLE) which is not available for other M_IM_RESULT */
   MIL_INT64 AugmentResultDataType;
   if(IsAugmentResult(ResultType, &AugmentResultDataType))
      return AugmentResultDataType;

   /* Other M_IM_RESULT*/
   switch (ResultType)
      {
      case M_NB_EVENT:
      case M_POSITION_X:
      case M_POSITION_Y:
      {
      // For these results, the doc specifies that MIL_INT is returned
      // except when allocated with 32+M_FLOAT, where a float is returned.
      return RequiredTypeFromBufType(ResultImId);
      }
      break;
   case M_VALUE:
      {
      // For M_VALUE, the doc specifies that MIL_INT is returned
      // except for M_PROJ_LIST, M_EXTREME_LIST, M_EVENT_LIST
      // allocated with 32+M_FLOAT, where a float is returned.
      MIL_INT64 IdResultType = 0;
      MimInquire(ResultImId, M_EXTENDED_RESULT_TYPE, &IdResultType);
      switch (IdResultType)
         {
      case M_PROJ_LIST:
      case M_EXTREME_LIST:
      case M_EVENT_LIST:
         {
         return RequiredTypeFromBufType(ResultImId);
         }
         break;
      default:
         return M_TYPE_MIL_INT;
         break;
         }
      }
      break;
   case M_ANGLE:
   case M_SCORE:
      {
      MIL_INT64 IdResultType = 0;
      MimInquire(ResultImId, M_EXTENDED_RESULT_TYPE, &IdResultType);
      switch (IdResultType)
         {
      case M_FIND_ORIENTATION_LIST:
         {
         return RequiredTypeFromBufType(ResultImId);
         }
         break;
      default:
         return M_TYPE_MIL_INT;
         break;
         }
      }
      break;

   case M_VALUE+M_PERCENTAGE:
   case M_CUMULATIVE_VALUE+M_PERCENTAGE:
   case M_PERCENTILE_VALUE:
   case M_NUMBER_OF_LEVELS:
   case M_TRANSFORMATION_MODE:
   case M_WAVELET_TYPE:
   case M_WAVELET_SIZE:
   case M_WAVELET_DRAW_SIZE_X:
   case M_WAVELET_DRAW_SIZE_Y:
   case M_WAVELET_DRAW_SIZE_X_WITH_PADDING:
   case M_WAVELET_DRAW_SIZE_Y_WITH_PADDING:
   case M_TRANSFORMATION_DOMAIN:
   case M_HIST_VALUE_OFFSET:
   case M_HIST_VALUE_RANGE:
   case M_HIST_REAL_SIZE:
   case M_ORIGINAL_IMAGE_SIZE_X:
   case M_ORIGINAL_IMAGE_SIZE_Y:
      return M_TYPE_MIL_INT;
      break;

   case M_CUMULATIVE_VALUE: /* case M_VALID: */
      {
      MIL_INT64 IdResultType = 0;

      MimInquire(ResultImId, M_EXTENDED_RESULT_TYPE, &IdResultType);

      switch (IdResultType)
         {
         case M_PROJ_LIST:
            {
            return RequiredTypeFromBufType(ResultImId);

            break;
            }

         default:
            {
            return M_TYPE_MIL_INT;

            break;
            }
         }

      break;
      }

   case M_WAVELET_COEFFICIENTS_IMAGE_ID:
   case M_WAVELET_COEFFICIENTS_IMAGE_ID + M_REAL_PART:
   case M_WAVELET_COEFFICIENTS_IMAGE_ID + M_IMAGINARY_PART:
      return M_TYPE_MIL_ID;
      break;

   case M_WAVELET_LEVEL_SIZE_X:
   case M_WAVELET_LEVEL_SIZE_Y:
   case M_WAVELET_LEVEL_PADDING_OFFSET_X:
   case M_WAVELET_LEVEL_PADDING_OFFSET_Y:
      return M_TYPE_DOUBLE;
      break;

   case M_ASSOCIATED_CONTEXT_TYPE:
      return M_TYPE_MIL_INT;
      break;

   default:
      {
      MIL_INT64 IdResultType = 0;
      MimInquire(ResultImId, M_EXTENDED_RESULT_TYPE, &IdResultType);
      if (M_LOCATE_PEAK_1D_RESULT == IdResultType)
         return M_TYPE_MIL_INT;
      }
      return M_TYPE_DOUBLE;
      break;
      }
   }


inline MIL_INT64 MimGetRequiredType(MIL_INT64 ResultType)
   {
   UNREFERENCED_PARAMETER(ResultType);

   return M_TYPE_MIL_INT;
   }

inline void MFTYPE MimGetResultSafeType(MIL_ID ResultImId, MIL_INT64 ResultType, int UserArrayPtr)
   {
   if (UserArrayPtr)
      SafeTypeError(MIL_TEXT("MimGetResult"));

   MimGetResult(ResultImId, ResultType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MimGetResultSafeType(MIL_ID ResultImId, MIL_INT64 ResultType, std::nullptr_t)
   {
   MimGetResult(ResultImId, ResultType, NULL);
   }
#endif

inline void MimGetResultSafeTypeExecute (MIL_ID ResultImId, MIL_INT64 ResultType, void *UserArrayPtr, MIL_INT64  GivenType)
   {
   MIL_INT64  RequiredType = ExtractTypeFromValue(ResultType, M_TYPE_DOUBLE, M_TYPE_MIL_INT32, M_TYPE_MIL_INT64, M_TYPE_FLOAT);
   if (RequiredType == 0)
      RequiredType = MimGetResultRequiredType(ResultImId, ResultType);

   if (RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("MimGetResult"));

   MimGetResult(ResultImId, ResultType, UserArrayPtr);
   }


inline void MFTYPE MimGetResultUnsafe  (MIL_ID ResultImId, MIL_INT64  ResultType, void        *UserArrayPtr) {MimGetResult               (ResultImId, ResultType, UserArrayPtr);}
inline void MFTYPE MimGetResultSafeType(MIL_ID ResultImId, MIL_INT64  ResultType, MIL_INT32   *UserArrayPtr) {MimGetResultSafeTypeExecute(ResultImId, ResultType, UserArrayPtr, M_TYPE_MIL_INT32);}
inline void MFTYPE MimGetResultSafeType(MIL_ID ResultImId, MIL_INT64  ResultType, MIL_INT64   *UserArrayPtr) {MimGetResultSafeTypeExecute(ResultImId, ResultType, UserArrayPtr, M_TYPE_MIL_INT64);}
inline void MFTYPE MimGetResultSafeType(MIL_ID ResultImId, MIL_INT64  ResultType, float       *UserArrayPtr) {MimGetResultSafeTypeExecute(ResultImId, ResultType, UserArrayPtr, M_TYPE_FLOAT);}
inline void MFTYPE MimGetResultSafeType(MIL_ID ResultImId, MIL_INT64  ResultType, MIL_DOUBLE  *UserArrayPtr) {MimGetResultSafeTypeExecute(ResultImId, ResultType, UserArrayPtr, M_TYPE_DOUBLE);}
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline void MFTYPE MimGetResultSafeType(MIL_ID ResultImId, MIL_INT64  ResultType, MIL_UINT32  *UserArrayPtr) {MimGetResultSafeTypeExecute(ResultImId, ResultType, UserArrayPtr, M_TYPE_MIL_INT32);}
inline void MFTYPE MimGetResultSafeType(MIL_ID ResultImId, MIL_INT64  ResultType, MIL_UINT64  *UserArrayPtr) {MimGetResultSafeTypeExecute(ResultImId, ResultType, UserArrayPtr, M_TYPE_MIL_INT64);}
#endif

// -------------------------------------------------------------------------
// MimGetResult1d

inline void MFTYPE MimGetResult1dSafeType(MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, int UserArrayPtr)
   {
   if (UserArrayPtr)
      SafeTypeError(MIL_TEXT("MimGetResult1d"));

   MimGetResult1d(ResultImId, OffEntry, NbEntries, ResultType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MimGetResult1dSafeType(MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, std::nullptr_t)
   {
   MimGetResult1d(ResultImId, OffEntry, NbEntries, ResultType, NULL);
   }
#endif

inline void MimGetResult1dSafeTypeExecute (MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, void *UserArrayPtr, MIL_INT64  GivenType)
   {
   MIL_INT64  RequiredType = ExtractTypeFromValue(ResultType, M_TYPE_DOUBLE, M_TYPE_MIL_INT32, M_TYPE_MIL_INT64, M_TYPE_FLOAT);
   if (RequiredType == 0)
      RequiredType = MimGetResultRequiredType(ResultImId, ResultType);

   if (RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("MimGetResult1d"));

   MimGetResult1d(ResultImId, OffEntry, NbEntries, ResultType, UserArrayPtr);
   }

inline void MFTYPE MimGetResult1dUnsafe  (MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, void        *UserArrayPtr){MimGetResult1d               (ResultImId, OffEntry, NbEntries, ResultType, UserArrayPtr);}
inline void MFTYPE MimGetResult1dSafeType(MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, MIL_INT32   *UserArrayPtr){MimGetResult1dSafeTypeExecute(ResultImId, OffEntry, NbEntries, ResultType, UserArrayPtr, M_TYPE_MIL_INT32);}
inline void MFTYPE MimGetResult1dSafeType(MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, MIL_INT64   *UserArrayPtr){MimGetResult1dSafeTypeExecute(ResultImId, OffEntry, NbEntries, ResultType, UserArrayPtr, M_TYPE_MIL_INT64);}
inline void MFTYPE MimGetResult1dSafeType(MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, float       *UserArrayPtr){MimGetResult1dSafeTypeExecute(ResultImId, OffEntry, NbEntries, ResultType, UserArrayPtr, M_TYPE_FLOAT);}
inline void MFTYPE MimGetResult1dSafeType(MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, MIL_DOUBLE  *UserArrayPtr){MimGetResult1dSafeTypeExecute(ResultImId, OffEntry, NbEntries, ResultType, UserArrayPtr, M_TYPE_DOUBLE);}
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline void MFTYPE MimGetResult1dSafeType(MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, MIL_UINT32  *UserArrayPtr){MimGetResult1dSafeTypeExecute(ResultImId, OffEntry, NbEntries, ResultType, UserArrayPtr, M_TYPE_MIL_INT32);}
inline void MFTYPE MimGetResult1dSafeType(MIL_ID ResultImId, MIL_INT OffEntry, MIL_INT NbEntries, MIL_INT64  ResultType, MIL_UINT64  *UserArrayPtr){MimGetResult1dSafeTypeExecute(ResultImId, OffEntry, NbEntries, ResultType, UserArrayPtr, M_TYPE_MIL_INT64);}
#endif

// -------------------------------------------------------------------------
// MimGetResult2d

inline void MFTYPE MimGetResult2dSafeType(MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, int UserArrayPtr)
   {
   if(UserArrayPtr)
      SafeTypeError(MIL_TEXT("MimGetResult2d"));

   MimGetResult2d(ResultImId, OffsetX, OffsetY, SizeX, SizeY, ResultType, ControlFlag, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MimGetResult2dSafeType(MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, std::nullptr_t)
   {
   MimGetResult2d(ResultImId, OffsetX, OffsetY, SizeX, SizeY, ResultType, ControlFlag, NULL);
   }
#endif

inline void MimGetResult2dSafeTypeExecute (MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, void *UserArrayPtr, MIL_INT64  GivenType)
   {
   MIL_INT64  RequiredType = ExtractTypeFromValue(ResultType, M_TYPE_DOUBLE, M_TYPE_MIL_INT32, M_TYPE_MIL_INT64, M_TYPE_FLOAT);
   if (RequiredType == 0)
      RequiredType = MimGetResultRequiredType(ResultImId, ResultType);

   if (RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("MimGetResult2d"));

   MimGetResult2d(ResultImId, OffsetX, OffsetY, SizeX, SizeY, ResultType, ControlFlag, UserArrayPtr);
   }

inline void MFTYPE MimGetResult2dUnsafe  (MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, void        *UserArrayPtr){MimGetResult2d               (ResultImId, OffsetX, OffsetY, SizeX, SizeY, ResultType, ControlFlag, UserArrayPtr);}
inline void MFTYPE MimGetResult2dSafeType(MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, MIL_INT32   *UserArrayPtr){MimGetResult2dSafeTypeExecute(ResultImId, OffsetX, OffsetY, SizeX, SizeY, ResultType, ControlFlag, UserArrayPtr, M_TYPE_MIL_INT32);}
inline void MFTYPE MimGetResult2dSafeType(MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, MIL_INT64   *UserArrayPtr){MimGetResult2dSafeTypeExecute(ResultImId, OffsetX, OffsetY, SizeX, SizeY, ResultType, ControlFlag, UserArrayPtr, M_TYPE_MIL_INT64);}
inline void MFTYPE MimGetResult2dSafeType(MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, float       *UserArrayPtr){MimGetResult2dSafeTypeExecute(ResultImId, OffsetX, OffsetY, SizeX, SizeY, ResultType, ControlFlag, UserArrayPtr, M_TYPE_FLOAT);}
inline void MFTYPE MimGetResult2dSafeType(MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, MIL_DOUBLE  *UserArrayPtr){MimGetResult2dSafeTypeExecute(ResultImId, OffsetX, OffsetY, SizeX, SizeY, ResultType, ControlFlag, UserArrayPtr, M_TYPE_DOUBLE);}
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline void MFTYPE MimGetResult2dSafeType(MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, MIL_UINT32  *UserArrayPtr){MimGetResult2dSafeTypeExecute(ResultImId, OffsetX, OffsetY, SizeX, SizeY, ResultType, ControlFlag, UserArrayPtr, M_TYPE_MIL_INT32);}
inline void MFTYPE MimGetResult2dSafeType(MIL_ID ResultImId, MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT64  ResultType, MIL_INT64  ControlFlag, MIL_UINT64  *UserArrayPtr){MimGetResult2dSafeTypeExecute(ResultImId, OffsetX, OffsetY, SizeX, SizeY, ResultType, ControlFlag, UserArrayPtr, M_TYPE_MIL_INT64);}
#endif

// -------------------------------------------------------------------------
// MimGetResultSingle

inline void MFTYPE MimGetResultSingleSafeType(MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, int UserArrayPtr)
   {
   if(UserArrayPtr)
      SafeTypeError(MIL_TEXT("MimGetResultSingle"));

   MimGetResultSingleInt64(ResultImId, Index1, Index2,ResultType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MimGetResultSingleSafeType(MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, std::nullptr_t)
   {
   MimGetResultSingleInt64(ResultImId, Index1, Index2, ResultType, NULL);
   }
#endif

inline void MFTYPE MimGetResultSingleSafeTypeExecute (MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, void *UserArrayPtr, MIL_INT64  GivenType)
   {
   MIL_INT64  RequiredType = ExtractTypeFromValue(ResultType, M_TYPE_DOUBLE, M_TYPE_MIL_INT32, M_TYPE_MIL_INT64, M_TYPE_FLOAT, M_TYPE_MIL_ID);
   if (RequiredType == 0)
      RequiredType = MimGetResultRequiredType(ResultImId, ResultType);

   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if (RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("MimGetResultSingle"));

   MimGetResultSingleInt64(ResultImId, Index1, Index2, ResultType, UserArrayPtr);
   }

inline void MFTYPE MimGetResultSingleUnsafe  (MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, void        *UserArrayPtr){MimGetResultSingleInt64          (ResultImId, Index1, Index2, ResultType, UserArrayPtr);}
inline void MFTYPE MimGetResultSingleSafeType(MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, MIL_INT32   *UserArrayPtr){MimGetResultSingleSafeTypeExecute(ResultImId, Index1, Index2, ResultType, UserArrayPtr, M_TYPE_MIL_INT32);}
inline void MFTYPE MimGetResultSingleSafeType(MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, MIL_INT64   *UserArrayPtr){MimGetResultSingleSafeTypeExecute(ResultImId, Index1, Index2, ResultType, UserArrayPtr, M_TYPE_MIL_INT64);}
inline void MFTYPE MimGetResultSingleSafeType(MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, float       *UserArrayPtr){MimGetResultSingleSafeTypeExecute(ResultImId, Index1, Index2, ResultType, UserArrayPtr, M_TYPE_FLOAT);}
inline void MFTYPE MimGetResultSingleSafeType(MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, MIL_DOUBLE  *UserArrayPtr){MimGetResultSingleSafeTypeExecute(ResultImId, Index1, Index2, ResultType, UserArrayPtr, M_TYPE_DOUBLE);}
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline void MFTYPE MimGetResultSingleSafeType(MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, MIL_UINT32  *UserArrayPtr){MimGetResultSingleSafeTypeExecute(ResultImId, Index1, Index2, ResultType, UserArrayPtr, M_TYPE_MIL_INT32);}
inline void MFTYPE MimGetResultSingleSafeType(MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64 ResultType, MIL_UINT64  *UserArrayPtr){MimGetResultSingleSafeTypeExecute(ResultImId, Index1, Index2, ResultType, UserArrayPtr, M_TYPE_MIL_INT64);}
#endif


// -------------------------------------------------------------------------
// MimGet

inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, int Param1Ptr, int ParamPtr2, MIL_INT64 ControlFlag)
   {
   if(Param1Ptr)
      SafeTypeError(MIL_TEXT("MimGet"));

   if(ParamPtr2)
      SafeTypeError(MIL_TEXT("MimGet"));

   return MimGet(ContextImId, GetType, ArraySize, NULL, NULL, ControlFlag);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, std::nullptr_t, std::nullptr_t, MIL_INT64 ControlFlag)
   {
   return MimGet(ContextImId, GetType, ArraySize, NULL, NULL, ControlFlag);
   }
#endif

inline MIL_INT MimGetSafeTypeExecute (MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, void *Param1Ptr, void *ParamPtr2, MIL_INT64 ControlFlag, MIL_INT64  GivenType)
   {
   MIL_INT64  RequiredType = ExtractTypeFromValue(GetType, M_TYPE_DOUBLE, M_TYPE_MIL_INT32, M_TYPE_MIL_INT64, M_TYPE_FLOAT, M_TYPE_MIL_ID, M_TYPE_CHAR, M_TYPE_SHORT);
   if (RequiredType == 0)
      RequiredType = MimGetRequiredType(GetType);

   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if (RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("MimGet"));

   return MimGet(ContextImId, GetType, ArraySize, Param1Ptr, ParamPtr2, ControlFlag);
   }

inline MIL_INT MFTYPE MimGetUnsafe  (MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, void        *Param1Ptr, void        *Param2Ptr, MIL_INT64 ControlFlag){return MimGet               (ContextImId, GetType, ArraySize, Param1Ptr, Param2Ptr, ControlFlag);}
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, MIL_INT32   *Param1Ptr, MIL_INT32   *Param2Ptr, MIL_INT64 ControlFlag){return MimGetSafeTypeExecute(ContextImId, GetType, ArraySize, Param1Ptr, Param2Ptr, ControlFlag, M_TYPE_MIL_INT32);}
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, MIL_INT64   *Param1Ptr, MIL_INT64   *Param2Ptr, MIL_INT64 ControlFlag){return MimGetSafeTypeExecute(ContextImId, GetType, ArraySize, Param1Ptr, Param2Ptr, ControlFlag, M_TYPE_MIL_INT64);}
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, float       *Param1Ptr, float       *Param2Ptr, MIL_INT64 ControlFlag){return MimGetSafeTypeExecute(ContextImId, GetType, ArraySize, Param1Ptr, Param2Ptr, ControlFlag, M_TYPE_FLOAT);}
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, MIL_DOUBLE  *Param1Ptr, MIL_DOUBLE  *Param2Ptr, MIL_INT64 ControlFlag){return MimGetSafeTypeExecute(ContextImId, GetType, ArraySize, Param1Ptr, Param2Ptr, ControlFlag, M_TYPE_DOUBLE);}
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, char        *Param1Ptr, char        *Param2Ptr, MIL_INT64 ControlFlag){return MimGetSafeTypeExecute(ContextImId, GetType, ArraySize, Param1Ptr, Param2Ptr, ControlFlag, M_TYPE_CHAR);}
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, short       *Param1Ptr, short       *Param2Ptr, MIL_INT64 ControlFlag){return MimGetSafeTypeExecute(ContextImId, GetType, ArraySize, Param1Ptr, Param2Ptr, ControlFlag, M_TYPE_SHORT);}
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, MIL_UINT32  *Param1Ptr, MIL_UINT32  *Param2Ptr, MIL_INT64 ControlFlag){return MimGetSafeTypeExecute(ContextImId, GetType, ArraySize, Param1Ptr, Param2Ptr, ControlFlag, M_TYPE_MIL_INT32);}
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, MIL_UINT64  *Param1Ptr, MIL_UINT64  *Param2Ptr, MIL_INT64 ControlFlag){return MimGetSafeTypeExecute(ContextImId, GetType, ArraySize, Param1Ptr, Param2Ptr, ControlFlag, M_TYPE_MIL_INT64);}
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, MIL_UINT8   *Param1Ptr, MIL_UINT8   *Param2Ptr, MIL_INT64 ControlFlag){return MimGetSafeTypeExecute(ContextImId, GetType, ArraySize, Param1Ptr, Param2Ptr, ControlFlag, M_TYPE_CHAR);}
inline MIL_INT MFTYPE MimGetSafeType(MIL_ID ContextImId, MIL_INT64 GetType, MIL_INT ArraySize, MIL_UINT16  *Param1Ptr, MIL_UINT16  *Param2Ptr, MIL_INT64 ControlFlag){return MimGetSafeTypeExecute(ContextImId, GetType, ArraySize, Param1Ptr, Param2Ptr, ControlFlag, M_TYPE_SHORT);}
#endif
// ----------------------------------------------------------
// MimInquire

inline MIL_INT64 MimInquireRequiredType(MIL_ID ContextOrResultId, MIL_INT64 InquireType)
   {
   MIL_INT64  DataType = ExtractTypeFromValue(InquireType, M_TYPE_DOUBLE, M_TYPE_MIL_ID, M_TYPE_MIL_INT32, M_TYPE_MIL_INT64);

   if (DataType)
      return DataType;

   if (M_IN_IM_INQUIRE_DOUBLE_RANGE(ContextOrResultId, InquireType))
      return M_TYPE_DOUBLE;

   if (M_IN_IM_INQUIRE_MIL_INT64_RANGE(ContextOrResultId, InquireType))
      return M_TYPE_MIL_INT64;

   return M_TYPE_MIL_INT;
   }

inline MIL_INT MFTYPE MimInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, int UserVarPtr)
   {
   bool MustHaveUserPointer = M_IM_INQUIRE_MUST_HAVE_USER_PTR(ContextOrResultId, InquireType);

   if (UserVarPtr || MustHaveUserPointer)
      SafeTypeError(MIL_TEXT("MimInquire"));

   return MimInquire(ContextOrResultId, InquireType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE MimInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, std::nullptr_t)
   {
   bool MustHaveUserPointer = M_IM_INQUIRE_MUST_HAVE_USER_PTR(ContextOrResultId, InquireType);

   if(MustHaveUserPointer)
      SafeTypeError(MIL_TEXT("MimInquire"));

   return MimInquire(ContextOrResultId, InquireType, NULL);
   }
#endif

inline MIL_INT MFTYPE MimInquireSafeTypeExecute (MIL_ID ContextOrResultId, MIL_INT64  InquireType, void  *UserVarPtr, MIL_INT64  GivenType)
   {
   MIL_INT64  RequiredType = MimInquireRequiredType(ContextOrResultId, InquireType);
   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if (RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("MimInquire"));

   return MimInquire(ContextOrResultId, InquireType, UserVarPtr);
   }

inline MIL_INT MFTYPE MimInquireUnsafe  (MIL_ID ContextOrResultId, MIL_INT64  InquireType, void        *UserVarPtr) {return MimInquire               (ContextOrResultId, InquireType, UserVarPtr                  );}
inline MIL_INT MFTYPE MimInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, MIL_INT32   *UserVarPtr) {return MimInquireSafeTypeExecute(ContextOrResultId, InquireType, UserVarPtr, M_TYPE_MIL_INT32);}
inline MIL_INT MFTYPE MimInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, MIL_INT64   *UserVarPtr) {return MimInquireSafeTypeExecute(ContextOrResultId, InquireType, UserVarPtr, M_TYPE_MIL_INT64);}
inline MIL_INT MFTYPE MimInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, MIL_DOUBLE  *UserVarPtr) {return MimInquireSafeTypeExecute(ContextOrResultId, InquireType, UserVarPtr, M_TYPE_DOUBLE   );}
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline MIL_INT MFTYPE MimInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, MIL_UINT32  *UserVarPtr) {return MimInquireSafeTypeExecute(ContextOrResultId, InquireType, UserVarPtr, M_TYPE_MIL_INT32);}
inline MIL_INT MFTYPE MimInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, MIL_UINT64  *UserVarPtr) {return MimInquireSafeTypeExecute(ContextOrResultId, InquireType, UserVarPtr, M_TYPE_MIL_INT64);}
#endif

#define MimGet               MimGetSafeType
#define MimGetResult         MimGetResultSafeType
#define MimGetResult1d       MimGetResult1dSafeType
#define MimGetResult2d       MimGetResult2dSafeType
#if (defined(MimGetResultSingle))
#undef MimGetResultSingle
#endif
#define MimGetResultSingle   MimGetResultSingleSafeType
#define MimInquire           MimInquireSafeType

#else // #if M_MIL_USE_SAFE_TYPE

#define MimGetUnsafe               MimGet
#define MimGetResultUnsafe         MimGetResult
#define MimGetResult1dUnsafe       MimGetResult1d
#define MimGetResult2dUnsafe       MimGetResult2d
#define MimGetResultSingleUnsafe   MimGetResultSingle
#define MimInquireUnsafe           MimInquire

#endif // #if M_MIL_USE_SAFE_TYPE

// ----------------------------------------------------------
// Overload for std::vector.
#if defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR
template <typename UserType>
inline void MFTYPE MimGetResult(MIL_ID ResultImId, MIL_INT64  ResultType, std::vector<UserType> &UserArrayPtr)
   {
   //! If the given MIL data type is not the same as the SrcType, change it to the correct one
   //! and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(ResultType) != 0)
      {
      SafeTypeError(MIL_TEXT("MimGetResult"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   ResultType = M_STRIP_HLVLDATATYPE(ResultType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   MimGetResult(ResultImId, M_STRIP_HLVLDATATYPE(ResultType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   UserArrayPtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      MimGetResult(ResultImId, ResultType, &UserArrayPtr[0]);
      }
   }
template <typename UserType>
inline void MFTYPE MimGetResultSingle(MIL_ID ResultImId, MIL_INT64 Index1, MIL_INT64 Index2, MIL_INT64  ResultType, std::vector<UserType> &UserArrayPtr)
   {
   //! If the given MIL data type is not the same as the SrcType, change it to the correct one
   //! and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(ResultType) != 0)
      {
      SafeTypeError(MIL_TEXT("MimGetResultSingle"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   ResultType = M_STRIP_HLVLDATATYPE(ResultType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   MimGetResultSingle(ResultImId, Index1, Index2, M_STRIP_HLVLDATATYPE(ResultType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   UserArrayPtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      MimGetResultSingle(ResultImId, Index1, Index2, ResultType, &UserArrayPtr[0]);
      }
   }

// ----------------------------------------------------------
// Overloads for std::vector in MimDeinterlace.
inline void MFTYPE MimDeinterlace(MIL_ID                     DeinterlaceContextImId,
                                  const std::vector<MIL_ID>& SrcImageArrayPtr,
                                  const std::vector<MIL_ID>& DstImageArrayPtr,
                                  MIL_INT                    SrcImageCount,
                                  MIL_INT                    DstImageCount,
                                  MIL_INT64                  ControlFlag)
   {
#if M_MIL_USE_SAFE_TYPE
   if(SrcImageCount <= 0)
      {
      SafeTypeError(MIL_TEXT("MimDeinterlace"), MIL_TEXT("SrcImageCount parameter must be greater than zero."));
      }
   if(DstImageCount <= 0)
      {
      SafeTypeError(MIL_TEXT("MimDeinterlace"), MIL_TEXT("DstImageCount parameter must be greater than zero."));
      }
   if(SrcImageArrayPtr.empty() || DstImageArrayPtr.empty())
      {
      SafeTypeError(MIL_TEXT("MimDeinterlace"), MIL_TEXT("The input vectors cannot be empty."));
      }
   if(SrcImageCount > (MIL_INT)SrcImageArrayPtr.size() && SrcImageCount != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("MimDeinterlace"), MIL_TEXT("SrcImageCount parameter must be smaller or equal (M_DEFAULT) to the size of input vector."));
      }
   if(DstImageCount > (MIL_INT)DstImageArrayPtr.size() && DstImageCount != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("MimDeinterlace"), MIL_TEXT("DstImageCount parameter must be smaller or equal (M_DEFAULT) to the size of input vector."));
      }
#endif

   if(SrcImageCount == M_DEFAULT || SrcImageCount > (MIL_INT)SrcImageArrayPtr.size())
      {
      SrcImageCount = (MIL_INT)SrcImageArrayPtr.size();
      }
   if(DstImageCount == M_DEFAULT || DstImageCount > (MIL_INT)DstImageArrayPtr.size())
      {
      DstImageCount = (MIL_INT)DstImageArrayPtr.size();
      }

   MimDeinterlace(DeinterlaceContextImId,
                  &SrcImageArrayPtr[0],
                  &DstImageArrayPtr[0],
                  SrcImageCount,
                  DstImageCount,
                  ControlFlag);
   }

// ----------------------------------------------------------
// Overloads for std::vector in MimGet with two output parameters
template <typename UserType>
inline MIL_INT MFTYPE MimGet(MIL_ID                ContextImId,
                             MIL_INT64             GetType,
                             MIL_INT               ArraySize,
                             std::vector<UserType> &Param1Ptr,
                             std::vector<UserType> &Param2Ptr,
                             MIL_INT64             ControlFlag)
   {
#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(GetType) != 0)
      {
      SafeTypeError(MIL_TEXT("MimGet"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   GetType = M_STRIP_HLVLDATATYPE(GetType) + MilTraits<UserType>::TypeFlag;

   bool InternalArraySizeSpecified = true;

   if(ArraySize == M_DEFAULT)
      {
      InternalArraySizeSpecified = false;
      ArraySize = 0;
      ArraySize = MimGet(ContextImId, M_STRIP_HLVLDATATYPE(GetType), M_NULL, M_NULL, M_NULL, ControlFlag);
      }

   if(ArraySize >= 0)
      {
      Param1Ptr.resize(ArraySize);
      Param2Ptr.resize(ArraySize);
      }

   // Call the original function in case the ArraySize parameter is specified.
   // It is to allow the MIL function to pop an MIL error if the ArraySize is invalid.
   // But, if the ArraySize is M_DEFAULT and that M3dmapGet outputs an MIL error,
   // the following condition will ensure to not recall the same function.
   if(ArraySize > 0 || InternalArraySizeSpecified)
      {
      MIL_INT InternalNbEntriesForStdVector = MimGet(ContextImId,
                                                  GetType,
                                                  ArraySize,
                                                  &Param1Ptr[0],
                                                  &Param2Ptr[0],
                                                  ControlFlag);

      if(InternalNbEntriesForStdVector < ArraySize && ArraySize != M_DEFAULT)
         {
         Param1Ptr.resize(InternalNbEntriesForStdVector);
         Param2Ptr.resize(InternalNbEntriesForStdVector);
         }
      return InternalNbEntriesForStdVector;
      }
   return 0;
   }

// ----------------------------------------------------------
// Overloads for std::vector in MimGet with only one output parameter.
template <typename UserType>
inline MIL_INT MFTYPE MimGet(MIL_ID                ContextImId,
                             MIL_INT64             GetType,
                             MIL_INT               ArraySize,
                             std::vector<UserType> &Param1Ptr,
                             void*                 Param2Ptr,
                             MIL_INT64             ControlFlag)
   {
#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(GetType) != 0)
      SafeTypeError(MIL_TEXT("MimGet"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
#endif

   GetType = M_STRIP_HLVLDATATYPE(GetType) + MilTraits<UserType>::TypeFlag;

   if(ArraySize == M_DEFAULT)
      {
      ArraySize = 0;
      ArraySize = MimGet(ContextImId, M_STRIP_HLVLDATATYPE(GetType), M_NULL, M_NULL, M_NULL, ControlFlag);
      }
   if(ArraySize >= 0)
      Param1Ptr.resize(ArraySize);
   if(ArraySize > 0)
      {
      MIL_INT InternalNbEntriesForStdVector = MimGet(ContextImId,
                                                     GetType,
                                                     ArraySize,
                                                     &Param1Ptr[0],
                                                     (UserType*)Param2Ptr,
                                                     ControlFlag);
      if(InternalNbEntriesForStdVector < ArraySize && ArraySize != M_DEFAULT)
         Param1Ptr.resize(InternalNbEntriesForStdVector);

      return InternalNbEntriesForStdVector;
      }
   return 0;
   }


// ----------------------------------------------------------
// Overloads for std::vector in MimGetResult1d.
template <typename UserType>
inline void MFTYPE MimGetResult1d(MIL_ID                ResultImId,
                                  MIL_INT               OffEntry,
                                  MIL_INT               NbEntries,
                                  MIL_INT64             ResultType,
                                  std::vector<UserType> &UserArrayPtr)
   {
#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(ResultType) != 0)
      {
      SafeTypeError(MIL_TEXT("MimGetResult1d"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
   if(NbEntries <= 0)
      {
      SafeTypeError(MIL_TEXT("MimGetResult1d"), MIL_TEXT("NbEntries must be greater than zero."));
      }
#endif

   ResultType = M_STRIP_HLVLDATATYPE(ResultType) + MilTraits<UserType>::TypeFlag;

   UserArrayPtr.resize(NbEntries);

   MimGetResult1d(ResultImId,
                  OffEntry,
                  NbEntries,
                  ResultType,
                  &UserArrayPtr[0]);
   }

// ----------------------------------------------------------
// Overloads for std::vector in MimGetResult2d.
template <typename UserType>
inline void MimGetResult2d(MIL_ID                ResultImId,
                           MIL_INT               OffsetX,
                           MIL_INT               OffsetY,
                           MIL_INT               SizeX,
                           MIL_INT               SizeY,
                           MIL_INT64             ResultType,
                           MIL_INT64             ControlFlag,
                           std::vector<UserType> &UserArrayPtr)
   {
#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(ResultType) != 0)
      {
      SafeTypeError(MIL_TEXT("MimGetResult2d"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
   if(SizeX <= 0 || SizeY <= 0)
      {
      SafeTypeError(MIL_TEXT("MimGetResult2d"), MIL_TEXT("SizeX and SizeY must be greater than zero."));
      }
#endif

   ResultType = M_STRIP_HLVLDATATYPE(ResultType) + MilTraits<UserType>::TypeFlag;

   UserArrayPtr.resize(SizeX*SizeY);

   MimGetResult2d(ResultImId,
                  OffsetX,
                  OffsetY,
                  SizeX,
                  SizeY,
                  ResultType,
                  ControlFlag,
                  &UserArrayPtr[0]);
   }

// ----------------------------------------------------------
// Overloads for std::vector in MimPut.
template <typename UserType>
inline void MFTYPE MimPut(MIL_ID                       ContextImId,
                          MIL_INT64                    PutType,
                          MIL_INT                      ArraySize,
                          const std::vector<UserType>& Param1Ptr,
                          const std::vector<UserType>& Param2Ptr,
                          MIL_INT64                    ControlFlag)
   {
#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(PutType) != 0)
      {
      SafeTypeError(MIL_TEXT("MimPut"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
   if(ArraySize <= 0)
      {
      SafeTypeError(MIL_TEXT("MimPut"), MIL_TEXT("ArraySize parameter must be greater than zero."));
      }
   if(Param1Ptr.empty())
      {
      SafeTypeError(MIL_TEXT("MimPut"), MIL_TEXT("The input vectors cannot be empty."));
      }
   if(Param1Ptr.size() != Param2Ptr.size())
      {
      SafeTypeError(MIL_TEXT("MimPut"), MIL_TEXT("The input vectors must have the same size."));
      }
   if(ArraySize > (MIL_INT)Param1Ptr.size() && ArraySize != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("MimPut"), MIL_TEXT("ArraySize parameter must be smaller or equal (M_DEFAULT) to the size of input vectors."));
      }
#endif

   PutType = M_STRIP_HLVLDATATYPE(PutType) + MilTraits<UserType>::TypeFlag;

   if(ArraySize == M_DEFAULT || ArraySize > (MIL_INT)Param1Ptr.size())
      {
      ArraySize = (MIL_INT)Param1Ptr.size();
      }

   MimPut(ContextImId,
          PutType,
          ArraySize,
          &Param1Ptr[0],
          &Param2Ptr[0],
          ControlFlag);
   }

#if (!M_MIL_LITE)
// ----------------------------------------------------------
// Overloads for std::vector in MimWarpList.
inline void MFTYPE MimWarpList(MIL_ID                         WarpParamBufId,
                               MIL_INT64                      TransformType,
                               MIL_INT                        NumPoints,
                               const std::vector<MIL_DOUBLE>& SrcCoordXArrayPtr,
                               const std::vector<MIL_DOUBLE>& SrcCoordYArrayPtr,
                               std::vector<MIL_DOUBLE>&       DstCoordXArrayPtr,
                               std::vector<MIL_DOUBLE>&       DstCoordYArrayPtr,
                               MIL_INT64                      ControlFlag)
   {
#if M_MIL_USE_SAFE_TYPE
   if(NumPoints <= 0)
      {
      SafeTypeError(MIL_TEXT("MimWarpList"), MIL_TEXT("NumPoints parameter must be greater than zero."));
      }
   if(SrcCoordXArrayPtr.empty())
      {
      SafeTypeError(MIL_TEXT("MimWarpList"), MIL_TEXT("The input vectors cannot be empty."));
      }
   if(SrcCoordXArrayPtr.size() != SrcCoordYArrayPtr.size())
      {
      SafeTypeError(MIL_TEXT("MimWarpList"), MIL_TEXT("The input vectors must have the same size."));
      }
   if(NumPoints > (MIL_INT)SrcCoordXArrayPtr.size() && NumPoints != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("MimWarpList"), MIL_TEXT("NumPoints parameter must be smaller or equal (M_DEFAULT) to the size of input vectors."));
      }
#endif

   if(NumPoints == M_DEFAULT || NumPoints > (MIL_INT)SrcCoordXArrayPtr.size())
      {
      NumPoints = (MIL_INT)SrcCoordXArrayPtr.size();
      }

   DstCoordXArrayPtr.resize(NumPoints);
   DstCoordYArrayPtr.resize(NumPoints);

   MimWarpList(WarpParamBufId,
               TransformType,
               NumPoints,
               &SrcCoordXArrayPtr[0],
               &SrcCoordYArrayPtr[0],
               &DstCoordXArrayPtr[0],
               &DstCoordYArrayPtr[0],
               ControlFlag);
   }
#endif // (!MIL_LITE)

// ----------------------------------------------------------
// Overloads for std::vector in MxxxStream.
inline void MFTYPE MimStream(std::vector<MIL_UINT8>  &MemPtrOrFileName,
                               MIL_ID                 SysId,
                               MIL_INT64              Operation,
                               MIL_INT64              StreamType,
                               MIL_DOUBLE             Version,
                               MIL_INT64              ControlFlag,
                               MIL_ID*                McontextIdPtr,
                               MIL_INT*               SizeByteVarPtr)
   {
   MxxxStreamForStdVector(MemPtrOrFileName,
                          SysId,
                          Operation,
                          StreamType,
                          Version,
                          ControlFlag,
                          McontextIdPtr,
                          SizeByteVarPtr,
                          MimStream);
   }
#endif // defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR

#if M_MIL_USE_STRING
/***************************************************************************/
/* IM MODULE                                                               */
/***************************************************************************/
#if M_MIL_USE_UNICODE
#if M_MIL_UNICODE_API
inline void MFTYPE MimSaveW(const MIL_STRING& FileName, MIL_ID ContextImId, MIL_INT64 ControlFlag)
   {
   return MimSaveW(FileName.c_str(), ContextImId, ControlFlag);
   }

inline MIL_ID MFTYPE MimRestoreW(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* ContextImIdPtr)
   {
   return MimRestoreW(FileName.c_str(), SysId, ControlFlag, ContextImIdPtr);
   }
#else
inline void MFTYPE MimSaveA(const MIL_STRING& FileName, MIL_ID ContextImId, MIL_INT64 ControlFlag)
   {
   return MimSaveA(FileName.c_str(), ContextImId, ControlFlag);
   }

inline MIL_ID MFTYPE MimRestoreA(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* ContextImIdPtr)
   {
   return MimRestoreA(FileName.c_str(), SysId, ControlFlag, ContextImIdPtr);
   }
#endif /* M_MIL_UNICODE_API */
#else
inline void MFTYPE MimSave(const MIL_STRING& FileName, MIL_ID ContextImId, MIL_INT64 ControlFlag)
   {
   return MimSave(FileName.c_str(), ContextImId, ControlFlag);
   }

inline MIL_ID MFTYPE MimRestore(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* ContextImIdPtr)
   {
   return MimRestore(FileName.c_str(), SysId, ControlFlag, ContextImIdPtr);
   }
#endif /* M_MIL_USE_UNICODE */
#endif /* M_MIL_USE_STRING */

////////////////////////////////////////////////////////////////////////////////
// MIL_UNIQUE_ID support

#if M_MIL_USE_MIL_UNIQUE_ID

#if M_MIL_USE_SAFE_TYPE
template <> inline bool MilIsCorrectObjectType<&MimFree>(MIL_INT64 ObjectType)
   {
   const MIL_INT64 AllImTypes = M_IM_ALLOC_RESULT_BUFFER_TYPES | M_IM_CONTEXT | M_IM_RESULT_OBJECT_TYPES;
   return (ObjectType & M_USER_ATTRIBUTE) == 0 && (ObjectType & AllImTypes) != 0;
   }
#endif

typedef MIL_UNIQUE_ID<&MimFree> MIL_UNIQUE_IM_ID;

#if M_MIL_USE_MOVE_SEMANTICS

inline MIL_UNIQUE_IM_ID MimAlloc(MIL_ID SysId, MIL_INT64 ContextType, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_IM_ID(MimAlloc(SysId, ContextType, ControlFlag, M_NULL));
   }
inline MIL_UNIQUE_IM_ID MimAllocResult(MIL_ID SysId, MIL_INT NbEntries, MIL_INT64 ResultType, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_IM_ID(MimAllocResult(SysId, NbEntries, ResultType, M_NULL));
   }
inline MIL_UNIQUE_IM_ID MimRestore(MIL_CONST_TEXT_PTR FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_IM_ID(MimRestore(FileName, SysId, ControlFlag, M_NULL));
   }
#if M_MIL_USE_STRING
inline MIL_UNIQUE_IM_ID MimRestore(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_IM_ID(MimRestore(FileName, SysId, ControlFlag, M_NULL));
   }
#endif // M_MIL_USE_STRING
template <MilFreeFuncType FreeFunc> inline void MimFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

inline void MimDeinterlace(
      MIL_ID               DeinterlaceContextImId,
      MilConstArrayIdParam SrcImageArrayPtr      ,
      MilConstArrayIdParam DstImageArrayPtr      ,
      MIL_INT              SrcImageCount         ,
      MIL_INT              DstImageCount         ,
      MIL_INT64            ControlFlag           )
   {
   MimDeinterlace(DeinterlaceContextImId, SrcImageArrayPtr.m_IdArrayPtr, DstImageArrayPtr.m_IdArrayPtr,
                  SrcImageCount, DstImageCount, ControlFlag);
   }

inline void MimStream(MilStreamParam     MemPtrOrFileName,
                      MIL_ID             SysId           ,
                      MIL_INT64          Operation       ,
                      MIL_INT64          StreamType      ,
                      MIL_DOUBLE         Version         ,
                      MIL_INT64          ControlFlag     ,
                      MIL_UNIQUE_IM_ID*  ContextImIdPtr  ,
                      MIL_INT*           SizeByteVarPtr  )
   {
   MxxxStreamForMilUniqueId(MemPtrOrFileName, SysId, Operation, StreamType, Version, ControlFlag, ContextImIdPtr, SizeByteVarPtr, MimStream);
   }

#endif // M_MIL_USE_MOVE_SEMANTICS
#endif // M_MIL_USE_MIL_UNIQUE_ID

// End of MIL_UNIQUE_ID support
////////////////////////////////////////////////////////////////////////////////

#endif //__MILIM_H__
