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

#include "../../Urho2D/CollisionPolygon2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterCollisionPolygon2D(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] CollisionPolygon2D : CollisionShape2D
    lua["CollisionPolygon2D"].setClass(UserdataMetatable<CollisionPolygon2D, CollisionShape2D>()
        // [Constructor] CollisionPolygon2D()
        .addStaticFunction("new", &CreateObject<CollisionPolygon2D>)

        // [Method] void SetVertexCount(unsigned count)
        .addFunction("SetVertexCount", &CollisionPolygon2D::SetVertexCount)
        // [Method] void SetVertex(unsigned index, const Vector2& vertex)
        .addFunction("SetVertex", &CollisionPolygon2D::SetVertex)
        // [Method] void SetVertices(const PODVector<Vector2>& vertices)
        .addFunction("SetVertices", &CollisionPolygon2D::SetVertices)

        // [Method] unsigned GetVertexCount() const
        .addFunction("GetVertexCount", &CollisionPolygon2D::GetVertexCount)
        // [Method] const Vector2& GetVertex(unsigned index) const
        .addFunction("GetVertex", &CollisionPolygon2D::GetVertex)
        // [Method] const PODVector<Vector2>& GetVertices() const
        .addFunction("GetVertices", &CollisionPolygon2D::GetVertices)

        // [Property] unsigned vertexCount
        .addProperty("vertexCount", &CollisionPolygon2D::GetVertexCount, &CollisionPolygon2D::SetVertexCount)
    );
}
}

#endif
