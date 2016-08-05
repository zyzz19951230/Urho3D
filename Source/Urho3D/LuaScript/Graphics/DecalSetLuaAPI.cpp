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

static bool DecalSetAddDecal0(DecalSet* self, Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, float size, float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV)
{
    return self->AddDecal(target, worldPosition, worldRotation, size, aspectRatio, depth, topLeftUV, bottomRightUV);
}

static bool DecalSetAddDecal1(DecalSet* self, Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, float size, float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV, float timeToLive)
{
    return self->AddDecal(target, worldPosition, worldRotation, size, aspectRatio, depth, topLeftUV, bottomRightUV, timeToLive);
}

static bool DecalSetAddDecal2(DecalSet* self, Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, float size, float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV, float timeToLive, float normalCutoff)
{
    return self->AddDecal(target, worldPosition, worldRotation, size, aspectRatio, depth, topLeftUV, bottomRightUV, timeToLive, normalCutoff);
}

static bool DecalSetAddDecal3(DecalSet* self, Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, float size, float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV, float timeToLive, float normalCutoff, unsigned int subGeometry)
{
    return self->AddDecal(target, worldPosition, worldRotation, size, aspectRatio, depth, topLeftUV, bottomRightUV, timeToLive, normalCutoff, subGeometry);
}

// KAGUYA_MEMBER_FUNCTION_OVERLOADS(DecalSetAddDecal, DecalSet, AddDecal, 8, 11);

void RegisterDecalSet(kaguya::State& lua)
{
    using namespace kaguya;

    lua["DecalSet"].setClass(UserdataMetatable<DecalSet, Drawable>()
        .addStaticFunction("new", &CreateObject<DecalSet>)

        .addFunction("SetMaterial", &DecalSet::SetMaterial)
        .addFunction("SetMaxVertices", &DecalSet::SetMaxVertices)
        .addFunction("SetMaxIndices", &DecalSet::SetMaxIndices)
        
        ADD_OVERLOADED_FUNCTIONS_4(DecalSet, AddDecal)
        // .addFunction("AddDecal", DecalSetAddDecal())

        .addFunction("RemoveDecals", &DecalSet::RemoveDecals)
        .addFunction("RemoveAllDecals", &DecalSet::RemoveAllDecals)

        .addFunction("GetMaterial", &DecalSet::GetMaterial)
        .addFunction("GetNumDecals", &DecalSet::GetNumDecals)
        .addFunction("GetNumVertices", &DecalSet::GetNumVertices)
        .addFunction("GetNumIndices", &DecalSet::GetNumIndices)
        .addFunction("GetMaxVertices", &DecalSet::GetMaxVertices)
        .addFunction("GetMaxIndices", &DecalSet::GetMaxIndices)

        .addProperty("material", &DecalSet::GetMaterial, &DecalSet::SetMaterial)
        .addProperty("numDecals", &DecalSet::GetNumDecals)
        .addProperty("numVertices", &DecalSet::GetNumVertices)
        .addProperty("numIndices", &DecalSet::GetNumIndices)
        .addProperty("maxVertices", &DecalSet::GetMaxVertices, &DecalSet::SetMaxVertices)
        .addProperty("maxIndices", &DecalSet::GetMaxIndices, &DecalSet::SetMaxIndices)
        );
}
}

