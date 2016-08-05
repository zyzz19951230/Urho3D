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

    lua["Sprite2D"].setClass(UserdataMetatable<Sprite2D, Resource>()
        .addStaticFunction("new", &CreateObject<Sprite2D>)

        .addFunction("SetTexture", &Sprite2D::SetTexture)
        .addFunction("SetRectangle", &Sprite2D::SetRectangle)
        .addFunction("SetHotSpot", &Sprite2D::SetHotSpot)
        .addFunction("SetOffset", &Sprite2D::SetOffset)
        .addFunction("SetTextureEdgeOffset", &Sprite2D::SetTextureEdgeOffset)
        .addFunction("SetSpriteSheet", &Sprite2D::SetSpriteSheet)

        .addFunction("GetTexture", &Sprite2D::GetTexture)
        .addFunction("GetRectangle", &Sprite2D::GetRectangle)
        .addFunction("GetHotSpot", &Sprite2D::GetHotSpot)
        .addFunction("GetOffset", &Sprite2D::GetOffset)
        .addFunction("GetTextureEdgeOffset", &Sprite2D::GetTextureEdgeOffset)
        .addFunction("GetSpriteSheet", &Sprite2D::GetSpriteSheet)

        .addProperty("texture", &Sprite2D::GetTexture, &Sprite2D::SetTexture)
        .addProperty("rectangle", &Sprite2D::GetRectangle, &Sprite2D::SetRectangle)
        .addProperty("hotSpot", &Sprite2D::GetHotSpot, &Sprite2D::SetHotSpot)
        .addProperty("offset", &Sprite2D::GetOffset, &Sprite2D::SetOffset)
        .addProperty("textureEdgeOffset", &Sprite2D::GetTextureEdgeOffset, &Sprite2D::SetTextureEdgeOffset)
        .addProperty("spriteSheet", &Sprite2D::GetSpriteSheet, &Sprite2D::SetSpriteSheet)
    );
}
}

#endif
