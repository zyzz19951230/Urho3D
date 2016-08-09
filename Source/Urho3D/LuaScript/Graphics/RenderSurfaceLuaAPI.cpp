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

    // [Class] RenderSurface : RefCounted
    lua["RenderSurface"].setClass(UserdataMetatable<RenderSurface, RefCounted>()
        .setConstructors<RenderSurface(Texture*)>()
        
        // [Method] void SetNumViewports(unsigned num)
        .addFunction("SetNumViewports", &RenderSurface::SetNumViewports)
        // [Method] void SetViewport(unsigned index, Viewport* viewport)
        .addFunction("SetViewport", &RenderSurface::SetViewport)
        // [Method] void SetUpdateMode(RenderSurfaceUpdateMode mode)
        .addFunction("SetUpdateMode", &RenderSurface::SetUpdateMode)
        // [Method] void SetLinkedRenderTarget(RenderSurface* renderTarget)
        .addFunction("SetLinkedRenderTarget", &RenderSurface::SetLinkedRenderTarget)
        // [Method] void SetLinkedDepthStencil(RenderSurface* depthStencil)
        .addFunction("SetLinkedDepthStencil", &RenderSurface::SetLinkedDepthStencil)
        // [Method] void QueueUpdate()
        .addFunction("QueueUpdate", &RenderSurface::QueueUpdate)
        // [Method] void Release()
        .addFunction("Release", &RenderSurface::Release)
        
        // [Method] Texture* GetParentTexture() const
        .addFunction("GetParentTexture", &RenderSurface::GetParentTexture)
        // [Method] int GetWidth() const
        .addFunction("GetWidth", &RenderSurface::GetWidth)
        // [Method] int GetHeight() const
        .addFunction("GetHeight", &RenderSurface::GetHeight)
        // [Method] TextureUsage GetUsage() const
        .addFunction("GetUsage", &RenderSurface::GetUsage)
        // [Method] unsigned GetNumViewports() const
        .addFunction("GetNumViewports", &RenderSurface::GetNumViewports)
        // [Method] Viewport* GetViewport(unsigned index) const
        .addFunction("GetViewport", &RenderSurface::GetViewport)
        // [Method] RenderSurfaceUpdateMode GetUpdateMode() const
        .addFunction("GetUpdateMode", &RenderSurface::GetUpdateMode)
        // [Method] RenderSurface* GetLinkedRenderTarget() const
        .addFunction("GetLinkedRenderTarget", &RenderSurface::GetLinkedRenderTarget)
        // [Method] RenderSurface* GetLinkedDepthStencil() const
        .addFunction("GetLinkedDepthStencil", &RenderSurface::GetLinkedDepthStencil)
        
        // [Property(ReadOnly)] Texture* parentTexture
        .addProperty("parentTexture", &RenderSurface::GetParentTexture)
        // [Property(ReadOnly)] int width
        .addProperty("width", &RenderSurface::GetWidth)
        // [Property(ReadOnly)] int height
        .addProperty("height", &RenderSurface::GetHeight)
        // [Property(ReadOnly)] TextureUsage usage
        .addProperty("usage", &RenderSurface::GetUsage)
        // [Property] unsigned numViewports
        .addProperty("numViewports", &RenderSurface::GetNumViewports, &RenderSurface::SetNumViewports)
        // [Property] RenderSurfaceUpdateMode updateMode
        .addProperty("updateMode", &RenderSurface::GetUpdateMode, &RenderSurface::SetUpdateMode)
        // [Property] RenderSurface* linkedRenderTarget
        .addProperty("linkedRenderTarget", &RenderSurface::GetLinkedRenderTarget, &RenderSurface::SetLinkedRenderTarget)
        // [Property] RenderSurface* linkedDepthStencil
        .addProperty("linkedDepthStencil", &RenderSurface::GetLinkedDepthStencil, &RenderSurface::SetLinkedDepthStencil)
    );
}
}

