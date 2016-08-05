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
#include "../../Graphics/Geometry.h"
#include "../../Graphics/Material.h"
#include "../../Graphics/Terrain.h"
#include "../../Graphics/TerrainPatch.h"
#include "../../Graphics/VertexBuffer.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterTerrainPatch(kaguya::State& lua)
{
    using namespace kaguya;

    lua["TerrainPatch"].setClass(UserdataMetatable<TerrainPatch, Drawable>()
        .addStaticFunction("new", &CreateObject<TerrainPatch>)

        .addFunction("SetOwner", &TerrainPatch::SetOwner)
        .addFunction("SetNeighbors", &TerrainPatch::SetNeighbors)
        .addFunction("SetMaterial", &TerrainPatch::SetMaterial)
        .addFunction("SetBoundingBox", &TerrainPatch::SetBoundingBox)
        .addFunction("SetCoordinates", &TerrainPatch::SetCoordinates)
        
        .addFunction("ResetLod", &TerrainPatch::ResetLod)
        
        .addFunction("GetGeometry", &TerrainPatch::GetGeometry)
        .addFunction("GetMaxLodGeometry", &TerrainPatch::GetMaxLodGeometry)
        .addFunction("GetOcclusionGeometry", &TerrainPatch::GetOcclusionGeometry)        
        .addFunction("GetVertexBuffer", &TerrainPatch::GetVertexBuffer)
        .addFunction("GetOwner", &TerrainPatch::GetOwner)
        .addFunction("GetNorthPatch", &TerrainPatch::GetNorthPatch)
        .addFunction("GetSouthPatch", &TerrainPatch::GetSouthPatch)
        .addFunction("GetWestPatch", &TerrainPatch::GetWestPatch)
        .addFunction("GetEastPatch", &TerrainPatch::GetEastPatch)
        .addFunction("GetCoordinates", &TerrainPatch::GetCoordinates)
        .addFunction("GetLodLevel", &TerrainPatch::GetLodLevel)

        .addProperty("geometry", &TerrainPatch::GetGeometry)
        .addProperty("maxLodGeometry", &TerrainPatch::GetMaxLodGeometry)
        .addProperty("occlusionGeometry", &TerrainPatch::GetOcclusionGeometry)
        .addProperty("owner", &TerrainPatch::GetOwner, &TerrainPatch::SetOwner)
        .addProperty("northPatch", &TerrainPatch::GetNorthPatch)
        .addProperty("southPatch", &TerrainPatch::GetSouthPatch)
        .addProperty("westPatch", &TerrainPatch::GetWestPatch)
        .addProperty("eastPatch", &TerrainPatch::GetEastPatch)
        .addProperty("coordinates", &TerrainPatch::GetCoordinates, &TerrainPatch::SetCoordinates)
        .addProperty("lodLevel", &TerrainPatch::GetLodLevel)
        .addProperty("boundingBox", &TerrainPatch::SetBoundingBox)
        );
}
}

