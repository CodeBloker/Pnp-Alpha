/////////////////////////////////////////////////////////////////
//
// Filename          :  MIL3DGEO.H
// Content           :  Define for the MIL 3D module
// Revision          :  10.40.0881
//
// Copyright © Matrox Electronic Systems Ltd., 1992-2021.
// All Rights Reserved
//
/////////////////////////////////////////////////////////////////


#ifndef __MIL3DGEO_H__
#define __MIL3DGEO_H__


////////////////////////////////////////////////////////////////////////////////////////////////
// M3DGEO
////////////////////////////////////////////////////////////////////////////////////////////////
/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
   {
#endif
#define M_GEOMETRY_TYPE                                     1321L 
#define M_GEOMETRY                                          1306L // Already defined
#define M_PLANE                                             1353L // Already defined in 3dmap
#define M_SPHERE                                            2931L
#define M_CYLINDER                                          3656
#define M_BOX                                               0x101L      // Already defined in    milblob.h
#define M_LINE                                         0x00000080L   // Already defined
#define M_UNCHANGED                                    0x40000005L // Already defined
//BoX
#define M_SIZE_X                                            1536L    //Already defined elsewhere
#define M_SIZE_Y                                            1537L    //Already defined elsewhere
#define M_SIZE_Z                                            1538L // also in mil.h
#define M_AXIS_ALIGNED                                 0x00040000 // Already defined in mil.h
#define M_BOX_ORIENTATION                                    3814
#define M_CORNER_X(N)                                     (1221L + (N)+ ((N) > 3 ? 2595 : 0))
#define M_CORNER_Y(N)                                     (1225L + (N)+ ((N) > 3 ? 2595 : 0))
#define M_CORNER_Z(N)                                     (3828+(N))
#define M_CORNER_X_ALL                                     3847                     
#define M_CORNER_Y_ALL                                     3848
#define M_CORNER_Z_ALL                                     3849
#define M_UNROTATED_MIN_X                                  3850
#define M_UNROTATED_MIN_Y                                  3851
#define M_UNROTATED_MIN_Z                                  3852
#define M_UNROTATED_MAX_X                                  3853
#define M_UNROTATED_MAX_Y                                  3854
#define M_UNROTATED_MAX_Z                                  3855
#define M_ORIENTATION_UNCHANGED                            0x8000L
//Plane type
#define M_COEFFICIENTS                                       3388
#define M_POINT_AND_NORMAL                                   3389
#define M_THREE_POINTS                                       3390
#define M_POINT_AND_TWO_VECTORS                              3391
//Sphere
#define M_CENTER_Z                                           3400
#define M_RADIUS                                       0x00000040L       // Already defined in MilMod.h
//Plane
#define M_COEFFICIENT_A                                     3401
#define M_COEFFICIENT_B                                     3402
#define M_COEFFICIENT_C                                     3403
#define M_COEFFICIENT_D                                     3404
#define M_NORMAL_X                                          3537
#define M_NORMAL_Y                                          3538
#define M_NORMAL_Z                                          3539
#define M_CLOSEST_TO_ORIGIN_X                               3540
#define M_CLOSEST_TO_ORIGIN_Y                               3541
#define M_CLOSEST_TO_ORIGIN_Z                               3542
//Cylinder
#define M_TWO_POINTS                                        3657
#define M_START_POINT_X                                     3658
#define M_START_POINT_Y                                     3659                               
#define M_START_POINT_Z                                     3660
#define M_END_POINT_X                                       3661
#define M_END_POINT_Y                                       3662
#define M_END_POINT_Z                                       3663
#define M_AXIS_X                                            3664
#define M_AXIS_Y                                            3665
#define M_AXIS_Z                                            3666
#define M_INFINITE                                            -1L // Also defined in Mil.h
#define M_POINT_AND_VECTOR                                  4670
//SetMatrix
#define M_TRANSFORMATION_MATRIX                               72L  // Already defined in milreg.h
#define M_TRANSFORM_TYPES_SHIFT                   8L  // =utilities=   (also defined in milcal.h)
#define M_ASSIGN                                (1 << M_TRANSFORM_TYPES_SHIFT)      /* (also defined in milcal.h) */
#define M_COMPOSE_WITH_CURRENT                  (2 << M_TRANSFORM_TYPES_SHIFT)      /* (also defined in milcal.h) */


#define M_TRANSFORMATION_TYPE                                      3L    // Already defined in Milreg.h
#define M_INVERSE                                             0x00100
#define M_IDENTITY                                           6L // already defined in milcal.h
#define M_TRANSLATION                                        1L // already defined in milcal.h 
#define M_ROTATION                                           3410
#define M_RIGID                                              3411 
#define M_SCALE_UNIFORM                                      3413   
#define M_SIMILARITY                                         3415
#define M_AFFINE                                             3416
#define M_PROJECTION                                         3417
#define M_COMPOSE_TWO_MATRICES                               3766
#define M_ROTATION_AXIS_ANGLE                                  2L // already defined in milcal.h
#define M_ROTATION_QUATERNION                                  3L // already defined in milcal.h
#define M_ROTATION_X                                           7L // already defined in milcal.h
#define M_ROTATION_Y                                           8L // already defined in milcal.h
#define M_ROTATION_Z                                           9L // already defined in milcal.h
#define M_ROTATION_YXZ                                         4L // already defined in milcal.h
#define M_ROTATION_XYZ                                        10L // already defined in milcal.h
#define M_ROTATION_XZY                                        11L // already defined in milcal.h
#define M_ROTATION_YZX                                        12L // already defined in milcal.h
#define M_ROTATION_ZXY                                        13L // already defined in milcal.h
#define M_ROTATION_ZYX                                        14L // already defined in milcal.h
#define M_ROTATION_AXIS_X                                     17L // already defined in milcal.h
#define M_ROTATION_AXIS_Y                                     18L // already defined in milcal.h
#define M_ROTATION_AXIS_Z                                     19L // already defined in milcal.h
#define M_FIXTURE_TO_PLANE                                    20L // already defined in milcal.h
#define M_FIXTURE_TO_GEOMETRY                                 21L // already defined in milcal.h
//MatrixDefine
#define M_XY_AXES                                           3926L
#define M_XZ_AXES                                           3927L
#define M_YX_AXES                                           3928L
#define M_YZ_AXES                                           3929L
#define M_ZX_AXES                                           3930L
#define M_ZY_AXES                                           3931L
#define M_FORWARD_TRANSFORMATION                      0x00001000L
#define M_BACKWARD_TRANSFORMATION                     0x00002000L
//Draw3d
#define M_ROOT_NODE                                            0
//Copy
#define M_ROTATION_AND_SCALE                                 3993

   // CAPI function prototypes
   MIL_ID  MFTYPE M3dgeoAlloc(MIL_ID     SysId,
                              MIL_INT64  ObjectType,
                              MIL_INT64  ControlFlag,
                              MIL_ID*    GeometryOrMatrix3dgeoIdPtr);

   MIL_DOUBLE MFTYPE M3dgeoInquire(MIL_ID     GeometryOrMatrix3dgeoId,
                                   MIL_INT64  InquireType,
                                   void*      UserVarPtr);

   void MFTYPE M3dgeoFree(MIL_ID GeometryOrMatrix3dgeoId);

   void MFTYPE M3dgeoBox(MIL_ID     Geometry3dgeoId,
                         MIL_INT64  CreationMode,
                         MIL_DOUBLE XPos1,
                         MIL_DOUBLE YPos1,
                         MIL_DOUBLE ZPos1,
                         MIL_DOUBLE XPos2OrLength,
                         MIL_DOUBLE YPos2OrLength,
                         MIL_DOUBLE ZPos2OrLength,
                         MIL_INT64  ControlFlag);

   void MFTYPE M3dgeoSphere(MIL_ID     Geometry3dgeoId,
                            MIL_DOUBLE CenterX,
                            MIL_DOUBLE CenterY,
                            MIL_DOUBLE CenterZ,
                            MIL_DOUBLE Radius,
                            MIL_INT64  ControlFlag);

   void MFTYPE M3dgeoPlane(MIL_ID     Geometry3dgeoId,
                           MIL_INT64  CreationMode,
                           MIL_DOUBLE X1,
                           MIL_DOUBLE Y1,
                           MIL_DOUBLE Z1,
                           MIL_DOUBLE X2OrD,
                           MIL_DOUBLE Y2,
                           MIL_DOUBLE Z2,
                           MIL_DOUBLE X3,
                           MIL_DOUBLE Y3,
                           MIL_DOUBLE Z3,
                           MIL_INT64  ControlFlag);

   void MFTYPE M3dgeoCopy(MIL_ID     SrcMilObjectId,
                          MIL_ID     DstMilObjectId,
                          MIL_INT64  CopyType,
                          MIL_INT64  ControlFlag);

   void MFTYPE M3dgeoMatrixSetTransformDouble(MIL_ID     Matrix3dgeoId,
                                              MIL_INT64  TransformType,
                                              MIL_DOUBLE Param1,
                                              MIL_DOUBLE Param2,
                                              MIL_DOUBLE Param3,
                                              MIL_DOUBLE Param4,
                                              MIL_INT64  ControlFlag);

   void MFTYPE M3dgeoMatrixPutDouble(MIL_ID            Matrix3dgeoId,
                                     MIL_INT64         PutType,
                                     const MIL_DOUBLE* UserArrayPtr);
   void MFTYPE M3dgeoMatrixPutFloat(MIL_ID           Matrix3dgeoId,
                                    MIL_INT64        PutType,
                                    const MIL_FLOAT* UserArrayPtr);

   void MFTYPE M3dgeoMatrixGetDouble(MIL_ID      Matrix3dgeoId,
                                     MIL_INT64   GetType,
                                     MIL_DOUBLE* UserArrayPtr);
   void MFTYPE M3dgeoMatrixGetFloat(MIL_ID      Matrix3dgeoId,
                                    MIL_INT64   GetType,
                                    MIL_FLOAT*  UserArrayPtr);

   void  MFTYPE M3dgeoMatrixGetTransform(MIL_ID     Matrix3dgeoId,
                                         MIL_INT64  InquireType,
                                         MIL_DOUBLE *Param1Ptr,
                                         MIL_DOUBLE *Param2Ptr,
                                         MIL_DOUBLE *Param3Ptr,
                                         MIL_DOUBLE *Param4Ptr,
                                         MIL_INT64  ControlFlag);

   void MFTYPE M3dgeoCylinder(MIL_ID     Geometry3dgeoId,
                              MIL_INT64  CreationMode,
                              MIL_DOUBLE XPos1,
                              MIL_DOUBLE YPos1,
                              MIL_DOUBLE ZPos1,
                              MIL_DOUBLE XPos2OrVector,
                              MIL_DOUBLE YPos2OrVector,
                              MIL_DOUBLE ZPos2OrVector,
                              MIL_DOUBLE Radius,
                              MIL_DOUBLE Length,
                              MIL_INT64  ControlFlag);

   MIL_INT64 MFTYPE M3dgeoDraw3d(MIL_ID     OperationDraw3dContext3dgeoId,
                                 MIL_ID     SrcGeometry3dgeoId,
                                 MIL_ID     DstList3dgraId,
                                 MIL_INT64  DstParentLabel,
                                 MIL_INT64  ControlFlag);


   void MFTYPE M3dgeoLine(MIL_ID     Geometry3dgeoId,
                          MIL_INT64  CreationMode,
                          MIL_DOUBLE XPos1,
                          MIL_DOUBLE YPos1,
                          MIL_DOUBLE ZPos1,
                          MIL_DOUBLE XPos2OrVector,
                          MIL_DOUBLE YPos2OrVector,
                          MIL_DOUBLE ZPos2OrVector,
                          MIL_DOUBLE Length,
                          MIL_INT64  ControlFlag);

   void MFTYPE M3dgeoMatrixSetWithAxes(MIL_ID     Matrix3dgeoId,
                                       MIL_INT64  Mode,
                                       MIL_DOUBLE OriginX,
                                       MIL_DOUBLE OriginY,
                                       MIL_DOUBLE OriginZ,
                                       MIL_DOUBLE Axis1VectorX,
                                       MIL_DOUBLE Axis1VectorY,
                                       MIL_DOUBLE Axis1VectorZ,
                                       MIL_DOUBLE Axis2VectorX,
                                       MIL_DOUBLE Axis2VectorY,
                                       MIL_DOUBLE Axis2VectorZ,
                                       MIL_INT64  ControlFlag);

   //M3dgeo Control  



#if M_MIL_USE_UNICODE
   void MFTYPE M3dgeoSaveA(MIL_CONST_TEXTA_PTR FileName,
                           MIL_ID              GeometryOrMatrix3dgeoId,
                           MIL_INT64           ControlFlag);

   MIL_ID MFTYPE M3dgeoRestoreA(MIL_CONST_TEXTA_PTR FileName,
                                MIL_ID              SysId,
                                MIL_INT64           ControlFlag,
                                MIL_ID*             GeometryOrMatrix3dgeoIdPtr);

   void MFTYPE M3dgeoStreamA(MIL_TEXTA_PTR MemPtrOrFileName,
                             MIL_ID        SysId,
                             MIL_INT64     Operation,
                             MIL_INT64     StreamType,
                             MIL_DOUBLE    Version,
                             MIL_INT64     ControlFlag,
                             MIL_ID*       GeometryOrMatrix3dgeoIdPtr,
                             MIL_INT*      SizeByteVarPtr);

   void MFTYPE M3dgeoSaveW(MIL_CONST_TEXTW_PTR FileName,
                           MIL_ID              GeometryOrMatrix3dgeoId,
                           MIL_INT64           ControlFlag);

   MIL_ID MFTYPE M3dgeoRestoreW(MIL_CONST_TEXTW_PTR FileName,
                                MIL_ID              SysId,
                                MIL_INT64           ControlFlag,
                                MIL_ID*             GeometryOrMatrix3dgeoIdPtr);

   void MFTYPE M3dgeoStreamW(MIL_TEXTW_PTR MemPtrOrFileName,
                             MIL_ID        SysId,
                             MIL_INT64     Operation,
                             MIL_INT64     StreamType,
                             MIL_DOUBLE    Version,
                             MIL_INT64     ControlFlag,
                             MIL_ID*       GeometryOrMatrix3dgeoIdPtr,
                             MIL_INT*      SizeByteVarPtr);



#if M_MIL_UNICODE_API
#define M3dgeoSave               M3dgeoSaveW
#define M3dgeoRestore            M3dgeoRestoreW
#define M3dgeoStream             M3dgeoStreamW
//#define M3dgeoImport             M3dgeoImportW
#else
#define M3dgeoSave               M3dgeoSaveA
#define M3dgeoRestore            M3dgeoRestoreA
#define M3dgeoStream             M3dgeoStreamA
//#define M3dgeoImport             M3dgeoImportA
#endif

#else

   void MFTYPE   M3dgeoSave(MIL_CONST_TEXT_PTR FileName,
                            MIL_ID             GeometryOrMatrix3dgeoId,
                            MIL_INT64          ControlFlag);

   MIL_ID MFTYPE   M3dgeoRestore(MIL_CONST_TEXT_PTR FileName,
                                 MIL_ID             SysId,
                                 MIL_INT64          ControlFlag,
                                 MIL_ID*            GeometryOrMatrix3dgeoIdPtr);

   void MFTYPE   M3dgeoStream(MIL_TEXT_PTR MemPtrOrFileName,
                              MIL_ID       SysId,
                              MIL_INT64    Operation,
                              MIL_INT64    StreamType,
                              MIL_DOUBLE   Version,
                              MIL_INT64    ControlFlag,
                              MIL_ID*      GeometryOrMatrix3dgeoIdPtr,
                              MIL_INT*     SizeByteVarPtr);

#endif  // M_MIL_USE_UNICODE

#ifdef __cplusplus

 inline bool In3dgeoInquireDoubleRange( MIL_INT64 InquireType)
      {
      if(M_NB_ELEMENTS_BIT_SET(InquireType))
         {
         return false;
         }

      switch(M_STRIP_INQ_COMBOFLAGS(InquireType))
         {
         //case M_ALLOCATION_FAILURE_REAL_TEST_FLAG:
         case M_CENTER_X:
         case M_CENTER_Y:
         case M_CENTER_Z:
         case M_RADIUS:
         case M_UNROTATED_MIN_X:
         case M_UNROTATED_MIN_Y:
         case M_UNROTATED_MIN_Z:
         case M_UNROTATED_MAX_X:
         case M_UNROTATED_MAX_Y:
         case M_UNROTATED_MAX_Z:
         case M_SIZE_X:
         case M_SIZE_Y:
         case M_SIZE_Z:
         case M_COEFFICIENT_A:
         case M_COEFFICIENT_B:
         case M_COEFFICIENT_C:
         case M_COEFFICIENT_D:
         case M_NORMAL_X:
         case M_NORMAL_Y:
         case M_NORMAL_Z:
         case M_CLOSEST_TO_ORIGIN_X:
         case M_CLOSEST_TO_ORIGIN_Y:
         case M_CLOSEST_TO_ORIGIN_Z:
         case M_START_POINT_X:
         case M_START_POINT_Y:
         case M_START_POINT_Z:
         case M_END_POINT_X:
         case M_END_POINT_Y:
         case M_END_POINT_Z:
         case M_AXIS_X:
         case M_AXIS_Y:
         case M_AXIS_Z:
         case M_LENGTH:
         case M_CORNER_X_ALL:
         case M_CORNER_Y_ALL:
         case M_CORNER_Z_ALL:
         case M_CORNER_X(0):
         case M_CORNER_X(1):
         case M_CORNER_X(2):
         case M_CORNER_X(3):
         case M_CORNER_X(4):
         case M_CORNER_X(5):
         case M_CORNER_X(6):
         case M_CORNER_X(7):
         case M_CORNER_Y(0):
         case M_CORNER_Y(1):
         case M_CORNER_Y(2):
         case M_CORNER_Y(3):
         case M_CORNER_Y(4):
         case M_CORNER_Y(5):
         case M_CORNER_Y(6):
         case M_CORNER_Y(7):
         case M_CORNER_Z(0):
         case M_CORNER_Z(1):
         case M_CORNER_Z(2):
         case M_CORNER_Z(3):
         case M_CORNER_Z(4):
         case M_CORNER_Z(5):
         case M_CORNER_Z(6):
         case M_CORNER_Z(7):
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

   inline bool In3dgeoInquireInt64Range( MIL_INT64 )
      {
      return false;
      }
   inline bool M3dgeoInquireMustHaveUserPtr( MIL_INT64 InquireType)
      {
      const MIL_INT64 ForcedDataType = MinquireOverrides(M_STRIP_HLVLDATATYPE(InquireType), M_TYPE_MIL_INT);
      if(ForcedDataType != 0)
         {
         return false;// ForcedDataType == M_TYPE_MIL_INT64;
         }

      return In3dgeoInquireInt64Range(InquireType);
      }
#endif // __cplusplus

   /* C++ directive if needed */
#ifdef __cplusplus
   }
#endif
#ifdef __cplusplus
   inline void MFTYPE M3dgeoStreamCpp(MilStreamParam MemPtrOrFileName,
                                      MIL_ID         SysId,
                                      MIL_INT64      Operation,
                                      MIL_INT64      StreamType,
                                      MIL_DOUBLE     Version,
                                      MIL_INT64      ControlFlag,
                                      MIL_ID*        GeometryOrMatrix3dgeoIdPtr,
                                      MIL_INT*       SizeByteVarPtr)
      {
      M3dgeoStream(MemPtrOrFileName.m_Param, SysId, Operation, StreamType, Version, ControlFlag, GeometryOrMatrix3dgeoIdPtr, SizeByteVarPtr);
      }

#undef  M3dgeoStream
#define M3dgeoStream M3dgeoStreamCpp

#endif // __cplusplus
#ifdef __cplusplus
   inline void M3dgeoMatrixGet(MIL_ID      Matrix3dgeoId,
                               MIL_INT64   GetType,
                               MIL_DOUBLE* UserArrayPtr)
      {
      return M3dgeoMatrixGetDouble(Matrix3dgeoId, GetType, UserArrayPtr);
      }
   inline void M3dgeoMatrixGet(MIL_ID      Matrix3dgeoId,
                               MIL_INT64   GetType,
                               MIL_FLOAT*  UserArrayPtr)
      {
      return M3dgeoMatrixGetFloat(Matrix3dgeoId, GetType, UserArrayPtr);
      }
   inline void M3dgeoMatrixPut(MIL_ID            Matrix3dgeoId,
                               MIL_INT64         PutType,
                               const MIL_DOUBLE* UserArrayPtr)
      {
      return M3dgeoMatrixPutDouble(Matrix3dgeoId, PutType, UserArrayPtr);
      }
   inline void M3dgeoMatrixPut(MIL_ID            Matrix3dgeoId,
                               MIL_INT64         PutType,
                               const MIL_FLOAT*  UserArrayPtr)
      {
      return M3dgeoMatrixPutFloat(Matrix3dgeoId, PutType, UserArrayPtr);
      }

#else
#define M3dgeoMatrixGet M3dgeoMatrixGetDouble
#define M3dgeoMatrixPut M3dgeoMatrixPutDouble
#endif

#ifdef __cplusplus
   inline MIL_INT64 M3dgeoInquireDataType(MIL_INT64 InquireType)
      {
      const MIL_INT64 ForcedDataType = MinquireOverrides(InquireType, M_TYPE_MIL_INT);
      if(ForcedDataType != 0)
         return ForcedDataType;

      if(In3dgeoInquireDoubleRange(InquireType))
         return M_TYPE_DOUBLE;

      if(In3dgeoInquireInt64Range(InquireType))
         return M_TYPE_MIL_INT64;

      return M_TYPE_MIL_INT;
      }
#if M_MIL_USE_SAFE_TYPE
   // ----------------------------------------------------------
// ----------------------------------------------------------
// M3dgeoInquire
   inline MIL_DOUBLE MFTYPE M3dgeoInquireSafeType(MIL_ID GeometryOrMatrix3dgeoId, MIL_INT64  InquireType, int UserVarPtr)
      {
      bool MustHaveUserPointer = M3dgeoInquireMustHaveUserPtr(InquireType);

      if(UserVarPtr)
         SafeTypeError(MIL_TEXT("M3dgeoInquire"));

      if(!UserVarPtr && MustHaveUserPointer)
         SafeTypeError(MIL_TEXT("M3dgeoInquire"), MIL_TEXT("The specified InquireType requires a non-null output pointer."));

      return M3dgeoInquire(GeometryOrMatrix3dgeoId, InquireType, NULL);
      }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
   inline MIL_DOUBLE MFTYPE M3dgeoInquireSafeType(MIL_ID GeometryOrMatrix3dgeoId, MIL_INT64  InquireType, std::nullptr_t)
      {
      bool MustHaveUserPointer = M3dgeoInquireMustHaveUserPtr(InquireType);

      if(MustHaveUserPointer)
         SafeTypeError(MIL_TEXT("M3dgeoInquire"),MIL_TEXT("The specified InquireType requires a non-null output pointer."));

      return M3dgeoInquire(GeometryOrMatrix3dgeoId, InquireType, NULL);
      }
#endif

   inline MIL_DOUBLE MFTYPE M3dgeoInquireSafeTypeExecute(MIL_ID GeometryOrMatrix3dgeoId, MIL_INT64  InquireType, void  *UserVarPtr, MIL_INT64  GivenType)
      {
      MIL_INT64  RequiredType = M3dgeoInquireDataType(InquireType);
      ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

      if(RequiredType != GivenType)
         SafeTypeError(MIL_TEXT("M3dgeoInquire"));

      return M3dgeoInquire(GeometryOrMatrix3dgeoId, InquireType, UserVarPtr);
      }

   inline MIL_DOUBLE MFTYPE M3dgeoInquireUnsafe(MIL_ID GeometryOrMatrix3dgeoId, MIL_INT64  InquireType, void        *UserVarPtr) { return M3dgeoInquire(GeometryOrMatrix3dgeoId, InquireType, UserVarPtr); }
   inline MIL_DOUBLE MFTYPE M3dgeoInquireSafeType(MIL_ID GeometryOrMatrix3dgeoId, MIL_INT64  InquireType, MIL_INT8*   UserVarPtr) { return M3dgeoInquireSafeTypeExecute(GeometryOrMatrix3dgeoId, InquireType, UserVarPtr, M_TYPE_CHAR); }
   inline MIL_DOUBLE MFTYPE M3dgeoInquireSafeType(MIL_ID GeometryOrMatrix3dgeoId, MIL_INT64  InquireType, MIL_INT16*  UserVarPtr) { return M3dgeoInquireSafeTypeExecute(GeometryOrMatrix3dgeoId, InquireType, UserVarPtr, M_TYPE_SHORT); }
   inline MIL_DOUBLE MFTYPE M3dgeoInquireSafeType(MIL_ID GeometryOrMatrix3dgeoId, MIL_INT64  InquireType, MIL_INT32   *UserVarPtr) { return M3dgeoInquireSafeTypeExecute(GeometryOrMatrix3dgeoId, InquireType, UserVarPtr, M_TYPE_MIL_INT32); }
   inline MIL_DOUBLE MFTYPE M3dgeoInquireSafeType(MIL_ID GeometryOrMatrix3dgeoId, MIL_INT64  InquireType, MIL_INT64   *UserVarPtr) { return M3dgeoInquireSafeTypeExecute(GeometryOrMatrix3dgeoId, InquireType, UserVarPtr, M_TYPE_MIL_INT64); }
   inline MIL_DOUBLE MFTYPE M3dgeoInquireSafeType(MIL_ID GeometryOrMatrix3dgeoId, MIL_INT64  InquireType, MIL_FLOAT   *UserVarPtr) { return M3dgeoInquireSafeTypeExecute(GeometryOrMatrix3dgeoId, InquireType, UserVarPtr, M_TYPE_MIL_FLOAT); }
   inline MIL_DOUBLE MFTYPE M3dgeoInquireSafeType(MIL_ID GeometryOrMatrix3dgeoId, MIL_INT64  InquireType, MIL_DOUBLE  *UserVarPtr) { return M3dgeoInquireSafeTypeExecute(GeometryOrMatrix3dgeoId, InquireType, UserVarPtr, M_TYPE_DOUBLE); }
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
   inline MIL_DOUBLE MFTYPE M3dgeoInquireSafeType(MIL_ID GeometryOrMatrix3dgeoId, MIL_INT64  InquireType, MIL_UINT8*   UserVarPtr) { return M3dgeoInquireSafeTypeExecute(GeometryOrMatrix3dgeoId, InquireType, UserVarPtr, M_TYPE_CHAR); }
   inline MIL_DOUBLE MFTYPE M3dgeoInquireSafeType(MIL_ID GeometryOrMatrix3dgeoId, MIL_INT64  InquireType, MIL_UINT16*  UserVarPtr) { return M3dgeoInquireSafeTypeExecute(GeometryOrMatrix3dgeoId, InquireType, UserVarPtr, M_TYPE_SHORT); }
   inline MIL_DOUBLE MFTYPE M3dgeoInquireSafeType(MIL_ID GeometryOrMatrix3dgeoId, MIL_INT64  InquireType, MIL_UINT32  *UserVarPtr) { return M3dgeoInquireSafeTypeExecute(GeometryOrMatrix3dgeoId, InquireType, UserVarPtr, M_TYPE_MIL_INT32); }
   inline MIL_DOUBLE MFTYPE M3dgeoInquireSafeType(MIL_ID GeometryOrMatrix3dgeoId, MIL_INT64  InquireType, MIL_UINT64  *UserVarPtr) { return M3dgeoInquireSafeTypeExecute(GeometryOrMatrix3dgeoId, InquireType, UserVarPtr, M_TYPE_MIL_INT64); }
#endif
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T                                                      
   inline MIL_DOUBLE MFTYPE M3dgeoInquireSafeType(MIL_ID GeometryOrMatrix3dgeoId, MIL_INT64  InquireType, wchar_t*    UserVarPtr) { return M3dgeoInquireSafeTypeExecute(GeometryOrMatrix3dgeoId, InquireType, UserVarPtr, M_TYPE_SHORT); }
#endif

#define M3dgeoInquire           M3dgeoInquireSafeType


#else // #if M_MIL_USE_SAFE_TYPE
#define M3dgeoInquireUnsafe     M3dgeoInquire

#endif // #if M_MIL_USE_SAFE_TYPE

#endif
#if M_MIL_USE_STRING
   inline void MFTYPE M3dgeoSave(const MIL_STRING& FileName, MIL_ID GeometryOrMatrix3dgeoId, MIL_INT64 ControlFlag)
      {
      return M3dgeoSave(FileName.c_str(), GeometryOrMatrix3dgeoId, ControlFlag);
      }

   inline MIL_ID MFTYPE M3dgeoRestore(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_ID* GeometryOrMatrix3dgeoIdPtr)
      {
      return M3dgeoRestore(FileName.c_str(), SysId, ControlFlag, GeometryOrMatrix3dgeoIdPtr);
      }
#endif /* M_MIL_USE_STRING */
   // ----------------------------------------------------------
// Overload for std::vector.
#if defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR
// ----------------------------------------------------------
// Overloads for std::vector in  M3dgeoInquire.
   template <typename UserType>
   inline MIL_DOUBLE MFTYPE M3dgeoInquire(MIL_ID GeometryOrMatrix3dgeoId, MIL_INT64  InquireType, std::vector<UserType> &UserVarPtr)
      {
      // If the given MIL data type is not the same as the SrcType, change it to the correct one
      // and give a warning.
      MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
      if(M_GET_HLVLDATATYPE(InquireType) != 0)
         {
         SafeTypeError(MIL_TEXT("M3dgeoInquire"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
         }
#endif

      InquireType = M_STRIP_HLVLDATATYPE(InquireType) + InternalTrueDataTypeForStdVector;

      MIL_INT InternalNumberOfElementsForStdVector = 0;
      M3dgeoInquire(GeometryOrMatrix3dgeoId, M_STRIP_HLVLDATATYPE(InquireType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

      UserVarPtr.resize(InternalNumberOfElementsForStdVector);

      if(InternalNumberOfElementsForStdVector > 0)
         {
         return M3dgeoInquire(GeometryOrMatrix3dgeoId, InquireType, &UserVarPtr[0]);
         }
      return 0;
      }
   // ----------------------------------------------------------
   // Overloads for std::vector in  M3dgeoMatrixPut.
   template <typename T>
   inline void MFTYPE  M3dgeoMatrixPut(MIL_ID                Matrix3dgeoId,
                                       MIL_INT64             PutType,
                                       const std::vector<T>& ArrayPtr)
      {
#if M_MIL_USE_SAFE_TYPE
      if(ArrayPtr.empty())
         {
         SafeTypeError(MIL_TEXT("M3dgeoMatrixPut"), MIL_TEXT("The input vector cannot be empty."));
         }

      if(ArrayPtr.size() != 16)
         {
         SafeTypeError(MIL_TEXT("M3dgeoMatrixPut"), MIL_TEXT("The size of the input vector must be 16."));
         }
#endif
      M3dgeoMatrixPut(Matrix3dgeoId,
                      PutType,
                      &ArrayPtr[0]);
      }
   // Overloads for std::vector in M3dgeoMatrixGet.
   template <typename T>
   inline void M3dgeoMatrixGet(MIL_ID          Matrix3dgeoId,
                               MIL_INT64       GetType,
                               std::vector<T>& ArrayPtr)
      {
      ArrayPtr.resize(16);//InternalNbElementRequired
      M3dgeoMatrixGet(Matrix3dgeoId,
                      GetType,
                      &ArrayPtr[0]);
      }
   // ----------------------------------------------------------
// Overloads for std::vector in M3dgeoStream.
   inline void MFTYPE M3dgeoStream(std::vector<MIL_UINT8> &MemPtrOrFileName,
                                   MIL_ID                 SysId,
                                   MIL_INT64              Operation,
                                   MIL_INT64              StreamType,
                                   MIL_DOUBLE             Version,
                                   MIL_INT64              ControlFlag,
                                   MIL_ID*                GeometryOrMatrix3dgeoIdPtr,
                                   MIL_INT*               SizeByteVarPtr)
      {
      MxxxStreamForStdVector(MemPtrOrFileName,
                             SysId,
                             Operation,
                             StreamType,
                             Version,
                             ControlFlag,
                             GeometryOrMatrix3dgeoIdPtr,
                             SizeByteVarPtr,
                             M3dgeoStream);
      }
#endif // defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR
 // Automatic double casting
#define M3dgeoMatrixSetTransform(Matrix3dgeoId, TransformType, Param1, Param2, Param3, Param4, ControlFlag) \
        M3dgeoMatrixSetTransformDouble(Matrix3dgeoId, TransformType, M_MILID_TO_DOUBLE(Param1), M_MILID_TO_DOUBLE(Param2), M_MILID_TO_DOUBLE(Param3), M_MILID_TO_DOUBLE(Param4), ControlFlag)
////////////////////////////////////////////////////////////////////////////////
// MIL_UNIQUE_ID support

#if M_MIL_USE_MIL_UNIQUE_ID

#if M_MIL_USE_SAFE_TYPE
   template <> inline bool MilIsCorrectObjectType<&M3dgeoFree>(MIL_INT64 ObjectType)
      {
      return (ObjectType == M_3DGEO_GEOMETRY || ObjectType == M_3DGEO_TRANSFORMATION_MATRIX);
      }
#endif

   typedef MIL_UNIQUE_ID<&M3dgeoFree > MIL_UNIQUE_3DGEO_ID;

#if M_MIL_USE_MOVE_SEMANTICS

   //3DGEO
   inline  MIL_UNIQUE_3DGEO_ID M3dgeoAlloc(MIL_ID SysId, MIL_INT64 ObjectType, MIL_INT64 InitFlag, MIL_UNIQUE_ID_TAG)
      {
      return MIL_UNIQUE_3DGEO_ID(M3dgeoAlloc(SysId, ObjectType, InitFlag, M_NULL));
      }
   inline MIL_UNIQUE_3DGEO_ID M3dgeoRestore(MIL_CONST_TEXT_PTR FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
      {
      return MIL_UNIQUE_3DGEO_ID(M3dgeoRestore(FileName, SysId, ControlFlag, M_NULL));
      }
#if M_MIL_USE_STRING
   inline MIL_UNIQUE_3DGEO_ID M3dgeoRestore(const MIL_STRING& FileName, MIL_ID SysId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
      {
      return MIL_UNIQUE_3DGEO_ID(M3dgeoRestore(FileName.c_str(), SysId, ControlFlag, M_NULL));
      }
#endif // M_MIL_USE_STRING
   template <MilFreeFuncType FreeFunc> inline void M3dgeoFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;

   inline void M3dgeoStream(MilStreamParam       MemPtrOrFileName,
                            MIL_ID               SysId,
                            MIL_INT64            Operation,
                            MIL_INT64            StreamType,
                            MIL_DOUBLE           Version,
                            MIL_INT64            ControlFlag,
                            MIL_UNIQUE_3DGEO_ID* Context3dgeoIdPtr,
                            MIL_INT*             SizeByteVarPtr)
      {
      MxxxStreamForMilUniqueId(MemPtrOrFileName, SysId, Operation, StreamType, Version, ControlFlag, Context3dgeoIdPtr, SizeByteVarPtr, M3dgeoStream);
      }
#endif // M_MIL_USE_MOVE_SEMANTICS
#endif // M_MIL_USE_MIL_UNIQUE_ID

// End of MIL_UNIQUE_ID support


////////////////////////////////////////////////////////////////////////////////

   /* C++ directive if needed */
#ifdef __cplusplus
extern "C"
   {
#endif
   // MbufConvert3d
#define M_COMPENSATE                   3713
#define M_REMOVE_NON_FINITE            0x00000001L


   void MFTYPE MbufConvert3d(MIL_ID    SrcContainerOrImageBufId,
                             MIL_ID    DstContainerOrImageBufId,
                             MIL_ID    ExternalYArrayBufId,
                             MIL_INT64 DstOptions,
                             MIL_INT64 ControlFlag);



   /* C++ directive if needed */
#ifdef __cplusplus
   }
#endif

////////////////////////////////////////////////////////////////////////////////
#endif // __MIL3D_H__
