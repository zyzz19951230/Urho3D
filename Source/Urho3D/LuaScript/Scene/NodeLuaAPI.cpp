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

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(NodeGetChild, Node, GetChild, 1, 2, Node*(Node::*)(const String&, bool)const);

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

    // [Enum] CreateMode
    // [Constant] Node* CreateChild(String& name
    lua["REPLICATED"] = REPLICATED;
    // [Variable] LOCAL
    lua["LOCAL"] = LOCAL;

    // [Enum] TransformSpace
    // [Constant] void Translate(Vector3& delta, TransformSpace space
    lua["TS_LOCAL"] = TS_LOCAL;
    // [Variable] TS_PARENT,
    lua["TS_PARENT"] = TS_PARENT;
    // [Constant] bool LookAt(Vector3& target, Vector3& up
    lua["TS_WORLD"] = TS_WORLD;

    // [Class] Node : Animatable
    lua["Node"].setClass(UserdataMetatable<Node, Animatable>()
        // [Constructor] Node()
        .addStaticFunction("new", &CreateObject<Node>)

        // [Method] bool SaveXML(const String& fileName, const String& indentation = "\t") const
        .addStaticFunction("SaveXML", NodeSaveXMLOverloads())
        // [Method] bool SaveJSON(const String& fileName, const String& indentation = "\t") const
        .addStaticFunction("SaveJSON", NodeSaveJSONOverloads())

        // [Method] void SetID(unsigned id)
        .addFunction("SetID", &Node::SetID)
        // [Method] void SetName(const String& name)
        .addFunction("SetName", &Node::SetName)
        // [Method] void SetTags(const StringVector& tags)
        .addFunction("SetTags", &Node::SetTags)
        // [Method] void AddTag(const String& tag)
        .addFunction("AddTag", &Node::AddTag)
        .addOverloadedFunctions("AddTags",
            // [Method] void AddTags(const String& tags, char separator = ';')
            NodeAddTags(),
            // [Method] void AddTags(const StringVector& tags)
            static_cast<void(Node::*)(const StringVector&)>(&Node::AddTags))
        // [Method] bool RemoveTag(const String& tag)
        .addFunction("RemoveTag", &Node::RemoveTag)
        // [Method] void RemoveAllTags()
        .addFunction("RemoveAllTags", &Node::RemoveAllTags)

        // [Method] void SetPosition(const Vector3& position)
        .addFunction("SetPosition", &Node::SetPosition)
        .addOverloadedFunctions("SetPosition2D",
            // [Method] 
            static_cast<void(Node::*)(const Vector2&)>(&Node::SetPosition2D),
            // [Method] 
            static_cast<void(Node::*)(float, float)>(&Node::SetPosition2D))
        // [Method] void SetRotation(const Quaternion& rotation)
        .addFunction("SetRotation", &Node::SetRotation)
        // [Method] void SetRotation2D(float rotation)
        .addFunction("SetRotation2D", &Node::SetRotation2D)
        // [Method] void SetDirection(const Vector3& direction)
        .addFunction("SetDirection", &Node::SetDirection)

        .addOverloadedFunctions("SetScale",
            // [Method] void SetScale(float scale)
            static_cast<void(Node::*)(float)>(&Node::SetScale),
            // [Method] void SetScale(const Vector3& scale)
            static_cast<void(Node::*)(const Vector3&)>(&Node::SetScale))
        .addOverloadedFunctions("SetScale2D",
            // [Method] void SetScale2D(const Vector2& scale)
            static_cast<void(Node::*)(const Vector2&)>(&Node::SetScale2D),
            // [Method] void SetScale2D(float x, float y)
            static_cast<void(Node::*)(float, float)>(&Node::SetScale2D))

        .addOverloadedFunctions("SetTransform",
            // [Method] void SetTransform(const Vector3& position, const Quaternion& rotation)
            static_cast<void(Node::*)(const Vector3&, const Quaternion&)>(&Node::SetTransform),
            // [Method] void SetTransform(const Vector3& position, const Quaternion& rotation, float scale)
            static_cast<void(Node::*)(const Vector3&, const Quaternion&, float)>(&Node::SetTransform),
            // [Method] void SetTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
            static_cast<void(Node::*)(const Vector3&, const Quaternion&, const Vector3&)>(&Node::SetTransform))
        
        .addOverloadedFunctions("SetTransform2D",
            // [Method] void SetTransform2D(const Vector2& position, float rotation)
            static_cast<void(Node::*)(const Vector2&, float)>(&Node::SetTransform2D),
            // [Method] void SetTransform2D(const Vector2& position, float rotation, float scale)
            static_cast<void(Node::*)(const Vector2&, float, float)>(&Node::SetTransform2D),
            // [Method] void SetTransform2D(const Vector2& position, float rotation, const Vector2& scale)
            static_cast<void(Node::*)(const Vector2&, float, const Vector2&)>(&Node::SetTransform2D))

        // [Method] void SetWorldPosition(const Vector3& position)
        .addFunction("SetWorldPosition", &Node::SetWorldPosition)
        
        .addOverloadedFunctions("SetWorldPosition2D",
            // [Method] void SetWorldPosition2D(const Vector2& position)
            static_cast<void(Node::*)(const Vector2&)>(&Node::SetWorldPosition2D),
            // [Method] void SetWorldPosition2D(float x, float y)
            static_cast<void(Node::*)(float, float)>(&Node::SetWorldPosition2D))

        // [Method] void SetWorldRotation(const Quaternion& rotation)
        .addFunction("SetWorldRotation", &Node::SetWorldRotation)
        // [Method] void SetWorldRotation2D(float rotation)
        .addFunction("SetWorldRotation2D", &Node::SetWorldRotation2D)

        // [Method] void SetWorldDirection(const Vector3& direction)
        .addFunction("SetWorldDirection", &Node::SetWorldDirection)

        .addOverloadedFunctions("SetWorldScale",
            // [Method] void SetWorldScale(float scale)
            static_cast<void(Node::*)(float)>(&Node::SetWorldScale),
            // [Method] void SetWorldScale(const Vector3& scale)
            static_cast<void(Node::*)(const Vector3&)>(&Node::SetWorldScale))

        .addOverloadedFunctions("SetWorldScale2D",
            // [Method] void SetWorldScale2D(const Vector2& scale)
            static_cast<void(Node::*)(const Vector2&)>(&Node::SetWorldScale2D),
            // [Method] void SetWorldScale2D(float x, float y)
            static_cast<void(Node::*)(float, float)>(&Node::SetWorldScale2D))

        .addOverloadedFunctions("SetWorldTransform",
            // [Method] void SetWorldTransform(const Vector3& position, const Quaternion& rotation)
            static_cast<void(Node::*)(const Vector3&, const Quaternion&)>(&Node::SetWorldTransform),
            // [Method] void SetWorldTransform(const Vector3& position, const Quaternion& rotation, float scale)
            static_cast<void(Node::*)(const Vector3&, const Quaternion&, float)>(&Node::SetWorldTransform),
            // [Method] void SetWorldTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
            static_cast<void(Node::*)(const Vector3&, const Quaternion&, const Vector3&)>(&Node::SetWorldTransform))

        .addOverloadedFunctions("SetWorldTransform2D",
            // [Method] void SetWorldTransform2D(const Vector2& position, float rotation)
            static_cast<void(Node::*)(const Vector2&, float)>(&Node::SetWorldTransform2D),
            // [Method] void SetWorldTransform2D(const Vector2& position, float rotation, float scale)
            static_cast<void(Node::*)(const Vector2&, float, float)>(&Node::SetWorldTransform2D),
            // [Method] void SetWorldTransform2D(const Vector2& position, float rotation, const Vector2& scale)
            static_cast<void(Node::*)(const Vector2&, float, const Vector2&)>(&Node::SetWorldTransform2D))

        // [Method] void Translate(const Vector3& delta, TransformSpace space = TS_LOCAL)
        .addFunction("Translate", NodeTranslate())
        // [Method] void Translate2D(const Vector2& delta, TransformSpace space = TS_LOCAL)
        .addFunction("Translate2D", NodeTranslate2D())

        // [Method] void Rotate(const Quaternion& delta, TransformSpace space = TS_LOCAL)
        .addFunction("Rotate", NodeRotate())
        // [Method] void Rotate2D(float delta, TransformSpace space = TS_LOCAL)
        .addFunction("Rotate2D", NodeRotate2D())

        // [Method] void RotateAround(const Vector3& point, const Quaternion& delta, TransformSpace space = TS_LOCAL)
        .addFunction("RotateAround", NodeRotateAround())
        // [Method] void RotateAround2D(const Vector2& point, float delta, TransformSpace space = TS_LOCAL)
        .addFunction("RotateAround2D", NodeRotateAround2D())

        // [Method] void Pitch(float angle, TransformSpace space = TS_LOCAL)
        .addFunction("Pitch", NodePitch())
        // [Method] void Yaw(float angle, TransformSpace space = TS_LOCAL)
        .addFunction("Yaw", NodeYaw())
        // [Method] void Roll(float angle, TransformSpace space = TS_LOCAL)
        .addFunction("Roll", NodeRoll())
        // [Method] bool LookAt(const Vector3& target, const Vector3& up = Vector3::UP, TransformSpace space = TS_WORLD)
        .addFunction("LookAt", NodeLookAt())

        .addOverloadedFunctions("Scale",
            // [Method] void Scale(float scale)
            static_cast<void(Node::*)(float)>(&Node::Scale),
            // [Method] void Scale(const Vector3& scale)
            static_cast<void(Node::*)(const Vector3&)>(&Node::Scale))

        // [Method] void Scale2D(const Vector2& scale)
        .addFunction("Scale2D", &Node::Scale2D)

        // [Method] void SetEnabled(bool enable)
        .addFunction("SetEnabled", static_cast<void(Node::*)(bool)>(&Node::SetEnabled))
        // [Method] void SetDeepEnabled(bool enable)
        .addFunction("SetDeepEnabled", &Node::SetDeepEnabled)
        // [Method] void ResetDeepEnabled()
        .addFunction("ResetDeepEnabled", &Node::ResetDeepEnabled)
        // [Method] void SetEnabledRecursive(bool enable)
        .addFunction("SetEnabledRecursive", &Node::SetEnabledRecursive)

        // [Method] void MarkDirty()
        .addFunction("MarkDirty", &Node::MarkDirty)

        // [Method] SharedPtr<Node> CreateChild(const String& name = String::EMPTY, CreateMode mode = REPLICATED, unsigned id = 0)
        .addStaticFunction("CreateChild", NodeCreateChildOverloads())

        // [Method] void AddChild(Node* node, unsigned index = M_MAX_UNSIGNED)
        .addFunction("AddChild", NodeAddChild())

        // [Method] void RemoveChild(Node* node)
        .addFunction("RemoveChild", static_cast<void(Node::*)(Node*)>(&Node::RemoveChild))
        // [Method] void RemoveAllChildren()
        .addFunction("RemoveAllChildren", &Node::RemoveAllChildren)
        // [Method] void RemoveChildren(bool removeReplicated, bool removeLocal, bool recursive)
        .addFunction("RemoveChildren", &Node::RemoveChildren)

        // [Method] SharedPtr<Component> CreateComponent(StringHash type, CreateMode mode = REPLICATED, unsigned id = 0)
        .addStaticFunction("CreateComponent", NodeCreateComponentOverloads())
        // [Method] SharedPtr<Component> GetOrCreateComponent(StringHash type, CreateMode mode = REPLICATED, unsigned id = 0)
        .addStaticFunction("GetOrCreateComponent", NodeGetOrCreateComponentOverloads())

        // [Method] LuaTable CreateScriptObject(const char* scriptObjectType)
        // [Method] LuaTable CreateScriptObject(const char* fileName, const char* scriptObjectType)
        .addOverloadedFunctions("CreateScriptObject", &NodeCreateScriptObject0, &NodeCreateScriptObject1)

        // [Method] LuaTable GetScriptObject()
        .addStaticFunction("GetScriptObject", &NodeGetScriptObject)

        .addOverloadedFunctions("CloneComponent", 
            // [Method] SharedPtr<Component> CloneComponent(Component* component, unsigned id = 0)
            NodeCloneComponentOverloads0(), 
            // [Method] SharedPtr<Component> CloneComponent(Component* component, CreateMode mode, unsigned id = 0)
            NodeCloneComponentOverloads1())

        .addOverloadedFunctions("RemoveComponent",
            // [Method] void RemoveComponent(Component* component)
            static_cast<void(Node::*)(Component*)>(&Node::RemoveComponent),
			// [Method] void RemoveComponent(StringHash type)
            static_cast<void(Node::*)(StringHash)>(&Node::RemoveComponent))

        .addOverloadedFunctions("RemoveComponents",
            // [Method] void RemoveComponents(bool removeReplicated, bool removeLocal)
            static_cast<void(Node::*)(bool, bool)>(&Node::RemoveComponents),
			// [Method] void RemoveComponents(StringHash type)
            static_cast<void(Node::*)(StringHash)>(&Node::RemoveComponents))

        // [Method] void RemoveAllComponents()
        .addFunction("RemoveAllComponents", &Node::RemoveAllComponents)
        // [Method] void ReorderComponent(Component* component, unsigned index)
        .addFunction("ReorderComponent", &Node::ReorderComponent)

        // [Method] SharedPtr<Node> Clone()
        .addStaticFunction("Clone", NodeCloneOverloads())

        // [Method] void Remove()
        .addFunction("Remove", &Node::Remove)
        // [Method] void SetParent(Node* parent)
        .addFunction("SetParent", &Node::SetParent)
        // [Method] void SetVar(StringHash key, const Variant& value)
        .addFunction("SetVar", &Node::SetVar)
        // [Method] void AddListener(Component* component)
        .addFunction("AddListener", &Node::AddListener)
        // [Method] void RemoveListener(Component* component)
        .addFunction("RemoveListener", &Node::RemoveListener)

        // [Method] unsigned GetID() const
        .addFunction("GetID", &Node::GetID)
        // [Method] const String& GetName() const
        .addFunction("GetName", &Node::GetName)
        // [Method] StringHash GetNameHash() const
        .addFunction("GetNameHash", &Node::GetNameHash)
        // [Method] const StringVector& GetTags() const
        .addFunction("GetTags", &Node::GetTags)
        // [Method] bool HasTag(const String& tag) const
        .addFunction("HasTag", &Node::HasTag)

        // [Method] Node* GetParent() const
        .addFunction("GetParent", &Node::GetParent)
        // [Method] Scene* GetScene() const
        .addFunction("GetScene", &Node::GetScene)
        // [Method] bool IsEnabled() const
        .addFunction("IsEnabled", &Node::IsEnabled)
        // [Method] bool IsEnabledSelf() const
        .addFunction("IsEnabledSelf", &Node::IsEnabledSelf)

        // [Method] const Vector3& GetPosition() const
        .addFunction("GetPosition", &Node::GetPosition)
        // [Method] Vector2 GetPosition2D() const
        .addFunction("GetPosition2D", &Node::GetPosition2D)
        // [Method] const Quaternion& GetRotation() const
        .addFunction("GetRotation", &Node::GetRotation)
        // [Method] float GetRotation2D() const
        .addFunction("GetRotation2D", &Node::GetRotation2D)
        // [Method] Vector3 GetDirection() const
        .addFunction("GetDirection", &Node::GetDirection)

        // [Method] Vector3 GetUp() const
        .addFunction("GetUp", &Node::GetUp)
        // [Method] Vector3 GetRight() const
        .addFunction("GetRight", &Node::GetRight)
        // [Method] const Vector3& GetScale() const
        .addFunction("GetScale", &Node::GetScale)
        // [Method] Vector2 GetScale2D() const
        .addFunction("GetScale2D", &Node::GetScale2D)
        // [Method] Matrix3x4 GetTransform() const
        .addFunction("GetTransform", &Node::GetTransform)

        // [Method] Vector3 GetWorldPosition() const
        .addFunction("GetWorldPosition", &Node::GetWorldPosition)
        // [Method] Vector2 GetWorldPosition2D() const
        .addFunction("GetWorldPosition2D", &Node::GetWorldPosition2D)
        // [Method] Quaternion GetWorldRotation() const
        .addFunction("GetWorldRotation", &Node::GetWorldRotation)
        // [Method] float GetWorldRotation2D() const
        .addFunction("GetWorldRotation2D", &Node::GetWorldRotation2D)
        // [Method] Vector3 GetWorldDirection() const
        .addFunction("GetWorldDirection", &Node::GetWorldDirection)

        // [Method] Vector3 GetWorldUp() const
        .addFunction("GetWorldUp", &Node::GetWorldUp)
        // [Method] Vector3 GetWorldRight() const
        .addFunction("GetWorldRight", &Node::GetWorldRight)
        // [Method] Vector3 GetWorldScale() const
        .addFunction("GetWorldScale", &Node::GetWorldScale)
        // [Method] Vector2 GetWorldScale2D() const
        .addFunction("GetWorldScale2D", &Node::GetWorldScale2D)
        // [Method] const Matrix3x4& GetWorldTransform() const
        .addFunction("GetWorldTransform", &Node::GetWorldTransform)

        .addOverloadedFunctions("LocalToWorld",
            // [Method] Vector3 LocalToWorld(const Vector3& position) const
            static_cast<Vector3(Node::*)(const Vector3&) const>(&Node::LocalToWorld),
            // [Method] Vector3 LocalToWorld(const Vector4& vector) const
            static_cast<Vector3(Node::*)(const Vector4&) const>(&Node::LocalToWorld))

        // [Method] Vector2 LocalToWorld2D(const Vector2& vector) const
        .addFunction("LocalToWorld2D", &Node::LocalToWorld2D)

        .addOverloadedFunctions("WorldToLocal",
            // [Method] Vector3 WorldToLocal(const Vector3& position) const
            static_cast<Vector3(Node::*)(const Vector3&) const>(&Node::WorldToLocal),
            // [Method] Vector3 WorldToLocal(const Vector4& vector) const
            static_cast<Vector3(Node::*)(const Vector4&) const>(&Node::WorldToLocal))

        // [Method] Vector2 WorldToLocal2D(const Vector2& vector) const
        .addFunction("WorldToLocal2D", &Node::WorldToLocal2D)

        // [Method] bool IsDirty() const
        .addFunction("IsDirty", &Node::IsDirty)

        // [Method] unsigned GetNumChildren(bool recursive = false) const
        .addFunction("GetNumChildren", NodeGetNumChildren())

        // [Method] PODVector<Node*> GetChildren(bool recursive = false) const
        .addStaticFunction("GetChildren", NodeGetChildrenOverloads())
        // [Method] PODVector<Node*> GetChildrenWithComponent(StringHash type, bool recursive = false) const
        .addStaticFunction("GetChildrenWithComponent", NodeGetChildrenWithComponentOverloads())
        // [Method] PODVector<Node*> GetChildrenWithTag(const String& tag, bool recursive = false) const
        .addStaticFunction("GetChildrenWithTag", NodeGetChildrenWithTagOverloads())

        .addOverloadedFunctions("GetChild",
            // [Method] Node* GetChild(unsigned index) const
            static_cast<Node*(Node::*)(unsigned) const>(&Node::GetChild),
            // [Method] Node* GetChild(const String& name, bool recursive = false) const
            NodeGetChild())

        // [Method] unsigned GetNumComponents() const
        .addFunction("GetNumComponents", &Node::GetNumComponents)
        // [Method] unsigned GetNumNetworkComponents() const
        .addFunction("GetNumNetworkComponents", &Node::GetNumNetworkComponents)

        .addOverloadedFunctions("GetComponents",
            // [Method] const Vector<SharedPtr<Component> >& GetComponents() const
            static_cast<const Vector<SharedPtr<Component> >&(Node::*)() const>(&Node::GetComponents),
            // [Method] PODVector<Component*> GetComponents(const Node* self, StringHash type, bool recursive = false)
            NodeGetComponentsOverloads())

        // [Method] SharedPtr<Component> GetComponent(StringHash type, bool recursive = false)
        .addStaticFunction("GetComponent", NodeGetComponentOverloads())
        // [Method] SharedPtr<Component> GetParentComponent(StringHash type, bool fullTraversal = false) const
        .addStaticFunction("GetParentComponent", NodeGetParentComponentOverloads())

        .addFunction("HasComponent", 
            // [Method] bool HasComponent(StringHash type) const
			static_cast<bool(Node::*)(StringHash)const>(&Node::HasComponent))

        // [Method] const Variant& GetVar(StringHash key) const
        .addFunction("GetVar", &Node::GetVar)
        // [Method] const VariantMap& GetVars() const
        .addFunction("GetVars", &Node::GetVars)

        // [Property(ReadOnly)] unsigned id
        .addProperty("id", &Node::GetID)
        // [Property] const String& name
        .addProperty("name", &Node::GetName, &Node::SetName)
        // [Property(ReadOnly)] StringHash nameHash
        .addProperty("nameHash", &Node::GetNameHash)
        // [Property] const StringVector& tags
        .addProperty("tags", &Node::GetTags, &Node::SetTags)

        // [Property] Node* parent
        .addProperty("parent", &Node::GetParent, &Node::SetParent)

        // [Property(ReadOnly)] Scene* scene
        .addProperty("scene", &Node::GetScene)
        // [Property] bool enabled
        .addProperty("enabled", &Node::IsEnabled, static_cast<void(Node::*)(bool)>(&Node::SetEnabled))
        // [Property(ReadOnly)] bool enabledSelf
        .addProperty("enabledSelf", &Node::IsEnabledSelf)

        // .addProperty("owner", &Node::GetOwner, &Node::SetOwner)
        // [Property] const Vector3& position
        .addProperty("position", &Node::GetPosition, &Node::SetPosition)
        // [Property] Vector2 position2D
        .addProperty("position2D", &Node::GetPosition2D, static_cast<void(Node::*)(const Vector2&)>(&Node::SetPosition2D))
        // [Property] const Quaternion& rotation
        .addProperty("rotation", &Node::GetRotation, &Node::SetRotation)
        // [Property] float rotation2D
        .addProperty("rotation2D", &Node::GetRotation2D, &Node::SetRotation2D)
        // [Property] Vector3 direction
        .addProperty("direction", &Node::GetDirection, &Node::SetDirection)
        // [Property(ReadOnly)] Vector3 up
        .addProperty("up", &Node::GetUp)
        // [Property(ReadOnly)] Vector3 right
        .addProperty("right", &Node::GetRight)
        // [Property] const Vector3& scale
        .addProperty("scale", &Node::GetScale, static_cast<void(Node::*)(const Vector3&)>(&Node::SetScale))
        // [Property] Vector2 scale2D
        .addProperty("scale2D", &Node::GetScale2D, static_cast<void(Node::*)(const Vector2&)>(&Node::SetScale2D))
        // [Property(ReadOnly)] Matrix3x4 transform
        .addProperty("transform", &Node::GetTransform)
        // [Property] Vector3 worldPosition
        .addProperty("worldPosition", &Node::GetWorldPosition, &Node::SetWorldPosition)
        // [Property] Vector2 worldPosition2D
        .addProperty("worldPosition2D", &Node::GetWorldPosition2D, static_cast<void(Node::*)(const Vector2&)>(&Node::SetWorldPosition2D))
        // [Property] Quaternion worldRotation
        .addProperty("worldRotation", &Node::GetWorldRotation, &Node::SetWorldRotation)
        // [Property] float worldRotation2D
        .addProperty("worldRotation2D", &Node::GetWorldRotation2D, &Node::SetWorldRotation2D)
        // [Property] Vector3 worldDirection
        .addProperty("worldDirection", &Node::GetWorldDirection, &Node::SetWorldDirection)
        // [Property(ReadOnly)] Vector3 worldUp
        .addProperty("worldUp", &Node::GetWorldUp)
        // [Property(ReadOnly)] Vector3 worldRight
        .addProperty("worldRight", &Node::GetWorldRight)
        // [Property(ReadOnly)] Vector3 worldScale
        .addProperty("worldScale", &Node::GetWorldScale)
        // [Property(ReadOnly)] Vector2 worldScale2D
        .addProperty("worldScale2D", &Node::GetWorldScale2D)
        // [Property(ReadOnly)] const Matrix3x4& worldTransform
        .addProperty("worldTransform", &Node::GetWorldTransform)
        // [Property(ReadOnly)] bool dirty
        .addProperty("dirty", &Node::IsDirty)
        // [Property(ReadOnly)] unsigned numComponents
        .addProperty("numComponents", &Node::GetNumComponents)
        // [Property(ReadOnly)] unsigned numNetworkComponents
        .addProperty("numNetworkComponents", &Node::GetNumNetworkComponents)
        );
}
}

