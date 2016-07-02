#include "../Graphics/Material.h"
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
#include "../Urho2D/PhysicsEvents2D.h"
#include "../Urho2D/PhysicsWorld2D.h"
#include "../Urho2D/Renderer2D.h"
#include "../Urho2D/RigidBody2D.h"
#include "../Urho2D/Sprite2D.h"
#include "../Urho2D/SpriteSheet2D.h"
#include "../Urho2D/StaticSprite2D.h"
#include "../Urho2D/TileMap2D.h"
#include "../Urho2D/TileMapDefs2D.h"
#include "../Urho2D/TileMapLayer2D.h"
#include "../Urho2D/TmxFile2D.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void RegisterAnimatedSprite2D(kaguya::State& lua)
{
	using namespace kaguya;

	lua["KAnimatedSprite2D"].setClass(UserdataMetatable<AnimatedSprite2D, StaticSprite2D>(false)
		.addStaticFunction("new", &KCreateObject<AnimatedSprite2D>)
		.addStaticFunction("__gc", &KReleaseObject<AnimatedSprite2D>)

		.addFunction("SetAnimationSet", &AnimatedSprite2D::SetAnimationSet)
		.addFunction("SetEntity", &AnimatedSprite2D::SetEntity)
		.addFunction("SetAnimation", &AnimatedSprite2D::SetAnimation)
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

	lua["KAnimationSet2D"].setClass(UserdataMetatable<AnimationSet2D, Resource>(false)
		.addStaticFunction("new", &KCreateObject<AnimationSet2D>)
		.addStaticFunction("__gc", &KReleaseObject<AnimationSet2D>)

		.addFunction("GetNumAnimations", &AnimationSet2D::GetNumAnimations)
		.addFunction("GetAnimation", &AnimationSet2D::GetAnimation)
		.addFunction("HasAnimation", &AnimationSet2D::HasAnimation)
		.addFunction("GetSprite", &AnimationSet2D::GetSprite)
		.addFunction("GetSpriterData", &AnimationSet2D::GetSpriterData)

		.addOverloadedFunctions("GetSpriterFileSprite",
			static_cast<Sprite2D*(AnimationSet2D::*)(int, int) const>(&AnimationSet2D::GetSpriterFileSprite))

		.addProperty("numAnimations", &AnimationSet2D::GetNumAnimations)
		.addProperty("sprite", &AnimationSet2D::GetSprite)
		.addProperty("spriterData", &AnimationSet2D::GetSpriterData)
	);
}

static void RegisterCollisionBox2D(kaguya::State& lua)
{
	using namespace kaguya;

	lua["KCollisionBox2D"].setClass(UserdataMetatable<CollisionBox2D, CollisionShape2D>(false)
		.addStaticFunction("new", &KCreateObject<CollisionBox2D>)
		.addStaticFunction("__gc", &KReleaseObject<CollisionBox2D>)


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

		.addProperty("size", &CollisionBox2D::GetSize)
		.addProperty("center", &CollisionBox2D::GetCenter)
		.addProperty("angle", &CollisionBox2D::GetAngle, &CollisionBox2D::SetAngle)
	);
}

static void RegisterCollisionChain2D(kaguya::State& lua)
{
	using namespace kaguya;

	lua["KCollisionChain2D"].setClass(UserdataMetatable<CollisionChain2D, CollisionShape2D>(false)
		.addStaticFunction("new", &KCreateObject<CollisionChain2D>)
		.addStaticFunction("__gc", &KReleaseObject<CollisionChain2D>)

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
		.addProperty("vertices", &CollisionChain2D::GetVertices, &CollisionChain2D::SetVertices)
	);
}

static void RegisterCollisionCircle2D(kaguya::State& lua)
{
	using namespace kaguya;

	lua["KCollisionCircle2D"].setClass(UserdataMetatable<CollisionCircle2D, CollisionShape2D>(false)
		.addStaticFunction("new", &KCreateObject<CollisionCircle2D>)
		.addStaticFunction("__gc", &KReleaseObject<CollisionCircle2D>)

		.addFunction("SetRadius", &CollisionCircle2D::SetRadius)

		.addOverloadedFunctions("SetCenter",
			static_cast<void(CollisionCircle2D::*)(const Vector2&)>(&CollisionCircle2D::SetCenter),
			static_cast<void(CollisionCircle2D::*)(float, float)>(&CollisionCircle2D::SetCenter))

		.addFunction("GetRadius", &CollisionCircle2D::GetRadius)
		.addFunction("GetCenter", &CollisionCircle2D::GetCenter)

		.addProperty("radius", &CollisionCircle2D::GetRadius, &CollisionCircle2D::SetRadius)
		.addProperty("center", &CollisionCircle2D::GetCenter)
	);
}

static void RegisterCollisionEdge2D(kaguya::State& lua)
{
	using namespace kaguya;

	lua["KCollisionEdge2D"].setClass(UserdataMetatable<CollisionEdge2D, CollisionShape2D>(false)
		.addStaticFunction("new", &KCreateObject<CollisionEdge2D>)
		.addStaticFunction("__gc", &KReleaseObject<CollisionEdge2D>)

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

	lua["KCollisionPolygon2D"].setClass(UserdataMetatable<CollisionPolygon2D, CollisionShape2D>(false)
		.addStaticFunction("new", &KCreateObject<CollisionPolygon2D>)
		.addStaticFunction("__gc", &KReleaseObject<CollisionPolygon2D>)

		.addFunction("SetVertexCount", &CollisionPolygon2D::SetVertexCount)
		.addFunction("SetVertex", &CollisionPolygon2D::SetVertex)
		.addFunction("SetVertices", &CollisionPolygon2D::SetVertices)
		.addFunction("GetVertexCount", &CollisionPolygon2D::GetVertexCount)
		.addFunction("GetVertex", &CollisionPolygon2D::GetVertex)
		.addFunction("GetVertices", &CollisionPolygon2D::GetVertices)

		.addProperty("vertexCount", &CollisionPolygon2D::GetVertexCount, &CollisionPolygon2D::SetVertexCount)
		.addProperty("vertices", &CollisionPolygon2D::GetVertices, &CollisionPolygon2D::SetVertices)
	);
}

static void RegisterCollisionShape2D(kaguya::State& lua)
{
	using namespace kaguya;

	lua["KCollisionShape2D"].setClass(UserdataMetatable<CollisionShape2D, Component>(false)

		.addFunction("SetTrigger", &CollisionShape2D::SetTrigger)
		.addFunction("SetCategoryBits", &CollisionShape2D::SetCategoryBits)
		.addFunction("SetMaskBits", &CollisionShape2D::SetMaskBits)
		.addFunction("SetGroupIndex", &CollisionShape2D::SetGroupIndex)
		.addFunction("SetDensity", &CollisionShape2D::SetDensity)
		.addFunction("SetFriction", &CollisionShape2D::SetFriction)
		.addFunction("SetRestitution", &CollisionShape2D::SetRestitution)
		.addFunction("CreateFixture", &CollisionShape2D::CreateFixture)
		.addFunction("ReleaseFixture", &CollisionShape2D::ReleaseFixture)
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
		.addFunction("GetFixture", &CollisionShape2D::GetFixture)

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
		.addProperty("fixture", &CollisionShape2D::GetFixture)
	);
}

static void RegisterConstraint2D(kaguya::State& lua)
{
	using namespace kaguya;

	lua["KConstraint2D"].setClass(UserdataMetatable<Constraint2D, Component>(false)
		.addStaticFunction("new", &KCreateObject<Constraint2D>)
		.addStaticFunction("__gc", &KReleaseObject<Constraint2D>)

		.addFunction("CreateJoint", &Constraint2D::CreateJoint)
		.addFunction("ReleaseJoint", &Constraint2D::ReleaseJoint)
		.addFunction("SetOtherBody", &Constraint2D::SetOtherBody)
		.addFunction("SetCollideConnected", &Constraint2D::SetCollideConnected)
		.addFunction("SetAttachedConstraint", &Constraint2D::SetAttachedConstraint)
		.addFunction("GetOwnerBody", &Constraint2D::GetOwnerBody)
		.addFunction("GetOtherBody", &Constraint2D::GetOtherBody)
		.addFunction("GetCollideConnected", &Constraint2D::GetCollideConnected)
		.addFunction("GetAttachedConstraint", &Constraint2D::GetAttachedConstraint)
		.addFunction("GetJoint", &Constraint2D::GetJoint)

		.addProperty("ownerBody", &Constraint2D::GetOwnerBody)
		.addProperty("otherBody", &Constraint2D::GetOtherBody, &Constraint2D::SetOtherBody)
		.addProperty("collideConnected", &Constraint2D::GetCollideConnected, &Constraint2D::SetCollideConnected)
		.addProperty("attachedConstraint", &Constraint2D::GetAttachedConstraint, &Constraint2D::SetAttachedConstraint)
		.addProperty("joint", &Constraint2D::GetJoint)
	);
}

static void RegisterConstraintDistance2D(kaguya::State& lua)
{
	using namespace kaguya;

	lua["KConstraintDistance2D"].setClass(UserdataMetatable<ConstraintDistance2D, Constraint2D>(false)
		.addStaticFunction("new", &KCreateObject<ConstraintDistance2D>)
		.addStaticFunction("__gc", &KReleaseObject<ConstraintDistance2D>)

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

	lua["KConstraintFriction2D"].setClass(UserdataMetatable<ConstraintFriction2D, Constraint2D>(false)
		.addStaticFunction("new", &KCreateObject<ConstraintFriction2D>)
		.addStaticFunction("__gc", &KReleaseObject<ConstraintFriction2D>)

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

	lua["KConstraintGear2D"].setClass(UserdataMetatable<ConstraintGear2D, Constraint2D>(false)
		.addStaticFunction("new", &KCreateObject<ConstraintGear2D>)
		.addStaticFunction("__gc", &KReleaseObject<ConstraintGear2D>)

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

	lua["KConstraintMotor2D"].setClass(UserdataMetatable<ConstraintMotor2D, Constraint2D>(false)
		.addStaticFunction("new", &KCreateObject<ConstraintMotor2D>)
		.addStaticFunction("__gc", &KReleaseObject<ConstraintMotor2D>)

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

	lua["KConstraintMouse2D"].setClass(UserdataMetatable<ConstraintMouse2D, Constraint2D>(false)
		.addStaticFunction("new", &KCreateObject<ConstraintMouse2D>)
		.addStaticFunction("__gc", &KReleaseObject<ConstraintMouse2D>)

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

	lua["KConstraintPrismatic2D"].setClass(UserdataMetatable<ConstraintPrismatic2D, Constraint2D>(false)
		.addStaticFunction("new", &KCreateObject<ConstraintPrismatic2D>)
		.addStaticFunction("__gc", &KReleaseObject<ConstraintPrismatic2D>)

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

	lua["KConstraintPulley2D"].setClass(UserdataMetatable<ConstraintPulley2D, Constraint2D>(false)
		.addStaticFunction("new", &KCreateObject<ConstraintPulley2D>)
		.addStaticFunction("__gc", &KReleaseObject<ConstraintPulley2D>)

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

	lua["KConstraintRevolute2D"].setClass(UserdataMetatable<ConstraintRevolute2D, Constraint2D>(false)
		.addStaticFunction("new", &KCreateObject<ConstraintRevolute2D>)
		.addStaticFunction("__gc", &KReleaseObject<ConstraintRevolute2D>)

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

	lua["KConstraintRope2D"].setClass(UserdataMetatable<ConstraintRope2D, Constraint2D>(false)
		.addStaticFunction("new", &KCreateObject<ConstraintRope2D>)
		.addStaticFunction("__gc", &KReleaseObject<ConstraintRope2D>)

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

	lua["KConstraintWeld2D"].setClass(UserdataMetatable<ConstraintWeld2D, Constraint2D>(false)
		.addStaticFunction("new", &KCreateObject<ConstraintWeld2D>)
		.addStaticFunction("__gc", &KReleaseObject<ConstraintWeld2D>)

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

	lua["KConstraintWheel2D"].setClass(UserdataMetatable<ConstraintWheel2D, Constraint2D>(false)
		.addStaticFunction("new", &KCreateObject<ConstraintWheel2D>)
		.addStaticFunction("__gc", &KReleaseObject<ConstraintWheel2D>)

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

	lua["KPIXEL_SIZE"] = PIXEL_SIZE;

	lua["KDrawable2D"].setClass(UserdataMetatable<Drawable2D, Drawable>(false)
		.addFunction("OnSetEnabled", &Drawable2D::OnSetEnabled)
		.addFunction("SetLayer", &Drawable2D::SetLayer)
		.addFunction("SetOrderInLayer", &Drawable2D::SetOrderInLayer)
		.addFunction("GetLayer", &Drawable2D::GetLayer)
		.addFunction("GetOrderInLayer", &Drawable2D::GetOrderInLayer)
		.addFunction("GetSourceBatches", &Drawable2D::GetSourceBatches)

		.addProperty("layer", &Drawable2D::GetLayer, &Drawable2D::SetLayer)
		.addProperty("orderInLayer", &Drawable2D::GetOrderInLayer, &Drawable2D::SetOrderInLayer)
		.addProperty("sourceBatches", &Drawable2D::GetSourceBatches)
	);
}

static void RegisterParticleEffect2D(kaguya::State& lua)
{
	using namespace kaguya;

	// enum EmitterType2D;
	lua["KEMITTER_TYPE_GRAVITY"] = EMITTER_TYPE_GRAVITY;
	lua["KEMITTER_TYPE_RADIAL"] = EMITTER_TYPE_RADIAL;

	lua["KParticleEffect2D"].setClass(UserdataMetatable<ParticleEffect2D, Resource>(false)
		.addStaticFunction("new", &KCreateObject<ParticleEffect2D>)
		.addStaticFunction("__gc", &KReleaseObject<ParticleEffect2D>)

		.addFunction("BeginLoad", &ParticleEffect2D::BeginLoad)
		.addFunction("EndLoad", &ParticleEffect2D::EndLoad)
		.addFunction("Save", &ParticleEffect2D::Save)
		.addFunction("SetSprite", &ParticleEffect2D::SetSprite)
		.addFunction("SetSourcePositionVariance", &ParticleEffect2D::SetSourcePositionVariance)
		.addFunction("SetSpeed", &ParticleEffect2D::SetSpeed)
		.addFunction("SetSpeedVariance", &ParticleEffect2D::SetSpeedVariance)
		.addFunction("SetParticleLifeSpan", &ParticleEffect2D::SetParticleLifeSpan)
		.addFunction("SetParticleLifespanVariance", &ParticleEffect2D::SetParticleLifespanVariance)
		.addFunction("SetAngle", &ParticleEffect2D::SetAngle)
		.addFunction("SetAngleVariance", &ParticleEffect2D::SetAngleVariance)
		.addFunction("SetGravity", &ParticleEffect2D::SetGravity)
		.addFunction("SetRadialAcceleration", &ParticleEffect2D::SetRadialAcceleration)
		.addFunction("SetTangentialAcceleration", &ParticleEffect2D::SetTangentialAcceleration)
		.addFunction("SetRadialAccelVariance", &ParticleEffect2D::SetRadialAccelVariance)
		.addFunction("SetTangentialAccelVariance", &ParticleEffect2D::SetTangentialAccelVariance)
		.addFunction("SetStartColor", &ParticleEffect2D::SetStartColor)
		.addFunction("SetStartColorVariance", &ParticleEffect2D::SetStartColorVariance)
		.addFunction("SetFinishColor", &ParticleEffect2D::SetFinishColor)
		.addFunction("SetFinishColorVariance", &ParticleEffect2D::SetFinishColorVariance)
		.addFunction("SetMaxParticles", &ParticleEffect2D::SetMaxParticles)
		.addFunction("SetStartParticleSize", &ParticleEffect2D::SetStartParticleSize)
		.addFunction("SetStartParticleSizeVariance", &ParticleEffect2D::SetStartParticleSizeVariance)
		.addFunction("SetFinishParticleSize", &ParticleEffect2D::SetFinishParticleSize)
		.addFunction("SetFinishParticleSizeVariance", &ParticleEffect2D::SetFinishParticleSizeVariance)
		.addFunction("SetDuration", &ParticleEffect2D::SetDuration)
		.addFunction("SetEmitterType", &ParticleEffect2D::SetEmitterType)
		.addFunction("SetMaxRadius", &ParticleEffect2D::SetMaxRadius)
		.addFunction("SetMaxRadiusVariance", &ParticleEffect2D::SetMaxRadiusVariance)
		.addFunction("SetMinRadius", &ParticleEffect2D::SetMinRadius)
		.addFunction("SetMinRadiusVariance", &ParticleEffect2D::SetMinRadiusVariance)
		.addFunction("SetRotatePerSecond", &ParticleEffect2D::SetRotatePerSecond)
		.addFunction("SetRotatePerSecondVariance", &ParticleEffect2D::SetRotatePerSecondVariance)
		.addFunction("SetBlendMode", &ParticleEffect2D::SetBlendMode)
		.addFunction("SetRotationStart", &ParticleEffect2D::SetRotationStart)
		.addFunction("SetRotationStartVariance", &ParticleEffect2D::SetRotationStartVariance)
		.addFunction("SetRotationEnd", &ParticleEffect2D::SetRotationEnd)
		.addFunction("SetRotationEndVariance", &ParticleEffect2D::SetRotationEndVariance)
		.addFunction("GetSprite", &ParticleEffect2D::GetSprite)
		.addFunction("GetSourcePositionVariance", &ParticleEffect2D::GetSourcePositionVariance)
		.addFunction("GetSpeed", &ParticleEffect2D::GetSpeed)
		.addFunction("GetSpeedVariance", &ParticleEffect2D::GetSpeedVariance)
		.addFunction("GetParticleLifeSpan", &ParticleEffect2D::GetParticleLifeSpan)
		.addFunction("GetParticleLifespanVariance", &ParticleEffect2D::GetParticleLifespanVariance)
		.addFunction("GetAngle", &ParticleEffect2D::GetAngle)
		.addFunction("GetAngleVariance", &ParticleEffect2D::GetAngleVariance)
		.addFunction("GetGravity", &ParticleEffect2D::GetGravity)
		.addFunction("GetRadialAcceleration", &ParticleEffect2D::GetRadialAcceleration)
		.addFunction("GetTangentialAcceleration", &ParticleEffect2D::GetTangentialAcceleration)
		.addFunction("GetRadialAccelVariance", &ParticleEffect2D::GetRadialAccelVariance)
		.addFunction("GetTangentialAccelVariance", &ParticleEffect2D::GetTangentialAccelVariance)
		.addFunction("GetStartColor", &ParticleEffect2D::GetStartColor)
		.addFunction("GetStartColorVariance", &ParticleEffect2D::GetStartColorVariance)
		.addFunction("GetFinishColor", &ParticleEffect2D::GetFinishColor)
		.addFunction("GetFinishColorVariance", &ParticleEffect2D::GetFinishColorVariance)
		.addFunction("GetMaxParticles", &ParticleEffect2D::GetMaxParticles)
		.addFunction("GetStartParticleSize", &ParticleEffect2D::GetStartParticleSize)
		.addFunction("GetStartParticleSizeVariance", &ParticleEffect2D::GetStartParticleSizeVariance)
		.addFunction("GetFinishParticleSize", &ParticleEffect2D::GetFinishParticleSize)
		.addFunction("GetFinishParticleSizeVariance", &ParticleEffect2D::GetFinishParticleSizeVariance)
		.addFunction("GetDuration", &ParticleEffect2D::GetDuration)
		.addFunction("GetEmitterType", &ParticleEffect2D::GetEmitterType)
		.addFunction("GetMaxRadius", &ParticleEffect2D::GetMaxRadius)
		.addFunction("GetMaxRadiusVariance", &ParticleEffect2D::GetMaxRadiusVariance)
		.addFunction("GetMinRadius", &ParticleEffect2D::GetMinRadius)
		.addFunction("GetMinRadiusVariance", &ParticleEffect2D::GetMinRadiusVariance)
		.addFunction("GetRotatePerSecond", &ParticleEffect2D::GetRotatePerSecond)
		.addFunction("GetRotatePerSecondVariance", &ParticleEffect2D::GetRotatePerSecondVariance)
		.addFunction("GetBlendMode", &ParticleEffect2D::GetBlendMode)
		.addFunction("GetRotationStart", &ParticleEffect2D::GetRotationStart)
		.addFunction("GetRotationStartVariance", &ParticleEffect2D::GetRotationStartVariance)
		.addFunction("GetRotationEnd", &ParticleEffect2D::GetRotationEnd)
		.addFunction("GetRotationEndVariance", &ParticleEffect2D::GetRotationEndVariance)

		.addProperty("sprite", &ParticleEffect2D::GetSprite, &ParticleEffect2D::SetSprite)
		.addProperty("sourcePositionVariance", &ParticleEffect2D::GetSourcePositionVariance, &ParticleEffect2D::SetSourcePositionVariance)
		.addProperty("speed", &ParticleEffect2D::GetSpeed, &ParticleEffect2D::SetSpeed)
		.addProperty("speedVariance", &ParticleEffect2D::GetSpeedVariance, &ParticleEffect2D::SetSpeedVariance)
		.addProperty("particleLifeSpan", &ParticleEffect2D::GetParticleLifeSpan, &ParticleEffect2D::SetParticleLifeSpan)
		.addProperty("particleLifespanVariance", &ParticleEffect2D::GetParticleLifespanVariance, &ParticleEffect2D::SetParticleLifespanVariance)
		.addProperty("angle", &ParticleEffect2D::GetAngle, &ParticleEffect2D::SetAngle)
		.addProperty("angleVariance", &ParticleEffect2D::GetAngleVariance, &ParticleEffect2D::SetAngleVariance)
		.addProperty("gravity", &ParticleEffect2D::GetGravity, &ParticleEffect2D::SetGravity)
		.addProperty("radialAcceleration", &ParticleEffect2D::GetRadialAcceleration, &ParticleEffect2D::SetRadialAcceleration)
		.addProperty("tangentialAcceleration", &ParticleEffect2D::GetTangentialAcceleration, &ParticleEffect2D::SetTangentialAcceleration)
		.addProperty("radialAccelVariance", &ParticleEffect2D::GetRadialAccelVariance, &ParticleEffect2D::SetRadialAccelVariance)
		.addProperty("tangentialAccelVariance", &ParticleEffect2D::GetTangentialAccelVariance, &ParticleEffect2D::SetTangentialAccelVariance)
		.addProperty("startColor", &ParticleEffect2D::GetStartColor, &ParticleEffect2D::SetStartColor)
		.addProperty("startColorVariance", &ParticleEffect2D::GetStartColorVariance, &ParticleEffect2D::SetStartColorVariance)
		.addProperty("finishColor", &ParticleEffect2D::GetFinishColor, &ParticleEffect2D::SetFinishColor)
		.addProperty("finishColorVariance", &ParticleEffect2D::GetFinishColorVariance, &ParticleEffect2D::SetFinishColorVariance)
		.addProperty("maxParticles", &ParticleEffect2D::GetMaxParticles, &ParticleEffect2D::SetMaxParticles)
		.addProperty("startParticleSize", &ParticleEffect2D::GetStartParticleSize, &ParticleEffect2D::SetStartParticleSize)
		.addProperty("startParticleSizeVariance", &ParticleEffect2D::GetStartParticleSizeVariance, &ParticleEffect2D::SetStartParticleSizeVariance)
		.addProperty("finishParticleSize", &ParticleEffect2D::GetFinishParticleSize, &ParticleEffect2D::SetFinishParticleSize)
		.addProperty("finishParticleSizeVariance", &ParticleEffect2D::GetFinishParticleSizeVariance, &ParticleEffect2D::SetFinishParticleSizeVariance)
		.addProperty("duration", &ParticleEffect2D::GetDuration, &ParticleEffect2D::SetDuration)
		.addProperty("emitterType", &ParticleEffect2D::GetEmitterType, &ParticleEffect2D::SetEmitterType)
		.addProperty("maxRadius", &ParticleEffect2D::GetMaxRadius, &ParticleEffect2D::SetMaxRadius)
		.addProperty("maxRadiusVariance", &ParticleEffect2D::GetMaxRadiusVariance, &ParticleEffect2D::SetMaxRadiusVariance)
		.addProperty("minRadius", &ParticleEffect2D::GetMinRadius, &ParticleEffect2D::SetMinRadius)
		.addProperty("minRadiusVariance", &ParticleEffect2D::GetMinRadiusVariance, &ParticleEffect2D::SetMinRadiusVariance)
		.addProperty("rotatePerSecond", &ParticleEffect2D::GetRotatePerSecond, &ParticleEffect2D::SetRotatePerSecond)
		.addProperty("rotatePerSecondVariance", &ParticleEffect2D::GetRotatePerSecondVariance, &ParticleEffect2D::SetRotatePerSecondVariance)
		.addProperty("blendMode", &ParticleEffect2D::GetBlendMode, &ParticleEffect2D::SetBlendMode)
		.addProperty("rotationStart", &ParticleEffect2D::GetRotationStart, &ParticleEffect2D::SetRotationStart)
		.addProperty("rotationStartVariance", &ParticleEffect2D::GetRotationStartVariance, &ParticleEffect2D::SetRotationStartVariance)
		.addProperty("rotationEnd", &ParticleEffect2D::GetRotationEnd, &ParticleEffect2D::SetRotationEnd)
		.addProperty("rotationEndVariance", &ParticleEffect2D::GetRotationEndVariance, &ParticleEffect2D::SetRotationEndVariance)
	);
}

static void RegisterParticleEmitter2D(kaguya::State& lua)
{
	using namespace kaguya;

	lua["KParticleEmitter2D"].setClass(UserdataMetatable<ParticleEmitter2D, Drawable2D>(false)
		.addStaticFunction("new", &KCreateObject<ParticleEmitter2D>)
		.addStaticFunction("__gc", &KReleaseObject<ParticleEmitter2D>)

		.addFunction("OnSetEnabled", &ParticleEmitter2D::OnSetEnabled)
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

static void RegisterPhysicsEvents2D(kaguya::State& lua)
{
	using namespace kaguya;

	lua["KE_PHYSICSBEGINCONTACT2D"] = E_PHYSICSBEGINCONTACT2D;
	lua["KE_PHYSICSENDCONTACT2D"] = E_PHYSICSENDCONTACT2D;
}

static void RegisterPhysicsWorld2D(kaguya::State& lua)
{
	using namespace kaguya;

	lua["KPhysicsRaycastResult2D"].setClass(UserdataMetatable<PhysicsRaycastResult2D>()
		.setConstructors<PhysicsRaycastResult2D()>()

		.addProperty("position", &PhysicsRaycastResult2D::position_)
		.addProperty("normal", &PhysicsRaycastResult2D::normal_)
		.addProperty("distance", &PhysicsRaycastResult2D::distance_)
		.addProperty("body", &PhysicsRaycastResult2D::body_)
	);

	lua["KPhysicsWorld2D"].setClass(UserdataMetatable<PhysicsWorld2D, Component>(false)
		.addStaticFunction("new", &KCreateObject<PhysicsWorld2D>)
		.addStaticFunction("__gc", &KReleaseObject<PhysicsWorld2D>)

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
		.addFunction("AddRigidBody", &PhysicsWorld2D::AddRigidBody)
		.addFunction("RemoveRigidBody", &PhysicsWorld2D::RemoveRigidBody)
		.addFunction("AddDelayedWorldTransform", &PhysicsWorld2D::AddDelayedWorldTransform)
		.addFunction("Raycast", &PhysicsWorld2D::Raycast)
		.addFunction("RaycastSingle", &PhysicsWorld2D::RaycastSingle)

		.addOverloadedFunctions("GetRigidBody",
			static_cast<RigidBody2D*(PhysicsWorld2D::*)(const Vector2&, unsigned)>(&PhysicsWorld2D::GetRigidBody),
			static_cast<RigidBody2D*(PhysicsWorld2D::*)(int, int, unsigned)>(&PhysicsWorld2D::GetRigidBody))

		.addFunction("GetRigidBodies", &PhysicsWorld2D::GetRigidBodies)
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
		.addFunction("GetWorld", &PhysicsWorld2D::GetWorld)
		.addFunction("SetApplyingTransforms", &PhysicsWorld2D::SetApplyingTransforms)
		.addFunction("IsApplyingTransforms", &PhysicsWorld2D::IsApplyingTransforms)

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
		.addProperty("world", &PhysicsWorld2D::GetWorld)
		.addProperty("applyingTransforms", &PhysicsWorld2D::IsApplyingTransforms, &PhysicsWorld2D::SetApplyingTransforms)
	);
}

static void RegisterRenderer2D(kaguya::State& lua)
{
	using namespace kaguya;

	lua["KRenderer2D"].setClass(UserdataMetatable<Renderer2D, Drawable>(false)
		.addStaticFunction("new", &KCreateObject<Renderer2D>)
		.addStaticFunction("__gc", &KReleaseObject<Renderer2D>)
	);
}

static void RegisterRigidBody2D(kaguya::State& lua)
{
	using namespace kaguya;

	// enum BodyType2D;
	lua["KBT_STATIC"] = BT_STATIC;
	lua["KBT_KINEMATIC"] = BT_KINEMATIC;
	lua["KBT_DYNAMIC"] = BT_DYNAMIC;

	lua["KRigidBody2D"].setClass(UserdataMetatable<RigidBody2D, Component>(false)
		.addStaticFunction("new", &KCreateObject<RigidBody2D>)
		.addStaticFunction("__gc", &KReleaseObject<RigidBody2D>)

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

		.addOverloadedFunctions("ApplyWorldTransform",
			static_cast<void(RigidBody2D::*)()>(&RigidBody2D::ApplyWorldTransform),
			static_cast<void(RigidBody2D::*)(const Vector3&, const Quaternion&)>(&RigidBody2D::ApplyWorldTransform))

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

	lua["KSprite2D"].setClass(UserdataMetatable<Sprite2D, Resource>(false)
		.addStaticFunction("new", &KCreateObject<Sprite2D>)
		.addStaticFunction("__gc", &KReleaseObject<Sprite2D>)

		.addFunction("BeginLoad", &Sprite2D::BeginLoad)
		.addFunction("EndLoad", &Sprite2D::EndLoad)
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

		.addOverloadedFunctions("GetDrawRectangle",
			static_cast<bool(Sprite2D::*)(Rect&, bool, bool) const>(&Sprite2D::GetDrawRectangle),
			static_cast<bool(Sprite2D::*)(Rect&, const Vector2&, bool, bool) const>(&Sprite2D::GetDrawRectangle))

		.addFunction("GetTextureRectangle", &Sprite2D::GetTextureRectangle)
		.addStaticFunction("SaveToResourceRef", &Sprite2D::SaveToResourceRef)
		.addStaticFunction("LoadFromResourceRef", &Sprite2D::LoadFromResourceRef)

		.addProperty("texture", &Sprite2D::GetTexture, &Sprite2D::SetTexture)
		.addProperty("rectangle", &Sprite2D::GetRectangle, &Sprite2D::SetRectangle)
		.addProperty("hotSpot", &Sprite2D::GetHotSpot, &Sprite2D::SetHotSpot)
		.addProperty("offset", &Sprite2D::GetOffset, &Sprite2D::SetOffset)
		.addProperty("textureEdgeOffset", &Sprite2D::GetTextureEdgeOffset, &Sprite2D::SetTextureEdgeOffset)
		.addProperty("spriteSheet", &Sprite2D::GetSpriteSheet, &Sprite2D::SetSpriteSheet)
	);
}

static void RegisterSpriteSheet2D(kaguya::State& lua)
{
	using namespace kaguya;

	lua["KSpriteSheet2D"].setClass(UserdataMetatable<SpriteSheet2D, Resource>(false)
		.addStaticFunction("new", &KCreateObject<SpriteSheet2D>)
		.addStaticFunction("__gc", &KReleaseObject<SpriteSheet2D>)

		.addFunction("SetTexture", &SpriteSheet2D::SetTexture)
		.addFunction("DefineSprite", &SpriteSheet2D::DefineSprite)
		.addFunction("GetTexture", &SpriteSheet2D::GetTexture)
		.addFunction("GetSprite", &SpriteSheet2D::GetSprite)
		.addFunction("GetSpriteMapping", &SpriteSheet2D::GetSpriteMapping)

		.addProperty("texture", &SpriteSheet2D::GetTexture, &SpriteSheet2D::SetTexture)
		.addProperty("spriteMapping", &SpriteSheet2D::GetSpriteMapping)
	);
}

static void RegisterStaticSprite2D(kaguya::State& lua)
{
	using namespace kaguya;

	lua["KStaticSprite2D"].setClass(UserdataMetatable<StaticSprite2D, Drawable2D>(false)
		.addStaticFunction("new", &KCreateObject<StaticSprite2D>)
		.addStaticFunction("__gc", &KReleaseObject<StaticSprite2D>)

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

	lua["KTileMap2D"].setClass(UserdataMetatable<TileMap2D, Component>(false)
		.addStaticFunction("new", &KCreateObject<TileMap2D>)
		.addStaticFunction("__gc", &KReleaseObject<TileMap2D>)


		.addOverloadedFunctions("DrawDebugGeometry",
			static_cast<void(TileMap2D::*)(DebugRenderer*, bool)>(&TileMap2D::DrawDebugGeometry),
			static_cast<void(TileMap2D::*)()>(&TileMap2D::DrawDebugGeometry))

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
	lua["KO_ORTHOGONAL"] = O_ORTHOGONAL;
	lua["KO_ISOMETRIC"] = O_ISOMETRIC;
	lua["KO_STAGGERED"] = O_STAGGERED;
	lua["KO_HEXAGONAL"] = O_HEXAGONAL;

	lua["KTileMapInfo2D"].setClass(UserdataMetatable<TileMapInfo2D>()

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
	lua["KLT_TILE_LAYER"] = LT_TILE_LAYER;
	lua["KLT_OBJECT_GROUP"] = LT_OBJECT_GROUP;
	lua["KLT_IMAGE_LAYER"] = LT_IMAGE_LAYER;
	lua["KLT_INVALID"] = LT_INVALID;

	// enum TileMapObjectType2D;
	lua["KOT_RECTANGLE"] = OT_RECTANGLE;
	lua["KOT_ELLIPSE"] = OT_ELLIPSE;
	lua["KOT_POLYGON"] = OT_POLYGON;
	lua["KOT_POLYLINE"] = OT_POLYLINE;
	lua["KOT_TILE"] = OT_TILE;
	lua["KOT_INVALID"] = OT_INVALID;

	lua["KPropertySet2D"].setClass(UserdataMetatable<PropertySet2D, RefCounted>()
		.setConstructors<PropertySet2D()>()

		.addFunction("Load", &PropertySet2D::Load)
		.addFunction("HasProperty", &PropertySet2D::HasProperty)
		.addFunction("GetProperty", &PropertySet2D::GetProperty)
	);

	lua["KTile2D"].setClass(UserdataMetatable<Tile2D, RefCounted>()
		.setConstructors<Tile2D()>()

		.addFunction("GetGid", &Tile2D::GetGid)
		.addFunction("GetSprite", &Tile2D::GetSprite)
		.addFunction("HasProperty", &Tile2D::HasProperty)
		.addFunction("GetProperty", &Tile2D::GetProperty)

		.addProperty("gid", &Tile2D::GetGid)
		.addProperty("sprite", &Tile2D::GetSprite)
	);

	lua["KTileMapObject2D"].setClass(UserdataMetatable<TileMapObject2D, RefCounted>()
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

	lua["KTileMapLayer2D"].setClass(UserdataMetatable<TileMapLayer2D, Component>(false)
		.addStaticFunction("new", &KCreateObject<TileMapLayer2D>)
		.addStaticFunction("__gc", &KReleaseObject<TileMapLayer2D>)

		.addFunction("Initialize", &TileMapLayer2D::Initialize)
		.addFunction("SetDrawOrder", &TileMapLayer2D::SetDrawOrder)
		.addFunction("SetVisible", &TileMapLayer2D::SetVisible)
		.addFunction("GetTileMap", &TileMapLayer2D::GetTileMap)
		.addFunction("GetTmxLayer", &TileMapLayer2D::GetTmxLayer)
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
		.addProperty("tmxLayer", &TileMapLayer2D::GetTmxLayer)
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

	lua["KTmxLayer2D"].setClass(UserdataMetatable<TmxLayer2D, RefCounted>()
		.setConstructors<TmxLayer2D(TmxFile2D*, TileMapLayerType2D)>()

		.addFunction("GetTmxFile", &TmxLayer2D::GetTmxFile)
		.addFunction("GetType", &TmxLayer2D::GetType)
		.addFunction("GetName", &TmxLayer2D::GetName)
		.addFunction("GetWidth", &TmxLayer2D::GetWidth)
		.addFunction("GetHeight", &TmxLayer2D::GetHeight)
		.addFunction("IsVisible", &TmxLayer2D::IsVisible)
		.addFunction("HasProperty", &TmxLayer2D::HasProperty)
		.addFunction("GetProperty", &TmxLayer2D::GetProperty)

		.addProperty("tmxFile", &TmxLayer2D::GetTmxFile)
		.addProperty("type", &TmxLayer2D::GetType)
		.addProperty("name", &TmxLayer2D::GetName)
		.addProperty("width", &TmxLayer2D::GetWidth)
		.addProperty("height", &TmxLayer2D::GetHeight)
		.addProperty("visible", &TmxLayer2D::IsVisible)
	);

	lua["KTmxTileLayer2D"].setClass(UserdataMetatable<TmxTileLayer2D, TmxLayer2D>()
		.setConstructors<TmxTileLayer2D(TmxFile2D*)>()

		.addFunction("Load", &TmxTileLayer2D::Load)
		.addFunction("GetTile", &TmxTileLayer2D::GetTile)
	);

	lua["KTmxObjectGroup2D"].setClass(UserdataMetatable<TmxObjectGroup2D, TmxLayer2D>()
		.setConstructors<TmxObjectGroup2D(TmxFile2D*)>()

		.addFunction("Load", &TmxObjectGroup2D::Load)
		.addFunction("GetNumObjects", &TmxObjectGroup2D::GetNumObjects)
		.addFunction("GetObject", &TmxObjectGroup2D::GetObject)

		.addProperty("numObjects", &TmxObjectGroup2D::GetNumObjects)
	);

	lua["KTmxImageLayer2D"].setClass(UserdataMetatable<TmxImageLayer2D, TmxLayer2D>()
		.setConstructors<TmxImageLayer2D(TmxFile2D*)>()

		.addFunction("Load", &TmxImageLayer2D::Load)
		.addFunction("GetPosition", &TmxImageLayer2D::GetPosition)
		.addFunction("GetSource", &TmxImageLayer2D::GetSource)
		.addFunction("GetSprite", &TmxImageLayer2D::GetSprite)

		.addProperty("position", &TmxImageLayer2D::GetPosition)
		.addProperty("source", &TmxImageLayer2D::GetSource)
		.addProperty("sprite", &TmxImageLayer2D::GetSprite)
	);

	lua["KTmxFile2D"].setClass(UserdataMetatable<TmxFile2D, Resource>(false)
		.addStaticFunction("new", &KCreateObject<TmxFile2D>)
		.addStaticFunction("__gc", &KReleaseObject<TmxFile2D>)

		.addFunction("BeginLoad", &TmxFile2D::BeginLoad)
		.addFunction("EndLoad", &TmxFile2D::EndLoad)
		.addFunction("SetInfo", &TmxFile2D::SetInfo)

		.addOverloadedFunctions("AddLayer",
			static_cast<void(TmxFile2D::*)(unsigned, TmxLayer2D*)>(&TmxFile2D::AddLayer),
			static_cast<void(TmxFile2D::*)(TmxLayer2D*)>(&TmxFile2D::AddLayer))

		.addFunction("GetInfo", &TmxFile2D::GetInfo)
		.addFunction("GetTileSprite", &TmxFile2D::GetTileSprite)
		.addFunction("GetTilePropertySet", &TmxFile2D::GetTilePropertySet)
		.addFunction("GetNumLayers", &TmxFile2D::GetNumLayers)
		.addFunction("GetLayer", &TmxFile2D::GetLayer)

		.addProperty("info", &TmxFile2D::GetInfo)
		.addProperty("numLayers", &TmxFile2D::GetNumLayers)
	);
}

void RegisterUrho2DLuaAPI(kaguya::State& lua)
{
	RegisterStaticSprite2D(lua);
	RegisterCollisionShape2D(lua);
	RegisterConstraint2D(lua);
	RegisterDrawable2D(lua);

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
	RegisterPhysicsEvents2D(lua);
	RegisterPhysicsWorld2D(lua);
	RegisterRenderer2D(lua);
	RegisterRigidBody2D(lua);
	RegisterSprite2D(lua);
	RegisterSpriteSheet2D(lua);	
	RegisterTileMap2D(lua);
	RegisterTileMapDefs2D(lua);
	RegisterTileMapLayer2D(lua);
	RegisterTmxFile2D(lua);
}
}
