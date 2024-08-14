/////////////////////////////////////////////////////////////////
//
// Filename          :  MIL3DGRA.H
// Content           :  Define for the MIL 3DGRA module
// Revision          :  10.40.0881
//
// Copyright © Matrox Electronic Systems Ltd., 1992-2021.
// All Rights Reserved
//
/////////////////////////////////////////////////////////////////


#ifndef __MIL3DGRA_H__
#define __MIL3DGRA_H__

#if !defined(__MIL3DGEO_H__)
#include <mildyn/mil3dgeo.h>
#endif

/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
   {
#endif
// Control values
#define M_ROOT_NODE                                                          0
#define M_NO_LABEL                                                  0x20000000L  // Also defined in milreg.h
#define M_LIST                                                      0x08000000L  /* already defined in mil.h */
#define M_DEFAULT_SETTINGS                                          0x04000000L

// M3dgraAlloc
// 1000-2000

#define M_GRAPHIC_TYPE_ARC                                               1505L   // already defined in mil.h
#define M_GRAPHIC_TYPE_DOTS                                              1507L   // already defined in mil.h
#define M_GRAPHIC_TYPE_LINE                                              1508L   // already defined in mil.h
#define M_GRAPHIC_TYPE_POLYGON                                           1510L   // already defined in mil.h
#define M_GRAPHIC_TYPE_TEXT                                              1513L   // already defined in mil.h
#define M_GRAPHIC_TYPE_AXIS                                              3881L
#define M_GRAPHIC_TYPE_BOX                                               3882L
#define M_GRAPHIC_TYPE_POINT_CLOUD                                       3883L
#define M_GRAPHIC_TYPE_CYLINDER                                          3884L
#define M_GRAPHIC_TYPE_GRID                                              3885L
#define M_GRAPHIC_TYPE_PLANE                                             3886L
#define M_GRAPHIC_TYPE_QUAD                                              3887L
#define M_GRAPHIC_TYPE_SPHERE                                            3888L
#define M_GRAPHIC_TYPE_NODE                                              3889L

// M3dgraCopy
#define M_CLIPPING_BOX                                                   3868L
#define M_GRAPHIC                                                        3879L
#define M_COLOR_LUT                                                      3945L
#define M_RECURSIVE                                                0x00040000 // already defined in milmod.h
#define M_CHILDREN_ONLY                                            0x00080000
#define M_BOUNDING_BOX                                             0x00000003L  // already defined
#define M_GEOMETRY                                                       1306L // Already defined

// Gralist controls
#define M_BOTH_CORNERS                                             0x00000004L  // Already defined in mil.h
#define M_CENTER_AND_DIMENSION                                     0x00000002L  // Already defined in 
#define M_POINT_AND_VECTOR                                               4670
#define M_VISIBLE                                                        1533L // Already defined in mil.h
#define M_LABEL_EXISTS                                                   4671
#define M_POSITION_X                                               0x00003400L // Already defined in milim.h
#define M_POSITION_Y                                               0x00004400L // Already defined in milim.h
#define M_POSITION_Z                                                     3960L

// Container
#define M_TRANSFORMATION_MATRIX                                            72L  // Already defined in milreg.h
#define M_BUFFER_LIMITS                                                  4672
#define M_DATA_EXTREMES_GLOBAL                                           4673
#define M_DATA_EXTREMES_PER_BAND                                         4674
#define M_USER_DEFINED                                                     21L // Already defined in alot of places
#define M_AUTO_COLOR                                               0x00100000L
#define M_CONTAINER_ID                                                   4675
#define M_GRAPHIC_RESOLUTION                                             4676

// Dots
#define M_PER_POINT                                                      3873L

// Axis
#define M_PER_AXIS                                                       3956L

//Plane
#define M_THREE_POINTS                                                   3390 // Already defined in mil3dgeo.h
#define M_COEFFICIENTS                                                   3388
#define M_POINT_AND_NORMAL                                               3389
#define M_POINT_AND_TWO_VECTORS                                          3391
// Text
#define M_GRAPHIC_TEXT                             (3869L | M_CLIENT_ENCODING)
#define M_FONT                                        (7L | M_CLIENT_ENCODING) // Already defined in mil.h
#define M_TEXT_ALIGN_HORIZONTAL                                            58L // Already defined in Mil.h
#define M_TEXT_ALIGN_VERTICAL                                              71L // Already defined in Mil.h
#define M_TEXT_BORDER                                                    1785L // Already defined in Mil.h
#define M_TEXT_DIRECTION                                           0x01000061L // Already defined in Mil.h
#define M_TEXT_SHADING                                                   4747L
#define M_BACKGROUND_MODE                                                  12L // Already defined in Mil.h
//Cylinder
#define M_TWO_POINTS                                                     3657
// Arc
#define M_CENTER_AND_TWO_POINTS                                          3875L  
#define M_CENTER_AND_TWO_VECTORS                                         3876L
#define M_NORMAL_AND_ANGLE                                               3877L

// Grid
#define M_SIZE_AND_SPACING                                               3932L  
#define M_TILES_AND_SPACING                                              3933L

////////////////////////////////////////////////////////////////////////////////
// M3dgraControl
////////////////////////////////////////////////////////////////////////////////
// MIL_INT64 CONTROLS
#define M_COLOR_COMPONENT                                                4678
#define M_APPEARANCE                                                     4679
#define M_COLOR_LIMITS                                                   4680
#define M_COLOR_LUT_SIZE                                                 4681
#define M_COLOR_LUT_SIZE_BAND                                            4682
#define M_COLOR_COMPONENT_BAND                                           4683
#define M_COLOR_USE_LUT                                                  4684  
#define M_CHILDREN                                                       4685    
#define M_NUMBER_OF_CHILDREN                                             4686   
#define M_PARENT                                                         4687   
#define M_CYLINDER_BASES                                                 4688   
#define M_COLOR_AXIS_X                                                   4689
#define M_COLOR_AXIS_Y                                                   4690
#define M_COLOR_AXIS_Z                                                   4691
#define M_SAME_AS_COLOR                                                  4692
#define M_COLOR_USE_TEXTURE                                              4693
#define M_COLOR_TEXTURE_SIZE_X                                           4694
#define M_COLOR_TEXTURE_SIZE_Y                                           4695
#define M_COLOR_TEXTURE_SIZE_BAND                                        4696
#define M_COLOR_TEXTURE                                                  4697
#define M_SHADING                                                        4698
#define M_FLAT                                                           4699
#define M_GOURAUD                                                        4700
#define M_PHONG                                                          4726
#define M_KEYING_COLOR                                                   4727
#define M_GRAPHIC_TYPE                                                   1518L // Already defined in mil.h
#define M_FILL_COLOR                                    (M_DISP_CONTROL_START+193L) // already defined in mildisplay.h

#define M_POINTS                                                   0x00000010L
#define M_WIREFRAME                                                0x00000020L
#define M_SOLID                                                    0x00000040L
#define M_SOLID_WITH_WIREFRAME                          (M_SOLID + M_WIREFRAME)

// MIL_DOUBLE CONTROLS
#define M_OPACITY                                                        4728
#define M_COLOR_LIMITS_MIN                                               4729
#define M_COLOR_LIMITS_MAX                                               4730
#define M_POINTS_X                                                       4733
#define M_POINTS_Y                                                       4734
#define M_POINTS_Z                                                       4735
#define M_SPACING_X                                                      4736
#define M_SPACING_Y                                                      4737
#define M_FONT_SIZE                                                0x01000060L  // already defined in Mil.h
#define M_THICKNESS                                                         3L  // also used in MgraLines
#define M_TRANSFORM_TYPES_SHIFT                                             8L  // =utilities=   (also defined in milcal.h)
#define M_RELATIVE_TO_ROOT                            (256 << M_TRANSFORM_TYPES_SHIFT)


////////////////////////////////////////////////////////////////////////////////

// M3dgra calls
   MIL_INT64 MFTYPE M3dgraAdd(MIL_ID    List3dgraId,
                              MIL_INT64 ParentLabel,
                              MIL_ID    ContainerOrImageBufId,
                              MIL_INT64 ControlFlag);

   MIL_ID    MFTYPE M3dgraAlloc(MIL_ID    SysId,
                                MIL_INT64 ControlFlag,
                                MIL_ID*   List3dgraIdPtr);

   void      MFTYPE M3dgraControlDouble(MIL_ID     List3dgraId,
                                        MIL_INT64  Label,
                                        MIL_INT64  ControlType,
                                        MIL_DOUBLE ControlValue);

   void      MFTYPE M3dgraControlInt64 (MIL_ID    List3dgraId,
                                        MIL_INT64 Label,
                                        MIL_INT64 ControlType,
                                        MIL_INT64 ControlValue);

   void      MFTYPE M3dgraFree(MIL_ID List3dgraId);

   MIL_INT64 MFTYPE M3dgraInquire(MIL_ID    List3dgraId,
                                  MIL_INT64 Label,
                                  MIL_INT64 InquireType,
                                  void*     UserVarPtr);

   void      MFTYPE M3dgraRemove(MIL_ID    List3dgraId,
                                 MIL_INT64 Label,
                                 MIL_INT64 ControlFlag);

   MIL_INT64 MFTYPE M3dgraBox(MIL_ID     List3dgraId,
                              MIL_INT64  ParentLabel,
                              MIL_INT64  CreationMode,
                              MIL_DOUBLE XPos1,
                              MIL_DOUBLE YPos1,
                              MIL_DOUBLE ZPos1,
                              MIL_DOUBLE XPos2OrLength,
                              MIL_DOUBLE YPos2OrLength,
                              MIL_DOUBLE ZPos2OrLength,
                              MIL_ID     Matrix3dgeoId,
                              MIL_INT64  ControlFlag);

   MIL_INT64 MFTYPE M3dgraSphere(MIL_ID     List3dgraId,
                                 MIL_INT64  ParentLabel,
                                 MIL_DOUBLE CenterX,
                                 MIL_DOUBLE CenterY,
                                 MIL_DOUBLE CenterZ,
                                 MIL_DOUBLE Radius,
                                 MIL_INT64  ControlFlag);

   MIL_INT64 MFTYPE M3dgraCylinder(MIL_ID     List3dgraId,
                                   MIL_INT64  ParentLabel,
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

   MIL_INT64 MFTYPE M3dgraGrid(MIL_ID     List3dgraId,
                               MIL_INT64  ParentLabel,
                               MIL_INT64  CreationMode,
                               MIL_ID     Matrix3dgeoId,
                               MIL_DOUBLE Param1,
                               MIL_DOUBLE Param2,
                               MIL_DOUBLE Param3,
                               MIL_DOUBLE Param4,
                               MIL_INT64  ControlFlag);

   MIL_INT64 MFTYPE M3dgraLine(MIL_ID     List3dgraId,
                               MIL_INT64  ParentLabel,
                               MIL_INT64  CreationMode,
                               MIL_INT64  Symbol,
                               MIL_DOUBLE PointX,
                               MIL_DOUBLE PointY,
                               MIL_DOUBLE PointZ,
                               MIL_DOUBLE PointOrVectorX,
                               MIL_DOUBLE PointOrVectorY,
                               MIL_DOUBLE PointOrVectorZ,
                               MIL_DOUBLE Length,
                               MIL_INT64  ControlFlag);
   
   MIL_INT64 MFTYPE M3dgraNode(MIL_ID     List3dgraId,
                               MIL_INT64  ParentLabel,
                               MIL_ID     Matrix3dgeoId,
                               MIL_INT64  ControlFlag);

   MIL_INT64 MFTYPE M3dgraPlane(MIL_ID     List3dgraId,
                                MIL_INT64  ParentLabel,
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
                                MIL_DOUBLE Size,
                                MIL_INT64  ControlFlag);

   MIL_INT64 MFTYPE M3dgraArc(MIL_ID     List3dgraId,
                              MIL_INT64  ParentLabel,
                              MIL_INT64  CreationMode,
                              MIL_INT64  Symbol,
                              MIL_DOUBLE X1,
                              MIL_DOUBLE Y1,
                              MIL_DOUBLE Z1,
                              MIL_DOUBLE X2,
                              MIL_DOUBLE Y2,
                              MIL_DOUBLE Z2,
                              MIL_DOUBLE X3,
                              MIL_DOUBLE Y3,
                              MIL_DOUBLE Z3,
                              MIL_DOUBLE Angle,
                              MIL_INT64  ControlFlag);

   MIL_INT64 MFTYPE M3dgraDotsDouble(MIL_ID            List3dgraId,
                                     MIL_INT64         ParentLabel,
                                     MIL_INT           NumPoints,
                                     const MIL_DOUBLE* CoordXArrayPtr,
                                     const MIL_DOUBLE* CoordYArrayPtr,
                                     const MIL_DOUBLE* CoordZArrayPtr,
                                     const MIL_UINT8*  PointsRArrayPtr,
                                     const MIL_UINT8*  PointsGArrayPtr,
                                     const MIL_UINT8*  PointsBArrayPtr,
                                     MIL_INT64         ControlFlag);

   MIL_INT64 MFTYPE M3dgraDotsFloat(MIL_ID           List3dgraId,
                                    MIL_INT64        ParentLabel,
                                    MIL_INT          NumPoints,
                                    const MIL_FLOAT* CoordXArrayPtr,
                                    const MIL_FLOAT* CoordYArrayPtr,
                                    const MIL_FLOAT* CoordZArrayPtr,
                                    const MIL_UINT8* PointsRArrayPtr,
                                    const MIL_UINT8* PointsGArrayPtr,
                                    const MIL_UINT8* PointsBArrayPtr,
                                    MIL_INT64        ControlFlag);

   MIL_INT64 MFTYPE M3dgraCopy(MIL_ID     SrcMilObjectId,
                               MIL_INT64  SrcLabel,
                               MIL_ID     DstMilObjectId,
                               MIL_INT64  DstLabel,
                               MIL_INT64  CopyType,
                               MIL_INT64  ControlFlag);

   MIL_INT64 MFTYPE M3dgraPolygonDouble(MIL_ID            List3dgraId,
                                        MIL_INT64         ParentLabel,
                                        MIL_INT64         CreationMode,
                                        MIL_INT           NumPoints,
                                        const MIL_DOUBLE* CoordXArrayPtr,
                                        const MIL_DOUBLE* CoordYArrayPtr,
                                        const MIL_DOUBLE* CoordZArrayPtr,
                                        const MIL_DOUBLE* TextureXArrayPtr,
                                        const MIL_DOUBLE* TextureYArrayPtr,
                                        MIL_ID            TextureBufId,
                                        MIL_INT64         ControlFlag);

   MIL_INT64 MFTYPE M3dgraPolygonFloat(MIL_ID           List3dgraId,
                                       MIL_INT64        ParentLabel,
                                       MIL_INT64        CreationMode,
                                       MIL_INT          NumPoints,
                                       const MIL_FLOAT* CoordXArrayPtr,
                                       const MIL_FLOAT* CoordYArrayPtr,
                                       const MIL_FLOAT* CoordZArrayPtr,
                                       const MIL_FLOAT* TextureXArrayPtr,
                                       const MIL_FLOAT* TextureYArrayPtr,
                                       MIL_ID           TextureBufId,
                                       MIL_INT64        ControlFlag);

// For CAPI calls with strings
#if M_MIL_USE_UNICODE
   MIL_INT64 MFTYPE M3dgraTextA(MIL_ID List3dgraId, MIL_INT64 ParentLabel, MIL_CONST_TEXTA_PTR Text, MIL_ID Matrix3dgeoId, MIL_INT64 Options, MIL_INT64 ControlFlag);
   MIL_INT64 MFTYPE M3dgraTextW(MIL_ID List3dgraId, MIL_INT64 ParentLabel, MIL_CONST_TEXTW_PTR Text, MIL_ID Matrix3dgeoId, MIL_INT64 Options, MIL_INT64 ControlFlag);
   MIL_INT64 MFTYPE M3dgraAxisA(MIL_ID List3dgraId, MIL_INT64 ParentLabel, MIL_ID Matrix3dgeoId, MIL_DOUBLE AxisLength, MIL_CONST_TEXTA_PTR Name, MIL_INT64 Options, MIL_INT64 ControlFlag);
   MIL_INT64 MFTYPE M3dgraAxisW(MIL_ID List3dgraId, MIL_INT64 ParentLabel, MIL_ID Matrix3dgeoId, MIL_DOUBLE AxisLength, MIL_CONST_TEXTW_PTR Name, MIL_INT64 Options, MIL_INT64 ControlFlag);
     

// create default calls
#if M_MIL_UNICODE_API
#define M3dgraText   M3dgraTextW
#define M3dgraAxis   M3dgraAxisW

#else
#define M3dgraText   M3dgraTextA
#define M3dgraAxis   M3dgraAxisA
#endif

#else
   MIL_INT64 MFTYPE M3dgraText(MIL_ID List3dgraId, MIL_INT64 ParentLabel, MIL_CONST_TEXT_PTR Text, MIL_ID Matrix3dgeoId, MIL_INT64 Options, MIL_INT64 ControlFlag);
   MIL_INT64 MFTYPE M3dgraAxis(MIL_ID List3dgraId, MIL_INT64 ParentLabel, MIL_ID Matrix3dgeoId, MIL_DOUBLE AxisLength, MIL_CONST_TEXT_PTR Name, MIL_INT64 Options, MIL_INT64 ControlFlag);
 #endif

#ifdef __cplusplus

   inline bool In3dgraInquireDoubleRange(MIL_INT64 InquireType)
      {
      InquireType &= ~(M_RELATIVE_TO_ROOT | M_RECURSIVE);  // Remove custom combo flags

      if(M_NB_ELEMENTS_BIT_SET(InquireType))
         return false;

      if(In3dgeoInquireDoubleRange(InquireType))
         return true;

      switch(M_STRIP_INQ_COMBOFLAGS(InquireType))
         {
         case M_ANGLE:
         case M_OPACITY:
         case M_COLOR_LIMITS_MIN:
         case M_COLOR_LIMITS_MAX:
         case M_POINTS_X:
         case M_POINTS_Y:
         case M_POINTS_Z:
         case M_SPACING_X:
         case M_SPACING_Y:
         case M_FONT_SIZE:
         case M_THICKNESS:
         case M_POSITION_X:
         case M_POSITION_Y:
         case M_POSITION_Z:
            return true;

         default:
            break;
         }

      return false;
      }

   inline bool In3dgraInquireInt64Range(MIL_INT64 InquireType)
      {
      InquireType &= ~(M_RELATIVE_TO_ROOT | M_RECURSIVE);  // Remove custom combo flags

      if(M_NB_ELEMENTS_BIT_SET(InquireType))
         return false;

      switch(M_STRIP_INQ_COMBOFLAGS(InquireType))
         {
         case M_COLOR_COMPONENT:
         case M_COLOR:
         case M_BACKGROUND_COLOR:
         case M_KEYING_COLOR:
         case M_COLOR_AXIS_X:
         case M_COLOR_AXIS_Y:
         case M_COLOR_AXIS_Z:
         case M_FILL_COLOR:
         case M_PARENT:
         case M_CHILDREN:
            return true;

         default:
            break;
         }

      return false;
      }

   inline bool In3dgraInquireStringRange(MIL_INT64 InquireType)
      {
      if(M_NB_ELEMENTS_BIT_SET(InquireType))
         return false;

      switch(M_STRIP_CLIENT_TEXT_ENCODING(M_STRIP_INQ_COMBOFLAGS(InquireType)))
         {
         case M_STRIP_CLIENT_TEXT_ENCODING(M_GRAPHIC_TEXT):
         case M_STRIP_CLIENT_TEXT_ENCODING(M_FONT):
            return true;

         default:
            break;
         }

      return false;
      }
   inline bool M3dgraInquireMustHaveUserPtr(MIL_INT64 InquireType)
      {
      const MIL_INT64 ForcedDataType = MinquireOverrides(M_STRIP_HLVLDATATYPE(InquireType), M_TYPE_MIL_INT);
      if(ForcedDataType != 0)
         {
         return false;
         }
      return In3dgraInquireDoubleRange(InquireType) || In3dgraInquireStringRange(InquireType);
      }

#endif // __cplusplus

   /* C++ directive if needed */
#ifdef __cplusplus
   }
#endif




// M3dgradots/polygon c++ overloads
#ifdef __cplusplus
   inline MIL_INT64 M3dgraDots(MIL_ID List3dgraId,
                               MIL_INT64 ParentLabel,
                               MIL_INT NumPoints,
                               const MIL_DOUBLE* CoordXArrayPtr,
                               const MIL_DOUBLE* CoordYArrayPtr,
                               const MIL_DOUBLE* CoordZArrayPtr,
                               const MIL_UINT8* PointsRArrayPtr,
                               const MIL_UINT8* PointsGArrayPtr,
                               const MIL_UINT8* PointsBArrayPtr,
                               MIL_INT64 ControlFlag)
      {
      return M3dgraDotsDouble(List3dgraId, ParentLabel, NumPoints, CoordXArrayPtr, CoordYArrayPtr, CoordZArrayPtr, PointsRArrayPtr, PointsGArrayPtr, PointsBArrayPtr, ControlFlag);
      }

   inline MIL_INT64 M3dgraDots(MIL_ID List3dgraId,
                               MIL_INT64 ParentLabel,
                               MIL_INT NumPoints,
                               const MIL_FLOAT* CoordXArrayPtr,
                               const MIL_FLOAT* CoordYArrayPtr,
                               const MIL_FLOAT* CoordZArrayPtr,
                               const MIL_UINT8* PointsRArrayPtr,
                               const MIL_UINT8* PointsGArrayPtr,
                               const MIL_UINT8* PointsBArrayPtr,
                               MIL_INT64 ControlFlag)
      {
      return M3dgraDotsFloat(List3dgraId, ParentLabel, NumPoints, CoordXArrayPtr, CoordYArrayPtr, CoordZArrayPtr, PointsRArrayPtr, PointsGArrayPtr, PointsBArrayPtr, ControlFlag);
      }

   inline MIL_INT64 M3dgraPolygon(MIL_ID List3dgraId,
                                  MIL_INT64 ParentLabel,
                                  MIL_INT64 CreationMode,
                                  MIL_INT    NumPoints,
                                  const MIL_DOUBLE* CoordXArrayPtr,
                                  const MIL_DOUBLE* CoordYArrayPtr,
                                  const MIL_DOUBLE* CoordZArrayPtr,
                                  const MIL_DOUBLE* TextureXArrayPtr,
                                  const MIL_DOUBLE* TextureYArrayPtr,
                                  MIL_ID TextureBufId,
                                  MIL_INT64 ControlFlag)
      {
      return M3dgraPolygonDouble(List3dgraId, ParentLabel, CreationMode, NumPoints, CoordXArrayPtr, CoordYArrayPtr, CoordZArrayPtr, TextureXArrayPtr, TextureYArrayPtr, TextureBufId, ControlFlag);
      }

   inline MIL_INT64 M3dgraPolygon(MIL_ID List3dgraId,
                                  MIL_INT64 ParentLabel,
                                  MIL_INT64 CreationMode,
                                  MIL_INT    NumPoints,
                                  const MIL_FLOAT* CoordXArrayPtr,
                                  const MIL_FLOAT* CoordYArrayPtr,
                                  const MIL_FLOAT* CoordZArrayPtr,
                                  const MIL_FLOAT* TextureXArrayPtr,
                                  const MIL_FLOAT* TextureYArrayPtr,
                                  MIL_ID TextureBufId,
                                  MIL_INT64 ControlFlag)
      {
      return M3dgraPolygonFloat(List3dgraId, ParentLabel, CreationMode, NumPoints, CoordXArrayPtr, CoordYArrayPtr, CoordZArrayPtr, TextureXArrayPtr, TextureYArrayPtr, TextureBufId, ControlFlag);
      }
#endif



#ifdef __cplusplus

inline void M3dgraControl(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 ControlType, MIL_DOUBLE ControlValue)
   {
   M3dgraControlDouble(List3dgraId, Label, ControlType, ControlValue);
   }

inline void M3dgraControl(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 ControlType, MIL_INT64 ControlValue)
   {
   M3dgraControlInt64(List3dgraId, Label, ControlType, ControlValue);
   }

inline void M3dgraControl(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 ControlType, MIL_INT32 ControlValue)
   {
   M3dgraControlInt64(List3dgraId, Label, ControlType, ControlValue);
   }

#if M_MIL_USE_STRING
inline void M3dgraControl(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 ControlType, const MIL_STRING& ControlValue)
   {
   M3dgraControl(List3dgraId, Label, ControlType, M_PTR_TO_MIL_INT(ControlValue.c_str()));
   }
#endif

inline void M3dgraControl(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 ControlType, MIL_CONST_TEXT_PTR ControlValuePtr)
   {
   M3dgraControl(List3dgraId, Label, ControlType, (MIL_INT)ControlValuePtr);
   }

#if !(M_MIL_USE_LINUX && M_MIL_USE_64BIT)
inline void M3dgraControl(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 ControlType, int ControlValue)
   {
   M3dgraControlInt64(List3dgraId, Label, ControlType, ControlValue);
   }
#endif



#else

#define M3dgraControl       M3dgraControlDouble
#endif

#ifdef __cplusplus
inline MIL_INT64 M3dgraInquireDataType(MIL_INT64 InquireType)
   {
   const MIL_INT64 ForcedDataType = MinquireOverrides(InquireType, M_TYPE_MIL_INT);
   if(ForcedDataType != 0)
      return ForcedDataType;

   if(In3dgraInquireDoubleRange(InquireType))
      return M_TYPE_DOUBLE;

   if(In3dgraInquireInt64Range(InquireType))
      return M_TYPE_MIL_INT64;

   if(In3dgraInquireStringRange(InquireType))
      return M_TYPE_TEXT_CHAR;

   return M_TYPE_MIL_INT;
   }

#if M_MIL_USE_SAFE_TYPE
// ----------------------------------------------------------
// M3dgraInquire
   inline MIL_INT64 MFTYPE M3dgraInquireSafeType(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 InquireType, int UserVarPtr)
      {
      bool MustHaveUserPointer = M3dgraInquireMustHaveUserPtr(InquireType);
         
      if(UserVarPtr)
         SafeTypeError(MIL_TEXT("M3dgraInquire"));

      if(!UserVarPtr && MustHaveUserPointer)
         SafeTypeError(MIL_TEXT("M3dgraInquire"), MIL_TEXT("The specified InquireType requires a non-null output pointer."));

      return M3dgraInquire(List3dgraId, Label, InquireType, NULL);
      }

#if M_MIL_SAFE_TYPE_M_NULL_PTR_TYPE_EXISTS
   inline MIL_INT64 MFTYPE M3dgraInquireSafeType(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 InquireType, std::nullptr_t)
      {
      bool MustHaveUserPointer = M3dgraInquireMustHaveUserPtr(InquireType);

      if(MustHaveUserPointer)
         SafeTypeError(MIL_TEXT("M3dgraInquire"), MIL_TEXT("The specified InquireType requires a non-null output pointer."));

      return M3dgraInquire(List3dgraId, Label, InquireType, NULL);
      }
#endif

   inline MIL_INT64 MFTYPE M3dgraInquireSafeTypeExecute(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64  InquireType, void  *UserVarPtr, MIL_INT64  GivenType)
      {
      MIL_INT64  RequiredType = M3dgraInquireDataType(InquireType);
      ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

      if(RequiredType != GivenType)
         SafeTypeError(MIL_TEXT("M3dgraInquire"));

      return M3dgraInquire(List3dgraId, Label, InquireType, UserVarPtr);
      }

   inline MIL_INT64 MFTYPE M3dgraInquireUnsafe(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 InquireType, void         *UserVarPtr) { return M3dgraInquire(List3dgraId, Label, InquireType, UserVarPtr); }
   inline MIL_INT64 MFTYPE M3dgraInquireSafeType(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 InquireType, MIL_INT8*   UserVarPtr) { return  M3dgraInquireSafeTypeExecute(List3dgraId, Label, InquireType, UserVarPtr, M_TYPE_CHAR); }
   inline MIL_INT64 MFTYPE M3dgraInquireSafeType(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 InquireType, MIL_INT16*  UserVarPtr) { return  M3dgraInquireSafeTypeExecute(List3dgraId, Label, InquireType, UserVarPtr, M_TYPE_SHORT); }
   inline MIL_INT64 MFTYPE M3dgraInquireSafeType(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 InquireType, MIL_INT32   *UserVarPtr) { return M3dgraInquireSafeTypeExecute(List3dgraId, Label, InquireType, UserVarPtr, M_TYPE_MIL_INT32); }
   inline MIL_INT64 MFTYPE M3dgraInquireSafeType(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 InquireType, MIL_INT64   *UserVarPtr) { return M3dgraInquireSafeTypeExecute(List3dgraId, Label, InquireType, UserVarPtr, M_TYPE_MIL_INT64); }
   inline MIL_INT64 MFTYPE M3dgraInquireSafeType(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 InquireType, MIL_FLOAT   *UserVarPtr) { return M3dgraInquireSafeTypeExecute(List3dgraId, Label, InquireType, UserVarPtr, M_TYPE_MIL_FLOAT); }
   inline MIL_INT64 MFTYPE M3dgraInquireSafeType(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 InquireType, MIL_DOUBLE  *UserVarPtr) { return M3dgraInquireSafeTypeExecute(List3dgraId, Label, InquireType, UserVarPtr, M_TYPE_DOUBLE); }
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
   inline MIL_INT64 MFTYPE M3dgraInquireSafeType(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 InquireType, MIL_UINT8*   UserVarPtr) { return M3dgraInquireSafeTypeExecute(List3dgraId, Label, InquireType, UserVarPtr, M_TYPE_CHAR); }
   inline MIL_INT64 MFTYPE M3dgraInquireSafeType(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 InquireType, MIL_UINT16*  UserVarPtr) { return M3dgraInquireSafeTypeExecute(List3dgraId, Label, InquireType, UserVarPtr, M_TYPE_SHORT); }
   inline MIL_INT64 MFTYPE M3dgraInquireSafeType(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 InquireType, MIL_UINT32  *UserVarPtr) { return M3dgraInquireSafeTypeExecute(List3dgraId, Label, InquireType, UserVarPtr, M_TYPE_MIL_INT32); }
   inline MIL_INT64 MFTYPE M3dgraInquireSafeType(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 InquireType, MIL_UINT64  *UserVarPtr) { return M3dgraInquireSafeTypeExecute(List3dgraId, Label, InquireType, UserVarPtr, M_TYPE_MIL_INT64); }
#endif
#if M_MIL_SAFE_TYPE_ADD_WCHAR_T                                                      
   inline MIL_INT64 MFTYPE M3dgraInquireSafeType(MIL_ID Display3dId, MIL_INT64 Label, MIL_INT64  InquireType, wchar_t*    UserVarPtr) { return M3dgraInquireSafeTypeExecute(Display3dId, Label, InquireType, UserVarPtr, M_TYPE_TEXT_CHAR); }
#endif

#define M3dgraInquire           M3dgraInquireSafeType

#else // #if M_MIL_USE_SAFE_TYPE
#define M3dgraInquireUnsafe     M3dgraInquire
#endif // #if M_MIL_USE_SAFE_TYPE

#endif //__cplusplus
#if M_MIL_USE_STRING

#if M_MIL_USE_SAFE_TYPE
inline MIL_INT64 MFTYPE M3dgraInquireSafeType(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64  InquireType, MIL_STRING&    UserVarPtr)
   {
   MIL_INT64 RetValue = 0;
   MIL_INT InternalStringSize = 0;

   if((InquireType & M_CLIENT_ENCODING) != M_CLIENT_ENCODING)
      {
      SafeTypeError(MIL_TEXT("M3dgraInquire"), MIL_TEXT("Inquire type not supported with MIL_STRING."));
      }

   M3dgraInquire(List3dgraId, Label, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = M3dgraInquire(List3dgraId, Label, InquireType, &UserVarPtr[0]);
      UserVarPtr.resize(InternalStringSize - 1);


      }

   return RetValue;
   }

#else
inline MIL_INT64 MFTYPE M3dgraInquire(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64  InquireType, MIL_STRING&    UserVarPtr)
   {
   MIL_INT64 RetValue = 0;
   MIL_INT InternalStringSize = 0;

   M3dgraInquire(List3dgraId, Label, InquireType + M_STRING_SIZE, &InternalStringSize);

   if(InternalStringSize > 0)
      {
      UserVarPtr.assign(InternalStringSize, MIL_TEXT('\0'));
      RetValue = M3dgraInquire(List3dgraId, Label, InquireType, &UserVarPtr[0]);
      UserVarPtr.resize(InternalStringSize - 1);

      }

   return RetValue;
   }
#endif

inline MIL_INT64 MFTYPE M3dgraText(MIL_ID List3dgraId, MIL_INT64 ParentLabel, const MIL_STRING& Text, MIL_ID Matrix3dgeoId, MIL_INT64 Options, MIL_INT64 ControlFlag)
   {
   return M3dgraText(List3dgraId, ParentLabel, Text.c_str(), Matrix3dgeoId, Options, ControlFlag);
   }


inline MIL_INT64 M3dgraAxis(MIL_ID List3dgraId, MIL_INT64 ParentLabel, MIL_ID Matrix3dgeoId, MIL_DOUBLE AxisLength, const MIL_STRING& Name, MIL_INT64 Options, MIL_INT64 ControlFlag)
   {
   return M3dgraAxis(List3dgraId, ParentLabel, Matrix3dgeoId, AxisLength, Name.c_str(), Options, ControlFlag);
   }
#endif /* M_MIL_USE_STRING */

// ----------------------------------------------------------
// Overload for std::vector.
#if defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR
// ----------------------------------------------------------
// Overloads for std::vector in  M3dgraInquire.
   template <typename UserType>
   inline MIL_INT64 MFTYPE M3dgraInquire(MIL_ID List3dgraId, MIL_INT64 Label, MIL_INT64 InquireType, std::vector<UserType> &UserVarPtr)
      {
      // If the given MIL data type is not the same as the SrcType, change it to the correct one
      // and give a warning.
      MIL_INT64 InternalTrueDataTypeForStdVector = MilTraits<UserType>::TypeFlag;

#if M_MIL_USE_SAFE_TYPE
      if(M_GET_HLVLDATATYPE(InquireType) != 0)
         {
         SafeTypeError(MIL_TEXT("M3dgraInquire"), MIL_TEXT("Combination value for the required data type is not supported with std::vector overload."));
         }
#endif

      InquireType = M_STRIP_HLVLDATATYPE(InquireType) + InternalTrueDataTypeForStdVector;

      MIL_INT InternalNumberOfElementsForStdVector = 0;
      M3dgraInquire(List3dgraId, Label, M_STRIP_HLVLDATATYPE(InquireType) + M_NB_ELEMENTS + M_TYPE_MIL_INT, &InternalNumberOfElementsForStdVector);

      UserVarPtr.resize(InternalNumberOfElementsForStdVector);

      if(InternalNumberOfElementsForStdVector > 0)
         {
         return M3dgraInquire(List3dgraId, Label, InquireType, &UserVarPtr[0]);
         }
      return 0;
      }

   // ----------------------------------------------------------
   // Overloads for std::vector in M3dgraDots.
   template <typename UserType>
   inline MIL_INT64 MFTYPE M3dgraDots(MIL_ID List3dgraId,
                                      MIL_INT64 ParentLabel,
                                      MIL_INT NumPoints,
                                      const std::vector<UserType>& CoordXArrayPtr,
                                      const std::vector<UserType>& CoordYArrayPtr,
                                      const std::vector<UserType>& CoordZArrayPtr,
                                      CMilArrayParamIn PointsRArrayPtr,
                                      CMilArrayParamIn PointsGArrayPtr,
                                      CMilArrayParamIn PointsBArrayPtr,
                                      MIL_INT64 ControlFlag)
      {
#if M_MIL_USE_SAFE_TYPE
      if(!PointsRArrayPtr.IsValidParam() ||
         !PointsGArrayPtr.IsValidParam() ||
         !PointsBArrayPtr.IsValidParam())
         {
         SafeTypeError(MIL_TEXT("M3dgraDots"), MIL_TEXT("The input arrays cannot be a non-zero integer."));
         }
      if((!PointsRArrayPtr.IsNullPtr() && PointsRArrayPtr.GetMilDataType() != MilTraits<MIL_UINT8>::TypeFlag) ||
         (!PointsGArrayPtr.IsNullPtr() && PointsGArrayPtr.GetMilDataType() != MilTraits<MIL_UINT8>::TypeFlag) ||
         (!PointsBArrayPtr.IsNullPtr() && PointsBArrayPtr.GetMilDataType() != MilTraits<MIL_UINT8>::TypeFlag))
         {
         SafeTypeError(MIL_TEXT("M3dgraDots"), MIL_TEXT("The data type of the color vectors must be MIL_UINT8."));
         }
      if(CoordXArrayPtr.size() != CoordYArrayPtr.size() || CoordXArrayPtr.size() != CoordZArrayPtr.size())
         {
         SafeTypeError(MIL_TEXT("M3dgraDots"), MIL_TEXT("The coordinate vectors must have the same size."));
         }
      if(CoordXArrayPtr.empty())
         {
         SafeTypeError(MIL_TEXT("M3dgraDots"), MIL_TEXT("The coordinate vectors cannot be empty."));
         }
      if((PointsRArrayPtr.IsNullPtr() != PointsGArrayPtr.IsNullPtr()) ||
         (PointsRArrayPtr.IsNullPtr() != PointsBArrayPtr.IsNullPtr()) ||
         (!PointsRArrayPtr.IsNullPtr() && (MIL_INT)CoordXArrayPtr.size() != PointsRArrayPtr.Size<MIL_UINT8>()) ||
         (!PointsGArrayPtr.IsNullPtr() && (MIL_INT)CoordXArrayPtr.size() != PointsGArrayPtr.Size<MIL_UINT8>()) ||
         (!PointsBArrayPtr.IsNullPtr() && (MIL_INT)CoordXArrayPtr.size() != PointsBArrayPtr.Size<MIL_UINT8>()))
         {
         SafeTypeError(MIL_TEXT("M3dgraDots"), MIL_TEXT("The color vectors must either all be empty or have the same size as the coordinate vectors."));
         }
      if(NumPoints <= 0)
         {
         SafeTypeError(MIL_TEXT("M3dgraDots"), MIL_TEXT("NumPoints parameter must be greater than zero."));
         }
      if(NumPoints > (MIL_INT)CoordXArrayPtr.size() && NumPoints != M_DEFAULT)
         {
         SafeTypeError(MIL_TEXT("M3dgraDots"), MIL_TEXT("NumPoints parameter must be smaller or equal (M_DEFAULT) to the size of the coordinate vectors."));
         }
#endif
      if(NumPoints == M_DEFAULT || NumPoints > (MIL_INT)CoordXArrayPtr.size())
         {
         NumPoints = (MIL_INT)CoordXArrayPtr.size();
         }

      return M3dgraDots(List3dgraId,
                        ParentLabel,
                        NumPoints,
                        &CoordXArrayPtr[0],
                        &CoordYArrayPtr[0],
                        &CoordZArrayPtr[0],
                        PointsRArrayPtr.GetData<MIL_UINT8>(),
                        PointsGArrayPtr.GetData<MIL_UINT8>(),
                        PointsBArrayPtr.GetData<MIL_UINT8>(),
                        ControlFlag);
      }
   // ----------------------------------------------------------
   // Overloads for std::vector in M3dgraPolygon.
   template <typename UserType>
   inline MIL_INT64 MFTYPE M3dgraPolygon(MIL_ID List3dgraId,
                                         MIL_INT64 ParentLabel,
                                         MIL_INT64 CreationMode,
                                         MIL_INT NumPoints,
                                         const std::vector<UserType>& CoordXArrayPtr,
                                         const std::vector<UserType>& CoordYArrayPtr,
                                         const std::vector<UserType>& CoordZArrayPtr,
                                         CMilArrayParamIn TextureXArrayPtr,
                                         CMilArrayParamIn TextureYArrayPtr,
                                         MIL_ID TextureBufId,
                                         MIL_INT64 ControlFlag)
      {
#if M_MIL_USE_SAFE_TYPE
      if(!TextureXArrayPtr.IsValidParam() ||
         !TextureYArrayPtr.IsValidParam())
         {
         SafeTypeError(MIL_TEXT("M3dgraPolygon"), MIL_TEXT("The input arrays cannot be a non-zero integer."));
         }
      if((!TextureXArrayPtr.IsNullPtr() && TextureXArrayPtr.GetMilDataType() != MilTraits<UserType>::TypeFlag) ||
         (!TextureYArrayPtr.IsNullPtr() && TextureYArrayPtr.GetMilDataType() != MilTraits<UserType>::TypeFlag))
         {
         SafeTypeError(MIL_TEXT("M3dgraPolygon"), MIL_TEXT("The coordinate and texture vectors must all have the same data type."));
         }
      if(CoordXArrayPtr.size() != CoordYArrayPtr.size() || CoordXArrayPtr.size() != CoordZArrayPtr.size())
         {
         SafeTypeError(MIL_TEXT("M3dgraPolygon"), MIL_TEXT("The coordinate vectors must have the same size."));
         }
      if(CoordXArrayPtr.empty())
         {
         SafeTypeError(MIL_TEXT("M3dgraPolygon"), MIL_TEXT("The vectors cannot be empty."));
         }
      if((TextureXArrayPtr.IsNullPtr() != TextureYArrayPtr.IsNullPtr()) ||
         (!TextureXArrayPtr.IsNullPtr() && (MIL_INT)CoordXArrayPtr.size() != TextureXArrayPtr.Size<UserType>()) ||
         (!TextureYArrayPtr.IsNullPtr() && (MIL_INT)CoordXArrayPtr.size() != TextureYArrayPtr.Size<UserType>()))
         {
         SafeTypeError(MIL_TEXT("M3dgraPolygon"), MIL_TEXT("The texture vectors must either both be null or have the same size as the coordinate vectors."));
         }
      if(NumPoints <= 0)
         {
         SafeTypeError(MIL_TEXT("M3dgraPolygon"), MIL_TEXT("NumPoints parameter must be greater than zero."));
         }
      if(NumPoints > (MIL_INT)CoordXArrayPtr.size() && NumPoints != M_DEFAULT)
         {
         SafeTypeError(MIL_TEXT("M3dgraPolygon"), MIL_TEXT("NumPoints parameter must be smaller or equal (M_DEFAULT) to the size of the coordinate vectors."));
         }
#endif
      if(NumPoints == M_DEFAULT || NumPoints > (MIL_INT)CoordXArrayPtr.size())
         {
         NumPoints = (MIL_INT)CoordXArrayPtr.size();
         }

      return M3dgraPolygon(List3dgraId,
                           ParentLabel,
                           CreationMode,
                           NumPoints,
                           &CoordXArrayPtr[0],
                           &CoordYArrayPtr[0],
                           &CoordZArrayPtr[0],
                           TextureXArrayPtr.GetData<UserType>(),
                           TextureYArrayPtr.GetData<UserType>(),
                           TextureBufId,
                           ControlFlag);
      }
#endif // defined(M_MIL_USE_VECTOR) && M_MIL_USE_VECTOR


////////////////////////////////////////////////////////////////////////////////
// MIL_UNIQUE_ID support

#if M_MIL_USE_MIL_UNIQUE_ID

#if M_MIL_USE_SAFE_TYPE
template <> inline bool MilIsCorrectObjectType<&M3dgraFree>(MIL_INT64 ObjectType)
   {
   return ObjectType == M_3D_GRAPHIC_LIST;
   }
#endif
typedef MIL_UNIQUE_ID<&M3dgraFree > MIL_UNIQUE_3DGRA_ID;

#if M_MIL_USE_MOVE_SEMANTICS
//3DGRA
inline MIL_UNIQUE_3DGRA_ID M3dgraAlloc(MIL_ID SysId, MIL_INT64 ControlFlag, MIL_UNIQUE_ID_TAG)
   {
   return MIL_UNIQUE_3DGRA_ID(M3dgraAlloc(SysId, ControlFlag, M_NULL));
   }

template <MilFreeFuncType FreeFunc> inline void M3dgraFree(const MIL_UNIQUE_ID<FreeFunc>&) = delete;
#endif // M_MIL_USE_MOVE_SEMANTICS
#endif // M_MIL_USE_MIL_UNIQUE_ID


// End of MIL_UNIQUE_ID support
////////////////////////////////////////////////////////////////////////////////
#endif // __MIL3DGRA_H__
