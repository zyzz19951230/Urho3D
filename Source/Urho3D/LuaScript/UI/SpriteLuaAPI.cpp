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

#include "../../Graphics/Texture.h"
#include "../../UI/Sprite.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterSprite(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Sprite"].setClass(UserdataMetatable<Sprite, UIElement>()
        .addStaticFunction("new", &CreateObject<Sprite>)

        .addOverloadedFunctions("SetPosition",
            static_cast<void(Sprite::*)(const Vector2&)>(&Sprite::SetPosition),
            static_cast<void(Sprite::*)(float, float)>(&Sprite::SetPosition))

        .addOverloadedFunctions("SetHotSpot",
            static_cast<void(Sprite::*)(const IntVector2&)>(&Sprite::SetHotSpot),
            static_cast<void(Sprite::*)(int, int)>(&Sprite::SetHotSpot))

        .addOverloadedFunctions("SetScale",
            static_cast<void(Sprite::*)(const Vector2&)>(&Sprite::SetScale),
            static_cast<void(Sprite::*)(float, float)>(&Sprite::SetScale),
            static_cast<void(Sprite::*)(float)>(&Sprite::SetScale))

        .addFunction("SetRotation", &Sprite::SetRotation)
        .addFunction("SetTexture", &Sprite::SetTexture)
        .addFunction("SetImageRect", &Sprite::SetImageRect)
        .addFunction("SetFullImageRect", &Sprite::SetFullImageRect)
        .addFunction("SetBlendMode", &Sprite::SetBlendMode)

        .addFunction("GetPosition", &Sprite::GetPosition)
        .addFunction("GetHotSpot", &Sprite::GetHotSpot)
        .addFunction("GetScale", &Sprite::GetScale)
        .addFunction("GetRotation", &Sprite::GetRotation)
        .addFunction("GetTexture", &Sprite::GetTexture)
        .addFunction("GetImageRect", &Sprite::GetImageRect)
        .addFunction("GetBlendMode", &Sprite::GetBlendMode)

        .addFunction("GetTransform", &Sprite::GetTransform)

        .addProperty("position", &Sprite::GetPosition, static_cast<void(Sprite::*)(const Vector2&)>(&Sprite::SetPosition))
        .addProperty("hotSpot", &Sprite::GetHotSpot, static_cast<void(Sprite::*)(const IntVector2&)>(&Sprite::SetHotSpot))
        .addProperty("scale", &Sprite::GetScale, static_cast<void(Sprite::*)(const Vector2&)>(&Sprite::SetScale))
        .addProperty("rotation", &Sprite::GetRotation, &Sprite::SetRotation)
        .addProperty("texture", &Sprite::GetTexture, &Sprite::SetTexture)
        .addProperty("imageRect", &Sprite::GetImageRect, &Sprite::SetImageRect)
        .addProperty("blendMode", &Sprite::GetBlendMode, &Sprite::SetBlendMode)

        .addProperty("transform", &Sprite::GetTransform)
        );
}
}

