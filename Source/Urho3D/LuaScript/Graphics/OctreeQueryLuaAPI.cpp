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

#include "../../Graphics/OctreeQuery.h"
#include "../../Scene/Node.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterOctreeQuery(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] OctreeQueryResult
    lua["OctreeQueryResult"].setClass(UserdataMetatable<OctreeQueryResult>()
        // [Constructor] OctreeQueryResult()
        .setConstructors<OctreeQueryResult()>()

        // [Field] Drawable* drawable
        .addProperty("drawable", &OctreeQueryResult::drawable_)
        // [Field] Node* node
        .addProperty("node", &OctreeQueryResult::node_)
        );

    // [Enum] RayQueryLevel
    lua["RAY_AABB"] = RAY_AABB;
    lua["RAY_OBB"] = RAY_OBB;
    lua["RAY_TRIANGLE"] = RAY_TRIANGLE;
    lua["RAY_TRIANGLE_UV"] = RAY_TRIANGLE_UV;

    // [Class] RayQueryResult
    lua["RayQueryResult"].setClass(UserdataMetatable<RayQueryResult>()
        // [Constructor] RayQueryResult()
        .setConstructors<RayQueryResult()>()

        // [Field] Vector3 position;
        .addProperty("position", &RayQueryResult::position_)
        // [Field] Vector3 normal;
        .addProperty("normal", &RayQueryResult::normal_)
        // [Field] Vector2 textureUV;
        .addProperty("textureUV", &RayQueryResult::textureUV_)
        // [Field] float distance;
        .addProperty("distance", &RayQueryResult::distance_)
        // [Field] Drawable* drawable;
        .addProperty("drawable", &RayQueryResult::drawable_)
        // [Field] Node* node;
        .addProperty("node", &RayQueryResult::node_)
        // [Field] unsigned subObject;
        .addProperty("subObject", &RayQueryResult::subObject_)
        );
}
}

