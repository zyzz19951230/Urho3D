// #include "../LuaScript/LuaFile.h"
// #include "../LuaScript/LuaFunction.h"
// #include "../LuaScript/LuaScript.h"
// #include "../LuaScript/LuaScriptEventInvoker.h"
// #include "../LuaScript/LuaScriptEventListener.h"
// #include "../LuaScript/LuaScriptInstance.h"
// #include "../LuaScript/ToluaUtils.h"
// #include "../LuaScript/LuaScriptUtils.h"

// #include <kaguya.hpp>

// namespace Urho3D
// {

// static void RegisterLuaFile(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KLuaFile"].setClass(UserdataMetatable<LuaFile, Resource>(false)
//         .addStaticFunction("new", &KCreateObject<LuaFile>)
//         .addStaticFunction("__gc", &KReleaseObject<LuaFile>)

//         .addFunction("BeginLoad", &LuaFile::BeginLoad)
//         .addFunction("Save", &LuaFile::Save)
//         .addFunction("LoadChunk", &LuaFile::LoadChunk)
//         .addFunction("LoadAndExecute", &LuaFile::LoadAndExecute)
//     );
// }

// static void RegisterLuaFunction(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KLuaFunction"].setClass(UserdataMetatable<LuaFunction, RefCounted>()
//         .setConstructors<LuaFunction(lua_State*, int),
//             LuaFunction(lua_State*, lua_CFunction)>()

//         .addFunction("IsValid", &LuaFunction::IsValid)
//         .addFunction("BeginCall", &LuaFunction::BeginCall)
//         .addFunction("EndCall", &LuaFunction::EndCall)
//         .addFunction("PushInt", &LuaFunction::PushInt)
//         .addFunction("PushBool", &LuaFunction::PushBool)
//         .addFunction("PushFloat", &LuaFunction::PushFloat)
//         .addFunction("PushDouble", &LuaFunction::PushDouble)
//         .addFunction("PushString", &LuaFunction::PushString)
//         .addFunction("PushUserType", &LuaFunction::PushUserType)
//         .addFunction("PushVariant", &LuaFunction::PushVariant)
//         .addFunction("PushLuaTable", &LuaFunction::PushLuaTable)
//         .addFunction("GetFunctionRef", &LuaFunction::GetFunctionRef)

//         .addProperty("valid", &LuaFunction::IsValid)
//         .addProperty("functionRef", &LuaFunction::GetFunctionRef)
//     );
// }

// static void RegisterLuaScript(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KLOGIC_CATEGORY"] = LOGIC_CATEGORY;
//     lua["KLuaScript"].setClass(UserdataMetatable<LuaScript, Object, LuaScriptEventListener>(false)
//         .addStaticFunction("new", &KCreateObject<LuaScript>)
//         .addStaticFunction("__gc", &KReleaseObject<LuaScript>)

//         .addOverloadedFunctions("AddEventHandler",
//             static_cast<void(LuaScript::*)(const String&, int)>(&LuaScript::AddEventHandler),
//             static_cast<void(LuaScript::*)(const String&, const String&)>(&LuaScript::AddEventHandler),
//             static_cast<void(LuaScript::*)(Object*, const String&, int)>(&LuaScript::AddEventHandler),
//             static_cast<void(LuaScript::*)(Object*, const String&, const String&)>(&LuaScript::AddEventHandler))


//         .addOverloadedFunctions("RemoveEventHandler",
//             static_cast<void(LuaScript::*)(const String&)>(&LuaScript::RemoveEventHandler),
//             static_cast<void(LuaScript::*)(Object*, const String&)>(&LuaScript::RemoveEventHandler))

//         .addFunction("RemoveEventHandlers", &LuaScript::RemoveEventHandlers)
//         .addFunction("RemoveAllEventHandlers", &LuaScript::RemoveAllEventHandlers)
//         .addFunction("RemoveEventHandlersExcept", &LuaScript::RemoveEventHandlersExcept)

//         .addOverloadedFunctions("HasEventHandler",
//             static_cast<bool(LuaScript::*)(const String&) const>(&LuaScript::HasEventHandler),
//             static_cast<bool(LuaScript::*)(Object*, const String&) const>(&LuaScript::HasEventHandler))

//         .addFunction("ExecuteFile", &LuaScript::ExecuteFile)
//         .addFunction("ExecuteString", &LuaScript::ExecuteString)
//         .addFunction("LoadRawFile", &LuaScript::LoadRawFile)
//         .addFunction("ExecuteRawFile", &LuaScript::ExecuteRawFile)
//         .addFunction("ExecuteFunction", &LuaScript::ExecuteFunction)
//         .addFunction("SetExecuteConsoleCommands", &LuaScript::SetExecuteConsoleCommands)
//         .addFunction("GetState", &LuaScript::GetState)

//         .addOverloadedFunctions("GetFunction",
//             static_cast<LuaFunction*(LuaScript::*)(int)>(&LuaScript::GetFunction),
//             static_cast<LuaFunction*(LuaScript::*)(const String&, bool)>(&LuaScript::GetFunction))

//         .addFunction("GetExecuteConsoleCommands", &LuaScript::GetExecuteConsoleCommands)
//         .addStaticFunction("PushLuaFunction", &LuaScript::PushLuaFunction)

//         .addProperty("state", &LuaScript::GetState)
//         .addProperty("executeConsoleCommands", &LuaScript::GetExecuteConsoleCommands, &LuaScript::SetExecuteConsoleCommands)
//     );
//     lua["KRegisterLuaScriptLibrary"] = function(&RegisterLuaScriptLibrary);
// }

// static void RegisterLuaScriptEventInvoker(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KLuaScriptEventInvoker"].setClass(UserdataMetatable<LuaScriptEventInvoker, Object>(false)
//         .addStaticFunction("new", &KCreateObject<LuaScriptEventInvoker>)
//         .addStaticFunction("__gc", &KReleaseObject<LuaScriptEventInvoker>)

//         .addFunction("AddEventHandler", &LuaScriptEventInvoker::AddEventHandler)
//     );
// }

// static void RegisterLuaScriptEventListener(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KLuaScriptEventListener"].setClass(UserdataMetatable<LuaScriptEventListener>()


//         .addOverloadedFunctions("AddEventHandler",
//             static_cast<void(LuaScriptEventListener::*)(const String&, int)>(&LuaScriptEventListener::AddEventHandler),
//             static_cast<void(LuaScriptEventListener::*)(const String&, const String&)>(&LuaScriptEventListener::AddEventHandler),
//             static_cast<void(LuaScriptEventListener::*)(Object*, const String&, int)>(&LuaScriptEventListener::AddEventHandler),
//             static_cast<void(LuaScriptEventListener::*)(Object*, const String&, const String&)>(&LuaScriptEventListener::AddEventHandler))


//         .addOverloadedFunctions("RemoveEventHandler",
//             static_cast<void(LuaScriptEventListener::*)(const String&)>(&LuaScriptEventListener::RemoveEventHandler),
//             static_cast<void(LuaScriptEventListener::*)(Object*, const String&)>(&LuaScriptEventListener::RemoveEventHandler))

//         .addFunction("RemoveEventHandlers", &LuaScriptEventListener::RemoveEventHandlers)
//         .addFunction("RemoveAllEventHandlers", &LuaScriptEventListener::RemoveAllEventHandlers)
//         .addFunction("RemoveEventHandlersExcept", &LuaScriptEventListener::RemoveEventHandlersExcept)

//         .addOverloadedFunctions("HasEventHandler",
//             static_cast<bool(LuaScriptEventListener::*)(const String&) const>(&LuaScriptEventListener::HasEventHandler),
//             static_cast<bool(LuaScriptEventListener::*)(Object*, const String&) const>(&LuaScriptEventListener::HasEventHandler))

//     );
// }

// static void RegisterLuaScriptInstance(kaguya::State& lua)
// {
//     using namespace kaguya;

//     // enum LuaScriptObjectMethod;
//     lua["KLSOM_START"] = LSOM_START;
//     lua["KLSOM_STOP"] = LSOM_STOP;
//     lua["KLSOM_DELAYEDSTART"] = LSOM_DELAYEDSTART;
//     lua["KLSOM_UPDATE"] = LSOM_UPDATE;
//     lua["KLSOM_POSTUPDATE"] = LSOM_POSTUPDATE;
//     lua["KLSOM_FIXEDUPDATE"] = LSOM_FIXEDUPDATE;
//     lua["KLSOM_FIXEDPOSTUPDATE"] = LSOM_FIXEDPOSTUPDATE;
//     lua["KLSOM_LOAD"] = LSOM_LOAD;
//     lua["KLSOM_SAVE"] = LSOM_SAVE;
//     lua["KLSOM_READNETWORKUPDATE"] = LSOM_READNETWORKUPDATE;
//     lua["KLSOM_WRITENETWORKUPDATE"] = LSOM_WRITENETWORKUPDATE;
//     lua["KLSOM_APPLYATTRIBUTES"] = LSOM_APPLYATTRIBUTES;
//     lua["KLSOM_TRANSFORMCHANGED"] = LSOM_TRANSFORMCHANGED;
//     lua["KMAX_LUA_SCRIPT_OBJECT_METHODS"] = MAX_LUA_SCRIPT_OBJECT_METHODS;

//     lua["KLuaScriptInstance"].setClass(UserdataMetatable<LuaScriptInstance, Component, LuaScriptEventListener>(false)
//         .addStaticFunction("new", &KCreateObject<LuaScriptInstance>)
//         .addStaticFunction("__gc", &KReleaseObject<LuaScriptInstance>)

//         .addFunction("OnSetAttribute", &LuaScriptInstance::OnSetAttribute)
//         .addFunction("OnGetAttribute", &LuaScriptInstance::OnGetAttribute)
//         .addFunction("GetAttributes", &LuaScriptInstance::GetAttributes)
//         .addFunction("ApplyAttributes", &LuaScriptInstance::ApplyAttributes)
//         .addFunction("OnSetEnabled", &LuaScriptInstance::OnSetEnabled)

//         .addOverloadedFunctions("AddEventHandler",
//             static_cast<void(LuaScriptInstance::*)(const String&, int)>(&LuaScriptInstance::AddEventHandler),
//             static_cast<void(LuaScriptInstance::*)(const String&, const String&)>(&LuaScriptInstance::AddEventHandler),
//             static_cast<void(LuaScriptInstance::*)(Object*, const String&, int)>(&LuaScriptInstance::AddEventHandler),
//             static_cast<void(LuaScriptInstance::*)(Object*, const String&, const String&)>(&LuaScriptInstance::AddEventHandler))


//         .addOverloadedFunctions("RemoveEventHandler",
//             static_cast<void(LuaScriptInstance::*)(const String&)>(&LuaScriptInstance::RemoveEventHandler),
//             static_cast<void(LuaScriptInstance::*)(Object*, const String&)>(&LuaScriptInstance::RemoveEventHandler))

//         .addFunction("RemoveEventHandlers", &LuaScriptInstance::RemoveEventHandlers)
//         .addFunction("RemoveAllEventHandlers", &LuaScriptInstance::RemoveAllEventHandlers)
//         .addFunction("RemoveEventHandlersExcept", &LuaScriptInstance::RemoveEventHandlersExcept)

//         .addOverloadedFunctions("HasEventHandler",
//             static_cast<bool(LuaScriptInstance::*)(const String&) const>(&LuaScriptInstance::HasEventHandler),
//             static_cast<bool(LuaScriptInstance::*)(Object*, const String&) const>(&LuaScriptInstance::HasEventHandler))


//         .addOverloadedFunctions("CreateObject",
//             static_cast<bool(LuaScriptInstance::*)(const String&)>(&LuaScriptInstance::CreateObject),
//             static_cast<bool(LuaScriptInstance::*)(LuaFile*, const String&)>(&LuaScriptInstance::CreateObject))

//         .addFunction("SetScriptFile", &LuaScriptInstance::SetScriptFile)
//         .addFunction("SetScriptObjectType", &LuaScriptInstance::SetScriptObjectType)
//         .addFunction("GetScriptFile", &LuaScriptInstance::GetScriptFile)
//         .addFunction("GetScriptObjectType", &LuaScriptInstance::GetScriptObjectType)
//         .addFunction("GetScriptObjectRef", &LuaScriptInstance::GetScriptObjectRef)
//         .addFunction("GetScriptObjectFunction", &LuaScriptInstance::GetScriptObjectFunction)

//         .addProperty("attributes", &LuaScriptInstance::GetAttributes)
//         .addProperty("scriptFile", &LuaScriptInstance::GetScriptFile, &LuaScriptInstance::SetScriptFile)
//         .addProperty("scriptObjectType", &LuaScriptInstance::GetScriptObjectType, &LuaScriptInstance::SetScriptObjectType)
//         .addProperty("scriptObjectRef", &LuaScriptInstance::GetScriptObjectRef)
//     );
// }

// static void RegisterToluaUtils(kaguya::State& lua)
// {
//     using namespace kaguya;

// }

// void RegisterLuaScriptLuaAPI(kaguya::State& lua)
// {
//     RegisterLuaFile(lua);
//     RegisterLuaFunction(lua);
//     RegisterLuaScript(lua);
//     RegisterLuaScriptEventInvoker(lua);
//     RegisterLuaScriptEventListener(lua);
//     RegisterLuaScriptInstance(lua);
//     RegisterToluaUtils(lua);
// }
// }
