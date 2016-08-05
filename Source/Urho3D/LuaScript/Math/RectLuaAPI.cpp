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

#include "../../Math/Rect.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterRect(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Rect"].setClass(UserdataMetatable<Rect>()
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

        .addProperty("center", &Rect::Center)
        .addProperty("size", &Rect::Size)
        .addProperty("halfSize", &Rect::HalfSize)

        .addStaticField("FULL", &Rect::FULL)
        .addStaticField("POSITIVE", &Rect::POSITIVE)
        .addStaticField("ZERO", &Rect::ZERO)
        );

    lua["IntRect"].setClass(UserdataMetatable<IntRect>()
        .setConstructors<IntRect(),
        IntRect(int, int, int, int)>()

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

        .addProperty("size", &IntRect::Size)
        .addProperty("width", &IntRect::Width)
        .addProperty("height", &IntRect::Height)

        .addStaticField("ZERO", &IntRect::ZERO)
        );
}
}

