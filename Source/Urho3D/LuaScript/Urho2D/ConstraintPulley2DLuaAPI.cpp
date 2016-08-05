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

#include "../../Urho2D/ConstraintPulley2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterConstraintPulley2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ConstraintPulley2D"].setClass(UserdataMetatable<ConstraintPulley2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintPulley2D>)

        .addFunction("SetOwnerBodyGroundAnchor", &ConstraintPulley2D::SetOwnerBodyGroundAnchor)
        .addFunction("SetOtherBodyGroundAnchor", &ConstraintPulley2D::SetOtherBodyGroundAnchor)
        .addFunction("SetOwnerBodyAnchor", &ConstraintPulley2D::SetOwnerBodyAnchor)
        .addFunction("SetOtherBodyAnchor", &ConstraintPulley2D::SetOtherBodyAnchor)
        .addFunction("SetRatio", &ConstraintPulley2D::SetRatio)

        .addFunction("GetOwnerBodyGroundAnchor", &ConstraintPulley2D::GetOwnerBodyGroundAnchor)
        .addFunction("GetOtherBodyGroundAnchor", &ConstraintPulley2D::GetOtherBodyGroundAnchor)
        .addFunction("GetOwnerBodyAnchor", &ConstraintPulley2D::GetOwnerBodyAnchor)
        .addFunction("GetOtherBodyAnchor", &ConstraintPulley2D::GetOtherBodyAnchor)
        .addFunction("GetRatio", &ConstraintPulley2D::GetRatio)

        .addProperty("ownerBodyGroundAnchor", &ConstraintPulley2D::GetOwnerBodyGroundAnchor, &ConstraintPulley2D::SetOwnerBodyGroundAnchor)
        .addProperty("otherBodyGroundAnchor", &ConstraintPulley2D::GetOtherBodyGroundAnchor, &ConstraintPulley2D::SetOtherBodyGroundAnchor)
        .addProperty("ownerBodyAnchor", &ConstraintPulley2D::GetOwnerBodyAnchor, &ConstraintPulley2D::SetOwnerBodyAnchor)
        .addProperty("otherBodyAnchor", &ConstraintPulley2D::GetOtherBodyAnchor, &ConstraintPulley2D::SetOtherBodyAnchor)
        .addProperty("ratio", &ConstraintPulley2D::GetRatio, &ConstraintPulley2D::SetRatio)
    );
}
}

#endif
