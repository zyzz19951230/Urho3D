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

#include "../../Graphics/Graphics.h"
#include "../../IO/Deserializer.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterGraphics(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Graphics"].setClass(UserdataMetatable<Graphics, Object>()

        .addFunction("SetWindowIcon", &Graphics::SetWindowIcon)
        .addFunction("SetWindowTitle", &Graphics::SetWindowTitle)

        .addOverloadedFunctions("SetWindowPosition",
            static_cast<void(Graphics::*)(const IntVector2&)>(&Graphics::SetWindowPosition),
            static_cast<void(Graphics::*)(int, int)>(&Graphics::SetWindowPosition))

        .addOverloadedFunctions("SetMode",
            static_cast<bool(Graphics::*)(int, int, bool, bool, bool, bool, bool, bool, int)>(&Graphics::SetMode),
            static_cast<bool(Graphics::*)(int, int)>(&Graphics::SetMode))

        .addFunction("SetSRGB", &Graphics::SetSRGB)
        .addFunction("SetFlushGPU", &Graphics::SetFlushGPU)
        .addFunction("SetOrientations", &Graphics::SetOrientations)
        .addFunction("ToggleFullscreen", &Graphics::ToggleFullscreen)

        .addFunction("Maximize", &Graphics::Maximize)
        .addFunction("Minimize", &Graphics::Minimize)
        .addFunction("Close", &Graphics::Close)
        
        .addFunction("TakeScreenShot", &Graphics::TakeScreenShot)        

        .addFunction("BeginDumpShaders", &Graphics::BeginDumpShaders)
        .addFunction("EndDumpShaders", &Graphics::EndDumpShaders)

        .addFunction("PrecacheShaders", &Graphics::PrecacheShaders)

        .addFunction("IsInitialized", &Graphics::IsInitialized)
        .addFunction("GetWindowTitle", &Graphics::GetWindowTitle)
        .addFunction("GetApiName", &Graphics::GetApiName)
        .addFunction("GetWindowPosition", &Graphics::GetWindowPosition)
        .addFunction("GetWidth", &Graphics::GetWidth)
        .addFunction("GetHeight", &Graphics::GetHeight)
        .addFunction("GetMultiSample", &Graphics::GetMultiSample)
        .addFunction("GetFullscreen", &Graphics::GetFullscreen)
        .addFunction("GetBorderless", &Graphics::GetBorderless)
        .addFunction("GetResizable", &Graphics::GetResizable)
        // .addFunction("GetHighDPI", &Graphics::GetHighDPI)
        .addFunction("GetVSync", &Graphics::GetVSync)
        .addFunction("GetTripleBuffer", &Graphics::GetTripleBuffer)
        .addFunction("GetSRGB", &Graphics::GetSRGB)
        .addFunction("GetFlushGPU", &Graphics::GetFlushGPU)
        .addFunction("GetOrientations", &Graphics::GetOrientations)

        .addFunction("GetNumPrimitives", &Graphics::GetNumPrimitives)
        .addFunction("GetNumBatches", &Graphics::GetNumBatches)

        .addFunction("GetDummyColorFormat", &Graphics::GetDummyColorFormat)
        .addFunction("GetShadowMapFormat", &Graphics::GetShadowMapFormat)
        .addFunction("GetHiresShadowMapFormat", &Graphics::GetHiresShadowMapFormat)
        
        .addFunction("GetInstancingSupport", &Graphics::GetInstancingSupport)
        .addFunction("GetLightPrepassSupport", &Graphics::GetLightPrepassSupport)
        .addFunction("GetDeferredSupport", &Graphics::GetDeferredSupport)        
        .addFunction("GetHardwareShadowSupport", &Graphics::GetHardwareShadowSupport)
        .addFunction("GetReadableDepthSupport", &Graphics::GetReadableDepthSupport)
        .addFunction("GetSRGBSupport", &Graphics::GetSRGBSupport)
        .addFunction("GetSRGBWriteSupport", &Graphics::GetSRGBWriteSupport)
        
        .addFunction("GetDesktopResolution", &Graphics::GetDesktopResolution)

        .addStaticFunction("GetAlphaFormat", &Graphics::GetAlphaFormat)
        .addStaticFunction("GetLuminanceFormat", &Graphics::GetLuminanceFormat)
        .addStaticFunction("GetLuminanceAlphaFormat", &Graphics::GetLuminanceAlphaFormat)
        .addStaticFunction("GetRGBFormat", &Graphics::GetRGBFormat)
        .addStaticFunction("GetRGBAFormat", &Graphics::GetRGBAFormat)
        .addStaticFunction("GetRGBA16Format", &Graphics::GetRGBA16Format)
        .addStaticFunction("GetRGBAFloat16Format", &Graphics::GetRGBAFloat16Format)
        .addStaticFunction("GetRGBAFloat32Format", &Graphics::GetRGBAFloat32Format)
        .addStaticFunction("GetRG16Format", &Graphics::GetRG16Format)
        .addStaticFunction("GetRGFloat16Format", &Graphics::GetRGFloat16Format)
        .addStaticFunction("GetRGFloat32Format", &Graphics::GetRGFloat32Format)
        .addStaticFunction("GetFloat16Format", &Graphics::GetFloat16Format)
        .addStaticFunction("GetFloat32Format", &Graphics::GetFloat32Format)
        .addStaticFunction("GetLinearDepthFormat", &Graphics::GetLinearDepthFormat)
        .addStaticFunction("GetDepthStencilFormat", &Graphics::GetDepthStencilFormat)
        .addStaticFunction("GetReadableDepthFormat", &Graphics::GetReadableDepthFormat)
        .addStaticFunction("GetPixelUVOffset", &Graphics::GetPixelUVOffset)
        .addStaticFunction("GetMaxBones", &Graphics::GetMaxBones)
        
        .addProperty("initialized", &Graphics::IsInitialized)
        .addProperty("windowTitle", &Graphics::GetWindowTitle, &Graphics::SetWindowTitle)
        .addProperty("apiName", &Graphics::GetApiName)
        .addProperty("windowPosition", &Graphics::GetWindowPosition, static_cast<void(Graphics::*)(const IntVector2&)>(&Graphics::SetWindowPosition))
        .addProperty("width", &Graphics::GetWidth)
        .addProperty("height", &Graphics::GetHeight)
        .addProperty("multiSample", &Graphics::GetMultiSample)

        .addProperty("fullscreen", &Graphics::GetFullscreen)
        .addProperty("borderless", &Graphics::GetBorderless)
        .addProperty("resizable", &Graphics::GetResizable)

        // .addProperty("highDPI", &Graphics::GetHighDPI)
        .addProperty("vSync", &Graphics::GetVSync)
        .addProperty("tripleBuffer", &Graphics::GetTripleBuffer)
        .addProperty("sRGB", &Graphics::GetSRGB, &Graphics::SetSRGB)
        .addProperty("flushGPU", &Graphics::GetFlushGPU, &Graphics::SetFlushGPU)
        .addProperty("orientations", &Graphics::GetOrientations, &Graphics::SetOrientations)

        .addProperty("deviceLost", &Graphics::IsDeviceLost)

        .addProperty("numPrimitives", &Graphics::GetNumPrimitives)
        .addProperty("numBatches", &Graphics::GetNumBatches)
        .addProperty("dummyColorFormat", &Graphics::GetDummyColorFormat)
        .addProperty("shadowMapFormat", &Graphics::GetShadowMapFormat)
        .addProperty("hiresShadowMapFormat", &Graphics::GetHiresShadowMapFormat)
        .addProperty("instancingSupport", &Graphics::GetInstancingSupport)
        .addProperty("lightPrepassSupport", &Graphics::GetLightPrepassSupport)
        .addProperty("deferredSupport", &Graphics::GetDeferredSupport)
        .addProperty("hardwareShadowSupport", &Graphics::GetHardwareShadowSupport)
        .addProperty("readableDepthSupport", &Graphics::GetReadableDepthSupport)
        .addProperty("sRGBSupport", &Graphics::GetSRGBSupport)
        .addProperty("sRGBWriteSupport", &Graphics::GetSRGBWriteSupport)
        .addProperty("desktopResolution", &Graphics::GetDesktopResolution)
    );
}
}

