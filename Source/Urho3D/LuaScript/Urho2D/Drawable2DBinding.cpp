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

#include "../../Urho2D/Drawable2D.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterDrawable2D(kaguya::State& lua)
{
    using namespace kaguya;

    // [Constant] float PIXEL_SIZE
    lua["PIXEL_SIZE"] = PIXEL_SIZE;

    // [Class] Drawable2D : Drawable
    lua["Drawable2D"].setClass(UserdataMetatable<Drawable2D, Drawable>()

        // [Method] void SetLayer(int layer)
        .addFunction("SetLayer", &Drawable2D::SetLayer)
        // [Method] void SetOrderInLayer(int orderInLayer)
        .addFunction("SetOrderInLayer", &Drawable2D::SetOrderInLayer)

        // [Method] int GetLayer() const
        .addFunction("GetLayer", &Drawable2D::GetLayer)
        // [Method] int GetOrderInLayer() const
        .addFunction("GetOrderInLayer", &Drawable2D::GetOrderInLayer)

        // [Property] int layer
        .addProperty("layer", &Drawable2D::GetLayer, &Drawable2D::SetLayer)
        // [Property] int orderInLayer
        .addProperty("orderInLayer", &Drawable2D::GetOrderInLayer, &Drawable2D::SetOrderInLayer)
    );
}
}

#endif
