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

KAGUYA_MEMBER_FUNCTION_OVERLOADS(ParticleEffectClone, ParticleEffect, Clone, 0, 1);
    
void RegisterParticleEffect(kaguya::State& lua)
{
    using namespace kaguya;

    // [Enum] EmitterType
    lua["EMITTER_SPHERE"] = EMITTER_SPHERE;
    lua["EMITTER_BOX"] = EMITTER_BOX;


    // [Class] ColorFrame
    lua["ColorFrame"].setClass(UserdataMetatable<ColorFrame>()
        // [Constructor] ColorFrame()
    	.setConstructors<ColorFrame(),
            // [Constructor] ColorFrame(const Color& color)
    		ColorFrame(const Color&),
            // [Constructor] ColorFrame(const Color& color, float time)
    		ColorFrame(const Color&, float)>()

        // [Method] Color Interpolate(const ColorFrame& next, float time) const
		.addFunction("Interpolate", &ColorFrame::Interpolate)

        // [Field] Color color
    	.addProperty("color", &ColorFrame::color_)
        // [Field] float time
    	.addProperty("time", &ColorFrame::time_)
    	);

    // [Class] TextureFrame
	lua["TextureFrame"].setClass(UserdataMetatable<TextureFrame>()
        // [Constructor] TextureFrame()
        .setConstructors<TextureFrame()>()

        // [Field] Vector2 uv
		.addProperty("uv", &TextureFrame::uv_)
        // [Field] float time
		.addProperty("time", &TextureFrame::time_)
		);

    // [Class] ParticleEffect : Resource
    lua["ParticleEffect"].setClass(UserdataMetatable<ParticleEffect, Resource>()
        // [Constructor] ParticleEffect()
        .addStaticFunction("new", &CreateObject<ParticleEffect>)

        // [Method] void SetMaterial(Material* material)
        .addFunction("SetMaterial", &ParticleEffect::SetMaterial)
        // [Method] void SetNumParticles(unsigned num)
        .addFunction("SetNumParticles", &ParticleEffect::SetNumParticles)
        // [Method] void SetUpdateInvisible(bool enable)
        .addFunction("SetUpdateInvisible", &ParticleEffect::SetUpdateInvisible)
        // [Method] void SetRelative(bool enable)
        .addFunction("SetRelative", &ParticleEffect::SetRelative)
        // [Method] void SetScaled(bool enable)
        .addFunction("SetScaled", &ParticleEffect::SetScaled)
        // [Method] void SetSorted(bool enable)
        .addFunction("SetSorted", &ParticleEffect::SetSorted)
        
        // [Method] void SetFixedScreenSize(bool enable)
        .addFunction("SetFixedScreenSize", &ParticleEffect::SetFixedScreenSize)
        // [Method] void SetAnimationLodBias(float lodBias)
        .addFunction("SetAnimationLodBias", &ParticleEffect::SetAnimationLodBias)
        // [Method] void SetEmitterType(EmitterType type)
        .addFunction("SetEmitterType", &ParticleEffect::SetEmitterType)
        // [Method] void SetEmitterSize(const Vector3& size)
        .addFunction("SetEmitterSize", &ParticleEffect::SetEmitterSize)
        // [Method] void SetMinDirection(const Vector3& direction)
        .addFunction("SetMinDirection", &ParticleEffect::SetMinDirection)
        // [Method] void SetMaxDirection(const Vector3& direction)
        .addFunction("SetMaxDirection", &ParticleEffect::SetMaxDirection)
        
        // [Method] void SetConstantForce(const Vector3& force)
        .addFunction("SetConstantForce", &ParticleEffect::SetConstantForce)
        // [Method] void SetDampingForce(float force)
        .addFunction("SetDampingForce", &ParticleEffect::SetDampingForce)
        // [Method] void SetActiveTime(float time)
        .addFunction("SetActiveTime", &ParticleEffect::SetActiveTime)
        // [Method] void SetInactiveTime(float time)
        .addFunction("SetInactiveTime", &ParticleEffect::SetInactiveTime)
        // [Method] void SetMinEmissionRate(float rate)
        .addFunction("SetMinEmissionRate", &ParticleEffect::SetMinEmissionRate)
        // [Method] void SetMaxEmissionRate(float rate)
        .addFunction("SetMaxEmissionRate", &ParticleEffect::SetMaxEmissionRate)
        
        // [Method] void SetMinParticleSize(const Vector2& size)
        .addFunction("SetMinParticleSize", &ParticleEffect::SetMinParticleSize)
        // [Method] void SetMaxParticleSize(const Vector2& size)
        .addFunction("SetMaxParticleSize", &ParticleEffect::SetMaxParticleSize)
        // [Method] void SetMinTimeToLive(float time)
        .addFunction("SetMinTimeToLive", &ParticleEffect::SetMinTimeToLive)
        // [Method] void SetMaxTimeToLive(float time)
        .addFunction("SetMaxTimeToLive", &ParticleEffect::SetMaxTimeToLive)
        // [Method] void SetMinVelocity(float velocity)
        .addFunction("SetMinVelocity", &ParticleEffect::SetMinVelocity)
        // [Method] void SetMaxVelocity(float velocity)
        .addFunction("SetMaxVelocity", &ParticleEffect::SetMaxVelocity)
        
        // [Method] void SetMinRotation(float rotation)
        .addFunction("SetMinRotation", &ParticleEffect::SetMinRotation)
        // [Method] void SetMaxRotation(float rotation)
        .addFunction("SetMaxRotation", &ParticleEffect::SetMaxRotation)
        // [Method] void SetMinRotationSpeed(float speed)
        .addFunction("SetMinRotationSpeed", &ParticleEffect::SetMinRotationSpeed)
        // [Method] void SetMaxRotationSpeed(float speed)
        .addFunction("SetMaxRotationSpeed", &ParticleEffect::SetMaxRotationSpeed)
        // [Method] void SetSizeAdd(float sizeAdd)
        .addFunction("SetSizeAdd", &ParticleEffect::SetSizeAdd)
        // [Method] void SetSizeMul(float sizeMul)
        .addFunction("SetSizeMul", &ParticleEffect::SetSizeMul)
        
        // [Method] void SetFaceCameraMode(FaceCameraMode mode)
        .addFunction("SetFaceCameraMode", &ParticleEffect::SetFaceCameraMode)
        
        // [Method] void AddColorTime(const Color& color, const float time)
        .addFunction("AddColorTime", &ParticleEffect::AddColorTime)
        // [Method] void AddColorFrame(const ColorFrame& colorFrame)
        .addFunction("AddColorFrame", &ParticleEffect::AddColorFrame)
        // [Method] void RemoveColorFrame(unsigned index)
        .addFunction("RemoveColorFrame", &ParticleEffect::RemoveColorFrame)
        // [Method] void SetColorFrames(const Vector<ColorFrame>& colorFrames)
        .addFunction("SetColorFrames", &ParticleEffect::SetColorFrames)
        // [Method] void SetColorFrame(unsigned index, const ColorFrame& colorFrame)
        .addFunction("SetColorFrame", &ParticleEffect::SetColorFrame)
        // [Method] void SetNumColorFrames(unsigned number)
        .addFunction("SetNumColorFrames", &ParticleEffect::SetNumColorFrames)
        // [Method] void SortColorFrames()
        .addFunction("SortColorFrames", &ParticleEffect::SortColorFrames)
        
        // [Method] void AddTextureTime(const Rect& uv, const float time)
        .addFunction("AddTextureTime", &ParticleEffect::AddTextureTime)
        // [Method] void AddTextureFrame(const TextureFrame& textureFrame)
        .addFunction("AddTextureFrame", &ParticleEffect::AddTextureFrame)
        // [Method] void RemoveTextureFrame(unsigned index)
        .addFunction("RemoveTextureFrame", &ParticleEffect::RemoveTextureFrame)
        // [Method] void SetTextureFrames(const Vector<TextureFrame>& animation)
        .addFunction("SetTextureFrames", &ParticleEffect::SetTextureFrames)
        // [Method] void SetTextureFrame(unsigned index, const TextureFrame& textureFrame)
        .addFunction("SetTextureFrame", &ParticleEffect::SetTextureFrame)
        // [Method] void SetNumTextureFrames(unsigned number)
        .addFunction("SetNumTextureFrames", &ParticleEffect::SetNumTextureFrames)
        // [Method] void SortTextureFrames()
        .addFunction("SortTextureFrames", &ParticleEffect::SortTextureFrames)

        // [Method] SharedPtr<ParticleEffect> Clone(const String& cloneName = String::EMPTY) const
        .addFunction("Clone", ParticleEffectClone())
        
        // [Method] Material* GetMaterial() const
        .addFunction("GetMaterial", &ParticleEffect::GetMaterial)
        // [Method] unsigned GetNumParticles() const
        .addFunction("GetNumParticles", &ParticleEffect::GetNumParticles)
        // [Method] bool GetUpdateInvisible() const
        .addFunction("GetUpdateInvisible", &ParticleEffect::GetUpdateInvisible)
        // [Method] bool IsRelative() const
        .addFunction("IsRelative", &ParticleEffect::IsRelative)
        // [Method] bool IsScaled() const
        .addFunction("IsScaled", &ParticleEffect::IsScaled)
        // [Method] bool IsSorted() const
        .addFunction("IsSorted", &ParticleEffect::IsSorted)
        // [Method] bool IsFixedScreenSize() const
        .addFunction("IsFixedScreenSize", &ParticleEffect::IsFixedScreenSize)
        // [Method] float GetAnimationLodBias() const
        .addFunction("GetAnimationLodBias", &ParticleEffect::GetAnimationLodBias)
        // [Method] EmitterType GetEmitterType() const
        .addFunction("GetEmitterType", &ParticleEffect::GetEmitterType)
        // [Method] const Vector3& GetEmitterSize() const
        .addFunction("GetEmitterSize", &ParticleEffect::GetEmitterSize)
        // [Method] const Vector3& GetMinDirection() const
        .addFunction("GetMinDirection", &ParticleEffect::GetMinDirection)
        // [Method] const Vector3& GetMaxDirection() const
        .addFunction("GetMaxDirection", &ParticleEffect::GetMaxDirection)
        // [Method] const Vector3& GetConstantForce() const
        .addFunction("GetConstantForce", &ParticleEffect::GetConstantForce)
        // [Method] float GetDampingForce() const
        .addFunction("GetDampingForce", &ParticleEffect::GetDampingForce)
        // [Method] float GetActiveTime() const
        .addFunction("GetActiveTime", &ParticleEffect::GetActiveTime)
        // [Method] float GetInactiveTime() const
        .addFunction("GetInactiveTime", &ParticleEffect::GetInactiveTime)
        // [Method] float GetMinEmissionRate() const
        .addFunction("GetMinEmissionRate", &ParticleEffect::GetMinEmissionRate)
        // [Method] float GetMaxEmissionRate() const
        .addFunction("GetMaxEmissionRate", &ParticleEffect::GetMaxEmissionRate)
        // [Method] const Vector2& GetMinParticleSize() const
        .addFunction("GetMinParticleSize", &ParticleEffect::GetMinParticleSize)
        // [Method] const Vector2& GetMaxParticleSize() const
        .addFunction("GetMaxParticleSize", &ParticleEffect::GetMaxParticleSize)
        // [Method] float GetMinTimeToLive() const
        .addFunction("GetMinTimeToLive", &ParticleEffect::GetMinTimeToLive)
        // [Method] float GetMaxTimeToLive() const
        .addFunction("GetMaxTimeToLive", &ParticleEffect::GetMaxTimeToLive)
        // [Method] float GetMinVelocity() const
        .addFunction("GetMinVelocity", &ParticleEffect::GetMinVelocity)
        // [Method] float GetMaxVelocity() const
        .addFunction("GetMaxVelocity", &ParticleEffect::GetMaxVelocity)
        // [Method] float GetMinRotation() const
        .addFunction("GetMinRotation", &ParticleEffect::GetMinRotation)
        // [Method] float GetMaxRotation() const
        .addFunction("GetMaxRotation", &ParticleEffect::GetMaxRotation)
        // [Method] float GetMinRotationSpeed() const
        .addFunction("GetMinRotationSpeed", &ParticleEffect::GetMinRotationSpeed)
        // [Method] float GetMaxRotationSpeed() const
        .addFunction("GetMaxRotationSpeed", &ParticleEffect::GetMaxRotationSpeed)
        // [Method] float GetSizeAdd() const
        .addFunction("GetSizeAdd", &ParticleEffect::GetSizeAdd)
        // [Method] float GetSizeMul() const
        .addFunction("GetSizeMul", &ParticleEffect::GetSizeMul)
        // [Method] const Vector<ColorFrame>& GetColorFrames() const
        .addFunction("GetColorFrames", &ParticleEffect::GetColorFrames)
        // [Method] unsigned GetNumColorFrames() const
        .addFunction("GetNumColorFrames", &ParticleEffect::GetNumColorFrames)
        // [Method] const ColorFrame* GetColorFrame(unsigned index) const
        .addFunction("GetColorFrame", &ParticleEffect::GetColorFrame)
        // [Method] const Vector<TextureFrame>& GetTextureFrames() const
        .addFunction("GetTextureFrames", &ParticleEffect::GetTextureFrames)
        // [Method] unsigned GetNumTextureFrames() const
        .addFunction("GetNumTextureFrames", &ParticleEffect::GetNumTextureFrames)
        // [Method] const TextureFrame* GetTextureFrame(unsigned index) const
        .addFunction("GetTextureFrame", &ParticleEffect::GetTextureFrame)
        // [Method] FaceCameraMode GetFaceCameraMode() const
        .addFunction("GetFaceCameraMode", &ParticleEffect::GetFaceCameraMode)
        
        // [Property] Material* material
        .addProperty("material", &ParticleEffect::GetMaterial, &ParticleEffect::SetMaterial)
        // [Property] unsigned numParticles
        .addProperty("numParticles", &ParticleEffect::GetNumParticles, &ParticleEffect::SetNumParticles)
        // [Property] bool updateInvisible
        .addProperty("updateInvisible", &ParticleEffect::GetUpdateInvisible, &ParticleEffect::SetUpdateInvisible)
        // [Property] bool relative
        .addProperty("relative", &ParticleEffect::IsRelative, &ParticleEffect::SetRelative)
        // [Property] bool scaled
        .addProperty("scaled", &ParticleEffect::IsScaled, &ParticleEffect::SetScaled)
        // [Property] bool sorted
        .addProperty("sorted", &ParticleEffect::IsSorted, &ParticleEffect::SetSorted)
        // [Property] bool fixedScreenSize
        .addProperty("fixedScreenSize", &ParticleEffect::IsFixedScreenSize, &ParticleEffect::SetFixedScreenSize)
        // [Property] float animationLodBias
        .addProperty("animationLodBias", &ParticleEffect::GetAnimationLodBias, &ParticleEffect::SetAnimationLodBias)
        // [Property] EmitterType emitterType
        .addProperty("emitterType", &ParticleEffect::GetEmitterType, &ParticleEffect::SetEmitterType)
        // [Property] const Vector3& emitterSize
        .addProperty("emitterSize", &ParticleEffect::GetEmitterSize, &ParticleEffect::SetEmitterSize)
        // [Property] const Vector3& minDirection
        .addProperty("minDirection", &ParticleEffect::GetMinDirection, &ParticleEffect::SetMinDirection)
        // [Property] const Vector3& maxDirection
        .addProperty("maxDirection", &ParticleEffect::GetMaxDirection, &ParticleEffect::SetMaxDirection)
        // [Property] const Vector3& constantForce
        .addProperty("constantForce", &ParticleEffect::GetConstantForce, &ParticleEffect::SetConstantForce)
        // [Property] float dampingForce
        .addProperty("dampingForce", &ParticleEffect::GetDampingForce, &ParticleEffect::SetDampingForce)
        // [Property] float activeTime
        .addProperty("activeTime", &ParticleEffect::GetActiveTime, &ParticleEffect::SetActiveTime)
        // [Property] float inactiveTime
        .addProperty("inactiveTime", &ParticleEffect::GetInactiveTime, &ParticleEffect::SetInactiveTime)
        // [Property] float minEmissionRate
        .addProperty("minEmissionRate", &ParticleEffect::GetMinEmissionRate, &ParticleEffect::SetMinEmissionRate)
        // [Property] float maxEmissionRate
        .addProperty("maxEmissionRate", &ParticleEffect::GetMaxEmissionRate, &ParticleEffect::SetMaxEmissionRate)
        // [Property] const Vector2& minParticleSize
        .addProperty("minParticleSize", &ParticleEffect::GetMinParticleSize, &ParticleEffect::SetMinParticleSize)
        // [Property] const Vector2& maxParticleSize
        .addProperty("maxParticleSize", &ParticleEffect::GetMaxParticleSize, &ParticleEffect::SetMaxParticleSize)
        // [Property] float minTimeToLive
        .addProperty("minTimeToLive", &ParticleEffect::GetMinTimeToLive, &ParticleEffect::SetMinTimeToLive)
        // [Property] float maxTimeToLive
        .addProperty("maxTimeToLive", &ParticleEffect::GetMaxTimeToLive, &ParticleEffect::SetMaxTimeToLive)
        // [Property] float minVelocity
        .addProperty("minVelocity", &ParticleEffect::GetMinVelocity, &ParticleEffect::SetMinVelocity)
        // [Property] float maxVelocity
        .addProperty("maxVelocity", &ParticleEffect::GetMaxVelocity, &ParticleEffect::SetMaxVelocity)
        // [Property] float minRotation
        .addProperty("minRotation", &ParticleEffect::GetMinRotation, &ParticleEffect::SetMinRotation)
        // [Property] float maxRotation
        .addProperty("maxRotation", &ParticleEffect::GetMaxRotation, &ParticleEffect::SetMaxRotation)
        // [Property] float minRotationSpeed
        .addProperty("minRotationSpeed", &ParticleEffect::GetMinRotationSpeed, &ParticleEffect::SetMinRotationSpeed)
        // [Property] float maxRotationSpeed
        .addProperty("maxRotationSpeed", &ParticleEffect::GetMaxRotationSpeed, &ParticleEffect::SetMaxRotationSpeed)
        // [Property] float sizeAdd
        .addProperty("sizeAdd", &ParticleEffect::GetSizeAdd, &ParticleEffect::SetSizeAdd)
        // [Property] float sizeMul
        .addProperty("sizeMul", &ParticleEffect::GetSizeMul, &ParticleEffect::SetSizeMul)
        // [Property] const Vector<ColorFrame>& colorFrames
        .addProperty("colorFrames", &ParticleEffect::GetColorFrames, &ParticleEffect::SetColorFrames)
        // [Property] unsigned numColorFrames
        .addProperty("numColorFrames", &ParticleEffect::GetNumColorFrames, &ParticleEffect::SetNumColorFrames)
        // [Property] const Vector<TextureFrame>& textureFrames
        .addProperty("textureFrames", &ParticleEffect::GetTextureFrames, &ParticleEffect::SetTextureFrames)
        // [Property] unsigned numTextureFrames
        .addProperty("numTextureFrames", &ParticleEffect::GetNumTextureFrames, &ParticleEffect::SetNumTextureFrames)
        // [Property] FaceCameraMode faceCameraMode
        .addProperty("faceCameraMode", &ParticleEffect::GetFaceCameraMode, &ParticleEffect::SetFaceCameraMode)
        );
}
}

