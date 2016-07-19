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

#include "../Core/Context.h"
#include "../Core/Object.h"
#include "../Core/ProcessUtils.h"
#include "../Core/Spline.h"
#include "../Core/StringUtils.h"
#include "../Core/Timer.h"
#include "../Core/Variant.h"
#include "../IO/VectorBuffer.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

extern Context* globalContext;

static Context* GlobalGetContext()
{
    return globalContext;
}

static SharedPtr<Object> GlobalGetEventSender()
{
    return SharedPtr<Object>(globalContext->GetEventSender());
}

static void RegisterContext(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Context"].setClass(UserdataMetatable<Context, RefCounted>()

        .addFunction("GetEventSender", &Context::GetEventSender)
        .addFunction("GetEventHandler", &Context::GetEventHandler)
        .addFunction("GetTypeName", &Context::GetTypeName)

        .addProperty("eventSender", &Context::GetEventSender)
        .addProperty("eventHandler", &Context::GetEventHandler)
    );

    lua["context"] = globalContext;
    lua["GetContext"] = GlobalGetContext();

    lua["GetEventSender"] = function(GlobalGetEventSender);
    // lua["GetEventHandler"] = function(GlobalGetEventHandler);
}

static void ObjectSendEvent0(Object* self, const String& eventName)
{
    self->SendEvent(StringHash(eventName));
}

static void ObjectSendEvent1(Object* self, const String& eventName, VariantMap* eventData)
{
    self->SendEvent(StringHash(eventName), *eventData);
}

static bool ObjectHasSubscribedToEvent0(const Object* self, const String& eventName)
{
    return self->HasSubscribedToEvent(StringHash(eventName));
}

static bool ObjectHasSubscribedToEvent1(const Object* self, Object* sender, const String& eventName)
{
    return self->HasSubscribedToEvent(sender, StringHash(eventName));
}

static void RegisterObject(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Object"].setClass(UserdataMetatable<Object, RefCounted>()

        .addFunction("GetType", &Object::GetType)
        .addFunction("GetTypeName", &Object::GetTypeName)
        .addFunction("GetCategory", &Object::GetCategory)

        ADD_OVERLOADED_FUNCTIONS_2(Object, SendEvent)
        ADD_OVERLOADED_FUNCTIONS_2(Object, HasSubscribedToEvent)

        .addProperty("type", &Object::GetType)
        .addProperty("typeName", &Object::GetTypeName)
        .addProperty("category", &Object::GetCategory)
    );
}

static void ErrorExit0()
{
    return ErrorExit();
}

static void ErrorExit1(const String& message)
{
    return ErrorExit(message);
}

static void ErrorExit2(const String& message, int exitCode)
{
    return ErrorExit(message, exitCode);
}


static void PrintLine0(const String& str)
{
    return PrintLine(str);
}

static void PrintLine1(const String& str, bool error)
{
    return PrintLine(str, error);
}

static void RegisterProcessUtils(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ErrorDialog"] = function(&ErrorDialog);

    lua["ErrorExit"] = overload(&ErrorExit0, &ErrorExit1, &ErrorExit2);

    lua["OpenConsoleWindow"] = function(&OpenConsoleWindow);

    lua["PrintLine"] = overload(&PrintLine0, &PrintLine1);

    lua["GetArguments"] = function(&GetArguments);

    lua["GetConsoleInput"] = function(&GetConsoleInput);
    lua["GetPlatform"] = function(&GetPlatform);

    lua["GetNumPhysicalCPUs"] = function(&GetNumPhysicalCPUs);
    lua["GetNumLogicalCPUs"] = function(&GetNumLogicalCPUs);

    lua["SetMiniDumpDir"] = function(&SetMiniDumpDir);
    lua["GetMiniDumpDir"] = function(&GetMiniDumpDir);
}

static void RegisterSpline(kaguya::State& lua)
{
    using namespace kaguya;

    // enum InterpolationMode;
    lua["BEZIER_CURVE"] = BEZIER_CURVE;
    lua["CATMULL_ROM_CURVE"] = CATMULL_ROM_CURVE;
    lua["LINEAR_CURVE"] = LINEAR_CURVE;
    lua["CATMULL_ROM_FULL_CURVE"] = CATMULL_ROM_FULL_CURVE;

    lua["Spline"].setClass(UserdataMetatable<Spline>()
        .setConstructors<Spline(),
        Spline(InterpolationMode)>()

        .addFunction("__eq", &Spline::operator==)

        .addFunction("SetInterpolationMode", &Spline::SetInterpolationMode)
        .addFunction("SetKnot", &Spline::SetKnot)
        
        .addOverloadedFunctions("AddKnot",
            static_cast<void(Spline::*)(const Variant&)>(&Spline::AddKnot),
            static_cast<void(Spline::*)(const Variant&, unsigned)>(&Spline::AddKnot))

        .addOverloadedFunctions("RemoveKnot",
            static_cast<void(Spline::*)()>(&Spline::RemoveKnot),
            static_cast<void(Spline::*)(unsigned)>(&Spline::RemoveKnot))
        .addFunction("Clear", &Spline::Clear)

        .addFunction("GetInterpolationMode", &Spline::GetInterpolationMode)
        .addFunction("GetKnot", &Spline::GetKnot)        
        .addFunction("GetPoint", &Spline::GetPoint)

        .addProperty("interpolationMode", &Spline::GetInterpolationMode, &Spline::SetInterpolationMode)
    );
}

static Vector4 ToVector40(const char* source)
{
    return ToVector4(source);
}

static Vector4 ToVector41(const char* source, bool allowMissingCoords)
{
    return ToVector4(source, allowMissingCoords);
}

static void RegisterStringUtils(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ToBool"] = static_cast<bool(*)(const char*)>(&ToBool);
    lua["ToFloat"] = static_cast<float(*)(const char*)>(&ToFloat);
    lua["ToDouble"] = static_cast<double(*)(const char*)>(&ToDouble);
    lua["ToInt"] = static_cast<int(*)(const char*)>(&ToInt);
    lua["ToUInt"] = static_cast<unsigned(*)(const char*)>(&ToUInt);
    
    lua["ToColor"] = static_cast<Color(*)(const char*)>(&ToColor);
    lua["ToIntRect"] = static_cast<IntRect(*)(const char*)>(&ToIntRect);
    lua["ToIntVector2"] = static_cast<IntVector2(*)(const char*)>(&ToIntVector2);
    lua["ToQuaternion"] = static_cast<Quaternion(*)(const char*)>(&ToQuaternion);
    lua["ToRect"] = static_cast<Rect(*)(const char*)>(&ToRect);
    lua["ToVector2"] = static_cast<Vector2(*)(const char*)>(&ToVector2);
    lua["ToVector3"] = static_cast<Vector3(*)(const char*)>(&ToVector3);    
    lua["ToVector4"] = overload(&ToVector40, &ToVector41);
    lua["ToMatrix3"] = static_cast<Matrix3(*)(const char*)>(&ToMatrix3);
    lua["ToMatrix3x4"] = static_cast<Matrix3x4(*)(const char*)>(&ToMatrix3x4);
    lua["ToMatrix4"] = static_cast<Matrix4(*)(const char*)>(&ToMatrix4);

    lua["ToStringHex"] = function(&ToStringHex);

    lua["IsAlpha"] = function(&IsAlpha);
    lua["IsDigit"] = function(&IsDigit);
    lua["ToUpper"] = function(&ToUpper);
    lua["ToLower"] = function(&ToLower);
}

static void RegisterTimer(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Time"].setClass(UserdataMetatable<Time, Object>()

        .addFunction("GetFrameNumber", &Time::GetFrameNumber)
        .addFunction("GetTimeStep", &Time::GetTimeStep)
        .addFunction("GetTimerPeriod", &Time::GetTimerPeriod)
        .addFunction("GetElapsedTime", &Time::GetElapsedTime)

        .addStaticFunction("GetSystemTime", &Time::GetSystemTime)
        .addStaticFunction("GetTimeSinceEpoch", &Time::GetTimeSinceEpoch)
        .addStaticFunction("GetTimeStamp", &Time::GetTimeStamp)
        .addStaticFunction("Sleep", &Time::GetTimeStamp)

        .addProperty("frameNumber", &Time::GetFrameNumber)
        .addProperty("timeStep", &Time::GetTimeStep)
        .addProperty("timerPeriod", &Time::GetTimerPeriod)
        .addProperty("elapsedTime", &Time::GetElapsedTime)
    );
}

static SharedPtr<RefCounted> VariantGetPtr(const Variant* self)
{
    return SharedPtr<RefCounted>(self->GetPtr());
}

static void RegisterVariant(kaguya::State& lua)
{
    using namespace kaguya;

    // enum VariantType;
    lua["VAR_NONE"] = VAR_NONE;
    lua["VAR_INT"] = VAR_INT;
    lua["VAR_BOOL"] = VAR_BOOL;
    lua["VAR_FLOAT"] = VAR_FLOAT;
    lua["VAR_VECTOR2"] = VAR_VECTOR2;
    lua["VAR_VECTOR3"] = VAR_VECTOR3;
    lua["VAR_VECTOR4"] = VAR_VECTOR4;
    lua["VAR_QUATERNION"] = VAR_QUATERNION;
    lua["VAR_COLOR"] = VAR_COLOR;
    lua["VAR_STRING"] = VAR_STRING;
    lua["VAR_BUFFER"] = VAR_BUFFER;
    lua["VAR_VOIDPTR"] = VAR_VOIDPTR;
    lua["VAR_RESOURCEREF"] = VAR_RESOURCEREF;
    lua["VAR_RESOURCEREFLIST"] = VAR_RESOURCEREFLIST;
    lua["VAR_VARIANTVECTOR"] = VAR_VARIANTVECTOR;
    lua["VAR_VARIANTMAP"] = VAR_VARIANTMAP;
    lua["VAR_INTRECT"] = VAR_INTRECT;
    lua["VAR_INTVECTOR2"] = VAR_INTVECTOR2;
    lua["VAR_PTR"] = VAR_PTR;
    lua["VAR_MATRIX3"] = VAR_MATRIX3;
    lua["VAR_MATRIX3X4"] = VAR_MATRIX3X4;
    lua["VAR_MATRIX4"] = VAR_MATRIX4;
    lua["VAR_DOUBLE"] = VAR_DOUBLE;
    lua["VAR_STRINGVECTOR"] = VAR_STRINGVECTOR;
    lua["MAX_VAR_TYPES"] = MAX_VAR_TYPES;

    lua["ResourceRef"].setClass(UserdataMetatable<ResourceRef>()
        .setConstructors<ResourceRef(),
        ResourceRef(StringHash),
        ResourceRef(StringHash, const String&),
        ResourceRef(const char*, const char*)>()

        .addFunction("__eq", &ResourceRef::operator==)

        .addProperty("type", &ResourceRef::type_)
        .addProperty("name", &ResourceRef::name_)
    );

    lua["ResourceRefList"].setClass(UserdataMetatable<ResourceRefList>()
        .setConstructors<ResourceRefList(),
        ResourceRefList(StringHash)>()

        .addFunction("__eq", &ResourceRefList::operator==)

        .addProperty("type", &ResourceRefList::type_)
    );

    // todo from here:
    lua["Variant"].setClass(UserdataMetatable<Variant>()
        .setConstructors<Variant(),
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
        Variant(const Matrix4&)> ()

        .addFunction("Clear", &Variant::Clear)

        .addFunction("__eq", static_cast<bool(Variant::*)(const Variant&) const>(&Variant::operator==))

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

        .addFunction("GetRawBuffer", &Variant::GetBuffer)
        .addFunction("GetBuffer", &Variant::GetVectorBuffer)
        .addFunction("GetVoidPtr", &Variant::GetVoidPtr)

        .addFunction("GetResourceRef", &Variant::GetResourceRef)
        .addFunction("GetResourceRefList", &Variant::GetResourceRefList)
        .addFunction("GetVariantVector", &Variant::GetVariantVector)
        .addFunction("GetStringVector", &Variant::GetStringVector)
        .addFunction("GetVariantMap", &Variant::GetVariantMap)
        .addFunction("GetIntRect", &Variant::GetIntRect)
        .addFunction("GetIntVector2", &Variant::GetIntVector2)
        
        .addStaticFunction("GetPtr", &VariantGetPtr)

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
    );
}

static const Variant& VariantMapGetVariant(const VariantMap& variantMap, const char* key)
{
    VariantMap::ConstIterator i = variantMap.Find(StringHash(key));
    if (i == variantMap.End())
        return Variant::EMPTY;

    return i->second_;
}

static void VariantMapSetVariant(VariantMap& variantMap, const char* key, const Variant& value)
{
    variantMap[StringHash(key)] = value;
}

static void RegisterVariantMap(kaguya::State& lua)
{
    using namespace kaguya;

    lua["VariantMap"].setClass(UserdataMetatable<VariantMap>()
        .setConstructors<VariantMap()>()

        .addStaticFunction("__index", &VariantMapGetVariant)
        .addStaticFunction("__newindex", &VariantMapSetVariant)
        );
}

void RegisterCoreLuaAPI(kaguya::State& lua)
{
    RegisterContext(lua);
    RegisterObject(lua);
    RegisterProcessUtils(lua);
    RegisterSpline(lua);
    RegisterStringUtils(lua);
    RegisterTimer(lua);
    RegisterVariant(lua);
    RegisterVariantMap(lua);

    lua["time"] = GetSubsystem<Time>();
    lua["GetTime"] = GetSubsystem<Time>;
}
}
