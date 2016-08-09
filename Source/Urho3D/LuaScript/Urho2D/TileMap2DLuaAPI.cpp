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

#ifdef URHO3D_URHO2D

#include "../../Precompiled.h"

#include "../../Urho2D/TileMap2D.h"
#include "../../Urho2D/TileMapLayer2D.h"
#include "../../Urho2D/TmxFile2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static kaguya::standard::tuple<bool, int, int> TileMap2DPositionToTileIndex(const TileMap2D* self, const Vector2& position)
{
    int x;
    int y;
    bool result = self->PositionToTileIndex(x, y, position);
    return kaguya::standard::make_tuple(result, x, y);
}

void RegisterTileMap2D(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] TileMap2D : Component
    lua["TileMap2D"].setClass(UserdataMetatable<TileMap2D, Component>()
        .addStaticFunction("new", &CreateObject<TileMap2D>)

        // [Method] void DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
        .addFunction("DrawDebugGeometry", static_cast<void(TileMap2D::*)()>(&TileMap2D::DrawDebugGeometry))
        // [Method] void SetTmxFile(TmxFile2D* tmxFile)
        .addFunction("SetTmxFile", &TileMap2D::SetTmxFile)        

        // [Method] TmxFile2D* GetTmxFile() const
        .addFunction("GetTmxFile", &TileMap2D::GetTmxFile)
        // [Method] const TileMapInfo2D& GetInfo() const
        .addFunction("GetInfo", &TileMap2D::GetInfo)
        // [Method] unsigned GetNumLayers() const
        .addFunction("GetNumLayers", &TileMap2D::GetNumLayers)
        // [Method] TileMapLayer2D* GetLayer(unsigned index) const
        .addFunction("GetLayer", &TileMap2D::GetLayer)
        // [Method] Vector2 TileIndexToPosition(int x, int y) const
        .addFunction("TileIndexToPosition", &TileMap2D::TileIndexToPosition)

        .addStaticFunction("PositionToTileIndex", &TileMap2DPositionToTileIndex)
        
        // [Property] TmxFile2D* tmxFile
        .addProperty("tmxFile", &TileMap2D::GetTmxFile, &TileMap2D::SetTmxFile)
        // [Property(ReadOnly)] const TileMapInfo2D& info
        .addProperty("info", &TileMap2D::GetInfo)
        // [Property(ReadOnly)] unsigned numLayers
        .addProperty("numLayers", &TileMap2D::GetNumLayers)
    );
}
}

#endif
