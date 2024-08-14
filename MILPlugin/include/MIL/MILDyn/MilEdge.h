﻿/***************************************************************************/
/*

    Filename:  MilEdge.h
    Owner   :  Matrox Imaging
    Revision:  10.40.0881
    Content :  This file contains the defines and the prototypes for the
               MIL edge and line crest extractor. (Medge...).

    Copyright © Matrox Electronic Systems Ltd., 1992-2021.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef __MILEDGEEXTR_H__
#define __MILEDGEEXTR_H__

#if (!M_MIL_LITE) // MIL FULL ONLY

#if M_MIL_USE_RT
#ifdef M_EDGE_EXPORTS
#define MIL_EDGE_DLLFUNC __declspec(dllexport)
#else
#define MIL_EDGE_DLLFUNC __declspec(dllimport)
#endif
#else
#define MIL_EDGE_DLLFUNC
#endif
/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************************/
/*                      MilEdge CAPI defines                               */
/***************************************************************************/


/***************************************************************************/
/* MedgeAlloc()                                                            */
/***************************************************************************/
#define M_CONTOUR                            0x800L      // Already defined in    milblob.h
#define M_CREST                              0x801L

/***************************************************************************/
/* MedgeControl()                                                          */
/***************************************************************************/

/* Global to context behavior */
#define M_CHAIN_ALL_NEIGHBORS                888L
#define M_MAGNITUDE_TYPE                     10L
#define M_NORM                               4000L
#define M_SQR_NORM                           4001L
#define M_FILTER_TYPE                        1046L       // Already defined in    mil.h
#define M_KERNEL_SIZE                        301L        // Already defined in    milmod.h
#define M_FILTER_MODE                        122L        // Already defined in    milmod.h
#if OldDefinesSupport
   #define M_KERNEL_WIDTH                    109L
   #define M_KERNEL_DEPTH                    368L
   ///MIL_DEPRECATED(M_KERNEL_WIDTH, 1010)
   ///MIL_DEPRECATED(M_KERNEL_DEPTH, 1010)
#endif
#define M_KERNEL                             0x00400000L // Already defined in    milmod.h, mil.h
#define M_RECURSIVE                          0x00040000  // Already defined in    mildev.h
#define M_SHEN                               0x802L
#define M_EXPONENTIAL                        2           // Already defined in    mil.h
#define M_GAUSSIAN                           0x805L
#define M_SOBEL                              M_EDGE_DETECT_SOBEL_FAST   // Already defined in mil.h
#define M_PREWITT                            M_EDGE_DETECT_PREWITT_FAST // Already defined in mil.h
#define M_FREI_CHEN                          M_ID_OFFSET_OF_DEFAULT_KERNEL + 9L
#define M_DERICHE                            M_ID_OFFSET_OF_DEFAULT_KERNEL + 10L
#define M_SMOOTHNESS                         108L         // Already defined in   milmod.h, milmeas.h, mil.h
#define M_FILTER_SMOOTHNESS                  M_SMOOTHNESS // Already defined in   mil.h, milmeas.h
#define M_ACCURACY                           106L        // Already defined in    milmod.h
#define M_SEARCH_ANGLE_ACCURACY              0x00001000L // Legacy. Use M_ANGLE_ACCURACY instead.
#define M_ANGLE_ACCURACY                     M_SEARCH_ANGLE_ACCURACY // Already defined in milpat.h
#define M_THRESHOLD_TYPE                     3000L
#define M_THRESHOLD_MODE                     33L
#define M_THRESHOLD_VALUE_LOW                3001L
#define M_THRESHOLD_VALUE_HIGH               3002L
#define M_THRESHOLD_LOW                      M_THRESHOLD_VALUE_LOW
#define M_THRESHOLD_HIGH                     M_THRESHOLD_VALUE_HIGH
#define M_USER_DEFINED                       21L         // Already defined in    mil.h, milocr.h
#define M_DETAIL_LEVEL                       111L        // Already defined in    milmod.h
#define M_NO_HYSTERESIS                      20L
#define M_FULL_HYSTERESIS                    25L
#define M_HYSTERESIS                         31L
#define M_SAVE_DERIVATIVES                   11L
#define M_SAVE_ANGLE                         12L
#define M_SAVE_MAGNITUDE                     13L
#define M_SAVE_MASK                          39L
#define M_SAVE_CHAIN_MAGNITUDE               59L
#define M_SAVE_CHAIN_ANGLE                   60L
#define M_SAVE_IMAGE                         61L
#define M_MASK_SIZE_X                        0x0000001DL
#define M_MASK_SIZE_Y                        0x0000001EL
#define M_FILL_GAP_DISTANCE                  44L
#define M_FILL_GAP_ANGLE                     45L
#define M_FILL_GAP_POLARITY                  46L
#define M_FILL_GAP_CONTINUITY                38L
#define M_FILL_GAP_CANDIDATE                 91L
#define M_EXTRACTION_SCALE                   58L

// Typical control values
#define M_LOW                                1L          // Already defined in    milcode.h, milmod.h, milocr, milpat.h, mil.h
#define M_MEDIUM                             2L          // Already defined in    milcode.h, milmod.h, milocr, milpat.h
#define M_HIGH                               3L          // Already defined in    milcode.h, milmod.h, milocr, milpat.h, mil.h
#define M_VERY_HIGH                          4L          // Already defined in    milcode.h, milmod.h, milocr, milpat.h

//Flag values for M_CHAINING_METHOD

// Parameters for output units
#define M_PIXEL                              0x1000L
#define M_WORLD                              0x2000L
#define M_ACCORDING_TO_CALIBRATION             1301L

// Utilities
#define M_FLOAT_MODE                         70L
#define M_ALIGNEMENT_MODE                    51L         // =Utilities=
#define M_TIMEOUT                            2077L       // Already defined in    milmod.h, mil.h
#define M_TIMEOUT_END                        10L         // Already defined in    milmod.h

/* Global to context features */
#define M_BOX_X_MIN                          6L          // Already defined in    milblob.h
#define M_BOX_Y_MIN                          7L          // Already defined in    milblob.h
#define M_BOX_X_MAX                          8L          // Already defined in    milblob.h
#define M_BOX_Y_MAX                          9L          // Already defined in    milblob.M
#define M_X_MIN_AT_Y_MIN                     21L         // Already defined in    milblob.h
#define M_X_MAX_AT_Y_MAX                     22L         // Already defined in    milblob.h
#define M_Y_MIN_AT_X_MAX                     23L         // Already defined in    milblob.h
#define M_Y_MAX_AT_X_MIN                     24L         // Already defined in    milblob.h
#define M_CHAIN_APPROXIMATION                0x00010200L 
#define M_APPROXIMATION_TOLERANCE            26L
#define M_LINE                               0x00000080L // Already defined in    milmod.h
#define M_WORLD_LINE                         2175L
#define M_ARC                                0x00000081L
#define M_CENTER_OF_GRAVITY_X                34L         // Already defined in    milblob.h
#define M_CENTER_OF_GRAVITY_Y                35L         // Already defined in    milblob.h
#define M_POSITION                           0x00000402L // Already defined in    milmeas.h
#define M_POSITION_X                         0x00003400L // Already defined in    milmeas.h, milcode.h, milmod.h, milpat.h, mil.h
#define M_POSITION_Y                         0x00004400L // Already defined in    milblob.h, milcode.h, milmod.h, milpat.h, mil.h
#define M_MOMENT_ELONGATION                  50L
#define M_MOMENT_ELONGATION_ANGLE            999L
#define M_SIZE                               0xC00L      // Already defined in    milmod.h
#define M_FAST_LENGTH                        52L
#define M_TORTUOSITY                         76L
#define M_CLOSURE                            77L
#define M_STRENGTH                           55L
#define M_AVERAGE_STRENGTH                   57L
#define M_BOX                                0x101L      // Already defined in    milblob.h
#define M_CONTACT_POINTS                     0x102L      // Already defined in    milblob.h
#define M_CENTER_OF_GRAVITY                  0x103L      // Already defined in    milblob.h
#define M_LENGTH                             0x00002000L // Already defined in    milblob.h, milcal.h, milmeas.h, milmod.h, mil.h
#define M_FERET_X                            72L         // Already defined in    milblob.h
#define M_FERET_Y                            5L          // Already defined in    milblob.h
#define M_FERET_BOX                          69L
#if OldDefinesSupport
#define M_FERET                              M_FERET_BOX
MIL_DEPRECATED(M_FERET, 1020)
#endif
#define M_FERET_MIN_ANGLE                    15L         // Already defined in    milblob.h
#define M_FERET_MAX_ANGLE                    17L         // Already defined in    milblob.h
#define M_FERET_MIN_DIAMETER                 14L         // Already defined in    milblob.h
#define M_FERET_MAX_DIAMETER                 16L         // Already defined in    milblob.h
#define M_FERET_MEAN_DIAMETER                18L         // Already defined in    milblob.h
#define M_FERET_ELONGATION                   27L         // Already defined in    milblob.h
#define M_NUMBER_OF_FERETS                   63L         // Already defined in    milblob.h
#define M_CONVEX_PERIMETER                   20L         // Already defined in    milblob.h
#define M_FERET_GENERAL                      0x400L      // Already defined in    milblob.h
#define M_FERET_GENERAL_ANGLE                62L         // Already defined in    milblob.h
#if OldDefinesSupport
   #define M_GENERAL_FERET                 M_FERET_GENERAL // Also defined in milblob.h
   #if !defined(MIL_DEPRECATED_M_GENERAL_FERET) || !MIL_DEPRECATED_M_GENERAL_FERET
      #define MIL_DEPRECATED_M_GENERAL_FERET 1
      MIL_DEPRECATED(M_GENERAL_FERET, 1020)
   #endif
   #define M_GENERAL_FERET_ANGLE           M_FERET_GENERAL_ANGLE
   MIL_DEPRECATED(M_GENERAL_FERET_ANGLE, 1020)
#endif
#define M_LINE_FIT                           80L
#define M_CIRCLE_FIT                         25L
#define M_ELLIPSE_FIT                        97L
#define M_FERET_ANGLE_SEARCH_START           90L
#define M_FERET_ANGLE_SEARCH_END             92L
#define M_ALL_FEATURES                       0x100L      // Already defined in    milblob.h
#define M_FIRST_FERET_INDEX                  640L
#define M_SECOND_FERET_INDEX                 257L

/* Specific to M_CREST context behavior */
#define M_FOREGROUND_VALUE                   4L          // Already defined in    milblob.h, milmod.h,  milcal.h,  milcode.h, milocr.h
#define M_FOREGROUND_BLACK                   0x100L      // Already defined in    milblob.h, milmod.h,  milcode.h, milocr.h
#define M_FOREGROUND_WHITE                   0x80L       // Already defined in    milblob.h, milmod.h,  milcode.h, milocr.h
#define M_ANY                                0x11000000L // Already defined in    milmod.h,  milcode.h, milocr.h,  milmeas.h, mil.h

/* Sorting keys */
#define M_SORT1_UP                           0x02000000L // Already defined in    milblob.h
#define M_SORT1_DOWN                         0x0A000000L // Already defined in    milblob.h
#define M_SORT2_UP                           0x04000000L // Already defined in    milblob.h
#define M_SORT2_DOWN                         0x0C000000L // Already defined in    milblob.h
#define M_SORT3_UP                           0x06000000L // Already defined in    milblob.h
#define M_SORT3_DOWN                         0x0E000000L // Already defined in    milblob.h
#define M_NO_SORT                            0L          // Already defined in    milblob.h

/* Statistic flags */
#define M_MIN                                0x02000000L // Already defined in    milmeas.h, mil.h
#define M_MAX                                0x04000000L // Already defined in    milmeas.h, mil.h
#define M_MEAN                               0x08000000L // Already defined in    milmeas.h, mil.h, milocr.h
#define M_MIN_ABS                            0x00200000L // Already defined in    mil.h
#define M_MAX_ABS                            0x00800000L // Already defined in    mil.h
#define M_STANDARD_DEVIATION                 0x10000000L // Already defined in    milmeas.h, mil.h

/* Global to result behavior */
#if OldDefinesSupport
   #define M_DRAW_RELATIVE_ORIGIN_X          319L        // deprecated : Use MgraControl(... M_DRAW_OFFSET_X...)
   #define M_DRAW_RELATIVE_ORIGIN_Y          320L        // deprecated : Use MgraControl(... M_DRAW_OFFSET_Y...)
   #define M_DRAW_SCALE_X                    3203L       // deprecated : Use MgraControl(... M_DRAW_ZOOM_X ...)
   #define M_DRAW_SCALE_Y                    3204L       // deprecated : Use MgraControl(... M_DRAW_ZOOM_Y ...)
//    MIL_DEPRECATED(M_DRAW_RELATIVE_ORIGIN_X, 1010)        Already defined in mil.h
//    MIL_DEPRECATED(M_DRAW_RELATIVE_ORIGIN_Y, 1010)        Already defined in mil.h
//    MIL_DEPRECATED(M_DRAW_SCALE_X, 1010)                  Already defined in mil.h
//    MIL_DEPRECATED(M_DRAW_SCALE_Y, 1010)                  Already defined in mil.h
#endif
#define M_DRAW_CROSS_SIZE                    115L

#define M_MODEL_FINDER_COMPATIBLE            19L
#define M_METROLOGY_COMPATIBLE               98L         // =Utilities=
#define M_RESULT_OUTPUT_UNITS 	            1300L


/***************************************************************************/
/* MedgeInquire()                                                          */
/***************************************************************************/

/* To Context */
#define M_OWNER_SYSTEM                       1101L       // Already defined in    mil.h, milmod.h
#define M_MODIFICATION_COUNT                 5010L       // Already defined in    mil.h, milmod.h
#define M_CONTEXT_TYPE                       162
#define M_FILTER_POWER                       1049L
#define M_OVERSCAN                           53L         // Already defined in    mil.h, milmod.h
#define M_OVERSCAN_REPLACE_VALUE             54L         // Already defined in    mil.h, milmod.h
#define M_MIRROR                             0x01000061L // Already defined in    mil.h
#define M_REPLACE                            0x01000060L // Already defined in    mil.h, milocr.h

/***************************************************************************/
/* MedgeSelect()                                                           */
/***************************************************************************/
#define M_INCLUDE                            1L          // Already defined in    milblob.h
#define M_INCLUDE_ONLY                       0x101L      // Already defined in    milblob.h
#define M_EXCLUDE                            2L          // Already defined in    milblob.h
#define M_EXCLUDE_ONLY                       0x102L      // Already defined in    milblob.h
#define M_DELETE                             3L          // Already defined in    milblob.h, milmod.h
#define M_ALL_EDGES                          0x00200000L
#define M_INCLUDED_EDGES                     0x00400000L
#define M_EXCLUDED_EDGES                     0x00800000L
#if OldDefinesSupport
#define M_INCLUDED_EDGE                      M_INCLUDED_EDGES 
#define M_EXCLUDED_EDGE                      M_EXCLUDED_EDGES
MIL_DEPRECATED(M_INCLUDED_EDGE, 1020)
MIL_DEPRECATED(M_EXCLUDED_EDGE, 1020)
#endif
#define M_IN_RANGE                           1L          // Already defined in    milblob.h, mil.h
#define M_OUT_RANGE                          2L          // Already defined in    milblob.h, mil.h
#define M_EQUAL                              3L          // Already defined in    milblob.h, mil.h
#define M_NOT_EQUAL                          4L          // Already defined in    milblob.h, mil.h
#define M_GREATER                            5L          // Already defined in    milblob.h, mil.h
#define M_LESS                               6L          // Already defined in    milblob.h, mil.h
#define M_GREATER_OR_EQUAL                   7L          // Already defined in    milblob.h, mil.h
#define M_LESS_OR_EQUAL                      8L          // Already defined in    milblob.h, mil.h

#define M_INSIDE_BOX                         300L
#define M_INSIDE_CHAIN                       301L
#define M_OUTSIDE_BOX                        302L
#define M_OUTSIDE_CHAIN                      303L
#define M_EQUAL_CHAIN                        0x40  // =Utilities=
#define M_INSIDE_OR_EQUAL_BOX                (M_INSIDE_BOX|M_EQUAL_CHAIN)
#define M_INSIDE_OR_EQUAL_CHAIN              (M_INSIDE_CHAIN|M_EQUAL_CHAIN)
#define M_OUTSIDE_OR_EQUAL_BOX               (M_OUTSIDE_BOX|M_EQUAL_CHAIN)
#define M_OUTSIDE_OR_EQUAL_CHAIN             (M_OUTSIDE_CHAIN|M_EQUAL_CHAIN)
#define M_CROP_CHAIN                         304L
#define M_NEAREST_NEIGHBOR                   0x00000040L // Already defined in    milmeas.h, mil.h
#define M_ALL_NEAREST_NEIGHBORS              0x00000080L 
#define M_NEAREST_NEIGHBOR_RADIUS            116L
#define M_STATUS                             0x00008002L // Already defined in    milcode.h

/***************************************************************************/
/* MedgeGetResult()                                                        */
/***************************************************************************/
#define M_LABEL_VALUE                        1L          // Already defined in    milblob.h
#define M_SPECIFIC_EDGE                      M_LABEL_VALUE
#define M_THRESHOLDS                         3003L
#if OldDefinesSupport
#define M_THRESHOLD_VALUES                   M_THRESHOLDS
MIL_DEPRECATED(M_THRESHOLD_VALUES, 1020)
#endif
#define M_NUMBER_OF_CHAINS                   0x769L
#define M_CHAIN_MAGNITUDE                    36L
#define M_CHAIN_ANGLE                        258L
#define M_IMAGE_ID                           0x04000000L    // Already defined in    milmod.h (0x04000000L)
#define M_MASK_ID                            (M_IMAGE_ID | 0x80000L)
#define M_ANGLE_ID                           0x20000000L
#define M_MAGNITUDE_ID                       0x8800L
#define M_FIRST_DERIVATIVE_X_ID              0x10000L
#define M_FIRST_DERIVATIVE_Y_ID              0x8000L
#define M_SECOND_DERIVATIVE_X_ID             0x4000L
#define M_SECOND_DERIVATIVE_Y_ID             0x1000L
#define M_CROSS_DERIVATIVE_ID                0x1000000L
#define M_FIRST_DERIVATIVES_ID               (M_FIRST_DERIVATIVE_X_ID  | M_FIRST_DERIVATIVE_Y_ID)
#define M_SECOND_DERIVATIVES_ID              (M_SECOND_DERIVATIVE_X_ID | M_SECOND_DERIVATIVE_Y_ID)
#define M_NUMBER_OF_CHAINED_PIXELS           56L         // Already defined in    milblob.h, milmod.h
#define M_NUMBER_OF_CHAINED_EDGELS           M_NUMBER_OF_CHAINED_PIXELS
#define M_CHAIN_CODE                         58L         // Already defined in    milblob.h
#define M_FIRST_POINT_X                      75L         // Already defined in    milblob.h
#define M_FIRST_POINT_Y                      132L
#define M_FIRST_POINT                        (M_FIRST_POINT_X|M_FIRST_POINT_Y)
#define M_CHAIN_INDEX                        67L         // Already defined in    milblob.h, milmod.h
#define M_CHAIN_X                            65L         // Already defined in    milblob.h, milmod.h
#define M_CHAIN_Y                            144L        // Already defined in    milblob.h, milmod.h
#define M_CHAIN                              209L        // Previously (M_CHAIN_X|M_CHAIN_Y), also defined in milblob.h
#define M_CHAINS                             209L        // Already defined in    milblob.h
#define M_VERTICES_X                         68L
#define M_VERTICES_Y                         40L
#define M_VERTICES                           (M_VERTICES_X|M_VERTICES_Y)
#if OldDefinesSupport
#define M_VERTEX_X                           M_VERTICES_X
#define M_VERTEX_Y                           M_VERTICES_Y
#define M_VERTEX                             M_VERTICES  
#define M_BULGE                              145L    
#define M_BULGES                             145L 
MIL_DEPRECATED(M_VERTEX_X, 1020)
MIL_DEPRECATED(M_VERTEX_Y, 1020)
MIL_DEPRECATED(M_VERTEX, 1020)
MIL_DEPRECATED(M_BULGE, 1020)
MIL_DEPRECATED(M_BULGES, 1020)
#endif
#define M_VERTICES_CHAIN_INDEX               71L
#define M_VERTICES_INDEX                     79L
#define M_NUMBER_OF_VERTICES                 73L
#if OldDefinesSupport
#define M_NUMBER_OF_VERTEXES                 M_NUMBER_OF_VERTICES
#define M_NUMBER_OF_VERTEX                   M_NUMBER_OF_VERTICES
MIL_DEPRECATED(M_NUMBER_OF_VERTEXES, 1020)
MIL_DEPRECATED(M_NUMBER_OF_VERTEX, 1020)
#endif
#define M_LINE_FIT_A                         82L
#define M_LINE_FIT_B                         83L
#define M_LINE_FIT_C                         31L
#define M_LINE_FIT_ERROR                     32L
#define M_CIRCLE_FIT_CENTER_X                41L
#define M_CIRCLE_FIT_CENTER_Y                42L
#define M_CIRCLE_FIT_RADIUS                  43L
#define M_CIRCLE_FIT_ERROR                   47L
#define M_CIRCLE_FIT_COVERAGE                48L 
#define M_ELLIPSE_FIT_CENTER_X               85L
#define M_ELLIPSE_FIT_CENTER_Y               86L
#define M_ELLIPSE_FIT_MINOR_AXIS             87L
#define M_ELLIPSE_FIT_MAJOR_AXIS             88L
#define M_ELLIPSE_FIT_ANGLE                  89L
#define M_ELLIPSE_FIT_COVERAGE               96L
#define M_ELLIPSE_FIT_ERROR                  74L

/***************************************************************************/
/* MedgeGetNeighbors()                                                     */
/***************************************************************************/
#define M_NEIGHBOR_MINIMUM_SPACING           117L
#define M_NEIGHBOR_MAXIMUM_NUMBER            118L
#define M_NEIGHBOR_ANGLE                     122L
#define M_NEIGHBOR_ANGLE_TOLERANCE           123L
#define M_SEARCH_RADIUS_MAX                  120L
#define M_SEARCH_RADIUS_MIN                  121L
#define M_SEARCH_ANGLE                       0x00000100L // Already defines in    milpat.h, milcode.h
#define M_SEARCH_ANGLE_TOLERANCE             0x00000800L // Already defines in    milpat.h, milcode.h
#define M_SEARCH_ANGLE_SIGN                  126L
#define M_GET_EDGELS                         1L
#define M_GET_SUBEDGELS                      2L

#if OldDefinesSupport
#define M_NEIGHBOR_POLARITY                          M_NEIGHBOR_ANGLE
#define M_NEIGHBOR_POLARITY_TOLERANCE                M_NEIGHBOR_ANGLE_TOLERANCE
#define M_NEIGHBOR_SEARCH_RADIUS_MAX                 M_SEARCH_RADIUS_MAX
#define M_NEIGHBOR_SEARCH_RADIUS_MIN                 M_SEARCH_RADIUS_MIN
#define M_NEIGHBOR_DIRECTION                         M_SEARCH_ANGLE
#define M_NEIGHBOR_DIRECTION_TOLERANCE               M_SEARCH_ANGLE_TOLERANCE
#define M_NEIGHBOR_DIRECTION_SIGN                    M_SEARCH_ANGLE_SIGN
MIL_DEPRECATED(M_NEIGHBOR_POLARITY           , 1020)
MIL_DEPRECATED(M_NEIGHBOR_POLARITY_TOLERANCE , 1020)
MIL_DEPRECATED(M_NEIGHBOR_SEARCH_RADIUS_MAX  , 1020)
MIL_DEPRECATED(M_NEIGHBOR_SEARCH_RADIUS_MIN  , 1020)
MIL_DEPRECATED(M_NEIGHBOR_DIRECTION          , 1020)
MIL_DEPRECATED(M_NEIGHBOR_DIRECTION_TOLERANCE, 1020)
MIL_DEPRECATED(M_NEIGHBOR_DIRECTION_SIGN     , 1020)
#endif

/***************************************************************************/
/* MedgeDraw()                                                             */
/***************************************************************************/
#define M_DRAW_LABEL                         0x00000001L
#define M_DRAW_IMAGE                         0x00000002L       // Already defines in    milmod.h, milpat.h
#define M_DRAW_EDGES                         0x00000004L       // Already defines in    milmod.h, milmeas.h 
#define M_DRAW_EDGE                          M_DRAW_EDGES
#define M_DRAW_FERET_MAX                     0x00000008L       // Already defined in    milblob.h
#define M_DRAW_FERET_BOX                     0x00000010L       // Already defined in    milblob.h
#define M_DRAW_BOX                           0x00000020L       // Already defined in    milblob.h, milmod.h, milmeas.h, milpat.h
#define M_DRAW_POSITION                      0x00000040L       // Already defined in    milblob.h, milmod.h, milmeas.h, milpat.h
#define M_DRAW_CENTER_OF_GRAVITY             0x00000080L       // Already defined in    milblob.h
#define M_DRAW_INDEX                         0x00000100L
#define M_DRAW_VERTICES                      0x00000400L
#if OldDefinesSupport
#define M_DRAW_VERTEXES                      M_DRAW_VERTICES
#define M_DRAW_VERTEX                        M_DRAW_VERTICES
MIL_DEPRECATED(M_DRAW_VERTEXES, 1020)
MIL_DEPRECATED(M_DRAW_VERTEX, 1020)
#endif
#define M_DRAW_SEGMENTS                      0x00000800L
#define M_DRAW_FERET_MIN                     0x00001000L       // Already defined in    milblob.h
#define M_DRAW_FERET_GENERAL                 0x00100000L
#if OldDefinesSupport
   #define M_DRAW_GENERAL_FERET              M_DRAW_FERET_GENERAL
   MIL_DEPRECATED(M_DRAW_GENERAL_FERET, 1020)
#endif
#define M_DRAW_BUFFER_MASK                   0x3E00000L        // =Utilities=
#define M_DRAW_FIRST_DERIVATIVE_Y            0xA00000L
#define M_DRAW_MAGNITUDE                     0xE00000L
#define M_DRAW_SECOND_DERIVATIVE_X           0x1200000L
#define M_DRAW_SECOND_DERIVATIVE_Y           0x1600000L
#define M_DRAW_ANGLE                         0x1A00000L
#define M_DRAW_CROSS_DERIVATIVE              0x1E00000L
#define M_DRAW_MASK                          0x200000L
#define M_DRAW_CIRCLE_FIT                    0x20000L
#define M_DRAW_FIRST_DERIVATIVE_X            0x600000L
#define M_DRAW_EDGELS                        0x2000L
#define M_DRAW_ACTIVEMIL_INDEX               0x4000L           // =Utilities=
#define M_DRAW_VALUE                         0x8000L
#if OldDefinesSupport
#define M_DRAW_NEAREST_EDGELS                0x10000L
MIL_DEPRECATED(M_DRAW_NEAREST_EDGELS, 1020)
#endif
#define M_DRAW_LINE_FIT                      0x200L
#define M_DRAW_ELLIPSE_FIT                   0x40000L

/***************************************************************************/
/* MedgeStream                                                             */
/***************************************************************************/
#define M_SAVE                             0x100L        // Already defines in    milmod.h, milocr.h
#define M_RESTORE                           0x10L
#define M_LOAD                                 1L        // Already defines in    milmod.h, milmeas.h, mil.h
#define M_INQUIRE_SIZE_BYTE                    2L        // Already defines in    milmod.h

/***************************************************************************/
/* Complementary definitions                                               */
/***************************************************************************/
#define M_ENABLE                             -9997L      // Already defined in    milblob.h, milcal.h, milmeas.h, mil.h
#define M_DISABLE                            -9999L      // Already defined in    milblob.h, milcal.h, milmeas.h, mil.h
#define M_PACKED                             0x00020000L // Already defined in    mil.h
#define M_AVAILABLE                          MAKE_INT64(0x0000400000000000) // Also defined in mil.h
#define M_SUPPORTED                          MAKE_INT64(0x0000800000000000) // Also defined in mil.h
#define M_TYPE_LABEL                         0x01000000L
#define M_TYPE_INDEX                         0x02000000L
#define M_ALL                                0x40000000L // Already defined in    milmod.h, milmeas.h, milocr.h,  milpat.h,  mil.h
#define M_DEFAULT                            0x10000000L // Already defined in    milmod.h, milocr.h,  milcode.h, mil.h
#if OldDefinesSupport
#define M_TYPE_MIL_ANGLE                     4L
#define M_TYPE_ANGLE                         8L
MIL_DEPRECATED(M_TYPE_MIL_ANGLE, 1020)
MIL_DEPRECATED(M_TYPE_ANGLE, 1020)
#endif
#define M_TRUE                               1L          // Already defined in    mil.h, milmeas.h
#define M_FALSE                              0L          // Already defined in    mil.h, milmeas.h
#define M_NO_CHECK                           0x40000000L
#define M_SAME                               -1L         // Already defined in    milmod.h, milmeas.h, milocr.h
#define M_SAME_OR_REVERSE                    5L          // Already defined in    milmod.h
#if OldDefinesSupport
#define M_SAME_EDGE                          67L
MIL_DEPRECATED(M_SAME_EDGE, 1020)
#endif
#define M_REVERSE                            4L          // Already defined in    milmod.h, mil.h
#define M_ANY                                0x11000000L // Already defined in    milmod.h, milmeas.h, milcode.h, milocr.h, mil.h
#define M_AUTO                               444L        // Already defined in    milocr.h, milmod.h
#define M_SIZE_X                             1536L       // Already defined in    milcode.h, mil.h
#define M_SIZE_Y                             1537L       // Already defined in    milcode.h, mil.h
#define M_SIZE_BAND                          1005L       // Already defined in    mil.h
#define M_TYPE                               1008L       // Already defined in    mil.h
#define M_SIGN                               1014L       // Already defined in    mil.h
#define M_SIZE_BIT                           1007L       // Already defined in    mil.h
#define M_WORLD                              0x2000L     // Already defined in    milcal.h
#define M_SIZE_BYTE                          5061L       // Already defined in    milmod.h, milcode.h, mil.h
#define M_UNKNOWN                            -9999L      // Already defined in    mil.h, milpat.h  

#define M_MEMORY                             (M_APP_INQUIRE_SYS_START+120L) /*5120*/ // Already defined in milmod.h, milcode.h, mil.h
#define M_EDGE_CONTOUR                       (M_EDGE_OBJECT | 0x00000001L) // Already defined in    mil.h
#define M_EDGE_CONTEXT                       (M_EDGE_OBJECT | 0x00000002L) // Already defined in    mil.h // =Utilities=
#define M_EDGE_RESULT                        (M_EDGE_OBJECT | 0x00000004L) // Already defined in    mil.h // =Utilities=
#define M_EDGE_RESULT_BUFFER                 M_EDGE_RESULT // =Utilities=
#define M_INTERACTIVE                        M_NULL // Already defined in mil.h, milcal.h, milcode.h, milmeas.h, milocr.h, milpat.h, milmod.h


// Deprecated flag names.
#if OldDefinesSupport
   // #define       M_FILTER M_FILTER_TYPE already defined in mil.h
   // MIL_DEPRECATED(M_FILTER, 1000)       already defined in mil.h
#endif

/***************************************************************************/
/*                 MilEdge CAPI function prototypes                        */
/***************************************************************************/

/***************************************************************************/
/* MedgeAlloc()                                                            */
/***************************************************************************/
MIL_EDGE_DLLFUNC MIL_ID MFTYPE  MedgeAlloc         (MIL_ID       SystemId,
                                   MIL_INT64    EdgeFinderType,
                                   MIL_INT64    ControlFlag,
                                   MIL_ID*      ContextIdPtr);

/***************************************************************************/
/* MedgeAllocResult()                                                      */
/***************************************************************************/
MIL_EDGE_DLLFUNC MIL_ID MFTYPE  MedgeAllocResult   (MIL_ID       SystemId,
                                   MIL_INT64    ControlFlag,
                                   MIL_ID*      EdgeResultIdPtr);

/***************************************************************************/
/* MedgeControl()                                                          */
/***************************************************************************/
#if M_MIL_USE_64BIT
// Prototypes for 64 bits OSs
MIL_EDGE_DLLFUNC void MFTYPE    MedgeControlInt64  (MIL_ID       ContextOrResultId,
                                   MIL_INT64    ControlType,
                                   MIL_INT64    ControlValue);
MIL_EDGE_DLLFUNC void MFTYPE    MedgeControlDouble (MIL_ID       ContextOrResultId,
                                   MIL_INT64    ControlType,
                                   MIL_DOUBLE   ControlValue);
#else
// Prototypes for 32 bits OSs
#define MedgeControlInt64  MedgeControl
#define MedgeControlDouble MedgeControl
MIL_EDGE_DLLFUNC void MFTYPE    MedgeControl       (MIL_ID       ContextOrResultId,
                                   MIL_INT64    ControlType,
                                   MIL_DOUBLE   ControlValue);
#endif
/***************************************************************************/
/* MedgeInquire()                                                          */
/***************************************************************************/
MIL_EDGE_DLLFUNC MIL_INT MFTYPE    MedgeInquire       (MIL_ID       ContextOrResultId,
                                      MIL_INT64    InquireType,
                                      void*        UserVarPtr);

/***************************************************************************/
/* MedgeSelect()                                                           */
/***************************************************************************/
MIL_EDGE_DLLFUNC void MFTYPE    MedgeSelect        (MIL_ID       EdgeResultId,
                                   MIL_INT64    Operation,
                                   MIL_INT64    SelectionCriterion,
                                   MIL_INT64    Condition,
                                   MIL_DOUBLE   Param1,
                                   MIL_DOUBLE   Param2);

/***************************************************************************/
/* MedgeGetResult()                                                        */
/***************************************************************************/
MIL_EDGE_DLLFUNC void MFTYPE    MedgeGetResult     (MIL_ID       EdgeResultId,
                                   MIL_INT      EdgeIndexOrLabelValue,
                                   MIL_INT64    ResultType,
                                   void*        FirstResultArrayPtr,
                                   void*        SecondResultArrayPtr);

/***************************************************************************/
/* MedgeDraw()                                                             */
/***************************************************************************/
MIL_EDGE_DLLFUNC void MFTYPE    MedgeDraw          (MIL_ID       ContextGraId,
                                   MIL_ID       ResultEdgeId,
                                   MIL_ID       DstImageBufOrListGraId,
                                   MIL_INT64    Operation,
                                   MIL_INT      IndexOrLabel,
                                   MIL_INT64    ControlFlag);

/***************************************************************************/
/* MedgeCalculate()                                                        */
/***************************************************************************/
MIL_EDGE_DLLFUNC void MFTYPE    MedgeCalculate     (MIL_ID       ContextId,
                                   MIL_ID       SourceImageId,
                                   MIL_ID       SourceDeriv1Id,
                                   MIL_ID       SourceDeriv2Id,
                                   MIL_ID       SourceDeriv3Id,
                                   MIL_ID       EdgeResultId,
                                   MIL_INT64    ControlFlag);

/***************************************************************************/
/* MedgeMask()                                                             */
/***************************************************************************/
MIL_EDGE_DLLFUNC void MFTYPE    MedgeMask          (MIL_ID       ContextId,
                                   MIL_ID       MaskImageId,
                                   MIL_INT64    ControlFlag);

/***************************************************************************/
/* MedgeGetNeighbors()                                                     */
/***************************************************************************/
MIL_EDGE_DLLFUNC void MFTYPE    MedgeGetNeighbors  (MIL_ID            EdgeResultId,
                                   MIL_INT           SizeOfArray,
                                   const MIL_DOUBLE* SrcArrayXPtr,
                                   const MIL_DOUBLE* SrcArrayYPtr,
                                   const MIL_DOUBLE* SrcArrayAnglePtr,
                                   MIL_DOUBLE*       DstArrayXPtr,
                                   MIL_DOUBLE*       DstArrayYPtr,
                                   MIL_INT*          DstArrayIndexPtr,
                                   MIL_INT*          DstArrayLabelPtr,
                                   MIL_INT64         ControlFlag);

/***************************************************************************/
/* MedgePut()                                                              */
/***************************************************************************/
MIL_EDGE_DLLFUNC void MFTYPE    MedgePut(MIL_ID            ResultEdgeId,
                                         MIL_INT           NumEdgels,
                                         const MIL_INT*    ChainIndexArrayPtr,
                                         const MIL_DOUBLE* PosXArrayPtr,
                                         const MIL_DOUBLE* PosYArrayPtr,
                                         const MIL_DOUBLE* AngleArrayPtr,
                                         const MIL_DOUBLE* MagnitudeArrayPtr,
                                         MIL_INT64         ControlFlag);

/***************************************************************************/
/* MedgeFree()                                                             */
/***************************************************************************/
MIL_EDGE_DLLFUNC void MFTYPE    MedgeFree          (MIL_ID       ObjectId);

#if M_MIL_USE_UNICODE

/***************************************************************************/
/* MedgeSave() Unicode                                                     */
/***************************************************************************/
MIL_EDGE_DLLFUNC void MFTYPE    MedgeSaveW         (MIL_CONST_TEXTW_PTR FileName,
                                   MIL_ID       ContextOrResultId,
                                   MIL_INT64    ControlFlag);

/***************************************************************************/
/* MedgeRestore() Unicode                                                  */
/***************************************************************************/
MIL_EDGE_DLLFUNC MIL_ID  MFTYPE MedgeRestoreW      (MIL_CONST_TEXTW_PTR FileName,
                                   MIL_ID       SystemId,
                                   MIL_INT64    ControlFlag,
                                   MIL_ID*      ContextIdPtr);

/***************************************************************************/
/* MedgeStream() Unicode                                                   */
/***************************************************************************/
MIL_EDGE_DLLFUNC void MFTYPE    MedgeStreamW      (MIL_TEXTW_PTR MemPtrOrFileName,
                                  MIL_ID       SysId,
                                  MIL_INT64    Operation,
                                  MIL_INT64    StreamType,
                                  MIL_DOUBLE   Version,
                                  MIL_INT64    ControlFlag,
                                  MIL_ID*      ContextOrResultEdgeIdPtr,
                                  MIL_INT*     SizeByteVarPtr);

/***************************************************************************/
/* MedgeSave() ASCII                                                       */
/***************************************************************************/
MIL_EDGE_DLLFUNC void MFTYPE    MedgeSaveA         (MIL_CONST_TEXTA_PTR  FileName,
                                   MIL_ID       ContextOrResultId,
                                   MIL_INT64    ControlFlag);

/***************************************************************************/
/* MedgeRestore() ASCII                                                    */
/***************************************************************************/
MIL_EDGE_DLLFUNC MIL_ID  MFTYPE MedgeRestoreA      (MIL_CONST_TEXTA_PTR  FileName,
                                   MIL_ID       SystemId,
                                   MIL_INT64    ControlFlag,
                                   MIL_ID*      ContextIdPtr);

/***************************************************************************/
/* MedgeStream() ASCII                                                     */
/***************************************************************************/
MIL_EDGE_DLLFUNC void MFTYPE    MedgeStreamA      (MIL_TEXTA_PTR      MemPtrOrFileName,
                                  MIL_ID     SysId,
                                  MIL_INT64  Operation,
                                  MIL_INT64  StreamType,
                                  MIL_DOUBLE Version,
                                  MIL_INT64  ControlFlag,
                                  MIL_ID*    ContextOrResultEdgeIdPtr,
                                  MIL_INT*   SizeByteVarPtr);

#if M_MIL_UNICODE_API

#define MedgeRestore MedgeRestoreW 
#define MedgeSave    MedgeSaveW 
#define MedgeStream  MedgeStreamW 

#else

#define MedgeRestore MedgeRestoreA
#define MedgeSave    MedgeSaveA
#define MedgeStream  MedgeStreamA

#endif //M_MIL_UNICODE_API

#else

/***************************************************************************/
/* MedgeSave()                                                             */
/***************************************************************************/
MIL_EDGE_DLLFUNC void MFTYPE    MedgeSave          (MIL_CONST_TEXT_PTR FileName,
                                   MIL_ID       ContextOrResultId,
                                   MIL_INT64    ControlFlag);

/***************************************************************************/
/* MedgeRestore()                                                          */
/***************************************************************************/
MIL_EDGE_DLLFUNC MIL_ID  MFTYPE MedgeRestore       (MIL_CONST_TEXT_PTR FileName,
                                   MIL_ID       SystemId,
                                   MIL_INT64    ControlFlag,
                                   MIL_ID*      ContextIdPtr);

/***************************************************************************/
/* MedgeStream()                                                           */
/***************************************************************************/
MIL_EDGE_DLLFUNC void MFTYPE    MedgeStream       (MIL_TEXT_PTR MemPtrOrFileName,
                                  MIL_ID       SysId,
                                  MIL_INT64    Operation,
                                  MIL_INT64    StreamType,
                                  MIL_DOUBLE   Version,
                                  MIL_INT64    ControlFlag,
                                  MIL_ID*      ContextOrResultEdgeIdPtr,
                                  MIL_INT*     SizeByteVarPtr);

#endif


/*************/
/* Utilities */
/*************/
#define MedgeCalculateDefault(ContextId, SourceImageId, EdgeResultId)   MedgeCalculate(ContextId, SourceImageId, M_NULL, M_NULL, M_NULL, EdgeResultId, M_DEFAULT);

/* C++ directive if needed */
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

inline void MFTYPE MedgeStreamCpp(MilStreamParam MemPtrOrFileName,
                                  MIL_ID         SysId,
                                  MIL_INT64      Operation,
                                  MIL_INT64      StreamType,
                                  MIL_DOUBLE     Version,
                                  MIL_INT64      ControlFlag,
                                  MIL_ID*        ContextOrResultEdgeIdPtr,
                                  MIL_INT*       SizeByteVarPtr)
   {
   MedgeStream(MemPtrOrFileName.m_Param, SysId, Operation, StreamType, Version, ControlFlag, ContextOrResultEdgeIdPtr, SizeByteVarPtr);
   }

#undef  MedgeStream
#define MedgeStream MedgeStreamCpp

#endif // __cplusplus

//////////////////////////////////////////////////////////////
// Overload functions 
//////////////////////////////////////////////////////////////

#if M_MIL_USE_64BIT
#ifdef __cplusplus
//////////////////////////////////////////////////////////////
// MedgeControl function definition when compiling c++ files
//////////////////////////////////////////////////////////////
#if !M_MIL_USE_LINUX
inline void MedgeControl (MIL_ID       ContextOrResultId, 
                          MIL_INT64      ControlType, 
                          int            ControlValue)
   {
   MedgeControlInt64(ContextOrResultId, ControlType, ControlValue);
   };
#endif

inline void MedgeControl (MIL_ID       ContextOrResultId, 
                          MIL_INT64       ControlType, 
                          MIL_INT32       ControlValue)
   {
   MedgeControlInt64(ContextOrResultId, ControlType, ControlValue);
   }

inline void MedgeControl (MIL_ID       ContextOrResultId, 
                          MIL_INT64       ControlType, 
                          MIL_INT64       ControlValue)
   {
   MedgeControlInt64(ContextOrResultId, ControlType, ControlValue);
   }

inline void MedgeControl (MIL_ID       ContextOrResultId, 
                          MIL_INT64    ControlType, 
                          MIL_DOUBLE   ControlValue)
   {
   MedgeControlDouble(ContextOrResultId, ControlType, ControlValue);
   }

#else
//////////////////////////////////////////////////////////////
// For C file, call the default function, i.e. Int64 one
//////////////////////////////////////////////////////////////
#define MedgeControl  MedgeControlDouble

#endif // __cplusplus
#endif // M_MIL_USE_64BIT

#if M_MIL_USE_SAFE_TYPE

//////////////////////////////////////////////////////////////
// See milos.h for explanation about these functions.
//////////////////////////////////////////////////////////////

// ----------------------------------------------------------
// MedgeGetResult

inline void MFTYPE MedgeGetResultUnsafe  (MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, void            *FirstResultArrayPtr, void           *SecondResultArrayPtr);
inline void MFTYPE MedgeGetResultSafeType(MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, int              FirstResultArrayPtr, int             SecondResultArrayPtr);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MedgeGetResultSafeType(MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, std::nullptr_t                      , std::nullptr_t                      );
#endif
inline void MFTYPE MedgeGetResultSafeType(MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, MIL_INT32       *FirstResultArrayPtr, MIL_INT32      *SecondResultArrayPtr);
inline void MFTYPE MedgeGetResultSafeType(MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, MIL_INT64       *FirstResultArrayPtr, MIL_INT64      *SecondResultArrayPtr);
inline void MFTYPE MedgeGetResultSafeType(MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, MIL_DOUBLE      *FirstResultArrayPtr, MIL_DOUBLE     *SecondResultArrayPtr);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                                         
inline void MFTYPE MedgeGetResultSafeType(MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, MIL_UINT32      *FirstResultArrayPtr, MIL_UINT32     *SecondResultArrayPtr);
inline void MFTYPE MedgeGetResultSafeType(MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, MIL_UINT64      *FirstResultArrayPtr, MIL_UINT64     *SecondResultArrayPtr);
#endif

// ----------------------------------------------------------
// MedgeInquire

inline MIL_INT MFTYPE MedgeInquireUnsafe  (MIL_ID ContextOrResultId, MIL_INT64  InquireType, void         *UserVarPtr);
inline MIL_INT MFTYPE MedgeInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, int           UserVarPtr);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE MedgeInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, std::nullptr_t);
#endif
inline MIL_INT MFTYPE MedgeInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, MIL_INT32    *UserVarPtr);
inline MIL_INT MFTYPE MedgeInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, MIL_INT64    *UserVarPtr);
inline MIL_INT MFTYPE MedgeInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, MIL_DOUBLE   *UserVarPtr);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline MIL_INT MFTYPE MedgeInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, MIL_UINT32   *UserVarPtr);
inline MIL_INT MFTYPE MedgeInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, MIL_UINT64   *UserVarPtr);
#endif

// -------------------------------------------------------------------------
// MedgeGetResult

inline void MFTYPE MedgeGetResultSafeType(MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, int FirstResultArrayPtr,int SecondResultArrayPtr)
   {
   if (SecondResultArrayPtr || FirstResultArrayPtr)
      SafeTypeError(MIL_TEXT("MedgeGetResult"));

   MedgeGetResult(EdgeResultId, EdgeIndexOrLabelValue, ResultType, NULL, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MedgeGetResultSafeType(MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, std::nullptr_t, std::nullptr_t)
   {
   MedgeGetResult(EdgeResultId, EdgeIndexOrLabelValue, ResultType, NULL, NULL);
   }
#endif

inline void MedgeGetResultSafeTypeExecute (MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, void           *FirstResultArrayPtr, void           *SecondResultArrayPtr, MIL_INT64  FirstGivenType, MIL_INT64  SecondGivenType)
   {
   MIL_INT64  RequiredType = ResultType & M_HLVLDATATYPE_MASK;
   if((RequiredType != M_TYPE_MIL_ID) && (RequiredType != M_TYPE_MIL_INT32) && (RequiredType != M_TYPE_MIL_INT64) && (RequiredType != M_TYPE_DOUBLE))
      RequiredType = 0;
   if (RequiredType == 0)
      RequiredType = M_TYPE_DOUBLE;
   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if (RequiredType != FirstGivenType || RequiredType != SecondGivenType)
      SafeTypeError(MIL_TEXT("MedgeGetResult"));

   MedgeGetResult(EdgeResultId, EdgeIndexOrLabelValue, ResultType, FirstResultArrayPtr, SecondResultArrayPtr);
   }

inline void MFTYPE MedgeGetResultUnsafe  (MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, void        *FirstResultArrayPtr, void        *SecondResultArrayPtr) {MedgeGetResult               (EdgeResultId, EdgeIndexOrLabelValue, ResultType, FirstResultArrayPtr, SecondResultArrayPtr);}
inline void MFTYPE MedgeGetResultSafeType(MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, MIL_INT32   *FirstResultArrayPtr, MIL_INT32   *SecondResultArrayPtr) {MedgeGetResultSafeTypeExecute(EdgeResultId, EdgeIndexOrLabelValue, ResultType, FirstResultArrayPtr, SecondResultArrayPtr, M_TYPE_MIL_INT32, M_TYPE_MIL_INT32);}
inline void MFTYPE MedgeGetResultSafeType(MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, MIL_INT64   *FirstResultArrayPtr, MIL_INT64   *SecondResultArrayPtr) {MedgeGetResultSafeTypeExecute(EdgeResultId, EdgeIndexOrLabelValue, ResultType, FirstResultArrayPtr, SecondResultArrayPtr, M_TYPE_MIL_INT64, M_TYPE_MIL_INT64);}
inline void MFTYPE MedgeGetResultSafeType(MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, MIL_DOUBLE  *FirstResultArrayPtr, MIL_DOUBLE  *SecondResultArrayPtr) {MedgeGetResultSafeTypeExecute(EdgeResultId, EdgeIndexOrLabelValue, ResultType, FirstResultArrayPtr, SecondResultArrayPtr, M_TYPE_DOUBLE   , M_TYPE_DOUBLE   );}
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                                         
inline void MFTYPE MedgeGetResultSafeType(MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, MIL_UINT32   *FirstResultArrayPtr, MIL_UINT32  *SecondResultArrayPtr) {MedgeGetResultSafeTypeExecute(EdgeResultId, EdgeIndexOrLabelValue, ResultType, FirstResultArrayPtr, SecondResultArrayPtr, M_TYPE_MIL_INT32, M_TYPE_MIL_INT32);}
inline void MFTYPE MedgeGetResultSafeType(MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, MIL_UINT64   *FirstResultArrayPtr, MIL_UINT64  *SecondResultArrayPtr) {MedgeGetResultSafeTypeExecute(EdgeResultId, EdgeIndexOrLabelValue, ResultType, FirstResultArrayPtr, SecondResultArrayPtr, M_TYPE_MIL_INT64, M_TYPE_MIL_INT64);}
#endif

// ----------------------------------------------------------
// MedgeInquire

inline MIL_INT MFTYPE MedgeInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, int UserVarPtr)
   {
   if (UserVarPtr)
      SafeTypeError(MIL_TEXT("MedgeInquire"));

   return MedgeInquire(ContextOrResultId, InquireType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE MedgeInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, std::nullptr_t)
   {
   return MedgeInquire(ContextOrResultId, InquireType, NULL);
   }
#endif

inline MIL_INT MFTYPE MedgeInquireSafeTypeExecute (MIL_ID ContextOrResultId, MIL_INT64  InquireType, void  *UserVarPtr, MIL_INT64  GivenType)
   {
   MIL_INT64  RequiredType = InquireType & M_HLVLDATATYPE_MASK;
   if((RequiredType != M_TYPE_MIL_ID) && (RequiredType != M_TYPE_MIL_INT32) && (RequiredType != M_TYPE_MIL_INT64) && (RequiredType != M_TYPE_DOUBLE))
      RequiredType = 0;
   if (RequiredType == 0)
      RequiredType = M_TYPE_DOUBLE;
   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if (RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("MedgeInquire"));

   return MedgeInquire(ContextOrResultId, InquireType, UserVarPtr);
   }

inline MIL_INT MFTYPE MedgeInquireUnsafe  (MIL_ID ContextOrResultId, MIL_INT64  InquireType, void        *UserVarPtr) {return MedgeInquire               (ContextOrResultId, InquireType, UserVarPtr                  );}
inline MIL_INT MFTYPE MedgeInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, MIL_INT32   *UserVarPtr) {return MedgeInquireSafeTypeExecute(ContextOrResultId, InquireType, UserVarPtr, M_TYPE_MIL_INT32);}
inline MIL_INT MFTYPE MedgeInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, MIL_INT64   *UserVarPtr) {return MedgeInquireSafeTypeExecute(ContextOrResultId, InquireType, UserVarPtr, M_TYPE_MIL_INT64);}
inline MIL_INT MFTYPE MedgeInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, MIL_DOUBLE  *UserVarPtr) {return MedgeInquireSafeTypeExecute(ContextOrResultId, InquireType, UserVarPtr, M_TYPE_DOUBLE   );}
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                
inline MIL_INT MFTYPE MedgeInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, MIL_UINT32  *UserVarPtr) {return MedgeInquireSafeTypeExecute(ContextOrResultId, InquireType, UserVarPtr, M_TYPE_MIL_INT32);}
inline MIL_INT MFTYPE MedgeInquireSafeType(MIL_ID ContextOrResultId, MIL_INT64  InquireType, MIL_UINT64  *UserVarPtr) {return MedgeInquireSafeTypeExecute(ContextOrResultId, InquireType, UserVarPtr, M_TYPE_MIL_INT64);}
#endif

#define MedgeGetResult       MedgeGetResultSafeType
#define MedgeInquire         MedgeInquireSafeType

#else // #if M_MIL_USE_SAFE_TYPE

#define MedgeGetResultUnsafe       MedgeGetResult
#define MedgeInquireUnsafe         MedgeInquire

#endif // #if M_MIL_USE_SAFE_TYPE

// ----------------------------------------------------------
// Overload for std::vector.
#if defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR
template <typename UserType>
inline void MFTYPE MedgeGetResult(MIL_ID EdgeResultId, MIL_INT EdgeIndexOrLabelValue, MIL_INT64  ResultType, std::vector<UserType> &FirstResultArrayPtr, CMilArrayParamOut SecondResultArrayPtr)
   {
   //! If the given MIL data type is not the same as the SrcType, change it to the correct one
   //! and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(!SecondResultArrayPtr.IsValidParam())
      {
      SafeTypeError(MIL_TEXT("MedgeGetResult"), MIL_TEXT("Cannot call MedgeGetResult with an std::vector and an non zero integer."));
      }
   if(M_GET_HLVLDATATYPE(ResultType) != 0)
      {
      SafeTypeError(MIL_TEXT("MedgeGetResult"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
   if(!SecondResultArrayPtr.IsNullPtr() && SecondResultArrayPtr.GetMilDataType() != MilTraits<UserType>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("MedgeGetResult"), MIL_TEXT("The data type of RMSErrorArrayPtr must be the same as FirstResultArrayPtr."));
      }
#endif

   ResultType = M_STRIP_HLVLDATATYPE(ResultType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   MedgeGetResult(EdgeResultId, EdgeIndexOrLabelValue, M_STRIP_HLVLDATATYPE(ResultType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector, M_NULL);

   FirstResultArrayPtr.resize(InternalNumberOfElementsForStdVector);
   SecondResultArrayPtr.Resize<UserType>(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      MedgeGetResult(EdgeResultId, EdgeIndexOrLabelValue, ResultType, &FirstResultArrayPtr[0], SecondResultArrayPtr.GetData<UserType>());
      }
   }

// ----------------------------------------------------------
// Overloads for std::vector in MedgeGetNeighbors.
inline void MFTYPE MedgeGetNeighbors(MIL_ID                          EdgeResultId,
                                     MIL_INT                         SizeOfArray,
                                     const std::vector<MIL_DOUBLE>&  SrcArrayXPtr,
                                     const std::vector<MIL_DOUBLE>&  SrcArrayYPtr,
                                     CMilArrayParamIn                SrcArrayAnglePtr,
                                     CMilArrayParamOut               DstArrayXPtr,
                                     CMilArrayParamOut               DstArrayYPtr,
                                     CMilArrayParamOut               DstArrayIndexPtr,
                                     CMilArrayParamOut               DstArrayLabelPtr,
                                     MIL_INT64                       ControlFlag)
   {
#if M_MIL_USE_SAFE_TYPE
   if(SrcArrayXPtr.empty())
      {
      SafeTypeError(MIL_TEXT("MedgeGetNeighbors"), MIL_TEXT("The input vectors cannot be empty."));
      }
   if(!SrcArrayAnglePtr.IsValidParam())
      {
      SafeTypeError(MIL_TEXT("MedgeGetNeighbors"), MIL_TEXT("SrcArrayAnglePtr cannot be an non zero integer."));
      }
   if(SrcArrayXPtr.size() != SrcArrayYPtr.size() ||
      ((MIL_INT)SrcArrayXPtr.size() != SrcArrayAnglePtr.Size<MIL_DOUBLE>() && !SrcArrayAnglePtr.IsNullPtr()) ||
      ((MIL_INT)SrcArrayYPtr.size() != SrcArrayAnglePtr.Size<MIL_DOUBLE>() && !SrcArrayAnglePtr.IsNullPtr()))
      {
      SafeTypeError(MIL_TEXT("MedgeGetNeighbors"), MIL_TEXT("The input vectors must have the same size."));
      }
   if(!SrcArrayAnglePtr.IsNullPtr() && SrcArrayAnglePtr.GetMilDataType() != MilTraits<MIL_DOUBLE>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("MedgeGetNeighbors"), MIL_TEXT("The data type of SrcArrayAnglePtr must be MIL_DOUBLE."));
      }
   if(!DstArrayXPtr.IsNullPtr() && DstArrayXPtr.GetMilDataType() != MilTraits<MIL_DOUBLE>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("MedgeGetNeighbors"), MIL_TEXT("The data type of DstArrayXPtr must be MIL_DOUBLE."));
      }
   if(!DstArrayYPtr.IsNullPtr() && DstArrayYPtr.GetMilDataType() != MilTraits<MIL_DOUBLE>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("MedgeGetNeighbors"), MIL_TEXT("The data type of DstArrayYPtr must be MIL_DOUBLE."));
      }
   if(!DstArrayIndexPtr.IsNullPtr() && DstArrayIndexPtr.GetMilDataType() != MilTraits<MIL_INT>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("MedgeGetNeighbors"), MIL_TEXT("The data type of DstArrayIndexPtr must be MIL_INT."));
      }
   if(!DstArrayLabelPtr.IsNullPtr() && DstArrayLabelPtr.GetMilDataType() != MilTraits<MIL_INT>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("MedgeGetNeighbors"), MIL_TEXT("The data type of DstArrayLabelPtr must be MIL_INT."));
      }
   if(SizeOfArray > (MIL_INT)SrcArrayXPtr.size() && SizeOfArray != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("MedgeGetNeighbors"), MIL_TEXT("SizeOfArray parameter must be smaller or equal (M_DEFAULT) to the size of input vectors."));
      }
#endif

   MIL_INT MaxNeighborNumber = 0;
   MedgeInquire(EdgeResultId, M_NEIGHBOR_MAXIMUM_NUMBER + M_TYPE_MIL_INT, &MaxNeighborNumber);

   if(MaxNeighborNumber == M_DEFAULT)
      {
      MaxNeighborNumber = 1;
      }

   if(SizeOfArray == M_DEFAULT || SizeOfArray > (MIL_INT)SrcArrayXPtr.size())
      {
      SizeOfArray = (MIL_INT)SrcArrayXPtr.size();
      }

   MIL_INT TotalArraySize = 0;

   if(SizeOfArray >= 0)
      {
      TotalArraySize = SizeOfArray * MaxNeighborNumber;

      DstArrayXPtr.Resize<MIL_DOUBLE>(TotalArraySize);
      DstArrayYPtr.Resize<MIL_DOUBLE>(TotalArraySize);
      DstArrayIndexPtr.Resize<MIL_INT>(TotalArraySize);
      DstArrayLabelPtr.Resize<MIL_INT>(TotalArraySize);
      }

   // The following condition will ensure that:
   // 1. If there is an MIL error during the call of MedgeInquire with M_NEIGHBOR_MAXIMUM_NUMBER, don't call any other MIL function;
   // 2. Otherwise, always call MedgeGetNeighbors even if SizeOfArray is not valid.
   if(TotalArraySize > 0 || MaxNeighborNumber > 0)
      {
      MedgeGetNeighbors(EdgeResultId,
                        SizeOfArray,
                        &SrcArrayXPtr[0],
                        &SrcArrayYPtr[0],
                        SrcArrayAnglePtr.GetData<MIL_DOUBLE>(),
                        DstArrayXPtr.GetData<MIL_DOUBLE>(),
                        DstArrayYPtr.GetData<MIL_DOUBLE>(),
                        DstArrayIndexPtr.GetData<MIL_INT>(),
                        DstArrayLabelPtr.GetData<MIL_INT>(),
                        ControlFlag);
      }
   }

// ----------------------------------------------------------
// Overloads for std::vector in MedgePut.
inline void MFTYPE MedgePut(MIL_ID                         ResultEdgeId,
                            MIL_INT                        NumEdgels,
                            CMilArrayParamIn               ChainIndexArrayPtr,
                            const std::vector<MIL_DOUBLE>& PosXArrayPtr,
                            const std::vector<MIL_DOUBLE>& PosYArrayPtr,
                            CMilArrayParamIn               AngleArrayPtr,
                            CMilArrayParamIn               MagnitudeArrayPtr,
                            MIL_INT64                      ControlFlag)
   {
#if M_MIL_USE_SAFE_TYPE
   if(NumEdgels <= 0)
      {
      SafeTypeError(MIL_TEXT("MedgePut"), MIL_TEXT("NumEdgels parameter must be greater than zero."));
      }
   if(PosXArrayPtr.empty())
      {
      SafeTypeError(MIL_TEXT("MedgePut"), MIL_TEXT("The input vectors cannot be empty."));
      }
   if(!ChainIndexArrayPtr.IsValidParam() || !AngleArrayPtr.IsValidParam() || !MagnitudeArrayPtr.IsValidParam())
      {
      SafeTypeError(MIL_TEXT("MedgePut"), MIL_TEXT("ChainIndexArrayPtr, AngleArrayPtr or MagnitudeArrayPtr cannot be an non zero integer."));
      }
   if((ChainIndexArrayPtr.Size<MIL_INT>() != (MIL_INT)PosXArrayPtr.size() && !ChainIndexArrayPtr.IsNullPtr()) ||
      (ChainIndexArrayPtr.Size<MIL_INT>() != (MIL_INT)PosYArrayPtr.size() && !ChainIndexArrayPtr.IsNullPtr()) ||
      (ChainIndexArrayPtr.Size<MIL_INT>() != AngleArrayPtr.Size<MIL_DOUBLE>() && !ChainIndexArrayPtr.IsNullPtr() && !AngleArrayPtr.IsNullPtr()) ||
      (ChainIndexArrayPtr.Size<MIL_INT>() != MagnitudeArrayPtr.Size<MIL_DOUBLE>() && !ChainIndexArrayPtr.IsNullPtr() && !MagnitudeArrayPtr.IsNullPtr()) ||
      PosXArrayPtr.size() != PosYArrayPtr.size() ||
      ((MIL_INT)PosXArrayPtr.size() != AngleArrayPtr.Size<MIL_DOUBLE>() && !AngleArrayPtr.IsNullPtr()) ||
      ((MIL_INT)PosXArrayPtr.size() != MagnitudeArrayPtr.Size<MIL_DOUBLE>() && !MagnitudeArrayPtr.IsNullPtr()) ||
      ((MIL_INT)PosYArrayPtr.size() != AngleArrayPtr.Size<MIL_DOUBLE>() && !AngleArrayPtr.IsNullPtr()) ||
      ((MIL_INT)PosYArrayPtr.size() != MagnitudeArrayPtr.Size<MIL_DOUBLE>() && !MagnitudeArrayPtr.IsNullPtr()) ||
      (AngleArrayPtr.Size<MIL_DOUBLE>() != MagnitudeArrayPtr.Size<MIL_DOUBLE>() && !AngleArrayPtr.IsNullPtr() && !MagnitudeArrayPtr.IsNullPtr()))
      {
      SafeTypeError(MIL_TEXT("MedgePut"), MIL_TEXT("The input vectors must have the same size."));
      }
   if(!ChainIndexArrayPtr.IsNullPtr() && ChainIndexArrayPtr.GetMilDataType() != MilTraits<MIL_INT>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("MedgePut"), MIL_TEXT("The data type of ChainIndexArrayPtr must be MIL_INT."));
      }
   if(!AngleArrayPtr.IsNullPtr() && AngleArrayPtr.GetMilDataType() != MilTraits<MIL_DOUBLE>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("MedgePut"), MIL_TEXT("The data type of AngleArrayPtr must be MIL_DOUBLE."));
      }
   if(!MagnitudeArrayPtr.IsNullPtr() && MagnitudeArrayPtr.GetMilDataType() != MilTraits<MIL_DOUBLE>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("MedgePut"), MIL_TEXT("The data type of MagnitudeArrayPtr must be MIL_DOUBLE."));
      }
   if(NumEdgels > (MIL_INT)PosXArrayPtr.size() && NumEdgels != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("MedgePut"), MIL_TEXT("NumEdgels parameter must be smaller or equal (M_DEFAULT) to the size of input vectors."));
      }
#endif

   if(NumEdgels == M_DEFAULT || NumEdgels > (MIL_INT)PosXArrayPtr.size())
      {
      NumEdgels = (MIL_INT)PosXArrayPtr.size();
      }

   MedgePut(ResultEdgeId,
            NumEdgels,
            ChainIndexArrayPtr.GetData<MIL_INT>(),
            &PosXArrayPtr[0],
            &PosYArrayPtr[0],
            AngleArrayPtr.GetData<MIL_DOUBLE>(),
            MagnitudeArrayPtr.GetData<MIL_DOUBLE>(),
            ControlFlag);
   }

// ----------------------------------------------------------
// Overloads for std::vector in MxxxStream.
inline void MFTYPE MedgeStream(std::vector<MIL_UINT8>  &MemPtrOrFileName,
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
                          MedgeStream);
   }
#endif // defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR

#if M_MIL_USE_STRING
/***************************************************************************/
/* EDGE FINDER MODULE                                                      */
/***************************************************************************/

#if M_MIL_USE_UNICODE
#if M_MIL_UNICODE_API
inline void MFTYPE MedgeSaveW(const MIL_STRING& FileName, MIL_ID ContextOrResultId, MIL_INT64 ControlFlag)
   {
   return MedgeSaveW(FileName.c_str(), ContextOrResultId, ControlFlag);
   }

inline MIL_ID MFTYPE MedgeRestoreW(const MIL_STRING& FileName, MIL_ID SystemId, MIL_INT64 ControlFlag, MIL_ID* ContextIdPtr)
   {
   return MedgeRestoreW(FileName.c_str(), SystemId, ControlFlag, ContextIdPtr);
   }

#else
inline void MFTYPE MedgeSaveA(const MIL_STRING& FileName, MIL_ID ContextOrResultId, MIL_INT64 ControlFlag)
   {
   return MedgeSaveA(FileName.c_str(), ContextOrResultId, ControlFlag);
   }

inline MIL_ID MFTYPE MedgeRestoreA(const MIL_STRING& FileName, MIL_ID SystemId, MIL_INT64 ControlFlag, MIL_ID* ContextIdPtr)
   {
   return MedgeRestoreA(FileName.c_str(), SystemId, ControlFlag, ContextIdPtr);
   }

#endif /* M_MIL_UNICODE_API */

#else
inline void MFTYPE MedgeSave(const MIL_STRING& FileName, MIL_ID ContextOrResultId, MIL_INT64 ControlFlag)
   {
   return MedgeSave(FileName.c_str(), ContextOrResultId, ControlFlag);
   }

inline MIL_ID MFTYPE MedgeRestore(const MIL_STRING& FileName, MIL_ID SystemId, MIL_INT64 ControlFlag, MIL_ID* ContextIdPtr)
   {
   return MedgeRestore(FileName.c_str(), SystemId, ControlFlag, ContextIdPtr);
   }

#endif /* M_MIL_USE_UNICODE */
#endif /* M_MIL_USE_STRING*/

////////////////////////////////////////////////////////////////////////////////
// MIL_UNIQUE_ID support

#if M_MIL_USE_MIL_UNIQUE_ID

#if M_MIL_USE_SAFE_TYPE
template <> inline bool MilIsCorrectObjectType<&MedgeFree>(MIL_INT64 ObjectType)
   {
   return (ObjectType & ~M_USER_DEFINE_LOW_ATTRIBUTE) == M_EDGE_OBJECT;
   }
#endif

typedef MIL_UNIQUE_ID<&MedgeFree> MIL_UNIQUE_EDGE_ID;

#if M_MIL_USE_MOVE_SEMANTICS

inline MIL_UNIQUE_EDGE_ID MedgeAlloc(MIL_ID SystemId, MIL_INT64 EdgeFinderType, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_EDGE_ID(MedgeAlloc(SystemId, EdgeFinderType, ControlFlag, M_NULL));
   }
inline MIL_UNIQUE_EDGE_ID MedgeAllocResult(MIL_ID SystemId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_EDGE_ID(MedgeAllocResult(SystemId, ControlFlag, M_NULL));
   }
inline MIL_UNIQUE_EDGE_ID MedgeRestore(MIL_CONST_TEXT_PTR FileName, MIL_ID SystemId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_EDGE_ID(MedgeRestore(FileName, SystemId, ControlFlag, M_NULL));
   }
#if M_MIL_USE_STRING
inline MIL_UNIQUE_EDGE_ID MedgeRestore(const MIL_STRING& FileName, MIL_ID SystemId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_EDGE_ID(MedgeRestore(FileName, SystemId, ControlFlag, M_NULL));
   }
#endif // M_MIL_USE_STRING
template <MilFreeFuncType FreeFunc> inline void MedgeFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

inline void MedgeStream(MilStreamParam       MemPtrOrFileName        ,
                        MIL_ID               SysId                   ,
                        MIL_INT64            Operation               ,
                        MIL_INT64            StreamType              ,
                        MIL_DOUBLE           Version                 ,
                        MIL_INT64            ControlFlag             ,
                        MIL_UNIQUE_EDGE_ID*  ContextOrResultEdgeIdPtr,
                        MIL_INT*             SizeByteVarPtr          )
   {
   MxxxStreamForMilUniqueId(MemPtrOrFileName, SysId, Operation, StreamType, Version, ControlFlag, ContextOrResultEdgeIdPtr, SizeByteVarPtr, MedgeStream);
   }

#endif // M_MIL_USE_MOVE_SEMANTICS
#endif // M_MIL_USE_MIL_UNIQUE_ID

// End of MIL_UNIQUE_ID support
////////////////////////////////////////////////////////////////////////////////

#endif // !M_MIL_LITE
#endif // __MILEDGEEXTR_H__
