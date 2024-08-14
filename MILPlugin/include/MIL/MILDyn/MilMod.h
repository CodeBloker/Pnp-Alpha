﻿/***************************************************************************/
/*

    Filename:  MilMod.h
    Owner   :  Matrox Imaging
    Revision:  10.40.0881
    Content :  This file contains the defines and the prototypes for the
               MIL geometric pattern matching module. (Mmod...).

    Copyright © Matrox Electronic Systems Ltd., 1992-2021.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef __MILMOD_H__
#define __MILMOD_H__

#if (!M_MIL_LITE) // MIL FULL ONLY

#if M_MIL_USE_RT
#ifdef M_MOD_EXPORTS
#define MIL_MOD_DLLFUNC __declspec(dllexport)
#else
#define MIL_MOD_DLLFUNC __declspec(dllimport)
#endif
#else
#define MIL_MOD_DLLFUNC
#endif

/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
{
#endif


/***************************************************************************/
/*                      MilMod CAPI defines                                */
/***************************************************************************/

/***************************************************************************/
/* MmodAlloc()                                                             */
/***************************************************************************/

/* Object types */
#define M_RESULT                0x00001000L

#define M_GEOMETRIC             0x00002000L
#define M_GEOMETRIC_CONTROLLED  0x00008000L
#define M_SHAPE_CIRCLE          0x00010000L
#define M_SHAPE_ELLIPSE         0x00020000L
#define M_SHAPE_RECTANGLE       0x00040000L
#define M_SHAPE_SEGMENT         0x00080000L

/***************************************************************************/
/* MmodGetResult()                                                         */
/***************************************************************************/
/* For ResultIndex */
#define M_ALL                  0x40000000L  // already defined in Mil.h

/* For Result Type */
#define M_NUMBER                     1009L  // already defined in Mil.h
#define M_GENERAL              0x20000000L  // also defined in milreg.h
#define M_CONTEXT_ID           0x00001010L
#define M_TIMEOUT_END                  10L
#define M_SCORE                0x00001400L  // already defined in MilPat.h
#define M_TARGET_COVERAGE      0x00001500L
#define M_MODEL_COVERAGE       0x00001600L
#define M_FIT_ERROR            0x00001700L
#define M_SCORE_TARGET         0x00001800L
#define M_POSITION_X           0x00003400L  // already defined in MilPat.h
#define M_POSITION_Y           0x00004400L  // already defined in MilPat.h
#define M_ANGLE                0x00000800L  // already defined in Mil.h
#define M_SCALE                0x00008010L  // already defined in Milpat.h
#define M_A_FORWARD            0x00004001L
#define M_B_FORWARD            0x00004002L
#define M_C_FORWARD            0x00004003L
#define M_D_FORWARD            0x00004004L
#define M_E_FORWARD            0x00004005L
#define M_F_FORWARD            0x00004006L
#define M_A_REVERSE            0x00004011L
#define M_B_REVERSE            0x00004012L
#define M_C_REVERSE            0x00004013L
#define M_D_REVERSE            0x00004014L
#define M_E_REVERSE            0x00004015L
#define M_F_REVERSE            0x00004016L
#define M_RADIUS               0x00000040L 
#define M_CIRCLE_ASPECT_RATIO  0x00002018L 
#define M_SQUARE_ASPECT_RATIO  0x00000008L // already defined in Mil.h 
#define M_CENTER_X                      4L
#define M_CENTER_Y                      5L
#define M_SCORE_FIT                  2461L
#define M_TOP_LEFT_X                 1004L   // already defined in MilCode.h
#define M_TOP_LEFT_Y                 1005L   // already defined in MilCode.h
#define M_TOP_RIGHT_X                1014L   // already defined in MilCode.h
#define M_TOP_RIGHT_Y                1015L   // already defined in MilCode.h
#define M_BOTTOM_LEFT_X              1016L   // already defined in MilCode.h
#define M_BOTTOM_LEFT_Y              1017L   // already defined in MilCode.h
#define M_BOTTOM_RIGHT_X             1018L   // already defined in MilCode.h
#define M_BOTTOM_RIGHT_Y             1019L   // already defined in MilCode.h

#define M_AVAILABLE       MAKE_INT64(0x0000400000000000) // Also defined in mil.h

/***************************************************************************/
/* MmodDefine()                                                            */
/***************************************************************************/

#define M_DELETE                    3L   // 3   Already defined in Milblob.h

#define M_IMAGE            0x00000004L   // 4   Already defined in  Mil.h       
#define M_CIRCLE           0x00000008L   // 8   Already defined in  MilBga.h        
#define M_ELLIPSE          0x00000010L   // 16
#define M_SQUARE           0x00000020L   // 32
#define M_RECTANGLE        0x00000040L   // 64
#define M_LINE             0x00000080L   // 128
#define M_RING             0x00000100L   // 256
#define M_DXF_FILE         0x00000200L   // 512
#define M_CROSS            0x00002000L   // 8192 Already defined in  MilBga.h
#define M_DIAMOND          0x00008000L   // 32768
#define M_TRIANGLE         0x00010000L   // 65536
#define M_MERGE_MODEL      0x00020000L   // 131072
#define M_AUTO_DEFINE      0x00040000L   // 262144
#define M_NO_CHECK         0x40000000L   // already defined.

#define M_SEGMENT          0x00000082L    // Already defined in milmetrol.h

/***************************************************************************/
/* MmodDefineFromFile()                                                    */
/***************************************************************************/
#define M_MEMORY           (M_APP_INQUIRE_SYS_START+120L) /*5120*/  // Already defined in Mil.h
#define M_INTERACTIVE           M_NULL   // Already defined in mil.h, milcal.h, milcode.h, miledge.h, milmeas.h, milocr.h, milpat.h
#define M_DXF_FILE         0x00000200L   // 512


/***************************************************************************/
/* MmodControl() / MmodInquire()                                           */
/***************************************************************************/
  
// For Index 
#define M_DEFAULT                      0x10000000L  // already defined in Mil.h                     
#define M_CONTEXT                      0x08000000L
#define M_ALL                          0x40000000L  // already defined in Mil.h

// Modifier 
#define M_SUPPORTED                    MAKE_INT64(0x0000800000000000) // Also defined in mil.h

// Context controls/inquires 
#define M_IMAGE_ID                     0x04000000L
#define M_NUMBER                       1009L  // already defined in Mil.h
#define M_REFERENCE_X                  100L  // also defined in milreg.h
#define M_REFERENCE_Y                  101L  // also defined in milreg.h
#define M_REFERENCE_ANGLE              110L
#if OldDefinesSupport
   #define M_SEARCH_OFFSET_X           102L
   #define M_SEARCH_OFFSET_Y           103L
   #define M_SEARCH_SIZE_X             104L
   #define M_SEARCH_SIZE_Y             105L 
// MIL_DEPRECATED(M_SEARCH_OFFSET_X, 1010) // Also defined in MilPat.h
// MIL_DEPRECATED(M_SEARCH_OFFSET_Y, 1010) // Also defined in MilPat.h
// MIL_DEPRECATED(M_SEARCH_SIZE_X  , 1010) // Also defined in MilPat.h
// MIL_DEPRECATED(M_SEARCH_SIZE_Y  , 1010) // Also defined in MilPat.h
#endif

#define M_ACCURACY                     106L
#define M_SPEED                          8L  // Already define in milpat.h
#define M_SMOOTHNESS                   108L
#if OldDefinesSupport
   #define M_KERNEL_WIDTH              109L
   //MIL_DEPRECATED(M_KERNEL_WIDTH, 1010)
#endif
#define M_FILTER_MODE                  122L  // allready defined in miledge.h
#define M_DETAIL_LEVEL                 111L
#define M_SEARCH_ANGLE_RANGE           113L  // also defined in milreg.h
#define M_SEARCH_SCALE_RANGE           114L  // also defined in milreg.h
#define M_SEARCH_POSITION_RANGE        119L  // also defined in milreg.h
#define M_TIMEOUT                     2077L    // already define in mil.h
#define M_STOP_FIND                    115L
#define M_SHARED_EDGES                 220L
#define M_TARGET_CACHING                39L    // Already define in milpat.h
#define M_SAVE_TARGET_EDGES            121L    // Already define in milpat.h
#define M_OVERSCAN                      53L    // Already define in mil.h
#define M_OVERSCAN_REPLACE_VALUE        54L    // Already define in mil.h
#define M_CONTEXT_CONVERT              535L    // Already define in milocr.h


#define M_SEARCH_POSITION_FROM_GRAPHIC_LIST 1723L

// Context controls/inquires for M_GEOMETRIC_CONTROLLED
#define M_FIRST_LEVEL                   31L //Already defined in milpat.h
#define M_LAST_LEVEL                    32L //Already defined in milpat.h
#define M_AUTO                         444L //Already defined in milocr.h


// Model controls/inquires
#define M_ACCEPTANCE                         200L
#define M_ACCEPTANCE_TARGET                  201L
#define M_CERTAINTY                          202L           
#define M_CERTAINTY_TARGET                   203L
#define M_POLARITY                           0x00004000L  // already defined in MilMeas.h 
#if OldDefinesSupport
   #define M_POLARITY_CHECK                  M_POLARITY
   MIL_DEPRECATED(M_POLARITY_CHECK, 1010)
#endif
#define M_MIN_SEPARATION_X                   35L              // already defined in MilPat.h 
#define M_MIN_SEPARATION_Y                   36L              // already defined in MilPat.h 
#define M_SCALE                              0x00008010L      // already defined in MilPat.h 
#define M_SCALE_MIN_FACTOR                   210L             // also defined in milreg.h
#define M_SCALE_MAX_FACTOR                   211L             // also defined in milreg.h
#define M_ASPECT_RATIO                      6001L             // (Already defined in milcal.h) 
#define M_EMPTY                              236L



#define M_ACTIVE_EDGELS                      1719L // also defined in MilMetrol.h



#define M_CORNER_RADIUS                      239L
#define M_ANGLE                              0x00000800L  // already defined in Mil.h
#define M_ANGLE_DELTA_NEG                    0x00000200L  // Already define in MilPat.h 
#define M_ANGLE_DELTA_POS                    0x00000400L  // Already define in MilPat.h 
#define M_INDEX                              217L
#define M_FIT_ERROR_WEIGHTING_FACTOR         221L
#define M_USER_LABEL                         228L   // also defined in milreg.h
#define M_INDEX_FROM_LABEL                   229L   // also defined in milreg.h
#define M_NUMBER_OF_CHAINED_PIXELS           56L    // Already define in MilBlob.h
#define M_NUMBER_OF_CHAINED_EDGELS           M_NUMBER_OF_CHAINED_PIXELS
#define M_CHAIN_X                            65L    // Already define in MilBlob.h
#define M_CHAIN_Y                            144L   // Already define in MilBlob.h
#define M_CHAIN_ANGLE                        258L   // Already define in MilEdge.h
#define M_CHAIN_INDEX                        67L    // Already define in MilBlob.h

#define M_MIN_SEPARATION_SCALE               68L
#define M_MIN_SEPARATION_ANGLE               69L
#define M_MIN_SEPARATION_ASPECT_RATIO        2016L
#define M_SEARCH_ASPECT_RATIO_CONSTRAINT     2215L
#define M_ASSOCIATED_CALIBRATION             125L   // Already define in MilCal.h
#define M_CALIBRATED                         0x0000300L

#define M_POSITION_DELTA_NEG_X               127L  // also defined in milreg.h
#define M_POSITION_DELTA_POS_X               128L  // also defined in milreg.h
#define M_POSITION_DELTA_NEG_Y               129L  // also defined in milreg.h
#define M_POSITION_DELTA_POS_Y               130L  // also defined in milreg.h







#define M_SAGITTA_TOLERANCE                  1969L
#define M_DEVIATION_TOLERANCE                3035L
#define M_MODEL_ASPECT_RATIO                 2219L
#define M_MODEL_ASPECT_RATIO_MIN_FACTOR      2220L
#define M_MODEL_ASPECT_RATIO_MAX_FACTOR      2221L

#define M_COVERAGE_MAX                       2457L 
#define M_FIT_SCORE_MIN                      2458L 
#define M_LINE_PRESEARCH                     2801L 
#define M_MIN_SIDE_COVERAGE                  2802L
#define M_ANGLE_MULTIPLE_RANGE               2803L
#define M_STEP_180                           2818L
#define M_STEP_90                            2905L 
#define M_USE_GRID_DECOMPOSITION             2849L
#define M_COVERAGE_MIN                       2453L 
#define M_ANGLE_REGION                       3095L

#define M_SEGMENT_CONSISTENT_GRADIENT        2943L

#define M_TRUE                               1L     // Already defined in    mil.h, milmeas.h, miledge.h
#define M_FALSE                              0L     // Already defined in    mil.h, milmeas.h, miledge.h
// Controls/inquires for Synthetic models

#define M_BOX_MARGIN_LEFT                    308L
#define M_BOX_MARGIN_RIGHT                   309L
#define M_BOX_MARGIN_TOP                     310L
#define M_BOX_MARGIN_BOTTOM                  311L
#define M_PIXEL_SCALE                        316L
#define M_CAD_Y_AXIS                         318L

// Controls/inquires for results
#define M_RESULT_OUTPUT_UNITS          1300L // Also in milim.h


// CAD Y Axis control values
#define M_FLIP                        0x00010000L   // Already defined in Mil.h
#define M_NO_FLIP                     0x04000000L   // Already defined in Mil.h


// Types of polarity check
#define M_SAME                               -1L   // Already defined in MilMeas.h
#define M_REVERSE                             4L   // Already defined in Mil.h
#define M_SAME_OR_REVERSE                     5L
#define M_ANY                        0x11000000L   // Already defined in MilMeas.h

#if OldDefinesSupport
   #define M_MIX                           M_ANY 
   MIL_DEPRECATED(M_MIX, 1010)
#endif

// To remove user label
#define M_NO_LABEL                   0x20000000L   // Also defined in milreg.h

// Control values
#define M_VERY_LOW                             0L  // Already define in milpat.h
#define M_LOW                                  1L  // Already define in milpat.h
#define M_MEDIUM                               2L  // Already define in milpat.h
#define M_HIGH                                 3L  // Already define in milpat.h
#define M_VERY_HIGH                            4L  // Already define in milpat.h


#if OldDefinesSupport
   #define M_KERNEL_DEPTH                    368L 
   ///MIL_DEPRECATED(M_KERNEL_DEPTH, 1010)
#endif
#define M_SIZE                             0xC00L  // Already define  in medge.h
#define M_RECURSIVE                    0x00040000  // Already defined in mildev.h
#define M_KERNEL                      0x00400000L  // Already defined in mil.h

// Parameters for output units
#define M_PIXEL                              0x1000L
#define M_WORLD                              0x2000L
#define M_ACCORDING_TO_CALIBRATION             1301L

/***************************************************************************/
/* MmodInquire()                                                           */
/***************************************************************************/
#define M_VALID                        0x00000001L  // Already define in Mil.h
#define M_CONTEXT_TYPE                 162
#define M_MODEL_TYPE                   162
#define M_PREPROCESSED                 14L          // Already define in MilPat.h
#define M_KERNEL_SIZE                  301L
#define M_NUMBER_MODELS                302L
#define M_MODIFICATION_COUNT           5010L        // Already define in Mil.h
#define M_OWNER_SYSTEM                 1101L        // already define in mil.h
#define M_SIZE_BYTE                    5061L        // already defined in Mil.h
#define M_ALLOC_OFFSET_X               15L          // Already define in MilPat.h
#define M_ALLOC_OFFSET_Y               16L          // Already define in MilPat.h
#define M_ALLOC_ANGLE                  3329L        // Already define in MilPat.h
#define M_ALLOC_SIZE_X                 2L           // Already define in MilPat.h
#define M_ALLOC_SIZE_Y                 3L           // Already define in MilPat.h
#define M_ORIGINAL_X                   6L           // Already define in MilPat.h
#define M_ORIGINAL_Y                   7L           // Already define in MilPat.h
#define M_WARNINGS                     306L
#define M_ALLOC_SIZE_BAND              321L
#define M_ALLOC_TYPE                   322L         // Already defined in MilPat.h
#define M_ALLOC_SIGN                   323L
#define M_ALLOC_SIZE_BIT                26L         // Already defined in MilPat.h

// Model inquires for Misc Synthetic Model 
#define M_RADIUS                             0x00000040L
#define M_FOREGROUND_VALUE                   4L       // Already defined in MilBlob.h         
#define M_FOREGROUND_WHITE                   0x80L    // Already define in MilBlob.h 
#define M_FOREGROUND_BLACK                   0x100L   // Already define in MilBlob.h 
#define M_FOREGROUND_ANY                     M_FOREGROUND_WHITE+M_FOREGROUND_BLACK

#define M_LENGTH                             0x00002000L // already defined in Mil.h
#define M_WIDTH                              0x00010000L // Already defined in Milmeas.h
#define M_HEIGHT                             317L
#define M_HORIZONTAL_THICKNESS               233L
#define M_VERTICAL_THICKNESS                 232L
#define M_INNER_RADIUS                       234L
#define M_OUTER_RADIUS                       235L
                                             
#define M_BOX_OFFSET_X                       312L
#define M_BOX_OFFSET_Y                       313L
#define M_BOX_SIZE_X                         314L
#define M_BOX_SIZE_Y                         315L

#define M_MOD_DEFINE_COMPATIBLE              330L


#define M_HAS_DONT_CARE_MASK                2391      // also defined in milpat.h
#define M_HAS_FLAT_REGIONS_MASK             2392
#define M_HAS_WEIGHT_REGIONS_MASK           2393

#define M_START_POS_X                       2820
#define M_START_POS_Y                       2821
#define M_END_POS_X                         2822
#define M_END_POS_Y                         2823
#define M_LINE_TYPE                         2824
#define M_CREST_WHITE                       2825
#define M_CREST_BLACK                       2826

#define M_RESULT_TYPE                          1L     // Already defined in    milmeas.h, milim.h
#define M_HAS_TARGET_EDGES_SAVED             2679

/***************************************************************************/
/* MmodDraw()                                                              */
/***************************************************************************/

#define M_DRAW_IMAGE                    0x00000002L   // Already define in MilPat.h
#define M_DRAW_EDGES                    0x00000004L
#define M_DRAW_DONT_CARE                0x00000008L   // Already define in MilPat.h
#if OldDefinesSupport
  #define M_DRAW_DONT_CARES            M_DRAW_DONT_CARE 
  //MIL_DEPRECATED(M_DRAW_DONT_CARES, 1010)
#endif
#define M_DRAW_FLAT_REGIONS             0x00000010L
#define M_DRAW_BOX                      0x00000020L   // Already define in MilPat.h
#define M_DRAW_POSITION                 0x00000040L   // Already define in MilPat.h
#define M_DRAW_WEIGHT_REGIONS           0x00000100L
#define M_DRAW_AXIS                     0x00000200L   // Already define in MilBlob.h

#define M_ORIGINAL                      0x00000199L   // Already define in MilPat.h
#define M_MODEL                         0x00010000L   //65536
#define M_TARGET                        0x00080000L   // Also defined in milreg.h

#define M_DRAW_ACTIVE_EDGELS            0x00100000L   // Also defined in milmetrol.h

#if OldDefinesSupport
   #define M_DRAW_RELATIVE_ORIGIN_X            319L        // deprecated : Use MgraControl(... M_DRAW_OFFSET_X...)
   #define M_DRAW_RELATIVE_ORIGIN_Y            320L        // deprecated : Use MgraControl(... M_DRAW_OFFSET_Y...)
   #define M_DRAW_SCALE_X                     3203L        // deprecated : Use MgraControl(... M_DRAW_ZOOM_X ...)
   #define M_DRAW_SCALE_Y                     3204L        // deprecated : Use MgraControl(... M_DRAW_ZOOM_Y ...)
//    MIL_DEPRECATED(M_DRAW_RELATIVE_ORIGIN_X, 1010)          Already defined in mil.h
//    MIL_DEPRECATED(M_DRAW_RELATIVE_ORIGIN_Y, 1010)          Already defined in mil.h
//    MIL_DEPRECATED(M_DRAW_SCALE_X, 1010)                    Already defined in mil.h
//    MIL_DEPRECATED(M_DRAW_SCALE_Y, 1010)                    Already defined in mil.h
#endif

/***************************************************************************/
/* MmodMask()                                                              */
/***************************************************************************/
#if OldDefinesSupport
   #define M_DONT_CARES            M_DONT_CARE
   MIL_DEPRECATED(M_DONT_CARES, 1010)
#endif
#define M_DONT_CARE             0x00008000L // already defined in mil.h, milpat.h, milmod.h
#define M_FLAT_REGIONS                 501L
#define M_WEIGHT_REGIONS               502L


/***************************************************************************/
/* MmodPreprocess()                                                        */
/***************************************************************************/
#define M_RESET                          9L
#define M_COMPLETE              0x00000000L // Already defined in Mil.h
#define M_PARTIAL               0x00000001L // Already defined in Mil.h



/***************************************************************************/
/* MmodSave()/MmodRestore()/MmodStream()                                   */
/***************************************************************************/
#define M_MEMORY                         (M_APP_INQUIRE_SYS_START+120L) /*5120*/  // Already defined in Mil.h
#define M_INTERACTIVE                    M_NULL // Already defined in    mil.h, milcal.h, milcode.h, milmeas.h, milocr.h, milpat.h, milmod.h

#define M_SAVE                             0x100L
#define M_RESTORE                           0x10L
#define M_LOAD                                 1L
#define M_INQUIRE_SIZE_BYTE                    2L

#define M_WITH_CALIBRATION            0x00020000L // Already in mil.h


/***************************************************************************/
/*                 WARNINGS definitions and string table                   */
/***************************************************************************/


// Deprecated flag names.
#if OldDefinesSupport
   // #define        M_MAJOR_AXIS_MAX 216L already defined in milmeas.h
   // MIL_DEPRECATED(M_MAJOR_AXIS_MAX, 1000)       already defined in milmeas.h
   // #define        M_MAJOR_AXIS_MIN 214L already defined in milmeas.h
   // MIL_DEPRECATED(M_MAJOR_AXIS_MIN, 1000)       already defined in milmeas.h
   // #define        M_MAJOR_AXIS M_RADIUS already defined in milmeas.h
   // MIL_DEPRECATED(M_MAJOR_AXIS, 1000)   already defined in milmeas.h
#endif

/***************************************************************************/
/*                 MilMod CAPI function prototypes                         */
/***************************************************************************/

MIL_MOD_DLLFUNC MIL_ID MFTYPE MmodAlloc         (MIL_ID      SystemId,
                                 MIL_INT64   ModelFinderType,
                                 MIL_INT64   ControlFlag,
                                 MIL_ID*     ContextIdPtr);

MIL_MOD_DLLFUNC MIL_ID MFTYPE MmodAllocResult   (MIL_ID      SystemId,
                                 MIL_INT64   ControlFlag,
                                 MIL_ID*     ModResultIdPtr);

#if M_MIL_USE_64BIT
// Prototypes for 64 bits OSs
MIL_MOD_DLLFUNC void MFTYPE MmodDefineInt64     (MIL_ID      ContextId,
                                 MIL_INT64   ModelType,
                                 MIL_INT64   Param1,
                                 MIL_DOUBLE  Param2,
                                 MIL_DOUBLE  Param3,
                                 MIL_DOUBLE  Param4,
                                 MIL_DOUBLE  Param5);

MIL_MOD_DLLFUNC void MFTYPE MmodDefineDouble    (MIL_ID      ContextId,
                                 MIL_INT64   ModelType,
                                 MIL_DOUBLE  Param1,
                                 MIL_DOUBLE  Param2,
                                 MIL_DOUBLE  Param3,
                                 MIL_DOUBLE  Param4,
                                 MIL_DOUBLE  Param5);
#else
// Prototypes for 32 bits OSs
#define MmodDefineInt64  MmodDefine
#define MmodDefineDouble MmodDefine
MIL_MOD_DLLFUNC void MFTYPE MmodDefine          (MIL_ID      ContextId,
                                 MIL_INT64   ModelType,
                                 MIL_DOUBLE  Param1,
                                 MIL_DOUBLE  Param2,
                                 MIL_DOUBLE  Param3,
                                 MIL_DOUBLE  Param4,
                                 MIL_DOUBLE  Param5);
#endif

#if M_MIL_USE_64BIT
// Prototypes for 64 bits OSs
MIL_MOD_DLLFUNC void MFTYPE MmodControlInt64    (MIL_ID      ContextOrResultId,
                                 MIL_INT     Index,
                                 MIL_INT64   ControlType,
                                 MIL_INT64   ControlValue);

MIL_MOD_DLLFUNC void MFTYPE MmodControlDouble   (MIL_ID      ContextOrResultId,
                                 MIL_INT     Index,
                                 MIL_INT64   ControlType,
                                 MIL_DOUBLE  ControlValue);

#else
// Prototypes for 32 bits OSs
#define MmodControlInt64  MmodControl
#define MmodControlDouble MmodControl
MIL_MOD_DLLFUNC void MFTYPE MmodControl         (MIL_ID      ContextOrResultId,
                                 MIL_INT     Index,
                                 MIL_INT64   ControlType,
                                 MIL_DOUBLE  ControlValue);
#endif

MIL_MOD_DLLFUNC MIL_INT MFTYPE MmodInquire      (MIL_ID      ContextOrResultId,
                                 MIL_INT     Index,
                                 MIL_INT64   InquireType,
                                 void*       UserVarPtr);

MIL_MOD_DLLFUNC void MFTYPE MmodMask            (MIL_ID      ContextId,
                                 MIL_INT     Index,
                                 MIL_ID      MaskBufferId,
                                 MIL_INT64   MaskType,
                                 MIL_INT64   ControlFlag);

MIL_MOD_DLLFUNC void MFTYPE MmodPreprocess      (MIL_ID      ContextId,
                                 MIL_INT64   ControlFlag);

MIL_MOD_DLLFUNC void MFTYPE MmodFind            (MIL_ID      ContextId,
                                 MIL_ID      TargetImageOrResultId,
                                 MIL_ID      ModResultId);

MIL_MOD_DLLFUNC void MFTYPE MmodGetResult       (MIL_ID      ResultId,
                                 MIL_INT     ResultIndex,
                                 MIL_INT64   ResultType,
                                 void*       ResultArrayPtr);

MIL_MOD_DLLFUNC void MFTYPE MmodGetResultOutputUnits(MIL_ID     ResultId,
                                     MIL_INT    ResultIndex,
                                     MIL_INT64  ResultType,
                                     MIL_INT64  OutputUnits,
                                     void*      ResultArrayPtr);

MIL_MOD_DLLFUNC void MFTYPE MmodDraw            (MIL_ID      ContextGraId,
                                 MIL_ID      ContextOrResultModId,
                                 MIL_ID      DstImageBufOrListGraId,
                                 MIL_INT64   Operation,
                                 MIL_INT     Index,
                                 MIL_INT64   ControlFlag);
#if M_MIL_USE_UNICODE

MIL_MOD_DLLFUNC void MFTYPE MmodDefineFromFileW (MIL_ID         ContextModId,
                                 MIL_INT64      FileType,
                                 MIL_CONST_TEXTW_PTR   FileName,
                                 MIL_INT64      ControlFlag );

MIL_MOD_DLLFUNC void MFTYPE MmodSaveW           (MIL_CONST_TEXTW_PTR   FileName,
                                 MIL_ID         ContextId,
                                 MIL_INT64      ControlFlag);

MIL_MOD_DLLFUNC MIL_ID  MFTYPE MmodRestoreW     (MIL_CONST_TEXTW_PTR   FileName,
                                 MIL_ID         SystemId, 
                                 MIL_INT64      ControlFlag,
                                 MIL_ID*        ContextIdPtr);

MIL_MOD_DLLFUNC void MFTYPE MmodStreamW         (MIL_TEXTW_PTR   MemPtrOrFileName,
                                 MIL_ID         SysId,
                                 MIL_INT64      Operation,
                                 MIL_INT64      StreamType,
                                 MIL_DOUBLE     Version,
                                 MIL_INT64      ControlFlag,
                                 MIL_ID         *ContextModIdPtr,
                                 MIL_INT        *SizeByteVarPtr);

MIL_MOD_DLLFUNC void MFTYPE MmodDefineFromFileA (MIL_ID         ContextModId,
                                 MIL_INT64      FileType,
                                 MIL_CONST_TEXTA_PTR    FileName,
                                 MIL_INT64      ControlFlag );

MIL_MOD_DLLFUNC void MFTYPE MmodSaveA           (MIL_CONST_TEXTA_PTR    FileName,
                                 MIL_ID         ContextId,
                                 MIL_INT64      ControlFlag);

MIL_MOD_DLLFUNC MIL_ID  MFTYPE MmodRestoreA     (MIL_CONST_TEXTA_PTR    FileName,
                                 MIL_ID         SystemId, 
                                 MIL_INT64      ControlFlag,
                                 MIL_ID*        ContextIdPtr);

MIL_MOD_DLLFUNC void MFTYPE MmodStreamA         (MIL_TEXTA_PTR          MemPtrOrFileName,
                                 MIL_ID         SysId,
                                 MIL_INT64      Operation,
                                 MIL_INT64      StreamType,
                                 MIL_DOUBLE     Version,
                                 MIL_INT64      ControlFlag,
                                 MIL_ID         *ContextModIdPtr,
                                 MIL_INT        *SizeByteVarPtr);
#if M_MIL_UNICODE_API

#define MmodDefineFromFile MmodDefineFromFileW
#define MmodSave           MmodSaveW
#define MmodRestore        MmodRestoreW
#define MmodStream         MmodStreamW

#else

#define MmodDefineFromFile MmodDefineFromFileA
#define MmodSave           MmodSaveA
#define MmodRestore        MmodRestoreA
#define MmodStream         MmodStreamA

#endif

#else

MIL_MOD_DLLFUNC void MFTYPE MmodDefineFromFile  (MIL_ID         ContextModId,
                                 MIL_INT64      FileType,
                                 MIL_CONST_TEXT_PTR   FileName,
                                 MIL_INT64      ControlFlag );

MIL_MOD_DLLFUNC void MFTYPE MmodSave            (MIL_CONST_TEXT_PTR   FileName,
                                 MIL_ID         ContextId,
                                 MIL_INT64      ControlFlag);

MIL_MOD_DLLFUNC MIL_ID  MFTYPE MmodRestore      (MIL_CONST_TEXT_PTR   FileName,
                                 MIL_ID         SystemId, 
                                 MIL_INT64      ControlFlag,
                                 MIL_ID*        ContextIdPtr);

MIL_MOD_DLLFUNC void MFTYPE MmodStream          (MIL_TEXT_PTR   MemPtrOrFileName,
                                 MIL_ID         SysId,
                                 MIL_INT64      Operation,
                                 MIL_INT64      StreamType,
                                 MIL_DOUBLE     Version,
                                 MIL_INT64      ControlFlag,
                                 MIL_ID         *ContextModIdPtr,
                                 MIL_INT        *SizeByteVarPtr);
#endif // M_MIL_USE_UNICODE


MIL_MOD_DLLFUNC void MFTYPE MmodFree            (MIL_ID ObjectId);

/* C++ directive if needed */
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

inline void MFTYPE MmodStreamCpp(MilStreamParam MemPtrOrFileName,
                                   MIL_ID         SysId,
                                   MIL_INT64      Operation,
                                   MIL_INT64      StreamType,
                                   MIL_DOUBLE     Version,
                                   MIL_INT64      ControlFlag,
                                   MIL_ID*        ContextModIdPtr,
                                   MIL_INT*       SizeByteVarPtr)
   {
   MmodStream(MemPtrOrFileName.m_Param, SysId, Operation, StreamType, Version, ControlFlag, ContextModIdPtr, SizeByteVarPtr);
   }

#undef  MmodStream
#define MmodStream MmodStreamCpp

#endif // __cplusplus

#if M_MIL_USE_64BIT
#ifdef __cplusplus
//////////////////////////////////////////////////////////////
// MmodControl function definition when compiling c++ files
//////////////////////////////////////////////////////////////
#if !M_MIL_USE_LINUX
inline void MmodControl(MIL_ID      ContextOrResultId, 
                        MIL_INT     Index,
                        MIL_INT64   ControlType, 
                        int         ControlValue)
   {
   MmodControlInt64(ContextOrResultId, Index, ControlType, ControlValue);
   };
#endif
inline void MmodControl(MIL_ID      ContextOrResultId, 
                        MIL_INT     Index,
                        MIL_INT64   ControlType, 
                        MIL_INT32   ControlValue)
   {
   MmodControlInt64(ContextOrResultId, Index, ControlType, ControlValue);
   }
inline void MmodControl(MIL_ID      ContextOrResultId, 
                        MIL_INT     Index,
                        MIL_INT64   ControlType, 
                        MIL_INT64   ControlValue)
   {
   MmodControlInt64(ContextOrResultId, Index, ControlType, ControlValue);
   }
inline void MmodControl(MIL_ID      ContextOrResultId, 
                        MIL_INT     Index,
                        MIL_INT64   ControlType, 
                        MIL_DOUBLE  ControlValue)
   {
   MmodControlDouble(ContextOrResultId, Index, ControlType, ControlValue);
   }
//////////////////////////////////////////////////////////////
// MmodDefine function definition when compiling c++ files
//////////////////////////////////////////////////////////////
#if !M_MIL_USE_LINUX
inline void MmodDefine(MIL_ID       ContextId,
                       MIL_INT64    ModelType, 
                       int          Param1,
                       MIL_DOUBLE   Param2,
                       MIL_DOUBLE   Param3,
                       MIL_DOUBLE   Param4,
                       MIL_DOUBLE   Param5)
   {
   MmodDefineInt64(ContextId, ModelType, Param1, Param2, Param3, Param4, Param5);
   }
#endif
inline void MmodDefine(MIL_ID       ContextId,
                       MIL_INT64    ModelType, 
                       MIL_INT32    Param1,
                       MIL_DOUBLE   Param2,
                       MIL_DOUBLE   Param3,
                       MIL_DOUBLE   Param4,
                       MIL_DOUBLE   Param5)
   {
   MmodDefineInt64(ContextId, ModelType, Param1, Param2, Param3, Param4, Param5);
   }
inline void MmodDefine(MIL_ID       ContextId,
                       MIL_INT64    ModelType, 
                       MIL_INT64    Param1,
                       MIL_DOUBLE   Param2,
                       MIL_DOUBLE   Param3,
                       MIL_DOUBLE   Param4,
                       MIL_DOUBLE   Param5)
   {
   MmodDefineInt64(ContextId, ModelType, Param1, Param2, Param3, Param4, Param5);
   }
inline void MmodDefine(MIL_ID       ContextId,
                       MIL_INT64    ModelType, 
                       MIL_DOUBLE   Param1,
                       MIL_DOUBLE   Param2,
                       MIL_DOUBLE   Param3,
                       MIL_DOUBLE   Param4,
                       MIL_DOUBLE   Param5)
   {
   MmodDefineDouble(ContextId, ModelType, Param1, Param2, Param3, Param4, Param5);
   }
#else
//////////////////////////////////////////////////////////////
// For C file, call the default function, i.e. Double one
//////////////////////////////////////////////////////////////
#define MmodControl  MmodControlDouble
#define MmodDefine   MmodDefineDouble

#endif // __cplusplus
#endif // M_MIL_USE_64BIT

#if M_MIL_USE_SAFE_TYPE

//////////////////////////////////////////////////////////////
// See milos.h for explanation about these functions.
//////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------
// MmodGetResult

inline void MFTYPE MmodGetResultUnsafe  (MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, void           *ResultArrayPtr);
inline void MFTYPE MmodGetResultSafeType(MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, int             ResultArrayPtr);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MmodGetResultSafeType(MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, std::nullptr_t                );
#endif
inline void MFTYPE MmodGetResultSafeType(MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, MIL_INT32      *ResultArrayPtr);
inline void MFTYPE MmodGetResultSafeType(MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, MIL_INT64      *ResultArrayPtr);
inline void MFTYPE MmodGetResultSafeType(MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, MIL_DOUBLE     *ResultArrayPtr);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                    
inline void MFTYPE MmodGetResultSafeType(MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, MIL_UINT32     *ResultArrayPtr);
inline void MFTYPE MmodGetResultSafeType(MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, MIL_UINT64     *ResultArrayPtr);
#endif

// ----------------------------------------------------------
// MmodInquire

inline MIL_INT MFTYPE MmodInquireUnsafe  (MIL_ID ContextOrResultId, MIL_INT Index, MIL_INT64  InquireType, void           *ResultArrayPtr);
inline MIL_INT MFTYPE MmodInquireSafeType(MIL_ID ContextOrResultId, MIL_INT Index, MIL_INT64  InquireType, int             ResultArrayPtr);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE MmodInquireSafeType(MIL_ID ContextOrResultId, MIL_INT Index, MIL_INT64  InquireType, std::nullptr_t                );
#endif
inline MIL_INT MFTYPE MmodInquireSafeType(MIL_ID ContextOrResultId, MIL_INT Index, MIL_INT64  InquireType, MIL_INT32      *ResultArrayPtr);
inline MIL_INT MFTYPE MmodInquireSafeType(MIL_ID ContextOrResultId, MIL_INT Index, MIL_INT64  InquireType, MIL_INT64      *ResultArrayPtr);
inline MIL_INT MFTYPE MmodInquireSafeType(MIL_ID ContextOrResultId, MIL_INT Index, MIL_INT64  InquireType, MIL_DOUBLE     *ResultArrayPtr);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                      
inline MIL_INT MFTYPE MmodInquireSafeType(MIL_ID ContextOrResultId, MIL_INT Index, MIL_INT64  InquireType, MIL_UINT32     *ResultArrayPtr);
inline MIL_INT MFTYPE MmodInquireSafeType(MIL_ID ContextOrResultId, MIL_INT Index, MIL_INT64  InquireType, MIL_UINT64     *ResultArrayPtr);
#endif

// ----------------------------------------------------------
// MmodGetResult

inline void MFTYPE MmodGetResultSafeType (MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, int ResultPtr)
   {
   if (ResultPtr)
      SafeTypeError(MIL_TEXT("MmodGetResult"));

   MmodGetResult(ResultId, Index, ResultType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MmodGetResultSafeType(MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, std::nullptr_t)
   {
   MmodGetResult(ResultId, Index, ResultType, NULL);
   }
#endif

inline void MmodGetResultSafeTypeExecute (MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, void        *ResultPtr, MIL_INT64  GivenType)
   {
   MIL_INT64  RequiredType = (ResultType & M_HLVLDATATYPE_MASK);
   if((RequiredType != M_TYPE_MIL_ID) && (RequiredType != M_TYPE_MIL_INT32) && (RequiredType != M_TYPE_MIL_INT64) && (RequiredType != M_TYPE_DOUBLE))
      RequiredType = 0;
   if (RequiredType == 0)
      RequiredType = M_TYPE_DOUBLE;
   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if (RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("MmodGetResult"));

   MmodGetResult(ResultId, Index, ResultType, ResultPtr);
   }

inline void   MFTYPE MmodGetResultUnsafe  (MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, void       *ResultPtr) {MmodGetResult(ResultId, Index, ResultType, ResultPtr);}
inline void   MFTYPE MmodGetResultSafeType(MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, MIL_INT32  *ResultPtr) {MmodGetResultSafeTypeExecute(ResultId, Index, ResultType, ResultPtr, M_TYPE_MIL_INT32);}
inline void   MFTYPE MmodGetResultSafeType(MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, MIL_INT64  *ResultPtr) {MmodGetResultSafeTypeExecute(ResultId, Index, ResultType, ResultPtr, M_TYPE_MIL_INT64);}
inline void   MFTYPE MmodGetResultSafeType(MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, MIL_DOUBLE *ResultPtr) {MmodGetResultSafeTypeExecute(ResultId, Index, ResultType, ResultPtr, M_TYPE_DOUBLE   );}
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                      
inline void   MFTYPE MmodGetResultSafeType(MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, MIL_UINT32 *ResultPtr) {MmodGetResultSafeTypeExecute(ResultId, Index, ResultType, ResultPtr, M_TYPE_MIL_INT32);}
inline void   MFTYPE MmodGetResultSafeType(MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, MIL_UINT64 *ResultPtr) {MmodGetResultSafeTypeExecute(ResultId, Index, ResultType, ResultPtr, M_TYPE_MIL_INT64);}
#endif

// ----------------------------------------------------------
// MmodInquire

inline MIL_INT MFTYPE MmodInquireSafeType(MIL_ID ContextOrResultId, MIL_INT Index, MIL_INT64  InquireType, int UserVarPtr)
   {
   if (UserVarPtr)
      SafeTypeError(MIL_TEXT("MmodInquire"));

   return MmodInquire(ContextOrResultId, Index, InquireType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE MmodInquireSafeType(MIL_ID ContextOrResultId, MIL_INT Index, MIL_INT64  InquireType, std::nullptr_t)
   {
   return MmodInquire(ContextOrResultId, Index, InquireType, NULL);
   }
#endif

inline MIL_INT MFTYPE MmodInquireSafeTypeExecute (MIL_ID ContextOrResultId, MIL_INT Index, MIL_INT64  InquireType, void *UserVarPtr, MIL_INT64  GivenType)
   {
   MIL_INT64  RequiredType = (InquireType & M_HLVLDATATYPE_MASK);
   if((RequiredType != M_TYPE_MIL_ID) && (RequiredType != M_TYPE_MIL_INT32) && (RequiredType != M_TYPE_MIL_INT64) && (RequiredType != M_TYPE_DOUBLE))
      RequiredType = 0;
   if (RequiredType == 0)
      RequiredType = M_TYPE_DOUBLE;
   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if (RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("MmodInquire"));

   return MmodInquire(ContextOrResultId, Index, InquireType, UserVarPtr);
   }

inline MIL_INT MFTYPE MmodInquireUnsafe  (MIL_ID ContextOrResultId, MIL_INT Index, MIL_INT64  InquireType, void       *UserVarPtr) {return MmodInquire               (ContextOrResultId, Index, InquireType, UserVarPtr                  );}
inline MIL_INT MFTYPE MmodInquireSafeType(MIL_ID ContextOrResultId, MIL_INT Index, MIL_INT64  InquireType, MIL_INT32  *UserVarPtr) {return MmodInquireSafeTypeExecute(ContextOrResultId, Index, InquireType, UserVarPtr, M_TYPE_MIL_INT32);}
inline MIL_INT MFTYPE MmodInquireSafeType(MIL_ID ContextOrResultId, MIL_INT Index, MIL_INT64  InquireType, MIL_INT64  *UserVarPtr) {return MmodInquireSafeTypeExecute(ContextOrResultId, Index, InquireType, UserVarPtr, M_TYPE_MIL_INT64);}
inline MIL_INT MFTYPE MmodInquireSafeType(MIL_ID ContextOrResultId, MIL_INT Index, MIL_INT64  InquireType, MIL_DOUBLE *UserVarPtr) {return MmodInquireSafeTypeExecute(ContextOrResultId, Index, InquireType, UserVarPtr, M_TYPE_DOUBLE   );}
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                      
inline MIL_INT MFTYPE MmodInquireSafeType(MIL_ID ContextOrResultId, MIL_INT Index, MIL_INT64  InquireType, MIL_UINT32 *UserVarPtr) {return MmodInquireSafeTypeExecute(ContextOrResultId, Index, InquireType, UserVarPtr, M_TYPE_MIL_INT32);}
inline MIL_INT MFTYPE MmodInquireSafeType(MIL_ID ContextOrResultId, MIL_INT Index, MIL_INT64  InquireType, MIL_UINT64 *UserVarPtr) {return MmodInquireSafeTypeExecute(ContextOrResultId, Index, InquireType, UserVarPtr, M_TYPE_MIL_INT64);}
#endif

#define MmodGetResult        MmodGetResultSafeType
#define MmodInquire          MmodInquireSafeType

#else // #if M_MIL_USE_SAFE_TYPE

#define MmodGetResultUnsafe        MmodGetResult
#define MmodInquireUnsafe          MmodInquire

#endif // #if M_MIL_USE_SAFE_TYPE

// ----------------------------------------------------------
// Overload for std::vector.
#if defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR
template <typename UserType>
inline MIL_INT MFTYPE MmodInquire(MIL_ID ContextId, MIL_INT Index, MIL_INT64  InquireType, std::vector<UserType> &ValuePtr)
   {
   // If the given MIL data type is not the same as the SrcType, change it to the correct one
   // and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(InquireType) != 0)
      {
      SafeTypeError(MIL_TEXT("MmodInquire"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   InquireType = M_STRIP_HLVLDATATYPE(InquireType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   MmodInquire(ContextId, Index, M_STRIP_HLVLDATATYPE(InquireType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   ValuePtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      return MmodInquire(ContextId, Index, InquireType, &ValuePtr[0]);
      }
   return 0;
   }
template <typename UserType>
inline void MFTYPE MmodGetResult(MIL_ID ResultId, MIL_INT Index, MIL_INT64  ResultType, std::vector<UserType> &ValuePtr)
   {
   //! If the given MIL data type is not the same as the SrcType, change it to the correct one
   //! and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(ResultType) != 0)
      {
      SafeTypeError(MIL_TEXT("MmodGetResult"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   ResultType = M_STRIP_HLVLDATATYPE(ResultType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   MmodGetResult(ResultId, Index, M_STRIP_HLVLDATATYPE(ResultType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   ValuePtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      MmodGetResult(ResultId, Index, ResultType, &ValuePtr[0]);
      }
   }

// ----------------------------------------------------------
// Overloads for std::vector in MxxxStream.
inline void MFTYPE MmodStream(std::vector<MIL_UINT8>  &MemPtrOrFileName,
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
                          MmodStream);
   }
#endif // defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR

#if M_MIL_USE_STRING
/***************************************************************************/
/* GMF MODULE                                                              */
/***************************************************************************/
#if M_MIL_USE_UNICODE
#if M_MIL_UNICODE_API
inline void MFTYPE MmodSaveW(const MIL_STRING& FileName, MIL_ID ContextId, MIL_INT64 ControlFlag)
   {
   return MmodSaveW(FileName.c_str(), ContextId, ControlFlag);
   }

inline MIL_ID MFTYPE MmodRestoreW(const MIL_STRING& FileName, MIL_ID SystemId, MIL_INT64 ControlFlag, MIL_ID* ContextIdPtr)
   {
   return MmodRestoreW(FileName.c_str(), SystemId, ControlFlag, ContextIdPtr);
   }

inline void MFTYPE MmodDefineFromFileW(MIL_ID ContextModId, MIL_INT64 FileType, const MIL_STRING& FileName, MIL_INT64 ControlFlag)
   {
   MmodDefineFromFileW(ContextModId, FileType, FileName.c_str(), ControlFlag);
   }

#else
inline void MFTYPE MmodSaveA(const MIL_STRING& FileName, MIL_ID ContextId, MIL_INT64 ControlFlag)
   {
   return MmodSaveA(FileName.c_str(), ContextId, ControlFlag);
   }

inline MIL_ID MFTYPE MmodRestoreA(const MIL_STRING& FileName, MIL_ID SystemId, MIL_INT64 ControlFlag, MIL_ID* ContextIdPtr)
   {
   return MmodRestoreA(FileName.c_str(), SystemId, ControlFlag, ContextIdPtr);
   }

inline void MFTYPE MmodDefineFromFileA(MIL_ID ContextModId, MIL_INT64 FileType, const MIL_STRING& FileName, MIL_INT64 ControlFlag)
   {
   MmodDefineFromFileA(ContextModId, FileType, FileName.c_str(), ControlFlag);
   }

#endif /* M_MIL_UNICODE_API */
#else
inline void MFTYPE MmodSave(const MIL_STRING& FileName, MIL_ID ContextId, MIL_INT64 ControlFlag)
   {
   return MmodSave(FileName.c_str(), ContextId, ControlFlag);
   }

inline MIL_ID MFTYPE MmodRestore(const MIL_STRING& FileName, MIL_ID SystemId, MIL_INT64 ControlFlag, MIL_ID* ContextIdPtr)
   {
   return MmodRestore(FileName.c_str(), SystemId, ControlFlag, ContextIdPtr);
   }

inline void MFTYPE MmodDefineFromFile(MIL_ID ContextModId, MIL_INT64 FileType, const MIL_STRING& FileName, MIL_INT64 ControlFlag)
   {
   MmodDefineFromFile(ContextModId, FileType, FileName.c_str(), ControlFlag);
   }

#endif /* M_MIL_USE_UNICODE */
#endif /* M_MIL_USE_STRING*/

////////////////////////////////////////////////////////////////////////////////
// MIL_UNIQUE_ID support

#if M_MIL_USE_MIL_UNIQUE_ID

#if M_MIL_USE_SAFE_TYPE
template <> inline bool MilIsCorrectObjectType<&MmodFree>(MIL_INT64 ObjectType)
   {
   return (ObjectType & ~M_USER_DEFINE_LOW_ATTRIBUTE) == M_MOD_OBJECT;
   }
#endif

typedef MIL_UNIQUE_ID<&MmodFree> MIL_UNIQUE_MOD_ID;

#if M_MIL_USE_MOVE_SEMANTICS

inline MIL_UNIQUE_MOD_ID MmodAlloc(MIL_ID SystemId, MIL_INT64 ModelFinderType, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_MOD_ID(MmodAlloc(SystemId, ModelFinderType, ControlFlag, M_NULL));
   }
inline MIL_UNIQUE_MOD_ID MmodAllocResult(MIL_ID SystemId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_MOD_ID(MmodAllocResult(SystemId, ControlFlag, M_NULL));
   }
inline MIL_UNIQUE_MOD_ID MmodRestore(MIL_CONST_TEXT_PTR FileName, MIL_ID SystemId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_MOD_ID(MmodRestore(FileName, SystemId, ControlFlag, M_NULL));
   }
#if M_MIL_USE_STRING
inline MIL_UNIQUE_MOD_ID MmodRestore(const MIL_STRING& FileName, MIL_ID SystemId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_MOD_ID(MmodRestore(FileName, SystemId, ControlFlag, M_NULL));
   }
#endif // M_MIL_USE_STRING
template <MilFreeFuncType FreeFunc> inline void MmodFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

inline void MmodStream(MilStreamParam     MemPtrOrFileName,
                       MIL_ID             SysId           ,
                       MIL_INT64          Operation       ,
                       MIL_INT64          StreamType      ,
                       MIL_DOUBLE         Version         ,
                       MIL_INT64          ControlFlag     ,
                       MIL_UNIQUE_MOD_ID* ContextModIdPtr ,
                       MIL_INT*           SizeByteVarPtr  )
   {
   MxxxStreamForMilUniqueId(MemPtrOrFileName, SysId, Operation, StreamType, Version, ControlFlag, ContextModIdPtr, SizeByteVarPtr, MmodStream);
   }


#endif // M_MIL_USE_MOVE_SEMANTICS
#endif // M_MIL_USE_MIL_UNIQUE_ID

// End of MIL_UNIQUE_ID support
////////////////////////////////////////////////////////////////////////////////

#endif // !M_MIL_LITE
#endif // __MILMOD_H__
