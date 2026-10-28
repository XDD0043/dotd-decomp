// Rt2dDebugDump.cpp - see Rt2dDebugDump.h. Debug tooling (no PS3 counterpart): it only reads the structs.
// The walk mirrors work/maestro_live.py field for field; a change to one needs the same change in the other.
#include "Renderware/rt2d/Rt2dDebugDump.h"

#include <cstdio>
#include <cstring>
#include <unordered_map>
#include <vector>

#include "Renderware/rt2d/Rt2dTypes.h"

namespace {

constexpr int32_t kMaxList = 100000;  // sanity bound for list counts and chains (as maestro_live.py)

// A minimal JSON writer: values after a Key() take no comma; everything else is comma-separated.
class Json {
public:
    std::string s;

    void Open(char c) {
        Sep();
        s += c;
        m_first.push_back(true);
    }
    void Close(char c) {
        s += c;
        m_first.pop_back();
    }
    void Key(const char* key) {
        Sep();
        Quote(key, std::strlen(key));
        s += ':';
        m_afterKey = true;
    }
    void Null() { Sep(); s += "null"; }
    void Bool(bool v) { Sep(); s += v ? "true" : "false"; }
    void Int(int64_t v) {
        Sep();
        char buf[32];
        std::snprintf(buf, sizeof(buf), "%lld", static_cast<long long>(v));
        s += buf;
    }
    void Hex(uint32_t v) {
        char buf[16];
        std::snprintf(buf, sizeof(buf), "%08x", v);
        Str(buf);
    }
    void Float(RwReal v) {
        uint32_t bits = 0;
        std::memcpy(&bits, &v, 4);
        char buf[16];
        std::snprintf(buf, sizeof(buf), "f:%08x", bits);
        Str(buf);
    }
    void Str(const char* v) { Sep(); Quote(v, std::strlen(v)); }
    // A string of code points (latin-1 bytes or 2-byte characters).
    void CodePoints(const std::vector<uint32_t>& cps) {
        Sep();
        s += '"';
        for (uint32_t c : cps) AppendCodePoint(c);
        s += '"';
    }
    void Raw(const std::string& json) { Sep(); s += json; }

private:
    std::vector<bool> m_first;
    bool m_afterKey = false;

    void Sep() {
        if (m_afterKey) {
            m_afterKey = false;
            return;
        }
        if (!m_first.empty()) {
            if (!m_first.back()) s += ',';
            m_first.back() = false;
        }
    }
    void Quote(const char* v, size_t n) {
        s += '"';
        for (size_t i = 0; i < n; ++i) AppendCodePoint(static_cast<uint8_t>(v[i]));
        s += '"';
    }
    void AppendCodePoint(uint32_t c) {
        if (c == '"' || c == '\\') {
            s += '\\';
            s += static_cast<char>(c);
        } else if (c >= 0x20 && c < 0x7f) {
            s += static_cast<char>(c);
        } else {
            char buf[8];
            std::snprintf(buf, sizeof(buf), "\\u%04x", c & 0xffffu);
            s += buf;
        }
    }
};

int32_t PtrToInt32(const void* p) { return static_cast<int32_t>(reinterpret_cast<intptr_t>(p)); }

uint32_t RgbaWord(const RwRGBA& c) {
    return (static_cast<uint32_t>(c.red) << 24) | (static_cast<uint32_t>(c.green) << 16) |
           (static_cast<uint32_t>(c.blue) << 8) | c.alpha;
}

// An RwSList's elements, count and entry size; false for a null list. count is 0 for a bad list.
struct ListView {
    const RwUInt8* elements = nullptr;
    int32_t count = 0;
    int32_t entrySize = 0;
};

class Walker {
public:
    std::vector<std::string> errors;

    std::string Maestro(const Rt2dMaestro* m) {
        Json j;
        j.Open('{');
        j.Key("flag"); j.Int(m->flag);
        j.Key("version"); j.Int(m->version);
        j.Key("messageHandler"); j.Bool(m->messageHandler != nullptr);
        j.Key("prevMouse");
        j.Open('{');
        j.Key("position");
        j.Open('[');
        j.Float(m->prevMouse.position.x);
        j.Float(m->prevMouse.position.y);
        j.Close(']');
        j.Key("button"); j.Int(m->prevMouse.button);
        j.Close('}');
        j.Key("invWinH"); j.Float(m->invWinH);
        j.Key("invWinW"); j.Float(m->invWinW);
        j.Key("winAspectRatio"); j.Float(m->winAspectRatio);
        j.Key("currAnimIndex"); j.Int(m->currAnimIndex);
        j.Key("bbox");
        j.Open('[');
        j.Float(m->bbox.x); j.Float(m->bbox.y); j.Float(m->bbox.w); j.Float(m->bbox.h);
        j.Close(']');
        j.Key("stateTransTable");
        j.Open('[');
        {
            const Rt2dStateTransData* t = &m->stateTransTable[0][0][0][0];
            for (int i = 0; i < 16; ++i) {
                j.Int(t[i].transState); j.Int(t[i].buttonUpImg); j.Int(t[i].buttonDownImg); j.Int(t[i].buttonOverImg);
            }
        }
        j.Close(']');
        // byte bucket and labels
        std::vector<uint8_t> bucket;
        ListView v;
        if (List(m->byteBucket, "byteBucket", &v)) {
            bucket.assign(v.elements, v.elements + static_cast<size_t>(v.count) * (v.entrySize > 0 ? v.entrySize : 1));
            j.Key("byteBucketSize"); j.Int(v.count);
        }
        j.Key("labels");
        j.Open('[');
        if (List(m->labels, "labels", &v)) {
            for (int32_t i = 0; i < v.count; ++i) {
                const Rt2dStringLabel* l = reinterpret_cast<const Rt2dStringLabel*>(v.elements + v.entrySize * i);
                j.Open('{');
                j.Key("entityType"); j.Int(l->entityType);
                j.Key("nameIndex"); j.Int(l->nameIndex);
                j.Key("name");
                if (l->nameIndex >= 0 && static_cast<size_t>(l->nameIndex) < bucket.size()) {
                    std::vector<uint32_t> cps;
                    for (size_t k = static_cast<size_t>(l->nameIndex); k < bucket.size() && bucket[k] != 0; ++k)
                        cps.push_back(bucket[k]);
                    j.CodePoints(cps);
                } else {
                    j.Null();
                }
                j.Key("internalData"); j.Int(PtrToInt32(l->internalData));
                j.Key("userData"); j.Int(PtrToInt32(l->userData));
                j.Close('}');
            }
        }
        j.Close(']');
        // the scene first: the other parts refer to its objects
        j.Key("scene");
        if (m->scene != nullptr) Object(j, m->scene, "s"); else j.Null();
        j.Key("buttons");
        j.Open('[');
        if (List(m->buttons, "buttons", &v)) {
            for (int32_t i = 0; i < v.count; ++i) {
                const Rt2dButton* b = reinterpret_cast<const Rt2dButton*>(v.elements + v.entrySize * i);
                j.Open('{');
                j.Key("strLabelIndex"); j.Int(b->strLabelIndex);
                j.Key("objectIndex"); j.Int(b->objectIndex);
                j.Key("stateFlag"); j.Hex(b->stateFlag);
                j.Key("buttonState"); j.Hex(b->buttonState);
                j.Key("actions");
                j.Open('[');
                for (int k = 0; k < 32; ++k) j.Int(b->actionListForStateTransition[k]);
                j.Close(']');
                j.Close('}');
            }
        }
        j.Close(']');
        j.Key("messageList");
        if (List(m->messageList, "messageList", &v)) {
            j.Open('[');
            for (int32_t i = 0; i < v.count; ++i) j.Int(*reinterpret_cast<const RwInt32*>(v.elements + v.entrySize * i));
            j.Close(']');
        } else {
            j.Null();
        }
        j.Key("messageStore");
        j.Open('[');
        if (List(m->messageStore, "messageStore", &v)) {
            for (int32_t i = 0; i < v.count; ++i) Message(j, reinterpret_cast<const Rt2dMessage*>(v.elements + v.entrySize * i));
        }
        j.Close(']');
        j.Key("messageQueue");
        if (const Rt2dMessageQueue* q = m->messageQueue) {
            j.Open('{');
            j.Key("top"); j.Int(q->messageTop);
            j.Key("bot"); j.Int(q->messageBot);
            j.Key("size"); j.Int(q->size);
            j.Key("pending");
            j.Open('[');
            if (q->messageQueue != nullptr && q->messageTop >= 0 && q->messageTop <= q->messageBot &&
                static_cast<uint32_t>(q->messageBot) <= (q->size < static_cast<uint32_t>(kMaxList) ? q->size : kMaxList)) {
                for (int32_t i = q->messageTop; i < q->messageBot; ++i) Message(j, &q->messageQueue[i]);
            }
            j.Close(']');
            j.Close('}');
        } else {
            j.Null();
        }
        j.Key("animations");
        j.Open('[');
        ListView anims;
        if (List(m->animations, "animations", &anims)) {
            for (int32_t i = 0; i < anims.count; ++i)
                AnimNode(j, reinterpret_cast<const Rt2dAnimNode*>(anims.elements + anims.entrySize * i));
        }
        j.Close(']');
        if (m->animations != nullptr) {
            j.Key("animationsEntrySize"); j.Int(anims.entrySize);
        }
        j.Key("shapeReps");
        j.Open('[');
        for (const std::string& rep : m_repJson) j.Raw(rep);
        j.Close(']');
        if (!errors.empty()) {
            j.Key("errors");
            j.Open('[');
            for (const std::string& e : errors) j.Str(e.c_str());
            j.Close(']');
        }
        j.Close('}');
        return j.s;
    }

private:
    std::unordered_map<const void*, std::string> m_objects;  // object -> "@path"
    std::unordered_map<const void*, int32_t> m_reps;         // shape rep -> index
    std::vector<std::string> m_repJson;
    std::vector<int32_t> m_repNodeCounts;

    bool List(const RwSList* list, const char* what, ListView* out) {
        *out = ListView();
        if (list == nullptr) return false;
        out->elements = list->listElements;
        out->entrySize = list->entrySize;
        out->count = list->numElementsFilled;
        if (out->count > kMaxList || out->count < 0 || (out->count != 0 && out->elements == nullptr)) {
            errors.push_back(std::string(what) + ": bad RwSList");
            out->count = 0;
        }
        return true;
    }

    void Ref(Json& j, const void* p) {
        if (p == nullptr) {
            j.Null();
            return;
        }
        auto it = m_objects.find(p);
        j.Str(it != m_objects.end() ? it->second.c_str() : "@ext");
    }

    static void Matrix(Json& j, const RwMatrix& m) {
        j.Open('{');
        j.Key("right"); j.Open('['); j.Float(m.right.x); j.Float(m.right.y); j.Float(m.right.z); j.Close(']');
        j.Key("flags"); j.Int(m.flags);
        j.Key("up"); j.Open('['); j.Float(m.up.x); j.Float(m.up.y); j.Float(m.up.z); j.Close(']');
        j.Key("at"); j.Open('['); j.Float(m.at.x); j.Float(m.at.y); j.Float(m.at.z); j.Close(']');
        j.Key("pos"); j.Open('['); j.Float(m.pos.x); j.Float(m.pos.y); j.Float(m.pos.z); j.Close(']');
        j.Close('}');
    }

    static void Color(Json& j, const RwRGBAReal& c) {
        j.Open('[');
        j.Float(c.red); j.Float(c.green); j.Float(c.blue); j.Float(c.alpha);
        j.Close(']');
    }

    static void Message(Json& j, const Rt2dMessage* m) {
        j.Open('[');
        j.Int(m->messageType); j.Int(m->index); j.Int(m->intParam1); j.Int(m->intParam2);
        j.Close(']');
    }

    static void Shade(Json& j, const rt2dShadeParameters& s) {
        j.Open('[');
        j.Float(s.col.red); j.Float(s.col.green); j.Float(s.col.blue); j.Float(s.col.alpha);
        j.Float(s.uv.x); j.Float(s.uv.y);
        j.Close(']');
    }

    static void Brush(Json& j, const Rt2dBrush* b) {
        if (b == nullptr) {
            j.Null();
            return;
        }
        j.Open('{');
        j.Key("top"); Shade(j, b->top);
        j.Key("dtop"); Shade(j, b->dtop);
        j.Key("bottom"); Shade(j, b->bottom);
        j.Key("dbottom"); Shade(j, b->dbottom);
        j.Key("colorCache"); j.Hex(RgbaWord(b->colorCache));
        j.Key("flag"); j.Int(static_cast<uint32_t>(b->flag));
        j.Key("texture"); j.Bool(b->texture != nullptr);
        j.Key("material"); j.Bool(b->material != nullptr);
        j.Key("halfwidth"); j.Float(b->halfwidth);
        j.Key("refCount"); j.Int(static_cast<uint32_t>(b->refCount));
        j.Close('}');
    }

    // An Rt2dPath and its subpath chain (next).
    void Path(Json& j, const Rt2dPath* p) {
        if (p == nullptr) {
            j.Null();
            return;
        }
        std::vector<const Rt2dPath*> seen;
        j.Open('[');
        while (p != nullptr && static_cast<int32_t>(seen.size()) < kMaxList) {
            bool loops = false;
            for (const Rt2dPath* q : seen) loops = loops || q == p;
            if (loops) {
                errors.push_back("path chain loops");
                break;
            }
            seen.push_back(p);
            int32_t num = p->numSegment;
            if (num > kMaxList || num < 0) {
                errors.push_back("path: too many segments");
                num = 0;
            }
            const void* seg = p->segments;
            const char* form = "array";
            if (seg != nullptr && num > 0) {
                // While unlocked the segments are an RwSList (path.c); locked, the rt2dPathNode array.
                const RwSList* list = static_cast<const RwSList*>(seg);
                if (list->numElementsFilled == num && list->entrySize == static_cast<RwInt32>(sizeof(rt2dPathNode)) &&
                    list->listElements != nullptr) {
                    form = "slist";
                    seg = list->listElements;
                }
            }
            j.Open('{');
            j.Key("segments");
            if (p->segments != nullptr) j.Str(form); else j.Null();
            j.Key("numSegment"); j.Int(num);
            j.Key("closed"); j.Int(static_cast<uint32_t>(p->closed));
            j.Key("flat"); j.Int(static_cast<uint32_t>(p->flat));
            j.Key("inset"); j.Float(p->inset);
            j.Key("curr");
            {
                int32_t index = -1;
                for (size_t k = 0; k < seen.size(); ++k)
                    if (seen[k] == p->curr) index = static_cast<int32_t>(k);
                if (index >= 0) j.Int(index);
                else if (p->curr == nullptr) j.Null();
                else j.Str("@ext");
            }
            j.Key("nodes");
            j.Open('[');
            if (seg != nullptr) {
                const rt2dPathNode* nodes = static_cast<const rt2dPathNode*>(seg);
                for (int32_t i = 0; i < num; ++i) {
                    j.Open('[');
                    j.Int(nodes[i].type);
                    j.Float(nodes[i].pos.x); j.Float(nodes[i].pos.y);
                    j.Float(nodes[i].normal.x); j.Float(nodes[i].normal.y);
                    j.Float(nodes[i].dist);
                    j.Close(']');
                }
            }
            j.Close(']');
            j.Close('}');
            p = p->next;
        }
        j.Close(']');
    }

    void ShapeRep(Json& j, const _rt2dShapeRep* rep) {
        if (rep == nullptr) {
            j.Null();
            return;
        }
        char id[16];
        auto it = m_reps.find(rep);
        if (it != m_reps.end()) {
            std::snprintf(id, sizeof(id), "#%d", it->second);
            j.Str(id);
            return;
        }
        const int32_t index = static_cast<int32_t>(m_repJson.size());
        m_reps[rep] = index;
        m_repJson.emplace_back();
        m_repNodeCounts.push_back(0);
        std::snprintf(id, sizeof(id), "#%d", index);
        Json r;
        r.Open('{');
        r.Key("id"); r.Str(id);
        r.Key("refCount"); r.Int(rep->refCount);
        r.Key("geometry"); r.Bool(rep->geometry != nullptr);
        r.Key("nodes");
        r.Open('[');
        ListView v;
        const bool hasList = List(rep->nodes, "rep nodes", &v);
        for (int32_t i = 0; hasList && i < v.count; ++i) {
            const _rt2dShapeNode* n = reinterpret_cast<const _rt2dShapeNode*>(v.elements + v.entrySize * i);
            r.Open('{');
            r.Key("flag"); r.Int(n->flag);
            r.Key("path"); Path(r, n->path);
            r.Key("brush"); Brush(r, n->brush);
            r.Close('}');
        }
        r.Close(']');
        if (hasList) {
            r.Key("nodesEntrySize"); r.Int(v.entrySize);
        }
        r.Close('}');
        m_repJson[static_cast<size_t>(index)] = r.s;
        m_repNodeCounts[static_cast<size_t>(index)] = v.count;
        j.Str(id);
    }

    void Text(Json& j, const _rt2dObjectString& s, int wide) {
        if (s.textString == nullptr) {
            j.Null();
            return;
        }
        int32_t n = s.maxLength < 0 ? 0 : (s.maxLength > 4096 ? 4096 : s.maxLength);
        n += 2;
        std::vector<uint32_t> cps;
        if (wide == 0) {
            const uint8_t* b = reinterpret_cast<const uint8_t*>(s.textString);
            for (int32_t i = 0; i < n + (n & 1) && b[i] != 0; ++i) cps.push_back(b[i]);
        } else {
            const Rt2dFontChar* c = reinterpret_cast<const Rt2dFontChar*>(s.textString);
            for (int32_t i = 0; i < (n + (n & 1)) / 2 && c[i] != 0; ++i) cps.push_back(c[i]);
        }
        j.CodePoints(cps);
    }

    void Object(Json& j, const Rt2dObject* o, const std::string& path) {
        m_objects[o] = "@" + path;
        j.Open('{');
        j.Key("path"); j.Str(path.c_str());
        j.Key("type"); j.Int(o->type);
        j.Key("depth"); j.Int(o->depth);
        j.Key("flag"); j.Hex(static_cast<uint32_t>(o->flag));
        j.Key("MTM"); Matrix(j, o->MTM);
        j.Key("LTM"); Matrix(j, o->LTM);
        j.Key("colorMult"); Color(j, o->colorMult);
        j.Key("colorOffs"); Color(j, o->colorOffs);
        int used = 0;
        if (o->type == rt2DOBJECTTYPESCENE) {
            used = 4;
            const _rt2dScene& sc = o->data.scene;
            j.Key("objectCount"); j.Int(sc.objectCount);
            j.Key("isDirtyDepths"); j.Int(static_cast<uint32_t>(sc.isDirtyDepths));
            ListView v;
            const bool hasObjects = List(sc.objects, (path + " objects").c_str(), &v);
            if (hasObjects) {
                j.Key("objectsEntrySize"); j.Int(v.entrySize);
            }
            j.Key("children");
            j.Open('[');
            for (int32_t i = 0; hasObjects && i < v.count; ++i) {
                char child[16];
                std::snprintf(child, sizeof(child), "/%d", i);
                Object(j, reinterpret_cast<const Rt2dObject*>(v.elements + v.entrySize * i), path + child);
            }
            j.Close(']');
            j.Key("depths");
            if (List(sc.depths, (path + " depths").c_str(), &v)) {
                j.Open('[');
                for (int32_t i = 0; i < v.count; ++i) {
                    const _rt2dDepthOfObject* d = reinterpret_cast<const _rt2dDepthOfObject*>(v.elements + v.entrySize * i);
                    j.Open('[');
                    Ref(j, d->object);
                    j.Int(d->depth);
                    j.Close(']');
                }
                j.Close(']');
            } else {
                j.Null();
            }
        } else if (o->type == rt2DOBJECTTYPESHAPE) {
            used = 3;
            const _rt2dShape& sh = o->data.shape;
            j.Key("rep"); ShapeRep(j, sh.rep);
            int32_t nodes = 0;
            if (sh.rep != nullptr) nodes = m_repNodeCounts[static_cast<size_t>(m_reps[sh.rep])];
            j.Key("colorCache");
            if (sh.colorCache == nullptr) {
                j.Null();
            } else {
                j.Open('[');
                for (int32_t i = 0; i < nodes; ++i) j.Hex(RgbaWord(sh.colorCache[i]));
                j.Close(']');
            }
            j.Key("atomic"); j.Bool(sh.atomic != nullptr);
        } else if (o->type == rt2DOBJECTTYPEPICKREGION) {
            used = 24;
            const _rt2dPickRegion& pr = o->data.pickRegion;
            j.Key("pickPath"); Path(j, pr.path);
            j.Key("bbox");
            j.Open('[');
            j.Float(pr.bbox.x); j.Float(pr.bbox.y); j.Float(pr.bbox.w); j.Float(pr.bbox.h);
            j.Close(']');
            j.Key("transformation"); Matrix(j, pr.transformation);
        } else if (o->type == rt2DOBJECTTYPEOBJECTSTRING) {
            used = 7;
            const _rt2dObjectString& s = o->data.objectString;
            int wide = -1;  // unknown (no font): read as 2-byte characters, like maestro_live.py
            if (s.font != nullptr && s.font->font != nullptr) wide = (s.font->font->flag & 2) != 0 ? 1 : 0;
            j.Key("text"); Text(j, s, wide);
            j.Key("maxLength"); j.Int(s.maxLength);
            j.Key("brush"); Brush(j, s.brush);
            j.Key("height"); j.Float(s.height);
            j.Key("font");
            if (s.font != nullptr && s.font->name != nullptr) {
                std::vector<uint32_t> cps;
                for (const RwChar* c = s.font->name; *c != 0 && cps.size() < 255; ++c) cps.push_back(static_cast<uint8_t>(*c));
                j.CodePoints(cps);
            } else {
                j.Null();
            }
            j.Key("wideChars");
            if (wide < 0) j.Null(); else j.Bool(wide == 1);
            j.Key("justiftype"); j.Int(s.justiftype);
            j.Key("boxwidth"); j.Float(s.boxwidth);
        }
        // Union words past the type's struct that are not zero (the PS3 layout only).
        if (sizeof(_rt2dObjectdata) == 0x60) {
            uint32_t words[24];
            std::memcpy(words, &o->data, sizeof(words));
            bool any = false;
            for (int i = used; i < 24; ++i) {
                if (words[i] == 0) continue;
                if (!any) {
                    j.Key("dataTail");
                    j.Open('{');
                    any = true;
                }
                char key[8];
                std::snprintf(key, sizeof(key), "+%02x", 0xb0 + 4 * i);
                j.Key(key);
                j.Hex(words[i]);
            }
            if (any) j.Close('}');
        }
        j.Close('}');
    }

    void Update(Json& j, const Rt2dAnimObjectUpdate* u) {
        j.Open('{');
        j.Key("hasSomething"); j.Int(u->hasSomething);
        j.Key("object"); Ref(j, u->object);
        j.Key("hasTransform"); j.Int(u->hasTransform);
        j.Key("transform"); Matrix(j, u->transform.matrix);
        j.Key("hasColorOffs"); j.Int(u->hasColorOffs);
        j.Key("colorOffs"); Color(j, u->colorOffs.color);
        j.Key("hasColorMult"); j.Int(u->hasColorMult);
        j.Key("colorMult"); Color(j, u->colorMult.color);
        j.Key("hasShow"); j.Int(u->hasShow);
        j.Key("show"); j.Open('['); j.Int(u->show.show); j.Int(u->show.depth); j.Close(']');
        j.Key("hasMorph"); j.Int(u->hasMorph);
        j.Key("morph");
        j.Open('[');
        Ref(j, u->morph.source);
        Ref(j, u->morph.destination);
        j.Float(u->morph.alpha);
        j.Close(']');
        j.Close('}');
    }

    // Rt2dKeyFrameList and its compact data (see the header).
    void KeyFrameList(Json& j, const Rt2dKeyFrameList* k) {
        if (k == nullptr) {
            j.Null();
            return;
        }
        j.Open('{');
        j.Key("time"); j.Float(k->time);
        j.Key("isLocked"); j.Int(k->isLocked);
        j.Key("sets");
        if (k->data != nullptr && !k->isLocked) {
            j.Open('[');
            const RwUInt8* q = k->data;
            for (int32_t n = 0; n < kMaxList; ++n) {
                const Rt2dKeyFrameSet* set = reinterpret_cast<const Rt2dKeyFrameSet*>(q);
                if ((set->flag & 0x20) != 0) break;
                q += sizeof(Rt2dKeyFrameSet);
                j.Open('{');
                j.Key("flag"); j.Int(set->flag);
                j.Key("objectIdx"); j.Int(set->objectIdx);
                if ((set->flag & 1) != 0) {
                    j.Key("transform"); Matrix(j, reinterpret_cast<const Rt2dKeyFrameTransform*>(q)->matrix);
                    q += sizeof(Rt2dKeyFrameTransform);
                }
                if ((set->flag & 2) != 0) {
                    j.Key("colorOffs"); Color(j, reinterpret_cast<const Rt2dKeyFrameColor*>(q)->color);
                    q += sizeof(Rt2dKeyFrameColor);
                }
                if ((set->flag & 4) != 0) {
                    j.Key("colorMult"); Color(j, reinterpret_cast<const Rt2dKeyFrameColor*>(q)->color);
                    q += sizeof(Rt2dKeyFrameColor);
                }
                if ((set->flag & 8) != 0) {
                    const Rt2dKeyFrameShow* show = reinterpret_cast<const Rt2dKeyFrameShow*>(q);
                    j.Key("show"); j.Open('['); j.Int(show->show); j.Int(show->depth); j.Close(']');
                    q += sizeof(Rt2dKeyFrameShow);
                }
                if ((set->flag & 0x10) != 0) {
                    const Rt2dKeyFrameMorph* morph = reinterpret_cast<const Rt2dKeyFrameMorph*>(q);
                    j.Key("morph");
                    j.Open('[');
                    j.Int(PtrToInt32(morph->source)); j.Int(PtrToInt32(morph->destination)); j.Float(morph->alpha);
                    j.Close(']');
                    q += sizeof(Rt2dKeyFrameMorph);
                }
                j.Close('}');
            }
            j.Close(']');
        } else {
            j.Null();
        }
        j.Close('}');
    }

    void AnimNode(Json& j, const Rt2dAnimNode* node) {
        const Rt2dAnim& a = node->anim;
        ListView sched;
        const bool hasSched = List(a.keyframeLists, "keyframeLists", &sched);
        auto schedRef = [&](const _rt2dAnimKeyFrameSched* q) {
            if (q == nullptr) {
                j.Null();
                return;
            }
            const RwUInt8* p = reinterpret_cast<const RwUInt8*>(q);
            if (sched.elements != nullptr && sched.entrySize > 0 && p >= sched.elements &&
                p < sched.elements + static_cast<size_t>(sched.entrySize) * sched.count &&
                (p - sched.elements) % sched.entrySize == 0) {
                j.Int((p - sched.elements) / sched.entrySize);
            } else {
                j.Str("@ext");
            }
        };
        j.Open('{');
        j.Key("flag"); j.Int(node->flag);
        j.Key("anim");
        j.Open('{');
        j.Key("deltaTimeScale"); j.Float(a.deltaTimeScale);
        j.Key("currentTime"); j.Float(a.currentTime);
        j.Key("flag"); j.Hex(a.flag);
        j.Key("prev"); schedRef(a.prev);
        j.Key("next"); schedRef(a.next);
        j.Key("last"); schedRef(a.last);
        j.Key("keyframeLists");
        if (hasSched) {
            j.Open('[');
            for (int32_t i = 0; i < sched.count; ++i) {
                const _rt2dAnimKeyFrameSched* s = reinterpret_cast<const _rt2dAnimKeyFrameSched*>(sched.elements + sched.entrySize * i);
                j.Open('{');
                j.Key("time"); j.Float(s->time);
                j.Key("kfl"); KeyFrameList(j, s->keyframeList);
                j.Close('}');
            }
            j.Close(']');
        } else {
            j.Null();
        }
        j.Close('}');
        j.Key("parent"); j.Int(node->parent);
        j.Key("posInParentScene"); j.Int(node->posInParentScene);
        j.Key("props");
        j.Open('{');
        j.Key("scene"); Ref(j, node->props.scene);
        ListView v;
        j.Key("directory");
        if (List(node->props.directory, "directory", &v)) {
            j.Open('[');
            for (int32_t i = 0; i < v.count; ++i) Ref(j, *reinterpret_cast<Rt2dObject* const*>(v.elements + v.entrySize * i));
            j.Close(']');
        } else {
            j.Null();
        }
        j.Key("labels");
        if (List(node->props.labels, "props labels", &v)) {
            j.Open('{');
            j.Key("count"); j.Int(v.count);
            j.Key("entrySize"); j.Int(v.entrySize);
            j.Close('}');
        } else {
            j.Null();
        }
        j.Key("sceneCurrentState");
        if (List(node->props.sceneCurrentState, "sceneCurrentState", &v)) {
            j.Open('[');
            for (int32_t i = 0; i < v.count; ++i) Update(j, reinterpret_cast<const Rt2dAnimObjectUpdate*>(v.elements + v.entrySize * i));
            j.Close(']');
        } else {
            j.Null();
        }
        j.Close('}');
        j.Key("celList");
        if (const Rt2dCelList* cl = node->celList) {
            j.Open('{');
            j.Key("flag"); j.Hex(cl->flag);
            j.Key("cels");
            j.Open('[');
            if (List(cl->cel, "cels", &v)) {
                for (int32_t i = 0; i < v.count; ++i) {
                    const Rt2dCel* c = reinterpret_cast<const Rt2dCel*>(v.elements + v.entrySize * i);
                    j.Open('{');
                    j.Key("strLabelIndex"); j.Int(c->strLabelIndex);
                    j.Key("celIndex"); j.Int(c->celIndex);
                    j.Key("buttonIndices");
                    ListView b;
                    if (List(c->buttonIndices, "cel buttons", &b)) {
                        j.Open('[');
                        for (int32_t k = 0; k < b.count; ++k) j.Int(*reinterpret_cast<const RwInt32*>(b.elements + b.entrySize * k));
                        j.Close(']');
                    } else {
                        j.Null();
                    }
                    j.Key("messageListIndex"); j.Int(c->messageListIndex);
                    j.Close('}');
                }
            }
            j.Close(']');
            j.Close('}');
        } else {
            j.Null();
        }
        j.Close('}');
    }
};

}  // namespace

std::string Rt2dDebugDumpMaestro(const Rt2dMaestro* maestro) {
    if (maestro == nullptr) return "null";
    Walker walker;
    return walker.Maestro(maestro);
}

bool Rt2dDebugDumpSceneVisible(const Rt2dMaestro* maestro) {
    return maestro != nullptr && maestro->scene != nullptr && (maestro->scene->flag & 4) != 0;
}

bool Rt2dDebugDumpWrite(const char* path, const char* tag, uint32_t frame, const Rt2dDebugDumpUI* uis,
                        int32_t count) {
    Json j;
    j.Open('{');
    j.Key("format"); j.Str("maestro-dump-1");
    j.Key("source"); j.Str("native");
    j.Key("tag"); j.Str(tag != nullptr ? tag : "");
    j.Key("time"); j.Null();
    j.Key("frame"); j.Int(frame);
    j.Key("uis");
    j.Open('[');
    for (int32_t i = 0; i < count; ++i) {
        const Rt2dDebugDumpUI& u = uis[i];
        j.Open('{');
        j.Key("index"); j.Int(u.index);
        j.Key("flags44"); j.Hex(u.flags44);
        j.Key("sceneVisible"); j.Bool(u.sceneVisible);
        j.Key("drawn"); j.Bool(u.drawn);
        j.Key("maestro"); j.Raw(Rt2dDebugDumpMaestro(u.maestro));
        j.Close('}');
    }
    j.Close(']');
    j.Key("frameAfter"); j.Int(frame);
    j.Close('}');
    FILE* f = std::fopen(path, "wb");
    if (f == nullptr) return false;
    const bool ok = std::fwrite(j.s.data(), 1, j.s.size(), f) == j.s.size();
    return std::fclose(f) == 0 && ok;
}
