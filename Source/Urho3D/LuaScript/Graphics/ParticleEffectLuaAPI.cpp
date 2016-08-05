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

#include "../../Graphics/Material.h"
#include "../../Graphics/ParticleEffect.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterParticleEffect(kaguya::State& lua)
{
    using namespace kaguya;

    // enum EmitterType;
    lua["EMITTER_SPHERE"] = EMITTER_SPHERE;
    lua["EMITTER_BOX"] = EMITTER_BOX;


    lua["ColorFrame"].setClass(UserdataMetatable<ColorFrame>()
    	.setConstructors<ColorFrame(),
    		ColorFrame(const Color&),
    		ColorFrame(const Color&, float)>()

		.addFunction("Interpolate", &ColorFrame::Interpolate)
    	.addProperty("color", &ColorFrame::color_)
    	.addProperty("time", &ColorFrame::time_)
    	);

	lua["TextureFrame"].setClass(UserdataMetatable<TextureFrame>()
		.setConstructors<TextureFrame()>()

		.addProperty("uv", &TextureFrame::uv_)
		.addProperty("time", &TextureFrame::time_)
		);

    lua["ParticleEffect"].setClass(UserdataMetatable<ParticleEffect, Resource>()
        .addStaticFunction("new", &CreateObject<ParticleEffect>)

        .addFunction("SetMaterial", &ParticleEffect::SetMaterial)
        .addFunction("SetNumParticles", &ParticleEffect::SetNumParticles)
        .addFunction("SetUpdateInvisible", &ParticleEffect::SetUpdateInvisible)
        .addFunction("SetRelative", &ParticleEffect::SetRelative)
        .addFunction("SetScaled", &ParticleEffect::SetScaled)
        .addFunction("SetSorted", &ParticleEffect::SetSorted)
        
        .addFunction("SetFixedScreenSize", &ParticleEffect::SetFixedScreenSize)
        .addFunction("SetAnimationLodBias", &ParticleEffect::SetAnimationLodBias)
        .addFunction("SetEmitterType", &ParticleEffect::SetEmitterType)
        .addFunction("SetEmitterSize", &ParticleEffect::SetEmitterSize)
        .addFunction("SetMinDirection", &ParticleEffect::SetMinDirection)
        .addFunction("SetMaxDirection", &ParticleEffect::SetMaxDirection)
        
        .addFunction("SetConstantForce", &ParticleEffect::SetConstantForce)
        .addFunction("SetDampingForce", &ParticleEffect::SetDampingForce)
        .addFunction("SetActiveTime", &ParticleEffect::SetActiveTime)
        .addFunction("SetInactiveTime", &ParticleEffect::SetInactiveTime)
        .addFunction("SetMinEmissionRate", &ParticleEffect::SetMinEmissionRate)
        .addFunction("SetMaxEmissionRate", &ParticleEffect::SetMaxEmissionRate)
        
        .addFunction("SetMinParticleSize", &ParticleEffect::SetMinParticleSize)
        .addFunction("SetMaxParticleSize", &ParticleEffect::SetMaxParticleSize)
        .addFunction("SetMinTimeToLive", &ParticleEffect::SetMinTimeToLive)
        .addFunction("SetMaxTimeToLive", &ParticleEffect::SetMaxTimeToLive)
        .addFunction("SetMinVelocity", &ParticleEffect::SetMinVelocity)
        .addFunction("SetMaxVelocity", &ParticleEffect::SetMaxVelocity)
        
        .addFunction("SetMinRotation", &ParticleEffect::SetMinRotation)
        .addFunction("SetMaxRotation", &ParticleEffect::SetMaxRotation)
        .addFunction("SetMinRotationSpeed", &ParticleEffect::SetMinRotationSpeed)
        .addFunction("SetMaxRotationSpeed", &ParticleEffect::SetMaxRotationSpeed)
        .addFunction("SetSizeAdd", &ParticleEffect::SetSizeAdd)
        .addFunction("SetSizeMul", &ParticleEffect::SetSizeMul)
        
        .addFunction("SetFaceCameraMode", &ParticleEffect::SetFaceCameraMode)
        
        .addFunction("AddColorTime", &ParticleEffect::AddColorTime)
        .addFunction("AddColorFrame", &ParticleEffect::AddColorFrame)
        .addFunction("RemoveColorFrame", &ParticleEffect::RemoveColorFrame)
        .addFunction("SetColorFrames", &ParticleEffect::SetColorFrames)
        .addFunction("SetColorFrame", &ParticleEffect::SetColorFrame)
        .addFunction("SetNumColorFrames", &ParticleEffect::SetNumColorFrames)
        .addFunction("SortColorFrames", &ParticleEffect::SortColorFrames)
        
        .addFunction("AddTextureTime", &ParticleEffect::AddTextureTime)
        .addFunction("AddTextureFrame", &ParticleEffect::AddTextureFrame)
        .addFunction("RemoveTextureFrame", &ParticleEffect::RemoveTextureFrame)
        .addFunction("SetTextureFrames", &ParticleEffect::SetTextureFrames)
        .addFunction("SetTextureFrame", &ParticleEffect::SetTextureFrame)
        .addFunction("SetNumTextureFrames", &ParticleEffect::SetNumTextureFrames)
        .addFunction("SortTextureFrames", &ParticleEffect::SortTextureFrames)
        
        .addFunction("GetMaterial", &ParticleEffect::GetMaterial)
        .addFunction("GetNumParticles", &ParticleEffect::GetNumParticles)
        .addFunction("GetUpdateInvisible", &ParticleEffect::GetUpdateInvisible)
        .addFunction("IsRelative", &ParticleEffect::IsRelative)
        .addFunction("IsScaled", &ParticleEffect::IsScaled)
        .addFunction("IsSorted", &ParticleEffect::IsSorted)
        .addFunction("IsFixedScreenSize", &ParticleEffect::IsFixedScreenSize)
        .addFunction("GetAnimationLodBias", &ParticleEffect::GetAnimationLodBias)
        .addFunction("GetEmitterType", &ParticleEffect::GetEmitterType)
        .addFunction("GetEmitterSize", &ParticleEffect::GetEmitterSize)
        .addFunction("GetMinDirection", &ParticleEffect::GetMinDirection)
        .addFunction("GetMaxDirection", &ParticleEffect::GetMaxDirection)
        .addFunction("GetConstantForce", &ParticleEffect::GetConstantForce)
        .addFunction("GetDampingForce", &ParticleEffect::GetDampingForce)
        .addFunction("GetActiveTime", &ParticleEffect::GetActiveTime)
        .addFunction("GetInactiveTime", &ParticleEffect::GetInactiveTime)
        .addFunction("GetMinEmissionRate", &ParticleEffect::GetMinEmissionRate)
        .addFunction("GetMaxEmissionRate", &ParticleEffect::GetMaxEmissionRate)
        .addFunction("GetMinParticleSize", &ParticleEffect::GetMinParticleSize)
        .addFunction("GetMaxParticleSize", &ParticleEffect::GetMaxParticleSize)
        .addFunction("GetMinTimeToLive", &ParticleEffect::GetMinTimeToLive)
        .addFunction("GetMaxTimeToLive", &ParticleEffect::GetMaxTimeToLive)
        .addFunction("GetMinVelocity", &ParticleEffect::GetMinVelocity)
        .addFunction("GetMaxVelocity", &ParticleEffect::GetMaxVelocity)
        .addFunction("GetMinRotation", &ParticleEffect::GetMinRotation)
        .addFunction("GetMaxRotation", &ParticleEffect::GetMaxRotation)
        .addFunction("GetMinRotationSpeed", &ParticleEffect::GetMinRotationSpeed)
        .addFunction("GetMaxRotationSpeed", &ParticleEffect::GetMaxRotationSpeed)
        .addFunction("GetSizeAdd", &ParticleEffect::GetSizeAdd)
        .addFunction("GetSizeMul", &ParticleEffect::GetSizeMul)
        .addFunction("GetColorFrames", &ParticleEffect::GetColorFrames)
        .addFunction("GetNumColorFrames", &ParticleEffect::GetNumColorFrames)
        .addFunction("GetColorFrame", &ParticleEffect::GetColorFrame)
        .addFunction("GetTextureFrames", &ParticleEffect::GetTextureFrames)
        .addFunction("GetNumTextureFrames", &ParticleEffect::GetNumTextureFrames)
        .addFunction("GetTextureFrame", &ParticleEffect::GetTextureFrame)
        .addFunction("GetFaceCameraMode", &ParticleEffect::GetFaceCameraMode)
        
        .addProperty("material", &ParticleEffect::GetMaterial, &ParticleEffect::SetMaterial)
        .addProperty("numParticles", &ParticleEffect::GetNumParticles, &ParticleEffect::SetNumParticles)
        .addProperty("updateInvisible", &ParticleEffect::GetUpdateInvisible, &ParticleEffect::SetUpdateInvisible)
        .addProperty("relative", &ParticleEffect::IsRelative, &ParticleEffect::SetRelative)
        .addProperty("scaled", &ParticleEffect::IsScaled, &ParticleEffect::SetScaled)
        .addProperty("sorted", &ParticleEffect::IsSorted, &ParticleEffect::SetSorted)
        .addProperty("fixedScreenSize", &ParticleEffect::IsFixedScreenSize, &ParticleEffect::SetFixedScreenSize)
        .addProperty("animationLodBias", &ParticleEffect::GetAnimationLodBias, &ParticleEffect::SetAnimationLodBias)
        .addProperty("emitterType", &ParticleEffect::GetEmitterType, &ParticleEffect::SetEmitterType)
        .addProperty("emitterSize", &ParticleEffect::GetEmitterSize, &ParticleEffect::SetEmitterSize)
        .addProperty("minDirection", &ParticleEffect::GetMinDirection, &ParticleEffect::SetMinDirection)
        .addProperty("maxDirection", &ParticleEffect::GetMaxDirection, &ParticleEffect::SetMaxDirection)
        .addProperty("constantForce", &ParticleEffect::GetConstantForce, &ParticleEffect::SetConstantForce)
        .addProperty("dampingForce", &ParticleEffect::GetDampingForce, &ParticleEffect::SetDampingForce)
        .addProperty("activeTime", &ParticleEffect::GetActiveTime, &ParticleEffect::SetActiveTime)
        .addProperty("inactiveTime", &ParticleEffect::GetInactiveTime, &ParticleEffect::SetInactiveTime)
        .addProperty("minEmissionRate", &ParticleEffect::GetMinEmissionRate, &ParticleEffect::SetMinEmissionRate)
        .addProperty("maxEmissionRate", &ParticleEffect::GetMaxEmissionRate, &ParticleEffect::SetMaxEmissionRate)
        .addProperty("minParticleSize", &ParticleEffect::GetMinParticleSize, &ParticleEffect::SetMinParticleSize)
        .addProperty("maxParticleSize", &ParticleEffect::GetMaxParticleSize, &ParticleEffect::SetMaxParticleSize)
        .addProperty("minTimeToLive", &ParticleEffect::GetMinTimeToLive, &ParticleEffect::SetMinTimeToLive)
        .addProperty("maxTimeToLive", &ParticleEffect::GetMaxTimeToLive, &ParticleEffect::SetMaxTimeToLive)
        .addProperty("minVelocity", &ParticleEffect::GetMinVelocity, &ParticleEffect::SetMinVelocity)
        .addProperty("maxVelocity", &ParticleEffect::GetMaxVelocity, &ParticleEffect::SetMaxVelocity)
        .addProperty("minRotation", &ParticleEffect::GetMinRotation, &ParticleEffect::SetMinRotation)
        .addProperty("maxRotation", &ParticleEffect::GetMaxRotation, &ParticleEffect::SetMaxRotation)
        .addProperty("minRotationSpeed", &ParticleEffect::GetMinRotationSpeed, &ParticleEffect::SetMinRotationSpeed)
        .addProperty("maxRotationSpeed", &ParticleEffect::GetMaxRotationSpeed, &ParticleEffect::SetMaxRotationSpeed)
        .addProperty("sizeAdd", &ParticleEffect::GetSizeAdd, &ParticleEffect::SetSizeAdd)
        .addProperty("sizeMul", &ParticleEffect::GetSizeMul, &ParticleEffect::SetSizeMul)
        .addProperty("colorFrames", &ParticleEffect::GetColorFrames, &ParticleEffect::SetColorFrames)
        .addProperty("numColorFrames", &ParticleEffect::GetNumColorFrames, &ParticleEffect::SetNumColorFrames)
        .addProperty("textureFrames", &ParticleEffect::GetTextureFrames, &ParticleEffect::SetTextureFrames)
        .addProperty("numTextureFrames", &ParticleEffect::GetNumTextureFrames, &ParticleEffect::SetNumTextureFrames)
        .addProperty("faceCameraMode", &ParticleEffect::GetFaceCameraMode, &ParticleEffect::SetFaceCameraMode)
        );
}
}

