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

    // [Class] CollisionShape2D : Component
    lua["CollisionShape2D"].setClass(UserdataMetatable<CollisionShape2D, Component>()

        // [Method] void SetTrigger(bool trigger)
        .addFunction("SetTrigger", &CollisionShape2D::SetTrigger)
        // [Method] void SetCategoryBits(int categoryBits)
        .addFunction("SetCategoryBits", &CollisionShape2D::SetCategoryBits)
        // [Method] void SetMaskBits(int maskBits)
        .addFunction("SetMaskBits", &CollisionShape2D::SetMaskBits)
        // [Method] void SetGroupIndex(int groupIndex)
        .addFunction("SetGroupIndex", &CollisionShape2D::SetGroupIndex)
        // [Method] void SetDensity(float density)
        .addFunction("SetDensity", &CollisionShape2D::SetDensity)
        // [Method] void SetFriction(float friction)
        .addFunction("SetFriction", &CollisionShape2D::SetFriction)
        // [Method] void SetRestitution(float restitution)
        .addFunction("SetRestitution", &CollisionShape2D::SetRestitution)

        // [Method] bool IsTrigger() const
        .addFunction("IsTrigger", &CollisionShape2D::IsTrigger)
        // [Method] int GetCategoryBits() const
        .addFunction("GetCategoryBits", &CollisionShape2D::GetCategoryBits)
        // [Method] int GetMaskBits() const
        .addFunction("GetMaskBits", &CollisionShape2D::GetMaskBits)
        // [Method] int GetGroupIndex() const
        .addFunction("GetGroupIndex", &CollisionShape2D::GetGroupIndex)
        // [Method] float GetDensity() const
        .addFunction("GetDensity", &CollisionShape2D::GetDensity)
        // [Method] float GetFriction() const
        .addFunction("GetFriction", &CollisionShape2D::GetFriction)
        // [Method] float GetRestitution() const
        .addFunction("GetRestitution", &CollisionShape2D::GetRestitution)
        // [Method] float GetMass() const
        .addFunction("GetMass", &CollisionShape2D::GetMass)
        // [Method] float GetInertia() const
        .addFunction("GetInertia", &CollisionShape2D::GetInertia)
        // [Method] Vector2 GetMassCenter() const
        .addFunction("GetMassCenter", &CollisionShape2D::GetMassCenter)

        // [Property] bool trigger
        .addProperty("trigger", &CollisionShape2D::IsTrigger, &CollisionShape2D::SetTrigger)
        // [Property] int categoryBits
        .addProperty("categoryBits", &CollisionShape2D::GetCategoryBits, &CollisionShape2D::SetCategoryBits)
        // [Property] int maskBits
        .addProperty("maskBits", &CollisionShape2D::GetMaskBits, &CollisionShape2D::SetMaskBits)
        // [Property] int groupIndex
        .addProperty("groupIndex", &CollisionShape2D::GetGroupIndex, &CollisionShape2D::SetGroupIndex)
        // [Property] float density
        .addProperty("density", &CollisionShape2D::GetDensity, &CollisionShape2D::SetDensity)
        // [Property] float friction
        .addProperty("friction", &CollisionShape2D::GetFriction, &CollisionShape2D::SetFriction)
        // [Property] float restitution
        .addProperty("restitution", &CollisionShape2D::GetRestitution, &CollisionShape2D::SetRestitution)
        // [Property(Readonly)] float mass
        .addProperty("mass", &CollisionShape2D::GetMass)
        // [Property(Readonly)] float inertia
        .addProperty("inertia", &CollisionShape2D::GetInertia)
        // [Property(Readonly)] Vector2 massCenter
        .addProperty("massCenter", &CollisionShape2D::GetMassCenter)
    );
}
}

#endif
