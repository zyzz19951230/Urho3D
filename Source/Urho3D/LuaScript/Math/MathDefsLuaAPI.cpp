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

    lua["M_PI"] = M_PI;
    lua["M_HALF_PI"] = M_HALF_PI;
    lua["M_MIN_INT"] = M_MIN_INT;
    lua["M_MAX_INT"] = M_MAX_INT;
    lua["M_MIN_UNSIGNED"] = M_MIN_UNSIGNED;
    lua["M_MAX_UNSIGNED"] = M_MAX_UNSIGNED;

    lua["M_EPSILON"] = M_EPSILON;
    lua["M_LARGE_EPSILON"] = M_LARGE_EPSILON;
    lua["M_MIN_NEARCLIP"] = M_MIN_NEARCLIP;
    lua["M_MAX_FOV"] = M_MAX_FOV;
    lua["M_LARGE_VALUE"] = M_LARGE_VALUE;
    lua["M_INFINITY"] = M_INFINITY;
    lua["M_DEGTORAD"] = M_DEGTORAD;
    lua["M_DEGTORAD_2"] = M_DEGTORAD_2;
    lua["M_RADTODEG"] = M_RADTODEG;

    // enum Intersection;
    lua["OUTSIDE"] = OUTSIDE;
    lua["INTERSECTS"] = INTERSECTS;
    lua["INSIDE"] = INSIDE;

    lua["Equals"] = static_cast<bool(*)(float, float)>(&Equals);
    lua["Lerp"] = static_cast<float(*)(float, float, float)>(&Lerp);
    lua["Min"] = static_cast<float(*)(float, float)>(&Min);
    lua["Max"] = static_cast<float(*)(float, float)>(&Max);
    lua["Abs"] = static_cast<float(*)(float)>(&Abs);
    lua["Sign"] = static_cast<float(*)(float)>(&Sign);

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

    lua["IsPowerOfTwo"] = function(&IsPowerOfTwo);
    lua["NextPowerOfTwo"] = function(&NextPowerOfTwo);
    lua["CountSetBits"] = function(&CountSetBits);
    lua["SDBMHash"] = function(&SDBMHash);

    lua["Random"] = overload(static_cast<float(*)()>(&Random),
        static_cast<float(*)(float)>(&Random),
        static_cast<float(*)(float, float)>(&Random));

    lua["RandomInt"] = overload(&Rand,
        static_cast<int(*)(int)>(&Random),
        static_cast<int(*)(int, int)>(&Random));

    lua["RandomNormal"] = function(&RandomNormal);
}
}

