#include "../Core/Attribute.h"
#include "../Core/Context.h"
#include "../Core/CoreEvents.h"
#include "../Core/Object.h"
#include "../Core/ProcessUtils.h"
#include "../Core/Spline.h"
#include "../Core/StringUtils.h"
#include "../Core/Timer.h"
#include "../Core/Variant.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{
extern Context* globalContext;

static Time* GetTime()
{
    return globalContext->GetSubsystem<Time>();
}

static void RegisterAttribute(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KAM_EDIT"] = AM_EDIT;
    lua["KAM_FILE"] = AM_FILE;
    lua["KAM_NET"] = AM_NET;
    lua["KAM_DEFAULT"] = AM_DEFAULT;
    lua["KAM_LATESTDATA"] = AM_LATESTDATA;
    lua["KAM_NOEDIT"] = AM_NOEDIT;
    lua["KAM_NODEID"] = AM_NODEID;
    lua["KAM_COMPONENTID"] = AM_COMPONENTID;
    lua["KAM_NODEIDVECTOR"] = AM_NODEIDVECTOR;

    lua["KAttributeInfo"].setClass(UserdataMetatable<AttributeInfo>()
        .setConstructors<AttributeInfo(),
        AttributeInfo(VariantType, const char*, AttributeAccessor*, const Variant&, unsigned),
        AttributeInfo(const char*, AttributeAccessor*, const char**, const Variant&, unsigned)>()

        .addProperty("type", &AttributeInfo::type_)
        .addProperty("name", &AttributeInfo::name_)

        .addProperty("enumNames", &AttributeInfo::enumNames_)
        .addProperty("defaultValue", &AttributeInfo::defaultValue_)
        .addProperty("mode", &AttributeInfo::mode_)
    );
}

static void RegisterContext(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KContext"].setClass(UserdataMetatable<Context, RefCounted>()

        .addFunction("GetEventDataMap", &Context::GetEventDataMap)
        .addFunction("GetGlobalVar", &Context::GetGlobalVar)
        .addFunction("GetGlobalVars", &Context::GetGlobalVars)
        .addFunction("SetGlobalVar", &Context::SetGlobalVar)
        .addFunction("GetEventSender", &Context::GetEventSender)
        .addFunction("GetEventHandler", &Context::GetEventHandler)
        .addFunction("GetTypeName", &Context::GetTypeName)

        .addProperty("eventDataMap", &Context::GetEventDataMap)
        .addProperty("globalVars", &Context::GetGlobalVars)
        .addProperty("eventSender", &Context::GetEventSender)
        .addProperty("eventHandler", &Context::GetEventHandler)
    );
}

static void RegisterCoreEvents(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KE_BEGINFRAME"] = E_BEGINFRAME;
    lua["KE_UPDATE"] = E_UPDATE;
    lua["KE_POSTUPDATE"] = E_POSTUPDATE;
    lua["KE_RENDERUPDATE"] = E_RENDERUPDATE;
    lua["KE_POSTRENDERUPDATE"] = E_POSTRENDERUPDATE;
    lua["KE_ENDFRAME"] = E_ENDFRAME;
}

static void RegisterObject(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KObject"].setClass(UserdataMetatable<Object, RefCounted>(false)
        .addFunction("GetType", &Object::GetType)
        .addFunction("GetTypeName", &Object::GetTypeName)
        .addFunction("GetTypeInfo", &Object::GetTypeInfo)
        
        /*
        .addOverloadedFunctions("IsTypeOf",
            static_cast<bool(Object::*)(StringHash)>(&Object::IsTypeOf),
            static_cast<bool(Object::*)(const TypeInfo*)>(&Object::IsTypeOf))

        .addOverloadedFunctions("IsInstanceOf",
            static_cast<bool(Object::*)(StringHash) const>(&Object::IsInstanceOf),
            static_cast<bool(Object::*)(const TypeInfo*) const>(&Object::IsInstanceOf))

        .addOverloadedFunctions("SubscribeToEvent",
            static_cast<void(Object::*)(StringHash, EventHandler*)>(&Object::SubscribeToEvent),
            static_cast<void(Object::*)(Object*, StringHash, EventHandler*)>(&Object::SubscribeToEvent))

        .addOverloadedFunctions("UnsubscribeFromEvent",
            static_cast<void(Object::*)(StringHash)>(&Object::UnsubscribeFromEvent),
            static_cast<void(Object::*)(Object*, StringHash)>(&Object::UnsubscribeFromEvent))

        .addFunction("UnsubscribeFromEvents", &Object::UnsubscribeFromEvents)
        .addFunction("UnsubscribeFromAllEvents", &Object::UnsubscribeFromAllEvents)
        .addFunction("UnsubscribeFromAllEventsExcept", &Object::UnsubscribeFromAllEventsExcept)
        */

        .addOverloadedFunctions("SendEvent",
            static_cast<void(Object::*)(StringHash)>(&Object::SendEvent),
            static_cast<void(Object::*)(StringHash, VariantMap&)>(&Object::SendEvent))

        .addFunction("GetEventDataMap", &Object::GetEventDataMap)

        .addFunction("GetContext", &Object::GetContext)
        .addFunction("GetGlobalVar", &Object::GetGlobalVar)
        .addFunction("GetGlobalVars", &Object::GetGlobalVars)
        .addFunction("SetGlobalVar", &Object::SetGlobalVar)
        .addFunction("GetEventSender", &Object::GetEventSender)
        .addFunction("GetEventHandler", &Object::GetEventHandler)

        /*
        .addOverloadedFunctions("HasSubscribedToEvent",
            static_cast<bool(Object::*)(StringHash) const>(&Object::HasSubscribedToEvent),
            static_cast<bool(Object::*)(Object*, StringHash) const>(&Object::HasSubscribedToEvent))
            */

        .addFunction("HasEventHandlers", &Object::HasEventHandlers)
        .addFunction("GetCategory", &Object::GetCategory)

        .addProperty("type", &Object::GetType)
        .addProperty("typeName", &Object::GetTypeName)
        .addProperty("typeInfo", &Object::GetTypeInfo)
        .addProperty("eventDataMap", &Object::GetEventDataMap)
        .addProperty("context", &Object::GetContext)
        .addProperty("globalVars", &Object::GetGlobalVars)
        .addProperty("eventSender", &Object::GetEventSender)
        .addProperty("eventHandler", &Object::GetEventHandler)
        .addProperty("category", &Object::GetCategory)
    );
}

static void RegisterProcessUtils(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KErrorDialog"] = function(&ErrorDialog);
    lua["KErrorExit"] = function(&ErrorExit);
    lua["KOpenConsoleWindow"] = function(&OpenConsoleWindow);

    lua["KPrintLine"] = function(&PrintLine);

    lua["KGetArguments"] = function(&GetArguments);
    lua["KGetConsoleInput"] = function(&GetConsoleInput);
    lua["KGetPlatform"] = function(&GetPlatform);

    lua["KGetNumPhysicalCPUs"] = function(&GetNumPhysicalCPUs);
    lua["KGetNumLogicalCPUs"] = function(&GetNumLogicalCPUs);
    lua["KSetMiniDumpDir"] = function(&SetMiniDumpDir);
}

static void RegisterSpline(kaguya::State& lua)
{
    using namespace kaguya;

    // enum InterpolationMode;
    lua["KBEZIER_CURVE"] = BEZIER_CURVE;
    lua["KCATMULL_ROM_CURVE"] = CATMULL_ROM_CURVE;
    lua["KLINEAR_CURVE"] = LINEAR_CURVE;
    lua["KCATMULL_ROM_FULL_CURVE"] = CATMULL_ROM_FULL_CURVE;

    lua["KSpline"].setClass(UserdataMetatable<Spline>()
        .setConstructors<Spline(),
        Spline(InterpolationMode),
        Spline(const Vector<Variant>&, InterpolationMode),
        Spline(const Spline&)>()

        .addFunction("__eq", &Spline::operator==)

        .addFunction("GetInterpolationMode", &Spline::GetInterpolationMode)
        .addFunction("GetKnots", &Spline::GetKnots)
        .addFunction("GetKnot", &Spline::GetKnot)
        .addFunction("GetPoint", &Spline::GetPoint)
        .addFunction("SetInterpolationMode", &Spline::SetInterpolationMode)
        .addFunction("SetKnots", &Spline::SetKnots)
        .addFunction("SetKnot", &Spline::SetKnot)

        .addOverloadedFunctions("AddKnot",
            static_cast<void(Spline::*)(const Variant&)>(&Spline::AddKnot),
            static_cast<void(Spline::*)(const Variant&, unsigned)>(&Spline::AddKnot))


        .addOverloadedFunctions("RemoveKnot",
            static_cast<void(Spline::*)()>(&Spline::RemoveKnot),
            static_cast<void(Spline::*)(unsigned)>(&Spline::RemoveKnot))

        .addFunction("Clear", &Spline::Clear)

        .addProperty("interpolationMode", &Spline::GetInterpolationMode, &Spline::SetInterpolationMode)
        .addProperty("knots", &Spline::GetKnots, &Spline::SetKnots)
    );
}

static void RegisterStringUtils(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KToBool"] = static_cast<bool(*)(const char*)>(&ToBool);
    lua["KToFloat"] = static_cast<float(*)(const char*)>(&ToFloat);
    lua["KToDouble"] = static_cast<double(*)(const char*)>(&ToDouble);
    lua["KToInt"] = static_cast<int(*)(const char*)>(&ToInt);
    lua["KToUInt"] = static_cast<unsigned(*)(const char*)>(&ToUInt);
    lua["KToColor"] = static_cast<Color(*)(const char*)>(&ToColor);
    lua["KToIntRect"] = static_cast<IntRect(*)(const char*)>(&ToIntRect);
    lua["KToIntVector2"] = static_cast<IntVector2(*)(const char*)>(&ToIntVector2);
    lua["KToQuaternion"] = static_cast<Quaternion(*)(const char*)>(&ToQuaternion);
    lua["KToRect"] = static_cast<Rect(*)(const char*)>(&ToRect);
    lua["KToVector2"] = static_cast<Vector2(*)(const char*)>(&ToVector2);
    lua["KToVector3"] = static_cast<Vector3(*)(const char*)>(&ToVector3);
    lua["KToVector4"] = static_cast<Vector4(*)(const char*, bool)>(&ToVector4);
    lua["KToVectorVariant"] = static_cast<Variant(*)(const char*)>(&ToVectorVariant);
    lua["KToMatrix3"] = static_cast<Matrix3(*)(const char*)>(&ToMatrix3);
    lua["KToMatrix3x4"] = static_cast<Matrix3x4(*)(const char*)>(&ToMatrix3x4);
    lua["KToMatrix4"] = static_cast<Matrix4(*)(const char*)>(&ToMatrix4);

    lua["KToStringHex"] = function(&ToStringHex);

    lua["KIsAlpha"] = function(&IsAlpha);
    lua["KIsDigit"] = function(&IsDigit);
    lua["KToUpper"] = function(&ToUpper);
    lua["KToLower"] = function(&ToLower);
    lua["KGetFileSizeString"] = function(&GetFileSizeString);
}

static void RegisterTimer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KTimer"].setClass(UserdataMetatable<Timer>()
        .setConstructors<Timer()>()

        .addFunction("GetMSec", &Timer::GetMSec)
        .addFunction("Reset", &Timer::Reset)
    );

    // GC is disable for subsystem object
    lua["KTime"].setClass(UserdataMetatable<Time, Object>(false)
        
        .addFunction("GetFrameNumber", &Time::GetFrameNumber)
        .addFunction("GetTimeStep", &Time::GetTimeStep)
        .addFunction("GetElapsedTime", &Time::GetElapsedTime)
        .addStaticFunction("GetSystemTime", &Time::GetSystemTime)
        .addStaticFunction("GetTimeSinceEpoch", &Time::GetTimeSinceEpoch)
        .addStaticFunction("GetTimeStamp", &Time::GetTimeStamp)

        .addProperty("frameNumber", &Time::GetFrameNumber)
        .addProperty("timeStep", &Time::GetTimeStep)
        .addProperty("elapsedTime", &Time::GetElapsedTime)
    );
}

static void RegisterVariant(kaguya::State& lua)
{
    using namespace kaguya;

    // enum VariantType;
    lua["KVAR_NONE"] = VAR_NONE;
    lua["KVAR_INT"] = VAR_INT;
    lua["KVAR_BOOL"] = VAR_BOOL;
    lua["KVAR_FLOAT"] = VAR_FLOAT;
    lua["KVAR_VECTOR2"] = VAR_VECTOR2;
    lua["KVAR_VECTOR3"] = VAR_VECTOR3;
    lua["KVAR_VECTOR4"] = VAR_VECTOR4;
    lua["KVAR_QUATERNION"] = VAR_QUATERNION;
    lua["KVAR_COLOR"] = VAR_COLOR;
    lua["KVAR_STRING"] = VAR_STRING;
    lua["KVAR_BUFFER"] = VAR_BUFFER;
    lua["KVAR_VOIDPTR"] = VAR_VOIDPTR;
    lua["KVAR_RESOURCEREF"] = VAR_RESOURCEREF;
    lua["KVAR_RESOURCEREFLIST"] = VAR_RESOURCEREFLIST;
    lua["KVAR_VARIANTVECTOR"] = VAR_VARIANTVECTOR;
    lua["KVAR_VARIANTMAP"] = VAR_VARIANTMAP;
    lua["KVAR_INTRECT"] = VAR_INTRECT;
    lua["KVAR_INTVECTOR2"] = VAR_INTVECTOR2;
    lua["KVAR_PTR"] = VAR_PTR;
    lua["KVAR_MATRIX3"] = VAR_MATRIX3;
    lua["KVAR_MATRIX3X4"] = VAR_MATRIX3X4;
    lua["KVAR_MATRIX4"] = VAR_MATRIX4;
    lua["KVAR_DOUBLE"] = VAR_DOUBLE;
    lua["KVAR_STRINGVECTOR"] = VAR_STRINGVECTOR;
    lua["KMAX_VAR_TYPES"] = MAX_VAR_TYPES;

    lua["KResourceRef"].setClass(UserdataMetatable<ResourceRef>()
        .setConstructors<ResourceRef(),
        ResourceRef(StringHash),
        ResourceRef(StringHash, const String&),
        ResourceRef(const char*, const char*),
        ResourceRef(const ResourceRef&)>()

        .addFunction("__eq", &ResourceRef::operator==)

        .addProperty("type", &ResourceRef::type_)
        .addProperty("name", &ResourceRef::name_)
    );

    lua["KResourceRefList"].setClass(UserdataMetatable<ResourceRefList>()
        .setConstructors<ResourceRefList(),
        ResourceRefList(StringHash),
        ResourceRefList(StringHash, const StringVector&)>()

        .addFunction("__eq", &ResourceRefList::operator==)

        .addProperty("type", &ResourceRefList::type_)
        .addProperty("names", &ResourceRefList::names_)
    );

    lua["KVariant"].setClass(UserdataMetatable<Variant>()
        .setConstructors < Variant(),
        Variant(int),
        Variant(unsigned),
        Variant(const StringHash&),
        Variant(bool),
        Variant(float),
        Variant(double),
        Variant(const Vector2&),
        Variant(const Vector3&),
        Variant(const Vector4&),
        Variant(const Quaternion&),
        Variant(const Color&),
        Variant(const char*),
        Variant(const ResourceRef&),
        Variant(const ResourceRefList&),
        Variant(const VariantVector&),
        Variant(const VariantMap&),
        Variant(const StringVector&),
        Variant(const IntRect&),
        Variant(const IntVector2&),
        Variant(RefCounted*),
        Variant(const Matrix3&),
        Variant(const Matrix3x4&),
        Variant(const Matrix4&),
        Variant(const String&, const String&),
        Variant(VariantType, const String&),
        Variant(const char*, const char*),
        Variant(VariantType, const char*),
        Variant(const Variant&) > ()

        .addFunction("Clear", &Variant::Clear)

        .addOverloadedFunctions("__eq",
            static_cast<bool(Variant::*)(const Variant&) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(int) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(unsigned) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(bool) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(float) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(double) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(const Vector2&) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(const Vector3&) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(const Vector4&) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(const Quaternion&) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(const Color&) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(const String&) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(const ResourceRef&) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(const ResourceRefList&) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(const VariantVector&) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(const StringVector&) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(const VariantMap&) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(const IntRect&) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(const IntVector2&) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(const StringHash&) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(RefCounted*) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(const Matrix3&) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(const Matrix3x4&) const>(&Variant::operator==),
            static_cast<bool(Variant::*)(const Matrix4&) const>(&Variant::operator==))


        .addOverloadedFunctions("FromString",
            static_cast<void(Variant::*)(const char*, const char*)>(&Variant::FromString),
            static_cast<void(Variant::*)(VariantType, const char*)>(&Variant::FromString))

        .addStaticFunction("SetInt", [](Variant& variant, int value) { variant = value; })
        .addStaticFunction("SetUInt", [](Variant& variant, unsigned value) { variant = value; })
        .addStaticFunction("SetStringHash", [](Variant& variant, StringHash value) { variant = value; })
        .addStaticFunction("SetBool", [](Variant& variant, bool value) { variant = value; })
        .addStaticFunction("SetFloat", [](Variant& variant, float value) { variant = value; })
        .addStaticFunction("SetDouble", [](Variant& variant, double value) { variant = value; })
        .addStaticFunction("SetVector2", [](Variant& variant, const Vector2& value) { variant = value; })
        .addStaticFunction("SetVector3", [](Variant& variant, const Vector3& value) { variant = value; })
        .addStaticFunction("SetVector4", [](Variant& variant, const Vector4& value) { variant = value; })
        .addStaticFunction("SetQuaternion", [](Variant& variant, const Quaternion& value) { variant = value; })
        .addStaticFunction("SetColor", [](Variant& variant, const Color& value) { variant = value; })
        .addStaticFunction("SetString", [](Variant& variant, const String& value) { variant = value; })
        .addStaticFunction("SetResourceRef", [](Variant& variant, const ResourceRef& value) { variant = value; })
        .addStaticFunction("SetResourceRefList", [](Variant& variant, const ResourceRefList& value) { variant = value; })
        .addStaticFunction("SetVariantVector", [](Variant& variant, const VariantVector& value) { variant = value; })
        .addStaticFunction("SetStringVector", [](Variant& variant, const StringVector& value) { variant = value; })
        .addStaticFunction("SetVariantMap", [](Variant& variant, const VariantMap& value) { variant = value; })
        .addStaticFunction("SetIntRect", [](Variant& variant, const IntRect& value) { variant = value; })
        .addStaticFunction("SetIntVector2", [](Variant& variant, const IntVector2& value) { variant = value; })
        .addStaticFunction("SetPtr", [](Variant& variant, RefCounted* value) { variant = value; })
        .addStaticFunction("SetMatrix3", [](Variant& variant, const Matrix3& value) { variant = value; })
        .addStaticFunction("SetMatrix3x4", [](Variant& variant, const Matrix3x4& value) { variant = value; })
        .addStaticFunction("SetMatrix4", [](Variant& variant, const Matrix4& value) { variant = value; })

        .addFunction("GetInt", &Variant::GetInt)
        .addFunction("GetUInt", &Variant::GetUInt)
        .addFunction("GetStringHash", &Variant::GetStringHash)
        .addFunction("GetBool", &Variant::GetBool)
        .addFunction("GetFloat", &Variant::GetFloat)
        .addFunction("GetDouble", &Variant::GetDouble)
        .addFunction("GetVector2", &Variant::GetVector2)
        .addFunction("GetVector3", &Variant::GetVector3)
        .addFunction("GetVector4", &Variant::GetVector4)
        .addFunction("GetQuaternion", &Variant::GetQuaternion)
        .addFunction("GetColor", &Variant::GetColor)
        .addFunction("GetString", &Variant::GetString)
        .addFunction("GetResourceRef", &Variant::GetResourceRef)
        .addFunction("GetResourceRefList", &Variant::GetResourceRefList)
        .addFunction("GetVariantVector", &Variant::GetVariantVector)
        .addFunction("GetStringVector", &Variant::GetStringVector)
        .addFunction("GetVariantMap", &Variant::GetVariantMap)
        .addFunction("GetIntRect", &Variant::GetIntRect)
        .addFunction("GetIntVector2", &Variant::GetIntVector2)
        .addFunction("GetPtr", &Variant::GetPtr)
        .addFunction("GetMatrix3", &Variant::GetMatrix3)
        .addFunction("GetMatrix3x4", &Variant::GetMatrix3x4)
        .addFunction("GetMatrix4", &Variant::GetMatrix4)

        .addFunction("GetType", &Variant::GetType)
        .addFunction("GetTypeName", static_cast<String(Variant::*)() const>(&Variant::GetTypeName))
        .addFunction("ToString", &Variant::ToString)

        .addFunction("IsZero", &Variant::IsZero)
        .addFunction("IsEmpty", &Variant::IsEmpty)

        .addProperty("type", &Variant::GetType)
        .addProperty("typeName", static_cast<String(Variant::*)() const>(&Variant::GetTypeName))

        .addProperty("zero", &Variant::IsZero)
        .addProperty("empty", &Variant::IsEmpty)

        .addStaticField("EMPTY", &Variant::EMPTY)
        .addStaticField("emptyBuffer", &Variant::emptyBuffer)
        .addStaticField("emptyResourceRef", &Variant::emptyResourceRef)
        .addStaticField("emptyResourceRefList", &Variant::emptyResourceRefList)
        .addStaticField("emptyVariantMap", &Variant::emptyVariantMap)
        .addStaticField("emptyVariantVector", &Variant::emptyVariantVector)
        .addStaticField("emptyStringVector", &Variant::emptyStringVector)
    );
}

void RegisterCoreLuaAPI(kaguya::State& lua)
{
    RegisterAttribute(lua);
    RegisterContext(lua);
    RegisterCoreEvents(lua);
    RegisterObject(lua);
    RegisterProcessUtils(lua);
    RegisterSpline(lua);
    RegisterStringUtils(lua);
    RegisterTimer(lua);
    RegisterVariant(lua);

    lua["ktime"] = GetTime();
    lua["KGetTime"] = GetTime;
}
}
