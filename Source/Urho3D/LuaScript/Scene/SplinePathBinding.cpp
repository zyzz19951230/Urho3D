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

#include "../../Scene/Node.h"
#include "../../Scene/SplinePath.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(SplinePathAddControlPoint, SplinePath, AddControlPoint, 1, 2)

void RegisterSplinePath(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] SplinePath : Component
    lua["SplinePath"].setClass(UserdataMetatable<SplinePath, Component>()
        // [Constructor] SplinePath()
    .addStaticFunction("new", &CreateObject<SplinePath>)

        // [Method] void AddControlPoint(Node* point, unsigned index = M_MAX_UNSIGNED)
        .addFunction("AddControlPoint", SplinePathAddControlPoint())

        // [Method] void RemoveControlPoint(Node* point)
        .addFunction("RemoveControlPoint", &SplinePath::RemoveControlPoint)
        // [Method] void ClearControlPoints()
        .addFunction("ClearControlPoints", &SplinePath::ClearControlPoints)

        // [Method] void SetInterpolationMode(InterpolationMode interpolationMode)
        .addFunction("SetInterpolationMode", &SplinePath::SetInterpolationMode)
        // [Method] void SetSpeed(float speed)
        .addFunction("SetSpeed", &SplinePath::SetSpeed)
        // [Method] void SetPosition(float factor)
        .addFunction("SetPosition", &SplinePath::SetPosition)
        // [Method] void SetControlledNode(Node* controlled)
        .addFunction("SetControlledNode", &SplinePath::SetControlledNode)

        // [Method] InterpolationMode GetInterpolationMode() const
        .addFunction("GetInterpolationMode", &SplinePath::GetInterpolationMode)
        // [Method] float GetSpeed() const
        .addFunction("GetSpeed", &SplinePath::GetSpeed)
        // [Method] float GetLength() const
        .addFunction("GetLength", &SplinePath::GetLength)
        // [Method] Vector3 GetPosition() const
        .addFunction("GetPosition", &SplinePath::GetPosition)
        // [Method] Node* GetControlledNode() const
        .addFunction("GetControlledNode", &SplinePath::GetControlledNode)
        // [Method] Vector3 GetPosition() const
        .addFunction("GetPoint", &SplinePath::GetPoint)
        // [Method] void Move(float timeStep)
        .addFunction("Move", &SplinePath::Move)
        // [Method] void Reset()
        .addFunction("Reset", &SplinePath::Reset)
        // [Method] bool IsFinished() const
        .addFunction("IsFinished", &SplinePath::IsFinished)

        // [Property] InterpolationMode interpolationMode
        .addProperty("interpolationMode", &SplinePath::GetInterpolationMode, &SplinePath::SetInterpolationMode)
        // [Property] float speed
        .addProperty("speed", &SplinePath::GetSpeed, &SplinePath::SetSpeed)
        // [Property(ReadOnly)] float length
        .addProperty("length", &SplinePath::GetLength)
        // [Property] Vector3 position
        .addProperty("position", &SplinePath::GetPosition, &SplinePath::SetPosition)
        // [Property] Node* controlledNode
        .addProperty("controlledNode", &SplinePath::GetControlledNode, &SplinePath::SetControlledNode)
        // [Property(ReadOnly)] bool finished
        .addProperty("finished", &SplinePath::IsFinished)
        );
}
}

