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

#include "../../Math/Color.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(ColorFromHSL, Color, FromHSL, 3, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(ColorFromHSV, Color, FromHSV, 3, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(ColorClip, Color, Clip, 0, 1);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(ColorInvert, Color, Invert, 0, 1);

void RegisterColor(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Color
    lua["Color"].setClass(UserdataMetatable<Color>()
        // [Constructor] Color()
        .setConstructors<Color(),
        // [Constructor] Color(const Color& color)
        Color(const Color&),
        // [Constructor] Color(const Color& color, float a)
        Color(const Color&, float),
        // [Constructor] Color(float r, float g, float b)
        Color(float, float, float),
        // [Constructor] Color(float r, float g, float b, float a)
        Color(float, float, float, float)>()

        // [Method] bool operator==(const Color& rhs)
        .addFunction("__eq", &Color::operator==)
        // [Method] Color operator*(float rhs) const
        .addFunction("__mul", &Color::operator*)
        // [Method] Color operator+(const Color& rhs)
        .addFunction("__add", &Color::operator+)

        // [Method] unsigned ToUInt() const
        .addFunction("ToUInt", &Color::ToUInt)
        // [Method] Vector3 ToHSL() const
        .addFunction("ToHSL", &Color::ToHSL)
        // [Method] Vector3 ToHSV() const
        .addFunction("ToHSV", &Color::ToHSV)

        // [Method] void FromHSL(float h, float s, float l, float a = 1.0f)
        .addFunction("FromHSL", ColorFromHSL())
        // [Method] void FromHSV(float h, float s, float v, float a = 1.0f)
        .addFunction("FromHSV", ColorFromHSV())

        // [Method] Vector3 ToVector3() const
        .addFunction("ToVector3", &Color::ToVector3)
        // [Method] Vector4 ToVector4() const
        .addFunction("ToVector4", &Color::ToVector4)

        // [Method] float SumRGB() const
        .addFunction("SumRGB", &Color::SumRGB)
        // [Method] float Average() const
        .addFunction("Average", &Color::Average)

        // [Method] float Luma() const
        .addFunction("Luma", &Color::Luma)
        // [Method] float Chroma() const
        .addFunction("Chroma", &Color::Chroma)
        // [Method] float Hue() const
        .addFunction("Hue", static_cast<float(Color::*)() const>(&Color::Hue))
        // [Method] float SaturationHSL() const
        .addFunction("SaturationHSL", static_cast<float(Color::*)() const>(&Color::SaturationHSL))
        // [Method] float SaturationHSV() const
        .addFunction("SaturationHSV", static_cast<float(Color::*)() const>(&Color::SaturationHSV))
        // [Method] float Value() const
        .addFunction("Value", &Color::Value)
        // [Method] float Lightness() const
        .addFunction("Lightness", &Color::Lightness)

        // [Method] float Value() const
        .addFunction("MaxRGB", &Color::MaxRGB)
        // [Method] float MinRGB() const
        .addFunction("MinRGB", &Color::MinRGB)
        // [Method] float Range() const
        .addFunction("Range", &Color::Range)

        // [Method] void Clip(bool clipAlpha = false)
        .addFunction("Clip", ColorClip())
        // [Method] void Invert(bool invertAlpha = false)
        .addFunction("Invert", ColorInvert())

        // [Method] Color Lerp(const Color& rhs, float t) const
        .addFunction("Lerp", &Color::Lerp)
        // [Method] Color Abs() const
        .addFunction("Abs", &Color::Abs)
        // [Method] bool Equals(const Color& rhs) const
        .addFunction("Equals", &Color::Equals)

        // [Method] String ToString() const
        .addFunction("ToString", &Color::ToString)

        // [Field] float r
        .addProperty("r", &Color::r_)
        // [Field] float g
        .addProperty("g", &Color::g_)
        // [Field] float b
        .addProperty("b", &Color::b_)
        // [Field] float a
        .addProperty("a", &Color::a_)

        // [StaticConstant] Color WHITE
        .addStaticField("WHITE", &Color::WHITE)
        // [StaticConstant] Color GRAY
        .addStaticField("GRAY", &Color::GRAY)
        // [StaticConstant] Color BLACK
        .addStaticField("BLACK", &Color::BLACK)
        // [StaticConstant] Color RED
        .addStaticField("RED", &Color::RED)
        // [StaticConstant] Color GREEN
        .addStaticField("GREEN", &Color::GREEN)
        // [StaticConstant] Color BLUE
        .addStaticField("BLUE", &Color::BLUE)
        // [StaticConstant] Color CYAN
        .addStaticField("CYAN", &Color::CYAN)
        // [StaticConstant] Color MAGENTA
        .addStaticField("MAGENTA", &Color::MAGENTA)
        // [StaticConstant] Color YELLOW
        .addStaticField("YELLOW", &Color::YELLOW)
        // [StaticConstant] Color TRANSPARENT
        .addStaticField("TRANSPARENT", &Color::TRANSPARENT)
        );
}
}

