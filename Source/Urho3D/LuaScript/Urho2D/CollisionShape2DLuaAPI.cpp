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

#include "../../Urho2D/CollisionShape2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterCollisionShape2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["CollisionShape2D"].setClass(UserdataMetatable<CollisionShape2D, Component>()

        .addFunction("SetTrigger", &CollisionShape2D::SetTrigger)
        .addFunction("SetCategoryBits", &CollisionShape2D::SetCategoryBits)
        .addFunction("SetMaskBits", &CollisionShape2D::SetMaskBits)
        .addFunction("SetGroupIndex", &CollisionShape2D::SetGroupIndex)
        .addFunction("SetDensity", &CollisionShape2D::SetDensity)
        .addFunction("SetFriction", &CollisionShape2D::SetFriction)
        .addFunction("SetRestitution", &CollisionShape2D::SetRestitution)

        .addFunction("IsTrigger", &CollisionShape2D::IsTrigger)
        .addFunction("GetCategoryBits", &CollisionShape2D::GetCategoryBits)
        .addFunction("GetMaskBits", &CollisionShape2D::GetMaskBits)
        .addFunction("GetGroupIndex", &CollisionShape2D::GetGroupIndex)
        .addFunction("GetDensity", &CollisionShape2D::GetDensity)
        .addFunction("GetFriction", &CollisionShape2D::GetFriction)
        .addFunction("GetRestitution", &CollisionShape2D::GetRestitution)
        .addFunction("GetMass", &CollisionShape2D::GetMass)
        .addFunction("GetInertia", &CollisionShape2D::GetInertia)
        .addFunction("GetMassCenter", &CollisionShape2D::GetMassCenter)

        .addProperty("trigger", &CollisionShape2D::IsTrigger, &CollisionShape2D::SetTrigger)
        .addProperty("categoryBits", &CollisionShape2D::GetCategoryBits, &CollisionShape2D::SetCategoryBits)
        .addProperty("maskBits", &CollisionShape2D::GetMaskBits, &CollisionShape2D::SetMaskBits)
        .addProperty("groupIndex", &CollisionShape2D::GetGroupIndex, &CollisionShape2D::SetGroupIndex)
        .addProperty("density", &CollisionShape2D::GetDensity, &CollisionShape2D::SetDensity)
        .addProperty("friction", &CollisionShape2D::GetFriction, &CollisionShape2D::SetFriction)
        .addProperty("restitution", &CollisionShape2D::GetRestitution, &CollisionShape2D::SetRestitution)
        .addProperty("mass", &CollisionShape2D::GetMass)
        .addProperty("inertia", &CollisionShape2D::GetInertia)
        .addProperty("massCenter", &CollisionShape2D::GetMassCenter)
    );
}
}

#endif
