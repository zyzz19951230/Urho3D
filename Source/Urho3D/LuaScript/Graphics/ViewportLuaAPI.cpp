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

    lua["Viewport"].setClass(UserdataMetatable<Viewport, Object>()
        .addOverloadedFunctions("new", &CreateViewport0, &CreateViewport1, &CreateViewport2, &CreateViewport3, &CreateViewport4)

        .addFunction("SetScene", &Viewport::SetScene)
        .addFunction("SetCamera", &Viewport::SetCamera)
        .addFunction("SetRect", &Viewport::SetRect)

        .addOverloadedFunctions("SetRenderPath",
            static_cast<void(Viewport::*)(RenderPath*)>(&Viewport::SetRenderPath),
            static_cast<void(Viewport::*)(XMLFile*)>(&Viewport::SetRenderPath))

        .addFunction("SetDrawDebug", &Viewport::SetDrawDebug)
        .addFunction("SetCullCamera", &Viewport::SetCullCamera)
        
        .addFunction("GetScene", &Viewport::GetScene)
        .addFunction("GetCamera", &Viewport::GetCamera)
        .addFunction("GetRect", &Viewport::GetRect)
        .addFunction("GetRenderPath", &Viewport::GetRenderPath)
        .addFunction("GetDrawDebug", &Viewport::GetDrawDebug)
        .addFunction("GetCullCamera", &Viewport::GetCullCamera)
        
        .addFunction("GetScreenRay", &Viewport::GetScreenRay)
        .addFunction("WorldToScreenPoint", &Viewport::WorldToScreenPoint)
        .addFunction("ScreenToWorldPoint", &Viewport::ScreenToWorldPoint)
        
        .addProperty("scene", &Viewport::GetScene, &Viewport::SetScene)
        .addProperty("camera", &Viewport::GetCamera, &Viewport::SetCamera)
        .addProperty("rect", &Viewport::GetRect, &Viewport::SetRect)
        .addProperty("renderPath", &Viewport::GetRenderPath, static_cast<void (Viewport::*)(RenderPath*)>(&Viewport::SetRenderPath))
        .addProperty("drawDebug", &Viewport::GetDrawDebug, &Viewport::SetDrawDebug)
        .addProperty("cullCamera", &Viewport::GetCullCamera, &Viewport::SetCullCamera)
    );
}
}

