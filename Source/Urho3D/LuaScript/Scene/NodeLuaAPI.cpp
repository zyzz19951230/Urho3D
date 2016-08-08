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

#include "../../IO/File.h"
#include "../../LuaScript/LuaFile.h"
#include "../../LuaScript/LuaScriptInstance.h"
#include "../../Resource/ResourceCache.h"
#include "../../Scene/Node.h"
#include "../../Scene/Scene.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

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
KAGUYA_MEMBER_FUNCTION_OVERLOADS(NodeLookAt, Node, LookAt, 1, 3);

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

void RegisterNode(kaguya::State& lua)
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

        .addFunction("SetID", &Node::SetID)
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

        // .addFunction("SetOwner", &Node::SetOwner)
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
        .addFunction("ReorderComponent", &Node::ReorderComponent)

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

        // .addFunction("GetOwner", &Node::GetOwner)
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

        // .addProperty("owner", &Node::GetOwner, &Node::SetOwner)
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
}

