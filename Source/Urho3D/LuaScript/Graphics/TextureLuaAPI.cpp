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

    lua["Texture"].setClass(UserdataMetatable<Texture, Resource>()
        .addStaticFunction("new", &CreateObject<Texture>)
        
        .addFunction("SetNumLevels", &Texture::SetNumLevels)
        .addFunction("SetFilterMode", &Texture::SetFilterMode)
        .addFunction("SetAddressMode", &Texture::SetAddressMode)
        .addFunction("SetBorderColor", &Texture::SetBorderColor)
        .addFunction("SetSRGB", &Texture::SetSRGB)
        .addFunction("SetBackupTexture", &Texture::SetBackupTexture)
        .addFunction("SetMipsToSkip", &Texture::SetMipsToSkip)

        .addFunction("GetFormat", &Texture::GetFormat)
        .addFunction("IsCompressed", &Texture::IsCompressed)
        .addFunction("GetLevels", &Texture::GetLevels)
        .addFunction("GetWidth", &Texture::GetWidth)
        .addFunction("GetHeight", &Texture::GetHeight)
        .addFunction("GetDepth", &Texture::GetDepth)
        .addFunction("GetFilterMode", &Texture::GetFilterMode)
        .addFunction("GetAddressMode", &Texture::GetAddressMode)
        .addFunction("GetBorderColor", &Texture::GetBorderColor)
        .addFunction("GetSRGB", &Texture::GetSRGB)
        .addFunction("GetBackupTexture", &Texture::GetBackupTexture)
        .addFunction("GetMipsToSkip", &Texture::GetMipsToSkip)
        .addFunction("GetLevelWidth", &Texture::GetLevelWidth)
        .addFunction("GetLevelHeight", &Texture::GetLevelHeight)
        .addFunction("GetLevelDepth", &Texture::GetLevelDepth)
        .addFunction("GetUsage", &Texture::GetUsage)

        .addOverloadedFunctions("GetDataSize",
            static_cast<unsigned(Texture::*)(int, int) const>(&Texture::GetDataSize),
            static_cast<unsigned(Texture::*)(int, int, int) const>(&Texture::GetDataSize))

        .addFunction("GetRowDataSize", &Texture::GetRowDataSize)
        .addFunction("GetComponents", &Texture::GetComponents)

        .addProperty("format", &Texture::GetFormat)
        .addProperty("compressed", &Texture::IsCompressed)
        .addProperty("levels", &Texture::GetLevels)
        .addProperty("width", &Texture::GetWidth)
        .addProperty("height", &Texture::GetHeight)
        .addProperty("depth", &Texture::GetDepth)
        .addProperty("filterMode", &Texture::GetFilterMode, &Texture::SetFilterMode)
        .addProperty("borderColor", &Texture::GetBorderColor, &Texture::SetBorderColor)
        .addProperty("sRGB", &Texture::GetSRGB, &Texture::SetSRGB)
        .addProperty("backupTexture", &Texture::GetBackupTexture, &Texture::SetBackupTexture)
        .addProperty("usage", &Texture::GetUsage)
        .addProperty("components", &Texture::GetComponents)
    );
}
}

