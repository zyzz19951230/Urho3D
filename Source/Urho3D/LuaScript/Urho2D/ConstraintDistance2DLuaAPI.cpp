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

#ifdef URHO3D_URHO2D

#include "../../Precompiled.h"

#include "../../Urho2D/ConstraintDistance2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterConstraintDistance2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ConstraintDistance2D"].setClass(UserdataMetatable<ConstraintDistance2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintDistance2D>)

        .addFunction("SetOwnerBodyAnchor", &ConstraintDistance2D::SetOwnerBodyAnchor)
        .addFunction("SetOtherBodyAnchor", &ConstraintDistance2D::SetOtherBodyAnchor)
        .addFunction("SetFrequencyHz", &ConstraintDistance2D::SetFrequencyHz)
        .addFunction("SetDampingRatio", &ConstraintDistance2D::SetDampingRatio)

        .addFunction("GetOwnerBodyAnchor", &ConstraintDistance2D::GetOwnerBodyAnchor)
        .addFunction("GetOtherBodyAnchor", &ConstraintDistance2D::GetOtherBodyAnchor)
        .addFunction("GetFrequencyHz", &ConstraintDistance2D::GetFrequencyHz)
        .addFunction("GetDampingRatio", &ConstraintDistance2D::GetDampingRatio)

        .addProperty("ownerBodyAnchor", &ConstraintDistance2D::GetOwnerBodyAnchor, &ConstraintDistance2D::SetOwnerBodyAnchor)
        .addProperty("otherBodyAnchor", &ConstraintDistance2D::GetOtherBodyAnchor, &ConstraintDistance2D::SetOtherBodyAnchor)
        .addProperty("frequencyHz", &ConstraintDistance2D::GetFrequencyHz, &ConstraintDistance2D::SetFrequencyHz)
        .addProperty("dampingRatio", &ConstraintDistance2D::GetDampingRatio, &ConstraintDistance2D::SetDampingRatio)
    );
}
}

#endif
