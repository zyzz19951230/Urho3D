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

#ifdef URHO3D_NETWORK

#include "../../Precompiled.h"

#include "../../Network/NetworkPriority.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterNetworkPriority(kaguya::State& lua)
{
    using namespace kaguya;
    
    lua["NetworkPriority"].setClass(UserdataMetatable<NetworkPriority, Component>()
        .addStaticFunction("new", &CreateObject<NetworkPriority>)

        .addFunction("SetBasePriority", &NetworkPriority::SetBasePriority)
        .addFunction("SetDistanceFactor", &NetworkPriority::SetDistanceFactor)
        .addFunction("SetMinPriority", &NetworkPriority::SetMinPriority)
        .addFunction("SetAlwaysUpdateOwner", &NetworkPriority::SetAlwaysUpdateOwner)
        
        .addFunction("GetBasePriority", &NetworkPriority::GetBasePriority)
        .addFunction("GetDistanceFactor", &NetworkPriority::GetDistanceFactor)
        .addFunction("GetMinPriority", &NetworkPriority::GetMinPriority)
        .addFunction("GetAlwaysUpdateOwner", &NetworkPriority::GetAlwaysUpdateOwner)
        
        .addFunction("CheckUpdate", &NetworkPriority::CheckUpdate)

        .addProperty("basePriority", &NetworkPriority::GetBasePriority, &NetworkPriority::SetBasePriority)
        .addProperty("distanceFactor", &NetworkPriority::GetDistanceFactor, &NetworkPriority::SetDistanceFactor)
        .addProperty("minPriority", &NetworkPriority::GetMinPriority, &NetworkPriority::SetMinPriority)
        .addProperty("alwaysUpdateOwner", &NetworkPriority::GetAlwaysUpdateOwner, &NetworkPriority::SetAlwaysUpdateOwner)
        );
}
}

#endif
