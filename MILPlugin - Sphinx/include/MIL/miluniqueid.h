/************************************************************************/
/*
*
* Filename     :  miluniqueid.h
* Revision     :  10.40.0881
* Content      :  MIL_UNIQUE_ID C++ RAII class for a MIL_ID
*
* Copyright © Matrox Electronic Systems Ltd., 1992-2021.
* All Rights Reserved
*************************************************************************/
#ifndef __UNIQUE_MIL_ID_H
#define __UNIQUE_MIL_ID_H

#ifndef M_MIL_USE_MIL_UNIQUE_ID
   #if defined(__cplusplus) && (!defined(M_COMPILING_MILDLL) || !M_COMPILING_MILDLL) && (!defined(M_LINUX_KERNEL) || !M_LINUX_KERNEL) && (!defined(M_WINDOWS_NT_KERNEL_MODE) || !M_WINDOWS_NT_KERNEL_MODE)
      #define M_MIL_USE_MIL_UNIQUE_ID 1
   #else
      #define M_MIL_USE_MIL_UNIQUE_ID 0
   #endif
#endif

#if M_MIL_USE_MIL_UNIQUE_ID

typedef void (MFTYPE MilFreeFuncType)(MIL_ID Id);

#if M_MIL_USE_SAFE_TYPE

template <MilFreeFuncType FreeFunc>
inline bool MilIsCorrectObjectType(MIL_INT64 ObjectType);

// Functions used in debug to report an error if a MIL object ends up in the wrong
// MIL_UNIQUE_ID type.

template <> inline bool MilIsCorrectObjectType<&MappFree>(MIL_INT64 ObjectType)
   {
   return ObjectType == M_APPLICATION;
   }

template <> inline bool MilIsCorrectObjectType<&MappCloseConnection>(MIL_INT64 ObjectType)
   {
   return ObjectType == M_APPLICATION;
   }

template <> inline bool MilIsCorrectObjectType<&MbufFree>(MIL_INT64 ObjectType)
   {
   return M_IS_BUFFER_TYPE(ObjectType) || ObjectType == M_CONTAINER;
   }

template <> inline bool MilIsCorrectObjectType<&MdigFree>(MIL_INT64 ObjectType)
   {
   return M_IS_DIGITIZER_TYPE(ObjectType);
   }

template <> inline bool MilIsCorrectObjectType<&MgraFree>(MIL_INT64 ObjectType)
   {
   return ObjectType == M_GRAPHIC_CONTEXT || ObjectType == M_GRAPHIC_LIST;
   }

template <> inline bool MilIsCorrectObjectType<&MobjFree>(MIL_INT64 ObjectType)
   {
   return (ObjectType == M_MESSAGE_MAILBOX) ||
          (ObjectType == M_HOOK_CONTEXT) ||
          (ObjectType == M_OPAQUE_HOOK_CONTEXT) ||
          (ObjectType == M_HTTP_SERVER);
   }

#if !M_MIL_USE_LINUX || M_MIL_USE_64BIT
template <> inline bool MilIsCorrectObjectType<&MseqFree>(MIL_INT64 ObjectType)
   {
   return ObjectType == M_SEQUENCE_CONTEXT;
   }
#endif
template <> inline bool MilIsCorrectObjectType<&MsysFree>(MIL_INT64 ObjectType)
   {
   return ObjectType == M_SYSTEM;
   }

template <> inline bool MilIsCorrectObjectType<&MsysIoFree>(MIL_INT64 ObjectType)
   {
   return ObjectType == M_SYS_IO_CONTEXT;
   }

template <> inline bool MilIsCorrectObjectType<&MthrFree>(MIL_INT64 ObjectType)
   {
   return ObjectType == M_EVENT || ObjectType == M_SYSTEM_THREAD || ObjectType == M_MUTEX;
   }

template <MilFreeFuncType FreeFunc>
inline void MilCheckObjectType(MIL_ID Id)
   {
   if (!M_ID_IS_VIRTUAL_OR_NULL(Id))
      {
      MIL_INT64 ObjectType;
      MobjInquire(Id, M_OBJECT_TYPE, &ObjectType);
      if (!MilIsCorrectObjectType<FreeFunc>(ObjectType))
         SafeTypeError(MIL_TEXT("allocation function"), MIL_TEXT("Mismatch between object type and MIL_UNIQUE_ID type."));
      }
   }

#define MIL_CHECK_OBJECT_TYPE(Id, FreeFunc) MilCheckObjectType<FreeFunc>(Id)

#else

// In release, there is no check at ID acquisition. When the free function is called,
// a MIL error is reported if the object type is incorrect.
#define MIL_CHECK_OBJECT_TYPE(Id, FreeFunc)

#endif

// MIL_ID wrapper that manages its lifetime by calling the corresponding free function
// in the destructor. Interface similar to std::unique_ptr.
template <MilFreeFuncType FreeFunc>
class MIL_UNIQUE_ID
   {
   public:
      explicit MIL_UNIQUE_ID(MIL_ID Id = M_NULL) MIL_NOEXCEPT
         : m_Id(Id)
         {
         MIL_CHECK_OBJECT_TYPE(m_Id, FreeFunc);
         }

      ~MIL_UNIQUE_ID() MIL_NOEXCEPT
         {
         free_id();
         }

#if M_MIL_USE_MOVE_SEMANTICS
      MIL_UNIQUE_ID(MIL_UNIQUE_ID&& Other) MIL_NOEXCEPT
         : m_Id(Other.m_Id)
         {
         Other.m_Id = M_NULL;
         }

      MIL_UNIQUE_ID& operator=(MIL_UNIQUE_ID&& Other) MIL_NOEXCEPT
         {
         if (&Other != this)
            {
            free_id();
            m_Id = Other.m_Id;
            Other.m_Id = M_NULL;
            }
         return *this;
         }

      // Forbid construction from MIL_UNIQUE_ID of a different type.
      // (Could happen because of implicit conversion to MIL_ID)
      template <MilFreeFuncType FreeFunc2>
      MIL_UNIQUE_ID(const MIL_UNIQUE_ID<FreeFunc2>&) = delete;
#endif

#if M_MIL_USE_NULLPTR
      MIL_UNIQUE_ID& operator=(std::nullptr_t) MIL_NOEXCEPT
         {
         reset();
         return *this;
         }
#endif

      MIL_ID release() MIL_NOEXCEPT
         {
         MIL_ID Id = m_Id;
         m_Id = M_NULL;
         return Id;
         }

      void reset(MIL_ID NewId = M_NULL) MIL_NOEXCEPT
         {
         if (NewId != m_Id)
            {
            free_id();
            m_Id = NewId;
            }
         MIL_CHECK_OBJECT_TYPE(m_Id, FreeFunc);
         }

      MIL_ID get() const MIL_NOEXCEPT
         {
         return m_Id;
         }

#if M_MIL_USE_REF_QUALIFIERS
      // Allow implicit conversion to MIL_ID only on non-temporary MIL_UNIQUE_IDs.
      operator MIL_ID() const & MIL_NOEXCEPT
         {
         return m_Id;
         }
      operator MIL_ID() && = delete;
#else
      operator MIL_ID() const MIL_NOEXCEPT
         {
         return m_Id;
         }
#endif

      friend void swap(MIL_UNIQUE_ID& lhs, MIL_UNIQUE_ID& rhs) MIL_NOEXCEPT
         {
         MIL_ID lhsId = lhs.m_Id;
         lhs.m_Id = rhs.m_Id;
         rhs.m_Id = lhsId;
         }

   private:
#ifndef M_MIL_USE_MOVE_SEMANTICS
      // Copy is forbidden
      MIL_UNIQUE_ID(const MIL_UNIQUE_ID&);
      MIL_UNIQUE_ID& operator=(const MIL_UNIQUE_ID&);
#endif

      void free_id() MIL_NOEXCEPT
         {
         if (!M_ID_IS_VIRTUAL_OR_NULL(m_Id))
            FreeFunc(m_Id);
         }

      MIL_ID m_Id;
   };

// Specific MIL_UNIQUE_ID instantiations for each free function.
typedef MIL_UNIQUE_ID<&MappFree  > MIL_UNIQUE_APP_ID;
typedef MIL_UNIQUE_ID<&MappCloseConnection> MIL_UNIQUE_CONNECTION_ID;
typedef MIL_UNIQUE_ID<&MbufFree  > MIL_UNIQUE_BUF_ID;
typedef MIL_UNIQUE_ID<&MdigFree  > MIL_UNIQUE_DIG_ID;
typedef MIL_UNIQUE_ID<&MgraFree  > MIL_UNIQUE_GRA_ID;
typedef MIL_UNIQUE_ID<&MobjFree  > MIL_UNIQUE_OBJ_ID;
typedef MIL_UNIQUE_ID<&MsysFree  > MIL_UNIQUE_SYS_ID;
typedef MIL_UNIQUE_ID<&MsysIoFree> MIL_UNIQUE_SYSIO_ID;
typedef MIL_UNIQUE_ID<&MthrFree  > MIL_UNIQUE_THR_ID;
#if !M_MIL_USE_LINUX || M_MIL_USE_64BIT
typedef MIL_UNIQUE_ID<&MseqFree  > MIL_UNIQUE_SEQ_ID;
#endif

// Factory functions that wrap all MIL allocation functions to return a MIL_UNIQUE_ID
// instead of a MIL_ID. To use the factory function, simply replace the last
// MIL_ID* parameter with M_UNIQUE_ID.

#if M_MIL_USE_MOVE_SEMANTICS

// Structure used for tag dispatching in the C++ overloads below.
struct MIL_UNIQUE_ID_TAG {};
#define M_UNIQUE_ID  MIL_UNIQUE_ID_TAG()

// Structure used to accept an array of either MIL_UNIQUE_IDs or MIL_IDs.
struct MilConstArrayIdParam
   {
   const MIL_ID* m_IdArrayPtr;

   inline MilConstArrayIdParam(const MIL_ID* p) : m_IdArrayPtr(p) {}

   template <MilFreeFuncType FreeFunc>
   inline MilConstArrayIdParam(const MIL_UNIQUE_ID<FreeFunc>* p)
      : m_IdArrayPtr(reinterpret_cast<const MIL_ID*>(p))
      {
      static_assert(sizeof(MIL_UNIQUE_ID<FreeFunc>[2]) == sizeof(MIL_ID[2]),
                    "cannot cast const MIL_UNIQUE_ID<FreeFunc>* to const MIL_ID*");
      }
   };

// Generic implementation of MxxxStream C++ overloads for MIL_UNIQUE_IDs.
template <MilFreeFuncType FreeFunc>
inline void MxxxStreamForMilUniqueId(MilStreamParam         MemPtrOrFileName,
                                     MIL_ID                 SysId           ,
                                     MIL_INT64              Operation       ,
                                     MIL_INT64              StreamType      ,
                                     MIL_DOUBLE             Version         ,
                                     MIL_INT64              ControlFlag     ,
                                     MIL_UNIQUE_ID<FreeFunc>* UniqueIdPtr     ,
                                     MIL_INT*               SizeByteVarPtr  ,
                                     M_XXX_STREAM_FUNCTION  MxxxStream      )
   {
   MIL_ID TempId = UniqueIdPtr->get();
   (*MxxxStream)(MemPtrOrFileName, SysId, Operation, StreamType, Version, ControlFlag, &TempId, SizeByteVarPtr);
   if (Operation & M_RESTORE)
      UniqueIdPtr->reset(TempId);
   }


// APP
inline MIL_UNIQUE_APP_ID MappAlloc(MIL_CONST_TEXT_PTR ServerDescription, MIL_INT64 InitFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_APP_ID(MappAlloc(ServerDescription, InitFlag, M_NULL));
   }
inline MIL_UNIQUE_CONNECTION_ID MappOpenConnection(MIL_CONST_TEXT_PTR ConnectionDescriptor, MIL_INT64 InitFlag, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   MIL_ID RemoteContextAppId = M_NULL;
   MappOpenConnection(ConnectionDescriptor, InitFlag, ControlFlag, &RemoteContextAppId);
   return MIL_UNIQUE_CONNECTION_ID(RemoteContextAppId);
   }
#if M_MIL_USE_STRING
inline MIL_UNIQUE_APP_ID MappAlloc(const MIL_STRING& ServerDescription, MIL_INT64 InitFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_APP_ID(MappAlloc(ServerDescription, InitFlag, M_NULL));
   }
inline MIL_UNIQUE_CONNECTION_ID MappOpenConnection(const MIL_STRING& ConnectionDescriptor, MIL_INT64 InitFlag, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   MIL_ID RemoteContextAppId = M_NULL;
   MappOpenConnection(ConnectionDescriptor, InitFlag, ControlFlag, &RemoteContextAppId);
   return MIL_UNIQUE_CONNECTION_ID(RemoteContextAppId);
   }
#endif
template <MilFreeFuncType FreeFunc> inline void MappFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;
template <MilFreeFuncType FreeFunc> inline void MappCloseConnection(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

// BUF
inline MIL_UNIQUE_BUF_ID MbufAlloc1d(MIL_ID SystemId, MIL_INT SizeX, MIL_INT Type, MIL_INT64 Attribute, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_BUF_ID(MbufAlloc1d(SystemId, SizeX, Type, Attribute, M_NULL));
   }
inline MIL_UNIQUE_BUF_ID MbufAlloc2d(MIL_ID SystemId, MIL_INT SizeX, MIL_INT SizeY, MIL_INT Type, MIL_INT64 Attribute, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_BUF_ID(MbufAlloc2d(SystemId, SizeX, SizeY, Type, Attribute, M_NULL));
   }
inline MIL_UNIQUE_BUF_ID MbufAllocColor(MIL_ID SystemId, MIL_INT SizeBand, MIL_INT SizeX, MIL_INT SizeY, MIL_INT Type, MIL_INT64 Attribute, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_BUF_ID(MbufAllocColor(SystemId, SizeBand, SizeX, SizeY, Type, Attribute, M_NULL));
   }
inline MIL_UNIQUE_BUF_ID MbufAllocDefault(MIL_ID SysId, MIL_ID RefMilObjectId, MIL_INT64 Attribute, MIL_INT64 ControlFlag, MIL_INT64 ControlValue, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_BUF_ID(MbufAllocDefault(SysId, RefMilObjectId, Attribute, ControlFlag, ControlValue, M_NULL));
   }
inline MIL_UNIQUE_BUF_ID MbufAllocContainer(MIL_ID SysId, MIL_INT64 Attribute, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_BUF_ID(MbufAllocContainer(SysId, Attribute, ControlFlag, M_NULL));
   }
inline MIL_UNIQUE_BUF_ID MbufChild1d(MIL_ID ParentBufId, MIL_INT OffX, MIL_INT SizeX, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_BUF_ID(MbufChild1d(ParentBufId, OffX, SizeX, M_NULL));
   }
inline MIL_UNIQUE_BUF_ID MbufChild2d(MIL_ID ParentBufId, MIL_INT OffX, MIL_INT OffY, MIL_INT SizeX, MIL_INT SizeY, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_BUF_ID(MbufChild2d(ParentBufId, OffX, OffY, SizeX, SizeY, M_NULL));
   }
inline MIL_UNIQUE_BUF_ID MbufChildColor2d(MIL_ID ParentBufId, MIL_INT Band, MIL_INT OffX, MIL_INT OffY, MIL_INT SizeX, MIL_INT SizeY, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_BUF_ID(MbufChildColor2d(ParentBufId, Band, OffX, OffY, SizeX, SizeY, M_NULL));
   }
inline MIL_UNIQUE_BUF_ID MbufChildColor2dClip(MIL_ID ParentBufId, MIL_INT Band, MIL_INT OffX, MIL_INT OffY, MIL_INT SizeX, MIL_INT SizeY, MIL_INT* StatusPtr, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_BUF_ID(MbufChildColor2dClip(ParentBufId, Band, OffX, OffY, SizeX, SizeY, StatusPtr, M_NULL));
   }
inline MIL_UNIQUE_BUF_ID MbufChildColor(MIL_ID ParentBufId, MIL_INT Band, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_BUF_ID(MbufChildColor(ParentBufId, Band, M_NULL));
   }
inline MIL_UNIQUE_BUF_ID MbufChildContainer(MIL_ID ContId, MIL_INT ComponentCriteriaSize, const MIL_INT64* ComponentCriteriaArrayPtr, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_BUF_ID(MbufChildContainer(ContId, ComponentCriteriaSize, ComponentCriteriaArrayPtr, ControlFlag, M_NULL));
   }
inline MIL_UNIQUE_BUF_ID MbufClone(MIL_ID SrcBufId, MIL_ID SysId, MIL_INT SizeX, MIL_INT SizeY, MIL_INT Type, MIL_INT64 Attribute, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_BUF_ID(MbufClone(SrcBufId, SysId, SizeX, SizeY, Type, Attribute, ControlFlag, M_NULL));
   }
inline MIL_UNIQUE_BUF_ID MbufCreate2dFunc(MIL_ID SystemId, MIL_INT SizeX, MIL_INT SizeY, MIL_INT Type, MIL_INT64 Attribute, MIL_INT64 ControlFlag, MIL_INT Pitch, MIL_DATA_PTR DataPtr, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_BUF_ID(MbufCreate2dFunc(SystemId, SizeX, SizeY, Type, Attribute, ControlFlag, Pitch, DataPtr, M_NULL));
   }
inline MIL_UNIQUE_BUF_ID MbufCreateColor(MIL_ID SystemId, MIL_INT SizeBand, MIL_INT SizeX, MIL_INT SizeY, MIL_INT Type, MIL_INT64 Attribute, MIL_INT64 ControlFlag, MIL_INT Pitch, void** ArrayOfDataPtr, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_BUF_ID(MbufCreateColor(SystemId, SizeBand, SizeX, SizeY, Type, Attribute, ControlFlag, Pitch, ArrayOfDataPtr, M_NULL));
   }
inline MIL_UNIQUE_BUF_ID MbufRestore(MIL_CONST_TEXT_PTR FileName, MIL_ID SystemId, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_BUF_ID(MbufRestore(FileName, SystemId, M_NULL));
   }
#if M_MIL_USE_STRING
inline MIL_UNIQUE_BUF_ID MbufRestore(const MIL_STRING& FileName, MIL_ID SystemId, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_BUF_ID(MbufRestore(FileName, SystemId, M_NULL));
   }
#endif
template <MilFreeFuncType FreeFunc> inline void MbufFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

inline void MbufExportSequence(
      MIL_CONST_TEXT_PTR   FileName                ,
      MIL_INT64            FileFormat              ,
      MilConstArrayIdParam BufArrayPtrOrSystemIdPtr,
      MIL_INT              NumOfIds                ,
      MIL_DOUBLE           FrameRate               ,
      MIL_INT64            ControlFlag             )
   {
   MbufExportSequence(FileName, FileFormat, BufArrayPtrOrSystemIdPtr.m_IdArrayPtr,
                      NumOfIds, FrameRate, ControlFlag);
   }
inline MIL_ID MbufImport(MIL_CONST_TEXT_PTR FileName, MIL_INT64 FileFormat, MIL_INT64 Operation, MIL_ID SystemId, int)
   {
   return MbufImport(FileName, FileFormat, Operation, SystemId, static_cast<MIL_ID*>(0));
   }
#if M_MIL_USE_NULLPTR
inline MIL_ID MbufImport(MIL_CONST_TEXT_PTR FileName, MIL_INT64 FileFormat, MIL_INT64 Operation, MIL_ID SystemId, std::nullptr_t)
   {
   return MbufImport(FileName, FileFormat, Operation, SystemId, static_cast<MIL_ID*>(0));
   }
#endif 
inline MIL_ID MbufImport(MIL_CONST_TEXT_PTR FileName, MIL_INT64 FileFormat, MIL_INT64 Operation, MIL_ID SystemId, MIL_UNIQUE_BUF_ID* BufIdPtr)
   {
   if (BufIdPtr)
      {
      MIL_ID TempBufId = BufIdPtr->get();
      MIL_ID ReturnValue = MbufImport(FileName, FileFormat, Operation, SystemId, &TempBufId);
      if (Operation & M_RESTORE)
         BufIdPtr->reset(TempBufId);
      return ReturnValue;
      }
   else
      {
      return MbufImport(FileName, FileFormat, Operation, SystemId, static_cast<MIL_ID*>(0));
      }
   }
inline  MIL_UNIQUE_BUF_ID MbufImport(MIL_CONST_TEXT_PTR FileName, MIL_INT64 FileFormat, MIL_INT64 Operation, MIL_ID SystemId, MIL_UNIQUE_ID_TAG)
   {
#if M_MIL_USE_SAFE_TYPE
   if ((Operation & M_RESTORE) != M_RESTORE)
      SafeTypeError(MIL_TEXT("MbufImport"), MIL_TEXT("This overload only supports the M_RESTORE operation."));
#endif
   return MIL_UNIQUE_BUF_ID(MbufImport(FileName, FileFormat, Operation, SystemId, M_NULL));
   }

#if M_MIL_USE_STRING
inline void MbufExportSequence(
      const MIL_STRING&    FileName                ,
      MIL_INT64            FileFormat              ,
      MilConstArrayIdParam BufArrayPtrOrSystemIdPtr,
      MIL_INT              NumOfIds                ,
      MIL_DOUBLE           FrameRate               ,
      MIL_INT64            ControlFlag             )
   {
   MbufExportSequence(FileName.c_str(), FileFormat, BufArrayPtrOrSystemIdPtr.m_IdArrayPtr,
                      NumOfIds, FrameRate, ControlFlag);
   }
inline MIL_ID MbufImport(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_INT64 Operation, MIL_ID SystemId, int)
   {
   return MbufImport(FileName.c_str(), FileFormat, Operation, SystemId, static_cast<MIL_ID*>(0));
   }
#if M_MIL_USE_NULLPTR
inline MIL_ID MbufImport(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_INT64 Operation, MIL_ID SystemId, std::nullptr_t)
   {
   return MbufImport(FileName.c_str(), FileFormat, Operation, SystemId, static_cast<MIL_ID*>(0));
   }
#endif
inline MIL_ID MbufImport(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_INT64 Operation, MIL_ID SystemId, MIL_UNIQUE_BUF_ID* BufIdPtr)
   {
   return MbufImport(FileName.c_str(), FileFormat, Operation, SystemId, BufIdPtr);
   }
inline  MIL_UNIQUE_BUF_ID MbufImport(const MIL_STRING& FileName, MIL_INT64 FileFormat, MIL_INT64 Operation, MIL_ID SystemId, MIL_UNIQUE_ID_TAG)
   {
#if M_MIL_USE_SAFE_TYPE
   if(Operation != M_RESTORE)
      SafeTypeError(MIL_TEXT("MbufImport"), MIL_TEXT("This overload only supports the M_RESTORE operation."));
#endif
   return MIL_UNIQUE_BUF_ID(MbufImport(FileName.c_str(), FileFormat, Operation, SystemId, M_NULL));
   }
#endif

inline void MbufStream(MilStreamParam     MemPtrOrFileName,
                       MIL_ID             SysId,
                       MIL_INT64          Operation,
                       MIL_INT64          StreamType,
                       MIL_DOUBLE         Version,
                       MIL_INT64          ControlFlag,
                       MIL_UNIQUE_BUF_ID* MbufIdPtr,
                       MIL_INT*           SizeByteVarPtr)
   {
   MxxxStreamForMilUniqueId(MemPtrOrFileName, SysId, Operation, StreamType, Version, ControlFlag, MbufIdPtr, SizeByteVarPtr, MbufStream);
   }

// DIG
inline MIL_UNIQUE_DIG_ID MdigAlloc(MIL_ID SystemId, MIL_INT DigNum, MIL_CONST_TEXT_PTR DataFormat, MIL_INT64 InitFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_DIG_ID(MdigAlloc(SystemId, DigNum, DataFormat, InitFlag, M_NULL));
   }
#if M_MIL_USE_STRING
inline MIL_UNIQUE_DIG_ID MdigAlloc(MIL_ID SystemId, MIL_INT DigNum, const MIL_STRING& DataFormat, MIL_INT64 InitFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_DIG_ID(MdigAlloc(SystemId, DigNum, DataFormat, InitFlag, M_NULL));
   }
#endif
template <MilFreeFuncType FreeFunc> inline void MdigFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

inline void MdigProcess(
   MIL_ID                    DigId,
   MilConstArrayIdParam      DestImageArrayPtr,
   MIL_INT                   ImageCount,
   MIL_INT64                 Operation,
   MIL_INT64                 OperationFlag,
   MIL_DIG_HOOK_FUNCTION_PTR HookHandlerPtr,
   void*                     UserDataPtr)
   {
   MdigProcess(DigId, DestImageArrayPtr.m_IdArrayPtr, ImageCount,
               Operation, OperationFlag, HookHandlerPtr, UserDataPtr);
   }

// GRA
inline MIL_UNIQUE_GRA_ID MgraAlloc(MIL_ID SysId, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_GRA_ID(MgraAlloc(SysId, M_NULL));
   }
inline MIL_UNIQUE_GRA_ID MgraAllocList(MIL_ID SysId, MIL_INT ListGraType, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_GRA_ID(MgraAllocList(SysId, ListGraType, M_NULL));
   }
template <MilFreeFuncType FreeFunc> inline void MgraFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

// OBJ
inline MIL_UNIQUE_OBJ_ID MobjAlloc(MIL_ID SysId, MIL_INT64 ObjectType, MIL_INT64 InitFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_OBJ_ID(MobjAlloc(SysId, ObjectType, InitFlag, M_NULL));
   }
template <MilFreeFuncType FreeFunc> inline void MobjFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

// SEQ
#if !M_MIL_USE_LINUX || M_MIL_USE_64BIT
inline MIL_UNIQUE_SEQ_ID MseqAlloc(MIL_ID SystemId, MIL_INT64 SequenceType, MIL_INT64 Operation, MIL_UINT32 OutputFormat, MIL_INT64 InitFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_SEQ_ID(MseqAlloc(SystemId, SequenceType, Operation, OutputFormat, InitFlag, M_NULL));
   }
template <MilFreeFuncType FreeFunc> inline void MseqFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;
#endif

// SYS
inline MIL_UNIQUE_SYS_ID MsysAlloc(MIL_ID ContextAppId, MIL_CONST_TEXT_PTR SystemDescriptor, MIL_INT SystemNum, MIL_INT64 InitFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_SYS_ID(MsysAlloc(ContextAppId, SystemDescriptor, SystemNum, InitFlag, M_NULL));
   }
#if M_MIL_USE_STRING
inline MIL_UNIQUE_SYS_ID MsysAlloc(MIL_ID ContextAppId, const MIL_STRING& SystemDescriptor, MIL_INT SystemNum, MIL_INT64 InitFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_SYS_ID(MsysAlloc(ContextAppId, SystemDescriptor, SystemNum, InitFlag, M_NULL));
   }
#endif
template <MilFreeFuncType FreeFunc> inline void MsysFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

// SYSIO
inline MIL_UNIQUE_SYSIO_ID MsysIoAlloc(MIL_ID SysId, MIL_INT64 IoCmdListNum, MIL_INT64 Type, MIL_INT64 CounterSrc, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_SYSIO_ID(MsysIoAlloc(SysId, IoCmdListNum, Type, CounterSrc, M_NULL));
   }
template <MilFreeFuncType FreeFunc> inline void MsysIoFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

// THR
inline MIL_UNIQUE_THR_ID MthrAlloc(MIL_ID SystemId, MIL_INT64 ObjectType, MIL_INT64 ControlFlag, MIL_THREAD_FUNCTION_PTR ThreadFctPtr, void *UserDataPtr, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_THR_ID(MthrAlloc(SystemId, ObjectType, ControlFlag, ThreadFctPtr, UserDataPtr, M_NULL));
   }
template <MilFreeFuncType FreeFunc> inline void MthrFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

inline MIL_INT MthrWaitMultiple(MilConstArrayIdParam EventArrayIdPtr, MIL_INT EventArraySize, MIL_INT64 WaitOption, MIL_INT *StatePtr)
   {
   return MthrWaitMultiple(EventArrayIdPtr.m_IdArrayPtr, EventArraySize, WaitOption, StatePtr);
   }

#endif // #if M_MIL_USE_MOVE_SEMANTICS

#endif // #if M_MIL_USE_MIL_UNIQUE_ID

#endif // #ifndef __UNIQUE_MIL_ID_H
