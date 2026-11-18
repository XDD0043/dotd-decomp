// RwMatrix.h - RenderWare 3.7 matrix and vector maths (rwcore: matrix.c, vector.c, the sqrt tables), as
// the PS3 library computes it. Rt2d (and later the 3D code) depends on these results bit for bit.
//
// Signatures are RW 3.7's public ones. PS3 addresses of the library code are in the comments; the
// bodies follow the PS3 assembly (fmadds vs fmuls+fadds, float vs double, the table sqrt, the VMX
// RwMatrixMultiply), STYLE.md §4.
//
// The RW module state is file-scope here: the matrix globals (RWEngineInstance + [0xcf01bc]: the matrix
// free list, the optimisation flags 0x20000, the multiply callback, the default tolerances 0.01f) and the
// vector globals (RWEngineInstance + [0xcf02a0]: the two sqrt tables, the transform callbacks, which stay
// the defaults: _rwV3dSetTransformFns is never called).
#pragma once
#include "Renderware/rwcore/RwTypes.h"

struct RwStream;

// RwMatrixTolerance (RwMatrixOptimize).
struct RwMatrixTolerance {
    RwReal Normal;
    RwReal Orthogonal;
    RwReal Identity;
};

// The engine's sqrt tables (vector globals +0 / +4: two 4096-entry tables that _rwV3dOpen 0x75eb48
// builds; here built on first use, identical word for word to the PS3's).
// 0x0075e738 RW_Sqrt (rwSqrt): 0 for +0.0; the table value for everything else (negative inputs
// included: the sign bit is ignored, -0.0 gives 0x1fb504f3).
RwReal rwSqrt(RwReal x);
// 0x0075e790 RW_InvSqrt (rwInvSqrt): 0 for +0.0.
RwReal rwInvSqrt(RwReal x);

// 0x007588f0 RwMatrixCreate: a new identity matrix (flags exactly rwMATRIXINTERNALIDENTITY |
// rwMATRIXTYPEORTHONORMAL) from the matrix free list.
RwMatrix* RwMatrixCreate();
// 0x00758890 RwMatrixDestroy
RwBool RwMatrixDestroy(RwMatrix* mpMat);
// RwMatrixSetIdentity (a macro on the PS3, inlined e.g. at 0x759218): the identity, flags |= 0x20003,
// the pads untouched.
RwMatrix* RwMatrixSetIdentity(RwMatrix* matrix);
// 0x007586b8 RwMatrixUpdate: clears the type and identity flags (the matrix was edited).
RwMatrix* RwMatrixUpdate(RwMatrix* matrix);
// 0x00759648 RwMatrixMultiply_maybe: dst = a * b (row vectors: a then b), computed with VMX (vmaddfp)
// including the w lanes; flags = a.flags & b.flags. dst may alias a or b: the lanes are all loaded
// first, but the flags are read after the stores (an aliased input's flags are then the w-lane value).
RwMatrix* RwMatrixMultiply(RwMatrix* matrixOut, const RwMatrix* matrixIn1, const RwMatrix* matrixIn2);
// 0x00759190 RwMatrixTranslate
RwMatrix* RwMatrixTranslate(RwMatrix* matrix, const RwV3d* translation, RwOpCombineType combineOp);
// 0x00759398 RwMatrixScale
RwMatrix* RwMatrixScale(RwMatrix* matrix, const RwV3d* scale, RwOpCombineType combineOp);
// 0x00759af0 RwMatrixRotate (angle in degrees; sin/cos through the libm's _Sin in double precision)
RwMatrix* RwMatrixRotate(RwMatrix* matrix, const RwV3d* axis, RwReal angle, RwOpCombineType combineOp);
// 0x00759920 RwMatrixRotateOneMinusCosineSine (unitAxis must be normalised)
RwMatrix* RwMatrixRotateOneMinusCosineSine(RwMatrix* matrix, const RwV3d* unitAxis, RwReal oneMinusCosine,
                                           RwReal sine, RwOpCombineType combineOp);
// 0x007586d8 RwMatrixInvert_maybe: a copy when the input is flagged identity (and identity optimisation
// is on), the transpose for orthonormal matrices, otherwise _rwMatrixInvertGeneric (0x758268).
RwMatrix* RwMatrixInvert(RwMatrix* matrixOut, const RwMatrix* matrixIn);
// 0x00758d48 RwMatrixOrthoNormalize
RwMatrix* RwMatrixOrthoNormalize(RwMatrix* matrixOut, const RwMatrix* matrixIn);
// 0x00759d90 RwMatrixOptimize (tolerance null: the default tolerances, 0.01f each)
RwMatrix* RwMatrixOptimize(RwMatrix* matrix, const RwMatrixTolerance* tolerance);
// 0x007597d8 RwMatrixTransform
RwMatrix* RwMatrixTransform(RwMatrix* matrix, const RwMatrix* transform, RwOpCombineType combineOp);
// 0x007572e0 RwMatrixStreamRead (after the caller's RwStreamFindChunk(rwID_MATRIX)): finds the struct
// chunk, checks its version, reads the stream matrix; RwMatrixOrthoNormalize when its flags say so.
RwMatrix* RwMatrixStreamRead(RwStream* stream, RwMatrix* matrix);

// 0x00758470 _rwMatrixDeterminant (of the 3x3 part)
RwReal _rwMatrixDeterminant(const RwMatrix* matrix);
// 0x007584c8 _rwMatrixOrthogonalError: the sum of the squared dot products of the axes.
RwReal _rwMatrixOrthogonalError(const RwMatrix* matrix);
// 0x00758528 _rwMatrixNormalError_maybe: the sum of the squared (|axis|^2 - 1).
RwReal _rwMatrixNormalError(const RwMatrix* matrix);
// 0x00758598 _rwMatrixIdentityError_maybe: the squared distance of the 4x3 part from the identity.
RwReal _rwMatrixIdentityError(const RwMatrix* matrix);
// 0x00758638 _rwMatrixGetOptimizeTolerances
RwBool _rwMatrixGetOptimizeTolerances(RwMatrixTolerance* tolerance);
// 0x00758678 _rwMatrixSetOptimizeTolerances
RwBool _rwMatrixSetOptimizeTolerances(const RwMatrixTolerance* tolerance);
// 0x00758448 RwMatrix_SetOptimizations_maybe (rwMATRIXOPTIMIZE_IDENTITY 0x20000 by default)
RwBool RwMatrixOptimizations(RwInt32 optimizeFlags);

// 0x0075e7f0 RwV3dTransformPoint (pointOut may alias pointIn)
RwV3d* RwV3dTransformPoint(RwV3d* pointOut, const RwV3d* pointIn, const RwMatrix* matrix);
// 0x00744b10 RwBBoxCalculate (rwcore babbox.c; the code is in rpworld/RpGeometry.cpp)
RwBBox* RwBBoxCalculate(RwBBox* boundBox, const RwV3d* verts, RwInt32 numVerts);
// 0x0075e850 RwV3dTransformPoints
RwV3d* RwV3dTransformPoints(RwV3d* pointsOut, const RwV3d* pointsIn, RwInt32 numPoints, const RwMatrix* matrix);
// 0x0075e8b0 RwV3dTransformVector
RwV3d* RwV3dTransformVector(RwV3d* vectorOut, const RwV3d* vectorIn, const RwMatrix* matrix);
// 0x0075e910 RwV3dTransformVectors
RwV3d* RwV3dTransformVectors(RwV3d* vectorsOut, const RwV3d* vectorsIn, RwInt32 numPoints, const RwMatrix* matrix);
// 0x0075f018 RwV3dNormalize: returns the length; a zero vector gives (0,0,0) and E_RW_ZEROLENGTH.
RwReal RwV3dNormalize(RwV3d* out, const RwV3d* in);
// 0x0075ee40 _rwV3dNormalize_maybe: like RwV3dNormalize but returns the reciprocal length, no error.
RwReal _rwV3dNormalize(RwV3d* out, const RwV3d* in);
// 0x0075ead8 RwV3dLength_maybe
RwReal RwV3dLength(const RwV3d* in);
// 0x0075eed0 RwV2dNormalize_maybe
RwReal RwV2dNormalize(RwV2d* out, const RwV2d* in);
// 0x0075ea70 RwV2dLength_maybe
RwReal RwV2dLength(const RwV2d* in);
