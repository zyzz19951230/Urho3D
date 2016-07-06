#include "../LuaScript/LuaScript.h"
#include "../LuaScript/LuaScriptInstance.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterLuaScriptInstance(kaguya::State &lua)
{
    using namespace kaguya;

    lua["KLuaScriptInstance"].setClass(UserdataMetatable<LuaScriptInstance, Component>()

        .addOverloadedFunctions("CreateObject", 
            static_cast<bool (LuaScriptInstance::*)(const String&)>(&LuaScriptInstance::CreateObject),
            static_cast<bool (LuaScriptInstance::*)(LuaFile*, const String&)>(&LuaScriptInstance::CreateObject))

        .addFunction("SetScriptFile", &LuaScriptInstance::SetScriptFile)
        .addFunction("SetScriptObjectType", &LuaScriptInstance::SetScriptObjectType)
        
        .addOverloadedFunctions("SubscribeToEvent", 
            // static_cast<void (LuaScriptInstance::*)(const String&, kaguya::LuaFunction)>(&LuaScriptInstance::AddEventHandler),
            static_cast<void (LuaScriptInstance::*)(const String&, const String&)>(&LuaScriptInstance::AddEventHandler),
            // static_cast<void (LuaScriptInstance::*)(void* sender, const String&, kaguya::LuaFunction)>(&LuaScriptInstance::AddEventHandler),
            static_cast<void (LuaScriptInstance::*)(void* sender, const String&, const String&)>(&LuaScriptInstance::AddEventHandler))

        .addOverloadedFunctions("UnsubscribeFromEvent", 
                static_cast<void (LuaScriptInstance::*)(const String&)>(&LuaScriptInstance::RemoveEventHandler),
                static_cast<void (LuaScriptInstance::*)(Object*, const String&)>(&LuaScriptInstance::RemoveEventHandler))

        .addFunction("UnsubscribeFromEvents", &LuaScriptInstance::RemoveEventHandlers)
        .addFunction("UnsubscribeFromAllEvents", &LuaScriptInstance::RemoveAllEventHandlers)
        .addFunction("UnsubscribeFromAllEventsExcept", &LuaScriptInstance::RemoveEventHandlersExcept)

        .addOverloadedFunctions("HasSubscribedToEvent", 
            static_cast<bool (LuaScriptInstance::*)(const String&) const>(&LuaScriptInstance::HasEventHandler),
            static_cast<bool (LuaScriptInstance::*)(Object*, const String&) const>(&LuaScriptInstance::HasEventHandler))

        .addFunction("GetScriptFile", &LuaScriptInstance::GetScriptObjectType)
        .addFunction("GetScriptObjectType", &LuaScriptInstance::GetScriptObjectType)
        );

    lua.dostring(
        "LuaScriptObject = {}                                                  "
        "                                                                      "
        "function LuaScriptObject:Start()                                      "
        "end                                                                   "
        "                                                                      "
        "function LuaScriptObject:Stop()                                       "
        "end                                                                   "
        "                                                                      "
        "function LuaScriptObject:GetNode()                                    "
        "    return self.node                                                  "
        "end                                                                   "
        "                                                                      "
        "function LuaScriptObject:SubscribeToEvent(param1, param2, param3)     "
        "    local instance = self.instance                                    "
        "    if instance == nil then                                           "
        "        return                                                        "
        "    end                                                               "
        "                                                                      "
        "    if param3 == nil then                                             "
        "        instance:SubscribeToEvent(param1, param2)                     "
        "    else                                                              "
        "        instance:SubscribeToEvent(param1, param2, param3)             "
        "    end                                                               "
        "end                                                                   "
        "                                                                      "
        "function LuaScriptObject:UnsubscribeFromEvent(param1, param2)         "
        "    local instance = self.instance                                    "
        "    if instance == nil then                                           "
        "        return                                                        "
        "    end                                                               "
        "                                                                      "
        "    if param2 == nil then                                             "
        "        instance:UnsubscribeFromEvent(param1)                         "
        "    else                                                              "
        "        instance:UnsubscribeFromEvent(param1, param2)                 "
        "    end                                                               "
        "end                                                                   "
        "                                                                      "
        "function LuaScriptObject:UnsubscribeFromEvents(sender)                "
        "    local instance = self.instance                                    "
        "    if instance == nil then                                           "
        "        return                                                        "
        "    end                                                               "
        "    instance:UnsubscribeFromEvents(sender)                            "
        "end                                                                   "
        "                                                                      "
        "function LuaScriptObject:UnsubscribeFromAllEvents()                   "
        "    local instance = self.instance                                    "
        "    if instance == nil then                                           "
        "        return                                                        "
        "    end                                                               "
        "    instance:UnsubscribeFromAllEvents()                               "
        "end                                                                   "
        "                                                                      "
        "function LuaScriptObject:UnsubscribeFromAllEventsExcept()             "
        "    local instance = self.instance                                    "
        "    if instance == nil then                                           "
        "        return                                                        "
        "    end                                                               "
        "    instance:UnsubscribeFromAllEventsExcept()                         "
        "end                                                                   "
        "                                                                      "
        "function LuaScriptObject:HasSubscribedToEvent(param1, param2)         "
        "    local instance = self.instance                                    "
        "    if instance == nil then                                           "
        "        return                                                        "
        "    end                                                               "
        "                                                                      "
        "    if param2 == nil then                                             "
        "        return instance:HasSubscribedToEvent(param1)                  "
        "    else                                                              "
        "        return instance:HasSubscribedToEvent(param1, param2)          "
        "    end                                                               "
        "end                                                                   "
        "                                                                      "
        "function ScriptObject()                                               "
        "    local o = {}                                                      "
        "    setmetatable(o, LuaScriptObject)                                  "
        "    LuaScriptObject.__index = LuaScriptObject                         "
        "    return o                                                          "
        "end                                                                   "
        "                                                                      "
        "function CreateScriptObjectInstance(object, instance)                 "
        "    local o = {}                                                      "
        "    setmetatable(o, object)                                           "
        "    object.__index = object                                           "
        "                                                                      "
        "    instance.object = o                                               "
        "    o.instance = instance                                             "
        "    o.node = instance:GetNode()                                       "
        "                                                                      "
        "    local keys = {}                                                   "
        "    for k, v in pairs(o) do                                           "
        "        keys[k] = true                                                "
        "    end                                                               "
        "                                                                      "
        "    -- Call start function                                            "
        "    o:Start()                                                         "
        "                                                                      "
        "    local attrNames = {}                                              "
        "    for k, v in pairs(o) do                                           "
        "        if keys[k] == nil then                                        "
        "            table.insert(attrNames, k)                                "
        "        end                                                           "
        "    end                                                               "
        "                                                                      "
        "    return o, attrNames                                               "
        "end                                                                   "
        "                                                                      "
        "function DestroyScriptObjectInstance(instance)                        "
        "    local object = instance.object                                    "
        "    if object == nil then                                             "
        "        return                                                        "
        "    end                                                               "
        "                                                                      "
        "    -- Call stop function                                             "
        "    object:Stop()                                                     "
        "                                                                      "
        "    object.node = nil                                                 "
        "    object.instance = nil                                             "
        "    instance.object = nil                                             "
        "end                                                                   "
        );
}

static void LuaScriptSubscribeToEvent(const String& eventName, const String& functionName)
{
    LuaScript* luaScript = globalContext->GetSubsystem<LuaScript>();
    luaScript->AddEventHandler(eventName, functionName);
}

static void LuaScriptUnsubscribeFromEvent(const String& eventName, const String& functionName)
{
    LuaScript* luaScript = globalContext->GetSubsystem<LuaScript>();
    luaScript->RemoveEventHandler(eventName);
}

static void LuaScriptSubscribeToEvent(const String& eventName, const kaguya::LuaFunction& luaFunction)
{
    // LuaScript* luaScript = globalContext->GetSubsystem<LuaScript>();
    // luaScript->AddEventHandler(eventName, luaFunction);
}

static void LuaScriptUnsubscribeFromEvent(const String& eventName, const kaguya::LuaFunction& luaFunction)
{
    // LuaScript* luaScript = globalContext->GetSubsystem<LuaScript>();
    // luaScript->RemoveEventHandler(eventName, luaFunction);
}


void RegisterLuaScript(kaguya::State &lua)
{
    using namespace kaguya;

    lua["KSubscribeToEvent"] = overload(
        (void(*)(const String&, const String&))&LuaScriptSubscribeToEvent,
        (void(*)(const String&, const kaguya::LuaFunction&))&LuaScriptSubscribeToEvent);

    lua["KUnsubscribeFromEvent"] = overload(
        (void(*)(const String&, const String&))&LuaScriptUnsubscribeFromEvent,
        (void(*)(const String&, const kaguya::LuaFunction&))&LuaScriptUnsubscribeFromEvent);    
}

void RegisterLuaScriptLuaAPI(kaguya::State& lua)
{
    using namespace kaguya;

    RegisterLuaScriptInstance(lua);
    RegisterLuaScript(lua);

}

}
