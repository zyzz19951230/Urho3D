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
#include "../../UI/BorderImage.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterBorderImage(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] BorderImage : UIElement
    lua["BorderImage"].setClass(UserdataMetatable<BorderImage, UIElement>()
        .addStaticFunction("new", &CreateObject<BorderImage>)

        // [Method] void SetTexture(Texture* texture)
        .addFunction("SetTexture", &BorderImage::SetTexture)
        // [Method] void SetImageRect(const IntRect& rect)
        .addFunction("SetImageRect", &BorderImage::SetImageRect)
        // [Method] void SetFullImageRect()
        .addFunction("SetFullImageRect", &BorderImage::SetFullImageRect)
        // [Method] void SetBorder(const IntRect& rect)
        .addFunction("SetBorder", &BorderImage::SetBorder)
        // [Method] void SetImageBorder(const IntRect& rect)
        .addFunction("SetImageBorder", &BorderImage::SetImageBorder)

        .addOverloadedFunctions("SetHoverOffset",
            static_cast<void(BorderImage::*)(const IntVector2&)>(&BorderImage::SetHoverOffset),
            static_cast<void(BorderImage::*)(int, int)>(&BorderImage::SetHoverOffset))

        // [Method] void SetBlendMode(BlendMode mode)
        .addFunction("SetBlendMode", &BorderImage::SetBlendMode)
        // [Method] void SetTiled(bool enable)
        .addFunction("SetTiled", &BorderImage::SetTiled)

        // [Method] Texture* GetTexture() const
        .addFunction("GetTexture", &BorderImage::GetTexture)
        // [Method] const IntRect& GetImageRect() const
        .addFunction("GetImageRect", &BorderImage::GetImageRect)
        // [Method] const IntRect& GetBorder() const
        .addFunction("GetBorder", &BorderImage::GetBorder)
        // [Method] const IntRect& GetImageBorder() const
        .addFunction("GetImageBorder", &BorderImage::GetImageBorder)
        // [Method] const IntVector2& GetHoverOffset() const
        .addFunction("GetHoverOffset", &BorderImage::GetHoverOffset)
        // [Method] BlendMode GetBlendMode() const
        .addFunction("GetBlendMode", &BorderImage::GetBlendMode)
        // [Method] bool IsTiled() const
        .addFunction("IsTiled", &BorderImage::IsTiled)

        // [Property] Texture* texture
        .addProperty("texture", &BorderImage::GetTexture, &BorderImage::SetTexture)
        // [Property] const IntRect& imageRect
        .addProperty("imageRect", &BorderImage::GetImageRect, &BorderImage::SetImageRect)
        // [Property] const IntRect& border
        .addProperty("border", &BorderImage::GetBorder, &BorderImage::SetBorder)
        // [Property] const IntRect& imageBorder
        .addProperty("imageBorder", &BorderImage::GetImageBorder, &BorderImage::SetImageBorder)
        // [Property] const IntVector2& hoverOffset
        .addProperty("hoverOffset", &BorderImage::GetHoverOffset, static_cast<void(BorderImage::*)(const IntVector2&)>(&BorderImage::SetHoverOffset))
        // [Property] BlendMode blendMode
        .addProperty("blendMode", &BorderImage::GetBlendMode, &BorderImage::SetBlendMode)
        // [Property] bool tiled
        .addProperty("tiled", &BorderImage::IsTiled, &BorderImage::SetTiled)
        );
}
}

