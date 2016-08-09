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

    // [Class] ConstraintGear2D : Constraint2D
    lua["ConstraintGear2D"].setClass(UserdataMetatable<ConstraintGear2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintGear2D>)

        // [Method] void SetOwnerConstraint(Constraint2D* constraint)
        .addFunction("SetOwnerConstraint", &ConstraintGear2D::SetOwnerConstraint)
        // [Method] void SetOtherConstraint(Constraint2D* constraint)
        .addFunction("SetOtherConstraint", &ConstraintGear2D::SetOtherConstraint)
        // [Method] void SetRatio(float ratio)
        .addFunction("SetRatio", &ConstraintGear2D::SetRatio)

        // [Method] Constraint2D* GetOwnerConstraint() const
        .addFunction("GetOwnerConstraint", &ConstraintGear2D::GetOwnerConstraint)
        // [Method] Constraint2D* GetOtherConstraint() const
        .addFunction("GetOtherConstraint", &ConstraintGear2D::GetOtherConstraint)
        // [Method] float GetRatio() const
        .addFunction("GetRatio", &ConstraintGear2D::GetRatio)

        // [Property] Constraint2D* ownerConstraint
        .addProperty("ownerConstraint", &ConstraintGear2D::GetOwnerConstraint, &ConstraintGear2D::SetOwnerConstraint)
        // [Property] Constraint2D* otherConstraint
        .addProperty("otherConstraint", &ConstraintGear2D::GetOtherConstraint, &ConstraintGear2D::SetOtherConstraint)
        // [Property] float ratio
        .addProperty("ratio", &ConstraintGear2D::GetRatio, &ConstraintGear2D::SetRatio)
    );
}
}

#endif
