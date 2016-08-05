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

    lua["BorderImage"].setClass(UserdataMetatable<BorderImage, UIElement>()
        .addStaticFunction("new", &CreateObject<BorderImage>)

        .addFunction("SetTexture", &BorderImage::SetTexture)
        .addFunction("SetImageRect", &BorderImage::SetImageRect)
        .addFunction("SetFullImageRect", &BorderImage::SetFullImageRect)
        .addFunction("SetBorder", &BorderImage::SetBorder)
        .addFunction("SetImageBorder", &BorderImage::SetImageBorder)

        .addOverloadedFunctions("SetHoverOffset",
            static_cast<void(BorderImage::*)(const IntVector2&)>(&BorderImage::SetHoverOffset),
            static_cast<void(BorderImage::*)(int, int)>(&BorderImage::SetHoverOffset))

        .addFunction("SetBlendMode", &BorderImage::SetBlendMode)
        .addFunction("SetTiled", &BorderImage::SetTiled)

        .addFunction("GetTexture", &BorderImage::GetTexture)
        .addFunction("GetImageRect", &BorderImage::GetImageRect)
        .addFunction("GetBorder", &BorderImage::GetBorder)
        .addFunction("GetImageBorder", &BorderImage::GetImageBorder)
        .addFunction("GetHoverOffset", &BorderImage::GetHoverOffset)
        .addFunction("GetBlendMode", &BorderImage::GetBlendMode)
        .addFunction("IsTiled", &BorderImage::IsTiled)

        .addProperty("texture", &BorderImage::GetTexture, &BorderImage::SetTexture)
        .addProperty("imageRect", &BorderImage::GetImageRect, &BorderImage::SetImageRect)
        .addProperty("border", &BorderImage::GetBorder, &BorderImage::SetBorder)
        .addProperty("imageBorder", &BorderImage::GetImageBorder, &BorderImage::SetImageBorder)
        .addProperty("hoverOffset", &BorderImage::GetHoverOffset, static_cast<void(BorderImage::*)(const IntVector2&)>(&BorderImage::SetHoverOffset))
        .addProperty("blendMode", &BorderImage::GetBlendMode, &BorderImage::SetBlendMode)
        .addProperty("tiled", &BorderImage::IsTiled, &BorderImage::SetTiled)
        );
}
}

