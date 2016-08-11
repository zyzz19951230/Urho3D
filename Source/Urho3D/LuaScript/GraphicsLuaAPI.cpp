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

#include "../Precompiled.h"

#include <kaguya.hpp>

namespace Urho3D
{

extern void RegisterAnimatedModel(kaguya::State& lua);
extern void RegisterAnimation(kaguya::State& lua);
extern void RegisterAnimationController(kaguya::State& lua);
extern void RegisterAnimationState(kaguya::State& lua);
extern void RegisterBillboardSet(kaguya::State& lua);
extern void RegisterCamera(kaguya::State& lua);
extern void RegisterCustomGeometry(kaguya::State& lua);
extern void RegisterDebugRenderer(kaguya::State& lua);
extern void RegisterDecalSet(kaguya::State& lua);
extern void RegisterDrawable(kaguya::State& lua);
extern void RegisterGeometry(kaguya::State& lua);
extern void RegisterGraphics(kaguya::State& lua);
extern void RegisterGraphicsDefs(kaguya::State& lua);
extern void RegisterIndexBuffer(kaguya::State& lua);
extern void RegisterLight(kaguya::State& lua);
extern void RegisterMaterial(kaguya::State& lua);
extern void RegisterModel(kaguya::State& lua);
extern void RegisterOctree(kaguya::State& lua);
extern void RegisterOctreeQuery(kaguya::State& lua);
extern void RegisterParticleEffect(kaguya::State& lua);
extern void RegisterParticleEmitter(kaguya::State& lua);
extern void RegisterRenderer(kaguya::State& lua);
extern void RegisterRenderPath(kaguya::State& lua);
extern void RegisterRenderSurface(kaguya::State& lua);
extern void RegisterRibbonTrail(kaguya::State& lua);
extern void RegisterSkeleton(kaguya::State& lua);
extern void RegisterSkybox(kaguya::State& lua);
extern void RegisterStaticModel(kaguya::State& lua);
extern void RegisterStaticModelGroup(kaguya::State& lua);
extern void RegisterTechnique(kaguya::State& lua);
extern void RegisterTerrain(kaguya::State& lua);
extern void RegisterTerrainPatch(kaguya::State& lua);
extern void RegisterTexture(kaguya::State& lua);
extern void RegisterTexture2D(kaguya::State& lua);
extern void RegisterTexture2DArray(kaguya::State& lua);
extern void RegisterTexture3D(kaguya::State& lua);
extern void RegisterTextureCube(kaguya::State& lua);
extern void RegisterVertexBuffer(kaguya::State& lua);
extern void RegisterViewport(kaguya::State& lua);
extern void RegisterZone(kaguya::State& lua);

void RegisterGraphicsLuaAPI(kaguya::State& lua)
{
    RegisterCamera(lua);
    RegisterGeometry(lua);
    RegisterMaterial(lua);
    RegisterDebugRenderer(lua);
    RegisterGraphics(lua);
    RegisterGraphicsDefs(lua);
    RegisterIndexBuffer(lua);
    RegisterRenderer(lua);
    RegisterRenderPath(lua);
    RegisterRenderSurface(lua);
    RegisterTechnique(lua);
    RegisterTexture(lua);
    RegisterTexture2D(lua);
    RegisterTexture2DArray(lua);
    RegisterTexture3D(lua);
    RegisterTextureCube(lua);
    RegisterVertexBuffer(lua);
    RegisterViewport(lua); 
    
    RegisterAnimation(lua);
    RegisterAnimationController(lua);
    RegisterAnimationState(lua);
    RegisterModel(lua);
    RegisterOctree(lua);
    RegisterOctreeQuery(lua);
    RegisterParticleEffect(lua);
    RegisterSkeleton(lua);
    RegisterTerrain(lua);

    RegisterDrawable(lua);
    RegisterStaticModel(lua);

    RegisterAnimatedModel(lua);
    RegisterBillboardSet(lua);
    RegisterCustomGeometry(lua);
    RegisterDecalSet(lua);
    RegisterLight(lua);
    RegisterParticleEmitter(lua);
    RegisterRibbonTrail(lua);
    RegisterSkybox(lua);
    RegisterStaticModelGroup(lua);
    RegisterTerrainPatch(lua);
    RegisterZone(lua);
}
}
