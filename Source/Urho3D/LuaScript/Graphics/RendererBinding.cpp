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

#include "../../Graphics/Renderer.h"
#include "../../Graphics/RenderPath.h"
#include "../../Graphics/Technique.h"
#include "../../Graphics/Texture2D.h"
#include "../../Graphics/Zone.h"
#include "../../Resource/XMLFile.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(RendererGetNumGeometries, Renderer, GetNumGeometries, 0, 1);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(RendererGetNumLights, Renderer, GetNumLights, 0, 1);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(RendererGetNumShadowMaps, Renderer, GetNumShadowMaps, 0, 1);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(RendererGetNumOccluders, Renderer, GetNumOccluders, 0, 1);

void RegisterRenderer(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Renderer : Object
    lua["Renderer"].setClass(UserdataMetatable<Renderer, Object>()

        // [Method] void SetNumViewports(unsigned num)
        .addFunction("SetNumViewports", &Renderer::SetNumViewports)
        // [Method] void SetViewport(unsigned index, Viewport* viewport)
        .addFunction("SetViewport", &Renderer::SetViewport)

        .addOverloadedFunctions("SetDefaultRenderPath",
            // [Method] void SetDefaultRenderPath(RenderPath* renderPath)
            static_cast<void(Renderer::*)(RenderPath*)>(&Renderer::SetDefaultRenderPath),
            // [Method] void SetDefaultRenderPath(XMLFile* xmlFile)
            static_cast<void(Renderer::*)(XMLFile*)>(&Renderer::SetDefaultRenderPath))

        // [Method] void SetDefaultTechnique(Technique* tech)
        .addFunction("SetDefaultTechnique", &Renderer::SetDefaultTechnique)
        // [Method] void SetHDRRendering(bool enable)
        .addFunction("SetHDRRendering", &Renderer::SetHDRRendering)
        // [Method] void SetSpecularLighting(bool enable)
        .addFunction("SetSpecularLighting", &Renderer::SetSpecularLighting)
        // [Method] void SetTextureAnisotropy(int level)
        .addFunction("SetTextureAnisotropy", &Renderer::SetTextureAnisotropy)
        // [Method] void SetTextureFilterMode(TextureFilterMode mode)
        .addFunction("SetTextureFilterMode", &Renderer::SetTextureFilterMode)
        // [Method] void SetTextureQuality(int quality)
        .addFunction("SetTextureQuality", &Renderer::SetTextureQuality)
        // [Method] void SetMaterialQuality(int quality)
        .addFunction("SetMaterialQuality", &Renderer::SetMaterialQuality)
        // [Method] void SetDrawShadows(bool enable)
        .addFunction("SetDrawShadows", &Renderer::SetDrawShadows)
        // [Method] void SetShadowMapSize(int size)
        .addFunction("SetShadowMapSize", &Renderer::SetShadowMapSize)
        // [Method] void SetShadowQuality(ShadowQuality quality)
        .addFunction("SetShadowQuality", &Renderer::SetShadowQuality)
        // [Method] void SetShadowSoftness(float shadowSoftness)
        .addFunction("SetShadowSoftness", &Renderer::SetShadowSoftness)
        // [Method] void SetShadowMapFilter(Object* instance, ShadowMapFilter functionPtr)
        .addFunction("SetShadowMapFilter", &Renderer::SetShadowMapFilter)
        // [Method] void SetReuseShadowMaps(bool enable)
        .addFunction("SetReuseShadowMaps", &Renderer::SetReuseShadowMaps)
        // [Method] void SetMaxShadowMaps(int shadowMaps)
        .addFunction("SetMaxShadowMaps", &Renderer::SetMaxShadowMaps)
        // [Method] void SetDynamicInstancing(bool enable)
        .addFunction("SetDynamicInstancing", &Renderer::SetDynamicInstancing)
        // [Method] void SetNumExtraInstancingBufferElements(int elements)
        .addFunction("SetNumExtraInstancingBufferElements", &Renderer::SetNumExtraInstancingBufferElements)
        // [Method] void SetMinInstances(int instances)
        .addFunction("SetMinInstances", &Renderer::SetMinInstances)
        // [Method] void SetMaxSortedInstances(int instances)
        .addFunction("SetMaxSortedInstances", &Renderer::SetMaxSortedInstances)
        // [Method] void SetMaxOccluderTriangles(int triangles)
        .addFunction("SetMaxOccluderTriangles", &Renderer::SetMaxOccluderTriangles)
        // [Method] void SetOcclusionBufferSize(int size)
        .addFunction("SetOcclusionBufferSize", &Renderer::SetOcclusionBufferSize)
        // [Method] void SetOccluderSizeThreshold(float screenSize)
        .addFunction("SetOccluderSizeThreshold", &Renderer::SetOccluderSizeThreshold)
        // [Method] void SetThreadedOcclusion(bool enable)
        .addFunction("SetThreadedOcclusion", &Renderer::SetThreadedOcclusion)
        // [Method] void SetMobileShadowBiasMul(float mul)
        .addFunction("SetMobileShadowBiasMul", &Renderer::SetMobileShadowBiasMul)
        // [Method] void SetMobileShadowBiasAdd(float add)
        .addFunction("SetMobileShadowBiasAdd", &Renderer::SetMobileShadowBiasAdd)
        // [Method] void SetMobileNormalOffsetMul(float mul)
        .addFunction("SetMobileNormalOffsetMul", &Renderer::SetMobileNormalOffsetMul)
        
        // [Method] void ReloadShaders()
        .addFunction("ReloadShaders", &Renderer::ReloadShaders)
        
        // [Method] unsigned GetNumViewports() const
        .addFunction("GetNumViewports", &Renderer::GetNumViewports)
        // [Method] Viewport* GetViewport(unsigned index) const
        .addFunction("GetViewport", &Renderer::GetViewport)
        // [Method] RenderPath* GetDefaultRenderPath() const
        .addFunction("GetDefaultRenderPath", &Renderer::GetDefaultRenderPath)
        // [Method] Technique* GetDefaultTechnique() const
        .addFunction("GetDefaultTechnique", &Renderer::GetDefaultTechnique)
        // [Method] bool GetHDRRendering() const
        .addFunction("GetHDRRendering", &Renderer::GetHDRRendering)
        // [Method] bool GetSpecularLighting() const
        .addFunction("GetSpecularLighting", &Renderer::GetSpecularLighting)
        // [Method] bool GetDrawShadows() const
        .addFunction("GetDrawShadows", &Renderer::GetDrawShadows)
        // [Method] int GetTextureAnisotropy() const
        .addFunction("GetTextureAnisotropy", &Renderer::GetTextureAnisotropy)
        // [Method] TextureFilterMode GetTextureFilterMode() const
        .addFunction("GetTextureFilterMode", &Renderer::GetTextureFilterMode)
        // [Method] int GetTextureQuality() const
        .addFunction("GetTextureQuality", &Renderer::GetTextureQuality)
        // [Method] int GetMaterialQuality() const
        .addFunction("GetMaterialQuality", &Renderer::GetMaterialQuality)
        // [Method] int GetShadowMapSize() const
        .addFunction("GetShadowMapSize", &Renderer::GetShadowMapSize)
        // [Method] ShadowQuality GetShadowQuality() const
        .addFunction("GetShadowQuality", &Renderer::GetShadowQuality)
        // [Method] float GetShadowSoftness() const
        .addFunction("GetShadowSoftness", &Renderer::GetShadowSoftness)
        // [Method] bool GetReuseShadowMaps() const
        .addFunction("GetReuseShadowMaps", &Renderer::GetReuseShadowMaps)
        // [Method] int GetMaxShadowMaps() const
        .addFunction("GetMaxShadowMaps", &Renderer::GetMaxShadowMaps)
        // [Method] bool GetDynamicInstancing() const
        .addFunction("GetDynamicInstancing", &Renderer::GetDynamicInstancing)
        // [Method] int GetNumExtraInstancingBufferElements() const
        .addFunction("GetNumExtraInstancingBufferElements", &Renderer::GetNumExtraInstancingBufferElements)
        // [Method] int GetMinInstances() const
        .addFunction("GetMinInstances", &Renderer::GetMinInstances)
        // [Method] int GetMaxSortedInstances() const
        .addFunction("GetMaxSortedInstances", &Renderer::GetMaxSortedInstances)
        // [Method] int GetMaxOccluderTriangles() const
        .addFunction("GetMaxOccluderTriangles", &Renderer::GetMaxOccluderTriangles)
        // [Method] int GetOcclusionBufferSize() const
        .addFunction("GetOcclusionBufferSize", &Renderer::GetOcclusionBufferSize)
        // [Method] float GetOccluderSizeThreshold() const
        .addFunction("GetOccluderSizeThreshold", &Renderer::GetOccluderSizeThreshold)
        // [Method] bool GetThreadedOcclusion() const
        .addFunction("GetThreadedOcclusion", &Renderer::GetThreadedOcclusion)
        // [Method] float GetMobileShadowBiasMul() const
        .addFunction("GetMobileShadowBiasMul", &Renderer::GetMobileShadowBiasMul)
        // [Method] float GetMobileShadowBiasAdd() const
        .addFunction("GetMobileShadowBiasAdd", &Renderer::GetMobileShadowBiasAdd)
        // [Method] float GetMobileNormalOffsetMul() const
        .addFunction("GetMobileNormalOffsetMul", &Renderer::GetMobileNormalOffsetMul)
        // [Method] unsigned GetNumViews() const
        .addFunction("GetNumViews", &Renderer::GetNumViews)
        // [Method] unsigned GetNumPrimitives() const
        .addFunction("GetNumPrimitives", &Renderer::GetNumPrimitives)
        // [Method] unsigned GetNumBatches() const
        .addFunction("GetNumBatches", &Renderer::GetNumBatches)
        
        // [Method] unsigned GetNumGeometries(bool allViews = false) const
        .addFunction("GetNumGeometries", RendererGetNumGeometries())
        // [Method] unsigned GetNumLights(bool allViews = false) const
        .addFunction("GetNumLights", RendererGetNumLights())
        // [Method] unsigned GetNumShadowMaps(bool allViews = false) const
        .addFunction("GetNumShadowMaps", RendererGetNumShadowMaps())
        // [Method] unsigned GetNumOccluders(bool allViews = false) const
        .addFunction("GetNumOccluders", RendererGetNumOccluders())

        // [Method] Zone* GetDefaultZone() const
        .addFunction("GetDefaultZone", &Renderer::GetDefaultZone)
        // [Method] Material* GetDefaultMaterial() const
        .addFunction("GetDefaultMaterial", &Renderer::GetDefaultMaterial)
        // [Method] Texture2D* GetDefaultLightRamp() const
        .addFunction("GetDefaultLightRamp", &Renderer::GetDefaultLightRamp)
        // [Method] Texture2D* GetDefaultLightSpot() const
        .addFunction("GetDefaultLightSpot", &Renderer::GetDefaultLightSpot)
        
        // [Method] void DrawDebugGeometry(bool depthTest)
        .addFunction("DrawDebugGeometry", &Renderer::DrawDebugGeometry)
        
        // [Property] unsigned numViewports
        .addProperty("numViewports", &Renderer::GetNumViewports, &Renderer::SetNumViewports)
        // [Property] RenderPath* defaultRenderPath
        .addProperty("defaultRenderPath", &Renderer::GetDefaultRenderPath, static_cast<void(Renderer::*)(RenderPath*)>(&Renderer::SetDefaultRenderPath))
        // [Property] Technique* defaultTechnique
        .addProperty("defaultTechnique", &Renderer::GetDefaultTechnique, &Renderer::SetDefaultTechnique)
        // [Property] bool hdrRendering
        .addProperty("hdrRendering", &Renderer::GetHDRRendering, &Renderer::SetHDRRendering)
        // [Property] bool specularLighting
        .addProperty("specularLighting", &Renderer::GetSpecularLighting, &Renderer::SetSpecularLighting)
        // [Property] bool drawShadows
        .addProperty("drawShadows", &Renderer::GetDrawShadows, &Renderer::SetDrawShadows)
        // [Property] int textureAnisotropy
        .addProperty("textureAnisotropy", &Renderer::GetTextureAnisotropy, &Renderer::SetTextureAnisotropy)
        // [Property] TextureFilterMode textureFilterMode
        .addProperty("textureFilterMode", &Renderer::GetTextureFilterMode, &Renderer::SetTextureFilterMode)
        // [Property] int textureQuality
        .addProperty("textureQuality", &Renderer::GetTextureQuality, &Renderer::SetTextureQuality)
        // [Property] int materialQuality
        .addProperty("materialQuality", &Renderer::GetMaterialQuality, &Renderer::SetMaterialQuality)
        // [Property] int shadowMapSize
        .addProperty("shadowMapSize", &Renderer::GetShadowMapSize, &Renderer::SetShadowMapSize)
        // [Property] ShadowQuality shadowQuality
        .addProperty("shadowQuality", &Renderer::GetShadowQuality, &Renderer::SetShadowQuality)
        // [Property] float shadowSoftness
        .addProperty("shadowSoftness", &Renderer::GetShadowSoftness, &Renderer::SetShadowSoftness)
        
        // [Property] bool reuseShadowMaps
        .addProperty("reuseShadowMaps", &Renderer::GetReuseShadowMaps, &Renderer::SetReuseShadowMaps)
        // [Property] int maxShadowMaps
        .addProperty("maxShadowMaps", &Renderer::GetMaxShadowMaps, &Renderer::SetMaxShadowMaps)
        // [Property] bool dynamicInstancing
        .addProperty("dynamicInstancing", &Renderer::GetDynamicInstancing, &Renderer::SetDynamicInstancing)
        // [Property] int numExtraInstancingBufferElements
        .addProperty("numExtraInstancingBufferElements", &Renderer::GetNumExtraInstancingBufferElements, &Renderer::SetNumExtraInstancingBufferElements)
        // [Property] int minInstances
        .addProperty("minInstances", &Renderer::GetMinInstances, &Renderer::SetMinInstances)
        // [Property] int maxSortedInstances
        .addProperty("maxSortedInstances", &Renderer::GetMaxSortedInstances, &Renderer::SetMaxSortedInstances)
        // [Property] int maxOccluderTriangles
        .addProperty("maxOccluderTriangles", &Renderer::GetMaxOccluderTriangles, &Renderer::SetMaxOccluderTriangles)
        // [Property] int occlusionBufferSize
        .addProperty("occlusionBufferSize", &Renderer::GetOcclusionBufferSize, &Renderer::SetOcclusionBufferSize)
        // [Property] float occluderSizeThreshold
        .addProperty("occluderSizeThreshold", &Renderer::GetOccluderSizeThreshold, &Renderer::SetOccluderSizeThreshold)
        // [Property] bool threadedOcclusion
        .addProperty("threadedOcclusion", &Renderer::GetThreadedOcclusion, &Renderer::SetThreadedOcclusion)
        // [Property] float mobileShadowBiasMul
        .addProperty("mobileShadowBiasMul", &Renderer::GetMobileShadowBiasMul, &Renderer::SetMobileShadowBiasMul)
        // [Property] float mobileShadowBiasAdd
        .addProperty("mobileShadowBiasAdd", &Renderer::GetMobileShadowBiasAdd, &Renderer::SetMobileShadowBiasAdd)
        // [Property] float mobileNormalOffsetMul
        .addProperty("mobileNormalOffsetMul", &Renderer::GetMobileNormalOffsetMul, &Renderer::SetMobileNormalOffsetMul)
        
        // [Property(Readonly)] unsigned numViews
        .addProperty("numViews", &Renderer::GetNumViews)
        // [Property(Readonly)] unsigned numPrimitives
        .addProperty("numPrimitives", &Renderer::GetNumPrimitives)
        // [Property(Readonly)] unsigned numBatches
        .addProperty("numBatches", &Renderer::GetNumBatches)
        // [Property(Readonly)] Zone* defaultZone
        .addProperty("defaultZone", &Renderer::GetDefaultZone)
        // [Property(Readonly)] Material* defaultMaterial
        .addProperty("defaultMaterial", &Renderer::GetDefaultMaterial)
        // [Property(Readonly)] Texture2D* defaultLightRamp
        .addProperty("defaultLightRamp", &Renderer::GetDefaultLightRamp)
        // [Property(Readonly)] Texture2D* defaultLightSpot
        .addProperty("defaultLightSpot", &Renderer::GetDefaultLightSpot)        
    );
    
    // [Variable] Renderer* renderer
    lua["renderer"] = GetSubsystem<Renderer>();
    // [Function] Renderer* GetRenderer()
    lua["GetRenderer"] = static_cast<Renderer*(*)()>(&GetSubsystem<Renderer>);
}
}

