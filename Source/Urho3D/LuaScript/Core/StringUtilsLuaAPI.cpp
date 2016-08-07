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

    lua["ToBool"] = static_cast<bool(*)(const char*)>(&ToBool);
    lua["ToFloat"] = static_cast<float(*)(const char*)>(&ToFloat);
    lua["ToDouble"] = static_cast<double(*)(const char*)>(&ToDouble);
    lua["ToInt"] = ToIntOverloads();
    lua["ToUInt"] = ToUIntOverloads();
    
    lua["ToColor"] = static_cast<Color(*)(const char*)>(&ToColor);
    lua["ToIntRect"] = static_cast<IntRect(*)(const char*)>(&ToIntRect);
    lua["ToIntVector2"] = static_cast<IntVector2(*)(const char*)>(&ToIntVector2);
    lua["ToQuaternion"] = static_cast<Quaternion(*)(const char*)>(&ToQuaternion);
    lua["ToRect"] = static_cast<Rect(*)(const char*)>(&ToRect);
    lua["ToVector2"] = static_cast<Vector2(*)(const char*)>(&ToVector2);
    lua["ToVector3"] = static_cast<Vector3(*)(const char*)>(&ToVector3);    
    
    lua["ToVector4"] = ToVector4Overloads();

    lua["ToMatrix3"] = static_cast<Matrix3(*)(const char*)>(&ToMatrix3);
    lua["ToMatrix3x4"] = static_cast<Matrix3x4(*)(const char*)>(&ToMatrix3x4);
    lua["ToMatrix4"] = static_cast<Matrix4(*)(const char*)>(&ToMatrix4);

    lua["ToStringHex"] = function(&ToStringHex);

    lua["IsAlpha"] = function(&IsAlpha);
    lua["IsDigit"] = function(&IsDigit);
    lua["ToUpper"] = function(&ToUpper);
    lua["ToLower"] = function(&ToLower);
}
}

