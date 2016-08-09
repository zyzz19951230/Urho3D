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

    // [Class] TerrainPatch : Drawable
    lua["TerrainPatch"].setClass(UserdataMetatable<TerrainPatch, Drawable>()
        // [Constructor] TerrainPatch()
        .addStaticFunction("new", &CreateObject<TerrainPatch>)

        // [Method] void SetOwner(Terrain* terrain)
        .addFunction("SetOwner", &TerrainPatch::SetOwner)
        // [Method] void SetNeighbors(TerrainPatch* north, TerrainPatch* south, TerrainPatch* west, TerrainPatch* east)
        .addFunction("SetNeighbors", &TerrainPatch::SetNeighbors)
        // [Method] void SetMaterial(Material* material)
        .addFunction("SetMaterial", &TerrainPatch::SetMaterial)
        // [Method] void SetBoundingBox(const BoundingBox& box)
        .addFunction("SetBoundingBox", &TerrainPatch::SetBoundingBox)
        // [Method] void SetCoordinates(const IntVector2& coordinates)
        .addFunction("SetCoordinates", &TerrainPatch::SetCoordinates)
        
        // [Method] void ResetLod()
        .addFunction("ResetLod", &TerrainPatch::ResetLod)
        
        // [Method] Geometry* GetGeometry() const
        .addFunction("GetGeometry", &TerrainPatch::GetGeometry)
        // [Method] Geometry* GetMaxLodGeometry() const
        .addFunction("GetMaxLodGeometry", &TerrainPatch::GetMaxLodGeometry)
        // [Method] Geometry* GetOcclusionGeometry() const
        .addFunction("GetOcclusionGeometry", &TerrainPatch::GetOcclusionGeometry)        
        // [Method] VertexBuffer* GetVertexBuffer() const
        .addFunction("GetVertexBuffer", &TerrainPatch::GetVertexBuffer)
        // [Method] Terrain* GetOwner() const
        .addFunction("GetOwner", &TerrainPatch::GetOwner)
        // [Method] TerrainPatch* GetNorthPatch() const
        .addFunction("GetNorthPatch", &TerrainPatch::GetNorthPatch)
        // [Method] TerrainPatch* GetSouthPatch() const
        .addFunction("GetSouthPatch", &TerrainPatch::GetSouthPatch)
        // [Method] TerrainPatch* GetWestPatch() const
        .addFunction("GetWestPatch", &TerrainPatch::GetWestPatch)
        // [Method] TerrainPatch* GetEastPatch() const
        .addFunction("GetEastPatch", &TerrainPatch::GetEastPatch)
        // [Method] const IntVector2& GetCoordinates() const
        .addFunction("GetCoordinates", &TerrainPatch::GetCoordinates)
        // [Method] unsigned GetLodLevel() const
        .addFunction("GetLodLevel", &TerrainPatch::GetLodLevel)

        // [Property(ReadOnly)] Geometry* geometry
        .addProperty("geometry", &TerrainPatch::GetGeometry)
        // [Property(ReadOnly)] Geometry* maxLodGeometry
        .addProperty("maxLodGeometry", &TerrainPatch::GetMaxLodGeometry)
        // [Property(ReadOnly)] Geometry* occlusionGeometry
        .addProperty("occlusionGeometry", &TerrainPatch::GetOcclusionGeometry)
        // [Property] Terrain* owner
        .addProperty("owner", &TerrainPatch::GetOwner, &TerrainPatch::SetOwner)
        // [Property(ReadOnly)] TerrainPatch* northPatch
        .addProperty("northPatch", &TerrainPatch::GetNorthPatch)
        // [Property(ReadOnly)] TerrainPatch* southPatch
        .addProperty("southPatch", &TerrainPatch::GetSouthPatch)
        // [Property(ReadOnly)] TerrainPatch* westPatch
        .addProperty("westPatch", &TerrainPatch::GetWestPatch)
        // [Property(ReadOnly)] TerrainPatch* eastPatch
        .addProperty("eastPatch", &TerrainPatch::GetEastPatch)
        // [Property] const IntVector2& coordinates
        .addProperty("coordinates", &TerrainPatch::GetCoordinates, &TerrainPatch::SetCoordinates)
        // [Property(ReadOnly)] unsigned lodLevel
        .addProperty("lodLevel", &TerrainPatch::GetLodLevel)
        // [Property(WriteOnly)] void boundingBox
        .addProperty("boundingBox", &TerrainPatch::SetBoundingBox)
        );
}
}

