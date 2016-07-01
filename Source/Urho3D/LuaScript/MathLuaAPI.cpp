#include "../Math/AreaAllocator.h"
#include "../Math/BoundingBox.h"
#include "../Math/Color.h"
#include "../Math/Frustum.h"
#include "../Math/MathDefs.h"
#include "../Math/Matrix2.h"
#include "../Math/Matrix3.h"
#include "../Math/Matrix3x4.h"
#include "../Math/Matrix4.h"
#include "../Math/Plane.h"
#include "../Math/Polyhedron.h"
#include "../Math/Quaternion.h"
#include "../Math/Random.h"
#include "../Math/Ray.h"
#include "../Math/Rect.h"
#include "../Math/Sphere.h"
#include "../Math/StringHash.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void RegisterAreaAllocator(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KAreaAllocator"].setClass(UserdataMetatable<AreaAllocator>()
        .setConstructors<AreaAllocator(),
            AreaAllocator(int, int, bool),
            AreaAllocator(int, int, int, int, bool)>()

        .addFunction("Reset", &AreaAllocator::Reset)
        .addFunction("Allocate", &AreaAllocator::Allocate)
        .addFunction("GetWidth", &AreaAllocator::GetWidth)
        .addFunction("GetHeight", &AreaAllocator::GetHeight)
        .addFunction("GetFastMode", &AreaAllocator::GetFastMode)

        .addProperty("width", &AreaAllocator::GetWidth)
        .addProperty("height", &AreaAllocator::GetHeight)
        .addProperty("fastMode", &AreaAllocator::GetFastMode)
    );
}

static void RegisterBoundingBox(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KBoundingBox"].setClass(UserdataMetatable<BoundingBox>()
        .setConstructors<BoundingBox(),
            BoundingBox(const BoundingBox&),
            BoundingBox(const Rect&),
            BoundingBox(const Vector3&, const Vector3&),
            BoundingBox(float, float),
            BoundingBox(const Frustum&),
            BoundingBox(const Polyhedron&),
            BoundingBox(const Sphere&)>()

        .addFunction("__eq", &BoundingBox::operator==)

        .addOverloadedFunctions("Define",
            static_cast<void(BoundingBox::*)(const BoundingBox&)>(&BoundingBox::Define),
            static_cast<void(BoundingBox::*)(const Rect&)>(&BoundingBox::Define),
            static_cast<void(BoundingBox::*)(const Vector3&, const Vector3&)>(&BoundingBox::Define),
            static_cast<void(BoundingBox::*)(float, float)>(&BoundingBox::Define),
            static_cast<void(BoundingBox::*)(const Vector3&)>(&BoundingBox::Define),
            static_cast<void(BoundingBox::*)(const Frustum&)>(&BoundingBox::Define),
            static_cast<void(BoundingBox::*)(const Polyhedron&)>(&BoundingBox::Define),
            static_cast<void(BoundingBox::*)(const Sphere&)>(&BoundingBox::Define))


        .addOverloadedFunctions("Merge",
            static_cast<void(BoundingBox::*)(const Vector3&)>(&BoundingBox::Merge),
            static_cast<void(BoundingBox::*)(const BoundingBox&)>(&BoundingBox::Merge),
            static_cast<void(BoundingBox::*)(const Frustum&)>(&BoundingBox::Merge),
            static_cast<void(BoundingBox::*)(const Polyhedron&)>(&BoundingBox::Merge),
            static_cast<void(BoundingBox::*)(const Sphere&)>(&BoundingBox::Merge))

        .addFunction("Clip", &BoundingBox::Clip)

        .addOverloadedFunctions("Transform",
            static_cast<void(BoundingBox::*)(const Matrix3&)>(&BoundingBox::Transform),
            static_cast<void(BoundingBox::*)(const Matrix3x4&)>(&BoundingBox::Transform))

        .addFunction("Clear", &BoundingBox::Clear)
        .addFunction("Defined", &BoundingBox::Defined)
        .addFunction("Center", &BoundingBox::Center)
        .addFunction("Size", &BoundingBox::Size)
        .addFunction("HalfSize", &BoundingBox::HalfSize)

        .addOverloadedFunctions("Transformed",
            static_cast<BoundingBox(BoundingBox::*)(const Matrix3&) const>(&BoundingBox::Transformed),
            static_cast<BoundingBox(BoundingBox::*)(const Matrix3x4&) const>(&BoundingBox::Transformed))

        .addFunction("Projected", &BoundingBox::Projected)

        .addOverloadedFunctions("IsInside",
            static_cast<Intersection(BoundingBox::*)(const Vector3&) const>(&BoundingBox::IsInside),
            static_cast<Intersection(BoundingBox::*)(const BoundingBox&) const>(&BoundingBox::IsInside),
            static_cast<Intersection(BoundingBox::*)(const Sphere&) const>(&BoundingBox::IsInside))


        .addOverloadedFunctions("IsInsideFast",
            static_cast<Intersection(BoundingBox::*)(const BoundingBox&) const>(&BoundingBox::IsInsideFast),
            static_cast<Intersection(BoundingBox::*)(const Sphere&) const>(&BoundingBox::IsInsideFast))

        .addFunction("ToString", &BoundingBox::ToString)
		
        .addProperty("min", &BoundingBox::min_)
        .addProperty("dummyMin", &BoundingBox::dummyMin_)
        .addProperty("max", &BoundingBox::max_)
        .addProperty("dummyMax", &BoundingBox::dummyMax_)
    );
}

static void RegisterColor(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KColor"].setClass(UserdataMetatable<Color>()
        .setConstructors<Color(),
            Color(const Color&),
            Color(const Color&, float),
            Color(float, float, float),
            Color(float, float, float, float)>()

        .addFunction("__eq", &Color::operator==)
        .addFunction("__mul", &Color::operator*)
        .addFunction("__add", &Color::operator+)

        .addOverloadedFunctions("__sub",
            static_cast<Color(Color::*)() const>(&Color::operator-),
            static_cast<Color(Color::*)(const Color&) const>(&Color::operator-))

        .addFunction("ToUInt", &Color::ToUInt)
        .addFunction("ToHSL", &Color::ToHSL)
        .addFunction("ToHSV", &Color::ToHSV)
        .addFunction("FromHSL", &Color::FromHSL)
        .addFunction("FromHSV", &Color::FromHSV)
        .addFunction("ToVector3", &Color::ToVector3)
        .addFunction("ToVector4", &Color::ToVector4)
        .addFunction("SumRGB", &Color::SumRGB)
        .addFunction("Average", &Color::Average)
        .addFunction("Luma", &Color::Luma)
        .addFunction("Chroma", &Color::Chroma)

        .addFunction("Hue", static_cast<float(Color::*)() const>(&Color::Hue))
        .addFunction("SaturationHSL", static_cast<float(Color::*)() const>(&Color::SaturationHSL))
        .addFunction("SaturationHSV", static_cast<float(Color::*)() const>(&Color::SaturationHSV))

        .addFunction("Value", &Color::Value)
        .addFunction("Lightness", &Color::Lightness)
        
        // .addFunction("Bounds", &Color::Bounds)

        .addFunction("MaxRGB", &Color::MaxRGB)
        .addFunction("MinRGB", &Color::MinRGB)
        .addFunction("Range", &Color::Range)
        .addFunction("Clip", &Color::Clip)
        .addFunction("Invert", &Color::Invert)
        .addFunction("Lerp", &Color::Lerp)
        .addFunction("Abs", &Color::Abs)
        .addFunction("Equals", &Color::Equals)
        .addFunction("ToString", &Color::ToString)

        .addProperty("r", &Color::r_)
        .addProperty("g", &Color::g_)
        .addProperty("b", &Color::b_)
        .addProperty("a", &Color::a_)

        .addStaticField("WHITE", &Color::WHITE)
        .addStaticField("GRAY", &Color::GRAY)
        .addStaticField("BLACK", &Color::BLACK)
        .addStaticField("RED", &Color::RED)
        .addStaticField("GREEN", &Color::GREEN)
        .addStaticField("BLUE", &Color::BLUE)
        .addStaticField("CYAN", &Color::CYAN)
        .addStaticField("MAGENTA", &Color::MAGENTA)
        .addStaticField("YELLOW", &Color::YELLOW)
        .addStaticField("TRANSPARENT", &Color::TRANSPARENT)
    );
}

static void RegisterFrustum(kaguya::State& lua)
{
    using namespace kaguya;

    // enum FrustumPlane;
    lua["KPLANE_NEAR"] = PLANE_NEAR;
    lua["KPLANE_LEFT"] = PLANE_LEFT;
    lua["KPLANE_RIGHT"] = PLANE_RIGHT;
    lua["KPLANE_UP"] = PLANE_UP;
    lua["KPLANE_DOWN"] = PLANE_DOWN;
    lua["KPLANE_FAR"] = PLANE_FAR;

    lua["KNUM_FRUSTUM_PLANES"] = NUM_FRUSTUM_PLANES;
    lua["KNUM_FRUSTUM_VERTICES"] = NUM_FRUSTUM_VERTICES;
    lua["KFrustum"].setClass(UserdataMetatable<Frustum>()
        .setConstructors<Frustum(), Frustum(const Frustum&)>()

        .addOverloadedFunctions("Define",
            static_cast<void(Frustum::*)(float, float, float, float, float, const Matrix3x4&)>(&Frustum::Define),
            static_cast<void(Frustum::*)(const Vector3&, const Vector3&, const Matrix3x4&)>(&Frustum::Define),
            static_cast<void(Frustum::*)(const BoundingBox&, const Matrix3x4&)>(&Frustum::Define))

        .addFunction("DefineOrtho", &Frustum::DefineOrtho)

        .addOverloadedFunctions("Transform",
            static_cast<void(Frustum::*)(const Matrix3&)>(&Frustum::Transform),
            static_cast<void(Frustum::*)(const Matrix3x4&)>(&Frustum::Transform))


        .addOverloadedFunctions("IsInside",
            static_cast<Intersection(Frustum::*)(const Vector3&) const>(&Frustum::IsInside),
            static_cast<Intersection(Frustum::*)(const Sphere&) const>(&Frustum::IsInside),
            static_cast<Intersection(Frustum::*)(const BoundingBox&) const>(&Frustum::IsInside))


        .addOverloadedFunctions("IsInsideFast",
            static_cast<Intersection(Frustum::*)(const Sphere&) const>(&Frustum::IsInsideFast),
            static_cast<Intersection(Frustum::*)(const BoundingBox&) const>(&Frustum::IsInsideFast))

        .addFunction("Distance", &Frustum::Distance)

        .addOverloadedFunctions("Transformed",
            static_cast<Frustum(Frustum::*)(const Matrix3&) const>(&Frustum::Transformed),
            static_cast<Frustum(Frustum::*)(const Matrix3x4&) const>(&Frustum::Transformed))

        .addFunction("Projected", &Frustum::Projected)
        .addFunction("UpdatePlanes", &Frustum::UpdatePlanes)
    );
}

static void RegisterMathDefs(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KM_PI"] = M_PI;
    lua["KM_HALF_PI"] = M_HALF_PI;
    lua["KM_MIN_INT"] = M_MIN_INT;
    lua["KM_MAX_INT"] = M_MAX_INT;
    lua["KM_MIN_UNSIGNED"] = M_MIN_UNSIGNED;
    lua["KM_MAX_UNSIGNED"] = M_MAX_UNSIGNED;
    lua["KM_EPSILON"] = M_EPSILON;
    lua["KM_LARGE_EPSILON"] = M_LARGE_EPSILON;
    lua["KM_MIN_NEARCLIP"] = M_MIN_NEARCLIP;
    lua["KM_MAX_FOV"] = M_MAX_FOV;
    lua["KM_LARGE_VALUE"] = M_LARGE_VALUE;
    lua["KM_INFINITY"] = M_INFINITY;
    lua["KM_DEGTORAD"] = M_DEGTORAD;
    lua["KM_DEGTORAD_2"] = M_DEGTORAD_2;
    lua["KM_RADTODEG"] = M_RADTODEG;
    // enum Intersection;
    lua["KOUTSIDE"] = OUTSIDE;
    lua["KINTERSECTS"] = INTERSECTS;
    lua["KINSIDE"] = INSIDE;

    // bool Equals(T lhs, T rhs);
    lua["KEquals"] = static_cast<bool(*)(float, float)>(&Equals);
    // T Lerp(T lhs, T rhs, U t);
    lua["KLerp"] = static_cast<float(*)(float, float, float)>(&Lerp);
    // T Min(T lhs, U rhs);
    lua["KMin"] = static_cast<float(*)(float, float)>(&Min);
    // T Max(T lhs, U rhs);
    lua["KMax"] = static_cast<float(*)(float, float)>(&Max);
    // T Abs(T value);
    lua["KAbs"] = static_cast<float(*)(float)>(&Abs);
    // T Sign(T value);
    lua["KSign"] = static_cast<float(*)(float)>(&Sign);
    
    lua["KIsNaN"] = function(&IsNaN);
    
    // T Clamp(T value, T min, T max);
    lua["KClamp"] = static_cast<float(*)(float, float, float)>(&Clamp);
    // T SmoothStep(T lhs, T rhs, T t);
    lua["KSmoothStep"] = static_cast<float(*)(float, float, float)>(&SmoothStep);
    // T Sin(T angle);
    lua["KSin"] = static_cast<float(*)(float)>(&Sin);
    // T Cos(T angle);
    lua["KCos"] = static_cast<float(*)(float)>(&Cos);
    // T Tan(T angle);
    lua["KTan"] = static_cast<float(*)(float)>(&Tan);
    // T Asin(T x);
    lua["KAsin"] = static_cast<float(*)(float)>(&Asin);
    // T Acos(T x);
    lua["KAcos"] = static_cast<float(*)(float)>(&Acos);
    // T Atan(T x);
    lua["KAtan"] = static_cast<float(*)(float)>(&Atan);
    // T Atan2(T y, T x);
    lua["KAtan2"] = static_cast<float(*)(float, float)>(&Atan2);

    lua["KIsPowerOfTwo"] = function(&IsPowerOfTwo);
    lua["KNextPowerOfTwo"] = function(&NextPowerOfTwo);
    lua["KCountSetBits"] = function(&CountSetBits);
    lua["KSDBMHash"] = function(&SDBMHash);

    lua["KRandom"] = overload(static_cast<float(*)()>(&Random),
        static_cast<float(*)(float)>(&Random),
        static_cast<float(*)(float, float)>(&Random),
        static_cast<int(*)(int)>(&Random),
        static_cast<int(*)(int, int)>(&Random));

    lua["KRandomNormal"] = function(&RandomNormal);
    lua["KFloatToHalf"] = function(&FloatToHalf);
    lua["KHalfToFloat"] = function(&HalfToFloat);
    lua["KSinCos"] = function(&SinCos);
}

static void RegisterMatrix2(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KMatrix2"].setClass(UserdataMetatable<Matrix2>()
        .setConstructors<Matrix2(),
            Matrix2(const Matrix2&),
            Matrix2(float, float, float, float)>()

        .addFunction("__eq", &Matrix2::operator==)

        .addOverloadedFunctions("__mul",
            static_cast<Vector2(Matrix2::*)(const Vector2&) const>(&Matrix2::operator*),
            static_cast<Matrix2(Matrix2::*)(float) const>(&Matrix2::operator*),
            static_cast<Matrix2(Matrix2::*)(const Matrix2&) const>(&Matrix2::operator*))

        .addFunction("__add", &Matrix2::operator+)
        .addFunction("__sub", &Matrix2::operator-)

        .addOverloadedFunctions("SetScale",
            static_cast<void(Matrix2::*)(const Vector2&)>(&Matrix2::SetScale),
            static_cast<void(Matrix2::*)(float)>(&Matrix2::SetScale))

        .addFunction("Scale", &Matrix2::Scale)
        .addFunction("Transpose", &Matrix2::Transpose)
        .addFunction("Scaled", &Matrix2::Scaled)
        .addFunction("Equals", &Matrix2::Equals)
        .addFunction("Inverse", &Matrix2::Inverse)
        .addFunction("ToString", &Matrix2::ToString)
        .addProperty("m00", &Matrix2::m00_)
        .addProperty("m01", &Matrix2::m01_)
        .addProperty("m02", &Matrix2::m02_)
        .addProperty("m10", &Matrix2::m10_)
        .addProperty("m11", &Matrix2::m11_)
        .addStaticField("ZERO", &Matrix2::ZERO)
        .addStaticField("IDENTITY", &Matrix2::IDENTITY)
    );
}

static void RegisterMatrix3(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KMatrix3"].setClass(UserdataMetatable<Matrix3>()
        .setConstructors<Matrix3(),
            Matrix3(const Matrix3&),
            Matrix3(float, float, float, float, float, float, float, float, float)>()

        .addFunction("__eq", &Matrix3::operator==)

        .addOverloadedFunctions("__mul",
            static_cast<Vector3(Matrix3::*)(const Vector3&) const>(&Matrix3::operator*),
            static_cast<Matrix3(Matrix3::*)(float) const>(&Matrix3::operator*),
            static_cast<Matrix3(Matrix3::*)(const Matrix3&) const>(&Matrix3::operator*))

        .addFunction("__add", &Matrix3::operator+)
        .addFunction("__sub", &Matrix3::operator-)

        .addOverloadedFunctions("SetScale",
            static_cast<void(Matrix3::*)(const Vector3&)>(&Matrix3::SetScale),
            static_cast<void(Matrix3::*)(float)>(&Matrix3::SetScale))

        .addFunction("Scale", &Matrix3::Scale)
        .addFunction("Transpose", &Matrix3::Transpose)
        .addFunction("Scaled", &Matrix3::Scaled)
        .addFunction("Equals", &Matrix3::Equals)
        .addFunction("Inverse", &Matrix3::Inverse)
        .addFunction("ToString", &Matrix3::ToString)
        .addProperty("m00", &Matrix3::m00_)
        .addProperty("m01", &Matrix3::m01_)
        .addProperty("m02", &Matrix3::m02_)
        .addProperty("m10", &Matrix3::m10_)
        .addProperty("m11", &Matrix3::m11_)
        .addProperty("m12", &Matrix3::m12_)
        .addProperty("m20", &Matrix3::m20_)
        .addProperty("m21", &Matrix3::m21_)
        .addProperty("m22", &Matrix3::m22_)
        .addStaticField("ZERO", &Matrix3::ZERO)
        .addStaticField("IDENTITY", &Matrix3::IDENTITY)
    );
}

static std::tuple<Vector3, Quaternion, Vector3> Matrix3x4Decompose(const Matrix3x4& matrix3x4)
{
    Vector3 translation;
    Quaternion rotation;
    Vector3 scale;
    matrix3x4.Decompose(translation, rotation, scale);
    return std::make_tuple(translation, rotation, scale);
}

static void RegisterMatrix3x4(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KMatrix3x4"].setClass(UserdataMetatable<Matrix3x4>()
        .setConstructors<Matrix3x4(),
            Matrix3x4(const Matrix3x4&),
            Matrix3x4(const Matrix3&),
            Matrix3x4(const Matrix4&),
            Matrix3x4(float, float, float, float, float, float, float, float, float, float, float, float),
            Matrix3x4(const Vector3&, const Quaternion&, float),
            Matrix3x4(const Vector3&, const Quaternion&, const Vector3&)>()

        .addFunction("__eq", &Matrix3x4::operator==)

        .addOverloadedFunctions("__mul",
            static_cast<Vector3(Matrix3x4::*)(const Vector3&) const>(&Matrix3x4::operator*),
            static_cast<Vector3(Matrix3x4::*)(const Vector4&) const>(&Matrix3x4::operator*),
            static_cast<Matrix3x4(Matrix3x4::*)(float) const>(&Matrix3x4::operator*),
            static_cast<Matrix3x4(Matrix3x4::*)(const Matrix3x4&) const>(&Matrix3x4::operator*),
            static_cast<Matrix4(Matrix3x4::*)(const Matrix4&) const>(&Matrix3x4::operator*))

        .addFunction("__add", &Matrix3x4::operator+)
        .addFunction("__sub", &Matrix3x4::operator-)
        .addFunction("SetTranslation", &Matrix3x4::SetTranslation)
        .addFunction("SetRotation", &Matrix3x4::SetRotation)

        .addOverloadedFunctions("SetScale",
            static_cast<void(Matrix3x4::*)(const Vector3&)>(&Matrix3x4::SetScale),
            static_cast<void(Matrix3x4::*)(float)>(&Matrix3x4::SetScale))

        .addFunction("ToMatrix3", &Matrix3x4::ToMatrix3)
        .addFunction("ToMatrix4", &Matrix3x4::ToMatrix4)
        .addFunction("RotationMatrix", &Matrix3x4::RotationMatrix)
        .addFunction("Translation", &Matrix3x4::Translation)
        .addFunction("Rotation", &Matrix3x4::Rotation)
        .addFunction("Scale", &Matrix3x4::Scale)
        .addFunction("Equals", &Matrix3x4::Equals)
        
        .addStaticFunction("Decompose", &Matrix3x4Decompose)

        .addFunction("Inverse", &Matrix3x4::Inverse)
        .addFunction("ToString", &Matrix3x4::ToString)

        .addProperty("translation", &Matrix3x4::SetTranslation)
        .addProperty("rotation", &Matrix3x4::SetRotation)
        .addProperty("m00", &Matrix3x4::m00_)
        .addProperty("m01", &Matrix3x4::m01_)
        .addProperty("m02", &Matrix3x4::m02_)
        .addProperty("m03", &Matrix3x4::m03_)
        .addProperty("m10", &Matrix3x4::m10_)
        .addProperty("m11", &Matrix3x4::m11_)
        .addProperty("m12", &Matrix3x4::m12_)
        .addProperty("m13", &Matrix3x4::m13_)
        .addProperty("m20", &Matrix3x4::m20_)
        .addProperty("m21", &Matrix3x4::m21_)
        .addProperty("m22", &Matrix3x4::m22_)
        .addProperty("m23", &Matrix3x4::m23_)
        .addStaticField("ZERO", &Matrix3x4::ZERO)
        .addStaticField("IDENTITY", &Matrix3x4::IDENTITY)
    );
}

static std::tuple<Vector3, Quaternion, Vector3> Matrix4Decompose(const Matrix4& matrix4)
{
    Vector3 translation;
    Quaternion rotation;
    Vector3 scale;
    matrix4.Decompose(translation, rotation, scale);
    return std::make_tuple(translation, rotation, scale);
}

static void RegisterMatrix4(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KMatrix4"].setClass(UserdataMetatable<Matrix4>()
        .setConstructors<Matrix4(),
            Matrix4(const Matrix4&),
            Matrix4(const Matrix3&),
            Matrix4(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float)>()

        .addFunction("__eq", &Matrix4::operator==)

        .addOverloadedFunctions("__mul",
            static_cast<Vector3(Matrix4::*)(const Vector3&) const>(&Matrix4::operator*),
            static_cast<Vector4(Matrix4::*)(const Vector4&) const>(&Matrix4::operator*),
            static_cast<Matrix4(Matrix4::*)(float) const>(&Matrix4::operator*),
            static_cast<Matrix4(Matrix4::*)(const Matrix4&) const>(&Matrix4::operator*),
            static_cast<Matrix4(Matrix4::*)(const Matrix3x4&) const>(&Matrix4::operator*))

        .addFunction("__add", &Matrix4::operator+)
        .addFunction("__sub", &Matrix4::operator-)
        .addFunction("SetTranslation", &Matrix4::SetTranslation)
        .addFunction("SetRotation", &Matrix4::SetRotation)

        .addOverloadedFunctions("SetScale",
            static_cast<void(Matrix4::*)(const Vector3&)>(&Matrix4::SetScale),
            static_cast<void(Matrix4::*)(float)>(&Matrix4::SetScale))

        .addFunction("ToMatrix3", &Matrix4::ToMatrix3)
        .addFunction("RotationMatrix", &Matrix4::RotationMatrix)
        .addFunction("Translation", &Matrix4::Translation)
        .addFunction("Rotation", &Matrix4::Rotation)
        .addFunction("Scale", &Matrix4::Scale)
        .addFunction("Transpose", &Matrix4::Transpose)
        .addFunction("Equals", &Matrix4::Equals)
        
        .addStaticFunction("Decompose", Matrix4Decompose)

        .addFunction("Inverse", &Matrix4::Inverse)
        .addFunction("ToString", &Matrix4::ToString)

        .addProperty("translation", &Matrix4::SetTranslation)
        .addProperty("rotation", &Matrix4::SetRotation)
        .addProperty("m00", &Matrix4::m00_)
        .addProperty("m01", &Matrix4::m01_)
        .addProperty("m02", &Matrix4::m02_)
        .addProperty("m03", &Matrix4::m03_)
        .addProperty("m10", &Matrix4::m10_)
        .addProperty("m11", &Matrix4::m11_)
        .addProperty("m12", &Matrix4::m12_)
        .addProperty("m13", &Matrix4::m13_)
        .addProperty("m20", &Matrix4::m20_)
        .addProperty("m21", &Matrix4::m21_)
        .addProperty("m22", &Matrix4::m22_)
        .addProperty("m23", &Matrix4::m23_)
        .addProperty("m30", &Matrix4::m30_)
        .addProperty("m31", &Matrix4::m31_)
        .addProperty("m32", &Matrix4::m32_)
        .addProperty("m33", &Matrix4::m33_)
        .addStaticField("ZERO", &Matrix4::ZERO)
        .addStaticField("IDENTITY", &Matrix4::IDENTITY)
    );
}

static void RegisterPlane(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KPlane"].setClass(UserdataMetatable<Plane>()
        .setConstructors<Plane(),
            Plane(const Plane&),
            Plane(const Vector3&, const Vector3&, const Vector3&),
            Plane(const Vector3&, const Vector3&),
            Plane(const Vector4&)>()


        .addOverloadedFunctions("Define",
            static_cast<void(Plane::*)(const Vector3&, const Vector3&, const Vector3&)>(&Plane::Define),
            static_cast<void(Plane::*)(const Vector3&, const Vector3&)>(&Plane::Define),
            static_cast<void(Plane::*)(const Vector4&)>(&Plane::Define))


        .addOverloadedFunctions("Transform",
            static_cast<void(Plane::*)(const Matrix3&)>(&Plane::Transform),
            static_cast<void(Plane::*)(const Matrix3x4&)>(&Plane::Transform),
            static_cast<void(Plane::*)(const Matrix4&)>(&Plane::Transform))

        .addFunction("Project", &Plane::Project)
        .addFunction("Distance", &Plane::Distance)
        .addFunction("Reflect", &Plane::Reflect)
        .addFunction("ReflectionMatrix", &Plane::ReflectionMatrix)

        .addOverloadedFunctions("Transformed",
            static_cast<Plane(Plane::*)(const Matrix3&) const>(&Plane::Transformed),
            static_cast<Plane(Plane::*)(const Matrix3x4&) const>(&Plane::Transformed),
            static_cast<Plane(Plane::*)(const Matrix4&) const>(&Plane::Transformed))

        .addFunction("ToVector4", &Plane::ToVector4)
        .addProperty("normal", &Plane::normal_)
        .addProperty("absNormal", &Plane::absNormal_)
        .addProperty("d", &Plane::d_)
        .addStaticField("UP", &Plane::UP)
    );
}

static void RegisterPolyhedron(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KPolyhedron"].setClass(UserdataMetatable<Polyhedron>()
        .setConstructors<Polyhedron(),
            Polyhedron(const Polyhedron&),
            Polyhedron(const Vector<PODVector<Vector3> >&),
            Polyhedron(const BoundingBox&),
            Polyhedron(const Frustum&)>()


        .addOverloadedFunctions("Define",
            static_cast<void(Polyhedron::*)(const BoundingBox&)>(&Polyhedron::Define),
            static_cast<void(Polyhedron::*)(const Frustum&)>(&Polyhedron::Define))


        .addOverloadedFunctions("AddFace",
            static_cast<void(Polyhedron::*)(const Vector3&, const Vector3&, const Vector3&)>(&Polyhedron::AddFace),
            static_cast<void(Polyhedron::*)(const Vector3&, const Vector3&, const Vector3&, const Vector3&)>(&Polyhedron::AddFace),
            static_cast<void(Polyhedron::*)(const PODVector<Vector3>&)>(&Polyhedron::AddFace))


        .addOverloadedFunctions("Clip",
            static_cast<void(Polyhedron::*)(const Plane&)>(&Polyhedron::Clip),
            static_cast<void(Polyhedron::*)(const BoundingBox&)>(&Polyhedron::Clip),
            static_cast<void(Polyhedron::*)(const Frustum&)>(&Polyhedron::Clip))

        .addFunction("Clear", &Polyhedron::Clear)

        .addOverloadedFunctions("Transform",
            static_cast<void(Polyhedron::*)(const Matrix3&)>(&Polyhedron::Transform),
            static_cast<void(Polyhedron::*)(const Matrix3x4&)>(&Polyhedron::Transform))


        .addOverloadedFunctions("Transformed",
            static_cast<Polyhedron(Polyhedron::*)(const Matrix3&) const>(&Polyhedron::Transformed),
            static_cast<Polyhedron(Polyhedron::*)(const Matrix3x4&) const>(&Polyhedron::Transformed))

        .addFunction("Empty", &Polyhedron::Empty)
        .addProperty("faces", &Polyhedron::faces_)
    );
}

static void RegisterQuaternion(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KQuaternion"].setClass(UserdataMetatable<Quaternion>()
        .setConstructors<Quaternion(),
            Quaternion(const Quaternion&),
            Quaternion(float, float, float, float),
            Quaternion(float, const Vector3&),
            Quaternion(float),
            Quaternion(float, float, float),
            Quaternion(const Vector3&, const Vector3&),
            Quaternion(const Vector3&, const Vector3&, const Vector3&),
            Quaternion(const Matrix3&)>()

        .addFunction("__eq", &Quaternion::operator==)

        .addOverloadedFunctions("__mul",
            static_cast<Quaternion(Quaternion::*)(float) const>(&Quaternion::operator*),
            static_cast<Quaternion(Quaternion::*)(const Quaternion&) const>(&Quaternion::operator*),
            static_cast<Vector3(Quaternion::*)(const Vector3&) const>(&Quaternion::operator*))


        .addOverloadedFunctions("__sub",
            static_cast<Quaternion(Quaternion::*)() const>(&Quaternion::operator-),
            static_cast<Quaternion(Quaternion::*)(const Quaternion&) const>(&Quaternion::operator-))

        .addFunction("__add", &Quaternion::operator+)
        .addFunction("FromAngleAxis", &Quaternion::FromAngleAxis)
        .addFunction("FromEulerAngles", &Quaternion::FromEulerAngles)
        .addFunction("FromRotationTo", &Quaternion::FromRotationTo)
        .addFunction("FromAxes", &Quaternion::FromAxes)
        .addFunction("FromRotationMatrix", &Quaternion::FromRotationMatrix)
        .addFunction("FromLookRotation", &Quaternion::FromLookRotation)
        .addFunction("Normalize", &Quaternion::Normalize)
        .addFunction("Normalized", &Quaternion::Normalized)
        .addFunction("Inverse", &Quaternion::Inverse)
        .addFunction("LengthSquared", &Quaternion::LengthSquared)
        .addFunction("DotProduct", &Quaternion::DotProduct)
        .addFunction("Equals", &Quaternion::Equals)
        .addFunction("IsNaN", &Quaternion::IsNaN)
        .addFunction("Conjugate", &Quaternion::Conjugate)
        .addFunction("EulerAngles", &Quaternion::EulerAngles)
        .addFunction("YawAngle", &Quaternion::YawAngle)
        .addFunction("PitchAngle", &Quaternion::PitchAngle)
        .addFunction("RollAngle", &Quaternion::RollAngle)
        .addFunction("RotationMatrix", &Quaternion::RotationMatrix)
        .addFunction("Slerp", &Quaternion::Slerp)
        .addFunction("Nlerp", &Quaternion::Nlerp)
        .addFunction("ToString", &Quaternion::ToString)

        .addProperty("naN", &Quaternion::IsNaN)
        .addProperty("w", &Quaternion::w_)
        .addProperty("x", &Quaternion::x_)
        .addProperty("y", &Quaternion::y_)
        .addProperty("z", &Quaternion::z_)
        .addStaticField("IDENTITY", &Quaternion::IDENTITY)
    );
}

static void RegisterRandom(kaguya::State& lua)
{
    using namespace kaguya;

}

static void RegisterRay(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KRay"].setClass(UserdataMetatable<Ray>()
        .setConstructors<Ray(),
            Ray(const Vector3&, const Vector3&),
            Ray(const Ray&)>()

        .addFunction("__eq", &Ray::operator==)
        .addFunction("Define", &Ray::Define)
        .addFunction("Project", &Ray::Project)
        .addFunction("Distance", &Ray::Distance)
        .addFunction("ClosestPoint", &Ray::ClosestPoint)

        .addOverloadedFunctions("HitDistance",
            static_cast<float(Ray::*)(const Plane&) const>(&Ray::HitDistance),
            static_cast<float(Ray::*)(const BoundingBox&) const>(&Ray::HitDistance),
            static_cast<float(Ray::*)(const Frustum&, bool) const>(&Ray::HitDistance),
            static_cast<float(Ray::*)(const Sphere&) const>(&Ray::HitDistance),
            static_cast<float(Ray::*)(const Vector3&, const Vector3&, const Vector3&, Vector3*, Vector3*) const>(&Ray::HitDistance),
            static_cast<float(Ray::*)(const void*, unsigned int, unsigned int, unsigned int, Vector3*, Vector2*, unsigned int) const>(&Ray::HitDistance),
            static_cast<float(Ray::*)(const void*, unsigned int, const void*, unsigned int, unsigned int, unsigned int, Vector3*, Vector2*, unsigned int) const>(&Ray::HitDistance))


        .addOverloadedFunctions("InsideGeometry",
            static_cast<bool(Ray::*)(const void*, unsigned int, unsigned int, unsigned int) const>(&Ray::InsideGeometry),
            static_cast<bool(Ray::*)(const void*, unsigned int, const void*, unsigned int, unsigned int, unsigned int) const>(&Ray::InsideGeometry))

        .addFunction("Transformed", &Ray::Transformed)
        .addProperty("origin", &Ray::origin_)
        .addProperty("direction", &Ray::direction_)
    );
}

static void RegisterRect(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KRect"].setClass(UserdataMetatable<Rect>()
        .setConstructors<Rect(),
            Rect(const Vector2&, const Vector2&),
            Rect(float, float, float, float),
            Rect(const Vector4&),
            Rect(const Rect&)>()

        .addFunction("__eq", &Rect::operator==)

        .addOverloadedFunctions("Define",
            static_cast<void(Rect::*)(const Rect&)>(&Rect::Define),
            static_cast<void(Rect::*)(const Vector2&, const Vector2&)>(&Rect::Define),
            static_cast<void(Rect::*)(const Vector2&)>(&Rect::Define))


        .addOverloadedFunctions("Merge",
            static_cast<void(Rect::*)(const Vector2&)>(&Rect::Merge),
            static_cast<void(Rect::*)(const Rect&)>(&Rect::Merge))

        .addFunction("Clear", &Rect::Clear)
        .addFunction("Clip", &Rect::Clip)
        .addFunction("Defined", &Rect::Defined)
        .addFunction("Center", &Rect::Center)
        .addFunction("Size", &Rect::Size)
        .addFunction("HalfSize", &Rect::HalfSize)
        .addFunction("Equals", &Rect::Equals)
        .addFunction("IsInside", &Rect::IsInside)
        .addFunction("ToVector4", &Rect::ToVector4)
        .addFunction("ToString", &Rect::ToString)
        .addProperty("min", &Rect::min_)
        .addProperty("max", &Rect::max_)
        .addStaticField("FULL", &Rect::FULL)
        .addStaticField("POSITIVE", &Rect::POSITIVE)
        .addStaticField("ZERO", &Rect::ZERO)
    );
    lua["KIntRect"].setClass(UserdataMetatable<IntRect>()
        .setConstructors<IntRect(),
            IntRect(int, int, int, int),
            IntRect(const int*)>()

        .addFunction("__eq", &IntRect::operator==)
        .addFunction("Size", &IntRect::Size)
        .addFunction("Width", &IntRect::Width)
        .addFunction("Height", &IntRect::Height)
        .addFunction("IsInside", &IntRect::IsInside)
        .addFunction("ToString", &IntRect::ToString)
        .addProperty("left", &IntRect::left_)
        .addProperty("top", &IntRect::top_)
        .addProperty("right", &IntRect::right_)
        .addProperty("bottom", &IntRect::bottom_)
        .addStaticField("ZERO", &IntRect::ZERO)
    );
}

static void RegisterSphere(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KSphere"].setClass(UserdataMetatable<Sphere>()
        .setConstructors<Sphere(),
            Sphere(const Sphere&),
            Sphere(const Vector3&, float),
            Sphere(const Vector3*, unsigned int),
            Sphere(const BoundingBox&),
            Sphere(const Frustum&),
            Sphere(const Polyhedron&)>()

        .addFunction("__eq", &Sphere::operator==)

        .addOverloadedFunctions("Define",
            static_cast<void(Sphere::*)(const Sphere&)>(&Sphere::Define),
            static_cast<void(Sphere::*)(const Vector3&, float)>(&Sphere::Define),
            static_cast<void(Sphere::*)(const Vector3*, unsigned int)>(&Sphere::Define),
            static_cast<void(Sphere::*)(const BoundingBox&)>(&Sphere::Define),
            static_cast<void(Sphere::*)(const Frustum&)>(&Sphere::Define),
            static_cast<void(Sphere::*)(const Polyhedron&)>(&Sphere::Define))


        .addOverloadedFunctions("Merge",
            static_cast<void(Sphere::*)(const Vector3&)>(&Sphere::Merge),
            static_cast<void(Sphere::*)(const Vector3*, unsigned int)>(&Sphere::Merge),
            static_cast<void(Sphere::*)(const BoundingBox&)>(&Sphere::Merge),
            static_cast<void(Sphere::*)(const Frustum&)>(&Sphere::Merge),
            static_cast<void(Sphere::*)(const Polyhedron&)>(&Sphere::Merge),
            static_cast<void(Sphere::*)(const Sphere&)>(&Sphere::Merge))

        .addFunction("Clear", &Sphere::Clear)
        .addFunction("Defined", &Sphere::Defined)

        .addOverloadedFunctions("IsInside",
            static_cast<Intersection(Sphere::*)(const Vector3&) const>(&Sphere::IsInside),
            static_cast<Intersection(Sphere::*)(const Sphere&) const>(&Sphere::IsInside),
            static_cast<Intersection(Sphere::*)(const BoundingBox&) const>(&Sphere::IsInside))


        .addOverloadedFunctions("IsInsideFast",
            static_cast<Intersection(Sphere::*)(const Sphere&) const>(&Sphere::IsInsideFast),
            static_cast<Intersection(Sphere::*)(const BoundingBox&) const>(&Sphere::IsInsideFast))

        .addFunction("Distance", &Sphere::Distance)
        .addProperty("center", &Sphere::center_)
        .addProperty("radius", &Sphere::radius_)
    );
}

static void RegisterStringHash(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KStringHash"].setClass(UserdataMetatable<StringHash>()
        .setConstructors<StringHash(),
            StringHash(const StringHash&),
            StringHash(unsigned int),
            StringHash(const char*),
            StringHash(const String&)>()

        .addFunction("__add", &StringHash::operator+)
        .addFunction("__eq", &StringHash::operator==)
        .addFunction("operator<", &StringHash::operator<)
        .addFunction("operator>", &StringHash::operator>)
        .addFunction("Value", &StringHash::Value)
        .addFunction("ToString", &StringHash::ToString)
        .addFunction("ToHash", &StringHash::ToHash)
        .addStaticFunction("Calculate", &StringHash::Calculate)
        .addStaticField("ZERO", &StringHash::ZERO)
    );
}

static void RegisterVector2(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KVector2"].setClass(UserdataMetatable<Vector2>()
        .setConstructors<Vector2(),
            Vector2(const Vector2&),
            Vector2(float, float)>()

        .addFunction("__eq", &Vector2::operator==)
        .addFunction("__add", &Vector2::operator+)

        .addOverloadedFunctions("__sub",
            static_cast<Vector2(Vector2::*)() const>(&Vector2::operator-),
            static_cast<Vector2(Vector2::*)(const Vector2&) const>(&Vector2::operator-))


        .addOverloadedFunctions("__mul",
            static_cast<Vector2(Vector2::*)(float) const>(&Vector2::operator*),
            static_cast<Vector2(Vector2::*)(const Vector2&) const>(&Vector2::operator*))


        .addOverloadedFunctions("__div",
            static_cast<Vector2(Vector2::*)(float) const>(&Vector2::operator/),
            static_cast<Vector2(Vector2::*)(const Vector2&) const>(&Vector2::operator/))

        .addFunction("Normalize", &Vector2::Normalize)
        .addFunction("Length", &Vector2::Length)
        .addFunction("LengthSquared", &Vector2::LengthSquared)
        .addFunction("DotProduct", &Vector2::DotProduct)
        .addFunction("AbsDotProduct", &Vector2::AbsDotProduct)
        .addFunction("Angle", &Vector2::Angle)
        .addFunction("Abs", &Vector2::Abs)
        .addFunction("Lerp", &Vector2::Lerp)
        .addFunction("Equals", &Vector2::Equals)
        .addFunction("IsNaN", &Vector2::IsNaN)
        .addFunction("Normalized", &Vector2::Normalized)
        .addFunction("ToString", &Vector2::ToString)

        .addProperty("naN", &Vector2::IsNaN)
        .addProperty("x", &Vector2::x_)
        .addProperty("y", &Vector2::y_)
        .addStaticField("ZERO", &Vector2::ZERO)
        .addStaticField("LEFT", &Vector2::LEFT)
        .addStaticField("RIGHT", &Vector2::RIGHT)
        .addStaticField("UP", &Vector2::UP)
        .addStaticField("DOWN", &Vector2::DOWN)
        .addStaticField("ONE", &Vector2::ONE)
    );
    lua["KIntVector2"].setClass(UserdataMetatable<IntVector2>()
        .setConstructors<IntVector2(),
            IntVector2(int, int),
            IntVector2(const int*),
            IntVector2(const IntVector2&)>()

        .addFunction("__eq", &IntVector2::operator==)
        .addFunction("__add", &IntVector2::operator+)

        .addOverloadedFunctions("__sub",
            static_cast<IntVector2(IntVector2::*)() const>(&IntVector2::operator-),
            static_cast<IntVector2(IntVector2::*)(const IntVector2&) const>(&IntVector2::operator-))

        .addFunction("__mul", &IntVector2::operator*)
        .addFunction("__div", &IntVector2::operator/)
        .addFunction("ToString", &IntVector2::ToString)
        .addProperty("x", &IntVector2::x_)
        .addProperty("y", &IntVector2::y_)
        .addStaticField("ZERO", &IntVector2::ZERO)
    );
}

static void RegisterVector3(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KVector3"].setClass(UserdataMetatable<Vector3>()
        .setConstructors<Vector3(),
            Vector3(const Vector3&),
            Vector3(const Vector2&, float),
            Vector3(const Vector2&),
            Vector3(float, float, float),
            Vector3(float, float)>()

        .addFunction("__eq", &Vector3::operator==)
        .addFunction("__add", &Vector3::operator+)

        .addOverloadedFunctions("__sub",
            static_cast<Vector3(Vector3::*)() const>(&Vector3::operator-),
            static_cast<Vector3(Vector3::*)(const Vector3&) const>(&Vector3::operator-))


        .addOverloadedFunctions("__mul",
            static_cast<Vector3(Vector3::*)(float) const>(&Vector3::operator*),
            static_cast<Vector3(Vector3::*)(const Vector3&) const>(&Vector3::operator*))


        .addOverloadedFunctions("__div",
            static_cast<Vector3(Vector3::*)(float) const>(&Vector3::operator/),
            static_cast<Vector3(Vector3::*)(const Vector3&) const>(&Vector3::operator/))

        .addFunction("Normalize", &Vector3::Normalize)
        .addFunction("Length", &Vector3::Length)
        .addFunction("LengthSquared", &Vector3::LengthSquared)
        .addFunction("DotProduct", &Vector3::DotProduct)
        .addFunction("AbsDotProduct", &Vector3::AbsDotProduct)
        .addFunction("CrossProduct", &Vector3::CrossProduct)
        .addFunction("Abs", &Vector3::Abs)
        .addFunction("Lerp", &Vector3::Lerp)
        .addFunction("Equals", &Vector3::Equals)
        .addFunction("Angle", &Vector3::Angle)
        .addFunction("IsNaN", &Vector3::IsNaN)
        .addFunction("Normalized", &Vector3::Normalized)
        .addFunction("ToString", &Vector3::ToString)

        .addProperty("naN", &Vector3::IsNaN)
        .addProperty("x", &Vector3::x_)
        .addProperty("y", &Vector3::y_)
        .addProperty("z", &Vector3::z_)
        .addStaticField("ZERO", &Vector3::ZERO)
        .addStaticField("LEFT", &Vector3::LEFT)
        .addStaticField("RIGHT", &Vector3::RIGHT)
        .addStaticField("UP", &Vector3::UP)
        .addStaticField("DOWN", &Vector3::DOWN)
        .addStaticField("FORWARD", &Vector3::FORWARD)
        .addStaticField("BACK", &Vector3::BACK)
        .addStaticField("ONE", &Vector3::ONE)
    );
}

static void RegisterVector4(kaguya::State& lua)
{
    using namespace kaguya;

    lua["KVector4"].setClass(UserdataMetatable<Vector4>()
        .setConstructors<Vector4(),
            Vector4(const Vector4&),
            Vector4(const Vector3&, float),
            Vector4(float, float, float, float)>()

        .addFunction("__eq", &Vector4::operator==)
        .addFunction("__add", &Vector4::operator+)

        .addOverloadedFunctions("__sub",
            static_cast<Vector4(Vector4::*)() const>(&Vector4::operator-),
            static_cast<Vector4(Vector4::*)(const Vector4&) const>(&Vector4::operator-))


        .addOverloadedFunctions("__mul",
            static_cast<Vector4(Vector4::*)(float) const>(&Vector4::operator*),
            static_cast<Vector4(Vector4::*)(const Vector4&) const>(&Vector4::operator*))


        .addOverloadedFunctions("__div",
            static_cast<Vector4(Vector4::*)(float) const>(&Vector4::operator/),
            static_cast<Vector4(Vector4::*)(const Vector4&) const>(&Vector4::operator/))

        .addFunction("DotProduct", &Vector4::DotProduct)
        .addFunction("AbsDotProduct", &Vector4::AbsDotProduct)
        .addFunction("Abs", &Vector4::Abs)
        .addFunction("Lerp", &Vector4::Lerp)
        .addFunction("Equals", &Vector4::Equals)
        .addFunction("IsNaN", &Vector4::IsNaN)
        .addFunction("ToString", &Vector4::ToString)

        .addProperty("naN", &Vector4::IsNaN)
        .addProperty("x", &Vector4::x_)
        .addProperty("y", &Vector4::y_)
        .addProperty("z", &Vector4::z_)
        .addProperty("w", &Vector4::w_)
        .addStaticField("ZERO", &Vector4::ZERO)
        .addStaticField("ONE", &Vector4::ONE)
    );
}

void RegisterMathLuaAPI(kaguya::State& lua)
{
    RegisterAreaAllocator(lua);
    RegisterBoundingBox(lua);
    RegisterColor(lua);
    RegisterFrustum(lua);
    RegisterMathDefs(lua);
    RegisterMatrix2(lua);
    RegisterMatrix3(lua);
    RegisterMatrix3x4(lua);
    RegisterMatrix4(lua);
    RegisterPlane(lua);
    RegisterPolyhedron(lua);
    RegisterQuaternion(lua);
    RegisterRandom(lua);
    RegisterRay(lua);
    RegisterRect(lua);
    RegisterSphere(lua);
    RegisterStringHash(lua);
    RegisterVector2(lua);
    RegisterVector3(lua);
    RegisterVector4(lua);
}
}
