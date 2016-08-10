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

#include "../../Urho2D/CollisionChain2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterCollisionChain2D(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] CollisionChain2D : CollisionShape2D
    lua["CollisionChain2D"].setClass(UserdataMetatable<CollisionChain2D, CollisionShape2D>()
        // [Constructor] CollisionChain2D()
        .addStaticFunction("new", &CreateObject<CollisionChain2D>)

        // [Method] void SetLoop(bool loop)
        .addFunction("SetLoop", &CollisionChain2D::SetLoop)
        // [Method] void SetVertexCount(unsigned count)
        .addFunction("SetVertexCount", &CollisionChain2D::SetVertexCount)
        // [Method] void SetVertex(unsigned index, const Vector2& vertex)
        .addFunction("SetVertex", &CollisionChain2D::SetVertex)
        // [Method] void SetVertices(const PODVector<Vector2>& vertices)
        .addFunction("SetVertices", &CollisionChain2D::SetVertices)

        // [Method] bool GetLoop() const
        .addFunction("GetLoop", &CollisionChain2D::GetLoop)
        // [Method] unsigned GetVertexCount() const
        .addFunction("GetVertexCount", &CollisionChain2D::GetVertexCount)
        // [Method] const Vector2& GetVertex(unsigned index) const
        .addFunction("GetVertex", &CollisionChain2D::GetVertex)
        // [Method] const PODVector<Vector2>& GetVertices() const
        .addFunction("GetVertices", &CollisionChain2D::GetVertices)

        // [Property] bool loop
        .addProperty("loop", &CollisionChain2D::GetLoop, &CollisionChain2D::SetLoop)
        // [Property] unsigned vertexCount
        .addProperty("vertexCount", &CollisionChain2D::GetVertexCount, &CollisionChain2D::SetVertexCount)
    );
}
}

#endif
