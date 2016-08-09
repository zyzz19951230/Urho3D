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

#ifdef URHO3D_URHO2D

#include "../../Precompiled.h"

#include "../../Urho2D/AnimationSet2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterAnimationSet2D(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] AnimationSet2D : Resource
    lua["AnimationSet2D"].setClass(UserdataMetatable<AnimationSet2D, Resource>()
        .addStaticFunction("new", &CreateObject<AnimationSet2D>)

        // [Method] unsigned GetNumAnimations() const
        .addFunction("GetNumAnimations", &AnimationSet2D::GetNumAnimations)
        // [Method] String GetAnimation(unsigned index) const
        .addFunction("GetAnimation", &AnimationSet2D::GetAnimation)
        // [Method] bool HasAnimation(const String& animation) const
        .addFunction("HasAnimation", &AnimationSet2D::HasAnimation)

        // [Property(ReadOnly)] unsigned numAnimations
        .addProperty("numAnimations", &AnimationSet2D::GetNumAnimations)
    );
}
}

#endif
