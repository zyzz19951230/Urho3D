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

#include "../../Graphics/BillboardSet.h"
#include "../../Graphics/Material.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterBillboardSet(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Billboard
    lua["Billboard"].setClass(UserdataMetatable<Billboard>()

        // [Field] Vector3 position;
        .addProperty("position", &Billboard::position_)
        // [Field] Vector2 size;
        .addProperty("size", &Billboard::size_)
        // [Field] Rect uv;
        .addProperty("uv", &Billboard::uv_)
        // [Field] Color color;
        .addProperty("color", &Billboard::color_)
        // [Field] float rotation;
        .addProperty("rotation", &Billboard::rotation_)
        // [Field] Vector3 direction;
        .addProperty("direction", &Billboard::direction_)
        // [Field] bool enabled;
        .addProperty("enabled", &Billboard::enabled_)
        );

    // [Class] BillboardSet : Drawable
    lua["BillboardSet"].setClass(UserdataMetatable<BillboardSet, Drawable>()
        // [Constructor] BillboardSet()
        .addStaticFunction("new", &CreateObject<BillboardSet>)

        // [Method] void SetMaterial(Material* material)
        .addFunction("SetMaterial", &BillboardSet::SetMaterial)
        // [Method] void SetNumBillboards(unsigned num)
        .addFunction("SetNumBillboards", &BillboardSet::SetNumBillboards)
        // [Method] void SetRelative(bool enable)
        .addFunction("SetRelative", &BillboardSet::SetRelative)
        // [Method] void SetScaled(bool enable)
        .addFunction("SetScaled", &BillboardSet::SetScaled)
        // [Method] void SetSorted(bool enable)
        .addFunction("SetSorted", &BillboardSet::SetSorted)
        // [Method] void SetFixedScreenSize(bool enable)
        .addFunction("SetFixedScreenSize", &BillboardSet::SetFixedScreenSize)
        // [Method] void SetFaceCameraMode(FaceCameraMode mode)
        .addFunction("SetFaceCameraMode", &BillboardSet::SetFaceCameraMode)        
        // [Method] void SetAnimationLodBias(float bias)
        .addFunction("SetAnimationLodBias", &BillboardSet::SetAnimationLodBias)
        
        // [Method] void Commit()
        .addFunction("Commit", &BillboardSet::Commit)

        // [Method] Material* GetMaterial() const
        .addFunction("GetMaterial", &BillboardSet::GetMaterial)
        // [Method] unsigned GetNumBillboards() const
        .addFunction("GetNumBillboards", &BillboardSet::GetNumBillboards)
        // [Method] Billboard* GetBillboard(unsigned index)
        .addFunction("GetBillboard", &BillboardSet::GetBillboard)
        // [Method] bool IsRelative() const
        .addFunction("IsRelative", &BillboardSet::IsRelative)
        // [Method] bool IsScaled() const
        .addFunction("IsScaled", &BillboardSet::IsScaled)
        // [Method] bool IsSorted() const
        .addFunction("IsSorted", &BillboardSet::IsSorted)
        // [Method] bool IsFixedScreenSize() const
        .addFunction("IsFixedScreenSize", &BillboardSet::IsFixedScreenSize)
        // [Method] FaceCameraMode GetFaceCameraMode() const
        .addFunction("GetFaceCameraMode", &BillboardSet::GetFaceCameraMode)
        // [Method] float GetAnimationLodBias() const
        .addFunction("GetAnimationLodBias", &BillboardSet::GetAnimationLodBias)

        // [Property] Material* material
        .addProperty("material", &BillboardSet::GetMaterial, &BillboardSet::SetMaterial)
        // [Property] unsigned numBillboards
        .addProperty("numBillboards", &BillboardSet::GetNumBillboards, &BillboardSet::SetNumBillboards)
        // [Property] bool relative
        .addProperty("relative", &BillboardSet::IsRelative, &BillboardSet::SetRelative)
        // [Property] bool scaled
        .addProperty("scaled", &BillboardSet::IsScaled, &BillboardSet::SetScaled)
        // [Property] bool sorted
        .addProperty("sorted", &BillboardSet::IsSorted, &BillboardSet::SetSorted)
        // [Property] bool fixedScreenSize
        .addProperty("fixedScreenSize", &BillboardSet::IsFixedScreenSize, &BillboardSet::SetFixedScreenSize)
        // [Property] FaceCameraMode faceCameraMode
        .addProperty("faceCameraMode", &BillboardSet::GetFaceCameraMode, &BillboardSet::SetFaceCameraMode)
        // [Property] float animationLodBias
        .addProperty("animationLodBias", &BillboardSet::GetAnimationLodBias, &BillboardSet::SetAnimationLodBias)
        );
}
}

