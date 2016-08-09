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

#include "../../Urho2D/ConstraintFriction2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterConstraintFriction2D(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] ConstraintFriction2D : Constraint2D
    lua["ConstraintFriction2D"].setClass(UserdataMetatable<ConstraintFriction2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintFriction2D>)

        // [Method] void SetAnchor(const Vector2& anchor)
        .addFunction("SetAnchor", &ConstraintFriction2D::SetAnchor)
        // [Method] void SetMaxForce(float maxForce)
        .addFunction("SetMaxForce", &ConstraintFriction2D::SetMaxForce)
        // [Method] void SetMaxTorque(float maxTorque)
        .addFunction("SetMaxTorque", &ConstraintFriction2D::SetMaxTorque)

        // [Method] const Vector2& GetAnchor() const
        .addFunction("GetAnchor", &ConstraintFriction2D::GetAnchor)
        // [Method] float GetMaxForce() const
        .addFunction("GetMaxForce", &ConstraintFriction2D::GetMaxForce)
        // [Method] float GetMaxTorque() const
        .addFunction("GetMaxTorque", &ConstraintFriction2D::GetMaxTorque)

        // [Property] const Vector2& anchor
        .addProperty("anchor", &ConstraintFriction2D::GetAnchor, &ConstraintFriction2D::SetAnchor)
        // [Property] float maxForce
        .addProperty("maxForce", &ConstraintFriction2D::GetMaxForce, &ConstraintFriction2D::SetMaxForce)
        // [Property] float maxTorque
        .addProperty("maxTorque", &ConstraintFriction2D::GetMaxTorque, &ConstraintFriction2D::SetMaxTorque)
    );
}
}

#endif
