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

#include "../../Graphics/Texture2D.h"
#include "../../Urho2D/Sprite2D.h"
#include "../../Urho2D/SpriteSheet2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterSprite2D(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Sprite2D : Resource
    lua["Sprite2D"].setClass(UserdataMetatable<Sprite2D, Resource>()
        .addStaticFunction("new", &CreateObject<Sprite2D>)

        // [Method] void SetTexture(Texture2D* texture)
        .addFunction("SetTexture", &Sprite2D::SetTexture)
        // [Method] void SetRectangle(const IntRect& rectangle)
        .addFunction("SetRectangle", &Sprite2D::SetRectangle)
        // [Method] void SetHotSpot(const Vector2& hotSpot)
        .addFunction("SetHotSpot", &Sprite2D::SetHotSpot)
        // [Method] void SetOffset(const IntVector2& offset)
        .addFunction("SetOffset", &Sprite2D::SetOffset)
        // [Method] void SetTextureEdgeOffset(float offset)
        .addFunction("SetTextureEdgeOffset", &Sprite2D::SetTextureEdgeOffset)
        // [Method] void SetSpriteSheet(SpriteSheet2D* spriteSheet)
        .addFunction("SetSpriteSheet", &Sprite2D::SetSpriteSheet)

        // [Method] Texture2D* GetTexture() const
        .addFunction("GetTexture", &Sprite2D::GetTexture)
        // [Method] const IntRect& GetRectangle() const
        .addFunction("GetRectangle", &Sprite2D::GetRectangle)
        // [Method] const Vector2& GetHotSpot() const
        .addFunction("GetHotSpot", &Sprite2D::GetHotSpot)
        // [Method] const IntVector2& GetOffset() const
        .addFunction("GetOffset", &Sprite2D::GetOffset)
        // [Method] float GetTextureEdgeOffset() const
        .addFunction("GetTextureEdgeOffset", &Sprite2D::GetTextureEdgeOffset)
        // [Method] SpriteSheet2D* GetSpriteSheet() const
        .addFunction("GetSpriteSheet", &Sprite2D::GetSpriteSheet)

        // [Property] Texture2D* texture
        .addProperty("texture", &Sprite2D::GetTexture, &Sprite2D::SetTexture)
        // [Property] const IntRect& rectangle
        .addProperty("rectangle", &Sprite2D::GetRectangle, &Sprite2D::SetRectangle)
        // [Property] const Vector2& hotSpot
        .addProperty("hotSpot", &Sprite2D::GetHotSpot, &Sprite2D::SetHotSpot)
        // [Property] const IntVector2& offset
        .addProperty("offset", &Sprite2D::GetOffset, &Sprite2D::SetOffset)
        // [Property] float textureEdgeOffset
        .addProperty("textureEdgeOffset", &Sprite2D::GetTextureEdgeOffset, &Sprite2D::SetTextureEdgeOffset)
        // [Property] SpriteSheet2D* spriteSheet
        .addProperty("spriteSheet", &Sprite2D::GetSpriteSheet, &Sprite2D::SetSpriteSheet)
    );
}
}

#endif
