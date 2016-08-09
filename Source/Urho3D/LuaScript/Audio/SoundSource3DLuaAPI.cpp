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

#include "../../Audio/SoundSource3D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterSoundSource3D(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] SoundSource3D : SoundSource
    lua["SoundSource3D"].setClass(UserdataMetatable<SoundSource3D, SoundSource>()
        // [Constructor] SoundSource3D()
        .addStaticFunction("new", &CreateObject<SoundSource3D>)

        // [Method] void SetDistanceAttenuation(float nearDistance, float farDistance, float rolloffFactor)
        .addFunction("SetDistanceAttenuation", &SoundSource3D::SetDistanceAttenuation)
        // [Method] void SetAngleAttenuation(float innerAngle, float outerAngle)
        .addFunction("SetAngleAttenuation", &SoundSource3D::SetAngleAttenuation)
        // [Method] void SetNearDistance(float distance)
        .addFunction("SetNearDistance", &SoundSource3D::SetNearDistance)
        // [Method] void SetFarDistance(float distance)
        .addFunction("SetFarDistance", &SoundSource3D::SetFarDistance)
        // [Method] void SetInnerAngle(float angle)
        .addFunction("SetInnerAngle", &SoundSource3D::SetInnerAngle)
        // [Method] void SetOuterAngle(float angle)
        .addFunction("SetOuterAngle", &SoundSource3D::SetOuterAngle)
        // [Method] void SetRolloffFactor(float factor)
        .addFunction("SetRolloffFactor", &SoundSource3D::SetRolloffFactor)
        // [Method] void CalculateAttenuation()
        .addFunction("CalculateAttenuation", &SoundSource3D::CalculateAttenuation)

        // [Method] float GetNearDistance() const
        .addFunction("GetNearDistance", &SoundSource3D::GetNearDistance)
        // [Method] float GetFarDistance() const
        .addFunction("GetFarDistance", &SoundSource3D::GetFarDistance)
        // [Method] float GetInnerAngle() const
        .addFunction("GetInnerAngle", &SoundSource3D::GetInnerAngle)
        // [Method] float GetOuterAngle() const
        .addFunction("GetOuterAngle", &SoundSource3D::GetOuterAngle)
        // [Method] float RollAngleoffFactor() const
        .addFunction("RollAngleoffFactor", &SoundSource3D::RollAngleoffFactor)

        // [Property] float nearDistance
        .addProperty("nearDistance", &SoundSource3D::GetNearDistance, &SoundSource3D::SetNearDistance)
        // [Property] float farDistance
        .addProperty("farDistance", &SoundSource3D::GetFarDistance, &SoundSource3D::SetFarDistance)
        // [Property] float innerAngle
        .addProperty("innerAngle", &SoundSource3D::GetInnerAngle, &SoundSource3D::SetInnerAngle)
        // [Property] float outerAngle
        .addProperty("outerAngle", &SoundSource3D::GetOuterAngle, &SoundSource3D::SetOuterAngle)
        // [Property(WriteOnly)] float rolloffFactor
        .addProperty("rolloffFactor", &SoundSource3D::SetRolloffFactor)
        );
}
}

