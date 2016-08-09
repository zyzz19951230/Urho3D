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

    // [Enum] PassLightingMode
    // [Variable] LIGHTING_UNLIT,
    lua["LIGHTING_UNLIT"] = LIGHTING_UNLIT;
    // [Variable] LIGHTING_PERVERTEX,
    lua["LIGHTING_PERVERTEX"] = LIGHTING_PERVERTEX;
    // [Variable] LIGHTING_PERPIXEL
    lua["LIGHTING_PERPIXEL"] = LIGHTING_PERPIXEL;

    // [Class] Pass : RefCounted
    lua["Pass"].setClass(UserdataMetatable<Pass, RefCounted>()
        .setConstructors<Pass(const String&)>()
        
        // [Method] void SetBlendMode(BlendMode mode)
        .addFunction("SetBlendMode", &Pass::SetBlendMode)
        // [Method] void SetCullMode(CullMode mode)
        .addFunction("SetCullMode", &Pass::SetCullMode)
        // [Method] void SetDepthTestMode(CompareMode mode)
        .addFunction("SetDepthTestMode", &Pass::SetDepthTestMode)
        // [Method] void SetLightingMode(PassLightingMode mode)
        .addFunction("SetLightingMode", &Pass::SetLightingMode)
        // [Method] void SetDepthWrite(bool enable)
        .addFunction("SetDepthWrite", &Pass::SetDepthWrite)
        // [Method] void SetAlphaMask(bool enable)
        .addFunction("SetAlphaMask", &Pass::SetAlphaMask)
        // [Method] void SetIsDesktop(bool enable)
        .addFunction("SetIsDesktop", &Pass::SetIsDesktop)
        // [Method] void SetVertexShader(const String& name)
        .addFunction("SetVertexShader", &Pass::SetVertexShader)
        // [Method] void SetPixelShader(const String& name)
        .addFunction("SetPixelShader", &Pass::SetPixelShader)
        // [Method] void SetVertexShaderDefines(const String& defines)
        .addFunction("SetVertexShaderDefines", &Pass::SetVertexShaderDefines)
        // [Method] void SetPixelShaderDefines(const String& defines)
        .addFunction("SetPixelShaderDefines", &Pass::SetPixelShaderDefines)
        // [Method] void ReleaseShaders()
        .addFunction("ReleaseShaders", &Pass::ReleaseShaders)
        

        // [Method] const String& GetName() const
        .addFunction("GetName", &Pass::GetName)
        // [Method] unsigned GetIndex() const
        .addFunction("GetIndex", &Pass::GetIndex)
        // [Method] BlendMode GetBlendMode() const
        .addFunction("GetBlendMode", &Pass::GetBlendMode)
        // [Method] CullMode GetCullMode() const
        .addFunction("GetCullMode", &Pass::GetCullMode)
        // [Method] CompareMode GetDepthTestMode() const
        .addFunction("GetDepthTestMode", &Pass::GetDepthTestMode)
        // [Method] PassLightingMode GetLightingMode() const
        .addFunction("GetLightingMode", &Pass::GetLightingMode)
        // [Method] unsigned GetShadersLoadedFrameNumber() const
        .addFunction("GetShadersLoadedFrameNumber", &Pass::GetShadersLoadedFrameNumber)
        // [Method] bool GetDepthWrite() const
        .addFunction("GetDepthWrite", &Pass::GetDepthWrite)
        // [Method] bool GetAlphaMask() const
        .addFunction("GetAlphaMask", &Pass::GetAlphaMask)
        // [Method] bool IsDesktop() const
        .addFunction("IsDesktop", &Pass::IsDesktop)
        // [Method] const String& GetVertexShader() const
        .addFunction("GetVertexShader", &Pass::GetVertexShader)
        // [Method] const String& GetPixelShader() const
        .addFunction("GetPixelShader", &Pass::GetPixelShader)
        // [Method] const String& GetVertexShaderDefines() const
        .addFunction("GetVertexShaderDefines", &Pass::GetVertexShaderDefines)
        // [Method] const String& GetPixelShaderDefines() const
        .addFunction("GetPixelShaderDefines", &Pass::GetPixelShaderDefines)

        // [Property(ReadOnly)] const String& name
        .addProperty("name", &Pass::GetName)
        // [Property(ReadOnly)] unsigned index
        .addProperty("index", &Pass::GetIndex)
        // [Property] BlendMode blendMode
        .addProperty("blendMode", &Pass::GetBlendMode, &Pass::SetBlendMode)
        // [Property] CullMode cullMode
        .addProperty("cullMode", &Pass::GetCullMode, &Pass::SetCullMode)
        // [Property] CompareMode depthTestMode
        .addProperty("depthTestMode", &Pass::GetDepthTestMode, &Pass::SetDepthTestMode)
        // [Property] PassLightingMode lightingMode
        .addProperty("lightingMode", &Pass::GetLightingMode, &Pass::SetLightingMode)
        // [Property(ReadOnly)] unsigned shadersLoadedFrameNumber
        .addProperty("shadersLoadedFrameNumber", &Pass::GetShadersLoadedFrameNumber)
        // [Property] bool depthWrite
        .addProperty("depthWrite", &Pass::GetDepthWrite, &Pass::SetDepthWrite)
        // [Property] bool alphaMask
        .addProperty("alphaMask", &Pass::GetAlphaMask, &Pass::SetAlphaMask)
        // [Property(ReadOnly)] bool desktop
        .addProperty("desktop", &Pass::IsDesktop)
        // [Property] const String& vertexShader
        .addProperty("vertexShader", &Pass::GetVertexShader, &Pass::SetVertexShader)
        // [Property] const String& pixelShader
        .addProperty("pixelShader", &Pass::GetPixelShader, &Pass::SetPixelShader)
        // [Property] const String& vertexShaderDefines
        .addProperty("vertexShaderDefines", &Pass::GetVertexShaderDefines, &Pass::SetVertexShaderDefines)
        // [Property] const String& pixelShaderDefines
        .addProperty("pixelShaderDefines", &Pass::GetPixelShaderDefines, &Pass::SetPixelShaderDefines)        
    );

    // [Class] Technique : Resource
    lua["Technique"].setClass(UserdataMetatable<Technique, Resource>()
        .addStaticFunction("new", &CreateObject<Technique>)
        
        // [Method] void SetIsDesktop(bool enable)
        .addFunction("SetIsDesktop", &Technique::SetIsDesktop)
        // [Method] Pass* CreatePass(const String& passName)
        .addFunction("CreatePass", &Technique::CreatePass)
        // [Method] void RemovePass(const String& passName)
        .addFunction("RemovePass", &Technique::RemovePass)
        // [Method] void ReleaseShaders()
        .addFunction("ReleaseShaders", &Technique::ReleaseShaders)
        
        // [Method] SharedPtr<Technique> Clone(const String& cloneName = String::EMPTY) const
        .addFunction("Clone", TechniqueClone())

        // [Method] bool IsDesktop() const
        .addFunction("IsDesktop", &Technique::IsDesktop)
        // [Method] bool IsSupported() const
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

        // [Method] unsigned GetNumPasses() const
        .addFunction("GetNumPasses", &Technique::GetNumPasses)

        // [Method] Vector<String> GetPassNames() const
        .addFunction("GetPassNames", &Technique::GetPassNames)
        // [Method] PODVector<Pass*> GetPasses() const
        .addFunction("GetPasses", &Technique::GetPasses)

        // [Property(ReadOnly)] bool desktop
        .addProperty("desktop", &Technique::IsDesktop)
        // [Property(ReadOnly)] bool supported
        .addProperty("supported", &Technique::IsSupported)
        // [Property(ReadOnly)] unsigned numPasses
        .addProperty("numPasses", &Technique::GetNumPasses)        
    );
}
}

