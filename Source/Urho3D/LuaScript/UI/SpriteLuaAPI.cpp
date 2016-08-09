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

    // [Class] Sprite : UIElement
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

        // [Method] void SetRotation(float angle)
        .addFunction("SetRotation", &Sprite::SetRotation)
        // [Method] void SetTexture(Texture* texture)
        .addFunction("SetTexture", &Sprite::SetTexture)
        // [Method] void SetImageRect(const IntRect& rect)
        .addFunction("SetImageRect", &Sprite::SetImageRect)
        // [Method] void SetFullImageRect()
        .addFunction("SetFullImageRect", &Sprite::SetFullImageRect)
        // [Method] void SetBlendMode(BlendMode mode)
        .addFunction("SetBlendMode", &Sprite::SetBlendMode)

        // [Method] const Vector2& GetPosition() const
        .addFunction("GetPosition", &Sprite::GetPosition)
        // [Method] const IntVector2& GetHotSpot() const
        .addFunction("GetHotSpot", &Sprite::GetHotSpot)
        // [Method] const Vector2& GetScale() const
        .addFunction("GetScale", &Sprite::GetScale)
        // [Method] float GetRotation() const
        .addFunction("GetRotation", &Sprite::GetRotation)
        // [Method] Texture* GetTexture() const
        .addFunction("GetTexture", &Sprite::GetTexture)
        // [Method] const IntRect& GetImageRect() const
        .addFunction("GetImageRect", &Sprite::GetImageRect)
        // [Method] BlendMode GetBlendMode() const
        .addFunction("GetBlendMode", &Sprite::GetBlendMode)

        // [Method] const Matrix3x4& GetTransform() const
        .addFunction("GetTransform", &Sprite::GetTransform)

        // [Property] const Vector2& position
        .addProperty("position", &Sprite::GetPosition, static_cast<void(Sprite::*)(const Vector2&)>(&Sprite::SetPosition))
        // [Property] const IntVector2& hotSpot
        .addProperty("hotSpot", &Sprite::GetHotSpot, static_cast<void(Sprite::*)(const IntVector2&)>(&Sprite::SetHotSpot))
        // [Property] const Vector2& scale
        .addProperty("scale", &Sprite::GetScale, static_cast<void(Sprite::*)(const Vector2&)>(&Sprite::SetScale))
        // [Property] float rotation
        .addProperty("rotation", &Sprite::GetRotation, &Sprite::SetRotation)
        // [Property] Texture* texture
        .addProperty("texture", &Sprite::GetTexture, &Sprite::SetTexture)
        // [Property] const IntRect& imageRect
        .addProperty("imageRect", &Sprite::GetImageRect, &Sprite::SetImageRect)
        // [Property] BlendMode blendMode
        .addProperty("blendMode", &Sprite::GetBlendMode, &Sprite::SetBlendMode)

        // [Property(ReadOnly)] const Matrix3x4& transform
        .addProperty("transform", &Sprite::GetTransform)
        );
}
}

