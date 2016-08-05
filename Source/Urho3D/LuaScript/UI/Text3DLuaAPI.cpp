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

#include "../../Graphics/Material.h"
#include "../../Resource/Image.h"
#include "../../UI/Font.h"
#include "../../UI/Text3D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(Text3DSetFont0, Text3D, SetFont, 1, 2, bool(Text3D::*)(const String&, int));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(Text3DSetFont1, Text3D, SetFont, 1, 2, bool(Text3D::*)(Font*, int));

static void Text3DSetColor(Text3D* self, const Color& color)
{
    self->SetColor(color);
}

static const Color& Text3DGetColor(const Text3D* self)
{
    return self->GetColor(C_TOPLEFT);
}

void RegisterText3D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Text3D"].setClass(UserdataMetatable<Text3D, Drawable>()
        .addStaticFunction("new", &CreateObject<Text3D>)

        .addOverloadedFunctions("SetFont", Text3DSetFont0(), Text3DSetFont1())

        .addFunction("SetMaterial", &Text3D::SetMaterial)
        .addFunction("SetText", &Text3D::SetText)
        .addFunction("SetAlignment", &Text3D::SetAlignment)
        .addFunction("SetHorizontalAlignment", &Text3D::SetHorizontalAlignment)
        .addFunction("SetVerticalAlignment", &Text3D::SetVerticalAlignment)
        .addFunction("SetTextAlignment", &Text3D::SetTextAlignment)
        .addFunction("SetRowSpacing", &Text3D::SetRowSpacing)
        .addFunction("SetWordwrap", &Text3D::SetWordwrap)
        .addFunction("SetTextEffect", &Text3D::SetTextEffect)
        .addFunction("SetEffectShadowOffset", &Text3D::SetEffectShadowOffset)
        .addFunction("SetEffectStrokeThickness", &Text3D::SetEffectStrokeThickness)
        .addFunction("SetEffectRoundStroke", &Text3D::SetEffectRoundStroke)
        .addFunction("SetEffectColor", &Text3D::SetEffectColor)
        .addFunction("SetEffectDepthBias", &Text3D::SetEffectDepthBias)
        .addFunction("SetWidth", &Text3D::SetWidth)

        .addOverloadedFunctions("SetColor",
            static_cast<void(Text3D::*)(const Color&)>(&Text3D::SetColor),
            static_cast<void(Text3D::*)(Corner, const Color&)>(&Text3D::SetColor))

        .addFunction("SetOpacity", &Text3D::SetOpacity)
        .addFunction("SetFixedScreenSize", &Text3D::SetFixedScreenSize)
        .addFunction("SetFaceCameraMode", &Text3D::SetFaceCameraMode)

        .addFunction("GetFont", &Text3D::GetFont)
        .addFunction("GetFontSize", &Text3D::GetFontSize)
        .addFunction("GetMaterial", &Text3D::GetMaterial)
        .addFunction("GetText", &Text3D::GetText)
        .addFunction("GetTextAlignment", &Text3D::GetTextAlignment)
        .addFunction("GetHorizontalAlignment", &Text3D::GetHorizontalAlignment)
        .addFunction("GetVerticalAlignment", &Text3D::GetVerticalAlignment)
        .addFunction("GetRowSpacing", &Text3D::GetRowSpacing)
        .addFunction("GetWordwrap", &Text3D::GetWordwrap)
        .addFunction("GetTextEffect", &Text3D::GetTextEffect)
        .addFunction("GetEffectShadowOffset", &Text3D::GetEffectShadowOffset)
        .addFunction("GetEffectStrokeThickness", &Text3D::GetEffectStrokeThickness)
        .addFunction("GetEffectRoundStroke", &Text3D::GetEffectRoundStroke)
        .addFunction("GetEffectColor", &Text3D::GetEffectColor)
        .addFunction("GetEffectDepthBias", &Text3D::GetEffectDepthBias)
        .addFunction("GetWidth", &Text3D::GetWidth)
        .addFunction("GetRowHeight", &Text3D::GetRowHeight)
        .addFunction("GetNumRows", &Text3D::GetNumRows)
        .addFunction("GetNumChars", &Text3D::GetNumChars)
        .addFunction("GetRowWidth", &Text3D::GetRowWidth)
        .addFunction("GetCharPosition", &Text3D::GetCharPosition)
        .addFunction("GetCharSize", &Text3D::GetCharSize)

        .addOverloadedFunctions("GetColor", &Text3DGetColor, &Text3D::GetColor)

        .addFunction("GetOpacity", &Text3D::GetOpacity)
        .addFunction("IsFixedScreenSize", &Text3D::IsFixedScreenSize)
        .addFunction("GetFaceCameraMode", &Text3D::GetFaceCameraMode)

        .addProperty("font", &Text3D::GetFont)
        .addProperty("fontSize", &Text3D::GetFontSize)
        .addProperty("material", &Text3D::GetMaterial, &Text3D::SetMaterial)
        .addProperty("text", &Text3D::GetText, &Text3D::SetText)
        .addProperty("textAlignment", &Text3D::GetTextAlignment, &Text3D::SetTextAlignment)
        .addProperty("horizontalAlignment", &Text3D::GetHorizontalAlignment, &Text3D::SetHorizontalAlignment)
        .addProperty("verticalAlignment", &Text3D::GetVerticalAlignment, &Text3D::SetVerticalAlignment)
        .addProperty("rowSpacing", &Text3D::GetRowSpacing, &Text3D::SetRowSpacing)
        .addProperty("wordwrap", &Text3D::GetWordwrap, &Text3D::SetWordwrap)
        .addProperty("textEffect", &Text3D::GetTextEffect, &Text3D::SetTextEffect)
        .addProperty("effectShadowOffset", &Text3D::GetEffectShadowOffset, &Text3D::SetEffectShadowOffset)
        .addProperty("effectStrokeThickness", &Text3D::GetEffectStrokeThickness, &Text3D::SetEffectStrokeThickness)
        .addProperty("effectRoundStroke", &Text3D::GetEffectRoundStroke, &Text3D::SetEffectRoundStroke)
        .addProperty("effectColor", &Text3D::GetEffectColor, &Text3D::SetEffectColor)
        .addProperty("effectDepthBias", &Text3D::GetEffectDepthBias, &Text3D::SetEffectDepthBias)
        .addProperty("width", &Text3D::GetWidth, &Text3D::SetWidth)
        .addProperty("rowHeight", &Text3D::GetRowHeight)
        .addProperty("numRows", &Text3D::GetNumRows)
        .addProperty("numChars", &Text3D::GetNumChars)
        .addProperty("color", &Text3DGetColor, &Text3DSetColor)
        .addProperty("opacity", &Text3D::GetOpacity, &Text3D::SetOpacity)
        .addProperty("fixedScreenSize", &Text3D::IsFixedScreenSize, &Text3D::SetFixedScreenSize)
        .addProperty("faceCameraMode", &Text3D::GetFaceCameraMode, &Text3D::SetFaceCameraMode)
        );
}
}

