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

    lua["TileMapLayer2D"].setClass(UserdataMetatable<TileMapLayer2D, Component>()
        .addStaticFunction("new", &CreateObject<TileMapLayer2D>)

        .addFunction("SetDrawOrder", &TileMapLayer2D::SetDrawOrder)
        .addFunction("SetVisible", &TileMapLayer2D::SetVisible)

        .addFunction("GetTileMap", &TileMapLayer2D::GetTileMap)
        .addFunction("GetDrawOrder", &TileMapLayer2D::GetDrawOrder)
        .addFunction("IsVisible", &TileMapLayer2D::IsVisible)
        .addFunction("HasProperty", &TileMapLayer2D::HasProperty)
        .addFunction("GetProperty", &TileMapLayer2D::GetProperty)
        .addFunction("GetLayerType", &TileMapLayer2D::GetLayerType)
        .addFunction("GetWidth", &TileMapLayer2D::GetWidth)
        .addFunction("GetHeight", &TileMapLayer2D::GetHeight)
        .addFunction("GetTileNode", &TileMapLayer2D::GetTileNode)
        .addFunction("GetTile", &TileMapLayer2D::GetTile)
        .addFunction("GetNumObjects", &TileMapLayer2D::GetNumObjects)
        .addFunction("GetObject", &TileMapLayer2D::GetObject)
        .addFunction("GetObjectNode", &TileMapLayer2D::GetObjectNode)
        .addFunction("GetImageNode", &TileMapLayer2D::GetImageNode)

        .addProperty("tileMap", &TileMapLayer2D::GetTileMap)
        .addProperty("drawOrder", &TileMapLayer2D::GetDrawOrder, &TileMapLayer2D::SetDrawOrder)
        .addProperty("visible", &TileMapLayer2D::IsVisible, &TileMapLayer2D::SetVisible)
        .addProperty("layerType", &TileMapLayer2D::GetLayerType)
        .addProperty("width", &TileMapLayer2D::GetWidth)
        .addProperty("height", &TileMapLayer2D::GetHeight)
        .addProperty("numObjects", &TileMapLayer2D::GetNumObjects)
        .addProperty("imageNode", &TileMapLayer2D::GetImageNode)
    );
}
}

#endif
