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

    // [Class] ParticleEmitter2D : Drawable2D
    lua["ParticleEmitter2D"].setClass(UserdataMetatable<ParticleEmitter2D, Drawable2D>()
        // [Constructor] ParticleEmitter2D()
        .addStaticFunction("new", &CreateObject<ParticleEmitter2D>)

        // [Method] void SetEffect(ParticleEffect2D* effect)
        .addFunction("SetEffect", &ParticleEmitter2D::SetEffect)
        // [Method] void SetSprite(Sprite2D* sprite)
        .addFunction("SetSprite", &ParticleEmitter2D::SetSprite)
        // [Method] void SetBlendMode(BlendMode blendMode)
        .addFunction("SetBlendMode", &ParticleEmitter2D::SetBlendMode)
        // [Method] void SetMaxParticles(unsigned maxParticles)
        .addFunction("SetMaxParticles", &ParticleEmitter2D::SetMaxParticles)

        // [Method] ParticleEffect2D* GetEffect() const
        .addFunction("GetEffect", &ParticleEmitter2D::GetEffect)
        // [Method] Sprite2D* GetSprite() const
        .addFunction("GetSprite", &ParticleEmitter2D::GetSprite)
        // [Method] BlendMode GetBlendMode() const
        .addFunction("GetBlendMode", &ParticleEmitter2D::GetBlendMode)
        // [Method] unsigned GetMaxParticles() const
        .addFunction("GetMaxParticles", &ParticleEmitter2D::GetMaxParticles)

        // [Property] ParticleEffect2D* effect
        .addProperty("effect", &ParticleEmitter2D::GetEffect, &ParticleEmitter2D::SetEffect)
        // [Property] Sprite2D* sprite
        .addProperty("sprite", &ParticleEmitter2D::GetSprite, &ParticleEmitter2D::SetSprite)
        // [Property] BlendMode blendMode
        .addProperty("blendMode", &ParticleEmitter2D::GetBlendMode, &ParticleEmitter2D::SetBlendMode)
        // [Property] unsigned maxParticles
        .addProperty("maxParticles", &ParticleEmitter2D::GetMaxParticles, &ParticleEmitter2D::SetMaxParticles)
    );
}
}

#endif
