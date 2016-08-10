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

    // [Class] Zone : Drawable
    lua["Zone"].setClass(UserdataMetatable<Zone, Drawable>()
        // [Constructor] Zone()
        .addStaticFunction("new", &CreateObject<Zone>)

        // [Method] void SetBoundingBox(const BoundingBox& box)
        .addFunction("SetBoundingBox", &Zone::SetBoundingBox)
        // [Method] void SetAmbientColor(const Color& color)
        .addFunction("SetAmbientColor", &Zone::SetAmbientColor)
        // [Method] void SetFogColor(const Color& color)
        .addFunction("SetFogColor", &Zone::SetFogColor)
        // [Method] void SetFogStart(float start)
        .addFunction("SetFogStart", &Zone::SetFogStart)
        // [Method] void SetFogEnd(float end)
        .addFunction("SetFogEnd", &Zone::SetFogEnd)
        // [Method] void SetFogHeight(float height)
        .addFunction("SetFogHeight", &Zone::SetFogHeight)
        // [Method] void SetFogHeightScale(float scale)
        .addFunction("SetFogHeightScale", &Zone::SetFogHeightScale)
        // [Method] void SetPriority(int priority)
        .addFunction("SetPriority", &Zone::SetPriority)
        // [Method] void SetHeightFog(bool enable)
        .addFunction("SetHeightFog", &Zone::SetHeightFog)
        // [Method] void SetOverride(bool enable)
        .addFunction("SetOverride", &Zone::SetOverride)
        // [Method] void SetAmbientGradient(bool enable)
        .addFunction("SetAmbientGradient", &Zone::SetAmbientGradient)
        // [Method] void SetZoneTexture(Texture* texture)
        .addFunction("SetZoneTexture", &Zone::SetZoneTexture)
        
        // [Method] const Matrix3x4& GetInverseWorldTransform() const
        .addFunction("GetInverseWorldTransform", &Zone::GetInverseWorldTransform)
        // [Method] const Color& GetAmbientColor() const
        .addFunction("GetAmbientColor", &Zone::GetAmbientColor)
        // [Method] const Color& GetAmbientStartColor()
        .addFunction("GetAmbientStartColor", &Zone::GetAmbientStartColor)
        // [Method] const Color& GetAmbientEndColor()
        .addFunction("GetAmbientEndColor", &Zone::GetAmbientEndColor)
        // [Method] const Color& GetFogColor() const
        .addFunction("GetFogColor", &Zone::GetFogColor)
        // [Method] float GetFogStart() const
        .addFunction("GetFogStart", &Zone::GetFogStart)
        // [Method] float GetFogEnd() const
        .addFunction("GetFogEnd", &Zone::GetFogEnd)
        // [Method] float GetFogHeight() const
        .addFunction("GetFogHeight", &Zone::GetFogHeight)
        // [Method] float GetFogHeightScale() const
        .addFunction("GetFogHeightScale", &Zone::GetFogHeightScale)
        // [Method] int GetPriority() const
        .addFunction("GetPriority", &Zone::GetPriority)
        // [Method] bool GetHeightFog() const
        .addFunction("GetHeightFog", &Zone::GetHeightFog)
        // [Method] bool GetOverride() const
        .addFunction("GetOverride", &Zone::GetOverride)
        // [Method] bool GetAmbientGradient() const
        .addFunction("GetAmbientGradient", &Zone::GetAmbientGradient)
        // [Method] Texture* GetZoneTexture() const
        .addFunction("GetZoneTexture", &Zone::GetZoneTexture)
        
        // [Method] bool IsInside(const Vector3& point) const
        .addFunction("IsInside", &Zone::IsInside)

        // [Property(Readonly)] const Matrix3x4& inverseWorldTransform
        .addProperty("inverseWorldTransform", &Zone::GetInverseWorldTransform)
        // [Property] const Color& ambientColor
        .addProperty("ambientColor", &Zone::GetAmbientColor, &Zone::SetAmbientColor)
        // [Property(Readonly)] const Color& ambientStartColor
        .addProperty("ambientStartColor", &Zone::GetAmbientStartColor)
        // [Property(Readonly)] const Color& ambientEndColor
        .addProperty("ambientEndColor", &Zone::GetAmbientEndColor)
        // [Property] const Color& fogColor
        .addProperty("fogColor", &Zone::GetFogColor, &Zone::SetFogColor)
        // [Property] float fogStart
        .addProperty("fogStart", &Zone::GetFogStart, &Zone::SetFogStart)
        // [Property] float fogEnd
        .addProperty("fogEnd", &Zone::GetFogEnd, &Zone::SetFogEnd)
        // [Property] float fogHeight
        .addProperty("fogHeight", &Zone::GetFogHeight, &Zone::SetFogHeight)
        // [Property] float fogHeightScale
        .addProperty("fogHeightScale", &Zone::GetFogHeightScale, &Zone::SetFogHeightScale)
        // [Property] int priority
        .addProperty("priority", &Zone::GetPriority, &Zone::SetPriority)
        // [Property] bool heightFog
        .addProperty("heightFog", &Zone::GetHeightFog, &Zone::SetHeightFog)
        // [Property] bool override
        .addProperty("override", &Zone::GetOverride, &Zone::SetOverride)
        // [Property] bool ambientGradient
        .addProperty("ambientGradient", &Zone::GetAmbientGradient, &Zone::SetAmbientGradient)
        // [Property] Texture* zoneTexture
        .addProperty("zoneTexture", &Zone::GetZoneTexture, &Zone::SetZoneTexture)
        // [Property(Writeonly)] void boundingBox
        .addProperty("boundingBox", &Zone::SetBoundingBox)
        );
}
}

