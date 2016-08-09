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

    // [Enum] Orientation2D
    // [Variable] O_ORTHOGONAL
    lua["O_ORTHOGONAL"] = O_ORTHOGONAL;
    // [Variable] O_ISOMETRIC,
    lua["O_ISOMETRIC"] = O_ISOMETRIC;
    // [Variable] O_STAGGERED,
    lua["O_STAGGERED"] = O_STAGGERED;
    // [Variable] O_HEXAGONAL
    lua["O_HEXAGONAL"] = O_HEXAGONAL;

    // [Class] TileMapInfo2D
    lua["TileMapInfo2D"].setClass(UserdataMetatable<TileMapInfo2D>()

        // [Method] float GetMapWidth() const
        .addFunction("GetMapWidth", &TileMapInfo2D::GetMapWidth)
        // [Method] float GetMapHeight() const
        .addFunction("GetMapHeight", &TileMapInfo2D::GetMapHeight)
        // [Method] Vector2 ConvertPosition(const Vector2& position) const
        .addFunction("ConvertPosition", &TileMapInfo2D::ConvertPosition)
        // [Method] Vector2 TileIndexToPosition(int x, int y) const
        .addFunction("TileIndexToPosition", &TileMapInfo2D::TileIndexToPosition)
        // [Method] bool PositionToTileIndex(int& x, int& y, const Vector2& positon) const
        .addFunction("PositionToTileIndex", &TileMapInfo2D::PositionToTileIndex)

        // [Property(ReadOnly)] float mapWidth
        .addProperty("mapWidth", &TileMapInfo2D::GetMapWidth)
        // [Property(ReadOnly)] float mapHeight
        .addProperty("mapHeight", &TileMapInfo2D::GetMapHeight)

        .addProperty("orientation", &TileMapInfo2D::orientation_)
        .addProperty("width", &TileMapInfo2D::width_)
        .addProperty("height", &TileMapInfo2D::height_)
        .addProperty("tileWidth", &TileMapInfo2D::tileWidth_)
        .addProperty("tileHeight", &TileMapInfo2D::tileHeight_)
    );

    // [Enum] TileMapLayerType2D
    // [Variable] LT_TILE_LAYER
    lua["LT_TILE_LAYER"] = LT_TILE_LAYER;
    // [Variable] LT_OBJECT_GROUP,
    lua["LT_OBJECT_GROUP"] = LT_OBJECT_GROUP;
    // [Variable] LT_IMAGE_LAYER,
    lua["LT_IMAGE_LAYER"] = LT_IMAGE_LAYER;
    // [Variable] LT_INVALID
    lua["LT_INVALID"] = LT_INVALID;

    // [Enum] TileMapObjectType2D
    // [Variable] OT_RECTANGLE
    lua["OT_RECTANGLE"] = OT_RECTANGLE;
    // [Variable] OT_ELLIPSE,
    lua["OT_ELLIPSE"] = OT_ELLIPSE;
    // [Variable] OT_POLYGON,
    lua["OT_POLYGON"] = OT_POLYGON;
    // [Variable] OT_POLYLINE,
    lua["OT_POLYLINE"] = OT_POLYLINE;
    // [Variable] OT_TILE,
    lua["OT_TILE"] = OT_TILE;
    // [Variable] OT_INVALID
    lua["OT_INVALID"] = OT_INVALID;

    // [Class] PropertySet2D : RefCounted
    lua["PropertySet2D"].setClass(UserdataMetatable<PropertySet2D, RefCounted>()
        .setConstructors<PropertySet2D()>()
        // [Method] bool HasProperty(const String& name) const
        .addFunction("HasProperty", &PropertySet2D::HasProperty)
        // [Method] const String& GetProperty(const String& name) const
        .addFunction("GetProperty", &PropertySet2D::GetProperty)
    );

    // [Class] Tile2D : RefCounted
    lua["Tile2D"].setClass(UserdataMetatable<Tile2D, RefCounted>()
        .setConstructors<Tile2D()>()

        // [Method] int GetGid() const
        .addFunction("GetGid", &Tile2D::GetGid)
        // [Method] Sprite2D* GetSprite() const
        .addFunction("GetSprite", &Tile2D::GetSprite)
        // [Method] bool HasProperty(const String& name) const
        .addFunction("HasProperty", &Tile2D::HasProperty)
        // [Method] const String& GetProperty(const String& name) const
        .addFunction("GetProperty", &Tile2D::GetProperty)

        // [Property(ReadOnly)] int gid
        .addProperty("gid", &Tile2D::GetGid)
        // [Property(ReadOnly)] Sprite2D* sprite
        .addProperty("sprite", &Tile2D::GetSprite)
    );

    // [Class] TileMapObject2D : RefCounted
    lua["TileMapObject2D"].setClass(UserdataMetatable<TileMapObject2D, RefCounted>()
        .setConstructors<TileMapObject2D()>()

        // [Method] TileMapObjectType2D GetObjectType() const
        .addFunction("GetObjectType", &TileMapObject2D::GetObjectType)
        // [Method] const String& GetName() const
        .addFunction("GetName", &TileMapObject2D::GetName)
        // [Method] const String& GetType() const
        .addFunction("GetType", &TileMapObject2D::GetType)
        // [Method] const Vector2& GetPosition() const
        .addFunction("GetPosition", &TileMapObject2D::GetPosition)
        // [Method] const Vector2& GetSize() const
        .addFunction("GetSize", &TileMapObject2D::GetSize)
        // [Method] unsigned GetNumPoints() const
        .addFunction("GetNumPoints", &TileMapObject2D::GetNumPoints)
        // [Method] const Vector2& GetPoint(unsigned index) const
        .addFunction("GetPoint", &TileMapObject2D::GetPoint)
        // [Method] int GetTileGid() const
        .addFunction("GetTileGid", &TileMapObject2D::GetTileGid)
        // [Method] Sprite2D* GetTileSprite() const
        .addFunction("GetTileSprite", &TileMapObject2D::GetTileSprite)
        // [Method] bool HasProperty(const String& name) const
        .addFunction("HasProperty", &TileMapObject2D::HasProperty)
        // [Method] const String& GetProperty(const String& name) const
        .addFunction("GetProperty", &TileMapObject2D::GetProperty)

        // [Property(ReadOnly)] TileMapObjectType2D objectType
        .addProperty("objectType", &TileMapObject2D::GetObjectType)
        // [Property(ReadOnly)] const String& name
        .addProperty("name", &TileMapObject2D::GetName)
        // [Property(ReadOnly)] const String& type
        .addProperty("type", &TileMapObject2D::GetType)
        // [Property(ReadOnly)] const Vector2& position
        .addProperty("position", &TileMapObject2D::GetPosition)
        // [Property(ReadOnly)] const Vector2& size
        .addProperty("size", &TileMapObject2D::GetSize)
        // [Property(ReadOnly)] unsigned numPoints
        .addProperty("numPoints", &TileMapObject2D::GetNumPoints)
        // [Property(ReadOnly)] int tileGid
        .addProperty("tileGid", &TileMapObject2D::GetTileGid)
        // [Property(ReadOnly)] Sprite2D* tileSprite
        .addProperty("tileSprite", &TileMapObject2D::GetTileSprite)
    );
}
}

#endif
