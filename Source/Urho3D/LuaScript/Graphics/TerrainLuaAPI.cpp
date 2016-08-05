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

    lua["Terrain"].setClass(UserdataMetatable<Terrain, Component>()
        .addStaticFunction("new", &CreateObject<Terrain>)

        .addFunction("SetPatchSize", &Terrain::SetPatchSize)
        .addFunction("SetSpacing", &Terrain::SetSpacing)
        .addFunction("SetMaxLodLevels", &Terrain::SetMaxLodLevels)
        .addFunction("SetOcclusionLodLevel", &Terrain::SetOcclusionLodLevel)
        .addFunction("SetSmoothing", &Terrain::SetSmoothing)
        .addFunction("SetHeightMap", &Terrain::SetHeightMap)
        .addFunction("SetMaterial", &Terrain::SetMaterial)
        .addFunction("SetDrawDistance", &Terrain::SetDrawDistance)
        .addFunction("SetShadowDistance", &Terrain::SetShadowDistance)
        .addFunction("SetLodBias", &Terrain::SetLodBias)
        .addFunction("SetViewMask", &Terrain::SetViewMask)
        .addFunction("SetLightMask", &Terrain::SetLightMask)
        .addFunction("SetShadowMask", &Terrain::SetShadowMask)
        .addFunction("SetZoneMask", &Terrain::SetZoneMask)
        .addFunction("SetMaxLights", &Terrain::SetMaxLights)
        .addFunction("SetCastShadows", &Terrain::SetCastShadows)
        .addFunction("SetOccluder", &Terrain::SetOccluder)
        .addFunction("SetOccludee", &Terrain::SetOccludee)
        .addFunction("ApplyHeightMap", &Terrain::ApplyHeightMap)

        .addFunction("GetPatchSize", &Terrain::GetPatchSize)
        .addFunction("GetSpacing", &Terrain::GetSpacing)
        .addFunction("GetNumVertices", &Terrain::GetNumVertices)
        .addFunction("GetNumPatches", &Terrain::GetNumPatches)
        .addFunction("GetMaxLodLevels", &Terrain::GetMaxLodLevels)
        .addFunction("GetOcclusionLodLevel", &Terrain::GetOcclusionLodLevel)
        .addFunction("GetSmoothing", &Terrain::GetSmoothing)
        .addFunction("GetHeightMap", &Terrain::GetHeightMap)
        .addFunction("GetMaterial", &Terrain::GetMaterial)

        .addOverloadedFunctions("GetPatch",
            static_cast<TerrainPatch*(Terrain::*)(unsigned) const>(&Terrain::GetPatch),
            static_cast<TerrainPatch*(Terrain::*)(int, int) const>(&Terrain::GetPatch))

        .addFunction("GetHeight", &Terrain::GetHeight)
        .addFunction("GetNormal", &Terrain::GetNormal)
        .addFunction("WorldToHeightMap", &Terrain::WorldToHeightMap)
        .addFunction("UpdatePatchLod", &Terrain::UpdatePatchLod)

        .addProperty("patchSize", &Terrain::GetPatchSize, &Terrain::SetPatchSize)
        .addProperty("spacing", &Terrain::GetSpacing, &Terrain::SetSpacing)
        .addProperty("numVertices", &Terrain::GetNumVertices)
        .addProperty("numPatches", &Terrain::GetNumPatches)
        .addProperty("maxLodLevels", &Terrain::GetMaxLodLevels, &Terrain::SetMaxLodLevels)
        .addProperty("occlusionLodLevel", &Terrain::GetOcclusionLodLevel, &Terrain::SetOcclusionLodLevel)
        .addProperty("smoothing", &Terrain::GetSmoothing, &Terrain::SetSmoothing)
        .addProperty("heightMap", &TerrainGetHeightMap, &TerrainSetHeightMap)
        .addProperty("material", &Terrain::GetMaterial, &Terrain::SetMaterial)
        .addProperty("drawDistance", &Terrain::SetDrawDistance)
        .addProperty("shadowDistance", &Terrain::SetShadowDistance)
        .addProperty("lodBias", &Terrain::SetLodBias)
        .addProperty("viewMask", &Terrain::SetViewMask)
        .addProperty("lightMask", &Terrain::SetLightMask)
        .addProperty("shadowMask", &Terrain::SetShadowMask)
        .addProperty("zoneMask", &Terrain::SetZoneMask)
        .addProperty("maxLights", &Terrain::SetMaxLights)
        .addProperty("castShadows", &Terrain::SetCastShadows)
        .addProperty("occluder", &Terrain::SetOccluder)
        .addProperty("occludee", &Terrain::SetOccludee)
        );
}
}

