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

    // [Class] Rect
    lua["Rect"].setClass(UserdataMetatable<Rect>()
        // [Constructor] Rect()
        .setConstructors<Rect(),
        // [Constructor] Rect(const Vector2& min, const Vector2& max)
        Rect(const Vector2&, const Vector2&),
        // [Constructor] Rect(float left, float top, float right, float bottom)
        Rect(float, float, float, float),
        // [Constructor] Rect(const Vector4& vector)
        Rect(const Vector4&),
        // [Constructor] Rect(const Rect& rect)
        Rect(const Rect&)>()

        // [Method] bool operator==(const Rect& rhs) const
        .addFunction("__eq", &Rect::operator==)

        .addOverloadedFunctions("Define",
            // [Method] void Define(const Rect& rect)
            static_cast<void(Rect::*)(const Rect&)>(&Rect::Define),
            // [Method] void Define(const Vector2& min, const Vector2& max)
            static_cast<void(Rect::*)(const Vector2&, const Vector2&)>(&Rect::Define),
            // [Method] void Define(const Vector2& point)
            static_cast<void(Rect::*)(const Vector2&)>(&Rect::Define))

        .addOverloadedFunctions("Merge",
            // [Method] void Merge(const Vector2& point)
            static_cast<void(Rect::*)(const Vector2&)>(&Rect::Merge),
            // [Method] void Merge(const Rect& rect)
            static_cast<void(Rect::*)(const Rect&)>(&Rect::Merge))

        // [Method] void Clear()
        .addFunction("Clear", &Rect::Clear)
        // [Method] void Clip(const Rect& rect)
        .addFunction("Clip", &Rect::Clip)

        // [Method] bool Defined() const
        .addFunction("Defined", &Rect::Defined)
        // [Method] Vector2 Center() const
        .addFunction("Center", &Rect::Center)
        // [Method] Vector2 Size() const
        .addFunction("Size", &Rect::Size)
        // [Method] Vector2 HalfSize() const
        .addFunction("HalfSize", &Rect::HalfSize)
        // [Method] bool Equals(const Rect& rhs) const
        .addFunction("Equals", &Rect::Equals)
        // [Method] Intersection IsInside(const Vector2& point) const
        .addFunction("IsInside", &Rect::IsInside)
        // [Method] Vector4 ToVector4() const
        .addFunction("ToVector4", &Rect::ToVector4)

        // [Method] String ToString() const
        .addFunction("ToString", &Rect::ToString)

        // [Field] Vector3 min
        .addProperty("min", &Rect::min_)
        // [Field] Vector3 max
        .addProperty("max", &Rect::max_)

        // [Property(Readonly)] Vector2 center
        .addProperty("center", &Rect::Center)
        // [Property(Readonly)] Vector2 size
        .addProperty("size", &Rect::Size)
        // [Property(Readonly)] Vector2 halfSize
        .addProperty("halfSize", &Rect::HalfSize)

        // [StaticConstant] Rect FULL
         .addStaticField("FULL", &Rect::FULL)
        // [StaticConstant] Rect POSITIVE
         .addStaticField("POSITIVE", &Rect::POSITIVE)
        // [StaticConstant] Rect ZERO
         .addStaticField("ZERO", &Rect::ZERO)
        );

    // [Class] IntRect
    lua["IntRect"].setClass(UserdataMetatable<IntRect>()
        // [Constructor] IntRect()
        .setConstructors<IntRect(),
        // [Constructor] IntRect(int left, int top, int right, int bottom)
        IntRect(int, int, int, int)>()

        // [Method] bool operator==(const IntRect& rhs) const
        .addFunction("__eq", &IntRect::operator==)

        // [Method] Vector2 Size() const
        .addFunction("Size", &IntRect::Size)
        // [Method] int Width() const
        .addFunction("Width", &IntRect::Width)
        // [Method] IntVector2 Size() const
        .addFunction("Height", &IntRect::Height)
        // [Method] Intersection IsInside(const Vector2& point) const
        .addFunction("IsInside", &IntRect::IsInside)

        // [Method] String ToString() const
        .addFunction("ToString", &IntRect::ToString)

        // [Field] float left
        .addProperty("left", &IntRect::left_)
        // [Field] float top
        .addProperty("top", &IntRect::top_)
        // [Field] float right
        .addProperty("right", &IntRect::right_)
        // [Field] float bottom
        .addProperty("bottom", &IntRect::bottom_)

        // [Property(Readonly)] Vector2 size
        .addProperty("size", &IntRect::Size)
        // [Property(Readonly)] int width
        .addProperty("width", &IntRect::Width)
        // [Property(Readonly)] IntVector2 Size() cons height
        .addProperty("height", &IntRect::Height)

        // [StaticConstant] IntRect ZERO
        .addStaticField("ZERO", &IntRect::ZERO)
        );
}
}

