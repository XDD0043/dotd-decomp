// IKSerializable.cpp - out-of-line pieces of the root classes (the other shared stubs are inline in
// IKSerializable.h; their original copies live in the COMDAT block 0x990b00-0x991100).
#include "k2000/core/IKSerializable.h"

#include "k2000/misc/ClassManager.h"
#include "k2000/misc/Engine.h"

// 0x00990d58 IKSerializable_GetName
const char* IKSerializable::GetName() { return g_pEngine->m_classManager->GetObjectDebugName(this); }
