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

#include "../../Graphics/RenderSurface.h"
#include "../../Graphics/Texture.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterRenderSurface(kaguya::State& lua)
{
    using namespace kaguya;

    lua["RenderSurface"].setClass(UserdataMetatable<RenderSurface, RefCounted>()
        .setConstructors<RenderSurface(Texture*)>()
        
        .addFunction("SetNumViewports", &RenderSurface::SetNumViewports)
        .addFunction("SetViewport", &RenderSurface::SetViewport)
        .addFunction("SetUpdateMode", &RenderSurface::SetUpdateMode)
        .addFunction("SetLinkedRenderTarget", &RenderSurface::SetLinkedRenderTarget)
        .addFunction("SetLinkedDepthStencil", &RenderSurface::SetLinkedDepthStencil)
        .addFunction("QueueUpdate", &RenderSurface::QueueUpdate)
        .addFunction("Release", &RenderSurface::Release)
        
        .addFunction("GetParentTexture", &RenderSurface::GetParentTexture)
        .addFunction("GetWidth", &RenderSurface::GetWidth)
        .addFunction("GetHeight", &RenderSurface::GetHeight)
        .addFunction("GetUsage", &RenderSurface::GetUsage)
        .addFunction("GetNumViewports", &RenderSurface::GetNumViewports)
        .addFunction("GetViewport", &RenderSurface::GetViewport)
        .addFunction("GetUpdateMode", &RenderSurface::GetUpdateMode)
        .addFunction("GetLinkedRenderTarget", &RenderSurface::GetLinkedRenderTarget)
        .addFunction("GetLinkedDepthStencil", &RenderSurface::GetLinkedDepthStencil)
        
        .addProperty("parentTexture", &RenderSurface::GetParentTexture)
        .addProperty("width", &RenderSurface::GetWidth)
        .addProperty("height", &RenderSurface::GetHeight)
        .addProperty("usage", &RenderSurface::GetUsage)
        .addProperty("numViewports", &RenderSurface::GetNumViewports, &RenderSurface::SetNumViewports)
        .addProperty("updateMode", &RenderSurface::GetUpdateMode, &RenderSurface::SetUpdateMode)
        .addProperty("linkedRenderTarget", &RenderSurface::GetLinkedRenderTarget, &RenderSurface::SetLinkedRenderTarget)
        .addProperty("linkedDepthStencil", &RenderSurface::GetLinkedDepthStencil, &RenderSurface::SetLinkedDepthStencil)
    );
}
}

