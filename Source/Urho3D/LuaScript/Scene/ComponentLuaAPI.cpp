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

#include "../../Scene/Component.h"
#include "../../Scene/ReplicationState.h"
#include "../../Scene/Scene.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static SharedPtr<Component> ComponentGetComponent(const Component* self, StringHash type)
{
    return SharedPtr<Component>(self->GetComponent(type));
}

static PODVector<Component*> ComponentGetComponents(const Component* self)
{
    PODVector<Component*> dest;
    self->GetComponents(dest);
    return dest;
}

void RegisterComponent(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Component"].setClass(UserdataMetatable<Component, Animatable>()
        .addStaticFunction("new", &CreateObject<Component>)

        .addFunction("SetEnabled", &Component::SetEnabled)
        .addFunction("Remove", &Component::Remove)
        .addFunction("GetID", &Component::GetID)
        .addFunction("GetNode", &Component::GetNode)
        .addFunction("GetScene", &Component::GetScene)
        .addFunction("IsEnabled", &Component::IsEnabled)
        .addFunction("IsEnabledEffective", &Component::IsEnabledEffective)

        .addStaticFunction("GetComponent", &ComponentGetComponent)
        .addStaticFunction("GetComponents", &ComponentGetComponents)

        .addFunction("AddReplicationState", &Component::AddReplicationState)
        .addFunction("PrepareNetworkUpdate", &Component::PrepareNetworkUpdate)
        // .addFunction("CleanupConnection", &Component::CleanupConnection)

        .addProperty("id", &Component::GetID)
        .addProperty("node", &Component::GetNode)
        .addProperty("scene", &Component::GetScene)
        .addProperty("enabled", &Component::IsEnabled, &Component::SetEnabled)
        .addProperty("enabledEffective", &Component::IsEnabledEffective)
        );
}
}

