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

#include "../../Graphics/Zone.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterZone(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Zone"].setClass(UserdataMetatable<Zone, Drawable>()
        .addStaticFunction("new", &CreateObject<Zone>)

        .addFunction("SetBoundingBox", &Zone::SetBoundingBox)
        .addFunction("SetAmbientColor", &Zone::SetAmbientColor)
        .addFunction("SetFogColor", &Zone::SetFogColor)
        .addFunction("SetFogStart", &Zone::SetFogStart)
        .addFunction("SetFogEnd", &Zone::SetFogEnd)
        .addFunction("SetFogHeight", &Zone::SetFogHeight)
        .addFunction("SetFogHeightScale", &Zone::SetFogHeightScale)
        .addFunction("SetPriority", &Zone::SetPriority)
        .addFunction("SetHeightFog", &Zone::SetHeightFog)
        .addFunction("SetOverride", &Zone::SetOverride)
        .addFunction("SetAmbientGradient", &Zone::SetAmbientGradient)
        .addFunction("SetZoneTexture", &Zone::SetZoneTexture)
        
        .addFunction("GetInverseWorldTransform", &Zone::GetInverseWorldTransform)
        .addFunction("GetAmbientColor", &Zone::GetAmbientColor)
        .addFunction("GetAmbientStartColor", &Zone::GetAmbientStartColor)
        .addFunction("GetAmbientEndColor", &Zone::GetAmbientEndColor)
        .addFunction("GetFogColor", &Zone::GetFogColor)
        .addFunction("GetFogStart", &Zone::GetFogStart)
        .addFunction("GetFogEnd", &Zone::GetFogEnd)
        .addFunction("GetFogHeight", &Zone::GetFogHeight)
        .addFunction("GetFogHeightScale", &Zone::GetFogHeightScale)
        .addFunction("GetPriority", &Zone::GetPriority)
        .addFunction("GetHeightFog", &Zone::GetHeightFog)
        .addFunction("GetOverride", &Zone::GetOverride)
        .addFunction("GetAmbientGradient", &Zone::GetAmbientGradient)
        .addFunction("GetZoneTexture", &Zone::GetZoneTexture)
        
        .addFunction("IsInside", &Zone::IsInside)

        .addProperty("inverseWorldTransform", &Zone::GetInverseWorldTransform)
        .addProperty("ambientColor", &Zone::GetAmbientColor, &Zone::SetAmbientColor)
        .addProperty("ambientStartColor", &Zone::GetAmbientStartColor)
        .addProperty("ambientEndColor", &Zone::GetAmbientEndColor)
        .addProperty("fogColor", &Zone::GetFogColor, &Zone::SetFogColor)
        .addProperty("fogStart", &Zone::GetFogStart, &Zone::SetFogStart)
        .addProperty("fogEnd", &Zone::GetFogEnd, &Zone::SetFogEnd)
        .addProperty("fogHeight", &Zone::GetFogHeight, &Zone::SetFogHeight)
        .addProperty("fogHeightScale", &Zone::GetFogHeightScale, &Zone::SetFogHeightScale)
        .addProperty("priority", &Zone::GetPriority, &Zone::SetPriority)
        .addProperty("heightFog", &Zone::GetHeightFog, &Zone::SetHeightFog)
        .addProperty("override", &Zone::GetOverride, &Zone::SetOverride)
        .addProperty("ambientGradient", &Zone::GetAmbientGradient, &Zone::SetAmbientGradient)
        .addProperty("zoneTexture", &Zone::GetZoneTexture, &Zone::SetZoneTexture)
        .addProperty("boundingBox", &Zone::SetBoundingBox)
        );
}
}

