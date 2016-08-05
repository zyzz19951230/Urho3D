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

#include "../../Graphics/Technique.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(TechniqueClone, Technique, Clone, 0, 1);

void RegisterTechnique(kaguya::State& lua)
{
    using namespace kaguya;

    // enum PassLightingMode;
    lua["LIGHTING_UNLIT"] = LIGHTING_UNLIT;
    lua["LIGHTING_PERVERTEX"] = LIGHTING_PERVERTEX;
    lua["LIGHTING_PERPIXEL"] = LIGHTING_PERPIXEL;

    lua["Pass"].setClass(UserdataMetatable<Pass, RefCounted>()
        .setConstructors<Pass(const String&)>()
        
        .addFunction("SetBlendMode", &Pass::SetBlendMode)
        .addFunction("SetCullMode", &Pass::SetCullMode)
        .addFunction("SetDepthTestMode", &Pass::SetDepthTestMode)
        .addFunction("SetLightingMode", &Pass::SetLightingMode)
        .addFunction("SetDepthWrite", &Pass::SetDepthWrite)
        .addFunction("SetAlphaMask", &Pass::SetAlphaMask)
        .addFunction("SetIsDesktop", &Pass::SetIsDesktop)
        .addFunction("SetVertexShader", &Pass::SetVertexShader)
        .addFunction("SetPixelShader", &Pass::SetPixelShader)
        .addFunction("SetVertexShaderDefines", &Pass::SetVertexShaderDefines)
        .addFunction("SetPixelShaderDefines", &Pass::SetPixelShaderDefines)
        .addFunction("ReleaseShaders", &Pass::ReleaseShaders)
        

        .addFunction("GetName", &Pass::GetName)
        .addFunction("GetIndex", &Pass::GetIndex)
        .addFunction("GetBlendMode", &Pass::GetBlendMode)
        .addFunction("GetCullMode", &Pass::GetCullMode)
        .addFunction("GetDepthTestMode", &Pass::GetDepthTestMode)
        .addFunction("GetLightingMode", &Pass::GetLightingMode)
        .addFunction("GetShadersLoadedFrameNumber", &Pass::GetShadersLoadedFrameNumber)
        .addFunction("GetDepthWrite", &Pass::GetDepthWrite)
        .addFunction("GetAlphaMask", &Pass::GetAlphaMask)
        .addFunction("IsDesktop", &Pass::IsDesktop)
        .addFunction("GetVertexShader", &Pass::GetVertexShader)
        .addFunction("GetPixelShader", &Pass::GetPixelShader)
        .addFunction("GetVertexShaderDefines", &Pass::GetVertexShaderDefines)
        .addFunction("GetPixelShaderDefines", &Pass::GetPixelShaderDefines)

        .addProperty("name", &Pass::GetName)
        .addProperty("index", &Pass::GetIndex)
        .addProperty("blendMode", &Pass::GetBlendMode, &Pass::SetBlendMode)
        .addProperty("cullMode", &Pass::GetCullMode, &Pass::SetCullMode)
        .addProperty("depthTestMode", &Pass::GetDepthTestMode, &Pass::SetDepthTestMode)
        .addProperty("lightingMode", &Pass::GetLightingMode, &Pass::SetLightingMode)
        .addProperty("shadersLoadedFrameNumber", &Pass::GetShadersLoadedFrameNumber)
        .addProperty("depthWrite", &Pass::GetDepthWrite, &Pass::SetDepthWrite)
        .addProperty("alphaMask", &Pass::GetAlphaMask, &Pass::SetAlphaMask)
        .addProperty("desktop", &Pass::IsDesktop)
        .addProperty("vertexShader", &Pass::GetVertexShader, &Pass::SetVertexShader)
        .addProperty("pixelShader", &Pass::GetPixelShader, &Pass::SetPixelShader)
        .addProperty("vertexShaderDefines", &Pass::GetVertexShaderDefines, &Pass::SetVertexShaderDefines)
        .addProperty("pixelShaderDefines", &Pass::GetPixelShaderDefines, &Pass::SetPixelShaderDefines)        
    );

    lua["Technique"].setClass(UserdataMetatable<Technique, Resource>()
        .addStaticFunction("new", &CreateObject<Technique>)
        
        .addFunction("SetIsDesktop", &Technique::SetIsDesktop)
        .addFunction("CreatePass", &Technique::CreatePass)
        .addFunction("RemovePass", &Technique::RemovePass)
        .addFunction("ReleaseShaders", &Technique::ReleaseShaders)
        
        .addFunction("Clone", TechniqueClone())

        .addFunction("IsDesktop", &Technique::IsDesktop)
        .addFunction("IsSupported", &Technique::IsSupported)

        .addOverloadedFunctions("HasPass",
            static_cast<bool(Technique::*)(unsigned) const>(&Technique::HasPass),
            static_cast<bool(Technique::*)(const String&) const>(&Technique::HasPass))


        .addOverloadedFunctions("GetPass",
            static_cast<Pass*(Technique::*)(unsigned) const>(&Technique::GetPass),
            static_cast<Pass*(Technique::*)(const String&) const>(&Technique::GetPass))

        .addOverloadedFunctions("GetSupportedPass",
            static_cast<Pass*(Technique::*)(unsigned) const>(&Technique::GetSupportedPass),
            static_cast<Pass*(Technique::*)(const String&) const>(&Technique::GetSupportedPass))

        .addFunction("GetNumPasses", &Technique::GetNumPasses)

        .addFunction("GetPassNames", &Technique::GetPassNames)
        .addFunction("GetPasses", &Technique::GetPasses)

        .addProperty("desktop", &Technique::IsDesktop)
        .addProperty("supported", &Technique::IsSupported)
        .addProperty("numPasses", &Technique::GetNumPasses)        
    );
}
}

