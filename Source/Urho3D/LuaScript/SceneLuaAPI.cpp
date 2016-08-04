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

KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimatableSetAttributeAnimation, Animatable, SetAttributeAnimation, 2, 4);

static void RegisterAnimatable(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Animatable"].setClass(UserdataMetatable<Animatable, Serializable>()

        .addFunction("SetAnimationEnabled", &Animatable::SetAnimationEnabled)
        .addFunction("SetAnimationTime", &Animatable::SetAnimationTime)
        .addFunction("SetObjectAnimation", &Animatable::SetObjectAnimation)

        .addFunction("SetAttributeAnimation", AnimatableSetAttributeAnimation())

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

static bool NodeSaveXML(const Node* self, const String& fileName, const String& indentation = "\t")
{
    SharedPtr<File> file(new File(globalContext, fileName, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return self->SaveXML(*file, indentation);
}

KAGUYA_FUNCTION_OVERLOADS(NodeSaveXMLOverloads, NodeSaveXML, 2, 3);

static bool NodeSaveJSON(const Node* self, const String& fileName, const String& indentation = "\t")
{
    SharedPtr<File> file(new File(globalContext, fileName, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return self->SaveJSON(*file, indentation);
}

KAGUYA_FUNCTION_OVERLOADS(NodeSaveJSONOverloads, NodeSaveJSON, 2, 3);

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(NodeAddTags, Node, AddTags, 1, 2, void(Node::*)(const String&, char));

KAGUYA_MEMBER_FUNCTION_OVERLOADS(NodeTranslate, Node, Translate, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(NodeTranslate2D, Node, Translate2D, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(NodeRotate, Node, Rotate, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(NodeRotate2D, Node, Rotate2D, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(NodeRotateAround, Node, RotateAround, 2, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(NodeRotateAround2D, Node, RotateAround2D, 2, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(NodePitch, Node, Pitch, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(NodeYaw, Node, Yaw, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(NodeRoll, Node, Roll, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(NodeLookAt, Node, LookAt, 2, 3);

static SharedPtr<Node> NodeCreateChild(Node* self, const String& name = String::EMPTY, CreateMode mode = REPLICATED, unsigned id = 0)
{
	return SharedPtr<Node>(self->CreateChild(name, mode, id));
}

KAGUYA_FUNCTION_OVERLOADS(NodeCreateChildOverloads, NodeCreateChild, 1, 4);

KAGUYA_MEMBER_FUNCTION_OVERLOADS(NodeAddChild, Node, AddChild, 1, 2);

static SharedPtr<Component> NodeCreateComponent(Node* self, StringHash type, CreateMode mode = REPLICATED, unsigned id = 0)
{
    return SharedPtr<Component>(self->CreateComponent(type, mode, id));
}

KAGUYA_FUNCTION_OVERLOADS(NodeCreateComponentOverloads, NodeCreateComponent, 2, 4);

static SharedPtr<Component> NodeGetOrCreateComponent(Node* self, StringHash type, CreateMode mode = REPLICATED, unsigned id = 0)
{
    return SharedPtr<Component>(self->GetOrCreateComponent(type, mode, id));
}

KAGUYA_FUNCTION_OVERLOADS(NodeGetOrCreateComponentOverloads, NodeGetOrCreateComponent, 2, 4);

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

static SharedPtr<Component> NodeCloneComponent0(Node* self, Component* component, unsigned id = 0)
{
    return SharedPtr<Component>(self->CloneComponent(component, id));
}

KAGUYA_FUNCTION_OVERLOADS(NodeCloneComponentOverloads0, NodeCloneComponent0, 2, 3);

static SharedPtr<Component> NodeCloneComponent1(Node* self, Component* component, CreateMode mode, unsigned id = 0)
{
    return SharedPtr<Component>(self->CloneComponent(component, mode, id));
}

KAGUYA_FUNCTION_OVERLOADS(NodeCloneComponentOverloads1, NodeCloneComponent1, 3, 4);

static SharedPtr<Node> NodeClone(Node* self, CreateMode mode = REPLICATED)
{
    return SharedPtr<Node>(self->Clone(mode));
}

KAGUYA_FUNCTION_OVERLOADS(NodeCloneOverloads, NodeClone, 1, 2);

KAGUYA_MEMBER_FUNCTION_OVERLOADS(NodeGetNumChildren, Node, GetNumChildren, 0, 1);

static PODVector<Node*> NodeGetChildren(const Node* self, bool recursive = false)
{
    PODVector<Node*> dest;
    self->GetChildren(dest, recursive);
    return dest;
}

KAGUYA_FUNCTION_OVERLOADS(NodeGetChildrenOverloads, NodeGetChildren, 1, 2);

static PODVector<Node*> NodeGetChildrenWithComponent(const Node* self, StringHash type, bool recursive = false)
{
    PODVector<Node*> dest;
    self->GetChildrenWithComponent(dest, type, recursive);
    return dest;
}

KAGUYA_FUNCTION_OVERLOADS(NodeGetChildrenWithComponentOverloads, NodeGetChildrenWithComponent, 2, 3);

static PODVector<Node*> NodeGetChildrenWithTag(const Node* self, const String& tag, bool recursive = false)
{
    PODVector<Node*> dest;
    self->GetChildrenWithTag(dest, tag, recursive);
    return dest;
}

KAGUYA_FUNCTION_OVERLOADS(NodeGetChildrenWithTagOverloads, NodeGetChildrenWithTag, 2, 3);

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(NodeGetChild, Node, GetChild, 1, 2, Node*(Node::*)(const char*, bool)const);

static PODVector<Component*> NodeGetComponents(const Node* self, StringHash type, bool recursive = false)
{
    PODVector<Component*> dest;
    self->GetComponents(dest, type, recursive);
    return dest;
}

KAGUYA_FUNCTION_OVERLOADS(NodeGetComponentsOverloads, NodeGetComponents, 2, 3);

static SharedPtr<Component> NodeGetComponent(const Node* node, StringHash type, bool recursive = false)
{
    return SharedPtr<Component>(node->GetComponent(type, recursive));
}

KAGUYA_FUNCTION_OVERLOADS(NodeGetComponentOverloads, NodeGetComponent, 2, 3);

static SharedPtr<Component> NodeGetParentComponent(const Node* node, StringHash type, bool fullTraversal = false)
{
    return SharedPtr<Component>(node->GetParentComponent(type, fullTraversal));
}

KAGUYA_FUNCTION_OVERLOADS(NodeGetParentComponentOverloads, NodeGetParentComponent, 2, 3);

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

        .addStaticFunction("SaveXML", NodeSaveXMLOverloads())
        .addStaticFunction("SaveJSON", NodeSaveJSONOverloads())

        .addFunction("SetName", &Node::SetName)
        .addFunction("SetTags", &Node::SetTags)
        .addFunction("AddTag", &Node::AddTag)
        .addOverloadedFunctions("AddTags",
            NodeAddTags(),
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

        .addFunction("Translate", NodeTranslate())
        .addFunction("Translate2D", NodeTranslate2D())

        .addFunction("Rotate", NodeRotate())
        .addFunction("Rotate2D", NodeRotate2D())

        .addFunction("RotateAround", NodeRotateAround())
        .addFunction("RotateAround2D", NodeRotateAround2D())

        .addFunction("Pitch", NodePitch())
        .addFunction("Yaw", NodeYaw())
        .addFunction("Roll", NodeRoll())
        .addFunction("LookAt", NodeLookAt())

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

        .addStaticFunction("CreateChild", NodeCreateChildOverloads())

        .addFunction("AddChild", NodeAddChild())

        .addFunction("RemoveChild", static_cast<void(Node::*)(Node*)>(&Node::RemoveChild))
        .addFunction("RemoveAllChildren", &Node::RemoveAllChildren)
        .addFunction("RemoveChildren", &Node::RemoveChildren)

        .addStaticFunction("CreateComponent", NodeCreateComponentOverloads())
        .addStaticFunction("GetOrCreateComponent", NodeGetOrCreateComponentOverloads())

        .addOverloadedFunctions("CreateScriptObject", &NodeCreateScriptObject0, &NodeCreateScriptObject1)

        .addStaticFunction("GetScriptObject", &NodeGetScriptObject)

        .addOverloadedFunctions("CloneComponent", 
            NodeCloneComponentOverloads0(), 
            NodeCloneComponentOverloads1())

        .addOverloadedFunctions("RemoveComponent",
            static_cast<void(Node::*)(Component*)>(&Node::RemoveComponent),
			static_cast<void(Node::*)(StringHash)>(&Node::RemoveComponent))

        .addOverloadedFunctions("RemoveComponents",
            static_cast<void(Node::*)(bool, bool)>(&Node::RemoveComponents),
			static_cast<void(Node::*)(StringHash)>(&Node::RemoveComponents))

        .addFunction("RemoveAllComponents", &Node::RemoveAllComponents)

        .addStaticFunction("Clone", NodeCloneOverloads())

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

        .addFunction("GetNumChildren", NodeGetNumChildren())

        .addStaticFunction("GetChildren", NodeGetChildrenOverloads())
        .addStaticFunction("GetChildrenWithComponent", NodeGetChildrenWithComponentOverloads())
        .addStaticFunction("GetChildrenWithTag", NodeGetChildrenWithTagOverloads())

        .addOverloadedFunctions("GetChild",
            static_cast<Node*(Node::*)(unsigned) const>(&Node::GetChild),
            NodeGetChild())

        .addFunction("GetNumComponents", &Node::GetNumComponents)
        .addFunction("GetNumNetworkComponents", &Node::GetNumNetworkComponents)

        .addOverloadedFunctions("GetComponents",
            static_cast<const Vector<SharedPtr<Component> >&(Node::*)() const>(&Node::GetComponents),
            NodeGetComponentsOverloads())

        .addStaticFunction("GetComponent", NodeGetComponentOverloads())
        .addStaticFunction("GetParentComponent", NodeGetParentComponentOverloads())

        .addFunction("HasComponent", 
			static_cast<bool(Node::*)(StringHash)const>(&Node::HasComponent))

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

KAGUYA_MEMBER_FUNCTION_OVERLOADS(ObjectAnimationAddAttributeAnimation, ObjectAnimation, AddAttributeAnimation, 2, 4);

static void RegisterObjectAnimation(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ObjectAnimation"].setClass(UserdataMetatable<ObjectAnimation, Resource>()
        .addStaticFunction("new", &CreateObject<ObjectAnimation>)

        .addFunction("AddAttributeAnimation", ObjectAnimationAddAttributeAnimation())

        .addOverloadedFunctions("RemoveAttributeAnimation",
            static_cast<void(ObjectAnimation::*)(const String&)>(&ObjectAnimation::RemoveAttributeAnimation),
            static_cast<void(ObjectAnimation::*)(ValueAnimation*)>(&ObjectAnimation::RemoveAttributeAnimation))

        .addFunction("GetAttributeAnimation", &ObjectAnimation::GetAttributeAnimation)
        .addFunction("GetAttributeAnimationWrapMode", &ObjectAnimation::GetAttributeAnimationWrapMode)
        .addFunction("GetAttributeAnimationSpeed", &ObjectAnimation::GetAttributeAnimationSpeed)
        );
}

static bool SceneLoadXML(Scene* scene, const String& fileName)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return false;
    return scene->LoadXML(*file);
}

static bool SceneLoadJSON(Scene* scene, const String& fileName)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return false;
    return scene->LoadJSON(*file);
}

static bool SceneSaveXML(const Scene* scene, const String& fileName, const String& indentation = "\t")
{
    SharedPtr<File> file(new File(globalContext, fileName, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return scene->SaveXML(*file, indentation);
}

KAGUYA_FUNCTION_OVERLOADS(SceneSaveXMLOverloads, SceneSaveXML, 2, 3);

static bool SceneSaveJSON(const Scene* scene, const String& fileName, const String& indentation = "\t")
{
    SharedPtr<File> file(new File(globalContext, fileName, FILE_WRITE));
    if (!file->IsOpen())
        return false;
    return scene->SaveJSON(*file, indentation);
}

KAGUYA_FUNCTION_OVERLOADS(SceneSaveJSONOverloads, SceneSaveJSON, 2, 3);

static bool SceneLoadAsync(Scene* self, const String& fileName, LoadMode mode = LOAD_SCENE_AND_RESOURCES)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return false;
    return self->LoadAsync(file, mode);
}

KAGUYA_FUNCTION_OVERLOADS(SceneLoadAsyncOverloads, SceneLoadAsync, 2, 3);

static bool SceneLoadAsyncXML(Scene* self, const String& fileName, LoadMode mode = LOAD_SCENE_AND_RESOURCES)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return false;
    return self->LoadAsyncXML(file, mode);
}

KAGUYA_FUNCTION_OVERLOADS(SceneLoadAsyncXMLOverloads, SceneLoadAsyncXML, 2, 3);

static bool SceneLoadAsyncJSON(Scene* self, const String& fileName, LoadMode mode = LOAD_SCENE_AND_RESOURCES)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return false;
    return self->LoadAsyncJSON(file, mode);
}

KAGUYA_FUNCTION_OVERLOADS(SceneLoadAsyncJSONOverloads, SceneLoadAsyncJSON, 2, 3);

static SharedPtr<Node> SceneInstantiate(Scene* self, const String& fileName, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return SharedPtr<Node>();
    return SharedPtr<Node>(self->Instantiate(*file, position, rotation, mode));
}

KAGUYA_FUNCTION_OVERLOADS(SceneInstantiateOverloads, SceneInstantiate, 4, 5);

static SharedPtr<Node> SceneInstantiateXML(Scene* self, const String& fileName, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return SharedPtr<Node>();
    return SharedPtr<Node>(self->InstantiateXML(*file, position, rotation, mode));
}

KAGUYA_FUNCTION_OVERLOADS(SceneInstantiateXMLOverloads, SceneInstantiateXML, 4, 5);

static SharedPtr<Node> SceneInstantiateJSON(Scene* self, const String& fileName, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    if (!file->IsOpen())
        return SharedPtr<Node>();
    return SharedPtr<Node>(self->InstantiateJSON(*file, position, rotation, mode));
}

KAGUYA_FUNCTION_OVERLOADS(SceneInstantiateJSONOverloads, SceneInstantiateJSON, 4, 5);

KAGUYA_MEMBER_FUNCTION_OVERLOADS(SceneClear, Scene, Clear, 0, 2);

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
        .addOverloadedFunctions("SaveXML", SceneSaveXMLOverloads(),
            static_cast<bool (Scene::*)(Serializer&, const String&) const>(&Scene::SaveXML))
        .addOverloadedFunctions("SaveJSON", SceneSaveJSONOverloads(),
            static_cast<bool (Scene::*)(Serializer&, const String&) const>(&Scene::SaveJSON))

        .addStaticFunction("LoadAsync", SceneLoadAsyncOverloads())
        .addStaticFunction("LoadAsyncXML", SceneLoadAsyncXMLOverloads())
        .addStaticFunction("LoadAsyncJSON", SceneLoadAsyncJSONOverloads())

        .addFunction("StopAsyncLoading", &Scene::StopAsyncLoading)

        .addStaticFunction("Instantiate", SceneInstantiateOverloads())
        .addStaticFunction("InstantiateXML", SceneInstantiateXMLOverloads())
        .addStaticFunction("InstantiateJSON", SceneInstantiateJSONOverloads())

        .addFunction("Clear", SceneClear())

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

static bool SerializableLoad0(Serializable* self, const String& fileName, bool setInstanceDefault = false)
{
    SharedPtr<File> file(new File(globalContext, fileName));
    return self->Load(*file, setInstanceDefault);
}

KAGUYA_FUNCTION_OVERLOADS(SerializableLoadOverloads0, SerializableLoad0, 2, 3);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(SerializableLoad1, Serializable, Load, 1, 2);

static bool SerializableSave(const Serializable* self, const String& fileName)
{
    SharedPtr<File> file(new File(globalContext, fileName, FILE_WRITE));
    return self->Save(*file);
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(SerializableLoadXML, Serializable, LoadXML, 1, 2);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(SerializableLoadJSON, Serializable, LoadJSON, 1, 2);

static void RegisterSerializable(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Serializable"].setClass(UserdataMetatable<Serializable, Object>()

        .addOverloadedFunctions("Load", 
            SerializableLoadOverloads0(),
            SerializableLoad1())

        .addOverloadedFunctions("Save", 
            &SerializableSave, 
            &Serializable::Save)

        .addFunction("LoadXML", SerializableLoadXML())
        .addFunction("SaveXML", &Serializable::SaveXML)

        .addFunction("LoadJSON", SerializableLoadJSON())
        .addFunction("SaveJSON", &Serializable::SaveJSON)

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

KAGUYA_MEMBER_FUNCTION_OVERLOADS(ValueAnimationSetEventFrame, ValueAnimation, SetEventFrame, 2, 3);

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

        .addFunction("SetEventFrame", ValueAnimationSetEventFrame())

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
