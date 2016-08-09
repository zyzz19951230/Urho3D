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

#include "../../Graphics/Material.h"
#include "../../Graphics/Technique.h"
#include "../../Scene/Scene.h"
#include "../../Scene/ValueAnimation.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(MaterialSetTechnique, Material, SetTechnique, 2, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(MaterialSetShaderParameterAnimation, Material, SetShaderParameterAnimation, 2, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(MaterialClone, Material, Clone, 0, 1);

void RegisterMaterial(kaguya::State& lua)
{
    using namespace kaguya;

    // [Constant] unsigned char DEFAULT_RENDER_ORDER
    lua["DEFAULT_RENDER_ORDER"] = DEFAULT_RENDER_ORDER;

    // [Class] Material : Resource
    lua["Material"].setClass(UserdataMetatable<Material, Resource>()
        // [Constructor] Material()
        .addStaticFunction("new", &CreateObject<Material>)
        
        // [Method] void SetNumTechniques(unsigned num)
        .addFunction("SetNumTechniques", &Material::SetNumTechniques)        
        // [Method] void SetTechnique(unsigned index, Technique* tech, unsigned qualityLevel = 0, float lodDistance = 0.0f)
        .addFunction("SetTechnique", MaterialSetTechnique())        
        // [Method] void SetShaderParameter(const String& name, const Variant& value)
        .addFunction("SetShaderParameter", &Material::SetShaderParameter)
        // [Method] void SetShaderParameterAnimation(const String& name, ValueAnimation* animation, WrapMode wrapMode = WM_LOOP, float speed = 1.0f)
        .addFunction("SetShaderParameterAnimation", MaterialSetShaderParameterAnimation())

        // [Method] void SetShaderParameterAnimationWrapMode(const String& name, WrapMode wrapMode)
        .addFunction("SetShaderParameterAnimationWrapMode", &Material::SetShaderParameterAnimationWrapMode)
        // [Method] void SetShaderParameterAnimationSpeed(const String& name, float speed)
        .addFunction("SetShaderParameterAnimationSpeed", &Material::SetShaderParameterAnimationSpeed)
        // [Method] void SetTexture(TextureUnit unit, Texture* texture)
        .addFunction("SetTexture", &Material::SetTexture)

        .addOverloadedFunctions("SetUVTransform",
            // [Method] void SetUVTransform(const Vector2& offset, float rotation, const Vector2& repeat)
            static_cast<void(Material::*)(const Vector2&, float, const Vector2&)>(&Material::SetUVTransform),
            // [Method] void SetUVTransform(const Vector2& offset, float rotation, float repeat)
            static_cast<void(Material::*)(const Vector2&, float, float)>(&Material::SetUVTransform))

        // [Method] void SetCullMode(CullMode mode)
        .addFunction("SetCullMode", &Material::SetCullMode)
        // [Method] void SetShadowCullMode(CullMode mode)
        .addFunction("SetShadowCullMode", &Material::SetShadowCullMode)
        // [Method] void SetFillMode(FillMode mode)
        .addFunction("SetFillMode", &Material::SetFillMode)
        // [Method] void SetDepthBias(const BiasParameters& parameters)
        .addFunction("SetDepthBias", &Material::SetDepthBias)
        // [Method] void SetRenderOrder(unsigned char order)
        .addFunction("SetRenderOrder", &Material::SetRenderOrder)
        // [Method] void SetScene(Scene* scene)
        .addFunction("SetScene", &Material::SetScene)
        // [Method] void RemoveShaderParameter(const String& name)
        .addFunction("RemoveShaderParameter", &Material::RemoveShaderParameter)
        // [Method] void ReleaseShaders()
        .addFunction("ReleaseShaders", &Material::ReleaseShaders)
        
        // [Method] SharedPtr<Material> Clone(const String& cloneName = String::EMPTY) const
        .addFunction("Clone", MaterialClone())

        // [Method] void SortTechniques()
        .addFunction("SortTechniques", &Material::SortTechniques)
        // [Method] void MarkForAuxView(unsigned frameNumber)
        .addFunction("MarkForAuxView", &Material::MarkForAuxView)
        // [Method] unsigned GetNumTechniques() const
        .addFunction("GetNumTechniques", &Material::GetNumTechniques)
        // [Method] const Vector<TechniqueEntry>& GetTechniques() const
        .addFunction("GetTechniques", &Material::GetTechniques)
        // [Method] Technique* GetTechnique(unsigned index) const
        .addFunction("GetTechnique", &Material::GetTechnique)
        // [Method] Pass* GetPass(unsigned index, const String& passName) const
        .addFunction("GetPass", &Material::GetPass)
        
        // [Method] Texture* GetTexture(TextureUnit unit) const
        .addFunction("GetTexture", &Material::GetTexture)
        // [Method] const Variant& GetShaderParameter(const String& name) const
        .addFunction("GetShaderParameter", &Material::GetShaderParameter)
        // [Method] ValueAnimation* GetShaderParameterAnimation(const String& name) const
        .addFunction("GetShaderParameterAnimation", &Material::GetShaderParameterAnimation)
        // [Method] WrapMode GetShaderParameterAnimationWrapMode(const String& name) const
        .addFunction("GetShaderParameterAnimationWrapMode", &Material::GetShaderParameterAnimationWrapMode)
        // [Method] float GetShaderParameterAnimationSpeed(const String& name) const
        .addFunction("GetShaderParameterAnimationSpeed", &Material::GetShaderParameterAnimationSpeed)
        
        // [Method] CullMode GetCullMode() const
        .addFunction("GetCullMode", &Material::GetCullMode)
        // [Method] CullMode GetShadowCullMode() const
        .addFunction("GetShadowCullMode", &Material::GetShadowCullMode)
        // [Method] FillMode GetFillMode() const
        .addFunction("GetFillMode", &Material::GetFillMode)
        // [Method] const BiasParameters& GetDepthBias() const
        .addFunction("GetDepthBias", &Material::GetDepthBias)
        // [Method] unsigned char GetRenderOrder() const
        .addFunction("GetRenderOrder", &Material::GetRenderOrder)
        // [Method] unsigned GetAuxViewFrameNumber() const
        .addFunction("GetAuxViewFrameNumber", &Material::GetAuxViewFrameNumber)
        // [Method] bool GetOcclusion() const
        .addFunction("GetOcclusion", &Material::GetOcclusion)
        // [Method] bool GetSpecular() const
        .addFunction("GetSpecular", &Material::GetSpecular)
        // [Method] Scene* GetScene() const
        .addFunction("GetScene", &Material::GetScene)
        
        // [Property] CullMode cullMode
        .addProperty("cullMode", &Material::GetCullMode, &Material::SetCullMode)
        // [Property] CullMode shadowCullMode
        .addProperty("shadowCullMode", &Material::GetShadowCullMode, &Material::SetShadowCullMode)
        // [Property] FillMode fillMode
        .addProperty("fillMode", &Material::GetFillMode, &Material::SetFillMode)
        // [Property] const BiasParameters& depthBias
        .addProperty("depthBias", &Material::GetDepthBias, &Material::SetDepthBias)
        // [Property] unsigned char renderOrder
        .addProperty("renderOrder", &Material::GetRenderOrder, &Material::SetRenderOrder)
        // [Property(ReadOnly)] bool occlusion
        .addProperty("occlusion", &Material::GetOcclusion)
        // [Property(ReadOnly)] bool specular
        .addProperty("specular", &Material::GetSpecular)
        // [Property] Scene* scene
        .addProperty("scene", &Material::GetScene, &Material::SetScene)
    );
}
}

