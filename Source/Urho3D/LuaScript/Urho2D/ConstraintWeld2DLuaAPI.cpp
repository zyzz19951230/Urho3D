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

#include "../../Urho2D/ConstraintWeld2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterConstraintWeld2D(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] ConstraintWeld2D : Constraint2D
    lua["ConstraintWeld2D"].setClass(UserdataMetatable<ConstraintWeld2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintWeld2D>)

        // [Method] void SetAnchor(const Vector2& anchor)
        .addFunction("SetAnchor", &ConstraintWeld2D::SetAnchor)
        // [Method] void SetFrequencyHz(float frequencyHz)
        .addFunction("SetFrequencyHz", &ConstraintWeld2D::SetFrequencyHz)
        // [Method] void SetDampingRatio(float dampingRatio)
        .addFunction("SetDampingRatio", &ConstraintWeld2D::SetDampingRatio)

        // [Method] const Vector2& GetAnchor() const
        .addFunction("GetAnchor", &ConstraintWeld2D::GetAnchor)
        // [Method] float GetFrequencyHz() const
        .addFunction("GetFrequencyHz", &ConstraintWeld2D::GetFrequencyHz)
        // [Method] float GetDampingRatio() const
        .addFunction("GetDampingRatio", &ConstraintWeld2D::GetDampingRatio)

        // [Property] const Vector2& anchor
        .addProperty("anchor", &ConstraintWeld2D::GetAnchor, &ConstraintWeld2D::SetAnchor)
        // [Property] float frequencyHz
        .addProperty("frequencyHz", &ConstraintWeld2D::GetFrequencyHz, &ConstraintWeld2D::SetFrequencyHz)
        // [Property] float dampingRatio
        .addProperty("dampingRatio", &ConstraintWeld2D::GetDampingRatio, &ConstraintWeld2D::SetDampingRatio)
    );
}
}

#endif
