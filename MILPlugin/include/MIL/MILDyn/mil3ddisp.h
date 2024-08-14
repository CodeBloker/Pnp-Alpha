/////////////////////////////////////////////////////////////////
//
// Filename          :  MIL3DDISP.H
// Content           :  Define for the MIL 3DDISP module
// Revision          :  10.40.0881
//
// Copyright © Matrox Electronic Systems Ltd., 1992-2021.
// All Rights Reserved
//
/////////////////////////////////////////////////////////////////


#ifndef __MIL3DDISP_H__
#define __MIL3DDISP_H__

// None of this should clash with disp (2d) controls so that if we want to forward them to the
// 2d display it will be trivial. Should also reuse creation types from 2d.

/* C++ directive if needed */
#ifdef __cplusplus
   extern "C"
      {
#endif

typedef MIL_INT(MFTYPE *MIL_3DDISP_HOOK_FUNCTION_PTR)(MIL_INT HookType,
                                                     MIL_ID  EventId,
                                                     void    *UserDataPtr);

#define M_VTK_TRACKBALL                                        0x00000002L                                         
#define M_VTK_TERRAIN                                          0x00000003L 
#define M_TEST_OPENGL                                          0x00000004L 
#define M_VTK_WINDOW                                           0x00000020L // Reserved in mildisplay.h

// M3ddispSelect  
#define M_OPEN                                                 0x00000010L // Already defined from mil.h
#define M_CLOSE                                                0x00000020L // Already defined from mil.h
#define M_ADD                                                  0x0000L     // Already defined in milocr.h, milim.h
#define M_REMOVE                                               0x00000004L // Already defined in milim.h
#define M_SELECT                                               3977L

// These should not clash with disp2d
// M3ddispAlloc
//#define M_WINDOWED_DISPLAY                                     0L
#define M_MIL_BUFFER_WINDOW                                    2L
#define M_WEB                                                  0x00800000L // Already defined in mil.h, mildisplay.h

// M3ddispControl types
#define M_3D_GRAPHIC_LIST_ID                                    4111
#define M_ROTATION_INDICATOR                                    4627
#define M_BACKGROUND_IMAGE                                      4628
#define M_BACKGROUND_IMAGE_SIZE_X                               4629
#define M_BACKGROUND_IMAGE_SIZE_Y                               4630
#define M_BACKGROUND_IMAGE_SIZE_BAND                            4631
#define M_AUTO_ROTATE                                           4633
#define M_ROTATION_SPEED                                        4634
#define M_ROTATION_AXIS                                         4636

#define M_ACTION_KEY_TRANSLATE_FORWARD                          4638
#define M_ACTION_KEY_TRANSLATE_BACKWARD                         4639
#define M_ACTION_KEY_TRANSLATE_DOWN                             2755L
#define M_ACTION_KEY_TRANSLATE_LEFT                             2756L
#define M_ACTION_KEY_TRANSLATE_RIGHT                            2757L
#define M_ACTION_KEY_TRANSLATE_UP                               2758L
#define M_ACTION_KEY_ROLL_LEFT                                  4640
#define M_ACTION_KEY_ROLL_RIGHT                                 4641
#define M_ACTION_KEY_ORBIT_LEFT                                 4642
#define M_ACTION_KEY_ORBIT_RIGHT                                4643
#define M_ACTION_KEY_ORBIT_UP                                   4644
#define M_ACTION_KEY_ORBIT_DOWN                                 4645
#define M_ACTION_KEY_TURN_LEFT                                  4646
#define M_ACTION_KEY_TURN_RIGHT                                 4647
#define M_ACTION_KEY_TURN_UP                                    4648
#define M_ACTION_KEY_TURN_DOWN                                  4649
#define M_ACTION_KEY_ZOOM_IN                                    4650
#define M_ACTION_KEY_ZOOM_OUT                                   4651
#define M_ACTION_KEY_RESET                                      4652
#define M_ALTERNATE_SPEED_FACTOR                                4653
#define M_BACKGROUND_COLOR_GRADIENT                             4654
#define M_ACTION_KEY_AUTO_ROTATE                                4658
#define M_ACTION_KEY_ORIENTATION_TOP_VIEW                       4659
#define M_ACTION_KEY_ORIENTATION_BOTTOM_VIEW                    4660
#define M_ACTION_KEY_ORIENTATION_FRONT_VIEW                     4661
#define M_ACTION_KEY_ORIENTATION_REAR_VIEW                      4662
#define M_ACTION_KEY_ORIENTATION_LEFT_VIEW                      4663
#define M_ACTION_KEY_ORIENTATION_RIGHT_VIEW                     4664
#define M_ACTION_KEY_ORIENTATION_TOP_TILTED                     4665
#define M_ACTION_KEY_ORIENTATION_BOTTOM_TILTED                  4666

#define M_ACTION_MODIFIER_SPEED                       		    2759L

#define M_DISP_CONTROL_START                                    10000L                              // Already defined in mildisplay.h (10000L)
#define M_BACKGROUND_COLOR                                      (M_DISP_CONTROL_START+66L)          // Already defined in mildisplay.h (10066) M_LOCAL_DISPLAY_CONTROL
#define M_TITLE                                                 (7702L|M_CLIENT_ENCODING)           // Already defined in mildisplay.h M_LOCAL_DISPLAY_CONTROL
#define M_DISPLAY_SYNC                                          (M_DISP_CONTROL_START+47L)          // Already defined in mildisplay.h (10047) M_LOCAL_DISPLAY_CONTROL
#define M_QT_MODE                                               (M_DISP_CONTROL_START+151L)         // already defined in mildisplay.h (10151) M_LOCAL_DISPLAY_CONTROL
#define M_WINDOW_CURSOR                                         (M_DISP_CONTROL_START+199L)         // already defined in mildisplay.h (10199) M_LOCAL_DISPLAY_CONTROL
#define M_SELECTED                                              1103L //M_REMOTE_DISPLAY_CONTROL   // Already defined in mildisplay.h
#define M_DISPLAY_SURFACE                                       1121L                              // Already defined in mildisplay.h M_LOCAL_DISPLAY_CONTROL          
#define M_WPF_DISPLAY_BUFFER_ID                                 M_DISPLAY_SURFACE                  // Already defined in mildisplay.h           
#define M_WINDOW_INITIAL_POSITION_X                             3088L //M_LOCAL_DISPLAY_CONTROL    // Already defined in mildisplay.h
#define M_WINDOW_INITIAL_POSITION_Y                             3089L //M_LOCAL_DISPLAY_CONTROL    // Already defined in mildisplay.h
#define M_WINDOW_HANDLE                                         3110L //M_LOCAL_DISPLAY_CONTROL    // Already defined in mildisplay.h
#define M_MOUSE_USE                                             3219L //M_LOCAL_DISPLAY_CONTROL    // Already defined in mildisplay.h
#define M_KEYBOARD_USE                                          3155L //M_LOCAL_DISPLAY_CONTROL    // Already defined in mildisplay.h
#define M_SAVE_INTERNAL_BUFFERS                                (M_DISP_CONTROL_START+26L) //(10026) M_LOCAL_DISPLAY_CONTROL Already defined in mildisplay.h

#define M_BACKGROUND_MODE                                       12L //already defined
#define M_SINGLE_COLOR                                          3969 
#define M_GRADIENT_VERTICAL                                     3970
#define M_STRING_SIZE                                    MAKE_INT64(0x0000050000000000)
#define M_UPDATE                                                3199L                     //M_REMOTE_DISPLAY_CONTROL defined in mildisplay.h
#define M_SIZE_X                                                1536L       // Already defined in    milcode.h, mil.h
#define M_SIZE_Y                                                1537L       // Already defined in    milcode.h, mil.h
#define M_ENABLE_ON_MOUSE_CLICK                                 3973L
                                                                                                              
// M3ddispControl
// MIL_DOUBLE
#define M_FOV_HORIZONTAL_ANGLE                                  4667
#define M_FOV_VERTICAL_ANGLE                                    4668

// List of 2d values that are whitelisted
#ifdef __cplusplus       
      inline bool In2dDisplayControlsWhiteList(MIL_INT64 ControlType)
         {
         switch(ControlType)
            {
            case M_QT_MODE:
            case M_WPF_DISPLAY_BUFFER_ID:
            case M_DISPLAY_SYNC:
            case M_WINDOW_CURSOR:
            case M_WINDOW_HANDLE:
            case M_SELECTED:
            case M_SAVE_INTERNAL_BUFFERS:
               return true;
            default:
               return false;

            }
         }
#endif

////////////////////////////////////////////////////////////////////////////////////////////////
//Dispcontrol values
////////////////////////////////////////////////////////////////////////////////////////////////
#define M_RED                                                            0x08L
#define M_GREEN                                                          0x10L
#define M_BLUE                                                           0x20L

#define M_ENABLE                                                        -9997L                              // Already defined in    milblob.h, milcal.h, milmeas.h, mil.h, miledge.h
#define M_DISABLE                                                       -9999L                              // Already defined in    milblob.h, milcal.h, milmeas.h, mil.h, miledge.h

#define M_NOW                                                              29L
#define M_ALLOCATION_FAILURE_REAL_TEST_FLAG                               971L // Also in milblob.h
////////////////////////////////////////////////////////////////////////////////

// M3ddispSet/GetViewpoint
#define M_VIEW_MATRIX                                                    4161L
#define M_TRAVEL                                                         4162L
#define M_VIEWPOINT                                                      4163L
#define M_INTEREST_POINT                                                 4164L
#define M_UP_VECTOR                                                      4165L
#define M_VIEW_BOX                                                       4166L
#define M_NO_REFRESH                                                     4167L
#define M_TOP_VIEW                                                       4168L
#define M_BOTTOM_VIEW                                                    4169L
#define M_LEFT_VIEW                                                      4170L
#define M_RIGHT_VIEW                                                     4171L
#define M_FRONT_VIEW                                                     4172L
#define M_REAR_VIEW                                                      4173L
#define M_TOP_TILTED                                                     4174L
#define M_BOTTOM_TILTED                                                  4175L
#define M_ORBIT_HORIZONTAL                                               4177L
#define M_ORBIT_VERTICAL                                                 4178L
#define M_AZIM_ELEV_ROLL                                                    4L  // already defined in milreg.h
#define M_TRANSLATE                                                         5L  // already defined in mil.h
#define M_DISTANCE                                                 0x00080000L  // already defined in milim.h
#define M_FLIP                                                     0x00010000L  // already defined in milim.h
#define M_ELEVATION                                                        49L  // already defined in milreg.h
#define M_AZIMUTH                                                          50L  // already defined in milreg.h
#define M_ROLL                                                             51L  // already defined in milreg.h
#define M_VIEW_ORIENTATION                                         0x00200000L
#define M_TRANSFORM_TYPES_SHIFT                                             8L  // =utilities=   (also defined in milcal.h)
#define M_MOVE_INTEREST_POINT                     (128 << M_TRANSFORM_TYPES_SHIFT)
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
// Hook values
////////////////////////////////////////////////////////////////////////////////////////////////
#define M_OBJ_HOOK_MODULE_RANGE_START                 0x00000FE00L    // Already defined in mil.h
#define M_OBJ_HOOK_MODULE_RANGE_END                   0x00000FFFFL    // Already defined in mil.h

// 3ddisplay hook

////////////////////////////////////////////////////////////////////////////////////////////////


   // M3ddisp calls
   void      MFTYPE M3ddispControlInt64(MIL_ID Disp3dId, MIL_INT64 ControlType, MIL_INT64 ControlValue);
   void      MFTYPE M3ddispControlDouble(MIL_ID Disp3dId, MIL_INT64 ControlType, MIL_DOUBLE ControlValue);
   void      MFTYPE M3ddispFree(MIL_ID Disp3dId);
   MIL_INT64 MFTYPE M3ddispInquire(MIL_ID Disp3dId, MIL_INT64 InquireType, void *UserVarPtr);
   MIL_INT64 MFTYPE M3ddispSelect(MIL_ID Disp3dId, MIL_ID ContainerOrImageBufId, MIL_INT64 Option, MIL_INT64 ControlFlag);
   MIL_INT64 MFTYPE M3ddispSelectWindow(MIL_ID Disp3dId, MIL_ID ContainerOrImageBufId, MIL_INT64 Option, MIL_INT64 ControlFlag, MIL_WINDOW_HANDLE ClientWindowHandle);
   void      MFTYPE M3ddispSetViewDouble(MIL_ID Disp3dId, MIL_INT64 Mode, const MIL_DOUBLE Param1, const MIL_DOUBLE Param2, const MIL_DOUBLE Param3, MIL_INT64   ControlFlag);
   void      MFTYPE M3ddispGetView(MIL_ID Disp3dId, MIL_INT64 Mode, MIL_DOUBLE* Param1Ptr, MIL_DOUBLE* Param2Ptr, MIL_DOUBLE* Param3Ptr, MIL_INT64   ControlFlag);
   void      MFTYPE M3ddispCopy(MIL_ID SrcMilObjectId, MIL_ID DstMilObjectId, MIL_INT64 CopyType, MIL_INT64 ControlFlag);
   void      MFTYPE M3ddispMessage(MIL_ID Disp3dId, MIL_INT64 EventType, MIL_INT64 MousePositionX, MIL_INT64 MousePositionY, MIL_INT64 EventValue, MIL_INT64 CombinationKeys, MIL_INT64 UserValue);
   void      MFTYPE M3ddispHookFunction(MIL_ID Disp3dId, MIL_INT HookType, MIL_3DDISP_HOOK_FUNCTION_PTR HookHandlerPtr, void* UserDataPtr);
   MIL_INT64 MFTYPE M3ddispGetHookInfo(MIL_ID EventId, MIL_INT64 InfoType, void* UserVarPtr);

   // For CAPI calls with strings
#if M_MIL_USE_UNICODE
   MIL_ID    MFTYPE M3ddispAllocA(MIL_ID SysId, MIL_INT64 DispNum, MIL_CONST_TEXTA_PTR DispFormat, MIL_INT64 InitFlag, MIL_ID *Disp3dIdPtr);
   MIL_ID    MFTYPE M3ddispAllocW(MIL_ID SysId, MIL_INT64 DispNum, MIL_CONST_TEXTW_PTR DispFormat, MIL_INT64 InitFlag, MIL_ID *Disp3dIdPtr);

   // create default calls
#if M_MIL_UNICODE_API
#define M3ddispAlloc M3ddispAllocW
#else
#define M3ddispAlloc M3ddispAllocA
#endif

#else
   MIL_ID    MFTYPE M3ddispAlloc(MIL_ID SysId, MIL_INT64 DispNum, MIL_CONST_TEXT_PTR DispFormat, MIL_INT64 InitFlag, MIL_ID *Display3dIdPtr);
#endif

#ifdef __cplusplus
   inline bool In3ddispInquireDoubleRange(MIL_INT64 InquireType)
      {
      if(M_NB_ELEMENTS_BIT_SET(InquireType))
         {
         return false;
         }

      switch(M_STRIP_INQ_COMBOFLAGS(InquireType))
         {
         case M_ALLOCATION_FAILURE_REAL_TEST_FLAG:
         case M_FOV_HORIZONTAL_ANGLE:
         case M_FOV_VERTICAL_ANGLE:
         case M_ALTERNATE_SPEED_FACTOR:
         case M_ROTATION_SPEED:
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
   inline bool In3ddispInquireIdRange(MIL_INT64 InquireType)
      {
      switch(M_STRIP_INQ_COMBOFLAGS(InquireType))
         {
         case M_3D_GRAPHIC_LIST_ID:
            return true;

         default:
            break;
         }
      return false;
      }
   inline bool In3ddispInquireStringRange(MIL_INT64 InquireType)
      {
      if(M_NB_ELEMENTS_BIT_SET(InquireType))
         {
         return false;
         }

      switch(M_STRIP_CLIENT_TEXT_ENCODING(M_STRIP_INQ_COMBOFLAGS(InquireType)))
         {
         case M_STRIP_CLIENT_TEXT_ENCODING(M_TITLE):
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
   inline bool In3ddispInquireInt64Range(MIL_INT64 InquireType)
      {

      switch(M_STRIP_INQ_COMBOFLAGS(InquireType))
         {
         case M_BACKGROUND_COLOR:
            return true;

         default:
            break;
         }

      return false;
      }
   inline bool M3ddispInquireMustHaveUserPtr(MIL_INT64 InquireType)
      {
      const MIL_INT64 ForcedDataType = MinquireOverrides(M_STRIP_HLVLDATATYPE(InquireType), M_TYPE_MIL_INT);
      if(ForcedDataType != 0)
         {
         return false;
         }
      return In3ddispInquireStringRange(InquireType) || In3ddispInquireDoubleRange(InquireType);
      }
   #endif // __cplusplus
   /* C++ directive if needed */
#ifdef __cplusplus
   }
#endif

#ifdef __cplusplus
inline void M3ddispControl(MIL_ID Disp3dId, MIL_INT64 ControlType, MIL_DOUBLE ControlValue)
   {
   M3ddispControlDouble(Disp3dId, ControlType, ControlValue);
   }

inline void M3ddispControl(MIL_ID Disp3dId, MIL_INT64 ControlType, MIL_INT64 ControlValue)
   {
   M3ddispControlInt64(Disp3dId, ControlType, ControlValue);
   }

inline void M3ddispControl(MIL_ID Disp3dId, MIL_INT64 ControlType, MIL_INT32 ControlValue)
   {
   M3ddispControlInt64(Disp3dId, ControlType, ControlValue);
   }

#if !(M_MIL_USE_LINUX && M_MIL_USE_64BIT)
inline void M3ddispControl(MIL_ID Disp3dId, MIL_INT64 ControlType, int ControlValue)
   {
   M3ddispControlInt64(Disp3dId, ControlType, ControlValue);
   }
#endif

inline void M3ddispControl(MIL_ID Disp3dId, MIL_INT64 ControlType, MIL_CONST_TEXT_PTR ControlValue)
   {
   M3ddispControl(Disp3dId, ControlType, (MIL_INT)ControlValue);
   }
#else
#define M3ddispControl      M3ddispControlDouble
#endif

#ifdef __cplusplus
inline MIL_INT64 M3ddispInquireDataType(MIL_INT64 InquireType)
   {
   const MIL_INT64 ForcedDataType = MinquireOverrides(InquireType, M_TYPE_MIL_INT);
   if(ForcedDataType != 0)
      return ForcedDataType;
  
   if(In3ddispInquireIdRange(InquireType))
      {
      return M_TYPE_MIL_ID;
      }
   if(In3ddispInquireStringRange(InquireType))
      {
      return M_TYPE_TEXT_CHAR;
      }
   if(In3ddispInquireInt64Range(InquireType))
      {
      return M_TYPE_MIL_INT64;
      }

   if(In3ddispInquireDoubleRange(InquireType))
      {
      return M_TYPE_MIL_DOUBLE;
      }

   return M_TYPE_MIL_INT;
   }
#if M_MIL_USE_SAFE_TYPE
// ----------------------------------------------------------
// M3ddispInquire
inline MIL_INT64 MFTYPE M3ddispInquireSafeType(MIL_ID Disp3dId, MIL_INT64 InquireType, int UserVarPtr)
   {
   bool MustHaveUserPointer = M3ddispInquireMustHaveUserPtr(InquireType);

   if(UserVarPtr)
      SafeTypeError(MIL_TEXT("M3ddispInquire"));

   if(!UserVarPtr && MustHaveUserPointer)
      SafeTypeError(MIL_TEXT("M3ddispInquire"), MIL_TEXT("The specified InquireType requires a non-null output pointer."));

   return M3ddispInquire(Disp3dId, InquireType, NULL);
   }
#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
inline MIL_INT64 MFTYPE M3ddispInquireSafeType(MIL_ID Disp3dId, MIL_INT64 InquireType, std::nullptr_t)
   {
   bool MustHaveUserPointer = M3ddispInquireMustHaveUserPtr(InquireType);

   if(MustHaveUserPointer)
      SafeTypeError(MIL_TEXT("M3ddispInquire"), MIL_TEXT("The specified InquireType requires a non-null output pointer."));
   return M3ddispInquire(Disp3dId, InquireType, NULL);
   }
#endif

inline MIL_INT64 MFTYPE M3ddispInquireSafeTypeExecute(MIL_ID Disp3dId, MIL_INT64  InquireType, void  *UserVarPtr, MIL_INT64  GivenType)
   {
   MIL_INT64 RequiredType = M_NULL;
   // Looking for M_TYPE flags
   RequiredType = M3ddispInquireDataType(InquireType);
   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if(RequiredType != GivenType)
      {
      SafeTypeError(MIL_TEXT("M3ddispInquire"));
      }

   return M3ddispInquire(Disp3dId, InquireType, UserVarPtr);
   }

inline MIL_INT64 MFTYPE M3ddispInquireUnsafe(MIL_ID Disp3dId, MIL_INT64  InquireType, void        *UserVarPtr) { return M3ddispInquire(Disp3dId, InquireType, UserVarPtr); }
inline MIL_INT64 MFTYPE M3ddispInquireSafeType(MIL_ID Disp3dId, MIL_INT64  InquireType, MIL_INT8*   UserVarPtr) { return M3ddispInquireSafeTypeExecute(Disp3dId, InquireType, UserVarPtr, M_TYPE_CHAR); }
inline MIL_INT64 MFTYPE M3ddispInquireSafeType(MIL_ID Disp3dId, MIL_INT64  InquireType, MIL_INT16*  UserVarPtr) { return M3ddispInquireSafeTypeExecute(Disp3dId, InquireType, UserVarPtr, M_TYPE_SHORT); }
inline MIL_INT64 MFTYPE M3ddispInquireSafeType(MIL_ID Disp3dId, MIL_INT64  InquireType, MIL_INT32   *UserVarPtr) { return M3ddispInquireSafeTypeExecute(Disp3dId, InquireType, UserVarPtr, M_TYPE_MIL_INT32); }
inline MIL_INT64 MFTYPE M3ddispInquireSafeType(MIL_ID Disp3dId, MIL_INT64  InquireType, MIL_INT64   *UserVarPtr) { return M3ddispInquireSafeTypeExecute(Disp3dId, InquireType, UserVarPtr, M_TYPE_MIL_INT64); }
inline MIL_INT64 MFTYPE M3ddispInquireSafeType(MIL_ID Disp3dId, MIL_INT64  InquireType, MIL_FLOAT   *UserVarPtr) { return M3ddispInquireSafeTypeExecute(Disp3dId, InquireType, UserVarPtr, M_TYPE_MIL_FLOAT); }
inline MIL_INT64 MFTYPE M3ddispInquireSafeType(MIL_ID Disp3dId, MIL_INT64  InquireType, MIL_DOUBLE  *UserVarPtr) { return M3ddispInquireSafeTypeExecute(Disp3dId, InquireType, UserVarPtr, M_TYPE_DOUBLE); }
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline MIL_INT64 MFTYPE M3ddispInquireSafeType(MIL_ID Disp3dId, MIL_INT64  InquireType, MIL_UINT8*   UserVarPtr) { return M3ddispInquireSafeTypeExecute(Disp3dId, InquireType, UserVarPtr, M_TYPE_CHAR); }
inline MIL_INT64 MFTYPE M3ddispInquireSafeType(MIL_ID Disp3dId, MIL_INT64  InquireType, MIL_UINT16*  UserVarPtr) { return M3ddispInquireSafeTypeExecute(Disp3dId, InquireType, UserVarPtr, M_TYPE_SHORT); }
inline MIL_INT64 MFTYPE M3ddispInquireSafeType(MIL_ID Disp3dId, MIL_INT64  InquireType, MIL_UINT32  *UserVarPtr) { return M3ddispInquireSafeTypeExecute(Disp3dId, InquireType, UserVarPtr, M_TYPE_MIL_INT32); }
inline MIL_INT64 MFTYPE M3ddispInquireSafeType(MIL_ID Disp3dId, MIL_INT64  InquireType, MIL_UINT64  *UserVarPtr) { return M3ddispInquireSafeTypeExecute(Disp3dId, InquireType, UserVarPtr, M_TYPE_MIL_INT64); }
#endif
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T                                                      
inline MIL_INT64 MFTYPE M3ddispInquireSafeType(MIL_ID Disp3dId, MIL_INT64  InquireType, wchar_t*    UserVarPtr) { return M3ddispInquireSafeTypeExecute(Disp3dId, InquireType, UserVarPtr, M_TYPE_TEXT_CHAR); }
#endif

#define M3ddispInquire          M3ddispInquireSafeType
#else // #if M_MIL_USE_SAFE_TYPE

#define M3ddispInquireUnsafe    M3ddispInquire 

#endif // #if M_MIL_USE_SAFE_TYPE

#endif //__cplusplus

#if M_MIL_USE_STRING
inline MIL_ID    MFTYPE M3ddispAlloc(MIL_ID SysId, MIL_INT64 DispNum, const MIL_STRING& ControlFlag, MIL_INT64 InitFlag, MIL_ID *Display3dIdPtr)
   {
   return M3ddispAlloc(SysId, DispNum, ControlFlag.c_str(), InitFlag, Display3dIdPtr);
   }
#if M_MIL_USE_SAFE_TYPE

inline MIL_INT64 MFTYPE M3ddispInquireSafeType(MIL_ID Disp3dId, MIL_INT64  InquireType, MIL_STRING& UserVarPtr)
   {
   MIL_INT64 RetValue = 0;
   MIL_INT InternalStringSize = 0;

   if(!In3ddispInquireStringRange(InquireType))
      {
      SafeTypeError(MIL_TEXT("M3ddispInquire"), MIL_TEXT("Inquire type not supported with MIL_STRING."));
      }

   M3ddispInquire(Disp3dId, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = M3ddispInquire(Disp3dId, InquireType, &UserVarPtr[0]);
      UserVarPtr.resize(InternalStringSize - 1);


      }

   return RetValue;
   }
#else
inline MIL_INT64 MFTYPE M3ddispInquire(MIL_ID Disp3dId, MIL_INT64  InquireType, MIL_STRING& UserVarPtr)
   {
   MIL_INT64 RetValue = 0;
   MIL_INT InternalStringSize = 0;

   M3ddispInquire(Disp3dId, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = M3ddispInquire(Disp3dId, InquireType, &UserVarPtr[0]);
      UserVarPtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }
#endif // #if M_MIL_USE_SAFE_TYPE
inline void M3ddispControl(MIL_ID Disp3dId, MIL_INT64 ControlType, const MIL_STRING& ControlValue)
   {
   M3ddispControl(Disp3dId, ControlType, M_PTR_TO_MIL_INT(ControlValue.c_str()));
   }

#endif /* M_MIL_USE_STRING */
// Automatic double casting
#define M3ddispSetView(Disp3dId, Mode, Param1, Param2, Param3, ControlFlag) \
        M3ddispSetViewDouble(Disp3dId, Mode, M_MILID_TO_DOUBLE(Param1), M_MILID_TO_DOUBLE(Param2), M_MILID_TO_DOUBLE(Param3), ControlFlag)
////////////////////////////////////////////////////////////////////////////////
//  MIL_UNIQUE_ID  support

#if M_MIL_USE_MIL_UNIQUE_ID
#if M_MIL_USE_SAFE_TYPE
template <> inline bool MilIsCorrectObjectType<&M3ddispFree>(MIL_INT64 ObjectType)
   {
   return ObjectType == M_3D_DISPLAY;;
   }
#endif
typedef MIL_UNIQUE_ID<&M3ddispFree> MIL_UNIQUE_3DDISP_ID;

#if M_MIL_USE_MOVE_SEMANTICS
//3DDISP
inline MIL_UNIQUE_3DDISP_ID M3ddispAlloc(MIL_ID SysId, MIL_INT DispNum, MIL_CONST_TEXT_PTR ControlFlag, MIL_INT64 InitFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DDISP_ID(M3ddispAlloc(SysId, DispNum, ControlFlag, InitFlag, M_NULL));
   }
template <MilFreeFuncType FreeFunc> inline void M3ddispFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;
#endif // M_MIL_USE_MOVE_SEMANTICS
#endif // M_MIL_USE_MIL_UNIQUE_ID
// End of MIL_UNIQUE_ID support

#endif // __MIL3DDISP_H__
