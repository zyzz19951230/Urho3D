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

#include "../../Precompiled.h"

#include "../../Scene/SmoothedTransform.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterSmoothedTransform(kaguya::State& lua)
{
    using namespace kaguya;

    // [Constant] unsigned SMOOTH_NONE
    lua["SMOOTH_NONE"] = SMOOTH_NONE;
    // [Constant] unsigned SMOOTH_POSITION
    lua["SMOOTH_POSITION"] = SMOOTH_POSITION;
    // [Constant] unsigned SMOOTH_ROTATION
    lua["SMOOTH_ROTATION"] = SMOOTH_ROTATION;

    // [Class] SmoothedTransform : Component
    lua["SmoothedTransform"].setClass(UserdataMetatable<SmoothedTransform, Component>()
        .addStaticFunction("new", &CreateObject<SmoothedTransform>)

        // [Method] void SetTargetPosition(const Vector3& position)
        .addFunction("SetTargetPosition", &SmoothedTransform::SetTargetPosition)
        // [Method] void SetTargetRotation(const Quaternion& rotation)
        .addFunction("SetTargetRotation", &SmoothedTransform::SetTargetRotation)
        // [Method] void SetTargetWorldPosition(const Vector3& position)
        .addFunction("SetTargetWorldPosition", &SmoothedTransform::SetTargetWorldPosition)
        // [Method] void SetTargetWorldRotation(const Quaternion& rotation)
        .addFunction("SetTargetWorldRotation", &SmoothedTransform::SetTargetWorldRotation)

        // [Method] const Vector3& GetTargetPosition() const
        .addFunction("GetTargetPosition", &SmoothedTransform::GetTargetPosition)
        // [Method] const Quaternion& GetTargetRotation() const
        .addFunction("GetTargetRotation", &SmoothedTransform::GetTargetRotation)
        // [Method] Vector3 GetTargetWorldPosition() const
        .addFunction("GetTargetWorldPosition", &SmoothedTransform::GetTargetWorldPosition)
        // [Method] Quaternion GetTargetWorldRotation() const
        .addFunction("GetTargetWorldRotation", &SmoothedTransform::GetTargetWorldRotation)

        // [Method] bool IsInProgress() const
        .addFunction("IsInProgress", &SmoothedTransform::IsInProgress)

        // [Property] const Vector3& targetPosition
        .addProperty("targetPosition", &SmoothedTransform::GetTargetPosition, &SmoothedTransform::SetTargetPosition)
        // [Property] const Quaternion& targetRotation
        .addProperty("targetRotation", &SmoothedTransform::GetTargetRotation, &SmoothedTransform::SetTargetRotation)
        // [Property] Vector3 targetWorldPosition
        .addProperty("targetWorldPosition", &SmoothedTransform::GetTargetWorldPosition, &SmoothedTransform::SetTargetWorldPosition)
        // [Property] Quaternion targetWorldRotation
        .addProperty("targetWorldRotation", &SmoothedTransform::GetTargetWorldRotation, &SmoothedTransform::SetTargetWorldRotation)

        // [Property(ReadOnly)] bool inProgress
        .addProperty("inProgress", &SmoothedTransform::IsInProgress)
        );
}
}

