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
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterTexture(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Texture : Resource
    lua["Texture"].setClass(UserdataMetatable<Texture, Resource>()
        // [Constructor] Texture()
        .addStaticFunction("new", &CreateObject<Texture>)
        
        // [Method] void SetNumLevels(unsigned levels)
        .addFunction("SetNumLevels", &Texture::SetNumLevels)
        // [Method] void SetFilterMode(TextureFilterMode filter)
        .addFunction("SetFilterMode", &Texture::SetFilterMode)
        // [Method] void SetAddressMode(TextureCoordinate coord, TextureAddressMode address)
        .addFunction("SetAddressMode", &Texture::SetAddressMode)
        // [Method] void SetBorderColor(const Color& color)
        .addFunction("SetBorderColor", &Texture::SetBorderColor)
        // [Method] void SetSRGB(bool enable)
        .addFunction("SetSRGB", &Texture::SetSRGB)
        // [Method] void SetBackupTexture(Texture* texture)
        .addFunction("SetBackupTexture", &Texture::SetBackupTexture)
        // [Method] void SetMipsToSkip(int quality, int toSkip)
        .addFunction("SetMipsToSkip", &Texture::SetMipsToSkip)

        // [Method] unsigned GetFormat() const
        .addFunction("GetFormat", &Texture::GetFormat)
        // [Method] bool IsCompressed() const
        .addFunction("IsCompressed", &Texture::IsCompressed)
        // [Method] unsigned GetLevels() const
        .addFunction("GetLevels", &Texture::GetLevels)
        // [Method] int GetWidth() const
        .addFunction("GetWidth", &Texture::GetWidth)
        // [Method] int GetHeight() const
        .addFunction("GetHeight", &Texture::GetHeight)
        // [Method] int GetDepth() const
        .addFunction("GetDepth", &Texture::GetDepth)
        // [Method] TextureFilterMode GetFilterMode() const
        .addFunction("GetFilterMode", &Texture::GetFilterMode)
        // [Method] TextureAddressMode GetAddressMode(TextureCoordinate coord) const
        .addFunction("GetAddressMode", &Texture::GetAddressMode)
        // [Method] const Color& GetBorderColor() const
        .addFunction("GetBorderColor", &Texture::GetBorderColor)
        // [Method] bool GetSRGB() const
        .addFunction("GetSRGB", &Texture::GetSRGB)
        // [Method] Texture* GetBackupTexture() const
        .addFunction("GetBackupTexture", &Texture::GetBackupTexture)
        // [Method] int GetMipsToSkip(int quality) const
        .addFunction("GetMipsToSkip", &Texture::GetMipsToSkip)
        // [Method] int GetLevelWidth(unsigned level) const
        .addFunction("GetLevelWidth", &Texture::GetLevelWidth)
        // [Method] int GetLevelHeight(unsigned level) const
        .addFunction("GetLevelHeight", &Texture::GetLevelHeight)
        // [Method] int GetLevelDepth(unsigned level) const
        .addFunction("GetLevelDepth", &Texture::GetLevelDepth)
        // [Method] TextureUsage GetUsage() const
        .addFunction("GetUsage", &Texture::GetUsage)

        .addOverloadedFunctions("GetDataSize",
            // [Method] unsigned GetDataSize(int width, int height) const
            static_cast<unsigned(Texture::*)(int, int) const>(&Texture::GetDataSize),
            // [Method] unsigned GetDataSize(int width, int height, int depth) const
            static_cast<unsigned(Texture::*)(int, int, int) const>(&Texture::GetDataSize))

        // [Method] unsigned GetRowDataSize(int width) const
        .addFunction("GetRowDataSize", &Texture::GetRowDataSize)
        // [Method] unsigned GetComponents() const
        .addFunction("GetComponents", &Texture::GetComponents)

        // [Property(Readonly)] unsigned format
        .addProperty("format", &Texture::GetFormat)
        // [Property(Readonly)] bool compressed
        .addProperty("compressed", &Texture::IsCompressed)
        // [Property(Readonly)] unsigned levels
        .addProperty("levels", &Texture::GetLevels)
        // [Property(Readonly)] int width
        .addProperty("width", &Texture::GetWidth)
        // [Property(Readonly)] int height
        .addProperty("height", &Texture::GetHeight)
        // [Property(Readonly)] int depth
        .addProperty("depth", &Texture::GetDepth)
        // [Property] TextureFilterMode filterMode
        .addProperty("filterMode", &Texture::GetFilterMode, &Texture::SetFilterMode)
        // [Property] const Color& borderColor
        .addProperty("borderColor", &Texture::GetBorderColor, &Texture::SetBorderColor)
        // [Property] bool sRGB
        .addProperty("sRGB", &Texture::GetSRGB, &Texture::SetSRGB)
        // [Property] Texture* backupTexture
        .addProperty("backupTexture", &Texture::GetBackupTexture, &Texture::SetBackupTexture)
        // [Property(Readonly)] TextureUsage usage
        .addProperty("usage", &Texture::GetUsage)
        // [Property(Readonly)] unsigned components
        .addProperty("components", &Texture::GetComponents)
    );
}
}

