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
        .setConstructors<OctreeQueryResult()>()

        .addProperty("drawable", &OctreeQueryResult::drawable_)
        .addProperty("node", &OctreeQueryResult::node_)
        );

    // [Enum] RayQueryLevel
    // [Variable] RAY_AABB
    lua["RAY_AABB"] = RAY_AABB;
    // [Variable] RAY_OBB,
    lua["RAY_OBB"] = RAY_OBB;
    // [Constant] RayOctreeQuery(PODVector<RayQueryResult>& result, Ray& ray, RayQueryLevel level
    lua["RAY_TRIANGLE"] = RAY_TRIANGLE;
    // [Variable] RAY_TRIANGLE_UV
    lua["RAY_TRIANGLE_UV"] = RAY_TRIANGLE_UV;

    // [Class] RayQueryResult
    lua["RayQueryResult"].setClass(UserdataMetatable<RayQueryResult>()
        .setConstructors<RayQueryResult()>()

        .addProperty("position", &RayQueryResult::position_)
        .addProperty("normal", &RayQueryResult::normal_)
        .addProperty("textureUV", &RayQueryResult::textureUV_)
        .addProperty("distance", &RayQueryResult::distance_)
        .addProperty("drawable", &RayQueryResult::drawable_)
        .addProperty("node", &RayQueryResult::node_)
        .addProperty("subObject", &RayQueryResult::subObject_)
        );
}
}

