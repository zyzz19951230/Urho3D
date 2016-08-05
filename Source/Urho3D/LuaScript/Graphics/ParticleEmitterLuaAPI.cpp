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

    lua["ParticleEmitter"].setClass(UserdataMetatable<ParticleEmitter, BillboardSet>()
        .addStaticFunction("new", &CreateObject<ParticleEmitter>)

        .addFunction("SetEffect", &ParticleEmitter::SetEffect)
        .addFunction("SetNumParticles", &ParticleEmitter::SetNumParticles)
        .addFunction("SetEmitting", &ParticleEmitter::SetEmitting)
        .addFunction("SetSerializeParticles", &ParticleEmitter::SetSerializeParticles)
        .addFunction("ResetEmissionTimer", &ParticleEmitter::ResetEmissionTimer)
        .addFunction("RemoveAllParticles", &ParticleEmitter::RemoveAllParticles)
        .addFunction("Reset", &ParticleEmitter::Reset)
        .addFunction("ApplyEffect", &ParticleEmitter::ApplyEffect)
        
        .addFunction("GetEffect", &ParticleEmitter::GetEffect)
        .addFunction("GetNumParticles", &ParticleEmitter::GetNumParticles)
        .addFunction("IsEmitting", &ParticleEmitter::IsEmitting)
        .addFunction("GetSerializeParticles", &ParticleEmitter::GetSerializeParticles)

        .addProperty("effect", &ParticleEmitter::GetEffect, &ParticleEmitter::SetEffect)
        .addProperty("numParticles", &ParticleEmitter::GetNumParticles, &ParticleEmitter::SetNumParticles)
        .addProperty("emitting", &ParticleEmitter::IsEmitting, &ParticleEmitter::SetEmitting)
        .addProperty("serializeParticles", &ParticleEmitter::GetSerializeParticles, &ParticleEmitter::SetSerializeParticles)
        );
}
}

