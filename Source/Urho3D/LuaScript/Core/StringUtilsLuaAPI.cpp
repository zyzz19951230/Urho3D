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

#include "../../Core/StringUtils.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_FUNCTION_OVERLOADS_WITH_SIGNATURE(ToIntOverloads, ToInt, 1, 2, int(const char*, int));
KAGUYA_FUNCTION_OVERLOADS_WITH_SIGNATURE(ToUIntOverloads, ToUInt, 1, 2, int(const char*, int));

KAGUYA_FUNCTION_OVERLOADS_WITH_SIGNATURE(ToVector4Overloads, ToVector4, 1, 2, Vector4(const char*, bool));

void RegisterStringUtils(kaguya::State& lua)
{
    using namespace kaguya;

    // [Function] bool ToBool(const char* source)
    lua["ToBool"] = static_cast<bool(*)(const char*)>(&ToBool);
    // [Function] float ToFloat(const char* source)
    lua["ToFloat"] = static_cast<float(*)(const char*)>(&ToFloat);
    // [Function] double ToDouble(const char* source)
    lua["ToDouble"] = static_cast<double(*)(const char*)>(&ToDouble);
    // [Function] int ToInt(const char* source, int base = 10)
    lua["ToInt"] = ToIntOverloads();
    // [Function] int ToUInt(const char* source, int base = 10)
    lua["ToUInt"] = ToUIntOverloads();

    // [Function] Color ToColor(const char* source)
    lua["ToColor"] = static_cast<Color(*)(const char*)>(&ToColor);
    // [Function] IntRect ToIntRect(const char* source)
    lua["ToIntRect"] = static_cast<IntRect(*)(const char*)>(&ToIntRect);
    // [Function] IntVector2 ToIntVector2(const char* source)
    lua["ToIntVector2"] = static_cast<IntVector2(*)(const char*)>(&ToIntVector2);
    // [Function] Quaternion ToQuaternion(const char* source)
    lua["ToQuaternion"] = static_cast<Quaternion(*)(const char*)>(&ToQuaternion);
    // [Function] Rect ToRect(const char* source)
    lua["ToRect"] = static_cast<Rect(*)(const char*)>(&ToRect);
    
    // [Function] Vector2 ToVector2(const char* source)
    lua["ToVector2"] = static_cast<Vector2(*)(const char*)>(&ToVector2);
    // [Function] Vector3 ToVector3(const char* source)
    lua["ToVector3"] = static_cast<Vector3(*)(const char*)>(&ToVector3);        
    // [Function] Vector4 ToVector4(const char* source, bool allowMissingCoords)
    lua["ToVector4"] = ToVector4Overloads();
    // [Function] Matrix3 ToMatrix3(const char* source)
    lua["ToMatrix3"] = static_cast<Matrix3(*)(const char*)>(&ToMatrix3);
    // [Function] Matrix3x4 ToMatrix3x4(const char* source)
    lua["ToMatrix3x4"] = static_cast<Matrix3x4(*)(const char*)>(&ToMatrix3x4);
    // [Function] Matrix4 ToMatrix4(const char* source)
    lua["ToMatrix4"] = static_cast<Matrix4(*)(const char*)>(&ToMatrix4);

    // [Function] String ToStringHex(unsigned value)
    lua["ToStringHex"] = function(&ToStringHex);

    // [Function] bool IsAlpha(unsigned ch)
    lua["IsAlpha"] = function(&IsAlpha);
    // [Function] bool IsDigit(unsigned ch)
    lua["IsDigit"] = function(&IsDigit);
    // [Function] unsigned ToUpper(unsigned ch)
    lua["ToUpper"] = function(&ToUpper);
    // [Function] unsigned ToLower(unsigned ch)
    lua["ToLower"] = function(&ToLower);
}
}

