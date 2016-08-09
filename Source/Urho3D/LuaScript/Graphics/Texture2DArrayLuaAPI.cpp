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

#include "../../Graphics/Texture2D.h"
#include "../../Graphics/Texture2DArray.h"
#include "../../Resource/Image.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(Texture2DArraySetSize, Texture2DArray, SetSize, 4, 5);
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(Texture2DArraySetData, Texture2DArray, SetData, 1, 2, bool(Texture2D::*)(Image*, bool));

void RegisterTexture2DArray(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Texture2DArray : Texture
    lua["Texture2DArray"].setClass(UserdataMetatable<Texture2DArray, Texture>()
        // [Constructor] Texture2DArray()
        .addStaticFunction("new", &CreateObject<Texture2DArray>)
        
        // [Method] void SetLayers(unsigned layers)
        .addFunction("SetLayers", &Texture2DArray::SetLayers)
        
        // [Method] bool SetSize(unsigned layers, int width, int height, unsigned format, TextureUsage usage = TEXTURE_STATIC)
        .addFunction("SetSize", Texture2DArraySetSize())
        // [Method] bool SetData(unsigned layer, unsigned level, int x, int y, int width, int height, const void* data)
        .addFunction("SetData", Texture2DArraySetData())

        // [Method] unsigned GetLayers() const
        .addFunction("GetLayers", &Texture2DArray::GetLayers)
        // [Method] RenderSurface* GetRenderSurface() const
        .addFunction("GetRenderSurface", &Texture2DArray::GetRenderSurface)

        // [Property] unsigned layers
        .addProperty("layers", &Texture2DArray::GetLayers, &Texture2DArray::SetLayers)
        // [Property(ReadOnly)] RenderSurface* renderSurface
        .addProperty("renderSurface", &Texture2DArray::GetRenderSurface)
    );
}
}

