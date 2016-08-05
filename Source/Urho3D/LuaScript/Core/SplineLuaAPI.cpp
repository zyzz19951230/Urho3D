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

#include "../../Core/Spline.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterSpline(kaguya::State& lua)
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
}

