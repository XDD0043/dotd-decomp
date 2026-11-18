// RwTypes.h - the RenderWare 3.7 core value types (rwplcore.h) as the PS3 build lays them out.
//
// Names and member order from XXL2's RW 3.7 build (the same SDK, DWARF in work/xxl2-dwarf); sizes and
// offsets are the PS3's (4-byte pointers, RwMatrix 16-byte aligned: Rt2dObject's MTM is at +0x10).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

typedef int32_t RwInt32;
typedef uint32_t RwUInt32;
typedef int16_t RwInt16;
typedef uint16_t RwUInt16;
typedef int8_t RwInt8;
typedef uint8_t RwUInt8;
typedef float RwReal;
typedef int32_t RwBool;
typedef char RwChar;
// RwImVertexIndex (RxVertexIndex) is 32-bit in the PS3 build: DrawPSGLImmediateGeometry 0x76b610 draws the
// indices as GL_UNSIGNED_INT (0x1405) and Index_ComputeRange 0x6bb0d0 reads them with lwz (stride 4); Rt2d's
// shared glyph index buffer (0xcfa7c0) holds 32-bit words.
typedef uint32_t RwImVertexIndex;

struct RwV2d {
    RwReal x;
    RwReal y;
};
DOTD_ASSERT_SIZE(RwV2d, 0x8);

struct RwV3d {
    RwReal x;
    RwReal y;
    RwReal z;
};
DOTD_ASSERT_SIZE(RwV3d, 0xc);

// RwBBox: sup (the maxima) then inf (the minima).
struct RwBBox {
    RwV3d sup;
    RwV3d inf;
};
DOTD_ASSERT_SIZE(RwBBox, 0x18);

struct RwRGBA {
    RwUInt8 red;
    RwUInt8 green;
    RwUInt8 blue;
    RwUInt8 alpha;
};
DOTD_ASSERT_SIZE(RwRGBA, 0x4);

struct RwRGBAReal {
    RwReal red;
    RwReal green;
    RwReal blue;
    RwReal alpha;
};
DOTD_ASSERT_SIZE(RwRGBAReal, 0x10);

// RwMatrixTag. flags: rwMATRIXTYPENORMAL 1, rwMATRIXTYPEORTHOGONAL 2, rwMATRIXTYPEORTHONORMAL 3,
// rwMATRIXINTERNALIDENTITY 0x20000.
struct alignas(16) RwMatrix {
    RwV3d right;      // +0x00
    RwUInt32 flags;   // +0x0c
    RwV3d up;         // +0x10
    RwUInt32 pad1;    // +0x1c
    RwV3d at;         // +0x20
    RwUInt32 pad2;    // +0x2c
    RwV3d pos;        // +0x30
    RwUInt32 pad3;    // +0x3c
};
DOTD_ASSERT_SIZE(RwMatrix, 0x40);

enum : RwUInt32 {
    rwMATRIXTYPENORMAL = 0x1,
    rwMATRIXTYPEORTHOGONAL = 0x2,
    rwMATRIXTYPEORTHONORMAL = 0x3,
    rwMATRIXTYPEMASK = 0x3,
    rwMATRIXINTERNALIDENTITY = 0x20000,
};

// RwOpCombineType (RwMatrixTranslate/Scale/Rotate/Transform).
enum RwOpCombineType : RwInt32 {
    rwCOMBINEREPLACE = 0,
    rwCOMBINEPRECONCAT = 1,
    rwCOMBINEPOSTCONCAT = 2,
};

// RwSList (internal resizable array; PS3 0x10). Ported in RwSList.cpp.
struct RwSList {
    RwUInt8* listElements;      // +0x00
    RwInt32 numElementsFilled;  // +0x04
    RwInt32 numElementsAlloced; // +0x08
    RwInt32 entrySize;          // +0x0c (the native sizeof of an entry)
};
DOTD_ASSERT_SIZE(RwSList, 0x10);

// RwIm3DVertex as the PS3 build lays it out (0x24): object-space position, normal, the colour as packed
// RwRGBA bytes, then u, v (RwIm3DVertexSet*: the Rt2d glyph and fill builders write exactly these).
struct RwIm3DVertex {
    RwV3d objVertex;   // +0x00
    RwV3d objNormal;   // +0x0c
    RwRGBA color;      // +0x18
    RwReal u;          // +0x1c
    RwReal v;          // +0x20
};
DOTD_ASSERT_SIZE(RwIm3DVertex, 0x24);

// RwPrimitiveType.
enum RwPrimitiveType : RwInt32 {
    rwPRIMTYPENAPRIMTYPE = 0,
    rwPRIMTYPELINELIST = 1,
    rwPRIMTYPEPOLYLINE = 2,
    rwPRIMTYPETRILIST = 3,
    rwPRIMTYPETRISTRIP = 4,
    rwPRIMTYPETRIFAN = 5,
    rwPRIMTYPEPOINTLIST = 6,
};

// RwIm3DTransformFlags.
enum : RwUInt32 {
    rwIM3D_VERTEXUV = 1,
    rwIM3D_ALLOPAQUE = 2,
    rwIM3D_NOCLIP = 4,
    rwIM3D_VERTEXXYZ = 8,
    rwIM3D_VERTEXRGBA = 0x10,
};

// RwRenderState (RW 3.7 numbering, from XXL2's rwplcore.h enum; the PS3's setter table at 0xcefcb4 has
// SRCBLENDALPHA/DESTBLENDALPHA at 30/31 and ALPHATESTFUNCTIONREF at 32).
enum RwRenderState : RwInt32 {
    rwRENDERSTATENARENDERSTATE = 0,
    rwRENDERSTATETEXTURERASTER = 1,
    rwRENDERSTATETEXTUREADDRESS = 2,
    rwRENDERSTATETEXTUREADDRESSU = 3,
    rwRENDERSTATETEXTUREADDRESSV = 4,
    rwRENDERSTATETEXTUREPERSPECTIVE = 5,
    rwRENDERSTATEZTESTENABLE = 6,
    rwRENDERSTATESHADEMODE = 7,
    rwRENDERSTATEZWRITEENABLE = 8,
    rwRENDERSTATETEXTUREFILTER = 9,
    rwRENDERSTATESRCBLEND = 10,
    rwRENDERSTATEDESTBLEND = 11,
    rwRENDERSTATEVERTEXALPHAENABLE = 12,
    rwRENDERSTATEBORDERCOLOR = 13,
    rwRENDERSTATEFOGENABLE = 14,
    rwRENDERSTATEFOGCOLOR = 15,
    rwRENDERSTATEFOGTYPE = 16,
    rwRENDERSTATEFOGDENSITY = 17,
    rwRENDERSTATECULLMODE = 20,
    rwRENDERSTATESTENCILENABLE = 21,
    rwRENDERSTATESTENCILFAIL = 22,
    rwRENDERSTATESTENCILZFAIL = 23,
    rwRENDERSTATESTENCILPASS = 24,
    rwRENDERSTATESTENCILFUNCTION = 25,
    rwRENDERSTATESTENCILFUNCTIONREF = 26,
    rwRENDERSTATESTENCILFUNCTIONMASK = 27,
    rwRENDERSTATESTENCILFUNCTIONWRITEMASK = 28,
    rwRENDERSTATEALPHATESTFUNCTION = 29,
    rwRENDERSTATESRCBLENDALPHA = 30,
    rwRENDERSTATEDESTBLENDALPHA = 31,
    rwRENDERSTATEALPHATESTFUNCTIONREF = 32,
};

// Opaque RW objects the 2D toolkit holds by pointer.
struct RwTexture;
struct RwTexDictionary;
struct RwCamera;
struct RwRaster;
struct RwFreeList;
