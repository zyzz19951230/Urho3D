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

#include "../../Resource/Image.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static SharedPtr<Image> ImageGetSubimage(const Image* self, const IntRect& rect)
{
    return SharedPtr<Image>(self->GetSubimage(rect));
}

void RegisterImage(kaguya::State& lua)
{
    using namespace kaguya;

    // enum CompressedFormat;
    lua["CF_NONE"] = CF_NONE;
    lua["CF_RGBA"] = CF_RGBA;
    lua["CF_DXT1"] = CF_DXT1;
    lua["CF_DXT3"] = CF_DXT3;
    lua["CF_DXT5"] = CF_DXT5;
    lua["CF_ETC1"] = CF_ETC1;
    lua["CF_PVRTC_RGB_2BPP"] = CF_PVRTC_RGB_2BPP;
    lua["CF_PVRTC_RGBA_2BPP"] = CF_PVRTC_RGBA_2BPP;
    lua["CF_PVRTC_RGB_4BPP"] = CF_PVRTC_RGB_4BPP;
    lua["CF_PVRTC_RGBA_4BPP"] = CF_PVRTC_RGBA_4BPP;

    lua["Image"].setClass(UserdataMetatable<Image, Resource>()
        .addStaticFunction("new", &CreateObject<Image>)

        .addOverloadedFunctions("SetSize",
            static_cast<bool(Image::*)(int, int, unsigned)>(&Image::SetSize),
            static_cast<bool(Image::*)(int, int, int, unsigned)>(&Image::SetSize))

        .addOverloadedFunctions("SetPixel",
            static_cast<void(Image::*)(int, int, const Color&)>(&Image::SetPixel),
            static_cast<void(Image::*)(int, int, int, const Color&)>(&Image::SetPixel))

        .addOverloadedFunctions("SetPixelInt",
            static_cast<void(Image::*)(int, int, unsigned)>(&Image::SetPixelInt),
            static_cast<void(Image::*)(int, int, int, unsigned)>(&Image::SetPixelInt))

        .addFunction("FlipHorizontal", &Image::FlipHorizontal)
        .addFunction("FlipVertical", &Image::FlipVertical)
        .addFunction("Resize", &Image::Resize)
        .addFunction("Clear", &Image::Clear)
        .addFunction("ClearInt", &Image::ClearInt)
        .addFunction("SaveBMP", &Image::SaveBMP)
        .addFunction("SavePNG", &Image::SavePNG)
        .addFunction("SaveTGA", &Image::SaveTGA)
        .addFunction("SaveJPG", &Image::SaveJPG)
        .addFunction("IsCubemap", &Image::IsCubemap)
        .addFunction("IsArray", &Image::IsArray)
        .addFunction("IsSRGB", &Image::IsSRGB)

        .addOverloadedFunctions("GetPixel",
            static_cast<Color(Image::*)(int, int) const>(&Image::GetPixel),
            static_cast<Color(Image::*)(int, int, int) const>(&Image::GetPixel))

        .addOverloadedFunctions("GetPixelInt",
            static_cast<unsigned(Image::*)(int, int) const>(&Image::GetPixelInt),
            static_cast<unsigned(Image::*)(int, int, int) const>(&Image::GetPixelInt))

        .addFunction("GetPixelBilinear", &Image::GetPixelBilinear)
        .addFunction("GetPixelTrilinear", &Image::GetPixelTrilinear)
        .addFunction("GetWidth", &Image::GetWidth)
        .addFunction("GetHeight", &Image::GetHeight)
        .addFunction("GetDepth", &Image::GetDepth)
        .addFunction("GetComponents", &Image::GetComponents)

        .addFunction("IsCompressed", &Image::IsCompressed)
        .addFunction("GetCompressedFormat", &Image::GetCompressedFormat)
        .addFunction("GetNumCompressedLevels", &Image::GetNumCompressedLevels)

        .addFunction("GetNextLevel", &Image::GetNextLevel)
        .addFunction("GetNextSibling", &Image::GetNextSibling)
        .addFunction("ConvertToRGBA", &Image::ConvertToRGBA)

        .addFunction("GetCompressedLevel", &Image::GetCompressedLevel)

        .addStaticFunction("GetSubimage", &ImageGetSubimage)

        .addProperty("cubemap", &Image::IsCubemap)
        .addProperty("array", &Image::IsArray)
        .addProperty("SRGB", &Image::IsSRGB)
        .addProperty("width", &Image::GetWidth)
        .addProperty("height", &Image::GetHeight)
        .addProperty("depth", &Image::GetDepth)
        .addProperty("components", &Image::GetComponents)
        .addProperty("data", &Image::GetData, &Image::SetData)
        .addProperty("compressed", &Image::IsCompressed)
        .addProperty("compressedFormat", &Image::GetCompressedFormat)
        .addProperty("numCompressedLevels", &Image::GetNumCompressedLevels)
        .addProperty("nextLevel", &Image::GetNextLevel)
        .addProperty("nextSibling", &Image::GetNextSibling)
    );
}
}

