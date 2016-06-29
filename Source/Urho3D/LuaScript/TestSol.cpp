#include "../Math/Vector3.h"
#include "../Resource/Image.h"

#include <sol.hpp>

namespace Urho3D
{
extern Context* globalContext;

static void RegisterVector3(sol::state_view& lua)
{
	using namespace sol;

	lua.new_usertype<Vector3>("SVector3", 
		constructors<types<>,
		types<const Vector3&>,
		types<const Vector2&, float>,
		types<const Vector2&>,
		types<float, float, float>,
		types<float, float >>(),

		meta_function::equal_to, &Vector3::operator==,
		meta_function::addition, &Vector3::operator+,

		meta_function::subtraction, overload(
			resolve<Vector3() const, Vector3>(&Vector3::operator-),
			resolve<Vector3(const Vector3& rhs) const, Vector3>(&Vector3::operator-)),

		meta_function::multiplication, overload(
			resolve<Vector3(float rhs) const, Vector3>(&Vector3::operator*),
			resolve<Vector3(const Vector3& rhs) const, Vector3>(&Vector3::operator*)),

		meta_function::division, overload(
			resolve<Vector3(float rhs) const, Vector3>(&Vector3::operator/),
			resolve<Vector3(const Vector3& rhs) const, Vector3>(&Vector3::operator/)),

		"Normalize", &Vector3::Normalize,
		"Length", &Vector3::Length,
		"LengthSquared", &Vector3::LengthSquared,
		"DotProduct", &Vector3::DotProduct,
		"AbsDotProduct", &Vector3::AbsDotProduct,
		"CrossProduct", &Vector3::CrossProduct,

		"Abs", &Vector3::Abs,
		"Lerp", &Vector3::Lerp,
		"Equals", &Vector3::Equals,
		"Angle", &Vector3::Angle,
		"IsNaN", &Vector3::IsNaN,
		"Normalized", &Vector3::Normalized,
		"Data", &Vector3::Data,
		"ToString", &Vector3::ToString,

		"x", &Vector3::x_,
		"y", &Vector3::y_,
		"z", &Vector3::z_);

	table table = lua["SVector3"];

	table.set("ZERO", &Vector3::ZERO);
	table.set("LEFT", &Vector3::LEFT);
	table.set("RIGHT", &Vector3::RIGHT);
	table.set("UP", &Vector3::UP);
	table.set("DOWN", &Vector3::DOWN);
	table.set("FORWARD", &Vector3::FORWARD);
	table.set("BACK", &Vector3::BACK);
	table.set("ONE", &Vector3::ONE);
}

template<typename TObject>
void SolCreateObject(TObject* object)
{
	new (object)TObject(globalContext);
}

template<typename TObject>
void SolDestroyObject(TObject* object)
{
	// Call destructor only
	if (object)
		object->~TObject();
}

static void RegisterImage(sol::state_view& lua)
{
	using namespace sol;

	lua.new_usertype<Image>("SImage",
		"new", initializers(SolCreateObject<Image>),
		"__gc", destructor(&SolDestroyObject<Image>),
		"SetSize", resolve<bool(int, int, unsigned), Image>(&Image::SetSize)
		);
}

void SolRegisterLuaAPI(lua_State* state)
{
	sol::state_view lua(state);

	RegisterVector3(lua);
	RegisterImage(lua);
}
}
