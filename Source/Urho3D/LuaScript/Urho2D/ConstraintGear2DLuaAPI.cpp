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

#include "../../Urho2D/ConstraintGear2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterConstraintGear2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ConstraintGear2D"].setClass(UserdataMetatable<ConstraintGear2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintGear2D>)

        .addFunction("SetOwnerConstraint", &ConstraintGear2D::SetOwnerConstraint)
        .addFunction("SetOtherConstraint", &ConstraintGear2D::SetOtherConstraint)
        .addFunction("SetRatio", &ConstraintGear2D::SetRatio)

        .addFunction("GetOwnerConstraint", &ConstraintGear2D::GetOwnerConstraint)
        .addFunction("GetOtherConstraint", &ConstraintGear2D::GetOtherConstraint)
        .addFunction("GetRatio", &ConstraintGear2D::GetRatio)

        .addProperty("ownerConstraint", &ConstraintGear2D::GetOwnerConstraint, &ConstraintGear2D::SetOwnerConstraint)
        .addProperty("otherConstraint", &ConstraintGear2D::GetOtherConstraint, &ConstraintGear2D::SetOtherConstraint)
        .addProperty("ratio", &ConstraintGear2D::GetRatio, &ConstraintGear2D::SetRatio)
    );
}
}

#endif
