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

    // enum TrailType;
    lua["TT_FACE_CAMERA"] = TT_FACE_CAMERA;
    lua["TT_BONE"] = TT_BONE;

    lua["RibbonTrail"].setClass(UserdataMetatable<RibbonTrail, Drawable>()
        .addStaticFunction("new", &CreateObject<RibbonTrail>)

        .addFunction("SetMaterial", &RibbonTrail::SetMaterial)
        .addFunction("SetVertexDistance", &RibbonTrail::SetVertexDistance)
        .addFunction("SetWidth", &RibbonTrail::SetWidth)
        .addFunction("SetStartColor", &RibbonTrail::SetStartColor)
        .addFunction("SetEndColor", &RibbonTrail::SetEndColor)
        .addFunction("SetStartScale", &RibbonTrail::SetStartScale)
        .addFunction("SetEndScale", &RibbonTrail::SetEndScale)
        .addFunction("SetTrailType", &RibbonTrail::SetTrailType)
        .addFunction("SetSorted", &RibbonTrail::SetSorted)
        .addFunction("SetLifetime", &RibbonTrail::SetLifetime)
        .addFunction("SetEmitting", &RibbonTrail::SetEmitting)
        .addFunction("SetUpdateInvisible", &RibbonTrail::SetUpdateInvisible)
        .addFunction("SetTailColumn", &RibbonTrail::SetTailColumn)
        .addFunction("SetAnimationLodBias", &RibbonTrail::SetAnimationLodBias)
        
        .addFunction("Commit", &RibbonTrail::Commit)
        
        .addFunction("GetMaterial", &RibbonTrail::GetMaterial)
        .addFunction("GetVertexDistance", &RibbonTrail::GetVertexDistance)
        .addFunction("GetWidth", &RibbonTrail::GetWidth)
        .addFunction("GetStartColor", &RibbonTrail::GetStartColor)
        .addFunction("GetEndColor", &RibbonTrail::GetEndColor)
        .addFunction("GetStartScale", &RibbonTrail::GetStartScale)
        .addFunction("GetEndScale", &RibbonTrail::GetEndScale)
        .addFunction("IsSorted", &RibbonTrail::IsSorted)
        .addFunction("GetLifetime", &RibbonTrail::GetLifetime)
        .addFunction("GetAnimationLodBias", &RibbonTrail::GetAnimationLodBias)
        .addFunction("GetTrailType", &RibbonTrail::GetTrailType)
        .addFunction("GetTailColumn", &RibbonTrail::GetTailColumn)
        .addFunction("IsEmitting", &RibbonTrail::IsEmitting)
        .addFunction("GetUpdateInvisible", &RibbonTrail::GetUpdateInvisible)

        .addProperty("material", &RibbonTrail::GetMaterial, &RibbonTrail::SetMaterial)
        .addProperty("vertexDistance", &RibbonTrail::GetVertexDistance, &RibbonTrail::SetVertexDistance)
        .addProperty("width", &RibbonTrail::GetWidth, &RibbonTrail::SetWidth)
        .addProperty("startColor", &RibbonTrail::GetStartColor, &RibbonTrail::SetStartColor)
        .addProperty("endColor", &RibbonTrail::GetEndColor, &RibbonTrail::SetEndColor)
        .addProperty("startScale", &RibbonTrail::GetStartScale, &RibbonTrail::SetStartScale)
        .addProperty("endScale", &RibbonTrail::GetEndScale, &RibbonTrail::SetEndScale)
        .addProperty("sorted", &RibbonTrail::IsSorted, &RibbonTrail::SetSorted)
        .addProperty("lifetime", &RibbonTrail::GetLifetime, &RibbonTrail::SetLifetime)
        .addProperty("animationLodBias", &RibbonTrail::GetAnimationLodBias, &RibbonTrail::SetAnimationLodBias)
        .addProperty("trailType", &RibbonTrail::GetTrailType, &RibbonTrail::SetTrailType)
        .addProperty("tailColumn", &RibbonTrail::GetTailColumn, &RibbonTrail::SetTailColumn)
        .addProperty("emitting", &RibbonTrail::IsEmitting, &RibbonTrail::SetEmitting)
        .addProperty("updateInvisible", &RibbonTrail::GetUpdateInvisible, &RibbonTrail::SetUpdateInvisible)
        );
}
}

