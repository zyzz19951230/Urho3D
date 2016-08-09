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
        .setConstructors<Color(),
        Color(const Color&),
        Color(const Color&, float),
        Color(float, float, float),
        Color(float, float, float, float)>()

        .addFunction("__eq", &Color::operator==)
        .addFunction("__mul", &Color::operator*)
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
}

