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

#include "../../Scene/SplinePath.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void SplinePathAddControlPoint0(SplinePath* self, Node* point)
{
    self->AddControlPoint(point);
}

static void SplinePathAddControlPoint1(SplinePath* self, Node* point, unsigned index)
{
    self->AddControlPoint(point, index);
}

void RegisterSplinePath(kaguya::State& lua)
{
    using namespace kaguya;

    lua["SplinePath"].setClass(UserdataMetatable<SplinePath, Component>()
        .addStaticFunction("new", &CreateObject<SplinePath>)

        ADD_OVERLOADED_FUNCTIONS_2(SplinePath, AddControlPoint)

        .addFunction("RemoveControlPoint", &SplinePath::RemoveControlPoint)
        .addFunction("ClearControlPoints", &SplinePath::ClearControlPoints)

        .addFunction("SetInterpolationMode", &SplinePath::SetInterpolationMode)
        .addFunction("SetSpeed", &SplinePath::SetSpeed)
        .addFunction("SetPosition", &SplinePath::SetPosition)
        .addFunction("SetControlledNode", &SplinePath::SetControlledNode)

        .addFunction("GetInterpolationMode", &SplinePath::GetInterpolationMode)
        .addFunction("GetSpeed", &SplinePath::GetSpeed)
        .addFunction("GetLength", &SplinePath::GetLength)
        .addFunction("GetPosition", &SplinePath::GetPosition)
        .addFunction("GetControlledNode", &SplinePath::GetControlledNode)
        .addFunction("GetPoint", &SplinePath::GetPoint)
        .addFunction("Move", &SplinePath::Move)
        .addFunction("Reset", &SplinePath::Reset)
        .addFunction("IsFinished", &SplinePath::IsFinished)

        .addProperty("interpolationMode", &SplinePath::GetInterpolationMode, &SplinePath::SetInterpolationMode)
        .addProperty("speed", &SplinePath::GetSpeed, &SplinePath::SetSpeed)
        .addProperty("length", &SplinePath::GetLength)
        .addProperty("position", &SplinePath::GetPosition, &SplinePath::SetPosition)
        .addProperty("controlledNode", &SplinePath::GetControlledNode, &SplinePath::SetControlledNode)
        .addProperty("finished", &SplinePath::IsFinished)
        );
}
}

