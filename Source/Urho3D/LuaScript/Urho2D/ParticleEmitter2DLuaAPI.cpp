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

#include "../../Urho2D/ParticleEffect2D.h"
#include "../../Urho2D/ParticleEmitter2D.h"
#include "../../Urho2D/Sprite2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterParticleEmitter2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ParticleEmitter2D"].setClass(UserdataMetatable<ParticleEmitter2D, Drawable2D>()
        .addStaticFunction("new", &CreateObject<ParticleEmitter2D>)

        .addFunction("SetEffect", &ParticleEmitter2D::SetEffect)
        .addFunction("SetSprite", &ParticleEmitter2D::SetSprite)
        .addFunction("SetBlendMode", &ParticleEmitter2D::SetBlendMode)
        .addFunction("SetMaxParticles", &ParticleEmitter2D::SetMaxParticles)

        .addFunction("GetEffect", &ParticleEmitter2D::GetEffect)
        .addFunction("GetSprite", &ParticleEmitter2D::GetSprite)
        .addFunction("GetBlendMode", &ParticleEmitter2D::GetBlendMode)
        .addFunction("GetMaxParticles", &ParticleEmitter2D::GetMaxParticles)

        .addProperty("effect", &ParticleEmitter2D::GetEffect, &ParticleEmitter2D::SetEffect)
        .addProperty("sprite", &ParticleEmitter2D::GetSprite, &ParticleEmitter2D::SetSprite)
        .addProperty("blendMode", &ParticleEmitter2D::GetBlendMode, &ParticleEmitter2D::SetBlendMode)
        .addProperty("maxParticles", &ParticleEmitter2D::GetMaxParticles, &ParticleEmitter2D::SetMaxParticles)
    );
}
}

#endif
