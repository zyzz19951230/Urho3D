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

    lua["Color"].setClass(UserdataMetatable<Color>()
        .setConstructors<Color(),
        Color(const Color&),
        Color(const Color&, float),
        Color(float, float, float),
        Color(float, float, float, float)>()

        .addFunction("__eq", &Color::operator==)
        .addFunction("__mul", &Color::operator*)
        .addFunction("__add", &Color::operator+)

        .addFunction("ToUInt", &Color::ToUInt)
        .addFunction("ToHSL", &Color::ToHSL)
        .addFunction("ToHSV", &Color::ToHSV)

        .addFunction("FromHSL", ColorFromHSL())
        .addFunction("FromHSV", ColorFromHSV())

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

        .addFunction("MaxRGB", &Color::MaxRGB)
        .addFunction("MinRGB", &Color::MinRGB)
        .addFunction("Range", &Color::Range)

        .addFunction("Clip", ColorClip())
        .addFunction("Invert", ColorInvert())

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
}

