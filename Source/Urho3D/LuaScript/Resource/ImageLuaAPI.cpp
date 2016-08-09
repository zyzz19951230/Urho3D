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

    // [Enum] CompressedFormat
    // [Variable] CF_NONE
    lua["CF_NONE"] = CF_NONE;
    // [Variable] CF_RGBA,
    lua["CF_RGBA"] = CF_RGBA;
    // [Variable] CF_DXT1,
    lua["CF_DXT1"] = CF_DXT1;
    // [Variable] CF_DXT3,
    lua["CF_DXT3"] = CF_DXT3;
    // [Variable] CF_DXT5,
    lua["CF_DXT5"] = CF_DXT5;
    // [Variable] CF_ETC1,
    lua["CF_ETC1"] = CF_ETC1;
    // [Variable] CF_PVRTC_RGB_2BPP,
    lua["CF_PVRTC_RGB_2BPP"] = CF_PVRTC_RGB_2BPP;
    // [Variable] CF_PVRTC_RGBA_2BPP,
    lua["CF_PVRTC_RGBA_2BPP"] = CF_PVRTC_RGBA_2BPP;
    // [Variable] CF_PVRTC_RGB_4BPP,
    lua["CF_PVRTC_RGB_4BPP"] = CF_PVRTC_RGB_4BPP;
    // [Variable] CF_PVRTC_RGBA_4BPP,
    lua["CF_PVRTC_RGBA_4BPP"] = CF_PVRTC_RGBA_4BPP;

    // [Class] Image : Resource
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

        // [Method] bool FlipHorizontal()
        .addFunction("FlipHorizontal", &Image::FlipHorizontal)
        // [Method] bool FlipVertical()
        .addFunction("FlipVertical", &Image::FlipVertical)
        // [Method] bool Resize(int width, int height)
        .addFunction("Resize", &Image::Resize)
        // [Method] void Clear(const Color& color)
        .addFunction("Clear", &Image::Clear)
        // [Method] void ClearInt(unsigned uintColor)
        .addFunction("ClearInt", &Image::ClearInt)
        // [Method] bool SaveBMP(const String& fileName) const
        .addFunction("SaveBMP", &Image::SaveBMP)
        // [Method] bool SavePNG(const String& fileName) const
        .addFunction("SavePNG", &Image::SavePNG)
        // [Method] bool SaveTGA(const String& fileName) const
        .addFunction("SaveTGA", &Image::SaveTGA)
        // [Method] bool SaveJPG(const String& fileName, int quality) const
        .addFunction("SaveJPG", &Image::SaveJPG)
        // [Method] bool IsCubemap() const
        .addFunction("IsCubemap", &Image::IsCubemap)
        // [Method] bool IsArray() const
        .addFunction("IsArray", &Image::IsArray)
        // [Method] bool IsSRGB() const
        .addFunction("IsSRGB", &Image::IsSRGB)

        .addOverloadedFunctions("GetPixel",
            static_cast<Color(Image::*)(int, int) const>(&Image::GetPixel),
            static_cast<Color(Image::*)(int, int, int) const>(&Image::GetPixel))

        .addOverloadedFunctions("GetPixelInt",
            static_cast<unsigned(Image::*)(int, int) const>(&Image::GetPixelInt),
            static_cast<unsigned(Image::*)(int, int, int) const>(&Image::GetPixelInt))

        // [Method] Color GetPixelBilinear(float x, float y) const
        .addFunction("GetPixelBilinear", &Image::GetPixelBilinear)
        // [Method] Color GetPixelTrilinear(float x, float y, float z) const
        .addFunction("GetPixelTrilinear", &Image::GetPixelTrilinear)
        // [Method] int GetWidth() const
        .addFunction("GetWidth", &Image::GetWidth)
        // [Method] int GetHeight() const
        .addFunction("GetHeight", &Image::GetHeight)
        // [Method] int GetDepth() const
        .addFunction("GetDepth", &Image::GetDepth)
        // [Method] unsigned GetComponents() const
        .addFunction("GetComponents", &Image::GetComponents)

        // [Method] bool IsCompressed() const
        .addFunction("IsCompressed", &Image::IsCompressed)
        // [Method] CompressedFormat GetCompressedFormat() const
        .addFunction("GetCompressedFormat", &Image::GetCompressedFormat)
        // [Method] unsigned GetNumCompressedLevels() const
        .addFunction("GetNumCompressedLevels", &Image::GetNumCompressedLevels)

        // [Method] SharedPtr<Image> GetNextLevel() const
        .addFunction("GetNextLevel", &Image::GetNextLevel)
        // [Method] SharedPtr<Image> GetNextSibling() const
        .addFunction("GetNextSibling", &Image::GetNextSibling)
        // [Method] SharedPtr<Image> ConvertToRGBA() const
        .addFunction("ConvertToRGBA", &Image::ConvertToRGBA)

        // [Method] CompressedLevel GetCompressedLevel(unsigned index) const
        .addFunction("GetCompressedLevel", &Image::GetCompressedLevel)

        .addStaticFunction("GetSubimage", &ImageGetSubimage)

        // [Property(ReadOnly)] bool cubemap
        .addProperty("cubemap", &Image::IsCubemap)
        // [Property(ReadOnly)] bool array
        .addProperty("array", &Image::IsArray)
        // [Property(ReadOnly)] bool SRGB
        .addProperty("SRGB", &Image::IsSRGB)
        // [Property(ReadOnly)] int width
        .addProperty("width", &Image::GetWidth)
        // [Property(ReadOnly)] int height
        .addProperty("height", &Image::GetHeight)
        // [Property(ReadOnly)] int depth
        .addProperty("depth", &Image::GetDepth)
        // [Property(ReadOnly)] unsigned components
        .addProperty("components", &Image::GetComponents)
        // [Property] unsigned char* data
        .addProperty("data", &Image::GetData, &Image::SetData)
        // [Property(ReadOnly)] bool compressed
        .addProperty("compressed", &Image::IsCompressed)
        // [Property(ReadOnly)] CompressedFormat compressedFormat
        .addProperty("compressedFormat", &Image::GetCompressedFormat)
        // [Property(ReadOnly)] unsigned numCompressedLevels
        .addProperty("numCompressedLevels", &Image::GetNumCompressedLevels)
        // [Property(ReadOnly)] SharedPtr<Image> nextLevel
        .addProperty("nextLevel", &Image::GetNextLevel)
        // [Property(ReadOnly)] SharedPtr<Image> nextSibling
        .addProperty("nextSibling", &Image::GetNextSibling)
    );
}
}

