﻿/***************************************************************************/
/*

    Filename:  MILCAL.H
    Owner   :  Matrox Imaging
    Revision:  10.40.0881
    Content :  This file contains the defines and the prototypes for the
               MIL calibration module. (Mcal...).

    Copyright © Matrox Electronic Systems Ltd., 1992-2021.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef __MILCAL_H__
#define __MILCAL_H__

#if (!M_MIL_LITE) /* MIL FULL ONLY */

#if M_MIL_USE_RT
#ifdef M_CAL_EXPORTS
#define MIL_CAL_DLLFUNC __declspec(dllexport)
#else
#define MIL_CAL_DLLFUNC __declspec(dllimport)
#endif
#else
#define MIL_CAL_DLLFUNC
#endif
/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
{
#endif


/***************************************************************************/
/*                      Calibration CAPI defines                           */
/***************************************************************************/

/***************************************************************************/
/* McalAlloc()                                                             */
/***************************************************************************/

/* Calibration mode */
#define M_LINEAR_INTERPOLATION                 0x01L
#define M_PERSPECTIVE_TRANSFORMATION           0x02L
#define M_TSAI_BASED                           0x08L
#define M_3D_ROBOTICS                          0x10L
#define M_UNIFORM_TRANSFORMATION               1368L

#define M_FIXTURING_OFFSET                     1369L

#define M_DEFAULT_UNIFORM_CALIBRATION          (M_PSEUDO_ID+8) // Already defined in mil.h

/***************************************************************************/
/* McalGrid(), McalList()                                                  */
/***************************************************************************/

/* Grid Calibration mode */
#define M_DISPLACE_CAMERA_COORD               0x100L
#define M_FULL_CALIBRATION                    0x101L
#define M_DISPLACE_RELATIVE_COORD             0x102L
#define M_ACCUMULATE                          0x200L

/* Calibration grid type */
#define M_CIRCLE_GRID                         0x001L
#define M_CHESSBOARD_GRID                     0x002L

/* Possible values for RowNumber and ColumnNumber */
#define M_UNKNOWN                             -9999L /* Also defined in mil.h, ... */

/* Possible values for RowSpacing and ColumnSpacing */
#define M_FROM_FIDUCIAL                          -2L

/* Optional ModeFlag that can be added to the grid type */
#define M_Y_AXIS_COUNTER_CLOCKWISE            0x010L
#define M_Y_AXIS_CLOCKWISE                    0x020L

#define M_FAST                           0x00002000L /* Also defined in milpat.h */

/***************************************************************************/
/* McalTransformCoordinate() and McalTransformResult()                       */
/***************************************************************************/

/* Transform type */
#define M_PIXEL_TO_WORLD                          1L
#define M_WORLD_TO_PIXEL                          2L

#define M_PACKED                         0x00020000L /* Also defined in mil.h */

/* Data type */
#define M_LENGTH_X                              0x3L
#define M_LENGTH_Y                              0x4L
#define M_LENGTH                         0x00002000L  /* (Already defined in milmeas.h) */
#define M_AREA                                    2L  /* (Already defined in milblob.h) */
#define M_ANGLE						        0x00000800L  /* (Already defined in milmeas.h) */

/* Error in McalTransformCoordinate() and McalTransformCoordinate() */
#define M_INVALID_POINT                  1.7976931348623158e+308  /* Already defined in mil.h */
#define M_NO_POINTS_BEHIND_CAMERA        0x00040000L              /* Already defined in mil.h */

/***************************************************************************/
/* McalTransformCoordinate3dList()                                         */
/***************************************************************************/

/* Optional ModeFlag */
#define M_UNIT_DIRECTION_VECTOR                 2L
#define M_NO_POINTS_BEHIND_CAMERA      0x00040000L              /* Already defined in mil.h */
#define M_DEPTH_MAP                    0x00800000L
#define M_NO_EXTRAPOLATED_POINTS       0x01000000L

/***************************************************************************/
/* McalControl() and/or McalInquire()                                      */
/***************************************************************************/

/* Control parameters. */

#define M_FOREGROUND_VALUE	                     4L
#define M_PRINCIPAL_POINT_X                     103L
#define M_PRINCIPAL_POINT_Y                     104L
#define M_GRID_ORIGIN_X                         109L
#define M_GRID_ORIGIN_Y                         110L
#define M_GRID_ORIGIN_Z                         111L
#define M_RELATIVE_ORIGIN_X                     112L  /* (also defined in mil.h) */
#define M_RELATIVE_ORIGIN_Y                     113L  /* (also defined in mil.h) */
#define M_RELATIVE_ORIGIN_Z                     114L  /* (also defined in mil.h) */
#define M_RELATIVE_ORIGIN_ANGLE                 115L  /* (also defined in mil.h) */
#define M_ROW_NUMBER                            116L
#define M_COLUMN_NUMBER                         117L
#define M_ROW_SPACING                           118L
#define M_COLUMN_SPACING                        119L

#define M_INPUT_UNITS                           121L  /* (Already defined in mil.h, milmeas.h) */
#define M_ASSOCIATED_CALIBRATION                125L
#define M_CORRECTION_STATE                      126L
#define M_TRANSFORM_CACHE                       132L
#define M_PIXEL_SIZE_X                          139L
#define M_PIXEL_SIZE_Y                          140L
#define M_CALIBRATION_CHILD_OFFSET_X            141L
#define M_CALIBRATION_CHILD_OFFSET_Y            142L

#define M_CCD_ASPECT_RATIO                      148L
#define M_DISTORTION_RADIAL_1                   150L
#define M_LINK_TOOL_AND_CAMERA                  155L
#define M_TOOL_POSITION_X                       156L
#define M_TOOL_POSITION_Y                       157L
#define M_TOOL_POSITION_Z                       158L
#define M_CALIBRATION_STATUS                    159L
#define M_CALIBRATION_PLANE                     160L
#define M_GRID_HINT_PIXEL_X                     162L
#define M_GRID_HINT_PIXEL_Y                     163L

#define M_NUMBER_OF_CALIBRATION_POSES           199L
#define M_NUMBER_OF_CALIBRATION_POINTS          200L
#define M_CALIBRATION_IMAGE_POINTS_X            201L
#define M_CALIBRATION_IMAGE_POINTS_Y            202L
#define M_CALIBRATION_WORLD_POINTS_X            203L
#define M_CALIBRATION_WORLD_POINTS_Y            204L
#define M_CALIBRATION_MODE                      205L
#define M_GRID_TYPE                             206L
#define M_WORLD_POS_X                           207L
#define M_WORLD_POS_Y                           208L
#define M_CALIBRATION_WORLD_POINTS_Z            213L
#define M_CALIBRATION_CATEGORY                  214L /* also defined in mil.h */

#define M_FOCAL_LENGTH                         1009L /* already defined in milreg.h */

#define M_GRAY_LEVEL_SIZE_Z                    1370L
#define M_WORLD_POS_Z                          1371L
#define M_PIXEL_ROTATION                       1373L
#define M_CONSTANT_PIXEL_SIZE                  1376L

#define M_LOCALIZATION_NB_ITERATIONS_MAX       1667L
#define M_LOCALIZATION_NB_OUTLIERS_MAX         1669L

#define M_CALIBRATION_INPUT_DATA               1851L

#define M_GRID_PARTIAL                         2185L
#define M_GRID_FIDUCIAL                        2186L
#define M_GRID_HINT_ANGLE_X                    2187L
#define M_GRID_SHAPE                           2188L

#define M_Y_AXIS_DIRECTION                     2389L

#define M_GRID_UNITS                           2394L
#define M_GRID_UNIT_SHORT_NAME                 (2395L|M_CLIENT_ENCODING)

#define M_ASPECT_RATIO                         6001L /* already defined in mil.h */

#define M_AVERAGE_PIXEL_ERROR                0x1000L
#define M_GLOBAL_AVERAGE_PIXEL_ERROR         0x1001L
#define M_MAXIMUM_PIXEL_ERROR                0x2000L
#define M_GLOBAL_MAXIMUM_PIXEL_ERROR         0x2002L
#define M_AVERAGE_WORLD_ERROR                0x4000L
#define M_GLOBAL_AVERAGE_WORLD_ERROR         0x4004L
#define M_MAXIMUM_WORLD_ERROR                0x8000L
#define M_GLOBAL_MAXIMUM_WORLD_ERROR         0x8008L

#define M_DEPTH_MAP                      0x00800000L

/* Control values. */
#define M_PIXEL                              0x1000L
#define M_WORLD                              0x2000L
#define M_ENABLE                              -9997L /* (Already defined in mil.h) */
#define M_DISABLE                             -9999L /* (Already defined in mil.h) */

/* M_CALIBRATION_SUCCESSFUL control values */
#define M_FALSE                                   0L /* already defined in mil.h */
#define M_TRUE                                    1L /* already defined in mil.h */

/* M_CALIBRATION_STATUS control values */
#define M_CALIBRATED                      0x0000300L /* already defined in milmod.h */
#define M_NOT_INITIALIZED                         3L
#define M_GRID_NOT_FOUND                          4L
#define M_PLANE_ANGLE_TOO_SMALL                   5L
#define M_CALIBRATING                             6L
#define M_INVALID_CALIBRATION_POINTS              7L
#define M_MATHEMATICAL_EXCEPTION                  8L
#define M_TOO_MANY_OUTLIERS                      10L

/* M_CALIBRATION_CATEGORY control values */
#define M_2D_CALIBRATION                          1L  /* also defined in mil.h */
#define M_3D_CALIBRATION                          2L  /* also defined in mil.h */

/* M_GRID_HINT_PIXEL_X and M_GRID_HINT_PIXEL_Y control values */
#define M_NONE                           0x08000000L /* already defined in milstr.h, milcolor.h */

/* M_ASPECT_RATIO, M_PIXEL_SIZE_X and M_PIXEL_SIZE_Y can return this if invalid */
#define M_INVALID_SCALE                      -999999.0

/* M_CALIBRATION_INPUT_DATA control values*/
#define M_PARAMETRIC                         0x0021L  /* already defined in milmetrol.h, mil3dmap.h */
#define M_GRID                                 1852L
#define M_LIST                           0x08000000L  /* already defined in mil.h */

/* M_GRID_FIDUCIAL control values*/
#define M_NONE                           0x08000000L  /* already defined in mil.h, ... */
#define M_DATAMATRIX                     0x00000002   /* already defined in milcode.h, ... */

/* M_GRID_SHAPE control values*/
#define M_RECTANGLE                      0x00000040L  /* already defined in milmod.h, ... */
#define M_ANY                            0x11000000L  /* already defined in mil.h, ... */

/* M_GRID_UNITS control values*/
#define M_MICROMETERS                          2449L
#define M_MILLIMETERS                          2450L
#define M_CENTIMETERS                          2451L
#define M_METERS                               2452L
#define M_KILOMETERS                           2453L
#define M_MILS                                    1L
#define M_INCHES                               2454L
#define M_FEET                                 2455L
#define M_MILES                                2456L
#define M_UNKNOWN                             -9999L  /* Also defined in mil.h, ... */


/* Maximum string sizes*/
#define M_GRID_UNIT_SHORT_NAME_MAX_SIZE          16

/***************************************************************************/
/* McalRestore(), McalSave(), McalStream()                                 */
/***************************************************************************/
#define M_INTERACTIVE                         M_NULL /* Already defined in mil.h, milcode.h, miledge.h, milmeas.h, milocr.h, milpat.h, milmod.h */

/***************************************************************************/
/* McalTransformImage()                                                    */
/***************************************************************************/
// Operation Type //
#define M_FULL_CORRECTION                      0x001L
#define M_CORRECT_LENS_DISTORTION_ONLY         0x002L

// Control Flag //
#define M_WARP_IMAGE                           0x001L
#define M_EXTRACT_LUT_X                        0x002L
#define M_EXTRACT_LUT_Y                        0x004L

// Combination flags
#define M_CLIP                               0x0010L
#define M_FIT                                0x0020L
#define M_USE_DESTINATION_CALIBRATION        0x0040L

/***************************************************************************/
/* McalGetCoordinateSystem(), McalSetCoordinateSystem()                    */
/***************************************************************************/

#define M_ABSOLUTE_COORDINATE_SYSTEM     0x01000000L
#define M_PIXEL_COORDINATE_SYSTEM        0x02000000L
#define M_LASER_LINE_COORDINATE_SYSTEM   0x03000000L
#define M_RELATIVE_COORDINATE_SYSTEM              0L
#define M_TOOL_COORDINATE_SYSTEM                  1L
#define M_CAMERA_COORDINATE_SYSTEM                2L
#define M_ROBOT_BASE_COORDINATE_SYSTEM            3L

#define M_HOMOGENEOUS_MATRIX                      0L  /* (also defined in mil.h) */
#define M_TRANSLATION                             1L
#define M_ROTATION_AXIS_ANGLE                     2L
#define M_ROTATION_QUATERNION                     3L
#define M_ROTATION_YXZ                            4L
#define M_ROTATION_MATRIX                         5L
#define M_IDENTITY                                6L
#define M_ROTATION_X                              7L
#define M_ROTATION_Y                              8L
#define M_ROTATION_Z                              9L
#define M_ROTATION_XYZ                           10L
#define M_ROTATION_XZY                           11L
#define M_ROTATION_YZX                           12L
#define M_ROTATION_ZXY                           13L
#define M_ROTATION_ZYX                           14L
#define M_ROTATION_AXIS_X                        17L
#define M_ROTATION_AXIS_Y                        18L
#define M_ROTATION_AXIS_Z                        19L     
#define M_FIXTURE_TO_PLANE                       20L

#define M_TRANSFORM_TYPES_SHIFT                   8L // =utilities=  (also defined in mil.h)

/* Combination flags for McalSetCoordinateSystem(), must be > M_TRANSFORM_TYPES_MASK */
#define M_ASSIGN                                (1 << M_TRANSFORM_TYPES_SHIFT)      /* (also defined in mil.h) */
#define M_COMPOSE_WITH_CURRENT                  (2 << M_TRANSFORM_TYPES_SHIFT)      /* (also defined in mil.h) */

/***************************************************************************/
/* McalDraw()                                                              */
/***************************************************************************/

#define M_DRAW_IMAGE_POINTS                        1L
#define M_DRAW_WORLD_POINTS                        2L
#define M_DRAW_VALID_REGION                        3L
#define M_DRAW_VALID_REGION_FILLED                 4L
#define M_DRAW_ABSOLUTE_COORDINATE_SYSTEM       1445L
#define M_DRAW_RELATIVE_COORDINATE_SYSTEM       1446L
#define M_DRAW_PIXEL_COORDINATE_SYSTEM          1494L
#define M_DRAW_FIXTURING_OFFSET                 1498L
#define M_DRAW_FIDUCIAL_BOX                     2545L

/* Combination flags for M_DRAW_[]_COORDINATE_SYSTEM */
#define M_DRAW_CS_SHIFT                           16L // =utilities=

#define M_DRAW_AXES                             (1 << M_DRAW_CS_SHIFT)
#define M_DRAW_FRAME                            (2 << M_DRAW_CS_SHIFT)
#define M_DRAW_MAJOR_MARKS                      (3 << M_DRAW_CS_SHIFT)
#define M_DRAW_MINOR_MARKS                      (4 << M_DRAW_CS_SHIFT)
#define M_DRAW_LEGEND                           (5 << M_DRAW_CS_SHIFT)
#define M_DRAW_ALL                              (6 << M_DRAW_CS_SHIFT)

#define M_ALWAYS_SHOW_AXES                0x00800000L

/***************************************************************************/
/* McalFixture()                                                           */
/***************************************************************************/

#define M_MOVE_RELATIVE                            0x00010000L
#define M_LEARN_OFFSET                             0x00020000L

#define M_TRANSLATION                              1L // also in milreg.h
#define M_TRANSLATION_ROTATION                     2L // also in milreg.h
#define M_TRANSLATION_ROTATION_SCALE               3L // also in milreg.h

#define M_RESULT_MOD                     0x00000010L
#define M_RESULT_PAT                     0x00000020L
#define M_MODEL_MOD                      0x00000030L
#define M_MODEL_PAT                      0x00000040L
#define M_POINT_AND_ANGLE                0x00000050L
#define M_POINT_AND_DIRECTION_POINT      0x00000060L
#define M_SAME_AS_SOURCE                 0x00000070L
#define M_RESULT_MET                     0x00000080L
#define M_RESULT_POINT_CLOUD_3DMAP       0x00000090L
#define M_LASER_3DMAP                    0x000000A0L

#define M_PIXEL_COORDINATE_SYSTEM        0x02000000L
#define M_ABSOLUTE_COORDINATE_SYSTEM     0x01000000L    /* (also defined in mil.h) */
#define M_RELATIVE_COORDINATE_SYSTEM              0L    /* (also defined in mil.h) */
#define M_PIXEL                                     0x1000L
#define M_WORLD                                     0x2000L

/***************************************************************************/
/* McalWarp()                                                              */
/***************************************************************************/

// Values for TransformationType
#define M_IDENTITY                                6L
#define M_WARP_POLYNOMIAL                0x00200000L // also defined in mil.h, milim.h, milreg.h
#define M_WARP_LUT                       0x00400000L // also defined in mil.h, milim.h

// Combination flags for M_WARP_LUT
#define M_FIXED_POINT                    0x00004000L // also defined in mil.h, milim.h

/***************************************************************************/
/* McalDraw3d()                                                              */
/***************************************************************************/
#define M_ROOT_NODE                                 0
#define M_DRAW_3D_CONTEXT                        3815
#define M_DRAW_CAMERA_COORDINATE_SYSTEM          3816
#define M_DRAW_ROBOT_BASE_COORDINATE_SYSTEM      3817
#define M_DRAW_TOOL_COORDINATE_SYSTEM            3818
#define M_DRAW_FRUSTUM                           3819
//#define M_DRAW_ABSOLUTE_COORDINATE_SYSTEM       1445L //Defined above
//#define M_DRAW_RELATIVE_COORDINATE_SYSTEM       1446L
#define M_DRAW_RELATIVE_XY_PLANE                       3844
#define M_DRAW_RELATIVE_XY_PLANE_COLOR_FILL            3836
#define M_DRAW_RELATIVE_XY_PLANE_OPACITY               3837
#define M_DRAW_FRUSTUM_COLOR                        3838
#define M_DRAW_COORDINATE_SYSTEM_LENGTH             3846  
#define M_DRAW_CAMERA_COORDINATE_SYSTEM_NAME        (3865| M_CLIENT_ENCODING)
#define M_DRAW_RELATIVE_COORDINATE_SYSTEM_NAME      (3866| M_CLIENT_ENCODING)
#define M_DRAW_RELATIVE_XY_PLANE_COLOR_OUTLINE      3903
#define M_TEXTURE_IMAGE                             2700L
#define M_AUTO_COLOR                                0x00100000L//already defined in mil3d
#define M_NO_COLOR                                  3908     
/***************************************************************************/
/* Deprecated                                                              */
/***************************************************************************/

#if MIL_COMPILE_VERSION < MIL_COMPILE_TRUNK_VERSION
   // Deprecated values.
   #if OldDefinesSupport
      #define M_CAMERA_POSITION_X                     100L // deprecated: use M_TOOL_POSITION_X
      MIL_DEPRECATED(M_CAMERA_POSITION_X, 1010)
      #define M_CAMERA_POSITION_Y                     101L // deprecated: use M_TOOL_POSITION_Y
      MIL_DEPRECATED(M_CAMERA_POSITION_Y, 1010)
      #define M_CAMERA_POSITION_Z                     102L // deprecated: use M_TOOL_POSITION_Z
      MIL_DEPRECATED(M_CAMERA_POSITION_Z, 1010)
   #endif
#endif

#if OldDefinesSupport
   // Deprecated names.
   #define M_LOCATE_CAMERA_ONLY                    M_DISPLACE_CAMERA_COORD
   MIL_DEPRECATED(M_LOCATE_CAMERA_ONLY, 1010)
   #define M_LOCATE_RELATIVE_ONLY                  M_DISPLACE_RELATIVE_COORD
   MIL_DEPRECATED(M_LOCATE_RELATIVE_ONLY, 1010)
   #define M_INPUT_COORDINATE_SYSTEM               M_INPUT_UNITS
   MIL_DEPRECATED(M_INPUT_COORDINATE_SYSTEM, 1010)
   #define M_OUTPUT_COORDINATE_SYSTEM              M_OUTPUT_UNITS
   // MIL_DEPRECATED(M_OUTPUT_COORDINATE_SYSTEM) already deprecated in mil.h
   #define M_TRANSFORM_FILL_MODE                   M_TRANSFORM_IMAGE_FILL_MODE
   MIL_DEPRECATED(M_TRANSFORM_FILL_MODE, 1010)
   #define M_CORRECTED_PIXEL_SIZE_X                M_PIXEL_SIZE_X
   MIL_DEPRECATED(M_CORRECTED_PIXEL_SIZE_X, 1010)
   #define M_CORRECTED_PIXEL_SIZE_Y                M_PIXEL_SIZE_Y
   MIL_DEPRECATED(M_CORRECTED_PIXEL_SIZE_Y, 1010)
   #define M_CORRECTED_GRAY_LEVEL_SIZE_Z           M_GRAY_LEVEL_SIZE_Z
   MIL_DEPRECATED(M_CORRECTED_GRAY_LEVEL_SIZE_Z, 1010)
   #define M_CORRECTED_WORLD_POS_X                 M_WORLD_POS_X
   MIL_DEPRECATED(M_CORRECTED_WORLD_POS_X, 1010)
   #define M_CORRECTED_WORLD_POS_Y                 M_WORLD_POS_Y
   MIL_DEPRECATED(M_CORRECTED_WORLD_POS_Y, 1010)
   #define M_CORRECTED_WORLD_POS_Z                 M_WORLD_POS_Z
   MIL_DEPRECATED(M_CORRECTED_WORLD_POS_Z, 1010)
   #define M_CORRECTED_PIXEL_ROTATION              M_PIXEL_ROTATION
   MIL_DEPRECATED(M_CORRECTED_PIXEL_ROTATION, 1010)
   #define M_CORRECTED_OFFSET_X                    M_CALIBRATION_CHILD_OFFSET_X
   MIL_DEPRECATED(M_CORRECTED_OFFSET_X, 1010)
   #define M_CORRECTED_OFFSET_Y                    M_CALIBRATION_CHILD_OFFSET_Y
   MIL_DEPRECATED(M_CORRECTED_OFFSET_Y, 1010)
   #define M_IMAGE_COORDINATE_SYSTEM               M_PIXEL_COORDINATE_SYSTEM
   MIL_DEPRECATED(M_IMAGE_COORDINATE_SYSTEM, 1010)
   #define M_ALLOW_INVALID_POINT_OUTPUT            M_NO_POINTS_BEHIND_CAMERA
   MIL_DEPRECATED(M_ALLOW_INVALID_POINT_OUTPUT, 1010)
   #define M_GRID_CORNER_HINT_X                    M_GRID_HINT_PIXEL_X
   MIL_DEPRECATED(M_GRID_CORNER_HINT_X, 1020)
   #define M_GRID_CORNER_HINT_Y                    M_GRID_HINT_PIXEL_Y
   MIL_DEPRECATED(M_GRID_CORNER_HINT_Y, 1020)
   #define M_Y_AXIS_UP                             M_Y_AXIS_COUNTER_CLOCKWISE  // deprecated; for the ControlType, use M_Y_AXIS_DIRECTION
   MIL_DEPRECATED(M_Y_AXIS_UP, 1020)
   #define M_Y_AXIS_DOWN                           M_Y_AXIS_CLOCKWISE
   MIL_DEPRECATED(M_Y_AXIS_DOWN, 1020)
   #define M_POINT_CLOUD_CONTAINER_3DMAP           M_RESULT_POINT_CLOUD_3DMAP
   MIL_DEPRECATED(M_POINT_CLOUD_CONTAINER_3DMAP, 1040)

   // Deprecated values.
   #define M_USER_DEFINED                          21L  // deprecated: use M_USE_DESTINATION_CALIBRATION
   #define M_PLANE_INTERSECTION                    1L   // deprecated: use M_DEFAULT
   MIL_DEPRECATED(M_PLANE_INTERSECTION, 1020)
   #define M_OUTPUT_UNITS                          122L // deprecated: use M_RESULT_OUTPUT_UNITS
   #define M_AUTO_ASPECT_RATIO                     123L
   MIL_DEPRECATED(M_AUTO_ASPECT_RATIO, 1020)
   #define M_ASPECT_RATIO_AUTO_SETTING             123L // deprecated name
   MIL_DEPRECATED(M_ASPECT_RATIO_AUTO_SETTING, 1010)
   #define M_CALIBRATION_SUCCESSFUL                130L // deprecated: use M_CALIBRATION_STATUS
   MIL_DEPRECATED(M_CALIBRATION_SUCCESSFUL, 1020)
   #define M_RESULT_ALIGNMENT_3DMAP         0x000000B0L // deprecated: use M3dregCopyResult or M3dregMerge
   MIL_DEPRECATED(M_RESULT_ALIGNMENT_3DMAP, 1040)
#endif

// Deprecated values.
#if OldDefinesSupport
   #define M_TRANSFORM_IMAGE_FILL_MODE             131L // deprecated: use M_USE_DESTINATION_CALIBRATION
   MIL_DEPRECATED(M_TRANSFORM_IMAGE_FILL_MODE, 1010)
   #define M_TRANSFORM_IMAGE_WORLD_POS_X           209L // deprecated: use M_USE_DESTINATION_CALIBRATION
   MIL_DEPRECATED(M_TRANSFORM_IMAGE_WORLD_POS_X, 1010)
   #define M_TRANSFORM_IMAGE_WORLD_POS_Y           210L // deprecated: use M_USE_DESTINATION_CALIBRATION
   MIL_DEPRECATED(M_TRANSFORM_IMAGE_WORLD_POS_Y, 1010)
   #define M_TRANSFORM_IMAGE_PIXEL_SIZE_X          211L // deprecated: use M_USE_DESTINATION_CALIBRATION
   MIL_DEPRECATED(M_TRANSFORM_IMAGE_PIXEL_SIZE_X, 1010)
   #define M_TRANSFORM_IMAGE_PIXEL_SIZE_Y          212L // deprecated: use M_USE_DESTINATION_CALIBRATION
   MIL_DEPRECATED(M_TRANSFORM_IMAGE_PIXEL_SIZE_Y, 1010)
#endif


/***************************************************************************/
/*                 Calibration CAPI function prototype                     */
/***************************************************************************/

MIL_CAL_DLLFUNC MIL_ID MFTYPE McalAlloc(MIL_ID      SysId,
                        MIL_INT64   Mode,
                        MIL_INT64   ModeFlag,
                        MIL_ID*     CalibrationIdPtr);

MIL_CAL_DLLFUNC void MFTYPE McalFree(MIL_ID CalibrationId);

MIL_CAL_DLLFUNC void MFTYPE McalAssociate(MIL_ID     SrcCalibrationOrMilId,
                          MIL_ID     TargetImageOrDigitizerId,
                          MIL_INT64  ControlFlag);

MIL_CAL_DLLFUNC void MFTYPE McalDraw(MIL_ID     ContextGraId,
                                     MIL_ID     ContextCalOrImageBufId,
                                     MIL_ID     DstImageBufOrListGraId,
                                     MIL_INT64  Operation,
                                     MIL_INT    Index,
                                     MIL_INT64  ControlFlag);

MIL_CAL_DLLFUNC void MFTYPE McalGrid(MIL_ID      CalibrationId,
                     MIL_ID      SrcImageBufId,
                     MIL_DOUBLE  GridOffsetX,
                     MIL_DOUBLE  GridOffsetY,
                     MIL_DOUBLE  GridOffsetZ,
                     MIL_INT     RowNumber,
                     MIL_INT     ColumnNumber,
                     MIL_DOUBLE  RowSpacing,
                     MIL_DOUBLE  ColumnSpacing,
                     MIL_INT64   Operation,
                     MIL_INT64   GridType);

MIL_CAL_DLLFUNC void MFTYPE McalList(MIL_ID            CalibrationId,
                     const MIL_DOUBLE* PixCoordXArrayPtr,
                     const MIL_DOUBLE* PixCoordYArrayPtr,
                     const MIL_DOUBLE* WorldCoordXArrayPtr,
                     const MIL_DOUBLE* WorldCoordYArrayPtr,
                     const MIL_DOUBLE* WorldCoordZArrayPtr,
                     MIL_INT           NumPoint,
                     MIL_INT64         Operation,
                     MIL_INT64         ControlFlag);

MIL_CAL_DLLFUNC void MFTYPE McalUniform(MIL_ID     CalibrationOrImageId,
                        MIL_DOUBLE WorldPosX,
                        MIL_DOUBLE WorldPosY,
                        MIL_DOUBLE PixelSizeX,
                        MIL_DOUBLE PixelSizeY,
                        MIL_DOUBLE PixelRotation,
                        MIL_INT64  ControlFlag);

MIL_CAL_DLLFUNC void MFTYPE McalRelativeOrigin(MIL_ID     CalibrationOrImageId,
                               MIL_DOUBLE XOffset,
                               MIL_DOUBLE YOffset,
                               MIL_DOUBLE ZOffset,
                               MIL_DOUBLE AngularOffset,
                               MIL_INT64  ControlFlag);

MIL_CAL_DLLFUNC void MFTYPE McalTransformCoordinate(MIL_ID      CalibrationOrImageId,
                                    MIL_INT64   TransformType,
                                    MIL_DOUBLE  X,
                                    MIL_DOUBLE  Y,
                                    MIL_DOUBLE* ResXPtr,
                                    MIL_DOUBLE* ResYPtr);

MIL_CAL_DLLFUNC void MFTYPE McalTransformCoordinateList(MIL_ID            CalibrationOrImageId,
                                        MIL_INT64         TransformType,
                                        MIL_INT           NumPoints,
                                        const MIL_DOUBLE* SrcCoordXArrayPtr,
                                        const MIL_DOUBLE* SrcCoordYArrayPtr,
                                        MIL_DOUBLE*       DstCoordXArrayPtr,
                                        MIL_DOUBLE*       DstCoordYArrayPtr);

MIL_CAL_DLLFUNC void MFTYPE McalTransformCoordinate3dList(MIL_ID            CalibrationOrImageId,
                                          MIL_INT64         SrcCoordinateSystem,
                                          MIL_INT64         DstCoordinateSystem,
                                          MIL_INT           NumPoints,
                                          const MIL_DOUBLE* SrcCoordXArrayPtr,
                                          const MIL_DOUBLE* SrcCoordYArrayPtr,
                                          const MIL_DOUBLE* SrcCoordZArrayPtr,
                                          MIL_DOUBLE*       DstCoordXArrayPtr,
                                          MIL_DOUBLE*       DstCoordYArrayPtr,
                                          MIL_DOUBLE*       DstCoordZArrayPtr,
                                          MIL_INT64         ModeFlag);

MIL_CAL_DLLFUNC void MFTYPE McalTransformResult(MIL_ID       CalibrationOrImageId,
                                MIL_INT64    TransformType,
                                MIL_INT64    ResultType,
                                MIL_DOUBLE   Result,
                                MIL_DOUBLE*  TransformedResultPtr);

MIL_CAL_DLLFUNC void MFTYPE McalTransformResultInRegion(MIL_ID     CalibrationOrImageId,
                                        MIL_INT64  TransformType,
                                        MIL_INT64  DataType,
                                        MIL_INT    lBoxMinX,
                                        MIL_INT    lBoxMinY,
                                        MIL_INT    lBoxMaxX,
                                        MIL_INT    lBoxMaxY,
                                        double     Data,
                                        double*    ResData);

MIL_CAL_DLLFUNC void MFTYPE McalTransformResultAtPosition(MIL_ID      CalibrationOrImageId,
                                          MIL_INT64   TransformType,
                                          MIL_INT64   ResultType,
                                          MIL_DOUBLE  PositionX,
                                          MIL_DOUBLE  PositionY,
                                          MIL_DOUBLE  Result,
                                          MIL_DOUBLE* ConvertedResultPtr);

MIL_CAL_DLLFUNC void MFTYPE McalTransformImage(MIL_ID     SrcImageBufId,
                                               MIL_ID     DstImageOrLutId,
                                               MIL_ID     CalibrationId,
                                               MIL_INT64  InterpolationMode,
                                               MIL_INT64  OperationType,
                                               MIL_INT64  ControlFlag);

MIL_CAL_DLLFUNC void MFTYPE McalWarp(MIL_ID     SrcImageOrContextCalId,
                                     MIL_ID     DstImageOrContextCalId,
                                     MIL_ID     WarpParam1Id,
                                     MIL_ID     WarpParam2Id,
                                     MIL_DOUBLE OffsetX,
                                     MIL_DOUBLE OffsetY,
                                     MIL_DOUBLE SizeX,
                                     MIL_DOUBLE SizeY,
                                     MIL_INT    RowNumber,
                                     MIL_INT    ColumnNumber,
                                     MIL_INT64  TransformationType,
                                     MIL_INT64  ControlFlag);

MIL_CAL_DLLFUNC MIL_INT64 MFTYPE McalDraw3d(MIL_ID    OperationDraw3dContextCalId,
                                            MIL_ID    ContextCalOrImageBufId,
                                            MIL_INT64 SrcIndex,
                                            MIL_ID    DstList3dgraId,
                                            MIL_INT64 DstParentLabel,
                                            MIL_ID    RelXYPlaneTextureImageBufId,
                                            MIL_INT64 ControlFlag);


// Prototypes for 32/64 bits OSs
MIL_CAL_DLLFUNC void MFTYPE McalControlInt64(MIL_ID      ContextCalOrCalibratedMilObjectId,
                                             MIL_INT64   ControlType,
                                             MIL_INT64   ControlValue);

MIL_CAL_DLLFUNC void MFTYPE McalControlDouble(MIL_ID     ContextCalOrCalibratedMilObjectId,
                                              MIL_INT64  ControlType,
                                              MIL_DOUBLE ControlValue);

MIL_CAL_DLLFUNC MIL_INT MFTYPE McalInquire(MIL_ID      ContextCalOrCalibratedMilObjectId,
                                           MIL_INT64   InquireType,
                                           void*       UserVarPtr);

MIL_CAL_DLLFUNC MIL_INT MFTYPE McalInquireSingle(MIL_ID     ContextCalOrCalibratedMilObjectId,
                                                 MIL_INT    Index,
                                                 MIL_INT64  InquireType,
                                                 void*      UserVarPtr);

MIL_CAL_DLLFUNC void MFTYPE McalGetCoordinateSystem(MIL_ID         CalibratedMilObjectId,
                                    MIL_INT64      TargetCoordinateSystem,
                                    MIL_INT64      ReferenceCoordinateSystem,
                                    MIL_INT64      InquireType,
                                    MIL_ID         ArrayBufOrMatrix3dgeoId,
                                    MIL_DOUBLE*    Param1Ptr,
                                    MIL_DOUBLE*    Param2Ptr,
                                    MIL_DOUBLE*    Param3Ptr,
                                    MIL_DOUBLE*    Param4Ptr);

MIL_CAL_DLLFUNC void MFTYPE McalSetCoordinateSystem(MIL_ID     CalibratedMilObjectId,
                                    MIL_INT64  TargetCoordinateSystem,
                                    MIL_INT64  ReferenceCoordinateSystem,
                                    MIL_INT64  TransformType,
                                    MIL_ID     ArrayBufOrMatrix3dgeoId,
                                    MIL_DOUBLE Param1,
                                    MIL_DOUBLE Param2,
                                    MIL_DOUBLE Param3,
                                    MIL_DOUBLE Param4);

#if M_MIL_USE_64BIT
   #define McalFixture(CalibrationOrImageId, FixturingOffsetId, Operation, LocationType, CalOrLocationSrcId, Param1, Param2, Param3, Param4) McalFixtureDouble(CalibrationOrImageId, FixturingOffsetId, Operation, LocationType, CalOrLocationSrcId, (MIL_DOUBLE)(Param1), (MIL_DOUBLE)(Param2), (MIL_DOUBLE)(Param3), (MIL_DOUBLE)(Param4))
#else
   #define McalFixtureDouble McalFixture
#endif
MIL_CAL_DLLFUNC void MFTYPE McalFixtureDouble(MIL_ID     DstCalibratedMilObjectId,
                              MIL_ID     FixturingOffsetCalId,
                              MIL_INT64  Operation,
                              MIL_INT64  LocationType,
                              MIL_ID     CalOrLocSourceId,
                              MIL_DOUBLE Param1,
                              MIL_DOUBLE Param2,
                              MIL_DOUBLE Param3,
                              MIL_DOUBLE Param4);

#if M_MIL_USE_UNICODE
MIL_CAL_DLLFUNC void MFTYPE McalSaveA(MIL_CONST_TEXTA_PTR FileName,
                      MIL_ID      CalibrationId,
                      MIL_INT64   ControlFlag);

MIL_CAL_DLLFUNC MIL_ID MFTYPE McalRestoreA(MIL_CONST_TEXTA_PTR FileName,
                           MIL_ID      SysId,
                           MIL_INT64   ControlFlag,
                           MIL_ID*     CalibrationIdPtr);

MIL_CAL_DLLFUNC void MFTYPE McalStreamA(MIL_TEXTA_PTR MemPtrOrFileName,
                        MIL_ID SysId,
                        MIL_INT64  Operation, MIL_INT64  StreamType,
                        MIL_DOUBLE Version,   MIL_INT64  ControlFlag,
                        MIL_ID *ContextCalIdPtr, MIL_INT   *SizeByteVarPtr);

MIL_CAL_DLLFUNC void MFTYPE McalSaveW(MIL_CONST_TEXTW_PTR FileName,
                      MIL_ID CalibrationId,
                      MIL_INT64  ControlFlag);

MIL_CAL_DLLFUNC MIL_ID MFTYPE McalRestoreW(MIL_CONST_TEXTW_PTR FileName,
                           MIL_ID SysId,
                           MIL_INT64  ControlFlag,
                           MIL_ID * CalibrationIdPtr);

MIL_CAL_DLLFUNC void MFTYPE McalStreamW(MIL_TEXTW_PTR MemPtrOrFileName,
                                        MIL_ID SysId,
                                        MIL_INT64  Operation, MIL_INT64  StreamType,
                                        MIL_DOUBLE Version, MIL_INT64  ControlFlag,
                                        MIL_ID *ContextCalIdPtr, MIL_INT   *SizeByteVarPtr);

#if M_MIL_UNICODE_API
#define McalSave           McalSaveW
#define McalRestore        McalRestoreW
#define McalStream         McalStreamW
#else
#define McalSave           McalSaveA
#define McalRestore        McalRestoreA
#define McalStream         McalStreamA
#endif

#else
MIL_CAL_DLLFUNC void MFTYPE McalSave(MIL_CONST_TEXT_PTR FileName,
                     MIL_ID CalibrationId,
                     MIL_INT64  ControlFlag);

MIL_CAL_DLLFUNC MIL_ID MFTYPE McalRestore(MIL_CONST_TEXT_PTR FileName,
                                          MIL_ID SysId,
                                          MIL_INT64  ControlFlag,
                                          MIL_ID * CalibrationIdPtr);

MIL_CAL_DLLFUNC void MFTYPE McalStream( MIL_TEXT_PTR MemPtrOrFileName,
                        MIL_ID SysId,
                        MIL_INT64  Operation, MIL_INT64  StreamType,
                        MIL_DOUBLE Version,   MIL_INT64  ControlFlag,
                        MIL_ID *ContextCalIdPtr, MIL_INT   *SizeByteVarPtr   );
#endif

/* C++ directive if needed */
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

inline void MFTYPE McalStreamCpp(MilStreamParam MemPtrOrFileName,
                                   MIL_ID         SysId,
                                   MIL_INT64      Operation,
                                   MIL_INT64      StreamType,
                                   MIL_DOUBLE     Version,
                                   MIL_INT64      ControlFlag,
                                   MIL_ID*        ContextCalIdPtr,
                                   MIL_INT*       SizeByteVarPtr)
   {
   McalStream(MemPtrOrFileName.m_Param, SysId, Operation, StreamType, Version, ControlFlag, ContextCalIdPtr, SizeByteVarPtr);
   }

#undef  McalStream
#define McalStream McalStreamCpp

#endif // __cplusplus

#ifdef __cplusplus
//////////////////////////////////////////////////////////////
// McalControl function definition when compiling c++ files
//////////////////////////////////////////////////////////////
#if !M_MIL_USE_LINUX || !M_MIL_USE_64BIT
inline void McalControl(MIL_ID ContextCalOrCalibratedMilObjectId, MIL_INT64  ControlType, int ControlValue)
   {
   McalControlInt64(ContextCalOrCalibratedMilObjectId, ControlType, ControlValue);
   };
#endif
inline void McalControl(MIL_ID ContextCalOrCalibratedMilObjectId, MIL_INT64  ControlType, MIL_INT32 ControlValue)
   {
   McalControlInt64(ContextCalOrCalibratedMilObjectId, ControlType, ControlValue);
   }

inline void McalControl(MIL_ID ContextCalOrCalibratedMilObjectId, MIL_INT64  ControlType, MIL_INT64 ControlValue)
   {
   McalControlInt64(ContextCalOrCalibratedMilObjectId, ControlType, ControlValue);
   }

inline void McalControl(MIL_ID ContextCalOrCalibratedMilObjectId, MIL_INT64  ControlType, MIL_DOUBLE ControlValue)
   {
   McalControlDouble(ContextCalOrCalibratedMilObjectId, ControlType, ControlValue);
   }

#else
//////////////////////////////////////////////////////////////
// For C file, call the default function, i.e. Int64 one
//////////////////////////////////////////////////////////////
#define McalControl  McalControlDouble

#endif // __cplusplus

#if M_MIL_USE_STRING
inline void McalControl(MIL_ID ContextCalOrCalibratedMilObjectId, MIL_INT64 ControlType, const MIL_STRING& ControlValue)
   {
   McalControl(ContextCalOrCalibratedMilObjectId, ControlType, M_PTR_TO_MIL_INT(ControlValue.c_str()));
   }
#endif

#ifdef __cplusplus
inline bool IN_CAL_STRING_RANGE(MIL_INT64 InquireType)
   {
   if (M_NB_ELEMENTS_BIT_SET(InquireType))
      return false;

   switch(InquireType)
      {
      case M_DRAW_CAMERA_COORDINATE_SYSTEM_NAME:
      case M_DRAW_RELATIVE_COORDINATE_SYSTEM_NAME:
         return true;
      default:
         return false;
      }
   }

inline bool MFTYPE McalInquireDataTypeIsSupported(MIL_INT64 DataType)
   {
   switch (DataType)
      {
      case 0:
      case M_TYPE_CHAR:
      case M_TYPE_SHORT:
      case M_TYPE_MIL_INT32:
      case M_TYPE_MIL_INT64:
      case M_TYPE_FLOAT:
      case M_TYPE_DOUBLE:
      case M_TYPE_MIL_ID:
         return true;

      default:
         return false;
      }
   }

inline bool MFTYPE McalInquireSingleDataTypeIsSupported(MIL_INT64 DataType)
   {
   switch (DataType)
      {
      case 0:
      case M_TYPE_CHAR:
      case M_TYPE_SHORT:
      case M_TYPE_MIL_INT32:
      case M_TYPE_MIL_INT64:
      case M_TYPE_FLOAT:
      case M_TYPE_DOUBLE:
         return true;

      default:
         return false;
      }
   }
#endif // __cplusplus

#if M_MIL_USE_SAFE_TYPE

//////////////////////////////////////////////////////////////
// See milos.h for explanation about these functions.
//////////////////////////////////////////////////////////////

// ----------------------------------------------------------
// McalInquire

inline MIL_INT MFTYPE McalInquireUnsafe  (MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, void*       UserVarPtr);
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, int         UserVarPtr);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, std::nullptr_t        );
#endif
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_INT8*   UserVarPtr);
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_INT16*  UserVarPtr);
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_INT32*  UserVarPtr);
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_INT64*  UserVarPtr);
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, float*      UserVarPtr);
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_DOUBLE* UserVarPtr);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_UINT8*  UserVarPtr);
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_UINT16* UserVarPtr);
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_UINT32* UserVarPtr);
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_UINT64* UserVarPtr);
#endif                                                               
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T                                      
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, wchar_t*    UserVarPtr);
#endif

// ----------------------------------------------------------
// McalInquireSingle
inline MIL_INT MFTYPE McalInquireSingleUnsafe  (MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, void*       UserVarPtr);
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, int         UserVarPtr);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, std::nullptr_t        );
#endif
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_INT8*   UserVarPtr);
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_INT16*  UserVarPtr);
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_INT32*  UserVarPtr);
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_INT64*  UserVarPtr);
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, float*      UserVarPtr);
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_DOUBLE* UserVarPtr);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                                
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_UINT8*  UserVarPtr);
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_UINT16* UserVarPtr);
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_UINT32* UserVarPtr);
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_UINT64* UserVarPtr);
#endif                                                                               
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T                                                      
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, wchar_t*    UserVarPtr);
#endif

// ----------------------------------------------------------
// McalInquire

inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, int UserVarPtr)
   {
   if (UserVarPtr)
      SafeTypeError(MIL_TEXT("McalInquire"));

   return McalInquire(CalibrationOrMilId, InquireType, NULL);
   }

inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, int UserVarPtr)
   {
   if (UserVarPtr)
      SafeTypeError(MIL_TEXT("McalInquireSingle"));

   return McalInquireSingle(CalibrationId, Index, InquireType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, std::nullptr_t)
   {
   return McalInquire(CalibrationOrMilId, InquireType, NULL);
   }

inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, std::nullptr_t)
   {
   return McalInquireSingle(CalibrationId, Index, InquireType, NULL);
   }
#endif

inline MIL_INT MFTYPE McalInquireExecute (MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, void* UserVarPtr, MIL_INT64  GivenType)
   {
   MIL_INT64 RequiredType = (InquireType & M_HLVLDATATYPE_MASK);
   if (!McalInquireDataTypeIsSupported(RequiredType))
      RequiredType = 0;

   if (RequiredType == 0)
      {
      MIL_INT64 StrippedInquireType = (InquireType & ~(M_HLVLDATATYPE_MASK|M_DEFAULT));
      switch (StrippedInquireType)
         {
         case M_GRID_UNIT_SHORT_NAME:
         case M_DRAW_CAMERA_COORDINATE_SYSTEM_NAME:
         case M_DRAW_RELATIVE_COORDINATE_SYSTEM_NAME:
            if (M_CLIENT_ASCII_ENCODING_SET(StrippedInquireType))
               RequiredType = M_TYPE_CHAR;
            else
               RequiredType = (M_MIL_USE_UNICODE ? M_TYPE_SHORT : M_TYPE_CHAR);
            break;

         default:
            RequiredType = M_TYPE_DOUBLE;
            break;
         }
      }

   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if (RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("McalInquire"));

   return McalInquire(CalibrationOrMilId, InquireType, UserVarPtr);
   }

inline MIL_INT MFTYPE McalInquireSingleExecute (MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, void* UserVarPtr, MIL_INT64  GivenType)
   {
   MIL_INT64 RequiredType = (InquireType &  M_HLVLDATATYPE_MASK);
   if (!McalInquireSingleDataTypeIsSupported(RequiredType))
      RequiredType = 0;

   if (RequiredType == 0)
      {
      MIL_INT64 StrippedInquireType = (InquireType & ~(M_HLVLDATATYPE_MASK|M_DEFAULT));
      switch (StrippedInquireType)
         {
         case M_GRID_UNIT_SHORT_NAME:
            if (M_CLIENT_ASCII_ENCODING_SET(StrippedInquireType))
               RequiredType = M_TYPE_CHAR;
            else
               RequiredType = (M_MIL_USE_UNICODE ? M_TYPE_SHORT : M_TYPE_CHAR);
            break;
      
         default:
            RequiredType = M_TYPE_DOUBLE;
            break;
         }
      }

   if (RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("McalInquireSingle"));

   return McalInquireSingle(CalibrationId, Index, InquireType, UserVarPtr);
   }

inline MIL_INT MFTYPE McalInquireUnsafe  (MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, void*       UserVarPtr) {return McalInquire       (CalibrationOrMilId, InquireType, UserVarPtr                  );}
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_INT8*   UserVarPtr) {return McalInquireExecute(CalibrationOrMilId, InquireType, UserVarPtr, M_TYPE_CHAR);}
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_INT16*  UserVarPtr) {return McalInquireExecute(CalibrationOrMilId, InquireType, UserVarPtr, M_TYPE_SHORT);}
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_INT32*  UserVarPtr) {return McalInquireExecute(CalibrationOrMilId, InquireType, UserVarPtr, M_TYPE_MIL_INT32);}
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_INT64*  UserVarPtr) {return McalInquireExecute(CalibrationOrMilId, InquireType, UserVarPtr, M_TYPE_MIL_INT64);}
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, float*      UserVarPtr) {return McalInquireExecute(CalibrationOrMilId, InquireType, UserVarPtr, M_TYPE_FLOAT   );}
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_DOUBLE* UserVarPtr) {return McalInquireExecute(CalibrationOrMilId, InquireType, UserVarPtr, M_TYPE_DOUBLE   );}
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_UINT8*  UserVarPtr) {return McalInquireExecute(CalibrationOrMilId, InquireType, UserVarPtr, M_TYPE_CHAR);}
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_UINT16* UserVarPtr) {return McalInquireExecute(CalibrationOrMilId, InquireType, UserVarPtr, M_TYPE_SHORT);}
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_UINT32* UserVarPtr) {return McalInquireExecute(CalibrationOrMilId, InquireType, UserVarPtr, M_TYPE_MIL_INT32);}
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, MIL_UINT64* UserVarPtr) {return McalInquireExecute(CalibrationOrMilId, InquireType, UserVarPtr, M_TYPE_MIL_INT64);}
#endif
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T
inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, wchar_t* UserVarPtr) {return McalInquireExecute(CalibrationOrMilId, InquireType, UserVarPtr, M_TYPE_SHORT);}
#endif

inline MIL_INT MFTYPE McalInquireSingleUnsafe  (MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, void*       UserVarPtr) {return McalInquireSingle       (CalibrationId, Index, InquireType, UserVarPtr                  );}
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_INT8*   UserVarPtr) {return McalInquireSingleExecute(CalibrationId, Index, InquireType, UserVarPtr, M_TYPE_CHAR);}
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_INT16*  UserVarPtr) {return McalInquireSingleExecute(CalibrationId, Index, InquireType, UserVarPtr, M_TYPE_SHORT);}
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_INT32*  UserVarPtr) {return McalInquireSingleExecute(CalibrationId, Index, InquireType, UserVarPtr, M_TYPE_MIL_INT32);}
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_INT64*  UserVarPtr) {return McalInquireSingleExecute(CalibrationId, Index, InquireType, UserVarPtr, M_TYPE_MIL_INT64);}
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, float*      UserVarPtr) {return McalInquireSingleExecute(CalibrationId, Index, InquireType, UserVarPtr, M_TYPE_FLOAT   );}
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_DOUBLE* UserVarPtr) {return McalInquireSingleExecute(CalibrationId, Index, InquireType, UserVarPtr, M_TYPE_DOUBLE   );}
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                                
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_UINT8*  UserVarPtr) {return McalInquireSingleExecute(CalibrationId, Index, InquireType, UserVarPtr, M_TYPE_CHAR);}
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_UINT16* UserVarPtr) {return McalInquireSingleExecute(CalibrationId, Index, InquireType, UserVarPtr, M_TYPE_SHORT);}
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_UINT32* UserVarPtr) {return McalInquireSingleExecute(CalibrationId, Index, InquireType, UserVarPtr, M_TYPE_MIL_INT32);}
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_UINT64* UserVarPtr) {return McalInquireSingleExecute(CalibrationId, Index, InquireType, UserVarPtr, M_TYPE_MIL_INT64);}
#endif                                                                               
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T                                                      
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, wchar_t*    UserVarPtr) {return McalInquireSingleExecute(CalibrationId, Index, InquireType, UserVarPtr, M_TYPE_SHORT);}
#endif

#define McalInquire          McalInquireSafeType
#define McalInquireSingle    McalInquireSingleSafeType

#else // #if M_MIL_USE_SAFE_TYPE

#define McalInquireUnsafe          McalInquire
#define McalInquireSingleUnsafe    McalInquireSingle

#endif // #if M_MIL_USE_SAFE_TYPE

// ----------------------------------------------------------
// Overload for std::vector.
#if defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR
template <typename UserType>
inline MIL_INT MFTYPE McalInquire(MIL_ID CalibrationOrMilId, MIL_INT64  InquireType, std::vector<UserType> &UserVarPtr)
   {
   // If the given MIL data type is not the same as the SrcType, change it to the correct one
   // and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(InquireType) != 0)
      {
      SafeTypeError(MIL_TEXT("McalInquire"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   InquireType = M_STRIP_HLVLDATATYPE(InquireType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   McalInquire(CalibrationOrMilId, M_STRIP_HLVLDATATYPE(InquireType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   UserVarPtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      return McalInquire(CalibrationOrMilId, InquireType, &UserVarPtr[0]);
      }
   return 0;
   }
template <typename UserType>
inline MIL_INT MFTYPE McalInquireSingle(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, std::vector<UserType> &UserVarPtr)
   {
   // If the given MIL data type is not the same as the SrcType, change it to the correct one
   // and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(InquireType) != 0)
      {
      SafeTypeError(MIL_TEXT("McalInquireSingle"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   InquireType = M_STRIP_HLVLDATATYPE(InquireType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   McalInquireSingle(CalibrationId, Index, M_STRIP_HLVLDATATYPE(InquireType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   UserVarPtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      return McalInquireSingle(CalibrationId, Index, InquireType, &UserVarPtr[0]);
      }
   return 0;
   }

// ----------------------------------------------------------
// Overloads for std::vector in McalList.
inline void MFTYPE McalList(MIL_ID                         CalibrationId,
                            const std::vector<MIL_DOUBLE>& PixCoordXArrayPtr,
                            const std::vector<MIL_DOUBLE>& PixCoordYArrayPtr,
                            const std::vector<MIL_DOUBLE>& WorldCoordXArrayPtr,
                            const std::vector<MIL_DOUBLE>& WorldCoordYArrayPtr,
                            CMilArrayParamIn               WorldCoordZArrayPtr,
                            MIL_INT                        NumPoint,
                            MIL_INT64                      Operation,
                            MIL_INT64                      ControlFlag)
   {
#if M_MIL_USE_SAFE_TYPE
   if(!WorldCoordZArrayPtr.IsValidParam())
      {
      SafeTypeError(MIL_TEXT("McalList"), MIL_TEXT("WorldCoordZArrayPtr cannot be an non zero pointer!"));
      }
   if(NumPoint <= 0)
      {
      SafeTypeError(MIL_TEXT("McalList"), MIL_TEXT("NumPoint parameter must be greater than zero."));
      }
   if(PixCoordXArrayPtr.size() != PixCoordYArrayPtr.size() ||
      PixCoordXArrayPtr.size() != WorldCoordXArrayPtr.size() ||
      PixCoordXArrayPtr.size() != WorldCoordYArrayPtr.size() ||
      ((MIL_INT)PixCoordXArrayPtr.size() != WorldCoordZArrayPtr.Size<MIL_DOUBLE>() && !WorldCoordZArrayPtr.IsNullPtr()) ||
      PixCoordYArrayPtr.size() != WorldCoordXArrayPtr.size() ||
      PixCoordYArrayPtr.size() != WorldCoordYArrayPtr.size() ||
      ((MIL_INT)PixCoordYArrayPtr.size() != WorldCoordZArrayPtr.Size<MIL_DOUBLE>() && !WorldCoordZArrayPtr.IsNullPtr()) ||
      WorldCoordXArrayPtr.size() != WorldCoordYArrayPtr.size() ||
      ((MIL_INT)WorldCoordXArrayPtr.size() != WorldCoordZArrayPtr.Size<MIL_DOUBLE>() && !WorldCoordZArrayPtr.IsNullPtr()) ||
      ((MIL_INT)WorldCoordYArrayPtr.size() != WorldCoordZArrayPtr.Size<MIL_DOUBLE>() && !WorldCoordZArrayPtr.IsNullPtr()))
      {
      SafeTypeError(MIL_TEXT("McalList"), MIL_TEXT("The input vectors must have the same size."));
      }
   if(PixCoordXArrayPtr.empty())
      {
      SafeTypeError(MIL_TEXT("McalList"), MIL_TEXT("The input vectors cannot be empty."));
      }
   if(!WorldCoordZArrayPtr.IsNullPtr() && WorldCoordZArrayPtr.GetMilDataType() != MilTraits<MIL_DOUBLE>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("McalList"), MIL_TEXT("The data type of WorldCoordZArrayPtr must be MIL_DOUBLE."));
      }
   if(NumPoint > (MIL_INT)PixCoordXArrayPtr.size() && NumPoint != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("McalList"), MIL_TEXT("NumPoint parameter must be smaller or equal (M_DEFAULT) to the size of input vectors."));
      }
#endif

   if(NumPoint == M_DEFAULT || NumPoint > (MIL_INT)PixCoordXArrayPtr.size())
      {
      NumPoint = (MIL_INT)PixCoordXArrayPtr.size();
      }

   McalList(CalibrationId,
            &PixCoordXArrayPtr[0],
            &PixCoordYArrayPtr[0],
            &WorldCoordXArrayPtr[0],
            &WorldCoordYArrayPtr[0],
            WorldCoordZArrayPtr.GetData<MIL_DOUBLE>(),
            NumPoint,
            Operation,
            ControlFlag);
   }

// ----------------------------------------------------------
// Overloads for std::vector in McalTransformCoordinate3dList.
inline void MFTYPE McalTransformCoordinate3dList(MIL_ID                         CalibrationOrImageId,
                                                 MIL_INT64                      SrcCoordinateSystem,
                                                 MIL_INT64                      DstCoordinateSystem,
                                                 MIL_INT                        NumPoints,
                                                 const std::vector<MIL_DOUBLE>& SrcCoordXArrayPtr,
                                                 const std::vector<MIL_DOUBLE>& SrcCoordYArrayPtr,
                                                 CMilArrayParamIn               SrcCoordZArrayPtr,
                                                 std::vector<MIL_DOUBLE>&       DstCoordXArrayPtr,
                                                 std::vector<MIL_DOUBLE>&       DstCoordYArrayPtr,
                                                 CMilArrayParamOut              DstCoordZArrayPtr,
                                                 MIL_INT64                      ModeFlag)
   {
#if M_MIL_USE_SAFE_TYPE
   if(!SrcCoordZArrayPtr.IsValidParam() || !DstCoordZArrayPtr.IsValidParam())
      {
      SafeTypeError(MIL_TEXT("McalTransformCoordinate3dList"), MIL_TEXT("SrcCoordZArrayPtr or DstCoordZArrayPtr cannot be an non zero integer."));
      }
   if(NumPoints <= 0)
      {
      SafeTypeError(MIL_TEXT("McalTransformCoordinate3dList"), MIL_TEXT("NumPoints parameter must be greater than zero."));
      }
   if(SrcCoordXArrayPtr.size() != SrcCoordYArrayPtr.size() ||
      ((MIL_INT)SrcCoordXArrayPtr.size() != SrcCoordZArrayPtr.Size<MIL_DOUBLE>() && !SrcCoordZArrayPtr.IsNullPtr()) ||
      ((MIL_INT)SrcCoordYArrayPtr.size() != SrcCoordZArrayPtr.Size<MIL_DOUBLE>() && !SrcCoordZArrayPtr.IsNullPtr()))
      {
      SafeTypeError(MIL_TEXT("McalTransformCoordinate3dList"), MIL_TEXT("The input vectors must have the same size."));
      }
   if(SrcCoordXArrayPtr.empty())
      {
      SafeTypeError(MIL_TEXT("McalTransformCoordinate3dList"), MIL_TEXT("The input vectors cannot be empty."));
      }
   if(!SrcCoordZArrayPtr.IsNullPtr() && SrcCoordZArrayPtr.GetMilDataType() != MilTraits<MIL_DOUBLE>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("McalTransformCoordinate3dList"), MIL_TEXT("The data type of SrcCoordZArrayPtr must be MIL_DOUBLE."));
      }
   if(!DstCoordZArrayPtr.IsNullPtr() && DstCoordZArrayPtr.GetMilDataType() != MilTraits<MIL_DOUBLE>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("McalTransformCoordinate3dList"), MIL_TEXT("The data type of DstCoordZArrayPtr must be MIL_DOUBLE."));
      }
   if(NumPoints > (MIL_INT)SrcCoordXArrayPtr.size() && NumPoints != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("McalTransformCoordinate3dList"), MIL_TEXT("NumPoints parameter must be smaller or equal (M_DEFAULT) to the size of input vectors."));
      }
#endif

   if(NumPoints == M_DEFAULT || NumPoints > (MIL_INT)SrcCoordXArrayPtr.size())
      {
      NumPoints = (MIL_INT)SrcCoordXArrayPtr.size();
      }

   DstCoordXArrayPtr.resize(NumPoints);
   DstCoordYArrayPtr.resize(NumPoints);
   DstCoordZArrayPtr.Resize<MIL_DOUBLE>(NumPoints);

   McalTransformCoordinate3dList(CalibrationOrImageId,
                                 SrcCoordinateSystem,
                                 DstCoordinateSystem,
                                 NumPoints,
                                 &SrcCoordXArrayPtr[0],
                                 &SrcCoordYArrayPtr[0],
                                 SrcCoordZArrayPtr.GetData<MIL_DOUBLE>(),
                                 &DstCoordXArrayPtr[0],
                                 &DstCoordYArrayPtr[0],
                                 DstCoordZArrayPtr.GetData<MIL_DOUBLE>(),
                                 ModeFlag);
   }

// ----------------------------------------------------------
// Overloads for std::vector in McalTransformCoordinateList.
inline void MFTYPE McalTransformCoordinateList(MIL_ID                         CalibrationOrImageId,
                                               MIL_INT64                      TransformType,
                                               MIL_INT                        NumPoints,
                                               const std::vector<MIL_DOUBLE>& SrcCoordXArrayPtr,
                                               CMilArrayParamIn               SrcCoordYArrayPtr,
                                               std::vector<MIL_DOUBLE>&       DstCoordXArrayPtr,
                                               CMilArrayParamOut              DstCoordYArrayPtr)
   {
#if M_MIL_USE_SAFE_TYPE
   if(!SrcCoordYArrayPtr.IsValidParam() || !DstCoordYArrayPtr.IsValidParam())
      {
      SafeTypeError(MIL_TEXT("McalTransformCoordinateList"), MIL_TEXT("SrcCoordYArrayPtr or DstCoordYArrayPtr cannot be an non zero integer."));
      }
   if(NumPoints <= 0)
      {
      SafeTypeError(MIL_TEXT("McalTransformCoordinateList"), MIL_TEXT("NumPoints parameter must be greater than zero."));
      }
   if((MIL_INT)SrcCoordXArrayPtr.size() != SrcCoordYArrayPtr.Size<MIL_DOUBLE>() && !SrcCoordYArrayPtr.IsNullPtr())
      {
      SafeTypeError(MIL_TEXT("McalTransformCoordinateList"), MIL_TEXT("The input vectors must have the same size."));
      }
   if(SrcCoordXArrayPtr.empty())
      {
      SafeTypeError(MIL_TEXT("McalTransformCoordinateList"), MIL_TEXT("The input vectors cannot be empty."));
      }
   if(!SrcCoordYArrayPtr.IsNullPtr() && SrcCoordYArrayPtr.GetMilDataType() != MilTraits<MIL_DOUBLE>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("McalTransformCoordinateList"), MIL_TEXT("The data type of SrcCoordYArrayPtr must be MIL_DOUBLE."));
      }
   if(!DstCoordYArrayPtr.IsNullPtr() && DstCoordYArrayPtr.GetMilDataType() != MilTraits<MIL_DOUBLE>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("McalTransformCoordinateList"), MIL_TEXT("The data type of DstCoordYArrayPtr must be MIL_DOUBLE."));
      }
#endif

   MIL_INT NeededNumPoints = SrcCoordYArrayPtr.IsNullPtr() ? (MIL_INT)SrcCoordXArrayPtr.size() / 2 : (MIL_INT)SrcCoordXArrayPtr.size();

   if(NumPoints == M_DEFAULT || NumPoints > NeededNumPoints)
      {
#if M_MIL_USE_SAFE_TYPE
      if(NumPoints > NeededNumPoints && NumPoints != M_DEFAULT)
         {
         SafeTypeError(MIL_TEXT("McalTransformCoordinateList"), MIL_TEXT("NumPoints parameter must be smaller or equal (M_DEFAULT) to the size of input vectors."));
         }
#endif
      NumPoints = NeededNumPoints;
      }

   DstCoordXArrayPtr.resize(DstCoordYArrayPtr.IsNullPtr() ? 2 * NumPoints : NumPoints);
   DstCoordYArrayPtr.Resize<MIL_DOUBLE>(NumPoints);

   McalTransformCoordinateList(CalibrationOrImageId,
                               TransformType,
                               NumPoints,
                               &SrcCoordXArrayPtr[0],
                               SrcCoordYArrayPtr.GetData<MIL_DOUBLE>(),
                               &DstCoordXArrayPtr[0],
                               DstCoordYArrayPtr.GetData<MIL_DOUBLE>());
   }

// ----------------------------------------------------------
// Overloads for std::vector in MxxxStream.
inline void MFTYPE McalStream(std::vector<MIL_UINT8>  &MemPtrOrFileName,
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
                          McalStream);
   }
#endif // defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR


#if M_MIL_USE_STRING
/***************************************************************************/
/* CALIBRATION MODULE                                                      */
/***************************************************************************/

#if M_MIL_USE_UNICODE
#if M_MIL_UNICODE_API
inline void MFTYPE McalSaveW(const MIL_STRING& FileName, MIL_ID CalibrationId, MIL_INT64 ControlFlag)
   {
   return McalSaveW(FileName.c_str(), CalibrationId, ControlFlag);
   }

inline MIL_ID MFTYPE McalRestoreW(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64   ControlFlag, MIL_ID* CalibrationIdPtr)
   {
   return McalRestoreW(FileName.c_str(), SysId, ControlFlag, CalibrationIdPtr);
   }

#else
inline void MFTYPE McalSaveA(const MIL_STRING& FileName, MIL_ID CalibrationId, MIL_INT64 ControlFlag)
   {
   return McalSaveA(FileName.c_str(), CalibrationId, ControlFlag);
   }

inline MIL_ID MFTYPE McalRestoreA(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64   ControlFlag, MIL_ID* CalibrationIdPtr)
   {
   return McalRestoreA(FileName.c_str(), SysId, ControlFlag, CalibrationIdPtr);
   }

#endif /* M_MIL_UNICODE_API */
#else
inline void MFTYPE McalSave(const MIL_STRING& FileName, MIL_ID CalibrationId, MIL_INT64 ControlFlag)
   {
   return McalSave(FileName.c_str(), CalibrationId, ControlFlag);
   }

inline MIL_ID MFTYPE McalRestore(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64   ControlFlag, MIL_ID* CalibrationIdPtr)
   {
   return McalRestore(FileName.c_str(), SysId, ControlFlag, CalibrationIdPtr);
   }

#endif /*M_MIL_USE_UNICODE */

#if M_MIL_USE_SAFE_TYPE
inline MIL_INT MFTYPE McalInquireSingleSafeType(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64  InquireType, MIL_STRING &UserVarPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InquireType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("McalInquireSingle"), MIL_TEXT("Inquire type not supported with MIL_STRING."));
      }
#endif

   MIL_INT RetValue = 0;

   MIL_INT InternalStringSize = 0;
   McalInquireSingleSafeType(CalibrationId, Index, (InquireType & (~M_HLVLDATATYPE_MASK)) + M_STRING_SIZE + M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = McalInquireSingleSafeType(CalibrationId, Index, InquireType, &UserVarPtr[0]);
      UserVarPtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }

inline MIL_INT MFTYPE McalInquireSafeType(MIL_ID CalibrationOrMilId, MIL_INT64 InquireType, MIL_STRING    &UserVarPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InquireType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("McalInquire"), MIL_TEXT("Inquire type not supported with MIL_STRING."));
      }
#endif
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   McalInquireSafeType(CalibrationOrMilId, (InquireType & (~M_HLVLDATATYPE_MASK)) + M_STRING_SIZE + M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = McalInquireSafeType(CalibrationOrMilId, InquireType, &UserVarPtr[0]);
      UserVarPtr.resize(InternalStringSize - 1);

      }
   return RetValue;
   }
#else /* M_MIL_USE_SAFE_TYPE */
inline MIL_INT MFTYPE McalInquire(MIL_ID CalibrationOrMilId, MIL_INT64 InquireType, MIL_STRING    &UserVarPtr)
   {
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   McalInquire(CalibrationOrMilId, (InquireType & (~M_HLVLDATATYPE_MASK)) + M_STRING_SIZE + M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = McalInquire(CalibrationOrMilId, InquireType, &UserVarPtr[0]);
      UserVarPtr.resize(InternalStringSize - 1);

      }


   return RetValue;
   }

inline MIL_INT MFTYPE McalInquireSingle(MIL_ID CalibrationId, MIL_INT Index, MIL_INT64 InquireType, MIL_STRING    &UserVarPtr)
   {
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;
   McalInquireSingle(CalibrationId, Index, (InquireType & (~M_HLVLDATATYPE_MASK)) + M_STRING_SIZE + M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = McalInquireSingle(CalibrationId, Index, InquireType, &UserVarPtr[0]);
      UserVarPtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }
#endif /* M_MIL_USE_SAFE_TYPE */
#endif /* M_MIL_USE_STRING*/

////////////////////////////////////////////////////////////////////////////////
// MIL_UNIQUE_ID support

#if M_MIL_USE_MIL_UNIQUE_ID

#if M_MIL_USE_SAFE_TYPE
template <> inline bool MilIsCorrectObjectType<&McalFree>(MIL_INT64 ObjectType)
   {
   return (ObjectType & ~M_USER_DEFINE_LOW_ATTRIBUTE) == M_CAL_OBJECT;
   }
#endif

typedef MIL_UNIQUE_ID<&McalFree> MIL_UNIQUE_CAL_ID;

#if M_MIL_USE_MOVE_SEMANTICS

inline MIL_UNIQUE_CAL_ID McalAlloc(MIL_ID SysId, MIL_INT64 Mode, MIL_INT64 ModeFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_CAL_ID(McalAlloc(SysId, Mode, ModeFlag, M_NULL));
   }
inline MIL_UNIQUE_CAL_ID McalRestore(MIL_CONST_TEXT_PTR FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_CAL_ID(McalRestore(FileName, SysId, ControlFlag, M_NULL));
   }
#if M_MIL_USE_STRING
inline MIL_UNIQUE_CAL_ID McalRestore(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_CAL_ID(McalRestore(FileName, SysId, ControlFlag, M_NULL));
   }
#endif // M_MIL_USE_STRING
template <MilFreeFuncType FreeFunc> inline void McalFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

inline void McalStream(MilStreamParam       MemPtrOrFileName,
                       MIL_ID               SysId           ,
                       MIL_INT64            Operation       ,
                       MIL_INT64            StreamType      ,
                       MIL_DOUBLE           Version         ,
                       MIL_INT64            ControlFlag     ,
                       MIL_UNIQUE_CAL_ID*   ContextCalIdPtr ,
                       MIL_INT*             SizeByteVarPtr  )
   {
   MxxxStreamForMilUniqueId(MemPtrOrFileName, SysId, Operation, StreamType, Version, ControlFlag, ContextCalIdPtr, SizeByteVarPtr, McalStream);
   }

#endif // M_MIL_USE_MOVE_SEMANTICS
#endif // M_MIL_USE_MIL_UNIQUE_ID

// End of MIL_UNIQUE_ID support
////////////////////////////////////////////////////////////////////////////////

#endif // !M_MIL_LITE
#endif // __MILCAL_H__
