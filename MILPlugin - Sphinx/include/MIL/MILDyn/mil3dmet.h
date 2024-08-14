//==============================================================================
//! 
//! \brief Mil3dmet CAPI header (M3dmet...)
//! 
//! AUTHOR:  Matrox Imaging
//!
//! COPYRIGHT NOTICE:
//! Copyright (c) Matrox Electronic Systems Ltd., 1992-2021.
//! All Rights Reserved 
//  Revision:  10.40.0881
//==============================================================================

#ifndef __MIL_3DMET_H__
#define __MIL_3DMET_H__


#if !defined(__MIL3DGEO_H__)
#include <mildyn/mil3dgeo.h>
#endif

#if (!M_MIL_LITE) /* MIL FULL ONLY */

#if M_MIL_USE_RT
#ifdef M_3DMET_EXPORTS
#define MIL_3DMET_DLLFUNC __declspec(dllexport)
#else
#define MIL_3DMET_DLLFUNC __declspec(dllimport)
#endif
#else
#define MIL_3DMET_DLLFUNC
#endif

/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
   {
#endif

//==============================================================================
// M3dmetAlloc ContextTypes
#define M_STATISTICS_CONTEXT                          16L   // already defined in milim.h
#define M_FIT_CONTEXT                                 3646L

//==============================================================================   
// Indexing, used in other M3dmet functions (M3dmetInquire(), M3dmetControl(), ...)
#define M_DEFAULT                               0x10000000L // already defined
#define M_CONTEXT                               0x08000000L // already defined
#define M_GENERAL                               0x20000000L // already defined
#define M_ALL                                   0x40000000L // already defined

#define M_ANY                                   0x11000000L // already defined


#define M_MODIFICATION_COUNT                          5010L // already defined

//==============================================================================
#define M_ALLOCATION_FAILURE_REAL_TEST_FLAG            971L // also in milblob.h, milstr.h

//==============================================================================
//M3dmetDistance
#define M_DISTANCE_TO_CENTER                          2983L 
#define M_DISTANCE_TO_CENTER_SQUARED                  2984L
#define M_DISTANCE_TO_CENTER_AXIS                     3017L 
#define M_DISTANCE_TO_CENTER_AXIS_SQUARED             3034L 
#define M_ABSOLUTE_DISTANCE_Z_TO_SURFACE              2985L 
#define M_ABSOLUTE_DISTANCE_TO_SURFACE                2986L 
#define M_SIGNED_DISTANCE_Z_TO_SURFACE                2987L 
#define M_SIGNED_DISTANCE_TO_SURFACE                  2988L 
#define M_DISTANCE_TO_NEAREST_NEIGHBOR                3444  // already defined in mil3dim.h
#define M_DISTANCE_TO_MESH                            3543L
#define M_MANHATTAN_DISTANCE_TO_SURFACE               3736L
#define M_DISTANCE_TO_LINE                            3934L
#define M_DISTANCE_TO_LINE_SQUARED                    3935L

//M3dmetFit
// Context
#define M_FIT_ITERATIONS_MAX                           104L // already defined in milmetrol.h
#define M_RMS_ERROR_THRESHOLD                         3565  // already defined in mil3dreg.h
#define M_INLIER_AMOUNT_THRESHOLD                     3599L

#define M_ESTIMATION_MODE                             3600L
#define M_RANDOM_SAMPLING                             3601L
#define M_NO_SAMPLING                                 3602L
#define M_FROM_GEOMETRY                               3603L

#define M_RANDOM_SAMPLING_CONFIDENCE                  3604L
#define M_RANDOM_SAMPLING_NUMBER_OF_TEST_POINTS       3605L
#define M_EXPECTED_OUTLIER_PERCENTAGE                 3606L

//M3dmetCopy
#define M_ESTIMATE_GEOMETRY                           3607L

// Result
#define M_SUCCESS                               0x00000000L // Already defined in milreg.h, milcolor.h
#define M_NOT_INITIALIZED                                3L // Already defined in milcal.h
#define M_ALL_POINTS_COPLANAR                         4742L
#define M_NOT_ENOUGH_VALID_DATA                       1336L 
#define M_BAD_ESTIMATE                                3616L
#define M_MATHEMATICAL_EXCEPTION                         8L

#define M_NUMBER_OF_POINTS_TOTAL                      3485  // already defined in mil3dim.h
#define M_NUMBER_OF_POINTS_VALID                      3440  // already defined in mil3dim.h
#define M_NUMBER_OF_POINTS_MISSING_DATA               3484  // already defined in mil3dim.h
#define M_NUMBER_OF_POINTS_INLIERS                    3557L
#define M_NUMBER_OF_POINTS_OUTLIERS                   3558L
#define M_FIT_RMS_ERROR                               1333L // already defined in mil3dmap.h

//M3dmetCopyResult
#define M_FITTED_GEOMETRY                             3559L
#define M_INLIER_MASK                                 3590L
#define M_OUTLIER_MASK                                3995L
#define M_FIXTURING_MATRIX                            3878L

//M3dmetStat
#define M_STAT_MIN                                    2502  // already defined in milim.h
#define M_STAT_MAX                                    2503  // already defined in milim.h
#define M_STAT_MIN_ABS                                2504
#define M_STAT_MAX_ABS                                2505
#define M_STAT_SUM_ABS                                2506
#define M_STAT_SUM_OF_SQUARES                         2507
#define M_STAT_SUM                                    2508
#define M_STAT_MEAN                                   2509
#define M_STAT_STANDARD_DEVIATION                     2510  // already defined in milim.h
#define M_STAT_NUMBER                                 1009L // already defined in milim.h
#define M_STAT_RMS                                    3562L
#define M_IN_RANGE                                      1L          // Already defined in    milblob.h, mil.h, miledge.h
#define M_GREATER                                       5L          // Already defined in    milblob.h, mil.h, miledge.h
#define M_LESS                                          6L          // Already defined in    milblob.h, mil.h, miledge.h
#define M_GREATER_OR_EQUAL                              7L          // Already defined in    milblob.h, mil.h, miledge.h
#define M_LESS_OR_EQUAL                                 8L          // Already defined in    milblob.h, mil.h, miledge.h
//M3dmetStat pseudo ids
#define M_STAT_CONTEXT_MIN                            (M_STAT_MIN | M_PSEUDO_ID)
#define M_STAT_CONTEXT_MAX                            (M_STAT_MAX | M_PSEUDO_ID)
#define M_STAT_CONTEXT_MIN_ABS                        (M_STAT_MIN_ABS | M_PSEUDO_ID)
#define M_STAT_CONTEXT_MAX_ABS                        (M_STAT_MAX_ABS | M_PSEUDO_ID)
#define M_STAT_CONTEXT_SUM_ABS                        (M_STAT_SUM_ABS | M_PSEUDO_ID)
#define M_STAT_CONTEXT_SUM_OF_SQUARES                 (M_STAT_SUM_OF_SQUARES | M_PSEUDO_ID)
#define M_STAT_CONTEXT_SUM                            (M_STAT_SUM | M_PSEUDO_ID)
#define M_STAT_CONTEXT_MEAN                           (M_STAT_MEAN | M_PSEUDO_ID)
#define M_STAT_CONTEXT_STANDARD_DEVIATION             (M_STAT_STANDARD_DEVIATION | M_PSEUDO_ID)
#define M_STAT_CONTEXT_NUMBER                         (M_STAT_NUMBER | M_PSEUDO_ID)
#define M_STAT_CONTEXT_RMS                            (M_STAT_RMS | M_PSEUDO_ID)

//M3dmetVolume
#define M_ABOVE                                       4076L // already defined in milmetrol.h
#define M_UNDER                                       4077L // already defined in milmetrol.h
#define M_TOTAL                                       3627L
#define M_DIFFERENCE                                  3628L

#define M_WARNING_GAPS                                3629L
#define M_FAIL_GAPS                                   3676L
#define M_FAIL_INVALID_MESH                           3675L

//M3dgeo
#define M_GEOMETRY_TYPE                               1321L // Already define in mil3dgeo
#define M_GEOMETRY                                    1306L // Already define in mil3dgeo
#define M_PLANE                                       1353L // Already defined in mil3dgeo
#define M_SPHERE                                      2931L // Already defined in mil3dgeo
#define M_CYLINDER                                    3656  // Already defined in mil3dgeo
#define M_BOX                                        0x101L // Already defined in    milblob.h
#define M_LINE                                  0x00000080L // Already defined
//Sphere
#define M_CENTER_X                                       4L // also in mil.h
#define M_CENTER_Y                                       5L
#define M_CENTER_Z                                    3400
#define M_RADIUS                                0x00000040L       // Already defined in MilMod.h
//Plane
#define M_COEFFICIENT_A                              3401 // Already defined in mil3dgeo
#define M_COEFFICIENT_B                              3402 // Already defined in mil3dgeo
#define M_COEFFICIENT_C                              3403
#define M_COEFFICIENT_D                              3404
#define M_NORMAL_X                                   3537
#define M_NORMAL_Y                                   3538
#define M_NORMAL_Z                                   3539
#define M_CLOSEST_TO_ORIGIN_X                        3540
#define M_CLOSEST_TO_ORIGIN_Y                        3541
#define M_CLOSEST_TO_ORIGIN_Z                        3542
//Cylinder
#define M_TWO_POINTS                                 3657
#define M_START_POINT_X                              3658
#define M_START_POINT_Y                              3659                               
#define M_START_POINT_Z                              3660
#define M_END_POINT_X                                3661
#define M_END_POINT_Y                                3662
#define M_END_POINT_Z                                3663
#define M_AXIS_X                                     3664
#define M_AXIS_Y                                     3665
#define M_AXIS_Z                                     3666
#define M_FINITE                                     3016L
#define M_INFINITE                                     -1L // Also defined in Mil.h


//==============================================================================
// M3dmetControl / M3dmetInquire
// Context 

#define M_ENABLE                                     -9997L // also in mil.h
#define M_DISABLE                                    -9999L // also in mil.h

#define M_AUTO                                         444L // also in mil.h
#define M_USER_DEFINED                                  21L // also in mil.h

#define M_SIZE                                       0xC00L // also in mil.h
#define M_SIZE_X                                      1536L // also in mil.h
#define M_SIZE_Y                                      1537L // also in mil.h
#define M_SIZE_Z                                      1538L // also in mil.h

#define M_MAX                                   0x04000000L // also in mil.h
#define M_AVERAGE                               0x00000020L // also in milim.h

//==============================================================================
// M3dmetInquire 
// Context
#define M_INVALID                                        -1 // also in mil.h

//==============================================================================
// M3dmetAllocResult ResultTypes

//==============================================================================
// M3dmetGetResult ResultTypes
#define M_STATISTICS_RESULT                          MAKE_INT64(0x0001000000000000) // also in mil.h
#define M_FIT_RESULT                                 3645L

// General
#define M_STATUS                                0x00008002L // already defined in milbead
#define M_COMPLETE                              0x00000000L // already defined in mil3dreg
#define M_INTERNAL_ERROR                                 5L // already defined in milreg.h

//==============================================================================
// Other defines

//==============================================================================
// CAPI function prototypes
MIL_3DMET_DLLFUNC MIL_ID MFTYPE M3dmetAlloc(MIL_ID    SysId,
                                            MIL_INT64 ContextType,
                                            MIL_INT64 ControlFlag,
                                            MIL_ID*   Context3dmetIdPtr);

MIL_3DMET_DLLFUNC MIL_ID MFTYPE M3dmetAllocResult(MIL_ID    SysId,
                                                  MIL_INT64 ResultType,
                                                  MIL_INT64 ControlFlag,
                                                  MIL_ID*   Result3dmetIdPtr);

MIL_3DMET_DLLFUNC void MFTYPE M3dmetFree(MIL_ID ContextOrResult3dmetId);


  
//#if M_MIL_USE_64BIT
   // Prototypes for 64 bits OSs
MIL_3DMET_DLLFUNC void MFTYPE M3dmetControlInt64(MIL_ID     Context3dmetId,
                                                 MIL_INT64  ControlType,
                                                 MIL_INT64  ControlValue);
 MIL_3DMET_DLLFUNC void MFTYPE M3dmetControlDouble(MIL_ID     Context3dmetId,
                                                   MIL_INT64  ControlType,
                                                   MIL_DOUBLE ControlValue);

 MIL_3DMET_DLLFUNC MIL_INT64 MFTYPE M3dmetInquire(MIL_ID    Context3dmetId,
                                                  MIL_INT64 InquireType,
                                                  void*     UserVarPtr);

 MIL_3DMET_DLLFUNC MIL_DOUBLE MFTYPE M3dmetGetResult(MIL_ID    Result3dmetId,
                                                     MIL_INT64 ResultType,
                                                     void*     ResultArrayPtr);

 MIL_3DMET_DLLFUNC void MFTYPE  M3dmetDistance(MIL_ID     SrcContainerOrImageBufId,
                                               MIL_ID     RefMilObjectId,
                                               MIL_ID     DstImageBufId,
                                               MIL_INT64  DistanceType,
                                               MIL_DOUBLE Param,
                                               MIL_INT64  ControlFlag);

 MIL_3DMET_DLLFUNC void MFTYPE  M3dmetFit(MIL_ID     Context3dmetId,
                                          MIL_ID     SrcContainerOrImageBufId,
                                          MIL_INT    GeometryType,
                                          MIL_ID     Result3dmetId,
                                          MIL_DOUBLE OutlierDistance,
                                          MIL_INT64  ControlFlag);

 MIL_3DMET_DLLFUNC void MFTYPE  M3dmetCopyResult(MIL_ID    SrcResult3dmetId,
                                                 MIL_ID    DstMilObjectId,
                                                 MIL_INT64 CopyType,
                                                 MIL_INT64 ControlFlag);


 MIL_3DMET_DLLFUNC void MFTYPE   M3dmetStat(MIL_ID     StatContext3dmetId,
                                            MIL_ID     SrcContainerOrImageBufId,
                                            MIL_ID     RefMilObjectId,
                                            MIL_ID     StatResult3dmetId,
                                            MIL_INT64  DistanceType,
                                            MIL_INT64  Condition,
                                            MIL_DOUBLE CondLow,
                                            MIL_DOUBLE CondHigh,
                                            MIL_INT64  ControlFlag);

 MIL_3DMET_DLLFUNC void MFTYPE M3dmetCopy(MIL_ID    SrcMilObjectId,
                                          MIL_ID    DstMilObjectId,
                                          MIL_INT64 CopyType,
                                          MIL_INT64 ControlFlag);

 MIL_3DMET_DLLFUNC MIL_DOUBLE MFTYPE M3dmetVolume(MIL_ID      SrcContainerOrImageBufId,
                                                  MIL_ID      Reference3dgeoOrImageBufId,
                                                  MIL_INT64   Options,
                                                  MIL_INT64   ControlFlag,
                                                  MIL_DOUBLE* VolumePtr,
                                                  MIL_INT64*  StatusPtr);

 MIL_3DMET_DLLFUNC MIL_INT64 MFTYPE M3dmetDraw3d(MIL_ID    OperationDraw3dContext3dmetId,
                                                 MIL_ID    SrcResult3dmetId,
                                                 MIL_ID    DstList3dgraId,
                                                 MIL_INT64 DstParentLabel,
                                                 MIL_INT64 ControlFlag);

#if M_MIL_USE_UNICODE
   MIL_3DMET_DLLFUNC void MFTYPE M3dmetSaveA(MIL_CONST_TEXTA_PTR FileName,
                                           MIL_ID      Context3dmetId,
                                           MIL_INT64   ControlFlag);

   MIL_3DMET_DLLFUNC MIL_ID MFTYPE M3dmetRestoreA(MIL_CONST_TEXTA_PTR FileName,
                                                MIL_ID      SysId,
                                                MIL_INT64   ControlFlag,
                                                MIL_ID*     Context3dmetIdPtr);

   MIL_3DMET_DLLFUNC void MFTYPE M3dmetStreamA(MIL_TEXTA_PTR MemPtrOrFileName,
                                             MIL_ID     SysId,
                                             MIL_INT64  Operation,
                                             MIL_INT64  StreamType,
                                             MIL_DOUBLE Version,
                                             MIL_INT64  ControlFlag,
                                             MIL_ID*    Context3dmetIdPtr,
                                             MIL_INT*   SizeByteVarPtr);



   MIL_3DMET_DLLFUNC void MFTYPE M3dmetSaveW(MIL_CONST_TEXTW_PTR FileName,
                                           MIL_ID              Context3dmetId,
                                           MIL_INT64           ControlFlag);

   MIL_3DMET_DLLFUNC MIL_ID MFTYPE M3dmetRestoreW(MIL_CONST_TEXTW_PTR FileName,
                                                MIL_ID              SysId,
                                                MIL_INT64           ControlFlag,
                                                MIL_ID*             Context3dmetIdPtr);

   MIL_3DMET_DLLFUNC void MFTYPE M3dmetStreamW(MIL_TEXTW_PTR MemPtrOrFileName,
                                             MIL_ID        SysId,
                                             MIL_INT64     Operation,
                                             MIL_INT64     StreamType,
                                             MIL_DOUBLE    Version,
                                             MIL_INT64     ControlFlag,
                                             MIL_ID*       Context3dmetIdPtr,
                                             MIL_INT*      SizeByteVarPtr);

#if M_MIL_UNICODE_API
#define M3dmetSave               M3dmetSaveW
#define M3dmetRestore            M3dmetRestoreW
#define M3dmetStream             M3dmetStreamW
#else
#define M3dmetSave               M3dmetSaveA
#define M3dmetRestore            M3dmetRestoreA
#define M3dmetStream             M3dmetStreamA
#endif //M_MIL_UNICODE_API

#else

 MIL_3DMET_DLLFUNC void MFTYPE   M3dmetSave(MIL_CONST_TEXT_PTR FileName,
                                            MIL_ID             Context3dmetId,
                                            MIL_INT64          ControlFlag);

 MIL_3DMET_DLLFUNC MIL_ID MFTYPE M3dmetRestore(MIL_CONST_TEXT_PTR FileName,
                                               MIL_ID             SysId,
                                               MIL_INT64          ControlFlag,
                                               MIL_ID*            Context3dmetIdPtr);

 MIL_3DMET_DLLFUNC void MFTYPE   M3dmetStream(MIL_TEXT_PTR MemPtrOrFileName,
                                              MIL_ID       SysId,
                                              MIL_INT64    Operation,
                                              MIL_INT64    StreamType,
                                              MIL_DOUBLE   Version,
                                              MIL_INT64    ControlFlag,
                                              MIL_ID*      Context3dmetIdPtr,
                                              MIL_INT*     SizeByteVarPtr);

#endif //M_MIL_USE_UNICODE
#ifdef __cplusplus
   inline bool In3dmetInquireDoubleRange(MIL_INT64 InquireType)
      {
      if(M_NB_ELEMENTS_BIT_SET(InquireType))
         {
         return false;
         }

      switch(M_STRIP_INQ_COMBOFLAGS(InquireType))
         {
         case M_ALLOCATION_FAILURE_REAL_TEST_FLAG:
         case M_RMS_ERROR_THRESHOLD:
         case M_RANDOM_SAMPLING_CONFIDENCE:
         case M_EXPECTED_OUTLIER_PERCENTAGE:
        
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

   inline bool In3dmetInquireInt64Range(MIL_INT64 InquireType)
      {
      UNREFERENCED_PARAMETER(InquireType);

      return false;
      }
   inline bool M3dmetInquireMustHaveUserPtr(MIL_INT64 InquireType)
      {
      const MIL_INT64 ForcedDataType = MinquireOverrides(M_STRIP_HLVLDATATYPE(InquireType), M_TYPE_MIL_INT);
      if(ForcedDataType != 0)
         {
         return false;// ForcedDataType == M_TYPE_DOUBLE;
         }
      return In3dmetInquireDoubleRange(InquireType);
      }
   inline bool In3dmetResultDoubleRange(MIL_INT64 InquireType)
      {
      if(M_NB_ELEMENTS_BIT_SET(InquireType))
         {
         return false;
         }

      if(In3dgeoInquireDoubleRange(InquireType))
         return true;

      switch(M_STRIP_INQ_COMBOFLAGS(InquireType))
         { 
         // Fit Result
         case M_FIT_RMS_ERROR:

         // Stat Result
         case M_STAT_MAX:
         case M_STAT_MAX_ABS:
         case M_STAT_MIN:
         case M_STAT_MIN_ABS:
         case M_STAT_MEAN:
         case M_STAT_STANDARD_DEVIATION:
         case M_STAT_SUM:
         case M_STAT_SUM_ABS:
         case M_STAT_SUM_OF_SQUARES:
         case M_STAT_RMS:

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
   inline bool In3dmetResultInt64Range(MIL_INT64 InquireType)
      {
      UNREFERENCED_PARAMETER(InquireType);
      if(M_NB_ELEMENTS_BIT_SET(InquireType))
         {
         return false;
         }

      return false;
      }
   inline bool M3dmetResultMustHaveUserPtr(MIL_INT64 ResultType)
      {
      const MIL_INT64 ForcedDataType = MinquireOverrides(M_STRIP_HLVLDATATYPE(ResultType), M_TYPE_MIL_INT);
      if(ForcedDataType != 0)
         {
         return false;// ForcedDataType == M_TYPE_MIL_INT64;
         }
      return In3dmetResultInt64Range(ResultType);
      }
#endif // __cplusplus
   /* C++ directive if needed */
#ifdef __cplusplus
   }
#endif
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
   inline void MFTYPE M3dmetStreamCpp(MilStreamParam MemPtrOrFileName,
                                      MIL_ID         SysId,
                                      MIL_INT64      Operation,
                                      MIL_INT64      StreamType,
                                      MIL_DOUBLE     Version,
                                      MIL_INT64      ControlFlag,
                                      MIL_ID*        Context3dmetIdPtr,
                                      MIL_INT*       SizeByteVarPtr)
   {
   M3dmetStream(MemPtrOrFileName.m_Param, SysId, Operation, StreamType, Version, ControlFlag, Context3dmetIdPtr, SizeByteVarPtr);
   }

#undef  M3dmetStream
#define M3dmetStream M3dmetStreamCpp

#endif // __cplusplus


#ifdef __cplusplus
inline MIL_INT64 M3dmetInquireDataType(MIL_INT64 InquireType)
   {
   const MIL_INT64 ForcedDataType = MinquireOverrides(InquireType, M_TYPE_MIL_INT);
   if(ForcedDataType != 0)
      return ForcedDataType;

   if(In3dmetInquireDoubleRange(InquireType))
      return M_TYPE_DOUBLE;

   if(In3dmetInquireInt64Range(InquireType))
      return M_TYPE_MIL_INT64;

   return M_TYPE_MIL_INT;
   }
//result
inline MIL_INT64 M3dmetResultDataType(MIL_INT64 InquireType)
   {
   const MIL_INT64 ForcedDataType = MinquireOverrides(InquireType, M_TYPE_MIL_INT);
   if(ForcedDataType != 0)
      return ForcedDataType;

   if(In3dmetResultDoubleRange(InquireType))
      return M_TYPE_DOUBLE;

   if(In3dmetResultInt64Range(InquireType))
      return M_TYPE_MIL_INT64;

   return M_TYPE_MIL_INT;
   }
// ----------------------------------------------------------
// M3dmetInquire
#if M_MIL_USE_SAFE_TYPE

inline MIL_INT64 MFTYPE M3dmetInquireSafeType(MIL_ID Context3dmetId, MIL_INT64  InquireType, int UserVarPtr)
   {
   bool MustHaveUserPointer = M3dmetInquireMustHaveUserPtr(InquireType);

   if(UserVarPtr)
      SafeTypeError(MIL_TEXT("M3dmetInquire"));

   if(!UserVarPtr && MustHaveUserPointer)
      SafeTypeError(MIL_TEXT("M3dmetInquire"), MIL_TEXT("The specified InquireType requires a non-null output pointer."));

   return M3dmetInquire(Context3dmetId, InquireType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT64 MFTYPE M3dmetInquireSafeType(MIL_ID Context3dmetId, MIL_INT64  InquireType, std::nullptr_t)
   {
   bool MustHaveUserPointer = M3dmetInquireMustHaveUserPtr(InquireType);

   if(MustHaveUserPointer)
      SafeTypeError(MIL_TEXT("M3dmetInquire"), MIL_TEXT("The specified InquireType requires a non-null output pointer."));

   return M3dmetInquire(Context3dmetId, InquireType, NULL);
   }
#endif // M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT64 MFTYPE M3dmetInquireSafeTypeExecute(MIL_ID Context3dmetId, MIL_INT64  InquireType, void  *UserVarPtr, MIL_INT64  GivenType)
   {
   MIL_INT64  RequiredType = M3dmetInquireDataType(InquireType);
   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if(RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("M3dmetInquire"));

   return M3dmetInquire(Context3dmetId, InquireType, UserVarPtr);
   }
inline MIL_INT64 MFTYPE M3dmetInquireUnsafe(MIL_ID Context3dmetId, MIL_INT64 InquireType, void*       UserVarPtr) { return M3dmetInquire(Context3dmetId, InquireType, UserVarPtr); }
inline MIL_INT64 MFTYPE M3dmetInquireSafeType(MIL_ID Context3dmetId, MIL_INT64 InquireType, MIL_INT8*   UserVarPtr) { return M3dmetInquireSafeTypeExecute(Context3dmetId, InquireType, UserVarPtr, M_TYPE_CHAR); }
inline MIL_INT64 MFTYPE M3dmetInquireSafeType(MIL_ID Context3dmetId, MIL_INT64 InquireType, MIL_INT16*  UserVarPtr) { return M3dmetInquireSafeTypeExecute(Context3dmetId, InquireType, UserVarPtr, M_TYPE_SHORT); }
inline MIL_INT64 MFTYPE M3dmetInquireSafeType(MIL_ID Context3dmetId, MIL_INT64 InquireType, MIL_INT32*  UserVarPtr) { return M3dmetInquireSafeTypeExecute(Context3dmetId, InquireType, UserVarPtr, M_TYPE_MIL_INT32); }
inline MIL_INT64 MFTYPE M3dmetInquireSafeType(MIL_ID Context3dmetId, MIL_INT64 InquireType, MIL_INT64*  UserVarPtr) { return M3dmetInquireSafeTypeExecute(Context3dmetId, InquireType, UserVarPtr, M_TYPE_MIL_INT64); }
inline MIL_INT64 MFTYPE M3dmetInquireSafeType(MIL_ID Context3dmetId, MIL_INT64 InquireType, MIL_FLOAT*  UserVarPtr) { return M3dmetInquireSafeTypeExecute(Context3dmetId, InquireType, UserVarPtr, M_TYPE_FLOAT); }
inline MIL_INT64 MFTYPE M3dmetInquireSafeType(MIL_ID Context3dmetId, MIL_INT64 InquireType, MIL_DOUBLE* UserVarPtr) { return M3dmetInquireSafeTypeExecute(Context3dmetId, InquireType, UserVarPtr, M_TYPE_MIL_DOUBLE); }
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline MIL_INT64 MFTYPE M3dmetInquireSafeType(MIL_ID Context3dmetId, MIL_INT64 InquireType, MIL_UINT8*  UserVarPtr) { return M3dmetInquireSafeTypeExecute(Context3dmetId, InquireType, UserVarPtr, M_TYPE_CHAR); }
inline MIL_INT64 MFTYPE M3dmetInquireSafeType(MIL_ID Context3dmetId, MIL_INT64 InquireType, MIL_UINT16* UserVarPtr) { return M3dmetInquireSafeTypeExecute(Context3dmetId, InquireType, UserVarPtr, M_TYPE_SHORT); }
inline MIL_INT64 MFTYPE M3dmetInquireSafeType(MIL_ID Context3dmetId, MIL_INT64 InquireType, MIL_UINT32* UserVarPtr) { return M3dmetInquireSafeTypeExecute(Context3dmetId, InquireType, UserVarPtr, M_TYPE_MIL_INT32); }
inline MIL_INT64 MFTYPE M3dmetInquireSafeType(MIL_ID Context3dmetId, MIL_INT64 InquireType, MIL_UINT64* UserVarPtr) { return M3dmetInquireSafeTypeExecute(Context3dmetId, InquireType, UserVarPtr, M_TYPE_MIL_INT64); }
#endif
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T
inline MIL_INT64 MFTYPE M3dmetInquireSafeType(MIL_ID Context3dmetId, MIL_INT64  InquireType, wchar_t*    UserVarPtr) { return M3dmetInquireSafeTypeExecute(Context3dmetId, InquireType, UserVarPtr, M_TYPE_STRING); }//or M_TYPE_SHORT??
#endif

#define M3dmetInquire           M3dmetInquireSafeType
#else // #if M_MIL_USE_SAFE_TYPE
#define M3dmetInquireUnsafe     M3dmetInquire
#endif // #if M_MIL_USE_SAFE_TYPE



#if M_MIL_USE_SAFE_TYPE
// -------------------------------------------------------------------------
// M3dmetGetResult safe type definitions
// 
inline MIL_DOUBLE MFTYPE M3dmetGetResultSafeType(MIL_ID Result3dmetId, MIL_INT64 ResultType, int ResultPtr)
   {
   bool MustHaveUserPointer = M3dmetResultMustHaveUserPtr(ResultType);

   if(ResultPtr)
      SafeTypeError(MIL_TEXT("M3dmetGetResult"));

   if(!ResultPtr && MustHaveUserPointer)
      SafeTypeError(MIL_TEXT("M3dmetGetResult"), MIL_TEXT("The specified ResultType requires a non-null output pointer."));

   return M3dmetGetResult(Result3dmetId, ResultType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_DOUBLE MFTYPE M3dmetGetResultSafeType(MIL_ID Result3dmetId, MIL_INT64 ResultType, std::nullptr_t)
   {
   bool MustHaveUserPointer = M3dmetResultMustHaveUserPtr(ResultType);

   if(MustHaveUserPointer)
      SafeTypeError(MIL_TEXT("M3dmetGetResult"), MIL_TEXT("The specified ResultType requires a non-null output pointer."));

   return M3dmetGetResult(Result3dmetId, ResultType, NULL);
   }
#endif
inline MIL_DOUBLE M3dmetGetResultSafeTypeExecute(MIL_ID Result3dmetId, MIL_INT64 ResultType, void* ResultArrayPtr, MIL_INT64 GivenType)
   {
   MIL_INT64  RequiredType = M3dmetResultDataType(ResultType);

   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if(RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("M3dmetGetResult"));

   return M3dmetGetResult(Result3dmetId, ResultType, ResultArrayPtr);
   }
//=========================================================
// See milos.h for explanation about these functions.
//=========================================================

// -------------------------------------------------------------------------
// M3dmetGetResult safe type 
inline MIL_DOUBLE MFTYPE M3dmetGetResultUnsafe  (MIL_ID Result3dmetId, MIL_INT64 ResultType, void*        ResultArrayPtr) { return M3dmetGetResult(Result3dmetId, ResultType, ResultArrayPtr); }
inline MIL_DOUBLE MFTYPE M3dmetGetResultSafeType(MIL_ID Result3dmetId, MIL_INT64 ResultType, MIL_INT8*    ResultArrayPtr) { return M3dmetGetResultSafeTypeExecute(Result3dmetId, ResultType, ResultArrayPtr, M_TYPE_CHAR); }
inline MIL_DOUBLE MFTYPE M3dmetGetResultSafeType(MIL_ID Result3dmetId, MIL_INT64 ResultType, MIL_INT16*   ResultArrayPtr) { return M3dmetGetResultSafeTypeExecute(Result3dmetId, ResultType, ResultArrayPtr, M_TYPE_SHORT); }
inline MIL_DOUBLE MFTYPE M3dmetGetResultSafeType(MIL_ID Result3dmetId, MIL_INT64 ResultType, MIL_INT32*   ResultArrayPtr) { return M3dmetGetResultSafeTypeExecute(Result3dmetId, ResultType, ResultArrayPtr, M_TYPE_MIL_INT32); }
inline MIL_DOUBLE MFTYPE M3dmetGetResultSafeType(MIL_ID Result3dmetId, MIL_INT64 ResultType, MIL_INT64*   ResultArrayPtr) { return M3dmetGetResultSafeTypeExecute(Result3dmetId, ResultType, ResultArrayPtr, M_TYPE_MIL_INT64); }
inline MIL_DOUBLE MFTYPE M3dmetGetResultSafeType(MIL_ID Result3dmetId, MIL_INT64 ResultType, float*       ResultArrayPtr) { return M3dmetGetResultSafeTypeExecute(Result3dmetId, ResultType, ResultArrayPtr, M_TYPE_FLOAT); }
inline MIL_DOUBLE MFTYPE M3dmetGetResultSafeType(MIL_ID Result3dmetId, MIL_INT64 ResultType, MIL_DOUBLE*  ResultArrayPtr) { return M3dmetGetResultSafeTypeExecute(Result3dmetId, ResultType, ResultArrayPtr, M_TYPE_MIL_DOUBLE); }

#if M_MIL_UNICODE_API
inline MIL_DOUBLE MFTYPE M3dmetGetResultSafeType(MIL_ID Result3dmetId, MIL_INT64 ResultType, MIL_TEXT_PTR ResultArrayPtr) { return M3dmetGetResultSafeTypeExecute(Result3dmetId, ResultType, ResultArrayPtr, M_TYPE_STRING); }
#endif

#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline MIL_DOUBLE MFTYPE M3dmetGetResultSafeType(MIL_ID Result3dmetId, MIL_INT64 ResultType, MIL_UINT8*   ResultArrayPtr) { return M3dmetGetResultSafeTypeExecute(Result3dmetId, ResultType, ResultArrayPtr, M_TYPE_CHAR); }
inline MIL_DOUBLE MFTYPE M3dmetGetResultSafeType(MIL_ID Result3dmetId, MIL_INT64 ResultType, MIL_UINT16* ResultArrayPtr)  { return M3dmetGetResultSafeTypeExecute(Result3dmetId, ResultType, ResultArrayPtr, M_TYPE_SHORT); }
inline MIL_DOUBLE MFTYPE M3dmetGetResultSafeType(MIL_ID Result3dmetId, MIL_INT64 ResultType, MIL_UINT32* ResultArrayPtr)  { return M3dmetGetResultSafeTypeExecute(Result3dmetId, ResultType, ResultArrayPtr, M_TYPE_MIL_INT32); }
inline MIL_DOUBLE MFTYPE M3dmetGetResultSafeType(MIL_ID Result3dmetId, MIL_INT64 ResultType, MIL_UINT64* ResultArrayPtr)  { return M3dmetGetResultSafeTypeExecute(Result3dmetId, ResultType, ResultArrayPtr, M_TYPE_MIL_INT64); }
#endif
//------------------------------
// Safetype functions assignment
#define M3dmetGetResult            M3dmetGetResultSafeType
#else // #if M_MIL_USE_SAFE_TYPE
#define M3dmetGetResultUnsafe            M3dmetGetResult
#endif // #if M_MIL_USE_SAFE_TYPE

#endif // __cplusplus

//#if M_MIL_USE_64BIT
#ifdef __cplusplus

//=========================================================
// M3dmetControl function overloads when compiling c++ files
//=========================================================
template <typename T>
inline void M3dmetControl(MIL_ID Context3dmetId, MIL_INT64 ControlType, T ControlValue)
   {
   M3dmetControlInt64(Context3dmetId, ControlType, ControlValue);
   }

inline void M3dmetControl(MIL_ID Context3dmetId, MIL_INT64 ControlType, float ControlValue)
   {
   M3dmetControlDouble(Context3dmetId, ControlType, ControlValue);
   }

inline void M3dmetControl(MIL_ID Context3dmetId, MIL_INT64 ControlType, MIL_DOUBLE ControlValue)
   {
   M3dmetControlDouble(Context3dmetId, ControlType, ControlValue);
   }
#else // __cplusplus
//=========================================================
// For C file, call the default function, i.e. Double one
//=========================================================
#define M3dmetControl            M3dmetControlDouble
#endif // __cplusplus
//#endif // M_MIL_USE_64BIT

#if M_MIL_USE_STRING
/***************************************************************************/
/* 3dmet MODULE                                                              */
/***************************************************************************/
#if M_MIL_USE_UNICODE
#if M_MIL_UNICODE_API

inline void MFTYPE M3dmetSaveW(const MIL_STRING& FileName, MIL_ID Context3dmetId, MIL_INT64 ControlFlag)
   {
   return M3dmetSaveW(FileName.c_str(), Context3dmetId, ControlFlag);
   }

inline MIL_ID MFTYPE M3dmetRestoreW(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* Context3dmetId)
   {
   return M3dmetRestoreW(FileName.c_str(), SysId, ControlFlag, Context3dmetId);
   }

#else // M_MIL_UNICODE_API
inline void MFTYPE M3dmetSaveA(const MIL_STRING& FileName, MIL_ID Context3dmetId, MIL_INT64 ControlFlag)
   {
   return M3dmetSaveA(FileName.c_str(), Context3dmetId, ControlFlag);
   }

inline MIL_ID MFTYPE M3dmetRestoreA(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* Context3dmetId)
   {
   return M3dmetRestoreA(FileName.c_str(), SysId, ControlFlag, Context3dmetId);
   }

#endif /* M_MIL_UNICODE_API*/

#else // M_MIL_USE_UNICODE
inline void MFTYPE M3dmetSave(const MIL_STRING& FileName, MIL_ID Context3dmetId, MIL_INT64 ControlFlag)
   {
   return M3dmetSave(FileName.c_str(), Context3dmetId, ControlFlag);
   }

inline MIL_ID MFTYPE M3dmetRestore(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* Context3dmetId)
   {
   return M3dmetRestore(FileName.c_str(), SysId, ControlFlag, Context3dmetId);
   }

//inline void MFTYPE M3dmetStream(const MIL_STRING& MemPtrOrFileName, MIL_ID SysId, MIL_INT64 Operation, MIL_INT64 StreamType,
//                              MIL_DOUBLE Version, MIL_INT64 ControlFlag, MIL_ID* Context3dmetId, MIL_INT* SizeByteVarPtr)
//   {
//   M3dmetStream((MIL_TEXT_PTR)MemPtrOrFileName.c_str(), SysId, Operation, StreamType, Version, ControlFlag, Context3dmetId, SizeByteVarPtr);
//   }

#endif /* M_MIL_USE_UNICODE */

#if M_MIL_USE_SAFE_TYPE

#if M_MIL_UNICODE_API

inline MIL_DOUBLE MFTYPE M3dmetGetResultSafeType(MIL_ID Result3dmetId, MIL_INT64 ResultType, MIL_STRING   &ResultArrayPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((ResultType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("M3dmetGetResult"), MIL_TEXT(" Result Type not supported with MIL_STRING."));
      }
#endif

   MIL_INT InternalStringSize = 0;

   M3dmetGetResultSafeType(Result3dmetId, (ResultType & (~M_HLVLDATATYPE_MASK)) + M_STRING_SIZE + M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      if(ResultArrayPtr.size() < (MIL_UINT)InternalStringSize)
         {
         ResultArrayPtr.resize((MIL_UINT)InternalStringSize);
         }
      }

   M3dmetGetResultSafeTypeExecute(Result3dmetId, ResultType, &ResultArrayPtr[0], M_TYPE_STRING);

   return 0.0;
   }
#endif /* M_MIL_UNICODE_API */
#else
//M3dmetGetResult is only defined in UNICODE
#if M_MIL_UNICODE_API
inline MIL_DOUBLE MFTYPE M3dmetGetResult(MIL_ID Result3dmetId, MIL_INT64 ResultType, MIL_STRING   &ResultArrayPtr)
   {
   MIL_INT InternalStringSize = 0;

   //Inquire the byte content
   M3dmetGetResult(Result3dmetId, (ResultType & (~M_HLVLDATATYPE_MASK)) + M_STRING_SIZE + M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ResultArrayPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      M3dmetGetResult(Result3dmetId, ResultType, &ResultArrayPtr[0]);
      ResultArrayPtr.resize(InternalStringSize);
      }

   return 0.0;
   }

#endif
#endif
#endif /* M_MIL_USE_STRING*/


// ----------------------------------------------------------
// Overload for std::vector.
#if defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR
// ----------------------------------------------------------
template <typename UserType>
inline MIL_INT64 MFTYPE M3dmetInquire(MIL_ID Context3dmetId, MIL_INT64  InquireType, std::vector<UserType> &UserVarPtr)
   {
   // If the given MIL data type is not the same as the SrcType, change it to the correct one
   // and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(InquireType) != 0)
      {
      SafeTypeError(MIL_TEXT("M3dmetInquire"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   InquireType = M_STRIP_HLVLDATATYPE(InquireType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   M3dmetInquire(Context3dmetId, M_STRIP_HLVLDATATYPE(InquireType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   UserVarPtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      return M3dmetInquire(Context3dmetId, InquireType, &UserVarPtr[0]);
      }
   return 0;
   }
template <typename UserType>
inline MIL_DOUBLE MFTYPE M3dmetGetResult(MIL_ID Result3dmetId, MIL_INT64  ResultType, std::vector<UserType> &ResultArrayPtr)
   {
   //! If the given MIL data type is not the same as the SrcType, change it to the correct one
   //! and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(ResultType) != 0)
      {
      SafeTypeError(MIL_TEXT("M3dmetGetResult"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   ResultType = M_STRIP_HLVLDATATYPE(ResultType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   M3dmetGetResult(Result3dmetId, M_STRIP_HLVLDATATYPE(ResultType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   ResultArrayPtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      M3dmetGetResult(Result3dmetId, ResultType, &ResultArrayPtr[0]);
      }
   return 0.0;
   }
// ----------------------------------------------------------
// Overloads for std::vector in M3dmetStream.
inline void MFTYPE M3dmetStream(std::vector<MIL_UINT8> &MemPtrOrFileName,
                                MIL_ID                 SysId,
                                MIL_INT64              Operation,
                                MIL_INT64              StreamType,
                                MIL_DOUBLE             Version,
                                MIL_INT64              ControlFlag,
                                MIL_ID*                Context3dmetIdPtr,
                                MIL_INT*               SizeByteVarPtr)
   {
   MxxxStreamForStdVector(MemPtrOrFileName,
                          SysId,
                          Operation,
                          StreamType,
                          Version,
                          ControlFlag,
                          Context3dmetIdPtr,
                          SizeByteVarPtr,
                          M3dmetStream);
   }
#endif // defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR
//==============================================================================
////////////////////////////////////////////////////////////////////////////////
// MIL_UNIQUE_ID support

#if M_MIL_USE_MIL_UNIQUE_ID

#if M_MIL_USE_SAFE_TYPE
template <> inline bool MilIsCorrectObjectType<&M3dmetFree>(MIL_INT64 ObjectType)
   {
   return (ObjectType & ~M_USER_DEFINE_LOW_ATTRIBUTE) == M_3DMET_OBJECT;
   }
#endif

typedef MIL_UNIQUE_ID<&M3dmetFree> MIL_UNIQUE_3DMET_ID;

#if M_MIL_USE_MOVE_SEMANTICS

inline MIL_UNIQUE_3DMET_ID M3dmetAlloc(MIL_ID SysId, MIL_INT64 ObjectType, MIL_INT64 InitFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DMET_ID(M3dmetAlloc(SysId, ObjectType, InitFlag, M_NULL));
   }
inline MIL_UNIQUE_3DMET_ID M3dmetAllocResult(MIL_ID     SysId, MIL_INT64  ResultType, MIL_INT64  ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DMET_ID(M3dmetAllocResult(SysId, ResultType, ControlFlag, M_NULL));
   }
inline MIL_UNIQUE_3DMET_ID M3dmetRestore(MIL_CONST_TEXT_PTR FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DMET_ID(M3dmetRestore(FileName, SysId, ControlFlag, M_NULL));
   }
#if M_MIL_USE_STRING
inline MIL_UNIQUE_3DMET_ID M3dmetRestore(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DMET_ID(M3dmetRestore(FileName.c_str(), SysId, ControlFlag, M_NULL));
   }
#endif // M_MIL_USE_STRING
template <MilFreeFuncType FreeFunc> inline void M3dmetFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

inline void M3dmetStream(MilStreamParam       MemPtrOrFileName,
                         MIL_ID               SysId,
                         MIL_INT64            Operation,
                         MIL_INT64            StreamType,
                         MIL_DOUBLE           Version,
                         MIL_INT64            ControlFlag,
                         MIL_UNIQUE_3DMET_ID* Context3dmetIdPtr,
                         MIL_INT*             SizeByteVarPtr)
   {
   MxxxStreamForMilUniqueId(MemPtrOrFileName, SysId, Operation, StreamType, Version, ControlFlag, Context3dmetIdPtr, SizeByteVarPtr, M3dmetStream);
   }

#endif // M_MIL_USE_MOVE_SEMANTICS
#endif // M_MIL_USE_MIL_UNIQUE_ID

// End of MIL_UNIQUE_ID support
////////////////////////////////////////////////////////////////////////////////

#endif // !M_MIL_LITE
#endif // __MIL_3DMET_H__
