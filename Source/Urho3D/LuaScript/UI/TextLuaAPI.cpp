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
#include "../../UI/Text.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(TextSetFont0, Text, SetFont, 1, 2, bool(Text::*)(const String&, int));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(TextSetFont1, Text, SetFont, 1, 2, bool(Text::*)(Font*, int));
KAGUYA_MEMBER_FUNCTION_OVERLOADS(TextSetSelection, Text, SetSelection, 1, 2);

void RegisterText(kaguya::State& lua)
{
    using namespace kaguya;

    // [Constant] bool SetFont(String& fontName, int size
    lua["DEFAULT_FONT_SIZE"] = DEFAULT_FONT_SIZE;

    // [Enum] TextEffect
    // [Variable] TE_NONE
    lua["TE_NONE"] = TE_NONE;
    // [Variable] TE_SHADOW,
    lua["TE_SHADOW"] = TE_SHADOW;
    // [Variable] TE_STROKE
    lua["TE_STROKE"] = TE_STROKE;

    // [Class] Text : UIElement
    lua["Text"].setClass(UserdataMetatable<Text, UIElement>()
        .addStaticFunction("new", &CreateObject<Text>)

        .addOverloadedFunctions("SetFont", TextSetFont0(), TextSetFont1())

        // [Method] bool SetFontSize(int size)
        .addFunction("SetFontSize", &Text::SetFontSize)

        // [Method] void SetText(const String& text)
        .addFunction("SetText", &Text::SetText)
        // [Method] void SetTextAlignment(HorizontalAlignment align)
        .addFunction("SetTextAlignment", &Text::SetTextAlignment)
        // [Method] void SetRowSpacing(float spacing)
        .addFunction("SetRowSpacing", &Text::SetRowSpacing)
        // [Method] void SetWordwrap(bool enable)
        .addFunction("SetWordwrap", &Text::SetWordwrap)
        // [Method] void SetAutoLocalizable(bool enable)
        .addFunction("SetAutoLocalizable", &Text::SetAutoLocalizable)

        // [Method] void SetSelection(unsigned start, unsigned length = M_MAX_UNSIGNED)
        .addFunction("SetSelection", TextSetSelection())

        // [Method] void ClearSelection()
        .addFunction("ClearSelection", &Text::ClearSelection)
        // [Method] void SetSelectionColor(const Color& color)
        .addFunction("SetSelectionColor", &Text::SetSelectionColor)
        // [Method] void SetHoverColor(const Color& color)
        .addFunction("SetHoverColor", &Text::SetHoverColor)
        // [Method] void SetTextEffect(TextEffect textEffect)
        .addFunction("SetTextEffect", &Text::SetTextEffect)
        // [Method] void SetEffectShadowOffset(const IntVector2& offset)
        .addFunction("SetEffectShadowOffset", &Text::SetEffectShadowOffset)
        // [Method] void SetEffectStrokeThickness(int thickness)
        .addFunction("SetEffectStrokeThickness", &Text::SetEffectStrokeThickness)
        // [Method] void SetEffectRoundStroke(bool roundStroke)
        .addFunction("SetEffectRoundStroke", &Text::SetEffectRoundStroke)
        // [Method] void SetEffectColor(const Color& effectColor)
        .addFunction("SetEffectColor", &Text::SetEffectColor)

        // [Method] Font* GetFont() const
        .addFunction("GetFont", &Text::GetFont)
        // [Method] int GetFontSize() const
        .addFunction("GetFontSize", &Text::GetFontSize)
        // [Method] const String& GetText() const
        .addFunction("GetText", &Text::GetText)
        // [Method] HorizontalAlignment GetTextAlignment() const
        .addFunction("GetTextAlignment", &Text::GetTextAlignment)
        // [Method] float GetRowSpacing() const
        .addFunction("GetRowSpacing", &Text::GetRowSpacing)
        // [Method] bool GetWordwrap() const
        .addFunction("GetWordwrap", &Text::GetWordwrap)
        // [Method] bool GetAutoLocalizable() const
        .addFunction("GetAutoLocalizable", &Text::GetAutoLocalizable)
        // [Method] unsigned GetSelectionStart() const
        .addFunction("GetSelectionStart", &Text::GetSelectionStart)
        // [Method] unsigned GetSelectionLength() const
        .addFunction("GetSelectionLength", &Text::GetSelectionLength)
        // [Method] const Color& GetSelectionColor() const
        .addFunction("GetSelectionColor", &Text::GetSelectionColor)
        // [Method] const Color& GetHoverColor() const
        .addFunction("GetHoverColor", &Text::GetHoverColor)
        // [Method] TextEffect GetTextEffect() const
        .addFunction("GetTextEffect", &Text::GetTextEffect)
        // [Method] const IntVector2& GetEffectShadowOffset() const
        .addFunction("GetEffectShadowOffset", &Text::GetEffectShadowOffset)
        // [Method] int GetEffectStrokeThickness() const
        .addFunction("GetEffectStrokeThickness", &Text::GetEffectStrokeThickness)
        // [Method] bool GetEffectRoundStroke() const
        .addFunction("GetEffectRoundStroke", &Text::GetEffectRoundStroke)
        // [Method] const Color& GetEffectColor() const
        .addFunction("GetEffectColor", &Text::GetEffectColor)
        // [Method] int GetRowHeight() const
        .addFunction("GetRowHeight", &Text::GetRowHeight)
        // [Method] unsigned GetNumRows() const
        .addFunction("GetNumRows", &Text::GetNumRows)
        // [Method] unsigned GetNumChars() const
        .addFunction("GetNumChars", &Text::GetNumChars)
        // [Method] int GetRowWidth(unsigned index) const
        .addFunction("GetRowWidth", &Text::GetRowWidth)
        // [Method] IntVector2 GetCharPosition(unsigned index)
        .addFunction("GetCharPosition", &Text::GetCharPosition)
        // [Method] IntVector2 GetCharSize(unsigned index)
        .addFunction("GetCharSize", &Text::GetCharSize)

        // [Method] void SetEffectDepthBias(float bias)
        .addFunction("SetEffectDepthBias", &Text::SetEffectDepthBias)
        // [Method] float GetEffectDepthBias() const
        .addFunction("GetEffectDepthBias", &Text::GetEffectDepthBias)

        // [Property(ReadOnly)] Font* font
        .addProperty("font", &Text::GetFont)
        // [Property] int fontSize
        .addProperty("fontSize", &Text::GetFontSize, &Text::SetFontSize)
        // [Property] const String& text
        .addProperty("text", &Text::GetText, &Text::SetText)
        // [Property] HorizontalAlignment textAlignment
        .addProperty("textAlignment", &Text::GetTextAlignment, &Text::SetTextAlignment)
        // [Property] float rowSpacing
        .addProperty("rowSpacing", &Text::GetRowSpacing, &Text::SetRowSpacing)
        // [Property] bool wordwrap
        .addProperty("wordwrap", &Text::GetWordwrap, &Text::SetWordwrap)
        // [Property] bool autoLocalizable
        .addProperty("autoLocalizable", &Text::GetAutoLocalizable, &Text::SetAutoLocalizable)
        // [Property(ReadOnly)] unsigned selectionStart
        .addProperty("selectionStart", &Text::GetSelectionStart)
        // [Property(ReadOnly)] unsigned selectionLength
        .addProperty("selectionLength", &Text::GetSelectionLength)
        // [Property] const Color& selectionColor
        .addProperty("selectionColor", &Text::GetSelectionColor, &Text::SetSelectionColor)
        // [Property] const Color& hoverColor
        .addProperty("hoverColor", &Text::GetHoverColor, &Text::SetHoverColor)
        // [Property] TextEffect textEffect
        .addProperty("textEffect", &Text::GetTextEffect, &Text::SetTextEffect)
        // [Property] const IntVector2& effectShadowOffset
        .addProperty("effectShadowOffset", &Text::GetEffectShadowOffset, &Text::SetEffectShadowOffset)
        // [Property] int effectStrokeThickness
        .addProperty("effectStrokeThickness", &Text::GetEffectStrokeThickness, &Text::SetEffectStrokeThickness)
        // [Property] bool effectRoundStroke
        .addProperty("effectRoundStroke", &Text::GetEffectRoundStroke, &Text::SetEffectRoundStroke)
        // [Property] const Color& effectColor
        .addProperty("effectColor", &Text::GetEffectColor, &Text::SetEffectColor)
        // [Property(ReadOnly)] int rowHeight
        .addProperty("rowHeight", &Text::GetRowHeight)
        // [Property(ReadOnly)] unsigned numRows
        .addProperty("numRows", &Text::GetNumRows)
        // [Property(ReadOnly)] unsigned numChars
        .addProperty("numChars", &Text::GetNumChars)
        // [Property] float effectDepthBias
        .addProperty("effectDepthBias", &Text::GetEffectDepthBias, &Text::SetEffectDepthBias)
        );
}
}

