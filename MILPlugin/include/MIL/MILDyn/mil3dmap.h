////////////////////////////////////////////////////////////////////////////////
//! 
//! \file  mil3dmap.h
//! 
//! \brief Mil3dmap CAPI header (M3dmap...)
//! 
//! AUTHOR: Matrox Imaging
//!
//! COPYRIGHT NOTICE:
//! Copyright © Matrox Electronic Systems Ltd., 1992-2021.
//! All Rights Reserved 
//  Revision:  10.40.0881
////////////////////////////////////////////////////////////////////////////////

#ifndef __MIL_3DMAP_H__
#define __MIL_3DMAP_H__

#if (!M_MIL_LITE) /* MIL FULL ONLY */

#if M_MIL_USE_RT
#ifdef M_3DMAP_EXPORTS
#define MIL_3DMAP_DLLFUNC __declspec(dllexport)
#else
#define MIL_3DMAP_DLLFUNC __declspec(dllimport)
#endif
#else
#define MIL_3DMAP_DLLFUNC
#endif

/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
   {
#endif

////////////////////////////////////////////////////////////////////////////////
// M3dmapAlloc ContextTypes

#define M_LASER                                       1L

// ControlFlags for M_LASER ContextType
#define M_CALIBRATED_CAMERA_LINEAR_MOTION             1L
#define M_DEPTH_CORRECTION                            2L

// Combination flags for M_CALIBRATED_CAMERA_LINEAR_MOTION
#define M_LASER_OFFSET                               16                // =utilities=
#define M_LASER_LABEL_FLAG                  0x40000000L                // =utilities=
#define M_LASER_LABEL(LaserLabel)    ( ((LaserLabel) << M_LASER_OFFSET) | M_LASER_LABEL_FLAG )

#define M_CAMERA_OFFSET                               3                // =utilities=
#define M_CAMERA_LABEL_FLAG                 0x20000000L                // =utilities=
#define M_CAMERA_LABEL(CameraLabel)  ( ((CameraLabel) << M_CAMERA_OFFSET) | M_CAMERA_LABEL_FLAG )

// Indexing, used in other M3dmap functions (M3dmapInquire(), M3dmapControl(), ...)
#define M_CONTEXT                            0x08000000L // already defined in mil.h
#define M_GENERAL                            0x20000000L // already defined in milmod.h, milstr.h, ...
#define M_ALL                                0x40000000L // already defined in mil.h

#define M_POINT_CLOUD_LABEL_FLAG             0x18000000L               // =utilities=      
#define M_POINT_CLOUD_LABEL(PointCloudLabel)    ((PointCloudLabel) | M_POINT_CLOUD_LABEL_FLAG)

#define M_POINT_CLOUD_INDEX_FLAG             0x28000000L               // =utilities= 
#define M_POINT_CLOUD_INDEX(PointCloudIndex)    ((PointCloudIndex) | M_POINT_CLOUD_INDEX_FLAG)

////////////////////////////////////////////////////////////////////////////////
// M3dmapAllocResult ResultTypes
#define M_LASER_CALIBRATION_DATA                   1901L
#define M_DEPTH_CORRECTED_DATA                     1902L
#define M_POINT_CLOUD_RESULT                       1903L
////////////////////////////////////////////////////////////////////////////////
// M3dmapControl/M3dmapInquire

// ControlTypes for 3d reconstruction contexts

#define M_SCAN_SPEED                                  2L


#define M_CORRECTED_DEPTH                            18L

#define M_CALIBRATION_STATUS                        159L // Already defined in milcal.h

#define M_CAMERA_IMAGE_SIZE_X                      1303L
#define M_CAMERA_IMAGE_SIZE_Y                      1304L
#define M_EXTRACTION_CHILD_OFFSET_X                1308L
#define M_EXTRACTION_CHILD_OFFSET_Y                1309L
#define M_EXTRACTION_FIXED_POINT                   1310L
#define M_LASER_CONTEXT_TYPE                       1313L
#define M_CALIBRATION_DEPTHS                       1314L
#define M_NUMBER_OF_CALIBRATION_DEPTHS             1315L
#define M_NUMBER_OF_MISSING_DATA_PER_COLUMN        1316L
#define M_NUMBER_OF_COLUMNS                        1317L
#define M_NUMBER_OF_COLUMNS_WITH_MISSING_DATA      1318L
#define M_NUMBER_OF_INVERSIONS_PER_COLUMN          1319L
#define M_NUMBER_OF_COLUMNS_WITH_INVERSIONS        1320L
#define M_FIT_RMS_ERROR                            1333L
#define M_LASER_PLANE_A                            1385L
#define M_LASER_PLANE_B                            1386L
#define M_LASER_PLANE_C                            1387L
#define M_LASER_PLANE_D                            1388L
#define M_LASER_LABEL_VALUE                        1871L
#define M_CAMERA_LABEL_VALUE                       1872L
#define M_ASSUMED_PERPENDICULAR_TO_MOTION          1878L
#define M_EXTRACTION_RANGE_Z_LIMIT1                1904L
#define M_EXTRACTION_RANGE_Z_LIMIT2                1905L
#define M_EXTRACTION_RANGE_Z                       1913L
#define M_LOCATE_PEAK_1D_CONTEXT_ID                2003L


// ControlTypes for 3d reconstruction result buffers
#define M_MAX_FRAMES                                 17L

#define M_RESULTS_DISPLACEMENT_MODE                1898L
#define M_RESULTS_DISPLACEMENT_Y                   1899L
#define M_NUMBER_OF_POINT_CLOUDS                   1916L
// ControlTypes for point clouds
#define M_MAX_FRAMES                                 17L
#define M_LASER_LABEL_VALUE                        1871L
#define M_CAMERA_LABEL_VALUE                       1872L
#define M_POINT_CLOUD_LABEL_VALUE                  1937L
#define M_POINT_CLOUD_INDEX_VALUE                  1938L
#define M_INFINITE                                   -1L // Already defined in mil.h, milstr.h, milreg.h, milmetrol.h

// Control Values for M_CALIBRATION_STATUS
#define M_CALIBRATED                          0x0000300L // Already defined in milcal.h, milmod.h
#define M_LASER_LINE_NOT_DETECTED                     2L
#define M_NOT_INITIALIZED                             3L // Already defined in milcal.h
#define M_NOT_ENOUGH_MEMORY                           4L
#define M_INTERNAL_ERROR                              5L
#define M_MATHEMATICAL_EXCEPTION                      8L // Already defined in milcal.h
#define M_GLOBAL_OPTIMIZATION_ERROR                1879L
                                                                                    
// Control Values for M_RESULTS_DISPLACEMENT_MODE

#define M_FIXED                                    0x50L // Already defined in milim.h
#define M_CURRENT                            0x00000002L // Already defined in mil.h

// Inquire values for M_POINT_CLOUD_TYPE
#define M_LASER_SCAN                               1917L
#define M_UNORGANIZED                              1919L
                                                                                                   
////////////////////////////////////////////////////////////////////////////////
// M3dmapAddScan ControlFlags

#define M_EXTRACT_LINE                             1338L
#define M_LINE_ALREADY_EXTRACTED                   1339L

////////////////////////////////////////////////////////////////////////////////
// M3dmapClear Operations
#define M_CLEAR                              0x00000001L // Already defined in mil.h, mildisplay.h, ...
#define M_DELETE                                      3L // Already defined in mil.h, milblob.h, ...
#define M_REMOVE_LAST_SCAN                         1493L

////////////////////////////////////////////////////////////////////////////////
// M3dmapCalibrateMultiple ControlFlags

#define M_ALLOW_DUPLICATES                   0x08000000L

////////////////////////////////////////////////////////////////////////////////
// M3dmapExtract Operations

//M3dmapCopyResult CopyType
#define M_CORRECTED_DEPTH_MAP                          1L
#define M_UNCORRECTED_DEPTH_MAP                     1341L
#define M_PARTIALLY_CORRECTED_DEPTH_MAP             3767
#define M_POINT_CLOUD                               3856 
#define M_POINT_CLOUD_UNORGANIZED                   3857
#define M_PARTIALLY_CORRECTED_DEPTH_MAP_SIZE_X      3858
#define M_PARTIALLY_CORRECTED_DEPTH_MAP_SIZE_Y      3859
#define M_PARTIALLY_CORRECTED_DEPTH_MAP_BUFFER_TYPE 3860
#define M_NO_REFLECTANCE                            3964    

////////////////////////////////////////////////////////////////////////////////
// M3dmapGetResult ResultTypes

#define M_SCAN_LANE_DIRECTION                         1  // Already defined in milim.h
#define M_NUMBER_OF_3D_POINTS                         5L
#define M_CORRECTED_DEPTH_MAP_SIZE_X                  6L
#define M_CORRECTED_DEPTH_MAP_SIZE_Y                  7L
#define M_CORRECTED_DEPTH_MAP_BUFFER_TYPE             8L
#define M_INTENSITY_MAP_BUFFER_TYPE                   9L
#define M_CAMERA_IMAGE_SIZE_X                      1303L
#define M_CAMERA_IMAGE_SIZE_Y                      1304L
#define M_UNCORRECTED_DEPTH_MAP_FIXED_POINT        1343L
#define M_UNCORRECTED_DEPTH_MAP_SIZE_X             1344L
#define M_UNCORRECTED_DEPTH_MAP_SIZE_Y             1345L
#define M_UNCORRECTED_DEPTH_MAP_BUFFER_TYPE        1346L
#define M_NUMBER_OF_MISSING_DATA_LAST_SCAN         1348L
#define M_TOTAL_DISPLACEMENT_Y                     1896L
#define M_HAS_FEATURE                        0x08000000L

// Combination flags for M_NUMBER_OF_3D_POINTS
#define M_PARTIAL_WRITE                      0x08000000L
#define M_LAST_SCAN                          0x20000000L
#define M_EXCLUDE_INVALID_POINTS             0x04000000L
#define M_INCLUDE_ALL_POINTS                 0x00000000L

// Combination flags for M_HAS_FEATURE

#define M_POSITION                           0x00000402L // Already defined in milmeas.h, miledge.h, milmetrol.h
#define M_INTENSITY                                  52L // Already defined in milbead.h
#define M_XYZ                                      1935L
#define M_XYZI                                     1936L

////////////////////////////////////////////////////////////////////////////////
// M3dmapGet/M3dmapPut

#define M_INVALID_POINT_FLOAT           3.402823466e+38F

// Features

#define M_POSITION                           0x00000402L // Already defined in milmeas.h, miledge.h, milmetrol.h
#define M_INTENSITY                                  52L // Already defined in milbead.h

// PointsToInclude
#define M_PARTIAL_WRITE                      0x08000000L
#define M_LAST_SCAN                          0x20000000L
#define M_EXCLUDE_INVALID_POINTS             0x04000000L
#define M_INCLUDE_ALL_POINTS                 0x00000000L

// Type
#define M_UNSIGNED                           0x00000000L             // Already defined in mil.h
#define M_SIGNED                             0x08000000L             // Already defined in mil.h
#define M_FLOAT                             (0x40000000L | M_SIGNED) // Already defined in mil.h

// ControlFlag
#define M_APPEND                             0x20000000L // Already defined in mil.h
#define M_DELETE                                      3L // Already defined in mil.h, ...
#define M_REPLACE                            0x01000060L // Already defined in mil.h, miledge.h, milocr.h, milbead.h

////////////////////////////////////////////////////////////////////////////////
// M3dmapDraw Operations
#define M_DRAW_PEAKS_LAST                          1305L
#define M_DRAW_GEOMETRY                            1357L
#define M_DRAW_REGION_VALID                        1380L
#define M_DRAW_REGION_INTERPOLATED                 1381L
#define M_DRAW_REGION_UNCALIBRATED                 1382L
#define M_DRAW_REGION_MISSING_DATA                 1383L
#define M_DRAW_REGION_INVERTED                     1384L
#define M_DRAW_CALIBRATION_LINES                   1391L
#define M_DRAW_CALIBRATION_PEAKS                   1678L

////////////////////////////////////////////////////////////////////////////////
#define M_IN_RANGE                              1L          // Already defined in    milblob.h, mil.h, miledge.h
#define M_OUT_RANGE                             2L          // Already defined in    milblob.h, mil.h, miledge.h
#define M_GREATER                               5L          // Already defined in    milblob.h, mil.h, miledge.h
#define M_LESS                                  6L          // Already defined in    milblob.h, mil.h, miledge.h
////////////////////////////////////////////////////////////////////////////////
// M3dmapCopyResult
#define M_INTENSITY_MAP                       2030L
#define M_ABSOLUTE_COORDINATE_SYSTEM     0x01000000L    /* (also defined in mil.h) */
////////////////////////////////////////////////////////////////////////////////
// M3dmapDraw3d()                                                             //
////////////////////////////////////////////////////////////////////////////////
#define M_ROOT_NODE                                 0
#define M_DRAW_3D_CONTEXT                        3815
#define M_DRAW_CAMERA_COORDINATE_SYSTEM          3816
#define M_DRAW_FRUSTUM                           3819
#define M_DRAW_ABSOLUTE_COORDINATE_SYSTEM        1445L 
#define M_DRAW_LASER_PLANE                       3845
#define M_DRAW_LASER_PLANE_COLOR_FILL            3905                    
#define M_DRAW_LASER_PLANE_OPACITY               3906
#define M_DRAW_FRUSTUM_COLOR                     3838
#define M_DRAW_LASER_LINE_COORDINATE_SYSTEM      3843
#define M_DRAW_COORDINATE_SYSTEM_LENGTH          3846
#define M_DRAW_CAMERA_COORDINATE_SYSTEM_NAME     (3865| M_CLIENT_ENCODING)
#define M_DRAW_LASER_PLANE_COLOR_OUTLINE         3907
#define M_TOOL_COORDINATE_SYSTEM                  1L
////////////////////////////////////////////////////////////////////////////////
// M3dmapAlignScan
////////////////////////////////////////////////////////////////////////////////
#define M_ALIGN_CONTEXT                               4891
#define M_ALIGN_RESULT                                4892
#define M_OBJECT_SHAPE                                4893 
#define M_FLAT_SURFACE                                4894 
#define M_DISK                                        4895
#define M_DIAMETER                                    4769L
#define M_ALIGN_X_POSITION                            5236
#define M_ALIGN_Z_POSITION                            5237
#define M_ALIGN_Z_DIRECTION                           5239
#define M_OBJECT_CENTER                               5244
#define M_Z_UP                                        5245
#define M_Z_DOWN                                      5246
#define M_OBJECT_TOP                                  5258
#define M_OBJECT_BOTTOM                               5259
#define M_SAME_Y                                      5361
#define M_SAME_X                                      5362
#define M_REVERSE_X                                   5087L // Already defined in mil
#define M_REVERSE_Y                                   5088L // Already defined in mil
#define M_ALIGN_XY_DIRECTION                          5363
#define M_UNKNOWN                                    -9999L // Already define in mil.h
#define M_SAME                                        -1L   // Already defined in MilMeas.h
#define M_REVERSE                                      4L   // Already defined in Mil.h
#define M_CAMERA_TILT_X                                5375
#define M_ZERO                                       0x100L // Already defined in milblob
#define M_POSITIVE                                       2L      // Already defined in milmeas.h
#define M_NEGATIVE                                      -2L      // Already defined in milmeas.h
//result
#define M_ALIGN_X_POSITION                            5236
#define M_ALIGN_Z_POSITION                            5237
#define M_ALIGN_Z_DIRECTION                           5239
#define M_OBJECT_CENTER                               5244
#define M_Z_UP                                        5245
#define M_Z_DOWN                                      5246
#define M_OBJECT_TOP                                  5258
#define M_OBJECT_BOTTOM                               5259
//result
#define M_STEP_LENGTH                                 5030
#define M_TRANSFORMATION_MATRIX                         72L
#define M_ROTATION_MATRIX                                5L
#define M_SHEAR_MATRIX                                5233
#define M_RIGID_MATRIX                                5371
#define M_SENSOR_PITCH                                5397
#define M_SENSOR_YAW                                  5398
#define M_STATUS                                0x00008002L      // Already defined in milcode.h, milcolor.h, miledge.h 
#define M_NOT_ENOUGH_VALID_DATA                       1336L      // Already defined in mil3dmet
#define M_ALL_POINTS_COLLINEAR                        1337L
#define M_DISK_NOT_FOUND                           0x01000
#define M_DISK_EDGES_NOT_FOUND                     0x0100
#define M_HOLES_FOUND                                 5373
#define M_Y_MIRRORED                                  5435
////////////////////////////////////////////////////////////////////////////////
// Other defines 
#define M_ROBOT_BASE_COORDINATE_SYSTEM            3L
// Possible value for OutlierDistanceWorld, MaxRadius
#define M_INFINITE                                   -1L // Already defined in mil.h

////////////////////////////////////////////////////////////////////////////////
// Deprecated names, kept for code backward compatibility
#if OldDefinesSupport
   // M3dmapControl/M3dmapInquire
   #define M_FILL_GAP_MODE                    M_FILL_SHARP_ELEVATION
   #define M_FILL_GAP_DEPTH                   M_FILL_SHARP_ELEVATION_DEPTH

   // M3dmapGet/M3dmapGetResult
   #define M_NO_INVALID_POINT                 M_EXCLUDE_INVALID_POINTS

   // M3dmapAllocResult
   #define M_POINT_CLOUD_CONTAINER            M_POINT_CLOUD_RESULT

   MIL_DEPRECATED(M_FILL_GAP_MODE , 1010)
   MIL_DEPRECATED(M_FILL_GAP_DEPTH, 1010)
   MIL_DEPRECATED(M_NO_INVALID_POINT, 1020)
   MIL_DEPRECATED(M_POINT_CLOUD_CONTAINER, 1040)
#endif

////////////////////////////////////////////////////////////////////////////////
// Deprecated values, kept for binary backward compatibility
#if OldDefinesSupport
   // M3dmapAllocResult
   #define M_LASER_DATA                                  1L // Deprecated, use other result types

   // M3dmapControl/M3dmapInquire
   #define M_MIN_INTENSITY                              12L // Deprecated for 3dmap only, use MimControl(M_MINIMUM_CONTRAST)
   #define M_DEPRECATED_GRAY_LEVEL_SIZE_Z              141L // Deprecated, use M_GRAY_LEVEL_SIZE_Z
   #define M_WORLD_OFFSET_X                            142L // Deprecated, use M3dmapSetBox
   #define M_WORLD_OFFSET_Y                            143L // Deprecated, use M3dmapSetBox
   #define M_WORLD_OFFSET_Z                            144L // Deprecated, use M3dmapSetBox

   #define M_TOP_WHITE                          0x00040000L // Deprecated, use M_AUTO_SCALE_Z with M_NEGATIVE
   #define M_TOP_BLACK                          0x00080000L // Deprecated, use M_AUTO_SCALE_Z with M_POSITIVE

   // M3dmapAddScan
   #define M_CLEAR_DATA                               1340L // Deprecated, use M3dmapClear()

   // M3dmapGetResult ResultTypes
   #define M_3D_POINTS_X                                 1L // Deprecated, use M3dmapGet()
   #define M_3D_POINTS_Y                                 2L // Deprecated, use M3dmapGet()
   #define M_3D_POINTS_Z                                 3L // Deprecated, use M3dmapGet()
   #define M_3D_POINTS_I                                 4L // Deprecated, use M3dmapGet()
   #define M_DEPTH_CORRECTION_STATE                   1347L // Deprecated, use MappInquireObject(M_OBJECT_TYPE)
   #define M_UNCORRECTED                              1349L // Deprecated, use MappInquireObject(M_OBJECT_TYPE)
   #define M_PARTIALLY_CORRECTED                      1350L // Deprecated, use MappInquireObject(M_OBJECT_TYPE)
   #define M_FULLY_CORRECTED                          1351L // Deprecated, use MappInquireObject(M_OBJECT_TYPE)

   MIL_DEPRECATED(M_LASER_DATA                  , 1010)
   MIL_DEPRECATED(M_DEPRECATED_GRAY_LEVEL_SIZE_Z, 1010)
   MIL_DEPRECATED(M_WORLD_OFFSET_X              , 1010)
   MIL_DEPRECATED(M_WORLD_OFFSET_Y              , 1010)
   MIL_DEPRECATED(M_WORLD_OFFSET_Z              , 1010)
   MIL_DEPRECATED(M_TOP_WHITE                   , 1010)
   MIL_DEPRECATED(M_TOP_BLACK                   , 1010)
   MIL_DEPRECATED(M_CLEAR_DATA                  , 1010)
   MIL_DEPRECATED(M_3D_POINTS_X                 , 1010)
   MIL_DEPRECATED(M_3D_POINTS_Y                 , 1010)
   MIL_DEPRECATED(M_3D_POINTS_Z                 , 1010)
   MIL_DEPRECATED(M_3D_POINTS_I                 , 1010)
   MIL_DEPRECATED(M_DEPTH_CORRECTION_STATE      , 1010)
   MIL_DEPRECATED(M_UNCORRECTED                 , 1010)
   MIL_DEPRECATED(M_PARTIALLY_CORRECTED         , 1010)
   MIL_DEPRECATED(M_FULLY_CORRECTED             , 1010)
#endif
////////////////////////////////////////////////////////////////////////////////
// Deprecated starting 10 SP4                                                 //
////////////////////////////////////////////////////////////////////////////////
#if OldDefinesSupport
#define M_PAIRWISE_ALIGNMENT_CONTEXT               1939L 
#define M_STAT_RESULT                              1307L 
#define M_ALIGNMENT_RESULT                         1921L  
// M3dmapCopyCond
#define M_X                                        2975L  
#define M_Z                                        2976L  
#define M_I                                        2977L  
#define M_CONDITION_BUFFER                         2978L  
// M3dmapStat
#define M_DEVIATION_MEAN                           1358L 
#define M_DEVIATION_MAX                            1359L 
#define M_DEVIATION_MIN                            2907L 
#define M_Z_MIN                                    2908L 
#define M_Z_MAX                                    2909L 
#define M_VOLUME                                   1360L 
#define M_NUMBER_OF_PIXELS_VALID                   1362L 
#define M_NUMBER_OF_PIXELS_OUTLIER                 1363L 
#define M_NUMBER_OF_PIXELS_MISSING_DATA            1364L 
#define M_NUMBER_OF_PIXELS_TOTAL                   1365L 
// StatType combination flags
#define M_STAT_POSITIVE                          0x1000L 
#define M_STAT_NEGATIVE                          0x2000L 
#define M_STAT_ABS                               0x4000L 
#define M_STAT_ALL                               0x8000L 
// M3dmapSetGeometry
#define M_HORIZONTAL_PLANE                         1352L 
#define M_HEMISPHERE                               1354L 
#define M_NO_INTENSITY                       0x00010000L
#define M_FIT_PARAM_AX                             1322L 
#define M_FIT_PARAM_AY                             1325L 
#define M_FIT_PARAM_RADIUS                         1327L  
#define M_FIT_PARAM_X0                             1328L  
#define M_FIT_PARAM_Y0                             1329L  
#define M_FIT_PARAM_Z0                             1330L 
#define M_FIT_PARAM_SIGN                           1331L 
#define M_GEOMETRY_DEFINITION_TYPE                 1332L 
#define M_EXTRACTION_CUMULATIVE                    1311L 
#define M_EXTRACTION_SCALE_MODE                    1312L 
#define M_EXTRACTION_SATURATION                    1859L 
#define M_EXTRACTION_OVERLAP                       1860L 
#define M_EXTRACTION_BOX_DEFINED                   1974L 
#define M_EXTRACTION_BOX_MIN_X                     1975L 
#define M_EXTRACTION_BOX_MIN_Y                     1976L 
#define M_EXTRACTION_BOX_MIN_Z                     1977L 
#define M_EXTRACTION_BOX_MAX_X                     1978L 
#define M_EXTRACTION_BOX_MAX_Y                     1979L 
#define M_EXTRACTION_BOX_MAX_Z                     1980L 
#define M_EXTRACTION_BOX_CENTER_X                  1981L 
#define M_EXTRACTION_BOX_CENTER_Y                  1982L 
#define M_EXTRACTION_BOX_CENTER_Z                  1983L 
#define M_EXTRACTION_BOX_SIZE_X                    1984L 
#define M_EXTRACTION_BOX_SIZE_Y                    1985L 
#define M_EXTRACTION_BOX_SIZE_Z                    1986L 
#define M_AUTO_SCALE_ASPECT_RATIO                  1987L 
#define M_AUTO_SCALE_XY                            1988L 
#define M_AUTO_SCALE_Z                             1989L 
#define M_DECIMATION_STEP_MODEL                    1940L 
#define M_DECIMATION_STEP_SCENE                    1941L  
#define M_PREALIGNMENT_MODE                        1942L
#define M_ORGANIZED_NORMALS_NEIGHBORHOOD_RADIUS    1943L 
#define M_MODEL_OVERLAP                            1947L 
#define M_ALIGN_RMS_ERROR_THRESHOLD                1951L 
#define M_ALIGN_RMS_ERROR_RELATIVE_THRESHOLD       1952L 
#define M_EXTRACTION_BOX_MODEL                     2084L 
#define M_EXTRACTION_BOX_SCENE                     2085L 
#define M_NEIGHBORHOOD                             3043L 
#define M_FIT_POINT_CLOUD                          3038L 
#define M_UNCONSTRAINED                              -2L 
#define M_USE_MODEL_NORMALS                  0x01000000L                    
#define M_USE_SCENE_NORMALS                  0x02000000L 
#define M_FILL_MISSING_DATA_ONLY                    1342L
#define M_INCLUDE_POINTS_INSIDE_BOX_ONLY     0x44000000L
#define M_INVALIDATE_POINTS_OUTSIDE_BOX      0x40000000L  
#define M_INSIDE_EXTRACTION_BOX              0x40000000L       
// Pairwise alignment ResultTypes
#define M_ALIGN_RMS_ERROR                          1333L 
#define M_ALIGN_RMS_ERROR_RELATIVE                 1973L 
#define M_ALIGNMENT_MATRIX                         1950L 
#define M_ALIGN_COMPLETED                          2777L 
// Result values for M_STATUS
#define M_ALIGN_RMS_ERROR_THRESHOLD_REACHED          1970L 
#define M_ALIGN_RMS_ERROR_RELATIVE_THRESHOLD_REACHED 1971L 
// M3dmapSetBox
#define M_EXTRACTION_BOX                                1L  
#define M_XYZ                                        1935L 
#define M_XYZI                                       1936L 
#define M_ORGANIZATION_SIZE_X                        2981L 
#define M_ORGANIZATION_SIZE_Y                        2982L
#define M_POINT_CLOUD_TYPE                           1915L
#define M_POINT_CLOUD_ORGANIZED                      1920L
#define M_ALL_POINTS_COLINEAR                        1337L

MIL_DEPRECATED(M_PAIRWISE_ALIGNMENT_CONTEXT                , 1040)
MIL_DEPRECATED(M_STAT_RESULT                               , 1040)
MIL_DEPRECATED(M_ALIGNMENT_RESULT                          , 1040)
MIL_DEPRECATED(M_X                                         , 1040)
MIL_DEPRECATED(M_Z                                         , 1040)
MIL_DEPRECATED(M_I                                         , 1040)
MIL_DEPRECATED(M_CONDITION_BUFFER                          , 1040)
MIL_DEPRECATED(M_DEVIATION_MEAN                            , 1040)
MIL_DEPRECATED(M_DEVIATION_MAX                             , 1040)
MIL_DEPRECATED(M_DEVIATION_MIN                             , 1040) 
MIL_DEPRECATED(M_Z_MIN                                     , 1040) 
MIL_DEPRECATED(M_Z_MAX                                     , 1040) 
MIL_DEPRECATED(M_VOLUME                                    , 1040)  
MIL_DEPRECATED(M_CROSS_SECTION_AREA                        , 1040) 
MIL_DEPRECATED(M_NUMBER_OF_PIXELS_VALID                    , 1040) 
MIL_DEPRECATED(M_NUMBER_OF_PIXELS_OUTLIER                  , 1040) 
MIL_DEPRECATED(M_NUMBER_OF_PIXELS_MISSING_DATA             , 1040)
MIL_DEPRECATED(M_NUMBER_OF_PIXELS_TOTAL                    , 1040)
MIL_DEPRECATED(M_STAT_POSITIVE                             , 1040) 
MIL_DEPRECATED(M_STAT_NEGATIVE                             , 1040) 
MIL_DEPRECATED(M_STAT_ABS                                  , 1040)
MIL_DEPRECATED(M_STAT_ALL                                  , 1040)
MIL_DEPRECATED(M_HORIZONTAL_PLANE                          , 1040) 
MIL_DEPRECATED(M_HEMISPHERE                                , 1040) 
MIL_DEPRECATED(M_NO_INTENSITY                              , 1040)
MIL_DEPRECATED(M_INCLUDE_POINTS_INSIDE_BOX_ONLY            , 1040)  
MIL_DEPRECATED(M_INVALIDATE_POINTS_OUTSIDE_BOX             , 1040) 
MIL_DEPRECATED(M_FIT_PARAM_AX                              , 1040) 
MIL_DEPRECATED(M_FIT_PARAM_AY                              , 1040) 
MIL_DEPRECATED(M_FIT_PARAM_RADIUS                          , 1040) 
MIL_DEPRECATED(M_FIT_PARAM_X0                              , 1040) 
MIL_DEPRECATED(M_FIT_PARAM_Y0                              , 1040)  
MIL_DEPRECATED(M_FIT_PARAM_Z0                              , 1040) 
MIL_DEPRECATED(M_FIT_PARAM_SIGN                            , 1040) 
MIL_DEPRECATED(M_GEOMETRY_DEFINITION_TYPE                  , 1040) 
MIL_DEPRECATED(M_MAX_PIXELS_FOR_STAT                       , 1040) 
MIL_DEPRECATED(M_EXTRACTION_CUMULATIVE                     , 1040) 
MIL_DEPRECATED(M_EXTRACTION_SCALE_MODE                     , 1040) 
MIL_DEPRECATED(M_EXTRACTION_SATURATION                     , 1040) 
MIL_DEPRECATED(M_EXTRACTION_OVERLAP                        , 1040) 
MIL_DEPRECATED(M_EXTRACTION_BOX_DEFINED                    , 1040) 
MIL_DEPRECATED(M_EXTRACTION_BOX_MIN_X                      , 1040) 
MIL_DEPRECATED(M_EXTRACTION_BOX_MIN_Y                      , 1040) 
MIL_DEPRECATED(M_EXTRACTION_BOX_MIN_Z                      , 1040) 
MIL_DEPRECATED(M_EXTRACTION_BOX_MAX_X                      , 1040) 
MIL_DEPRECATED(M_EXTRACTION_BOX_MAX_Y                      , 1040) 
MIL_DEPRECATED(M_EXTRACTION_BOX_MAX_Z                      , 1040)
MIL_DEPRECATED(M_EXTRACTION_BOX_CENTER_X                   , 1040)
MIL_DEPRECATED(M_EXTRACTION_BOX_CENTER_Y                   , 1040)
MIL_DEPRECATED(M_EXTRACTION_BOX_CENTER_Z                   , 1040)
MIL_DEPRECATED(M_EXTRACTION_BOX_SIZE_X                     , 1040)
MIL_DEPRECATED(M_EXTRACTION_BOX_SIZE_Y                     , 1040)
MIL_DEPRECATED(M_EXTRACTION_BOX_SIZE_Z                     , 1040)
MIL_DEPRECATED(M_AUTO_SCALE_ASPECT_RATIO                   , 1040)
MIL_DEPRECATED(M_AUTO_SCALE_XY                             , 1040)
MIL_DEPRECATED(M_AUTO_SCALE_Z                              , 1040)
MIL_DEPRECATED(M_DECIMATION_STEP_MODEL                     , 1040)
MIL_DEPRECATED(M_DECIMATION_STEP_SCENE                     , 1040)
MIL_DEPRECATED(M_PREALIGNMENT_MODE                         , 1040)
MIL_DEPRECATED(M_ORGANIZED_NORMALS_NEIGHBORHOOD_RADIUS     , 1040)
MIL_DEPRECATED(M_MODEL_OVERLAP                             , 1040)
MIL_DEPRECATED(M_ALIGN_RMS_ERROR_THRESHOLD                 , 1040)
MIL_DEPRECATED(M_ALIGN_RMS_ERROR_RELATIVE_THRESHOLD        , 1040)
MIL_DEPRECATED(M_DISTANCE_UNITS                            , 1040)
MIL_DEPRECATED(M_EXTRACTION_BOX_MODEL                      , 1040)
MIL_DEPRECATED(M_EXTRACTION_BOX_SCENE                      , 1040)
MIL_DEPRECATED(M_NEIGHBORHOOD                              , 1040)
MIL_DEPRECATED(M_FIT_POINT_CLOUD                           , 1040)
MIL_DEPRECATED(M_UNCONSTRAINED                             , 1040)
MIL_DEPRECATED(M_USE_MODEL_NORMALS                         , 1040)                    
MIL_DEPRECATED(M_USE_SCENE_NORMALS                         , 1040)
MIL_DEPRECATED(M_FILL_MISSING_DATA_ONLY                    , 1040)
MIL_DEPRECATED(M_INSIDE_EXTRACTION_BOX                     , 1040)
MIL_DEPRECATED(M_ALIGN_RMS_ERROR                           , 1040)
MIL_DEPRECATED(M_ALIGN_RMS_ERROR_RELATIVE                  , 1040)
MIL_DEPRECATED(M_ALIGNMENT_MATRIX                          , 1040)
MIL_DEPRECATED(M_ALIGN_COMPLETED                           , 1040)
MIL_DEPRECATED(M_ALIGN_RMS_ERROR_THRESHOLD_REACHED         , 1040)
MIL_DEPRECATED(M_ALIGN_RMS_ERROR_RELATIVE_THRESHOLD_REACHED, 1040)
MIL_DEPRECATED(M_EXTRACTION_BOX                            , 1040)
MIL_DEPRECATED(M_XYZ                                       , 1040)
MIL_DEPRECATED(M_XYZI                                      , 1040)
MIL_DEPRECATED(M_ORGANIZATION_SIZE_X                       , 1040)
MIL_DEPRECATED(M_ORGANIZATION_SIZE_Y                       , 1040)
MIL_DEPRECATED(M_POINT_CLOUD_TYPE                          , 1040)
MIL_DEPRECATED(M_POINT_CLOUD_ORGANIZED                     , 1040)
MIL_DEPRECATED(M_ALL_POINTS_COLINEAR                       , 1040)
#endif
////////////////////////////////////////////////////////////////////////////////
// CAPI function prototypes

MIL_3DMAP_DLLFUNC MIL_ID MFTYPE M3dmapAlloc(MIL_ID     SysId,
                                            MIL_INT64  ContextType,
                                            MIL_INT64  ControlFlag,
                                            MIL_ID*    ContextOrGeometry3dmapIdPtr);

MIL_3DMAP_DLLFUNC MIL_ID MFTYPE M3dmapAllocResult(MIL_ID     SysId,
                                                  MIL_INT64  ResultType,
                                                  MIL_INT64  ControlFlag,
                                                  MIL_ID*    Result3dmapIdPtr);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapFree(MIL_ID M3dmapId);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapClear(MIL_ID    Result3dmapId,
                                          MIL_INT   LabelOrIndex,
                                          MIL_INT64 Operation,
                                          MIL_INT64 ControlFlag);

// Prototypes for 32/64 bits OSs
MIL_3DMAP_DLLFUNC void MFTYPE M3dmapControlInt64(MIL_ID     ContextOrResult3dmapId,
                                                 MIL_INT    LabelOrIndex,
                                                 MIL_INT64  ControlType,
                                                 MIL_INT64  ControlValue);
MIL_3DMAP_DLLFUNC void MFTYPE M3dmapControlDouble(MIL_ID     ContextOrResult3dmapId,
                                                  MIL_INT    LabelOrIndex,
                                                  MIL_INT64  ControlType,
                                                  MIL_DOUBLE ControlValue);


MIL_3DMAP_DLLFUNC MIL_INT MFTYPE M3dmapInquire(MIL_ID     ContextOrResult3dmapId,
                                               MIL_INT    LabelOrIndex,
                                               MIL_INT64  InquireType,
                                               void*      UserVarPtr);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapAddScan(MIL_ID     Context3dmapId,
                                            MIL_ID     Result3dmapId,
                                            MIL_ID     LaserOrDepthMapImageBufId, 
                                            MIL_ID     IntensityImageBufId,
                                            MIL_ID     ExtraInfoArrayId,
                                            MIL_INT    PointCloudLabel,
                                            MIL_INT64  ControlFlag);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapCalibrate(MIL_ID     Context3dmapId,
                                              MIL_ID     Result3dmapId,
                                              MIL_ID     ContextCalId,
                                              MIL_INT64  ControlFlag);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapCalibrateMultiple(const MIL_ID* Context3dmapIdArrayPtr,
                                                      const MIL_ID* Result3dmapIdArrayPtr ,
                                                      const MIL_ID* ContextCalIdArrayPtr  ,
                                                      MIL_INT       ArraySize             ,
                                                      MIL_INT64     ControlFlag           );


MIL_3DMAP_DLLFUNC void MFTYPE M3dmapGetResult(MIL_ID     Result3dmapId,
                                              MIL_INT    LabelOrIndex,
                                              MIL_INT64  ResultType,
                                              void*      ResultArrayPtr);



MIL_3DMAP_DLLFUNC void MFTYPE M3dmapTriangulate(const MIL_ID*     ContextCalOrImageBufIdArrayPtr,
                                                const MIL_DOUBLE* PixelCoordXArrayPtr,
                                                const MIL_DOUBLE* PixelCoordYArrayPtr,
                                                MIL_DOUBLE*       WorldCoordXArrayPtr,
                                                MIL_DOUBLE*       WorldCoordYArrayPtr,
                                                MIL_DOUBLE*       WorldCoordZArrayPtr,
                                                MIL_DOUBLE*       RMSErrorArrayPtr,
                                                MIL_INT           NumCalibrations,
                                                MIL_INT           NumPoints,
                                                MIL_INT64         CoordinateSystem,
                                                MIL_INT64         ControlFlag);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapDraw(MIL_ID     ContextGraId,
                                         MIL_ID     ContextOrResult3dmapId,
                                         MIL_ID     DstImageBufOrListGraId,
                                         MIL_INT64  Operation,
                                         MIL_INT    LabelOrIndex,
                                         MIL_INT64  ControlFlag);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapCopy(MIL_ID    SrcResult3dmapId,
                                         MIL_INT   SrcLabelOrIndex ,
                                         MIL_ID    DstResult3dmapId,
                                         MIL_INT   DstLabel        ,
                                         MIL_INT64 Operation       ,
                                         MIL_INT64 ControlFlag     );

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapCopyResult(MIL_ID    SrcResult3dmapId,
                                               MIL_INT   SrcLabelOrIndex,
                                               MIL_ID    DstContainerOrImageBufId,
                                               MIL_INT64 CopyType,
                                               MIL_INT64 ControlFlag);

MIL_3DMAP_DLLFUNC MIL_INT64 MFTYPE M3dmapDraw3d(MIL_ID     OperationDraw3dContext3dmapId,
                                                MIL_ID     SrcReconContext3dmapId,
                                                MIL_INT64  SrcIndex,
                                                MIL_ID     DstList3dgraId,
                                                MIL_INT64  DstParentLabel,
                                                MIL_ID     LaserPlaneTextureImageBufId,
                                                MIL_INT64  ControlFlag);

void MFTYPE M3dmapAlignScan(MIL_ID     ContextId,
                            MIL_ID     ContainerBufId,
                            MIL_ID     ResultId,
                            MIL_INT64  ControlFlag);


#if M_MIL_USE_UNICODE
MIL_3DMAP_DLLFUNC void MFTYPE M3dmapSaveA(MIL_CONST_TEXTA_PTR FileName,
                                          MIL_ID      M3dmapId,
                                          MIL_INT64   ControlFlag);

MIL_3DMAP_DLLFUNC MIL_ID MFTYPE M3dmapRestoreA(MIL_CONST_TEXTA_PTR FileName,
                                               MIL_ID      SysId,
                                               MIL_INT64   ControlFlag,
                                               MIL_ID*     M3dmapIdPtr);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapStreamA(MIL_TEXTA_PTR      MemPtrOrFileName,
                                            MIL_ID     SysId,
                                            MIL_INT64  Operation,
                                            MIL_INT64  StreamType,
                                            MIL_DOUBLE Version,
                                            MIL_INT64  ControlFlag,
                                            MIL_ID*    M3dmapIdPtr,
                                            MIL_INT*   SizeByteVarPtr);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapSaveW(MIL_CONST_TEXTW_PTR FileName,
                                          MIL_ID             M3dmapId,
                                          MIL_INT64          ControlFlag);

MIL_3DMAP_DLLFUNC MIL_ID MFTYPE M3dmapRestoreW(MIL_CONST_TEXTW_PTR FileName,
                                               MIL_ID             SysId,
                                               MIL_INT64          ControlFlag,
                                               MIL_ID*            M3dmapIdPtr);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapStreamW(MIL_TEXTW_PTR MemPtrOrFileName,
                                            MIL_ID       SysId,
                                            MIL_INT64    Operation,
                                            MIL_INT64    StreamType,
                                            MIL_DOUBLE   Version,
                                            MIL_INT64    ControlFlag,
                                            MIL_ID*      M3dmapIdPtr,
                                            MIL_INT*     SizeByteVarPtr);

#if M_MIL_UNICODE_API
#define M3dmapSave           M3dmapSaveW
#define M3dmapRestore        M3dmapRestoreW
#define M3dmapStream         M3dmapStreamW
#define M3dmapImport         M3dmapImportW
#define M3dmapExport         M3dmapExportW
#else
#define M3dmapSave           M3dmapSaveA
#define M3dmapRestore        M3dmapRestoreA
#define M3dmapStream         M3dmapStreamA
#define M3dmapImport         M3dmapImportA
#define M3dmapExport         M3dmapExportA
#endif

#else
MIL_3DMAP_DLLFUNC void MFTYPE M3dmapSave(MIL_CONST_TEXT_PTR FileName,
                                         MIL_ID             M3dmapId,
                                         MIL_INT64          ControlFlag);

MIL_3DMAP_DLLFUNC MIL_ID MFTYPE M3dmapRestore(MIL_CONST_TEXT_PTR FileName,
                                              MIL_ID             SysId,
                                              MIL_INT64          ControlFlag,
                                              MIL_ID*            M3dmapIdPtr);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapStream(MIL_TEXT_PTR MemPtrOrFileName,
                                           MIL_ID       SysId,
                                           MIL_INT64    Operation,
                                           MIL_INT64    StreamType,
                                           MIL_DOUBLE   Version,
                                           MIL_INT64    ControlFlag,
                                           MIL_ID*      M3dmapIdPtr,
                                           MIL_INT*     SizeByteVarPtr);

#endif

// Internal functions: do not use in an application.
MIL_3DMAP_DLLFUNC void MFTYPE M3dmapInternalGetCoordinateSystem(MIL_ID ContextOrResultId,       MIL_DOUBLE* CoordinateSystem4x4ArrayPtr);
MIL_3DMAP_DLLFUNC void MFTYPE M3dmapInternalSetCoordinateSystem(MIL_ID          ResultId, const MIL_DOUBLE* CoordinateSystem4x4ArrayPtr);

//////////////////////////////////////////////////////////////
// Deprecated functions.                                    //
//////////////////////////////////////////////////////////////
MIL_3DMAP_DLLFUNC void MFTYPE M3dmapExtract(MIL_ID     Result3dmapId,
                                            MIL_ID     DepthMapImageBufId,
                                            MIL_ID     IntensityMapImageBufId,
                                            MIL_INT64  Operation,
                                            MIL_INT    LabelOrIndex,
                                            MIL_INT64  ControlFlag); 

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapPut(MIL_ID      Result3dmapId,
                                        MIL_INT     LabelOrIndex,
                                        MIL_INT64   Feature,
                                        MIL_INT64   Type,
                                        MIL_INT     ArraySize,
                                        const void* Coord1OrPackedArrayPtr,
                                        const void* Coord2ArrayPtr,
                                        const void* Coord3ArrayPtr,
                                        MIL_ID      CalibratedMilObjectId,
                                        MIL_INT64   ControlFlag);

MIL_3DMAP_DLLFUNC MIL_INT MFTYPE M3dmapGet(MIL_ID      Result3dmapId,
                                           MIL_INT     LabelOrIndex,
                                           MIL_INT64   Feature,
                                           MIL_INT64   PointsToInclude,
                                           MIL_INT64   Type,
                                           MIL_INT     ArraySize,
                                           void*       Coord1OrPackedArrayPtr,
                                           void*       Coord2ArrayPtr,
                                           void*       Coord3ArrayPtr,
                                           MIL_INT*    NeededSizePtr);
MIL_3DMAP_DLLFUNC void MFTYPE M3dmapSetGeometry(MIL_ID     Geometry3dmapId,
                                                MIL_INT64  GeometryType,
                                                MIL_INT64  OperationType,
                                                MIL_DOUBLE Param1,
                                                MIL_DOUBLE Param2,
                                                MIL_DOUBLE Param3,
                                                MIL_DOUBLE Param4,
                                                MIL_DOUBLE Param5);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapStat(MIL_ID      ImageBufId,
                                         MIL_ID      ImageBufOrGeometry3dmapId,
                                         MIL_ID      MaskBufId,
                                         MIL_ID      Result3dmapId,
                                         MIL_INT64   StatType,
                                         MIL_DOUBLE  OutlierDistanceWorld,
                                         MIL_INT64   ControlFlag,
                                         MIL_DOUBLE* StatValuePtr);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapArith(MIL_ID     Src1ImageBufOrGeometry3dmapId,
                                          MIL_ID     Src2ImageBufOrGeometry3dmapId,
                                          MIL_ID     DstImageBufId,
                                          MIL_ID     MaskBufId,
                                          MIL_INT64  Operation,
                                          MIL_INT64  ControlFlag);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapAlign(MIL_ID      Context3dmapId,
                                          MIL_ID      ModelResult3dmapId,
                                          MIL_INT     ModelLabelOrIndex,
                                          MIL_ID      SceneResult3dmapId,
                                          MIL_INT     SceneLabelOrIndex,
                                          MIL_ID      PreAlignmentResult3dmapOrArrayBufId,
                                          MIL_ID      AlignmentResult3dmapOrArrayBufId,
                                          MIL_INT64   ControlFlag,
                                          MIL_INT64*  StatusPtr);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapSetBox(MIL_ID     Result3dmapId,
                                           MIL_INT64  BoxType,
                                           MIL_INT64  BoxDefinitionType,
                                           MIL_DOUBLE XPos1OrSource,
                                           MIL_DOUBLE YPos1,
                                           MIL_DOUBLE ZPos1,
                                           MIL_DOUBLE XPos2OrLength,
                                           MIL_DOUBLE YPos2OrLength,
                                           MIL_DOUBLE ZPos2OrLength);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapCopyCond(MIL_ID     SrcResult3dmapId,
                                             MIL_INT    SrcLabelOrIndex,
                                             MIL_ID     DstResult3dmapId,
                                             MIL_INT    DstLabel,
                                             MIL_INT64  Attribute,
                                             MIL_ID     CondBufId,
                                             MIL_INT64  Condition,
                                             MIL_DOUBLE CondLow,
                                             MIL_DOUBLE CondHigh,
                                             MIL_INT64  ControlFlag);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapPtCldCalculate(MIL_ID     Src1Result3dmapId,
                                                   MIL_INT    Src1LabelOrIndex,
                                                   MIL_ID     Src2ImageBufOrGeometry3dmapId,
                                                   MIL_INT    Src2LabelOrIndex,
                                                   MIL_ID     DstImageBufId,
                                                   MIL_INT64  Operation,
                                                   MIL_INT64  ControlFlag);

#if M_MIL_USE_UNICODE
MIL_3DMAP_DLLFUNC void MFTYPE M3dmapImportA(MIL_CONST_TEXTA_PTR FileName,
                                            MIL_INT64   FileFormat,
                                            MIL_ID      Result3dmapId,
                                            MIL_INT     PointCloudLabel,
                                            MIL_ID      CalibratedMilObjectId,
                                            MIL_INT64   ControlFlag);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapExportA(MIL_CONST_TEXTA_PTR FileName,
                                            MIL_INT64           FileFormat,
                                            MIL_ID              Result3dmapId,
                                            MIL_INT             LabelOrIndex,
                                            MIL_INT64           PointsToInclude,
                                            MIL_INT64           PositionType,
                                            MIL_INT64           IntensityType,
                                            MIL_INT64           ControlFlag);
MIL_3DMAP_DLLFUNC void MFTYPE M3dmapImportW(MIL_CONST_TEXTW_PTR FileName,
                                            MIL_INT64          FileFormat,
                                            MIL_ID             Result3dmapId,
                                            MIL_INT            PointCloudLabel,
                                            MIL_ID             CalibratedMilObjectId,
                                            MIL_INT64          ControlFlag);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapExportW(MIL_CONST_TEXTW_PTR FileName,
                                            MIL_INT64           FileFormat,
                                            MIL_ID              Result3dmapId,
                                            MIL_INT             LabelOrIndex,
                                            MIL_INT64           PointsToInclude,
                                            MIL_INT64           PositionType,
                                            MIL_INT64           IntensityType,
                                            MIL_INT64           ControlFlag);
#if M_MIL_UNICODE_API
#define M3dmapImport         M3dmapImportW
#define M3dmapExport         M3dmapExportW
#else
#define M3dmapImport         M3dmapImportA
#define M3dmapExport         M3dmapExportA
#endif

#else
MIL_3DMAP_DLLFUNC void MFTYPE M3dmapImport(MIL_CONST_TEXT_PTR FileName,
                                           MIL_INT64          FileFormat,
                                           MIL_ID             Result3dmapId,
                                           MIL_INT            PointCloudLabel,
                                           MIL_ID             CalibratedMilObjectId,
                                           MIL_INT64          ControlFlag);

MIL_3DMAP_DLLFUNC void MFTYPE M3dmapExport(MIL_CONST_TEXT_PTR FileName,
                                           MIL_INT64          FileFormat,
                                           MIL_ID             Result3dmapId,
                                           MIL_INT            LabelOrIndex,
                                           MIL_INT64          PointsToInclude,
                                           MIL_INT64          PositionType,
                                           MIL_INT64          IntensityType,
                                           MIL_INT64          ControlFlag);
#endif
/* C++ directive if needed */
#ifdef __cplusplus
}
#endif
////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

inline void MFTYPE M3dmapStreamCpp(MilStreamParam MemPtrOrFileName,
                                   MIL_ID         SysId,
                                   MIL_INT64      Operation,
                                   MIL_INT64      StreamType,
                                   MIL_DOUBLE     Version,
                                   MIL_INT64      ControlFlag,
                                   MIL_ID*        M3dmapIdPtr,
                                   MIL_INT*       SizeByteVarPtr)
   {
   M3dmapStream(MemPtrOrFileName.m_Param, SysId, Operation, StreamType, Version, ControlFlag, M3dmapIdPtr, SizeByteVarPtr);
   }

#undef  M3dmapStream
#define M3dmapStream M3dmapStreamCpp

#endif // __cplusplus


#ifdef __cplusplus
//////////////////////////////////////////////////////////////
// M3dmapControl function definition when compiling c++ files
//////////////////////////////////////////////////////////////
#if !M_MIL_USE_LINUX
inline void M3dmapControl(MIL_ID ContextOrResult3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ControlType, int ControlValue)
   {
   M3dmapControlInt64(ContextOrResult3dmapId, LabelOrIndex, ControlType, ControlValue);
   };
#endif
inline void M3dmapControl(MIL_ID ContextOrResult3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ControlType, MIL_INT32 ControlValue)
   {
   M3dmapControlInt64(ContextOrResult3dmapId, LabelOrIndex, ControlType, ControlValue);
   }

inline void M3dmapControl(MIL_ID ContextOrResult3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ControlType, MIL_INT64 ControlValue)
   {
   M3dmapControlInt64(ContextOrResult3dmapId, LabelOrIndex, ControlType, ControlValue);
   }
inline void M3dmapControl(MIL_ID ContextOrResult3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ControlType, MIL_DOUBLE ControlValue)
   {
   M3dmapControlDouble(ContextOrResult3dmapId, LabelOrIndex, ControlType, ControlValue);
   }
#else
//////////////////////////////////////////////////////////////
// For C file, call the default function, i.e. Double one
//////////////////////////////////////////////////////////////
#define M3dmapControl  M3dmapControlDouble

#endif // __cplusplus


#if M_MIL_USE_STRING                                                                                                                 
inline void M3dmapControl(MIL_ID ContextOrResult3dmapId, MIL_INT LabelOrIndex, MIL_INT64 ControlType, const MIL_STRING& ControlValue)
   {                                                                                                                                 
   M3dmapControlInt64(ContextOrResult3dmapId, LabelOrIndex, ControlType, M_PTR_TO_MIL_INT(ControlValue.c_str()));
   }                                                                                                                                 
#endif                                                                                                                               

#ifdef __cplusplus                                                               
inline bool IN_3DMAP_STRING_RANGE(MIL_INT64 InquireType)           
   {                                                               
   if(M_NB_ELEMENTS_BIT_SET(InquireType))                          
      return false;                                                

   switch(InquireType)                                             
      {                                                            
      case M_DRAW_CAMERA_COORDINATE_SYSTEM_NAME:                   
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

//-------------------------------------------------------------------------------------
//  M3dmapGetResult

inline void MFTYPE M3dmapGetResultUnsafe  (MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, void*       ResultArrayPtr);
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, int         ResultArrayPtr);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, std::nullptr_t            );
#endif
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_INT8*   ResultArrayPtr);
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_INT16*  ResultArrayPtr);
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_INT32*  ResultArrayPtr);
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_INT64*  ResultArrayPtr);
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, float*      ResultArrayPtr);
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_DOUBLE* ResultArrayPtr);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                      
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_UINT8*  ResultArrayPtr);
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_UINT16* ResultArrayPtr);
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_UINT32* ResultArrayPtr);
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_UINT64* ResultArrayPtr);
#endif

// ----------------------------------------------------------
// M3dmapInquire

inline MIL_INT MFTYPE M3dmapInquireUnsafe  (MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, void*       UserVarPtr);
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, int         UserVarPtr);
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, std::nullptr_t        );
#endif
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_INT8*   UserVarPtr);
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_INT16*  UserVarPtr);
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_INT32*  UserVarPtr);
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_INT64*  UserVarPtr);
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, float*      UserVarPtr);
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_DOUBLE* UserVarPtr);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                                
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_UINT8*  UserVarPtr);
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_UINT16* UserVarPtr);
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_UINT32* UserVarPtr);
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_UINT64* UserVarPtr);
#endif                                                                               
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T                                                      
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, wchar_t*    UserVarPtr);
#endif

// -------------------------------------------------------------------------
// M3dmapGetResult

inline void MFTYPE M3dmapGetResultSafeType (MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, int ResultPtr)
   {
   if (ResultPtr != 0)
      SafeTypeError(MIL_TEXT("M3dmapGetResult"));

   M3dmapGetResult(Result3dmapId, LabelOrIndex, ResultType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, std::nullptr_t)
   {
   M3dmapGetResult(Result3dmapId, LabelOrIndex, ResultType, NULL);
   }
#endif

inline void M3dmapGetResultSafeTypeExecute (MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, void* ResultArrayPtr, MIL_INT64  GivenType)
   {
   MIL_INT64  RequiredType = (ResultType & M_HLVLDATATYPE_MASK);
   if((RequiredType != M_TYPE_DOUBLE) && (RequiredType != M_TYPE_MIL_INT32) && (RequiredType != M_TYPE_MIL_INT64) && 
      (RequiredType != M_TYPE_MIL_ID) && (RequiredType != M_TYPE_FLOAT) && (RequiredType != M_TYPE_CHAR) && (RequiredType != M_TYPE_SHORT))
      RequiredType = 0;
   if (RequiredType == 0)
      RequiredType = M_TYPE_DOUBLE;
   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if (RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("M3dmapGetResult"));

   M3dmapGetResult(Result3dmapId, LabelOrIndex, ResultType, ResultArrayPtr);
   }


inline void MFTYPE M3dmapGetResultUnsafe  (MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, void*       ResultArrayPtr){M3dmapGetResult               (Result3dmapId, LabelOrIndex, ResultType, ResultArrayPtr                  );}
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_INT8*   ResultArrayPtr){M3dmapGetResultSafeTypeExecute(Result3dmapId, LabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_CHAR     );}
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_INT16*  ResultArrayPtr){M3dmapGetResultSafeTypeExecute(Result3dmapId, LabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_SHORT    );}
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_INT32*  ResultArrayPtr){M3dmapGetResultSafeTypeExecute(Result3dmapId, LabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_MIL_INT32);}
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_INT64*  ResultArrayPtr){M3dmapGetResultSafeTypeExecute(Result3dmapId, LabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_MIL_INT64);}
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, float*      ResultArrayPtr){M3dmapGetResultSafeTypeExecute(Result3dmapId, LabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_FLOAT    );}
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_DOUBLE* ResultArrayPtr){M3dmapGetResultSafeTypeExecute(Result3dmapId, LabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_DOUBLE   );}
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                      
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_UINT8*  ResultArrayPtr){M3dmapGetResultSafeTypeExecute(Result3dmapId, LabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_CHAR     );}
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_UINT16* ResultArrayPtr){M3dmapGetResultSafeTypeExecute(Result3dmapId, LabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_SHORT    );}
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_UINT32* ResultArrayPtr){M3dmapGetResultSafeTypeExecute(Result3dmapId, LabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_MIL_INT32);}
inline void MFTYPE M3dmapGetResultSafeType(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, MIL_UINT64* ResultArrayPtr){M3dmapGetResultSafeTypeExecute(Result3dmapId, LabelOrIndex, ResultType, ResultArrayPtr, M_TYPE_MIL_INT64);}
#endif

// ----------------------------------------------------------
// M3dmapInquire

inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, int UserVarPtr)
   {
   if (UserVarPtr != 0)
      SafeTypeError(MIL_TEXT("M3dmapInquire"));

   return M3dmapInquire(M3dmapId, LabelOrIndex, InquireType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, std::nullptr_t)
   {
   return M3dmapInquire(M3dmapId, LabelOrIndex, InquireType, NULL);
   }
#endif

inline MIL_INT MFTYPE M3dmapInquireSafeTypeExecute(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, void* UserVarPtr, MIL_INT64  GivenType)
   {
   MIL_INT64  RequiredType = (InquireType & M_HLVLDATATYPE_MASK);
   if((RequiredType != M_TYPE_DOUBLE) && (RequiredType != M_TYPE_MIL_INT32) && (RequiredType != M_TYPE_MIL_INT64) && 
      (RequiredType != M_TYPE_MIL_ID) && (RequiredType != M_TYPE_FLOAT) && (RequiredType != M_TYPE_CHAR) && (RequiredType != M_TYPE_SHORT))
      RequiredType = 0;

   if (RequiredType == 0)
      RequiredType = M_TYPE_DOUBLE;
   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if (RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("M3dmapInquire"));

   return M3dmapInquire(M3dmapId, LabelOrIndex, InquireType, UserVarPtr);
   }

inline MIL_INT MFTYPE M3dmapInquireUnsafe  (MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, void*       UserVarPtr) {return M3dmapInquire               (M3dmapId, LabelOrIndex, InquireType, UserVarPtr                  );}
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_INT8*   UserVarPtr) {return M3dmapInquireSafeTypeExecute(M3dmapId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_CHAR     );}
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_INT16*  UserVarPtr) {return M3dmapInquireSafeTypeExecute(M3dmapId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_SHORT    );}
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_INT32*  UserVarPtr) {return M3dmapInquireSafeTypeExecute(M3dmapId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_MIL_INT32);}
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_INT64*  UserVarPtr) {return M3dmapInquireSafeTypeExecute(M3dmapId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_MIL_INT64);}
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, float*      UserVarPtr) {return M3dmapInquireSafeTypeExecute(M3dmapId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_FLOAT    );}
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_DOUBLE* UserVarPtr) {return M3dmapInquireSafeTypeExecute(M3dmapId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_DOUBLE   );}
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED                                                
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_UINT8*  UserVarPtr) {return M3dmapInquireSafeTypeExecute(M3dmapId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_CHAR     );}
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_UINT16* UserVarPtr) {return M3dmapInquireSafeTypeExecute(M3dmapId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_SHORT    );}
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_UINT32* UserVarPtr) {return M3dmapInquireSafeTypeExecute(M3dmapId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_MIL_INT32);}
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, MIL_UINT64* UserVarPtr) {return M3dmapInquireSafeTypeExecute(M3dmapId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_MIL_INT64);}
#endif                                                                               
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T                                                      
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, wchar_t*    UserVarPtr) {return M3dmapInquireSafeTypeExecute(M3dmapId, LabelOrIndex, InquireType, UserVarPtr, M_TYPE_SHORT    );}
#endif

// ----------------------------------------------------------
// M3dmapGet

struct MilVoidPtr
   {
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
   inline MilVoidPtr(std::nullptr_t          ) : m_IntVal (M_NULL      ), m_PtrType( 0             ) {}
#endif
   inline MilVoidPtr(int         NullPtr     ) : m_IntVal (NullPtr     ), m_PtrType( 0             ) {}
   inline MilVoidPtr(MIL_UINT8  *MilUInt8Ptr ) : m_VoidPtr(MilUInt8Ptr ), m_PtrType( 8 + M_UNSIGNED) {}
   inline MilVoidPtr(MIL_UINT16 *MilUInt16Ptr) : m_VoidPtr(MilUInt16Ptr), m_PtrType(16 + M_UNSIGNED) {}
   inline MilVoidPtr(MIL_UINT32 *MilUInt32Ptr) : m_VoidPtr(MilUInt32Ptr), m_PtrType(32 + M_UNSIGNED) {}
   inline MilVoidPtr(MIL_UINT64 *MilUInt64Ptr) : m_VoidPtr(MilUInt64Ptr), m_PtrType(64 + M_UNSIGNED) {}
   inline MilVoidPtr(MIL_INT8   *MilInt8Ptr  ) : m_VoidPtr(MilInt8Ptr  ), m_PtrType( 8 + M_SIGNED  ) {}
   inline MilVoidPtr(MIL_INT16  *MilInt16Ptr ) : m_VoidPtr(MilInt16Ptr ), m_PtrType(16 + M_SIGNED  ) {}
   inline MilVoidPtr(MIL_INT32  *MilInt32Ptr ) : m_VoidPtr(MilInt32Ptr ), m_PtrType(32 + M_SIGNED  ) {}
   inline MilVoidPtr(MIL_INT64  *MilInt64Ptr ) : m_VoidPtr(MilInt64Ptr ), m_PtrType(64 + M_SIGNED  ) {}
   inline MilVoidPtr(MIL_FLOAT  *MilFloatPtr ) : m_VoidPtr(MilFloatPtr ), m_PtrType(32 + M_FLOAT   ) {}
   inline MilVoidPtr(MIL_DOUBLE *MilDoublePtr) : m_VoidPtr(MilDoublePtr), m_PtrType(64 + M_FLOAT   ) {}

   union
      {
      void*   m_VoidPtr;
      MIL_INT m_IntVal;
      };
   MIL_INT64  m_PtrType;
   };

inline MIL_INT MFTYPE M3dmapGetUnsafe(MIL_ID      Result3dmapId         ,
                                      MIL_INT     LabelOrIndex          ,
                                      MIL_INT64   Feature               ,
                                      MIL_INT64   PointsToInclude       ,
                                      MIL_INT64   Type                  ,
                                      MIL_INT     ArraySize             ,
                                      void*       Coord1OrPackedArrayPtr,
                                      void*       Coord2ArrayPtr        ,
                                      void*       Coord3ArrayPtr        ,
                                      MIL_INT*    NeededSizePtr         )
   {
   return M3dmapGet(Result3dmapId         ,
                    LabelOrIndex          ,
                    Feature               ,
                    PointsToInclude       ,
                    Type                  ,
                    ArraySize             ,
                    Coord1OrPackedArrayPtr,
                    Coord2ArrayPtr        ,
                    Coord3ArrayPtr        ,
                    NeededSizePtr         );
   }

inline void M3dmapGetValidatePtrType(MilVoidPtr UserPtr, MIL_INT64 UserType)
   {
   if (UserPtr.m_PtrType == 0)
      {
      if (UserPtr.m_IntVal != 0)
         SafeTypeError(MIL_TEXT("M3dmapGet"));
      }
   else
      {
      if (UserPtr.m_PtrType != UserType)
         SafeTypeError(MIL_TEXT("M3dmapGet"));
      }
   }

inline MIL_INT MFTYPE M3dmapGetSafeType(MIL_ID      Result3dmapId         ,
                                        MIL_INT     LabelOrIndex          ,
                                        MIL_INT64   Feature               ,
                                        MIL_INT64   PointsToInclude       ,
                                        MIL_INT64   Type                  ,
                                        MIL_INT     ArraySize             ,
                                        MilVoidPtr  Coord1OrPackedArrayPtr,
                                        MilVoidPtr  Coord2ArrayPtr        ,
                                        MilVoidPtr  Coord3ArrayPtr        ,
                                        MIL_INT*    NeededSizePtr         )
   {
   M3dmapGetValidatePtrType(Coord1OrPackedArrayPtr, Type);
   M3dmapGetValidatePtrType(Coord2ArrayPtr        , Type);
   M3dmapGetValidatePtrType(Coord3ArrayPtr        , Type);

   return M3dmapGet(Result3dmapId                   ,
                    LabelOrIndex                    ,
                    Feature                         ,
                    PointsToInclude                 ,
                    Type                            ,
                    ArraySize                       ,
                    Coord1OrPackedArrayPtr.m_VoidPtr,
                    Coord2ArrayPtr        .m_VoidPtr,
                    Coord3ArrayPtr        .m_VoidPtr,
                    NeededSizePtr                   );
   }

// ----------------------------------------------------------
// M3dmapPut

struct MilConstVoidPtr
   {
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
   inline MilConstVoidPtr(std::nullptr_t                ) : m_IntVal      (M_NULL      ), m_PtrType( 0             ) {}
#endif
   inline MilConstVoidPtr(int               NullPtr     ) : m_IntVal      (NullPtr     ), m_PtrType( 0             ) {}
   inline MilConstVoidPtr(const MIL_UINT8  *MilUInt8Ptr ) : m_ConstVoidPtr(MilUInt8Ptr ), m_PtrType( 8 + M_UNSIGNED) {}
   inline MilConstVoidPtr(const MIL_UINT16 *MilUInt16Ptr) : m_ConstVoidPtr(MilUInt16Ptr), m_PtrType(16 + M_UNSIGNED) {}
   inline MilConstVoidPtr(const MIL_UINT32 *MilUInt32Ptr) : m_ConstVoidPtr(MilUInt32Ptr), m_PtrType(32 + M_UNSIGNED) {}
   inline MilConstVoidPtr(const MIL_UINT64 *MilUInt64Ptr) : m_ConstVoidPtr(MilUInt64Ptr), m_PtrType(64 + M_UNSIGNED) {}
   inline MilConstVoidPtr(const MIL_INT8   *MilInt8Ptr  ) : m_ConstVoidPtr(MilInt8Ptr  ), m_PtrType( 8 + M_SIGNED  ) {}
   inline MilConstVoidPtr(const MIL_INT16  *MilInt16Ptr ) : m_ConstVoidPtr(MilInt16Ptr ), m_PtrType(16 + M_SIGNED  ) {}
   inline MilConstVoidPtr(const MIL_INT32  *MilInt32Ptr ) : m_ConstVoidPtr(MilInt32Ptr ), m_PtrType(32 + M_SIGNED  ) {}
   inline MilConstVoidPtr(const MIL_INT64  *MilInt64Ptr ) : m_ConstVoidPtr(MilInt64Ptr ), m_PtrType(64 + M_SIGNED  ) {}
   inline MilConstVoidPtr(const MIL_FLOAT  *MilFloatPtr ) : m_ConstVoidPtr(MilFloatPtr ), m_PtrType(32 + M_FLOAT   ) {}
   inline MilConstVoidPtr(const MIL_DOUBLE *MilDoublePtr) : m_ConstVoidPtr(MilDoublePtr), m_PtrType(64 + M_FLOAT   ) {}

   union
      {
      const void* m_ConstVoidPtr;
      MIL_INT     m_IntVal;
      };
   MIL_INT64      m_PtrType;
   };

inline void MFTYPE M3dmapPutUnsafe(MIL_ID      Result3dmapId         ,
                                   MIL_INT     LabelOrIndex          ,
                                   MIL_INT64   Feature               ,
                                   MIL_INT64   Type                  ,
                                   MIL_INT     ArraySize             ,
                                   const void* Coord1OrPackedArrayPtr,
                                   const void* Coord2ArrayPtr        ,
                                   const void* Coord3ArrayPtr        ,
                                   MIL_ID      CalibratedMilObjectId ,
                                   MIL_INT64   ControlFlag           ) 
   {
   M3dmapPut(Result3dmapId         ,
             LabelOrIndex          ,
             Feature               ,
             Type                  ,
             ArraySize             ,
             Coord1OrPackedArrayPtr,
             Coord2ArrayPtr        ,
             Coord3ArrayPtr        ,
             CalibratedMilObjectId ,
             ControlFlag           );
   }

inline void M3dmapPutValidatePtrType(MilConstVoidPtr UserPtr, MIL_INT64 UserType)
   {
   if (UserPtr.m_PtrType == 0)
      {
      if (UserPtr.m_IntVal != 0)
         SafeTypeError(MIL_TEXT("M3dmapPut"));
      }
   else
      {
      if (UserPtr.m_PtrType != UserType)
         SafeTypeError(MIL_TEXT("M3dmapPut"));
      }
   }

inline void MFTYPE M3dmapPutSafeType(MIL_ID          Result3dmapId         ,
                                     MIL_INT         LabelOrIndex          ,
                                     MIL_INT64       Feature               ,
                                     MIL_INT64       Type                  ,
                                     MIL_INT         ArraySize             ,
                                     MilConstVoidPtr Coord1OrPackedArrayPtr,
                                     MilConstVoidPtr Coord2ArrayPtr        ,
                                     MilConstVoidPtr Coord3ArrayPtr        ,
                                     MIL_ID          CalibratedMilObjectId ,
                                     MIL_INT64       ControlFlag           ) 
   {
   M3dmapPutValidatePtrType(Coord1OrPackedArrayPtr, Type);
   M3dmapPutValidatePtrType(Coord2ArrayPtr        , Type);
   M3dmapPutValidatePtrType(Coord3ArrayPtr        , Type);

   M3dmapPut(Result3dmapId                        ,
             LabelOrIndex                         ,
             Feature                              ,
             Type                                 ,
             ArraySize                            ,
             Coord1OrPackedArrayPtr.m_ConstVoidPtr,
             Coord2ArrayPtr        .m_ConstVoidPtr,
             Coord3ArrayPtr        .m_ConstVoidPtr,
             CalibratedMilObjectId                ,
             ControlFlag                          );
   }

#define M3dmapGetResult        M3dmapGetResultSafeType
#define M3dmapInquire          M3dmapInquireSafeType
#define M3dmapGet              M3dmapGetSafeType 
#define M3dmapPut              M3dmapPutSafeType 

#else // #if M_MIL_USE_SAFE_TYPE

#define M3dmapGetResultUnsafe  M3dmapGetResult
#define M3dmapInquireUnsafe    M3dmapInquire 
#define M3dmapGetUnsafe        M3dmapGet  
#define M3dmapPutUnsafe        M3dmapPut  

#endif // #if M_MIL_USE_SAFE_TYPE

// ----------------------------------------------------------
// Overload for std::vector.
#if defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR
template <typename UserType>
inline MIL_INT MFTYPE M3dmapInquire(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64  InquireType, std::vector<UserType> &UserVarPtr)
   {
   // If the given MIL data type is not the same as the SrcType, change it to the correct one
   // and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(InquireType) != 0)
      {
      SafeTypeError(MIL_TEXT("M3dmapInquire"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   InquireType = M_STRIP_HLVLDATATYPE(InquireType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   M3dmapInquire(M3dmapId, LabelOrIndex, M_STRIP_HLVLDATATYPE(InquireType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   UserVarPtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      return M3dmapInquire(M3dmapId, LabelOrIndex, InquireType, &UserVarPtr[0]);
      }
   return 0;
   }
template <typename UserType>
inline void MFTYPE M3dmapGetResult(MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64  ResultType, std::vector<UserType> &ResultArrayPtr)
   {
   //! If the given MIL data type is not the same as the SrcType, change it to the correct one
   //! and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(ResultType) != 0)
      {
      SafeTypeError(MIL_TEXT("M3dmapGetResult"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   ResultType = M_STRIP_HLVLDATATYPE(ResultType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   M3dmapGetResult(Result3dmapId, LabelOrIndex, M_STRIP_HLVLDATATYPE(ResultType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   ResultArrayPtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      M3dmapGetResult(Result3dmapId, LabelOrIndex, ResultType, &ResultArrayPtr[0]);
      }
   }

// ----------------------------------------------------------
// Overloads for std::vector in M3dmapCalibrateMultiple.
inline void MFTYPE M3dmapCalibrateMultiple(const std::vector<MIL_ID>& Context3dmapIdArrayPtr,
                                           const std::vector<MIL_ID>& Result3dmapIdArrayPtr,
                                           const std::vector<MIL_ID>& ContextCalIdArrayPtr,
                                           MIL_INT                    ArraySize,
                                           MIL_INT64                  ControlFlag)
   {
#if M_MIL_USE_SAFE_TYPE
   if(ArraySize <= 0)
      {
      SafeTypeError(MIL_TEXT("M3dmapCalibrateMultiple"), MIL_TEXT("ArraySize parameter must be greater than zero."));
      }
   if(Context3dmapIdArrayPtr.empty())
      {
      SafeTypeError(MIL_TEXT("M3dmapCalibrateMultiple"), MIL_TEXT("The input vectors cannot be empty."));
      }
   if(Context3dmapIdArrayPtr.size() != Result3dmapIdArrayPtr.size() ||
      Context3dmapIdArrayPtr.size() != ContextCalIdArrayPtr.size() ||
      Result3dmapIdArrayPtr.size() != ContextCalIdArrayPtr.size())
      {
      SafeTypeError(MIL_TEXT("M3dmapCalibrateMultiple"), MIL_TEXT("The input vectors must have the same size."));
      }
   if(ArraySize > (MIL_INT)Context3dmapIdArrayPtr.size() && ArraySize != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("M3dmapCalibrateMultiple"), MIL_TEXT("ArraySize parameter must be smaller or equal (M_DEFAULT) to the size of input vectors."));
      }
#endif

   if(ArraySize == M_DEFAULT || ArraySize > (MIL_INT)Context3dmapIdArrayPtr.size())
      {
      ArraySize = (MIL_INT)Context3dmapIdArrayPtr.size();
      }

   M3dmapCalibrateMultiple(&Context3dmapIdArrayPtr[0],
                           &Result3dmapIdArrayPtr[0],
                           &ContextCalIdArrayPtr[0],
                           ArraySize,
                           ControlFlag);
   }

// ----------------------------------------------------------
// Overloads for std::vector in M3dmapGet.
template <typename UserType>
inline MIL_INT MFTYPE M3dmapGet(MIL_ID                      Result3dmapId,
                                MIL_INT                     LabelOrIndex,
                                MIL_INT64                   Feature,
                                MIL_INT64                   PointsToInclude,
                                MIL_INT64                   Type,
                                MIL_INT                     ArraySize,
                                std::vector<UserType>       &Coord1OrPackedArrayPtr,
                                CMilArrayParamOut           Coord2ArrayPtr,
                                CMilArrayParamOut           Coord3ArrayPtr,
                                MIL_INT*                    NeededSizePtr)  
   {
#if M_MIL_USE_SAFE_TYPE
   if(!Coord2ArrayPtr.IsValidParam() || !Coord3ArrayPtr.IsValidParam())
      {
      SafeTypeError(MIL_TEXT("M3dmapGet"), MIL_TEXT("Coord2ArrayPtr or Coord3ArrayPtr cannot be an non zero pointer."));
      }
   if(Type != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("M3dmapGet"), MIL_TEXT("Type parameter must always be set to M_DEFAULT with std::vector overload."));
      }
   if(ArraySize <= 0)
      {
      SafeTypeError(MIL_TEXT("M3dmapGet"), MIL_TEXT("ArraySize parameter must be greater than zero."));
      }
   if(!Coord2ArrayPtr.IsNullPtr() && Coord2ArrayPtr.GetMilDataType() != MilTraits<UserType>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("M3dmapGet"), MIL_TEXT("The data type of Coord2ArrayPtr must be the same as Coord1OrPackedArrayPtr."));
      }
   if(!Coord3ArrayPtr.IsNullPtr() && Coord3ArrayPtr.GetMilDataType() != MilTraits<UserType>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("M3dmapGet"), MIL_TEXT("The data type of Coord3ArrayPtr must be the same as Coord1OrPackedArrayPtr."));
      }
#endif
   // If the given MIL data type is not the same as the SrcType, change it to the correct one
   // and give a safe type error.
   Type = MilTraits<UserType>::BufferTypeFlag;

   bool InternalArraySizeSpecified = true;

   if(ArraySize == M_DEFAULT)
      {
      InternalArraySizeSpecified = false;
      ArraySize = 0;
      ArraySize = M3dmapGet(Result3dmapId, LabelOrIndex, Feature, PointsToInclude, Type, M_NULL, M_NULL, M_NULL, M_NULL, M_NULL);
      }

   if(ArraySize >= 0)
      {
      Coord1OrPackedArrayPtr.resize(ArraySize);
      Coord2ArrayPtr.Resize<UserType>(ArraySize);
      Coord3ArrayPtr.Resize<UserType>(ArraySize);
      }

   // Call the original function in case the ArraySize parameter is specified.
   // It is to allow the MIL function to pop an MIL error if the ArraySize is invalid.
   // But, if the ArraySize is M_DEFAULT and that M3dmapGet outputs an MIL error,
   // the following condition will ensure to not recall the same function.
   if(ArraySize > 0 || InternalArraySizeSpecified)
      {
      MIL_INT InternalNeededSizeForStdVector = M3dmapGet(Result3dmapId,
                                     LabelOrIndex,
                                     Feature,
                                     PointsToInclude,
                                     Type,
                                     ArraySize,
                                     &Coord1OrPackedArrayPtr[0],
                                     Coord2ArrayPtr.GetData<UserType>(),
                                     Coord3ArrayPtr.GetData<UserType>(),
                                     NeededSizePtr);

      if(InternalNeededSizeForStdVector < ArraySize)
         {
         Coord1OrPackedArrayPtr.resize(InternalNeededSizeForStdVector);
         Coord2ArrayPtr.Resize<UserType>(InternalNeededSizeForStdVector);
         Coord3ArrayPtr.Resize<UserType>(InternalNeededSizeForStdVector);
         }
      return InternalNeededSizeForStdVector;
      }
   return 0;
   }

// ----------------------------------------------------------
// Overloads for std::vector in M3dmapPut.
template <typename UserType>
inline void MFTYPE M3dmapPut(MIL_ID                       Result3dmapId,
                             MIL_INT                      LabelOrIndex,
                             MIL_INT64                    Feature,
                             MIL_INT64                    Type,
                             MIL_INT                      ArraySize,
                             const std::vector<UserType>& Coord1OrPackedArrayPtr,
                             CMilArrayParamIn             Coord2ArrayPtr,
                             CMilArrayParamIn             Coord3ArrayPtr,
                             MIL_ID                       CalibratedMilObjectId,
                             MIL_INT64                    ControlFlag)  
   {
#if M_MIL_USE_SAFE_TYPE
   if(!Coord2ArrayPtr.IsValidParam() || !Coord3ArrayPtr.IsValidParam())
      {
      SafeTypeError(MIL_TEXT("M3dmapPut"), MIL_TEXT("Coord2ArrayPtr or Coord3ArrayPtr cannot be an non zero integer!"));
      }
   if(((MIL_INT)Coord1OrPackedArrayPtr.size() != Coord2ArrayPtr.Size<UserType>() && !Coord2ArrayPtr.IsNullPtr()) ||
      ((MIL_INT)Coord1OrPackedArrayPtr.size() != Coord3ArrayPtr.Size<UserType>() && !Coord3ArrayPtr.IsNullPtr()) ||
      Coord2ArrayPtr.Size<UserType>() != Coord3ArrayPtr.Size<UserType>())
      {
      SafeTypeError(MIL_TEXT("M3dmapPut"), MIL_TEXT("The input vectors must have the same size!"));
      }
   if(Coord1OrPackedArrayPtr.empty())
      {
      SafeTypeError(MIL_TEXT("M3dmapPut"), MIL_TEXT("The input vectors cannot be empty."));
      }
   if(Type != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("M3dmapPut"), MIL_TEXT("Type parameter must always be set to M_DEFAULT with std::vector overload."));
      }
   if(ArraySize <= 0)
      {
      SafeTypeError(MIL_TEXT("M3dmapPut"), MIL_TEXT("ArraySize parameter must be greater than zero."));
      }
   if(!Coord2ArrayPtr.IsNullPtr() && Coord2ArrayPtr.GetMilDataType() != MilTraits<UserType>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("M3dmapPut"), MIL_TEXT("The data type of Coord2ArrayPtr must be the same as Coord1OrPackedArrayPtr."));
      }
   if(!Coord3ArrayPtr.IsNullPtr() && Coord3ArrayPtr.GetMilDataType() != MilTraits<UserType>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("M3dmapPut"), MIL_TEXT("The data type of Coord3ArrayPtr must be the same as Coord1OrPackedArrayPtr."));
      }
   if(ArraySize > (MIL_INT)Coord1OrPackedArrayPtr.size() && ArraySize != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("M3dmapPut"), MIL_TEXT("ArraySize parameter must be smaller or equal (M_DEFAULT) to the size of input vectors."));
      }
#endif

   // If the given MIL data type is not the same as the SrcType, change it to the correct one
   // and give a safe type error.
   Type = MilTraits<UserType>::BufferTypeFlag;

   if(ArraySize == M_DEFAULT || ArraySize > (MIL_INT)Coord1OrPackedArrayPtr.size())
      {
      ArraySize = (MIL_INT)Coord1OrPackedArrayPtr.size();
      }

   M3dmapPut(Result3dmapId,
             LabelOrIndex,
             Feature,
             Type,
             ArraySize,
             &Coord1OrPackedArrayPtr[0],
             Coord2ArrayPtr.GetData<UserType>(),
             Coord3ArrayPtr.GetData<UserType>(),
             CalibratedMilObjectId,
             ControlFlag);
   }

// ----------------------------------------------------------
// Overloads for std::vector in M3dmapTriangulate.
inline void MFTYPE M3dmapTriangulate(const std::vector<MIL_ID    >& ContextCalOrImageBufIdArrayPtr,
                                     const std::vector<MIL_DOUBLE>& PixelCoordXArrayPtr,
                                     const std::vector<MIL_DOUBLE>& PixelCoordYArrayPtr,
                                     std::vector<MIL_DOUBLE>&       WorldCoordXArrayPtr,
                                     std::vector<MIL_DOUBLE>&       WorldCoordYArrayPtr,
                                     std::vector<MIL_DOUBLE>&       WorldCoordZArrayPtr,
                                     CMilArrayParamOut              RMSErrorArrayPtr,
                                     MIL_INT                        NumCalibrations,
                                     MIL_INT                        NumPoints,
                                     MIL_INT64                      CoordinateSystem,
                                     MIL_INT64                      ControlFlag)
   {
#if M_MIL_USE_SAFE_TYPE
   if(NumCalibrations <= 0)
      {
      SafeTypeError(MIL_TEXT("M3dmapTriangulate"), MIL_TEXT("NumCalibrations parameter must be greater than zero."));
      }
   if(NumPoints <= 0)
      {
      SafeTypeError(MIL_TEXT("M3dmapTriangulate"), MIL_TEXT("NumPoints parameter must be greater than zero."));
      }
   if(!RMSErrorArrayPtr.IsValidParam())
      {
      SafeTypeError(MIL_TEXT("M3dmapTriangulate"), MIL_TEXT("RMSErrorArrayPtr cannot be an non zero integer."));
      }
   if(PixelCoordXArrayPtr.size() != PixelCoordYArrayPtr.size())
      {
      SafeTypeError(MIL_TEXT("M3dmapTriangulate"), MIL_TEXT("PixelCoordXArrayPtr and PixelCoordYArrayPtr must have the same size."));
      }
   if(ContextCalOrImageBufIdArrayPtr.empty() || PixelCoordXArrayPtr.empty())
      {
      SafeTypeError(MIL_TEXT("M3dmapTriangulate"), MIL_TEXT("The input vectors cannot be empty."));
      }
   if(!RMSErrorArrayPtr.IsNullPtr() && RMSErrorArrayPtr.GetMilDataType() != MilTraits<MIL_DOUBLE>::TypeFlag)
      {
      SafeTypeError(MIL_TEXT("M3dmapTriangulate"), MIL_TEXT("The data type of RMSErrorArrayPtr must be MIL_DOUBLE."));
      }
   if(NumCalibrations != (MIL_INT)ContextCalOrImageBufIdArrayPtr.size() && NumCalibrations != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("M3dmapTriangulate"), MIL_TEXT("NumCalibrations parameter must be equal (or M_DEFAULT) to the size of input vector."));
      }
#endif

   if(NumCalibrations == M_DEFAULT)
      {
      NumCalibrations = (MIL_INT)ContextCalOrImageBufIdArrayPtr.size();
      }

   MIL_INT NumPointsNeeded = NumCalibrations ? (MIL_INT)PixelCoordXArrayPtr.size() / NumCalibrations : 0;

#if M_MIL_USE_SAFE_TYPE
   if(NumPoints != NumPointsNeeded && NumPoints != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("M3dmapTriangulate"), MIL_TEXT("NumPoints parameter must be equal (or M_DEFAULT) to the needed size."));
      }
#endif

   if(NumPoints != NumPointsNeeded)
      {
      NumPoints = NumPointsNeeded;
      }

   WorldCoordXArrayPtr.resize(NumPoints);
   WorldCoordYArrayPtr.resize(NumPoints);
   WorldCoordZArrayPtr.resize(NumPoints);
   RMSErrorArrayPtr.Resize<MIL_DOUBLE>(NumPoints);

   M3dmapTriangulate(&ContextCalOrImageBufIdArrayPtr[0],
                     &PixelCoordXArrayPtr[0],
                     &PixelCoordYArrayPtr[0],
                     &WorldCoordXArrayPtr[0],
                     &WorldCoordYArrayPtr[0],
                     &WorldCoordZArrayPtr[0],
                     RMSErrorArrayPtr.GetData<MIL_DOUBLE>(),
                     NumCalibrations,
                     NumPoints,
                     CoordinateSystem,
                     ControlFlag);
   }

// ----------------------------------------------------------
// Overloads for std::vector in M3dmapStream.
inline void MFTYPE M3dmapStream(std::vector<MIL_UINT8> &MemPtrOrFileName,
                                MIL_ID                 SysId,
                                MIL_INT64              Operation,
                                MIL_INT64              StreamType,
                                MIL_DOUBLE             Version,
                                MIL_INT64              ControlFlag,
                                MIL_ID*                M3dmapIdPtr,
                                MIL_INT*               SizeByteVarPtr)
   {
   MxxxStreamForStdVector(MemPtrOrFileName,
                          SysId,
                          Operation,
                          StreamType,
                          Version,
                          ControlFlag,
                          M3dmapIdPtr,
                          SizeByteVarPtr,
                          M3dmapStream);
   }
#endif // defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR

#if M_MIL_USE_STRING
/***************************************************************************/
/* M3DMAP MODULE                                                           */
/***************************************************************************/
#if M_MIL_USE_UNICODE

#if M_MIL_UNICODE_API
inline void MFTYPE M3dmapSaveW(const MIL_STRING& FileName, MIL_ID M3dmapId, MIL_INT64 ControlFlag)
   {
   return M3dmapSaveW(FileName.c_str(), M3dmapId, ControlFlag);
   }

inline MIL_ID MFTYPE M3dmapRestoreW(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* M3dmapIdPtr)
   {
   return M3dmapRestoreW(FileName.c_str(), SysId, ControlFlag, M3dmapIdPtr);
   }

inline void MFTYPE M3dmapImportW(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_ID Result3dmapId, MIL_INT PointCloudLabel, MIL_ID CalibratedMilObjectId, MIL_INT64 ControlFlag)
   { 
   return M3dmapImportW(FileName.c_str(), FileFormat, Result3dmapId, PointCloudLabel, CalibratedMilObjectId, ControlFlag);
   }

inline void MFTYPE M3dmapExportW(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64 PointsToInclude, MIL_INT64 PositionType, MIL_INT64 IntensityType, MIL_INT64 ControlFlag)
   { 
   return M3dmapExportW(FileName.c_str(), FileFormat, Result3dmapId, LabelOrIndex, PointsToInclude, PositionType, IntensityType, ControlFlag);
   }
#else
inline void MFTYPE M3dmapSaveA(const MIL_STRING& FileName, MIL_ID M3dmapId, MIL_INT64 ControlFlag)
   {
   return M3dmapSaveA(FileName.c_str(), M3dmapId, ControlFlag);
   }

inline MIL_ID MFTYPE M3dmapRestoreA(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* M3dmapIdPtr)
   {
   return M3dmapRestoreA(FileName.c_str(), SysId, ControlFlag, M3dmapIdPtr);
   }

inline void MFTYPE M3dmapImportA(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_ID Result3dmapId, MIL_INT PointCloudLabel, MIL_ID CalibratedMilObjectId, MIL_INT64 ControlFlag)
   { 
   return M3dmapImportA(FileName.c_str(), FileFormat, Result3dmapId, PointCloudLabel, CalibratedMilObjectId, ControlFlag);
   }

inline void MFTYPE M3dmapExportA(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64 PointsToInclude, MIL_INT64 PositionType, MIL_INT64 IntensityType, MIL_INT64 ControlFlag)
   { 
   return M3dmapExportA(FileName.c_str(), FileFormat, Result3dmapId, LabelOrIndex, PointsToInclude, PositionType, IntensityType, ControlFlag);
   }
#endif /* M_MIL_UNICODE_API */
#else
inline void MFTYPE M3dmapSave(const MIL_STRING& FileName, MIL_ID M3dmapId, MIL_INT64 ControlFlag)
   {
   return M3dmapSave(FileName.c_str(), M3dmapId, ControlFlag);
   }

inline MIL_ID MFTYPE M3dmapRestore(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* M3dmapIdPtr)
   {
   return M3dmapRestore(FileName.c_str(), SysId, ControlFlag, M3dmapIdPtr);
   }

inline void MFTYPE M3dmapImport(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_ID Result3dmapId, MIL_INT PointCloudLabel, MIL_ID CalibratedMilObjectId, MIL_INT64 ControlFlag)
   {
   return M3dmapImport(FileName.c_str(), FileFormat, Result3dmapId, PointCloudLabel, CalibratedMilObjectId, ControlFlag);
   }

inline void MFTYPE M3dmapExport(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_ID Result3dmapId, MIL_INT LabelOrIndex, MIL_INT64 PointsToInclude, MIL_INT64 PositionType, MIL_INT64 IntensityType, MIL_INT64 ControlFlag)
   { 
   return M3dmapExport(FileName.c_str(), FileFormat, Result3dmapId, LabelOrIndex, PointsToInclude, PositionType, IntensityType, ControlFlag);
   }

#endif /* M_MIL_USE_UNICODE */

#if M_MIL_USE_SAFE_TYPE
inline MIL_INT MFTYPE M3dmapInquireSafeType(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64 InquireType, MIL_STRING    &UserVarPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION 
   if((InquireType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("M3dmapInquire"), MIL_TEXT("Inquire type not supported with MIL_STRING."));
      }
#endif
   MIL_INT64  RequiredType = (InquireType & M_HLVLDATATYPE_MASK);
   if((RequiredType != 0) && (RequiredType != M_TYPE_CHAR) && (RequiredType != M_TYPE_SHORT))
      SafeTypeError(MIL_TEXT("M3dmapInquire"), MIL_TEXT("Inquire type not supported with MIL_STRING."));
      
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   M3dmapInquireSafeType(M3dmapId, LabelOrIndex, (InquireType & (~M_HLVLDATATYPE_MASK)) + M_STRING_SIZE + M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      MIL_INT64 Type;
      if(M_CLIENT_ASCII_ENCODING_SET(InquireType))
         Type = M_TYPE_CHAR;
      else
         Type = (M_MIL_USE_UNICODE ? M_TYPE_SHORT : M_TYPE_CHAR);
      RetValue = M3dmapInquire(M3dmapId, LabelOrIndex, (InquireType& (~M_HLVLDATATYPE_MASK) )+Type, &UserVarPtr[0]);
      UserVarPtr.resize(InternalStringSize - 1);

      }
   return RetValue;
   }
#else /* M_MIL_USE_SAFE_TYPE */
inline MIL_INT MFTYPE M3dmapInquire(MIL_ID M3dmapId, MIL_INT LabelOrIndex, MIL_INT64 InquireType, MIL_STRING    &UserVarPtr)
   {
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   M3dmapInquire(M3dmapId, LabelOrIndex,(InquireType & (~M_HLVLDATATYPE_MASK)) + M_STRING_SIZE + M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = M3dmapInquire(M3dmapId, LabelOrIndex, InquireType, &UserVarPtr[0]);
      UserVarPtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }
#endif /* M_MIL_USE_SAFE_TYPE */
#endif /* M_MIL_USE_STRING */

#ifndef M_MIL_WARN_ON_DEPRECATED_MIL3DMAP
#define M_MIL_WARN_ON_DEPRECATED_MIL3DMAP 1
#endif
#if defined(M_MIL_WARN_ON_DEPRECATED_MIL3DMAP) && M_MIL_WARN_ON_DEPRECATED_MIL3DMAP
MIL_DEPRECATED(M3dmapExtract, 1040) // Use M3dimProject() instead.
MIL_DEPRECATED(M3dmapPut, 1040) // Use MbufPut instead.
MIL_DEPRECATED(M3dmapGet, 1040) // Use MbufGet instead.
MIL_DEPRECATED(M3dmapSetGeometry, 1040) // Use M3dgeoAlloc() or M3dmetFit() instead.
MIL_DEPRECATED(M3dmapStat, 1040) // Use M3dimStat instead.
MIL_DEPRECATED(M3dmapArith, 1040) // Use M3dimArith instead. 
MIL_DEPRECATED(M3dmapAlign, 1040) // Use M3dregCalculate instead. 
MIL_DEPRECATED(M3dmapSetBox, 1040) // Use M3dgeoBox instead. 
MIL_DEPRECATED(M3dmapCopyCond, 1040) // Use M3dimCrop instead.
MIL_DEPRECATED(M3dmapPtCldCalculate, 1040) // Use M3dmetDistance instead
MIL_DEPRECATED(M3dmapImport, 1040) // Use MbufImport instead. 
MIL_DEPRECATED(M3dmapExport, 1040) // Use MbufExport instead.
MIL_DEPRECATED(M3dmapImportA, 1040) // Use MbufImport instead. 
MIL_DEPRECATED(M3dmapExportA, 1040) // Use MbufExport instead.
MIL_DEPRECATED(M3dmapImportW, 1040) // Use MbufImport instead. 
MIL_DEPRECATED(M3dmapExportW, 1040) // Use MbufExport instead.
#endif

////////////////////////////////////////////////////////////////////////////////
// MIL_UNIQUE_ID support

#if M_MIL_USE_MIL_UNIQUE_ID

#if M_MIL_USE_SAFE_TYPE
template <> inline bool MilIsCorrectObjectType<&M3dmapFree>(MIL_INT64 ObjectType)
   {
   return (ObjectType & ~M_USER_DEFINE_LOW_ATTRIBUTE) == M_3DMAP_OBJECT;
   }
#endif

typedef MIL_UNIQUE_ID<&M3dmapFree> MIL_UNIQUE_3DMAP_ID;

#if M_MIL_USE_MOVE_SEMANTICS

inline MIL_UNIQUE_3DMAP_ID M3dmapAlloc(MIL_ID SysId, MIL_INT64 ContextType, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DMAP_ID(M3dmapAlloc(SysId, ContextType, ControlFlag, M_NULL));
   }
inline MIL_UNIQUE_3DMAP_ID M3dmapAllocResult(MIL_ID SysId, MIL_INT64 ResultType, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DMAP_ID(M3dmapAllocResult(SysId, ResultType, ControlFlag, M_NULL));
   }
inline MIL_UNIQUE_3DMAP_ID M3dmapRestore(MIL_CONST_TEXT_PTR FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DMAP_ID(M3dmapRestore(FileName, SysId, ControlFlag, M_NULL));
   }
#if M_MIL_USE_STRING
inline MIL_UNIQUE_3DMAP_ID M3dmapRestore(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DMAP_ID(M3dmapRestore(FileName, SysId, ControlFlag, M_NULL));
   }
#endif // M_MIL_USE_STRING
template <MilFreeFuncType FreeFunc> inline void M3dmapFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

inline void M3dmapCalibrateMultiple(
      MilConstArrayIdParam Context3dmapIdArrayPtr,
      MilConstArrayIdParam Result3dmapIdArrayPtr ,
      MilConstArrayIdParam ContextCalIdArrayPtr  ,
      MIL_INT              ArraySize             ,
      MIL_INT64            ControlFlag           )
   {
   M3dmapCalibrateMultiple(Context3dmapIdArrayPtr.m_IdArrayPtr, Result3dmapIdArrayPtr.m_IdArrayPtr,
                           ContextCalIdArrayPtr.m_IdArrayPtr, ArraySize, ControlFlag);
   }

inline void M3dmapStream(MilStreamParam       MemPtrOrFileName,
                         MIL_ID               SysId           ,
                         MIL_INT64            Operation       ,
                         MIL_INT64            StreamType      ,
                         MIL_DOUBLE           Version         ,
                         MIL_INT64            ControlFlag     ,
                         MIL_UNIQUE_3DMAP_ID* M3dmapIdPtr     ,
                         MIL_INT*             SizeByteVarPtr  )
   {
   MxxxStreamForMilUniqueId(MemPtrOrFileName, SysId, Operation, StreamType, Version, ControlFlag, M3dmapIdPtr, SizeByteVarPtr, M3dmapStream);
   }

inline void M3dmapTriangulate(
      MilConstArrayIdParam ContextCalOrImageBufIdArrayPtr,
      const MIL_DOUBLE*    PixelCoordXArrayPtr           ,
      const MIL_DOUBLE*    PixelCoordYArrayPtr           ,
      MIL_DOUBLE*          WorldCoordXArrayPtr           ,
      MIL_DOUBLE*          WorldCoordYArrayPtr           ,
      MIL_DOUBLE*          WorldCoordZArrayPtr           ,
      MIL_DOUBLE*          RMSErrorArrayPtr              ,
      MIL_INT              NumCalibrations               ,
      MIL_INT              NumPoints                     ,
      MIL_INT64            CoordinateSystem              ,
      MIL_INT64            ControlFlag                   )
   {
   M3dmapTriangulate(ContextCalOrImageBufIdArrayPtr.m_IdArrayPtr,
                     PixelCoordXArrayPtr, PixelCoordYArrayPtr,
                     WorldCoordXArrayPtr, WorldCoordYArrayPtr, WorldCoordZArrayPtr,
                     RMSErrorArrayPtr, NumCalibrations, NumPoints, CoordinateSystem, ControlFlag);
   }

#endif // M_MIL_USE_MOVE_SEMANTICS
#endif // M_MIL_USE_MIL_UNIQUE_ID

// End of MIL_UNIQUE_ID support
////////////////////////////////////////////////////////////////////////////////

#endif // !M_MIL_LITE
#endif // __MIL_3DMAP_H__
