// CKILError.cpp - reconstructed original translation unit 0x103288-0x103810 (GAME_TOC1, main_toc1), 14 functions, 11 live.
// Primary class: CKILError  key 0xce  category Error  size 0x4  vtable 0xb19460
// Other owners: CKInput (1), CKVibrationData (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x103288  CKILError_Delete
//   [ ] 0x1032d8  CKILError_Construct  [dead]
//   [ ] 0x1032e8  CKILError_Construct_2  [dead]
//   [x] 0x1032f8  CKILError_GetErrorMessage
//   [ ] 0x103510  RegisterCKILErrorClass
//   [ ] 0x103588  _GLOBAL__I_103588
//   [x] 0x103598  CKILError_DeleteArray
//   [x] 0x103638  CKILError_Create
//   [x] 0x103670  CKILError_CreateArray
//   [x] 0x103700  CKILError_Destructor
//   [ ] 0x103718  CKILError_Destructor_2  [dead]
//   [x] 0x103730  CKILError_DeletingDestructor
//   [x] 0x103770  CKInput_Delete  (CKInput::Delete (the deleting destructor, vt+0x04), CKInput.cpp)
//   [x] 0x1037c0  CKVibrationData_Delete  (the Delete factory: DOTD_DECLARE_FACTORIES(CKVibrationData))
//
//   [x] 0x9a6388  CKILError_GetClassID  [inline]
//   [x] 0x9a6390  CKILError_GetClassType  [inline]
//   [x] 0x9a6398  CKILError_vf2C  [inline]
//   [x] 0x9a63a0  CKILError_Destroy  [inline]
//   [x] 0x9a63a8  CKILError_IsKindOfClass  [inline]
#include "k2000/core/CKILError.h"

// C2.8 port-rest R02. The messages are the original bytes (Latin-1, octal escapes); nothing displays them.

// 0x001032f8 CKILError_GetErrorMessage: a jump table over code - 0x30000 (41 entries), the rest the default.
const char* CKILError::GetErrorMessage(int32_t code) {
    switch (code) {
        case 0x30000:
            return "L'initialisation des libraries pour la gestion des pads a \351chou\351e";
        case 0x30001:
            return "La commande a mapp\351 est en dehors des possibilit\351s du pad";
        case 0x30002:
            return "La commande a mapp\351 est en dehors des possibilit\351s de la souris";
        case 0x30003:
            return "La commande a mapp\351 est en dehors des possibilit\351s du clavier";
        case 0x30005:
            return "Le nombre d'\351tat de retour du filtre \340 seuil est supp\351rieur au nombre maximum autoris\351 (par defaut:4)";
        case 0x30006:
            return "La cr\351ation du device8 par DirectInput a \351chou\351e";
        case 0x30007:
            return "La cr\351ation du clavier par DirectInput a \351chou\351e";
        case 0x30008:
            return "Le formattage des donn\351es pour le clavier par DirectInput a \351chou\351e";
        case 0x30009:
            return "L'initialisation du niveau de coop\351ration du clavier entre les applications par DirectInput a \351chou\351e";
        case 0x3000a:
            return "L'initialisation du clavier par DirectInput a \351chou\351e";
        case 0x3000b:
            return "L'initialisation des propri\351t\351s du clavier par DirectInput a \351chou\351e";
        case 0x3000c:
            return "La cr\351ation de la souris par DirectInput a \351chou\351e";
        case 0x3000d:
            return "Le formattage des donn\351es pour la souris par DirectInput a \351chou\351e";
        case 0x3000e:
            return "L'initialisation du niveau de coop\351ration de la souris entre les applications par DirectInput a \351chou\351e";
        case 0x3000f:
            return "L'initialisation de la souris par DirectInput a \351chou\351e";
        case 0x30010:
            return "L'initialisation des propri\351t\351s de la souris par DirectInput a \351chou\351e";
        case 0x30011:
            return "La cr\351ation du pad par DirectInput a \351chou\351e";
        case 0x30012:
            return "Le formattage des donn\351es pour le pad par DirectInput a \351chou\351e";
        case 0x30013:
            return "L'initialisation du niveau de coop\351ration du pad entre les applications par DirectInput a \351chou\351e";
        case 0x30014:
            return "L'\351num\351ration des possibilit\351s du pad a \351chou\351e";
        case 0x30015:
            return "L'initialisation du pad par DirectInput a \351chou\351e";
        case 0x30016:
            return "L'initialisation des propri\351t\351s du pad par DirectInput a \351chou\351e";
        case 0x30017:
            return "La cr\351ation des vibrations du pad par directinput a \351chou\351e";
        case 0x30018:
            return "L'ouverture des port des pads de la PS2 a \351chou\351e";
        case 0x30019:
            return "Le pad est d\351connect\351";
        case 0x3001a:
            return "Le pad n'est pas stable";
        case 0x3001c:
            return "Aucuns claviers trouv\351s";
        case 0x3001d:
            return "Clavier non cr\351\351";
        case 0x3001e:
            return "Donn\351es du clavier non r\351cup\351r\351es";
        case 0x3001f:
            return "Donn\351es du clavier non lues";
        case 0x30020:
            return "Aucunes souris trouv\351s";
        case 0x30021:
            return "Souris non cr\351\351";
        case 0x30022:
            return "Donn\351es de loa souris non r\351cup\351r\351es";
        case 0x30023:
            return "Donn\351es de la souris non lues";
        case 0x30024:
            return "Aucuns pads trouv\351s";
        case 0x30025:
            return "Pad non cr\351\351";
        case 0x30026:
            return "Donn\351es du pad non r\351cup\351r\351es";
        case 0x30027:
            return "Donn\351es du pad non lues";
        case 0x30028:
            return "Probleme lors de la sauvegarde de la configuration utilisateur";
        default:  // and the table entries that jump to it
            return "L'erreur n'est pas document\351e par le module KIL";
    }
}
