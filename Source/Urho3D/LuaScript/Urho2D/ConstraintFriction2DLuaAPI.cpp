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

    lua["ConstraintFriction2D"].setClass(UserdataMetatable<ConstraintFriction2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintFriction2D>)

        .addFunction("SetAnchor", &ConstraintFriction2D::SetAnchor)
        .addFunction("SetMaxForce", &ConstraintFriction2D::SetMaxForce)
        .addFunction("SetMaxTorque", &ConstraintFriction2D::SetMaxTorque)

        .addFunction("GetAnchor", &ConstraintFriction2D::GetAnchor)
        .addFunction("GetMaxForce", &ConstraintFriction2D::GetMaxForce)
        .addFunction("GetMaxTorque", &ConstraintFriction2D::GetMaxTorque)

        .addProperty("anchor", &ConstraintFriction2D::GetAnchor, &ConstraintFriction2D::SetAnchor)
        .addProperty("maxForce", &ConstraintFriction2D::GetMaxForce, &ConstraintFriction2D::SetMaxForce)
        .addProperty("maxTorque", &ConstraintFriction2D::GetMaxTorque, &ConstraintFriction2D::SetMaxTorque)
    );
}
}

#endif
