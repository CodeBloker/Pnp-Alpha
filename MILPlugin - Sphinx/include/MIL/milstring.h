/***************************************************************************/
/*

    Filename:  MILSTRING.H
    Owner   :  Matrox Imaging
    Revision:  10.40.0881
    Content :  This file contains the MIL_STRING overload for the Matrox
    Imaging Library (MIL)

    Copyright © Matrox Electronic Systems Ltd., 1992-2021.
    All Rights Reserved
    */
/***************************************************************************/
#ifndef __MILPROTO_H
#error milproto.h required
#else

#ifndef __MILSTRING_H__
#define __MILSTRING_H__

/************************************************************************/
/* SUPPORT FOR MIL_STRING                                               */
/************************************************************************/
#ifndef M_MIL_USE_STRING
#if defined(__cplusplus) && !defined(__MIL_AVX_H__) && (!defined(M_LINUX_KERNEL) || !M_LINUX_KERNEL) && (!defined(M_WINDOWS_NT_KERNEL_MODE) || !M_WINDOWS_NT_KERNEL_MODE)
   #define M_MIL_USE_STRING 1
#else
   #define M_MIL_USE_STRING 0
#endif
#endif

#if M_MIL_USE_STRING

#if M_MIL_USE_LINUX
#include <string.h>
#endif
#include <string>
#include <sstream>

#define M_STATIC_STRING_SIZE 64

typedef std::basic_string<MIL_TEXT_CHAR, std::char_traits<MIL_TEXT_CHAR>, std::allocator<MIL_TEXT_CHAR> >
MIL_STRING;

typedef std::basic_stringstream<MIL_TEXT_CHAR, std::char_traits<MIL_TEXT_CHAR>, std::allocator<MIL_TEXT_CHAR> >
MIL_STRING_STREAM;

#if M_MIL_UNICODE_API                    
#define M_TO_STRING(X) std::to_wstring(X)
#else                                     
#define M_TO_STRING(X) std::to_string(X)
#endif

#if (MIL_COMPILE_VERSION < MIL_COMPILE_TRUNK_VERSION)
#define milstring       MIL_STRING
#define milstringstream MIL_STRING_STREAM
#endif

#if M_MIL_UNICODE_API
#if (!defined(M_WINDOWS_NT_KERNEL_MODE) || !M_WINDOWS_NT_KERNEL_MODE)
#define     MOs_UseDeprecatedStrLength   wcslen
#endif
#elif (M_MIL_USE_WINDOWS)
#if !(defined(M_WINDOWS_NT_KERNEL_MODE) && M_WINDOWS_NT_KERNEL_MODE) 
#define     MOs_UseDeprecatedStrLength   strlen
#endif // !M_WINDOWS_NT_KERNEL_MODE 
#elif M_MIL_USE_LINUX
#define     MOs_UseDeprecatedStrLength   strlen
#endif

/***************************************************************************/
/* FUNC MODULE                                                             */
/***************************************************************************/
inline void MFTYPE MfuncParamValue(MIL_ID ContextFuncId, MIL_INT ParamIndex, MIL_STRING &ParamValuePtr)
   {
   //No need to inquire text since MfuncParamMilText will return the address of the string content
   MfuncParamValue(ContextFuncId, ParamIndex, const_cast<MIL_TEXT_PTR>(ParamValuePtr.c_str()));
   }

inline void MFTYPE MfuncParamMilText(MIL_ID ContextFuncId, MIL_INT ParamIndex, MIL_STRING &ParamValuePtr, MIL_INT NumOfItems, MIL_INT Attribute)
   {
   //No need to inquire text since MfuncParamMilText will return the address of the string content
   MfuncParamMilText(ContextFuncId, ParamIndex, const_cast<MIL_TEXT_PTR>(ParamValuePtr.c_str()), NumOfItems, Attribute);
   }

inline void MFTYPE MfuncParamConstMilText(MIL_ID ContextFuncId, MIL_INT ParamIndex, const MIL_STRING &ParamValuePtr, MIL_INT NumOfItems, MIL_INT Attribute)
   {
   MfuncParamConstMilText(ContextFuncId, ParamIndex, ParamValuePtr.c_str(), NumOfItems, Attribute);
   }

inline void MFTYPE MfuncParamFilename(MIL_ID ContextFuncId, MIL_INT ParamIndex, const MIL_STRING& ParamValuePtr, MIL_INT NumOfItems, MIL_INT Attribute)
   {
   MfuncParamFilename(ContextFuncId, ParamIndex, ParamValuePtr.c_str(), NumOfItems, Attribute);
   }

inline MIL_ID MFTYPE MfuncAlloc(const MIL_STRING &FunctionName, MIL_INT ParameterNum, MIL_FUNC_FUNCTION_PTR SlaveFunctionPtr, const MIL_STRING &SlaveFunctionDLLName,
                                const MIL_STRING &SlaveFunctionName, MIL_INT SlaveFunctionOpcode, MIL_INT64 InitFlag, MIL_ID *CBasedContextFuncIdPtr)
   {
   return MfuncAlloc(FunctionName.c_str(), ParameterNum, SlaveFunctionPtr, SlaveFunctionDLLName.c_str(), SlaveFunctionName.c_str(), SlaveFunctionOpcode, InitFlag, CBasedContextFuncIdPtr);
   }

inline MIL_ID MFTYPE MfuncAllocScript(const MIL_STRING &FunctionName, MIL_INT ParameterNum, const MIL_STRING &InterpreterLanguage, const MIL_STRING &ScriptFileName,
                                      const MIL_STRING &ScriptFunctionName, MIL_INT ScriptFunctionOpcode, MIL_INT64 InitFlag, MIL_ID *ScriptBasedContextFuncIdPtr)
   {
   return MfuncAllocScript(FunctionName.c_str(), ParameterNum, InterpreterLanguage.c_str(), ScriptFileName.c_str(), ScriptFunctionName.c_str(),
                           ScriptFunctionOpcode, InitFlag, ScriptBasedContextFuncIdPtr);
   }

inline MIL_ID MFTYPE MfuncAllocScript(const MIL_STRING &FunctionName, MIL_INT ParameterNum, MIL_CONST_TEXT_PTR InterpreterLanguage, const MIL_STRING &ScriptFileName,
                                      const MIL_STRING &ScriptFunctionName, MIL_INT ScriptFunctionOpcode, MIL_INT64 InitFlag, MIL_ID *ScriptBasedContextFuncIdPtr)
   {
   return MfuncAllocScript(FunctionName.c_str(), ParameterNum, InterpreterLanguage, ScriptFileName.c_str(), ScriptFunctionName.c_str(),
                           ScriptFunctionOpcode, InitFlag, ScriptBasedContextFuncIdPtr);
   }

inline MIL_INT MFTYPE MfuncErrorReport(MIL_ID ContextFuncId, MIL_INT ErrorCode, const MIL_STRING &ErrorMessage, const MIL_STRING &ErrorSubMessage1,
                                       const MIL_STRING &ErrorSubMessage2, const MIL_STRING &ErrorSubMessage3)
   {
   return MfuncErrorReport(ContextFuncId, ErrorCode, ErrorMessage.c_str(), ErrorSubMessage1.c_str(), ErrorSubMessage2.c_str(), ErrorSubMessage3.c_str());
   }

inline MIL_INT MFTYPE MfuncPrintMessage(MIL_INT Mode, const MIL_STRING &Str1, const MIL_STRING &Str2, const MIL_STRING &Str3, const MIL_STRING &Str4, const MIL_STRING &Str5)
   {
   return MfuncPrintMessage(Mode, Str1.c_str(), Str2.c_str(), Str3.c_str(), Str4.c_str(), Str5.c_str());
   }

//// MfuncInquireSafeType is not activated because too many undocumented InquireTypes with various pointer types.
//#if M_MIL_USE_SAFE_TYPE
//inline MIL_INT MFTYPE MfuncInquireSafeType(MIL_ID ObjectId, MIL_INT64 InquireType, MIL_STRING    &UserVarPtr)
//   {
//   MIL_INT RetValue = 0;
//
//   //Test if InquireType is in string range
//   if(M_IN_FUNC_INQUIRE_STRING_RANGE(InquireType))
//      {
//      MIL_INT InternalStringSize = 0;
//      MfuncInquireSafeType(ObjectId, InquireType + M_STRING_SIZE, &InternalStringSize);
//
//      if(InternalStringSize > 0)
//         {
//         UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
//         RetValue = MfuncInquireSafeTypeExecute(ObjectId, InquireType, &UserVarPtr[0], M_TYPE_TEXT_CHAR);
//         UserVarPtr.resize(InternalStringSize - 1);
//         }
//      }
//   else
//      {
//      SafeTypeError(MIL_TEXT("MfuncInquire: Inquire type not in string range"));
//      }
//   return RetValue;
//   }
//
//#else
inline MIL_INT MFTYPE MfuncInquire(MIL_ID ObjectId, MIL_INT64 InquireType, MIL_STRING    &UserVarPtr)
   {
   MIL_INT RetValue = 0;
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InquireType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MfuncInquire"), MIL_TEXT("Inquire type not supported with MIL_STRING."));
      }
#endif

   MIL_INT InternalStringSize = 0;
   MfuncInquire(ObjectId, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MfuncInquire(ObjectId, InquireType, &UserVarPtr[0]);
      UserVarPtr.resize(InternalStringSize - 1);
      
      }

   return RetValue;
   }
//#endif

/***************************************************************************/
/* GRAPHIC MODULE                                                          */
/***************************************************************************/
#if M_MIL_USE_64BIT
inline void MFTYPE MgraText(MIL_ID ContextGraId, MIL_ID DstImageBufOrListGraId, const MCppParameter& XStart, const MCppParameter& YStart, MIL_STRING StringPtr)
   {
   MgraText(ContextGraId, DstImageBufOrListGraId, XStart, YStart, (MIL_CONST_TEXT_PTR)StringPtr.c_str());
   }
#else //different prototype are used for 32-bit
inline void MFTYPE MgraText(MIL_ID ContextGraId, MIL_ID DstImageBufOrListGraId, MIL_DOUBLE XStart, MIL_DOUBLE YStart, MIL_STRING StringPtr)
   {
   MgraText(ContextGraId, DstImageBufOrListGraId, XStart, YStart, (MIL_CONST_TEXT_PTR)StringPtr.c_str());
   }

#endif //M_MIL_USE_64BIT

/***************************************************************************/
/* BUFFER MODULE                                                          */
/***************************************************************************/
inline void MFTYPE MbufExportSequence(const MIL_STRING& FileName, MIL_INT64 FileFormat, const MIL_ID * BufArrayPtrOrSystemIdPtr, MIL_INT NumOfIds, MIL_DOUBLE FrameRate, MIL_INT64 ControlFlag)
   {
   return MbufExportSequence(FileName.c_str(), FileFormat, BufArrayPtrOrSystemIdPtr, NumOfIds, FrameRate, ControlFlag);
   }

inline void MFTYPE MbufExport(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_ID SrcBufId)
   {
   return MbufExport(FileName.c_str(), FileFormat, SrcBufId);
   }

inline void MFTYPE MbufImportSequence(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_INT64 Operation, MIL_ID SystemId, MIL_ID *BufArrayPtr, MIL_INT StartImage, MIL_INT NumberOfImages, MIL_INT64 ControlFlag)
   {
   return MbufImportSequence(FileName.c_str(), FileFormat, Operation, SystemId, BufArrayPtr, StartImage, NumberOfImages, ControlFlag);
   }

inline MIL_ID MFTYPE MbufImport(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_INT64 Operation, MIL_ID SystemId, MIL_ID* BufIdPtr)
   {
   return MbufImport(FileName.c_str(), FileFormat, Operation, SystemId, BufIdPtr);
   }

inline void MFTYPE MbufLoad(const MIL_STRING& FileName, MIL_ID BufId)
   {
   return MbufLoad(FileName.c_str(), BufId);
   }

inline MIL_ID MFTYPE MbufRestore(const MIL_STRING& FileName, MIL_ID SystemId, MIL_ID* BufIdPtr)
   {
   return MbufRestore(FileName.c_str(), SystemId, BufIdPtr);
   }

inline void MFTYPE MbufSave(const MIL_STRING& FileName, MIL_ID BufId)
   {
   return MbufSave(FileName.c_str(), BufId);
   }

#if M_MIL_USE_SAFE_TYPE

inline MIL_INT MFTYPE MbufDiskInquireSafeType(const MIL_STRING& FileName, MIL_INT64 InquireType, int UserVarPtr)
   {
   if(UserVarPtr != M_NULL)
      SafeTypeError(MIL_TEXT("MbufDiskInquire"));

   return MbufDiskInquire(FileName.c_str(), InquireType, M_NULL);
   }
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT MFTYPE MbufDiskInquireSafeType(const MIL_STRING& FileName, MIL_INT64 InquireType, std::nullptr_t)
   {
   return MbufDiskInquire(FileName.c_str(), InquireType, M_NULL);
   }
#endif
inline MIL_INT MFTYPE MbufDiskInquireUnsafe(const MIL_STRING& FileName, MIL_INT64 InquireType, void        *UserVarPtr) { return MbufDiskInquireUnsafe(FileName.c_str(), InquireType, UserVarPtr); }
inline MIL_INT MFTYPE MbufDiskInquireSafeType(const MIL_STRING& FileName, MIL_INT64 InquireType, MIL_INT     *UserVarPtr) { return MbufDiskInquireSafeTypeExecute(FileName.c_str(), InquireType, UserVarPtr, M_TYPE_MIL_INT); }
inline MIL_INT MFTYPE MbufDiskInquireSafeType(const MIL_STRING& FileName, MIL_INT64 InquireType, MIL_DOUBLE  *UserVarPtr) { return MbufDiskInquireSafeTypeExecute(FileName.c_str(), InquireType, UserVarPtr, M_TYPE_DOUBLE); }
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline MIL_INT MFTYPE MbufDiskInquireSafeType(const MIL_STRING& FileName, MIL_INT64 InquireType, MIL_UINT    *UserVarPtr) { return MbufDiskInquireSafeTypeExecute(FileName.c_str(), InquireType, UserVarPtr, M_TYPE_MIL_INT); }
#endif

#if (MIL_COMPILE_VERSION >= 1020)
inline void MFTYPE MbufInquireFeatureSafeType(MIL_ID BufId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_STRING    &UserVarPtr)
   {
   UNREFERENCED_PARAMETER(UserVarType);
   MIL_INT InternalStringSize = 0;
   MbufInquireFeatureSafeType(BufId, InquireType + M_STRING_SIZE, FeatureName.c_str(), M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      MbufInquireFeatureExecute(BufId, InquireType, FeatureName.c_str(), M_TYPE_STRING + M_FEATURE_USER_ARRAY_SIZE(InternalStringSize), &UserVarPtr[0], M_TYPE_TEXT_CHAR);
      UserVarPtr.resize(InternalStringSize - 1);

      }
   }

inline void MFTYPE MbufInquireFeatureSafeType(MIL_ID BufId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_INT64      *UserVarPtr)
   {
   MbufInquireFeatureExecute(BufId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_INT64);
   }
inline void MFTYPE MbufInquireFeatureSafeType(MIL_ID BufId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_DOUBLE     *UserVarPtr)
   {
   MbufInquireFeatureExecute(BufId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_DOUBLE);
   }
inline void MFTYPE MbufInquireFeatureSafeType(MIL_ID BufId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_INT32      *UserVarPtr)
   {
   MbufInquireFeatureExecute(BufId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_MIL_INT32);
   }
inline void MFTYPE MbufInquireFeatureSafeType(MIL_ID BufId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_UINT8      *UserVarPtr)
   {
   MbufInquireFeatureExecute(BufId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_UINT8);
   }
inline void MFTYPE MbufInquireFeatureSafeType(MIL_ID BufId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, bool           *UserVarPtr)
   {
   SafeTypeError(MIL_TEXT("MbufInquireFeature"));

   MbufInquireFeature(BufId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MbufInquireFeatureSafeType(MIL_ID BufId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, int             UserVarPtr)
   {
   if(UserVarPtr != 0)
      SafeTypeError(MIL_TEXT("MbufInquireFeature"));

   MbufInquireFeature(BufId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MbufInquireFeatureSafeType(MIL_ID BufId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, std::nullptr_t            )
   {
   MbufInquireFeature(BufId, InquireType, FeatureName.c_str(), UserVarType, M_NULL);
   }
#endif
inline void MFTYPE MbufControlFeatureSafeType(MIL_ID BufId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_STRING&        UserVarPtr)
   {
   MbufControlFeatureExecute(BufId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr.c_str(), M_TYPE_TEXT_CHAR);
   }
inline void MFTYPE MbufControlFeatureSafeType(MIL_ID BufId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_INT64        *UserVarPtr)
   {
   MbufControlFeatureExecute(BufId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_INT64);
   }
inline void MFTYPE MbufControlFeatureSafeType(MIL_ID BufId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_DOUBLE       *UserVarPtr)
   {
   MbufControlFeatureExecute(BufId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_DOUBLE);
   }
inline void MFTYPE MbufControlFeatureSafeType(MIL_ID BufId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_INT32        *UserVarPtr)
   {
   MbufControlFeatureExecute(BufId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_MIL_INT32);
   }
inline void MFTYPE MbufControlFeatureSafeType(MIL_ID BufId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_UINT8        *UserVarPtr)
   {
   MbufControlFeatureExecute(BufId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_UINT8);
   }
inline void MFTYPE MbufControlFeatureSafeType(MIL_ID BufId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const bool             *UserVarPtr)
   {
   SafeTypeError(MIL_TEXT("MbufControlFeature"));

   MbufControlFeature(BufId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MbufControlFeatureSafeType(MIL_ID BufId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, int               UserVarPtr)
   {
   MbufControlFeatureExecute(BufId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, UserVarType);
   }
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MbufControlFeatureSafeType(MIL_ID BufId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, std::nullptr_t                   )
   {
   MbufControlFeatureExecute(BufId, ControlType, FeatureName.c_str(), UserVarType, M_NULL, UserVarType);
   }
#endif

#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED

inline void MFTYPE MbufControlFeatureSafeType(MIL_ID BufId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_UINT64       *UserVarPtr)
   {
   MbufControlFeatureExecute(BufId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_INT64);
   }

inline void MFTYPE MbufInquireFeatureSafeType(MIL_ID BufId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_UINT64     *UserVarPtr)
   {
   MbufInquireFeatureExecute(BufId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_INT64);
   }
#endif
#endif // MIL_COMPILE_VERSION >= 1020

#else /* MIL_SAFE_TYPE */
inline MIL_INT MFTYPE MbufDiskInquire(const MIL_STRING& FileName, MIL_INT64 InquireType, void * UserVarPtr)
   {
   return MbufDiskInquire(FileName.c_str(), InquireType, UserVarPtr);
   }

#if (MIL_COMPILE_VERSION >= 1020)   
inline void MFTYPE MbufInquireFeature(MIL_ID BufId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, void           *UserVarPtr)
   {
   MbufInquireFeature(BufId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }

#if !M_MIL_USE_SAFE_TYPE
inline void MFTYPE MbufInquireFeature(MIL_ID BufId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, MIL_STRING &UserVarPtr)
   {
   UNREFERENCED_PARAMETER(UserVarType);
   MIL_INT InternalStringSize = 0;
   MbufInquireFeature(BufId, InquireType + M_STRING_SIZE, FeatureName.c_str(), M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      MbufInquireFeature(BufId, InquireType, FeatureName.c_str(), M_TYPE_STRING + M_FEATURE_USER_ARRAY_SIZE(InternalStringSize), &UserVarPtr[0]);
      MIL_INT Len = MosStrlen(&UserVarPtr[0]);
      UserVarPtr.resize(Len);

      }
   }
#endif

inline void MFTYPE MbufControlFeature(MIL_ID BufId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, const void *UserVarPtr)
   {
   MbufControlFeature(BufId, InquireType, (MIL_CONST_TEXT_PTR)FeatureName.c_str(), UserVarType, UserVarPtr);
   }

inline void MFTYPE MbufControlFeature(MIL_ID BufId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, const MIL_STRING &UserVarPtr)
   {
   MbufControlFeature(BufId, InquireType, (MIL_CONST_TEXT_PTR)FeatureName.c_str(), UserVarType, (MIL_CONST_TEXT_PTR)UserVarPtr.c_str());
   }
#endif // MIL_COMPILE_VERSION >= 1020
#endif /* M_MIL_USE_SAFETYPE */   

/***************************************************************************/
/* APP MODULE                                                              */
/***************************************************************************/
inline void MFTYPE MappOpenConnection(const MIL_STRING& ConnectionDescriptor, MIL_INT64 InitFlag, MIL_INT64 ControlFlag, MIL_ID* RemoteContextAppIdPtr)
   {
   return MappOpenConnection(ConnectionDescriptor.c_str(), InitFlag, ControlFlag, RemoteContextAppIdPtr);
   }

inline MIL_ID MFTYPE MappAlloc(const MIL_STRING& ServerDescription, MIL_INT64 InitFlag, MIL_ID* ContextAppIdPtr)
   {
   return MappAlloc(ServerDescription.c_str(), InitFlag, ContextAppIdPtr);
   }

inline void MFTYPE MappTrace(MIL_ID ContextAppId, MIL_INT64 TraceType, MIL_INT64 TraceTag, MIL_INT64 TraceValue, const MIL_STRING &TraceString)
   {
   return MappTrace(ContextAppId, TraceType, TraceTag, TraceValue, TraceString.c_str());
   }


#if M_MIL_USE_SAFE_TYPE
inline MIL_INT MFTYPE MappGetErrorSafeType(MIL_INT64 ErrorType, MIL_STRING&      ErrorPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((ErrorType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MappGetError"), MIL_TEXT("Error type not supported with MIL_STRING."));
      }
#endif

   MIL_INT InternalStringSize = 0;
   MIL_INT RetValue = 0;
   MappGetErrorSafeType(ErrorType + M_STRING_SIZE, &InternalStringSize);
   if(InternalStringSize > 0)
      {
      ErrorPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MappGetErrorSafeTypeExecute(ErrorType, &ErrorPtr[0], M_TYPE_TEXT_CHAR);
      ErrorPtr.resize(MOs_UseDeprecatedStrLength(ErrorPtr.c_str()));
      }

   return RetValue;
   }

inline MIL_INT MFTYPE MappGetErrorSafeType(MIL_ID ContextAppId, MIL_INT64 ErrorType, MIL_STRING      &ErrorPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((ErrorType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MappGetError"), MIL_TEXT("Error type not supported with MIL_STRING."));
      }
#endif
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MappGetErrorSafeType(ContextAppId, ErrorType + M_STRING_SIZE, &InternalStringSize);
   if(InternalStringSize > 0)
      {
      ErrorPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MappGetErrorSafeTypeExecute(ContextAppId, ErrorType, &ErrorPtr[0], M_TYPE_TEXT_CHAR);
      ErrorPtr.resize(MOs_UseDeprecatedStrLength(ErrorPtr.c_str()));
      }

   return RetValue;
   }

inline MIL_INT MFTYPE MappGetHookInfoSafeType(MIL_ID EventId, MIL_INT64 InfoType, MIL_STRING       &ErrorPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InfoType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MappGetHookInfo"), MIL_TEXT("Info type not supported with MIL_STRING."));
      }
#endif
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;
   //Resize to M_ERROR_MESSAGE_SIZE first
   MappGetHookInfoSafeType(EventId, InfoType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ErrorPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MappGetHookInfoSafeTypeExecute(EventId, InfoType, &ErrorPtr[0], M_TYPE_TEXT_CHAR);
      ErrorPtr.resize(MOs_UseDeprecatedStrLength(ErrorPtr.c_str()));
      }

   return RetValue;
   }

inline MIL_INT MFTYPE MappGetHookInfoSafeType(MIL_ID ContextAppId, MIL_ID EventId, MIL_INT64 InfoType, MIL_STRING       &ResultPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InfoType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MappGetHookInfo"), MIL_TEXT("Info type not supported with MIL_STRING."));
      }
#endif
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MappGetHookInfoSafeType(ContextAppId, EventId, InfoType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ResultPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MappGetHookInfoSafeTypeExecute(ContextAppId, EventId, InfoType, &ResultPtr[0], M_TYPE_TEXT_CHAR);
      ResultPtr.resize(MOs_UseDeprecatedStrLength(ResultPtr.c_str()));
      }

   return RetValue;
   }

inline MIL_INT MFTYPE MappInquireSafeType(MIL_INT64 InquireType, MIL_STRING      &UserVarPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InquireType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MappInquire"), MIL_TEXT("Inquire type not supported with MIL_STRING."));
      }
#endif
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MappInquireSafeType(InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MappInquireSafeTypeExecute(InquireType, &UserVarPtr[0], M_TYPE_TEXT_CHAR);
      UserVarPtr.resize(MOs_UseDeprecatedStrLength(UserVarPtr.c_str()));
      }

   return RetValue;
   }

inline MIL_INT MFTYPE MappInquireSafeType(MIL_ID ContextAppId, MIL_INT64 InquireType, MIL_STRING&      UserVarPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InquireType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MappInquire"), MIL_TEXT("Inquire type not supported with MIL_STRING."));
      }
#endif
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MappInquireSafeType(ContextAppId, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MappInquireSafeTypeExecute(ContextAppId, InquireType, &UserVarPtr[0], M_TYPE_TEXT_CHAR);
      UserVarPtr.resize(MOs_UseDeprecatedStrLength(UserVarPtr.c_str()));
      }

   return RetValue;
   }

inline void MFTYPE MappFileOperationUnsafe(MIL_ID                  Comp1ContextAppId,
                                           const MIL_STRING&       Comp1FileName,
                                           MIL_ID                  Comp2ContextAppId,
                                           const MIL_STRING&       Comp2FileName,
                                           MIL_INT64               Operation,
                                           MIL_INT64               OperationFlag,
                                           void*                   OperationDataPtr)
   {
   MappFileOperationUnsafe(Comp1ContextAppId, Comp1FileName.c_str(), Comp2ContextAppId, Comp2FileName.c_str(), Operation, OperationFlag, OperationDataPtr);
   }

inline void MFTYPE MappFileOperationSafeType(MIL_ID                  Comp1ContextAppId,
                                             const MIL_STRING&       Comp1FileName,
                                             MIL_ID                  Comp2ContextAppId,
                                             const MIL_STRING&       Comp2FileName,
                                             MIL_INT64               Operation,
                                             MIL_INT64               OperationFlag,
                                             int                     OperationDataPtr)
   {
   MappFileOperationSafeType(Comp1ContextAppId, Comp1FileName.c_str(), Comp2ContextAppId, Comp2FileName.c_str(), Operation, OperationFlag, OperationDataPtr);
   }
inline void MFTYPE MappFileOperationSafeType(MIL_ID                  Comp1ContextAppId,
                                             int                     Comp1FileName,
                                             MIL_ID                  Comp2ContextAppId,
                                             const MIL_STRING&       Comp2FileName,
                                             MIL_INT64               Operation,
                                             MIL_INT64               OperationFlag,
                                             int                     OperationDataPtr)
   {
   MappFileOperationSafeType(Comp1ContextAppId, Comp1FileName, Comp2ContextAppId, Comp2FileName.c_str(), Operation, OperationFlag, OperationDataPtr);
   }
inline void MFTYPE MappFileOperationSafeType(MIL_ID                  Comp1ContextAppId,
                                             const MIL_STRING&       Comp1FileName,
                                             MIL_ID                  Comp2ContextAppId,
                                             int                     Comp2FileName,
                                             MIL_INT64               Operation,
                                             MIL_INT64               OperationFlag,
                                             int                     OperationDataPtr)
   {
   MappFileOperationSafeType(Comp1ContextAppId, Comp1FileName.c_str(), Comp2ContextAppId, Comp2FileName, Operation, OperationFlag, OperationDataPtr);
   }


inline void MFTYPE MappFileOperationSafeType(MIL_ID                     Comp1ContextAppId,
                                             const MIL_STRING&          Comp1FileName,
                                             MIL_ID                     Comp2ContextAppId,
                                             int                        Comp2FileName,
                                             MIL_INT64                  Operation,
                                             MIL_INT64                  OperationFlag,
                                             MIL_INT*                   OperationDataPtr)
   {
   MappFileOperationSafeType(Comp1ContextAppId, Comp1FileName.c_str(), Comp2ContextAppId, Comp2FileName, Operation, OperationFlag, OperationDataPtr);
   }
inline void MFTYPE MappFileOperationSafeType(MIL_ID                     Comp1ContextAppId,
                                             const MIL_STRING&          Comp1FileName,
                                             MIL_ID                     Comp2ContextAppId,
                                             int                        Comp2FileName,
                                             MIL_INT64                  Operation,
                                             MIL_INT64                  OperationFlag,
                                             MIL_TEXT_PTR               OperationDataPtr)
   {
   MappFileOperationSafeType(Comp1ContextAppId, Comp1FileName.c_str(), Comp2ContextAppId, Comp2FileName, Operation, OperationFlag, OperationDataPtr);
   }

inline void MFTYPE MappFileOperation(MIL_ID            Comp1ContextAppId,
                                     const MIL_STRING& Comp1FileName,
                                     MIL_ID            Comp2ContextAppId,
                                     const MIL_STRING& Comp2FileName,
                                     MIL_INT64         Operation,
                                     MIL_INT64         OperationFlag,
                                     void*             OperationDataPtr)
   {
   MappFileOperation(Comp1ContextAppId, Comp1FileName.c_str(), Comp2ContextAppId, Comp2FileName.c_str(), Operation, OperationFlag, OperationDataPtr);
   }

inline void MFTYPE MappFileOperation(MIL_ID            Comp1ContextAppId,
                                     const MIL_STRING& Comp1FileName,
                                     MIL_ID            Comp2ContextAppId,
                                     int               Comp2FileName,
                                     MIL_INT64         Operation,
                                     MIL_INT64         OperationFlag,
                                     void*             OperationDataPtr)
   {
   MappFileOperation(Comp1ContextAppId, Comp1FileName.c_str(), Comp2ContextAppId, (MIL_CONST_TEXT_PTR)(MIL_UINT)Comp2FileName, Operation, OperationFlag, OperationDataPtr);
   }
inline void MFTYPE MappFileOperation(MIL_ID                  Comp1ContextAppId,
                                     MIL_CONST_TEXT_PTR      Comp1FileName,
                                     MIL_ID                  Comp2ContextAppId,
                                     int                     Comp2FileName,
                                     MIL_INT64               Operation,
                                     MIL_INT64               OperationFlag,
                                     void*                   OperationDataPtr)
   {
   MappFileOperation(Comp1ContextAppId, Comp1FileName, Comp2ContextAppId,(MIL_CONST_TEXT_PTR)(MIL_UINT)Comp2FileName, Operation, OperationFlag, OperationDataPtr);
   }
inline void MFTYPE MappFileOperationSafeType(MIL_ID                     Comp1ContextAppId,
                                             const MIL_STRING&          Comp1FileName,
                                             MIL_ID                     Comp2ContextAppId,
                                             int                        Comp2FileName,
                                             MIL_INT64                  Operation,
                                             MIL_INT64                  OperationFlag,
                                             MIL_STRING&                OperationDataPtr)
   {

   MIL_INT InternalStringSize = 0;
   MappFileOperationSafeType(Comp1ContextAppId, Comp1FileName.c_str(), Comp2ContextAppId, Comp2FileName, Operation + M_STRING_SIZE, OperationFlag, &InternalStringSize);

   if (InternalStringSize > 0)
      {
      OperationDataPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      MappFileOperationSafeType(Comp1ContextAppId, Comp1FileName.c_str(), Comp2ContextAppId, Comp2FileName, Operation , OperationFlag, &OperationDataPtr[0]);
      OperationDataPtr.resize(InternalStringSize - 1);
      }
   }

#else /* !M_MIL_USE_SAFE_TYPE */

inline MIL_INT MFTYPE MappGetHookInfo(MIL_ID ContextAppId, MIL_ID EventId, MIL_INT64 InfoType, MIL_STRING       &ErrorPtr)
   {
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;
   MappGetHookInfo(ContextAppId, EventId, InfoType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ErrorPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MappGetHookInfo(ContextAppId, EventId, InfoType, &ErrorPtr[0]);
      ErrorPtr.resize(MOs_UseDeprecatedStrLength(ErrorPtr.c_str()));
      }


   return RetValue;
   }

inline MIL_INT MFTYPE MappGetHookInfo(MIL_ID EventId, MIL_INT64 InfoType, MIL_STRING       &ErrorPtr)
   {
   return MappGetHookInfo(M_DEFAULT, EventId, InfoType, ErrorPtr);
   }

inline MIL_INT MFTYPE MappInquire(MIL_ID ContextAppId, MIL_INT64 InquireType, MIL_STRING&      UserVarPtr)
   {
   MIL_INT RetValue = 0;

   MIL_INT InternalStringSize = 0;
   MappInquire(ContextAppId, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MappInquire(ContextAppId, InquireType, &UserVarPtr[0]);
      UserVarPtr.resize(MOs_UseDeprecatedStrLength(UserVarPtr.c_str()));
      }


   return RetValue;
   }

inline MIL_INT MFTYPE MappInquire(MIL_INT64 InquireType, MIL_STRING      &UserVarPtr)
   {
   return MappInquire(M_DEFAULT, InquireType, UserVarPtr);
   }
inline MIL_INT MFTYPE MappGetError(MIL_ID ContextAppId, MIL_INT64 ErrorType, MIL_STRING&      ErrorPtr)
   {
   MIL_INT RetValue = 0;


   MIL_INT InternalStringSize = 0;
   MappGetError(ContextAppId, ErrorType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ErrorPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MappGetError(ContextAppId, ErrorType, &ErrorPtr[0]);
      ErrorPtr.resize(MOs_UseDeprecatedStrLength(ErrorPtr.c_str()));
      }


   return RetValue;
   }

inline MIL_INT MFTYPE MappGetError(MIL_INT64 ErrorType, MIL_STRING& ErrorPtr)
   {
   return MappGetError(M_DEFAULT, ErrorType, ErrorPtr);
   }


inline void MFTYPE MappFileOperation(MIL_ID            Comp1ContextAppId,
                                     const MIL_STRING& Comp1FileName,
                                     MIL_ID            Comp2ContextAppId,
                                     const MIL_STRING& Comp2FileName,
                                     MIL_INT64         Operation,
                                     MIL_INT64         OperationFlag,
                                     void*             OperationDataPtr)
   {
   MappFileOperation(Comp1ContextAppId, Comp1FileName.c_str(), Comp2ContextAppId, Comp2FileName.c_str(), Operation, OperationFlag, OperationDataPtr);
   }
inline void MFTYPE MappFileOperation(MIL_ID            Comp1ContextAppId,
                                     const MIL_STRING& Comp1FileName,
                                     MIL_ID            Comp2ContextAppId,
                                     int               Comp2FileName,
                                     MIL_INT64         Operation,
                                     MIL_INT64         OperationFlag,
                                     void*             OperationDataPtr)
   {
   MappFileOperation(Comp1ContextAppId, Comp1FileName.c_str(), Comp2ContextAppId, (MIL_CONST_TEXT_PTR)(MIL_UINT)Comp2FileName, Operation, OperationFlag, OperationDataPtr);
   }
inline void MFTYPE MappFileOperation(MIL_ID                  Comp1ContextAppId,
                                     MIL_CONST_TEXT_PTR      Comp1FileName,
                                     MIL_ID                  Comp2ContextAppId,
                                     int                     Comp2FileName,
                                     MIL_INT64               Operation,
                                     MIL_INT64               OperationFlag,
                                     void*                   OperationDataPtr)
   {
   MappFileOperation(Comp1ContextAppId, Comp1FileName, Comp2ContextAppId, (MIL_CONST_TEXT_PTR)(MIL_UINT)Comp2FileName, Operation, OperationFlag, OperationDataPtr);
   }

inline void MFTYPE MappFileOperation(MIL_ID                  Comp1ContextAppId,
                                     const MIL_STRING&       Comp1FileName,
                                     MIL_ID                  Comp2ContextAppId,
                                     int                     Comp2FileName,
                                     MIL_INT64               Operation,
                                     MIL_INT64               OperationFlag,
                                     MIL_STRING&             OperationDataPtr)
   {

   MIL_INT InternalStringSize = 0;
   MappFileOperation(Comp1ContextAppId, Comp1FileName.c_str(), Comp2ContextAppId, (MIL_CONST_TEXT_PTR)(MIL_UINT)Comp2FileName, Operation + M_STRING_SIZE, OperationFlag, &InternalStringSize);
   if (InternalStringSize > 0)
      {
      OperationDataPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      MappFileOperation(Comp1ContextAppId, Comp1FileName.c_str(), Comp2ContextAppId, (MIL_CONST_TEXT_PTR)(MIL_UINT)Comp2FileName, Operation, OperationFlag, &OperationDataPtr[0]);
      OperationDataPtr.resize(InternalStringSize - 1);
      }
   }
#endif /* M_MIL_USE_SAFE_TYPE*/

/***************************************************************************/
/* SYS MODULE                                                              */
/***************************************************************************/
inline void MsysControl(MIL_ID SysId, MIL_INT64 ControlType, const MIL_STRING& ControlValue)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((ControlType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MsysControl"), MIL_TEXT("Control type not supported with MIL_STRING."));
      }
#endif

   MsysControl(SysId, ControlType, ControlValue.c_str());
   }


inline MIL_ID MFTYPE MsysAlloc(MIL_ID ContextAppId, const MIL_STRING &SystemDescriptor, MIL_INT SystemNum, MIL_INT64 InitFlag, MIL_ID* SysIdPtr)
   {
   return MsysAlloc(ContextAppId, SystemDescriptor.c_str(), SystemNum, InitFlag, SysIdPtr);
   }
inline MIL_ID MFTYPE MsysAlloc(MIL_ID ContextAppId, const MIL_STRING &SystemDescriptor, const MIL_STRING &SystemNum, MIL_INT64 InitFlag, MIL_ID* SysIdPtr)
   {
   return MsysAlloc(ContextAppId, SystemDescriptor.c_str(), SystemNum.c_str(), InitFlag, SysIdPtr);
   }

#if M_MIL_USE_SAFE_TYPE

#if (MIL_COMPILE_VERSION >= 1020)
inline void MFTYPE MsysInquireFeatureSafeType(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_STRING      &UserVarPtr)
   {
   UNREFERENCED_PARAMETER(UserVarType);
   MIL_INT InternalStringSize = 0;
   MsysInquireFeatureSafeType(SysId, InquireType + M_STRING_SIZE, FeatureName.c_str(), M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      MsysInquireFeatureExecute(SysId, InquireType, FeatureName.c_str(), M_TYPE_STRING + M_FEATURE_USER_ARRAY_SIZE(InternalStringSize), &UserVarPtr[0], M_TYPE_TEXT_CHAR);
      MIL_INT Len = MosStrlen(&UserVarPtr[0]);
      UserVarPtr.resize(Len);

      }
   }
inline void MFTYPE MsysInquireFeatureSafeType(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_INT64      *UserVarPtr)
   {
   MsysInquireFeatureExecute(SysId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_INT64);
   }
inline void MFTYPE MsysInquireFeatureSafeType(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_DOUBLE     *UserVarPtr)
   {
   MsysInquireFeatureExecute(SysId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_DOUBLE);
   }
inline void MFTYPE MsysInquireFeatureSafeType(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_INT32      *UserVarPtr)
   {
   MsysInquireFeatureExecute(SysId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_MIL_INT32);
   }
inline void MFTYPE MsysInquireFeatureSafeType(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_UINT8      *UserVarPtr)
   {
   MsysInquireFeatureExecute(SysId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_UINT8);
   }
inline void MFTYPE MsysInquireFeatureSafeType(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, bool           *UserVarPtr)
   {
   SafeTypeError(MIL_TEXT("MsysInquireFeature"));

   MsysInquireFeature(SysId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MsysInquireFeatureSafeType(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, int             UserVarPtr)
   {
   if(UserVarPtr != 0)
      SafeTypeError(MIL_TEXT("MsysInquireFeature"));

   MsysInquireFeature(SysId, InquireType, FeatureName.c_str(), UserVarType, M_NULL);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MsysInquireFeatureSafeType(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, std::nullptr_t)
   {
   MsysInquireFeature(SysId, InquireType, FeatureName.c_str(), UserVarType, M_NULL);
   }
#endif

inline void MFTYPE MsysControlFeatureSafeType(MIL_ID SysId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_STRING       &UserVarPtr)
   {
   MsysControlFeatureExecute(SysId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr.c_str(), M_TYPE_TEXT_CHAR);
   }
inline void MFTYPE MsysControlFeatureSafeType(MIL_ID SysId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_INT64        *UserVarPtr)
   {
   MsysControlFeatureExecute(SysId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_INT64);
   }
inline void MFTYPE MsysControlFeatureSafeType(MIL_ID SysId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_DOUBLE       *UserVarPtr)
   {
   MsysControlFeatureExecute(SysId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_DOUBLE);
   }
inline void MFTYPE MsysControlFeatureSafeType(MIL_ID SysId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_INT32        *UserVarPtr)
   {
   MsysControlFeatureExecute(SysId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_MIL_INT32);
   }
inline void MFTYPE MsysControlFeatureSafeType(MIL_ID SysId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_UINT8        *UserVarPtr)
   {
   MsysControlFeatureExecute(SysId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_UINT8);
   }
inline void MFTYPE MsysControlFeatureSafeType(MIL_ID SysId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const bool             *UserVarPtr)
   {
   if(UserVarPtr)
      SafeTypeError(MIL_TEXT("MsysControlFeature"));

   MsysControlFeature(SysId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MsysControlFeatureSafeType(MIL_ID SysId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, int               UserVarPtr)
   {
   if(UserVarPtr)
      SafeTypeError(MIL_TEXT("MsysControlFeature"));
   MsysControlFeatureExecute(SysId, ControlType, FeatureName.c_str(), UserVarType, M_NULL, UserVarType);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MsysControlFeatureSafeType(MIL_ID SysId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, std::nullptr_t)
   {
   MsysControlFeatureExecute(SysId, ControlType, FeatureName.c_str(), UserVarType, M_NULL, UserVarType);
   }
#endif

#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED

inline void MFTYPE MsysControlFeatureSafeType(MIL_ID SysId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_UINT64       *UserVarPtr)
   {
   MsysControlFeatureExecute(SysId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_INT64);
   }

inline void MFTYPE MsysInquireFeatureSafeType(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_UINT64     *UserVarPtr)
   {
   MsysInquireFeatureExecute(SysId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_INT64);
   }
#endif
#endif // (MIL_COMPILE_VERSION >= 1020)

inline MIL_INT MFTYPE MsysIoInquireSafeType(MIL_ID IoObjectId, MIL_INT64 InquireType, MIL_STRING&       UserVarPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InquireType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MsysIoInquire"), MIL_TEXT("Inquire type not supported with MIL_STRING."));
      }
#endif

   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MsysIoInquireSafeType(IoObjectId, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MsysIoInquireSafeTypeExecute(IoObjectId, InquireType, &UserVarPtr[0], M_TYPE_TEXT_CHAR);
      UserVarPtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }

#if (MIL_COMPILE_VERSION >= 1020)
inline MIL_INT MFTYPE MsysGetHookInfoSafeType(MIL_ID SysId, MIL_ID EventId, MIL_INT64 InquireType, MIL_STRING       &ResultPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InquireType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MsysGetHookInfo"), MIL_TEXT("Inquire type not supported with MIL_STRING."));
      }
#endif

   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MsysGetHookInfoSafeType(SysId, EventId, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ResultPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MsysGetHookInfoSafeTypeExecute(SysId, EventId, InquireType, &ResultPtr[0], M_PARAM_TYPE_MIL_TEXT);
      ResultPtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }
#endif /* (MIL_COMPILE_VERSION >= 1020) */

inline MIL_INT MFTYPE MsysInquireSafeType(MIL_ID SysId, MIL_INT64 InquireType, MIL_STRING       &ResultPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InquireType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MsysInquire"), MIL_TEXT("Inquire type not supported with MIL_STRING."));
      }
#endif

   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MsysInquireSafeType(SysId, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ResultPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MsysInquireSafeTypeExecute(SysId, InquireType, &ResultPtr[0], M_TYPE_TEXT_CHAR);
      ResultPtr.resize(MOs_UseDeprecatedStrLength(ResultPtr.c_str()));
      }

   return RetValue;
   }

inline MIL_INT MFTYPE MbufInquireSafeType(MIL_ID BufId, MIL_INT64 InquireType, MIL_STRING       &ResultPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InquireType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MbufInquire"), MIL_TEXT("Inquire type not supported with MIL_STRING."));
      }
#endif

   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MbufInquireSafeType(BufId, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ResultPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MbufInquireSafeTypeExecute(BufId, InquireType, &ResultPtr[0], M_TYPE_TEXT_CHAR);
      ResultPtr.resize(MOs_UseDeprecatedStrLength(ResultPtr.c_str()));
      }

   return RetValue;
   }
#else /* !M_MIL_USE_SAFE_TYPE*/

inline MIL_INT MFTYPE MsysIoInquire(MIL_ID IoObjectId, MIL_INT64 InquireType, MIL_STRING        UserVarPtr)
   {
   MIL_INT RetValue = 0;

   MIL_INT InternalStringSize = 0;
   MsysIoInquire(IoObjectId, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MsysIoInquire(IoObjectId, InquireType, &UserVarPtr[0]);
      UserVarPtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }

#if (MIL_COMPILE_VERSION >= 1020)
inline MIL_INT MFTYPE MsysGetHookInfo(MIL_ID SysId, MIL_ID EventId, MIL_INT64 InquireType, MIL_STRING       &ResultPtr)
   {
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MsysGetHookInfo(SysId, EventId, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ResultPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MsysGetHookInfo(SysId, EventId, InquireType, &ResultPtr[0]);
      ResultPtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }
#endif /* (MIL_COMPILE_VERSION >= 1020)*/    
inline MIL_INT MFTYPE MsysInquire(MIL_ID SysId, MIL_INT64 InquireType, MIL_STRING       &ResultPtr)
   {
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MsysInquire(SysId, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ResultPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MsysInquire(SysId, InquireType, &ResultPtr[0]);
      ResultPtr.resize(MOs_UseDeprecatedStrLength(ResultPtr.c_str()));
      }

   return RetValue;
   }

inline MIL_INT MFTYPE MbufInquire(MIL_ID SysId, MIL_INT64 InquireType, MIL_STRING       &ResultPtr)
   {
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MbufInquire(SysId, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ResultPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MbufInquire(SysId, InquireType, &ResultPtr[0]);
      ResultPtr.resize(MOs_UseDeprecatedStrLength(ResultPtr.c_str()));
      }

   return RetValue;
   }


#if M_MIL_USE_UNICODE
#if M_MIL_UNICODE_API
#if (MIL_COMPILE_VERSION >= 1020)
inline void MFTYPE MsysInquireFeatureW(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, void           *UserVarPtr)
   {
   MsysInquireFeatureW(SysId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }

inline void MFTYPE MsysControlFeatureW(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, const void *UserVarPtr)
   {
   MsysControlFeatureW(SysId, InquireType, (MIL_CONST_TEXT_PTR)FeatureName.c_str(), UserVarType, UserVarPtr);
   }


inline void MFTYPE MsysControlFeatureW(MIL_ID BufId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, const MIL_STRING &UserVarPtr)
   {
   MsysControlFeatureW(BufId, InquireType, (MIL_CONST_TEXT_PTR)FeatureName.c_str(), UserVarType, (MIL_CONST_TEXT_PTR)UserVarPtr.c_str());
   }

inline void MFTYPE MsysInquireFeatureW(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, MIL_STRING &UserVarPtr)
   {
   UNREFERENCED_PARAMETER(UserVarType);
   MIL_INT InternalStringSize = 0;
   MsysInquireFeatureW(SysId, InquireType + M_STRING_SIZE, FeatureName.c_str(), M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      MsysInquireFeatureW(SysId, InquireType, FeatureName.c_str(), M_TYPE_STRING + M_FEATURE_USER_ARRAY_SIZE(InternalStringSize), &UserVarPtr[0]);
      MIL_INT Len = MosStrlen(&UserVarPtr[0]);
      UserVarPtr.resize(Len);

      }
   }
#endif /* (MIL_COMPILE_VERSION >= 1020) */
#else
#if (MIL_COMPILE_VERSION >= 1020)
inline void MFTYPE MsysInquireFeatureA(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, void           *UserVarPtr)
   {
   MsysInquireFeatureA(SysId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }

inline void MFTYPE MsysControlFeatureA(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, const void *UserVarPtr)
   {
   MsysControlFeatureA(SysId, InquireType, (MIL_CONST_TEXT_PTR)FeatureName.c_str(), UserVarType, UserVarPtr);
   }


inline void MFTYPE MsysControlFeatureA(MIL_ID BufId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, const MIL_STRING &UserVarPtr)
   {
   MsysControlFeatureA(BufId, InquireType, (MIL_CONST_TEXT_PTR)FeatureName.c_str(), UserVarType, (MIL_CONST_TEXT_PTR)UserVarPtr.c_str());
   }

inline void MFTYPE MsysInquireFeatureA(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, MIL_STRING &UserVarPtr)
   {
   UNREFERENCED_PARAMETER(UserVarType);
   MIL_INT InternalStringSize = 0;
   MsysInquireFeatureA(SysId, InquireType + M_STRING_SIZE, FeatureName.c_str(), M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      MsysInquireFeatureA(SysId, InquireType, FeatureName.c_str(), M_TYPE_STRING + M_FEATURE_USER_ARRAY_SIZE(InternalStringSize), &UserVarPtr[0]);
      MIL_INT Len = MosStrlen(&UserVarPtr[0]);
      UserVarPtr.resize(Len);

      }
   }
#endif /* (MIL_COMPILE_VERSION >= 1020) */
#endif /* M_MIL_UNICODE_API */
#else
inline void MFTYPE MsysInquireFeature(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, void           *UserVarPtr)
   {
   MsysInquireFeature(SysId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }

inline void MFTYPE MsysControlFeature(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, const void *UserVarPtr)
   {
   MsysControlFeature(SysId, InquireType, (MIL_CONST_TEXT_PTR)FeatureName.c_str(), UserVarType, UserVarPtr);
   }


inline void MFTYPE MsysControlFeature(MIL_ID BufId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, const MIL_STRING &UserVarPtr)
   {
   MsysControlFeature(BufId, InquireType, (MIL_CONST_TEXT_PTR)FeatureName.c_str(), UserVarType, (MIL_CONST_TEXT_PTR)UserVarPtr.c_str());
   }

inline void MFTYPE MsysInquireFeature(MIL_ID SysId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, MIL_STRING &UserVarPtr)
   {
   UNREFERENCED_PARAMETER(UserVarType);
   MIL_INT InternalStringSize = 0;
   MsysInquireFeature(SysId, InquireType + M_STRING_SIZE, FeatureName.c_str(), M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      MsysInquireFeature(SysId, InquireType, FeatureName.c_str(), M_TYPE_STRING + M_FEATURE_USER_ARRAY_SIZE(InternalStringSize), &UserVarPtr[0]);
      MIL_INT Len = MosStrlen(&UserVarPtr[0]);
      UserVarPtr.resize(Len);

      }
   }
#endif /* M_MIL_USE_UNICODE*/

#endif
/***************************************************************************/
/* OBJ MODULE                                                              */
/***************************************************************************/
inline MIL_INT MFTYPE MobjInquire(MIL_ID ObjectId, MIL_INT64 InquireType, MIL_STRING  &UserVarPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InquireType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MobjInquire"), MIL_TEXT("Inquire type not supported with MIL_STRING."));
      }
#endif
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MobjInquire(ObjectId, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MobjInquire(ObjectId, InquireType, &UserVarPtr[0]);
      UserVarPtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }

inline void MobjControl(MIL_ID ObjectId, MIL_INT64 ControlType, const MIL_STRING& ControlValue)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((ControlType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MobjControl"), MIL_TEXT("Control type not supported with MIL_STRING."));
      }
#endif

   MobjControl(ObjectId, ControlType, ControlValue.c_str());
   }

/***************************************************************************/
/* DIG MODULE                                                              */
/***************************************************************************/
inline void MdigControl(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& ControlValue)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((ControlType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MdigControl"), MIL_TEXT("Control type not supported with MIL_STRING."));
      }
#endif

   MdigControl(DigId, ControlType, ControlValue.c_str());
   }

/***************************************************************************/
/* BUF MODULE                                                              */
/***************************************************************************/
inline void MFTYPE MbufInquireContainer(MIL_ID ContainerId, MIL_INT64 TargetObject, MIL_INT64 InquireType, MIL_STRING    &UserVarPtr)
   {
   if(M_IN_BUF_INQUIRE_STRING_RANGE(InquireType))
      {
      MIL_INT InternalStringSize = 0;
      MbufInquireContainer(ContainerId, TargetObject, InquireType + M_STRING_SIZE, &InternalStringSize);

      if(InternalStringSize > 0)
         {
         UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
         MbufInquireContainer(ContainerId, TargetObject, InquireType, &UserVarPtr[0]);
         UserVarPtr.resize(MOs_UseDeprecatedStrLength(UserVarPtr.c_str()));
         }
      }
#if M_MIL_USE_SAFE_TYPE	  
   else
      {
      SafeTypeError(MIL_TEXT("MbufInquireContainer: Inquire type not in string range"));
      }
#endif	  
   }

inline void MbufControl(MIL_ID BufId, MIL_INT64 ControlType, const MIL_STRING& ControlValue)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if ((ControlType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MbufControl"), MIL_TEXT("Control type not supported with MIL_STRING."));
      }
#endif

   MbufControl(BufId, ControlType, ControlValue.c_str());
   }

inline void MbufControlContainer(MIL_ID ContainerId, MIL_INT64 TargetObject, MIL_INT64 CtrlType, const MIL_STRING& ControlValue)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((CtrlType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MbufControlContainer"), MIL_TEXT("Control type not supported with MIL_STRING."));
      }
#endif

   MbufControlContainer(ContainerId, TargetObject, CtrlType, ControlValue.c_str());
   }
#if M_MIL_USE_UNICODE
#if M_MIL_UNICODE_API
inline MIL_ID MFTYPE MdigAllocW(MIL_ID SystemId, MIL_INT DigNum, const MIL_STRING& DataFormat, MIL_INT64 InitFlag, MIL_ID* DigIdPtr)
   {
   return MdigAllocW(SystemId, DigNum, DataFormat.c_str(), InitFlag, DigIdPtr);
   }
inline MIL_ID MFTYPE MdigAllocW(MIL_ID SystemId, const MIL_STRING& DigNum, const MIL_STRING& DataFormat, MIL_INT64 InitFlag, MIL_ID* DigIdPtr)
   {
   return MdigAllocW(SystemId, DigNum.c_str(), DataFormat.c_str(), InitFlag, DigIdPtr);
   }
#else
inline MIL_ID MFTYPE MdigAllocA(MIL_ID SystemId, MIL_INT DigNum, const MIL_STRING& DataFormat, MIL_INT64 InitFlag, MIL_ID* DigIdPtr)
   {
   return MdigAllocA(SystemId, DigNum, DataFormat.c_str(), InitFlag, DigIdPtr);
   }
inline MIL_ID MFTYPE MdigAllocA(MIL_ID SystemId, const MIL_STRING& DigNum, const MIL_STRING& DataFormat, MIL_INT64 InitFlag, MIL_ID* DigIdPtr)
   {
   return MdigAllocA(SystemId, DigNum.c_str(), DataFormat.c_str(), InitFlag, DigIdPtr);
   }
#endif /* M_MIL_UNICODE_API */
#else
inline MIL_ID MFTYPE MdigAlloc(MIL_ID SystemId, MIL_INT DigNum, const MIL_STRING& DataFormat, MIL_INT64 InitFlag, MIL_ID* DigIdPtr)
   {
   return MdigAlloc(SystemId, DigNum, DataFormat.c_str(), InitFlag, DigIdPtr);
   }
inline MIL_ID MFTYPE MdigAlloc(MIL_ID SystemId, const MIL_STRING&  DigNum, const MIL_STRING& DataFormat, MIL_INT64 InitFlag, MIL_ID* DigIdPtr)
   {
   return MdigAlloc(SystemId, DigNum.c_str(), DataFormat.c_str(), InitFlag, DigIdPtr);
   }
#endif /* M_MIL_USE_UNICODE */

#if M_MIL_USE_SAFE_TYPE
#if (MIL_COMPILE_VERSION >= 1020)
inline MIL_INT MFTYPE MdigGetHookInfoSafeType(MIL_ID EventId, MIL_INT64 InfoType, MIL_STRING&     ResultPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InfoType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MdigGetHookInfo"), MIL_TEXT("Info type not supported with MIL_STRING."));
      }
#endif
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MdigGetHookInfoSafeType(EventId, InfoType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ResultPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MdigGetHookInfoSafeTypeExecute(EventId, InfoType, &ResultPtr[0], M_TYPE_STRING_PTR);
      ResultPtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }
#endif
#if M_MIL_USE_UNICODE
#if M_MIL_UNICODE_API
#if (MIL_COMPILE_VERSION >= 1020)
inline void MFTYPE MdigInquireFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_STRING&     UserVarPtr)
   {
   UNREFERENCED_PARAMETER(UserVarType);
   MIL_INT InternalStringSize = 0;
   MdigInquireFeatureSafeTypeW(DigId, InquireType + M_STRING_SIZE, FeatureName.c_str(), M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      MdigInquireFeatureExecuteW(DigId, InquireType, FeatureName.c_str(), M_TYPE_STRING + M_FEATURE_USER_ARRAY_SIZE(InternalStringSize), &UserVarPtr[0], M_TYPE_TEXT_CHAR);
      MIL_INT Len = MosStrlen(&UserVarPtr[0]);
      UserVarPtr.resize(Len);

      }

   }
inline void MFTYPE MdigInquireFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_INT64      *UserVarPtr)
   {
   MdigInquireFeatureSafeTypeW(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigInquireFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_DOUBLE     *UserVarPtr)
   {
   MdigInquireFeatureSafeTypeW(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigInquireFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_INT32      *UserVarPtr)
   {
   MdigInquireFeatureSafeTypeW(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigInquireFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_UINT8      *UserVarPtr)
   {
   MdigInquireFeatureSafeTypeW(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigInquireFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, bool           *UserVarPtr)
   {
   MdigInquireFeatureSafeTypeW(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigInquireFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, int             UserVarPtr)
   {
   MdigInquireFeatureSafeTypeW(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MdigInquireFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, std::nullptr_t)
   {
   MdigInquireFeatureSafeTypeW(DigId, InquireType, FeatureName.c_str(), UserVarType, M_NULL);
   }
#endif
inline void MFTYPE MdigControlFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_STRING      &UserVarPtr)
   {
   MdigControlFeatureExecuteW(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr.c_str(), M_TYPE_TEXT_CHAR);
   }
inline void MFTYPE MdigControlFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_INT64       *UserVarPtr)
   {
   MdigControlFeatureExecuteW(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_INT64);
   }
inline void MFTYPE MdigControlFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_DOUBLE      *UserVarPtr)
   {
   MdigControlFeatureExecuteW(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_DOUBLE);
   }
inline void MFTYPE MdigControlFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_INT32       *UserVarPtr)
   {
   MdigControlFeatureExecuteW(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_MIL_INT32);
   }
inline void MFTYPE MdigControlFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_UINT8       *UserVarPtr)
   {
   MdigControlFeatureExecuteW(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_UINT8);
   }
inline void MFTYPE MdigControlFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const bool            *UserVarPtr)
   {
   SafeTypeError(MIL_TEXT("MdigControlFeature"));

   MdigControlFeatureW(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigControlFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, int              UserVarPtr)
   {
   MdigControlFeatureExecuteW(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, UserVarType);
   }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MdigControlFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, std::nullptr_t)
   {
   MdigControlFeatureExecuteW(DigId, ControlType, FeatureName.c_str(), UserVarType, M_NULL, UserVarType);
   }
#endif

#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline void MFTYPE MdigControlFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_UINT64      *UserVarPtr)
   {
   MdigControlFeatureExecuteW(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_INT64);
   }

inline void MFTYPE MdigInquireFeatureSafeTypeW(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_UINT64     *UserVarPtr)
   {
   MdigInquireFeatureSafeTypeW(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
#endif
#endif /* (MIL_COMPILE_VERSION >= 1020) */
#else
#if (MIL_COMPILE_VERSION >= 1020)
inline void MFTYPE MdigInquireFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_STRING&      UserVarPtr)
   {
   UNREFERENCED_PARAMETER(UserVarType);
   MIL_INT InternalStringSize = 0;
   MdigInquireFeatureSafeTypeA(DigId, InquireType + M_STRING_SIZE, FeatureName.c_str(), M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      MdigInquireFeatureExecuteA(DigId, InquireType, FeatureName.c_str(), M_TYPE_STRING + M_FEATURE_USER_ARRAY_SIZE(InternalStringSize), &UserVarPtr[0], M_TYPE_TEXT_CHAR);
      MIL_INT Len = MosStrlen(&UserVarPtr[0]);
      UserVarPtr.resize(Len);

      }
   }

inline void MFTYPE MdigInquireFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_INT64      *UserVarPtr)
   {
   MdigInquireFeatureSafeTypeA(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigInquireFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_DOUBLE     *UserVarPtr)
   {
   MdigInquireFeatureSafeTypeA(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigInquireFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_INT32      *UserVarPtr)
   {
   MdigInquireFeatureSafeTypeA(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigInquireFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_UINT8      *UserVarPtr)
   {
   MdigInquireFeatureSafeTypeA(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigInquireFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, bool           *UserVarPtr)
   {
   MdigInquireFeatureSafeTypeA(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigInquireFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, int             UserVarPtr)
   {
   MdigInquireFeatureSafeTypeA(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MdigInquireFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, std::nullptr_t)
   {
   MdigInquireFeatureSafeTypeA(DigId, InquireType, FeatureName.c_str(), UserVarType, M_NULL);
   }
#endif
inline void MFTYPE MdigControlFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_STRING&               UserVarPtr)
   {
   MdigControlFeatureSafeTypeA(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr.c_str());
   }
inline void MFTYPE MdigControlFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_INT64              *UserVarPtr)
   {
   MdigControlFeatureSafeTypeA(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigControlFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_DOUBLE             *UserVarPtr)
   {
   MdigControlFeatureSafeTypeA(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigControlFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_INT32              *UserVarPtr)
   {
   MdigControlFeatureSafeTypeA(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigControlFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_UINT8              *UserVarPtr)
   {
   MdigControlFeatureSafeTypeA(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigControlFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const bool                   *UserVarPtr)
   {
   MdigControlFeatureSafeTypeA(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigControlFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, int                     UserVarPtr)
   {
   MdigControlFeatureSafeTypeA(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MdigControlFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, std::nullptr_t)
   {
   MdigControlFeatureSafeTypeA(DigId, ControlType, FeatureName.c_str(), UserVarType, M_NULL);
   }
#endif

#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED

inline void MFTYPE MdigControlFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_UINT64             *UserVarPtr)
   {
   MdigControlFeatureSafeTypeA(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }

inline void MFTYPE MdigInquireFeatureSafeTypeA(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_UINT64     *UserVarPtr)
   {
   MdigInquireFeatureSafeTypeA(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
#endif
#endif /* (MIL_COMPILE_VERSION >= 1020) */
#endif /* M_MIL_UNICODE_API */
#else

inline void MFTYPE MdigInquireFeatureSafeType(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_STRING&      UserVarPtr)
   {
   UNREFERENCED_PARAMETER(UserVarType);
   MIL_INT InternalStringSize = 0;
   MdigInquireFeatureSafeType(DigId, InquireType + M_STRING_SIZE, FeatureName.c_str(), M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      MdigInquireFeatureExecute(DigId, InquireType, FeatureName.c_str(), M_TYPE_STRING + M_FEATURE_USER_ARRAY_SIZE(InternalStringSize), &UserVarPtr[0], M_TYPE_TEXT_CHAR);
      MIL_INT Len = MosStrlen(&UserVarPtr[0]);
      UserVarPtr.resize(Len);

      }
   }
inline void MFTYPE MdigInquireFeatureSafeType(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_INT64      *UserVarPtr)
   {
   MdigInquireFeatureExecute(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_INT64);
   }
inline void MFTYPE MdigInquireFeatureSafeType(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_DOUBLE     *UserVarPtr)
   {
   MdigInquireFeatureExecute(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_DOUBLE);
   }
inline void MFTYPE MdigInquireFeatureSafeType(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_INT32      *UserVarPtr)
   {
   MdigInquireFeatureExecute(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_MIL_INT32);
   }
inline void MFTYPE MdigInquireFeatureSafeType(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_UINT8      *UserVarPtr)
   {
   MdigInquireFeatureExecute(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_UINT8);
   }
inline void MFTYPE MdigInquireFeatureSafeType(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, bool           *UserVarPtr)
   {
   SafeTypeError(MIL_TEXT("MdigInquireFeature"));

   MdigInquireFeature(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigInquireFeatureSafeType(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, int             UserVarPtr)
   {
   if(UserVarPtr != 0)
      SafeTypeError(MIL_TEXT("MdigInquireFeature"));

   MdigInquireFeatureSafeType(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MdigInquireFeatureSafeType(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, std::nullptr_t)
   {
   MdigInquireFeatureSafeType(DigId, InquireType, FeatureName.c_str(), UserVarType, M_NULL);
   }
#endif
inline void MFTYPE MdigControlFeatureSafeType(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_STRING&       UserVarPtr)
   {
   MdigControlFeatureExecute(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr.c_str(), M_TYPE_TEXT_CHAR);
   }
inline void MFTYPE MdigControlFeatureSafeType(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_INT64        *UserVarPtr)
   {
   MdigControlFeatureExecute(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_INT64);
   }
inline void MFTYPE MdigControlFeatureSafeType(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_DOUBLE       *UserVarPtr)
   {
   MdigControlFeatureExecute(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_DOUBLE);
   }
inline void MFTYPE MdigControlFeatureSafeType(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_INT32        *UserVarPtr)
   {
   MdigControlFeatureExecute(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_MIL_INT32);
   }
inline void MFTYPE MdigControlFeatureSafeType(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_UINT8        *UserVarPtr)
   {
   MdigControlFeatureExecute(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_UINT8);
   }
inline void MFTYPE MdigControlFeatureSafeType(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const bool             *UserVarPtr)
   {
   SafeTypeError(MIL_TEXT("MdigControlFeature"));

   MdigControlFeature(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }
inline void MFTYPE MdigControlFeatureSafeType(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, int               UserVarPtr)
   {
   MdigControlFeatureExecute(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, UserVarType);
   }
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline void MFTYPE MdigControlFeatureSafeType(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, std::nullptr_t)
   {
   MdigControlFeatureExecute(DigId, ControlType, FeatureName.c_str(), UserVarType, M_NULL, UserVarType);
   }
#endif

#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED

inline void MFTYPE MdigControlFeatureSafeType(MIL_ID DigId, MIL_INT64 ControlType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, const MIL_UINT64       *UserVarPtr)
   {
   MdigControlFeatureExecute(DigId, ControlType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_INT64);
   }

inline void MFTYPE MdigInquireFeatureSafeType(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING& FeatureName, MIL_INT64 UserVarType, MIL_UINT64     *UserVarPtr)
   {
   MdigInquireFeatureExecute(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr, M_TYPE_INT64);
   }
#endif
#endif   /* M_MIL_USE_UNICODE */

inline MIL_INT MFTYPE MdigInquireSafeType(MIL_ID DigId, MIL_INT64 InquireType, MIL_STRING      &UserVarPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InquireType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MdigInquire"), MIL_TEXT("Inquire type not supported with MIL_STRING."));
      }
#endif

   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MdigInquireSafeType(DigId, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MdigInquireExecute(DigId, InquireType, &UserVarPtr[0], M_TYPE_TEXT_CHAR);
      UserVarPtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }

#else
inline MIL_INT MFTYPE MdigInquire(MIL_ID DigId, MIL_INT64 InquireType, MIL_STRING      &UserVarPtr)
   {
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MdigInquire(DigId, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MdigInquire(DigId, InquireType, &UserVarPtr[0]);
      UserVarPtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }

inline void MFTYPE MdigInquireFeature(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, void           *UserVarPtr)
   {
   MdigInquireFeature(DigId, InquireType, FeatureName.c_str(), UserVarType, UserVarPtr);
   }

inline void MFTYPE MdigInquireFeature(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, MIL_STRING &UserVarPtr)
   {
   UNREFERENCED_PARAMETER(UserVarType);
   MIL_INT InternalStringSize = 0;
   MdigInquireFeature(DigId, InquireType + M_STRING_SIZE, FeatureName.c_str(), M_TYPE_MIL_INT, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      MdigInquireFeature(DigId, InquireType, FeatureName.c_str(), M_TYPE_STRING + M_FEATURE_USER_ARRAY_SIZE(InternalStringSize), &UserVarPtr[0]);
      MIL_INT Len = MosStrlen(&UserVarPtr[0]);
      UserVarPtr.resize(Len);

      }
   }

inline void MFTYPE MdigControlFeature(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, const void *UserVarPtr)
   {
   MdigControlFeature(DigId, InquireType, (MIL_CONST_TEXT_PTR)FeatureName.c_str(), UserVarType, UserVarPtr);
   }

inline void MFTYPE MdigControlFeature(MIL_ID DigId, MIL_INT64 InquireType, const MIL_STRING &FeatureName, MIL_INT64 UserVarType, const MIL_STRING &UserVarPtr)
   {
   MdigControlFeature(DigId, InquireType, (MIL_CONST_TEXT_PTR)FeatureName.c_str(), UserVarType, (MIL_CONST_TEXT_PTR)UserVarPtr.c_str());
   }

#if (MIL_COMPILE_VERSION >= 1020)
inline MIL_INT MFTYPE MdigGetHookInfo(MIL_ID EventId, MIL_INT64 InfoType, MIL_STRING&    ResultPtr)
   {
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;
   MdigGetHookInfo(EventId, InfoType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ResultPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MdigGetHookInfo(EventId, InfoType, &ResultPtr[0]);
      ResultPtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }
#endif /* (MIL_COMPILE_VERSION >= 1020) */
#endif /* M_MIL_USE_SAFE_TYPE */

/***************************************************************************/
/* COM MODULE                                                              */
/***************************************************************************/
#ifdef  __MILCOM_H__
inline MIL_INT MFTYPE McomInquire(MIL_ID ComId, MIL_INT64  InquireType, MIL_STRING &UserVarPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InquireType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("McomInquire"), MIL_TEXT("Inquire type not supported with MIL_STRING."));
      }
#endif
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   McomInquire(ComId, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      ResultPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = McomInquire(ComId, InquireType, &ResultPtr[0]);
      ResultPtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }
#endif

/***************************************************************************/
/* SEQ MODULE                                                              */
/***************************************************************************/

#if  !M_MIL_USE_LINUX || M_MIL_USE_64BIT
inline void MFTYPE MseqDefine(MIL_ID ContextSeqId, MIL_INT SequenceIndex, MIL_INT64 SequenceType, const MIL_STRING& Param1Ptr, MIL_DOUBLE Param2)
   {
   MseqDefine(ContextSeqId, SequenceIndex, SequenceType, Param1Ptr.c_str(), Param2);
   }

#if M_MIL_USE_SAFE_TYPE
inline MIL_INT MFTYPE MseqInquireSafeType(MIL_ID ContextSeqId, MIL_INT SequenceIndex, MIL_INT64 InquireType, MIL_STRING       &UserVarPtr)
   {
#if MIL_COMPILE_VERSION >= MIL_COMPILE_TRUNK_VERSION && M_MIL_USE_SAFE_TYPE
   if((InquireType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("MseqInquire"), MIL_TEXT("Inquire type not supported with MIL_STRING."));
      }
#endif
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MseqInquireSafeType(ContextSeqId, SequenceIndex, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MseqInquireSafeTypeExecute(ContextSeqId, SequenceIndex, InquireType, &UserVarPtr[0], M_TYPE_TEXT_CHAR);
      UserVarPtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }

#else
inline MIL_INT MFTYPE MseqInquire(MIL_ID ContextSeqId, MIL_INT SequenceIndex, MIL_INT64 InquireType, MIL_STRING       &UserVarPtr)
   {
   MIL_INT RetValue = 0;
   MIL_INT InternalStringSize = 0;

   MseqInquire(ContextSeqId, SequenceIndex, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = MseqInquire(ContextSeqId, SequenceIndex, InquireType, &UserVarPtr[0]);
      UserVarPtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }

#endif

//Undefined MOs_UseDeprecatedStrLength
#ifdef  MOs_UseDeprecatedStrLength
#undef  MOs_UseDeprecatedStrLength
#endif


#endif //#!M_MIL_USE_LINUX
#endif /* M_MIL_USE_STRING */
#endif /* __MILSTRING_H__ */	
#endif /* __MILPROTO_H */
