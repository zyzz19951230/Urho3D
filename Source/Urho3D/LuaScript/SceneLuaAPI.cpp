// #include "../Scene/Animatable.h"
// #include "../Scene/AnimationDefs.h"
// #include "../Scene/Component.h"
// #include "../Scene/LogicComponent.h"
// #include "../Scene/Node.h"
// #include "../Scene/ObjectAnimation.h"
// #include "../Scene/ReplicationState.h"
// #include "../Scene/Scene.h"
// #include "../Scene/SceneEvents.h"
// #include "../Scene/SceneResolver.h"
// #include "../Scene/Serializable.h"
// #include "../Scene/SmoothedTransform.h"
// #include "../Scene/SplinePath.h"
// #include "../Scene/UnknownComponent.h"
// #include "../Scene/ValueAnimation.h"
// #include "../Scene/ValueAnimationInfo.h"

// #include "../LuaScript/LuaScriptUtils.h"

// #include <kaguya.hpp>

// namespace Urho3D
// {

// static void RegisterAnimatable(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KAttributeAnimationInfo"].setClass(UserdataMetatable<AttributeAnimationInfo, ValueAnimationInfo>()
//         .setConstructors<AttributeAnimationInfo(Animatable*, const AttributeInfo&, ValueAnimation*, WrapMode, float),
//             AttributeAnimationInfo(const AttributeAnimationInfo&)>()

//         .addFunction("GetAttributeInfo", &AttributeAnimationInfo::GetAttributeInfo)

//         .addProperty("attributeInfo", &AttributeAnimationInfo::GetAttributeInfo)
//     );
//     lua["KAnimatable"].setClass(UserdataMetatable<Animatable, Serializable>(false)
//         .addStaticFunction("new", &KCreateObject<Animatable>)
//         .addStaticFunction("__gc", &KReleaseObject<Animatable>)

//         .addFunction("GetType", &Animatable::GetType)
//         .addFunction("GetTypeName", &Animatable::GetTypeName)
//         .addFunction("GetTypeInfo", &Animatable::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Animatable::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Animatable::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Animatable::GetTypeInfoStatic)
//         .addFunction("LoadXML", &Animatable::LoadXML)
//         .addFunction("SaveXML", &Animatable::SaveXML)
//         .addFunction("LoadJSON", &Animatable::LoadJSON)
//         .addFunction("SaveJSON", &Animatable::SaveJSON)
//         .addFunction("SetAnimationEnabled", &Animatable::SetAnimationEnabled)
//         .addFunction("SetAnimationTime", &Animatable::SetAnimationTime)
//         .addFunction("SetObjectAnimation", &Animatable::SetObjectAnimation)
//         .addFunction("SetAttributeAnimation", &Animatable::SetAttributeAnimation)
//         .addFunction("SetAttributeAnimationWrapMode", &Animatable::SetAttributeAnimationWrapMode)
//         .addFunction("SetAttributeAnimationSpeed", &Animatable::SetAttributeAnimationSpeed)
//         .addFunction("SetAttributeAnimationTime", &Animatable::SetAttributeAnimationTime)
//         .addFunction("RemoveObjectAnimation", &Animatable::RemoveObjectAnimation)
//         .addFunction("RemoveAttributeAnimation", &Animatable::RemoveAttributeAnimation)
//         .addFunction("GetAnimationEnabled", &Animatable::GetAnimationEnabled)
//         .addFunction("GetObjectAnimation", &Animatable::GetObjectAnimation)
//         .addFunction("GetAttributeAnimation", &Animatable::GetAttributeAnimation)
//         .addFunction("GetAttributeAnimationWrapMode", &Animatable::GetAttributeAnimationWrapMode)
//         .addFunction("GetAttributeAnimationSpeed", &Animatable::GetAttributeAnimationSpeed)
//         .addFunction("GetAttributeAnimationTime", &Animatable::GetAttributeAnimationTime)

//         .addProperty("type", &Animatable::GetType)
//         .addProperty("typeName", &Animatable::GetTypeName)
//         .addProperty("typeInfo", &Animatable::GetTypeInfo)
//         .addProperty("animationEnabled", &Animatable::GetAnimationEnabled, &Animatable::SetAnimationEnabled)
//         .addProperty("objectAnimation", &Animatable::GetObjectAnimation, &Animatable::SetObjectAnimation)
//         .addProperty("animationTime", &Animatable::SetAnimationTime)
//     );
// }

// static void RegisterAnimationDefs(kaguya::State& lua)
// {
//     using namespace kaguya;

//     // enum WrapMode;
//     lua["KWM_LOOP"] = WM_LOOP;
//     lua["KWM_ONCE"] = WM_ONCE;
//     lua["KWM_CLAMP"] = WM_CLAMP;

// }

// static void RegisterComponent(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KComponent"].setClass(UserdataMetatable<Component, Animatable>(false)
//         .addStaticFunction("new", &KCreateObject<Component>)
//         .addStaticFunction("__gc", &KReleaseObject<Component>)

//         .addFunction("GetType", &Component::GetType)
//         .addFunction("GetTypeName", &Component::GetTypeName)
//         .addFunction("GetTypeInfo", &Component::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Component::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Component::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Component::GetTypeInfoStatic)
//         .addFunction("OnSetEnabled", &Component::OnSetEnabled)
//         .addFunction("Save", &Component::Save)
//         .addFunction("SaveXML", &Component::SaveXML)
//         .addFunction("SaveJSON", &Component::SaveJSON)
//         .addFunction("MarkNetworkUpdate", &Component::MarkNetworkUpdate)
//         .addFunction("GetDependencyNodes", &Component::GetDependencyNodes)
//         .addFunction("DrawDebugGeometry", &Component::DrawDebugGeometry)
//         .addFunction("SetEnabled", &Component::SetEnabled)
//         .addFunction("Remove", &Component::Remove)
//         .addFunction("GetID", &Component::GetID)
//         .addFunction("GetNode", &Component::GetNode)
//         .addFunction("GetScene", &Component::GetScene)
//         .addFunction("IsEnabled", &Component::IsEnabled)
//         .addFunction("IsEnabledEffective", &Component::IsEnabledEffective)
//         .addFunction("GetComponent", &Component::GetComponent)
//         .addFunction("GetComponents", &Component::GetComponents)
//         .addFunction("AddReplicationState", &Component::AddReplicationState)
//         .addFunction("PrepareNetworkUpdate", &Component::PrepareNetworkUpdate)
//         .addFunction("CleanupConnection", &Component::CleanupConnection)

//         .addProperty("type", &Component::GetType)
//         .addProperty("typeName", &Component::GetTypeName)
//         .addProperty("typeInfo", &Component::GetTypeInfo)
//         .addProperty("iD", &Component::GetID)
//         .addProperty("node", &Component::GetNode)
//         .addProperty("scene", &Component::GetScene)
//         .addProperty("enabled", &Component::IsEnabled, &Component::SetEnabled)
//         .addProperty("enabledEffective", &Component::IsEnabledEffective)
//     );
//     // template <class T> T* Component::GetComponent();
//     // template <class T> void Component::GetComponents(PODVector<T*>& dest);
// }

// static void RegisterLogicComponent(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KUSE_UPDATE"] = USE_UPDATE;
//     lua["KUSE_POSTUPDATE"] = USE_POSTUPDATE;
//     lua["KUSE_FIXEDUPDATE"] = USE_FIXEDUPDATE;
//     lua["KUSE_FIXEDPOSTUPDATE"] = USE_FIXEDPOSTUPDATE;
//     lua["KLogicComponent"].setClass(UserdataMetatable<LogicComponent, Component>(false)
//         .addStaticFunction("new", &KCreateObject<LogicComponent>)
//         .addStaticFunction("__gc", &KReleaseObject<LogicComponent>)

//         .addFunction("GetType", &LogicComponent::GetType)
//         .addFunction("GetTypeName", &LogicComponent::GetTypeName)
//         .addFunction("GetTypeInfo", &LogicComponent::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &LogicComponent::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &LogicComponent::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &LogicComponent::GetTypeInfoStatic)
//         .addFunction("OnSetEnabled", &LogicComponent::OnSetEnabled)
//         .addFunction("Start", &LogicComponent::Start)
//         .addFunction("DelayedStart", &LogicComponent::DelayedStart)
//         .addFunction("Stop", &LogicComponent::Stop)
//         .addFunction("Update", &LogicComponent::Update)
//         .addFunction("PostUpdate", &LogicComponent::PostUpdate)
//         .addFunction("FixedUpdate", &LogicComponent::FixedUpdate)
//         .addFunction("FixedPostUpdate", &LogicComponent::FixedPostUpdate)
//         .addFunction("SetUpdateEventMask", &LogicComponent::SetUpdateEventMask)
//         .addFunction("GetUpdateEventMask", &LogicComponent::GetUpdateEventMask)
//         .addFunction("IsDelayedStartCalled", &LogicComponent::IsDelayedStartCalled)

//         .addProperty("type", &LogicComponent::GetType)
//         .addProperty("typeName", &LogicComponent::GetTypeName)
//         .addProperty("typeInfo", &LogicComponent::GetTypeInfo)
//         .addProperty("updateEventMask", &LogicComponent::GetUpdateEventMask, &LogicComponent::SetUpdateEventMask)
//         .addProperty("delayedStartCalled", &LogicComponent::IsDelayedStartCalled)
//     );
// }

// static void RegisterNode(kaguya::State& lua)
// {
//     using namespace kaguya;

//     // enum CreateMode;
//     lua["KREPLICATED"] = REPLICATED;
//     lua["KLOCAL"] = LOCAL;

//     // enum TransformSpace;
//     lua["KTS_LOCAL"] = TS_LOCAL;
//     lua["KTS_PARENT"] = TS_PARENT;
//     lua["KTS_WORLD"] = TS_WORLD;

//     lua["KNode"].setClass(UserdataMetatable<Node, Animatable>(false)
//         .addStaticFunction("new", &KCreateObject<Node>)
//         .addStaticFunction("__gc", &KReleaseObject<Node>)

//         .addFunction("GetType", &Node::GetType)
//         .addFunction("GetTypeName", &Node::GetTypeName)
//         .addFunction("GetTypeInfo", &Node::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Node::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Node::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Node::GetTypeInfoStatic)

//         .addOverloadedFunctions("Load",
//             static_cast<bool(Node::*)(Deserializer&, bool)>(&Node::Load),
//             static_cast<bool(Node::*)(Deserializer&, SceneResolver&, bool, bool, CreateMode)>(&Node::Load))


//         .addOverloadedFunctions("LoadXML",
//             static_cast<bool(Node::*)(const XMLElement&, bool)>(&Node::LoadXML),
//             static_cast<bool(Node::*)(const XMLElement&, SceneResolver&, bool, bool, CreateMode)>(&Node::LoadXML))


//         .addOverloadedFunctions("LoadJSON",
//             static_cast<bool(Node::*)(const JSONValue&, bool)>(&Node::LoadJSON),
//             static_cast<bool(Node::*)(const JSONValue&, SceneResolver&, bool, bool, CreateMode)>(&Node::LoadJSON))

//         .addFunction("Save", &Node::Save)

//         .addOverloadedFunctions("SaveXML",
//             static_cast<bool(Node::*)(XMLElement&) const>(&Node::SaveXML),
//             static_cast<bool(Node::*)(Serializer&, const String&) const>(&Node::SaveXML))


//         .addOverloadedFunctions("SaveJSON",
//             static_cast<bool(Node::*)(JSONValue&) const>(&Node::SaveJSON),
//             static_cast<bool(Node::*)(Serializer&, const String&) const>(&Node::SaveJSON))

//         .addFunction("ApplyAttributes", &Node::ApplyAttributes)
//         .addFunction("SaveDefaultAttributes", &Node::SaveDefaultAttributes)
//         .addFunction("MarkNetworkUpdate", &Node::MarkNetworkUpdate)
//         .addFunction("AddReplicationState", &Node::AddReplicationState)
//         .addFunction("SetName", &Node::SetName)
//         .addFunction("SetTags", &Node::SetTags)
//         .addFunction("AddTag", &Node::AddTag)

//         .addOverloadedFunctions("AddTags",
//             static_cast<void(Node::*)(const String&, char)>(&Node::AddTags),
//             static_cast<void(Node::*)(const StringVector&)>(&Node::AddTags))

//         .addFunction("RemoveTag", &Node::RemoveTag)
//         .addFunction("RemoveAllTags", &Node::RemoveAllTags)
//         .addFunction("SetPosition", &Node::SetPosition)

//         .addOverloadedFunctions("SetPosition2D",
//             static_cast<void(Node::*)(const Vector2&)>(&Node::SetPosition2D),
//             static_cast<void(Node::*)(float, float)>(&Node::SetPosition2D))

//         .addFunction("SetRotation", &Node::SetRotation)
//         .addFunction("SetRotation2D", &Node::SetRotation2D)
//         .addFunction("SetDirection", &Node::SetDirection)

//         .addOverloadedFunctions("SetScale",
//             static_cast<void(Node::*)(float)>(&Node::SetScale),
//             static_cast<void(Node::*)(const Vector3&)>(&Node::SetScale))


//         .addOverloadedFunctions("SetScale2D",
//             static_cast<void(Node::*)(const Vector2&)>(&Node::SetScale2D),
//             static_cast<void(Node::*)(float, float)>(&Node::SetScale2D))


//         .addOverloadedFunctions("SetTransform",
//             static_cast<void(Node::*)(const Vector3&, const Quaternion&)>(&Node::SetTransform),
//             static_cast<void(Node::*)(const Vector3&, const Quaternion&, float)>(&Node::SetTransform),
//             static_cast<void(Node::*)(const Vector3&, const Quaternion&, const Vector3&)>(&Node::SetTransform))


//         .addOverloadedFunctions("SetTransform2D",
//             static_cast<void(Node::*)(const Vector2&, float)>(&Node::SetTransform2D),
//             static_cast<void(Node::*)(const Vector2&, float, float)>(&Node::SetTransform2D),
//             static_cast<void(Node::*)(const Vector2&, float, const Vector2&)>(&Node::SetTransform2D))

//         .addFunction("SetWorldPosition", &Node::SetWorldPosition)

//         .addOverloadedFunctions("SetWorldPosition2D",
//             static_cast<void(Node::*)(const Vector2&)>(&Node::SetWorldPosition2D),
//             static_cast<void(Node::*)(float, float)>(&Node::SetWorldPosition2D))

//         .addFunction("SetWorldRotation", &Node::SetWorldRotation)
//         .addFunction("SetWorldRotation2D", &Node::SetWorldRotation2D)
//         .addFunction("SetWorldDirection", &Node::SetWorldDirection)

//         .addOverloadedFunctions("SetWorldScale",
//             static_cast<void(Node::*)(float)>(&Node::SetWorldScale),
//             static_cast<void(Node::*)(const Vector3&)>(&Node::SetWorldScale))


//         .addOverloadedFunctions("SetWorldScale2D",
//             static_cast<void(Node::*)(const Vector2&)>(&Node::SetWorldScale2D),
//             static_cast<void(Node::*)(float, float)>(&Node::SetWorldScale2D))


//         .addOverloadedFunctions("SetWorldTransform",
//             static_cast<void(Node::*)(const Vector3&, const Quaternion&)>(&Node::SetWorldTransform),
//             static_cast<void(Node::*)(const Vector3&, const Quaternion&, float)>(&Node::SetWorldTransform),
//             static_cast<void(Node::*)(const Vector3&, const Quaternion&, const Vector3&)>(&Node::SetWorldTransform))


//         .addOverloadedFunctions("SetWorldTransform2D",
//             static_cast<void(Node::*)(const Vector2&, float)>(&Node::SetWorldTransform2D),
//             static_cast<void(Node::*)(const Vector2&, float, float)>(&Node::SetWorldTransform2D),
//             static_cast<void(Node::*)(const Vector2&, float, const Vector2&)>(&Node::SetWorldTransform2D))

//         .addFunction("Translate", &Node::Translate)
//         .addFunction("Translate2D", &Node::Translate2D)
//         .addFunction("Rotate", &Node::Rotate)
//         .addFunction("Rotate2D", &Node::Rotate2D)
//         .addFunction("RotateAround", &Node::RotateAround)
//         .addFunction("RotateAround2D", &Node::RotateAround2D)
//         .addFunction("Pitch", &Node::Pitch)
//         .addFunction("Yaw", &Node::Yaw)
//         .addFunction("Roll", &Node::Roll)
//         .addFunction("LookAt", &Node::LookAt)

//         .addOverloadedFunctions("Scale",
//             static_cast<void(Node::*)(float)>(&Node::Scale),
//             static_cast<void(Node::*)(const Vector3&)>(&Node::Scale))

//         .addFunction("Scale2D", &Node::Scale2D)

//         .addOverloadedFunctions("SetEnabled",
//             static_cast<void(Node::*)(bool)>(&Node::SetEnabled))

//         .addFunction("SetDeepEnabled", &Node::SetDeepEnabled)
//         .addFunction("ResetDeepEnabled", &Node::ResetDeepEnabled)
//         .addFunction("SetEnabledRecursive", &Node::SetEnabledRecursive)
//         .addFunction("SetOwner", &Node::SetOwner)
//         .addFunction("MarkDirty", &Node::MarkDirty)

//         .addOverloadedFunctions("CreateChild",
//             static_cast<Node*(Node::*)(const String&, CreateMode, unsigned int)>(&Node::CreateChild),
//             static_cast<Node*(Node::*)(unsigned int, CreateMode)>(&Node::CreateChild))

//         .addFunction("AddChild", &Node::AddChild)
//         .addFunction("RemoveChild", &Node::RemoveChild)
//         .addFunction("RemoveAllChildren", &Node::RemoveAllChildren)
//         .addFunction("RemoveChildren", &Node::RemoveChildren)
//         .addFunction("CreateComponent", &Node::CreateComponent)
//         .addFunction("GetOrCreateComponent", &Node::GetOrCreateComponent)

//         .addOverloadedFunctions("CloneComponent",
//             static_cast<Component*(Node::*)(Component*, unsigned int)>(&Node::CloneComponent),
//             static_cast<Component*(Node::*)(Component*, CreateMode, unsigned int)>(&Node::CloneComponent))


//         .addOverloadedFunctions("RemoveComponent",
//             static_cast<void(Node::*)(Component*)>(&Node::RemoveComponent),
//             static_cast<void(Node::*)(StringHash)>(&Node::RemoveComponent))


//         .addOverloadedFunctions("RemoveComponents",
//             static_cast<void(Node::*)(bool, bool)>(&Node::RemoveComponents),
//             static_cast<void(Node::*)(StringHash)>(&Node::RemoveComponents))

//         .addFunction("RemoveAllComponents", &Node::RemoveAllComponents)
//         .addFunction("Clone", &Node::Clone)
//         .addFunction("Remove", &Node::Remove)
//         .addFunction("SetParent", &Node::SetParent)
//         .addFunction("SetVar", &Node::SetVar)
//         .addFunction("AddListener", &Node::AddListener)
//         .addFunction("RemoveListener", &Node::RemoveListener)
//         .addFunction("GetID", &Node::GetID)
//         .addFunction("GetName", &Node::GetName)
//         .addFunction("GetNameHash", &Node::GetNameHash)
//         .addFunction("GetTags", &Node::GetTags)
//         .addFunction("HasTag", &Node::HasTag)
//         .addFunction("GetParent", &Node::GetParent)
//         .addFunction("GetScene", &Node::GetScene)
//         .addFunction("IsEnabled", &Node::IsEnabled)
//         .addFunction("IsEnabledSelf", &Node::IsEnabledSelf)
//         .addFunction("GetOwner", &Node::GetOwner)
//         .addFunction("GetPosition", &Node::GetPosition)
//         .addFunction("GetPosition2D", &Node::GetPosition2D)
//         .addFunction("GetRotation", &Node::GetRotation)
//         .addFunction("GetRotation2D", &Node::GetRotation2D)
//         .addFunction("GetDirection", &Node::GetDirection)
//         .addFunction("GetUp", &Node::GetUp)
//         .addFunction("GetRight", &Node::GetRight)
//         .addFunction("GetScale", &Node::GetScale)
//         .addFunction("GetScale2D", &Node::GetScale2D)
//         .addFunction("GetTransform", &Node::GetTransform)
//         .addFunction("GetWorldPosition", &Node::GetWorldPosition)
//         .addFunction("GetWorldPosition2D", &Node::GetWorldPosition2D)
//         .addFunction("GetWorldRotation", &Node::GetWorldRotation)
//         .addFunction("GetWorldRotation2D", &Node::GetWorldRotation2D)
//         .addFunction("GetWorldDirection", &Node::GetWorldDirection)
//         .addFunction("GetWorldUp", &Node::GetWorldUp)
//         .addFunction("GetWorldRight", &Node::GetWorldRight)
//         .addFunction("GetWorldScale", &Node::GetWorldScale)
//         .addFunction("GetWorldScale2D", &Node::GetWorldScale2D)
//         .addFunction("GetWorldTransform", &Node::GetWorldTransform)

//         .addOverloadedFunctions("LocalToWorld",
//             static_cast<Vector3(Node::*)(const Vector3&) const>(&Node::LocalToWorld),
//             static_cast<Vector3(Node::*)(const Vector4&) const>(&Node::LocalToWorld))

//         .addFunction("LocalToWorld2D", &Node::LocalToWorld2D)

//         .addOverloadedFunctions("WorldToLocal",
//             static_cast<Vector3(Node::*)(const Vector3&) const>(&Node::WorldToLocal),
//             static_cast<Vector3(Node::*)(const Vector4&) const>(&Node::WorldToLocal))

//         .addFunction("WorldToLocal2D", &Node::WorldToLocal2D)
//         .addFunction("IsDirty", &Node::IsDirty)
//         .addFunction("GetNumChildren", &Node::GetNumChildren)

//         .addOverloadedFunctions("GetChildren",
//             static_cast<const Vector<SharedPtr<Node> >&(Node::*)() const>(&Node::GetChildren),
//             static_cast<void(Node::*)(PODVector<Node*>&, bool) const>(&Node::GetChildren))

//         .addFunction("GetChildrenWithComponent", &Node::GetChildrenWithComponent)
//         .addFunction("GetChildrenWithTag", &Node::GetChildrenWithTag)

//         .addOverloadedFunctions("GetChild",
//             static_cast<Node*(Node::*)(unsigned int) const>(&Node::GetChild),
//             static_cast<Node*(Node::*)(const String&, bool) const>(&Node::GetChild),
//             static_cast<Node*(Node::*)(const char*, bool) const>(&Node::GetChild),
//             static_cast<Node*(Node::*)(StringHash, bool) const>(&Node::GetChild))

//         .addFunction("GetNumComponents", &Node::GetNumComponents)
//         .addFunction("GetNumNetworkComponents", &Node::GetNumNetworkComponents)

//         .addOverloadedFunctions("GetComponents",
//             static_cast<const Vector<SharedPtr<Component> >&(Node::*)() const>(&Node::GetComponents),
//             static_cast<void(Node::*)(PODVector<Component*>&, StringHash, bool) const>(&Node::GetComponents))

//         .addFunction("GetComponent", &Node::GetComponent)
//         .addFunction("GetParentComponent", &Node::GetParentComponent)
//         .addFunction("HasComponent", &Node::HasComponent)
//         .addFunction("GetListeners", &Node::GetListeners)
//         .addFunction("GetVar", &Node::GetVar)
//         .addFunction("GetVars", &Node::GetVars)
//         .addFunction("SetID", &Node::SetID)
//         .addFunction("SetScene", &Node::SetScene)
//         .addFunction("ResetScene", &Node::ResetScene)
//         .addFunction("GetDependencyNodes", &Node::GetDependencyNodes)
//         .addFunction("PrepareNetworkUpdate", &Node::PrepareNetworkUpdate)
//         .addFunction("CleanupConnection", &Node::CleanupConnection)
//         .addFunction("MarkReplicationDirty", &Node::MarkReplicationDirty)
//         .addFunction("AddComponent", &Node::AddComponent)
//         .addFunction("GetNumPersistentChildren", &Node::GetNumPersistentChildren)
//         .addFunction("GetNumPersistentComponents", &Node::GetNumPersistentComponents)
//         .addFunction("SetPositionSilent", &Node::SetPositionSilent)
//         .addFunction("SetRotationSilent", &Node::SetRotationSilent)
//         .addFunction("SetScaleSilent", &Node::SetScaleSilent)
//         .addFunction("SetTransformSilent", &Node::SetTransformSilent)

//         .addProperty("type", &Node::GetType)
//         .addProperty("typeName", &Node::GetTypeName)
//         .addProperty("typeInfo", &Node::GetTypeInfo)
//         .addProperty("iD", &Node::GetID, &Node::SetID)
//         .addProperty("name", &Node::GetName, &Node::SetName)
//         .addProperty("nameHash", &Node::GetNameHash)
//         .addProperty("tags", &Node::GetTags, &Node::SetTags)
//         .addProperty("parent", &Node::GetParent, &Node::SetParent)
//         .addProperty("scene", &Node::GetScene, &Node::SetScene)
//         .addProperty("enabled", &Node::IsEnabled)
//         .addProperty("enabledSelf", &Node::IsEnabledSelf)
//         .addProperty("owner", &Node::GetOwner, &Node::SetOwner)
//         .addProperty("position", &Node::GetPosition, &Node::SetPosition)
//         .addProperty("position2D", &Node::GetPosition2D)
//         .addProperty("rotation", &Node::GetRotation, &Node::SetRotation)
//         .addProperty("rotation2D", &Node::GetRotation2D, &Node::SetRotation2D)
//         .addProperty("direction", &Node::GetDirection, &Node::SetDirection)
//         .addProperty("up", &Node::GetUp)
//         .addProperty("right", &Node::GetRight)
//         .addProperty("scale", &Node::GetScale)
//         .addProperty("scale2D", &Node::GetScale2D)
//         .addProperty("transform", &Node::GetTransform)
//         .addProperty("worldPosition", &Node::GetWorldPosition, &Node::SetWorldPosition)
//         .addProperty("worldPosition2D", &Node::GetWorldPosition2D)
//         .addProperty("worldRotation", &Node::GetWorldRotation, &Node::SetWorldRotation)
//         .addProperty("worldRotation2D", &Node::GetWorldRotation2D, &Node::SetWorldRotation2D)
//         .addProperty("worldDirection", &Node::GetWorldDirection, &Node::SetWorldDirection)
//         .addProperty("worldUp", &Node::GetWorldUp)
//         .addProperty("worldRight", &Node::GetWorldRight)
//         .addProperty("worldScale", &Node::GetWorldScale)
//         .addProperty("worldScale2D", &Node::GetWorldScale2D)
//         .addProperty("worldTransform", &Node::GetWorldTransform)
//         .addProperty("dirty", &Node::IsDirty)
//         .addProperty("numComponents", &Node::GetNumComponents)
//         .addProperty("numNetworkComponents", &Node::GetNumNetworkComponents)
//         .addProperty("listeners", &Node::GetListeners)
//         .addProperty("vars", &Node::GetVars)
//         .addProperty("dependencyNodes", &Node::GetDependencyNodes)
//         .addProperty("numPersistentChildren", &Node::GetNumPersistentChildren)
//         .addProperty("numPersistentComponents", &Node::GetNumPersistentComponents)
//         .addProperty("deepEnabled", &Node::SetDeepEnabled)
//         .addProperty("enabledRecursive", &Node::SetEnabledRecursive)
//         .addProperty("positionSilent", &Node::SetPositionSilent)
//         .addProperty("rotationSilent", &Node::SetRotationSilent)
//         .addProperty("scaleSilent", &Node::SetScaleSilent)
//     );
//     // template <class T> T* Node::CreateComponent(CreateMode mode, unsigned id);
//     // template <class T> T* Node::GetOrCreateComponent(CreateMode mode, unsigned id);
//     // template <class T> void Node::RemoveComponent();
//     // template <class T> void Node::RemoveComponents();
//     // template <class T> void Node::GetChildrenWithComponent(PODVector<Node*>& dest, bool recursive);
//     // template <class T> T* Node::GetComponent(bool recursive);
//     // template <class T> T* Node::GetParentComponent(bool fullTraversal);
//     // template <class T> void Node::GetComponents(PODVector<T*>& dest, bool recursive);
//     // template <class T> bool Node::HasComponent();
//     // template <class T> T* Node::GetDerivedComponent(bool recursive);
//     // template <class T> T* Node::GetParentDerivedComponent(bool fullTraversal);
//     // template <class T> void Node::GetDerivedComponents(PODVector<T*>& dest, bool recursive, bool clearVector);
// }

// static void RegisterObjectAnimation(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KObjectAnimation"].setClass(UserdataMetatable<ObjectAnimation, Resource>(false)
//         .addStaticFunction("new", &KCreateObject<ObjectAnimation>)
//         .addStaticFunction("__gc", &KReleaseObject<ObjectAnimation>)

//         .addFunction("GetType", &ObjectAnimation::GetType)
//         .addFunction("GetTypeName", &ObjectAnimation::GetTypeName)
//         .addFunction("GetTypeInfo", &ObjectAnimation::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &ObjectAnimation::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &ObjectAnimation::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &ObjectAnimation::GetTypeInfoStatic)
//         .addFunction("BeginLoad", &ObjectAnimation::BeginLoad)
//         .addFunction("Save", &ObjectAnimation::Save)
//         .addFunction("LoadXML", &ObjectAnimation::LoadXML)
//         .addFunction("SaveXML", &ObjectAnimation::SaveXML)
//         .addFunction("LoadJSON", &ObjectAnimation::LoadJSON)
//         .addFunction("SaveJSON", &ObjectAnimation::SaveJSON)
//         .addFunction("AddAttributeAnimation", &ObjectAnimation::AddAttributeAnimation)

//         .addOverloadedFunctions("RemoveAttributeAnimation",
//             static_cast<void(ObjectAnimation::*)(const String&)>(&ObjectAnimation::RemoveAttributeAnimation),
//             static_cast<void(ObjectAnimation::*)(ValueAnimation*)>(&ObjectAnimation::RemoveAttributeAnimation))

//         .addFunction("GetAttributeAnimation", &ObjectAnimation::GetAttributeAnimation)
//         .addFunction("GetAttributeAnimationWrapMode", &ObjectAnimation::GetAttributeAnimationWrapMode)
//         .addFunction("GetAttributeAnimationSpeed", &ObjectAnimation::GetAttributeAnimationSpeed)
//         .addFunction("GetAttributeAnimationInfos", &ObjectAnimation::GetAttributeAnimationInfos)
//         .addFunction("GetAttributeAnimationInfo", &ObjectAnimation::GetAttributeAnimationInfo)

//         .addProperty("type", &ObjectAnimation::GetType)
//         .addProperty("typeName", &ObjectAnimation::GetTypeName)
//         .addProperty("typeInfo", &ObjectAnimation::GetTypeInfo)
//         .addProperty("attributeAnimationInfos", &ObjectAnimation::GetAttributeAnimationInfos)
//     );
// }

// static void RegisterReplicationState(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KMAX_NETWORK_ATTRIBUTES"] = MAX_NETWORK_ATTRIBUTES;
//     lua["KDirtyBits"].setClass(UserdataMetatable<DirtyBits>()
//         .setConstructors<DirtyBits(),
//             DirtyBits(const DirtyBits&)>()

//         .addFunction("Set", &DirtyBits::Set)
//         .addFunction("Clear", &DirtyBits::Clear)
//         .addFunction("ClearAll", &DirtyBits::ClearAll)
//         .addFunction("IsSet", &DirtyBits::IsSet)
//         .addFunction("Count", &DirtyBits::Count)

//         .addProperty("", &DirtyBits::Set)
//         .addProperty("data", &DirtyBits::data_)
//         .addProperty("count", &DirtyBits::count_)
//     );
//     lua["KNetworkState"].setClass(UserdataMetatable<NetworkState>()
//         .setConstructors<NetworkState()>()

//         .addProperty("attributes", &NetworkState::attributes_)
//         .addProperty("currentValues", &NetworkState::currentValues_)
//         .addProperty("previousValues", &NetworkState::previousValues_)
//         .addProperty("replicationStates", &NetworkState::replicationStates_)
//         .addProperty("previousVars", &NetworkState::previousVars_)
//         .addProperty("interceptMask", &NetworkState::interceptMask_)
//     );
//     lua["KReplicationState"].setClass(UserdataMetatable<ReplicationState>()

//         .addProperty("connection", &ReplicationState::connection_)
//     );
//     lua["KComponentReplicationState"].setClass(UserdataMetatable<ComponentReplicationState, ReplicationState>()

//         .addProperty("nodeState", &ComponentReplicationState::nodeState_)
//         .addProperty("component", &ComponentReplicationState::component_)
//         .addProperty("dirtyAttributes", &ComponentReplicationState::dirtyAttributes_)
//     );
//     lua["KNodeReplicationState"].setClass(UserdataMetatable<NodeReplicationState, ReplicationState>()
//         .setConstructors<NodeReplicationState()>()

//         .addProperty("sceneState", &NodeReplicationState::sceneState_)
//         .addProperty("node", &NodeReplicationState::node_)
//         .addProperty("dirtyAttributes", &NodeReplicationState::dirtyAttributes_)
//         .addProperty("dirtyVars", &NodeReplicationState::dirtyVars_)
//         .addProperty("componentStates", &NodeReplicationState::componentStates_)
//         .addProperty("priorityAcc", &NodeReplicationState::priorityAcc_)
//         .addProperty("markedDirty", &NodeReplicationState::markedDirty_)
//     );
//     lua["KSceneReplicationState"].setClass(UserdataMetatable<SceneReplicationState, ReplicationState>()

//         .addFunction("Clear", &SceneReplicationState::Clear)
//         .addProperty("nodeStates", &SceneReplicationState::nodeStates_)
//         .addProperty("dirtyNodes", &SceneReplicationState::dirtyNodes_)
//     );
// }

// static void RegisterScene(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KFIRST_REPLICATED_ID"] = FIRST_REPLICATED_ID;
//     lua["KLAST_REPLICATED_ID"] = LAST_REPLICATED_ID;
//     lua["KFIRST_LOCAL_ID"] = FIRST_LOCAL_ID;
//     lua["KLAST_LOCAL_ID"] = LAST_LOCAL_ID;
//     // enum LoadMode;
//     lua["KLOAD_RESOURCES_ONLY"] = LOAD_RESOURCES_ONLY;
//     lua["KLOAD_SCENE"] = LOAD_SCENE;
//     lua["KLOAD_SCENE_AND_RESOURCES"] = LOAD_SCENE_AND_RESOURCES;

//     lua["KAsyncProgress"].setClass(UserdataMetatable<AsyncProgress>()

//         .addProperty("file", &AsyncProgress::file_)
//         .addProperty("xmlFile", &AsyncProgress::xmlFile_)
//         .addProperty("jsonFile", &AsyncProgress::jsonFile_)
//         .addProperty("xmlElement", &AsyncProgress::xmlElement_)
//         .addProperty("jsonIndex", &AsyncProgress::jsonIndex_)
//         .addProperty("mode", &AsyncProgress::mode_)
//         .addProperty("resources", &AsyncProgress::resources_)
//         .addProperty("loadedResources", &AsyncProgress::loadedResources_)
//         .addProperty("totalResources", &AsyncProgress::totalResources_)
//         .addProperty("loadedNodes", &AsyncProgress::loadedNodes_)
//         .addProperty("totalNodes", &AsyncProgress::totalNodes_)
//     );
//     lua["KScene"].setClass(UserdataMetatable<Scene, Node>(false)
//         .addStaticFunction("new", &KCreateObject<Scene>)
//         .addStaticFunction("__gc", &KReleaseObject<Scene>)

//         .addFunction("GetType", &Scene::GetType)
//         .addFunction("GetTypeName", &Scene::GetTypeName)
//         .addFunction("GetTypeInfo", &Scene::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Scene::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Scene::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Scene::GetTypeInfoStatic)
//         .addFunction("Load", &Scene::Load)
//         .addFunction("Save", &Scene::Save)

//         .addOverloadedFunctions("LoadXML",
//             static_cast<bool(Scene::*)(const XMLElement&, bool)>(&Scene::LoadXML),
//             static_cast<bool(Scene::*)(Deserializer&)>(&Scene::LoadXML))


//         .addOverloadedFunctions("LoadJSON",
//             static_cast<bool(Scene::*)(const JSONValue&, bool)>(&Scene::LoadJSON),
//             static_cast<bool(Scene::*)(Deserializer&)>(&Scene::LoadJSON))


//         .addOverloadedFunctions("MarkNetworkUpdate",
//             static_cast<void(Scene::*)()>(&Scene::MarkNetworkUpdate),
//             static_cast<void(Scene::*)(Node*)>(&Scene::MarkNetworkUpdate),
//             static_cast<void(Scene::*)(Component*)>(&Scene::MarkNetworkUpdate))

//         .addFunction("AddReplicationState", &Scene::AddReplicationState)
//         .addFunction("SaveXML", &Scene::SaveXML)
//         .addFunction("SaveJSON", &Scene::SaveJSON)
//         .addFunction("LoadAsync", &Scene::LoadAsync)
//         .addFunction("LoadAsyncXML", &Scene::LoadAsyncXML)
//         .addFunction("LoadAsyncJSON", &Scene::LoadAsyncJSON)
//         .addFunction("StopAsyncLoading", &Scene::StopAsyncLoading)
//         .addFunction("Instantiate", &Scene::Instantiate)

//         .addOverloadedFunctions("InstantiateXML",
//             static_cast<Node*(Scene::*)(const XMLElement&, const Vector3&, const Quaternion&, CreateMode)>(&Scene::InstantiateXML),
//             static_cast<Node*(Scene::*)(Deserializer&, const Vector3&, const Quaternion&, CreateMode)>(&Scene::InstantiateXML))


//         .addOverloadedFunctions("InstantiateJSON",
//             static_cast<Node*(Scene::*)(const JSONValue&, const Vector3&, const Quaternion&, CreateMode)>(&Scene::InstantiateJSON),
//             static_cast<Node*(Scene::*)(Deserializer&, const Vector3&, const Quaternion&, CreateMode)>(&Scene::InstantiateJSON))

//         .addFunction("Clear", &Scene::Clear)
//         .addFunction("SetUpdateEnabled", &Scene::SetUpdateEnabled)
//         .addFunction("SetTimeScale", &Scene::SetTimeScale)
//         .addFunction("SetElapsedTime", &Scene::SetElapsedTime)
//         .addFunction("SetSmoothingConstant", &Scene::SetSmoothingConstant)
//         .addFunction("SetSnapThreshold", &Scene::SetSnapThreshold)
//         .addFunction("SetAsyncLoadingMs", &Scene::SetAsyncLoadingMs)
//         .addFunction("AddRequiredPackageFile", &Scene::AddRequiredPackageFile)
//         .addFunction("ClearRequiredPackageFiles", &Scene::ClearRequiredPackageFiles)
//         .addFunction("RegisterVar", &Scene::RegisterVar)
//         .addFunction("UnregisterVar", &Scene::UnregisterVar)
//         .addFunction("UnregisterAllVars", &Scene::UnregisterAllVars)
//         .addFunction("GetNode", &Scene::GetNode)
//         .addFunction("GetComponent", &Scene::GetComponent)
//         .addFunction("GetNodesWithTag", &Scene::GetNodesWithTag)
//         .addFunction("IsUpdateEnabled", &Scene::IsUpdateEnabled)
//         .addFunction("IsAsyncLoading", &Scene::IsAsyncLoading)
//         .addFunction("GetAsyncProgress", &Scene::GetAsyncProgress)
//         .addFunction("GetAsyncLoadMode", &Scene::GetAsyncLoadMode)
//         .addFunction("GetFileName", &Scene::GetFileName)
//         .addFunction("GetChecksum", &Scene::GetChecksum)
//         .addFunction("GetTimeScale", &Scene::GetTimeScale)
//         .addFunction("GetElapsedTime", &Scene::GetElapsedTime)
//         .addFunction("GetSmoothingConstant", &Scene::GetSmoothingConstant)
//         .addFunction("GetSnapThreshold", &Scene::GetSnapThreshold)
//         .addFunction("GetAsyncLoadingMs", &Scene::GetAsyncLoadingMs)
//         .addFunction("GetRequiredPackageFiles", &Scene::GetRequiredPackageFiles)
//         .addFunction("GetVarName", &Scene::GetVarName)
//         .addFunction("Update", &Scene::Update)
//         .addFunction("BeginThreadedUpdate", &Scene::BeginThreadedUpdate)
//         .addFunction("EndThreadedUpdate", &Scene::EndThreadedUpdate)
//         .addFunction("DelayedMarkedDirty", &Scene::DelayedMarkedDirty)
//         .addFunction("IsThreadedUpdate", &Scene::IsThreadedUpdate)
//         .addFunction("GetFreeNodeID", &Scene::GetFreeNodeID)
//         .addFunction("GetFreeComponentID", &Scene::GetFreeComponentID)
//         .addFunction("NodeTagAdded", &Scene::NodeTagAdded)
//         .addFunction("NodeTagRemoved", &Scene::NodeTagRemoved)
//         .addFunction("NodeAdded", &Scene::NodeAdded)
//         .addFunction("NodeRemoved", &Scene::NodeRemoved)
//         .addFunction("ComponentAdded", &Scene::ComponentAdded)
//         .addFunction("ComponentRemoved", &Scene::ComponentRemoved)
//         .addFunction("PrepareNetworkUpdate", &Scene::PrepareNetworkUpdate)
//         .addFunction("CleanupConnection", &Scene::CleanupConnection)
//         .addFunction("MarkReplicationDirty", &Scene::MarkReplicationDirty)

//         .addProperty("type", &Scene::GetType)
//         .addProperty("typeName", &Scene::GetTypeName)
//         .addProperty("typeInfo", &Scene::GetTypeInfo)
//         .addProperty("updateEnabled", &Scene::IsUpdateEnabled, &Scene::SetUpdateEnabled)
//         .addProperty("asyncLoading", &Scene::IsAsyncLoading)
//         .addProperty("asyncProgress", &Scene::GetAsyncProgress)
//         .addProperty("asyncLoadMode", &Scene::GetAsyncLoadMode)
//         .addProperty("fileName", &Scene::GetFileName)
//         .addProperty("checksum", &Scene::GetChecksum)
//         .addProperty("timeScale", &Scene::GetTimeScale, &Scene::SetTimeScale)
//         .addProperty("elapsedTime", &Scene::GetElapsedTime, &Scene::SetElapsedTime)
//         .addProperty("smoothingConstant", &Scene::GetSmoothingConstant, &Scene::SetSmoothingConstant)
//         .addProperty("snapThreshold", &Scene::GetSnapThreshold, &Scene::SetSnapThreshold)
//         .addProperty("asyncLoadingMs", &Scene::GetAsyncLoadingMs, &Scene::SetAsyncLoadingMs)
//         .addProperty("requiredPackageFiles", &Scene::GetRequiredPackageFiles)
//         .addProperty("threadedUpdate", &Scene::IsThreadedUpdate)
//     );
//     lua["KRegisterSceneLibrary"] = function(&RegisterSceneLibrary);
// }

// static void RegisterSceneEvents(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KE_SCENEUPDATE"] = E_SCENEUPDATE;
//     lua["KE_SCENESUBSYSTEMUPDATE"] = E_SCENESUBSYSTEMUPDATE;
//     lua["KE_UPDATESMOOTHING"] = E_UPDATESMOOTHING;
//     lua["KE_SCENEDRAWABLEUPDATEFINISHED"] = E_SCENEDRAWABLEUPDATEFINISHED;
//     lua["KE_TARGETPOSITION"] = E_TARGETPOSITION;
//     lua["KE_TARGETROTATION"] = E_TARGETROTATION;
//     lua["KE_ATTRIBUTEANIMATIONUPDATE"] = E_ATTRIBUTEANIMATIONUPDATE;
//     lua["KE_ATTRIBUTEANIMATIONADDED"] = E_ATTRIBUTEANIMATIONADDED;
//     lua["KE_ATTRIBUTEANIMATIONREMOVED"] = E_ATTRIBUTEANIMATIONREMOVED;
//     lua["KE_SCENEPOSTUPDATE"] = E_SCENEPOSTUPDATE;
//     lua["KE_ASYNCLOADPROGRESS"] = E_ASYNCLOADPROGRESS;
//     lua["KE_ASYNCLOADFINISHED"] = E_ASYNCLOADFINISHED;
//     lua["KE_NODEADDED"] = E_NODEADDED;
//     lua["KE_NODEREMOVED"] = E_NODEREMOVED;
//     lua["KE_COMPONENTADDED"] = E_COMPONENTADDED;
//     lua["KE_COMPONENTREMOVED"] = E_COMPONENTREMOVED;
//     lua["KE_NODENAMECHANGED"] = E_NODENAMECHANGED;
//     lua["KE_NODEENABLEDCHANGED"] = E_NODEENABLEDCHANGED;
//     lua["KE_NODETAGADDED"] = E_NODETAGADDED;
//     lua["KE_NODETAGREMOVED"] = E_NODETAGREMOVED;
//     lua["KE_COMPONENTENABLEDCHANGED"] = E_COMPONENTENABLEDCHANGED;
//     lua["KE_TEMPORARYCHANGED"] = E_TEMPORARYCHANGED;
//     lua["KE_NODECLONED"] = E_NODECLONED;
//     lua["KE_COMPONENTCLONED"] = E_COMPONENTCLONED;
//     lua["KE_INTERCEPTNETWORKUPDATE"] = E_INTERCEPTNETWORKUPDATE;
// }

// static void RegisterSceneResolver(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KSceneResolver"].setClass(UserdataMetatable<SceneResolver>()
//         .setConstructors<SceneResolver()>()

//         .addFunction("Reset", &SceneResolver::Reset)
//         .addFunction("AddNode", &SceneResolver::AddNode)
//         .addFunction("AddComponent", &SceneResolver::AddComponent)
//         .addFunction("Resolve", &SceneResolver::Resolve)
//     );
// }

// static void RegisterSerializable(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KSerializable"].setClass(UserdataMetatable<Serializable, Object>(false)
//         .addStaticFunction("new", &KCreateObject<Serializable>)
//         .addStaticFunction("__gc", &KReleaseObject<Serializable>)

//         .addFunction("GetType", &Serializable::GetType)
//         .addFunction("GetTypeName", &Serializable::GetTypeName)
//         .addFunction("GetTypeInfo", &Serializable::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Serializable::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Serializable::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Serializable::GetTypeInfoStatic)
//         .addFunction("OnSetAttribute", &Serializable::OnSetAttribute)
//         .addFunction("OnGetAttribute", &Serializable::OnGetAttribute)
//         .addFunction("GetAttributes", &Serializable::GetAttributes)
//         .addFunction("GetNetworkAttributes", &Serializable::GetNetworkAttributes)
//         .addFunction("Load", &Serializable::Load)
//         .addFunction("Save", &Serializable::Save)
//         .addFunction("LoadXML", &Serializable::LoadXML)
//         .addFunction("SaveXML", &Serializable::SaveXML)
//         .addFunction("LoadJSON", &Serializable::LoadJSON)
//         .addFunction("SaveJSON", &Serializable::SaveJSON)
//         .addFunction("ApplyAttributes", &Serializable::ApplyAttributes)
//         .addFunction("SaveDefaultAttributes", &Serializable::SaveDefaultAttributes)
//         .addFunction("MarkNetworkUpdate", &Serializable::MarkNetworkUpdate)

//         .addOverloadedFunctions("SetAttribute",
//             static_cast<bool(Serializable::*)(unsigned int, const Variant&)>(&Serializable::SetAttribute),
//             static_cast<bool(Serializable::*)(const String&, const Variant&)>(&Serializable::SetAttribute))

//         .addFunction("ResetToDefault", &Serializable::ResetToDefault)
//         .addFunction("RemoveInstanceDefault", &Serializable::RemoveInstanceDefault)
//         .addFunction("SetTemporary", &Serializable::SetTemporary)
//         .addFunction("SetInterceptNetworkUpdate", &Serializable::SetInterceptNetworkUpdate)
//         .addFunction("AllocateNetworkState", &Serializable::AllocateNetworkState)
//         .addFunction("WriteInitialDeltaUpdate", &Serializable::WriteInitialDeltaUpdate)
//         .addFunction("WriteDeltaUpdate", &Serializable::WriteDeltaUpdate)
//         .addFunction("WriteLatestDataUpdate", &Serializable::WriteLatestDataUpdate)
//         .addFunction("ReadDeltaUpdate", &Serializable::ReadDeltaUpdate)
//         .addFunction("ReadLatestDataUpdate", &Serializable::ReadLatestDataUpdate)

//         .addOverloadedFunctions("GetAttribute",
//             static_cast<Variant(Serializable::*)(unsigned int) const>(&Serializable::GetAttribute),
//             static_cast<Variant(Serializable::*)(const String&) const>(&Serializable::GetAttribute))


//         .addOverloadedFunctions("GetAttributeDefault",
//             static_cast<Variant(Serializable::*)(unsigned int) const>(&Serializable::GetAttributeDefault),
//             static_cast<Variant(Serializable::*)(const String&) const>(&Serializable::GetAttributeDefault))

//         .addFunction("GetNumAttributes", &Serializable::GetNumAttributes)
//         .addFunction("GetNumNetworkAttributes", &Serializable::GetNumNetworkAttributes)
//         .addFunction("IsTemporary", &Serializable::IsTemporary)
//         .addFunction("GetInterceptNetworkUpdate", &Serializable::GetInterceptNetworkUpdate)
//         .addFunction("GetNetworkState", &Serializable::GetNetworkState)

//         .addProperty("type", &Serializable::GetType)
//         .addProperty("typeName", &Serializable::GetTypeName)
//         .addProperty("typeInfo", &Serializable::GetTypeInfo)
//         .addProperty("attributes", &Serializable::GetAttributes)
//         .addProperty("networkAttributes", &Serializable::GetNetworkAttributes)
//         .addProperty("numAttributes", &Serializable::GetNumAttributes)
//         .addProperty("numNetworkAttributes", &Serializable::GetNumNetworkAttributes)
//         .addProperty("temporary", &Serializable::IsTemporary, &Serializable::SetTemporary)
//         .addProperty("networkState", &Serializable::GetNetworkState)
//     );
//     lua["KAttributeTrait"].setClass(UserdataMetatable<AttributeTrait>()

//     );
//     lua["KAttributeTrait"].setClass(UserdataMetatable<AttributeTrait>()

//     );
//     lua["KAttributeTrait"].setClass(UserdataMetatable<AttributeTrait>()

//     );
//     lua["KAttributeTrait"].setClass(UserdataMetatable<AttributeTrait>()

//     );
// }

// static void RegisterSmoothedTransform(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KSMOOTH_NONE"] = SMOOTH_NONE;
//     lua["KSMOOTH_POSITION"] = SMOOTH_POSITION;
//     lua["KSMOOTH_ROTATION"] = SMOOTH_ROTATION;
//     lua["KSmoothedTransform"].setClass(UserdataMetatable<SmoothedTransform, Component>(false)
//         .addStaticFunction("new", &KCreateObject<SmoothedTransform>)
//         .addStaticFunction("__gc", &KReleaseObject<SmoothedTransform>)

//         .addFunction("GetType", &SmoothedTransform::GetType)
//         .addFunction("GetTypeName", &SmoothedTransform::GetTypeName)
//         .addFunction("GetTypeInfo", &SmoothedTransform::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &SmoothedTransform::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &SmoothedTransform::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &SmoothedTransform::GetTypeInfoStatic)
//         .addFunction("Update", &SmoothedTransform::Update)
//         .addFunction("SetTargetPosition", &SmoothedTransform::SetTargetPosition)
//         .addFunction("SetTargetRotation", &SmoothedTransform::SetTargetRotation)
//         .addFunction("SetTargetWorldPosition", &SmoothedTransform::SetTargetWorldPosition)
//         .addFunction("SetTargetWorldRotation", &SmoothedTransform::SetTargetWorldRotation)
//         .addFunction("GetTargetPosition", &SmoothedTransform::GetTargetPosition)
//         .addFunction("GetTargetRotation", &SmoothedTransform::GetTargetRotation)
//         .addFunction("GetTargetWorldPosition", &SmoothedTransform::GetTargetWorldPosition)
//         .addFunction("GetTargetWorldRotation", &SmoothedTransform::GetTargetWorldRotation)
//         .addFunction("IsInProgress", &SmoothedTransform::IsInProgress)

//         .addProperty("type", &SmoothedTransform::GetType)
//         .addProperty("typeName", &SmoothedTransform::GetTypeName)
//         .addProperty("typeInfo", &SmoothedTransform::GetTypeInfo)
//         .addProperty("targetPosition", &SmoothedTransform::GetTargetPosition, &SmoothedTransform::SetTargetPosition)
//         .addProperty("targetRotation", &SmoothedTransform::GetTargetRotation, &SmoothedTransform::SetTargetRotation)
//         .addProperty("targetWorldPosition", &SmoothedTransform::GetTargetWorldPosition, &SmoothedTransform::SetTargetWorldPosition)
//         .addProperty("targetWorldRotation", &SmoothedTransform::GetTargetWorldRotation, &SmoothedTransform::SetTargetWorldRotation)
//         .addProperty("inProgress", &SmoothedTransform::IsInProgress)
//     );
// }

// static void RegisterSplinePath(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KSplinePath"].setClass(UserdataMetatable<SplinePath, Component>(false)
//         .addStaticFunction("new", &KCreateObject<SplinePath>)
//         .addStaticFunction("__gc", &KReleaseObject<SplinePath>)

//         .addFunction("GetType", &SplinePath::GetType)
//         .addFunction("GetTypeName", &SplinePath::GetTypeName)
//         .addFunction("GetTypeInfo", &SplinePath::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &SplinePath::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &SplinePath::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &SplinePath::GetTypeInfoStatic)
//         .addFunction("ApplyAttributes", &SplinePath::ApplyAttributes)
//         .addFunction("DrawDebugGeometry", &SplinePath::DrawDebugGeometry)
//         .addFunction("AddControlPoint", &SplinePath::AddControlPoint)
//         .addFunction("RemoveControlPoint", &SplinePath::RemoveControlPoint)
//         .addFunction("ClearControlPoints", &SplinePath::ClearControlPoints)
//         .addFunction("SetInterpolationMode", &SplinePath::SetInterpolationMode)
//         .addFunction("SetSpeed", &SplinePath::SetSpeed)
//         .addFunction("SetPosition", &SplinePath::SetPosition)
//         .addFunction("SetControlledNode", &SplinePath::SetControlledNode)
//         .addFunction("GetInterpolationMode", &SplinePath::GetInterpolationMode)
//         .addFunction("GetSpeed", &SplinePath::GetSpeed)
//         .addFunction("GetLength", &SplinePath::GetLength)
//         .addFunction("GetPosition", &SplinePath::GetPosition)
//         .addFunction("GetControlledNode", &SplinePath::GetControlledNode)
//         .addFunction("GetPoint", &SplinePath::GetPoint)
//         .addFunction("Move", &SplinePath::Move)
//         .addFunction("Reset", &SplinePath::Reset)
//         .addFunction("IsFinished", &SplinePath::IsFinished)

//         .addProperty("type", &SplinePath::GetType)
//         .addProperty("typeName", &SplinePath::GetTypeName)
//         .addProperty("typeInfo", &SplinePath::GetTypeInfo)
//         .addProperty("interpolationMode", &SplinePath::GetInterpolationMode, &SplinePath::SetInterpolationMode)
//         .addProperty("speed", &SplinePath::GetSpeed, &SplinePath::SetSpeed)
//         .addProperty("length", &SplinePath::GetLength)
//         .addProperty("position", &SplinePath::GetPosition, &SplinePath::SetPosition)
//         .addProperty("controlledNode", &SplinePath::GetControlledNode, &SplinePath::SetControlledNode)
//         .addProperty("finished", &SplinePath::IsFinished)
//     );
// }

// static void RegisterUnknownComponent(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KUnknownComponent"].setClass(UserdataMetatable<UnknownComponent, Component>(false)
//         .addStaticFunction("new", &KCreateObject<UnknownComponent>)
//         .addStaticFunction("__gc", &KReleaseObject<UnknownComponent>)

//         .addFunction("GetType", &UnknownComponent::GetType)
//         .addFunction("GetTypeName", &UnknownComponent::GetTypeName)
//         .addFunction("GetAttributes", &UnknownComponent::GetAttributes)
//         .addFunction("Load", &UnknownComponent::Load)
//         .addFunction("LoadXML", &UnknownComponent::LoadXML)
//         .addFunction("LoadJSON", &UnknownComponent::LoadJSON)
//         .addFunction("Save", &UnknownComponent::Save)
//         .addFunction("SaveXML", &UnknownComponent::SaveXML)
//         .addFunction("SaveJSON", &UnknownComponent::SaveJSON)
//         .addFunction("SetTypeName", &UnknownComponent::SetTypeName)
//         .addFunction("SetType", &UnknownComponent::SetType)
//         .addFunction("GetXMLAttributes", &UnknownComponent::GetXMLAttributes)
//         .addFunction("GetBinaryAttributes", &UnknownComponent::GetBinaryAttributes)
//         .addFunction("GetUseXML", &UnknownComponent::GetUseXML)
//         .addStaticFunction("GetTypeStatic", &UnknownComponent::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &UnknownComponent::GetTypeNameStatic)

//         .addProperty("type", &UnknownComponent::GetType, &UnknownComponent::SetType)
//         .addProperty("typeName", &UnknownComponent::GetTypeName, &UnknownComponent::SetTypeName)
//         .addProperty("attributes", &UnknownComponent::GetAttributes)
//         .addProperty("xMLAttributes", &UnknownComponent::GetXMLAttributes)
//         .addProperty("binaryAttributes", &UnknownComponent::GetBinaryAttributes)
//         .addProperty("useXML", &UnknownComponent::GetUseXML)
//     );
// }

// static void RegisterValueAnimation(kaguya::State& lua)
// {
//     using namespace kaguya;

//     // enum InterpMethod;
//     lua["KIM_NONE"] = IM_NONE;
//     lua["KIM_LINEAR"] = IM_LINEAR;
//     lua["KIM_SPLINE"] = IM_SPLINE;

//     lua["KVAnimKeyFrame"].setClass(UserdataMetatable<VAnimKeyFrame>()

//         .addProperty("time", &VAnimKeyFrame::time_)
//         .addProperty("value", &VAnimKeyFrame::value_)
//     );
//     lua["KVAnimEventFrame"].setClass(UserdataMetatable<VAnimEventFrame>()

//         .addProperty("time", &VAnimEventFrame::time_)
//         .addProperty("eventType", &VAnimEventFrame::eventType_)
//         .addProperty("eventData", &VAnimEventFrame::eventData_)
//     );
//     lua["KValueAnimation"].setClass(UserdataMetatable<ValueAnimation, Resource>(false)
//         .addStaticFunction("new", &KCreateObject<ValueAnimation>)
//         .addStaticFunction("__gc", &KReleaseObject<ValueAnimation>)

//         .addFunction("GetType", &ValueAnimation::GetType)
//         .addFunction("GetTypeName", &ValueAnimation::GetTypeName)
//         .addFunction("GetTypeInfo", &ValueAnimation::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &ValueAnimation::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &ValueAnimation::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &ValueAnimation::GetTypeInfoStatic)
//         .addFunction("BeginLoad", &ValueAnimation::BeginLoad)
//         .addFunction("Save", &ValueAnimation::Save)
//         .addFunction("LoadXML", &ValueAnimation::LoadXML)
//         .addFunction("SaveXML", &ValueAnimation::SaveXML)
//         .addFunction("LoadJSON", &ValueAnimation::LoadJSON)
//         .addFunction("SaveJSON", &ValueAnimation::SaveJSON)
//         .addFunction("SetOwner", &ValueAnimation::SetOwner)
//         .addFunction("SetInterpolationMethod", &ValueAnimation::SetInterpolationMethod)
//         .addFunction("SetSplineTension", &ValueAnimation::SetSplineTension)
//         .addFunction("SetValueType", &ValueAnimation::SetValueType)
//         .addFunction("SetKeyFrame", &ValueAnimation::SetKeyFrame)
//         .addFunction("SetEventFrame", &ValueAnimation::SetEventFrame)
//         .addFunction("IsValid", &ValueAnimation::IsValid)
//         .addFunction("GetOwner", &ValueAnimation::GetOwner)
//         .addFunction("GetInterpolationMethod", &ValueAnimation::GetInterpolationMethod)
//         .addFunction("GetSplineTension", &ValueAnimation::GetSplineTension)
//         .addFunction("GetValueType", &ValueAnimation::GetValueType)
//         .addFunction("GetBeginTime", &ValueAnimation::GetBeginTime)
//         .addFunction("GetEndTime", &ValueAnimation::GetEndTime)
//         .addFunction("GetAnimationValue", &ValueAnimation::GetAnimationValue)
//         .addFunction("HasEventFrames", &ValueAnimation::HasEventFrames)
//         .addFunction("GetEventFrames", &ValueAnimation::GetEventFrames)

//         .addProperty("type", &ValueAnimation::GetType)
//         .addProperty("typeName", &ValueAnimation::GetTypeName)
//         .addProperty("typeInfo", &ValueAnimation::GetTypeInfo)
//         .addProperty("valid", &ValueAnimation::IsValid)
//         .addProperty("owner", &ValueAnimation::GetOwner, &ValueAnimation::SetOwner)
//         .addProperty("interpolationMethod", &ValueAnimation::GetInterpolationMethod, &ValueAnimation::SetInterpolationMethod)
//         .addProperty("splineTension", &ValueAnimation::GetSplineTension, &ValueAnimation::SetSplineTension)
//         .addProperty("valueType", &ValueAnimation::GetValueType, &ValueAnimation::SetValueType)
//         .addProperty("beginTime", &ValueAnimation::GetBeginTime)
//         .addProperty("endTime", &ValueAnimation::GetEndTime)
//     );
// }

// static void RegisterValueAnimationInfo(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KValueAnimationInfo"].setClass(UserdataMetatable<ValueAnimationInfo, RefCounted>()
//         .setConstructors<ValueAnimationInfo(ValueAnimation*, WrapMode, float),
//             ValueAnimationInfo(Object*, ValueAnimation*, WrapMode, float),
//             ValueAnimationInfo(const ValueAnimationInfo&)>()

//         .addFunction("Update", &ValueAnimationInfo::Update)
//         .addFunction("SetTime", &ValueAnimationInfo::SetTime)
//         .addFunction("SetWrapMode", &ValueAnimationInfo::SetWrapMode)
//         .addFunction("SetSpeed", &ValueAnimationInfo::SetSpeed)
//         .addFunction("GetTarget", &ValueAnimationInfo::GetTarget)
//         .addFunction("GetAnimation", &ValueAnimationInfo::GetAnimation)
//         .addFunction("GetWrapMode", &ValueAnimationInfo::GetWrapMode)
//         .addFunction("GetTime", &ValueAnimationInfo::GetTime)
//         .addFunction("GetSpeed", &ValueAnimationInfo::GetSpeed)

//         .addProperty("target", &ValueAnimationInfo::GetTarget)
//         .addProperty("animation", &ValueAnimationInfo::GetAnimation)
//         .addProperty("wrapMode", &ValueAnimationInfo::GetWrapMode, &ValueAnimationInfo::SetWrapMode)
//         .addProperty("time", &ValueAnimationInfo::GetTime, &ValueAnimationInfo::SetTime)
//         .addProperty("speed", &ValueAnimationInfo::GetSpeed, &ValueAnimationInfo::SetSpeed)
//     );
// }

// void RegisterSceneLuaAPI(kaguya::State& lua)
// {
//     RegisterAnimatable(lua);
//     RegisterAnimationDefs(lua);
//     RegisterComponent(lua);
//     RegisterLogicComponent(lua);
//     RegisterNode(lua);
//     RegisterObjectAnimation(lua);
//     RegisterReplicationState(lua);
//     RegisterScene(lua);
//     RegisterSceneEvents(lua);
//     RegisterSceneResolver(lua);
//     RegisterSerializable(lua);
//     RegisterSmoothedTransform(lua);
//     RegisterSplinePath(lua);
//     RegisterUnknownComponent(lua);
//     RegisterValueAnimation(lua);
//     RegisterValueAnimationInfo(lua);
// }
// }
