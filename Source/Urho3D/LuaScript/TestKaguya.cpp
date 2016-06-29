#include "../Math/Vector3.h"
#include "../Resource/Image.h"

#include <kaguya.hpp>

namespace Urho3D
{

extern Context* globalContext;

static void RegisterVector3(kaguya::State& lua)
{
	using namespace kaguya;

	lua["KVector3"].setClass(kaguya::UserdataMetatable<Vector3>()
		.setConstructors<Vector3(), Vector3(const Vector3&), Vector3(const Vector2&, float), Vector3(const Vector2&), Vector3(float, float, float), Vector3(float, float)>()
		
		.addFunction("__eq", &Vector3::operator==)
		.addFunction("__add", &Vector3::operator+)
		
		.addOverloadedFunctions("__sub", 
			static_cast<Vector3(Vector3::*)() const>(&Vector3::operator-), 
			static_cast<Vector3(Vector3::*)(const Vector3&) const>(&Vector3::operator-))

		.addOverloadedFunctions("__mul", 
			static_cast<Vector3(Vector3::*)(float) const>(&Vector3::operator*), 
			static_cast<Vector3(Vector3::*)(const Vector3&) const>(&Vector3::operator*))

		.addOverloadedFunctions("__div", 
			static_cast<Vector3(Vector3::*)(float) const>(&Vector3::operator*), 
			static_cast<Vector3(Vector3::*)(const Vector3&) const>(&Vector3::operator*))

		.addFunction("Normalize", &Vector3::Normalize)
		.addFunction("Length", &Vector3::Length)
		.addFunction("LengthSquared", &Vector3::LengthSquared)
		.addFunction("DotProduct", &Vector3::DotProduct)
		.addFunction("AbsDotProduct", &Vector3::AbsDotProduct)
		.addFunction("CrossProduct", &Vector3::CrossProduct)
		
		.addFunction("Abs", &Vector3::Abs)
		.addFunction("Lerp", &Vector3::Lerp)
		.addFunction("Equals", &Vector3::Equals)
		.addFunction("IsNaN", &Vector3::IsNaN)
		.addFunction("Angle", &Vector3::Angle)
		.addFunction("Normalized", &Vector3::Normalized)
		.addFunction("ToString", &Vector3::ToString)

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

template<typename TObject>
TObject* KaguyaCreateObject()
{
	TObject* object = new TObject(globalContext);
	object->AddRef();
	return object;
}

template<typename TObject>
void KaguyaDestroyObject(TObject* object)
{
	if (object)
		object->ReleaseRef();
}

static void RegisterImage(kaguya::State& lua)
{
	using namespace kaguya;

	lua["KImage"].setClass(kaguya::UserdataMetatable<Image>(false)
		.addStaticFunction("new", &KaguyaCreateObject<Image>)
		.addStaticFunction("__gc", &KaguyaDestroyObject<Image>)
		.addFunction("SetSize", static_cast<bool(Image::*)(int, int, unsigned)>(&Image::SetSize))
		);
}

void KaguyaRegisterLuaAPI(lua_State* state)
{
	kaguya::State lua(state);

	RegisterVector3(lua);
	RegisterImage(lua);
}

}
