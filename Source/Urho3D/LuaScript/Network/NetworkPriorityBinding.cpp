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
    
    // [Class] NetworkPriority : Component
    lua["NetworkPriority"].setClass(UserdataMetatable<NetworkPriority, Component>()
        // [Constructor] NetworkPriority()
        .addStaticFunction("new", &CreateObject<NetworkPriority>)

        // [Method] void SetBasePriority(float priority)
        .addFunction("SetBasePriority", &NetworkPriority::SetBasePriority)
        // [Method] void SetDistanceFactor(float factor)
        .addFunction("SetDistanceFactor", &NetworkPriority::SetDistanceFactor)
        // [Method] void SetMinPriority(float priority)
        .addFunction("SetMinPriority", &NetworkPriority::SetMinPriority)
        // [Method] void SetAlwaysUpdateOwner(bool enable)
        .addFunction("SetAlwaysUpdateOwner", &NetworkPriority::SetAlwaysUpdateOwner)
        
        // [Method] float GetBasePriority() const
        .addFunction("GetBasePriority", &NetworkPriority::GetBasePriority)
        // [Method] float GetDistanceFactor() const
        .addFunction("GetDistanceFactor", &NetworkPriority::GetDistanceFactor)
        // [Method] float GetMinPriority() const
        .addFunction("GetMinPriority", &NetworkPriority::GetMinPriority)
        // [Method] bool GetAlwaysUpdateOwner() const
        .addFunction("GetAlwaysUpdateOwner", &NetworkPriority::GetAlwaysUpdateOwner)
        
        // [Method] bool CheckUpdate(float distance, float& accumulator)
        .addFunction("CheckUpdate", &NetworkPriority::CheckUpdate)

        // [Property] float basePriority
        .addProperty("basePriority", &NetworkPriority::GetBasePriority, &NetworkPriority::SetBasePriority)
        // [Property] float distanceFactor
        .addProperty("distanceFactor", &NetworkPriority::GetDistanceFactor, &NetworkPriority::SetDistanceFactor)
        // [Property] float minPriority
        .addProperty("minPriority", &NetworkPriority::GetMinPriority, &NetworkPriority::SetMinPriority)
        // [Property] bool alwaysUpdateOwner
        .addProperty("alwaysUpdateOwner", &NetworkPriority::GetAlwaysUpdateOwner, &NetworkPriority::SetAlwaysUpdateOwner)
        );
}
}

#endif
