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

#ifdef URHO3D_URHO2D

#include "../../Precompiled.h"

#include "../../Graphics/Material.h"
#include "../../Urho2D/Sprite2D.h"
#include "../../Urho2D/StaticSprite2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterStaticSprite2D(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] StaticSprite2D : Drawable2D
    lua["StaticSprite2D"].setClass(UserdataMetatable<StaticSprite2D, Drawable2D>()
        // [Constructor] StaticSprite2D()
        .addStaticFunction("new", &CreateObject<StaticSprite2D>)

        // [Method] void SetSprite(Sprite2D* sprite)
        .addFunction("SetSprite", &StaticSprite2D::SetSprite)
        // [Method] void SetBlendMode(BlendMode blendMode)
        .addFunction("SetBlendMode", &StaticSprite2D::SetBlendMode)
        // [Method] void SetFlip(bool flipX, bool flipY)
        .addFunction("SetFlip", &StaticSprite2D::SetFlip)
        // [Method] void SetFlipX(bool flipX)
        .addFunction("SetFlipX", &StaticSprite2D::SetFlipX)
        // [Method] void SetFlipY(bool flipY)
        .addFunction("SetFlipY", &StaticSprite2D::SetFlipY)
        // [Method] void SetColor(const Color& color)
        .addFunction("SetColor", &StaticSprite2D::SetColor)
        // [Method] void SetAlpha(float alpha)
        .addFunction("SetAlpha", &StaticSprite2D::SetAlpha)
        // [Method] void SetUseHotSpot(bool useHotSpot)
        .addFunction("SetUseHotSpot", &StaticSprite2D::SetUseHotSpot)
        // [Method] void SetHotSpot(const Vector2& hotspot)
        .addFunction("SetHotSpot", &StaticSprite2D::SetHotSpot)
        // [Method] void SetCustomMaterial(Material* customMaterial)
        .addFunction("SetCustomMaterial", &StaticSprite2D::SetCustomMaterial)

        // [Method] Sprite2D* GetSprite() const
        .addFunction("GetSprite", &StaticSprite2D::GetSprite)
        // [Method] BlendMode GetBlendMode() const
        .addFunction("GetBlendMode", &StaticSprite2D::GetBlendMode)
        // [Method] bool GetFlipX() const
        .addFunction("GetFlipX", &StaticSprite2D::GetFlipX)
        // [Method] bool GetFlipY() const
        .addFunction("GetFlipY", &StaticSprite2D::GetFlipY)
        // [Method] const Color& GetColor() const
        .addFunction("GetColor", &StaticSprite2D::GetColor)
        // [Method] float GetAlpha() const
        .addFunction("GetAlpha", &StaticSprite2D::GetAlpha)
        // [Method] bool GetUseHotSpot() const
        .addFunction("GetUseHotSpot", &StaticSprite2D::GetUseHotSpot)
        // [Method] const Vector2& GetHotSpot() const
        .addFunction("GetHotSpot", &StaticSprite2D::GetHotSpot)
        // [Method] Material* GetCustomMaterial() const
        .addFunction("GetCustomMaterial", &StaticSprite2D::GetCustomMaterial)

        // [Property] Sprite2D* sprite
        .addProperty("sprite", &StaticSprite2D::GetSprite, &StaticSprite2D::SetSprite)
        // [Property] BlendMode blendMode
        .addProperty("blendMode", &StaticSprite2D::GetBlendMode, &StaticSprite2D::SetBlendMode)
        // [Property] bool flipX
        .addProperty("flipX", &StaticSprite2D::GetFlipX, &StaticSprite2D::SetFlipX)
        // [Property] bool flipY
        .addProperty("flipY", &StaticSprite2D::GetFlipY, &StaticSprite2D::SetFlipY)
        // [Property] const Color& color
        .addProperty("color", &StaticSprite2D::GetColor, &StaticSprite2D::SetColor)
        // [Property] float alpha
        .addProperty("alpha", &StaticSprite2D::GetAlpha, &StaticSprite2D::SetAlpha)
        // [Property] bool useHotSpot
        .addProperty("useHotSpot", &StaticSprite2D::GetUseHotSpot, &StaticSprite2D::SetUseHotSpot)
        // [Property] const Vector2& hotSpot
        .addProperty("hotSpot", &StaticSprite2D::GetHotSpot, &StaticSprite2D::SetHotSpot)
        // [Property] Material* customMaterial
        .addProperty("customMaterial", &StaticSprite2D::GetCustomMaterial, &StaticSprite2D::SetCustomMaterial)
    );
}
}

#endif
