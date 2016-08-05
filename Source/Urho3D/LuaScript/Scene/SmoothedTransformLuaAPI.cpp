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

    lua["SMOOTH_NONE"] = SMOOTH_NONE;
    lua["SMOOTH_POSITION"] = SMOOTH_POSITION;
    lua["SMOOTH_ROTATION"] = SMOOTH_ROTATION;

    lua["SmoothedTransform"].setClass(UserdataMetatable<SmoothedTransform, Component>()
        .addStaticFunction("new", &CreateObject<SmoothedTransform>)

        .addFunction("SetTargetPosition", &SmoothedTransform::SetTargetPosition)
        .addFunction("SetTargetRotation", &SmoothedTransform::SetTargetRotation)
        .addFunction("SetTargetWorldPosition", &SmoothedTransform::SetTargetWorldPosition)
        .addFunction("SetTargetWorldRotation", &SmoothedTransform::SetTargetWorldRotation)

        .addFunction("GetTargetPosition", &SmoothedTransform::GetTargetPosition)
        .addFunction("GetTargetRotation", &SmoothedTransform::GetTargetRotation)
        .addFunction("GetTargetWorldPosition", &SmoothedTransform::GetTargetWorldPosition)
        .addFunction("GetTargetWorldRotation", &SmoothedTransform::GetTargetWorldRotation)

        .addFunction("IsInProgress", &SmoothedTransform::IsInProgress)

        .addProperty("targetPosition", &SmoothedTransform::GetTargetPosition, &SmoothedTransform::SetTargetPosition)
        .addProperty("targetRotation", &SmoothedTransform::GetTargetRotation, &SmoothedTransform::SetTargetRotation)
        .addProperty("targetWorldPosition", &SmoothedTransform::GetTargetWorldPosition, &SmoothedTransform::SetTargetWorldPosition)
        .addProperty("targetWorldRotation", &SmoothedTransform::GetTargetWorldRotation, &SmoothedTransform::SetTargetWorldRotation)

        .addProperty("inProgress", &SmoothedTransform::IsInProgress)
        );
}
}

