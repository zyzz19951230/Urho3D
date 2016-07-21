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

#include "../Precompiled.h"

#include "../IO/File.h"
#include "../IO/PackageFile.h"
#include "../LuaScript/LuaFile.h"
#include "../LuaScript/LuaScriptInstance.h"
#include "../LuaScript/LuaScriptUtils.h"
#include "../Resource/ResourceCache.h"
#include "../Scene/Animatable.h"
#include "../Scene/AnimationDefs.h"
#include "../Scene/Component.h"
#include "../Scene/LogicComponent.h"
#include "../Scene/Node.h"
#include "../Scene/ObjectAnimation.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"
#include "../Scene/Serializable.h"
#include "../Scene/SmoothedTransform.h"
#include "../Scene/SplinePath.h"
#include "../Scene/ValueAnimation.h"
#include "../Scene/ValueAnimationInfo.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void AnimatableSetAttributeAnimation0(Animatable* self, const String& name, ValueAnimation* attributeAnimation)
{
    self->SetAttributeAnimation(name, attributeAnimation);
}

static void AnimatableSetAttributeAnimation1(Animatable* self, const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode)
{
    self->SetAttributeAnimation(name, attributeAnimation, wrapMode);
}

static void AnimatableSetAttributeAnimation2(Animatable* self, const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed)
{
    self->SetAttributeAnimation(name, attributeAnimation, wrapMode, speed);
}

static void RegisterAnimatable(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Animatable"].setClass(UserdataMetatable<Animatable, Serializable>()

        .addFunction("SetAnimationEnabled", &Animatable::SetAnimationEnabled)
        .addFunction("SetAnimationTime", &Animatable::SetAnimationTime)
        .addFunction("SetObjectAnimation", &Animatable::SetObjectAnimation)

        ADD_OVERLOADED_FUNCTIONS_3(Animatable, SetAttributeAnimation)

        .addFunction("SetAttributeAnimationWrapMode", &Animatable::SetAttributeAnimationWrapMode)
        .addFunction("SetAttributeAnimationSpeed", &Animatable::SetAttributeAnimationSpeed)
        .addFunction("SetAttributeAnimationTime", &Animatable::SetAttributeAnimationTime)
        .addFunction("RemoveObjectAnimation", &Animatable::RemoveObjectAnimation)
        .addFunction("RemoveAttributeAnimation", &Animatable::RemoveAttributeAnimation)

        .addFunction("GetAnimationEnabled", &Animatable::GetAnimationEnabled)
        .addFunction("GetObjectAnimation", &Animatable::GetObjectAnimation)
        .addFunction("GetAttributeAnimation", &Animatable::GetAttributeAnimation)
        .addFunction("GetAttributeAnimationWrapMode", &Animatable::GetAttributeAnimationWrapMode)
        .addFunction("GetAttributeAnimationSpeed", &Animatable::GetAttributeAnimationSpeed)
        .addFunction("GetAttributeAnimationTime", &Animatable::GetAttributeAnimationTime)

        .addProperty("animationEnabled", &Animatable::GetAnimationEnabled, &Animatable::SetAnimationEnabled)
        .addProperty("objectAnimation", &Animatable::GetObjectAnimation, &Animatable::SetObjectAnimation)
        .addProperty("animationTime", &Animatable::SetAnimationTime)
        );
}

static void RegisterAnimationDefs(kaguya::State& lua)
{
    using namespace kaguya;

    // enum WrapMode;
    lua["WM_LOOP"] = WM_LOOP;
    lua["WM_ONCE"] = WM_ONCE;
    lua["WM_CLAMP"] = WM_CLAMP;
}

static SharedPtr<Component> ComponentGetComponent(const Component* self, const char* type)
{
    return SharedPtr<Component>(self->GetComponent(StringHash(type)));
}

static PODVector<Component*> ComponentGetComponents(const Component* self)
{
    PODVector<Component*> dest;
    self->GetComponents(dest);
    return dest;
}

static void RegisterComponent(kaguya::State& lua)
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
        .addFunction("CleanupConnection", &Component::CleanupConnection)

        .addProperty("id", &Component::GetID)
        .addProperty("node", &Component::GetNode)
        .addProperty("scene", &Component::GetScene)
        .addProperty("enabled", &Component::IsEnabled, &Component::SetEnabled)
        .addProperty("enabledEffective", &Component::IsEnabledEffective)
        );
}

static void RegisterLogicComponent(kaguya::State& lua)
{
    using namespace kaguya;

    lua["USE_UPDATE"] = USE_UPDATE;
    lua["USE_POSTUPDATE"] = USE_POSTUPDATE;
    lua["USE_FIXEDUPDATE"] = USE_FIXEDUPDATE;
    lua["USE_FIXEDPOSTUPDATE"] = USE_FIXEDPOSTUPDATE;

    lua["LogicComponent"].setClass(UserdataMetatable<LogicComponent, Component>()
        .addStaticFunction("new", &CreateObject<LogicComponent>)

        .addFunction("SetUpdateEventMask", &LogicComponent::SetUpdateEventMask)
        .addFunction("GetUpdateEventMask", &LogicComponent::GetUpdateEventMask)
        .addFunction("IsDelayedStartCalled", &LogicComponent::IsDelayedStartCalled)

        .addProperty("updateEventMask", &LogicComponent::GetUpdateEventMask, &LogicComponent::SetUpdateEventMask)
        .addProperty("delayedStartCalled", &LogicComponent::IsDelayedStartCalled)
        );
}

static bool NodeSaveXML0(const Node* self, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return self->SaveXML(*file);
}

static bool NodeSaveXML1(const Node* self, const char* filepath, const String& indentation)
{
    SharedPtr<File> file(new File(globalContext, filepath, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return self->SaveXML(*file, indentation);
}

static bool NodeSaveJSON0(const Node* self, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return self->SaveJSON(*file);
}

static bool NodeSaveJSON1(const Node* self, const char* filepath, const String& indentation)
{
    SharedPtr<File> file(new File(globalContext, filepath, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return self->SaveJSON(*file, indentation);
}

static void NodeAddTags0(Node* self, const String& tags)
{
    self->AddTags(tags);
}

static void NodeAddTags1(Node* self, const String& tags, char separator)
{
    self->AddTags(tags, separator);
}

static void NodeTranslate0(Node* self, const Vector3& delta)
{
    self->Translate(delta);
}

static void NodeTranslate1(Node* self, const Vector3& delta, TransformSpace space)
{
    self->Translate(delta, space);
}

static void NodeTranslate2D0(Node* self, const Vector2& delta)
{
    self->Translate2D(delta);
}

static void NodeTranslate2D1(Node* self, const Vector2& delta, TransformSpace space)
{
    self->Translate2D(delta, space);
}

static void NodeRotate0(Node* node, const Quaternion& delta)
{
    node->Rotate(delta);
}

static void NodeRotate1(Node* node, const Quaternion& delta, TransformSpace space)
{
    node->Rotate(delta, space);
}

static void NodeRotate2D0(Node* self, float delta)
{
    self->Rotate2D(delta);
}

static void NodeRotate2D1(Node* self, float delta, TransformSpace space)
{
    self->Rotate2D(delta, space);
}

static void NodeRotateAround0(Node* self, const Vector3& point, const Quaternion& delta)
{
    self->RotateAround(point, delta);
}

static void NodeRotateAround1(Node* self, const Vector3& point, const Quaternion& delta, TransformSpace space)
{
    self->RotateAround(point, delta, space);
}

static void NodeRotateAround2D0(Node* self, const Vector2& point, float delta)
{
    self->RotateAround2D(point, delta);
}

static void NodeRotateAround2D1(Node* self, const Vector2& point, float delta, TransformSpace space)
{
    self->RotateAround2D(point, delta, space);
}

static void NodePitch0(Node* self, float angle)
{
    self->Pitch(angle);
}

static void NodePitch1(Node* self, float angle, TransformSpace space)
{
    self->Pitch(angle, space);
}

static void NodeYaw0(Node* self, float angle)
{
    self->Yaw(angle);
}

static void NodeYaw1(Node* self, float angle, TransformSpace space)
{
    self->Yaw(angle, space);
}

static void NodeRoll0(Node* self, float angle)
{
    self->Roll(angle);
}

static void NodeRoll1(Node* self, float angle, TransformSpace space)
{
    self->Roll(angle, space);
}

static bool NodeLookAt0(Node* self, const Vector3& target)
{
    return self->LookAt(target);
}

static bool NodeLookAt1(Node* self, const Vector3& target, const Vector3& up)
{
    return self->LookAt(target, up);
}

static bool NodeLookAt2(Node* self, const Vector3& target, const Vector3& up, TransformSpace space)
{
    return self->LookAt(target, up, space);
}

static Node* NodeCreateChild0(Node* self)
{
    return self->CreateChild();
}

static Node* NodeCreateChild1(Node* self, const String& name)
{
    return self->CreateChild(name);
}

static Node* NodeCreateChild2(Node* self, const String& name, CreateMode mode)
{
    return self->CreateChild(name, mode);
}

static Node* NodeCreateChild3(Node* self, const String& name, CreateMode mode, unsigned id)
{
    return self->CreateChild(name, mode, id);
}

static void NodeAddChild0(Node* self, Node* node)
{
    self->AddChild(node);
}

static void NodeAddChild1(Node* self, Node* node, unsigned index)
{
    self->AddChild(node, index);
}

static SharedPtr<Component> NodeCreateComponent0(Node* self, const char* type)
{
    return SharedPtr<Component>(self->CreateComponent(StringHash(type)));
}

static SharedPtr<Component> NodeCreateComponent1(Node* self, const char* type, CreateMode mode)
{
    return SharedPtr<Component>(self->CreateComponent(StringHash(type), mode));
}

static SharedPtr<Component> NodeCreateComponent2(Node* self, const char* type, CreateMode mode, unsigned id)
{
    return SharedPtr<Component>(self->CreateComponent(StringHash(type), mode, id));
}

static SharedPtr<Component> NodeGetOrCreateComponent0(Node* self, const char* type)
{
    return SharedPtr<Component>(self->GetOrCreateComponent(StringHash(type)));
}

static SharedPtr<Component> NodeGetOrCreateComponent1(Node* self, const char* type, CreateMode mode)
{
    return SharedPtr<Component>(self->GetOrCreateComponent(StringHash(type), mode));
}

static SharedPtr<Component> NodeGetOrCreateComponent2(Node* self, const char* type, CreateMode mode, unsigned id)
{
    return SharedPtr<Component>(self->GetOrCreateComponent(StringHash(type), mode, id));
}

static kaguya::LuaTable NodeCreateScriptObject0(Node* node, const char* scriptObjectType)
{
    LuaScriptInstance* instance = node->CreateComponent<LuaScriptInstance>();
    instance->CreateObject(scriptObjectType);

    lua_rawgeti(instance->GetLuaState(), LUA_REGISTRYINDEX, instance->GetScriptObjectRef());

    return kaguya::LuaTable(instance->GetLuaState(), kaguya::StackTop());
}

static kaguya::LuaTable NodeCreateScriptObject1(Node* node, const char* fileName, const char* scriptObjectType)
{
    ResourceCache* cache = node->GetSubsystem<ResourceCache>();
    LuaFile* scriptFile = cache->GetResource<LuaFile>(fileName);
    if (!scriptFile)
        return 0;

    LuaScriptInstance* instance = node->CreateComponent<LuaScriptInstance>();
    instance->CreateObject(scriptFile, scriptObjectType);

    lua_rawgeti(instance->GetLuaState(), LUA_REGISTRYINDEX, instance->GetScriptObjectRef());
    return kaguya::LuaTable(instance->GetLuaState(), kaguya::StackTop());
}

static kaguya::LuaTable NodeGetScriptObject(Node* self)
{
    LuaScriptInstance* instance = self->GetComponent<LuaScriptInstance>();
    if (!instance)
        return 0;

    lua_rawgeti(instance->GetLuaState(), LUA_REGISTRYINDEX, instance->GetScriptObjectRef());
    return kaguya::LuaTable(instance->GetLuaState(), kaguya::StackTop());
}

static SharedPtr<Component> NodeCloneComponent0(Node* self, Component* component)
{
    return SharedPtr<Component>(self->CloneComponent(component));
}

static SharedPtr<Component> NodeCloneComponent1(Node* self, Component* component, unsigned id)
{
    return SharedPtr<Component>(self->CloneComponent(component, id));
}

static SharedPtr<Component> NodeCloneComponent2(Node* self, Component* component, CreateMode mode)
{
    return SharedPtr<Component>(self->CloneComponent(component, mode));
}

static SharedPtr<Component> NodeCloneComponent3(Node* self, Component* component, CreateMode mode, unsigned id)
{
    return SharedPtr<Component>(self->CloneComponent(component, mode, id));
}

static void NodeRemoveComponent(Node* self, const char* type)
{
    self->RemoveComponent(StringHash(type));
}

static void NodeRemoveComponents(Node* self, const char* type)
{
    self->RemoveComponents(StringHash(type));
}

static SharedPtr<Node> NodeClone0(Node* self)
{
    return SharedPtr<Node>(self->Clone());
}

static SharedPtr<Node> NodeClone1(Node* self, CreateMode mode)
{
    return SharedPtr<Node>(self->Clone(mode));
}

static unsigned NodeGetNumChildren0(const Node* self)
{
    return self->GetNumChildren();
}

static unsigned NodeGetNumChildren1(const Node* self, bool recursive)
{
    return self->GetNumChildren(recursive);
}

static PODVector<Node*> NodeGetChildren0(const Node* self)
{
    PODVector<Node*> dest;
    self->GetChildren(dest);
    return dest;
}

static PODVector<Node*> NodeGetChildren1(const Node* self, bool recursive)
{
    PODVector<Node*> dest;
    self->GetChildren(dest, recursive);
    return dest;
}

static PODVector<Node*> NodeGetChildrenWithComponent0(const Node* self, const char* type)
{
    PODVector<Node*> dest;
    self->GetChildrenWithComponent(dest, StringHash(type));
    return dest;
}

static PODVector<Node*> NodeGetChildrenWithComponent1(const Node* self, const char* type, bool recursive)
{
    PODVector<Node*> dest;
    self->GetChildrenWithComponent(dest, StringHash(type), recursive);
    return dest;
}

static PODVector<Node*> NodeGetChildrenWithTag0(const Node* self, const String& tag)
{
    PODVector<Node*> dest;
    self->GetChildrenWithTag(dest, tag);
    return dest;
}

static PODVector<Node*> NodeGetChildrenWithTag1(const Node* self, const String& tag, bool recursive)
{
    PODVector<Node*> dest;
    self->GetChildrenWithTag(dest, tag, recursive);
    return dest;
}

static Node* NodeGetChild0(const Node* self, const String& name)
{
    return self->GetChild(name);
}

static Node* NodeGetChild1(const Node* self, const String& name, bool recursive)
{
    return self->GetChild(name, recursive);
}

static PODVector<Component*> NodeGetComponents0(const Node* self, const char* type)
{
    PODVector<Component*> dest;
    self->GetComponents(dest, StringHash(type));
    return dest;
}

static PODVector<Component*> NodeGetComponents1(const Node* self, const char* type, bool recursive)
{
    PODVector<Component*> dest;
    self->GetComponents(dest, StringHash(type), recursive);
    return dest;
}

static SharedPtr<Component> NodeGetComponent0(const Node* node, const char* type)
{
    return SharedPtr<Component>(node->GetComponent(StringHash(type)));
}

static SharedPtr<Component> NodeGetComponent1(const Node* node, const char* type, bool recursive)
{
    return SharedPtr<Component>(node->GetComponent(StringHash(type), recursive));
}

static SharedPtr<Component> NodeGetParentComponent0(const Node* node, const char* type)
{
    return SharedPtr<Component>(node->GetParentComponent(StringHash(type)));
}

static SharedPtr<Component> NodeGetParentComponent1(const Node* node, const char* type, bool fullTraversal)
{
    return SharedPtr<Component>(node->GetParentComponent(StringHash(type), fullTraversal));
}

static bool NodeHasComponent(const Node* self, const char* type)
{
    return self->HasComponent(StringHash(type));
}

static void RegisterNode(kaguya::State& lua)
{
    using namespace kaguya;

    // enum CreateMode;
    lua["REPLICATED"] = REPLICATED;
    lua["LOCAL"] = LOCAL;

    // enum TransformSpace;
    lua["TS_LOCAL"] = TS_LOCAL;
    lua["TS_PARENT"] = TS_PARENT;
    lua["TS_WORLD"] = TS_WORLD;

    lua["Node"].setClass(UserdataMetatable<Node, Animatable>()
        .addStaticFunction("new", &CreateObject<Node>)

        ADD_OVERLOADED_FUNCTIONS_2(Node, SaveXML)
        ADD_OVERLOADED_FUNCTIONS_2(Node, SaveJSON)

        .addFunction("SetName", &Node::SetName)
        .addFunction("SetTags", &Node::SetTags)
        .addFunction("AddTag", &Node::AddTag)
        .addOverloadedFunctions("AddTags",
            &NodeAddTags0,
            &NodeAddTags1,
            static_cast<void(Node::*)(const StringVector&)>(&Node::AddTags))
        .addFunction("RemoveTag", &Node::RemoveTag)
        .addFunction("RemoveAllTags", &Node::RemoveAllTags)

        .addFunction("SetPosition", &Node::SetPosition)
        .addOverloadedFunctions("SetPosition2D",
            static_cast<void(Node::*)(const Vector2&)>(&Node::SetPosition2D),
            static_cast<void(Node::*)(float, float)>(&Node::SetPosition2D))
        .addFunction("SetRotation", &Node::SetRotation)
        .addFunction("SetRotation2D", &Node::SetRotation2D)
        .addFunction("SetDirection", &Node::SetDirection)

        .addOverloadedFunctions("SetScale",
            static_cast<void(Node::*)(float)>(&Node::SetScale),
            static_cast<void(Node::*)(const Vector3&)>(&Node::SetScale))
        .addOverloadedFunctions("SetScale2D",
            static_cast<void(Node::*)(const Vector2&)>(&Node::SetScale2D),
            static_cast<void(Node::*)(float, float)>(&Node::SetScale2D))

        .addOverloadedFunctions("SetTransform",
            static_cast<void(Node::*)(const Vector3&, const Quaternion&)>(&Node::SetTransform),
            static_cast<void(Node::*)(const Vector3&, const Quaternion&, float)>(&Node::SetTransform),
            static_cast<void(Node::*)(const Vector3&, const Quaternion&, const Vector3&)>(&Node::SetTransform))
        .addOverloadedFunctions("SetTransform2D",
            static_cast<void(Node::*)(const Vector2&, float)>(&Node::SetTransform2D),
            static_cast<void(Node::*)(const Vector2&, float, float)>(&Node::SetTransform2D),
            static_cast<void(Node::*)(const Vector2&, float, const Vector2&)>(&Node::SetTransform2D))

        .addFunction("SetWorldPosition", &Node::SetWorldPosition)
        .addOverloadedFunctions("SetWorldPosition2D",
            static_cast<void(Node::*)(const Vector2&)>(&Node::SetWorldPosition2D),
            static_cast<void(Node::*)(float, float)>(&Node::SetWorldPosition2D))

        .addFunction("SetWorldRotation", &Node::SetWorldRotation)
        .addFunction("SetWorldRotation2D", &Node::SetWorldRotation2D)

        .addFunction("SetWorldDirection", &Node::SetWorldDirection)

        .addOverloadedFunctions("SetWorldScale",
            static_cast<void(Node::*)(float)>(&Node::SetWorldScale),
            static_cast<void(Node::*)(const Vector3&)>(&Node::SetWorldScale))

        .addOverloadedFunctions("SetWorldScale2D",
            static_cast<void(Node::*)(const Vector2&)>(&Node::SetWorldScale2D),
            static_cast<void(Node::*)(float, float)>(&Node::SetWorldScale2D))

        .addOverloadedFunctions("SetWorldTransform",
            static_cast<void(Node::*)(const Vector3&, const Quaternion&)>(&Node::SetWorldTransform),
            static_cast<void(Node::*)(const Vector3&, const Quaternion&, float)>(&Node::SetWorldTransform),
            static_cast<void(Node::*)(const Vector3&, const Quaternion&, const Vector3&)>(&Node::SetWorldTransform))

        .addOverloadedFunctions("SetWorldTransform2D",
            static_cast<void(Node::*)(const Vector2&, float)>(&Node::SetWorldTransform2D),
            static_cast<void(Node::*)(const Vector2&, float, float)>(&Node::SetWorldTransform2D),
            static_cast<void(Node::*)(const Vector2&, float, const Vector2&)>(&Node::SetWorldTransform2D))

        ADD_OVERLOADED_FUNCTIONS_2(Node, Translate)
        ADD_OVERLOADED_FUNCTIONS_2(Node, Translate2D)

        ADD_OVERLOADED_FUNCTIONS_2(Node, Rotate)
        ADD_OVERLOADED_FUNCTIONS_2(Node, Rotate2D)

        ADD_OVERLOADED_FUNCTIONS_2(Node, RotateAround)
        ADD_OVERLOADED_FUNCTIONS_2(Node, RotateAround2D)

        ADD_OVERLOADED_FUNCTIONS_2(Node, Pitch)
        ADD_OVERLOADED_FUNCTIONS_2(Node, Yaw)
        ADD_OVERLOADED_FUNCTIONS_2(Node, Roll)
        ADD_OVERLOADED_FUNCTIONS_3(Node, LookAt)

        .addOverloadedFunctions("Scale",
            static_cast<void(Node::*)(float)>(&Node::Scale),
            static_cast<void(Node::*)(const Vector3&)>(&Node::Scale))

        .addFunction("Scale2D", &Node::Scale2D)

        .addFunction("SetEnabled", static_cast<void(Node::*)(bool)>(&Node::SetEnabled))
        .addFunction("SetDeepEnabled", &Node::SetDeepEnabled)
        .addFunction("ResetDeepEnabled", &Node::ResetDeepEnabled)
        .addFunction("SetEnabledRecursive", &Node::SetEnabledRecursive)
        .addFunction("SetOwner", &Node::SetOwner)
        .addFunction("MarkDirty", &Node::MarkDirty)

        ADD_OVERLOADED_FUNCTIONS_4(Node, CreateChild)
        ADD_OVERLOADED_FUNCTIONS_2(Node, AddChild)

        .addFunction("RemoveChild", static_cast<void(Node::*)(Node*)>(&Node::RemoveChild))
        .addFunction("RemoveAllChildren", &Node::RemoveAllChildren)
        .addFunction("RemoveChildren", &Node::RemoveChildren)

        ADD_OVERLOADED_FUNCTIONS_3(Node, CreateComponent)
        ADD_OVERLOADED_FUNCTIONS_3(Node, GetOrCreateComponent)
        ADD_OVERLOADED_FUNCTIONS_2(Node, CreateScriptObject)

        .addStaticFunction("GetScriptObject", &NodeGetScriptObject)

        ADD_OVERLOADED_FUNCTIONS_4(Node, CloneComponent)

        .addOverloadedFunctions("RemoveComponent",
            static_cast<void(Node::*)(Component*)>(&Node::RemoveComponent),
            &NodeRemoveComponent)

        .addOverloadedFunctions("RemoveComponents",
            static_cast<void(Node::*)(bool, bool)>(&Node::RemoveComponents),
            &NodeRemoveComponents)

        .addFunction("RemoveAllComponents", &Node::RemoveAllComponents)

        ADD_OVERLOADED_FUNCTIONS_2(Node, Clone)

        .addFunction("Remove", &Node::Remove)
        .addFunction("SetParent", &Node::SetParent)
        .addFunction("SetVar", &Node::SetVar)
        .addFunction("AddListener", &Node::AddListener)
        .addFunction("RemoveListener", &Node::RemoveListener)

        .addFunction("GetID", &Node::GetID)
        .addFunction("GetName", &Node::GetName)
        .addFunction("GetNameHash", &Node::GetNameHash)
        .addFunction("GetTags", &Node::GetTags)
        .addFunction("HasTag", &Node::HasTag)

        .addFunction("GetParent", &Node::GetParent)
        .addFunction("GetScene", &Node::GetScene)
        .addFunction("IsEnabled", &Node::IsEnabled)
        .addFunction("IsEnabledSelf", &Node::IsEnabledSelf)
        .addFunction("GetOwner", &Node::GetOwner)

        .addFunction("GetPosition", &Node::GetPosition)
        .addFunction("GetPosition2D", &Node::GetPosition2D)
        .addFunction("GetRotation", &Node::GetRotation)
        .addFunction("GetRotation2D", &Node::GetRotation2D)
        .addFunction("GetDirection", &Node::GetDirection)

        .addFunction("GetUp", &Node::GetUp)
        .addFunction("GetRight", &Node::GetRight)
        .addFunction("GetScale", &Node::GetScale)
        .addFunction("GetScale2D", &Node::GetScale2D)
        .addFunction("GetTransform", &Node::GetTransform)

        .addFunction("GetWorldPosition", &Node::GetWorldPosition)
        .addFunction("GetWorldPosition2D", &Node::GetWorldPosition2D)
        .addFunction("GetWorldRotation", &Node::GetWorldRotation)
        .addFunction("GetWorldRotation2D", &Node::GetWorldRotation2D)
        .addFunction("GetWorldDirection", &Node::GetWorldDirection)

        .addFunction("GetWorldUp", &Node::GetWorldUp)
        .addFunction("GetWorldRight", &Node::GetWorldRight)
        .addFunction("GetWorldScale", &Node::GetWorldScale)
        .addFunction("GetWorldScale2D", &Node::GetWorldScale2D)
        .addFunction("GetWorldTransform", &Node::GetWorldTransform)

        .addOverloadedFunctions("LocalToWorld",
            static_cast<Vector3(Node::*)(const Vector3&) const>(&Node::LocalToWorld),
            static_cast<Vector3(Node::*)(const Vector4&) const>(&Node::LocalToWorld))

        .addFunction("LocalToWorld2D", &Node::LocalToWorld2D)

        .addOverloadedFunctions("WorldToLocal",
            static_cast<Vector3(Node::*)(const Vector3&) const>(&Node::WorldToLocal),
            static_cast<Vector3(Node::*)(const Vector4&) const>(&Node::WorldToLocal))

        .addFunction("WorldToLocal2D", &Node::WorldToLocal2D)

        .addFunction("IsDirty", &Node::IsDirty)

        ADD_OVERLOADED_FUNCTIONS_2(Node, GetNumChildren)

        ADD_OVERLOADED_FUNCTIONS_2(Node, GetChildren)
        ADD_OVERLOADED_FUNCTIONS_2(Node, GetChildrenWithComponent)
        ADD_OVERLOADED_FUNCTIONS_2(Node, GetChildrenWithTag)

        .addOverloadedFunctions("GetChild",
            static_cast<Node*(Node::*)(unsigned) const>(&Node::GetChild),
            &NodeGetChild0,
            &NodeGetChild1)

        .addFunction("GetNumComponents", &Node::GetNumComponents)
        .addFunction("GetNumNetworkComponents", &Node::GetNumNetworkComponents)

        .addOverloadedFunctions("GetComponents",
            static_cast<const Vector<SharedPtr<Component> >&(Node::*)() const>(&Node::GetComponents),
            &NodeGetComponents0,
            &NodeGetComponents1)

        ADD_OVERLOADED_FUNCTIONS_2(Node, GetComponent)
        ADD_OVERLOADED_FUNCTIONS_2(Node, GetParentComponent)

        .addStaticFunction("HasComponent", &NodeHasComponent)

        // .addFunction("GetListeners", &Node::GetListeners)

        .addFunction("GetVar", &Node::GetVar)
        .addFunction("GetVars", &Node::GetVars)

        .addProperty("id", &Node::GetID)
        .addProperty("name", &Node::GetName, &Node::SetName)
        .addProperty("nameHash", &Node::GetNameHash)
        .addProperty("tags", &Node::GetTags, &Node::SetTags)

        .addProperty("parent", &Node::GetParent, &Node::SetParent)

        .addProperty("scene", &Node::GetScene)
        .addProperty("enabled", &Node::IsEnabled, static_cast<void(Node::*)(bool)>(&Node::SetEnabled))
        .addProperty("enabledSelf", &Node::IsEnabledSelf)

        .addProperty("owner", &Node::GetOwner, &Node::SetOwner)
        .addProperty("position", &Node::GetPosition, &Node::SetPosition)
        .addProperty("position2D", &Node::GetPosition2D, static_cast<void(Node::*)(const Vector2&)>(&Node::SetPosition2D))
        .addProperty("rotation", &Node::GetRotation, &Node::SetRotation)
        .addProperty("rotation2D", &Node::GetRotation2D, &Node::SetRotation2D)
        .addProperty("direction", &Node::GetDirection, &Node::SetDirection)
        .addProperty("up", &Node::GetUp)
        .addProperty("right", &Node::GetRight)
        .addProperty("scale", &Node::GetScale, static_cast<void(Node::*)(const Vector3&)>(&Node::SetScale))
        .addProperty("scale2D", &Node::GetScale2D, static_cast<void(Node::*)(const Vector2&)>(&Node::SetScale2D))
        .addProperty("transform", &Node::GetTransform)
        .addProperty("worldPosition", &Node::GetWorldPosition, &Node::SetWorldPosition)
        .addProperty("worldPosition2D", &Node::GetWorldPosition2D, static_cast<void(Node::*)(const Vector2&)>(&Node::SetWorldPosition2D))
        .addProperty("worldRotation", &Node::GetWorldRotation, &Node::SetWorldRotation)
        .addProperty("worldRotation2D", &Node::GetWorldRotation2D, &Node::SetWorldRotation2D)
        .addProperty("worldDirection", &Node::GetWorldDirection, &Node::SetWorldDirection)
        .addProperty("worldUp", &Node::GetWorldUp)
        .addProperty("worldRight", &Node::GetWorldRight)
        .addProperty("worldScale", &Node::GetWorldScale)
        .addProperty("worldScale2D", &Node::GetWorldScale2D)
        .addProperty("worldTransform", &Node::GetWorldTransform)
        .addProperty("dirty", &Node::IsDirty)
        .addProperty("numComponents", &Node::GetNumComponents)
        .addProperty("numNetworkComponents", &Node::GetNumNetworkComponents)
        // .addProperty("listeners", &Node::GetListeners)
        // .addProperty("vars", &Node::GetVars)
        );
}

static void ObjectAnimationAddAttributeAnimation0(ObjectAnimation* self, const String& name, ValueAnimation* attributeAnimation)
{
    self->AddAttributeAnimation(name, attributeAnimation);
}

static void ObjectAnimationAddAttributeAnimation1(ObjectAnimation* self, const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode)
{
    self->AddAttributeAnimation(name, attributeAnimation, wrapMode);
}

static void ObjectAnimationAddAttributeAnimation2(ObjectAnimation* self, const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed)
{
    self->AddAttributeAnimation(name, attributeAnimation, wrapMode, speed);
}

static void RegisterObjectAnimation(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ObjectAnimation"].setClass(UserdataMetatable<ObjectAnimation, Resource>()
        .addStaticFunction("new", &CreateObject<ObjectAnimation>)

        ADD_OVERLOADED_FUNCTIONS_3(ObjectAnimation, AddAttributeAnimation)

        .addOverloadedFunctions("RemoveAttributeAnimation",
            static_cast<void(ObjectAnimation::*)(const String&)>(&ObjectAnimation::RemoveAttributeAnimation),
            static_cast<void(ObjectAnimation::*)(ValueAnimation*)>(&ObjectAnimation::RemoveAttributeAnimation))

        .addFunction("GetAttributeAnimation", &ObjectAnimation::GetAttributeAnimation)
        .addFunction("GetAttributeAnimationWrapMode", &ObjectAnimation::GetAttributeAnimationWrapMode)
        .addFunction("GetAttributeAnimationSpeed", &ObjectAnimation::GetAttributeAnimationSpeed)
        );
}

static bool SceneLoadXML(Scene* scene, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return false;
    return scene->LoadXML(*file);
}

static bool SceneLoadJSON(Scene* scene, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return false;
    return scene->LoadJSON(*file);
}

static bool SceneSaveXML(const Scene* scene, const char* filepath, const String& indentation = "\t")
{
    SharedPtr<File> file(new File(globalContext, filepath, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return scene->SaveXML(*file, indentation);
}

static bool SceneSaveJSON(const Scene* scene, const char* filepath, const String& indentation = "\t")
{
    SharedPtr<File> file(new File(globalContext, filepath, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return scene->SaveJSON(*file, indentation);
}

static bool SceneLoadAsync0(Scene* self, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return false;
    return self->LoadAsync(file);
}

static bool SceneLoadAsync1(Scene* self, const char* filepath, LoadMode mode)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return false;
    return self->LoadAsync(file, mode);
}

static bool SceneLoadAsyncXML0(Scene* self, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return false;
    return self->LoadAsyncXML(file);
}

static bool SceneLoadAsyncXML1(Scene* self, const char* filepath, LoadMode mode)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return false;
    return self->LoadAsyncXML(file, mode);
}

static bool SceneLoadAsyncJSON0(Scene* self, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return false;
    return self->LoadAsyncJSON(file);
}

static bool SceneLoadAsyncJSON1(Scene* self, const char* filepath, LoadMode mode)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return false;
    return self->LoadAsyncJSON(file, mode);
}

static SharedPtr<Node> SceneInstantiate0(Scene* self, const char* filepath, const Vector3& position, const Quaternion& rotation)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return SharedPtr<Node>();
    return SharedPtr<Node>(self->Instantiate(*file, position, rotation));
}

static SharedPtr<Node> SceneInstantiate1(Scene* self, const char* filepath, const Vector3& position, const Quaternion& rotation, CreateMode mode)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return SharedPtr<Node>();
    return SharedPtr<Node>(self->Instantiate(*file, position, rotation, mode));
}

static SharedPtr<Node> SceneInstantiateXML0(Scene* self, const char* filepath, const Vector3& position, const Quaternion& rotation)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return SharedPtr<Node>();
    return SharedPtr<Node>(self->InstantiateXML(*file, position, rotation));
}

static SharedPtr<Node> SceneInstantiateXML1(Scene* self, const char* filepath, const Vector3& position, const Quaternion& rotation, CreateMode mode)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return SharedPtr<Node>();
    return SharedPtr<Node>(self->InstantiateXML(*file, position, rotation, mode));
}

static SharedPtr<Node> SceneInstantiateJSON0(Scene* self, const char* filepath, const Vector3& position, const Quaternion& rotation)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return SharedPtr<Node>();
    return SharedPtr<Node>(self->InstantiateJSON(*file, position, rotation));
}

static SharedPtr<Node> SceneInstantiateJSON1(Scene* self, const char* filepath, const Vector3& position, const Quaternion& rotation, CreateMode mode)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return SharedPtr<Node>();
    return SharedPtr<Node>(self->InstantiateJSON(*file, position, rotation, mode));
}

static void SceneClear0(Scene* self)
{
    self->Clear();
}

static void SceneClear1(Scene* self, bool clearReplicated)
{
    self->Clear(clearReplicated);
}

static void SceneClear2(Scene* self, bool clearReplicated, bool clearLocal)
{
    self->Clear(clearReplicated, clearLocal);
}

static void RegisterScene(kaguya::State& lua)
{
    using namespace kaguya;

    lua["FIRST_REPLICATED_ID"] = FIRST_REPLICATED_ID;
    lua["LAST_REPLICATED_ID"] = LAST_REPLICATED_ID;
    lua["FIRST_LOCAL_ID"] = FIRST_LOCAL_ID;
    lua["LAST_LOCAL_ID"] = LAST_LOCAL_ID;

    // enum LoadMode;
    lua["LOAD_RESOURCES_ONLY"] = LOAD_RESOURCES_ONLY;
    lua["LOAD_SCENE"] = LOAD_SCENE;
    lua["LOAD_SCENE_AND_RESOURCES"] = LOAD_SCENE_AND_RESOURCES;

    lua["Scene"].setClass(UserdataMetatable<Scene, Node>()
        .addStaticFunction("new", &CreateObject<Scene>)

        .addOverloadedFunctions("LoadXML", &SceneLoadXML,
            static_cast<bool (Scene::*)(Deserializer&)>(&Scene::LoadXML))
        .addOverloadedFunctions("LoadJSON", &SceneLoadJSON,
            static_cast<bool (Scene::*)(Deserializer&)>(&Scene::LoadJSON))
        .addOverloadedFunctions("SaveXML", &SceneSaveXML,
            static_cast<bool (Scene::*)(Serializer&, const String&) const>(&Scene::SaveXML))
        .addOverloadedFunctions("SaveJSON", &SceneSaveJSON,
            static_cast<bool (Scene::*)(Serializer&, const String&) const>(&Scene::SaveJSON))

        ADD_OVERLOADED_FUNCTIONS_2(Scene, LoadAsync)
        ADD_OVERLOADED_FUNCTIONS_2(Scene, LoadAsyncXML)
        ADD_OVERLOADED_FUNCTIONS_2(Scene, LoadAsyncJSON)
        .addFunction("StopAsyncLoading", &Scene::StopAsyncLoading)

        ADD_OVERLOADED_FUNCTIONS_2(Scene, Instantiate)
        ADD_OVERLOADED_FUNCTIONS_2(Scene, InstantiateXML)
        ADD_OVERLOADED_FUNCTIONS_2(Scene, InstantiateJSON)

        ADD_OVERLOADED_FUNCTIONS_3(Scene, Clear)

        .addFunction("SetUpdateEnabled", &Scene::SetUpdateEnabled)
        .addFunction("SetTimeScale", &Scene::SetTimeScale)
        .addFunction("SetElapsedTime", &Scene::SetElapsedTime)
        .addFunction("SetSmoothingConstant", &Scene::SetSmoothingConstant)
        .addFunction("SetSnapThreshold", &Scene::SetSnapThreshold)
        .addFunction("SetAsyncLoadingMs", &Scene::SetAsyncLoadingMs)

        .addFunction("AddRequiredPackageFile", &Scene::AddRequiredPackageFile)
        .addFunction("ClearRequiredPackageFiles", &Scene::ClearRequiredPackageFiles)

        .addFunction("RegisterVar", &Scene::RegisterVar)
        .addFunction("UnregisterVar", &Scene::UnregisterVar)
        .addFunction("UnregisterAllVars", &Scene::UnregisterAllVars)

        .addFunction("GetNode", &Scene::GetNode)
        .addFunction("GetComponentByID", static_cast<Component* (Scene::*)(unsigned) const>(&Scene::GetComponent))
        .addFunction("GetNodesWithTag", &Scene::GetNodesWithTag)

        .addFunction("IsUpdateEnabled", &Scene::IsUpdateEnabled)
        .addFunction("IsAsyncLoading", &Scene::IsAsyncLoading)
        .addFunction("GetAsyncProgress", &Scene::GetAsyncProgress)
        .addFunction("GetAsyncLoadMode", &Scene::GetAsyncLoadMode)
        .addFunction("GetFileName", &Scene::GetFileName)
        .addFunction("GetChecksum", &Scene::GetChecksum)
        .addFunction("GetTimeScale", &Scene::GetTimeScale)
        .addFunction("GetElapsedTime", &Scene::GetElapsedTime)
        .addFunction("GetSmoothingConstant", &Scene::GetSmoothingConstant)
        .addFunction("GetSnapThreshold", &Scene::GetSnapThreshold)
        .addFunction("GetAsyncLoadingMs", &Scene::GetAsyncLoadingMs)

        .addFunction("GetRequiredPackageFiles", &Scene::GetRequiredPackageFiles)

        .addProperty("updateEnabled", &Scene::IsUpdateEnabled, &Scene::SetUpdateEnabled)
        .addProperty("asyncLoading", &Scene::IsAsyncLoading)
        .addProperty("asyncProgress", &Scene::GetAsyncProgress)
        .addProperty("asyncLoadMode", &Scene::GetAsyncLoadMode)
        .addProperty("fileName", &Scene::GetFileName)
        .addProperty("checksum", &Scene::GetChecksum)
        .addProperty("timeScale", &Scene::GetTimeScale, &Scene::SetTimeScale)
        .addProperty("elapsedTime", &Scene::GetElapsedTime, &Scene::SetElapsedTime)
        .addProperty("smoothingConstant", &Scene::GetSmoothingConstant, &Scene::SetSmoothingConstant)
        .addProperty("snapThreshold", &Scene::GetSnapThreshold, &Scene::SetSnapThreshold)
        .addProperty("asyncLoadingMs", &Scene::GetAsyncLoadingMs, &Scene::SetAsyncLoadingMs)
        );
}

static void RegisterSceneEvents(kaguya::State& lua)
{
    using namespace kaguya;

    lua["E_SCENEUPDATE"] = E_SCENEUPDATE;
    lua["E_SCENESUBSYSTEMUPDATE"] = E_SCENESUBSYSTEMUPDATE;
    lua["E_UPDATESMOOTHING"] = E_UPDATESMOOTHING;
    lua["E_SCENEDRAWABLEUPDATEFINISHED"] = E_SCENEDRAWABLEUPDATEFINISHED;
    lua["E_TARGETPOSITION"] = E_TARGETPOSITION;
    lua["E_TARGETROTATION"] = E_TARGETROTATION;
    lua["E_ATTRIBUTEANIMATIONUPDATE"] = E_ATTRIBUTEANIMATIONUPDATE;
    lua["E_ATTRIBUTEANIMATIONADDED"] = E_ATTRIBUTEANIMATIONADDED;
    lua["E_ATTRIBUTEANIMATIONREMOVED"] = E_ATTRIBUTEANIMATIONREMOVED;
    lua["E_SCENEPOSTUPDATE"] = E_SCENEPOSTUPDATE;
    lua["E_ASYNCLOADPROGRESS"] = E_ASYNCLOADPROGRESS;
    lua["E_ASYNCLOADFINISHED"] = E_ASYNCLOADFINISHED;
    lua["E_NODEADDED"] = E_NODEADDED;
    lua["E_NODEREMOVED"] = E_NODEREMOVED;
    lua["E_COMPONENTADDED"] = E_COMPONENTADDED;
    lua["E_COMPONENTREMOVED"] = E_COMPONENTREMOVED;
    lua["E_NODENAMECHANGED"] = E_NODENAMECHANGED;
    lua["E_NODEENABLEDCHANGED"] = E_NODEENABLEDCHANGED;
    lua["E_NODETAGADDED"] = E_NODETAGADDED;
    lua["E_NODETAGREMOVED"] = E_NODETAGREMOVED;
    lua["E_COMPONENTENABLEDCHANGED"] = E_COMPONENTENABLEDCHANGED;
    lua["E_TEMPORARYCHANGED"] = E_TEMPORARYCHANGED;
    lua["E_NODECLONED"] = E_NODECLONED;
    lua["E_COMPONENTCLONED"] = E_COMPONENTCLONED;
    lua["E_INTERCEPTNETWORKUPDATE"] = E_INTERCEPTNETWORKUPDATE;
}

static bool SerializableLoad0(Serializable* self, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    if (!file->IsOpen())
        return false;
    return self->Load(*file);
}

static bool SerializableLoad1(Serializable* self, const char* filepath, bool setInstanceDefault)
{
    SharedPtr<File> file(new File(globalContext, filepath));
    return self->Load(*file, setInstanceDefault);
}

static bool SerializableSave(const Serializable* self, const char* filepath)
{
    SharedPtr<File> file(new File(globalContext, filepath, FILE_WRITE));
    return self->Save(*file);
}

static void RegisterSerializable(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Serializable"].setClass(UserdataMetatable<Serializable, Object>()

        ADD_OVERLOADED_FUNCTIONS_2(Serializable, Load)
        .addStaticFunction("Save", &SerializableSave)

        .addOverloadedFunctions("SetAttribute",
            static_cast<bool(Serializable::*)(unsigned, const Variant&)>(&Serializable::SetAttribute),
            static_cast<bool(Serializable::*)(const String&, const Variant&)>(&Serializable::SetAttribute))

        .addOverloadedFunctions("GetAttribute",
            static_cast<Variant(Serializable::*)(unsigned) const>(&Serializable::GetAttribute),
            static_cast<Variant(Serializable::*)(const String&) const>(&Serializable::GetAttribute))

        .addOverloadedFunctions("GetAttributeDefault",
            static_cast<Variant(Serializable::*)(unsigned) const>(&Serializable::GetAttributeDefault),
            static_cast<Variant(Serializable::*)(const String&) const>(&Serializable::GetAttributeDefault))

        .addFunction("GetNumAttributes", &Serializable::GetNumAttributes)
        .addFunction("GetNumNetworkAttributes", &Serializable::GetNumNetworkAttributes)
        );
}

static void RegisterSmoothedTransform(kaguya::State& lua)
{
    using namespace kaguya;

    lua["SMOOTH_NONE"] = SMOOTH_NONE;
    lua["SMOOTH_POSITION"] = SMOOTH_POSITION;
    lua["SMOOTH_ROTATION"] = SMOOTH_ROTATION;

    lua["SmoothedTransform"].setClass(UserdataMetatable<SmoothedTransform, Component>()
        .addStaticFunction("new", &CreateObject<SmoothedTransform>)

        .addFunction("SetTargetPosition", &SmoothedTransform::SetTargetPosition)
        .addFunction("SetTargetRotation", &SmoothedTransform::SetTargetRotation)
        .addFunction("SetTargetWorldPosition", &SmoothedTransform::SetTargetWorldPosition)
        .addFunction("SetTargetWorldRotation", &SmoothedTransform::SetTargetWorldRotation)

        .addFunction("GetTargetPosition", &SmoothedTransform::GetTargetPosition)
        .addFunction("GetTargetRotation", &SmoothedTransform::GetTargetRotation)
        .addFunction("GetTargetWorldPosition", &SmoothedTransform::GetTargetWorldPosition)
        .addFunction("GetTargetWorldRotation", &SmoothedTransform::GetTargetWorldRotation)

        .addFunction("IsInProgress", &SmoothedTransform::IsInProgress)

        .addProperty("targetPosition", &SmoothedTransform::GetTargetPosition, &SmoothedTransform::SetTargetPosition)
        .addProperty("targetRotation", &SmoothedTransform::GetTargetRotation, &SmoothedTransform::SetTargetRotation)
        .addProperty("targetWorldPosition", &SmoothedTransform::GetTargetWorldPosition, &SmoothedTransform::SetTargetWorldPosition)
        .addProperty("targetWorldRotation", &SmoothedTransform::GetTargetWorldRotation, &SmoothedTransform::SetTargetWorldRotation)

        .addProperty("inProgress", &SmoothedTransform::IsInProgress)
        );
}

static void SplinePathAddControlPoint0(SplinePath* self, Node* point)
{
    self->AddControlPoint(point);
}

static void SplinePathAddControlPoint1(SplinePath* self, Node* point, unsigned index)
{
    self->AddControlPoint(point, index);
}

static void RegisterSplinePath(kaguya::State& lua)
{
    using namespace kaguya;

    lua["SplinePath"].setClass(UserdataMetatable<SplinePath, Component>()
        .addStaticFunction("new", &CreateObject<SplinePath>)

        ADD_OVERLOADED_FUNCTIONS_2(SplinePath, AddControlPoint)

        .addFunction("RemoveControlPoint", &SplinePath::RemoveControlPoint)
        .addFunction("ClearControlPoints", &SplinePath::ClearControlPoints)

        .addFunction("SetInterpolationMode", &SplinePath::SetInterpolationMode)
        .addFunction("SetSpeed", &SplinePath::SetSpeed)
        .addFunction("SetPosition", &SplinePath::SetPosition)
        .addFunction("SetControlledNode", &SplinePath::SetControlledNode)

        .addFunction("GetInterpolationMode", &SplinePath::GetInterpolationMode)
        .addFunction("GetSpeed", &SplinePath::GetSpeed)
        .addFunction("GetLength", &SplinePath::GetLength)
        .addFunction("GetPosition", &SplinePath::GetPosition)
        .addFunction("GetControlledNode", &SplinePath::GetControlledNode)
        .addFunction("GetPoint", &SplinePath::GetPoint)
        .addFunction("Move", &SplinePath::Move)
        .addFunction("Reset", &SplinePath::Reset)
        .addFunction("IsFinished", &SplinePath::IsFinished)

        .addProperty("interpolationMode", &SplinePath::GetInterpolationMode, &SplinePath::SetInterpolationMode)
        .addProperty("speed", &SplinePath::GetSpeed, &SplinePath::SetSpeed)
        .addProperty("length", &SplinePath::GetLength)
        .addProperty("position", &SplinePath::GetPosition, &SplinePath::SetPosition)
        .addProperty("controlledNode", &SplinePath::GetControlledNode, &SplinePath::SetControlledNode)
        .addProperty("finished", &SplinePath::IsFinished)
        );
}

static void ValueAnimationSetEventFrame0(ValueAnimation* self, float time, const StringHash& eventType)
{
    self->SetEventFrame(time, eventType);
}

static void ValueAnimationSetEventFrame1(ValueAnimation* self, float time, const StringHash& eventType, const VariantMap& eventData)
{
    self->SetEventFrame(time, eventType, eventData);
}

static void RegisterValueAnimation(kaguya::State& lua)
{
    using namespace kaguya;

    // enum InterpMethod;
    lua["IM_NONE"] = IM_NONE;
    lua["IM_LINEAR"] = IM_LINEAR;
    lua["IM_SPLINE"] = IM_SPLINE;

    lua["ValueAnimation"].setClass(UserdataMetatable<ValueAnimation, Resource>()
        .addStaticFunction("new", &CreateObject<ValueAnimation>)

        .addFunction("SetInterpolationMethod", &ValueAnimation::SetInterpolationMethod)
        .addFunction("SetSplineTension", &ValueAnimation::SetSplineTension)
        .addFunction("SetValueType", &ValueAnimation::SetValueType)
        .addFunction("SetKeyFrame", &ValueAnimation::SetKeyFrame)

        ADD_OVERLOADED_FUNCTIONS_2(ValueAnimation, SetEventFrame)

        .addFunction("IsValid", &ValueAnimation::IsValid)
        .addFunction("GetInterpolationMethod", &ValueAnimation::GetInterpolationMethod)
        .addFunction("GetSplineTension", &ValueAnimation::GetSplineTension)
        .addFunction("GetValueType", &ValueAnimation::GetValueType)
        .addFunction("GetBeginTime", &ValueAnimation::GetBeginTime)
        .addFunction("GetEndTime", &ValueAnimation::GetEndTime)
        .addFunction("GetAnimationValue", &ValueAnimation::GetAnimationValue)
        .addFunction("HasEventFrames", &ValueAnimation::HasEventFrames)

        .addProperty("valid", &ValueAnimation::IsValid)
        .addProperty("interpolationMethod", &ValueAnimation::GetInterpolationMethod, &ValueAnimation::SetInterpolationMethod)
        .addProperty("splineTension", &ValueAnimation::GetSplineTension, &ValueAnimation::SetSplineTension)
        .addProperty("valueType", &ValueAnimation::GetValueType, &ValueAnimation::SetValueType)
        );
}

void RegisterSceneLuaAPI(kaguya::State& lua)
{
    RegisterSerializable(lua);

    RegisterAnimatable(lua);
    RegisterAnimationDefs(lua);
    RegisterComponent(lua);
    RegisterLogicComponent(lua);
    RegisterNode(lua);
    RegisterObjectAnimation(lua);
    RegisterScene(lua);
    RegisterSceneEvents(lua);
    RegisterSmoothedTransform(lua);
    RegisterSplinePath(lua);
    RegisterValueAnimation(lua);
}
}
