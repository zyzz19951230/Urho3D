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

#include "../../UI/Font.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterFont(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Font : Resource
    lua["Font"].setClass(UserdataMetatable<Font, Resource>()
        // [Constructor] Font()
        .addStaticFunction("new", &CreateObject<Font>)

        // [Method] void SetAbsoluteGlyphOffset(const IntVector2& offset)
        .addFunction("SetAbsoluteGlyphOffset", &Font::SetAbsoluteGlyphOffset)
        // [Method] void SetScaledGlyphOffset(const Vector2& offset)
        .addFunction("SetScaledGlyphOffset", &Font::SetScaledGlyphOffset)

        // [Method] bool IsSDFFont() const
        .addFunction("IsSDFFont", &Font::IsSDFFont)
        // [Method] const IntVector2& GetAbsoluteGlyphOffset() const
        .addFunction("GetAbsoluteGlyphOffset", &Font::GetAbsoluteGlyphOffset)
        // [Method] const Vector2& GetScaledGlyphOffset() const
        .addFunction("GetScaledGlyphOffset", &Font::GetScaledGlyphOffset)
        // [Method] IntVector2 GetTotalGlyphOffset(int pointSize) const
        .addFunction("GetTotalGlyphOffset", &Font::GetTotalGlyphOffset)

        // [Property(Readonly)] bool sdfFont
        .addProperty("sdfFont", &Font::IsSDFFont)
        // [Property] const IntVector2& absoluteGlyphOffset
        .addProperty("absoluteGlyphOffset", &Font::GetAbsoluteGlyphOffset, &Font::SetAbsoluteGlyphOffset)
        // [Property] const Vector2& scaledGlyphOffset
        .addProperty("scaledGlyphOffset", &Font::GetScaledGlyphOffset, &Font::SetScaledGlyphOffset)
        );
}
}

