//
// Copyright (c) 2008-2016 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../../Precompiled.h"

#include "../../Graphics/DecalSet.h"
#include "../../Graphics/Material.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

//static bool DecalSetAddDecal0(DecalSet* self, Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, float size, float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV)
//{
//    return self->AddDecal(target, worldPosition, worldRotation, size, aspectRatio, depth, topLeftUV, bottomRightUV);
//}
//
//static bool DecalSetAddDecal1(DecalSet* self, Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, float size, float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV, float timeToLive)
//{
//    return self->AddDecal(target, worldPosition, worldRotation, size, aspectRatio, depth, topLeftUV, bottomRightUV, timeToLive);
//}
//
//static bool DecalSetAddDecal2(DecalSet* self, Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, float size, float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV, float timeToLive, float normalCutoff)
//{
//    return self->AddDecal(target, worldPosition, worldRotation, size, aspectRatio, depth, topLeftUV, bottomRightUV, timeToLive, normalCutoff);
//}
//
//static bool DecalSetAddDecal3(DecalSet* self, Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, float size, float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV, float timeToLive, float normalCutoff, unsigned int subGeometry)
//{
//    return self->AddDecal(target, worldPosition, worldRotation, size, aspectRatio, depth, topLeftUV, bottomRightUV, timeToLive, normalCutoff, subGeometry);
//}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(DecalSetAddDecal, DecalSet, AddDecal, 8, 11);

void RegisterDecalSet(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] DecalSet : Drawable
    lua["DecalSet"].setClass(UserdataMetatable<DecalSet, Drawable>()
        // [Constructor] DecalSet()
        .addStaticFunction("new", &CreateObject<DecalSet>)

        // [Method] void SetMaterial(Material* material)
        .addFunction("SetMaterial", &DecalSet::SetMaterial)
        // [Method] void SetMaxVertices(unsigned num)
        .addFunction("SetMaxVertices", &DecalSet::SetMaxVertices)
        // [Method] void SetMaxIndices(unsigned num)
        .addFunction("SetMaxIndices", &DecalSet::SetMaxIndices)
        
        // [Method]  bool AddDecal(Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, float size, float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV, float timeToLive = 0.0f, float normalCutoff = 0.1f, unsigned subGeometry = M_MAX_UNSIGNED)
        // .addFunction("AddDecal", DecalSetAddDecal())

        // [Method] void RemoveDecals(unsigned num)
        .addFunction("RemoveDecals", &DecalSet::RemoveDecals)
        // [Method] void RemoveAllDecals()
        .addFunction("RemoveAllDecals", &DecalSet::RemoveAllDecals)

        // [Method] Material* GetMaterial() const
        .addFunction("GetMaterial", &DecalSet::GetMaterial)
        // [Method] unsigned GetNumDecals() const
        .addFunction("GetNumDecals", &DecalSet::GetNumDecals)
        // [Method] unsigned GetNumVertices() const
        .addFunction("GetNumVertices", &DecalSet::GetNumVertices)
        // [Method] unsigned GetNumIndices() const
        .addFunction("GetNumIndices", &DecalSet::GetNumIndices)
        // [Method] unsigned GetMaxVertices() const
        .addFunction("GetMaxVertices", &DecalSet::GetMaxVertices)
        // [Method] unsigned GetMaxIndices() const
        .addFunction("GetMaxIndices", &DecalSet::GetMaxIndices)

        // [Property] Material* material
        .addProperty("material", &DecalSet::GetMaterial, &DecalSet::SetMaterial)
        // [Property(WriteOnly)] unsigned numDecals
        .addProperty("numDecals", &DecalSet::GetNumDecals)
        // [Property(WriteOnly)] unsigned numVertices
        .addProperty("numVertices", &DecalSet::GetNumVertices)
        // [Property(WriteOnly)] unsigned numIndices
        .addProperty("numIndices", &DecalSet::GetNumIndices)
        // [Property] unsigned maxVertices
        .addProperty("maxVertices", &DecalSet::GetMaxVertices, &DecalSet::SetMaxVertices)
        // [Property] unsigned maxIndices
        .addProperty("maxIndices", &DecalSet::GetMaxIndices, &DecalSet::SetMaxIndices)
        );
}
}

