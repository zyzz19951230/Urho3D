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

#include "../../Container/ArrayPtr.h"
#include "../../Graphics/Material.h"
#include "../../Graphics/Terrain.h"
#include "../../Graphics/TerrainPatch.h"
#include "../../Resource/Image.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static Image* TerrainGetHeightMap(const Terrain* terrain)
{
    return terrain->GetHeightMap();
}

static void TerrainSetHeightMap(Terrain* terrain, Image* heightMap)
{
    terrain->SetHeightMap(heightMap);
}

void RegisterTerrain(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Terrain : Component
    lua["Terrain"].setClass(UserdataMetatable<Terrain, Component>()
        .addStaticFunction("new", &CreateObject<Terrain>)

        // [Method] void SetPatchSize(int size)
        .addFunction("SetPatchSize", &Terrain::SetPatchSize)
        // [Method] void SetSpacing(const Vector3& spacing)
        .addFunction("SetSpacing", &Terrain::SetSpacing)
        // [Method] void SetMaxLodLevels(unsigned levels)
        .addFunction("SetMaxLodLevels", &Terrain::SetMaxLodLevels)
        // [Method] void SetOcclusionLodLevel(unsigned level)
        .addFunction("SetOcclusionLodLevel", &Terrain::SetOcclusionLodLevel)
        // [Method] void SetSmoothing(bool enable)
        .addFunction("SetSmoothing", &Terrain::SetSmoothing)
        // [Method] bool SetHeightMap(Image* image)
        .addFunction("SetHeightMap", &Terrain::SetHeightMap)
        // [Method] void SetMaterial(Material* material)
        .addFunction("SetMaterial", &Terrain::SetMaterial)
        // [Method] void SetDrawDistance(float distance)
        .addFunction("SetDrawDistance", &Terrain::SetDrawDistance)
        // [Method] void SetShadowDistance(float distance)
        .addFunction("SetShadowDistance", &Terrain::SetShadowDistance)
        // [Method] void SetLodBias(float bias)
        .addFunction("SetLodBias", &Terrain::SetLodBias)
        // [Method] void SetViewMask(unsigned mask)
        .addFunction("SetViewMask", &Terrain::SetViewMask)
        // [Method] void SetLightMask(unsigned mask)
        .addFunction("SetLightMask", &Terrain::SetLightMask)
        // [Method] void SetShadowMask(unsigned mask)
        .addFunction("SetShadowMask", &Terrain::SetShadowMask)
        // [Method] void SetZoneMask(unsigned mask)
        .addFunction("SetZoneMask", &Terrain::SetZoneMask)
        // [Method] void SetMaxLights(unsigned num)
        .addFunction("SetMaxLights", &Terrain::SetMaxLights)
        // [Method] void SetCastShadows(bool enable)
        .addFunction("SetCastShadows", &Terrain::SetCastShadows)
        // [Method] void SetOccluder(bool enable)
        .addFunction("SetOccluder", &Terrain::SetOccluder)
        // [Method] void SetOccludee(bool enable)
        .addFunction("SetOccludee", &Terrain::SetOccludee)
        // [Method] void ApplyHeightMap()
        .addFunction("ApplyHeightMap", &Terrain::ApplyHeightMap)

        // [Method] int GetPatchSize() const
        .addFunction("GetPatchSize", &Terrain::GetPatchSize)
        // [Method] const Vector3& GetSpacing() const
        .addFunction("GetSpacing", &Terrain::GetSpacing)
        // [Method] const IntVector2& GetNumVertices() const
        .addFunction("GetNumVertices", &Terrain::GetNumVertices)
        // [Method] const IntVector2& GetNumPatches() const
        .addFunction("GetNumPatches", &Terrain::GetNumPatches)
        // [Method] unsigned GetMaxLodLevels() const
        .addFunction("GetMaxLodLevels", &Terrain::GetMaxLodLevels)
        // [Method] unsigned GetOcclusionLodLevel() const
        .addFunction("GetOcclusionLodLevel", &Terrain::GetOcclusionLodLevel)
        // [Method] bool GetSmoothing() const
        .addFunction("GetSmoothing", &Terrain::GetSmoothing)
        // [Method] Image* GetHeightMap() const
        .addFunction("GetHeightMap", &Terrain::GetHeightMap)
        // [Method] Material* GetMaterial() const
        .addFunction("GetMaterial", &Terrain::GetMaterial)

        .addOverloadedFunctions("GetPatch",
            static_cast<TerrainPatch*(Terrain::*)(unsigned) const>(&Terrain::GetPatch),
            static_cast<TerrainPatch*(Terrain::*)(int, int) const>(&Terrain::GetPatch))

        // [Method] float GetHeight(const Vector3& worldPosition) const
        .addFunction("GetHeight", &Terrain::GetHeight)
        // [Method] Vector3 GetNormal(const Vector3& worldPosition) const
        .addFunction("GetNormal", &Terrain::GetNormal)
        // [Method] IntVector2 WorldToHeightMap(const Vector3& worldPosition) const
        .addFunction("WorldToHeightMap", &Terrain::WorldToHeightMap)
        // [Method] void UpdatePatchLod(TerrainPatch* patch)
        .addFunction("UpdatePatchLod", &Terrain::UpdatePatchLod)

        // [Property] int patchSize
        .addProperty("patchSize", &Terrain::GetPatchSize, &Terrain::SetPatchSize)
        // [Property] const Vector3& spacing
        .addProperty("spacing", &Terrain::GetSpacing, &Terrain::SetSpacing)
        // [Property(ReadOnly)] const IntVector2& numVertices
        .addProperty("numVertices", &Terrain::GetNumVertices)
        // [Property(ReadOnly)] const IntVector2& numPatches
        .addProperty("numPatches", &Terrain::GetNumPatches)
        // [Property] unsigned maxLodLevels
        .addProperty("maxLodLevels", &Terrain::GetMaxLodLevels, &Terrain::SetMaxLodLevels)
        // [Property] unsigned occlusionLodLevel
        .addProperty("occlusionLodLevel", &Terrain::GetOcclusionLodLevel, &Terrain::SetOcclusionLodLevel)
        // [Property] bool smoothing
        .addProperty("smoothing", &Terrain::GetSmoothing, &Terrain::SetSmoothing)
        .addProperty("heightMap", &TerrainGetHeightMap, &TerrainSetHeightMap)
        // [Property] Material* material
        .addProperty("material", &Terrain::GetMaterial, &Terrain::SetMaterial)
        // [Property(WriteOnly)] void drawDistance
        .addProperty("drawDistance", &Terrain::SetDrawDistance)
        // [Property(WriteOnly)] void shadowDistance
        .addProperty("shadowDistance", &Terrain::SetShadowDistance)
        // [Property(WriteOnly)] void lodBias
        .addProperty("lodBias", &Terrain::SetLodBias)
        // [Property(WriteOnly)] void viewMask
        .addProperty("viewMask", &Terrain::SetViewMask)
        // [Property(WriteOnly)] void lightMask
        .addProperty("lightMask", &Terrain::SetLightMask)
        // [Property(WriteOnly)] void shadowMask
        .addProperty("shadowMask", &Terrain::SetShadowMask)
        // [Property(WriteOnly)] void zoneMask
        .addProperty("zoneMask", &Terrain::SetZoneMask)
        // [Property(WriteOnly)] void maxLights
        .addProperty("maxLights", &Terrain::SetMaxLights)
        // [Property(WriteOnly)] void castShadows
        .addProperty("castShadows", &Terrain::SetCastShadows)
        // [Property(WriteOnly)] void occluder
        .addProperty("occluder", &Terrain::SetOccluder)
        // [Property(WriteOnly)] void occludee
        .addProperty("occludee", &Terrain::SetOccludee)
        );
}
}

