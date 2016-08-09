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

    // [Class] Graphics : Object
    lua["Graphics"].setClass(UserdataMetatable<Graphics, Object>()

        // [Method] void SetWindowIcon(Image* windowIcon)
        .addFunction("SetWindowIcon", &Graphics::SetWindowIcon)
        // [Method] void SetWindowTitle(const String& windowTitle)
        .addFunction("SetWindowTitle", &Graphics::SetWindowTitle)

        .addOverloadedFunctions("SetWindowPosition",
            static_cast<void(Graphics::*)(const IntVector2&)>(&Graphics::SetWindowPosition),
            static_cast<void(Graphics::*)(int, int)>(&Graphics::SetWindowPosition))

        .addOverloadedFunctions("SetMode",
            static_cast<bool(Graphics::*)(int, int, bool, bool, bool, bool, bool, bool, int)>(&Graphics::SetMode),
            static_cast<bool(Graphics::*)(int, int)>(&Graphics::SetMode))

        // [Method] void SetSRGB(bool enable)
        .addFunction("SetSRGB", &Graphics::SetSRGB)
        // [Method] void SetDither(bool enable)
        .addFunction("SetDither", &Graphics::SetDither)
        // [Method] void SetFlushGPU(bool enable)
        .addFunction("SetFlushGPU", &Graphics::SetFlushGPU)
        // [Method] void SetOrientations(const String& orientations)
        .addFunction("SetOrientations", &Graphics::SetOrientations)
        // [Method] bool ToggleFullscreen()
        .addFunction("ToggleFullscreen", &Graphics::ToggleFullscreen)

        // [Method] void Maximize()
        .addFunction("Maximize", &Graphics::Maximize)
        // [Method] void Minimize()
        .addFunction("Minimize", &Graphics::Minimize)
        // [Method] void Close()
        .addFunction("Close", &Graphics::Close)
        
        // [Method] bool TakeScreenShot(Image& destImage)
        .addFunction("TakeScreenShot", &Graphics::TakeScreenShot)        

        // [Method] void BeginDumpShaders(const String& fileName)
        .addFunction("BeginDumpShaders", &Graphics::BeginDumpShaders)
        // [Method] void EndDumpShaders()
        .addFunction("EndDumpShaders", &Graphics::EndDumpShaders)

        // [Method] void PrecacheShaders(Deserializer& source)
        .addFunction("PrecacheShaders", &Graphics::PrecacheShaders)

        // [Method] bool IsInitialized() const
        .addFunction("IsInitialized", &Graphics::IsInitialized)
        // [Method] const String& GetWindowTitle() const
        .addFunction("GetWindowTitle", &Graphics::GetWindowTitle)
        // [Method] const String& GetApiName() const
        .addFunction("GetApiName", &Graphics::GetApiName)
        // [Method] IntVector2 GetWindowPosition() const
        .addFunction("GetWindowPosition", &Graphics::GetWindowPosition)
        // [Method] int GetWidth() const
        .addFunction("GetWidth", &Graphics::GetWidth)
        // [Method] int GetHeight() const
        .addFunction("GetHeight", &Graphics::GetHeight)
        // [Method] int GetMultiSample() const
        .addFunction("GetMultiSample", &Graphics::GetMultiSample)
        // [Method] bool GetFullscreen() const
        .addFunction("GetFullscreen", &Graphics::GetFullscreen)
        // [Method] bool GetBorderless() const
        .addFunction("GetBorderless", &Graphics::GetBorderless)
        // [Method] bool GetResizable() const
        .addFunction("GetResizable", &Graphics::GetResizable)
        // .addFunction("GetHighDPI", &Graphics::GetHighDPI)
        // [Method] bool GetVSync() const
        .addFunction("GetVSync", &Graphics::GetVSync)
        // [Method] bool GetTripleBuffer() const
        .addFunction("GetTripleBuffer", &Graphics::GetTripleBuffer)
        // [Method] bool GetSRGB() const
        .addFunction("GetSRGB", &Graphics::GetSRGB)
        // [Method] bool GetDither() const
        .addFunction("GetDither", &Graphics::GetDither)
        // [Method] bool GetFlushGPU() const
        .addFunction("GetFlushGPU", &Graphics::GetFlushGPU)
        // [Method] const String& GetOrientations() const
        .addFunction("GetOrientations", &Graphics::GetOrientations)

        // [Method] unsigned GetNumPrimitives() const
        .addFunction("GetNumPrimitives", &Graphics::GetNumPrimitives)
        // [Method] unsigned GetNumBatches() const
        .addFunction("GetNumBatches", &Graphics::GetNumBatches)

        // [Method] unsigned GetDummyColorFormat() const
        .addFunction("GetDummyColorFormat", &Graphics::GetDummyColorFormat)
        // [Method] unsigned GetShadowMapFormat() const
        .addFunction("GetShadowMapFormat", &Graphics::GetShadowMapFormat)
        // [Method] unsigned GetHiresShadowMapFormat() const
        .addFunction("GetHiresShadowMapFormat", &Graphics::GetHiresShadowMapFormat)
        
        // [Method] bool GetInstancingSupport() const
        .addFunction("GetInstancingSupport", &Graphics::GetInstancingSupport)
        // [Method] bool GetLightPrepassSupport() const
        .addFunction("GetLightPrepassSupport", &Graphics::GetLightPrepassSupport)
        // [Method] bool GetDeferredSupport() const
        .addFunction("GetDeferredSupport", &Graphics::GetDeferredSupport)        
        // [Method] bool GetHardwareShadowSupport() const
        .addFunction("GetHardwareShadowSupport", &Graphics::GetHardwareShadowSupport)
        // [Method] bool GetReadableDepthSupport() const
        .addFunction("GetReadableDepthSupport", &Graphics::GetReadableDepthSupport)
        // [Method] bool GetSRGBSupport() const
        .addFunction("GetSRGBSupport", &Graphics::GetSRGBSupport)
        // [Method] bool GetSRGBWriteSupport() const
        .addFunction("GetSRGBWriteSupport", &Graphics::GetSRGBWriteSupport)
        
        // [Method] IntVector2 GetDesktopResolution() const
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
        
        // [Property(ReadOnly)] bool initialized
        .addProperty("initialized", &Graphics::IsInitialized)
        // [Property] const String& windowTitle
        .addProperty("windowTitle", &Graphics::GetWindowTitle, &Graphics::SetWindowTitle)
        // [Property(ReadOnly)] const String& apiName
        .addProperty("apiName", &Graphics::GetApiName)
        // [Property] IntVector2 windowPosition
        .addProperty("windowPosition", &Graphics::GetWindowPosition, static_cast<void(Graphics::*)(const IntVector2&)>(&Graphics::SetWindowPosition))
        // [Property(ReadOnly)] int width
        .addProperty("width", &Graphics::GetWidth)
        // [Property(ReadOnly)] int height
        .addProperty("height", &Graphics::GetHeight)
        // [Property(ReadOnly)] int multiSample
        .addProperty("multiSample", &Graphics::GetMultiSample)

        // [Property(ReadOnly)] bool fullscreen
        .addProperty("fullscreen", &Graphics::GetFullscreen)
        // [Property(ReadOnly)] bool borderless
        .addProperty("borderless", &Graphics::GetBorderless)
        // [Property(ReadOnly)] bool resizable
        .addProperty("resizable", &Graphics::GetResizable)

        // .addProperty("highDPI", &Graphics::GetHighDPI)
        // [Property(ReadOnly)] bool vSync
        .addProperty("vSync", &Graphics::GetVSync)
        // [Property(ReadOnly)] bool tripleBuffer
        .addProperty("tripleBuffer", &Graphics::GetTripleBuffer)
        // [Property] bool sRGB
        .addProperty("sRGB", &Graphics::GetSRGB, &Graphics::SetSRGB)
        // [Property] bool dither
        .addProperty("dither", &Graphics::GetDither, &Graphics::SetDither)
        // [Property] bool flushGPU
        .addProperty("flushGPU", &Graphics::GetFlushGPU, &Graphics::SetFlushGPU)
        // [Property] const String& orientations
        .addProperty("orientations", &Graphics::GetOrientations, &Graphics::SetOrientations)

        // [Property(ReadOnly)] bool deviceLost
        .addProperty("deviceLost", &Graphics::IsDeviceLost)

        // [Property(ReadOnly)] unsigned numPrimitives
        .addProperty("numPrimitives", &Graphics::GetNumPrimitives)
        // [Property(ReadOnly)] unsigned numBatches
        .addProperty("numBatches", &Graphics::GetNumBatches)
        // [Property(ReadOnly)] unsigned dummyColorFormat
        .addProperty("dummyColorFormat", &Graphics::GetDummyColorFormat)
        // [Property(ReadOnly)] unsigned shadowMapFormat
        .addProperty("shadowMapFormat", &Graphics::GetShadowMapFormat)
        // [Property(ReadOnly)] unsigned hiresShadowMapFormat
        .addProperty("hiresShadowMapFormat", &Graphics::GetHiresShadowMapFormat)
        // [Property(ReadOnly)] bool instancingSupport
        .addProperty("instancingSupport", &Graphics::GetInstancingSupport)
        // [Property(ReadOnly)] bool lightPrepassSupport
        .addProperty("lightPrepassSupport", &Graphics::GetLightPrepassSupport)
        // [Property(ReadOnly)] bool deferredSupport
        .addProperty("deferredSupport", &Graphics::GetDeferredSupport)
        // [Property(ReadOnly)] bool hardwareShadowSupport
        .addProperty("hardwareShadowSupport", &Graphics::GetHardwareShadowSupport)
        // [Property(ReadOnly)] bool readableDepthSupport
        .addProperty("readableDepthSupport", &Graphics::GetReadableDepthSupport)
        // [Property(ReadOnly)] bool sRGBSupport
        .addProperty("sRGBSupport", &Graphics::GetSRGBSupport)
        // [Property(ReadOnly)] bool sRGBWriteSupport
        .addProperty("sRGBWriteSupport", &Graphics::GetSRGBWriteSupport)
        // [Property(ReadOnly)] IntVector2 desktopResolution
        .addProperty("desktopResolution", &Graphics::GetDesktopResolution)
    );
}
}

