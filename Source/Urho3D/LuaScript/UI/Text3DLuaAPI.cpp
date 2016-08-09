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

    // [Class] Text3D : Drawable
    lua["Text3D"].setClass(UserdataMetatable<Text3D, Drawable>()
        .addStaticFunction("new", &CreateObject<Text3D>)

        .addOverloadedFunctions("SetFont", Text3DSetFont0(), Text3DSetFont1())

        // [Method] bool SetFontSize(int size)
		.addFunction("SetFontSize", &Text3D::SetFontSize)

        // [Method] void SetMaterial(Material* material)
        .addFunction("SetMaterial", &Text3D::SetMaterial)
        // [Method] void SetText(const String& text)
        .addFunction("SetText", &Text3D::SetText)
        // [Method] void SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign)
        .addFunction("SetAlignment", &Text3D::SetAlignment)
        // [Method] void SetHorizontalAlignment(HorizontalAlignment align)
        .addFunction("SetHorizontalAlignment", &Text3D::SetHorizontalAlignment)
        // [Method] void SetVerticalAlignment(VerticalAlignment align)
        .addFunction("SetVerticalAlignment", &Text3D::SetVerticalAlignment)
        // [Method] void SetTextAlignment(HorizontalAlignment align)
        .addFunction("SetTextAlignment", &Text3D::SetTextAlignment)
        // [Method] void SetRowSpacing(float spacing)
        .addFunction("SetRowSpacing", &Text3D::SetRowSpacing)
        // [Method] void SetWordwrap(bool enable)
        .addFunction("SetWordwrap", &Text3D::SetWordwrap)
        // [Method] void SetTextEffect(TextEffect textEffect)
        .addFunction("SetTextEffect", &Text3D::SetTextEffect)
        // [Method] void SetEffectShadowOffset(const IntVector2& offset)
        .addFunction("SetEffectShadowOffset", &Text3D::SetEffectShadowOffset)
        // [Method] void SetEffectStrokeThickness(int thickness)
        .addFunction("SetEffectStrokeThickness", &Text3D::SetEffectStrokeThickness)
        // [Method] void SetEffectRoundStroke(bool roundStroke)
        .addFunction("SetEffectRoundStroke", &Text3D::SetEffectRoundStroke)
        // [Method] void SetEffectColor(const Color& effectColor)
        .addFunction("SetEffectColor", &Text3D::SetEffectColor)
        // [Method] void SetEffectDepthBias(float bias)
        .addFunction("SetEffectDepthBias", &Text3D::SetEffectDepthBias)
        // [Method] void SetWidth(int width)
        .addFunction("SetWidth", &Text3D::SetWidth)

        .addOverloadedFunctions("SetColor",
            static_cast<void(Text3D::*)(const Color&)>(&Text3D::SetColor),
            static_cast<void(Text3D::*)(Corner, const Color&)>(&Text3D::SetColor))

        // [Method] void SetOpacity(float opacity)
        .addFunction("SetOpacity", &Text3D::SetOpacity)
        // [Method] void SetFixedScreenSize(bool enable)
        .addFunction("SetFixedScreenSize", &Text3D::SetFixedScreenSize)
        // [Method] void SetFaceCameraMode(FaceCameraMode mode)
        .addFunction("SetFaceCameraMode", &Text3D::SetFaceCameraMode)

        // [Method] Font* GetFont() const
        .addFunction("GetFont", &Text3D::GetFont)
        // [Method] int GetFontSize() const
        .addFunction("GetFontSize", &Text3D::GetFontSize)
        // [Method] Material* GetMaterial() const
        .addFunction("GetMaterial", &Text3D::GetMaterial)
        // [Method] const String& GetText() const
        .addFunction("GetText", &Text3D::GetText)
        // [Method] HorizontalAlignment GetTextAlignment() const
        .addFunction("GetTextAlignment", &Text3D::GetTextAlignment)
        // [Method] HorizontalAlignment GetHorizontalAlignment() const
        .addFunction("GetHorizontalAlignment", &Text3D::GetHorizontalAlignment)
        // [Method] VerticalAlignment GetVerticalAlignment() const
        .addFunction("GetVerticalAlignment", &Text3D::GetVerticalAlignment)
        // [Method] float GetRowSpacing() const
        .addFunction("GetRowSpacing", &Text3D::GetRowSpacing)
        // [Method] bool GetWordwrap() const
        .addFunction("GetWordwrap", &Text3D::GetWordwrap)
        // [Method] TextEffect GetTextEffect() const
        .addFunction("GetTextEffect", &Text3D::GetTextEffect)
        // [Method] const IntVector2& GetEffectShadowOffset() const
        .addFunction("GetEffectShadowOffset", &Text3D::GetEffectShadowOffset)
        // [Method] int GetEffectStrokeThickness() const
        .addFunction("GetEffectStrokeThickness", &Text3D::GetEffectStrokeThickness)
        // [Method] bool GetEffectRoundStroke() const
        .addFunction("GetEffectRoundStroke", &Text3D::GetEffectRoundStroke)
        // [Method] const Color& GetEffectColor() const
        .addFunction("GetEffectColor", &Text3D::GetEffectColor)
        // [Method] float GetEffectDepthBias() const
        .addFunction("GetEffectDepthBias", &Text3D::GetEffectDepthBias)
        // [Method] int GetWidth() const
        .addFunction("GetWidth", &Text3D::GetWidth)
        // [Method] int GetRowHeight() const
        .addFunction("GetRowHeight", &Text3D::GetRowHeight)
        // [Method] unsigned GetNumRows() const
        .addFunction("GetNumRows", &Text3D::GetNumRows)
        // [Method] unsigned GetNumChars() const
        .addFunction("GetNumChars", &Text3D::GetNumChars)
        // [Method] int GetRowWidth(unsigned index) const
        .addFunction("GetRowWidth", &Text3D::GetRowWidth)
        // [Method] IntVector2 GetCharPosition(unsigned index)
        .addFunction("GetCharPosition", &Text3D::GetCharPosition)
        // [Method] IntVector2 GetCharSize(unsigned index)
        .addFunction("GetCharSize", &Text3D::GetCharSize)

        .addOverloadedFunctions("GetColor", &Text3DGetColor, &Text3D::GetColor)

        // [Method] float GetOpacity() const
        .addFunction("GetOpacity", &Text3D::GetOpacity)
        // [Method] bool IsFixedScreenSize() const
        .addFunction("IsFixedScreenSize", &Text3D::IsFixedScreenSize)
        // [Method] FaceCameraMode GetFaceCameraMode() const
        .addFunction("GetFaceCameraMode", &Text3D::GetFaceCameraMode)

        // [Property(ReadOnly)] Font* font
        .addProperty("font", &Text3D::GetFont)
        // [Property] int fontSize
        .addProperty("fontSize", &Text3D::GetFontSize, &Text3D::SetFontSize)
        // [Property] Material* material
        .addProperty("material", &Text3D::GetMaterial, &Text3D::SetMaterial)
        // [Property] const String& text
        .addProperty("text", &Text3D::GetText, &Text3D::SetText)
        // [Property] HorizontalAlignment textAlignment
        .addProperty("textAlignment", &Text3D::GetTextAlignment, &Text3D::SetTextAlignment)
        // [Property] HorizontalAlignment horizontalAlignment
        .addProperty("horizontalAlignment", &Text3D::GetHorizontalAlignment, &Text3D::SetHorizontalAlignment)
        // [Property] VerticalAlignment verticalAlignment
        .addProperty("verticalAlignment", &Text3D::GetVerticalAlignment, &Text3D::SetVerticalAlignment)
        // [Property] float rowSpacing
        .addProperty("rowSpacing", &Text3D::GetRowSpacing, &Text3D::SetRowSpacing)
        // [Property] bool wordwrap
        .addProperty("wordwrap", &Text3D::GetWordwrap, &Text3D::SetWordwrap)
        // [Property] TextEffect textEffect
        .addProperty("textEffect", &Text3D::GetTextEffect, &Text3D::SetTextEffect)
        // [Property] const IntVector2& effectShadowOffset
        .addProperty("effectShadowOffset", &Text3D::GetEffectShadowOffset, &Text3D::SetEffectShadowOffset)
        // [Property] int effectStrokeThickness
        .addProperty("effectStrokeThickness", &Text3D::GetEffectStrokeThickness, &Text3D::SetEffectStrokeThickness)
        // [Property] bool effectRoundStroke
        .addProperty("effectRoundStroke", &Text3D::GetEffectRoundStroke, &Text3D::SetEffectRoundStroke)
        // [Property] const Color& effectColor
        .addProperty("effectColor", &Text3D::GetEffectColor, &Text3D::SetEffectColor)
        // [Property] float effectDepthBias
        .addProperty("effectDepthBias", &Text3D::GetEffectDepthBias, &Text3D::SetEffectDepthBias)
        // [Property] int width
        .addProperty("width", &Text3D::GetWidth, &Text3D::SetWidth)
        // [Property(ReadOnly)] int rowHeight
        .addProperty("rowHeight", &Text3D::GetRowHeight)
        // [Property(ReadOnly)] unsigned numRows
        .addProperty("numRows", &Text3D::GetNumRows)
        // [Property(ReadOnly)] unsigned numChars
        .addProperty("numChars", &Text3D::GetNumChars)
        .addProperty("color", &Text3DGetColor, &Text3DSetColor)
        // [Property] float opacity
        .addProperty("opacity", &Text3D::GetOpacity, &Text3D::SetOpacity)
        // [Property] bool fixedScreenSize
        .addProperty("fixedScreenSize", &Text3D::IsFixedScreenSize, &Text3D::SetFixedScreenSize)
        // [Property] FaceCameraMode faceCameraMode
        .addProperty("faceCameraMode", &Text3D::GetFaceCameraMode, &Text3D::SetFaceCameraMode)
        );
}
}

