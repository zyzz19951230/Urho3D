#include "../LuaScript/LuaScript.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

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

void RegisterLuaScriptLuaAPI(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KSubscribeToEvent"] = overload(
        (void(*)(const String&, const String&))&LuaScriptSubscribeToEvent,
        (void(*)(const String&, const kaguya::LuaFunction&))&LuaScriptSubscribeToEvent);

    lua["KUnsubscribeFromEvent"] = overload(
        (void(*)(const String&, const String&))&LuaScriptUnsubscribeFromEvent,
        (void(*)(const String&, const kaguya::LuaFunction&))&LuaScriptUnsubscribeFromEvent);
}

}
