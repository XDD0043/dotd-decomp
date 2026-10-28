// rt2d_test - C1.5 family B: the Rt2d (tool/2d) port. Hand-built paths with exact expected nodes, the
// triangulator; then, after BootToFrontEnd, the press-start movie's (#3) scene as the real readers build
// it, compared with the values read live from RPCS3 at the main menu (2026-10-18: the scene tree, the 16
// shape reps' RpGeometry: counts, format, vertices, triangles, bounding sphere, colour caches); the fonts
// (CManager2d's three, the dictionary); and one render of the scene and of a text through the recorders.
#include <cmath>
#include <cstdio>
#include <cstring>

#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rt2d/Rt2dInternal.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "boot_helper.h"
#include "k2000/graphical/ui/CKFlashManager.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/misc/Engine.h"

namespace {

uint32_t Bits(float f) {
    uint32_t u;
    std::memcpy(&u, &f, 4);
    return u;
}

rt2dPathNode* Nodes(Rt2dPath* path, RwInt32* count) {
    if (path->numSegment == -1) {
        *count = _rwSListGetNumEntries(static_cast<RwSList*>(path->segments));
        return static_cast<rt2dPathNode*>(_rwSListGetArray(static_cast<RwSList*>(path->segments)));
    }
    *count = path->numSegment;
    return static_cast<rt2dPathNode*>(path->segments);
}

// Rt2dPathRect: five nodes (the close repeats the first), lengths 2, 3, 5, 6, unit normals with the
// miters (1, -1) / (1, 1) / (-1, 1) at the corners and (-1, -1) shared by the first and last node.
void TestRectPath() {
    Rt2dPath* path = Rt2dPathCreate();
    Rt2dPathRect(path, 0.0f, 0.0f, 2.0f, 1.0f);
    RwInt32 count = 0;
    rt2dPathNode* n = Nodes(path, &count);
    C15_CHECK(count == 5);
    C15_CHECK(path->closed == 1 && path->flat == 1);
    if (count == 5) {
        const float expect[5][5] = {{0, 0, -1, -1, 0}, {2, 0, 1, -1, 2}, {2, 1, 1, 1, 3}, {0, 1, -1, 1, 5}, {0, 0, -1, -1, 6}};
        for (int i = 0; i < 5; ++i) {
            C15_CHECK(n[i].pos.x == expect[i][0] && n[i].pos.y == expect[i][1]);
            C15_CHECK(n[i].normal.x == expect[i][2] && n[i].normal.y == expect[i][3]);
            C15_CHECK(n[i].dist == expect[i][4]);
        }
        C15_CHECK(n[0].type == rt2dMOVE && n[1].type == rt2dLINE && n[4].type == rt2dLINE);
    }
    // Unlock: an array of the same five nodes; Lock again: an RwSList.
    Rt2dPathUnlock(path);
    C15_CHECK(path->numSegment == 5);
    Rt2dPathLock(path);
    C15_CHECK(path->numSegment == -1 && _rwSListGetNumEntries(static_cast<RwSList*>(path->segments)) == 5);
    // A second moveto starts a second subpath.
    Rt2dPathMoveto(path, 5.0f, 5.0f);
    C15_CHECK(path->next != nullptr && path->curr == path->next);
    C15_CHECK(Rt2dPathDestroy(path) == 1);
}

// Rt2dPathCurveto keeps three curve nodes; the fill flattens it into line nodes ending on the end point.
void TestCurve() {
    Rt2dPath* path = Rt2dPathCreate();
    Rt2dPathMoveto(path, 0.0f, 0.0f);
    Rt2dPathCurveto(path, 0.0f, 100.0f, 100.0f, 100.0f, 100.0f, 0.0f);
    RwInt32 count = 0;
    rt2dPathNode* n = Nodes(path, &count);
    C15_CHECK(count == 4 && n[1].type == rt2dCURVE && n[3].type == rt2dCURVE && path->flat == 0);
    Rt2dPath* flat = _rt2dGetEmptyScratchPath();
    _rt2dSubPathFlatten(flat, path);
    RwInt32 flatCount = 0;
    rt2dPathNode* f = Nodes(flat, &flatCount);
    C15_CHECK(flatCount > 4 && flatCount <= 1 + 128);
    C15_CHECK(f[flatCount - 1].pos.x == 100.0f && f[flatCount - 1].pos.y == 0.0f);
    for (RwInt32 i = 1; i < flatCount; ++i) C15_CHECK(f[i].type == rt2dLINE);
    std::printf("rt2d: curve flattened into %d nodes (tolerance %08x)\n", flatCount, Bits(rt2dGlobals.sqTolerance));
    Rt2dPathDestroy(path);
}

// The triangulator: a unit square (closed: 5 nodes) gives 2 triangles, an L (7 nodes) 4, every index in
// range.
void TestTriangulation() {
    Rt2dPath* square = Rt2dPathCreate();
    Rt2dPathRect(square, 0.0f, 0.0f, 1.0f, 1.0f);
    RwImVertexIndex idx[64] = {};
    RwInt32 numTri = -1;
    _rt2dShapeTriangulateFill(square, &numTri, idx);
    C15_CHECK(numTri == 2);
    Rt2dPathDestroy(square);
    Rt2dPath* ell = Rt2dPathCreate();
    Rt2dPathMoveto(ell, 0.0f, 0.0f);
    Rt2dPathLineto(ell, 2.0f, 0.0f);
    Rt2dPathLineto(ell, 2.0f, 1.0f);
    Rt2dPathLineto(ell, 1.0f, 1.0f);
    Rt2dPathLineto(ell, 1.0f, 2.0f);
    Rt2dPathLineto(ell, 0.0f, 2.0f);
    Rt2dPathClose(ell);
    numTri = -1;
    _rt2dShapeTriangulateFill(ell, &numTri, idx);
    C15_CHECK(numTri == 4);
    for (int i = 0; i < numTri * 3; ++i) C15_CHECK(idx[i] < 6);
    Rt2dPathDestroy(ell);
}

// Rt2dBrushSetRGBA: top = col3, deltas col2 - col3 / col1 - col0; flag 1 when anything varies.
void TestBrush() {
    Rt2dBrush* brush = Rt2dBrushCreate();
    C15_CHECK(brush->halfwidth == 0.5f && brush->refCount == 1 && (brush->flag & 1) == 0);
    C15_CHECK(brush->colorCache.red == 0xff && brush->colorCache.alpha == 0xff);
    RwRGBA c0 = {10, 20, 30, 40}, c1 = {10, 20, 30, 40}, c2 = {10, 20, 30, 40}, c3 = {11, 20, 30, 40};
    Rt2dBrushSetRGBA(brush, &c0, &c1, &c2, &c3);
    C15_CHECK(brush->top.col.red == 11.0f && brush->dtop.col.red == -1.0f && brush->bottom.col.red == 10.0f);
    C15_CHECK((brush->flag & 1) != 0 && brush->colorCache.red == 11);
    C15_CHECK(Rt2dBrushDestroy(brush) == 1);
}

// The live RpGeometry of movie #3's shape s/7 (RPCS3, main menu): 5 vertices (z = layer depth 1), the
// rectangle (-58.05, -618.15)-(824.2, 36) from its first node around, two triangles (3,1,2) (1,3,0).
const uint32_t kS7Verts[15] = {0x444e0ccd, 0xc41a899a, 0x3f800000, 0x444e0ccd, 0x42180000, 0x3f800000,
                               0xc2683330, 0x42180000, 0x3f800000, 0xc2683330, 0xc41a899a, 0x3f800000,
                               0x444e0ccd, 0xc41a899a, 0x3f800000};
// The colour-cache alpha of s/7 .. s/22 (the shapes' black fills fading in), as read live.
const uint8_t kShapeAlpha[16] = {0x0d, 0x0e, 0x11, 0x16, 0x1c, 0x25, 0x2f, 0x3b,
                                 0x4a, 0x5a, 0x6c, 0x7f, 0x95, 0xad, 0xc6, 0xff};

void TestPressStartScene(Rt2dObject* scene) {
    C15_CHECK(scene->type == rt2DOBJECTTYPESCENE && Rt2dSceneGetChildCount(scene) == 23);
    C15_CHECK((scene->flag & 1) == 0);
    int scenes = 0, strings = 0, shapes = 0;
    for (RwInt32 i = 0; i < Rt2dSceneGetChildCount(scene); ++i) {
        Rt2dObject* child = Rt2dSceneGetChildByIndex(scene, i);
        if (child->type == rt2DOBJECTTYPESCENE) ++scenes;
        if (child->type == rt2DOBJECTTYPEOBJECTSTRING) ++strings;
        if (child->type != rt2DOBJECTTYPESHAPE) continue;
        const int s = shapes++;
        _rt2dShapeRep* rep = child->data.shape.rep;
        RpGeometry* g = rep->geometry;
        C15_CHECK(g != nullptr && child->data.shape.atomic != nullptr);
        if (g == nullptr) continue;
        C15_CHECK(g->numTriangles == 2 && g->numVertices == 5 && g->flags == 0x4f);
        C15_CHECK(g->matList.numMaterials == 1 && child->data.shape.colorCache != nullptr);
        if (s < 16 && child->data.shape.colorCache != nullptr) {
            const RwRGBA cc = child->data.shape.colorCache[0];
            C15_CHECK(cc.red == 0 && cc.green == 0 && cc.blue == 0 && cc.alpha == kShapeAlpha[s]);
        }
        const RwSphere& sphere = g->morphTarget->boundingSphere;
        C15_CHECK(Bits(sphere.center.x) == Bits(383.075012f) && Bits(sphere.center.y) == Bits(-290.075012f));
        C15_CHECK(sphere.center.z == 1.0f && Bits(sphere.radius) == Bits(550.284241f));
        if (s == 0) {
            bool same = true;
            for (int k = 0; k < 5; ++k) {
                const RwV3d& v = g->morphTarget->verts[k];
                same = same && Bits(v.x) == kS7Verts[3 * k] && Bits(v.y) == kS7Verts[3 * k + 1] &&
                       Bits(v.z) == kS7Verts[3 * k + 2];
            }
            C15_CHECK(same);
            const RpTriangle& t0 = g->triangles[0];
            const RpTriangle& t1 = g->triangles[1];
            C15_CHECK(t0.vertIndex[0] == 3 && t0.vertIndex[1] == 1 && t0.vertIndex[2] == 2 && t0.matIndex == 0);
            C15_CHECK(t1.vertIndex[0] == 1 && t1.vertIndex[1] == 3 && t1.vertIndex[2] == 0 && t1.matIndex == 0);
            for (int k = 0; k < 5; ++k) C15_CHECK(Bits(*reinterpret_cast<float*>(&g->preLitLum[k])) == 0xffffffffu);
        }
    }
    C15_CHECK(scenes == 4 && strings == 3 && shapes == 16);
    // The string inside the fourth scene and the three after it: Fonte_Flash_0 text objects.
    Rt2dObject* inner = Rt2dSceneGetChildByIndex(Rt2dSceneGetChildByIndex(scene, 3), 0);
    C15_CHECK(inner->type == rt2DOBJECTTYPEOBJECTSTRING);
}

}  // namespace

int main() {
    if (!c15::BootToFrontEnd()) {
        std::printf("rt2d: no game data configured; skipped\n");
        return 77;
    }
    TestRectPath();
    TestCurve();
    TestTriangulation();
    TestBrush();

    // Fonts: CManager2d's three LLC fonts, read by Rt2dFontStreamRead, are in the font dictionary.
    CManager2d* manager2d = g_pEngine->m_manager2d;
    int fonts = 0;
    for (Rt2dFont* font : manager2d->m_apFonts) fonts += font != nullptr ? 1 : 0;
    C15_CHECK(fonts == 3);
    _rt2dFontDictionaryNode* entry = _rt2dFontDictionaryFindEntry("Fonte_Flash_0");
    C15_CHECK(entry != nullptr && entry->font == manager2d->m_apFonts[0]);
    if (entry != nullptr) {
        Rt2dFont* font = entry->font;
        std::printf("rt2d: Fonte_Flash_0: outline %d, %d glyphs, flag %x, height %08x\n", font->isOutline,
                    font->charCount, font->flag, Bits(font->height));
        C15_CHECK(font->isOutline == 0 && font->fontshowCB != nullptr);
        // As read live (RPCS3, CManager2d +0x1c): 167 glyphs, height 58, baseline 0.0517, flag 2, unicode
        // table offset 169 / 59309 entries; 'A' is glyph 24, width 0.62069, UVs (0.2373, 0.1240)-(0.3076, 0.2373).
        C15_CHECK(font->charCount == 167 && font->height == 58.0f && Bits(font->baseline) == Bits(0.0517241396f));
        C15_CHECK(font->flag == 2 && font->uCharOffset == 169 && font->uCharIndexCount == 59309);
        C15_CHECK(_rt2dFontCharIndex(font, 'A') == 24);
        const rt2dCharRect* rects = static_cast<const rt2dCharRect*>(_rwSListGetArray(font->charMap));
        const rt2dCharRect& a = rects[24];
        C15_CHECK(Bits(a.width) == Bits(0.620689630f) && a.uv[0].x == 0.2373046875f && a.uv[0].y == 0.1240234375f);
        C15_CHECK(a.uv[1].x == 0.3076171875f && a.uv[1].y == 0.2373046875f && a.charpage == 0 && a.tex != nullptr);
    }
    // The dictionary, newest first: the three LLC fonts, then the GLC's TrcFont (as live).
    const char* order[4] = {"Fonte_Flash_2", "Fonte_Flash_1", "Fonte_Flash_0", "TrcFont"};
    _rt2dFontDictionaryNode* node = rt2dGlobals.fontDictionary;
    for (const char* name : order) {
        C15_CHECK(node != nullptr && std::strcmp(node->name, name) == 0);
        if (node != nullptr) node = node->next;
    }
    C15_CHECK(node == nullptr);

    CKFlashManager* manager = g_pEngine->m_flashManager;
    C15_CHECK(manager != nullptr && manager->m_ui32NbFlashUI == 29);
    if (manager == nullptr || manager->m_ui32NbFlashUI < 4) {
        c15::Shutdown();
        return 1;
    }
    Rt2dMaestro* maestro = static_cast<CKFlashUI*>(manager->m_apFlashUI[3])->m_pMaestro;
    C15_CHECK(maestro != nullptr && maestro->scene != nullptr);
    if (maestro != nullptr && maestro->scene != nullptr) TestPressStartScene(maestro->scene);

    // The movies' strings were read before the LLC fonts (as on the PS3: CKFlashUI_Load runs before
    // CManager2d_LoadFonts); the PS3 resolves them at mode 4 through CKFlashManager_ApplyFontsToAllUIs.
    manager->UpdateLocalizedData(0, nullptr);
    Rt2dObject* text = maestro != nullptr ? Rt2dSceneGetChildByIndex(maestro->scene, 4) : nullptr;
    if (text != nullptr) {
        C15_CHECK(text->type == rt2DOBJECTTYPEOBJECTSTRING);
        std::printf("rt2d: s/4 font %s, flag %08x\n",
                    text->data.objectString.font != nullptr ? text->data.objectString.font->name : "(none)", text->flag);
    }

    // One render of the press-start scene: every shape as an atomic, every visible string as glyphs.
    if (maestro != nullptr && maestro->scene != nullptr) {
        Rt2dDeviceSetCamera(Rt2dDeviceGetCamera());
        Rt2dCTMPush();
        Rt2dCTMSetIdentity();
        Rt2dDeviceSetMetric(0.0f, 0.0f, 0x1.c71c72p+0f, 1.0f);
        Rt2dCTMPop();
        RpAtomicBeginFrame();
        RwIm3DBeginFrame();
        Rt2dObject* scene = maestro->scene;
        // Before any visible render the shapes' frames hold what _rt2dShapeStreamReadTo set at load: the
        // composite CTM with an identity CTM. The live s/7 frame (RPCS3 at the main menu: its shapes are
        // hidden, flag 3, and were never drawn) holds exactly that: right (-0.5625, 0, 0), up (0, 1, 0),
        // at (0, 0, 1), pos (1, 0, -1); it shows the PS3's metric (0, 0, 16/9, 1) was set before the load.
        {
            RpAtomic* atomic = Rt2dSceneGetChildByIndex(scene, 7)->data.shape.atomic;
            const RwMatrix& m = atomic->frame->modelling;
            std::printf("rt2d: s/7 frame before render: right %08x up %08x pos %08x %08x %08x, shape flag %x\n",
                        Bits(m.right.x), Bits(m.up.y), Bits(m.pos.x), Bits(m.pos.y), Bits(m.pos.z),
                        Rt2dSceneGetChildByIndex(scene, 7)->flag);
            C15_CHECK(m.right.y == 0.0f && Bits(m.up.y) == 0x3f800000u);
            C15_CHECK(Bits(m.at.z) == 0x3f800000u && Bits(m.pos.x) == 0x3f800000u && m.pos.y == 0.0f);
            C15_CHECK(Bits(m.pos.z) == 0xbf800000u);
            // right.x is -(the metric's x scale at load time): the boot's loading frames run
            // CManager2d_PreRenderPass (0x63320, through RenderFallbackFrame 0xa11b0) long before
            // CKFlashUI_Load, as on the PS3 (first run at 587 ms vs 12943 ms), so the metric is 16:9.
            C15_CHECK(Bits(m.right.x) == 0xbf100000u);
        }
        // The boot fitted the movie as on the PS3: the scene MTM is the live #3 scene's (scale 1/600,
        // 0x3ada740e; pos (0.2222, 1), 0x3e638e3a / 0x3f800000).
        C15_CHECK(Bits(scene->MTM.right.x) == 0x3ada740eu && Bits(scene->MTM.up.y) == 0x3ada740eu);
        C15_CHECK(Bits(scene->MTM.pos.x) == 0x3e638e3au && Bits(scene->MTM.pos.y) == 0x3f800000u);
        for (RwInt32 i = 0; i < Rt2dSceneGetChildCount(scene); ++i) Rt2dObjectSetVisible(Rt2dSceneGetChildByIndex(scene, i), 1);
        Rt2dObjectSetVisible(scene, 1);
        // The boot's frames have already fitted the movie (CManager2d_UpdateScreen -> RefreshSize ->
        // InitializeMaestroScenePosition: the scene MTM scaled by 1/600 and placed), as on the PS3.
        Rt2dSceneRender(scene);
        const auto& atomics = RpAtomicFrameDraws();
        const auto& draws = RwIm3DFrameDraws();
        std::printf("rt2d: render: %zu atomics, %zu immediate draws\n", atomics.size(), draws.size());
        C15_CHECK(atomics.size() == 16);
        for (const RwIm3DDraw& d : draws) {
            C15_CHECK(d.primType == rwPRIMTYPETRILIST && d.indices.size() % 6 == 0 && d.vertices.size() * 6 == d.indices.size() * 4);
            for (const RwIm3DVertex& v : d.vertices) C15_CHECK(v.objVertex.y == 0.0f || v.objVertex.y == 1.0f);
        }
        // A visible render places each atomic's frame at the composite CTM with the shape's LTM pushed
        // (DrawUIShapeSceneObject 0x71bb80: RwFrameTransform(frame, UI2D_GetCompositeMatrix, replace) after
        // the push): top = shape MTM (identity) x scene MTM; x metric (x 0.5625) x (-1, 1, 1) + (0.5, -0.5);
        // x the camera frame (pos (0.5, 0.5, -1)): right.x -0.5625/600, up.y 1/600, pos (0.875, 1, -1).
        if (!atomics.empty()) {
            const RwMatrix& ltm = atomics[0].ltm;
            std::printf("rt2d: atomic 0 LTM right %08x %08x up %08x %08x pos %08x %08x %08x\n", Bits(ltm.right.x),
                        Bits(ltm.right.y), Bits(ltm.up.x), Bits(ltm.up.y), Bits(ltm.pos.x), Bits(ltm.pos.y), Bits(ltm.pos.z));
            C15_CHECK(Bits(ltm.right.x) == 0xba75c290u && ltm.right.y == 0.0f && Bits(ltm.up.y) == 0x3ada740eu);
            C15_CHECK(Bits(ltm.at.z) == 0x3f800000u);
            C15_CHECK(Bits(ltm.pos.x) == 0x3f600000u && Bits(ltm.pos.y) == 0x3f800000u && Bits(ltm.pos.z) == 0xbf800000u);
        }
        // The live strings of this movie hold " " (nothing is drawn); a two-character text draws one
        // batch: 2 glyph quads (8 vertices, 12 indices over fonttopo), y 0 / 1, x advancing by the glyph
        // widths, the UVs of the glyphs' rects.
        Rt2dObject* string = Rt2dSceneGetChildByIndex(scene, 4);
        Rt2dFont* font = string->data.objectString.font != nullptr ? string->data.objectString.font->font : nullptr;
        if (font != nullptr && (font->flag & 2) != 0) {
            const uint16_t ab[3] = {'A', 'B', 0};
            Rt2dObjectStringSetText(string, reinterpret_cast<const RwChar*>(ab));
            // The movie's box (0.8, set by the K side) is narrower than "AB" (1.07): Rt2dFontFlow would
            // break before B, find the next line below the box and draw nothing (as the PS3 does).
            const RwReal box = string->data.objectString.boxwidth;
            C15_CHECK(Rt2dFontGetStringWidth(font, string->data.objectString.textString, 1.0f) > box);
            string->data.objectString.boxwidth = 10.0f;
            std::printf("rt2d: s/4 flag %08x height %08x box %08x width(AB) %08x maxLength %d\n", string->flag,
                        Bits(string->data.objectString.height), Bits(string->data.objectString.boxwidth),
                        Bits(Rt2dFontGetStringWidth(font, string->data.objectString.textString, 1.0f)),
                        string->data.objectString.maxLength);
            RwIm3DBeginFrame();
            Rt2dSceneRender(scene);
            C15_CHECK(RwIm3DFrameDraws().size() == 1);
            if (RwIm3DFrameDraws().size() == 1) {
                const RwIm3DDraw& d = RwIm3DFrameDraws()[0];
                C15_CHECK(d.vertices.size() == 8 && d.indices.size() == 12);
                const rt2dCharRect* rects = static_cast<const rt2dCharRect*>(_rwSListGetArray(font->charMap));
                const rt2dCharRect& a = rects[_rt2dFontCharIndex(font, 'A')];
                if (d.vertices.size() == 8) {
                    C15_CHECK(d.vertices[0].objVertex.x == 0.0f && d.vertices[2].objVertex.x == a.width);
                    C15_CHECK(d.vertices[4].objVertex.x == a.width + font->intergap);
                    C15_CHECK(d.vertices[0].u == a.uv[0].x && d.vertices[0].v == a.uv[1].y);
                    C15_CHECK(d.vertices[3].u == a.uv[1].x && d.vertices[3].v == a.uv[0].y);
                }
                const RwImVertexIndex expect[6] = {0, 2, 3, 0, 3, 1};
                for (int i = 0; i < 6 && i < static_cast<int>(d.indices.size()); ++i) C15_CHECK(d.indices[i] == expect[i]);
                C15_CHECK((d.transformFlags & (rwIM3D_VERTEXUV | rwIM3D_NOCLIP)) == (rwIM3D_VERTEXUV | rwIM3D_NOCLIP));
            }
        }
    }

    c15::Shutdown();
    if (c15::g_failures == 0) std::printf("rt2d: all tests passed\n");
    return c15::g_failures == 0 ? 0 : 1;
}
