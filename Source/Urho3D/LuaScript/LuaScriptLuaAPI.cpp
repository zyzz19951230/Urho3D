#include "../LuaScript/LuaScript.h"
#include "../LuaScript/LuaScriptInstance.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void RegisterCoroutine(kaguya::State &lua)
{
    // The following code copy from Coroutine.pkg file
    lua.dostring(
        "local totalTime_ = 0                                                \n"
        "local sleepedCoroutines_ = {}                                       \n"
        "local waitEventCoroutines_ = {}                                     \n"
        "function coroutine.start(func)                                      \n"
        "    if func == nil then                                             \n"
        "        return nil                                                  \n"
        "    end                                                             \n"
        "    local co = coroutine.create(func)                               \n"
        "    return coroutine.resume(co)                                     \n"
        "end                                                                 \n"
        "function coroutine.sleep(time)                                      \n"
        "    local co = coroutine.running()                                  \n"
        "    if co == nil then                                               \n"
        "        return                                                      \n"
        "    end                                                             \n"
        "    sleepedCoroutines_[co] = totalTime_ + time                      \n"
        "    return coroutine.yield(co)                                      \n"
        "end                                                                 \n"
        "function coroutine.update(steptime)                                 \n"
        "    totalTime_ = totalTime_ + steptime                              \n"
        "    local coroutines = {}                                           \n"
        "    for co, wakeupTime in pairs(sleepedCoroutines_) do              \n"
        "        if wakeupTime < totalTime_ then                             \n"
        "            table.insert(coroutines, co)                            \n"
        "        end                                                         \n"
        "    end                                                             \n"
        "    for _, co in ipairs(coroutines) do                              \n"
        "        sleepedCoroutines_[co] = nil                                \n"
        "        coroutine.resume(co)                                        \n"
        "    end                                                             \n"
        "end                                                                 \n"
        "function coroutine.waitevent(event)                                 \n"
        "    local co = coroutine.running()                                  \n"
        "    if co == nil then                                               \n"
        "        return                                                      \n"
        "    end                                                             \n"
        "    if waitEventCoroutines_[event] == nil then                      \n"
        "        waitEventCoroutines_[event] = { co }                        \n"
        "    else                                                            \n"
        "        table.insert(waitEventCoroutines_[event], co)               \n"
        "    end                                                             \n"
        "    return coroutine.yield(co)                                      \n"
        "end                                                                 \n"
        "function coroutine.sendevent(event)                                 \n"
        "    local coroutines = waitEventCoroutines_[event]                  \n"
        "    if coroutines == nil then                                       \n"
        "        return                                                      \n"
        "    end                                                             \n"
        "    waitEventCoroutines_[event] = nil                               \n"
        "                                                                    \n"
        "    for _, co in ipairs(coroutines) do                              \n"
        "        coroutine.resume(co)                                        \n"
        "    end                                                             \n"
        "end                                                                 \n"
    );
}

static void RegisterLuaScriptInstance(kaguya::State &lua)
{
    using namespace kaguya;

    // The following code copy from LuaScriptInstance.pkg file
    lua.dostring(
        "LuaScriptObject = {}                                                \n"
        "function LuaScriptObject:Start()                                    \n"
        "end                                                                 \n"
        "function LuaScriptObject:Stop()                                     \n"
        "end                                                                 \n"
        "function LuaScriptObject:GetNode()                                  \n"
        "    return self.node                                                \n"
        "end                                                                 \n"
        "function LuaScriptObject:SubscribeToEvent(param1, param2, param3)   \n"
        "    local instance = self.instance                                  \n"
        "    if instance == nil then                                         \n"
        "        return                                                      \n"
        "    end                                                             \n"
        "    if param3 == nil then                                           \n"
        "        instance:SubscribeToEvent(param1, param2)                   \n"
        "    else                                                            \n"
        "        instance:SubscribeToEvent(param1, param2, param3)           \n"
        "    end                                                             \n"
        "end                                                                 \n"
        "function LuaScriptObject:UnsubscribeFromEvent(param1, param2)       \n"
        "    local instance = self.instance                                  \n"
        "    if instance == nil then                                         \n"
        "        return                                                      \n"
        "    end                                                             \n"
        "    if param2 == nil then                                           \n"
        "        instance:UnsubscribeFromEvent(param1)                       \n"
        "    else                                                            \n"
        "        instance:UnsubscribeFromEvent(param1, param2)               \n"
        "    end                                                             \n"
        "end                                                                 \n"
        "function LuaScriptObject:UnsubscribeFromEvents(sender)              \n"
        "    local instance = self.instance                                  \n"
        "    if instance == nil then                                         \n"
        "        return                                                      \n"
        "    end                                                             \n"
        "    instance:UnsubscribeFromEvents(sender)                          \n"
        "end                                                                 \n"
        "function LuaScriptObject:UnsubscribeFromAllEvents()                 \n"
        "    local instance = self.instance                                  \n"
        "    if instance == nil then                                         \n"
        "        return                                                      \n"
        "    end                                                             \n"
        "    instance:UnsubscribeFromAllEvents()                             \n"
        "end                                                                 \n"
        "function LuaScriptObject:UnsubscribeFromAllEventsExcept()           \n"
        "    local instance = self.instance                                  \n"
        "    if instance == nil then                                         \n"
        "        return                                                      \n"
        "    end                                                             \n"
        "    instance:UnsubscribeFromAllEventsExcept()                       \n"
        "end                                                                 \n"
        "function LuaScriptObject:HasSubscribedToEvent(param1, param2)       \n"
        "    local instance = self.instance                                  \n"
        "    if instance == nil then                                         \n"
        "        return                                                      \n"
        "    end                                                             \n"
        "    if param2 == nil then                                           \n"
        "        return instance:HasSubscribedToEvent(param1)                \n"
        "    else                                                            \n"
        "        return instance:HasSubscribedToEvent(param1, param2)        \n"
        "    end                                                             \n"
        "end                                                                 \n"
        "function ScriptObject()                                             \n"
        "    local o = {}                                                    \n"
        "    setmetatable(o, LuaScriptObject)                                \n"
        "    LuaScriptObject.__index = LuaScriptObject                       \n"
        "    return o                                                        \n"
        "end                                                                 \n"
        "function CreateScriptObjectInstance(object, instance)               \n"
        "    local o = {}                                                    \n"
        "    setmetatable(o, object)                                         \n"
        "    object.__index = object                                         \n"
        "    o.instance = instance                                           \n"
        "    o.node = instance:GetNode()                                     \n"
        "    local keys = {}                                                 \n"
        "    for k, v in pairs(o) do                                         \n"
        "        keys[k] = true                                              \n"
        "    end                                                             \n"
        "    -- Call start function                                          \n"
        "    o:Start()                                                       \n"
        "    local attrNames = {}                                            \n"
        "    for k, v in pairs(o) do                                         \n"
        "        if keys[k] == nil then                                      \n"
        "            table.insert(attrNames, k)                              \n"
        "        end                                                         \n"
        "    end                                                             \n"
        "    return o, attrNames                                             \n"
        "end                                                                 \n"
    );

    lua["LuaScriptInstance"].setClass(UserdataMetatable<LuaScriptInstance, Component>()

        .addOverloadedFunctions("CreateObject", 
            static_cast<bool (LuaScriptInstance::*)(const String&)>(&LuaScriptInstance::CreateObject),
            static_cast<bool (LuaScriptInstance::*)(LuaFile*, const String&)>(&LuaScriptInstance::CreateObject))

        .addFunction("SetScriptFile", &LuaScriptInstance::SetScriptFile)
        .addFunction("SetScriptObjectType", &LuaScriptInstance::SetScriptObjectType)
        
        .addOverloadedFunctions("SubscribeToEvent",
            static_cast<void (LuaScriptInstance::*)(const String&, const String&)>(&LuaScriptInstance::AddEventHandler),
            static_cast<void (LuaScriptInstance::*)(Object*, const String&, const String&)>(&LuaScriptInstance::AddEventHandler))

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
}

static void LuaScriptSubscribeToEvent0(const String& eventName, const String& functionName)
{
    LuaScript* luaScript = globalContext->GetSubsystem<LuaScript>();
    luaScript->AddEventHandler(eventName, functionName);
}

static void LuaScriptSubscribeToEvent1(Object* sender, const String& eventName, const String& functionName)
{
    LuaScript* luaScript = globalContext->GetSubsystem<LuaScript>();
    luaScript->AddEventHandler(sender, eventName, functionName);
}

static void LuaScriptSubscribeToEvent2(const String& eventName, const kaguya::LuaFunction& function)
{
    LuaScript* luaScript = globalContext->GetSubsystem<LuaScript>();
    luaScript->AddEventHandler(eventName, 2); // 2 is the stack index of function
}

static void LuaScriptSubscribeToEvent3(Object* sender, const String& eventName, const kaguya::LuaFunction& function)
{
    LuaScript* luaScript = globalContext->GetSubsystem<LuaScript>();
    luaScript->AddEventHandler(sender, eventName, 3); // 3 is the stack index of function
}

static void LuaScriptUnsubscribeFromEvent0(const String& eventName, const String& functionName)
{
    LuaScript* luaScript = globalContext->GetSubsystem<LuaScript>();
    luaScript->RemoveEventHandler(eventName);
}

static void LuaScriptUnsubscribeFromEvent1(Object* sender, const String& eventName, const String& functionName)
{
    LuaScript* luaScript = globalContext->GetSubsystem<LuaScript>();
    luaScript->RemoveEventHandler(sender, eventName);
}

static void LuaScriptUnsubscribeFromEvent2(const String& eventName, const kaguya::LuaFunction& function)
{
    LuaScript* luaScript = globalContext->GetSubsystem<LuaScript>();
    luaScript->RemoveEventHandler(eventName);
}

static void LuaScriptUnsubscribeFromEvent3(Object* sender, const String& eventName, const kaguya::LuaFunction& function)
{
    LuaScript* luaScript = globalContext->GetSubsystem<LuaScript>();
    luaScript->RemoveEventHandler(sender, eventName);
}

void RegisterLuaScript(kaguya::State &lua)
{
    using namespace kaguya;

    lua["SubscribeToEvent"] = overload(&LuaScriptSubscribeToEvent0, 
        &LuaScriptSubscribeToEvent1,
        &LuaScriptSubscribeToEvent2,
        &LuaScriptSubscribeToEvent3);

    lua["UnsubscribeFromEvent"] = overload(&LuaScriptUnsubscribeFromEvent0,
        &LuaScriptUnsubscribeFromEvent1, 
        &LuaScriptUnsubscribeFromEvent2, 
        &LuaScriptUnsubscribeFromEvent3);
}

void RegisterLuaScriptLuaAPI(kaguya::State& lua)
{
    using namespace kaguya;

    RegisterCoroutine(lua);
    RegisterLuaScriptInstance(lua);
    RegisterLuaScript(lua);
}

}
