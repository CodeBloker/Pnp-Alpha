//==============================================================================
//! 
//! \brief Mil3dreg CAPI header (M3dreg...)
//! 
//! AUTHOR:  Matrox Imaging
//!
//! COPYRIGHT NOTICE:
//! Copyright (c) Matrox Electronic Systems Ltd., 1992-2021.
//! All Rights Reserved 
//  Revision:  10.40.0881
//==============================================================================

#ifndef __MIL_3DREG_H__
#define __MIL_3DREG_H__

#if (!M_MIL_LITE) /* MIL FULL ONLY */

#if M_MIL_USE_RT
#ifdef M_3DREG_EXPORTS
#define MIL_3DREG_DLLFUNC __declspec(dllexport)
#else
#define MIL_3DREG_DLLFUNC __declspec(dllimport)
#endif
#else
#define MIL_3DREG_DLLFUNC
#endif

/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
   {
#endif

//==============================================================================
// M3dregAlloc ContextTypes
#define M_PAIRWISE_REGISTRATION_CONTEXT                3507
//==============================================================================   
// Indexing, used in other M3dreg functions (M3dregInquire(), M3dregControl(), ...)
#define M_DEFAULT                               0x10000000L // already defined in mil.h
#define M_CONTEXT                               0x08000000L // already defined in mil.h
#define M_GENERAL                               0x20000000L // already defined in milmod.h, ..
#define M_ALL                                   0x40000000L // already defined in mil.h
#define M_REGISTRATION_INDEX_FLAG               0x00200000L

#define M_REGISTRATION_INDEX_VALUE                    3534

#define M_MODIFICATION_COUNT                          5010L // already defined in mil.h

//==============================================================================

//==============================================================================
// M3dregControl / M3dregInquire
// Context 
#define M_ENABLE                                     -9997L // also in mil.h
#define M_DISABLE                                    -9999L // also in mil.h
#define M_TRUE                                           1L // Already defined in    mil.h, milmeas.h, miledge.h
#define M_FALSE                                          0L // Already defined in    mil.h, milmeas.h, miledge.h
#define M_AUTO                                         444L // also in mil.h
#define M_USER_DEFINED                                  21L // also in mil.h
#define M_TIMEOUT                                     2077L
#define M_MIN                                   0x02000000L // Already defined in    milmeas.h, mil.h, miledge.h
#define M_MAX                                   0x04000000L // also in mil.h
#define M_AVERAGE                               0x00000020L // also in milim.h
#define M_CENTER                                0x00000080L          // already defined in milim.h

#define M_ALLOCATION_FAILURE_REAL_TEST_FLAG            971L // also in milblob.h, milstr.h

// Context
#define M_COMPUTATION_DIRECTION                        3587               
#define M_TO_REFERENCE                                 3588
#define M_FROM_REFERENCE                               3589
#define M_STOP_CALCULATE                               116L  // also in milblob.h
#define M_CENTROID                                     1956L // already defined in mil3dim
#define M_POINT_TO_POINT                               1957L                                     
#define M_POINT_TO_PLANE                               1958L
//==============================================================================
// M3dregInquire 
// Context
#define M_NUMBER_OF_REGISTRATION_ELEMENTS             2L //already defined in milreg.h
#define M_PREREGISTRATION_MODE                     3564
#define M_RMS_ERROR_THRESHOLD                      3565
#define M_RMS_ERROR_RELATIVE_THRESHOLD             3566
#define M_ITERATION_INDEX                          3568
#define M_ERROR_MINIMIZATION_METRIC                1946L
#define M_OVERLAP                                  1966L                           
#define M_MAX_POINT_PAIR_DISTANCE                  1948L 
#define M_MAX_ITERATIONS                           1504L // Already defined in milmeas.h
#define M_ALL_ITERATIONS                     0x01000000L 
#define M_INVALID                                     -1 // also in mil.h
#define M_SUBSAMPLE                                 5091L
#define M_SUBSAMPLE_CONTEXT_ID                      3641
//==============================================================================
// M3dregAllocResult ResultTypes
#define M_PAIRWISE_REGISTRATION_RESULT               3500
#define M_REGISTRATION_COMPLETED                     3501
#define M_RMS_ERROR                                  3502
#define M_RMS_ERROR_RELATIVE                         3503
#define M_REGISTRATION_MATRIX                        3504
#define M_PREREGISTRATION_MATRIX                     3560
#define M_RMS_ERROR_THRESHOLD_REACHED                3569
#define M_RMS_ERROR_RELATIVE_THRESHOLD_REACHED       3570
#define M_MAX_ITERATIONS_REACHED                     1965L
#define M_NOT_ENOUGH_POINT_PAIRS                     1972L
#define M_NO_VALID_POINTS                            2097L
#define M_LAST_ITERATION                             -1
#define M_REGISTRATION_GLOBAL                   0x02000000L
#define M_STATUS_REGISTRATION_ELEMENT                 3925
#define M_INTERMEDIATE_ITERATION                 0x00050000L
#define M_NB_ITERATIONS                            1893L // Already defined in milim.h
//==============================================================================
// M3dregGetResult ResultTypes
// General
#define M_STATUS                                0x00008002L // already defined
#define M_EMPTY                                        236L // also in milmod.h, mildmr.h
#define M_CURRENTLY_CALCULATING                       2718L //already defined in milreg
#define M_TIMEOUT_REACHED                             2554L // also in milmod.h, mildmr.h
#define M_STOPPED_BY_REQUEST                          2555L // also in milmod.h, mildmr.h
#define M_NOT_ENOUGH_MEMORY                              4L // also in mil.h, mildmr.h
#define M_COMPLETE                              0x00000000L // also in mil.h, milmod.h, mildmr.h
#define M_INTERNAL_ERROR                                 5L // also in milcal.h, mildmr.h
//==============================================================================
// M3dregSetLocation
#define M_PREVIOUS                              0x40000003L
#define M_NEXT                                  0x40000004L
#define M_UNCHANGED                             0x40000005L

//==============================================================================
// Other defines

//==============================================================================
// CAPI function prototypes
MIL_3DREG_DLLFUNC MIL_ID MFTYPE M3dregAlloc(MIL_ID    SysId,
                                            MIL_INT64 ContextType,
                                            MIL_INT64 ControlFlag,
                                            MIL_ID*   Context3dregIdPtr);

MIL_3DREG_DLLFUNC MIL_ID MFTYPE M3dregAllocResult(MIL_ID    SysId,
                                                  MIL_INT64 ResultType,
                                                  MIL_INT64 ControlFlag,
                                                  MIL_ID*   Result3dregIdPtr);

MIL_3DREG_DLLFUNC void MFTYPE M3dregFree(MIL_ID ContextOrResult3dregId);

MIL_3DREG_DLLFUNC void MFTYPE M3dregCopyResult(MIL_ID     SrcResult3dregId,
                                               MIL_INT    SrcIndex,
                                               MIL_INT    SrcReference,
                                               MIL_ID     DstMatrix3dgeoId,
                                               MIL_INT64  CopyType,
                                               MIL_INT64  ControlFlag);

MIL_3DREG_DLLFUNC void MFTYPE M3dregCalculate(MIL_ID        Context3dregId,
                                              const MIL_ID* ContainerBufIdArrayPtr,
                                              MIL_INT       NumContainers,
                                              MIL_ID        Result3dregId,
                                              MIL_INT64     ControlFlag);

MIL_3DREG_DLLFUNC void MFTYPE M3dregCopy(MIL_ID     SrcContext3dregId,
                                         MIL_INT    SrcIndex,
                                         MIL_ID     DstMatrix3dgeoId,
                                         MIL_INT    DstIndex,
                                         MIL_INT64  CopyType,
                                         MIL_INT64  ControlFlag);

MIL_3DREG_DLLFUNC void MFTYPE M3dregSetLocation(MIL_ID     Context3dregId,
                                                MIL_INT    Index,
                                                MIL_INT    Reference,
                                                MIL_ID     ParamId,
                                                MIL_INT    ParamIndex,
                                                MIL_INT    ParamReference,
                                                MIL_INT64  ControlFlag);

MIL_3DREG_DLLFUNC void MFTYPE M3dregMerge(MIL_ID        Result3dregId,
                                          const MIL_ID* ContainerBufIdArrayPtr,
                                          MIL_INT       NumContainers,
                                          MIL_ID        DstContainerBufId,
                                          MIL_ID        SubsampleContext3dimId,
                                          MIL_INT64     ControlFlag);
//#if M_MIL_USE_64BIT
MIL_3DREG_DLLFUNC void MFTYPE M3dregControlInt64(MIL_ID     ContextOrResult3dregId,
                                                 MIL_INT64  Index,
                                                 MIL_INT64  ControlType,
                                                 MIL_INT64  ControlValue);
MIL_3DREG_DLLFUNC void MFTYPE M3dregControlDouble(MIL_ID     ContextOrResult3dregId,
                                                  MIL_INT64  Index,
                                                  MIL_INT64  ControlType,
                                                  MIL_DOUBLE ControlValue);


MIL_3DREG_DLLFUNC MIL_INT64 MFTYPE M3dregInquire(MIL_ID    ContextOrResult3dregId,
                                                 MIL_INT64 Index,
                                                 MIL_INT64 InquireType,
                                                 void*     UserVarPtr);

MIL_3DREG_DLLFUNC MIL_DOUBLE MFTYPE M3dregGetResult(MIL_ID    Result3dregId,
                                              MIL_INT64 ResultIndex,
                                              MIL_INT64 ResultType,
                                              void*     ResultArrayPtr);

#if M_MIL_USE_UNICODE
MIL_3DREG_DLLFUNC void MFTYPE M3dregSaveA(MIL_CONST_TEXTA_PTR FileName,
                                          MIL_ID      ContextOrResult3dregId,
                                          MIL_INT64   ControlFlag);

MIL_3DREG_DLLFUNC MIL_ID MFTYPE M3dregRestoreA(MIL_CONST_TEXTA_PTR FileName,
                                               MIL_ID      SysId,
                                               MIL_INT64   ControlFlag,
                                               MIL_ID*     ContextOrResult3dregIdPtr);

MIL_3DREG_DLLFUNC void MFTYPE M3dregStreamA(MIL_TEXTA_PTR MemPtrOrFileName,
                                            MIL_ID     SysId,
                                            MIL_INT64  Operation,
                                            MIL_INT64  StreamType,
                                            MIL_DOUBLE Version,
                                            MIL_INT64  ControlFlag,
                                            MIL_ID*    ContextOrResult3dregIdPtr,
                                            MIL_INT*   SizeByteVarPtr);



MIL_3DREG_DLLFUNC void MFTYPE M3dregSaveW(MIL_CONST_TEXTW_PTR FileName,
                                          MIL_ID              ContextOrResult3dregId,
                                          MIL_INT64           ControlFlag);

MIL_3DREG_DLLFUNC MIL_ID MFTYPE M3dregRestoreW(MIL_CONST_TEXTW_PTR FileName,
                                               MIL_ID              SysId,
                                               MIL_INT64           ControlFlag,
                                               MIL_ID*             ContextOrResult3dregIdPtr);

MIL_3DREG_DLLFUNC void MFTYPE M3dregStreamW(MIL_TEXTW_PTR MemPtrOrFileName,
                                            MIL_ID        SysId,
                                            MIL_INT64     Operation,
                                            MIL_INT64     StreamType,
                                            MIL_DOUBLE    Version,
                                            MIL_INT64     ControlFlag,
                                            MIL_ID*       ContextOrResult3dregIdPtr,
                                            MIL_INT*      SizeByteVarPtr);



#if M_MIL_UNICODE_API
#define M3dregSave               M3dregSaveW
#define M3dregRestore            M3dregRestoreW
#define M3dregStream             M3dregStreamW
#else
#define M3dregSave               M3dregSaveA
#define M3dregRestore            M3dregRestoreA
#define M3dregStream             M3dregStreamA
#endif //M_MIL_UNICODE_API

#else

MIL_3DREG_DLLFUNC void MFTYPE   M3dregSave(MIL_CONST_TEXT_PTR FileName,
                                           MIL_ID             ContextOrResult3dregId,
                                           MIL_INT64          ControlFlag);

MIL_3DREG_DLLFUNC MIL_ID MFTYPE M3dregRestore(MIL_CONST_TEXT_PTR FileName,
                                            MIL_ID             SysId,
                                            MIL_INT64          ControlFlag,
                                            MIL_ID*            ContextOrResult3dregIdPtr);

MIL_3DREG_DLLFUNC void MFTYPE   M3dregStream(MIL_TEXT_PTR MemPtrOrFileName,
                                             MIL_ID       SysId,
                                             MIL_INT64    Operation,
                                             MIL_INT64    StreamType,
                                             MIL_DOUBLE   Version,
                                             MIL_INT64    ControlFlag,
                                             MIL_ID*      ContextOrResult3dregIdPtr,
                                             MIL_INT*     SizeByteVarPtr);

#endif //M_MIL_USE_UNICODE
#ifdef __cplusplus
inline bool In3dregInquireDoubleRange(MIL_INT64 InquireType)
   {
   if(M_NB_ELEMENTS_BIT_SET(InquireType))
      {
      return false;
      }

   switch(M_STRIP_INQ_COMBOFLAGS(InquireType))
      {
      case M_ALLOCATION_FAILURE_REAL_TEST_FLAG:
      case M_TIMEOUT:
      //icp context
      case M_OVERLAP:
      case M_RMS_ERROR_THRESHOLD:
      case M_RMS_ERROR_RELATIVE_THRESHOLD:
      case M_MAX_POINT_PAIR_DISTANCE:
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

inline bool In3dregInquireInt64Range(MIL_INT64 InquireType)
   {
   UNREFERENCED_PARAMETER(InquireType);

   return false;
   }
inline bool M3dregInquireMustHaveUserPtr(MIL_INT64 InquireType)
   {
   const MIL_INT64 ForcedDataType = MinquireOverrides(M_STRIP_HLVLDATATYPE(InquireType), M_TYPE_MIL_INT);
   if(ForcedDataType != 0)
      {
      return false; // ForcedDataType == M_TYPE_DOUBLE;
      }
   return In3dregInquireDoubleRange(InquireType);
   }
inline bool In3dregResultDoubleRange(MIL_INT64 InquireType)
   {
   if(M_NB_ELEMENTS_BIT_SET(InquireType))
      {
      return false;
      }

   switch(M_STRIP_INQ_COMBOFLAGS(InquireType))
      {
      case M_RMS_ERROR:
      case M_RMS_ERROR_RELATIVE:
      case M_RMS_ERROR + M_INTERMEDIATE_ITERATION:
      case M_RMS_ERROR_RELATIVE + M_INTERMEDIATE_ITERATION:
      case M_RMS_ERROR + M_ALL_ITERATIONS:
      case M_RMS_ERROR_RELATIVE + M_ALL_ITERATIONS:
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
inline bool In3dregResultInt64Range(MIL_INT64 InquireType)
   {
   UNREFERENCED_PARAMETER(InquireType);
   if(M_NB_ELEMENTS_BIT_SET(InquireType))
      {
      return false;
      }

   return false;
   }
inline bool M3dregResultMustHaveUserPtr(MIL_INT64 ResultType)
   {
   const MIL_INT64 ForcedDataType = MinquireOverrides(M_STRIP_HLVLDATATYPE(ResultType), M_TYPE_MIL_INT);
   if(ForcedDataType != 0)
      {
      return false;// ForcedDataType == M_TYPE_MIL_INT64;
      }
   return In3dregResultInt64Range(ResultType);
   }
#endif // __cplusplus
/* C++ directive if needed */
#ifdef __cplusplus
}
#endif
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
//C++ overloads

inline void MFTYPE M3dregStreamCpp(MilStreamParam MemPtrOrFileName,
                                  MIL_ID         SysId,
                                  MIL_INT64      Operation,
                                  MIL_INT64      StreamType,
                                  MIL_DOUBLE     Version,
                                  MIL_INT64      ControlFlag,
                                  MIL_ID*        ContextOrResult3dregIdPtr,
                                  MIL_INT*       SizeByteVarPtr)
   {
   M3dregStream(MemPtrOrFileName.m_Param, SysId, Operation, StreamType, Version, ControlFlag, ContextOrResult3dregIdPtr, SizeByteVarPtr);
   }

#undef  M3dregStream
#define M3dregStream M3dregStreamCpp
#else

#endif // __cplusplus


//==============================================================================

#ifdef __cplusplus
inline MIL_INT64 M3dregInquireDataType(MIL_INT64 InquireType)
   {
   const MIL_INT64 ForcedDataType = MinquireOverrides(InquireType, M_TYPE_MIL_INT);
   if(ForcedDataType != 0)
      return ForcedDataType;

   if(In3dregInquireDoubleRange(InquireType))
      return M_TYPE_DOUBLE;

   if(In3dregResultInt64Range(InquireType))
      return M_TYPE_MIL_INT64;

   return M_TYPE_MIL_INT;
   }
//result
inline MIL_INT64 M3dregResultDataType(MIL_INT64 InquireType)
   {
   const MIL_INT64 ForcedDataType = MinquireOverrides(InquireType, M_TYPE_MIL_INT);
   if(ForcedDataType != 0)
      return ForcedDataType;

   if(In3dregResultDoubleRange(InquireType))
      return M_TYPE_DOUBLE;

   if(In3dregResultInt64Range(InquireType))
      return M_TYPE_MIL_INT64;

   return M_TYPE_MIL_INT;
   }
// ----------------------------------------------------------
// M3dregInquire
#if M_MIL_USE_SAFE_TYPE

inline MIL_INT64 MFTYPE M3dregInquireSafeType(MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64  InquireType, int UserVarPtr)
   {
   bool MustHaveUserPointer = M3dregInquireMustHaveUserPtr(InquireType);

   if(UserVarPtr)
      SafeTypeError(MIL_TEXT("M3dregInquire"));

   if(!UserVarPtr && MustHaveUserPointer)
      SafeTypeError(MIL_TEXT("M3dregInquire"), MIL_TEXT("The specified InquireType requires a non-null output pointer."));

   return M3dregInquire(ContextOrResult3dregId,Index, InquireType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT64 MFTYPE M3dregInquireSafeType(MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64  InquireType, std::nullptr_t)
   {
   bool MustHaveUserPointer = M3dregInquireMustHaveUserPtr(InquireType);

   if(MustHaveUserPointer)
      SafeTypeError(MIL_TEXT("M3dregInquire"),MIL_TEXT("The specified InquireType requires a non-null output pointer."));

   return M3dregInquire(ContextOrResult3dregId,Index, InquireType, NULL);
   }
#endif // M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT64 MFTYPE M3dregInquireSafeTypeExecute(MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64  InquireType, void  *UserVarPtr, MIL_INT64  GivenType)
   {
   MIL_INT64  RequiredType = M3dregInquireDataType(InquireType);
   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if(RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("M3dregInquire"));

   return M3dregInquire(ContextOrResult3dregId, Index,InquireType, UserVarPtr);
   }
inline MIL_INT64 MFTYPE M3dregInquireUnsafe  (MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64 InquireType   , void*     UserVarPtr) { return M3dregInquire(ContextOrResult3dregId,Index, InquireType, UserVarPtr); }
inline MIL_INT64 MFTYPE M3dregInquireSafeType(MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64 InquireType , MIL_INT8*   UserVarPtr) { return M3dregInquireSafeTypeExecute(ContextOrResult3dregId, Index, InquireType, UserVarPtr, M_TYPE_CHAR); }
inline MIL_INT64 MFTYPE M3dregInquireSafeType(MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64  InquireType, MIL_INT16*  UserVarPtr) { return M3dregInquireSafeTypeExecute(ContextOrResult3dregId, Index, InquireType, UserVarPtr, M_TYPE_SHORT); }
inline MIL_INT64 MFTYPE M3dregInquireSafeType(MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64 InquireType , MIL_INT32*  UserVarPtr) { return M3dregInquireSafeTypeExecute(ContextOrResult3dregId, Index, InquireType, UserVarPtr, M_TYPE_MIL_INT32); }
inline MIL_INT64 MFTYPE M3dregInquireSafeType(MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64 InquireType , MIL_INT64*  UserVarPtr) { return M3dregInquireSafeTypeExecute(ContextOrResult3dregId, Index, InquireType, UserVarPtr, M_TYPE_MIL_INT64); }
inline MIL_INT64 MFTYPE M3dregInquireSafeType(MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64 InquireType , MIL_FLOAT*  UserVarPtr) { return M3dregInquireSafeTypeExecute(ContextOrResult3dregId, Index, InquireType, UserVarPtr, M_TYPE_FLOAT); }
inline MIL_INT64 MFTYPE M3dregInquireSafeType(MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64 InquireType , MIL_DOUBLE* UserVarPtr) { return M3dregInquireSafeTypeExecute(ContextOrResult3dregId, Index, InquireType, UserVarPtr, M_TYPE_MIL_DOUBLE); }
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline MIL_INT64 MFTYPE M3dregInquireSafeType(MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64 InquireType, MIL_UINT8*  UserVarPtr) { return M3dregInquireSafeTypeExecute(ContextOrResult3dregId, Index, InquireType, UserVarPtr, M_TYPE_CHAR); }
inline MIL_INT64 MFTYPE M3dregInquireSafeType(MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64 InquireType, MIL_UINT16* UserVarPtr) { return M3dregInquireSafeTypeExecute(ContextOrResult3dregId, Index, InquireType, UserVarPtr, M_TYPE_SHORT); }
inline MIL_INT64 MFTYPE M3dregInquireSafeType(MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64 InquireType, MIL_UINT32* UserVarPtr) { return M3dregInquireSafeTypeExecute(ContextOrResult3dregId, Index, InquireType, UserVarPtr, M_TYPE_MIL_INT32); }
inline MIL_INT64 MFTYPE M3dregInquireSafeType(MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64 InquireType, MIL_UINT64* UserVarPtr) { return M3dregInquireSafeTypeExecute(ContextOrResult3dregId, Index, InquireType, UserVarPtr, M_TYPE_MIL_INT64); }
#endif
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T
inline MIL_INT64 MFTYPE M3dregInquireSafeType(MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64  InquireType, wchar_t*    UserVarPtr) { return M3dregInquireSafeTypeExecute(ContextOrResult3dregId, Index, InquireType, UserVarPtr, M_TYPE_STRING); }//or M_TYPE_SHORT??
#endif

#define M3dregInquire           M3dregInquireSafeType
#else // #if M_MIL_USE_SAFE_TYPE
#define M3dregInquireUnsafe     M3dregInquire
#endif // #if M_MIL_USE_SAFE_TYPE


#if M_MIL_USE_SAFE_TYPE
// -------------------------------------------------------------------------
// M3dregGetResult safe type definitions
// 
inline MIL_DOUBLE MFTYPE M3dregGetResultSafeType(MIL_ID Result3dregId,MIL_INT64 ResultIndex, MIL_INT64 ResultType, int ResultPtr)
   {
   bool MustHaveUserPointer = M3dregResultMustHaveUserPtr(ResultType);

   if(ResultPtr)
      SafeTypeError(MIL_TEXT("M3dregGetResult"));

   if(!ResultPtr && MustHaveUserPointer)
      SafeTypeError(MIL_TEXT("M3dregGetResult"), MIL_TEXT("The specified ResultType requires a non-null output pointer."));

   return M3dregGetResult(Result3dregId,ResultIndex, ResultType, NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_DOUBLE MFTYPE M3dregGetResultSafeType(MIL_ID Result3dregId, MIL_INT64 ResultIndex, MIL_INT64 ResultType, std::nullptr_t)
   {
   bool MustHaveUserPointer = M3dregResultMustHaveUserPtr(ResultType);

   if(MustHaveUserPointer)
      SafeTypeError(MIL_TEXT("M3dregGetResult"), MIL_TEXT("The specified ResultType requires a non-null output pointer."));

   return M3dregGetResult(Result3dregId, ResultIndex, ResultType, NULL);
   }
#endif
inline MIL_DOUBLE M3dregGetResultSafeTypeExecute(MIL_ID Result3dregId, MIL_INT64 ResultIndex, MIL_INT64 ResultType, void* ResultArrayPtr, MIL_INT64 GivenType)
   {
   MIL_INT64  RequiredType = M3dregResultDataType(ResultType);

   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if(RequiredType != GivenType)
      SafeTypeError(MIL_TEXT("M3dregGetResult"));

   return M3dregGetResult(Result3dregId, ResultIndex, ResultType, ResultArrayPtr);
   }
//=========================================================
// See milos.h for explanation about these functions.
//=========================================================

// -------------------------------------------------------------------------
// M3dregGetResult safe type 
inline MIL_DOUBLE MFTYPE M3dregGetResultUnsafe  (MIL_ID Result3dregId, MIL_INT64 ResultIndex, MIL_INT64 ResultType  , void*      ResultArrayPtr) { return M3dregGetResult(Result3dregId, ResultIndex, ResultType, ResultArrayPtr); }
inline MIL_DOUBLE MFTYPE M3dregGetResultSafeType(MIL_ID Result3dregId, MIL_INT64 ResultIndex, MIL_INT64 ResultType, MIL_INT8*    ResultArrayPtr) { return M3dregGetResultSafeTypeExecute(Result3dregId, ResultIndex, ResultType, ResultArrayPtr, M_TYPE_CHAR); }
inline MIL_DOUBLE MFTYPE M3dregGetResultSafeType(MIL_ID Result3dregId, MIL_INT64 ResultIndex, MIL_INT64 ResultType, MIL_INT16*   ResultArrayPtr) { return M3dregGetResultSafeTypeExecute(Result3dregId, ResultIndex, ResultType, ResultArrayPtr, M_TYPE_SHORT); }
inline MIL_DOUBLE MFTYPE M3dregGetResultSafeType(MIL_ID Result3dregId, MIL_INT64 ResultIndex, MIL_INT64 ResultType, MIL_INT32*   ResultArrayPtr) { return M3dregGetResultSafeTypeExecute(Result3dregId, ResultIndex, ResultType, ResultArrayPtr, M_TYPE_MIL_INT32); }
inline MIL_DOUBLE MFTYPE M3dregGetResultSafeType(MIL_ID Result3dregId, MIL_INT64 ResultIndex, MIL_INT64 ResultType, MIL_INT64*   ResultArrayPtr) { return M3dregGetResultSafeTypeExecute(Result3dregId, ResultIndex, ResultType, ResultArrayPtr, M_TYPE_MIL_INT64); }
inline MIL_DOUBLE MFTYPE M3dregGetResultSafeType(MIL_ID Result3dregId, MIL_INT64 ResultIndex, MIL_INT64 ResultType, float*       ResultArrayPtr) { return M3dregGetResultSafeTypeExecute(Result3dregId, ResultIndex, ResultType, ResultArrayPtr, M_TYPE_FLOAT); }
inline MIL_DOUBLE MFTYPE M3dregGetResultSafeType(MIL_ID Result3dregId, MIL_INT64 ResultIndex, MIL_INT64 ResultType, MIL_DOUBLE*  ResultArrayPtr) { return M3dregGetResultSafeTypeExecute(Result3dregId, ResultIndex, ResultType, ResultArrayPtr, M_TYPE_MIL_DOUBLE); }

#if M_MIL_UNICODE_API
inline MIL_DOUBLE MFTYPE M3dregGetResultSafeType(MIL_ID Result3dregId, MIL_INT64 ResultIndex, MIL_INT64 ResultType, MIL_TEXT_PTR ResultArrayPtr) { return M3dregGetResultSafeTypeExecute(Result3dregId, ResultIndex, ResultType, ResultArrayPtr, M_TYPE_STRING); }
#endif

#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline MIL_DOUBLE MFTYPE M3dregGetResultSafeType(MIL_ID Result3dregId, MIL_INT64 ResultIndex, MIL_INT64 ResultType, MIL_UINT8*  ResultArrayPtr) { return M3dregGetResultSafeTypeExecute(Result3dregId, ResultIndex, ResultType, ResultArrayPtr, M_TYPE_CHAR); }
inline MIL_DOUBLE MFTYPE M3dregGetResultSafeType(MIL_ID Result3dregId, MIL_INT64 ResultIndex, MIL_INT64 ResultType, MIL_UINT16* ResultArrayPtr) { return M3dregGetResultSafeTypeExecute(Result3dregId, ResultIndex, ResultType, ResultArrayPtr, M_TYPE_SHORT); }
inline MIL_DOUBLE MFTYPE M3dregGetResultSafeType(MIL_ID Result3dregId, MIL_INT64 ResultIndex, MIL_INT64 ResultType, MIL_UINT32* ResultArrayPtr) { return M3dregGetResultSafeTypeExecute(Result3dregId, ResultIndex, ResultType, ResultArrayPtr, M_TYPE_MIL_INT32); }
inline MIL_DOUBLE MFTYPE M3dregGetResultSafeType(MIL_ID Result3dregId, MIL_INT64 ResultIndex, MIL_INT64 ResultType, MIL_UINT64* ResultArrayPtr) { return M3dregGetResultSafeTypeExecute(Result3dregId, ResultIndex, ResultType, ResultArrayPtr, M_TYPE_MIL_INT64); }
#endif
//------------------------------
// Safetype functions assignment
#define M3dregGetResult            M3dregGetResultSafeType
#else // #if M_MIL_USE_SAFE_TYPE
#define M3dregGetResultUnsafe            M3dregGetResult
#endif // #if M_MIL_USE_SAFE_TYPE

#endif // __cplusplus

//#if M_MIL_USE_64BIT
#ifdef __cplusplus

//=========================================================
// M3dregControl function overloads when compiling c++ files
//=========================================================
template <typename T>
inline void M3dregControl(MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64 ControlType, T ControlValue)
   {
   M3dregControlInt64(ContextOrResult3dregId, Index, ControlType, ControlValue);
   }

inline void M3dregControl(MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64 ControlType, float ControlValue)
   { M3dregControlDouble(ContextOrResult3dregId, Index, ControlType, ControlValue); }

inline void M3dregControl(MIL_ID ContextOrResult3dregId, MIL_INT64 Index, MIL_INT64 ControlType, MIL_DOUBLE ControlValue)
   { M3dregControlDouble(ContextOrResult3dregId, Index, ControlType, ControlValue); }
#else // __cplusplus
//=========================================================
// For C file, call the default function, i.e. Double one
//=========================================================
#define M3dregControl            M3dregControlDouble
#endif // __cplusplus
//#endif // M_MIL_USE_64BIT

// ----------------------------------------------------------
// Overload for std::vector.
#if defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR
template <typename UserType>
inline MIL_INT64 MFTYPE M3dregInquire(MIL_ID ContextOrResult3dregId, MIL_INT Index, MIL_INT64  InquireType, std::vector<UserType> &UserVarPtr)
   {
   // If the given MIL data type is not the same as the SrcType, change it to the correct one
   // and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(InquireType) != 0)
      {
      SafeTypeError(MIL_TEXT("M3dregInquire"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   InquireType = M_STRIP_HLVLDATATYPE(InquireType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   M3dregInquire(ContextOrResult3dregId, Index, M_STRIP_HLVLDATATYPE(InquireType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   UserVarPtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      return M3dregInquire(ContextOrResult3dregId, Index, InquireType, &UserVarPtr[0]);
      }
   return 0;
   }
template <typename UserType>
inline MIL_DOUBLE MFTYPE M3dregGetResult(MIL_ID Result3dregId, MIL_INT Index, MIL_INT64  ResultType, std::vector<UserType> &ResultArrayPtr)
   {
   //! If the given MIL data type is not the same as the SrcType, change it to the correct one
   //! and give a warning.
   MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
   if(M_GET_HLVLDATATYPE(ResultType) != 0)
      {
      SafeTypeError(MIL_TEXT("M3dregGetResult"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
      }
#endif

   ResultType = M_STRIP_HLVLDATATYPE(ResultType) + InternalTrueDataTypeForStdVector;

   MIL_INT InternalNumberOfElementsForStdVector = 0;
   M3dregGetResult(Result3dregId, Index, M_STRIP_HLVLDATATYPE(ResultType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

   ResultArrayPtr.resize(InternalNumberOfElementsForStdVector);

   if(InternalNumberOfElementsForStdVector > 0)
      {
      M3dregGetResult(Result3dregId, Index, ResultType, &ResultArrayPtr[0]);
      }
   return 0.0;
   }
// ----------------------------------------------------------
// Overloads for std::vector in M3dregCalculate
inline void MFTYPE M3dregCalculate(MIL_ID                     Context3dregId,
                                   const std::vector<MIL_ID>& ContainerBufIdArrayPtr,
                                   MIL_INT                    NumContainers,
                                   MIL_ID                     ResultId,
                                   MIL_INT64                  ControlFlag)
   {
#if M_MIL_USE_SAFE_TYPE
   if(ContainerBufIdArrayPtr.empty())
      {
      SafeTypeError(MIL_TEXT("M3dregCalculate"), MIL_TEXT("The input vectors cannot be empty."));
      }
   if(NumContainers <= 0)
      {
      SafeTypeError(MIL_TEXT("M3dregCalculate"), MIL_TEXT("NumContainers parameter must be greater than zero."));
      }
   if(NumContainers > (MIL_INT)ContainerBufIdArrayPtr.size() && NumContainers != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("M3dregCalculate"), MIL_TEXT("NumContainers parameter must be smaller or equal (M_DEFAULT) to the size of input vector."));
      }
#endif

   if(NumContainers == M_DEFAULT || NumContainers > (MIL_INT)ContainerBufIdArrayPtr.size())
      {
      NumContainers = (MIL_INT)ContainerBufIdArrayPtr.size();
      }

   M3dregCalculate(Context3dregId,
                   &ContainerBufIdArrayPtr[0],
                   NumContainers,
                   ResultId,
                   ControlFlag);
   }
// ----------------------------------------------------------
// Overloads for std::vector in M3dregMerge
inline void MFTYPE M3dregMerge(MIL_ID        Result3dregId,
                               const std::vector<MIL_ID>&  ContainerBufIdArrayPtr,
                               MIL_INT       NumContainers,
                               MIL_ID        DstContainerBufId,
                               MIL_ID        SubsampleContext3dimId,
                               MIL_INT64     ControlFlag)
   {
#if M_MIL_USE_SAFE_TYPE
   if(ContainerBufIdArrayPtr.empty())
      {
      SafeTypeError(MIL_TEXT("M3dregMerge"), MIL_TEXT("The input vectors cannot be empty."));
      }
   if(NumContainers <= 1)
      {
      SafeTypeError(MIL_TEXT("M3dregMerge"), MIL_TEXT("NumContainers parameter must be greater than one."));
      }
   if(NumContainers > (MIL_INT)ContainerBufIdArrayPtr.size() && NumContainers != M_DEFAULT)
      {
      SafeTypeError(MIL_TEXT("M3dregMerge"), MIL_TEXT("NumContainers parameter must be smaller or equal (M_DEFAULT) to the size of input vector."));
      }
#endif

   if(NumContainers == M_DEFAULT || NumContainers > (MIL_INT)ContainerBufIdArrayPtr.size())
      {
      NumContainers = (MIL_INT)ContainerBufIdArrayPtr.size();
      }

   M3dregMerge(Result3dregId,
               &ContainerBufIdArrayPtr[0],
               NumContainers,
               DstContainerBufId,
               SubsampleContext3dimId,
               ControlFlag);
   }
// Overloads for std::vector in M3dregStream.
inline void MFTYPE M3dregStream(std::vector<MIL_UINT8> &MemPtrOrFileName,
                                MIL_ID                 SysId,
                                MIL_INT64              Operation,
                                MIL_INT64              StreamType,
                                MIL_DOUBLE             Version,
                                MIL_INT64              ControlFlag,
                                MIL_ID*                ContextOrResult3dregIdPtr,
                                MIL_INT*               SizeByteVarPtr)
   {
   MxxxStreamForStdVector(MemPtrOrFileName,
                          SysId,
                          Operation,
                          StreamType,
                          Version,
                          ControlFlag,
                          ContextOrResult3dregIdPtr,
                          SizeByteVarPtr,
                          M3dregStream);
   }

#endif // defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR
#if M_MIL_USE_STRING
/***************************************************************************/
/* 3dreg MODULE                                                              */
/***************************************************************************/
#if M_MIL_USE_UNICODE
#if M_MIL_UNICODE_API

inline void MFTYPE M3dregSaveW(const MIL_STRING& FileName, MIL_ID ContextOrResult3dregId, MIL_INT64 ControlFlag)
   {
   return M3dregSaveW(FileName.c_str(), ContextOrResult3dregId, ControlFlag);
   }

inline MIL_ID MFTYPE M3dregRestoreW(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* ContextOrResult3dregIdPtr)
   {
   return M3dregRestoreW(FileName.c_str(), SysId, ControlFlag, ContextOrResult3dregIdPtr);
   }

#else // M_MIL_UNICODE_API
inline void MFTYPE M3dregSaveA(const MIL_STRING& FileName, MIL_ID ContextOrResult3dregId, MIL_INT64 ControlFlag)
   {
   return M3dregSaveA(FileName.c_str(), ContextOrResult3dregId, ControlFlag);
   }

inline MIL_ID MFTYPE M3dregRestoreA(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* ContextOrResult3dregIdPtr)
   {
   return M3dregRestoreA(FileName.c_str(), SysId, ControlFlag, ContextOrResult3dregIdPtr);
   }

#endif /* M_MIL_UNICODE_API*/

#else // M_MIL_USE_UNICODE
inline void MFTYPE M3dregSave(const MIL_STRING& FileName, MIL_ID ContextOrResult3dregId, MIL_INT64 ControlFlag)
   {
   return M3dregSave(FileName.c_str(), ContextOrResult3dregId, ControlFlag);
   }

inline MIL_ID MFTYPE M3dregRestore(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* ContextOrResult3dregIdPtr)
   {
   return M3dregRestore(FileName.c_str(), SysId, ControlFlag, ContextOrResult3dregIdPtr);
   }

#endif /* M_MIL_USE_UNICODE */

#if M_MIL_USE_SAFE_TYPE

#if M_MIL_UNICODE_API

inline MIL_DOUBLE MFTYPE M3dregGetResultSafeType(MIL_ID Result3dregId,MIL_INT64 ResultIndex,  MIL_INT64 ResultType, MIL_STRING &ResultArrayPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((ResultType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("M3dregGetResult: Result Type not supported with MIL_STRING."));
      }
#endif

   MIL_INT InternalStringSize = 0;

   M3dregGetResultSafeType(Result3dregId, ResultIndex, (ResultType & (~M_HLVLDATATYPE_MASK)) + M_STRING_SIZE + M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      if(ResultArrayPtr.size() < (MIL_UINT)InternalStringSize)
         {
         ResultArrayPtr.resize((MIL_UINT)InternalStringSize);
         }
      }

   M3dregGetResultSafeTypeExecute(Result3dregId, ResultIndex, ResultType, &ResultArrayPtr[0], M_TYPE_STRING);
   return 0.0;
   }
#endif /* M_MIL_UNICODE_API */
#else
//M3dregGetResult is only defined in UNICODE
#if M_MIL_UNICODE_API
inline MIL_DOUBLE MFTYPE M3dregGetResult(MIL_ID Result3dregId,MIL_INT64 Index, MIL_INT64 ResultType, MIL_STRING   &ResultArrayPtr)
   {

   MIL_INT InternalStringSize = 0;

   //Inquire the byte content
   M3dregGetResult(Result3dregId, Index, (ResultType & (~M_HLVLDATATYPE_MASK)) + M_STRING_SIZE + M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ResultArrayPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      M3dregGetResult(Result3dregId, Index, ResultType, &ResultArrayPtr[0]);
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
template <> inline bool MilIsCorrectObjectType<&M3dregFree>(MIL_INT64 ObjectType)
   {
   return (ObjectType & ~M_USER_DEFINE_LOW_ATTRIBUTE) == M_3DREG_OBJECT;
   }
#endif

typedef MIL_UNIQUE_ID<&M3dregFree> MIL_UNIQUE_3DREG_ID;

#if M_MIL_USE_MOVE_SEMANTICS

inline MIL_UNIQUE_3DREG_ID M3dregAlloc(MIL_ID SysId, MIL_INT64 ObjectType, MIL_INT64 InitFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DREG_ID(M3dregAlloc(SysId, ObjectType, InitFlag, M_NULL));
   }
inline MIL_UNIQUE_3DREG_ID M3dregAllocResult(MIL_ID SysId, MIL_INT64 ResultType, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DREG_ID(M3dregAllocResult(SysId, ResultType, ControlFlag, M_NULL));
   }
inline MIL_UNIQUE_3DREG_ID M3dregRestore(MIL_CONST_TEXT_PTR FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DREG_ID(M3dregRestore(FileName, SysId, ControlFlag, M_NULL));
   }
#if M_MIL_USE_STRING
inline MIL_UNIQUE_3DREG_ID M3dregRestore(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DREG_ID(M3dregRestore(FileName.c_str(), SysId, ControlFlag, M_NULL));
   }
#endif // M_MIL_USE_STRING
template <MilFreeFuncType FreeFunc> inline void M3dregFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

inline void M3dregStream(MilStreamParam       MemPtrOrFileName,
                         MIL_ID               SysId,
                         MIL_INT64            Operation,
                         MIL_INT64            StreamType,
                         MIL_DOUBLE           Version,
                         MIL_INT64            ControlFlag,
                         MIL_UNIQUE_3DREG_ID* Context3dregIdPtr,
                         MIL_INT*             SizeByteVarPtr)
   {
   MxxxStreamForMilUniqueId(MemPtrOrFileName, SysId, Operation, StreamType, Version, ControlFlag, Context3dregIdPtr, SizeByteVarPtr, M3dregStream);
   }
inline void M3dregCalculate(MIL_ID ContextId, MilConstArrayIdParam ContArrayPtr, MIL_INT NumContainers, MIL_ID  ResultorMatrixId, MIL_INT64  ControlFlag)
   {
   M3dregCalculate(ContextId, ContArrayPtr.m_IdArrayPtr, NumContainers, ResultorMatrixId, ControlFlag);
   }
inline void MFTYPE M3dregMerge(MIL_ID Result3dregId, MilConstArrayIdParam  ContainerArrayPtr, MIL_INT NumContainers, MIL_ID DstContainerId, MIL_ID SubsampleContext3dimId, MIL_INT64 ControlFlag)
   {
   M3dregMerge(Result3dregId, ContainerArrayPtr.m_IdArrayPtr, NumContainers, DstContainerId, SubsampleContext3dimId, ControlFlag);
   }

#endif // M_MIL_USE_MOVE_SEMANTICS
#endif // M_MIL_USE_MIL_UNIQUE_ID

// End of MIL_UNIQUE_ID support
////////////////////////////////////////////////////////////////////////////////

#endif // !M_MIL_LITE
#endif // __MIL_3DREG_H__
