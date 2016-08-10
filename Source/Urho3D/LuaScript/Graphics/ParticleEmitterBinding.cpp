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

#include "../../Graphics/ParticleEffect.h"
#include "../../Graphics/ParticleEmitter.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterParticleEmitter(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] ParticleEmitter : BillboardSet
    lua["ParticleEmitter"].setClass(UserdataMetatable<ParticleEmitter, BillboardSet>()
        // [Constructor] ParticleEmitter()
        .addStaticFunction("new", &CreateObject<ParticleEmitter>)

        // [Method] void SetEffect(ParticleEffect* effect)
        .addFunction("SetEffect", &ParticleEmitter::SetEffect)
        // [Method] void SetNumParticles(unsigned num)
        .addFunction("SetNumParticles", &ParticleEmitter::SetNumParticles)
        // [Method] void SetEmitting(bool enable)
        .addFunction("SetEmitting", &ParticleEmitter::SetEmitting)
        // [Method] void SetSerializeParticles(bool enable)
        .addFunction("SetSerializeParticles", &ParticleEmitter::SetSerializeParticles)
        // [Method] void ResetEmissionTimer()
        .addFunction("ResetEmissionTimer", &ParticleEmitter::ResetEmissionTimer)
        // [Method] void RemoveAllParticles()
        .addFunction("RemoveAllParticles", &ParticleEmitter::RemoveAllParticles)
        // [Method] void Reset()
        .addFunction("Reset", &ParticleEmitter::Reset)
        // [Method] void ApplyEffect()
        .addFunction("ApplyEffect", &ParticleEmitter::ApplyEffect)
        
        // [Method] ParticleEffect* GetEffect() const
        .addFunction("GetEffect", &ParticleEmitter::GetEffect)
        // [Method] unsigned GetNumParticles() const
        .addFunction("GetNumParticles", &ParticleEmitter::GetNumParticles)
        // [Method] bool IsEmitting() const
        .addFunction("IsEmitting", &ParticleEmitter::IsEmitting)
        // [Method] bool GetSerializeParticles() const
        .addFunction("GetSerializeParticles", &ParticleEmitter::GetSerializeParticles)

        // [Property] ParticleEffect* effect
        .addProperty("effect", &ParticleEmitter::GetEffect, &ParticleEmitter::SetEffect)
        // [Property] unsigned numParticles
        .addProperty("numParticles", &ParticleEmitter::GetNumParticles, &ParticleEmitter::SetNumParticles)
        // [Property] bool emitting
        .addProperty("emitting", &ParticleEmitter::IsEmitting, &ParticleEmitter::SetEmitting)
        // [Property] bool serializeParticles
        .addProperty("serializeParticles", &ParticleEmitter::GetSerializeParticles, &ParticleEmitter::SetSerializeParticles)
        );
}
}

