// CKGLError.cpp - reconstructed original translation unit 0x87b18-0x87f78 (GAME_TOC1, main_toc1), 12 functions, 9 live.
// Primary class: CKGLError  key 0x4e  category Error  size 0x4  vtable 0xb16998
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x87b18  CKGLError_Delete
//   [ ] 0x87b68  CKGLError_Construct  [dead]
//   [ ] 0x87b78  CKGLError_Construct_2  [dead]
//   [x] 0x87b88  CKGLError_GetErrorMessage
//   [ ] 0x87d18  RegisterCKGLErrorClass
//   [ ] 0x87d90  _GLOBAL__I_87d90
//   [x] 0x87da0  CKGLError_DeleteArray
//   [x] 0x87e40  CKGLError_Create
//   [x] 0x87e78  CKGLError_CreateArray
//   [x] 0x87f08  CKGLError_Destructor
//   [ ] 0x87f20  CKGLError_Destructor_2  [dead]
//   [x] 0x87f38  CKGLError_DeletingDestructor
//
//   [x] 0x99c2c8  CKGLError_GetClassID  [inline]
//   [x] 0x99c2d0  CKGLError_GetClassType  [inline]
//   [x] 0x99c2d8  CKGLError_Destroy  [inline]
//   [x] 0x99c2e0  CKGLError_IsKindOfClass  [inline]
#include "k2000/core/CKGLError.h"

// C2.8 port-rest R02. The messages are the original bytes (Latin-1, octal escapes); nothing displays them.

// 0x00087b88 CKGLError_GetErrorMessage: a jump table over code - 0x10000 (29 entries), the rest the default.
const char* CKGLError::GetErrorMessage(int32_t code) {
    switch (code) {
        case 0x10000:
            return "L'attachement du plugin \340 \351chou\351.";
        case 0x10002:
            return "L'initialisation du moteur a \351chou\351. V\351rifier que vous avez une version r\351cente de DirectX. Et essayer aussi de fermer toutes les applications actuellement ouverte (3DSMAX, MAYA, etc...) et de relancer l'application.";
        case 0x10003:
            return "La cr\351ation du raster \340 \351chou\351e";
        case 0x10004:
            return "La destruction du raster \340 \351chou\351e";
        case 0x10005:
            return "Le stream n'a pu etre ouvert";
        case 0x10006:
            return "La g\351om\351trie n'a pu etre cr\351\351e";
        case 0x10007:
            return "La g\351om\351trie n'a pu etre sauvegard\351e";
        case 0x10008:
            return "La g\351om\351trie n'a pu etre charg\351e";
        case 0x10009:
            return "Une g\351om\351trie ne peut etre cr\351\351e sans vertice";
        case 0x1000a:
            return "Une g\351om\351trie ne peut etre cr\351\351e sans indices de triangulation";
        case 0x1000b:
            return "La g\351om\351trie ne dispose pas de coordonn\351es de textures alors que le nombre de sets de texture est diff\351rent de 0";
        case 0x1000c:
            return "La g\351om\351trie dispose de coordonn\351es de textures alors que le nombre de sets de texture est 0";
        case 0x1000d:
            return "Le skin n'a pu etre cr\351\351";
        case 0x1000e:
            return "La cr\351ation d'un skin n\351cessite un CHierarchyNode (a_pHierarchyNode) non NULL";
        case 0x1000f:
            return "La cr\351ation d'un skin n\351cessite un tableau de poids (a_pVertexWeights) non NULL";
        case 0x10010:
            return "La cr\351ation d'un skin n\351cessite un tableau d'association bones/ vertex (a_ui32VertexIndices) non NULL";
        case 0x10011:
            return "La hi\351rarchie n'a pu etre cr\351er";
        case 0x10012:
            return "Une hi\351rarchie ne peut pas avoir 0 bones";
        case 0x10013:
            return "Une hi\351rarchie doit avoir un bone Root";
        case 0x10014:
            return "La hi\351rachie de bones ne contient pas le bon nombre de bones";
        case 0x10015:
            return "Le num\351ro du bone est invalide";
        case 0x10016:
            return "La texture n'a pas pu \352tre lu";
        case 0x10017:
            return "Le dictionaire de texture n'a pu \352tre cr\351er";
        case 0x10018:
            return "Le dictionaire de texture n'a pu \352tre lu";
        case 0x10019:
            return "Le dictionaire de texture n'a pu \352tre sauvegard\351";
        case 0x1001a:
            return "Un Ground ne peut \352tre cr\351\351 sans vertex";
        case 0x1001b:
            return "Un Ground ne peut \352tre cr\351\351 sans triangle";
        case 0x1001c:
            return "OwnerType du BoundingVolume non valide";
        default:  // and the table entries that jump to it
            return "L'erreur n'est pas document\351e par le module KGL";
    }
}
