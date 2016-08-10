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

#include "../../Scene/Node.h"
#include "../../Urho2D/TileMap2D.h"
#include "../../Urho2D/TileMapLayer2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterTileMapLayer2D(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] TileMapLayer2D : Component
    lua["TileMapLayer2D"].setClass(UserdataMetatable<TileMapLayer2D, Component>()
        // [Constructor] TileMapLayer2D()
        .addStaticFunction("new", &CreateObject<TileMapLayer2D>)

        // [Method] void SetDrawOrder(int drawOrder)
        .addFunction("SetDrawOrder", &TileMapLayer2D::SetDrawOrder)
        // [Method] void SetVisible(bool visible)
        .addFunction("SetVisible", &TileMapLayer2D::SetVisible)

        // [Method] TileMap2D* GetTileMap() const
        .addFunction("GetTileMap", &TileMapLayer2D::GetTileMap)
        // [Method] int GetDrawOrder() const
        .addFunction("GetDrawOrder", &TileMapLayer2D::GetDrawOrder)
        // [Method] bool IsVisible() const
        .addFunction("IsVisible", &TileMapLayer2D::IsVisible)
        // [Method] bool HasProperty(const String& name) const
        .addFunction("HasProperty", &TileMapLayer2D::HasProperty)
        // [Method] const String& GetProperty(const String& name) const
        .addFunction("GetProperty", &TileMapLayer2D::GetProperty)
        // [Method] TileMapLayerType2D GetLayerType() const
        .addFunction("GetLayerType", &TileMapLayer2D::GetLayerType)
        // [Method] int GetWidth() const
        .addFunction("GetWidth", &TileMapLayer2D::GetWidth)
        // [Method] int GetHeight() const
        .addFunction("GetHeight", &TileMapLayer2D::GetHeight)
        // [Method] Node* GetTileNode(int x, int y) const
        .addFunction("GetTileNode", &TileMapLayer2D::GetTileNode)
        // [Method] Tile2D* GetTile(int x, int y) const
        .addFunction("GetTile", &TileMapLayer2D::GetTile)
        // [Method] unsigned GetNumObjects() const
        .addFunction("GetNumObjects", &TileMapLayer2D::GetNumObjects)
        // [Method] TileMapObject2D* GetObject(unsigned index) const
        .addFunction("GetObject", &TileMapLayer2D::GetObject)
        // [Method] Node* GetObjectNode(unsigned index) const
        .addFunction("GetObjectNode", &TileMapLayer2D::GetObjectNode)
        // [Method] Node* GetImageNode() const
        .addFunction("GetImageNode", &TileMapLayer2D::GetImageNode)

        // [Property(Readonly)] TileMap2D* tileMap
        .addProperty("tileMap", &TileMapLayer2D::GetTileMap)
        // [Property] int drawOrder
        .addProperty("drawOrder", &TileMapLayer2D::GetDrawOrder, &TileMapLayer2D::SetDrawOrder)
        // [Property] bool visible
        .addProperty("visible", &TileMapLayer2D::IsVisible, &TileMapLayer2D::SetVisible)
        // [Property(Readonly)] TileMapLayerType2D layerType
        .addProperty("layerType", &TileMapLayer2D::GetLayerType)
        // [Property(Readonly)] int width
        .addProperty("width", &TileMapLayer2D::GetWidth)
        // [Property(Readonly)] int height
        .addProperty("height", &TileMapLayer2D::GetHeight)
        // [Property(Readonly)] unsigned numObjects
        .addProperty("numObjects", &TileMapLayer2D::GetNumObjects)
        // [Property(Readonly)] Node* imageNode
        .addProperty("imageNode", &TileMapLayer2D::GetImageNode)
    );
}
}

#endif
