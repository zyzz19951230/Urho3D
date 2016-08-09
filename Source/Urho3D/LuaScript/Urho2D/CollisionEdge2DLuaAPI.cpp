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

#include "../../Urho2D/CollisionEdge2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterCollisionEdge2D(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] CollisionEdge2D : CollisionShape2D
    lua["CollisionEdge2D"].setClass(UserdataMetatable<CollisionEdge2D, CollisionShape2D>()
        .addStaticFunction("new", &CreateObject<CollisionEdge2D>)

        // [Method] void SetVertex1(const Vector2& vertex)
        .addFunction("SetVertex1", &CollisionEdge2D::SetVertex1)
        // [Method] void SetVertex2(const Vector2& vertex)
        .addFunction("SetVertex2", &CollisionEdge2D::SetVertex2)
        // [Method] void SetVertices(const Vector2& vertex1, const Vector2& vertex2)
        .addFunction("SetVertices", &CollisionEdge2D::SetVertices)

        // [Method] const Vector2& GetVertex1() const
        .addFunction("GetVertex1", &CollisionEdge2D::GetVertex1)
        // [Method] const Vector2& GetVertex2() const
        .addFunction("GetVertex2", &CollisionEdge2D::GetVertex2)

        // [Property] const Vector2& vertex1
        .addProperty("vertex1", &CollisionEdge2D::GetVertex1, &CollisionEdge2D::SetVertex1)
        // [Property] const Vector2& vertex2
        .addProperty("vertex2", &CollisionEdge2D::GetVertex2, &CollisionEdge2D::SetVertex2)
    );
}
}

#endif
