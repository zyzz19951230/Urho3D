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

    // [Class] ConstraintPulley2D : Constraint2D
    lua["ConstraintPulley2D"].setClass(UserdataMetatable<ConstraintPulley2D, Constraint2D>()
        // [Constructor] ConstraintPulley2D()
        .addStaticFunction("new", &CreateObject<ConstraintPulley2D>)

        // [Method] void SetOwnerBodyGroundAnchor(const Vector2& groundAnchor)
        .addFunction("SetOwnerBodyGroundAnchor", &ConstraintPulley2D::SetOwnerBodyGroundAnchor)
        // [Method] void SetOtherBodyGroundAnchor(const Vector2& groundAnchor)
        .addFunction("SetOtherBodyGroundAnchor", &ConstraintPulley2D::SetOtherBodyGroundAnchor)
        // [Method] void SetOwnerBodyAnchor(const Vector2& anchor)
        .addFunction("SetOwnerBodyAnchor", &ConstraintPulley2D::SetOwnerBodyAnchor)
        // [Method] void SetOtherBodyAnchor(const Vector2& anchor)
        .addFunction("SetOtherBodyAnchor", &ConstraintPulley2D::SetOtherBodyAnchor)
        // [Method] void SetRatio(float ratio)
        .addFunction("SetRatio", &ConstraintPulley2D::SetRatio)

        // [Method] const Vector2& GetOwnerBodyGroundAnchor() const
        .addFunction("GetOwnerBodyGroundAnchor", &ConstraintPulley2D::GetOwnerBodyGroundAnchor)
        // [Method] const Vector2& GetOtherBodyGroundAnchor() const
        .addFunction("GetOtherBodyGroundAnchor", &ConstraintPulley2D::GetOtherBodyGroundAnchor)
        // [Method] const Vector2& GetOwnerBodyAnchor() const
        .addFunction("GetOwnerBodyAnchor", &ConstraintPulley2D::GetOwnerBodyAnchor)
        // [Method] const Vector2& GetOtherBodyAnchor() const
        .addFunction("GetOtherBodyAnchor", &ConstraintPulley2D::GetOtherBodyAnchor)
        // [Method] float GetRatio() const
        .addFunction("GetRatio", &ConstraintPulley2D::GetRatio)

        // [Property] const Vector2& ownerBodyGroundAnchor
        .addProperty("ownerBodyGroundAnchor", &ConstraintPulley2D::GetOwnerBodyGroundAnchor, &ConstraintPulley2D::SetOwnerBodyGroundAnchor)
        // [Property] const Vector2& otherBodyGroundAnchor
        .addProperty("otherBodyGroundAnchor", &ConstraintPulley2D::GetOtherBodyGroundAnchor, &ConstraintPulley2D::SetOtherBodyGroundAnchor)
        // [Property] const Vector2& ownerBodyAnchor
        .addProperty("ownerBodyAnchor", &ConstraintPulley2D::GetOwnerBodyAnchor, &ConstraintPulley2D::SetOwnerBodyAnchor)
        // [Property] const Vector2& otherBodyAnchor
        .addProperty("otherBodyAnchor", &ConstraintPulley2D::GetOtherBodyAnchor, &ConstraintPulley2D::SetOtherBodyAnchor)
        // [Property] float ratio
        .addProperty("ratio", &ConstraintPulley2D::GetRatio, &ConstraintPulley2D::SetRatio)
    );
}
}

#endif
