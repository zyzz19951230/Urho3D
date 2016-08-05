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

    lua["DEFAULT_FONT_SIZE"] = DEFAULT_FONT_SIZE;

    // enum TextEffect;
    lua["TE_NONE"] = TE_NONE;
    lua["TE_SHADOW"] = TE_SHADOW;
    lua["TE_STROKE"] = TE_STROKE;

    lua["Text"].setClass(UserdataMetatable<Text, UIElement>()
        .addStaticFunction("new", &CreateObject<Text>)

        .addOverloadedFunctions("SetFont", TextSetFont0(), TextSetFont1())

        .addFunction("SetText", &Text::SetText)
        .addFunction("SetTextAlignment", &Text::SetTextAlignment)
        .addFunction("SetRowSpacing", &Text::SetRowSpacing)
        .addFunction("SetWordwrap", &Text::SetWordwrap)
        .addFunction("SetAutoLocalizable", &Text::SetAutoLocalizable)

        .addFunction("SetSelection", TextSetSelection())

        .addFunction("ClearSelection", &Text::ClearSelection)
        .addFunction("SetSelectionColor", &Text::SetSelectionColor)
        .addFunction("SetHoverColor", &Text::SetHoverColor)
        .addFunction("SetTextEffect", &Text::SetTextEffect)
        .addFunction("SetEffectShadowOffset", &Text::SetEffectShadowOffset)
        .addFunction("SetEffectStrokeThickness", &Text::SetEffectStrokeThickness)
        .addFunction("SetEffectRoundStroke", &Text::SetEffectRoundStroke)
        .addFunction("SetEffectColor", &Text::SetEffectColor)

        .addFunction("GetFont", &Text::GetFont)
        .addFunction("GetFontSize", &Text::GetFontSize)
        .addFunction("GetText", &Text::GetText)
        .addFunction("GetTextAlignment", &Text::GetTextAlignment)
        .addFunction("GetRowSpacing", &Text::GetRowSpacing)
        .addFunction("GetWordwrap", &Text::GetWordwrap)
        .addFunction("GetAutoLocalizable", &Text::GetAutoLocalizable)
        .addFunction("GetSelectionStart", &Text::GetSelectionStart)
        .addFunction("GetSelectionLength", &Text::GetSelectionLength)
        .addFunction("GetSelectionColor", &Text::GetSelectionColor)
        .addFunction("GetHoverColor", &Text::GetHoverColor)
        .addFunction("GetTextEffect", &Text::GetTextEffect)
        .addFunction("GetEffectShadowOffset", &Text::GetEffectShadowOffset)
        .addFunction("GetEffectStrokeThickness", &Text::GetEffectStrokeThickness)
        .addFunction("GetEffectRoundStroke", &Text::GetEffectRoundStroke)
        .addFunction("GetEffectColor", &Text::GetEffectColor)
        .addFunction("GetRowHeight", &Text::GetRowHeight)
        .addFunction("GetNumRows", &Text::GetNumRows)
        .addFunction("GetNumChars", &Text::GetNumChars)
        .addFunction("GetRowWidth", &Text::GetRowWidth)
        .addFunction("GetCharPosition", &Text::GetCharPosition)
        .addFunction("GetCharSize", &Text::GetCharSize)

        .addFunction("SetEffectDepthBias", &Text::SetEffectDepthBias)
        .addFunction("GetEffectDepthBias", &Text::GetEffectDepthBias)

        .addProperty("font", &Text::GetFont)
        .addProperty("fontSize", &Text::GetFontSize)
        .addProperty("text", &Text::GetText, &Text::SetText)
        .addProperty("textAlignment", &Text::GetTextAlignment, &Text::SetTextAlignment)
        .addProperty("rowSpacing", &Text::GetRowSpacing, &Text::SetRowSpacing)
        .addProperty("wordwrap", &Text::GetWordwrap, &Text::SetWordwrap)
        .addProperty("autoLocalizable", &Text::GetAutoLocalizable, &Text::SetAutoLocalizable)
        .addProperty("selectionStart", &Text::GetSelectionStart)
        .addProperty("selectionLength", &Text::GetSelectionLength)
        .addProperty("selectionColor", &Text::GetSelectionColor, &Text::SetSelectionColor)
        .addProperty("hoverColor", &Text::GetHoverColor, &Text::SetHoverColor)
        .addProperty("textEffect", &Text::GetTextEffect, &Text::SetTextEffect)
        .addProperty("effectShadowOffset", &Text::GetEffectShadowOffset, &Text::SetEffectShadowOffset)
        .addProperty("effectStrokeThickness", &Text::GetEffectStrokeThickness, &Text::SetEffectStrokeThickness)
        .addProperty("effectRoundStroke", &Text::GetEffectRoundStroke, &Text::SetEffectRoundStroke)
        .addProperty("effectColor", &Text::GetEffectColor, &Text::SetEffectColor)
        .addProperty("rowHeight", &Text::GetRowHeight)
        .addProperty("numRows", &Text::GetNumRows)
        .addProperty("numChars", &Text::GetNumChars)
        .addProperty("effectDepthBias", &Text::GetEffectDepthBias, &Text::SetEffectDepthBias)
        );
}
}

