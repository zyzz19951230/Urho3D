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

    lua["StaticSprite2D"].setClass(UserdataMetatable<StaticSprite2D, Drawable2D>()
        .addStaticFunction("new", &CreateObject<StaticSprite2D>)

        .addFunction("SetSprite", &StaticSprite2D::SetSprite)
        .addFunction("SetBlendMode", &StaticSprite2D::SetBlendMode)
        .addFunction("SetFlip", &StaticSprite2D::SetFlip)
        .addFunction("SetFlipX", &StaticSprite2D::SetFlipX)
        .addFunction("SetFlipY", &StaticSprite2D::SetFlipY)
        .addFunction("SetColor", &StaticSprite2D::SetColor)
        .addFunction("SetAlpha", &StaticSprite2D::SetAlpha)
        .addFunction("SetUseHotSpot", &StaticSprite2D::SetUseHotSpot)
        .addFunction("SetHotSpot", &StaticSprite2D::SetHotSpot)
        .addFunction("SetCustomMaterial", &StaticSprite2D::SetCustomMaterial)

        .addFunction("GetSprite", &StaticSprite2D::GetSprite)
        .addFunction("GetBlendMode", &StaticSprite2D::GetBlendMode)
        .addFunction("GetFlipX", &StaticSprite2D::GetFlipX)
        .addFunction("GetFlipY", &StaticSprite2D::GetFlipY)
        .addFunction("GetColor", &StaticSprite2D::GetColor)
        .addFunction("GetAlpha", &StaticSprite2D::GetAlpha)
        .addFunction("GetUseHotSpot", &StaticSprite2D::GetUseHotSpot)
        .addFunction("GetHotSpot", &StaticSprite2D::GetHotSpot)
        .addFunction("GetCustomMaterial", &StaticSprite2D::GetCustomMaterial)

        .addProperty("sprite", &StaticSprite2D::GetSprite, &StaticSprite2D::SetSprite)
        .addProperty("blendMode", &StaticSprite2D::GetBlendMode, &StaticSprite2D::SetBlendMode)
        .addProperty("flipX", &StaticSprite2D::GetFlipX, &StaticSprite2D::SetFlipX)
        .addProperty("flipY", &StaticSprite2D::GetFlipY, &StaticSprite2D::SetFlipY)
        .addProperty("color", &StaticSprite2D::GetColor, &StaticSprite2D::SetColor)
        .addProperty("alpha", &StaticSprite2D::GetAlpha, &StaticSprite2D::SetAlpha)
        .addProperty("useHotSpot", &StaticSprite2D::GetUseHotSpot, &StaticSprite2D::SetUseHotSpot)
        .addProperty("hotSpot", &StaticSprite2D::GetHotSpot, &StaticSprite2D::SetHotSpot)
        .addProperty("customMaterial", &StaticSprite2D::GetCustomMaterial, &StaticSprite2D::SetCustomMaterial)
    );
}
}

#endif
