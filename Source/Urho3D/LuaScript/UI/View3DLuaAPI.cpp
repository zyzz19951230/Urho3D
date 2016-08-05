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
#include "../../Graphics/Texture2D.h"
#include "../../Graphics/Viewport.h"
#include "../../Scene/Scene.h"
#include "../../UI/View3D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(View3DSetView, View3D, SetView, 2, 3);

void RegisterView3D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["View3D"].setClass(UserdataMetatable<View3D, Window>()
        .addStaticFunction("new", &CreateObject<View3D>)

        .addFunction("SetView", View3DSetView())

        .addFunction("SetFormat", &View3D::SetFormat)
        .addFunction("SetAutoUpdate", &View3D::SetAutoUpdate)
        .addFunction("QueueUpdate", &View3D::QueueUpdate)

        .addFunction("GetFormat", &View3D::GetFormat)
        .addFunction("GetAutoUpdate", &View3D::GetAutoUpdate)
        .addFunction("GetScene", &View3D::GetScene)
        .addFunction("GetCameraNode", &View3D::GetCameraNode)
        .addFunction("GetRenderTexture", &View3D::GetRenderTexture)
        .addFunction("GetDepthTexture", &View3D::GetDepthTexture)
        .addFunction("GetViewport", &View3D::GetViewport)

        .addProperty("format", &View3D::GetFormat, &View3D::SetFormat)
        .addProperty("autoUpdate", &View3D::GetAutoUpdate, &View3D::SetAutoUpdate)
        );
}
}

