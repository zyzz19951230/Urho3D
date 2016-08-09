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

#ifdef URHO3D_NAVIGATION

#include "../../Precompiled.h"

#include "../../Navigation/OffMeshConnection.h"
#include "../../Scene/Node.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <Detour/DetourNavMeshQuery.h>
#include <kaguya.hpp>

namespace Urho3D
{

void RegisterOffMeshConnection(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] OffMeshConnection : Component
    lua["OffMeshConnection"].setClass(UserdataMetatable<OffMeshConnection, Component>()
        .addStaticFunction("new", &CreateObject<OffMeshConnection>)

        // [Method] void SetEndPoint(Node* node)
        .addFunction("SetEndPoint", &OffMeshConnection::SetEndPoint)
        // [Method] void SetRadius(float radius)
        .addFunction("SetRadius", &OffMeshConnection::SetRadius)
        // [Method] void SetBidirectional(bool enabled)
        .addFunction("SetBidirectional", &OffMeshConnection::SetBidirectional)
        // [Method] void SetMask(unsigned newMask)
        .addFunction("SetMask", &OffMeshConnection::SetMask)
        // [Method] void SetAreaID(unsigned newAreaID)
        .addFunction("SetAreaID", &OffMeshConnection::SetAreaID)
        
        // [Method] Node* GetEndPoint() const
        .addFunction("GetEndPoint", &OffMeshConnection::GetEndPoint)
        // [Method] float GetRadius() const
        .addFunction("GetRadius", &OffMeshConnection::GetRadius)
        // [Method] bool IsBidirectional() const
        .addFunction("IsBidirectional", &OffMeshConnection::IsBidirectional)
        // [Method] unsigned GetMask() const
        .addFunction("GetMask", &OffMeshConnection::GetMask)
        // [Method] unsigned GetAreaID() const
        .addFunction("GetAreaID", &OffMeshConnection::GetAreaID)

        // [Property] Node* endPoint
        .addProperty("endPoint", &OffMeshConnection::GetEndPoint, &OffMeshConnection::SetEndPoint)
        // [Property] float radius
        .addProperty("radius", &OffMeshConnection::GetRadius, &OffMeshConnection::SetRadius)
        // [Property] bool bidirectional
        .addProperty("bidirectional", &OffMeshConnection::IsBidirectional, &OffMeshConnection::SetBidirectional)
        // [Property] unsigned mask
        .addProperty("mask", &OffMeshConnection::GetMask, &OffMeshConnection::SetMask)
        // [Property] unsigned areaID
        .addProperty("areaID", &OffMeshConnection::GetAreaID, &OffMeshConnection::SetAreaID)
        );
}
}

#endif
