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

#include "../../Graphics/Camera.h"
#include "../../Graphics/RenderPath.h"
#include "../../Graphics/Viewport.h"
#include "../../Resource/XMLFile.h"
#include "../../Scene/Scene.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static SharedPtr<Viewport> CreateViewport0()
{
    return SharedPtr<Viewport>(new Viewport(globalContext));
}

static SharedPtr<Viewport> CreateViewport1(Scene* scene, Camera* camera)
{
    return SharedPtr<Viewport>(new Viewport(globalContext, scene, camera));
}

static SharedPtr<Viewport> CreateViewport2(Scene* scene, Camera* camera, RenderPath* renderPath)
{
    return SharedPtr<Viewport>(new Viewport(globalContext, scene, camera, renderPath));
}

static SharedPtr<Viewport> CreateViewport3(Scene* scene, Camera* camera, const IntRect& rect)
{
    return SharedPtr<Viewport>(new Viewport(globalContext, scene, camera, rect));
}

static SharedPtr<Viewport> CreateViewport4(Scene* scene, Camera* camera, const IntRect& rect, RenderPath* renderPath)
{
    return SharedPtr<Viewport>(new Viewport(globalContext, scene, camera, rect, renderPath));
}

void RegisterViewport(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Viewport : Object
    lua["Viewport"].setClass(UserdataMetatable<Viewport, Object>()
        // [Constructor] Viewport()
        // [Constructor] Viewport(Scene* scene, Camera* camera, RenderPath* renderPath = 0)
        // [Constructor] Viewport(Scene* scene, Camera* camera, const IntRect& rect, RenderPath* renderPath = 0)
        .addOverloadedFunctions("new", &CreateViewport0, &CreateViewport1, &CreateViewport2, &CreateViewport3, &CreateViewport4)

        // [Method] void SetScene(Scene* scene)
        .addFunction("SetScene", &Viewport::SetScene)
        // [Method] void SetCamera(Camera* camera)
        .addFunction("SetCamera", &Viewport::SetCamera)
        // [Method] void SetRect(const IntRect& rect)
        .addFunction("SetRect", &Viewport::SetRect)

        .addOverloadedFunctions("SetRenderPath",
            // [Method] void SetRenderPath(RenderPath* renderPath)
            static_cast<void(Viewport::*)(RenderPath*)>(&Viewport::SetRenderPath),
            // [Method] void SetRenderPath(XMLFile* file)
            static_cast<void(Viewport::*)(XMLFile*)>(&Viewport::SetRenderPath))

        // [Method] void SetDrawDebug(bool enable)
        .addFunction("SetDrawDebug", &Viewport::SetDrawDebug)
        // [Method] void SetCullCamera(Camera* camera)
        .addFunction("SetCullCamera", &Viewport::SetCullCamera)
        
        // [Method] Scene* GetScene() const
        .addFunction("GetScene", &Viewport::GetScene)
        // [Method] Camera* GetCamera() const
        .addFunction("GetCamera", &Viewport::GetCamera)
        // [Method] const IntRect& GetRect() const
        .addFunction("GetRect", &Viewport::GetRect)
        // [Method] RenderPath* GetRenderPath() const
        .addFunction("GetRenderPath", &Viewport::GetRenderPath)
        // [Method] bool GetDrawDebug() const
        .addFunction("GetDrawDebug", &Viewport::GetDrawDebug)
        // [Method] Camera* GetCullCamera() const
        .addFunction("GetCullCamera", &Viewport::GetCullCamera)
        
        // [Method] Ray GetScreenRay(int x, int y) const
        .addFunction("GetScreenRay", &Viewport::GetScreenRay)
        // [Method] IntVector2 WorldToScreenPoint(const Vector3& worldPos) const
        .addFunction("WorldToScreenPoint", &Viewport::WorldToScreenPoint)
        // [Method] Vector3 ScreenToWorldPoint(int x, int y, float depth) const
        .addFunction("ScreenToWorldPoint", &Viewport::ScreenToWorldPoint)
        
        // [Property] Scene* scene
        .addProperty("scene", &Viewport::GetScene, &Viewport::SetScene)
        // [Property] Camera* camera
        .addProperty("camera", &Viewport::GetCamera, &Viewport::SetCamera)
        // [Property] const IntRect& rect
        .addProperty("rect", &Viewport::GetRect, &Viewport::SetRect)
        // [Property] RenderPath* renderPath
        .addProperty("renderPath", &Viewport::GetRenderPath, static_cast<void (Viewport::*)(RenderPath*)>(&Viewport::SetRenderPath))
        // [Property] bool drawDebug
        .addProperty("drawDebug", &Viewport::GetDrawDebug, &Viewport::SetDrawDebug)
        // [Property] Camera* cullCamera
        .addProperty("cullCamera", &Viewport::GetCullCamera, &Viewport::SetCullCamera)
    );
}
}

