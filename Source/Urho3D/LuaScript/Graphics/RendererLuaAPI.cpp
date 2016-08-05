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
// KAGUYA_MEMBER_FUNCTION_OVERLOADS(RendererGetScreenBuffer, Renderer, GetScreenBuffer, 6, 7);
// KAGUYA_MEMBER_FUNCTION_OVERLOADS(RendererSetBatchShaders, Renderer, SetBatchShaders, 2, 3);

void RegisterRenderer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Renderer"].setClass(UserdataMetatable<Renderer, Object>()

        .addFunction("SetNumViewports", &Renderer::SetNumViewports)
        .addFunction("SetViewport", &Renderer::SetViewport)

        .addOverloadedFunctions("SetDefaultRenderPath",
            static_cast<void(Renderer::*)(RenderPath*)>(&Renderer::SetDefaultRenderPath),
            static_cast<void(Renderer::*)(XMLFile*)>(&Renderer::SetDefaultRenderPath))

        .addFunction("SetDefaultTechnique", &Renderer::SetDefaultTechnique)
        .addFunction("SetHDRRendering", &Renderer::SetHDRRendering)
        .addFunction("SetSpecularLighting", &Renderer::SetSpecularLighting)
        .addFunction("SetTextureAnisotropy", &Renderer::SetTextureAnisotropy)
        .addFunction("SetTextureFilterMode", &Renderer::SetTextureFilterMode)
        .addFunction("SetTextureQuality", &Renderer::SetTextureQuality)
        .addFunction("SetMaterialQuality", &Renderer::SetMaterialQuality)
        .addFunction("SetDrawShadows", &Renderer::SetDrawShadows)
        .addFunction("SetShadowMapSize", &Renderer::SetShadowMapSize)
        .addFunction("SetShadowQuality", &Renderer::SetShadowQuality)
        .addFunction("SetShadowSoftness", &Renderer::SetShadowSoftness)
        .addFunction("SetShadowMapFilter", &Renderer::SetShadowMapFilter)
        .addFunction("SetReuseShadowMaps", &Renderer::SetReuseShadowMaps)
        .addFunction("SetMaxShadowMaps", &Renderer::SetMaxShadowMaps)
        .addFunction("SetDynamicInstancing", &Renderer::SetDynamicInstancing)
        .addFunction("SetNumExtraInstancingBufferElements", &Renderer::SetNumExtraInstancingBufferElements)
        .addFunction("SetMinInstances", &Renderer::SetMinInstances)
        .addFunction("SetMaxSortedInstances", &Renderer::SetMaxSortedInstances)
        .addFunction("SetMaxOccluderTriangles", &Renderer::SetMaxOccluderTriangles)
        .addFunction("SetOcclusionBufferSize", &Renderer::SetOcclusionBufferSize)
        .addFunction("SetOccluderSizeThreshold", &Renderer::SetOccluderSizeThreshold)
        .addFunction("SetThreadedOcclusion", &Renderer::SetThreadedOcclusion)
        .addFunction("SetMobileShadowBiasMul", &Renderer::SetMobileShadowBiasMul)
        .addFunction("SetMobileShadowBiasAdd", &Renderer::SetMobileShadowBiasAdd)
        .addFunction("SetMobileNormalOffsetMul", &Renderer::SetMobileNormalOffsetMul)
        
        .addFunction("ReloadShaders", &Renderer::ReloadShaders)
        
        .addFunction("GetNumViewports", &Renderer::GetNumViewports)
        .addFunction("GetViewport", &Renderer::GetViewport)
        .addFunction("GetDefaultRenderPath", &Renderer::GetDefaultRenderPath)
        .addFunction("GetDefaultTechnique", &Renderer::GetDefaultTechnique)
        .addFunction("GetHDRRendering", &Renderer::GetHDRRendering)
        .addFunction("GetSpecularLighting", &Renderer::GetSpecularLighting)
        .addFunction("GetDrawShadows", &Renderer::GetDrawShadows)
        .addFunction("GetTextureAnisotropy", &Renderer::GetTextureAnisotropy)
        .addFunction("GetTextureFilterMode", &Renderer::GetTextureFilterMode)
        .addFunction("GetTextureQuality", &Renderer::GetTextureQuality)
        .addFunction("GetMaterialQuality", &Renderer::GetMaterialQuality)
        .addFunction("GetShadowMapSize", &Renderer::GetShadowMapSize)
        .addFunction("GetShadowQuality", &Renderer::GetShadowQuality)
        .addFunction("GetShadowSoftness", &Renderer::GetShadowSoftness)
        .addFunction("GetReuseShadowMaps", &Renderer::GetReuseShadowMaps)
        .addFunction("GetMaxShadowMaps", &Renderer::GetMaxShadowMaps)
        .addFunction("GetDynamicInstancing", &Renderer::GetDynamicInstancing)
        .addFunction("GetNumExtraInstancingBufferElements", &Renderer::GetNumExtraInstancingBufferElements)
        .addFunction("GetMinInstances", &Renderer::GetMinInstances)
        .addFunction("GetMaxSortedInstances", &Renderer::GetMaxSortedInstances)
        .addFunction("GetMaxOccluderTriangles", &Renderer::GetMaxOccluderTriangles)
        .addFunction("GetOcclusionBufferSize", &Renderer::GetOcclusionBufferSize)
        .addFunction("GetOccluderSizeThreshold", &Renderer::GetOccluderSizeThreshold)
        .addFunction("GetThreadedOcclusion", &Renderer::GetThreadedOcclusion)
        .addFunction("GetMobileShadowBiasMul", &Renderer::GetMobileShadowBiasMul)
        .addFunction("GetMobileShadowBiasAdd", &Renderer::GetMobileShadowBiasAdd)
        .addFunction("GetMobileNormalOffsetMul", &Renderer::GetMobileNormalOffsetMul)
        .addFunction("GetNumViews", &Renderer::GetNumViews)
        .addFunction("GetNumPrimitives", &Renderer::GetNumPrimitives)
        .addFunction("GetNumBatches", &Renderer::GetNumBatches)
        
        .addFunction("GetNumGeometries", RendererGetNumGeometries())
        .addFunction("GetNumLights", RendererGetNumLights())
        .addFunction("GetNumShadowMaps", RendererGetNumShadowMaps())
        .addFunction("GetNumOccluders", RendererGetNumOccluders())

        // .addFunction("GetScreenBuffer", RendererGetScreenBuffer())
        // .addFunction("SetBatchShaders", RendererSetBatchShaders())
        
        .addFunction("GetDefaultZone", &Renderer::GetDefaultZone)
        .addFunction("GetDefaultMaterial", &Renderer::GetDefaultMaterial)
        .addFunction("GetDefaultLightRamp", &Renderer::GetDefaultLightRamp)
        .addFunction("GetDefaultLightSpot", &Renderer::GetDefaultLightSpot)
        
        .addFunction("DrawDebugGeometry", &Renderer::DrawDebugGeometry)
        
        .addProperty("numViewports", &Renderer::GetNumViewports, &Renderer::SetNumViewports)
        .addProperty("defaultRenderPath", &Renderer::GetDefaultRenderPath, static_cast<void(Renderer::*)(RenderPath*)>(&Renderer::SetDefaultRenderPath))
        .addProperty("defaultTechnique", &Renderer::GetDefaultTechnique, &Renderer::SetDefaultTechnique)
        .addProperty("hdrRendering", &Renderer::GetHDRRendering, &Renderer::SetHDRRendering)
        .addProperty("specularLighting", &Renderer::GetSpecularLighting, &Renderer::SetSpecularLighting)
        .addProperty("drawShadows", &Renderer::GetDrawShadows, &Renderer::SetDrawShadows)
        .addProperty("textureAnisotropy", &Renderer::GetTextureAnisotropy, &Renderer::SetTextureAnisotropy)
        .addProperty("textureFilterMode", &Renderer::GetTextureFilterMode, &Renderer::SetTextureFilterMode)
        .addProperty("textureQuality", &Renderer::GetTextureQuality, &Renderer::SetTextureQuality)
        .addProperty("materialQuality", &Renderer::GetMaterialQuality, &Renderer::SetMaterialQuality)
        .addProperty("shadowMapSize", &Renderer::GetShadowMapSize, &Renderer::SetShadowMapSize)
        .addProperty("shadowQuality", &Renderer::GetShadowQuality, &Renderer::SetShadowQuality)
        .addProperty("shadowSoftness", &Renderer::GetShadowSoftness, &Renderer::SetShadowSoftness)
        
        .addProperty("reuseShadowMaps", &Renderer::GetReuseShadowMaps, &Renderer::SetReuseShadowMaps)
        .addProperty("maxShadowMaps", &Renderer::GetMaxShadowMaps, &Renderer::SetMaxShadowMaps)
        .addProperty("dynamicInstancing", &Renderer::GetDynamicInstancing, &Renderer::SetDynamicInstancing)
        .addProperty("numExtraInstancingBufferElements", &Renderer::GetNumExtraInstancingBufferElements, &Renderer::SetNumExtraInstancingBufferElements)
        .addProperty("minInstances", &Renderer::GetMinInstances, &Renderer::SetMinInstances)
        .addProperty("maxSortedInstances", &Renderer::GetMaxSortedInstances, &Renderer::SetMaxSortedInstances)
        .addProperty("maxOccluderTriangles", &Renderer::GetMaxOccluderTriangles, &Renderer::SetMaxOccluderTriangles)
        .addProperty("occlusionBufferSize", &Renderer::GetOcclusionBufferSize, &Renderer::SetOcclusionBufferSize)
        .addProperty("occluderSizeThreshold", &Renderer::GetOccluderSizeThreshold, &Renderer::SetOccluderSizeThreshold)
        .addProperty("threadedOcclusion", &Renderer::GetThreadedOcclusion, &Renderer::SetThreadedOcclusion)
        .addProperty("mobileShadowBiasMul", &Renderer::GetMobileShadowBiasMul, &Renderer::SetMobileShadowBiasMul)
        .addProperty("mobileShadowBiasAdd", &Renderer::GetMobileShadowBiasAdd, &Renderer::SetMobileShadowBiasAdd)
        .addProperty("mobileNormalOffsetMul", &Renderer::GetMobileNormalOffsetMul, &Renderer::SetMobileNormalOffsetMul)
        
        .addProperty("numViews", &Renderer::GetNumViews)
        .addProperty("numPrimitives", &Renderer::GetNumPrimitives)
        .addProperty("numBatches", &Renderer::GetNumBatches)
        .addProperty("defaultZone", &Renderer::GetDefaultZone)
        .addProperty("defaultMaterial", &Renderer::GetDefaultMaterial)
        .addProperty("defaultLightRamp", &Renderer::GetDefaultLightRamp)
        .addProperty("defaultLightSpot", &Renderer::GetDefaultLightSpot)        
    );
}
}

