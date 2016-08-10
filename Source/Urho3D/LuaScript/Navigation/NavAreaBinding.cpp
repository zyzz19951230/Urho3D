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

#ifdef URHO3D_NAVIGATION

#include "../../Precompiled.h"

#include "../../Navigation/NavArea.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterNavArea(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] NavArea : Component
    lua["NavArea"].setClass(UserdataMetatable<NavArea, Component>()
        // [Constructor] NavArea()
        .addStaticFunction("new", &CreateObject<NavArea>)

        // [Method] unsigned GetAreaID() const
        .addFunction("GetAreaID", &NavArea::GetAreaID)
        // [Method] void SetAreaID(unsigned newID)
        .addFunction("SetAreaID", &NavArea::SetAreaID)

        // [Method] BoundingBox GetBoundingBox() const
        .addFunction("GetBoundingBox", &NavArea::GetBoundingBox)
        // [Method] void SetBoundingBox(const BoundingBox& bnds)
        .addFunction("SetBoundingBox", &NavArea::SetBoundingBox)

        // [Method] BoundingBox GetWorldBoundingBox() const
        .addFunction("GetWorldBoundingBox", &NavArea::GetWorldBoundingBox)

        // [Property] unsigned areaID
        .addProperty("areaID", &NavArea::GetAreaID, &NavArea::SetAreaID)
        // [Property] BoundingBox boundingBox
        .addProperty("boundingBox", &NavArea::GetBoundingBox, &NavArea::SetBoundingBox)
        // [Property(Readonly)] BoundingBox worldBoundingBox
        .addProperty("worldBoundingBox", &NavArea::GetWorldBoundingBox)
        );
}
}

#endif
