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

    // [Class] ConstraintDistance2D : Constraint2D
    lua["ConstraintDistance2D"].setClass(UserdataMetatable<ConstraintDistance2D, Constraint2D>()
        // [Constructor] ConstraintDistance2D()
        .addStaticFunction("new", &CreateObject<ConstraintDistance2D>)

        // [Method] void SetOwnerBodyAnchor(const Vector2& anchor)
        .addFunction("SetOwnerBodyAnchor", &ConstraintDistance2D::SetOwnerBodyAnchor)
        // [Method] void SetOtherBodyAnchor(const Vector2& anchor)
        .addFunction("SetOtherBodyAnchor", &ConstraintDistance2D::SetOtherBodyAnchor)
        // [Method] void SetFrequencyHz(float frequencyHz)
        .addFunction("SetFrequencyHz", &ConstraintDistance2D::SetFrequencyHz)
        // [Method] void SetDampingRatio(float dampingRatio)
        .addFunction("SetDampingRatio", &ConstraintDistance2D::SetDampingRatio)

        // [Method] const Vector2& GetOwnerBodyAnchor() const
        .addFunction("GetOwnerBodyAnchor", &ConstraintDistance2D::GetOwnerBodyAnchor)
        // [Method] const Vector2& GetOtherBodyAnchor() const
        .addFunction("GetOtherBodyAnchor", &ConstraintDistance2D::GetOtherBodyAnchor)
        // [Method] float GetFrequencyHz() const
        .addFunction("GetFrequencyHz", &ConstraintDistance2D::GetFrequencyHz)
        // [Method] float GetDampingRatio() const
        .addFunction("GetDampingRatio", &ConstraintDistance2D::GetDampingRatio)

        // [Property] const Vector2& ownerBodyAnchor
        .addProperty("ownerBodyAnchor", &ConstraintDistance2D::GetOwnerBodyAnchor, &ConstraintDistance2D::SetOwnerBodyAnchor)
        // [Property] const Vector2& otherBodyAnchor
        .addProperty("otherBodyAnchor", &ConstraintDistance2D::GetOtherBodyAnchor, &ConstraintDistance2D::SetOtherBodyAnchor)
        // [Property] float frequencyHz
        .addProperty("frequencyHz", &ConstraintDistance2D::GetFrequencyHz, &ConstraintDistance2D::SetFrequencyHz)
        // [Property] float dampingRatio
        .addProperty("dampingRatio", &ConstraintDistance2D::GetDampingRatio, &ConstraintDistance2D::SetDampingRatio)
    );
}
}

#endif
