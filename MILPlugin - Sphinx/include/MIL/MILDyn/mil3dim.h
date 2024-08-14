//==============================================================================
//! 
//! \brief Mil3dim CAPI header (M3dim...)
//! 
//! AUTHOR:  Matrox Imaging
//!
//! COPYRIGHT NOTICE:
//! Copyright (c) Matrox Electronic Systems Ltd., 1992-2021.
//! All Rights Reserved 
//  Revision:  10.40.0881
//==============================================================================

#ifndef __MIL_3DIM_H__
#define __MIL_3DIM_H__

#if (!M_MIL_LITE) /* MIL FULL ONLY */

#if M_MIL_USE_RT
#ifdef M_3DIM_EXPORTS
#define MIL_3DIM_DLLFUNC __declspec(dllexport)
#else
#define MIL_3DIM_DLLFUNC __declspec(dllimport)
#endif
#else
#define MIL_3DIM_DLLFUNC
#endif

/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
   {
#endif

//==============================================================================
// M3dimAlloc ContextTypes
#define M_CALCULATE_MAP_SIZE_CONTEXT                  3378L
#define M_MESH_CONTEXT                                3314  
#define M_NORMALS_CONTEXT                             3438
#define M_SUBSAMPLE_CONTEXT                           3639
#define M_STATISTICS_CONTEXT                          16L //Already defined in milim
#define M_FILL_GAPS_CONTEXT                           3759
#define M_SURFACE_SAMPLE_CONTEXT                      3799 
//==============================================================================   
// Indexing, used in other M3dim functions (M3dimInquire(), M3dimControl(), ...)
#define M_DEFAULT                               0x10000000L // already defined
#define M_CONTEXT                               0x08000000L // already defined
                                         
#define M_MODIFICATION_COUNT                          5010L // already defined

//==============================================================================
//M3dimCrop
#define M_SHRINK                                      3409
#define M_SAME                                         -1L//Already defined
#define M_INVERSE                                  0x00100//already defined in mil3d
#define M_UNORGANIZED                                1919L//Already defined in mil3dmap
//M3dimSample
#define M_ORGANIZED                                   3418
#define M_SUBSAMPLE_DECIMATE                          3046L
#define M_SUBSAMPLE_RANDOM                            3047L
#define M_SUBSAMPLE_GRID                              3049L
#define M_SUBSAMPLE_NORMAL                            3109L
#define M_INFINITE                                    -1L // Also defined in Mil.h                             
//M3dimMesh
#define M_MESH_SMOOTHED                               3097L
#define M_MESH_ORGANIZED                              3320L
//M3dimCopy
#define M_EXTENT_BOX                                  3466
//M3dimProject
#define M_POINT_BASED                                 3300
#define M_MESH_BASED                                  3301
#define M_OVERWRITE                                   1861L       
//M3dimRotate
 #define M_GEOMETRY_CENTER                            3794
//Remove invalid
#define M_INVALID_POINTS_ONLY                         3734  
#define M_INVALID_NORMALS                             3735
//M3dimFix
#define M_RANGE_FINITE                          0x00000001L
#define M_NORMALS_FINITE                        0x00000002L
#define M_NORMALS_NORMALIZED                    0x00000004L
#define M_MESH_VALID_POINTS                     0x00000008L
#define M_MESH_VALID_NEIGHBORS                  0x00000010L
//M3dimTransformList
#define M_ROTATION_AND_SCALE                           3993
#define M_PLANAR                                0x00040000L //already defined in mil
#define M_PACKED                                0x00020000L             // Already defined in    mil.h, miledge.h
//==============================================================================
// M3dimControl / M3dimInquire
// Context 
#define M_ENABLE                                     -9997L // also in mil.h
#define M_DISABLE                                    -9999L // also in mil.h
#define M_TRUE                                           1L // Already defined in    mil.h, milmeas.h, miledge.h
#define M_FALSE                                          0L // Already defined in    mil.h, milmeas.h, miledge.h
#define M_AUTO                                         444L // also in mil.h
#define M_USER_DEFINED                                  21L // also in mil.h

#define M_MIN                                   0x02000000L // Already defined in    milmeas.h, mil.h, miledge.h
#define M_MAX                                   0x04000000L // also in mil.h
#define M_AVERAGE                               0x00000020L // also in milim.h
#define M_CENTER                                0x00000080L          // already defined in milim.h


#define M_ALLOCATION_FAILURE_REAL_TEST_FLAG            971L // also in milblob.h, milstr.h

 //Mesh Context
#define M_MESH_MODE                                   3430   
#define M_MAXIMUM_ORIENTATION_ANGLE_DIFFERENCE        3315
#define M_MAXIMUM_NUMBER_NEIGHBORS                    3316
#define M_NUMBER_POINTS_PER_CELL                      3317
#define M_MAX_TREE_DEPTH                              3318
#define M_MAX_DISTANCE_TO_SOURCE                      3321
#define M_MESH_STEP_X                                 3322
#define M_MESH_STEP_Y                                 3323
#define M_MAX_DISTANCE                                 12L  // already defined
//Normal Context
#define M_DIRECTION_MODE                              3431                
#define M_TOWARDS_POSITION                            3432
#define M_AWAY_FROM_POSITION                          3433
#define M_TOWARDS_DIRECTION                           3434
#define M_DIRECTION_REFERENCE_X                       3435
#define M_DIRECTION_REFERENCE_Y                       3436
#define M_DIRECTION_REFERENCE_Z                       3437
#define M_NEIGHBOR_SEARCH_MODE                        3041L 
#define M_TREE                                        3042L 
#define M_NEIGHBORHOOD_ORGANIZED_SIZE                 1943L
#define M_SMOOTH                                      (M_ID_OFFSET_OF_DEFAULT_KERNEL +  0L)  // already defined in milim.h
#define M_NEIGHBORHOOD_DISTANCE                       3313
#define M_MESH                                        3994

 //Stat Context
#define M_BOUNDING_BOX                       0x00000003L 
#define M_BOUNDING_BOX_ALGORITHM                   1990L
#define M_BOUNDING_BOX_OUTLIER_RATIO_X             1991L 
#define M_BOUNDING_BOX_OUTLIER_RATIO_Y             1992L
#define M_BOUNDING_BOX_OUTLIER_RATIO_Z             1993L
#define M_BOUNDING_BOX_SECURITY_FACTOR_X           1994L
#define M_BOUNDING_BOX_SECURITY_FACTOR_Y           1995L
#define M_BOUNDING_BOX_SECURITY_FACTOR_Z           1996L
#define M_BOUNDING_BOX_CLAMP_TO_INLIERS            1997L
#define M_CENTROID                                 1956L
 // Control Values for M_BOUNDING_BOX_ALGORITHM
#define M_ALL_POINTS                               1998L
#define M_ROBUST                                   1999L
//MapSize Context
#define M_PIXEL_ASPECT_RATIO                       5L//already defined
#define M_PIXEL_SIZE_X                                 139L // also in milcal.h
#define M_PIXEL_SIZE_Y                                 140L // also in milcal.h
#define M_SIZE_X                                      1536L // also in mil.h
#define M_SIZE_Y                                      1537L // also in mil.h
#define M_FIRST_PERCENTILE                            3481
#define M_SECOND_PERCENTILE                           3482
 //Subsampling context
#define M_SUBSAMPLE_MODE                              3630
#define M_FRACTION_OF_POINTS                          3631
#define M_GRID_SIZE_X                                 3632
#define M_GRID_SIZE_Y                                 3633
#define M_GRID_SIZE_Z                                 3634
#define M_POINT_SELECTED                              3635
#define M_DISTINCT_ANGLE_DIFFERENCE                   3636
#define M_SUBSAMPLE_NORMAL_MODE                       3637
#define M_ORGANIZATION_TYPE                           3638
#define M_PRECISE                                     0x00040000L //already defined
#define M_FAST                                        0x00002000L // already defined in milim.h
#define M_STEP_SIZE_X                                 2153  // already defined
#define M_STEP_SIZE_Y                                 2160  // already defined
#define M_SEED_VALUE                                  2867L // already defined
//Fill gaps
#define M_FILL_MODE                                   3L 
#define M_FILL_SHARP_ELEVATION                        4L 
#define M_FILL_SHARP_ELEVATION_DEPTH                  5L
#define M_FILL_THRESHOLD_X                         1674L 
#define M_FILL_THRESHOLD_Y                         1675L 
#define M_FILL_BORDER                              3050L 
#define M_X_THEN_Y                                    1L
#define M_Y_THEN_X                                 1773L 
//surface sample context
#define M_RESOLUTION                                  7L//already defined

//==============================================================================
// M3dimInquire 
// Context
#define M_INVALID                                        -1 // also in mil.h

//==============================================================================
// M3dimAllocResult ResultTypes
#define M_STATISTICS_RESULT                           MAKE_INT64(0x0001000000000000)//Already defined
#define M_PROFILE_RESULT                              3910
//==============================================================================
// M3dimGetResult ResultTypes
//Stat Result
#define M_NUMBER_OF_POINTS                        M_NUMBER //previously defined in metrol,  1009L
#define M_NUMBER_OF_POINTS_VALID                      3440
#define M_NUMBER_OF_POINTS_MISSING_DATA               3484
#define M_NUMBER_OF_POINTS_TOTAL                      3485
//Box
#define M_MIN_X                                       3382
#define M_MIN_Y                                       3383
#define M_MIN_Z                                       3384
#define M_MAX_X                                       3385
#define M_MAX_Y                                       3386
#define M_MAX_Z                                       3387
#define M_BOX_CENTER_X                                3445
#define M_BOX_CENTER_Y                                3446
#define M_BOX_CENTER_Z                                3447
#define M_SIZE_X                                      1536L       // Already defined in    milcode.h, mil.h
#define M_SIZE_Y                                      1537L       // Already defined in    milcode.h, mil.h
#define M_SIZE_Z                                      1538L // also in mil.h
//Distance
#define M_MIN_DISTANCE_TO_NEAREST_NEIGHBOR            3441
#define M_AVG_DISTANCE_TO_NEAREST_NEIGHBOR            3442
#define M_MAX_DISTANCE_TO_NEAREST_NEIGHBOR            3443
#define M_DISTANCE_TO_NEAREST_NEIGHBOR                3444
//Centroid
#define M_CENTROID_X                                  3451
#define M_CENTROID_Y                                  3452
#define M_CENTROID_Z                                  3453
//Profile result
#define M_PROFILE_TYPE                                3890
#define M_PIXEL_X                                     3891
#define M_PIXEL_Y                                     3892
#define M_PROFILE_PLANE_X                             3893
#define M_PROFILE_PLANE_Y                             3894
#define M_WORLD_X                                     3895
#define M_WORLD_Y                                     3896
#define M_WORLD_Z                                     3897
#define M_MATRIX_WORLD_TO_PROFILE_PLANE               3898
#define M_MATRIX_PROFILE_PLANE_TO_WORLD               3899
//==============================================================================
//M3dimProfile
#define M_PROFILE_DEPTH_MAP                          3900
#define M_PROFILE_POINT_CLOUD                        3901
//M3dimArith
#define M_ADD                                        0x0000L //already defined
#define M_DIST_NN_SIGNED_TAG                         0x0200L
#define M_DIST_NN_TAG                                0x0600L
#define M_REPLACE_MISSING_DATA                        3090L
#define M_SUB                                        0x0001L // Already defined in milim.h
#define M_SUB_ABS                                    0x0011L // Already defined in milim.h
#define M_VALIDITY_MAP                               0x0800L
#define M_USE_SOURCE1_SCALES                           3091L
#define M_USE_SOURCE2_SCALES                           3092L
#define M_FIT_SCALES                                   1366L
#define M_SET_WORLD_OFFSET_Z                           1367L
#define M_USE_DESTINATION_SCALES                       1335L
#define M_DIST_NN_SIZE_MASK                           0x007FL
#define M_DIST_NN_SIGNED(N)             ((((N) >> 1) & M_DIST_NN_SIZE_MASK) | M_DIST_NN_SIGNED_TAG)
#define M_DIST_NN(N)                    ((((N) >> 1) & M_DIST_NN_SIZE_MASK) | M_DIST_NN_TAG)
#define M_NO_SRC_VALID_LABEL                          0L  
#define M_ONLY_SRC1_VALID_LABEL                      85L 
#define M_ONLY_SRC2_VALID_LABEL                     170L 
#define M_BOTH_SRC_VALID_LABEL                      255L 
//Calibrated depth map
#define M_POSITIVE                                    2L // Already defined in milmeas.h
#define M_NEGATIVE                                   -2L // Already defined in milmeas.h
//M3dimProject
#define M_ACCUMULATE                                 0x200L // already defined in milcal.h
//M3dimRotate
#define M_ROTATION_AXIS_ANGLE                          2L //already defined in milcal.h
#define M_ROTATION_QUATERNION                          3L
#define M_ROTATION_YXZ                                 4L
#define M_ROTATION_X                                   7L
#define M_ROTATION_Y                                   8L
#define M_ROTATION_Z                                   9L
#define M_ROTATION_XYZ                                10L
#define M_ROTATION_XZY                                11L
#define M_ROTATION_YZX                                12L
#define M_ROTATION_ZXY                                13L
#define M_ROTATION_ZYX                                14L
#define M_ROTATION_AXIS_X                             17L
#define M_ROTATION_AXIS_Y                             18L
#define M_ROTATION_AXIS_Z                             19L     

//==============================================================================
// Pseudo Ids
#define M_MESH_CONTEXT_SMOOTHED                       (M_3DIM_PSEUDO_ID + M_MESH_SMOOTHED)  // Used by M3dimMesh
#define M_MESH_CONTEXT_ORGANIZED                      (M_3DIM_PSEUDO_ID + M_MESH_ORGANIZED)  // Used by M3dimMesh
#define M_NORMALS_CONTEXT_TREE                        (M_3DIM_PSEUDO_ID + M_TREE)  // Used by M3dimNormals
#define M_NORMALS_CONTEXT_ORGANIZED                   (M_3DIM_PSEUDO_ID + M_ORGANIZED)  // Used by M3dimNormals
#define M_NORMALS_CONTEXT_MESH                        (M_3DIM_PSEUDO_ID + M_MESH)  // Used by M3dimNormals
#define M_3DIM_STAT_PSEUDO_ID                         (M_3DIM_PSEUDO_ID +0x030000)
#define M_STAT_CONTEXT_BOUNDING_BOX                   (M_3DIM_STAT_PSEUDO_ID + M_BOUNDING_BOX)
#define M_STAT_CONTEXT_NUMBER_OF_POINTS               (M_3DIM_STAT_PSEUDO_ID + M_NUMBER_OF_POINTS)
#define M_STAT_CONTEXT_DISTANCE_TO_NEAREST_NEIGHBOR   (M_3DIM_STAT_PSEUDO_ID + M_DISTANCE_TO_NEAREST_NEIGHBOR)
#define M_STAT_CONTEXT_CENTROID                       (M_3DIM_STAT_PSEUDO_ID + M_CENTROID)

//==============================================================================
// CAPI function prototypes
MIL_3DIM_DLLFUNC MIL_ID MFTYPE M3dimAlloc(MIL_ID    SysId,
                                          MIL_INT64 ContextType,
                                          MIL_INT64 ControlFlag,
                                          MIL_ID*   Context3dimIdPtr);

MIL_3DIM_DLLFUNC MIL_ID MFTYPE M3dimAllocResult(MIL_ID    SysId,
                                                MIL_INT64 ResultType,
                                                MIL_INT64 ControlFlag,
                                                MIL_ID*   Result3dimIdPtr);

MIL_3DIM_DLLFUNC void MFTYPE M3dimFree(MIL_ID ContextOrResult3dimId);

MIL_3DIM_DLLFUNC void MFTYPE M3dimTranslate(MIL_ID     SrcContainerBufOrGeometry3dgeoId,
                                            MIL_ID     DstContainerBufOrGeometry3dgeoId,
                                            MIL_DOUBLE TranslationX,
                                            MIL_DOUBLE TranslationY,
                                            MIL_DOUBLE TranslationZ,
                                            MIL_INT64  ControlFlag);

MIL_3DIM_DLLFUNC void MFTYPE M3dimScale(MIL_ID     SrcContainerBufOrGeometry3dgeoId,
                                        MIL_ID     DstContainerBufOrGeometry3dgeoId,
                                        MIL_DOUBLE ScaleX,
                                        MIL_DOUBLE ScaleY,
                                        MIL_DOUBLE ScaleZ,
                                        MIL_DOUBLE CenterX,
                                        MIL_DOUBLE CenterY,
                                        MIL_DOUBLE CenterZ,
                                        MIL_INT64  ControlFlag);

MIL_3DIM_DLLFUNC  void MFTYPE M3dimRotate(MIL_ID     SrcContainerBufOrGeometry3dgeoId,
                                          MIL_ID     DstContainerBufOrGeometry3dgeoId,
                                          MIL_INT64  RotationType,
                                          MIL_DOUBLE Param1,
                                          MIL_DOUBLE Param2,
                                          MIL_DOUBLE Param3,
                                          MIL_DOUBLE Param4,
                                          MIL_DOUBLE CenterX,
                                          MIL_DOUBLE CenterY,
                                          MIL_DOUBLE CenterZ,
                                          MIL_INT64  ControlFlag);

MIL_3DIM_DLLFUNC void MFTYPE M3dimMatrixTransform(MIL_ID    SrcContainerBufOrGeometry3dgeoId,
                                                  MIL_ID    DstContainerBufOrGeometry3dgeoId,
                                                  MIL_ID    Matrix3dgeoId,
                                                  MIL_INT64 ControlFlag);

MIL_3DIM_DLLFUNC  void MFTYPE M3dimCrop(MIL_ID    SrcContainerBufId,
                                        MIL_ID    DstContainerBufId,
                                        MIL_ID    ImageBufOrGeometry3dgeoId,
                                        MIL_ID    Matrix3dgeoId,
                                        MIL_INT64 OrganizationType,
                                        MIL_INT64 ControlFlag);

MIL_3DIM_DLLFUNC  void MFTYPE M3dimMerge(const MIL_ID* SrcContainerBufIdArrayPtr,
                                         MIL_ID        DstContainerBufId,
                                         MIL_INT       NumContainers,
                                         MIL_ID        SubsampleContext3dimId,
                                         MIL_INT64     ControlFlag);


MIL_3DIM_DLLFUNC void MFTYPE  M3dimSample(MIL_ID     SampleContext3dimId,
                                          MIL_ID     SrcContainerBufId,
                                          MIL_ID     DstContainerBufId,
                                          MIL_INT64  ControlFlag);

MIL_3DIM_DLLFUNC void MFTYPE M3dimNormals(MIL_ID    NormalsContext3dimId,
                                          MIL_ID    SrcContainerBufId,
                                          MIL_ID    DstContainerBufId,
                                          MIL_INT64 ControlFlag);

MIL_3DIM_DLLFUNC void MFTYPE M3dimMesh(MIL_ID    MeshContext3dimId,
                                       MIL_ID    SrcContainerBufId,
                                       MIL_ID    DstContainerBufId,
                                       MIL_INT64 ControlFlag);

MIL_3DIM_DLLFUNC void MFTYPE M3dimStat(MIL_ID      StatContext3dimId,
                                       MIL_ID      ContainerOrImageBufId,
                                       MIL_ID      StatResult3dimId,
                                       MIL_INT64   ControlFlag);

MIL_3DIM_DLLFUNC void MFTYPE M3dimCopyResult(MIL_ID     SrcResult3dimId,
                                             MIL_ID     DstGeometryOrMatrix3dgeoId,
                                             MIL_INT64  CopyType,
                                             MIL_INT64  ControlFlag);

MIL_3DIM_DLLFUNC  void MFTYPE M3dimProject(MIL_ID    SrcContainerBufOrGeometry3dgeoId,
                                           MIL_ID    DepthMapImageBufId,
                                           MIL_ID    IntensityMapImageBufId,
                                           MIL_INT64 ProjectionMode,
                                           MIL_INT64 OverlapMode,
                                           MIL_INT64 Options,
                                           MIL_INT64 ControlFlag);

MIL_3DIM_DLLFUNC void MFTYPE M3dimCopy(MIL_ID     SrcDepthMapImageBufId,
                                       MIL_ID     DstGeometry3dgeoId,
                                       MIL_INT64  CopyType,
                                       MIL_INT64  ControlFlag);

MIL_3DIM_DLLFUNC void MFTYPE M3dimCalibrateDepthMap(MIL_ID     SrcContainerBufOrGeometry3dgeoId,
                                                    MIL_ID     DepthMapImageBufId,
                                                    MIL_ID     IntensityMapImageBufId,
                                                    MIL_ID     CalibrationMilObjectOrMatrix3dgeoId,
                                                    MIL_DOUBLE PixelSizeAspectRatio,
                                                    MIL_INT64  ZSign,
                                                    MIL_INT64  ControlFlag);

MIL_3DIM_DLLFUNC void MFTYPE M3dimMatrixTransformListDouble(MIL_ID            Matrix3dgeoId,
                                                            MIL_INT           NumPoints,
                                                            const MIL_DOUBLE* SrcCoordXArrayPtr,
                                                            const MIL_DOUBLE* SrcCoordYArrayPtr,
                                                            const MIL_DOUBLE* SrcCoordZArrayPtr,
                                                            MIL_DOUBLE*       DstCoordXArrayPtr,
                                                            MIL_DOUBLE*       DstCoordYArrayPtr,
                                                            MIL_DOUBLE*       DstCoordZArrayPtr,
                                                            MIL_INT64         ControlFlag);

MIL_3DIM_DLLFUNC void MFTYPE M3dimMatrixTransformListFloat(MIL_ID           Matrix3dgeoId,
                                                           MIL_INT          NumPoints,
                                                           const MIL_FLOAT* SrcCoordXArrayPtr,
                                                           const MIL_FLOAT* SrcCoordYArrayPtr,
                                                           const MIL_FLOAT* SrcCoordZArrayPtr,
                                                           MIL_FLOAT*       DstCoordXArrayPtr,
                                                           MIL_FLOAT*       DstCoordYArrayPtr,
                                                           MIL_FLOAT*       DstCoordZArrayPtr,
                                                           MIL_INT64        ControlFlag);

MIL_3DIM_DLLFUNC void MFTYPE M3dimCalculateMapSize(MIL_ID    CalculateMapSizeContext3dimId,
                                                   MIL_ID    SrcContainerBufId,
                                                   MIL_ID    AABox3dgeoId,
                                                   MIL_INT64 ControlFlag,
                                                   MIL_INT*  DepthMapSizeXPtr,
                                                   MIL_INT*  DepthMapSizeYPtr);

MIL_3DIM_DLLFUNC void MFTYPE M3dimRemovePoints(MIL_ID    SrcContainerBufId,
                                               MIL_ID    DstContainerBufId,
                                               MIL_INT64 Option,
                                               MIL_INT64 ControlFlag);

MIL_3DIM_DLLFUNC void MFTYPE M3dimArith(MIL_ID    Src1ImageBufOrGeometry3dgeoId,
                                        MIL_ID    Src2ImageBufOrGeometry3dgeoId,
                                        MIL_ID    DstImageBufId,
                                        MIL_ID    MaskBufId,
                                        MIL_INT64 Operation,
                                        MIL_INT64 SignMode,
                                        MIL_INT64 ControlFlag);

MIL_3DIM_DLLFUNC void MFTYPE M3dimFillGaps(MIL_ID     GapFillingContext3dimId,
                                           MIL_ID     DepthMapImageBufId,
                                           MIL_ID     IntensityMapImageBufId,
                                           MIL_INT64  ControlFlag);

MIL_3DIM_DLLFUNC void MFTYPE M3dimFix(MIL_ID     SrcContainerBufId,
                                      MIL_ID     DstContainerBufId,
                                      MIL_INT64  Conditions,
                                      MIL_INT64  ControlFlag,
                                      MIL_INT64* ResultPtr);

MIL_3DIM_DLLFUNC void MFTYPE M3dimProfile(MIL_ID    SrcContainerOrImageBufId,
                                          MIL_ID    ProfileResult3dimId,
                                          MIL_INT64 ProfileType,
                                          MIL_INT64 Param1,
                                          MIL_DOUBLE Param2,
                                          MIL_DOUBLE Param3,
                                          MIL_DOUBLE Param4,
                                          MIL_DOUBLE Param5,
                                          MIL_INT64  ControlFlag);

//#if M_MIL_USE_64BIT
// Prototypes for 64 bits OSs
MIL_3DIM_DLLFUNC void MFTYPE M3dimControlInt64(MIL_ID     Context3dimId,
                                               MIL_INT64  ControlType,
                                               MIL_INT64  ControlValue);
MIL_3DIM_DLLFUNC void MFTYPE M3dimControlDouble(MIL_ID     Context3dimId,
                                                MIL_INT64  ControlType,
                                                MIL_DOUBLE ControlValue);

MIL_3DIM_DLLFUNC MIL_INT64 MFTYPE M3dimInquire(MIL_ID    Context3dimId,
                                               MIL_INT64 InquireType,
                                               void*     UserVarPtr);

MIL_3DIM_DLLFUNC MIL_DOUBLE MFTYPE M3dimGetResult(MIL_ID    Result3dimId,
                                                  MIL_INT64 ResultType,
                                                  void*     ResultArrayPtr);

#if M_MIL_USE_UNICODE
MIL_3DIM_DLLFUNC void MFTYPE M3dimSaveA(MIL_CONST_TEXTA_PTR FileName,
                                        MIL_ID              Context3dimId,
                                        MIL_INT64           ControlFlag);

MIL_3DIM_DLLFUNC MIL_ID MFTYPE M3dimRestoreA(MIL_CONST_TEXTA_PTR FileName,
                                             MIL_ID              SysId,
                                             MIL_INT64           ControlFlag,
                                             MIL_ID*             Context3dimIdPtr);

MIL_3DIM_DLLFUNC void MFTYPE M3dimStreamA(MIL_TEXTA_PTR MemPtrOrFileName,
                                          MIL_ID        SysId,
                                          MIL_INT64     Operation,
                                          MIL_INT64     StreamType,
                                          MIL_DOUBLE    Version,
                                          MIL_INT64     ControlFlag,
                                          MIL_ID*       Context3dimIdPtr,
                                          MIL_INT*      SizeByteVarPtr);



MIL_3DIM_DLLFUNC void MFTYPE M3dimSaveW(MIL_CONST_TEXTW_PTR FileName,
                                        MIL_ID              Context3dimId,
                                        MIL_INT64           ControlFlag);

MIL_3DIM_DLLFUNC MIL_ID MFTYPE M3dimRestoreW(MIL_CONST_TEXTW_PTR FileName,
                                             MIL_ID              SysId,
                                             MIL_INT64           ControlFlag,
                                             MIL_ID*             Context3dimIdPtr);

MIL_3DIM_DLLFUNC void MFTYPE M3dimStreamW(MIL_TEXTW_PTR MemPtrOrFileName,
                                          MIL_ID        SysId,
                                          MIL_INT64     Operation,
                                          MIL_INT64     StreamType,
                                          MIL_DOUBLE    Version,
                                          MIL_INT64     ControlFlag,
                                          MIL_ID*       Context3dimIdPtr,
                                          MIL_INT*      SizeByteVarPtr);

#if M_MIL_UNICODE_API
#define M3dimSave               M3dimSaveW
#define M3dimRestore            M3dimRestoreW
#define M3dimStream             M3dimStreamW
#else
#define M3dimSave               M3dimSaveA
#define M3dimRestore            M3dimRestoreA
#define M3dimStream             M3dimStreamA
#endif //M_MIL_UNICODE_API

#else

MIL_3DIM_DLLFUNC void MFTYPE   M3dimSave(MIL_CONST_TEXT_PTR FileName,
                                         MIL_ID             Context3dimId,
                                         MIL_INT64          ControlFlag);

MIL_3DIM_DLLFUNC MIL_ID MFTYPE M3dimRestore(MIL_CONST_TEXT_PTR FileName,
                                            MIL_ID             SysId,
                                            MIL_INT64          ControlFlag,
                                            MIL_ID*            Context3dimIdPtr);

MIL_3DIM_DLLFUNC void MFTYPE   M3dimStream(MIL_TEXT_PTR MemPtrOrFileName,
                                           MIL_ID       SysId,
                                           MIL_INT64    Operation,
                                           MIL_INT64    StreamType,
                                           MIL_DOUBLE   Version,
                                           MIL_INT64    ControlFlag,
                                           MIL_ID*      Context3dimIdPtr,
                                           MIL_INT*     SizeByteVarPtr);

#endif //M_MIL_USE_UNICODE
#ifdef __cplusplus
inline bool In3dimInquireDoubleRange(MIL_INT64 InquireType)
   {
   if(M_NB_ELEMENTS_BIT_SET(InquireType))
      {
      return false;
      }

   switch(M_STRIP_INQ_COMBOFLAGS(InquireType))
      {
      case M_ALLOCATION_FAILURE_REAL_TEST_FLAG:
      //mesh context
      case M_MAXIMUM_ORIENTATION_ANGLE_DIFFERENCE:
      case M_MAX_DISTANCE_TO_SOURCE:
      case M_MAX_DISTANCE:
         //normal context
      case M_DIRECTION_REFERENCE_X:
      case M_DIRECTION_REFERENCE_Y:
      case M_DIRECTION_REFERENCE_Z:
      case M_NEIGHBORHOOD_DISTANCE:
         //map size context
      case M_PIXEL_ASPECT_RATIO :
      case M_PIXEL_SIZE_X:
      case M_PIXEL_SIZE_Y:
      case M_FIRST_PERCENTILE:
      case M_SECOND_PERCENTILE:
         //stat context
      case M_BOUNDING_BOX_OUTLIER_RATIO_X:
      case M_BOUNDING_BOX_OUTLIER_RATIO_Y:
      case M_BOUNDING_BOX_OUTLIER_RATIO_Z:
      case M_BOUNDING_BOX_SECURITY_FACTOR_X:
      case M_BOUNDING_BOX_SECURITY_FACTOR_Y:
      case M_BOUNDING_BOX_SECURITY_FACTOR_Z:
       //subsample context
      case M_FRACTION_OF_POINTS:
      case M_GRID_SIZE_X:
      case M_GRID_SIZE_Y:
      case M_GRID_SIZE_Z:
      //case M_NEIGHBORHOOD_DISTANCE: //Defined above
      case M_DISTINCT_ANGLE_DIFFERENCE:
      //fill gaps
      case M_FILL_THRESHOLD_X:
      case M_FILL_THRESHOLD_Y:
      //case M_FILL_SHARP_ELEVATION_DEPTH: same value as M_APECT_RATIO
      //surface sample
      case M_RESOLUTION:
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

inline bool In3dimInquireInt64Range(MIL_INT64 InquireType)
   {
   UNREFERENCED_PARAMETER(InquireType);
   return false;
   }
inline bool M3dimInquireMustHaveUserPtr(MIL_INT64 InquireType)
   {
   const MIL_INT64 ForcedDataType = MinquireOverrides(M_STRIP_HLVLDATATYPE(InquireType), M_TYPE_MIL_INT);
   if(ForcedDataType != 0)
      {
      return false;// ForcedDataType == M_TYPE_DOUBLE;
      }
   return In3dimInquireDoubleRange(InquireType);
   }
inline bool In3dimResultDoubleRange(MIL_INT64 InquireType)
   {
   if(M_NB_ELEMENTS_BIT_SET(InquireType))
      {
      return false;
      }

   switch(M_STRIP_INQ_COMBOFLAGS(InquireType))
      {
     //container stat result
      //M_BOUNDING_BOX
      case M_MIN_X:
      case M_MIN_Y:
      case M_MIN_Z:
      case M_MAX_X:
      case M_MAX_Y:
      case M_MAX_Z:
      case M_BOX_CENTER_X:
      case M_BOX_CENTER_Y:
      case M_BOX_CENTER_Z:
      case M_SIZE_X:
      case M_SIZE_Y:
      case M_SIZE_Z:
      //
      case M_MIN_DISTANCE_TO_NEAREST_NEIGHBOR:
      case M_MAX_DISTANCE_TO_NEAREST_NEIGHBOR:
      case M_AVG_DISTANCE_TO_NEAREST_NEIGHBOR:
         //
      case M_CENTROID_X:
      case M_CENTROID_Y:
      case M_CENTROID_Z:
      case M_PIXEL_X:
      case M_PIXEL_Y:
      case M_PROFILE_PLANE_X:
      case M_PROFILE_PLANE_Y:
      case M_WORLD_X:
      case M_WORLD_Y:
      case M_WORLD_Z:
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
//MIL_INT64
inline bool In3dimResultInt64Range(MIL_INT64 InquireType)
   {
   UNREFERENCED_PARAMETER(InquireType);
   if(M_NB_ELEMENTS_BIT_SET(InquireType))
      {
      return false;
      }
   return false;
   }
inline bool M3dimResultMustHaveUserPtr(MIL_INT64 ResultType)
   {
   const MIL_INT64 ForcedDataType = MinquireOverrides(M_STRIP_HLVLDATATYPE(ResultType), M_TYPE_MIL_INT);
   if(ForcedDataType != 0)
      {
      return false;// ForcedDataType == M_TYPE_MIL_INT64;
      }

   return In3dimResultInt64Range(ResultType);
   }
#endif // __cplusplus
/* C++ directive if needed */
#ifdef __cplusplus
}
#endif
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
//C++ overloads
inline void M3dimMatrixTransformList(MIL_ID            Matrix3dgeoId,
                                     MIL_INT           NumPoints,
                                     const MIL_DOUBLE* SrcCoordXArrayPtr,
                                     const MIL_DOUBLE* SrcCoordYArrayPtr,
                                     const MIL_DOUBLE* SrcCoordZArrayPtr,
                                     MIL_DOUBLE*       DstCoordXArrayPtr,
                                     MIL_DOUBLE*       DstCoordYArrayPtr,
                                     MIL_DOUBLE*       DstCoordZArrayPtr,
                                     MIL_INT64         ControlFlag)
   {
   return M3dimMatrixTransformListDouble(Matrix3dgeoId,
                                         NumPoints,
                                         SrcCoordXArrayPtr,
                                         SrcCoordYArrayPtr,
                                         SrcCoordZArrayPtr,
                                         DstCoordXArrayPtr,
                                         DstCoordYArrayPtr,
                                         DstCoordZArrayPtr,
                                         ControlFlag);
   }
inline void M3dimMatrixTransformList(MIL_ID           Matrix3dgeoId,
                                     MIL_INT          NumPoints,
                                     const MIL_FLOAT* SrcCoordXArrayPtr,
                                     const MIL_FLOAT* SrcCoordYArrayPtr,
                                     const MIL_FLOAT* SrcCoordZArrayPtr,
                                     MIL_FLOAT*       DstCoordXArrayPtr,
                                     MIL_FLOAT*       DstCoordYArrayPtr,
                                     MIL_FLOAT*       DstCoordZArrayPtr,
                                     MIL_INT64        ControlFlag)
   {
   return M3dimMatrixTransformListFloat(Matrix3dgeoId,
                                        NumPoints,
                                        SrcCoordXArrayPtr,
                                        SrcCoordYArrayPtr,
                                        SrcCoordZArrayPtr,
                                        DstCoordXArrayPtr,
                                        DstCoordYArrayPtr,
                                        DstCoordZArrayPtr,
                                        ControlFlag);
   }
inline void MFTYPE M3dimStreamCpp(MilStreamParam MemPtrOrFileName,
                                  MIL_ID         SysId,
                                  MIL_INT64      Operation,
                                  MIL_INT64      StreamType,
                                  MIL_DOUBLE     Version,
                                  MIL_INT64      ControlFlag,
                                  MIL_ID*        Context3dimIdPtr,
                                  MIL_INT*       SizeByteVarPtr)
   {
   M3dimStream(MemPtrOrFileName.m_Param, SysId, Operation, StreamType, Version, ControlFlag, Context3dimIdPtr, SizeByteVarPtr);
   }

#undef  M3dimStream
#define M3dimStream M3dimStreamCpp
#else
#define M3dimMatrixTransformList M3dimMatrixTransformListDouble
#endif // __cplusplus


//==============================================================================

#ifdef __cplusplus
inline MIL_INT64 M3dimInquireDataType(MIL_INT64 InquireType)
   {
   const MIL_INT64 ForcedDataType = MinquireOverrides(InquireType, M_TYPE_MIL_INT);
   if(ForcedDataType != 0)
      return ForcedDataType;

   if(In3dimInquireDoubleRange(InquireType))
      return M_TYPE_DOUBLE;

   if(In3dimInquireInt64Range(InquireType))
      return M_TYPE_MIL_INT64;

   return M_TYPE_MIL_INT;
   }
//result
inline MIL_INT64 M3dimResultDataType(MIL_INT64 InquireType)
   {
   const MIL_INT64 ForcedDataType = MinquireOverrides(InquireType, M_TYPE_MIL_INT);
   if(ForcedDataType != 0)
      return ForcedDataType;

   if(In3dimResultDoubleRange(InquireType))
      return M_TYPE_DOUBLE;

   if(In3dimResultInt64Range(InquireType))
      return M_TYPE_MIL_INT64;

   return M_TYPE_MIL_INT;
   }
// ----------------------------------------------------------
// M3dimInquire
#if M_MIL_USE_SAFE_TYPE

inline MIL_INT64 MFTYPE M3dimInquireSafeType(MIL_ID Context3dimId, MIL_INT64  InquireType, int UserVarPtr)
   {
   bool MustHaveUserPointer = M3dimInquireMustHaveUserPtr(InquireType);

   if(UserVarPtr)
      SafeTypeError(MIL_TEXT("M3dimInquire"));

   if(!UserVarPtr && MustHaveUserPointer)
      SafeTypeError(MIL_TEXT("M3dimInquire"), MIL_TEXT("The specified InquireType requires a non-null output pointer."));


   return M3dimInquire(Context3dimId, InquireType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT64 MFTYPE M3dimInquireSafeType(MIL_ID Context3dimId, MIL_INT64  InquireType, std::nullptr_t)
   {
   bool MustHaveUserPointer = M3dimInquireMustHaveUserPtr(InquireType);

   if(MustHaveUserPointer)
      SafeTypeError(MIL_TEXT("M3dimInquire"), MIL_TEXT("The specified InquireType requires a non-null output pointer."));

   return M3dimInquire(Context3dimId, InquireType, NULL);
   }
#endif // M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT64 MFTYPE M3dimInquireSafeTypeExecute(MIL_ID Context3dimId, MIL_INT64  InquireType, void  *UserVarPtr, MIL_INT64  GivenType)
   {
   MIL_INT64  RequiredType = M3dimInquireDataType(InquireType);
   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if(RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("M3dimInquire"));

   return M3dimInquire(Context3dimId, InquireType, UserVarPtr);
   }
inline MIL_INT64 MFTYPE M3dimInquireUnsafe  (MIL_ID ContextOrResult3dimId, MIL_INT64 InquireType   , void*     UserVarPtr) { return M3dimInquire(ContextOrResult3dimId, InquireType, UserVarPtr); }
inline MIL_INT64 MFTYPE M3dimInquireSafeType(MIL_ID ContextOrResult3dimId, MIL_INT64 InquireType , MIL_INT8*   UserVarPtr) { return M3dimInquireSafeTypeExecute(ContextOrResult3dimId, InquireType, UserVarPtr, M_TYPE_CHAR); }
inline MIL_INT64 MFTYPE M3dimInquireSafeType(MIL_ID ContextOrResult3dimId, MIL_INT64  InquireType, MIL_INT16*  UserVarPtr) { return M3dimInquireSafeTypeExecute(ContextOrResult3dimId, InquireType, UserVarPtr, M_TYPE_SHORT); }
inline MIL_INT64 MFTYPE M3dimInquireSafeType(MIL_ID ContextOrResult3dimId, MIL_INT64 InquireType , MIL_INT32*  UserVarPtr) { return M3dimInquireSafeTypeExecute(ContextOrResult3dimId, InquireType, UserVarPtr, M_TYPE_MIL_INT32); }
inline MIL_INT64 MFTYPE M3dimInquireSafeType(MIL_ID ContextOrResult3dimId, MIL_INT64 InquireType , MIL_INT64*  UserVarPtr) { return M3dimInquireSafeTypeExecute(ContextOrResult3dimId, InquireType, UserVarPtr, M_TYPE_MIL_INT64); }
inline MIL_INT64 MFTYPE M3dimInquireSafeType(MIL_ID ContextOrResult3dimId, MIL_INT64 InquireType , MIL_FLOAT*  UserVarPtr) { return M3dimInquireSafeTypeExecute(ContextOrResult3dimId, InquireType, UserVarPtr, M_TYPE_FLOAT); }
inline MIL_INT64 MFTYPE M3dimInquireSafeType(MIL_ID ContextOrResult3dimId, MIL_INT64 InquireType , MIL_DOUBLE* UserVarPtr) { return M3dimInquireSafeTypeExecute(ContextOrResult3dimId, InquireType, UserVarPtr, M_TYPE_MIL_DOUBLE); }
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline MIL_INT64 MFTYPE M3dimInquireSafeType(MIL_ID ContextOrResult3dimId, MIL_INT64 InquireType, MIL_UINT8*  UserVarPtr) { return M3dimInquireSafeTypeExecute(ContextOrResult3dimId, InquireType, UserVarPtr, M_TYPE_CHAR); }
inline MIL_INT64 MFTYPE M3dimInquireSafeType(MIL_ID ContextOrResult3dimId, MIL_INT64 InquireType, MIL_UINT16* UserVarPtr) { return M3dimInquireSafeTypeExecute(ContextOrResult3dimId, InquireType, UserVarPtr, M_TYPE_SHORT); }
inline MIL_INT64 MFTYPE M3dimInquireSafeType(MIL_ID ContextOrResult3dimId, MIL_INT64 InquireType, MIL_UINT32* UserVarPtr) { return M3dimInquireSafeTypeExecute(ContextOrResult3dimId, InquireType, UserVarPtr, M_TYPE_MIL_INT32); }
inline MIL_INT64 MFTYPE M3dimInquireSafeType(MIL_ID ContextOrResult3dimId, MIL_INT64 InquireType, MIL_UINT64* UserVarPtr) { return M3dimInquireSafeTypeExecute(ContextOrResult3dimId, InquireType, UserVarPtr, M_TYPE_MIL_INT64); }
#endif
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T
inline MIL_INT64 MFTYPE M3dimInquireSafeType(MIL_ID ContextOrResult3dimId, MIL_INT64  InquireType, wchar_t*    UserVarPtr) { return M3dimInquireSafeTypeExecute(ContextOrResult3dimId, InquireType, UserVarPtr, M_TYPE_STRING); }//or M_TYPE_SHORT??
#endif

#define M3dimInquire           M3dimInquireSafeType
#else // #if M_MIL_USE_SAFE_TYPE
#define M3dimInquireUnsafe     M3dimInquire
#endif // #if M_MIL_USE_SAFE_TYPE


#if M_MIL_USE_SAFE_TYPE
// -------------------------------------------------------------------------
// M3dimGetResult safe type definitions
// 
inline MIL_DOUBLE MFTYPE M3dimGetResultSafeType(MIL_ID Result3dimId, MIL_INT64 ResultType, int ResultPtr)
   {
   bool MustHaveUserPointer = M3dimResultMustHaveUserPtr(ResultType);
     
   if(ResultPtr)
      SafeTypeError(MIL_TEXT("M3dimGetResult"));

   if(!ResultPtr && MustHaveUserPointer)
      SafeTypeError(MIL_TEXT("M3dimGetResult"), MIL_TEXT("The specified ResultType requires a non-null output pointer."));

   return M3dimGetResult(Result3dimId, ResultType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_DOUBLE MFTYPE M3dimGetResultSafeType(MIL_ID Result3dimId, MIL_INT64 ResultType, std::nullptr_t)
   {
   bool MustHaveUserPointer = M3dimResultMustHaveUserPtr(ResultType);

   if(MustHaveUserPointer)
      SafeTypeError(MIL_TEXT("M3dimGetResult"), MIL_TEXT("The specified ResultType must have a non-null output pointer."));
   return M3dimGetResult(Result3dimId, ResultType, NULL);
   }
#endif
inline MIL_DOUBLE M3dimGetResultSafeTypeExecute(MIL_ID Result3dimId, MIL_INT64 ResultType, void* ResultArrayPtr, MIL_INT64 GivenType)
   {
   MIL_INT64  RequiredType = M3dimResultDataType(ResultType);

   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if(RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("M3dimGetResult"));

   return M3dimGetResult(Result3dimId, ResultType, ResultArrayPtr);
   }
//=========================================================
// See milos.h for explanation about these functions.
//=========================================================

// -------------------------------------------------------------------------
// M3dimGetResult safe type 
inline MIL_DOUBLE MFTYPE M3dimGetResultUnsafe  (MIL_ID Result3dimId, MIL_INT64 ResultType  , void*      ResultArrayPtr) { return M3dimGetResult(Result3dimId, ResultType, ResultArrayPtr); }
inline MIL_DOUBLE MFTYPE M3dimGetResultSafeType(MIL_ID Result3dimId, MIL_INT64 ResultType, MIL_INT8*    ResultArrayPtr) { return M3dimGetResultSafeTypeExecute(Result3dimId, ResultType, ResultArrayPtr, M_TYPE_CHAR); }
inline MIL_DOUBLE MFTYPE M3dimGetResultSafeType(MIL_ID Result3dimId, MIL_INT64 ResultType, MIL_INT16*   ResultArrayPtr) { return M3dimGetResultSafeTypeExecute(Result3dimId, ResultType, ResultArrayPtr, M_TYPE_SHORT); }
inline MIL_DOUBLE MFTYPE M3dimGetResultSafeType(MIL_ID Result3dimId, MIL_INT64 ResultType, MIL_INT32*   ResultArrayPtr) { return M3dimGetResultSafeTypeExecute(Result3dimId, ResultType, ResultArrayPtr, M_TYPE_MIL_INT32); }
inline MIL_DOUBLE MFTYPE M3dimGetResultSafeType(MIL_ID Result3dimId, MIL_INT64 ResultType, MIL_INT64*   ResultArrayPtr) { return M3dimGetResultSafeTypeExecute(Result3dimId, ResultType, ResultArrayPtr, M_TYPE_MIL_INT64); }
inline MIL_DOUBLE MFTYPE M3dimGetResultSafeType(MIL_ID Result3dimId, MIL_INT64 ResultType, float*       ResultArrayPtr) { return M3dimGetResultSafeTypeExecute(Result3dimId, ResultType, ResultArrayPtr, M_TYPE_FLOAT); }
inline MIL_DOUBLE MFTYPE M3dimGetResultSafeType(MIL_ID Result3dimId, MIL_INT64 ResultType, MIL_DOUBLE*  ResultArrayPtr) { return M3dimGetResultSafeTypeExecute(Result3dimId, ResultType, ResultArrayPtr, M_TYPE_MIL_DOUBLE); }

#if M_MIL_UNICODE_API
inline MIL_DOUBLE MFTYPE M3dimGetResultSafeType(MIL_ID Result3dimId, MIL_INT64 ResultType, MIL_TEXT_PTR ResultArrayPtr) { return M3dimGetResultSafeTypeExecute(Result3dimId, ResultType, ResultArrayPtr, M_TYPE_STRING); }
#endif

#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline MIL_DOUBLE MFTYPE M3dimGetResultSafeType(MIL_ID Result3dimId, MIL_INT64 ResultType, MIL_UINT8*   ResultArrayPtr) { return M3dimGetResultSafeTypeExecute(Result3dimId, ResultType, ResultArrayPtr, M_TYPE_CHAR); }
inline MIL_DOUBLE MFTYPE M3dimGetResultSafeType(MIL_ID Result3dimId, MIL_INT64 ResultType, MIL_UINT16* ResultArrayPtr)  { return M3dimGetResultSafeTypeExecute(Result3dimId, ResultType, ResultArrayPtr, M_TYPE_SHORT); }
inline MIL_DOUBLE MFTYPE M3dimGetResultSafeType(MIL_ID Result3dimId, MIL_INT64 ResultType, MIL_UINT32* ResultArrayPtr)  { return M3dimGetResultSafeTypeExecute(Result3dimId, ResultType, ResultArrayPtr, M_TYPE_MIL_INT32); }
inline MIL_DOUBLE MFTYPE M3dimGetResultSafeType(MIL_ID Result3dimId, MIL_INT64 ResultType, MIL_UINT64* ResultArrayPtr)  { return M3dimGetResultSafeTypeExecute(Result3dimId, ResultType, ResultArrayPtr, M_TYPE_MIL_INT64); }
#endif
//------------------------------
// Safetype functions assignment
#define M3dimGetResult            M3dimGetResultSafeType
#else // #if M_MIL_USE_SAFE_TYPE
#define M3dimGetResultUnsafe            M3dimGetResult
#endif // #if M_MIL_USE_SAFE_TYPE

#endif // __cplusplus

//#if M_MIL_USE_64BIT
#ifdef __cplusplus

//=========================================================
// M3dimControl function overloads when compiling c++ files
//=========================================================
template <typename T>
inline void M3dimControl(MIL_ID Context3dimId,  MIL_INT64 ControlType, T ControlValue)
   { M3dimControlInt64(Context3dimId,  ControlType, ControlValue); }

inline void M3dimControl(MIL_ID Context3dimId,  MIL_INT64 ControlType, float ControlValue)
   { M3dimControlDouble(Context3dimId,  ControlType, ControlValue); }

inline void M3dimControl(MIL_ID Context3dimId,  MIL_INT64 ControlType, MIL_DOUBLE ControlValue)
   { M3dimControlDouble(Context3dimId,  ControlType, ControlValue); }
#else // __cplusplus
//=========================================================
// For C file, call the default function, i.e. Double one
//=========================================================
#define M3dimControl            M3dimControlDouble
#endif // __cplusplus
//#endif // M_MIL_USE_64BIT
// ----------------------------------------------------------
// Overload for std::vector.
#if defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR
template <typename UserType>
inline MIL_INT64 MFTYPE M3dimInquire(MIL_ID Context3dimId, MIL_INT64  InquireType, std::vector<UserType> &UserVarPtr)
   {
   // If the given MIL data type is not the same as the SrcType, change it to the correct one
   // and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(InquireType) != 0)
      {
      SafeTypeError(MIL_TEXT("M3dimInquire"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   InquireType = M_STRIP_HLVLDATATYPE(InquireType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   M3dimInquire(Context3dimId, M_STRIP_HLVLDATATYPE(InquireType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   UserVarPtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      return M3dimInquire(Context3dimId, InquireType, &UserVarPtr[0]);
      }
   return 0;
   }
template <typename UserType>
inline MIL_DOUBLE MFTYPE M3dimGetResult(MIL_ID Result3dimId, MIL_INT64  ResultType, std::vector<UserType> &ResultArrayPtr)
   {
   //! If the given MIL data type is not the same as the SrcType, change it to the correct one
   //! and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(ResultType) != 0)
      {
      SafeTypeError(MIL_TEXT("M3dimGetResult"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   ResultType = M_STRIP_HLVLDATATYPE(ResultType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   M3dimGetResult(Result3dimId, M_STRIP_HLVLDATATYPE(ResultType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   ResultArrayPtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      M3dimGetResult(Result3dimId, ResultType, &ResultArrayPtr[0]);
      }
   return 0.0;
   }
// ----------------------------------------------------------
// Overloads for std::vector in  M3dimMerge. 
inline void MFTYPE  M3dimMerge(const std::vector<MIL_ID>& SrcContainerBufIdArrayPtr,
                               MIL_ID                     DstContainerBufId,
                               MIL_INT                    NumContainers,
                               MIL_ID                     SubsampleContext3dimId,
                               MIL_INT64                  ControlFlag)
   {
#if M_MIL_USE_SAFE_TYPE
   if(SrcContainerBufIdArrayPtr.empty())
      {
      SafeTypeError(MIL_TEXT("M3dimMerge"), MIL_TEXT("The input vectors cannot be empty."));
      }
   if(NumContainers <= 0)
      {
      SafeTypeError(MIL_TEXT("M3dimMerge"), MIL_TEXT("NumContainers parameter must be greater than zero."));
      }
   if(NumContainers > (MIL_INT)SrcContainerBufIdArrayPtr.size() && NumContainers != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("M3dimMerge"), MIL_TEXT("NumContainers parameter must be smaller or equal (M_DEFAULT) to the size of input vector."));
      }
#endif

   if(NumContainers == M_DEFAULT || NumContainers > (MIL_INT)SrcContainerBufIdArrayPtr.size())
      {
      NumContainers = (MIL_INT)SrcContainerBufIdArrayPtr.size();
      }

   M3dimMerge(&SrcContainerBufIdArrayPtr[0],
              DstContainerBufId,
              NumContainers,
              SubsampleContext3dimId,
              ControlFlag);
   }
// Overloads for std::vector in M3dimStream.
inline void MFTYPE M3dimStream(std::vector<MIL_UINT8> &MemPtrOrFileName,
                               MIL_ID                 SysId,
                               MIL_INT64              Operation,
                               MIL_INT64              StreamType,
                               MIL_DOUBLE             Version,
                               MIL_INT64              ControlFlag,
                               MIL_ID*                Context3dimIdPtr,
                               MIL_INT*               SizeByteVarPtr)
   {
   MxxxStreamForStdVector(MemPtrOrFileName,
                          SysId,
                          Operation,
                          StreamType,
                          Version,
                          ControlFlag,
                          Context3dimIdPtr,
                          SizeByteVarPtr,
                          M3dimStream);
   }
template <typename T>
inline void MFTYPE M3dimMatrixTransformList(MIL_ID                Matrix3dgeoId,
                                            MIL_INT               NumPoints,
                                            const std::vector<T>& SrcCoordXArrayPtr,
                                            const std::vector<T>& SrcCoordYArrayPtr,
                                            const std::vector<T>& SrcCoordZArrayPtr,
                                            std::vector<T>&       DstCoordXArrayPtr,
                                            std::vector<T>&       DstCoordYArrayPtr,
                                            std::vector<T>&       DstCoordZArrayPtr,
                                            MIL_INT64             ControlFlag)
   {
#if M_MIL_USE_SAFE_TYPE
   if(SrcCoordXArrayPtr.size() != SrcCoordYArrayPtr.size() || SrcCoordXArrayPtr.size() != SrcCoordZArrayPtr.size())
      {
      SafeTypeError(MIL_TEXT("M3dimMatrixTransformList"), MIL_TEXT("The input vectors must have the same size."));
      }
   if(SrcCoordXArrayPtr.empty())
      {
      SafeTypeError(MIL_TEXT("M3dimMatrixTransformList"), MIL_TEXT("The input vectors cannot be empty."));
      }
   if(NumPoints <= 0)
      {
      SafeTypeError(MIL_TEXT("M3dimMatrixTransformList"), MIL_TEXT("NumContainers parameter must be greater than zero."));
      }
   if(NumPoints > (MIL_INT)SrcCoordXArrayPtr.size() && NumPoints != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("M3dimMatrixTransformList"), MIL_TEXT("NumPoints parameter must be smaller or equal (M_DEFAULT) to the size of input vector."));
      }
#endif
   if(NumPoints == M_DEFAULT || NumPoints > (MIL_INT)SrcCoordXArrayPtr.size())
      {
      NumPoints = (MIL_INT)SrcCoordXArrayPtr.size();
      }

   DstCoordXArrayPtr.resize(NumPoints);
   DstCoordYArrayPtr.resize(NumPoints);
   DstCoordZArrayPtr.resize(NumPoints);

   M3dimMatrixTransformList(Matrix3dgeoId,
                            NumPoints,
                            &SrcCoordXArrayPtr[0],
                            &SrcCoordYArrayPtr[0],
                            &SrcCoordZArrayPtr[0],
                            &DstCoordXArrayPtr[0],
                            &DstCoordYArrayPtr[0],
                            &DstCoordZArrayPtr[0],
                            ControlFlag);
   }
#endif // defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR
#if M_MIL_USE_STRING
/***************************************************************************/
/* 3dim MODULE                                                              */
/***************************************************************************/
#if M_MIL_USE_UNICODE
#if M_MIL_UNICODE_API

inline void MFTYPE M3dimSaveW(const MIL_STRING& FileName, MIL_ID Context3dimId, MIL_INT64 ControlFlag)
   {
   return M3dimSaveW(FileName.c_str(), Context3dimId, ControlFlag);
   }

inline MIL_ID MFTYPE M3dimRestoreW(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* Context3dimIdPtr)
   {
   return M3dimRestoreW(FileName.c_str(), SysId, ControlFlag, Context3dimIdPtr);
   }

#else // M_MIL_UNICODE_API
inline void MFTYPE M3dimSaveA(const MIL_STRING& FileName, MIL_ID Context3dimId, MIL_INT64 ControlFlag)
   {
   return M3dimSaveA(FileName.c_str(), Context3dimId, ControlFlag);
   }

inline MIL_ID MFTYPE M3dimRestoreA(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* Context3dimIdPtr)
   {
   return M3dimRestoreA(FileName.c_str(), SysId, ControlFlag, Context3dimIdPtr);
   }

//inline void MFTYPE M3dimStreamA(const MIL_STRING& MemPtrOrFileName, MIL_ID SysId, MIL_INT64 Operation, MIL_INT64 StreamType,
//                               MIL_DOUBLE Version, MIL_INT64 ControlFlag, MIL_ID* Context3dimId, MIL_INT* SizeByteVarPtr)
//   {
//   M3dimStreamA((MIL_TEXT_PTR)MemPtrOrFileName.c_str(), SysId, Operation, StreamType, Version, ControlFlag, Context3dimId, SizeByteVarPtr);
//   }
#endif /* M_MIL_UNICODE_API*/

#else // M_MIL_USE_UNICODE
inline void MFTYPE M3dimSave(const MIL_STRING& FileName, MIL_ID Context3dimId, MIL_INT64 ControlFlag)
   {
   return M3dimSave(FileName.c_str(), Context3dimId, ControlFlag);
   }

inline MIL_ID MFTYPE M3dimRestore(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* Context3dimIdPtr)
   {
   return M3dimRestore(FileName.c_str(), SysId, ControlFlag, Context3dimIdPtr);
   }

//inline void MFTYPE M3dimStream(const MIL_STRING& MemPtrOrFileName, MIL_ID SysId, MIL_INT64 Operation, MIL_INT64 StreamType,
//                              MIL_DOUBLE Version, MIL_INT64 ControlFlag, MIL_ID* Context3dimId, MIL_INT* SizeByteVarPtr)
//   {
//   M3dimStream((MIL_TEXT_PTR)MemPtrOrFileName.c_str(), SysId, Operation, StreamType, Version, ControlFlag, Context3dimId, SizeByteVarPtr);
//   }
#endif /* M_MIL_USE_UNICODE */

#if M_MIL_USE_SAFE_TYPE

#if M_MIL_UNICODE_API

inline MIL_DOUBLE MFTYPE M3dimGetResultSafeType(MIL_ID Result3dimId,  MIL_INT64 ResultType, MIL_STRING   &ResultArrayPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((ResultType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("M3dimGetResult"), MIL_TEXT("Result Type not supported with MIL_STRING."));
      }
#endif

   MIL_INT InternalStringSize = 0;

   M3dimGetResultSafeType(Result3dimId,(ResultType & (~M_HLVLDATATYPE_MASK)) + M_STRING_SIZE + M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      if(ResultArrayPtr.size() < (MIL_UINT)InternalStringSize)
         {
         ResultArrayPtr.resize((MIL_UINT)InternalStringSize);
         }
      }

   M3dimGetResultSafeTypeExecute(Result3dimId,  ResultType, &ResultArrayPtr[0], M_TYPE_STRING);
   return 0.0;
   }
#endif /* M_MIL_UNICODE_API */
#else
//M3dimGetResult is only defined in UNICODE
#if M_MIL_UNICODE_API
inline MIL_DOUBLE MFTYPE M3dimGetResult(MIL_ID Result3dimId, MIL_INT64 ResultType, MIL_STRING   &ResultArrayPtr)
   {
   MIL_INT InternalStringSize = 0;

   //Inquire the byte content
   M3dimGetResult(Result3dimId,  (ResultType & (~M_HLVLDATATYPE_MASK)) + M_STRING_SIZE + M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ResultArrayPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      M3dimGetResult(Result3dimId, ResultType, &ResultArrayPtr[0]);
      ResultArrayPtr.resize(InternalStringSize);
      }
   return 0.0;
   }

#endif
#endif
#endif /* M_MIL_USE_STRING*/

////////////////////////////////////////////////////////////////////////////////
// MIL_UNIQUE_ID support

#if M_MIL_USE_MIL_UNIQUE_ID

#if M_MIL_USE_SAFE_TYPE
template <> inline bool MilIsCorrectObjectType<&M3dimFree>(MIL_INT64 ObjectType)
   {
   return (ObjectType & ~M_USER_DEFINE_LOW_ATTRIBUTE) == M_3DIM_OBJECT;
   }
#endif

typedef MIL_UNIQUE_ID<&M3dimFree> MIL_UNIQUE_3DIM_ID;

#if M_MIL_USE_MOVE_SEMANTICS

inline MIL_UNIQUE_3DIM_ID M3dimAlloc(MIL_ID SysId, MIL_INT64 ObjectType, MIL_INT64 InitFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DIM_ID(M3dimAlloc(SysId, ObjectType, InitFlag, M_NULL));
   }
inline MIL_UNIQUE_3DIM_ID M3dimAllocResult(MIL_ID SysId, MIL_INT64 ResultType, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DIM_ID(M3dimAllocResult(SysId, ResultType, ControlFlag, M_NULL));
   }
inline MIL_UNIQUE_3DIM_ID M3dimRestore(MIL_CONST_TEXT_PTR FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DIM_ID(M3dimRestore(FileName, SysId, ControlFlag, M_NULL));
   }
#if M_MIL_USE_STRING
inline MIL_UNIQUE_3DIM_ID M3dimRestore(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DIM_ID(M3dimRestore(FileName.c_str(), SysId, ControlFlag, M_NULL));
   }
#endif // M_MIL_USE_STRING
template <MilFreeFuncType FreeFunc> inline void M3dimFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

inline void M3dimStream(MilStreamParam     MemPtrOrFileName,
                        MIL_ID             SysId,
                        MIL_INT64          Operation,
                        MIL_INT64          StreamType,
                        MIL_DOUBLE         Version,
                        MIL_INT64          ControlFlag,
                        MIL_UNIQUE_3DIM_ID* Context3dimIdPtr,
                        MIL_INT*            SizeByteVarPtr)
   {
   MxxxStreamForMilUniqueId(MemPtrOrFileName, SysId, Operation, StreamType, Version, ControlFlag, Context3dimIdPtr, SizeByteVarPtr, M3dimStream);
   }
inline void M3dimMerge(MilConstArrayIdParam ContArrayPtr, MIL_ID DstContainerId, MIL_INT NumContainers, MIL_ID SubsampleContext3dimId, MIL_INT64 ControlFlag)
   {
   M3dimMerge(ContArrayPtr.m_IdArrayPtr, DstContainerId, NumContainers, SubsampleContext3dimId, ControlFlag);
   }

#endif // M_MIL_USE_MOVE_SEMANTICS
#endif // M_MIL_USE_MIL_UNIQUE_ID

// End of MIL_UNIQUE_ID support
////////////////////////////////////////////////////////////////////////////////

#endif // !M_MIL_LITE
#endif // __MIL_3DIM_H__
