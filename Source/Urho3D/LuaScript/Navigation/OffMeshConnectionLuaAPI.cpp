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

    lua["OffMeshConnection"].setClass(UserdataMetatable<OffMeshConnection, Component>()
        .addStaticFunction("new", &CreateObject<OffMeshConnection>)

        .addFunction("SetEndPoint", &OffMeshConnection::SetEndPoint)
        .addFunction("SetRadius", &OffMeshConnection::SetRadius)
        .addFunction("SetBidirectional", &OffMeshConnection::SetBidirectional)
        .addFunction("SetMask", &OffMeshConnection::SetMask)
        .addFunction("SetAreaID", &OffMeshConnection::SetAreaID)
        
        .addFunction("GetEndPoint", &OffMeshConnection::GetEndPoint)
        .addFunction("GetRadius", &OffMeshConnection::GetRadius)
        .addFunction("IsBidirectional", &OffMeshConnection::IsBidirectional)
        .addFunction("GetMask", &OffMeshConnection::GetMask)
        .addFunction("GetAreaID", &OffMeshConnection::GetAreaID)

        .addProperty("endPoint", &OffMeshConnection::GetEndPoint, &OffMeshConnection::SetEndPoint)
        .addProperty("radius", &OffMeshConnection::GetRadius, &OffMeshConnection::SetRadius)
        .addProperty("bidirectional", &OffMeshConnection::IsBidirectional, &OffMeshConnection::SetBidirectional)
        .addProperty("mask", &OffMeshConnection::GetMask, &OffMeshConnection::SetMask)
        .addProperty("areaID", &OffMeshConnection::GetAreaID, &OffMeshConnection::SetAreaID)
        );
}
}

#endif
