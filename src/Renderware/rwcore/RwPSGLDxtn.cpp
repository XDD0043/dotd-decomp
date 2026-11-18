// RwPSGLDxtn.cpp - see RwPSGLDxtn.h. libtxc_dxtn 1.0 (Copyright (C) 2004 Roland Scheidegger, MIT licence: "Permission
// is hereby granted, free of charge, to any person obtaining a copy of this software ... THE SOFTWARE IS PROVIDED "AS
// IS", WITHOUT WARRANTY OF ANY KIND"), as the PS3 build has it: integer arithmetic only (C's promotions: every byte
// operand widens to int, the errors are unsigned), the luminance weights 4 / 16 / 1, the alpha cut 127.
#include "Renderware/rwcore/RwPSGLDxtn.h"

#include <cstdio>
#include <cstdlib>

namespace {

constexpr int kRedWeight = 4;
constexpr int kGreenWeight = 16;
constexpr int kBlueWeight = 1;
constexpr int kAlphaCut = 127;

typedef uint8_t SrcColors[4][4][4];

int Packed565(const uint8_t* c) { return (c[0] & 0xf8) << 8 | (c[1] & 0xfc) << 3 | c[2] >> 3; }

// fancybasecolorsearch: the two base colours refined by the mean signed error of the pixels mapped to each (with the
// 4-colour encoding: weights 3 / 2 / 1 per end), then pushed apart when they would round to the same 565 value, and
// ordered (the smaller packed value first).
void FancyBaseColorSearch(SrcColors srccolors, uint8_t* bestcolor[2], int numxpixels, int numypixels) {
    int blockerrlin[2][3];
    uint8_t nrcolor[2];
    int pixerrorcolorbest[3] = {0, 0, 0};
    uint8_t enc = 0;
    uint8_t cv[4][4];
    uint8_t testcolor[2][3];

    if (Packed565(bestcolor[0]) < Packed565(bestcolor[1])) {
        for (int i = 0; i < 3; ++i) {
            testcolor[0][i] = bestcolor[0][i];
            testcolor[1][i] = bestcolor[1][i];
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            testcolor[1][i] = bestcolor[0][i];
            testcolor[0][i] = bestcolor[1][i];
        }
    }
    for (int i = 0; i < 3; ++i) {
        cv[0][i] = testcolor[0][i];
        cv[1][i] = testcolor[1][i];
        cv[2][i] = static_cast<uint8_t>((testcolor[0][i] * 2 + testcolor[1][i]) / 3);
        cv[3][i] = static_cast<uint8_t>((testcolor[0][i] + testcolor[1][i] * 2) / 3);
    }
    for (int j = 0; j < 2; ++j)
        for (int z = 0; z < 3; ++z) blockerrlin[j][z] = 0;
    nrcolor[0] = 0;
    nrcolor[1] = 0;
    for (int j = 0; j < numypixels; ++j) {
        for (int i = 0; i < numxpixels; ++i) {
            uint32_t pixerrorbest = 0xffffffffu;
            for (int colors = 0; colors < 4; ++colors) {
                int colordist = srccolors[j][i][0] - cv[colors][0];
                uint32_t pixerror = static_cast<uint32_t>(colordist * colordist * kRedWeight);
                const uint32_t pixerrorred = static_cast<uint32_t>(colordist);
                colordist = srccolors[j][i][1] - cv[colors][1];
                pixerror += static_cast<uint32_t>(colordist * colordist * kGreenWeight);
                const uint32_t pixerrorgreen = static_cast<uint32_t>(colordist);
                colordist = srccolors[j][i][2] - cv[colors][2];
                pixerror += static_cast<uint32_t>(colordist * colordist * kBlueWeight);
                const uint32_t pixerrorblue = static_cast<uint32_t>(colordist);
                if (pixerror < pixerrorbest) {
                    enc = static_cast<uint8_t>(colors);
                    pixerrorbest = pixerror;
                    pixerrorcolorbest[0] = static_cast<int>(pixerrorred);
                    pixerrorcolorbest[1] = static_cast<int>(pixerrorgreen);
                    pixerrorcolorbest[2] = static_cast<int>(pixerrorblue);
                }
            }
            if (enc == 0) {
                for (int z = 0; z < 3; ++z) blockerrlin[0][z] += 3 * pixerrorcolorbest[z];
                nrcolor[0] = static_cast<uint8_t>(nrcolor[0] + 3);
            } else if (enc == 2) {
                for (int z = 0; z < 3; ++z) blockerrlin[0][z] += 2 * pixerrorcolorbest[z];
                nrcolor[0] = static_cast<uint8_t>(nrcolor[0] + 2);
                for (int z = 0; z < 3; ++z) blockerrlin[1][z] += 1 * pixerrorcolorbest[z];
                nrcolor[1] = static_cast<uint8_t>(nrcolor[1] + 1);
            } else if (enc == 3) {
                for (int z = 0; z < 3; ++z) blockerrlin[0][z] += 1 * pixerrorcolorbest[z];
                nrcolor[0] = static_cast<uint8_t>(nrcolor[0] + 1);
                for (int z = 0; z < 3; ++z) blockerrlin[1][z] += 2 * pixerrorcolorbest[z];
                nrcolor[1] = static_cast<uint8_t>(nrcolor[1] + 2);
            } else if (enc == 1) {
                for (int z = 0; z < 3; ++z) blockerrlin[1][z] += 3 * pixerrorcolorbest[z];
                nrcolor[1] = static_cast<uint8_t>(nrcolor[1] + 3);
            }
        }
    }
    if (nrcolor[0] == 0) nrcolor[0] = 1;
    if (nrcolor[1] == 0) nrcolor[1] = 1;
    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < 3; ++i) {
            const int newvalue = testcolor[j][i] + blockerrlin[j][i] / nrcolor[j];  // divw: truncated
            if (newvalue <= 0) {
                testcolor[j][i] = 0;
            } else if (newvalue >= 255) {
                testcolor[j][i] = 255;
            } else {
                testcolor[j][i] = static_cast<uint8_t>(newvalue);
            }
        }
    }

    if (std::abs(testcolor[0][0] - testcolor[1][0]) < 8 && std::abs(testcolor[0][1] - testcolor[1][1]) < 4 &&
        std::abs(testcolor[0][2] - testcolor[1][2]) < 8) {
        // Both colours so close that they might round to the same 16-bit value.
        const uint8_t coldiffred = static_cast<uint8_t>(std::abs(testcolor[0][0] - testcolor[1][0]));
        const uint8_t coldiffgreen = static_cast<uint8_t>(2 * std::abs(testcolor[0][1] - testcolor[1][1]));
        const uint8_t coldiffblue = static_cast<uint8_t>(std::abs(testcolor[0][2] - testcolor[1][2]));
        uint8_t coldiffmax = coldiffred;
        if (coldiffmax < coldiffgreen) coldiffmax = coldiffgreen;
        if (coldiffmax < coldiffblue) coldiffmax = coldiffblue;
        if (coldiffmax > 0) {
            uint8_t factor;
            if (coldiffmax > 4) {
                factor = 2;
            } else if (coldiffmax > 2) {
                factor = 3;
            } else {
                factor = 4;
            }
            uint8_t ind0, ind1;
            if (testcolor[1][1] >= testcolor[0][1]) {
                ind1 = 1;
                ind0 = 0;
            } else {
                ind1 = 0;
                ind0 = 1;
            }
            if (testcolor[ind1][1] + factor * coldiffgreen <= 255) {
                testcolor[ind1][1] = static_cast<uint8_t>(testcolor[ind1][1] + factor * coldiffgreen);
            } else {
                testcolor[ind1][1] = 255;
            }
            // BUG(original): the red test subtracts the other colour's green.
            if (testcolor[ind1][0] - testcolor[ind0][1] > 0) {
                if (testcolor[ind1][0] + factor * coldiffred <= 255) {
                    testcolor[ind1][0] = static_cast<uint8_t>(testcolor[ind1][0] + factor * coldiffred);
                } else {
                    testcolor[ind1][0] = 255;
                }
            } else {
                if (testcolor[ind0][0] + factor * coldiffred <= 255) {
                    testcolor[ind0][0] = static_cast<uint8_t>(testcolor[ind0][0] + factor * coldiffred);
                } else {
                    testcolor[ind0][0] = 255;
                }
            }
            if (testcolor[ind1][2] - testcolor[ind0][2] > 0) {
                if (testcolor[ind1][2] + factor * coldiffblue <= 255) {
                    testcolor[ind1][2] = static_cast<uint8_t>(testcolor[ind1][2] + factor * coldiffblue);
                } else {
                    testcolor[ind1][2] = 255;
                }
            } else {
                if (testcolor[ind0][2] + factor * coldiffblue <= 255) {
                    testcolor[ind0][2] = static_cast<uint8_t>(testcolor[ind0][2] + factor * coldiffblue);
                } else {
                    testcolor[ind0][2] = 255;
                }
            }
        }
    }

    // BUG(original): the second packed value is shifted right by 3 as a whole (a misplaced parenthesis).
    if (Packed565(testcolor[0]) < (((testcolor[1][0] & 0xf8) << 8 | (testcolor[1][1] & 0xfc) << 3 | testcolor[1][2]) >> 3)) {
        for (int i = 0; i < 3; ++i) {
            bestcolor[0][i] = testcolor[0][i];
            bestcolor[1][i] = testcolor[1][i];
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            bestcolor[0][i] = testcolor[1][i];
            bestcolor[1][i] = testcolor[0][i];
        }
    }
}

// storedxtencodedblock: the base colours cut to 565, color0 >= color1, every pixel's nearest of the four colours; for
// DXT1 also the three-colour encoding (the mean as colour 2, and for RGBA DXT1 the transparent index 3 for pixels at or
// below the alpha cut), kept when its error is smaller or the block has alpha.
void StoreDxtEncodedBlock(uint8_t* blkaddr, SrcColors srccolors, uint8_t* bestcolor[2], int numxpixels, int numypixels,
                          uint32_t type, bool haveAlpha) {
    uint32_t bits = 0, bits2 = 0;
    uint8_t enc = 0;
    uint8_t cv[4][4];

    bestcolor[0][0] = bestcolor[0][0] & 0xf8;
    bestcolor[0][1] = bestcolor[0][1] & 0xfc;
    bestcolor[0][2] = bestcolor[0][2] & 0xf8;
    bestcolor[1][0] = bestcolor[1][0] & 0xf8;
    bestcolor[1][1] = bestcolor[1][1] & 0xfc;
    bestcolor[1][2] = bestcolor[1][2] & 0xf8;

    uint16_t color0 = static_cast<uint16_t>(bestcolor[0][0] << 8 | bestcolor[0][1] << 3 | bestcolor[0][2] >> 3);
    uint16_t color1 = static_cast<uint16_t>(bestcolor[1][0] << 8 | bestcolor[1][1] << 3 | bestcolor[1][2] >> 3);
    if (color0 < color1) {
        const uint16_t tempcolor = color0;
        color0 = color1;
        color1 = tempcolor;
        uint8_t* colorptr = bestcolor[0];
        bestcolor[0] = bestcolor[1];
        bestcolor[1] = colorptr;
    }
    for (int i = 0; i < 3; ++i) {
        cv[0][i] = bestcolor[0][i];
        cv[1][i] = bestcolor[1][i];
        cv[2][i] = static_cast<uint8_t>((bestcolor[0][i] * 2 + bestcolor[1][i]) / 3);
        cv[3][i] = static_cast<uint8_t>((bestcolor[0][i] + bestcolor[1][i] * 2) / 3);
    }

    uint32_t testerror = 0;
    for (int j = 0; j < numypixels; ++j) {
        for (int i = 0; i < numxpixels; ++i) {
            uint32_t pixerrorbest = 0xffffffffu;
            for (int colors = 0; colors < 4; ++colors) {
                int colordist = srccolors[j][i][0] - cv[colors][0];
                uint32_t pixerror = static_cast<uint32_t>(colordist * colordist * kRedWeight);
                colordist = srccolors[j][i][1] - cv[colors][1];
                pixerror += static_cast<uint32_t>(colordist * colordist * kGreenWeight);
                colordist = srccolors[j][i][2] - cv[colors][2];
                pixerror += static_cast<uint32_t>(colordist * colordist * kBlueWeight);
                if (pixerror < pixerrorbest) {
                    pixerrorbest = pixerror;
                    enc = static_cast<uint8_t>(colors);
                }
            }
            testerror += pixerrorbest;
            bits |= static_cast<uint32_t>(enc) << (2 * (j * 4 + i));
        }
    }
    uint32_t testerror2;
    if (type == kGlCompressedRgbS3tcDxt1 || type == kGlCompressedRgbaS3tcDxt1) {
        for (int i = 0; i < 3; ++i) {
            cv[2][i] = static_cast<uint8_t>((bestcolor[0][i] + bestcolor[1][i]) / 2);
            cv[3][i] = 0;
        }
        testerror2 = 0;
        for (int j = 0; j < numypixels; ++j) {
            for (int i = 0; i < numxpixels; ++i) {
                uint32_t pixerrorbest = 0xffffffffu;
                if (type == kGlCompressedRgbaS3tcDxt1 && srccolors[j][i][3] <= kAlphaCut) {
                    enc = 3;
                    pixerrorbest = 0;
                } else {
                    for (int colors = 0; colors < 3; ++colors) {
                        int colordist = srccolors[j][i][0] - cv[colors][0];
                        uint32_t pixerror = static_cast<uint32_t>(colordist * colordist * kRedWeight);
                        colordist = srccolors[j][i][1] - cv[colors][1];
                        pixerror += static_cast<uint32_t>(colordist * colordist * kGreenWeight);
                        colordist = srccolors[j][i][2] - cv[colors][2];
                        pixerror += static_cast<uint32_t>(colordist * colordist * kBlueWeight);
                        if (pixerror < pixerrorbest) {
                            pixerrorbest = pixerror;
                            enc = static_cast<uint8_t>(colors > 1 ? colors : colors ^ 1);  // the colours swap below
                        }
                    }
                }
                testerror2 += pixerrorbest;
                bits2 |= static_cast<uint32_t>(enc) << (2 * (j * 4 + i));
            }
        }
    } else {
        testerror2 = 0xffffffffu;
    }

    if (testerror > testerror2 || haveAlpha) {
        *blkaddr++ = static_cast<uint8_t>(color1 & 0xff);
        *blkaddr++ = static_cast<uint8_t>(color1 >> 8);
        *blkaddr++ = static_cast<uint8_t>(color0 & 0xff);
        *blkaddr++ = static_cast<uint8_t>(color0 >> 8);
        *blkaddr++ = static_cast<uint8_t>(bits2 & 0xff);
        *blkaddr++ = static_cast<uint8_t>((bits2 >> 8) & 0xff);
        *blkaddr++ = static_cast<uint8_t>((bits2 >> 16) & 0xff);
        *blkaddr = static_cast<uint8_t>(bits2 >> 24);
    } else {
        *blkaddr++ = static_cast<uint8_t>(color0 & 0xff);
        *blkaddr++ = static_cast<uint8_t>(color0 >> 8);
        *blkaddr++ = static_cast<uint8_t>(color1 & 0xff);
        *blkaddr++ = static_cast<uint8_t>(color1 >> 8);
        *blkaddr++ = static_cast<uint8_t>(bits & 0xff);
        *blkaddr++ = static_cast<uint8_t>((bits >> 8) & 0xff);
        *blkaddr++ = static_cast<uint8_t>((bits >> 16) & 0xff);
        *blkaddr = static_cast<uint8_t>(bits >> 24);
    }
}

// 0x00741b98 libdxtn_encodeColorBlock_maybe (encodedxtcolorblockfaster): the darkest and the brightest pixel (weighted
// squared length; for RGBA DXT1 only the pixels above the alpha cut, the others mark the block as having alpha) as
// base colours, refined and stored.
void EncodeDxtColorBlockFaster(uint8_t* blkaddr, SrcColors srccolors, int numxpixels, int numypixels, uint32_t type) {
    uint8_t* bestcolor[2];
    uint8_t basecolors[2][3];
    bool haveAlpha = false;
    uint32_t lowcv = static_cast<uint32_t>(srccolors[0][0][0] * srccolors[0][0][0] * kRedWeight +
                                           srccolors[0][0][1] * srccolors[0][0][1] * kGreenWeight +
                                           srccolors[0][0][2] * srccolors[0][0][2] * kBlueWeight);
    uint32_t highcv = lowcv;
    bestcolor[0] = bestcolor[1] = srccolors[0][0];
    for (uint8_t j = 0; j < numypixels; ++j) {
        for (uint8_t i = 0; i < numxpixels; ++i) {
            if (type != kGlCompressedRgbaS3tcDxt1 || srccolors[j][i][3] > kAlphaCut) {
                const uint32_t testcv = static_cast<uint32_t>(srccolors[j][i][0] * srccolors[j][i][0] * kRedWeight +
                                                              srccolors[j][i][1] * srccolors[j][i][1] * kGreenWeight +
                                                              srccolors[j][i][2] * srccolors[j][i][2] * kBlueWeight);
                if (testcv > highcv) {
                    highcv = testcv;
                    bestcolor[1] = srccolors[j][i];
                } else if (testcv < lowcv) {
                    lowcv = testcv;
                    bestcolor[0] = srccolors[j][i];
                }
            } else {
                haveAlpha = true;
            }
        }
    }
    for (int j = 0; j < 2; ++j)
        for (int i = 0; i < 3; ++i) basecolors[j][i] = bestcolor[j][i];
    bestcolor[0] = basecolors[0];
    bestcolor[1] = basecolors[1];
    FancyBaseColorSearch(srccolors, bestcolor, numxpixels, numypixels);
    StoreDxtEncodedBlock(blkaddr, srccolors, bestcolor, numxpixels, numypixels, type, haveAlpha);
}

void WriteDxt5EncodedAlphaBlock(uint8_t* blkaddr, uint8_t alphabase1, uint8_t alphabase2, const uint8_t alphaenc[16]) {
    *blkaddr++ = alphabase1;
    *blkaddr++ = alphabase2;
    *blkaddr++ = static_cast<uint8_t>(alphaenc[0] | (alphaenc[1] << 3) | ((alphaenc[2] & 3) << 6));
    *blkaddr++ = static_cast<uint8_t>((alphaenc[2] >> 2) | (alphaenc[3] << 1) | (alphaenc[4] << 4) | ((alphaenc[5] & 1) << 7));
    *blkaddr++ = static_cast<uint8_t>((alphaenc[5] >> 1) | (alphaenc[6] << 2) | (alphaenc[7] << 5));
    *blkaddr++ = static_cast<uint8_t>(alphaenc[8] | (alphaenc[9] << 3) | ((alphaenc[10] & 3) << 6));
    *blkaddr++ = static_cast<uint8_t>((alphaenc[10] >> 2) | (alphaenc[11] << 1) | (alphaenc[12] << 4) | ((alphaenc[13] & 1) << 7));
    *blkaddr++ = static_cast<uint8_t>((alphaenc[13] >> 1) | (alphaenc[14] << 2) | (alphaenc[15] << 5));
}

// encodedxt5alpha: three candidate alpha encodings (8 alphas between the extremes, 0 and 255 included when present;
// 6 alphas between the extremes other than 0 / 255, with 0 and 255 exact; the same refined by the mean errors), the
// one with the smallest squared error written.
void EncodeDxt5Alpha(uint8_t* blkaddr, SrcColors srccolors, int numxpixels, int numypixels) {
    uint8_t alphabase[2], alphause[2];
    int16_t alphatest[2] = {0, 0};
    uint8_t acutValues[7];
    uint8_t alphaenc1[16], alphaenc2[16], alphaenc3[16];
    bool alphaabsmin = false;
    bool alphaabsmax = false;
    int16_t alphadist;

    alphabase[0] = 0xff;
    alphabase[1] = 0x0;
    for (uint8_t j = 0; j < numypixels; ++j) {
        for (uint8_t i = 0; i < numxpixels; ++i) {
            if (srccolors[j][i][3] == 0) {
                alphaabsmin = true;
            } else if (srccolors[j][i][3] == 255) {
                alphaabsmax = true;
            } else {
                if (srccolors[j][i][3] > alphabase[1]) alphabase[1] = srccolors[j][i][3];
                if (srccolors[j][i][3] < alphabase[0]) alphabase[0] = srccolors[j][i][3];
            }
        }
    }

    if (alphabase[0] > alphabase[1] && !(alphaabsmin && alphaabsmax)) {
        // Every alpha 0 or every alpha 255: the alpha itself and all indices 0. BUG(original): the second alpha byte
        // is left as the destination buffer holds it (the PS3's malloc'd block; the decoders read index 0 only).
        *blkaddr++ = srccolors[0][0][3];
        blkaddr++;
        for (int k = 0; k < 6; ++k) *blkaddr++ = 0;
        return;
    }

    uint32_t alphablockerror1 = 0x0;
    uint32_t alphablockerror2 = 0xffffffffu;
    uint32_t alphablockerror3 = 0xffffffffu;
    alphause[0] = alphaabsmin ? 0 : alphabase[0];
    alphause[1] = alphaabsmax ? 255 : alphabase[1];
    for (uint8_t aindex = 0; aindex < 7; ++aindex) {
        acutValues[aindex] = static_cast<uint8_t>(
            (alphause[0] * (2 * aindex + 1) + alphause[1] * (14 - (2 * aindex + 1))) / 14);
    }
    for (uint8_t j = 0; j < numypixels; ++j) {
        for (uint8_t i = 0; i < numxpixels; ++i) {
            const uint8_t a = srccolors[j][i][3];
            uint8_t& e = alphaenc1[4 * j + i];
            if (a > acutValues[0]) {
                e = 0;
                alphadist = static_cast<int16_t>(a - alphause[1]);
            } else if (a > acutValues[1]) {
                e = 2;
                alphadist = static_cast<int16_t>(a - (alphause[1] * 6 + alphause[0] * 1) / 7);
            } else if (a > acutValues[2]) {
                e = 3;
                alphadist = static_cast<int16_t>(a - (alphause[1] * 5 + alphause[0] * 2) / 7);
            } else if (a > acutValues[3]) {
                e = 4;
                alphadist = static_cast<int16_t>(a - (alphause[1] * 4 + alphause[0] * 3) / 7);
            } else if (a > acutValues[4]) {
                e = 5;
                alphadist = static_cast<int16_t>(a - (alphause[1] * 3 + alphause[0] * 4) / 7);
            } else if (a > acutValues[5]) {
                e = 6;
                alphadist = static_cast<int16_t>(a - (alphause[1] * 2 + alphause[0] * 5) / 7);
            } else if (a > acutValues[6]) {
                e = 7;
                alphadist = static_cast<int16_t>(a - (alphause[1] * 1 + alphause[0] * 6) / 7);
            } else {
                e = 1;
                alphadist = static_cast<int16_t>(a - alphause[0]);
            }
            alphablockerror1 += static_cast<uint32_t>(alphadist * alphadist);
        }
    }

    if (alphablockerror1 >= 32) {
        alphablockerror2 = 0;
        for (uint8_t aindex = 0; aindex < 5; ++aindex) {
            acutValues[aindex] = static_cast<uint8_t>(
                (alphabase[0] * (10 - (2 * aindex + 1)) + alphabase[1] * (2 * aindex + 1)) / 10);
        }
        for (uint8_t j = 0; j < numypixels; ++j) {
            for (uint8_t i = 0; i < numxpixels; ++i) {
                const uint8_t a = srccolors[j][i][3];
                uint8_t& e = alphaenc2[4 * j + i];
                if (a == 0) {
                    e = 6;
                    alphadist = 0;
                } else if (a == 255) {
                    e = 7;
                    alphadist = 0;
                } else if (a <= acutValues[0]) {
                    e = 0;
                    alphadist = static_cast<int16_t>(a - alphabase[0]);
                } else if (a <= acutValues[1]) {
                    e = 2;
                    alphadist = static_cast<int16_t>(a - (alphabase[0] * 4 + alphabase[1] * 1) / 5);
                } else if (a <= acutValues[2]) {
                    e = 3;
                    alphadist = static_cast<int16_t>(a - (alphabase[0] * 3 + alphabase[1] * 2) / 5);
                } else if (a <= acutValues[3]) {
                    e = 4;
                    alphadist = static_cast<int16_t>(a - (alphabase[0] * 2 + alphabase[1] * 3) / 5);
                } else if (a <= acutValues[4]) {
                    e = 5;
                    alphadist = static_cast<int16_t>(a - (alphabase[0] * 1 + alphabase[1] * 4) / 5);
                } else {
                    e = 1;
                    alphadist = static_cast<int16_t>(a - alphabase[1]);
                }
                alphablockerror2 += static_cast<uint32_t>(alphadist * alphadist);
            }
        }

        if (alphablockerror2 > 96 && alphablockerror1 > 96) {
            int16_t blockerrlin1 = 0;
            int16_t blockerrlin2 = 0;
            uint8_t nralphainrangelow = 0;
            uint8_t nralphainrangehigh = 0;
            alphatest[0] = 0xff;
            alphatest[1] = 0x0;
            for (uint8_t j = 0; j < numypixels; ++j) {
                for (uint8_t i = 0; i < numxpixels; ++i) {
                    const uint8_t a = srccolors[j][i][3];
                    if (a > alphatest[1] && a < (255 - (alphabase[1] - alphabase[0]) / 28)) alphatest[1] = a;
                    if (a < alphatest[0] && a > (alphabase[1] - alphabase[0]) / 28) alphatest[0] = a;
                }
            }
            if (alphatest[1] <= alphatest[0]) {
                alphatest[0] = 1;
                alphatest[1] = 254;
            }
            for (uint8_t aindex = 0; aindex < 5; ++aindex) {
                acutValues[aindex] = static_cast<uint8_t>(
                    (alphatest[0] * (10 - (2 * aindex + 1)) + alphatest[1] * (2 * aindex + 1)) / 10);
            }
            for (uint8_t j = 0; j < numypixels; ++j) {
                for (uint8_t i = 0; i < numxpixels; ++i) {
                    const uint8_t a = srccolors[j][i][3];
                    if (a <= alphatest[0] / 2) {
                    } else if (a > (255 + alphatest[1]) / 2) {
                    } else if (a <= acutValues[0]) {
                        blockerrlin1 = static_cast<int16_t>(blockerrlin1 + (a - alphatest[0]));
                        nralphainrangelow = static_cast<uint8_t>(nralphainrangelow + 1);
                    } else if (a <= acutValues[4]) {
                        // acutValues[1..4]: the interpolated alphas 4:1, 3:2, 2:3, 1:4 (fifths).
                        int k = 1;
                        while (k < 4 && a > acutValues[k]) ++k;
                        const int v = (alphatest[0] * (5 - k) + alphatest[1] * k) / 5;
                        blockerrlin1 = static_cast<int16_t>(blockerrlin1 + (a - v));
                        blockerrlin2 = static_cast<int16_t>(blockerrlin2 + (a - v));
                        nralphainrangelow = static_cast<uint8_t>(nralphainrangelow + 1);
                        nralphainrangehigh = static_cast<uint8_t>(nralphainrangehigh + 1);
                    } else {
                        blockerrlin2 = static_cast<int16_t>(blockerrlin2 + (a - alphatest[1]));
                        nralphainrangehigh = static_cast<uint8_t>(nralphainrangehigh + 1);
                    }
                }
            }
            if (nralphainrangelow == 0) nralphainrangelow = 1;
            if (nralphainrangehigh == 0) nralphainrangehigh = 1;
            alphatest[0] = static_cast<int16_t>(alphatest[0] + blockerrlin1 / nralphainrangelow);
            if (alphatest[0] < 0) alphatest[0] = 0;
            alphatest[1] = static_cast<int16_t>(alphatest[1] + blockerrlin2 / nralphainrangehigh);
            if (alphatest[1] > 255) alphatest[1] = 255;

            alphablockerror3 = 0;
            for (uint8_t aindex = 0; aindex < 5; ++aindex) {
                acutValues[aindex] = static_cast<uint8_t>(
                    (alphatest[0] * (10 - (2 * aindex + 1)) + alphatest[1] * (2 * aindex + 1)) / 10);
            }
            for (uint8_t j = 0; j < numypixels; ++j) {
                for (uint8_t i = 0; i < numxpixels; ++i) {
                    const uint8_t a = srccolors[j][i][3];
                    uint8_t& e = alphaenc3[4 * j + i];
                    if (a <= alphatest[0] / 2) {
                        e = 6;
                        alphadist = a;
                    } else if (a > (255 + alphatest[1]) / 2) {
                        e = 7;
                        alphadist = static_cast<int16_t>(255 - a);
                    } else if (a <= acutValues[0]) {
                        e = 0;
                        alphadist = static_cast<int16_t>(a - alphatest[0]);
                    } else if (a <= acutValues[1]) {
                        e = 2;
                        alphadist = static_cast<int16_t>(a - (alphatest[0] * 4 + alphatest[1] * 1) / 5);
                    } else if (a <= acutValues[2]) {
                        e = 3;
                        alphadist = static_cast<int16_t>(a - (alphatest[0] * 3 + alphatest[1] * 2) / 5);
                    } else if (a <= acutValues[3]) {
                        e = 4;
                        alphadist = static_cast<int16_t>(a - (alphatest[0] * 2 + alphatest[1] * 3) / 5);
                    } else if (a <= acutValues[4]) {
                        e = 5;
                        alphadist = static_cast<int16_t>(a - (alphatest[0] * 1 + alphatest[1] * 4) / 5);
                    } else {
                        e = 1;
                        alphadist = static_cast<int16_t>(a - alphatest[1]);
                    }
                    alphablockerror3 += static_cast<uint32_t>(alphadist * alphadist);
                }
            }
        }
    }
    if (alphablockerror1 <= alphablockerror2 && alphablockerror1 <= alphablockerror3) {
        WriteDxt5EncodedAlphaBlock(blkaddr, alphause[1], alphause[0], alphaenc1);
    } else if (alphablockerror2 <= alphablockerror3) {
        WriteDxt5EncodedAlphaBlock(blkaddr, alphabase[0], alphabase[1], alphaenc2);
    } else {
        WriteDxt5EncodedAlphaBlock(blkaddr, static_cast<uint8_t>(alphatest[0]), static_cast<uint8_t>(alphatest[1]),
                                   alphaenc3);
    }
}

// extractsrccolors: one block's pixels (rows `srcRowStride` pixels apart).
void ExtractSrcColors(SrcColors srcpixels, const uint8_t* srcaddr, int srcRowStride, int numxpixels, int numypixels,
                      int comps) {
    for (uint8_t j = 0; j < numypixels; ++j) {
        const uint8_t* curaddr = srcaddr + j * srcRowStride * comps;
        for (uint8_t i = 0; i < numxpixels; ++i)
            for (uint8_t c = 0; c < comps; ++c) srcpixels[j][i][c] = *curaddr++;  // / (CHAN_MAX / 255)
    }
}

}  // namespace

// 0x00743020 tx_compress_dxtn
void tx_compress_dxtn(int32_t srccomps, int32_t width, int32_t height, const uint8_t* srcPixData, uint32_t destFormat,
                      uint8_t* dest) {
    uint8_t* blkaddr = dest;
    // The block buffer keeps a partial block's unused pixels from the previous block (nothing reads them; zeroed here
    // for the first).
    uint8_t srcpixels[4][4][4] = {};
    switch (destFormat) {
        case kGlCompressedRgbS3tcDxt1:
        case kGlCompressedRgbaS3tcDxt1:
            for (int32_t j = 0; j < height; j += 4) {
                const int numypixels = height > j + 3 ? 4 : height - j;
                const uint8_t* srcaddr = srcPixData + j * width * srccomps;
                for (int32_t i = 0; i < width; i += 4) {
                    const int numxpixels = width > i + 3 ? 4 : width - i;
                    ExtractSrcColors(srcpixels, srcaddr, width, numxpixels, numypixels, srccomps);
                    EncodeDxtColorBlockFaster(blkaddr, srcpixels, numxpixels, numypixels, destFormat);
                    srcaddr += srccomps * numxpixels;
                    blkaddr += 8;
                }
            }
            break;
        case kGlCompressedRgbaS3tcDxt3:
            for (int32_t j = 0; j < height; j += 4) {
                const int numypixels = height > j + 3 ? 4 : height - j;
                const uint8_t* srcaddr = srcPixData + j * width * srccomps;
                for (int32_t i = 0; i < width; i += 4) {
                    const int numxpixels = width > i + 3 ? 4 : width - i;
                    ExtractSrcColors(srcpixels, srcaddr, width, numxpixels, numypixels, srccomps);
                    for (int row = 0; row < 4; ++row) {
                        *blkaddr++ = static_cast<uint8_t>((srcpixels[row][0][3] >> 4) | (srcpixels[row][1][3] & 0xf0));
                        *blkaddr++ = static_cast<uint8_t>((srcpixels[row][2][3] >> 4) | (srcpixels[row][3][3] & 0xf0));
                    }
                    EncodeDxtColorBlockFaster(blkaddr, srcpixels, numxpixels, numypixels, destFormat);
                    srcaddr += srccomps * numxpixels;
                    blkaddr += 8;
                }
            }
            break;
        case kGlCompressedRgbaS3tcDxt5:
            for (int32_t j = 0; j < height; j += 4) {
                const int numypixels = height > j + 3 ? 4 : height - j;
                const uint8_t* srcaddr = srcPixData + j * width * srccomps;
                for (int32_t i = 0; i < width; i += 4) {
                    const int numxpixels = width > i + 3 ? 4 : width - i;
                    ExtractSrcColors(srcpixels, srcaddr, width, numxpixels, numypixels, srccomps);
                    EncodeDxt5Alpha(blkaddr, srcpixels, numxpixels, numypixels);
                    EncodeDxtColorBlockFaster(blkaddr + 8, srcpixels, numxpixels, numypixels, destFormat);
                    srcaddr += srccomps * numxpixels;
                    blkaddr += 16;
                }
            }
            break;
        default:
            std::fprintf(stderr, "tx_compress_dxtn: format 0x%x not supported\n", destFormat);  // TOC -0x3468
            return;
    }
}
