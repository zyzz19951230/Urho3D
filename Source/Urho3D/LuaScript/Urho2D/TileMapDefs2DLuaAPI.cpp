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

#include "../../Urho2D/TileMapDefs2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterTileMapDefs2D(kaguya::State& lua)
{
    using namespace kaguya;

    // enum Orientation2D;
    lua["O_ORTHOGONAL"] = O_ORTHOGONAL;
    lua["O_ISOMETRIC"] = O_ISOMETRIC;
    lua["O_STAGGERED"] = O_STAGGERED;
    lua["O_HEXAGONAL"] = O_HEXAGONAL;

    lua["TileMapInfo2D"].setClass(UserdataMetatable<TileMapInfo2D>()

        .addFunction("GetMapWidth", &TileMapInfo2D::GetMapWidth)
        .addFunction("GetMapHeight", &TileMapInfo2D::GetMapHeight)
        .addFunction("ConvertPosition", &TileMapInfo2D::ConvertPosition)
        .addFunction("TileIndexToPosition", &TileMapInfo2D::TileIndexToPosition)
        .addFunction("PositionToTileIndex", &TileMapInfo2D::PositionToTileIndex)

        .addProperty("mapWidth", &TileMapInfo2D::GetMapWidth)
        .addProperty("mapHeight", &TileMapInfo2D::GetMapHeight)

        .addProperty("orientation", &TileMapInfo2D::orientation_)
        .addProperty("width", &TileMapInfo2D::width_)
        .addProperty("height", &TileMapInfo2D::height_)
        .addProperty("tileWidth", &TileMapInfo2D::tileWidth_)
        .addProperty("tileHeight", &TileMapInfo2D::tileHeight_)
    );

    // enum TileMapLayerType2D;
    lua["LT_TILE_LAYER"] = LT_TILE_LAYER;
    lua["LT_OBJECT_GROUP"] = LT_OBJECT_GROUP;
    lua["LT_IMAGE_LAYER"] = LT_IMAGE_LAYER;
    lua["LT_INVALID"] = LT_INVALID;

    // enum TileMapObjectType2D;
    lua["OT_RECTANGLE"] = OT_RECTANGLE;
    lua["OT_ELLIPSE"] = OT_ELLIPSE;
    lua["OT_POLYGON"] = OT_POLYGON;
    lua["OT_POLYLINE"] = OT_POLYLINE;
    lua["OT_TILE"] = OT_TILE;
    lua["OT_INVALID"] = OT_INVALID;

    lua["PropertySet2D"].setClass(UserdataMetatable<PropertySet2D, RefCounted>()
        .setConstructors<PropertySet2D()>()
        .addFunction("HasProperty", &PropertySet2D::HasProperty)
        .addFunction("GetProperty", &PropertySet2D::GetProperty)
    );

    lua["Tile2D"].setClass(UserdataMetatable<Tile2D, RefCounted>()
        .setConstructors<Tile2D()>()

        .addFunction("GetGid", &Tile2D::GetGid)
        .addFunction("GetSprite", &Tile2D::GetSprite)
        .addFunction("HasProperty", &Tile2D::HasProperty)
        .addFunction("GetProperty", &Tile2D::GetProperty)

        .addProperty("gid", &Tile2D::GetGid)
        .addProperty("sprite", &Tile2D::GetSprite)
    );

    lua["TileMapObject2D"].setClass(UserdataMetatable<TileMapObject2D, RefCounted>()
        .setConstructors<TileMapObject2D()>()

        .addFunction("GetObjectType", &TileMapObject2D::GetObjectType)
        .addFunction("GetName", &TileMapObject2D::GetName)
        .addFunction("GetType", &TileMapObject2D::GetType)
        .addFunction("GetPosition", &TileMapObject2D::GetPosition)
        .addFunction("GetSize", &TileMapObject2D::GetSize)
        .addFunction("GetNumPoints", &TileMapObject2D::GetNumPoints)
        .addFunction("GetPoint", &TileMapObject2D::GetPoint)
        .addFunction("GetTileGid", &TileMapObject2D::GetTileGid)
        .addFunction("GetTileSprite", &TileMapObject2D::GetTileSprite)
        .addFunction("HasProperty", &TileMapObject2D::HasProperty)
        .addFunction("GetProperty", &TileMapObject2D::GetProperty)

        .addProperty("objectType", &TileMapObject2D::GetObjectType)
        .addProperty("name", &TileMapObject2D::GetName)
        .addProperty("type", &TileMapObject2D::GetType)
        .addProperty("position", &TileMapObject2D::GetPosition)
        .addProperty("size", &TileMapObject2D::GetSize)
        .addProperty("numPoints", &TileMapObject2D::GetNumPoints)
        .addProperty("tileGid", &TileMapObject2D::GetTileGid)
        .addProperty("tileSprite", &TileMapObject2D::GetTileSprite)
    );
}
}

#endif
