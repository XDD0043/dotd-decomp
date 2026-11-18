// Reconstructed original translation unit: 0x253e70-0x256d38 (GAME_TOC1, main_toc1), 13 functions, 8 live.
// Primary owner: Rijndael (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x253e70  Rijndael_GfMul_maybe  [dead]
//   [ ] 0x253ee8  Rijndael_AddRoundKey_maybe  [dead]
//   [ ] 0x253f48  Rijndael_SubBytes_maybe  [dead]
//   [ ] 0x253fa8  Rijndael_ShiftRows_maybe  [dead]
//   [ ] 0x2540a0  Rijndael_MixColumns_maybe  [dead: no pointer to the descriptors of the unit's only roots Crypto_DecryptAndVerifyBlock400_maybe 0x256d38 (0xb84a10) / Crypto_SelfTest_maybe 0x256f48 (0xb84a18) and no call to them (raw ELF scan, R08); every call to the AES / SHA-1 functions is from inside 0x2540a0-0x25a000]
//   [ ] 0x2544d0  Rijndael_InvMixColumns_maybe  [dead: no pointer to the descriptors of the unit's only roots Crypto_DecryptAndVerifyBlock400_maybe 0x256d38 (0xb84a10) / Crypto_SelfTest_maybe 0x256f48 (0xb84a18) and no call to them (raw ELF scan, R08); every call to the AES / SHA-1 functions is from inside 0x2540a0-0x25a000]
//   [ ] 0x254bd0  Rijndael_KeyExpansion_maybe  [dead: no pointer to the descriptors of the unit's only roots Crypto_DecryptAndVerifyBlock400_maybe 0x256d38 (0xb84a10) / Crypto_SelfTest_maybe 0x256f48 (0xb84a18) and no call to them (raw ELF scan, R08); every call to the AES / SHA-1 functions is from inside 0x2540a0-0x25a000]
//   [ ] 0x255128  Rijndael_Init  [dead: no pointer to the descriptors of the unit's only roots Crypto_DecryptAndVerifyBlock400_maybe 0x256d38 (0xb84a10) / Crypto_SelfTest_maybe 0x256f48 (0xb84a18) and no call to them (raw ELF scan, R08); every call to the AES / SHA-1 functions is from inside 0x2540a0-0x25a000]
//   [ ] 0x255390  Rijndael_DecryptBlock  [dead: no pointer to the descriptors of the unit's only roots Crypto_DecryptAndVerifyBlock400_maybe 0x256d38 (0xb84a10) / Crypto_SelfTest_maybe 0x256f48 (0xb84a18) and no call to them (raw ELF scan, R08); every call to the AES / SHA-1 functions is from inside 0x2540a0-0x25a000]
//   [ ] 0x2557a8  Rijndael_DecryptCBC_maybe  [dead: no pointer to the descriptors of the unit's only roots Crypto_DecryptAndVerifyBlock400_maybe 0x256d38 (0xb84a10) / Crypto_SelfTest_maybe 0x256f48 (0xb84a18) and no call to them (raw ELF scan, R08); every call to the AES / SHA-1 functions is from inside 0x2540a0-0x25a000]
//   [ ] 0x255a20  Rijndael_EncryptBlock_maybe  [dead: no pointer to the descriptors of the unit's only roots Crypto_DecryptAndVerifyBlock400_maybe 0x256d38 (0xb84a10) / Crypto_SelfTest_maybe 0x256f48 (0xb84a18) and no call to them (raw ELF scan, R08); every call to the AES / SHA-1 functions is from inside 0x2540a0-0x25a000]
//   [ ] 0x255e08  Rijndael_EncryptCBC_maybe  [dead]
//   [ ] 0x256018  Rijndael_SelfTest_maybe  [dead: no pointer to the descriptors of the unit's only roots Crypto_DecryptAndVerifyBlock400_maybe 0x256d38 (0xb84a10) / Crypto_SelfTest_maybe 0x256f48 (0xb84a18) and no call to them (raw ELF scan, R08); every call to the AES / SHA-1 functions is from inside 0x2540a0-0x25a000]
