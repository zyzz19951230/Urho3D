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

    // [Class] Component : Animatable
    lua["Component"].setClass(UserdataMetatable<Component, Animatable>()
        // [Constructor] Component()
        .addStaticFunction("new", &CreateObject<Component>)

        // [Method] void SetEnabled(bool enable)
        .addFunction("SetEnabled", &Component::SetEnabled)
        // [Method] void Remove()
        .addFunction("Remove", &Component::Remove)
        // [Method] unsigned GetID() const
        .addFunction("GetID", &Component::GetID)
        // [Method] Node* GetNode() const
        .addFunction("GetNode", &Component::GetNode)
        // [Method] Scene* GetScene() const
        .addFunction("GetScene", &Component::GetScene)
        // [Method] bool IsEnabled() const
        .addFunction("IsEnabled", &Component::IsEnabled)
        // [Method] bool IsEnabledEffective() const
        .addFunction("IsEnabledEffective", &Component::IsEnabledEffective)

        // [Method] SharedPtr<Component> GetComponent(StringHash type) const
        .addStaticFunction("GetComponent", &ComponentGetComponent)
        // [Method] PODVector<Component*> GetComponents() const
        .addStaticFunction("GetComponents", &ComponentGetComponents)

        // [Method] void AddReplicationState(ComponentReplicationState* state)
        .addFunction("AddReplicationState", &Component::AddReplicationState)
        // [Method] void PrepareNetworkUpdate()
        .addFunction("PrepareNetworkUpdate", &Component::PrepareNetworkUpdate)
        // .addFunction("CleanupConnection", &Component::CleanupConnection)

        // [Property(ReadOnly)] unsigned id
        .addProperty("id", &Component::GetID)
        // [Property(ReadOnly)] Node* node
        .addProperty("node", &Component::GetNode)
        // [Property(ReadOnly)] Scene* scene
        .addProperty("scene", &Component::GetScene)
        // [Property] bool enabled
        .addProperty("enabled", &Component::IsEnabled, &Component::SetEnabled)
        // [Property(ReadOnly)] bool enabledEffective
        .addProperty("enabledEffective", &Component::IsEnabledEffective)
        );
}
}

