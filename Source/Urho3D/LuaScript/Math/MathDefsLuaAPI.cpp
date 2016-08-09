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

#include "../../Math/MathDefs.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterMathDefs(kaguya::State& lua)
{
    using namespace kaguya;

    // [Constant] float M_HALF_PI
    lua["M_PI"] = M_PI;
    // [Constant] float M_HALF_PI
    lua["M_HALF_PI"] = M_HALF_PI;
    // [Constant] int M_MIN_INT
    lua["M_MIN_INT"] = M_MIN_INT;
    // [Constant] int M_MAX_INT
    lua["M_MAX_INT"] = M_MAX_INT;
    // [Constant] unsigned M_MIN_UNSIGNED
    lua["M_MIN_UNSIGNED"] = M_MIN_UNSIGNED;
    // [Constant] unsigned M_MAX_UNSIGNED
    lua["M_MAX_UNSIGNED"] = M_MAX_UNSIGNED;

    // [Constant] float M_EPSILON
    lua["M_EPSILON"] = M_EPSILON;
    // [Constant] float M_LARGE_EPSILON
    lua["M_LARGE_EPSILON"] = M_LARGE_EPSILON;
    // [Constant] float M_MIN_NEARCLIP
    lua["M_MIN_NEARCLIP"] = M_MIN_NEARCLIP;
    // [Constant] float M_MAX_FOV
    lua["M_MAX_FOV"] = M_MAX_FOV;
    // [Constant] float M_LARGE_VALUE
    lua["M_LARGE_VALUE"] = M_LARGE_VALUE;
    // [Constant] float M_INFINITY
    lua["M_INFINITY"] = M_INFINITY;
    // [Constant] float M_DEGTORAD
    lua["M_DEGTORAD"] = M_DEGTORAD;
    // [Constant] float M_DEGTORAD_2
    lua["M_DEGTORAD_2"] = M_DEGTORAD_2;
    // [Constant] float M_RADTODEG
    lua["M_RADTODEG"] = M_RADTODEG;

    // [Enum] Intersection
    // [Variable] OUTSIDE,
    lua["OUTSIDE"] = OUTSIDE;
    // [Variable] INTERSECTS,
    lua["INTERSECTS"] = INTERSECTS;
    // [Variable] INSIDE
    lua["INSIDE"] = INSIDE;

    lua["Equals"] = static_cast<bool(*)(float, float)>(&Equals);
    lua["Lerp"] = static_cast<float(*)(float, float, float)>(&Lerp);
    lua["Min"] = static_cast<float(*)(float, float)>(&Min);
    lua["Max"] = static_cast<float(*)(float, float)>(&Max);
    lua["Abs"] = static_cast<float(*)(float)>(&Abs);
    lua["Sign"] = static_cast<float(*)(float)>(&Sign);

    // [Function] bool IsNaN(float value)
    lua["IsNaN"] = function(&IsNaN);

    lua["Clamp"] = static_cast<float(*)(float, float, float)>(&Clamp);
    lua["SmoothStep"] = static_cast<float(*)(float, float, float)>(&SmoothStep);
    lua["Sin"] = static_cast<float(*)(float)>(&Sin);
    lua["Cos"] = static_cast<float(*)(float)>(&Cos);
    lua["Tan"] = static_cast<float(*)(float)>(&Tan);
    lua["Asin"] = static_cast<float(*)(float)>(&Asin);
    lua["Acos"] = static_cast<float(*)(float)>(&Acos);
    lua["Atan"] = static_cast<float(*)(float)>(&Atan);
    lua["Atan2"] = static_cast<float(*)(float, float)>(&Atan2);

    lua["MinInt"] = static_cast<int(*)(int, int)>(&Min);
    lua["MaxInt"] = static_cast<int(*)(int, int)>(&Max);
    lua["AbsInt"] = static_cast<int(*)(int)>(&Abs);
    lua["ClampInt"] = static_cast<int(*)(int, int, int)>(&Clamp);

    // [Function] bool IsPowerOfTwo(unsigned value)
    lua["IsPowerOfTwo"] = function(&IsPowerOfTwo);
    // [Function] unsigned NextPowerOfTwo(unsigned value)
    lua["NextPowerOfTwo"] = function(&NextPowerOfTwo);
    // [Function] unsigned CountSetBits(unsigned value)
    lua["CountSetBits"] = function(&CountSetBits);
    // [Function] unsigned SDBMHash(unsigned hash, unsigned char c)
    lua["SDBMHash"] = function(&SDBMHash);

    lua["Random"] = overload(static_cast<float(*)()>(&Random),
        static_cast<float(*)(float)>(&Random),
        static_cast<float(*)(float, float)>(&Random));

    lua["RandomInt"] = overload(&Rand,
        static_cast<int(*)(int)>(&Random),
        static_cast<int(*)(int, int)>(&Random));

    // [Function] float RandomNormal(float meanValue, float variance)
    lua["RandomNormal"] = function(&RandomNormal);
}
}

