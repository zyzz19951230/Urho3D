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

#include "../../UI/Cursor.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterCursor(kaguya::State& lua)
{
    using namespace kaguya;

    // [Enum] CursorShape
    // [Variable] CS_NORMAL
    lua["CS_NORMAL"] = CS_NORMAL;
    // [Variable] CS_IBEAM,
    lua["CS_IBEAM"] = CS_IBEAM;
    // [Variable] CS_CROSS,
    lua["CS_CROSS"] = CS_CROSS;
    // [Variable] CS_RESIZEVERTICAL,
    lua["CS_RESIZEVERTICAL"] = CS_RESIZEVERTICAL;
    // [Variable] CS_RESIZEDIAGONAL_TOPRIGHT,
    lua["CS_RESIZEDIAGONAL_TOPRIGHT"] = CS_RESIZEDIAGONAL_TOPRIGHT;
    // [Variable] CS_RESIZEHORIZONTAL,
    lua["CS_RESIZEHORIZONTAL"] = CS_RESIZEHORIZONTAL;
    // [Variable] CS_RESIZEDIAGONAL_TOPLEFT,
    lua["CS_RESIZEDIAGONAL_TOPLEFT"] = CS_RESIZEDIAGONAL_TOPLEFT;
    // [Variable] CS_RESIZE_ALL,
    lua["CS_RESIZE_ALL"] = CS_RESIZE_ALL;
    // [Variable] CS_ACCEPTDROP,
    lua["CS_ACCEPTDROP"] = CS_ACCEPTDROP;
    // [Variable] CS_REJECTDROP,
    lua["CS_REJECTDROP"] = CS_REJECTDROP;
    // [Variable] CS_BUSY,
    lua["CS_BUSY"] = CS_BUSY;
    // [Variable] CS_BUSY_ARROW,
    lua["CS_BUSY_ARROW"] = CS_BUSY_ARROW;
    // [Variable] CS_MAX_SHAPES
    lua["CS_MAX_SHAPES"] = CS_MAX_SHAPES;

    // [Class] Cursor : BorderImage
    lua["Cursor"].setClass(UserdataMetatable<Cursor, BorderImage>()
        .addStaticFunction("new", &CreateObject<Cursor>)

        .addOverloadedFunctions("DefineShape",
            static_cast<void(Cursor::*)(const String&, Image*, const IntRect&, const IntVector2&)>(&Cursor::DefineShape),
            static_cast<void(Cursor::*)(CursorShape, Image*, const IntRect&, const IntVector2&)>(&Cursor::DefineShape))

        .addOverloadedFunctions("SetShape",
            static_cast<void(Cursor::*)(const String&)>(&Cursor::SetShape),
            static_cast<void(Cursor::*)(CursorShape)>(&Cursor::SetShape))

        // [Method] void SetUseSystemShapes(bool enable)
        .addFunction("SetUseSystemShapes", &Cursor::SetUseSystemShapes)

        // [Method] const String& GetShape() const
        .addFunction("GetShape", &Cursor::GetShape)
        // [Method] bool GetUseSystemShapes() const
        .addFunction("GetUseSystemShapes", &Cursor::GetUseSystemShapes)

        // [Property] const String& shape
        .addProperty("shape", &Cursor::GetShape, static_cast<void(Cursor::*)(const String&)>(&Cursor::SetShape))
        // [Property] bool useSystemShapes
        .addProperty("useSystemShapes", &Cursor::GetUseSystemShapes, &Cursor::SetUseSystemShapes)
        );
}
}

