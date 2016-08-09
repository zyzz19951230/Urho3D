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

#include "../../Graphics/TextureCube.h"
#include "../../Resource/Image.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(TextureCubeSetSize, TextureCube, SetSize, 2, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(TextureCubeSetData, TextureCube, SetData, 2, 3, bool(TextureCube::*)(CubeMapFace, Image*, bool));

void RegisterTextureCube(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] TextureCube : Texture
    lua["TextureCube"].setClass(UserdataMetatable<TextureCube, Texture>()
        .addStaticFunction("new", &CreateObject<TextureCube>)
        
        // [Method] bool SetSize(int size, unsigned format, TextureUsage usage = TEXTURE_STATIC)
        .addFunction("SetSize", TextureCubeSetSize())
        // [Method] bool SetData(CubeMapFace face, unsigned level, int x, int y, int width, int height, const void* data)
        .addFunction("SetData", TextureCubeSetData())

        // [Method] RenderSurface* GetRenderSurface(CubeMapFace face) const
        .addFunction("GetRenderSurface", &TextureCube::GetRenderSurface)

        // [Property(ReadOnly)] RenderSurface* renderSurface
        .addProperty("renderSurface", &TextureCube::GetRenderSurface)
    );
}
}

