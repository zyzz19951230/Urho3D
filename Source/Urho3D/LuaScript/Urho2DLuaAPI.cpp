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

#include "../Precompiled.h"

#include <kaguya.hpp>

namespace Urho3D
{

extern void RegisterDrawable2D(kaguya::State& lua); 
extern void RegisterStaticSprite2D(kaguya::State& lua);
extern void RegisterCollisionShape2D(kaguya::State& lua);
extern void RegisterConstraint2D(kaguya::State& lua);
extern void RegisterAnimatedSprite2D(kaguya::State& lua);
extern void RegisterAnimationSet2D(kaguya::State& lua);
extern void RegisterCollisionBox2D(kaguya::State& lua);
extern void RegisterCollisionChain2D(kaguya::State& lua);
extern void RegisterCollisionCircle2D(kaguya::State& lua);
extern void RegisterCollisionEdge2D(kaguya::State& lua);
extern void RegisterCollisionPolygon2D(kaguya::State& lua);
extern void RegisterConstraintDistance2D(kaguya::State& lua);
extern void RegisterConstraintFriction2D(kaguya::State& lua);
extern void RegisterConstraintGear2D(kaguya::State& lua);
extern void RegisterConstraintMotor2D(kaguya::State& lua);
extern void RegisterConstraintMouse2D(kaguya::State& lua);
extern void RegisterConstraintPrismatic2D(kaguya::State& lua);
extern void RegisterConstraintPulley2D(kaguya::State& lua);
extern void RegisterConstraintRevolute2D(kaguya::State& lua);
extern void RegisterConstraintRope2D(kaguya::State& lua);
extern void RegisterConstraintWeld2D(kaguya::State& lua);
extern void RegisterConstraintWheel2D(kaguya::State& lua);
extern void RegisterParticleEffect2D(kaguya::State& lua);
extern void RegisterParticleEmitter2D(kaguya::State& lua);
extern void RegisterPhysicsWorld2D(kaguya::State& lua);
extern void RegisterRigidBody2D(kaguya::State& lua);
extern void RegisterSprite2D(kaguya::State& lua);
extern void RegisterSpriteSheet2D(kaguya::State& lua);
extern void RegisterTileMap2D(kaguya::State& lua);
extern void RegisterTileMapDefs2D(kaguya::State& lua);
extern void RegisterTileMapLayer2D(kaguya::State& lua);
extern void RegisterTmxFile2D(kaguya::State& lua);

void RegisterUrho2DLuaAPI(kaguya::State& lua)
{
    RegisterDrawable2D(lua); 
    RegisterStaticSprite2D(lua);
    RegisterCollisionShape2D(lua);
    RegisterConstraint2D(lua);

    RegisterAnimatedSprite2D(lua);
    RegisterAnimationSet2D(lua);
    RegisterCollisionBox2D(lua);
    RegisterCollisionChain2D(lua);
    RegisterCollisionCircle2D(lua);
    RegisterCollisionEdge2D(lua);
    RegisterCollisionPolygon2D(lua);
    RegisterConstraintDistance2D(lua);
    RegisterConstraintFriction2D(lua);
    RegisterConstraintGear2D(lua);
    RegisterConstraintMotor2D(lua);
    RegisterConstraintMouse2D(lua);
    RegisterConstraintPrismatic2D(lua);
    RegisterConstraintPulley2D(lua);
    RegisterConstraintRevolute2D(lua);
    RegisterConstraintRope2D(lua);
    RegisterConstraintWeld2D(lua);
    RegisterConstraintWheel2D(lua);
    RegisterParticleEffect2D(lua);
    RegisterParticleEmitter2D(lua);
    RegisterPhysicsWorld2D(lua);
    RegisterRigidBody2D(lua);
    RegisterSprite2D(lua);
    RegisterSpriteSheet2D(lua);
    RegisterTileMap2D(lua);
    RegisterTileMapDefs2D(lua);
    RegisterTileMapLayer2D(lua);
    RegisterTmxFile2D(lua);
}
}

#endif
