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

#include "../../Graphics/Texture3D.h"
#include "../../Resource/Image.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(Texture3DSetSize, Texture3D, SetSize, 4, 5);
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(Texture3DSetData, Texture3D, SetData, 1, 2, bool(Texture3D::*)(Image*, bool));

void RegisterTexture3D(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Texture3D"].setClass(UserdataMetatable<Texture3D, Texture>()
        .addStaticFunction("new", &CreateObject<Texture3D>)
        
        .addFunction("SetSize", Texture3DSetSize())
        .addFunction("SetData", Texture3DSetData())
    );
}
}

