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

#include "../Graphics/Material.h"
#include "../Graphics/Texture2D.h"
#include "../LuaScript/LuaScriptUtils.h"
#include "../Scene/Node.h"
#include "../Urho2D/AnimatedSprite2D.h"
#include "../Urho2D/AnimationSet2D.h"
#include "../Urho2D/CollisionBox2D.h"
#include "../Urho2D/CollisionChain2D.h"
#include "../Urho2D/CollisionCircle2D.h"
#include "../Urho2D/CollisionEdge2D.h"
#include "../Urho2D/CollisionPolygon2D.h"
#include "../Urho2D/CollisionShape2D.h"
#include "../Urho2D/Constraint2D.h"
#include "../Urho2D/ConstraintDistance2D.h"
#include "../Urho2D/ConstraintFriction2D.h"
#include "../Urho2D/ConstraintGear2D.h"
#include "../Urho2D/ConstraintMotor2D.h"
#include "../Urho2D/ConstraintMouse2D.h"
#include "../Urho2D/ConstraintPrismatic2D.h"
#include "../Urho2D/ConstraintPulley2D.h"
#include "../Urho2D/ConstraintRevolute2D.h"
#include "../Urho2D/ConstraintRope2D.h"
#include "../Urho2D/ConstraintWeld2D.h"
#include "../Urho2D/ConstraintWheel2D.h"
#include "../Urho2D/Drawable2D.h"
#include "../Urho2D/ParticleEffect2D.h"
#include "../Urho2D/ParticleEmitter2D.h"
#include "../Urho2D/PhysicsWorld2D.h"
#include "../Urho2D/RigidBody2D.h"
#include "../Urho2D/Sprite2D.h"
#include "../Urho2D/SpriteSheet2D.h"
#include "../Urho2D/StaticSprite2D.h"
#include "../Urho2D/TileMap2D.h"
#include "../Urho2D/TileMapDefs2D.h"
#include "../Urho2D/TileMapLayer2D.h"
#include "../Urho2D/TmxFile2D.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(AnimatedSprite2DSetAnimation, AnimatedSprite2D, SetAnimation, 1, 2);

static void RegisterAnimatedSprite2D(kaguya::State& lua)
{
    using namespace kaguya;

    // enum LoopMode2D;
    lua["LM_DEFAULT"] = LM_DEFAULT;
    lua["LM_FORCE_LOOPED"] = LM_FORCE_LOOPED;
    lua["LM_FORCE_CLAMPED"] = LM_FORCE_CLAMPED;

    lua["AnimatedSprite2D"].setClass(UserdataMetatable<AnimatedSprite2D, StaticSprite2D>()
        .addStaticFunction("new", &CreateObject<AnimatedSprite2D>)

        .addFunction("SetAnimationSet", &AnimatedSprite2D::SetAnimationSet)
        .addFunction("SetEntity", &AnimatedSprite2D::SetEntity)

        .addFunction("SetAnimation", AnimatedSprite2DSetAnimation())

        .addFunction("SetLoopMode", &AnimatedSprite2D::SetLoopMode)
        .addFunction("SetSpeed", &AnimatedSprite2D::SetSpeed)

        .addFunction("GetAnimationSet", &AnimatedSprite2D::GetAnimationSet)
        .addFunction("GetEntity", &AnimatedSprite2D::GetEntity)
        .addFunction("GetAnimation", &AnimatedSprite2D::GetAnimation)
        .addFunction("GetLoopMode", &AnimatedSprite2D::GetLoopMode)
        .addFunction("GetSpeed", &AnimatedSprite2D::GetSpeed)

        .addProperty("animationSet", &AnimatedSprite2D::GetAnimationSet, &AnimatedSprite2D::SetAnimationSet)
        .addProperty("entity", &AnimatedSprite2D::GetEntity, &AnimatedSprite2D::SetEntity)
        .addProperty("animation", &AnimatedSprite2D::GetAnimation)
        .addProperty("loopMode", &AnimatedSprite2D::GetLoopMode, &AnimatedSprite2D::SetLoopMode)
        .addProperty("speed", &AnimatedSprite2D::GetSpeed, &AnimatedSprite2D::SetSpeed)
    );
}

static void RegisterAnimationSet2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["AnimationSet2D"].setClass(UserdataMetatable<AnimationSet2D, Resource>()
        .addStaticFunction("new", &CreateObject<AnimationSet2D>)

        .addFunction("GetNumAnimations", &AnimationSet2D::GetNumAnimations)
        .addFunction("GetAnimation", &AnimationSet2D::GetAnimation)
        .addFunction("HasAnimation", &AnimationSet2D::HasAnimation)

        .addProperty("numAnimations", &AnimationSet2D::GetNumAnimations)
    );
}

static void RegisterCollisionBox2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["CollisionBox2D"].setClass(UserdataMetatable<CollisionBox2D, CollisionShape2D>()
        .addStaticFunction("new", &CreateObject<CollisionBox2D>)

        .addOverloadedFunctions("SetSize",
            static_cast<void(CollisionBox2D::*)(const Vector2&)>(&CollisionBox2D::SetSize),
            static_cast<void(CollisionBox2D::*)(float, float)>(&CollisionBox2D::SetSize))

        .addOverloadedFunctions("SetCenter",
            static_cast<void(CollisionBox2D::*)(const Vector2&)>(&CollisionBox2D::SetCenter),
            static_cast<void(CollisionBox2D::*)(float, float)>(&CollisionBox2D::SetCenter))

        .addFunction("SetAngle", &CollisionBox2D::SetAngle)

        .addFunction("GetSize", &CollisionBox2D::GetSize)
        .addFunction("GetCenter", &CollisionBox2D::GetCenter)
        .addFunction("GetAngle", &CollisionBox2D::GetAngle)

        .addProperty("size", &CollisionBox2D::GetSize, static_cast<void(CollisionBox2D::*)(const Vector2&)>(&CollisionBox2D::SetSize))
        .addProperty("center", &CollisionBox2D::GetCenter, static_cast<void(CollisionBox2D::*)(const Vector2&)>(&CollisionBox2D::SetCenter))
        .addProperty("angle", &CollisionBox2D::GetAngle, &CollisionBox2D::SetAngle)
    );
}

static void RegisterCollisionChain2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["CollisionChain2D"].setClass(UserdataMetatable<CollisionChain2D, CollisionShape2D>()
        .addStaticFunction("new", &CreateObject<CollisionChain2D>)

        .addFunction("SetLoop", &CollisionChain2D::SetLoop)
        .addFunction("SetVertexCount", &CollisionChain2D::SetVertexCount)
        .addFunction("SetVertex", &CollisionChain2D::SetVertex)
        .addFunction("SetVertices", &CollisionChain2D::SetVertices)

        .addFunction("GetLoop", &CollisionChain2D::GetLoop)
        .addFunction("GetVertexCount", &CollisionChain2D::GetVertexCount)
        .addFunction("GetVertex", &CollisionChain2D::GetVertex)
        .addFunction("GetVertices", &CollisionChain2D::GetVertices)

        .addProperty("loop", &CollisionChain2D::GetLoop, &CollisionChain2D::SetLoop)
        .addProperty("vertexCount", &CollisionChain2D::GetVertexCount, &CollisionChain2D::SetVertexCount)
    );
}

static void RegisterCollisionCircle2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["CollisionCircle2D"].setClass(UserdataMetatable<CollisionCircle2D, CollisionShape2D>()
        .addStaticFunction("new", &CreateObject<CollisionCircle2D>)

        .addFunction("SetRadius", &CollisionCircle2D::SetRadius)

        .addOverloadedFunctions("SetCenter",
            static_cast<void(CollisionCircle2D::*)(const Vector2&)>(&CollisionCircle2D::SetCenter),
            static_cast<void(CollisionCircle2D::*)(float, float)>(&CollisionCircle2D::SetCenter))

        .addFunction("GetRadius", &CollisionCircle2D::GetRadius)
        .addFunction("GetCenter", &CollisionCircle2D::GetCenter)

        .addProperty("radius", &CollisionCircle2D::GetRadius, &CollisionCircle2D::SetRadius)
        .addProperty("center", &CollisionCircle2D::GetCenter, static_cast<void(CollisionCircle2D::*)(const Vector2&)>(&CollisionCircle2D::SetCenter))
    );
}

static void RegisterCollisionEdge2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["CollisionEdge2D"].setClass(UserdataMetatable<CollisionEdge2D, CollisionShape2D>()
        .addStaticFunction("new", &CreateObject<CollisionEdge2D>)

        .addFunction("SetVertex1", &CollisionEdge2D::SetVertex1)
        .addFunction("SetVertex2", &CollisionEdge2D::SetVertex2)
        .addFunction("SetVertices", &CollisionEdge2D::SetVertices)

        .addFunction("GetVertex1", &CollisionEdge2D::GetVertex1)
        .addFunction("GetVertex2", &CollisionEdge2D::GetVertex2)

        .addProperty("vertex1", &CollisionEdge2D::GetVertex1, &CollisionEdge2D::SetVertex1)
        .addProperty("vertex2", &CollisionEdge2D::GetVertex2, &CollisionEdge2D::SetVertex2)
    );
}

static void RegisterCollisionPolygon2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["CollisionPolygon2D"].setClass(UserdataMetatable<CollisionPolygon2D, CollisionShape2D>()
        .addStaticFunction("new", &CreateObject<CollisionPolygon2D>)

        .addFunction("SetVertexCount", &CollisionPolygon2D::SetVertexCount)
        .addFunction("SetVertex", &CollisionPolygon2D::SetVertex)
        .addFunction("SetVertices", &CollisionPolygon2D::SetVertices)

        .addFunction("GetVertexCount", &CollisionPolygon2D::GetVertexCount)
        .addFunction("GetVertex", &CollisionPolygon2D::GetVertex)
        .addFunction("GetVertices", &CollisionPolygon2D::GetVertices)

        .addProperty("vertexCount", &CollisionPolygon2D::GetVertexCount, &CollisionPolygon2D::SetVertexCount)
    );
}

static void RegisterCollisionShape2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["CollisionShape2D"].setClass(UserdataMetatable<CollisionShape2D, Component>()

        .addFunction("SetTrigger", &CollisionShape2D::SetTrigger)
        .addFunction("SetCategoryBits", &CollisionShape2D::SetCategoryBits)
        .addFunction("SetMaskBits", &CollisionShape2D::SetMaskBits)
        .addFunction("SetGroupIndex", &CollisionShape2D::SetGroupIndex)
        .addFunction("SetDensity", &CollisionShape2D::SetDensity)
        .addFunction("SetFriction", &CollisionShape2D::SetFriction)
        .addFunction("SetRestitution", &CollisionShape2D::SetRestitution)

        .addFunction("IsTrigger", &CollisionShape2D::IsTrigger)
        .addFunction("GetCategoryBits", &CollisionShape2D::GetCategoryBits)
        .addFunction("GetMaskBits", &CollisionShape2D::GetMaskBits)
        .addFunction("GetGroupIndex", &CollisionShape2D::GetGroupIndex)
        .addFunction("GetDensity", &CollisionShape2D::GetDensity)
        .addFunction("GetFriction", &CollisionShape2D::GetFriction)
        .addFunction("GetRestitution", &CollisionShape2D::GetRestitution)
        .addFunction("GetMass", &CollisionShape2D::GetMass)
        .addFunction("GetInertia", &CollisionShape2D::GetInertia)
        .addFunction("GetMassCenter", &CollisionShape2D::GetMassCenter)

        .addProperty("trigger", &CollisionShape2D::IsTrigger, &CollisionShape2D::SetTrigger)
        .addProperty("categoryBits", &CollisionShape2D::GetCategoryBits, &CollisionShape2D::SetCategoryBits)
        .addProperty("maskBits", &CollisionShape2D::GetMaskBits, &CollisionShape2D::SetMaskBits)
        .addProperty("groupIndex", &CollisionShape2D::GetGroupIndex, &CollisionShape2D::SetGroupIndex)
        .addProperty("density", &CollisionShape2D::GetDensity, &CollisionShape2D::SetDensity)
        .addProperty("friction", &CollisionShape2D::GetFriction, &CollisionShape2D::SetFriction)
        .addProperty("restitution", &CollisionShape2D::GetRestitution, &CollisionShape2D::SetRestitution)
        .addProperty("mass", &CollisionShape2D::GetMass)
        .addProperty("inertia", &CollisionShape2D::GetInertia)
        .addProperty("massCenter", &CollisionShape2D::GetMassCenter)
    );
}

static void RegisterConstraint2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Constraint2D"].setClass(UserdataMetatable<Constraint2D, Component>()
        .addStaticFunction("new", &CreateObject<Constraint2D>)

        .addFunction("SetOtherBody", &Constraint2D::SetOtherBody)
        .addFunction("SetCollideConnected", &Constraint2D::SetCollideConnected)
        
        .addFunction("GetOwnerBody", &Constraint2D::GetOwnerBody)
        .addFunction("GetOtherBody", &Constraint2D::GetOtherBody)
        .addFunction("GetCollideConnected", &Constraint2D::GetCollideConnected)
        
        .addProperty("ownerBody", &Constraint2D::GetOwnerBody)
        .addProperty("otherBody", &Constraint2D::GetOtherBody, &Constraint2D::SetOtherBody)
        .addProperty("collideConnected", &Constraint2D::GetCollideConnected, &Constraint2D::SetCollideConnected)
    );
}

static void RegisterConstraintDistance2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ConstraintDistance2D"].setClass(UserdataMetatable<ConstraintDistance2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintDistance2D>)

        .addFunction("SetOwnerBodyAnchor", &ConstraintDistance2D::SetOwnerBodyAnchor)
        .addFunction("SetOtherBodyAnchor", &ConstraintDistance2D::SetOtherBodyAnchor)
        .addFunction("SetFrequencyHz", &ConstraintDistance2D::SetFrequencyHz)
        .addFunction("SetDampingRatio", &ConstraintDistance2D::SetDampingRatio)

        .addFunction("GetOwnerBodyAnchor", &ConstraintDistance2D::GetOwnerBodyAnchor)
        .addFunction("GetOtherBodyAnchor", &ConstraintDistance2D::GetOtherBodyAnchor)
        .addFunction("GetFrequencyHz", &ConstraintDistance2D::GetFrequencyHz)
        .addFunction("GetDampingRatio", &ConstraintDistance2D::GetDampingRatio)

        .addProperty("ownerBodyAnchor", &ConstraintDistance2D::GetOwnerBodyAnchor, &ConstraintDistance2D::SetOwnerBodyAnchor)
        .addProperty("otherBodyAnchor", &ConstraintDistance2D::GetOtherBodyAnchor, &ConstraintDistance2D::SetOtherBodyAnchor)
        .addProperty("frequencyHz", &ConstraintDistance2D::GetFrequencyHz, &ConstraintDistance2D::SetFrequencyHz)
        .addProperty("dampingRatio", &ConstraintDistance2D::GetDampingRatio, &ConstraintDistance2D::SetDampingRatio)
    );
}

static void RegisterConstraintFriction2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ConstraintFriction2D"].setClass(UserdataMetatable<ConstraintFriction2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintFriction2D>)

        .addFunction("SetAnchor", &ConstraintFriction2D::SetAnchor)
        .addFunction("SetMaxForce", &ConstraintFriction2D::SetMaxForce)
        .addFunction("SetMaxTorque", &ConstraintFriction2D::SetMaxTorque)

        .addFunction("GetAnchor", &ConstraintFriction2D::GetAnchor)
        .addFunction("GetMaxForce", &ConstraintFriction2D::GetMaxForce)
        .addFunction("GetMaxTorque", &ConstraintFriction2D::GetMaxTorque)

        .addProperty("anchor", &ConstraintFriction2D::GetAnchor, &ConstraintFriction2D::SetAnchor)
        .addProperty("maxForce", &ConstraintFriction2D::GetMaxForce, &ConstraintFriction2D::SetMaxForce)
        .addProperty("maxTorque", &ConstraintFriction2D::GetMaxTorque, &ConstraintFriction2D::SetMaxTorque)
    );
}

static void RegisterConstraintGear2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ConstraintGear2D"].setClass(UserdataMetatable<ConstraintGear2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintGear2D>)

        .addFunction("SetOwnerConstraint", &ConstraintGear2D::SetOwnerConstraint)
        .addFunction("SetOtherConstraint", &ConstraintGear2D::SetOtherConstraint)
        .addFunction("SetRatio", &ConstraintGear2D::SetRatio)

        .addFunction("GetOwnerConstraint", &ConstraintGear2D::GetOwnerConstraint)
        .addFunction("GetOtherConstraint", &ConstraintGear2D::GetOtherConstraint)
        .addFunction("GetRatio", &ConstraintGear2D::GetRatio)

        .addProperty("ownerConstraint", &ConstraintGear2D::GetOwnerConstraint, &ConstraintGear2D::SetOwnerConstraint)
        .addProperty("otherConstraint", &ConstraintGear2D::GetOtherConstraint, &ConstraintGear2D::SetOtherConstraint)
        .addProperty("ratio", &ConstraintGear2D::GetRatio, &ConstraintGear2D::SetRatio)
    );
}

static void RegisterConstraintMotor2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ConstraintMotor2D"].setClass(UserdataMetatable<ConstraintMotor2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintMotor2D>)

        .addFunction("SetLinearOffset", &ConstraintMotor2D::SetLinearOffset)
        .addFunction("SetAngularOffset", &ConstraintMotor2D::SetAngularOffset)
        .addFunction("SetMaxForce", &ConstraintMotor2D::SetMaxForce)
        .addFunction("SetMaxTorque", &ConstraintMotor2D::SetMaxTorque)
        .addFunction("SetCorrectionFactor", &ConstraintMotor2D::SetCorrectionFactor)

        .addFunction("GetLinearOffset", &ConstraintMotor2D::GetLinearOffset)
        .addFunction("GetAngularOffset", &ConstraintMotor2D::GetAngularOffset)
        .addFunction("GetMaxForce", &ConstraintMotor2D::GetMaxForce)
        .addFunction("GetMaxTorque", &ConstraintMotor2D::GetMaxTorque)
        .addFunction("GetCorrectionFactor", &ConstraintMotor2D::GetCorrectionFactor)

        .addProperty("linearOffset", &ConstraintMotor2D::GetLinearOffset, &ConstraintMotor2D::SetLinearOffset)
        .addProperty("angularOffset", &ConstraintMotor2D::GetAngularOffset, &ConstraintMotor2D::SetAngularOffset)
        .addProperty("maxForce", &ConstraintMotor2D::GetMaxForce, &ConstraintMotor2D::SetMaxForce)
        .addProperty("maxTorque", &ConstraintMotor2D::GetMaxTorque, &ConstraintMotor2D::SetMaxTorque)
        .addProperty("correctionFactor", &ConstraintMotor2D::GetCorrectionFactor, &ConstraintMotor2D::SetCorrectionFactor)
    );
}

static void RegisterConstraintMouse2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ConstraintMouse2D"].setClass(UserdataMetatable<ConstraintMouse2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintMouse2D>)

        .addFunction("SetTarget", &ConstraintMouse2D::SetTarget)
        .addFunction("SetMaxForce", &ConstraintMouse2D::SetMaxForce)
        .addFunction("SetFrequencyHz", &ConstraintMouse2D::SetFrequencyHz)
        .addFunction("SetDampingRatio", &ConstraintMouse2D::SetDampingRatio)

        .addFunction("GetTarget", &ConstraintMouse2D::GetTarget)
        .addFunction("GetMaxForce", &ConstraintMouse2D::GetMaxForce)
        .addFunction("GetFrequencyHz", &ConstraintMouse2D::GetFrequencyHz)
        .addFunction("GetDampingRatio", &ConstraintMouse2D::GetDampingRatio)

        .addProperty("target", &ConstraintMouse2D::GetTarget, &ConstraintMouse2D::SetTarget)
        .addProperty("maxForce", &ConstraintMouse2D::GetMaxForce, &ConstraintMouse2D::SetMaxForce)
        .addProperty("frequencyHz", &ConstraintMouse2D::GetFrequencyHz, &ConstraintMouse2D::SetFrequencyHz)
        .addProperty("dampingRatio", &ConstraintMouse2D::GetDampingRatio, &ConstraintMouse2D::SetDampingRatio)
    );
}

static void RegisterConstraintPrismatic2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ConstraintPrismatic2D"].setClass(UserdataMetatable<ConstraintPrismatic2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintPrismatic2D>)

        .addFunction("SetAnchor", &ConstraintPrismatic2D::SetAnchor)
        .addFunction("SetAxis", &ConstraintPrismatic2D::SetAxis)
        .addFunction("SetEnableLimit", &ConstraintPrismatic2D::SetEnableLimit)
        .addFunction("SetLowerTranslation", &ConstraintPrismatic2D::SetLowerTranslation)
        .addFunction("SetUpperTranslation", &ConstraintPrismatic2D::SetUpperTranslation)
        .addFunction("SetEnableMotor", &ConstraintPrismatic2D::SetEnableMotor)
        .addFunction("SetMaxMotorForce", &ConstraintPrismatic2D::SetMaxMotorForce)
        .addFunction("SetMotorSpeed", &ConstraintPrismatic2D::SetMotorSpeed)

        .addFunction("GetAnchor", &ConstraintPrismatic2D::GetAnchor)
        .addFunction("GetAxis", &ConstraintPrismatic2D::GetAxis)
        .addFunction("GetEnableLimit", &ConstraintPrismatic2D::GetEnableLimit)
        .addFunction("GetLowerTranslation", &ConstraintPrismatic2D::GetLowerTranslation)
        .addFunction("GetUpperTranslation", &ConstraintPrismatic2D::GetUpperTranslation)
        .addFunction("GetEnableMotor", &ConstraintPrismatic2D::GetEnableMotor)
        .addFunction("GetMaxMotorForce", &ConstraintPrismatic2D::GetMaxMotorForce)
        .addFunction("GetMotorSpeed", &ConstraintPrismatic2D::GetMotorSpeed)

        .addProperty("anchor", &ConstraintPrismatic2D::GetAnchor, &ConstraintPrismatic2D::SetAnchor)
        .addProperty("axis", &ConstraintPrismatic2D::GetAxis, &ConstraintPrismatic2D::SetAxis)
        .addProperty("enableLimit", &ConstraintPrismatic2D::GetEnableLimit, &ConstraintPrismatic2D::SetEnableLimit)
        .addProperty("lowerTranslation", &ConstraintPrismatic2D::GetLowerTranslation, &ConstraintPrismatic2D::SetLowerTranslation)
        .addProperty("upperTranslation", &ConstraintPrismatic2D::GetUpperTranslation, &ConstraintPrismatic2D::SetUpperTranslation)
        .addProperty("enableMotor", &ConstraintPrismatic2D::GetEnableMotor, &ConstraintPrismatic2D::SetEnableMotor)
        .addProperty("maxMotorForce", &ConstraintPrismatic2D::GetMaxMotorForce, &ConstraintPrismatic2D::SetMaxMotorForce)
        .addProperty("motorSpeed", &ConstraintPrismatic2D::GetMotorSpeed, &ConstraintPrismatic2D::SetMotorSpeed)
    );
}

static void RegisterConstraintPulley2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ConstraintPulley2D"].setClass(UserdataMetatable<ConstraintPulley2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintPulley2D>)

        .addFunction("SetOwnerBodyGroundAnchor", &ConstraintPulley2D::SetOwnerBodyGroundAnchor)
        .addFunction("SetOtherBodyGroundAnchor", &ConstraintPulley2D::SetOtherBodyGroundAnchor)
        .addFunction("SetOwnerBodyAnchor", &ConstraintPulley2D::SetOwnerBodyAnchor)
        .addFunction("SetOtherBodyAnchor", &ConstraintPulley2D::SetOtherBodyAnchor)
        .addFunction("SetRatio", &ConstraintPulley2D::SetRatio)

        .addFunction("GetOwnerBodyGroundAnchor", &ConstraintPulley2D::GetOwnerBodyGroundAnchor)
        .addFunction("GetOtherBodyGroundAnchor", &ConstraintPulley2D::GetOtherBodyGroundAnchor)
        .addFunction("GetOwnerBodyAnchor", &ConstraintPulley2D::GetOwnerBodyAnchor)
        .addFunction("GetOtherBodyAnchor", &ConstraintPulley2D::GetOtherBodyAnchor)
        .addFunction("GetRatio", &ConstraintPulley2D::GetRatio)

        .addProperty("ownerBodyGroundAnchor", &ConstraintPulley2D::GetOwnerBodyGroundAnchor, &ConstraintPulley2D::SetOwnerBodyGroundAnchor)
        .addProperty("otherBodyGroundAnchor", &ConstraintPulley2D::GetOtherBodyGroundAnchor, &ConstraintPulley2D::SetOtherBodyGroundAnchor)
        .addProperty("ownerBodyAnchor", &ConstraintPulley2D::GetOwnerBodyAnchor, &ConstraintPulley2D::SetOwnerBodyAnchor)
        .addProperty("otherBodyAnchor", &ConstraintPulley2D::GetOtherBodyAnchor, &ConstraintPulley2D::SetOtherBodyAnchor)
        .addProperty("ratio", &ConstraintPulley2D::GetRatio, &ConstraintPulley2D::SetRatio)
    );
}

static void RegisterConstraintRevolute2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ConstraintRevolute2D"].setClass(UserdataMetatable<ConstraintRevolute2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintRevolute2D>)

        .addFunction("SetAnchor", &ConstraintRevolute2D::SetAnchor)
        .addFunction("SetEnableLimit", &ConstraintRevolute2D::SetEnableLimit)
        .addFunction("SetLowerAngle", &ConstraintRevolute2D::SetLowerAngle)
        .addFunction("SetUpperAngle", &ConstraintRevolute2D::SetUpperAngle)
        .addFunction("SetEnableMotor", &ConstraintRevolute2D::SetEnableMotor)
        .addFunction("SetMotorSpeed", &ConstraintRevolute2D::SetMotorSpeed)
        .addFunction("SetMaxMotorTorque", &ConstraintRevolute2D::SetMaxMotorTorque)

        .addFunction("GetAnchor", &ConstraintRevolute2D::GetAnchor)
        .addFunction("GetEnableLimit", &ConstraintRevolute2D::GetEnableLimit)
        .addFunction("GetLowerAngle", &ConstraintRevolute2D::GetLowerAngle)
        .addFunction("GetUpperAngle", &ConstraintRevolute2D::GetUpperAngle)
        .addFunction("GetEnableMotor", &ConstraintRevolute2D::GetEnableMotor)
        .addFunction("GetMotorSpeed", &ConstraintRevolute2D::GetMotorSpeed)
        .addFunction("GetMaxMotorTorque", &ConstraintRevolute2D::GetMaxMotorTorque)

        .addProperty("anchor", &ConstraintRevolute2D::GetAnchor, &ConstraintRevolute2D::SetAnchor)
        .addProperty("enableLimit", &ConstraintRevolute2D::GetEnableLimit, &ConstraintRevolute2D::SetEnableLimit)
        .addProperty("lowerAngle", &ConstraintRevolute2D::GetLowerAngle, &ConstraintRevolute2D::SetLowerAngle)
        .addProperty("upperAngle", &ConstraintRevolute2D::GetUpperAngle, &ConstraintRevolute2D::SetUpperAngle)
        .addProperty("enableMotor", &ConstraintRevolute2D::GetEnableMotor, &ConstraintRevolute2D::SetEnableMotor)
        .addProperty("motorSpeed", &ConstraintRevolute2D::GetMotorSpeed, &ConstraintRevolute2D::SetMotorSpeed)
        .addProperty("maxMotorTorque", &ConstraintRevolute2D::GetMaxMotorTorque, &ConstraintRevolute2D::SetMaxMotorTorque)
    );
}

static void RegisterConstraintRope2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ConstraintRope2D"].setClass(UserdataMetatable<ConstraintRope2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintRope2D>)

        .addFunction("SetOwnerBodyAnchor", &ConstraintRope2D::SetOwnerBodyAnchor)
        .addFunction("SetOtherBodyAnchor", &ConstraintRope2D::SetOtherBodyAnchor)
        .addFunction("SetMaxLength", &ConstraintRope2D::SetMaxLength)

        .addFunction("GetOwnerBodyAnchor", &ConstraintRope2D::GetOwnerBodyAnchor)
        .addFunction("GetOtherBodyAnchor", &ConstraintRope2D::GetOtherBodyAnchor)
        .addFunction("GetMaxLength", &ConstraintRope2D::GetMaxLength)

        .addProperty("ownerBodyAnchor", &ConstraintRope2D::GetOwnerBodyAnchor, &ConstraintRope2D::SetOwnerBodyAnchor)
        .addProperty("otherBodyAnchor", &ConstraintRope2D::GetOtherBodyAnchor, &ConstraintRope2D::SetOtherBodyAnchor)
        .addProperty("maxLength", &ConstraintRope2D::GetMaxLength, &ConstraintRope2D::SetMaxLength)
    );
}

static void RegisterConstraintWeld2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ConstraintWeld2D"].setClass(UserdataMetatable<ConstraintWeld2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintWeld2D>)

        .addFunction("SetAnchor", &ConstraintWeld2D::SetAnchor)
        .addFunction("SetFrequencyHz", &ConstraintWeld2D::SetFrequencyHz)
        .addFunction("SetDampingRatio", &ConstraintWeld2D::SetDampingRatio)

        .addFunction("GetAnchor", &ConstraintWeld2D::GetAnchor)
        .addFunction("GetFrequencyHz", &ConstraintWeld2D::GetFrequencyHz)
        .addFunction("GetDampingRatio", &ConstraintWeld2D::GetDampingRatio)

        .addProperty("anchor", &ConstraintWeld2D::GetAnchor, &ConstraintWeld2D::SetAnchor)
        .addProperty("frequencyHz", &ConstraintWeld2D::GetFrequencyHz, &ConstraintWeld2D::SetFrequencyHz)
        .addProperty("dampingRatio", &ConstraintWeld2D::GetDampingRatio, &ConstraintWeld2D::SetDampingRatio)
    );
}

static void RegisterConstraintWheel2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["ConstraintWheel2D"].setClass(UserdataMetatable<ConstraintWheel2D, Constraint2D>()
        .addStaticFunction("new", &CreateObject<ConstraintWheel2D>)

        .addFunction("SetAnchor", &ConstraintWheel2D::SetAnchor)
        .addFunction("SetAxis", &ConstraintWheel2D::SetAxis)
        .addFunction("SetEnableMotor", &ConstraintWheel2D::SetEnableMotor)
        .addFunction("SetMaxMotorTorque", &ConstraintWheel2D::SetMaxMotorTorque)
        .addFunction("SetMotorSpeed", &ConstraintWheel2D::SetMotorSpeed)
        .addFunction("SetFrequencyHz", &ConstraintWheel2D::SetFrequencyHz)
        .addFunction("SetDampingRatio", &ConstraintWheel2D::SetDampingRatio)

        .addFunction("GetAnchor", &ConstraintWheel2D::GetAnchor)
        .addFunction("GetAxis", &ConstraintWheel2D::GetAxis)
        .addFunction("GetEnableMotor", &ConstraintWheel2D::GetEnableMotor)
        .addFunction("GetMaxMotorTorque", &ConstraintWheel2D::GetMaxMotorTorque)
        .addFunction("GetMotorSpeed", &ConstraintWheel2D::GetMotorSpeed)
        .addFunction("GetFrequencyHz", &ConstraintWheel2D::GetFrequencyHz)
        .addFunction("GetDampingRatio", &ConstraintWheel2D::GetDampingRatio)

        .addProperty("anchor", &ConstraintWheel2D::GetAnchor, &ConstraintWheel2D::SetAnchor)
        .addProperty("axis", &ConstraintWheel2D::GetAxis, &ConstraintWheel2D::SetAxis)
        .addProperty("enableMotor", &ConstraintWheel2D::GetEnableMotor, &ConstraintWheel2D::SetEnableMotor)
        .addProperty("maxMotorTorque", &ConstraintWheel2D::GetMaxMotorTorque, &ConstraintWheel2D::SetMaxMotorTorque)
        .addProperty("motorSpeed", &ConstraintWheel2D::GetMotorSpeed, &ConstraintWheel2D::SetMotorSpeed)
        .addProperty("frequencyHz", &ConstraintWheel2D::GetFrequencyHz, &ConstraintWheel2D::SetFrequencyHz)
        .addProperty("dampingRatio", &ConstraintWheel2D::GetDampingRatio, &ConstraintWheel2D::SetDampingRatio)
    );
}

static void RegisterDrawable2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["PIXEL_SIZE"] = PIXEL_SIZE;

    lua["Drawable2D"].setClass(UserdataMetatable<Drawable2D, Drawable>()

        .addFunction("SetLayer", &Drawable2D::SetLayer)
        .addFunction("SetOrderInLayer", &Drawable2D::SetOrderInLayer)

        .addFunction("GetLayer", &Drawable2D::GetLayer)
        .addFunction("GetOrderInLayer", &Drawable2D::GetOrderInLayer)

        .addProperty("layer", &Drawable2D::GetLayer, &Drawable2D::SetLayer)
        .addProperty("orderInLayer", &Drawable2D::GetOrderInLayer, &Drawable2D::SetOrderInLayer)
    );
}

static void RegisterParticleEffect2D(kaguya::State& lua)
{
    using namespace kaguya;

    // enum EmitterType2D;
    lua["EMITTER_TYPE_GRAVITY"] = EMITTER_TYPE_GRAVITY;
    lua["EMITTER_TYPE_RADIAL"] = EMITTER_TYPE_RADIAL;

    lua["ParticleEffect2D"].setClass(UserdataMetatable<ParticleEffect2D, Resource>()
        .addStaticFunction("new", &CreateObject<ParticleEffect2D>)
         );
}

static void RegisterParticleEmitter2D(kaguya::State& lua)
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

static PODVector<PhysicsRaycastResult2D> PhysicsWorld2DRaycast(PhysicsWorld2D* self, const Vector2& startPoint, const Vector2& endPoint, unsigned int collisionMask = M_MAX_UNSIGNED)
{
    PODVector<PhysicsRaycastResult2D> results;
    self->Raycast(results, startPoint, endPoint, collisionMask);
    return results;
}

KAGUYA_FUNCTION_OVERLOADS(PhysicsWorld2DRaycastOverloads, PhysicsWorld2DRaycast, 3, 4);

static PhysicsRaycastResult2D PhysicsWorld2DRaycastSingle(PhysicsWorld2D* self, const Vector2& startPoint, const Vector2& endPoint, unsigned int collisionMask = M_MAX_UNSIGNED)
{
    PhysicsRaycastResult2D result;
    self->RaycastSingle(result, startPoint, endPoint, collisionMask);
    return result;
}

KAGUYA_FUNCTION_OVERLOADS(PhysicsWorld2DRaycastSingleOverloads, PhysicsWorld2DRaycastSingle, 3, 4);

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(PhysicsWorld2DGetRigidBody0, PhysicsWorld2D, GetRigidBody, 1, 2, RigidBody2D*(PhysicsWorld2D::*)(const Vector2&, unsigned));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(PhysicsWorld2DGetRigidBody1, PhysicsWorld2D, GetRigidBody, 2, 3, RigidBody2D*(PhysicsWorld2D::*)(int, int, unsigned));

static PODVector<RigidBody2D*> PhysicsWorld2DGetRigidBodies(PhysicsWorld2D* self, const Rect& aabb, unsigned int collisionMask = M_MAX_UNSIGNED)
{
    PODVector<RigidBody2D*> result;
    self->GetRigidBodies(result, aabb, collisionMask);
    return result;
}

KAGUYA_FUNCTION_OVERLOADS(PhysicsWorld2DGetRigidBodiesOverloads, PhysicsWorld2DGetRigidBodies, 2, 3);

static void RegisterPhysicsWorld2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["PhysicsRaycastResult2D"].setClass(UserdataMetatable<PhysicsRaycastResult2D>()
        .setConstructors<PhysicsRaycastResult2D()>()

        .addProperty("position", &PhysicsRaycastResult2D::position_)
        .addProperty("normal", &PhysicsRaycastResult2D::normal_)
        .addProperty("distance", &PhysicsRaycastResult2D::distance_)
        .addProperty("body", &PhysicsRaycastResult2D::body_)
    );

    lua["PhysicsWorld2D"].setClass(UserdataMetatable<PhysicsWorld2D, Component>()
        .addStaticFunction("new", &CreateObject<PhysicsWorld2D>)

        .addFunction("DrawDebugGeometry", static_cast<void(PhysicsWorld2D::*)()>(&PhysicsWorld2D::DrawDebugGeometry))

        .addFunction("SetUpdateEnabled", &PhysicsWorld2D::SetUpdateEnabled)
        .addFunction("SetDrawShape", &PhysicsWorld2D::SetDrawShape)
        .addFunction("SetDrawJoint", &PhysicsWorld2D::SetDrawJoint)
        .addFunction("SetDrawAabb", &PhysicsWorld2D::SetDrawAabb)
        .addFunction("SetDrawPair", &PhysicsWorld2D::SetDrawPair)
        .addFunction("SetDrawCenterOfMass", &PhysicsWorld2D::SetDrawCenterOfMass)
        .addFunction("SetAllowSleeping", &PhysicsWorld2D::SetAllowSleeping)
        .addFunction("SetWarmStarting", &PhysicsWorld2D::SetWarmStarting)
        .addFunction("SetContinuousPhysics", &PhysicsWorld2D::SetContinuousPhysics)
        .addFunction("SetSubStepping", &PhysicsWorld2D::SetSubStepping)
        .addFunction("SetGravity", &PhysicsWorld2D::SetGravity)
        .addFunction("SetAutoClearForces", &PhysicsWorld2D::SetAutoClearForces)
        .addFunction("SetVelocityIterations", &PhysicsWorld2D::SetVelocityIterations)
        .addFunction("SetPositionIterations", &PhysicsWorld2D::SetPositionIterations)

        .addStaticFunction("Raycast", PhysicsWorld2DRaycastOverloads())

        .addStaticFunction("RaycastSingle", PhysicsWorld2DRaycastSingleOverloads())
        
        .addOverloadedFunctions("GetRigidBody", PhysicsWorld2DGetRigidBody0(), PhysicsWorld2DGetRigidBody1())

        .addStaticFunction("GetRigidBodies", PhysicsWorld2DGetRigidBodiesOverloads())

        .addFunction("IsUpdateEnabled", &PhysicsWorld2D::IsUpdateEnabled)
        .addFunction("GetDrawShape", &PhysicsWorld2D::GetDrawShape)
        .addFunction("GetDrawJoint", &PhysicsWorld2D::GetDrawJoint)
        .addFunction("GetDrawAabb", &PhysicsWorld2D::GetDrawAabb)
        .addFunction("GetDrawPair", &PhysicsWorld2D::GetDrawPair)
        .addFunction("GetDrawCenterOfMass", &PhysicsWorld2D::GetDrawCenterOfMass)
        .addFunction("GetAllowSleeping", &PhysicsWorld2D::GetAllowSleeping)
        .addFunction("GetWarmStarting", &PhysicsWorld2D::GetWarmStarting)
        .addFunction("GetContinuousPhysics", &PhysicsWorld2D::GetContinuousPhysics)
        .addFunction("GetSubStepping", &PhysicsWorld2D::GetSubStepping)
        .addFunction("GetAutoClearForces", &PhysicsWorld2D::GetAutoClearForces)
        .addFunction("GetGravity", &PhysicsWorld2D::GetGravity)
        .addFunction("GetVelocityIterations", &PhysicsWorld2D::GetVelocityIterations)
        .addFunction("GetPositionIterations", &PhysicsWorld2D::GetPositionIterations)

        .addProperty("updateEnabled", &PhysicsWorld2D::IsUpdateEnabled, &PhysicsWorld2D::SetUpdateEnabled)
        .addProperty("drawShape", &PhysicsWorld2D::GetDrawShape, &PhysicsWorld2D::SetDrawShape)
        .addProperty("drawJoint", &PhysicsWorld2D::GetDrawJoint, &PhysicsWorld2D::SetDrawJoint)
        .addProperty("drawAabb", &PhysicsWorld2D::GetDrawAabb, &PhysicsWorld2D::SetDrawAabb)
        .addProperty("drawPair", &PhysicsWorld2D::GetDrawPair, &PhysicsWorld2D::SetDrawPair)
        .addProperty("drawCenterOfMass", &PhysicsWorld2D::GetDrawCenterOfMass, &PhysicsWorld2D::SetDrawCenterOfMass)
        .addProperty("allowSleeping", &PhysicsWorld2D::GetAllowSleeping, &PhysicsWorld2D::SetAllowSleeping)
        .addProperty("warmStarting", &PhysicsWorld2D::GetWarmStarting, &PhysicsWorld2D::SetWarmStarting)
        .addProperty("continuousPhysics", &PhysicsWorld2D::GetContinuousPhysics, &PhysicsWorld2D::SetContinuousPhysics)
        .addProperty("subStepping", &PhysicsWorld2D::GetSubStepping, &PhysicsWorld2D::SetSubStepping)
        .addProperty("autoClearForces", &PhysicsWorld2D::GetAutoClearForces, &PhysicsWorld2D::SetAutoClearForces)
        .addProperty("gravity", &PhysicsWorld2D::GetGravity, &PhysicsWorld2D::SetGravity)
        .addProperty("velocityIterations", &PhysicsWorld2D::GetVelocityIterations, &PhysicsWorld2D::SetVelocityIterations)
        .addProperty("positionIterations", &PhysicsWorld2D::GetPositionIterations, &PhysicsWorld2D::SetPositionIterations)
    );
}

static void RegisterRigidBody2D(kaguya::State& lua)
{
    using namespace kaguya;

    // enum BodyType2D;
    lua["BT_STATIC"] = BT_STATIC;
    lua["BT_KINEMATIC"] = BT_KINEMATIC;
    lua["BT_DYNAMIC"] = BT_DYNAMIC;

    lua["RigidBody2D"].setClass(UserdataMetatable<RigidBody2D, Component>()
        .addStaticFunction("new", &CreateObject<RigidBody2D>)

        .addFunction("SetBodyType", &RigidBody2D::SetBodyType)
        .addFunction("SetMass", &RigidBody2D::SetMass)
        .addFunction("SetInertia", &RigidBody2D::SetInertia)
        .addFunction("SetMassCenter", &RigidBody2D::SetMassCenter)
        .addFunction("SetUseFixtureMass", &RigidBody2D::SetUseFixtureMass)
        .addFunction("SetLinearDamping", &RigidBody2D::SetLinearDamping)
        .addFunction("SetAngularDamping", &RigidBody2D::SetAngularDamping)
        .addFunction("SetAllowSleep", &RigidBody2D::SetAllowSleep)
        .addFunction("SetFixedRotation", &RigidBody2D::SetFixedRotation)
        .addFunction("SetBullet", &RigidBody2D::SetBullet)
        .addFunction("SetGravityScale", &RigidBody2D::SetGravityScale)
        .addFunction("SetAwake", &RigidBody2D::SetAwake)
        .addFunction("SetLinearVelocity", &RigidBody2D::SetLinearVelocity)
        .addFunction("SetAngularVelocity", &RigidBody2D::SetAngularVelocity)

        .addFunction("ApplyForce", &RigidBody2D::ApplyForce)
        .addFunction("ApplyForceToCenter", &RigidBody2D::ApplyForceToCenter)
        .addFunction("ApplyTorque", &RigidBody2D::ApplyTorque)
        .addFunction("ApplyLinearImpulse", &RigidBody2D::ApplyLinearImpulse)
        .addFunction("ApplyAngularImpulse", &RigidBody2D::ApplyAngularImpulse)

        .addFunction("GetBodyType", &RigidBody2D::GetBodyType)
        .addFunction("GetMass", &RigidBody2D::GetMass)
        .addFunction("GetInertia", &RigidBody2D::GetInertia)
        .addFunction("GetMassCenter", &RigidBody2D::GetMassCenter)
        .addFunction("GetUseFixtureMass", &RigidBody2D::GetUseFixtureMass)
        .addFunction("GetLinearDamping", &RigidBody2D::GetLinearDamping)
        .addFunction("GetAngularDamping", &RigidBody2D::GetAngularDamping)

        .addFunction("IsAllowSleep", &RigidBody2D::IsAllowSleep)
        .addFunction("IsFixedRotation", &RigidBody2D::IsFixedRotation)
        .addFunction("IsBullet", &RigidBody2D::IsBullet)
        .addFunction("GetGravityScale", &RigidBody2D::GetGravityScale)
        .addFunction("IsAwake", &RigidBody2D::IsAwake)
        .addFunction("GetLinearVelocity", &RigidBody2D::GetLinearVelocity)
        .addFunction("GetAngularVelocity", &RigidBody2D::GetAngularVelocity)

        .addProperty("bodyType", &RigidBody2D::GetBodyType, &RigidBody2D::SetBodyType)
        .addProperty("mass", &RigidBody2D::GetMass, &RigidBody2D::SetMass)
        .addProperty("inertia", &RigidBody2D::GetInertia, &RigidBody2D::SetInertia)
        .addProperty("massCenter", &RigidBody2D::GetMassCenter, &RigidBody2D::SetMassCenter)
        .addProperty("useFixtureMass", &RigidBody2D::GetUseFixtureMass, &RigidBody2D::SetUseFixtureMass)
        .addProperty("linearDamping", &RigidBody2D::GetLinearDamping, &RigidBody2D::SetLinearDamping)
        .addProperty("angularDamping", &RigidBody2D::GetAngularDamping, &RigidBody2D::SetAngularDamping)
        .addProperty("allowSleep", &RigidBody2D::IsAllowSleep, &RigidBody2D::SetAllowSleep)
        .addProperty("fixedRotation", &RigidBody2D::IsFixedRotation, &RigidBody2D::SetFixedRotation)
        .addProperty("bullet", &RigidBody2D::IsBullet, &RigidBody2D::SetBullet)
        .addProperty("gravityScale", &RigidBody2D::GetGravityScale, &RigidBody2D::SetGravityScale)
        .addProperty("awake", &RigidBody2D::IsAwake, &RigidBody2D::SetAwake)
        .addProperty("linearVelocity", &RigidBody2D::GetLinearVelocity, &RigidBody2D::SetLinearVelocity)
        .addProperty("angularVelocity", &RigidBody2D::GetAngularVelocity, &RigidBody2D::SetAngularVelocity)
    );
}

static void RegisterSprite2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Sprite2D"].setClass(UserdataMetatable<Sprite2D, Resource>()
        .addStaticFunction("new", &CreateObject<Sprite2D>)

        .addFunction("SetTexture", &Sprite2D::SetTexture)
        .addFunction("SetRectangle", &Sprite2D::SetRectangle)
        .addFunction("SetHotSpot", &Sprite2D::SetHotSpot)
        .addFunction("SetOffset", &Sprite2D::SetOffset)
        .addFunction("SetTextureEdgeOffset", &Sprite2D::SetTextureEdgeOffset)
        .addFunction("SetSpriteSheet", &Sprite2D::SetSpriteSheet)

        .addFunction("GetTexture", &Sprite2D::GetTexture)
        .addFunction("GetRectangle", &Sprite2D::GetRectangle)
        .addFunction("GetHotSpot", &Sprite2D::GetHotSpot)
        .addFunction("GetOffset", &Sprite2D::GetOffset)
        .addFunction("GetTextureEdgeOffset", &Sprite2D::GetTextureEdgeOffset)
        .addFunction("GetSpriteSheet", &Sprite2D::GetSpriteSheet)

        .addProperty("texture", &Sprite2D::GetTexture, &Sprite2D::SetTexture)
        .addProperty("rectangle", &Sprite2D::GetRectangle, &Sprite2D::SetRectangle)
        .addProperty("hotSpot", &Sprite2D::GetHotSpot, &Sprite2D::SetHotSpot)
        .addProperty("offset", &Sprite2D::GetOffset, &Sprite2D::SetOffset)
        .addProperty("textureEdgeOffset", &Sprite2D::GetTextureEdgeOffset, &Sprite2D::SetTextureEdgeOffset)
        .addProperty("spriteSheet", &Sprite2D::GetSpriteSheet, &Sprite2D::SetSpriteSheet)
    );
}

KAGUYA_MEMBER_FUNCTION_OVERLOADS(SpriteSheet2DDefineSprite, SpriteSheet2D, DefineSprite, 2, 4);

static void RegisterSpriteSheet2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["SpriteSheet2D"].setClass(UserdataMetatable<SpriteSheet2D, Resource>()
        .addStaticFunction("new", &CreateObject<SpriteSheet2D>)

        .addFunction("SetTexture", &SpriteSheet2D::SetTexture)

        .addFunction("DefineSprite", SpriteSheet2DDefineSprite())

        .addFunction("GetTexture", &SpriteSheet2D::GetTexture)
        .addFunction("GetSprite", &SpriteSheet2D::GetSprite)

        .addProperty("texture", &SpriteSheet2D::GetTexture, &SpriteSheet2D::SetTexture)
    );
}

static void RegisterStaticSprite2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["StaticSprite2D"].setClass(UserdataMetatable<StaticSprite2D, Drawable2D>()
        .addStaticFunction("new", &CreateObject<StaticSprite2D>)

        .addFunction("SetSprite", &StaticSprite2D::SetSprite)
        .addFunction("SetBlendMode", &StaticSprite2D::SetBlendMode)
        .addFunction("SetFlip", &StaticSprite2D::SetFlip)
        .addFunction("SetFlipX", &StaticSprite2D::SetFlipX)
        .addFunction("SetFlipY", &StaticSprite2D::SetFlipY)
        .addFunction("SetColor", &StaticSprite2D::SetColor)
        .addFunction("SetAlpha", &StaticSprite2D::SetAlpha)
        .addFunction("SetUseHotSpot", &StaticSprite2D::SetUseHotSpot)
        .addFunction("SetHotSpot", &StaticSprite2D::SetHotSpot)
        .addFunction("SetCustomMaterial", &StaticSprite2D::SetCustomMaterial)

        .addFunction("GetSprite", &StaticSprite2D::GetSprite)
        .addFunction("GetBlendMode", &StaticSprite2D::GetBlendMode)
        .addFunction("GetFlipX", &StaticSprite2D::GetFlipX)
        .addFunction("GetFlipY", &StaticSprite2D::GetFlipY)
        .addFunction("GetColor", &StaticSprite2D::GetColor)
        .addFunction("GetAlpha", &StaticSprite2D::GetAlpha)
        .addFunction("GetUseHotSpot", &StaticSprite2D::GetUseHotSpot)
        .addFunction("GetHotSpot", &StaticSprite2D::GetHotSpot)
        .addFunction("GetCustomMaterial", &StaticSprite2D::GetCustomMaterial)

        .addProperty("sprite", &StaticSprite2D::GetSprite, &StaticSprite2D::SetSprite)
        .addProperty("blendMode", &StaticSprite2D::GetBlendMode, &StaticSprite2D::SetBlendMode)
        .addProperty("flipX", &StaticSprite2D::GetFlipX, &StaticSprite2D::SetFlipX)
        .addProperty("flipY", &StaticSprite2D::GetFlipY, &StaticSprite2D::SetFlipY)
        .addProperty("color", &StaticSprite2D::GetColor, &StaticSprite2D::SetColor)
        .addProperty("alpha", &StaticSprite2D::GetAlpha, &StaticSprite2D::SetAlpha)
        .addProperty("useHotSpot", &StaticSprite2D::GetUseHotSpot, &StaticSprite2D::SetUseHotSpot)
        .addProperty("hotSpot", &StaticSprite2D::GetHotSpot, &StaticSprite2D::SetHotSpot)
        .addProperty("customMaterial", &StaticSprite2D::GetCustomMaterial, &StaticSprite2D::SetCustomMaterial)
    );
}

static void RegisterTileMap2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["TileMap2D"].setClass(UserdataMetatable<TileMap2D, Component>()
        .addStaticFunction("new", &CreateObject<TileMap2D>)

        .addFunction("DrawDebugGeometry", static_cast<void(TileMap2D::*)()>(&TileMap2D::DrawDebugGeometry))
        .addFunction("SetTmxFile", &TileMap2D::SetTmxFile)        

        .addFunction("GetTmxFile", &TileMap2D::GetTmxFile)
        .addFunction("GetInfo", &TileMap2D::GetInfo)
        .addFunction("GetNumLayers", &TileMap2D::GetNumLayers)
        .addFunction("GetLayer", &TileMap2D::GetLayer)
        .addFunction("TileIndexToPosition", &TileMap2D::TileIndexToPosition)
        .addFunction("PositionToTileIndex", &TileMap2D::PositionToTileIndex)
        
        .addProperty("tmxFile", &TileMap2D::GetTmxFile, &TileMap2D::SetTmxFile)
        .addProperty("info", &TileMap2D::GetInfo)
        .addProperty("numLayers", &TileMap2D::GetNumLayers)
    );
}

static void RegisterTileMapDefs2D(kaguya::State& lua)
{
    using namespace kaguya;

    // enum Orientation2D;
    lua["O_ORTHOGONAL"] = O_ORTHOGONAL;
    lua["O_ISOMETRIC"] = O_ISOMETRIC;
    lua["O_STAGGERED"] = O_STAGGERED;
    lua["O_HEXAGONAL"] = O_HEXAGONAL;

    lua["TileMapInfo2D"].setClass(UserdataMetatable<TileMapInfo2D>()

        .addFunction("GetMapWidth", &TileMapInfo2D::GetMapWidth)
        .addFunction("GetMapHeight", &TileMapInfo2D::GetMapHeight)
        .addFunction("ConvertPosition", &TileMapInfo2D::ConvertPosition)
        .addFunction("TileIndexToPosition", &TileMapInfo2D::TileIndexToPosition)
        .addFunction("PositionToTileIndex", &TileMapInfo2D::PositionToTileIndex)

        .addProperty("mapWidth", &TileMapInfo2D::GetMapWidth)
        .addProperty("mapHeight", &TileMapInfo2D::GetMapHeight)

        .addProperty("orientation", &TileMapInfo2D::orientation_)
        .addProperty("width", &TileMapInfo2D::width_)
        .addProperty("height", &TileMapInfo2D::height_)
        .addProperty("tileWidth", &TileMapInfo2D::tileWidth_)
        .addProperty("tileHeight", &TileMapInfo2D::tileHeight_)
    );

    // enum TileMapLayerType2D;
    lua["LT_TILE_LAYER"] = LT_TILE_LAYER;
    lua["LT_OBJECT_GROUP"] = LT_OBJECT_GROUP;
    lua["LT_IMAGE_LAYER"] = LT_IMAGE_LAYER;
    lua["LT_INVALID"] = LT_INVALID;

    // enum TileMapObjectType2D;
    lua["OT_RECTANGLE"] = OT_RECTANGLE;
    lua["OT_ELLIPSE"] = OT_ELLIPSE;
    lua["OT_POLYGON"] = OT_POLYGON;
    lua["OT_POLYLINE"] = OT_POLYLINE;
    lua["OT_TILE"] = OT_TILE;
    lua["OT_INVALID"] = OT_INVALID;

    lua["PropertySet2D"].setClass(UserdataMetatable<PropertySet2D, RefCounted>()
        .setConstructors<PropertySet2D()>()
        .addFunction("HasProperty", &PropertySet2D::HasProperty)
        .addFunction("GetProperty", &PropertySet2D::GetProperty)
    );

    lua["Tile2D"].setClass(UserdataMetatable<Tile2D, RefCounted>()
        .setConstructors<Tile2D()>()

        .addFunction("GetGid", &Tile2D::GetGid)
        .addFunction("GetSprite", &Tile2D::GetSprite)
        .addFunction("HasProperty", &Tile2D::HasProperty)
        .addFunction("GetProperty", &Tile2D::GetProperty)

        .addProperty("gid", &Tile2D::GetGid)
        .addProperty("sprite", &Tile2D::GetSprite)
    );

    lua["TileMapObject2D"].setClass(UserdataMetatable<TileMapObject2D, RefCounted>()
        .setConstructors<TileMapObject2D()>()

        .addFunction("GetObjectType", &TileMapObject2D::GetObjectType)
        .addFunction("GetName", &TileMapObject2D::GetName)
        .addFunction("GetType", &TileMapObject2D::GetType)
        .addFunction("GetPosition", &TileMapObject2D::GetPosition)
        .addFunction("GetSize", &TileMapObject2D::GetSize)
        .addFunction("GetNumPoints", &TileMapObject2D::GetNumPoints)
        .addFunction("GetPoint", &TileMapObject2D::GetPoint)
        .addFunction("GetTileGid", &TileMapObject2D::GetTileGid)
        .addFunction("GetTileSprite", &TileMapObject2D::GetTileSprite)
        .addFunction("HasProperty", &TileMapObject2D::HasProperty)
        .addFunction("GetProperty", &TileMapObject2D::GetProperty)

        .addProperty("objectType", &TileMapObject2D::GetObjectType)
        .addProperty("name", &TileMapObject2D::GetName)
        .addProperty("type", &TileMapObject2D::GetType)
        .addProperty("position", &TileMapObject2D::GetPosition)
        .addProperty("size", &TileMapObject2D::GetSize)
        .addProperty("numPoints", &TileMapObject2D::GetNumPoints)
        .addProperty("tileGid", &TileMapObject2D::GetTileGid)
        .addProperty("tileSprite", &TileMapObject2D::GetTileSprite)
    );
}

static void RegisterTileMapLayer2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["TileMapLayer2D"].setClass(UserdataMetatable<TileMapLayer2D, Component>()
        .addStaticFunction("new", &CreateObject<TileMapLayer2D>)

        .addFunction("SetDrawOrder", &TileMapLayer2D::SetDrawOrder)
        .addFunction("SetVisible", &TileMapLayer2D::SetVisible)

        .addFunction("GetTileMap", &TileMapLayer2D::GetTileMap)
        .addFunction("GetDrawOrder", &TileMapLayer2D::GetDrawOrder)
        .addFunction("IsVisible", &TileMapLayer2D::IsVisible)
        .addFunction("HasProperty", &TileMapLayer2D::HasProperty)
        .addFunction("GetProperty", &TileMapLayer2D::GetProperty)
        .addFunction("GetLayerType", &TileMapLayer2D::GetLayerType)
        .addFunction("GetWidth", &TileMapLayer2D::GetWidth)
        .addFunction("GetHeight", &TileMapLayer2D::GetHeight)
        .addFunction("GetTileNode", &TileMapLayer2D::GetTileNode)
        .addFunction("GetTile", &TileMapLayer2D::GetTile)
        .addFunction("GetNumObjects", &TileMapLayer2D::GetNumObjects)
        .addFunction("GetObject", &TileMapLayer2D::GetObject)
        .addFunction("GetObjectNode", &TileMapLayer2D::GetObjectNode)
        .addFunction("GetImageNode", &TileMapLayer2D::GetImageNode)

        .addProperty("tileMap", &TileMapLayer2D::GetTileMap)
        .addProperty("drawOrder", &TileMapLayer2D::GetDrawOrder, &TileMapLayer2D::SetDrawOrder)
        .addProperty("visible", &TileMapLayer2D::IsVisible, &TileMapLayer2D::SetVisible)
        .addProperty("layerType", &TileMapLayer2D::GetLayerType)
        .addProperty("width", &TileMapLayer2D::GetWidth)
        .addProperty("height", &TileMapLayer2D::GetHeight)
        .addProperty("numObjects", &TileMapLayer2D::GetNumObjects)
        .addProperty("imageNode", &TileMapLayer2D::GetImageNode)
    );
}

static void RegisterTmxFile2D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["TmxFile2D"].setClass(UserdataMetatable<TmxFile2D, Resource>()
        .addStaticFunction("new", &CreateObject<TmxFile2D>)
    );
}

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
