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

#include "../../Graphics/RibbonTrail.h"
#include "../../Graphics/Material.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterRibbonTrail(kaguya::State& lua)
{
    using namespace kaguya;

    // [Enum] TrailType
    // [Variable] TT_FACE_CAMERA
    lua["TT_FACE_CAMERA"] = TT_FACE_CAMERA;
    // [Variable] TT_BONE
    lua["TT_BONE"] = TT_BONE;

    // [Class] RibbonTrail : Drawable
    lua["RibbonTrail"].setClass(UserdataMetatable<RibbonTrail, Drawable>()
        .addStaticFunction("new", &CreateObject<RibbonTrail>)

        // [Method] void SetMaterial(Material* material)
        .addFunction("SetMaterial", &RibbonTrail::SetMaterial)
        // [Method] void SetVertexDistance(float length)
        .addFunction("SetVertexDistance", &RibbonTrail::SetVertexDistance)
        // [Method] void SetWidth(float width)
        .addFunction("SetWidth", &RibbonTrail::SetWidth)
        // [Method] void SetStartColor(const Color& color)
        .addFunction("SetStartColor", &RibbonTrail::SetStartColor)
        // [Method] void SetEndColor(const Color& color)
        .addFunction("SetEndColor", &RibbonTrail::SetEndColor)
        // [Method] void SetStartScale(float startScale)
        .addFunction("SetStartScale", &RibbonTrail::SetStartScale)
        // [Method] void SetEndScale(float endScale)
        .addFunction("SetEndScale", &RibbonTrail::SetEndScale)
        // [Method] void SetTrailType(TrailType type)
        .addFunction("SetTrailType", &RibbonTrail::SetTrailType)
        // [Method] void SetSorted(bool enable)
        .addFunction("SetSorted", &RibbonTrail::SetSorted)
        // [Method] void SetLifetime(float time)
        .addFunction("SetLifetime", &RibbonTrail::SetLifetime)
        // [Method] void SetEmitting(bool emitting)
        .addFunction("SetEmitting", &RibbonTrail::SetEmitting)
        // [Method] void SetUpdateInvisible(bool enable)
        .addFunction("SetUpdateInvisible", &RibbonTrail::SetUpdateInvisible)
        // [Method] void SetTailColumn(unsigned tailColumn)
        .addFunction("SetTailColumn", &RibbonTrail::SetTailColumn)
        // [Method] void SetAnimationLodBias(float bias)
        .addFunction("SetAnimationLodBias", &RibbonTrail::SetAnimationLodBias)
        
        // [Method] void Commit()
        .addFunction("Commit", &RibbonTrail::Commit)
        
        // [Method] Material* GetMaterial() const
        .addFunction("GetMaterial", &RibbonTrail::GetMaterial)
        // [Method] float GetVertexDistance() const
        .addFunction("GetVertexDistance", &RibbonTrail::GetVertexDistance)
        // [Method] float GetWidth() const
        .addFunction("GetWidth", &RibbonTrail::GetWidth)
        // [Method] const Color& GetStartColor() const
        .addFunction("GetStartColor", &RibbonTrail::GetStartColor)
        // [Method] const Color& GetEndColor() const
        .addFunction("GetEndColor", &RibbonTrail::GetEndColor)
        // [Method] float GetStartScale() const
        .addFunction("GetStartScale", &RibbonTrail::GetStartScale)
        // [Method] float GetEndScale() const
        .addFunction("GetEndScale", &RibbonTrail::GetEndScale)
        // [Method] bool IsSorted() const
        .addFunction("IsSorted", &RibbonTrail::IsSorted)
        // [Method] float GetLifetime() const
        .addFunction("GetLifetime", &RibbonTrail::GetLifetime)
        // [Method] float GetAnimationLodBias() const
        .addFunction("GetAnimationLodBias", &RibbonTrail::GetAnimationLodBias)
        // [Method] TrailType GetTrailType() const
        .addFunction("GetTrailType", &RibbonTrail::GetTrailType)
        // [Method] unsigned GetTailColumn() const
        .addFunction("GetTailColumn", &RibbonTrail::GetTailColumn)
        // [Method] bool IsEmitting() const
        .addFunction("IsEmitting", &RibbonTrail::IsEmitting)
        // [Method] bool GetUpdateInvisible() const
        .addFunction("GetUpdateInvisible", &RibbonTrail::GetUpdateInvisible)

        // [Property] Material* material
        .addProperty("material", &RibbonTrail::GetMaterial, &RibbonTrail::SetMaterial)
        // [Property] float vertexDistance
        .addProperty("vertexDistance", &RibbonTrail::GetVertexDistance, &RibbonTrail::SetVertexDistance)
        // [Property] float width
        .addProperty("width", &RibbonTrail::GetWidth, &RibbonTrail::SetWidth)
        // [Property] const Color& startColor
        .addProperty("startColor", &RibbonTrail::GetStartColor, &RibbonTrail::SetStartColor)
        // [Property] const Color& endColor
        .addProperty("endColor", &RibbonTrail::GetEndColor, &RibbonTrail::SetEndColor)
        // [Property] float startScale
        .addProperty("startScale", &RibbonTrail::GetStartScale, &RibbonTrail::SetStartScale)
        // [Property] float endScale
        .addProperty("endScale", &RibbonTrail::GetEndScale, &RibbonTrail::SetEndScale)
        // [Property] bool sorted
        .addProperty("sorted", &RibbonTrail::IsSorted, &RibbonTrail::SetSorted)
        // [Property] float lifetime
        .addProperty("lifetime", &RibbonTrail::GetLifetime, &RibbonTrail::SetLifetime)
        // [Property] float animationLodBias
        .addProperty("animationLodBias", &RibbonTrail::GetAnimationLodBias, &RibbonTrail::SetAnimationLodBias)
        // [Property] TrailType trailType
        .addProperty("trailType", &RibbonTrail::GetTrailType, &RibbonTrail::SetTrailType)
        // [Property] unsigned tailColumn
        .addProperty("tailColumn", &RibbonTrail::GetTailColumn, &RibbonTrail::SetTailColumn)
        // [Property] bool emitting
        .addProperty("emitting", &RibbonTrail::IsEmitting, &RibbonTrail::SetEmitting)
        // [Property] bool updateInvisible
        .addProperty("updateInvisible", &RibbonTrail::GetUpdateInvisible, &RibbonTrail::SetUpdateInvisible)
        );
}
}

